/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Lanbotian on 2023/10/18.
//

#pragma once

#include "sql/operator/logical_operator.h"
#include <string>
#include <vector>

/**
 * @brief 逻辑算子，用于执行delete语句
 * @ingroup LogicalOperator
 */
class AggregationLogicalOperator : public LogicalOperator 
{
public:
  AggregationLogicalOperator(const std::vector<std::string> &aggr_funcs);
  virtual ~AggregationLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::AGGREGATION;
  }
  const std::vector<std::string> &aggr_funcs() const
  {
    return aggr_funcs_;
  }

private:
  std::vector<std::string> aggr_funcs_;
};