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
// Created by Daijinxiang on 2023/10/17.
//

#include "common/log/log.h"
#include "sql/operator/update_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &old_record = row_tuple->record();
    // todo
    Record new_record;
    // 新record data初始化
    char * new_data = (char*) malloc(table_->table_meta().record_size());
    memset(new_data,0,table_->table_meta().record_size());

    // 将更新的数据覆盖到新record对应的field中
    memcpy(new_data,old_record.data(),table_->table_meta().record_size());
    if (value_.is_null()){
      auto field = table_->table_meta().field(NULLABLE_TABLE_STRING);
      common::Bitmap nullable_table(old_record.data()+field->offset(),NULL_BITMAP_SIZE);
      nullable_table.set_bit(table_->table_meta().find_user_index_by_field(field_.field_name()));
      //  拷贝 新的null表到新record中
      memcpy(new_data+field->offset(),nullable_table.data(),field_.meta()->len());
      memset(new_data+field_.meta()->offset(),0,field_.meta()->len());
    }else{
      memcpy(new_data+field_.meta()->offset(),value_.data(),field_.meta()->len());
    }
    new_record.set_data(new_data,table_->table_meta().record_size());

    rc = trx_->update_record(table_, old_record,new_record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }
    free(new_data);
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}