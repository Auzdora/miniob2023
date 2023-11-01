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
// Created by Daijinxiang on 2023/11/1
//

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示创建视图的语句
 * @ingroup Statement
 */
class CreateViewStmt : public Stmt
{
public:
 CreateViewStmt(const std::string &table_name, const std::vector<AttrInfoSqlNode> &attr_infos, SelectSqlNode &select_sqlNode)
        : table_name_(table_name),
          attr_infos_(attr_infos),
          select_sql_node_(select_sqlNode)
  {}
  virtual ~CreateViewStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  const std::string &table_name() const { return table_name_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }
  SelectSqlNode &get_select_sql_node() { return select_sql_node_; }

  static RC create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt, SelectSqlNode &selectSqlNode);

private:
  std::string table_name_;
  SelectSqlNode select_sql_node_;
  std::vector<AttrInfoSqlNode> attr_infos_;
};