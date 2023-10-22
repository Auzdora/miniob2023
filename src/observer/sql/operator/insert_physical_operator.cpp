/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/insert_physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

using namespace std;

InsertPhysicalOperator::InsertPhysicalOperator(Table *table, vector<vector<Value>> &&values)
    : table_(table), values_(std::move(values))
{}

RC InsertPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  if (table_->table_meta().multi_index_num() > 0) {
    if (children_.size() != 1) {
      LOG_WARN("insert for multi index operator must has one child");
      return RC::INTERNAL;
    }

    children_[0]->open(trx);

    // do scan
    if (table_->table_meta().multi_index_num() > 0) {
      RC rc = RC::SUCCESS;
      PhysicalOperator *oper = children_.front().get();
      Record record;
      rc = table_->make_record(static_cast<int>(values_[0].size()), values_[0].data(), record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to make record. rc=%s", strrc(rc));
        return rc;
      }
      RowTuple insert_tuple;
      insert_tuple.set_record(&record);
      insert_tuple.set_schema(table_, table_->table_meta().field_metas());

      while (RC::SUCCESS == (rc = oper->next())) {
        Tuple *tuple = oper->current_tuple();
        if (nullptr == tuple) {
          rc = RC::INTERNAL;
          LOG_WARN("failed to get tuple from operator");
          break;
        }

        int same_cnt = 0;
        RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
        for (int i = 0; i < table_->table_meta().multi_index_num(); i++) {
          Value cell;
          Value insert_cell;
          TupleCellSpec spec(table_->name(), table_->table_meta().multi_index(i)->field());
          row_tuple->find_cell(spec, cell);
          insert_tuple.find_cell(spec, insert_cell);
          int result = cell.compare(insert_cell);
          if (result == 0) {
            same_cnt++;
          }
        }

        if (same_cnt == table_->table_meta().multi_index_num()) {
          return RC::INTERNAL;
        }
      }
      if (rc == RC::RECORD_EOF) {
        Record record;
        RC rc = table_->make_record(static_cast<int>(values_[0].size()), values_[0].data(), record);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to make record. rc=%s", strrc(rc));
          return rc;
        }
        rc = table_->insert_record(record);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
        }
        return rc;
      }
      return rc;
    }
  }

  std::vector<Record> succ_record;
  for(auto values:values_)
  {
    Record record;
    RC rc = table_->make_record(static_cast<int>(values.size()), values.data(), record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make record. rc=%s", strrc(rc));
      for(auto srd:succ_record){
        trx->delete_record(table_,record);
      }
      return rc;
    }
    rc = trx->insert_record(table_, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
      for(auto srd:succ_record){
        trx->delete_record(table_,record);
      }
      return rc;
    }
    succ_record.push_back(record);
  }
  return rc;
}

RC InsertPhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC InsertPhysicalOperator::close()
{
  if (table_->table_meta().multi_index_num() > 0) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
