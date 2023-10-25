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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"

UpdateStmt::UpdateStmt(Table *table, const std::unordered_map<std::string, std::tuple<const Value*,bool,SelectStmt*>> &update_map, FilterStmt *filter_stmt) : table_(table), update_map_(update_map), filter_stmt_(filter_stmt)
{}

UpdateStmt::UpdateStmt(Table *table, std::vector<const Value*> values, int value_amount, FilterStmt *filter_stmt, std::vector<std::string> attr_names)
    : table_(table), values_(values), value_amount_(value_amount),filter_stmt_(filter_stmt), attr_names_(attr_names)
{}


UpdateStmt::UpdateStmt(Table *table, const Value *values, int value_amount,FilterStmt *filter_stmt,std::string attr_name)
    : table_(table), value_(values), value_amount_(value_amount),filter_stmt_(filter_stmt)
{
  this->attr_name_.swap(attr_name);
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  std::string table_name = update.relation_name;
  if (nullptr == db || table_name.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", 
             db, table_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // 判断table是否存在
  Table *table = db->find_table(table_name.c_str());
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, std::tuple<const Value*,bool,SelectStmt*>> update_map;
  // 循环检查 field 类型
  for (const auto &[attr_name,subSelect,is_value,value] : update.fields) {
    auto num = update_map.size();
    Stmt *subselect_stmt = nullptr;
    if (!is_value)
    {
      RC rc = SelectStmt::create(db,subSelect,subselect_stmt);
      if(rc != RC::SUCCESS)
      {
        return rc;
      }
    }

    // 检查 field 类型
    bool isIn = false;
    std::string attrName = attr_name;
    const TableMeta &table_meta = table->table_meta();
    const int sys_field_num = table_meta.sys_field_num();
    const int cus_field_num = table_meta.custom_fields_num();

    for (int i = 0; i < table_meta.field_num() - sys_field_num - cus_field_num; i++) {
      const FieldMeta *field_meta = table_meta.field(i + sys_field_num + cus_field_num);
      const AttrType field_type = field_meta->type();
      AttrType value_type = AttrType::UNDEFINED;
      // 获取子查询中的返回字段的field
      if (!is_value){
        // 判断子查询查询字段是否为单个字段
        SelectStmt* substmt =static_cast<SelectStmt*>(subselect_stmt);
        if (substmt->query_fields().size() != 1)
          return RC::INTERNAL;
        value_type = substmt->query_fields()[0].attr_type();
      }else{
        value_type = value.attr_type();
      }
      if (0 == strcmp(attrName.c_str(),field_meta->name()))
      {
        isIn = true;
        if (is_value)
          if (table->check_value_null(value,*field_meta)){
            continue;
          }
        if (field_type != value_type) {
          if (!(field_type == AttrType::INTS && value_type == AttrType::FLOATS) &&
              !(field_type == AttrType::FLOATS && value_type == AttrType::INTS)) 
          {
             // TODO try to convert the value type to field type
              LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d", 
                      table_name.c_str(), field_meta->name(), field_type, value_type);
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }   
        }
        break;
      }
    }
    if (!isIn){
      // value 的col 不存在
      LOG_WARN("%s not in fields",attrName.c_str());
      return RC::NOTFOUND;
    }
    update_map.emplace(attr_name,std::tuple<const Value*,bool,SelectStmt*>(&value,is_value,static_cast<SelectStmt*>(subselect_stmt)));
  }

  // 检查 数据是否合法  除了date 其他类型在词法解析时应该有过滤数据应该是合法的
  
  // 构建filter_stmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map,
        update.conditions.data(),
        static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, update_map, filter_stmt);
  return RC::SUCCESS;
}
