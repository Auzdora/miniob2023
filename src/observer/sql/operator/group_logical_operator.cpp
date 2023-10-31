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

#include "sql/operator/group_logical_operator.h"
#include "sql/expr/expression.h"
#include <memory>
#include <vector>

GroupByLogicalOperator::GroupByLogicalOperator(const std::vector<std::string> &aggr_funcs) : aggr_funcs_(aggr_funcs)
{}

GroupByLogicalOperator::GroupByLogicalOperator(const std::vector<std::string> &aggr_funcs, const std::vector<Expression *> &expressions, const std::vector<Expression *> &group_by_exprs) : aggr_funcs_(aggr_funcs)
{
  for (Expression* expr : expressions) {
    expressions_.emplace_back(expr);
  }
  for (Expression* expr : group_by_exprs) {
    group_by_exprs_.emplace_back(expr);
  }
}