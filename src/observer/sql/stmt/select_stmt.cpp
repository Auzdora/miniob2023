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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <vector>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
  if (!filter_stmts_.empty()) {
    for (auto filter:filter_stmts_)
    {
      delete filter;
      filter = nullptr;
    }
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num() + table_meta.custom_fields_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // create a map between alias and original name which stored in database
  // whenever you access a table or attr using alias, you have to lookup
  // this map first
  std::unordered_map<std::string, std::string> rel_alias_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    if (!select_sql.relations[i].alias.empty()) {
      rel_alias_map.insert(std::pair<std::string, std::string>(select_sql.relations[i].alias, select_sql.relations[i].relation_name));
    }
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].relation_name.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
    if (!select_sql.relations[i].alias.empty()) {
      table_map.insert(std::pair<std::string, Table *>(select_sql.relations[i].alias.c_str(), table));
    }
  }

  for (const auto &[relation_name, alias] : select_sql.rel_alias) {
    auto it = table_map.find(relation_name);
    if (it != table_map.end()) {
      continue;
    }
    Table *table = db->find_table(relation_name.c_str());
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), relation_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    table_map.insert(std::pair<std::string, Table *>(relation_name, table));
    if (!alias.empty()) {
      table_map.insert(std::pair<std::string, Table *>(alias, table));
    }
  }

  // collect join tables in `inner join` statement
  for (size_t i = 0; i < select_sql.innerJoins.size(); i++) {
    const char *table_name = select_sql.innerJoins[i].relation.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
      }

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else if (0 != strcmp(table_name, "*") && 0 == strcmp(field_name, "*")){
        Table *table = table_map.at(table_name);
        wildcard_fields(table, query_fields);
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*") && select_sql.aggregations.size() > 0) {
          query_fields.push_back(Field(table, new FieldMeta("*",AttrType::AGGRSTAR, 0, 1,true, true))); // TODO 逻辑要理一下
        } else if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // collect aggregation functions in `select` statement
  // TODO: not support multi table for now
  std::vector<std::string> aggr_funcs;

  // TODO if add group by, the logic should be changed
  if (select_sql.aggregations.size() > 0 && select_sql.aggregations.size() != select_sql.attributes.size()) {
    return RC::INTERNAL;
  }
  for (int i = static_cast<int>(select_sql.aggregations.size()) - 1; i >= 0; i--) {
    const AggrAttrSqlNode &aggr_attr = select_sql.aggregations[i];
    if (0 == strcmp(aggr_attr.attribute_name.c_str(), "*")) {
      aggr_funcs.push_back(aggr_attr.aggregation_name);
      continue;
    }
    Table *table;
    if (default_table != nullptr) {
      table = default_table;
    } else {
      table = table_map.at(aggr_attr.relation_name);;
    }
    const FieldMeta *field_meta = table->table_meta().field(aggr_attr.attribute_name.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), aggr_attr.attribute_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    aggr_funcs.push_back(aggr_attr.aggregation_name);
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  // create filters statement in `inner join` statement
  std::vector<FilterStmt *> filter_stmts;
  for (size_t i = 0; i < select_sql.innerJoins.size(); i++)
  {
    RC rc = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.innerJoins[i].conditions.data(),
      static_cast<int>(select_sql.innerJoins[i].conditions.size()),
      filter_stmt, select_sql.rel_alias);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
    filter_stmts.emplace_back(filter_stmt);
  }

  // create filter statement in `where` statement
  filter_stmt = nullptr;
  RC rc = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt, select_sql.rel_alias);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // collect order by information
  std::vector<OrderType> sort_types;
  std::vector<Field> sort_fields;
  for (int i=0; i < select_sql.orderbys.size(); i++) {
    const OrderBySqlNode &order_by = select_sql.orderbys[i];
    const char *table_name = order_by.relation_name.c_str();
    const char *field_name = order_by.attribute_name.c_str();
    auto iter = table_map.find(table_name);
    if (iter == table_map.end() && select_sql.relations.size() > 1) {
      LOG_WARN("no such table in from list: %s", table_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    Table *table = nullptr;
    if (select_sql.relations.size() == 1) {
      table = table_map.begin()->second;
    } else {
      table = iter->second;
    }
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    sort_fields.push_back(Field(table, field_meta));
    sort_types.push_back(order_by.order_type);
  }

  // collect query expressions information
  std::vector<Expression *> query_expressions;
  std::vector<std::string> query_expressions_names;
  for (int i=0; i < select_sql.expressions.size(); i++) {
    Expression *expr = select_sql.expressions[i].expression;
    if (expr == nullptr) {
      continue;
    }
    expr->init(db, default_table, &table_map);
    if (expr->star_expr()) {
      const auto &star_expr = static_cast<FieldExpr *>(expr);
      for (const auto &name : star_expr->names()) {
        query_expressions_names.push_back(name);
      }
      query_expressions.push_back(expr);
      continue;
    }
    query_expressions.push_back(expr);
    query_expressions_names.push_back(expr->name());
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->aggr_funcs_.swap(aggr_funcs);
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->filter_stmts_.swap(filter_stmts);
  select_stmt->sort_fields_.swap(sort_fields);
  select_stmt->sort_types_.swap(sort_types);
  select_stmt->query_expressions_.swap(query_expressions);
  select_stmt->query_expressions_names_.swap(query_expressions_names);
  stmt = select_stmt;
  return RC::SUCCESS;
}
