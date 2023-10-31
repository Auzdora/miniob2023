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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt 
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const
  {
    return tables_;
  }
  const std::vector<Field> &query_fields() const
  {
    return query_fields_;
  }
  const std::vector<Field> &sort_fields() const
  {
    return sort_fields_;
  }
  const std::vector<OrderType> &sort_types() const
  {
    return sort_types_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
  FilterStmt *having_filter_stmt() const
  {
    return having_filter_stmt_;
  }
  const bool use_group_by() const {
    return use_group_by_;
  }
  std::vector<FilterStmt *> filter_stmts() const
  {
    return filter_stmts_;
  }
  const std::vector<std::string> &aggr_funcs() const
  {
    return aggr_funcs_;
  }
  const std::vector<Expression *> &query_expressions() const
  {
    return query_expressions_;
  }
  const std::vector<Expression *> &group_by_exprs() const
  {
    return group_by_exprs_;
  }
  const std::vector<std::string> &query_expressions_names() const
  {
    return query_expressions_names_;
  }

  const std::vector<std::string> &star_field_names() const
  {
    return start_field_names_;
  }

private:
  std::vector<Field> sort_fields_;
  std::vector<OrderType> sort_types_;
  std::vector<std::string> aggr_funcs_;
  std::vector<Field> query_fields_;
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr;
  FilterStmt *having_filter_stmt_ = nullptr;
  bool use_group_by_ = false;
  std::vector<Expression *> group_by_exprs_;
  std::vector<FilterStmt *> filter_stmts_;   // 多个filter for join 或者其他筛选
  std::vector<Expression *> query_expressions_;
  std::vector<std::string> query_expressions_names_;
  std::vector<std::string> start_field_names_; // 为create table select 创建，特殊情况
  std::vector<std::string> original_col_names_; // 为create table select 创建，处理名字的情况
};
