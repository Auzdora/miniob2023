/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    CALC = 264,                    /* CALC  */
    SELECT = 265,                  /* SELECT  */
    INNER = 266,                   /* INNER  */
    JOIN = 267,                    /* JOIN  */
    DESC = 268,                    /* DESC  */
    SHOW = 269,                    /* SHOW  */
    SYNC = 270,                    /* SYNC  */
    INSERT = 271,                  /* INSERT  */
    DELETE = 272,                  /* DELETE  */
    UPDATE = 273,                  /* UPDATE  */
    LBRACE = 274,                  /* LBRACE  */
    RBRACE = 275,                  /* RBRACE  */
    COMMA = 276,                   /* COMMA  */
    TRX_BEGIN = 277,               /* TRX_BEGIN  */
    TRX_COMMIT = 278,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 279,            /* TRX_ROLLBACK  */
    INT_T = 280,                   /* INT_T  */
    STRING_T = 281,                /* STRING_T  */
    FLOAT_T = 282,                 /* FLOAT_T  */
    DATE_T = 283,                  /* DATE_T  */
    NULL_T = 284,                  /* NULL_T  */
    TEXT_T = 285,                  /* TEXT_T  */
    HELP = 286,                    /* HELP  */
    EXIT = 287,                    /* EXIT  */
    DOT = 288,                     /* DOT  */
    INTO = 289,                    /* INTO  */
    VALUES = 290,                  /* VALUES  */
    FROM = 291,                    /* FROM  */
    WHERE = 292,                   /* WHERE  */
    AND = 293,                     /* AND  */
    SET = 294,                     /* SET  */
    ON = 295,                      /* ON  */
    LOAD = 296,                    /* LOAD  */
    DATA = 297,                    /* DATA  */
    INFILE = 298,                  /* INFILE  */
    EXPLAIN = 299,                 /* EXPLAIN  */
    EQ = 300,                      /* EQ  */
    LT = 301,                      /* LT  */
    GT = 302,                      /* GT  */
    LE = 303,                      /* LE  */
    GE = 304,                      /* GE  */
    NE = 305,                      /* NE  */
    LIKE = 306,                    /* LIKE  */
    IS = 307,                      /* IS  */
    NOT = 308,                     /* NOT  */
    UNIQUE = 309,                  /* UNIQUE  */
    ORDER = 310,                   /* ORDER  */
    BY = 311,                      /* BY  */
    ASC = 312,                     /* ASC  */
    MINUS = 313,                   /* MINUS  */
    LENGTH = 314,                  /* LENGTH  */
    ROUND = 315,                   /* ROUND  */
    DATE_FORMAT = 316,             /* DATE_FORMAT  */
    AS = 317,                      /* AS  */
    IN = 318,                      /* IN  */
    EXISTS = 319,                  /* EXISTS  */
    COUNT = 320,                   /* COUNT  */
    MIN = 321,                     /* MIN  */
    MAX = 322,                     /* MAX  */
    SUM = 323,                     /* SUM  */
    AVG = 324,                     /* AVG  */
    NUMBER = 325,                  /* NUMBER  */
    DATE = 326,                    /* DATE  */
    FLOAT = 327,                   /* FLOAT  */
    ID = 328,                      /* ID  */
    SSS = 329,                     /* SSS  */
    UMINUS = 330                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 129 "yacc_sql.y"

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

#line 176 "yacc_sql.hpp"

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
