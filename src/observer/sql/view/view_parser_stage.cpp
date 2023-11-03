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

#include <string.h>
#include <string>

#include "view_parser_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/stmt/stmt.h"
#include "storage/view/view_meta.h"
#include "sql/executor/create_view_executor.h"

using namespace common;

RC ViewParseStage::handle_request(SQLStageEvent *sql_event)
{
  ParsedSqlResult parsed_sql_result;
  Session *session = sql_event->session_event()->session();
  Db* db = session->get_current_db();
  auto input_sql_node = sql_event->sql_node().get();
  std::string view_sql;
  switch (input_sql_node->flag)
  {
  case SCF_SELECT:
    {
      bool has_view = false;
      if (input_sql_node->selection.relations.empty())
      {
        return RC::SUCCESS;
      }
      std::string rel_name = input_sql_node->selection.relations[0].relation_name;
      std::string view_name;
      Table *table = db->find_table(rel_name.c_str());
      if (table == nullptr)
      {
        for (auto viewmeta : db->all_view())
        {
          if (viewmeta.second.get_view_name() == rel_name)
          {
            has_view = true;
            view_name = rel_name;
            break;
          }
        }
        if (!has_view)
          return RC::SUCCESS;
        auto meta = db->get_view(rel_name.c_str());
        view_sql = meta.get_sql_string();
        view_name_ = meta.get_view_name();
        parse(view_sql.c_str(), &parsed_sql_result);
        sql_event->set_view_sql_node(parsed_sql_result.sql_nodes()[0].get()->selection);
        has_view = true;
      }else{
        if (table->check_view())
        {
          view_name = table->name();
          auto meta = db->get_view(rel_name.c_str());
          view_sql = meta.get_sql_string();
          view_name_ = meta.get_view_name();
          parse(view_sql.c_str(), &parsed_sql_result);
          sql_event->set_view_sql_node(parsed_sql_result.sql_nodes()[0].get()->selection);
          has_view = true;
        }
      }
      if (has_view)
      {
        input_sql_node->selection.select_view = true;
        input_sql_node->selection.select_view_sql_node = &sql_event->get_view_sql_node();
        // RC rc = rewrite_sql_node(*input_sql_node,*parsed_sql_result.sql_nodes()[0].get());
        //sql_event->set_sql_node(std::move(parsed_sql_result.sql_nodes()[0]));
        return RC::SUCCESS;
      }
      return RC::SUCCESS;
    }
    break;
  case SCF_CREATE_VIEW:
    {
      return RC::SUCCESS;
    }
    break;
  case SCF_UPDATE:
    {
      bool has_view = false;
      std::string rel_name = input_sql_node->update.relation_name;
      Table *table = db->find_table(rel_name.c_str());
      if (table == nullptr)
      {
        return RC::SUCCESS;
      }
      if(table->check_view())
      {
        std::string view_name = table->name();
        auto meta = db->get_view(rel_name.c_str());
        view_sql = meta.get_sql_string();
        view_name_ = meta.get_view_name();
        parse(view_sql.c_str(), &parsed_sql_result);
        has_view = true;
      }
      if (has_view)
      {
        RC rc = rewrite_sql_node(*input_sql_node,*parsed_sql_result.sql_nodes()[0].get());
        //sql_event->set_sql_node(std::move(parsed_sql_result.sql_nodes()[0]));
        return rc;
      }
    }
    break;
  case SCF_DELETE:
    {
      bool has_view = false;
      std::string rel_name = input_sql_node->deletion.relation_name;
      Table *table = db->find_table(rel_name.c_str());
      if (table == nullptr)
      {
        return RC::SUCCESS;
      }
      if(table->check_view())
      {
        std::string view_name = table->name();
        auto meta = db->get_view(rel_name.c_str());
        view_sql = meta.get_sql_string();
        view_name_ = meta.get_view_name();
        parse(view_sql.c_str(), &parsed_sql_result);
        has_view = true;
      }
      if (has_view)
      {
        RC rc = rewrite_sql_node(*input_sql_node,*parsed_sql_result.sql_nodes()[0].get());
        //sql_event->set_sql_node(std::move(parsed_sql_result.sql_nodes()[0]));
        return rc;
      }
    }
    break;
  case SCF_INSERT:
    {
      bool has_view = false;
      std::string rel_name = input_sql_node->insertion.relation_name;
      std::string view_name;
      Table *table = db->find_table(rel_name.c_str());
      if (table == nullptr)
      {
        for (auto viewmeta : db->all_view())
        {
          if (viewmeta.second.get_view_name() == rel_name)
          {
            has_view = true;
            view_name = rel_name;
            break;
          }
        }
        if (!has_view)
          return RC::SUCCESS;
        auto meta = db->get_view(rel_name.c_str());
        view_sql = meta.get_sql_string();
        view_name_ = meta.get_view_name();
        parse(view_sql.c_str(), &parsed_sql_result);
        has_view = true;
      }else{
        if (table->check_view())
        {
          view_name = table->name();
          auto meta = db->get_view(rel_name.c_str());
          view_sql = meta.get_sql_string();
          view_name_ = meta.get_view_name();
          parse(view_sql.c_str(), &parsed_sql_result);
          has_view = true;

        }
      }
      if (has_view)
      {
        RC rc = rewrite_sql_node(*input_sql_node,*parsed_sql_result.sql_nodes()[0].get());
        //sql_event->set_sql_node(std::move(parsed_sql_result.sql_nodes()[0]));
        return rc;
      }
    }
    break;
  default:
    return RC::SUCCESS;
    break;
  }
  return RC::SUCCESS;
  
  

    
//   RC rc = RC::SUCCESS;
//   SessionEvent *session_event = sql_event->session_event();
//   SqlResult *sql_result = session_event->sql_result();

//   Db *db = session_event->session()->get_current_db();
//   if (nullptr == db) {
//     LOG_ERROR("cannot find current db");
//     rc = RC::SCHEMA_DB_NOT_EXIST;
//     sql_result->set_return_code(rc);
//     sql_result->set_state_string("no db selected");
//     return rc;
//   }

//   ParsedSqlNode *sql_node = sql_event->sql_node().get();
//   Stmt *stmt = nullptr;
//   rc = Stmt::create_stmt(db, *sql_node, stmt);
//   if (rc != RC::SUCCESS && rc != RC::UNIMPLENMENT) {
//     LOG_WARN("failed to create stmt. rc=%d:%s", rc, strrc(rc));
//     sql_result->set_return_code(rc);
//     return rc;
//   }

//   sql_event->set_stmt(stmt);

//   return rc;
}

RC ViewParseStage::rewrite_sql_node(ParsedSqlNode &input_sql_node, ParsedSqlNode &view_sql_node){
  switch (input_sql_node.flag)
  {
  case SCF_SELECT:
    {
      return RC::SUCCESS;
    } 
    break;
   case SCF_CREATE_VIEW:
    {
        
    }
    break;
   case SCF_INSERT:
    {
      input_sql_node.insertion.relation_name = view_sql_node.selection.relations[0].relation_name;
    }
    break;
   case SCF_DELETE:
    {
      input_sql_node.deletion.relation_name = view_sql_node.selection.relations[0].relation_name;
    }
    break;
   case SCF_UPDATE:
    {
      input_sql_node.update.relation_name = view_sql_node.selection.relations[0].relation_name;
    }
    break;
  default:
    break;
  }
  return RC::SUCCESS;
}