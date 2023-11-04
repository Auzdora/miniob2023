/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

InsertStmt::InsertStmt(Table *table, std::vector<std::vector<Value>> values, int value_amount, int values_num)
    : table_(table), value_amount_(value_amount), values_num_(values_num)
{
  values_.swap(values);
}

RC InsertStmt::create(Db *db, const InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::vector<std::vector<Value>> records;
  std::vector<Value> add_value;

  for (auto value:inserts.values){

    // check the fields number
    const Value *values = value.data();
    const int value_num = static_cast<int>(value.size());
    const TableMeta &table_meta = table->table_meta();
    int stat_idx = table_meta.sys_field_num() + table_meta.custom_fields_num();
    const int field_num = table_meta.field_num() - table_meta.sys_field_num() - table_meta.custom_fields_num();
    if (inserts.select_view)
    {
      Table *view_table = db->find_table(inserts.view_name.c_str());
      if (!view_table)
      {
        return RC::INTERNAL;
      }
      for (int i = 0; i < field_num;i++){
        bool is_in = false;
        if (inserts.view_string.empty()) {
          // 如果没有在插入时指定字段
          for (auto vfield : *view_table->table_meta().field_metas())
          {
            if (0 == strcmp(vfield.name(),(*table_meta.field_metas())[i + stat_idx].name()))
            {
              is_in = true;
              break;
            }
          }
          if (is_in)
          {
            continue;
          }else{
            if ((*table_meta.field_metas())[i + stat_idx].nullable())
            {
              value.insert(value.begin() + i,Value(AttrType::OBNULL));
              values = value.data();
            }else{
              return RC::INTERNAL;
            }
          }
        } else {
          // 如果有在插入时指定字短
          for (int k = 0; k < inserts.view_string.size(); k++) {
            if (0 == strcmp(inserts.view_string[k].c_str(),(*table_meta.field_metas())[i + stat_idx].name())) {
              is_in = true;
              break;
            }
          }
          if (is_in)
          {
            continue;
          }else{
            if ((*table_meta.field_metas())[i + stat_idx].nullable())
            {
              value.insert(value.begin() + i,Value(AttrType::OBNULL));
              values = value.data();
            }else{
              return RC::INTERNAL;
            }
          }
        }
      }
    }
    if (field_num != value_num && !inserts.select_view) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // check fields type
    const int user_field_start_idx = table_meta.sys_field_num() + table_meta.custom_fields_num();
    for (int i = 0; i < value_num; i++) {
      const FieldMeta *field_meta = table_meta.field(i + user_field_start_idx);
      const AttrType field_type = field_meta->type();
      const AttrType value_type = values[i].attr_type();
      if (table->check_value_null(values[i],*field_meta)){
        continue;
      }
      if (field_type != value_type) {  // TODO try to convert the value type to field type
        if (value_type == CHARS && field_type == TEXTS)
        {
          value[i].cast_type_to(TEXTS);
          continue;
        }
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
    records.push_back(value);
  }

  // everything alright
  stmt = new InsertStmt(table, records, inserts.values[0].size(),inserts.values.size());
  return RC::SUCCESS;
}
