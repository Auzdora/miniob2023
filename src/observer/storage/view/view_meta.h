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

#include <string>
#include <vector>

#include "common/rc.h"
#include "json/json.h"
#include "storage/field/field_meta.h"
#include "storage/index/index_meta.h"
#include "common/lang/serializable.h"

/**
 * @brief 视图元数据
 * 
 */
class ViewMeta : public common::Serializable
{
public:
  ViewMeta() = default;
  ~ViewMeta() = default;

  ViewMeta(const ViewMeta &other);

  void swap(ViewMeta &other) noexcept;

  RC init(const char * view_file_path, const char *view_name, SelectSqlNode *selection);

public:
  int serialize(std::ostream &os) const override;
  int deserialize(std::istream &is) override;
  int get_serial_size() const override;
  void to_string(std::string &output) const override;
  void desc(std::ostream &os) const;
  std::string get_view_name() const { return view_name_; }
  std::string get_sql_string()const { return sql_string_; }
  std::vector<std::string> relate_tables() const { return relate_tables_; }

protected:
  std::string view_name_;
  std::string sql_string_;
  std::vector<std::string> relate_tables_;
  std::string view_file_path_;
  SelectSqlNode * selection_;
};
