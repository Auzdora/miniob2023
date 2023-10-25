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

#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/aggr_physical_operator.h"

AggregationPhysicalOperator::AggregationPhysicalOperator(const std::vector<std::string> &aggr_funcs)
    : aggr_funcs_(aggr_funcs)
{
  // init aggr results value
  aggr_results_.reserve(aggr_funcs_.size());
}

RC AggregationPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("aggregation operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC AggregationPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (!first_call_) {
    return RC::RECORD_EOF;
  }
  //   if (children_.empty()) {
  //     return RC::RECORD_EOF;
  //   }
  bool first_loop = true;
  int cnt = 0;
  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    for (int i = 0; i < aggr_funcs_.size(); i++) {
      do_aggregate(tuple, i, first_loop);
    }
    if (first_loop) {
      first_loop = false;
    }
    cnt++;
  }

  // finish all aggregation
  for (int i = 0; i < aggr_funcs_.size(); i++) {
    if (aggr_funcs_[i] == "avg") {
      if (avg_count_results_[i] == 0)
      {
        aggr_results_[i].set_null();                            ///< 除数为0， 结果置null
      }else{
        if (aggr_results_[i].is_null())
           aggr_results_[i].set_null();
        else
          aggr_results_[i].set_float(aggr_results_[i].get_float() / avg_count_results_[i]);
      }
    }
  }
  tuple_.set_cells(aggr_results_);
  if (first_call_) {
    first_call_ = false;
    return RC::SUCCESS;
  }

  return RC::RECORD_EOF;
}

RC AggregationPhysicalOperator::do_count(int idx, Value &val)
{
  aggr_results_[idx].set_int(aggr_results_[idx].get_int() + 1);
  return RC::SUCCESS;
}

RC AggregationPhysicalOperator::do_min(int idx, Value &val)
{
  int ans = aggr_results_[idx].compare(val);
  if (ans > 0) {
    aggr_results_[idx] = val;
    return RC::SUCCESS;
  }
  return RC::SUCCESS;
}

RC AggregationPhysicalOperator::do_max(int idx, Value &val)
{
  int ans = aggr_results_[idx].compare(val);
  if (ans < 0) {
    aggr_results_[idx] = val;
    return RC::SUCCESS;
  }
  return RC::SUCCESS;
}

RC AggregationPhysicalOperator::do_avg(int idx, Value &val) {
  if (aggr_results_[idx].is_null() && val.is_null())
    aggr_results_[idx].set_null();
  else
    aggr_results_[idx].set_float(aggr_results_[idx].get_float() + val.get_float());
  return RC::SUCCESS;
}

RC AggregationPhysicalOperator::do_sum(int idx, Value &val) {
  if (aggr_results_[idx].is_null() && val.is_null())
    aggr_results_[idx].set_null();
  else
    aggr_results_[idx].set_float(aggr_results_[idx].get_float() + val.get_float());
  return RC::SUCCESS;
}

void AggregationPhysicalOperator::do_aggregate(Tuple *tuple, int idx, bool init)
{
  if (init) {
    Value cell;
    tuple->cell_at(idx, cell);
    if (aggr_funcs_[idx] == "count") {
      if (!cell.is_null())
      {
        aggr_results_.push_back(Value(1));
        avg_count_results_.push_back(1);
      } else {
        aggr_results_.push_back(Value(0));
        avg_count_results_.push_back(0);
      } 
    } else if (aggr_funcs_[idx] == "count_star") {
      aggr_results_.push_back(Value(1));
      avg_count_results_.push_back(1);
    } else if (aggr_funcs_[idx] == "min") {
      aggr_results_.push_back(cell);
      avg_count_results_.push_back(1);
    } else if (aggr_funcs_[idx] == "max") {
      aggr_results_.push_back(cell);
      avg_count_results_.push_back(1);
    } else if (aggr_funcs_[idx] == "sum") {
      aggr_results_.push_back(cell);
      avg_count_results_.push_back(1);
    } else {  // avg
      if (!cell.is_null())
      {
        aggr_results_.push_back(cell);
        avg_count_results_.push_back(1);
      } else {
        aggr_results_.push_back(cell);
        avg_count_results_.push_back(0);
      }  
    }
    return;
  }

  Value cell;
  tuple->cell_at(idx, cell);
  if (aggr_funcs_[idx] == "count") {
    if (!cell.is_null())
    {
      aggr_results_[idx].set_int(aggr_results_[idx].get_int() + 1);
      avg_count_results_[idx] += 1;
    }
  } else if (aggr_funcs_[idx] == "count_star") {
    aggr_results_[idx].set_int(aggr_results_[idx].get_int() + 1);
    avg_count_results_[idx] += 1;
  } else if (aggr_funcs_[idx] == "min") {
    do_min(idx, cell);
    avg_count_results_[idx] += 1;
  } else if (aggr_funcs_[idx] == "max") {
    do_max(idx, cell);
    avg_count_results_[idx] += 1;
  } else if (aggr_funcs_[idx] == "sum") {
    do_sum(idx, cell);
    avg_count_results_[idx] += 1;
  } else {  // avg
    do_avg(idx, cell);
    if (!cell.is_null())
    {
      avg_count_results_[idx] += 1;
    }
  }
}

RC AggregationPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *AggregationPhysicalOperator::current_tuple() {
  return &tuple_;
}
