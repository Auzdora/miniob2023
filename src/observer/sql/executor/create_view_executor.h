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

#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief 创建表的执行器
 * @ingroup Executor
 */
class CreateViewExecutor
{
public:
  CreateViewExecutor() = default;
  virtual ~CreateViewExecutor() = default;

  RC execute(SQLStageEvent *sql_event);

private:
  

};

/**
 * select_sql_node_:
 *      aggregations:
 *   std::string relation_name;      ///< 表名，可能是alias，需要在stmt做映射解析
     std::string aggregation_name;   ///< aggregation name          聚合函数名
     std::string attribute_name;     ///< attribute name            属性名
     std::string alias;
 *      attributes: 
 *         []:
 *              relation_name
 *              attribute_name
 *              attribute_alias
 *      relations:
 *          []:
 *              relation_name
 *              alias
 *      innerJoins:
 *      conditions:
 *          []:
 *              left_value
 *                  attr_type
 *                  length_
 *                  num_value_
 *                  str_value_
 *                  is_nullable_
 *              left_attr
 *                  relation_name
 *                  attribute_name
 *                  attribute_alias
 *              comp
 *              right_attr
 *                  ...
 *              right_value 
 *                  ...
 *              left_expr_node
 *                  expression
 *                      name_
 *                      star_expr
 *                      index_
 *                  aggregations
 *                  attributes
 *                      ...
 *                  functions:
 *              right_expr_node
 *                  ...
 *              left_con_type
 *              right_con_type
 *      orderbys:
 *            std::string  relation_name;
              std::string  attribute_name;
              OrderType    order_type;
 *      expressions:
 *          []:
 *              expression
 *              aggregations
 *              attributes
 *              functions
 *      rel_alias:
 *      groupbys:
 *      having_conditions:
 *      use_group_by:
 *              
 *          
*/