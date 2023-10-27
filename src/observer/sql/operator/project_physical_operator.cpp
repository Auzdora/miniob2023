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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include <vector>

RC ProjectPhysicalOperator::open(Trx *trx)
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

  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty() && expressions_.empty()) {
    return RC::RECORD_EOF;
  }
  if (expressions_.empty()) {
    RC rc = children_[0]->next();
    if (rc == RC::NOTFOUND)
      return RC::RECORD_EOF;
    return rc;
  }

  if (children_.empty() && !expressions_.empty()) {
    RowTuple useless;
    std::vector<Value> cells;
    Value cell;
    for (const auto &expr : expressions_) {
      RC rc = expr->get_value(useless, cell);
      if (rc != RC::SUCCESS) {
        LOG_INFO("project expression operator get value error");
        return RC::INTERNAL;
      }
      cells.push_back(cell);
    }
    std::reverse(cells.begin(), cells.end());
    val_tuple_.set_cells(cells);
    if (first_call_) {
      first_call_ = false;
      return RC::SUCCESS;
    }
    return RC::RECORD_EOF;
  }

  // do expression
  RC rc = RC::SUCCESS;
  if (RC::SUCCESS == children_[0]->next()) {
    Tuple *tuple = children_[0]->current_tuple();
    std::vector<Value> cells;
    Value cell;
    for (const auto &expr : expressions_) {
      rc = expr->get_value(*tuple, cell);
      if (rc != RC::SUCCESS) {
        LOG_INFO("project expression operator get value error");
        return RC::INTERNAL;
      }
      cells.push_back(cell);
    }
    std::reverse(cells.begin(), cells.end());

    val_tuple_.set_cells(cells);
  } else {
    return RC::RECORD_EOF;
  }

  return rc;
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  first_call_ = true;
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  if (expressions_.empty()) {
    tuple_.set_tuple(children_[0]->current_tuple());
    return &tuple_;
  }
  return&val_tuple_;
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}
