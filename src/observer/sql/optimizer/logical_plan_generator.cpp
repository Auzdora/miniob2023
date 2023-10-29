/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/operator/aggr_logical_operator.h"
#include "sql/operator/create_table_select_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/sort_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"

#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/create_table_select_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "storage/field/field.h"
#include <cstring>
#include <memory>
#include <vector>
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt,
                                unique_ptr<LogicalOperator> &logical_operator) {
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
  case StmtType::CALC: {
    CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
    rc = create_plan(calc_stmt, logical_operator);
  } break;

  case StmtType::SELECT: {
    SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
    rc = create_plan(select_stmt, logical_operator);
  } break;

  case StmtType::INSERT: {
    InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
    rc = create_plan(insert_stmt, logical_operator);
  } break;

  case StmtType::DELETE: {
    DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
    rc = create_plan(delete_stmt, logical_operator);
  } break;

  case StmtType::UPDATE: {
    UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
    rc = create_plan(update_stmt, logical_operator);
  } break;

  case StmtType::EXPLAIN: {
    ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
    rc = create_plan(explain_stmt, logical_operator);
  } break;

  case StmtType::CREATE_TABLE_SELECT: {
    CreateTableSelectStmt *create_table_select_stmt = static_cast<CreateTableSelectStmt *>(stmt);
    rc = create_plan(create_table_select_stmt, logical_operator);
  } break;

  default: {
    rc = RC::UNIMPLENMENT;
  }
}
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  logical_operator.reset(
      new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables = select_stmt->tables();
  const std::vector<Field> &all_fields = select_stmt->query_fields();
  const std::vector<Expression *> &all_expressions = select_stmt->query_expressions();
  int inner_join_idx = 0;
  const std::vector<std::string> &all_aggr_funcs = select_stmt->aggr_funcs();
  // only support aggr on one table for now
  // if (!all_aggr_funcs.empty() && tables.size() > 1) {
  //   LOG_WARN("do not support aggregation on multiple tables");
  //   return RC::INTERNAL;
  // }

  bool contain_expression = false;
  if (select_stmt->query_fields().size() > select_stmt->query_expressions().size()) {
    contain_expression = true;
  } else {
    // 意味着attribute的数量和expression的数量相同，一种可能是单纯的查询，另一种则是每个expression与常量运算
    // 所以这里进一步判断
    for (const auto expr : select_stmt->query_expressions()) {
      if (expr->type() == ExprType::ARITHMETIC || expr->type() == ExprType::FUNCTION) {
        contain_expression = true;
      }
    }
  }
  
  for (Table *table : tables) {
    std::vector<Field> fields;
    for (const Field &field : all_fields) {
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }

    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, all_aggr_funcs, true/*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
      if (inner_join_idx < select_stmt->filter_stmts().size()){
        unique_ptr<LogicalOperator> predicate_oper;
        RC rc = create_plan(select_stmt->filter_stmts()[inner_join_idx], predicate_oper);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
          return rc;
        }
        predicate_oper->add_child(std::move(table_oper));
        table_oper = std::move(predicate_oper);
        inner_join_idx++;
      }
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  unique_ptr<LogicalOperator> project_oper;
  if (contain_expression && all_aggr_funcs.empty()) {
    project_oper = std::make_unique<ProjectLogicalOperator>(all_fields, all_expressions);
  } else {
    project_oper = std::make_unique<ProjectLogicalOperator>(all_fields);
  }

  if (predicate_oper) {
    if (table_oper) {
      predicate_oper->add_child(std::move(table_oper));
    }
    project_oper->add_child(std::move(predicate_oper));
  } else {
    if (table_oper) {
      project_oper->add_child(std::move(table_oper));
    }
  }

  if (!all_aggr_funcs.empty()) {
    unique_ptr<LogicalOperator> aggr_oper(new AggregationLogicalOperator(all_aggr_funcs, all_expressions));
    aggr_oper->add_child(std::move(project_oper));
    logical_operator.swap(aggr_oper);
    return RC::SUCCESS;
  }

  const std::vector<OrderType> &sort_types = select_stmt->sort_types();
  const std::vector<Field> &sort_fields = select_stmt->sort_fields();
  // compute the sort fields index on project tuple
  std::vector<int> sort_idx;
  for (int i = 0; i < sort_fields.size(); i++) {
    const Field &target = sort_fields[i];
    for (int idx = 0; idx < all_fields.size(); idx++) {
      if (0 == strcmp(target.table_name(), all_fields[idx].table_name())
          && 0 == strcmp(target.field_name(), all_fields[idx].field_name()))
      {
        sort_idx.push_back(idx);
      }
    }
  }
  // create sort operator if it has order by
  if (!sort_fields.empty()) {
    unique_ptr<LogicalOperator> sort_oper(new SortLogicalOperator(sort_fields, sort_types, sort_idx));
    sort_oper->add_child(std::move(project_oper));
    logical_operator.swap(sort_oper);
    return RC::SUCCESS;
  }

  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  std::vector<std::unique_ptr<LogicalOperator>> subselect_lopers;
  std::vector<std::string> subselect_expr_names;
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;

    switch (filter_obj_left.type) {
      case FilterObjType::FIELD: {
        left = std::make_unique<FieldExpr>(filter_obj_left.field);
      } break;
      case FilterObjType::VALUE: {
        left = std::make_unique<ValueExpr>(filter_obj_left.value);
      } break;
      case FilterObjType::CALC: {
        left.reset(filter_obj_left.expr);
      } break;
      case FilterObjType::SUBSELECT: {
        left.reset(filter_obj_left.expr);
      } break;
      case FilterObjType::SET: {
        left.reset(filter_obj_left.expr);
      } break;
      default: {
        return RC::INTERNAL;
      } break;
    }
  
    switch (filter_obj_right.type) {
      case FilterObjType::FIELD: {
        right = std::make_unique<FieldExpr>(filter_obj_right.field);
      } break;
      case FilterObjType::VALUE: {
        right = std::make_unique<ValueExpr>(filter_obj_right.value);
      } break;
      case FilterObjType::CALC: {
        right.reset(filter_obj_right.expr);
      } break;
      case FilterObjType::SUBSELECT: {
        right.reset(filter_obj_right.expr);
      } break;
      case FilterObjType::SET: {
        right.reset(filter_obj_right.expr);
      } break;
      default: {
        return RC::INTERNAL;
      } break;
    }

    if (left->type() == ExprType::SUBSELECT)
    {
      SubSelectExpr * subselect_expr = static_cast<SubSelectExpr *>(left.get());
      
      subselect_expr->get_subsqlNode().rel_alias.insert(filter_stmt->get_rel_alias().begin(), filter_stmt->get_rel_alias().end());
      if(RC::SUCCESS != subselect_expr->create_stmt())
        return RC::INTERNAL;
      unique_ptr<LogicalOperator> subselect_loper = nullptr;
      if (RC::SUCCESS != create(subselect_expr->get_stmt(),subselect_loper))
        return RC::INTERNAL;
      subselect_lopers.emplace_back(std::move(subselect_loper));
      subselect_expr_names.push_back(subselect_expr->name());
    }

    if (right->type() == ExprType::SUBSELECT)
    {
      SubSelectExpr * subselect_expr = static_cast<SubSelectExpr *>(right.get());
      subselect_expr->get_subsqlNode().rel_alias.insert(filter_stmt->get_rel_alias().begin(), filter_stmt->get_rel_alias().end());
      if(RC::SUCCESS != subselect_expr->create_stmt())
        return RC::INTERNAL;
      unique_ptr<LogicalOperator> subselect_loper = nullptr;
      if (RC::SUCCESS != create(subselect_expr->get_stmt(),subselect_loper))
        return RC::INTERNAL;
      subselect_lopers.emplace_back(std::move(subselect_loper));
      subselect_expr_names.push_back(subselect_expr->name());
    }

    ComparisonExpr *cmp_expr = new ComparisonExpr(
        filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(
        new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(
        new PredicateLogicalOperator(std::move(conjunction_expr)));
  }
  predicate_oper->set_subselect_expr_name(subselect_expr_names);
  logical_operator = std::move(predicate_oper);
  
  for (int i = 0;i < subselect_lopers.size();i++)
  {
    logical_operator->add_child(std::move(subselect_lopers[i]));
  }

  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  Table *table = insert_stmt->table();
  vector<vector<Value>> values;
  for (auto record:insert_stmt->values()){
    values.push_back(record);
  }
  // vector<Value> values(insert_stmt->values(),
  //                      insert_stmt->values() + insert_stmt->value_amount());
  // for multi index unique
  if (table->table_meta().multi_index_num() > 0) {
    std::vector<Field> fields;
    const TableMeta &table_meta = table->table_meta();
    const int user_field_start_idx = table_meta.sys_field_num() + table_meta.custom_fields_num();
    for (int i = user_field_start_idx; i < table->table_meta().field_num(); i++) {
      const FieldMeta *field_meta = table->table_meta().field(i);
      fields.push_back(Field(table, field_meta));
    }
    unique_ptr<LogicalOperator> table_get_oper(
        new TableGetLogicalOperator(table, fields, false /*readonly*/));
    unique_ptr<LogicalOperator> insert_oper(new InsertLogicalOperator(table, values));
    insert_oper->add_child(std::move(table_get_oper));
    logical_operator = std::move(insert_oper);
    return RC::SUCCESS;
  }

  InsertLogicalOperator *insert_operator =
      new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(
    DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  Table *table = delete_stmt->table();
  FilterStmt *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num() + table->table_meta().custom_fields_num();
       i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(
      new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  Stmt *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    UpdateStmt *update_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table = update_stmt->table();
  FilterStmt *filter_stmt = update_stmt->filter_stmt();
  int idx = 0;
  std::vector<Field> fields;
  std::vector<Value> update_values;  // multi update values
  std::vector<Field> update_fields;  // multi update fields

  int usr_field_start = table->table_meta().sys_field_num() + table->table_meta().custom_fields_num();
  // 添加需要更新的field 到逻辑算子对象成员中
  for (int i = 0; i < table->table_meta().field_num() - usr_field_start; i++) {
    const FieldMeta *field_meta = table->table_meta().field(i + usr_field_start);
    fields.push_back(Field(table, field_meta));
    auto it = update_stmt->get_update_map().find(field_meta->name());
    if (it != update_stmt->get_update_map().end()) {
      update_values.push_back(*std::get<0>((it->second)));
      update_fields.push_back(fields[i]);
    }
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false/*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::unordered_map<std::string,int> subselect_map;
  std::vector<unique_ptr<LogicalOperator>> subselect_opers;
  int subselect_idx = 1;
  for (int i = 0; i < update_fields.size(); i++){
    auto it = update_stmt->get_update_map().find(update_fields[i].field_name());
    if (!std::get<1>(it->second))
    {
      subselect_map[update_fields[i].field_name()] = subselect_idx++;
      unique_ptr<LogicalOperator> subselect_oper;
      auto rc = create_plan(std::get<2>(it->second), subselect_oper);
      if (rc != RC::SUCCESS){
        return rc;
      }
      subselect_opers.push_back(std::move(subselect_oper));
    }
  }
  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, update_values, update_fields,subselect_map));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }
  for(int i = 0;i < subselect_opers.size();i++){
    update_oper->add_child(std::move(subselect_opers[i]));
  }

  logical_operator = std::move(update_oper);
  return rc;

}

RC LogicalPlanGenerator::create_plan(
    CreateTableSelectStmt *create_table_select_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  
  unique_ptr<LogicalOperator> select_oper;
  LogicalPlanGenerator::create_plan(create_table_select_stmt->select_stmt(), select_oper);

  unique_ptr<LogicalOperator> create_table_select_oper(new CreateTableSelectLogicalOperator(create_table_select_stmt->table_name(), create_table_select_stmt->field_names(), create_table_select_stmt->star_field_names(), create_table_select_stmt->get_db()));
  create_table_select_oper->add_child(std::move(select_oper));
  
  logical_operator = std::move(create_table_select_oper);
  return RC::SUCCESS;
}