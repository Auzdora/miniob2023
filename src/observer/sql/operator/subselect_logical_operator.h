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
// Created by Daijinxiang on 2023/10/26.
//

#pragma once
#include "logical_operator.h"
#include "sql/expr/expression.h"
#include "sql/parser/value.h"
#include <vector>

/**
 * @brief 子查询逻辑算子
 * @ingroup LogicalOperator
 */
class SubselectLogicalOperator : public LogicalOperator
{
public:
  SubselectLogicalOperator(){};
  virtual ~SubselectLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::SUBSELECT;
  }
};