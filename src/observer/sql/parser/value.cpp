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
// Created by WangYunlai on 2023/06/28.
//

#include "sql/parser/value.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field.h"
#include <cmath>
#include <sstream>

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "dates", "null","floats", "booleans"};

const char *attr_type_to_string(AttrType type) {
  if (type >= UNDEFINED && type <= FLOATS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s) {
  for (unsigned int i = 0;
       i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

int check_date(int y, int m, int d)
{
    static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (y%400==0 || (y%100 && y%4==0));
    return y > 0
        && (m > 0)&&(m <= 12)
        && (d > 0)&&(d <= ((m==2 && leap)?1:0) + mon[m]);
}

Value::Value(int val)
{
  set_int(val);
}

Value::Value(const char *s, bool *check)
{
  int year, month, day;
  sscanf(s, "%d-%d-%d", &year, &month, &day);
  *check = check_date(year, month, day);
  int val = year*10000 + month*100 + day;
  set_date(val);
}

Value::Value(float val)
{
  set_float(val);
}

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

Value::Value(AttrType val) { set_type(val);}

void Value::set_data(char *data, int length) {
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_ = length;
    } break;
    case DATES: {
      num_value_.date_value_ = *(int *)data;
      length_ = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_ = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_ = length;
    } break;
    case OBNULL:{
      // do nothing
    } 
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val) {
  attr_type_ = INTS;
  num_value_.int_value_ = val;
  length_ = sizeof(val);
}

void Value::set_date(int val)
{
  attr_type_ = DATES;
  num_value_.date_value_ = val;
  length_ = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_ = FLOATS;
  num_value_.float_value_ = val;
  length_ = sizeof(val);
}
void Value::set_boolean(bool val) {
  attr_type_ = BOOLEANS;
  num_value_.bool_value_ = val;
  length_ = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/) {
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_null(){
  attr_type_ = OBNULL;
}

void Value::set_value(const Value &value) {
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case DATES: {
      set_date(value.get_date());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case OBNULL: {
      set_null();
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}
// TODO index_sacn_physical_operator.cpp 中index scan处理null
// 
const char *Value::data() const {
  switch (attr_type_) {
  case CHARS: {
    return str_value_.c_str();
  } break;
  case OBNULL: {
    return nullptr;
  } break;
  default: {
    return (const char *)&num_value_;
  } break;
  }
}

std::string Value::to_string() const {
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case DATES: {
      os << common::date_to_str(num_value_.date_value_);
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case OBNULL: {
      os << attr_type_to_string(OBNULL);
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const {
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case DATES: {
        return common::compare_int((void *)&this->num_value_.date_value_, (void *)&other.num_value_.date_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      case OBNULL: {
        return 0;
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data,
                                 (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == OBNULL) {
    return -1;
  } else if (other.attr_type_ == OBNULL) {
    return 1;
  } else{
    return common::compare_other(this->get_float(),other.get_float());
  }
  LOG_WARN("not supported");
  return -1; // TODO return rc?
}

int Value::get_int() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case DATES: {
      return num_value_.date_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

int Value::get_date() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case DATES: {
      return num_value_.date_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case DATES: {
      return float(num_value_.date_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    case OBNULL: {
      return 0;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const
{
  return this->to_string();
}

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case DATES: {
      return num_value_.date_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    case OBNULL: {
      return false;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
}

// like条件过滤，后面考虑改写common中去
// other是pattern
bool Value::compare_like(const Value &other) const {
  int i = 0, j = 0;
  int i_len = this->str_value_.length();
  int p_len = other.str_value_.length();
  std::string input = this->str_value_;
  std::string pattern = other.str_value_;
  int prev_i = -1, prev_j = -1;

  while (i < i_len) {
    if (j < p_len && (pattern[j] == input[i] || pattern[j] == '_')) {
      i++;
      j++;
    } else if (j < p_len && pattern[j] == '%') {
      prev_i = i;
      prev_j = j++;
    } else if (prev_i != -1) {
      i = ++prev_i;
      j = prev_j + 1;
    } else {
      return false;
    }
  }

  while (j < p_len && pattern[j] == '%') {
    j++;
  }

  return j == p_len;
}

int Value::compare(const Value &other,int op) const{
  AttrType project_type1;
  AttrType project_type2;

  // 为 index 的null做映射
  if (this->attr_type_ == INTS){
    if (NULL_CNT + 1000 > this->get_int() && this->get_int() > NULL_CNT)
      project_type1 = AttrType::OBNULL;
  }
  // 为 index 的null做映射
  if (other.attr_type_ == INTS){
    if (NULL_CNT + 1000 > this->get_int() && other.get_int() > NULL_CNT)
      project_type2 = AttrType::OBNULL;
  }
  project_type1 = this->attr_type_;
  project_type2 = other.attr_type();
  if (op != IS_OP && op != IS_NOT_OP){
    if (project_type1 == OBNULL || project_type2 == OBNULL)
      return false;
  }
  int cmp_result = this->compare(other);
  switch (op) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;
    case LIKE_OP: {
      return this->compare_like(other);
    } break;
    case NOT_LIKE_OP: {
      return !this->compare_like(other);
    } break;
    case IS_OP: {
      if(project_type1 == OBNULL && project_type2 == OBNULL)
        return true;
      else
        return false;
    } break;
    case IS_NOT_OP:{
      if(project_type1 == OBNULL && OBNULL == project_type2)
        return false;
      else if (project_type1 != OBNULL && OBNULL != project_type2)
        return -1;
      else
        return true;
    }break;
    case IN_OP: {
        return 0 == cmp_result;
    }break;
    case NOT_IN_OP:{
        return 0 != cmp_result;
    }break;
    default:
      return -1;
      break;
  }
}

bool Value::is_null() const{
  return (attr_type() == AttrType::OBNULL);
}

bool Value::cast_type_to(AttrType type){
  switch (type)
  {
  case INTS:
  {
    if (this->attr_type() == CHARS)
    {  
      try {
          size_t idx;
          size_t len = this->get_string().size();
          this->set_int((int)(std::round(std::stof(this->get_string().c_str(),&idx))));
          return idx==len;
      } catch (std::exception const &ex) {
          return false;
      }
    }else if (this->attr_type() == FLOATS){
      this->set_int(std::round(this->get_float()));
      return true;
    }else{
      this->set_int(this->get_int());
      return true;
    }
  }break;
  case FLOATS:
  {
    if (this->attr_type() == CHARS)
    { 
      try {
        size_t idx;
        size_t len = this->get_string().size();
        this->set_float(std::stof(this->get_string().c_str(),&idx));
        return idx==len;
      } catch (std::exception const &ex) {
        return false;
      }
    }else{
      this->set_float(this->get_float());
      return true;
    }
  }break;
  case CHARS:
  {
    this->set_string(this->get_string().c_str());
    return true;
  }
  default:
    break;
  }
}