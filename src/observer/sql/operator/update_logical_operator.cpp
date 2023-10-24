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
// Created by Daijinxiang on 2023/10/17.
//

#include "update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table,const Value values, Field field)
:table_(table),value_(values),field_(field)
{}

UpdateLogicalOperator::UpdateLogicalOperator(Table *table,const std::vector<Value> &values, const std::vector<Field> &field)
:table_(table),values_(values),fields_(field)
{}

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const std::vector<Value> &values, const std::vector<Field> &field, const std::unordered_map<std::string,int> subselect_map)
:table_(table),values_(values),fields_(field),subselect_map_(subselect_map)
{}