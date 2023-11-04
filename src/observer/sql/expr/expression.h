/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <memory>
#include <string.h>
#include <string>

#include "storage/field/field.h"
#include "sql/stmt/select_stmt.h"
#include "sql/parser/value.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"

class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType {
  NONE,
  STAR, ///< 星号，表示所有字段
  FIELD, ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,       ///< 常量值
  CAST,        ///< 需要做类型转换的表达式
  COMPARISON,  ///< 需要做比较的表达式
  CONJUNCTION, ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,  ///< 算术运算
  AGGREGATION, ///< 聚合函数
  FUNCTION,    ///< 函数
  SUBSELECT,    ///< 子查询
  SET,          ///< 集合
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression {
public:
  Expression() = default;
  virtual ~Expression() = default;

  virtual void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) = 0;

  /**
   * @brief
   * 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  /**
   * @brief
   * 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLENMENT; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }
  virtual int index() const { return index_; }
  virtual void set_index(int index) { index_ = index; }
  virtual void set_name(std::string name) { name_ = name; }
  virtual void set_star_flag(bool flag) { star_expr_ = flag; }
  virtual bool star_expr() { return star_expr_; }

private:
  std::string name_;
  bool star_expr_{false};
  int index_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression {
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field)
      : field_(table, field) {}

  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override {
    if (table_name_.empty()) {
      const FieldMeta *field_meta =
          default_table->table_meta().field(field_name_.c_str());
      field_.set_table(default_table);
      field_.set_field(field_meta);
      table_name_ = default_table->name();
      field_name_ = field_meta->name();
      return;
    }

    // Table *new_table = db->find_table(table_name_.c_str());
    Table *new_table = tables->at(table_name_);
    if (0 == strcmp(field_name_.c_str(), "*")) {
      set_star_flag(true);
      star_table_ = new_table;
      table_name_ = new_table->name();
      const TableMeta &table_meta = star_table_->table_meta();
      const int user_field_start_idx = table_meta.sys_field_num() + table_meta.custom_fields_num();
      for (int i = user_field_start_idx; i < star_table_->table_meta().field_num(); i++) {
        const FieldMeta *field_meta = star_table_->table_meta().field(i);
        field_names_.push_back(field_meta->name());
      }
      std::reverse(field_names_.begin(), field_names_.end());
      return;
    }
    const FieldMeta *field_meta =
        new_table->table_meta().field(field_name_.c_str());
    field_.set_table(new_table);
    field_.set_field(field_meta);
    table_name_ = new_table->name();
    field_name_ = field_meta->name();
  }

  FieldExpr(const Field &field) : field_(field) {
    table_name_ = field.table_name();
    field_name_ = field.field_name();
  }
  FieldExpr(const std::string table_name, const std::string field_name)
      : table_name_(table_name), field_name_(field_name) {}

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  void init_field(const Field &field) { field_ = field; }

  const char *table_name() const { return table_name_.c_str(); }

  const char *field_name() const { return field_name_.c_str(); }

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_values(const Tuple &tuple, std::vector<Value> &values) const;
  RC get_value_same_table(const Tuple &tuple, Value &value);
  const std::vector<std::string> &names() { return field_names_; }

private:
  Field field_;
  Table *star_table_;
  std::vector<std::string> field_names_;   // for table.* case, special consideration
  std::string table_name_; // for expression parser
  std::string field_name_; // for expression parser
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression {
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override { return; }

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override {
    value = value_;
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

private:
  Value value_;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression {
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override { return; }

  ExprType type() const override { return ExprType::CAST; }
  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_; ///< 从这个表达式转换
  AttrType cast_type_;                ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression {
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left,
                 std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override {
    left_->init(db, default_table, tables);
    right_->init(db, default_table, tables);
  }

  ExprType type() const override { return ExprType::COMPARISON; }

  RC get_value(const Tuple &tuple, Value &value) const override;
  
  RC get_value_same_table(const Tuple &tuple, Value &value);

  AttrType value_type() const override { return BOOLEANS; }

  CompOp comp() const { return comp_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

private:
  CompOp comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression {
public:
  enum class Type {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type,
                  std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override {
    for (const auto &child : children_) {
      child->init(db, default_table, tables);
    }
  }

  ExprType type() const override { return ExprType::CONJUNCTION; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
  Type conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression {
public:
  enum class Type {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left,
                 std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override {
    left_->init(db, default_table, tables);
    if (arithmetic_type_ != Type::NEGATIVE) {
      right_->init(db, default_table, tables);
    } else {
      right_.reset(new ValueExpr(Value(0)));
    }
  }

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

private:
  RC calc_value(const Value &left_value, const Value &right_value,
                Value &value) const;

private:
  Type arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 聚合函数表达式
 * @ingroup Expression
 */
class AggregationExpr : public Expression {
public:
  AggregationExpr() = default;
  AggregationExpr(const std::string table_name, const std::string field_name)
      : table_name_(table_name), field_name_(field_name) {}

  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override { return; }

  virtual ~AggregationExpr() = default;

  ExprType type() const override { return ExprType::AGGREGATION; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  const char *table_name() const { return table_name_.c_str(); }

  const char *field_name() const { return field_name_.c_str(); }

  RC get_value(const Tuple &tuple, Value &value) const override;

private:
  std::string table_name_; // for expression parser
  std::string field_name_; // for expression parser
};

/**
 * @brief 函数运算表达式
 * @ingroup Expression
 */
class FunctionExpr : public Expression {
public:
  FunctionExpr() = default;
  FunctionExpr(const Value &value, FunctionType func_type)
      : value_(value), func_type_(func_type) {
    is_value_ = true;
  }
  FunctionExpr(const Value &value, FunctionType func_type, int int_param)
      : value_(value), func_type_(func_type), int_param_(int_param) {
    is_value_ = true;
  }
  FunctionExpr(const Value &value, FunctionType func_type,
               std::string date_param)
      : value_(value), func_type_(func_type), date_param_(date_param) {
    is_value_ = true;
  }
  FunctionExpr(const std::string table_name, const std::string field_name,
               FunctionType func_type)
      : table_name_(table_name), field_name_(field_name),
        func_type_(func_type) {
    is_value_ = false;
  }
  FunctionExpr(const std::string table_name, const std::string field_name,
               FunctionType func_type, int int_param)
      : table_name_(table_name), field_name_(field_name), func_type_(func_type),
        int_param_(int_param) {
    is_value_ = false;
  }
  FunctionExpr(const std::string table_name, const std::string field_name,
               FunctionType func_type, std::string date_param)
      : table_name_(table_name), field_name_(field_name), func_type_(func_type),
        date_param_(date_param) {
    is_value_ = false;
  }
  virtual ~FunctionExpr() = default;

  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override {
    if (is_value_) {
      return;
    }
    if (table_name_.empty()) {
      const FieldMeta *field_meta =
          default_table->table_meta().field(field_name_.c_str());
      field_.set_table(default_table);
      field_.set_field(field_meta);
      table_name_ = default_table->name();
      field_name_ = field_meta->name();
      return;
    }

    // Table *new_table = db->find_table(table_name_.c_str());
    Table *new_table = tables->at(table_name_);
    const FieldMeta *field_meta =
        new_table->table_meta().field(field_name_.c_str());
    field_.set_table(new_table);
    field_.set_field(field_meta);
    table_name_ = new_table->name();
    field_name_ = field_meta->name();
  }

  ExprType type() const override { return ExprType::FUNCTION; }
  AttrType value_type() const override {
    if (is_value_) {
      return value_.attr_type();
    }
    return field_.attr_type();
  }

  const char *table_name() const { return table_name_.c_str(); }

  const char *field_name() const { return field_name_.c_str(); }

  RC get_value(const Tuple &tuple, Value &value) const override;
  std::string to_padded_string(int value, int padding = 2) const;

private:
  std::string format_date(int date_int, const std::string& format) const;
  bool is_value_;
  Value value_;
  Field field_;
  int int_param_;          // parameter for round
  std::string date_param_; // parameter for date_format
  FunctionType func_type_;
  std::string table_name_;
  std::string field_name_;
};

/**
 * @brief 子查询表达式
 * @ingroup Expression
 */
class SubSelectExpr : public Expression 
{
public:
  SubSelectExpr() = default;
  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override { return; }
  explicit SubSelectExpr(ParsedSqlNode *&subselect) : subselect_(subselect)
  {}

  virtual ~SubSelectExpr(){
    if (subselect_ != nullptr)
      delete subselect_;
    if (subselect_stmt_ != nullptr)
      delete subselect_stmt_;
  };

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_value(const Tuple &tuple, Value &value);

  RC try_get_value(Value &value) const override { value = value_; return RC::SUCCESS; }

  ExprType type() const override { return ExprType::SUBSELECT; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  void init_tables(std::unordered_map<std::string, Table *> *&tables,Db *db){ 
    tables_ = tables;
    db_ = db;
  }

  SelectSqlNode &get_subsqlNode() { return subselect_->selection; }


  RC create_stmt();
  Stmt *&get_stmt() { return subselect_stmt_; }

  const Value &get_value() const { return value_; }

private:
  Value value_;
  Tuple *tuple_ = nullptr;
  Db * db_ = nullptr;
  ParsedSqlNode *subselect_;
  Stmt *subselect_stmt_;
  std::unordered_map<std::string, Table *> *tables_;
};



/**
 * @brief 集合表达式
 * @ingroup Expression
 */
class SetExpr : public Expression 
{
public:
  SetExpr() = default;
  void init(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables) override { return; }
  explicit SetExpr(std::vector<Expression*> &expr_set)
  {
    expr_set_.swap(expr_set);
  }

  virtual ~SetExpr(){
    for (int i = 0; i < expr_set_.size();i++)// 是否需要对 epxr_set_ 做释放？
    {
      delete expr_set_[i];
      expr_set_.clear();
    }
  };

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_value(const Tuple &tuple, Value &value);

  RC try_get_value(Value &value) const override { value = value_; return RC::SUCCESS; }

  ExprType type() const override { return ExprType::SET; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

  std::vector<Expression*> &get_expr_set(){ return expr_set_;}

private:
  Value value_;
  std::vector<Expression*> expr_set_;
};
