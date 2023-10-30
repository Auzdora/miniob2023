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

#include "sql/stmt/create_table_select_stmt.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"

RC CreateTableSelectStmt::create(Db *db, const CreateTableSqlNode &create_table, const SelectSqlNode &selection, Stmt *&stmt)
{
  Stmt *select_stmt;
  RC rc = SelectStmt::create(db, selection, select_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("create table select, select stmt create failed");
    return rc;
  }
  SelectStmt *cast_select_stmt = static_cast<SelectStmt *>(select_stmt);
  const auto &query_fields = cast_select_stmt->query_fields();
  const auto &exprs = cast_select_stmt->query_expressions();
  const auto &expr_names = cast_select_stmt->query_expressions_names();
  const auto &star_field_names = cast_select_stmt->star_field_names();

  stmt = new CreateTableSelectStmt(create_table.relation_name, expr_names, star_field_names, cast_select_stmt, db);
  // extract 
  return RC::SUCCESS;
}
