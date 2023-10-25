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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include <string>
#include <unordered_map>
#include <vector>

class Table;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt 
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, const std::unordered_map<std::string, std::tuple<const Value*,bool,SelectStmt*>> &update_map, FilterStmt *filter_stmt);
  UpdateStmt(Table *table, std::vector<const Value*> values, int value_amount, FilterStmt *filter_stmt, std::vector<std::string> attr_names);
  UpdateStmt(Table *table, const Value *values, int value_amount,FilterStmt *filter_stmt,const std::string attr_name);
  StmtType type() const override
  {
    return StmtType::UPDATE;
  }

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);
  static bool check_update_type(AttrType val_type, AttrType field_type);

public:
  Table *table() const
  {
    return table_;
  }
  const Value *values() const
  {
    return value_;
  }

  const std::vector<const Value*> &get_values() const
  {
    return values_;
  }

  int value_amount() const
  {
    return value_amount_;
  }
  FilterStmt * filter_stmt()
  {
    return filter_stmt_;
  }

  const std::string attrName() const
  {
    return attr_name_;
  }

  const std::vector<std::string> attrNames() const
  {
    return attr_names_;
  }

  const std::unordered_map<std::string, std::tuple<const Value*,bool,SelectStmt*>> &get_update_map() const
  {
    return update_map_;
  }

private:
  Table *table_ = nullptr;
  const Value *value_ = nullptr;
  FilterStmt *filter_stmt_ = nullptr;
  std::string attr_name_;
  std::vector<std::string> attr_names_;
  std::vector<const Value*> values_; 
  std::unordered_map<std::string, std::tuple<const Value*,bool,SelectStmt*>> update_map_;
  int value_amount_ = 0;
};
