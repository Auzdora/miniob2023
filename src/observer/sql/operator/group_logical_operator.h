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
// Created by Lanbotian on 2023/10/30.
//

#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include <memory>
#include <string>
#include <vector>

/**
 * @brief 逻辑算子
 * @ingroup LogicalOperator
 */
class GroupByLogicalOperator : public LogicalOperator 
{
public:
  GroupByLogicalOperator(const std::vector<std::string> &aggr_funcs);
  GroupByLogicalOperator(const std::vector<std::string> &aggr_funcs, const std::vector<Expression *> &expressions, const std::vector<Expression *> &group_by_exprs);
  virtual ~GroupByLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::GROUPBY;
  }
  const std::vector<std::string> &aggr_funcs() const
  {
    return aggr_funcs_;
  }
  const std::vector<Expression *> &group_by_exprs()
  {
    return group_by_exprs_;
  }

private:
  std::vector<std::string> aggr_funcs_;
  std::vector<Expression *> group_by_exprs_;
};