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

#pragma once
#include "logical_operator.h"
#include "sql/parser/value.h"
#include <vector>

/**
 * @brief 更新逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const Value values, Field field);
  UpdateLogicalOperator(Table *table, const std::vector<Value> &values, const std::vector<Field> &field);
  UpdateLogicalOperator(Table *table, const std::vector<Value> &values, const std::vector<Field> &field, const std::unordered_map<std::string,int> subselect_map);

  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }

  Table *table() const { return table_; }
  const Value &values() const { return value_; }
  const std::vector<Value> &get_values() const { return values_; }
  std::unordered_map<std::string,int> &get_subselect_map() {return subselect_map_;}
  std::vector<Value> &get_values() { return values_; }
  std::vector<Field> &get_field() { return fields_; }
  Value &values() { return value_; }
  Field &field() { return field_;}

private:
  Table *table_ = nullptr;
  Value value_;
  std::vector<Value> values_;
  std::vector<Field> fields_;
  std::unordered_map<std::string,int> subselect_map_;
  Field field_;
};