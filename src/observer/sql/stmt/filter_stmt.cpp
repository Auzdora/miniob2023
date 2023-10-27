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

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit_expr(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  if (condition.left_type == CON_ATTR_T) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
  } else if(condition.left_type == CON_VALUE_T) {
    FilterObj filter_obj;
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  }

  if (condition.right_type == CON_ATTR_T) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
  } else if(condition.right_type == CON_VALUE_T) {
    FilterObj filter_obj;
    filter_obj.init_value(condition.right_value);
    filter_unit->set_right(filter_obj);
  }

  filter_unit->set_comp(comp);
  // 检查两个类型是否能够比较
  return rc;
}

RC FilterStmt::create_filter_unit_expr(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;
  rc = Init_filter_unit(db,default_table,tables,condition,filter_unit);
  filter_unit->set_comp(comp);
  // 检查两个类型是否能够比较
  return rc;
}

RC FilterStmt::Init_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit){
  RC rc = RC::SUCCESS;

  // 左expression
  switch (condition.left_type)
  {
  case CON_ATTR_T:
    {
      Table *table = nullptr;
      const FieldMeta *field = nullptr;
      rc = get_table_and_field(db, default_table, tables, condition.left_expr_node.attributes[0], table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      FilterObj filter_obj;
      filter_obj.init_attr(Field(table, field));
      filter_obj.expr = new FieldExpr(Field(table, field));
      filter_unit->set_left(filter_obj);
    }
    break;
  case CON_VALUE_T:
    {
      FilterObj filter_obj;
      ValueExpr *value_expr = static_cast<ValueExpr*>(condition.left_expr_node.expression);
      filter_obj.init_value(value_expr->get_value());
      filter_obj.expr = value_expr;
      filter_unit->set_left(filter_obj);
    }break;
  case CON_SUBSELECT_T:
    {
      FilterObj filter_obj;
      filter_obj.expr = condition.left_expr_node.expression;   
      SubSelectExpr *subselect_expr =  static_cast<SubSelectExpr*>(condition.left_expr_node.expression);
      subselect_expr->init_tables(tables,db);
      filter_unit->set_left(filter_obj);
    }break;
  case CON_SET_T:
    {
      FilterObj filter_obj;
      filter_obj.expr = condition.left_expr_node.expression;  
      filter_unit->set_left(filter_obj);
    }break;
  default:
    return RC::INTERNAL;
    break;
  }

  // 右expression
  switch (condition.right_type)
  {
  case CON_ATTR_T:
    {
      Table *table = nullptr;
      const FieldMeta *field = nullptr;
      rc = get_table_and_field(db, default_table, tables, condition.right_expr_node.attributes[0], table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      FilterObj filter_obj;
      filter_obj.init_attr(Field(table, field));
      filter_obj.expr = new FieldExpr(Field(table, field));
      filter_unit->set_right(filter_obj);
    }
    break;
  case CON_VALUE_T:
    {
      FilterObj filter_obj;
      ValueExpr *value_expr = static_cast<ValueExpr*>(condition.right_expr_node.expression);
      filter_obj.init_value(value_expr->get_value());
      filter_obj.expr = value_expr;
      filter_unit->set_right(filter_obj);
    }break;
  case CON_SUBSELECT_T:
    {
      FilterObj filter_obj;
      filter_obj.expr = condition.right_expr_node.expression;   // TODO 指针空间被释放的问题吗
      SubSelectExpr *subselect_expr =  static_cast<SubSelectExpr*>(condition.right_expr_node.expression);
      subselect_expr->init_tables(tables,db);
      filter_unit->set_right(filter_obj);
    }break;
  case CON_SET_T:
    {
      FilterObj filter_obj;
      filter_obj.expr = condition.right_expr_node.expression; 
      filter_unit->set_right(filter_obj);
    }break;
  default:
    return RC::INTERNAL;
    break;
  }

  return rc;
}