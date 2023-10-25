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

#include "sql/operator/physical_operator.h"
#include <vector>


class Trx;
class DeleteStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table,Value value,Field field) : table_(table),value_(value),field_(field)
  {}
  UpdatePhysicalOperator(Table *table,const std::vector<Value> &values,const std::vector<Field> &fields) : table_(table),values_(values),fields_(fields)
  {}
  UpdatePhysicalOperator(Table *table,const std::vector<Value> &values,const std::vector<Field> &fields,std::unordered_map<std::string,int> subselect_map) 
  : table_(table),values_(values),fields_(fields),subselect_map_(subselect_map)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::UPDATE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override
  {
    return nullptr;
  }

private:
  Table *table_ = nullptr;
  std::vector<Value> values_;
  std::vector<Field> fields_;
  std::unordered_map<std::string,int> subselect_map_;
  Value value_;
  Field field_;
  Trx *trx_ = nullptr;
};
