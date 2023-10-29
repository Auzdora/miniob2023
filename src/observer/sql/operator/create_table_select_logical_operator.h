//
// Created by Lanbotian on 2023/10/18.
//

#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "storage/db/db.h"

/**
 * @brief 逻辑算子
 * @ingroup LogicalOperator
 */
class CreateTableSelectLogicalOperator : public LogicalOperator 
{
public:
  CreateTableSelectLogicalOperator(std::string table_name, const std::vector<std::string> &expr_names, Db *db) : table_name_(table_name), expr_names_(expr_names), db_(db) {}
  virtual ~CreateTableSelectLogicalOperator() = default;

  LogicalOperatorType type() const override
  { 
    return LogicalOperatorType::CREATE_TABLE_SELECT;
  }

  const std::string table_name() const { return table_name_; }
  const std::vector<std::string> expr_names() const { return expr_names_; }
  Db *get_db() { return db_; }

private:
  Db *db_;
  std::string table_name_;
  std::vector<std::string> expr_names_;
};