
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

int aggregation_cnt = 0;

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        INNER
        JOIN
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        NULL_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        EQ
        LT
        GT
        LE
        GE
        NE
        LIKE
        IS
        NOT
        UNIQUE
        ORDER
        BY
        ASC
        MINUS
        LENGTH
        ROUND
        DATE_FORMAT
        AS
        IN
        EXISTS
        COUNT
        MIN
        MAX
        SUM
        AVG

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  Value *                           expr_value;
  enum CompOp                       comp;
  enum OrderType                    order_type;
  RelAttrSqlNode *                  rel_attr;
  OrderBySqlNode *                  order_attr;
  AggrAttrSqlNode *                 aggr_attr;
  UpdateFieldNode *                 update_field;
  FuncSqlNode *                     func;
  ExprSqlNode *                     expression;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  // Expression *                      expression;
  InnerJoinSqlNode *                inner_join;
  // std::vector<Expression *> *       expression_list;
  std::vector<ExprSqlNode> *        expression_list;
  std::vector<Value> *              value_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<OrderBySqlNode> *     order_by_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<AggrAttrSqlNode> *    aggr_attr_list;
  std::vector<RelSqlNode> *         relation_list;
  std::vector<InnerJoinSqlNode> *   inner_join_list;
  std::vector<std::vector<Value>> * value_lists;
  std::vector<std::string> *        index_list;
  std::vector<UpdateFieldNode> *    update_field_list;
  char *                            string;
  char *                            alias;
  char *                            aggr_func;
  int                               number;
  float                             floats;
  bool                              nullable;
}

%token <number> NUMBER
%token <string> DATE
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <alias>               alias
%type <aggr_func>           aggr_func
%type <expr_value>          expr_value
%type <number>              number
%type <comp>                comp_op
%type <order_type>          order_type
%type <order_attr>          order_attr
%type <order_by_list>       order_by_list
%type <order_by_list>       order_by
%type <rel_attr>            rel_attr
%type <inner_join>          inner_join
%type <aggr_attr>           aggr_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <value_lists>         value_lists
%type <condition_list>      where
%type <condition_list>      condition_list
%type <rel_attr_list>       select_attr
%type <aggr_attr_list>      select_aggr_attr
%type <relation_list>       rel_list
%type <rel_attr_list>       attr_list
%type <inner_join_list>     innerJoin_list
%type <aggr_attr_list>      aggr_attr_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     set_expression
%type <nullable>            nullable
%type <index_list>          index_list
%type <update_field>        update_field
%type <update_field_list>   update_field_list
%type <func>                func
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' MINUS
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    /* CREATE INDEX ID ON ID LBRACE ID RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.attribute_name = $7;
      free($3);
      free($5);
      free($7);
    } */
    CREATE INDEX ID ON ID LBRACE index_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      if ($7 != nullptr) {
        create_index.attribute_names.swap(*$7);
        delete $7;
      }
      create_index.is_unique = false;
      free($3);
      free($5);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE index_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      if ($8 != nullptr) {
        create_index.attribute_names.swap(*$8);
        delete $8;
      }
      create_index.is_unique = true;
      free($4);
      free($6);
    }
    ;

index_list:
    ID
    {
        $$ = new std::vector<std::string>;
        $$->push_back($1);
        free($1);
    }
    | index_list COMMA ID 
    {
        $$ = $1;
        $$->push_back($3);
        free($3);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);
      create_table.use_select = false;
      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    | CREATE TABLE ID AS select_stmt
    {
      $$ = $5;
      $$->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);
      create_table.use_select = true;
    }
    | CREATE TABLE ID select_stmt 
    {
      $$ = $4;
      $$->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);
      create_table.use_select = true;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = $6;
      free($1);
    }
    | ID type nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = $3;
      free($1);
    }
    ;
nullable:
    /* empty 如果不指定默认字段可以为NULL （参考mysql的设计）*/
    {
      $$ = true;
    }
    |NULL_T
    {
      $$ = true;
    }
    |NOT NULL_T
    {
      $$ = false;
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES value_lists
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      $$->insertion.values.swap(*$5);
      delete $5;
      free($3);
    }
    ;
value_lists:
    LBRACE value_list RBRACE
    {
      $$ = new std::vector<std::vector<Value>>;
      $$->emplace_back(*$2);
      delete $2;
    }
    | value_lists COMMA LBRACE value_list RBRACE
    {
      $$ = $1;
      $$->emplace_back(*$4);
      delete $4;
    }
    ;
value_list:
      value
    {
      $$ = new std::vector<Value>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | value_list COMMA value { 
      $$ = $1;
      $$->emplace_back(*$3);
      delete $3;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    | MINUS NUMBER {
      $$ = new Value(-(int)$2);
      @$ = @2;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |MINUS FLOAT {
      $$ = new Value(-(float)$2);
      @$ = @2;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |DATE {
      char *tmp = common::substr($1,1,strlen($1)-2);
      bool check;
      $$ = new Value(tmp, &check);
      free(tmp);
      if (!check) {
        return -1;
      }
    }
    |NULL_T {
      $$ = new Value(AttrType::OBNULL);
    }
    ;
expr_value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |DATE {
      char *tmp = common::substr($1,1,strlen($1)-2);
      bool check;
      $$ = new Value(tmp, &check);
      free(tmp);
      if (!check) {
        return -1;
      }
    }
    |NULL_T {
      $$ = new Value(AttrType::OBNULL);
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_field_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      if ($5 != nullptr) {
        $$->update.conditions.swap(*$5);
        delete $5;
      }
      $$->update.fields.swap(*$4);
      delete $4;
      free($2);
    }
    ;
update_field_list:
    update_field
    {
      $$ = new std::vector<UpdateFieldNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | update_field_list COMMA update_field
    {
      $$ = $1;
      $$->emplace_back(*$3);
      delete $3;
    }
update_field:
    ID EQ value
    {
      $$ = new UpdateFieldNode();
      $$->attribute_name = $1;
      $$->is_value = true;
      $$->value = *$3;
      delete $3;
      free($1);
    }
    |
    ID EQ LBRACE select_stmt RBRACE
    {
      $$ = new UpdateFieldNode();
      $$->attribute_name = $1;
      $$->is_value = false;
      $$->subSelect = $4->selection;
      delete $4;
      free($1);
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    /* SELECT select_attr FROM ID rel_list innerJoin_list where order_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back($4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());
      if ($6 != nullptr) {
        $$->selection.innerJoins.swap(*$6);
        std::reverse($$->selection.innerJoins.begin(), $$->selection.innerJoins.end());
        delete $6;
      }
      if ($7 != nullptr) {
        $$->selection.conditions.swap(*$7);
        delete $7;
      }
      if ($8 != nullptr) {
        $$->selection.orderbys.swap(*$8);
        std::reverse($$->selection.orderbys.begin(), $$->selection.orderbys.end());
        delete $8;
      }
      free($4);
    }
    | SELECT select_aggr_attr FROM ID rel_list where
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.aggregations.swap(*$2);
        // add attribute too
        for (int i=0; i < $$->selection.aggregations.size(); i++) {
          RelAttrSqlNode attr;
          attr.relation_name  = $4;
          attr.attribute_name = $$->selection.aggregations[i].attribute_name;
          $$->selection.attributes.emplace_back(attr);
        }
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back($4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      if ($6 != nullptr) {
        $$->selection.conditions.swap(*$6);
        delete $6;
      }
      free($4);
    } */
    SELECT expression_list FROM ID alias rel_list innerJoin_list where order_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        for (const auto &expr : $$->selection.expressions) {
          for (const auto &attr : expr.attributes) {
            $$->selection.attributes.emplace_back(attr);
          }
          for (const auto &aggr : expr.aggregations) {
            $$->selection.aggregations.emplace_back(aggr);
          }
        }
        for (int i=0; i < $$->selection.aggregations.size(); i++) {
          $$->selection.attributes[i].relation_name = $4;
        }
        delete $2;
      }

      if ($6 != nullptr) {
        $$->selection.relations.swap(*$6);
        delete $6;
      }
      RelSqlNode rel_node;
      rel_node.relation_name = $4;
      free($4);
      if ($5 != nullptr) {
        rel_node.alias = $5;
      }
      $$->selection.relations.push_back(rel_node);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      // construct map
      for (const auto &[relation_name, alias] : $$->selection.relations) {
        $$->selection.rel_alias.insert(std::pair<std::string, std::string>(relation_name, alias));
      }

      if ($7 != nullptr) {
        $$->selection.innerJoins.swap(*$7);
        std::reverse($$->selection.innerJoins.begin(), $$->selection.innerJoins.end());
        delete $7;
      }
      if ($8 != nullptr) {
        $$->selection.conditions.swap(*$8);
        delete $8;
      }
      if ($9 != nullptr) {
        $$->selection.orderbys.swap(*$9);
        std::reverse($$->selection.orderbys.begin(), $$->selection.orderbys.end());
        delete $9;
      }
      aggregation_cnt = 0;
    }
    | SELECT expression_list
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }
    }
    /* | SELECT select_attr FROM ID rel_list where ORDER BY order_by_list 
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back($4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());
      if ($6 != nullptr) {
        $$->selection.innerJoins.swap(*$6);
        std::reverse($$->selection.innerJoins.begin(), $$->selection.innerJoins.end());
        delete $6;
      }
      if ($9 != nullptr) {
        $$->selection.orderbys.swap(*$9);
        delete $9;
      }
      free($4);
    } */
    | SELECT error FROM ID rel_list where
    {
      return -1;
    }
    ;
order_by:
    {
      $$ = nullptr;
    }
    | ORDER BY order_by_list 
    {
      $$ = $3;
    }
    ;

order_by_list:
    {
      $$ = nullptr;
    }
    | order_attr {
      $$ = new std::vector<OrderBySqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | order_attr COMMA order_by_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<OrderBySqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      // std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      std::reverse($$->calc.expressions.begin(), $$->calc.expressions.end());
      delete $2;
    }
    ;

expression_list:
    '*' alias
    {
      $$ = new std::vector<ExprSqlNode>;
      ExprSqlNode *expr_node = new ExprSqlNode;
      RelAttrSqlNode *rel_node = new RelAttrSqlNode;
      rel_node->attribute_name = "*";
      rel_node->relation_name = "";
      expr_node->attributes.push_back(*rel_node);
      expr_node->expression = nullptr;
      $$->emplace_back(*expr_node);
      delete rel_node;
      delete expr_node;
    }
    | expression
    {
      $$ = new std::vector<ExprSqlNode>;
      $$->emplace_back(*$1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<ExprSqlNode>;
      }
      $$->emplace_back(*$1);
    }
    ;
set_expression:
     COMMA expression
    {
      $$ = new std::vector<ExprSqlNode>;
      $$->emplace_back(*$2);
    }
    | COMMA expression set_expression{
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<ExprSqlNode>;
      }
      $$->emplace_back(*$2);
    }

expression:
    expression '+' expression {
      $$ = new ExprSqlNode;
      $$->expression = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1->expression, $3->expression, sql_string, &@$);
      // $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
      $$->aggregations.swap($3->aggregations);
      for (const auto &aggr : $1->aggregations) {
        $$->aggregations.emplace_back(aggr);
      }
      $$->attributes.swap($3->attributes);
      for (const auto &rel : $1->attributes) {
        $$->attributes.emplace_back(rel);
      }
      $$->functions.swap($3->functions);
      for (const auto &func : $1->functions) {
        $$->functions.emplace_back(func);
      }
    }
    | expression MINUS expression {
      $$ = new ExprSqlNode;
      $$->expression = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1->expression, $3->expression, sql_string, &@$);
      $$->aggregations.swap($3->aggregations);
      for (const auto &aggr : $1->aggregations) {
        $$->aggregations.emplace_back(aggr);
      }
      $$->attributes.swap($3->attributes);
      for (const auto &rel : $1->attributes) {
        $$->attributes.emplace_back(rel);
      }
      $$->functions.swap($3->functions);
      for (const auto &func : $1->functions) {
        $$->functions.emplace_back(func);
      }
    }
    | expression '*' expression {
      $$ = new ExprSqlNode;
      $$->expression = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1->expression, $3->expression, sql_string, &@$);
      $$->aggregations.swap($3->aggregations);
      for (const auto &aggr : $1->aggregations) {
        $$->aggregations.emplace_back(aggr);
      }
      $$->attributes.swap($3->attributes);
      for (const auto &rel : $1->attributes) {
        $$->attributes.emplace_back(rel);
      }
      $$->functions.swap($3->functions);
      for (const auto &func : $1->functions) {
        $$->functions.emplace_back(func);
      }
    }
    | expression '/' expression {
      $$ = new ExprSqlNode;
      $$->expression = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1->expression, $3->expression, sql_string, &@$);
      $$->aggregations.swap($3->aggregations);
      for (const auto &aggr : $1->aggregations) {
        $$->aggregations.emplace_back(aggr);
      }
      $$->attributes.swap($3->attributes);
      for (const auto &rel : $1->attributes) {
        $$->attributes.emplace_back(rel);
      }
      $$->functions.swap($3->functions);
      for (const auto &func : $1->functions) {
        $$->functions.emplace_back(func);
      }
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->expression->set_name(token_name(sql_string, &@$));
    }
    | LBRACE expression set_expression RBRACE
    {
      $3->emplace_back(*$2);
      std::reverse($3->begin(), $3->end());
      $$ = new ExprSqlNode;
      std::vector<Expression*> set;
      for (int i = 0; i < $3->size(); i++){
        set.push_back(std::move($3->at(i).expression));
      }
      $$->expression = new SetExpr(set);
      $$->expression->set_name(token_name(sql_string, &@$));
    }
    | MINUS expression {
      $$ = new ExprSqlNode;
      $$->expression = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2->expression, nullptr, sql_string, &@$);
      $$->aggregations.swap($2->aggregations);
      $$->attributes.swap($2->attributes);
      $$->functions.swap($2->functions);
    }
    | expr_value {
      $$ = new ExprSqlNode;
      $$->expression = new ValueExpr(*$1);
      $$->expression->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      $$ = new ExprSqlNode;
      $$->expression = new FieldExpr($1->relation_name,$1->attribute_name);
      if (!$1->attribute_alias.empty()) {
        $$->expression->set_name($1->attribute_alias);
      } else {
        $$->expression->set_name(token_name(sql_string, &@$));
      }
      $$->attributes.emplace_back(*$1);
      delete $1;
    }
    | aggr_attr {
      $$ = new ExprSqlNode;
      $$->expression = new AggregationExpr($1->aggregation_name,$1->attribute_name);
      $$->expression->set_name(token_name(sql_string, &@$));
      $$->aggregations.emplace_back(*$1);
      $$->expression->set_index(aggregation_cnt);
      aggregation_cnt++;
      RelAttrSqlNode *rel_node = new RelAttrSqlNode;
      rel_node->attribute_name = $1->attribute_name;
      $$->attributes.push_back(*rel_node);
      delete $1;
      delete rel_node;
    }
    | func {
      $$ = new ExprSqlNode;
      switch($1->function_type) {
        case FunctionType::LENGTH_T: {
          if ($1->is_attr) {
            $$->expression = new FunctionExpr($1->relation_name, $1->attribute_name, $1->function_type);
            // $$->expression->set_name(token_name(sql_string, &@$));
            $$->functions.emplace_back(*$1);
          } else {
            $$->expression = new FunctionExpr($1->value, $1->function_type);
            // $$->expression->set_name(token_name(sql_string, &@$));
            $$->functions.emplace_back(*$1);
          }
        } break;
        case FunctionType::ROUND_T: {
          if ($1->is_attr) {
            $$->expression = new FunctionExpr($1->relation_name, $1->attribute_name, $1->function_type, $1->param.get_int());
//$$->expression->set_name(token_name(sql_string, &@$));
            $$->functions.emplace_back(*$1);
          } else {
            $$->expression = new FunctionExpr($1->value, $1->function_type, $1->param.get_int());
//$$->expression->set_name(token_name(sql_string, &@$));
            $$->functions.emplace_back(*$1);
          }
        } break;
        case FunctionType::DATE_FORMAT_T: {
          if ($1->is_attr) {
            $$->expression = new FunctionExpr($1->relation_name, $1->attribute_name, $1->function_type, $1->param.get_string());
//$$->expression->set_name(token_name(sql_string, &@$));
            $$->functions.emplace_back(*$1);
          } else {
            $$->expression = new FunctionExpr($1->value, $1->function_type, $1->param.get_string());
//$$->expression->set_name(token_name(sql_string, &@$));
            $$->functions.emplace_back(*$1);
          }
        } break;
        default: {
          return -1;
        } break;
      }
      if (!$1->alias.empty()) {
        $$->expression->set_name($1->alias);
      } else {
        $$->expression->set_name(token_name(sql_string, &@$));
      }
      delete $1;
    }
    ;
    | select_stmt{
      $$ = new ExprSqlNode;
      ParsedSqlNode * subsql_node = std::move($1);
      $$->expression = new SubSelectExpr(subsql_node);   
      $$->expression->set_name(token_name(sql_string, &@$));
    }
    ;

select_attr:
    '*' {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      $$->emplace_back(attr);
    }
    | rel_attr attr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }

select_aggr_attr:
    aggr_attr aggr_attr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<AggrAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

rel_attr:
    ID alias {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      if ($2 != nullptr) {
        $$->attribute_alias = $2;
      }
      free($1);
    }
    | ID DOT '*' alias {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = "*";
      if ($4 != nullptr) {
        $$->attribute_alias = $4;
      }
      free($1);
    }
    | ID DOT ID alias {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      if ($4 != nullptr) {
        $$->attribute_alias = $4;
      }
      free($1);
      free($3);
    }
    ;

order_attr:
    ID order_type {
      $$ = new OrderBySqlNode;
      $$->attribute_name = $1;
      $$->order_type = $2;
      free($1);
    }
    | ID DOT ID order_type {
      $$ = new OrderBySqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      $$->order_type = $4;
      free($1);
      free($3);
    }
    ;

order_type:
    {
      $$ = ASC_T;
    }
    | ASC { $$ = ASC_T; }
    | DESC { $$ = DESC_T; }

aggr_attr:
    COUNT LBRACE '*' RBRACE alias {
      $$ = new AggrAttrSqlNode;
      $$->aggregation_name = "count";
      if ($5 != nullptr) {
        $$->alias = $5;
      }
      $$->attribute_name = "*";
    }
    | COUNT LBRACE ID RBRACE alias {
      $$ = new AggrAttrSqlNode;
      $$->aggregation_name = "count";
      if ($5 != nullptr) {
        $$->alias = $5;
      }
      $$->attribute_name = $3;
    }
    | aggr_func LBRACE ID RBRACE alias {
      $$ = new AggrAttrSqlNode;
      $$->aggregation_name = $1;
      if ($5 != nullptr) {
        $$->alias = $5;
      }
      $$->attribute_name = $3;
    }
    | aggr_func LBRACE ID DOT ID RBRACE alias {
      $$ = new AggrAttrSqlNode;
      $$->aggregation_name = $1;
      $$->relation_name =$3;
      if ($7 != nullptr) {
        $$->alias = $7;
      }
      $$->attribute_name = $5;
    }
    | aggr_func LBRACE RBRACE {
      return -1;
    }
    | aggr_func LBRACE error RBRACE {
      return -1;
    }
    ;

aggr_func:
    COUNT {
      $$ = "count";
    }
    | MIN {
      $$ = "min";
    }
    | MAX {
      $$ = "max";
    }
    | SUM {
      $$ = "sum";
    }
    | AVG {
      $$ = "avg";
    }
    ;
func:
    LENGTH LBRACE ID RBRACE alias {
      $$ = new FuncSqlNode;
      if ($5 != nullptr) {
        $$->alias = $5;
      }
      $$->function_type = FunctionType::LENGTH_T;
      $$->attribute_name = $3;
      $$->is_attr = true;
      free($3);
    }
    | LENGTH LBRACE ID DOT ID RBRACE alias {
      $$ = new FuncSqlNode;
      if ($7 != nullptr) {
        $$->alias = $7;
      }
      $$->function_type = FunctionType::LENGTH_T;
      $$->relation_name = $3;
      $$->attribute_name = $5;
      $$->is_attr = true;
      free($3);
      free($5);
    }
    | LENGTH LBRACE value RBRACE alias {
      $$ = new FuncSqlNode;
      if ($5 != nullptr) {
        $$->alias = $5;
      }
      $$->function_type = FunctionType::LENGTH_T;
      $$->value = *$3;
      $$->is_attr = false;
      delete $3;
    }
    | ROUND LBRACE ID RBRACE alias {
      $$ = new FuncSqlNode;
      if ($5 != nullptr) {
        $$->alias = $5;
      }
      $$->function_type = FunctionType::ROUND_T;
      $$->attribute_name = $3;
      $$->param = Value(0);
      free($3);
      $$->is_attr = true;
    }
    | ROUND LBRACE ID DOT ID RBRACE alias {
      $$ = new FuncSqlNode;
      if ($7 != nullptr) {
        $$->alias = $7;
      }
      $$->function_type = FunctionType::ROUND_T;
      $$->relation_name = $3;
      $$->attribute_name = $5;
      $$->is_attr = true;
      $$->param = Value(0);
      free($3);
      free($5);
    }
    | ROUND LBRACE value RBRACE alias {
      $$ = new FuncSqlNode;
      if ($5 != nullptr) {
        $$->alias = $5;
      }
      $$->function_type = FunctionType::ROUND_T;
      $$->value = *$3;
      $$->is_attr = false;
      $$->param = Value(0);
      delete $3;
    }
    | ROUND LBRACE ID COMMA value RBRACE alias {
      $$ = new FuncSqlNode;
      if ($7 != nullptr) {
        $$->alias = $7;
      }
      $$->function_type = FunctionType::ROUND_T;
      $$->attribute_name = $3;
      free($3);
      $$->param = *$5;
      $$->is_attr = true;
      delete $5;
    }
    | ROUND LBRACE ID DOT ID COMMA value RBRACE alias {
      $$ = new FuncSqlNode;
      if ($9 != nullptr) {
        $$->alias = $9;
      }
      $$->function_type = FunctionType::ROUND_T;
      $$->relation_name = $3;
      $$->attribute_name = $5;
      free($3);
      free($5);
      $$->param = *$7;
      $$->is_attr = true;
      delete $7;
    }
    | ROUND LBRACE value COMMA value RBRACE alias {
      $$ = new FuncSqlNode;
      if ($7 != nullptr) {
        $$->alias = $7;
      }
      $$->function_type = FunctionType::ROUND_T;
      $$->value = *$3;
      delete $3;
      $$->param = *$5;
      $$->is_attr = false;
      delete $5;
    }
    | DATE_FORMAT LBRACE ID COMMA value RBRACE alias {
      $$ = new FuncSqlNode;
      if ($7 != nullptr) {
        $$->alias = $7;
      }
      $$->function_type = FunctionType::DATE_FORMAT_T;
      $$->attribute_name = $3;
      free($3);
      $$->param = *$5;
      $$->is_attr = true;
      delete $5;
    }
    | DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE alias {
      $$ = new FuncSqlNode;
      if ($9 != nullptr) {
        $$->alias = $9;
      }
      $$->function_type = FunctionType::DATE_FORMAT_T;
      $$->relation_name = $3;
      $$->attribute_name = $5;
      free($3);
      free($5);
      $$->param = *$7;
      $$->is_attr = true;
      delete $7;
    }
    | DATE_FORMAT LBRACE value COMMA value RBRACE alias {
      $$ = new FuncSqlNode;
      if ($7 != nullptr) {
        $$->alias = $7;
      }
      $$->function_type = FunctionType::DATE_FORMAT_T;
      $$->value = *$3;
      delete $3;
      $$->param = *$5;
      $$->is_attr = false;
      delete $5;
    }
    ;

alias:
    {
      $$ = nullptr;
    }
    | ID {
      if (0 == strcmp($1, "alias")) {
        return -1;
      }
      $$ = $1;
    }
    | AS ID {
      if (0 == strcmp($2, "alias")) {
        return -1;
      }
      $$ = $2;
    }

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

aggr_attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA aggr_attr aggr_attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AggrAttrSqlNode>; 
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID alias rel_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<RelSqlNode>;
      }

      RelSqlNode *rel_node = new RelSqlNode;
      rel_node->relation_name = $2;
      free($2);
      if ($3 != nullptr) {
        rel_node->alias = $3;
      }
      $$->push_back(*rel_node);
    }
    ;
innerJoin_list:
    /* empty */
    {
      $$ = nullptr;
    }
    |inner_join innerJoin_list{
      if ($2 == nullptr)
        $$ = new std::vector<InnerJoinSqlNode>;
      else
        $$ = $2;
      $$->emplace_back(*$1);
      delete $1;
    }
inner_join:
    INNER JOIN ID ON condition_list {
      $$ = new InnerJoinSqlNode;
      $$->relation = $3;
      delete $3;
      $$->conditions.swap(*$5);
      delete $5;
    }
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    expression comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->comp = $2;
      $$->left_expr_node = *$1;
      // left
      switch ($1->expression->type()) {
        case ExprType::FIELD: {
          $$->left_con_type = ConditionType::CON_ATTR_T;
        } break;
        case ExprType::VALUE: {
          $$->left_con_type = ConditionType::CON_VALUE_T;
        } break;
        case ExprType::ARITHMETIC: {
          $$->left_con_type = ConditionType::CON_CALC_T;
        } break;
        case ExprType::AGGREGATION: {
          $$->left_con_type = ConditionType::CON_AGGR_T;
        } break;
        case ExprType::FUNCTION: {
          $$->left_con_type = ConditionType::CON_FUNC_T;
        } break;
        case ExprType::SUBSELECT: {
          $$->left_con_type = ConditionType::CON_SUBSELECT_T;
        } break;
        case ExprType::SET: {
          $$->left_con_type = ConditionType::CON_SET_T;
        } break;
        default: {
          return -1;
        } break;
      }
      // right
      $$->right_expr_node = *$3;
      switch ($3->expression->type()) {
        case ExprType::FIELD: {
          $$->right_con_type = ConditionType::CON_ATTR_T;
        } break;
        case ExprType::VALUE: {
          $$->right_con_type = ConditionType::CON_VALUE_T;
        } break;
        case ExprType::ARITHMETIC: {
          $$->right_con_type = ConditionType::CON_CALC_T;
        } break;
        case ExprType::AGGREGATION: {
          $$->right_con_type = ConditionType::CON_AGGR_T;
        } break;
        case ExprType::FUNCTION: {
          $$->right_con_type = ConditionType::CON_FUNC_T;
        } break;
        case ExprType::SUBSELECT: {
          $$->right_con_type = ConditionType::CON_SUBSELECT_T;
        } break;
        case ExprType::SET: {
          $$->right_con_type = ConditionType::CON_SET_T;
        } break;
        default: {
          return -1;
        } break;
      }
    }
    | EXISTS expression
    {
      $$ = new ConditionSqlNode;
      $$->comp = CompOp::EXISTS_OP;
      ExprSqlNode * left = new ExprSqlNode;
      left->expression = new ValueExpr(Value(1));
      left->expression->set_name("1");
      $$->left_expr_node = *left;
      $$->left_con_type = CON_VALUE_T;
      $$->right_expr_node = *$2;
      if ($2->expression->type() == ExprType::SUBSELECT)
      {
        $$->right_con_type = CON_SUBSELECT_T;
      }
      else
        return -1; /// exists 目前只考虑后面是子查询语句的情况
    }
    | NOT EXISTS expression
    {
      $$ = new ConditionSqlNode;
      $$->comp = CompOp::NOT_EXISTS_OP;
      ExprSqlNode * left = new ExprSqlNode;
      left->expression = new ValueExpr(Value(1));
      left->expression->set_name("1");
      $$->left_expr_node = *left;
      $$->left_con_type = CON_VALUE_T;
      $$->right_expr_node = *$3;
      if ($3->expression->type() == ExprType::SUBSELECT)
      {
        $$->right_con_type = CON_SUBSELECT_T;
      }
      else
        return -1; /// exists 目前只考虑后面是子查询语句的情况
    }
    /* rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    } */
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE {$$ = LIKE_OP;}
    | NOT LIKE { $$ = NOT_LIKE_OP;}
    | IS { $$ = IS_OP;}
    | IS NOT { $$ = IS_NOT_OP;}
    | IN {$$ = IN_OP;}
    | NOT IN { $$ = NOT_IN_OP;}
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
