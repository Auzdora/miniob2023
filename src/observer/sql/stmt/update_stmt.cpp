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
#include "common/log/log.h"
#include "storage/db/db.h"

UpdateStmt::UpdateStmt(Table *table, const Value *values, int value_amount,FilterStmt *filter_stmt,std::string attr_name)
    : table_(table), values_(values), value_amount_(value_amount),filter_stmt_(filter_stmt)
{
  this->attr_name_.swap(attr_name);
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const Value *value = &(update.value);
  std::string table_name = update.relation_name;
  if (nullptr == db || table_name.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", 
             db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // 判断table是否存在
  Table *table = db->find_table(table_name.c_str());
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // 检查 field 类型
  bool isIn = false;
  std::string attrName = update.attribute_name;
  const TableMeta &table_meta = table->table_meta();
  const int sys_field_num = table_meta.sys_field_num();
  for (int i = 0; i < table_meta.field_num() - sys_field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
    if (0 == strcmp(attrName.c_str(),field_meta->name())){
      isIn = true;
      const AttrType field_type = field_meta->type();
      const AttrType value_type = value->attr_type();
      if (field_type != value_type) { // TODO try to convert the value type to field type
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d", 
               table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      break;
    }
  }
  if (!isIn){
    // value 的col 不存在
    LOG_WARN("%s not in fields",attrName.c_str());
    return RC::NOTFOUND;
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

  stmt = new UpdateStmt(table,value,1,filter_stmt,attrName);
  return RC::SUCCESS;
}
