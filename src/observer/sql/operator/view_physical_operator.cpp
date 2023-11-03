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
// Created by Daijinxiang on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/operator/view_physical_operator.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include <vector>

RC ViewPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  int user_field_idx = table_->table_meta().sys_field_num() + table_->table_meta().custom_fields_num();
  view_tuple_.set_schema(table_, table_->table_meta().field_metas(),user_field_idx);

  return RC::SUCCESS;
}

RC ViewPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  while (RC::SUCCESS == (rc = children_[0]->next())) {
    Tuple *tuple = children_[0]->current_tuple();
    view_tuple_.clear();
    view_tuple_.set_valuelist(tuple);
    break;
  }
  return rc;
}

RC ViewPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ViewPhysicalOperator::current_tuple()
{
  return &view_tuple_;
}

void ViewPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
//   tuple_.add_cell_spec(spec);
}
