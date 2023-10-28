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
#include "event/sql_debug.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"

RC CreateTableSelectStmt::create(Db *db, const CreateTableSqlNode &create_table, const SelectSqlNode &selection, Stmt *&stmt)
{
  Stmt *select_stmt;
  SelectStmt::create(db, selection, select_stmt);
  stmt = new CreateTableSelectStmt(create_table.relation_name, create_table.attr_infos);
  //sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}
