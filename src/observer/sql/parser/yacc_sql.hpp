/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    CALC = 264,
    SELECT = 265,
    INNER = 266,
    JOIN = 267,
    DESC = 268,
    SHOW = 269,
    SYNC = 270,
    INSERT = 271,
    DELETE = 272,
    UPDATE = 273,
    LBRACE = 274,
    RBRACE = 275,
    COMMA = 276,
    TRX_BEGIN = 277,
    TRX_COMMIT = 278,
    TRX_ROLLBACK = 279,
    INT_T = 280,
    STRING_T = 281,
    FLOAT_T = 282,
    DATE_T = 283,
    NULL_T = 284,
    HELP = 285,
    EXIT = 286,
    DOT = 287,
    INTO = 288,
    VALUES = 289,
    FROM = 290,
    WHERE = 291,
    AND = 292,
    SET = 293,
    ON = 294,
    LOAD = 295,
    DATA = 296,
    INFILE = 297,
    EXPLAIN = 298,
    EQ = 299,
    LT = 300,
    GT = 301,
    LE = 302,
    GE = 303,
    NE = 304,
    LIKE = 305,
    IS = 306,
    NOT = 307,
    NUMBER = 308,
    DATE = 309,
    FLOAT = 310,
    ID = 311,
    SSS = 312,
    UMINUS = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 109 "yacc_sql.y"

  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  AggrAttrSqlNode *                 aggr_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  InnerJoinSqlNode *                inner_join;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<AggrAttrSqlNode> *    aggr_attr_list;
  std::vector<std::string> *        relation_list;
  std::vector<InnerJoinSqlNode> *   inner_join_list;
  std::vector<std::vector<Value>> * value_lists;
  char *                            string;
  int                               number;
  float                             floats;
  bool                              nullable;

#line 141 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
