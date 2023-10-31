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

#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/group_physical_operator.h"
#include "sql/parser/value.h"

GroupByPhysicalOperator::GroupByPhysicalOperator(const std::vector<std::string> &aggr_funcs, std::vector<std::unique_ptr<Expression>> &&expressions, std::vector<Expression *> group_by_expressions)
    : aggr_funcs_(aggr_funcs),
    expressions_(std::move(expressions)),
    group_by_expressions_(group_by_expressions),
    aht_(expressions_, aggr_funcs_),
    aht_iterator_(aht_.Begin())
{
  // init aggr results value
  aggr_results_.reserve(aggr_funcs_.size());
}

RC GroupByPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("aggregation operator must has one child");
    return RC::INTERNAL;
  }
  aht_iterator_ = aht_.Begin();
  first_call_ = true;

  return children_[0]->open(trx);
}

RC GroupByPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (first_call_) {
    PhysicalOperator *oper = children_.front().get();
    // construct hash table
    while (RC::SUCCESS == (rc = oper->next())) {
      Tuple *tuple = oper->current_tuple();
      AggregateKey akey = MakeAggregateKey(tuple);
      AggregateValue avalue = MakeAggregateValue(tuple);
      aht_.InsertCombine(akey, avalue);
    }
    first_call_ = false;
    
    auto avg_result_set = aht_.avg_results();
    for (auto it = aht_.Begin(); it != aht_.End(); ++it) {
      auto avg_result_cnt = avg_result_set[it.Key()];
      aht_.ComputeAvg(it.Key(), avg_result_set[it.Key()]);
    }
    aht_iterator_ = aht_.Begin();
  }

  if (aht_.Begin() == aht_.End()) {
    // no groups, no output
    return RC::RECORD_EOF;
  }

//   if (aht_.Begin() == aht_.End() && !empty_call_) {
//     auto values = aht_.GenerateInitialAggregateValue().aggregates_;
//     *tuple = Tuple{values, &GetOutputSchema()};
//     empty_call_ = true;
//     return true;
//   }

  if (aht_iterator_ == aht_.End()) {
    return RC::RECORD_EOF;
  }

  std::vector<Value> values{};
  int print_size = 0;
  int curr_attr_size = 0;
  for (const auto &expr : expressions_) {
    if (expr->type() == ExprType::AGGREGATION) {
      continue;
    }
    // Value val;
    // expr->get_value(tuple_, val);
    // values.emplace_back(val);
    print_size++;
  }
  for (auto &key : aht_iterator_.Key().group_bys_) {
    if (print_size == curr_attr_size) {
      break;
    }
    values.emplace_back(key);
    curr_attr_size++;
  }
  for (auto &val : aht_iterator_.Val().aggregates_) {
    values.emplace_back(val);
  }
  val_tuple_.set_cells(values);
  ++aht_iterator_;
  return RC::SUCCESS;
}

RC GroupByPhysicalOperator::do_count(int idx, Value &val)
{
  aggr_results_[idx].set_int(aggr_results_[idx].get_int() + 1);
  return RC::SUCCESS;
}

RC GroupByPhysicalOperator::do_min(int idx, Value &val)
{
  int ans = aggr_results_[idx].compare(val);
  if (ans > 0) {
    aggr_results_[idx] = val;
    return RC::SUCCESS;
  }
  return RC::SUCCESS;
}

RC GroupByPhysicalOperator::do_max(int idx, Value &val)
{
  int ans = aggr_results_[idx].compare(val);
  if (ans < 0) {
    aggr_results_[idx] = val;
    return RC::SUCCESS;
  }
  return RC::SUCCESS;
}

RC GroupByPhysicalOperator::do_avg(int idx, Value &val) {
  if (aggr_results_[idx].is_null() && val.is_null())
    aggr_results_[idx].set_null();
  else
    aggr_results_[idx].set_float(aggr_results_[idx].get_float() + val.get_float());
  return RC::SUCCESS;
}

RC GroupByPhysicalOperator::do_sum(int idx, Value &val) {
  if (aggr_results_[idx].is_null() && val.is_null())
    aggr_results_[idx].set_null();
  else
    aggr_results_[idx].set_float(aggr_results_[idx].get_float() + val.get_float());
  return RC::SUCCESS;
}

void GroupByPhysicalOperator::do_aggregate(Tuple *tuple, int idx, bool init)
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

RC GroupByPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  aggr_results_.clear();
  avg_count_results_.clear();
  return RC::SUCCESS;
}

Tuple *GroupByPhysicalOperator::current_tuple() {
  return &val_tuple_;
}
