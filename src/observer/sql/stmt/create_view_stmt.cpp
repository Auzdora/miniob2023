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
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "sql/expr/expression.h"

RC CreateViewStmt::create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt, SelectSqlNode &selectSqlNode)
{
  std::unordered_map<std::string,std::string> alias_to_table;
  for (int i = 0; i < selectSqlNode.relations.size(); i++)
  {
    std::string rel_name = selectSqlNode.relations[i].relation_name;
    Table* table = db->find_table(rel_name.c_str());
    if (table == nullptr)
      return RC::INTERNAL;
    if (selectSqlNode.relations[i].alias != "")
    {
      alias_to_table.insert(std::pair(selectSqlNode.relations[i].alias,rel_name));
    }
  }

  std::vector<AttrInfoSqlNode> infos;

  for (int i = 0; i < selectSqlNode.expressions.size();i++)
  {
    ExprSqlNode &exprnode = selectSqlNode.expressions[i];
    if (exprnode.aggregations.size() == 0)
    {
      // 不是aggregation 表达式
      if(exprnode.attributes.size() == 1)
      {
        if (exprnode.expression == nullptr)
        {
          if (exprnode.attributes[0].attribute_name == "*")
          {
            // star
            for (auto rel : selectSqlNode.relations)
            {
              Table * table = db->find_table(rel.relation_name.c_str());
              TableMeta table_meta = table->table_meta();
              for (int i = 0;i < table_meta.field_num() - table_meta.sys_field_num() - table_meta.custom_fields_num(); i++)
              {
                AttrInfoSqlNode info;
                FieldMeta field = *table_meta.field(i+table_meta.sys_field_num()+table_meta.custom_fields_num());
                info.name = field.name();
                info.length = field.len();
                info.nullable = field.nullable();
                info.type = field.type();
                infos.push_back(info);
              }
            }
          }
        }
        else if (!exprnode.expression)
        {
          // 说明是 字段
          AttrInfoSqlNode info;
          Table* table = db->find_table(exprnode.attributes[0].relation_name.c_str());
          if (exprnode.attributes[0].attribute_alias.c_str())
          {
            // 有alias 就使用alias
            info.name = exprnode.attributes[0].attribute_alias;
          }else{
            info.name = exprnode.attributes[0].attribute_name;
          }
          const FieldMeta field =  *table->table_meta().field(exprnode.attributes[0].attribute_name.c_str());
          info.type = field.type();
          info.length = field.len();
          info.nullable = field.nullable();
          infos.push_back(info);
        }else{
          // 说明是表达式
          AttrInfoSqlNode info;
          std::string table_name;
          if (exprnode.expression->type() != ExprType::FIELD) {
            info.is_virtual = true;
          }
          if (exprnode.attributes[0].relation_name != "")
          {
            if (!selectSqlNode.relations.empty())
            {
              table_name = find_relation(selectSqlNode.relations,exprnode.attributes[0].relation_name);
              if (table_name == "")
              {
                return RC::INTERNAL;
              }
            }else{
              return RC::INTERNAL;
            }
          }
          else
            table_name =  selectSqlNode.relations[0].relation_name;
          Table* table = db->find_table(table_name.c_str());
          info.name = extractColumnNameOrAlias(exprnode.expression->name());
          const FieldMeta field =  *table->table_meta().field(exprnode.attributes[0].attribute_name.c_str());
          info.type = field.type();
          info.length = field.len();
          info.nullable = field.nullable();
          infos.push_back(info);
        }
      }else{
          AttrInfoSqlNode info;
          std::string table_name;
          if (exprnode.expression->type() != ExprType::FIELD) {
            info.is_virtual = true;
          }
          if (exprnode.attributes[0].relation_name != "")
          {
            // 多表的情况，从reltion中找对应的表，因为可能用的是 alias 所以需要找到对应的实际表名
            if (!selectSqlNode.relations.empty())
            {
              table_name = find_relation(selectSqlNode.relations,exprnode.attributes[0].relation_name);
              if (table_name == "")
              {
                return RC::INTERNAL;
              }
            }else{
              return RC::INTERNAL;
            }
          }
          else
            table_name =  selectSqlNode.relations[0].relation_name;  // 单表的情况 直接从relation中获取
          Table* table = db->find_table(table_name.c_str());
          info.name = extractColumnNameOrAlias(exprnode.expression->name());
          const FieldMeta field =  *table->table_meta().field(exprnode.attributes[0].attribute_name.c_str());
          info.type = field.type();
          info.length = field.len();
          info.nullable = field.nullable();
          infos.push_back(info);
      }
    }else{
      // 表达式只含 aggr
      if (exprnode.aggregations.size() == 1)
      {
        AttrInfoSqlNode info;
        if (exprnode.aggregations[0].alias != "")
        {
          info.name = exprnode.aggregations[0].alias;
        }else{
          info.name = exprnode.expression->name();
        }
        if (exprnode.aggregations[0].aggregation_name == "count")
        {
          info.type = INTS;
          info.length = sizeof(int);
        } 
        else if (exprnode.aggregations[0].aggregation_name == "avg")
        {
          info.type = FLOATS;
          info.length = sizeof(int);
        }else
        {
          if (exprnode.attributes[0].relation_name == "")
          {
            if (selectSqlNode.relations[0].relation_name.c_str() == "")
              return RC::INTERNAL;
            TableMeta tablemeta = db->find_table(selectSqlNode.relations[0].relation_name.c_str())->table_meta();
            FieldMeta field = *tablemeta.field(exprnode.attributes[0].attribute_name.c_str());
            info.type = field.type();
            info.length = field.len();
          }else
          {
            // 多表的情况 从relation中找
            std::string table_name = find_relation(selectSqlNode.relations,exprnode.attributes[0].relation_name);
            if (table_name == "")
            {
              return RC::INTERNAL;
            }
            TableMeta tablemeta = db->find_table(table_name.c_str())->table_meta();
            FieldMeta field = *tablemeta.field(exprnode.attributes[0].attribute_name.c_str());
            info.type = field.type();
            info.length = field.len();
          }
        }
        info.nullable = true;
        infos.push_back(info);
      }
      else{
        AttrInfoSqlNode info;
        info.name = exprnode.expression->name();
        info.length = sizeof(float);
        info.nullable = true;
        info.type = FLOATS;
      }
    }
  }

  
  stmt = new CreateViewStmt(create_table.relation_name, infos,selectSqlNode);
  //sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}

std::string CreateViewStmt::get_rel_name(std::unordered_map<std::string,std::string> alias_to_rel,std::string alias){
  auto it = alias_to_rel.find(alias);
  if (it != alias_to_rel.end())
  {
    return it->second;
  }else{
    return std::string("");
  }
}

std::string CreateViewStmt::find_relation(std::vector<RelSqlNode> relations,std::string relation_name)
{
  for (auto rel : relations)
  {
    if (rel.relation_name == relation_name || rel.alias == relation_name)
    {
      return rel.relation_name;
    }
  }
  return std::string("");
}

std::string CreateViewStmt::extractColumnNameOrAlias(const std::string& input) {
      // Check if there's an "as" keyword to define an alias
      auto asPos = input.rfind(" as ");
      if (asPos != std::string::npos) {
          return input.substr(asPos + 4); // Return the alias
      }

      // If there's no alias, check for a table alias (e.g., "t.id")
      // auto dotPos = input.rfind(".");
      // if (dotPos != std::string::npos) {
      //     return input.substr(dotPos + 1); // Return the column name
      // }

      // If there's no table or alias, return the input as-is
      return input;
  }