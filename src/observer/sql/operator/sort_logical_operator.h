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

#include <string>
#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief sort 表示order by排序运算
 * @ingroup LogicalOperator
 * @details 从表中获取数据后，在内存中对所有tuple排序
 */
class SortLogicalOperator : public LogicalOperator 
{
public:
  SortLogicalOperator(const std::vector<Field> &sort_fields, const std::vector<OrderType> &sort_types,
  const std::vector<int> &sort_idx);
  virtual ~SortLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::SORT;
  }
  const std::vector<Field> &sort_fields() const
  {
    return sort_fields_;
  }
  const std::vector<OrderType> &sort_types() const
  {
    return sort_types_;
  }
  const std::vector<int> &sort_idx() const
  {
    return sort_idx_;
  }

private:
  std::vector<Field> sort_fields_;
  std::vector<OrderType> sort_types_;
  std::vector<int> sort_idx_;
};