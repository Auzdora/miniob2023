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
// Created by Longda on 2021/4/13.
//

#include "session_stage.h"

#include <string.h>
#include <string>

#include "common/conf/ini.h"
#include "common/log/log.h"
#include "common/lang/mutex.h"
#include "common/lang/string.h"
#include "common/seda/callback.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "net/server.h"
#include "net/communicator.h"
#include "session/session.h"
#include "event/sql_debug.h"
#include "sql/parser/parse_defs.h"

using namespace common;

// Constructor
SessionStage::SessionStage(const char *tag) : Stage(tag)
{}

// Destructor
SessionStage::~SessionStage()
{}

// Parse properties, instantiate a stage object
Stage *SessionStage::make_stage(const std::string &tag)
{
  SessionStage *stage = new (std::nothrow) SessionStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecutorStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

// Set properties for this object set in stage specific properties
bool SessionStage::set_properties()
{
  //  std::string stageNameStr(stage_name_);
  //  std::map<std::string, std::string> section = g_properties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

// Initialize stage params and validate outputs
bool SessionStage::initialize()
{
  return true;
}

// Cleanup after disconnection
void SessionStage::cleanup()
{

}

void SessionStage::handle_event(StageEvent *event)
{
  // right now, we just support only one event.
  handle_request(event);

  event->done_immediate();
  return;
}

void SessionStage::handle_request(StageEvent *event)
{
  SessionEvent *sev = dynamic_cast<SessionEvent *>(event);
  if (nullptr == sev) {
    LOG_ERROR("Cannot cat event to sessionEvent");
    return;
  }

  std::string sql = sev->query();
  if (common::is_blank(sql.c_str())) {
    return;
  }

  Session::set_current_session(sev->session());
  sev->session()->set_current_request(sev);
  SQLStageEvent sql_event(sev, sql);
  (void)handle_sql(&sql_event);

  Communicator *communicator = sev->get_communicator();
  bool need_disconnect = false;
  RC rc = communicator->write_result(sev, need_disconnect);
  if (sql_event.sql_node() != nullptr) {
    RC rc2 = handle_update_view_table(&sql_event);
  }
  LOG_INFO("write result return %s", strrc(rc));
  if (need_disconnect) {
    Server::close_connection(communicator);
  }
  sev->session()->set_current_request(nullptr);
  Session::set_current_session(nullptr);
}

/**
 * 处理一个SQL语句经历这几个阶段。
 * 虽然看起来流程比较多，但是对于大多数SQL来说，更多的可以关注parse和executor阶段。
 * 通常只有select、delete等带有查询条件的语句才需要进入optimize。
 * 对于DDL语句，比如create table、create index等，没有对应的查询计划，可以直接搜索
 * create_table_executor、create_index_executor来看具体的执行代码。
 * select、delete等DML语句，会产生一些执行计划，如果感觉繁琐，可以跳过optimize直接看
 * execute_stage中的执行，通过explain语句看需要哪些operator，然后找对应的operator来
 * 调试或者看代码执行过程即可。
 */
RC SessionStage::handle_sql(SQLStageEvent *sql_event)
{
  RC rc = query_cache_stage_.handle_request(sql_event);
  if (OB_FAIL(rc)) {
    LOG_TRACE("failed to do query cache. rc=%s", strrc(rc));
    return rc;
  }

  rc = parse_stage_.handle_request(sql_event);
  if (OB_FAIL(rc)) {
    LOG_TRACE("failed to do parse. rc=%s", strrc(rc));
    return rc;
  }

  rc = view_parse_stage_.handle_request(sql_event);
  if (OB_FAIL(rc)) {
    LOG_TRACE("failed to do parse. rc=%s", strrc(rc));
    return rc;
  }

  rc = resolve_stage_.handle_request(sql_event);
  if (OB_FAIL(rc)) {
    LOG_TRACE("failed to do resolve. rc=%s", strrc(rc));
    return rc;
  }
  
  rc = optimize_stage_.handle_request(sql_event);
  if (rc != RC::UNIMPLENMENT && rc != RC::SUCCESS) {
    LOG_TRACE("failed to do optimize. rc=%s", strrc(rc));
    return rc;
  }
  
  rc = execute_stage_.handle_request(sql_event);
  if (OB_FAIL(rc)) {
    LOG_TRACE("failed to do execute. rc=%s", strrc(rc));
    return rc;
  }

  return rc;
}


RC SessionStage::handle_update_view_table(SQLStageEvent * sql_event){
  RC rc = RC::SUCCESS;
  Session *session = sql_event->session_event()->session();
  Db* db = session->get_current_db();
  std::string table_name;
  switch (sql_event->sql_node()->flag)
  {
  case SCF_INSERT:
    {
      table_name = sql_event->sql_node()->insertion.relation_name;
    }
    break;
  case SCF_UPDATE:
    {
      table_name = sql_event->sql_node()->update.relation_name;
    }
    break;
  case SCF_DELETE:
    {
      table_name = sql_event->sql_node()->deletion.relation_name;
    }
    break;
  default:
    return RC::SUCCESS;
    break;
  }
  const std::unordered_map<std::string, ViewMeta> views = db->all_view();
  bool is_in = false;
  ViewMeta viewmeta;
  for (auto &itr : views)
  {
    for (auto rel : itr.second.relate_tables())
    {
      if (rel == table_name)
      {
        is_in = true;
        viewmeta = itr.second;
        break;
      }
    }
    if (is_in)
      break;
  }
  if (is_in)
  {
    db->drop_table(viewmeta.get_view_name().c_str());
    std::unique_ptr<ParsedSqlNode> create_view_sql = std::unique_ptr<ParsedSqlNode>(new ParsedSqlNode(SCF_CREATE_VIEW));
    ParsedSqlResult parsed_sql_result;
    std::string view_sql = viewmeta.get_sql_string();
    create_view_sql->create_table.use_select = true;
    create_view_sql->create_table.is_view = true;

    parse(view_sql.c_str(), &parsed_sql_result);
    create_view_sql->selection = parsed_sql_result.sql_nodes()[0].get()->selection;
    create_view_sql->create_table.relation_name = viewmeta.get_view_name();

    sql_event->set_sql_node(std::move(create_view_sql));

    rc = view_parse_stage_.handle_request(sql_event);
    if (OB_FAIL(rc)) {
      LOG_TRACE("failed to do parse. rc=%s", strrc(rc));
      return rc;
    }
    
    rc = resolve_stage_.handle_request(sql_event);
    if (OB_FAIL(rc)) {
      LOG_TRACE("failed to do resolve. rc=%s", strrc(rc));
      return rc;
    }
    
    rc = optimize_stage_.handle_request(sql_event);
    if (rc != RC::UNIMPLENMENT && rc != RC::SUCCESS) {
      LOG_TRACE("failed to do optimize. rc=%s", strrc(rc));
      return rc;
    }
    
    rc = execute_stage_.handle_request(sql_event);
    if (OB_FAIL(rc)) {
      LOG_TRACE("failed to do execute. rc=%s", strrc(rc));
      return rc;
    }

    SqlResult *sql_result = sql_event->session_event()->sql_result();
    rc = sql_result->open();
    Tuple *tuple = nullptr;
    while(sql_result->next_tuple(tuple) == RC::SUCCESS)
    {

    }
    return RC::SUCCESS;
    sql_result->close();
  }
  return RC::SUCCESS;
}