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
// Created by Lanbotian on 2023/10/29.
//
#include "sql/operator/create_table_select_logical_operator.h"
#include "sql/operator/create_table_select_physical_operator.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <vector>

RC CreateTableSelectPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  trx_ = trx;
  return children_[0]->open(trx);
}

RC CreateTableSelectPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();
  bool first_round = true;
  Table *new_table;
  
  while(RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }   
    if (first_round) {
      // parse the tuple, and create the table;
      first_round = false;
      const char *table_name = table_name_.c_str();
      std::vector<AttrInfoSqlNode> attr_infos;
      ValueListTuple *val_tuple = static_cast<ValueListTuple *>(tuple);
      if (val_tuple->cell_num() != expr_names_.size()) {
        if (expr_names_.size() == 0) {
          // single * case
          for(const auto name : star_field_names_) {
            expr_names_.push_back(name);
          }
        }
        else {
          std::cout << "val tuple size is not equal to expression, maybe it is a * case" << std::endl;
          return RC::INTERNAL;
        }
      }
      for (int i = 0; i < val_tuple->cell_num(); i++) {
        Value tmp_val;
        val_tuple->cell_at(i, tmp_val);
        AttrInfoSqlNode attr_info;
        attr_info.type = tmp_val.attr_type();
        attr_info.length = tmp_val.length();
        attr_info.name = expr_names_[i];
        attr_info.nullable = tmp_val.is_nullable();
        attr_infos.push_back(attr_info);
      }

      rc = db_->create_table(table_name, expr_names_.size(), attr_infos.data(),is_view_);
      if (rc != RC::SUCCESS) {
        LOG_WARN("create table select failed during create table");
        return rc;
      }
      new_table = db_->find_table(table_name);
      if (new_table == nullptr) {
        LOG_WARN("create table select failed during find table");
        return RC::INTERNAL;
      }
    }

    // insert record into table

    // first create a vector of value
    std::vector<Value> values;
    ValueListTuple *val_tuple = static_cast<ValueListTuple *>(tuple);
    for (int i = 0; i < val_tuple->cell_num(); i++) {
      Value tmp;
      val_tuple->cell_at(i, tmp);
      values.push_back(tmp);
    }
    Record record;
    RC rc = new_table->make_record(static_cast<int>(values.size()), values.data(), record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make record. rc=%s", strrc(rc));
      trx_->delete_record(new_table, record);
      return rc;
    }

    rc = trx_->insert_record(new_table, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make record. rc=%s", strrc(rc));
      trx_->delete_record(new_table, record);
      return rc;
    }
  }
  return RC::RECORD_EOF;
}

RC CreateTableSelectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  first_call_ = true;
  return RC::SUCCESS;
}
Tuple *CreateTableSelectPhysicalOperator::current_tuple()
{
  return nullptr;
}
