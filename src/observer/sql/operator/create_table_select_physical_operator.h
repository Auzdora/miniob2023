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
// Created by Lanbotian on 2023/10/29.
//

#pragma once

#include "event/sql_event.h"
#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include <memory>

/**
 * @brief 复制表
 * @ingroup PhysicalOperator
 */
class CreateTableSelectPhysicalOperator : public PhysicalOperator
{
public:
  CreateTableSelectPhysicalOperator(Db *db, std::string table_name, const std::vector<std::string> &expr_names) : db_(db), table_name_(table_name), expr_names_(expr_names)
  {}

  virtual ~CreateTableSelectPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::CREATE_TABLE_SELECT;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  Db *db_;
  std::string table_name_;
  std::vector<std::string> expr_names_;
  bool first_call_{true};
  Trx *trx_;
};
