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

#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include <cmath>

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const {
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

RC FieldExpr::get_values(const Tuple &tuple, std::vector<Value> &values) const {
  std::vector<Value> vals;
  const TableMeta &table_meta = star_table_->table_meta();
  const int user_field_start_idx = table_meta.sys_field_num() + table_meta.custom_fields_num();
  for (int i = user_field_start_idx; i < star_table_->table_meta().field_num(); i++) {
    Value tmp_val;
    const FieldMeta *field_meta = star_table_->table_meta().field(i);
    tuple.find_cell(TupleCellSpec(table_name(), field_meta->name()), tmp_val);
    vals.push_back(tmp_val);
  }
  values = vals;
  return RC::SUCCESS;
}


RC ValueExpr::get_value(const Tuple &tuple, Value &value) const {
  value = value_;
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type)
    : child_(std::move(child)), cast_type_(cast_type) {}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const {
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
  case BOOLEANS: {
    bool val = value.get_boolean();
    cast_value.set_boolean(val);
  } break;
  default: {
    rc = RC::INTERNAL;
    LOG_WARN("unsupported convert from type %d to %d", child_->value_type(),
             cast_type_);
  }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell) const {
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const {
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left,
                               unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right)) {}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right,
                                 bool &result) const {
  RC rc = RC::SUCCESS;
  result = left.compare(right,comp_);
  if (result == -1) {
    LOG_WARN("unsupported comparison. %d", comp_);
    rc = RC::INTERNAL;
  } 

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const {
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell = left_value_expr->get_value();
    const Value &right_cell = right_value_expr->get_value();

    bool value = false;
    RC rc = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const {
  Value left_value;
  Value right_value;

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  // 对setexpr 做in 操作
  if (comp_ == IN_OP || comp_ == NOT_IN_OP)
  {
    if (right_->type() == ExprType::SET)
    {
      bool bool_value = false;
      SetExpr * set_expr = static_cast<SetExpr *>(right_.get());
      std::vector<Expression *> sets = set_expr->get_expr_set();
      for (int i = 0; i < sets.size();i++){
        Value right_value;
        rc = sets[i]->try_get_value(right_value);
        if (rc != RC::SUCCESS)
          return rc;
        rc = compare_value(left_value, right_value, bool_value);
        if (rc != RC::SUCCESS)
          return rc;
        if (comp_ == IN_OP){
          if (bool_value)
          {
            value.set_boolean(true);
            return RC::SUCCESS;
          }
        }else{
          if (!bool_value)
          {
            value.set_boolean(false);
            return RC::SUCCESS;
          }
        }
      }
      if (comp_ == IN_OP)
      {
        value.set_boolean(false);
      }else {
        value.set_boolean(true);
      }
      return RC::SUCCESS;
    }
  }

  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;
  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type,
                                 vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children)) {}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const {
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) ||
        (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left,
                               Expression *right)
    : arithmetic_type_(type), left_(left), right_(right) {}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type,
                               unique_ptr<Expression> left,
                               unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right)) {
}

AttrType ArithmeticExpr::value_type() const {
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS &&
      right_->value_type() == AttrType::INTS && arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }
  if ((left_->value_type() == AttrType::OBNULL || right_->value_type() == AttrType::OBNULL)){
    return AttrType::OBNULL;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value,
                              Value &value) const {
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  value.set_type(target_type);

  if (left_value.is_null() || right_value.is_null()) {
    value.set_null();
    return RC::SUCCESS;
  }

  switch (arithmetic_type_) {
  case Type::ADD: {
    if (target_type == AttrType::INTS) {
      value.set_int(left_value.get_int() + right_value.get_int());
    } else {
      value.set_float(left_value.get_float() + right_value.get_float());
    }
  } break;

  case Type::SUB: {
    if (target_type == AttrType::INTS) {
      value.set_int(left_value.get_int() - right_value.get_int());
    } else {
      value.set_float(left_value.get_float() - right_value.get_float());
    }
  } break;

  case Type::MUL: {
    if (target_type == AttrType::INTS) {
      value.set_int(left_value.get_int() * right_value.get_int());
    } else {
      value.set_float(left_value.get_float() * right_value.get_float());
    }
  } break;

  case Type::DIV: {
    if (target_type == AttrType::INTS) {
      if (right_value.get_int() == 0) {
        // NOTE:
        // 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
        //value.set_int(numeric_limits<int>::max());
        value.set_null();
      } else {
        value.set_int(left_value.get_int() / right_value.get_int());
      }
    } else {
      if (right_value.get_float() > -EPSILON &&
          right_value.get_float() < EPSILON) {
        // NOTE:
        // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
        value.set_null();
      } else {
        value.set_float(left_value.get_float() / right_value.get_float());
      }
    }
  } break;

  case Type::NEGATIVE: {
    if (target_type == AttrType::INTS) {
      value.set_int(-left_value.get_int());
    } else {
      value.set_float(-left_value.get_float());
    }
  } break;

  default: {
    rc = RC::INTERNAL;
    LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
  } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const {
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const {
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
RC AggregationExpr::get_value(const Tuple &tuple, Value &value) const {
  return tuple.cell_at(index(), value);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: implement function
RC FunctionExpr::get_value(const Tuple &tuple, Value &value) const {
  RC rc = RC::SUCCESS;
  Value ans;
  if (!is_value_) {
    rc =tuple.find_cell(TupleCellSpec(table_name(), field_name()), ans);
    if (rc != RC::SUCCESS) {
      LOG_WARN("function expression get value error");
      return rc;
    }
  } else {
    ans = value_;
  }

  // do function
  switch (func_type_) {
    case FunctionType::LENGTH_T: {
      if (ans.attr_type() != AttrType::CHARS) {
        return RC::INTERNAL;
      }
      // length func
      int length = ans.get_string().length();
      value.set_int(length);
    } break;
    case FunctionType::ROUND_T: {
      if (ans.attr_type() != AttrType::FLOATS) {
        return RC::INTERNAL;
      }
      float rounded_value = std::round(ans.get_float() * std::pow(10, int_param_)) / std::pow(10, int_param_);
      value.set_float(rounded_value);
    } break;
    case FunctionType::DATE_FORMAT_T: {
      if (ans.attr_type() != AttrType::DATES) {
        return RC::INTERNAL;
      }
      // date_format func
      int date_as_int = ans.get_int();
      std::string formatted_date = format_date(date_as_int, date_param_);
      value.set_string(formatted_date.c_str());
      value.set_type(AttrType::CHARS);
    } break;
    default: {
      return RC::INTERNAL;
    } break;
  }
  return rc;
}

std::string FunctionExpr::to_padded_string(int value, int padding) const {
    std::string str = std::to_string(value);
    while (str.length() < padding) {
        str = "0" + str;
    }
    return str;
}

std::string FunctionExpr::format_date(int date_int, const std::string& format) const  {
    int year = date_int / 10000;
    int month = (date_int % 10000) / 100;
    int day = date_int % 100;

    std::string result = "";
    for (size_t i = 0; i < format.size(); ++i) {
        if (format[i] == '%' && i + 1 < format.size()) {
            char next_char = format[i + 1];
            switch (next_char) {
                case 'y': result += to_padded_string(year % 100); break;
                case 'Y': result += std::to_string(year); break;
                case 'm': result += to_padded_string(month); break;
                case 'd': result += to_padded_string(day); break;
                case 'D': {
                    static const std::array<std::string, 31> suffixes = {
                        "st", "nd", "rd", "th", "th", "th", "th", "th", "th", "th",
                        "th", "th", "th", "th", "th", "th", "th", "th", "th", "th",
                        "st", "nd", "rd", "th", "th", "th", "th", "th", "th", "th", "st"
                    };
                    result += std::to_string(day) + suffixes[day - 1];
                } break;
                case 'M': {
                    static const std::vector<std::string> months = {
                        "January", "February", "March", "April", "May", "June",
                        "July", "August", "September", "October", "November", "December"
                    };
                    result += months[month - 1];
                } break;
                case 'z': result += 'z'; break;
                case 'n': result += 'n'; break;
                default: result += format[i]; break;
            }
            i++; // Skip next character
        } else {
            result += format[i];
        }
    }
    return result;
}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////

 RC SubSelectExpr::get_value(const Tuple &tuple, Value &value) const{
  return RC::INTERNAL;
 }


 RC SubSelectExpr::create_stmt(){
  Stmt * stmt  =nullptr;
  RC rc = SelectStmt::create(db_,this->get_subsqlNode(),stmt);
  subselect_stmt_ = stmt;
  return rc;
 }


///////////////////////////////////////////////////////////////////////////////////////////////////////////
RC SetExpr::get_value(const Tuple &tuple, Value &value) const{
  return RC::INTERNAL;
}

