//
// Created by Daijinxiang on 2023/11/1.
//


#include <algorithm>
#include <common/lang/string.h>

#include "storage/view/view_meta.h"
#include "json/json.h"
#include "common/log/log.h"
#include "storage/trx/trx.h"

using namespace std;

static const Json::StaticString FIELD_VIEW_NAME("view_name");
static const Json::StaticString FIELD_SQL_STRING("sql_string");
// static const Json::StaticString FIELD_ALIAS("alias");
// static const Json::StaticString FIELD_REL_NAME("relation_name");
// static const Json::StaticString FIELD_ATTR_NAME("attribute_name");

// static const Json::StaticString FIELD_SELECT_ATTRS("attributes");
// static const Json::StaticString FIELD_SELECT_ATTR_ALIAS("attribute_alias");

// static const Json::StaticString FIELD_SELECT_RELATIONS("relations");

// static const Json::StaticString FIELD_SELECT_AGGREGATIONS("aggregations");
// static const Json::StaticString FIELD_AGGR_NAME("aggregation_name");

// static const Json::StaticString FIELD_FROM_CONDITIONS("conditions");
// static const Json::StaticString FIELD_COMP("comp");
// static const Json::StaticString FIELD_LEFT_CON_TYPE("left_con_type");
// static const Json::StaticString FIELD_RIGHT_CON_TYPE("right_con_type");

// static const Json::StaticString FIELD_LEFT_EXPR("right_expr_node");
// static const Json::StaticString FIELD_RIGHT_EXPR("left_expr_node");

// static const Json::StaticString FIELD_ATTR_TYPE("attr_type");
// static const Json::StaticString FIELD_LENGTH("length_");
// static const Json::StaticString FIELD_NUM_VALUE("num_value_");
// static const Json::StaticString FIELD_STR_VALUE("str_value_");

// static const Json::StaticString FIELD_ORDERBYS("orderbys");
// static const Json::StaticString FIELD_ORDERBY_TYPE("order_type");

ViewMeta::ViewMeta(const ViewMeta &other)
{
    view_name_ = other.view_name_;
    sql_string_ = other.sql_string_;
    view_file_path_ = other.view_file_path_;
}

void ViewMeta::to_string(std::string &output) const {}

void ViewMeta::desc(std::ostream &os) const {}

int ViewMeta::get_serial_size() const {};

RC ViewMeta::init(const char * view_file_path, const char *view_name, SelectSqlNode *selection)
{
    view_name_ = view_name;
    view_file_path_ = view_file_path;
    selection_ = selection;
}

int ViewMeta::serialize(std::ostream &ss) const
{   
    Json::Value view_value_;
    view_value_[FIELD_VIEW_NAME] = view_name_;
    view_value_[FIELD_SQL_STRING] = selection_->select_string;


    Json::StreamWriterBuilder builder;
    Json::StreamWriter *writer = builder.newStreamWriter();

    std::streampos old_pos = ss.tellp();
    writer->write(view_value_, &ss);
    int ret = (int)(ss.tellp() - old_pos);

    delete writer;
    return ret;
}

int ViewMeta::deserialize(std::istream &is)
{
  Json::Value view_value;
  Json::CharReaderBuilder builder;
  std::string errors;

  std::streampos old_pos = is.tellg();
  if (!Json::parseFromStream(builder, is, &view_value, &errors)) {
    LOG_ERROR("Failed to deserialize table meta. error=%s", errors.c_str());
    return -1;
  }
  view_name_ = view_value[FIELD_VIEW_NAME].asString();
  sql_string_ = view_value[FIELD_SQL_STRING].asString();
  return (int)(is.tellg() - old_pos);
  
//   const Json::Value &table_id_value = table_value[FIELD_TABLE_ID];
//   if (!table_id_value.isInt()) {
//     LOG_ERROR("Invalid table id. json value=%s", table_id_value.toStyledString().c_str());
//     return -1;
//   }

//   int32_t table_id = table_id_value.asInt();

//   const Json::Value &table_name_value = table_value[FIELD_TABLE_NAME];
//   if (!table_name_value.isString()) {
//     LOG_ERROR("Invalid table name. json value=%s", table_name_value.toStyledString().c_str());
//     return -1;
//   }

//   std::string table_name = table_name_value.asString();

//   const Json::Value &fields_value = table_value[FIELD_FIELDS];
//   if (!fields_value.isArray() || fields_value.size() <= 0) {
//     LOG_ERROR("Invalid table meta. fields is not array, json value=%s", fields_value.toStyledString().c_str());
//     return -1;
//   }

//   RC rc = RC::SUCCESS;
//   int field_num = fields_value.size();
//   std::vector<FieldMeta> fields(field_num);
//   for (int i = 0; i < field_num; i++) {
//     FieldMeta &field = fields[i];

//     const Json::Value &field_value = fields_value[i];
//     rc = FieldMeta::from_json(field_value, field);
//     if (rc != RC::SUCCESS) {
//       LOG_ERROR("Failed to deserialize table meta. table name =%s", table_name.c_str());
//       return -1;
//     }
//   }

//   auto comparator = [](const FieldMeta &f1, const FieldMeta &f2) { return f1.offset() < f2.offset(); };
//   std::sort(fields.begin(), fields.end(), comparator);

//   table_id_ = table_id;
//   name_.swap(table_name);
//   fields_.swap(fields);
//   custom_fields_init();
//   record_size_ = fields_.back().offset() + fields_.back().len() - fields_.begin()->offset();

//   const Json::Value &indexes_value = table_value[FIELD_INDEXES];
//   if (!indexes_value.empty()) {
//     if (!indexes_value.isArray()) {
//       LOG_ERROR("Invalid table meta. indexes is not array, json value=%s", fields_value.toStyledString().c_str());
//       return -1;
//     }
//     const int index_num = indexes_value.size();
//     std::vector<IndexMeta> indexes(index_num);
//     for (int i = 0; i < index_num; i++) {
//       IndexMeta &index = indexes[i];

//       const Json::Value &index_value = indexes_value[i];
//       rc = IndexMeta::from_json(*this, index_value, index);
//       if (rc != RC::SUCCESS) {
//         LOG_ERROR("Failed to deserialize table meta. table name=%s", table_name.c_str());
//         return -1;
//       }
//     }
//     indexes_.swap(indexes);
//   }

//   const Json::Value &multi_indexes_value = table_value[FIELD_MULTI_INDEXES];
//   if (!multi_indexes_value.empty()) {
//     if (!multi_indexes_value.isArray()) {
//       LOG_ERROR("Invalid table meta. indexes is not array, json value=%s", fields_value.toStyledString().c_str());
//       return -1;
//     }
//     const int index_num = multi_indexes_value.size();
//     std::vector<IndexMeta> indexes(index_num);
//     for (int i = 0; i < index_num; i++) {
//       IndexMeta &index = indexes[i];

//       const Json::Value &multi_index_value = multi_indexes_value[i];
//       rc = IndexMeta::from_json(*this, multi_index_value, index);
//       if (rc != RC::SUCCESS) {
//         LOG_ERROR("Failed to deserialize table meta. table name=%s", table_name.c_str());
//         return -1;
//       }
//     }
//     multi_indexes_.swap(indexes);
//   }
//   isView_ = table_value[FIELD_IS_VIEW].asBool();

//   return (int)(is.tellg() - old_pos);
}