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
// Created by Lanbotian on 2023/10/28.
//

#pragma once

#include <string>
#include <vector>

#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示复制表的语句
 * @ingroup Statement
 */
class CreateTableSelectStmt : public Stmt
{
public:
  CreateTableSelectStmt(const std::string &table_name, const std::vector<std::string> &field_names, SelectStmt *select_stmt, Db *db)
        : table_name_(table_name),
          field_names_(field_names),
          select_stmt_(select_stmt),
          db_(db)
  {}
  virtual ~CreateTableSelectStmt() = default;

  StmtType type() const override { return StmtType::CREATE_TABLE_SELECT; }

  const std::string &table_name() const { return table_name_; }
  const std::vector<std::string> &field_names() const { return field_names_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }
  Db *get_db() { return db_; }
  SelectStmt *select_stmt() const { return select_stmt_; }

  static RC create(Db *db, const CreateTableSqlNode &create_table, const SelectSqlNode &selection, Stmt *&stmt);

private:
  Db *db_;
  std::string table_name_;
  std::vector<std::string> field_names_;
  std::vector<AttrInfoSqlNode> attr_infos_;
  SelectStmt *select_stmt_;
};