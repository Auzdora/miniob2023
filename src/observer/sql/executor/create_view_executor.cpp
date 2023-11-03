//
// Created by Daijinxiang on 2023/11/1
//

#include "sql/executor/create_view_executor.h"

#include "session/session.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "sql/stmt/create_view_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "storage/db/db.h"

RC CreateViewExecutor::execute(SQLStageEvent *sql_event)
{
  Session *session = sql_event->session_event()->session();
  Db *db = session->get_current_db();
  Stmt *stmt = nullptr;
  RC rc = Stmt::create_stmt(db, *sql_event->sql_node().get(), stmt);
  
  ASSERT(stmt->type() == StmtType::CREATE_VIEW, 
         "create table executor can not run this command: %d", static_cast<int>(stmt->type()));

  CreateViewStmt *create_view_stmt = static_cast<CreateViewStmt *>(stmt);

  const int attribute_count = static_cast<int>(create_view_stmt->attr_infos().size());

  const char *table_name = create_view_stmt->table_name().c_str();
  rc = session->get_current_db()->create_table(table_name, attribute_count, create_view_stmt->attr_infos().data(),true);
  RC rc1 = session->get_current_db()->create_view(table_name,create_view_stmt->get_select_sql_node());

  return rc;
}