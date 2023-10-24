/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Lanbotian on 2023/10/23.
//

#include "sql/operator/sort_physical_operator.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include <algorithm>
#include <vector>

RC SortPhysicalOperator::open(Trx *trx) {
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC SortPhysicalOperator::next() {
  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();
  if (first_call_) {
    while (RC::SUCCESS == (rc = oper->next())) {
      Tuple *tuple = oper->current_tuple();
      if (nullptr == tuple) {
        rc = RC::INTERNAL;
        LOG_WARN("failed to get tuple from operator");
        break;
      }
      if (rc != RC::SUCCESS) {
        return rc;
      }
      ProjectTuple *proj_tuple = static_cast<ProjectTuple *>(tuple);
      ValueListTuple val_tuple;
      std::vector<Value> cells;
      for (int i = 0; i < proj_tuple->cell_num(); i++) {
        Value cell;
        proj_tuple->cell_at(i, cell);
        cells.push_back(cell);
      }
      val_tuple.set_cells(cells);
      tuple_vec_.push_back(val_tuple);
    }
    first_call_ = false;

    auto comparison = [&](const ValueListTuple &t1,
                          const ValueListTuple &t2) -> bool {
      for (int i = 0; i < sort_types_.size(); i++) {
        Value t1_cell;
        Value t2_cell;
        t1.cell_at(sort_index_[i], t1_cell);
        t2.cell_at(sort_index_[i], t2_cell);
        int result = t1_cell.compare(t2_cell);
        if (result != 0) {
          if (sort_types_[i] == OrderType::DESC_T) {
            return result > 0;
          } else if (sort_types_[i] == OrderType::ASC_T) {
            return result < 0;
          }
        }
      }
      return false;
    };
    std::sort(tuple_vec_.begin(), tuple_vec_.end(), comparison);
    return RC::SUCCESS;
  }

  tuple_idx_++;
  if (tuple_idx_ == tuple_vec_.size()) {
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}

RC SortPhysicalOperator::close() {
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *SortPhysicalOperator::current_tuple() { return &tuple_vec_[tuple_idx_]; }