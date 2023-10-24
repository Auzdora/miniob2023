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
// Created by Lanbotian on 2023/10/23.
//

#include "sql/operator/sort_logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field.h"

SortLogicalOperator::SortLogicalOperator(const std::vector<Field> &sort_fields, const std::vector<OrderType> &sort_types, const std::vector<int> &sort_idx) : sort_fields_(sort_fields), sort_types_(sort_types), sort_idx_(sort_idx)
{}