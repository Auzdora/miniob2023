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

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include <vector>

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class AggregationPhysicalOperator : public PhysicalOperator
{
public:
  AggregationPhysicalOperator(const std::vector<std::string> &aggr_funcs);

  virtual ~AggregationPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::AGGREGATION;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  RC do_count(int idx, Value &val);
  RC do_min(int idx, Value &val);
  RC do_max(int idx, Value &val);
  RC do_sum(int idx, Value &val);
  RC do_avg(int idx, Value &val);

  void do_aggregate(Tuple *tuple, int idx, bool init);

  Tuple *current_tuple() override;

private:
  std::vector<std::string> aggr_funcs_;
  std::vector<Value> aggr_results_;
  ValueListTuple tuple_;
  bool first_call_{true};
};
