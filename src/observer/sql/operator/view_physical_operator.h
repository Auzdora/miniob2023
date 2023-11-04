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
// Created by Daijinxiang on 2022/07/01.
//

#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include <memory>

/**
 * @brief view 物理算子
 * @ingroup PhysicalOperator
 */
class ViewPhysicalOperator : public PhysicalOperator
{
public:
  ViewPhysicalOperator(Table *table,std::vector<Field> &fields) : table_(table)
  {
    fields_.swap(fields);
  }

  virtual ~ViewPhysicalOperator() = default;

  void add_projection(const Table *table, const FieldMeta *field);

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::PROJECT;
  }


  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const
  {
    return view_tuple_.cell_num();
  }

  Tuple *current_tuple() override;

private:
  ViewTuple view_tuple_;
  std::vector<Field> fields_;
  Table *table_;
};
