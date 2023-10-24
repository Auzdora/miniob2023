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
// Created by Lanbotian on 2023/10/23.
//

#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include <vector>

/**
 * @brief sort物理算子
 * @ingroup PhysicalOperator
 */
class SortPhysicalOperator : public PhysicalOperator
{
public:
  SortPhysicalOperator(const std::vector<Field> &sort_fields, const std::vector<OrderType> &sort_types, const std::vector<int> &sort_index) : sort_fields_(sort_fields), sort_types_(sort_types), sort_index_(sort_index)
  {}

  virtual ~SortPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::SORT;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  std::vector<Field> sort_fields_;
  std::vector<OrderType> sort_types_;
  std::vector<int> sort_index_;
  /** The first call of next*/
  bool first_call_{true};
  /** The vector of sorted tuple*/
  std::vector<ValueListTuple> tuple_vec_{};
  int tuple_idx_{0};
};