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
#include "sql/parser/parse_defs.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include <vector>

void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num() + table_meta.custom_fields_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}


RC CreateViewStmt::create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt, SelectSqlNode &selectSqlNode)
{
  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < selectSqlNode.relations.size(); i++) {
    const char *table_name = selectSqlNode.relations[i].relation_name.c_str();
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
    if (!selectSqlNode.relations[i].alias.empty()) {
      table_map.insert(std::pair<std::string, Table *>(selectSqlNode.relations[i].alias.c_str(), table));
    }
  }

  for (const auto &[relation_name, alias] : selectSqlNode.rel_alias) {
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

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  std::vector<std::string> star_field_names;
  for (int i = static_cast<int>(selectSqlNode.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = selectSqlNode.attributes[i];

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
        for (const auto &field : query_fields) {
          star_field_names.push_back(field.field_name());
        }
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
        if (0 == strcmp(field_name, "*") && selectSqlNode.aggregations.size() > 0) {
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

  std::vector<AttrInfoSqlNode> attr_infos;
  for (const auto &field : query_fields) {
    AttrInfoSqlNode attr_info;
    attr_info.length = field.meta()->len();
    attr_info.name = field.field_name();
    attr_info.nullable = field.meta()->nullable();
    attr_info.type = field.attr_type();
    attr_infos.push_back(attr_info);
  }

  stmt = new CreateViewStmt(create_table.relation_name, attr_infos, selectSqlNode);
  //sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}