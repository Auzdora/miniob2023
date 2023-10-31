/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Lanbotian on 2023/10/23.
//
#pragma once

#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/value.h"
#include <memory>
#include <unordered_map>
#include <vector>
using hash_t = std::size_t;
/**
 * @brief GroupBy物理算子
 * @ingroup PhysicalOperator
 */

class HashUtil {
private:
  static const hash_t PRIME_FACTOR = 10000019;

public:
  static inline auto HashBytes(const char *bytes, size_t length) -> hash_t {
    // https://github.com/greenplum-db/gpos/blob/b53c1acd6285de94044ff91fbee91589543feba1/libgpos/src/utils.cpp#L126
    hash_t hash = length;
    for (size_t i = 0; i < length; ++i) {
      hash = ((hash << 5) ^ (hash >> 27)) ^ bytes[i];
    }
    return hash;
  }

  static inline auto CombineHashes(hash_t l, hash_t r) -> hash_t {
    hash_t both[2] = {};
    both[0] = l;
    both[1] = r;
    return HashBytes(reinterpret_cast<char *>(both), sizeof(hash_t) * 2);
  }

  static inline auto SumHashes(hash_t l, hash_t r) -> hash_t {
    return (l % PRIME_FACTOR + r % PRIME_FACTOR) % PRIME_FACTOR;
  }

  template <typename T> static inline auto Hash(const T *ptr) -> hash_t {
    return HashBytes(reinterpret_cast<const char *>(ptr), sizeof(T));
  }

  template <typename T> static inline auto HashPtr(const T *ptr) -> hash_t {
    return HashBytes(reinterpret_cast<const char *>(&ptr), sizeof(void *));
  }

  /** @return the hash of the value */
  static inline auto HashValue(const Value *val) -> hash_t {
    switch (val->attr_type()) {
    case AttrType::INTS: {
      auto raw = static_cast<int64_t>(val->get_int());
      return Hash<int64_t>(&raw);
    }
    case AttrType::BOOLEANS: {
      auto raw = val->get_boolean();
      return Hash<bool>(&raw);
    }
    case AttrType::CHARS: {
      auto raw = val->get_string();
      auto len = val->length();
      return HashBytes(raw.c_str(), len);
    }
    case AttrType::FLOATS: {
      auto raw = val->get_float();
      return Hash<float>(&raw);
    }
    case AttrType::OBNULL: {
      int raw = -9999;
      return Hash<int>(&raw);
    }
    default: {
      LOG_ERROR("Unsupported type.");
    }
    }
  }
};

struct AggregateKey {
  /** The group-by values */
  std::vector<Value> group_bys_;

  auto operator==(const AggregateKey &other) const -> bool {
    for (uint32_t i = 0; i < other.group_bys_.size(); i++) {
      if (group_bys_[i].compare(other.group_bys_[i])) {
        return false;
      }
    }
    return true;
  }
};

struct AggregateValue {
  /** The aggregate values */
  std::vector<Value> aggregates_;
};

namespace std {

/** Implements std::hash on AggregateKey */
template <>
struct hash<AggregateKey> {
  auto operator()(const AggregateKey &agg_key) const -> std::size_t {
    size_t curr_hash = 0;
    for (const auto &key : agg_key.group_bys_) {
      if (!key.is_null()) {
        curr_hash = HashUtil::CombineHashes(curr_hash, HashUtil::HashValue(&key));
      }
    }
    return curr_hash;
  }
};
}

class SimpleAggregationHashTable {
public:
  /**
   * Construct a new SimpleAggregationHashTable instance.
   * @param agg_exprs the aggregation expressions
   * @param agg_types the types of aggregations
   */
  SimpleAggregationHashTable(
      const std::vector<std::unique_ptr<Expression>> &aggr_exprs,
      const std::vector<std::string> &aggr_funcs)
      : aggr_exprs_{aggr_exprs}, aggr_funcs_{aggr_funcs} {}

  auto GenerateInitialAggregateValue() -> AggregateValue {
    std::vector<Value> values{};
    for (int i = 0; i < aggr_funcs_.size(); i++) {
      if (aggr_funcs_[i] == "count") {
        values.emplace_back(Value(0));
      } else if (aggr_funcs_[i] == "count_star") {
        values.emplace_back(Value(0));
      } else if (aggr_funcs_[i] == "min") {
        Value val;
        val.set_null();
        values.emplace_back(val);
      } else if (aggr_funcs_[i] == "max") {
        Value val;
        val.set_null();
        values.emplace_back(val);
      } else if (aggr_funcs_[i] == "sum") {
        Value val;
        val.set_null();
        values.emplace_back(val);
      } else if (aggr_funcs_[i] == "avg") {
        values.emplace_back(Value(0));
      }
    }
    return {values};
  }

  void CombineAggregateValues(AggregateValue *result, std::vector<int> &avg_count_result,
                              const AggregateValue &input) {
    for (int i = 0; i < aggr_funcs_.size(); i++) {
      if (aggr_funcs_[i] == "count") {
        if (!input.aggregates_[i].is_null()) {
          result->aggregates_[i].set_int(result->aggregates_[i].get_int() + 1);
          avg_count_result[i] += 1;
        }
      } else if (aggr_funcs_[i] == "count_star") {
        result->aggregates_[i].set_int(result->aggregates_[i].get_int() + 1);
        avg_count_result[i] += 1;
      } else if (aggr_funcs_[i] == "min") {
        if (result->aggregates_[i].is_null() && !input.aggregates_[i].is_null()) {
            result->aggregates_[i] = input.aggregates_[i];
            avg_count_result[i] += 1;
            continue;
        }
        int ans = result->aggregates_[i].compare(input.aggregates_[i]);
        if (ans > 0) {
            result->aggregates_[i] = input.aggregates_[i];
        }
        avg_count_result[i] += 1;
      } else if (aggr_funcs_[i] == "max") {
        if (result->aggregates_[i].is_null() && !input.aggregates_[i].is_null()) {
            result->aggregates_[i] = input.aggregates_[i];
            avg_count_result[i] += 1;
            continue;
        }
        int ans = result->aggregates_[i].compare(input.aggregates_[i]);
        if (ans < 0) {
            result->aggregates_[i] = input.aggregates_[i];
        }
        avg_count_result[i] += 1;
        // avg_count_results_[idx] += 1;
      } else if (aggr_funcs_[i] == "sum") {
        if (result->aggregates_[i].is_null() && input.aggregates_[i].is_null()) {
            result->aggregates_[i].set_null();
            avg_count_result[i] += 1;
            continue;
        }
        if (result->aggregates_[i].is_null()) {
            result->aggregates_[i] = Value(0);
        }
        result->aggregates_[i].set_float(result->aggregates_[i].get_float() + input.aggregates_[i].get_float());
        avg_count_result[i] += 1;
      } else if (aggr_funcs_[i] == "avg") {
        if (result->aggregates_[i].is_null() && input.aggregates_[i].is_null()) {
            result->aggregates_[i].set_null();
            continue;
        }
        if (result->aggregates_[i].is_null()) {
            result->aggregates_[i] = Value(0);
        }
        result->aggregates_[i].set_float(result->aggregates_[i].get_float() + input.aggregates_[i].get_float());
        avg_count_result[i] += 1;
      }
    }
  }

  /**
   * Inserts a value into the hash table and then combines it with the current
   * aggregation.
   * @param agg_key the key to be inserted
   * @param agg_val the value to be inserted
   */
  void InsertCombine(const AggregateKey &agg_key,
                     const AggregateValue &agg_val) {
    if (ht_.count(agg_key) == 0) {
      ht_.insert({agg_key, GenerateInitialAggregateValue()});
      for (int i = 0; i < aggr_funcs_.size(); i++) {
        aggr_results_set_[agg_key].push_back(0);
      }
    }
    CombineAggregateValues(&ht_[agg_key], aggr_results_set_[agg_key], agg_val);
  }

  void ComputeAvg(const AggregateKey &agg_key, std::vector<int> avg_cnt) {
    for(int i = 0; i < aggr_funcs_.size(); i++) {
      if (aggr_funcs_[i] == "avg") {
        ht_[agg_key].aggregates_[i].set_float(ht_[agg_key].aggregates_[i].get_float() / avg_cnt[i]);
      }
    }
  }

  const std::unordered_map<AggregateKey, std::vector<int>> &avg_results() const { return aggr_results_set_; }

  /**
   * Clear the hash table
   */
  void Clear() { ht_.clear(); }

  /** An iterator over the aggregation hash table */
  class Iterator {
  public:
    /** Creates an iterator for the aggregate map. */
    explicit Iterator(
        std::unordered_map<AggregateKey, AggregateValue>::const_iterator iter)
        : iter_{iter} {}

    /** @return The key of the iterator */
    auto Key() -> const AggregateKey & { return iter_->first; }

    /** @return The value of the iterator */
    auto Val() -> const AggregateValue & { return iter_->second; }

    /** @return The iterator before it is incremented */
    auto operator++() -> Iterator & {
      ++iter_;
      return *this;
    }

    /** @return `true` if both iterators are identical */
    auto operator==(const Iterator &other) -> bool {
      return this->iter_ == other.iter_;
    }

    /** @return `true` if both iterators are different */
    auto operator!=(const Iterator &other) -> bool {
      return this->iter_ != other.iter_;
    }

  private:
    /** Aggregates map */
    std::unordered_map<AggregateKey, AggregateValue>::const_iterator iter_;
  };

  /** @return Iterator to the start of the hash table */
  auto Begin() -> Iterator { return Iterator{ht_.cbegin()}; }

  /** @return Iterator to the end of the hash table */
  auto End() -> Iterator { return Iterator{ht_.cend()}; }

private:
  /** The hash table is just a map from aggregate keys to aggregate values */
  std::unordered_map<AggregateKey, AggregateValue> ht_{};
  std::unordered_map<AggregateKey, std::vector<int>> aggr_results_set_;
  /** The aggregate expressions that we have */
  const std::vector<std::unique_ptr<Expression>> &aggr_exprs_;
  /** The types of aggregations that we have */
  const std::vector<std::string> &aggr_funcs_;
};

class GroupByPhysicalOperator : public PhysicalOperator {
public:
  GroupByPhysicalOperator(
      const std::vector<std::string> &aggr_funcs,
      std::vector<std::unique_ptr<Expression>> &&expressions,
      std::vector<Expression *> group_by_expressions);
  void add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions) {
    expressions_ = std::move(expressions);
  }

  void add_group_by_expressions(const std::vector<Expression *> &&expressions) {
    group_by_expressions_ = expressions;
  }

  virtual ~GroupByPhysicalOperator() = default;

  PhysicalOperatorType type() const override {
    return PhysicalOperatorType::GROUPBY;
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
  /** @return The tuple as an AggregateKey */
  auto MakeAggregateKey(const Tuple *tuple) -> AggregateKey {
    std::vector<Value> keys;
    for (const auto &expr : group_by_expressions_) {
      Value val;
      RC rc = expr->get_value(*tuple, val);
      keys.emplace_back(val);
    }
    return {keys};
  }

  /** @return The tuple as an AggregateValue */
  auto MakeAggregateValue(const Tuple *tuple) -> AggregateValue {
    std::vector<Value> vals;
    for (const auto &expr : expressions_) {
      if (expr->type() == ExprType::AGGREGATION) {
        Value val;
        RC rc = expr->get_value(*tuple, val);
        vals.emplace_back(val);
      }
    }
    std::reverse(vals.begin(), vals.end());
    return {vals};
  }
  std::vector<std::unique_ptr<Expression>> expressions_;
  std::vector<Expression *> group_by_expressions_;
  std::vector<std::string> aggr_funcs_;
  std::vector<int> avg_count_results_;
  std::vector<Value> aggr_results_;
  ValueListTuple tuple_;
  ValueListTuple val_tuple_;
  /** Simple aggregation hash table */
  SimpleAggregationHashTable aht_;
  /** Simple aggregation hash table iterator */
  SimpleAggregationHashTable::Iterator aht_iterator_;
  bool first_call_{true};
};
