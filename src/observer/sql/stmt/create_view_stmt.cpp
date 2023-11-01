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

#include "sql/stmt/create_view_stmt.h"

RC CreateViewStmt::create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt, SelectSqlNode &selectSqlNode)
{


  
  stmt = new CreateViewStmt(create_table.relation_name, create_table.attr_infos,selectSqlNode);
  //sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}