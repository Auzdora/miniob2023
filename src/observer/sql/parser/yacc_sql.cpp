/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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
int offset_aggr_cnt = 0;
int aggr_start_offset = 0; // for group by and aggr 


#line 119 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_INNER = 11,                     /* INNER  */
  YYSYMBOL_JOIN = 12,                      /* JOIN  */
  YYSYMBOL_DESC = 13,                      /* DESC  */
  YYSYMBOL_SHOW = 14,                      /* SHOW  */
  YYSYMBOL_SYNC = 15,                      /* SYNC  */
  YYSYMBOL_INSERT = 16,                    /* INSERT  */
  YYSYMBOL_DELETE = 17,                    /* DELETE  */
  YYSYMBOL_UPDATE = 18,                    /* UPDATE  */
  YYSYMBOL_VIEW = 19,                      /* VIEW  */
  YYSYMBOL_LBRACE = 20,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 21,                    /* RBRACE  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 23,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 24,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 25,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 26,                     /* INT_T  */
  YYSYMBOL_STRING_T = 27,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 28,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 29,                    /* DATE_T  */
  YYSYMBOL_NULL_T = 30,                    /* NULL_T  */
  YYSYMBOL_TEXT_T = 31,                    /* TEXT_T  */
  YYSYMBOL_HELP = 32,                      /* HELP  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_INTO = 35,                      /* INTO  */
  YYSYMBOL_VALUES = 36,                    /* VALUES  */
  YYSYMBOL_FROM = 37,                      /* FROM  */
  YYSYMBOL_WHERE = 38,                     /* WHERE  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_SET = 40,                       /* SET  */
  YYSYMBOL_ON = 41,                        /* ON  */
  YYSYMBOL_LOAD = 42,                      /* LOAD  */
  YYSYMBOL_INFILE = 43,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 44,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 45,                        /* EQ  */
  YYSYMBOL_LT = 46,                        /* LT  */
  YYSYMBOL_GT = 47,                        /* GT  */
  YYSYMBOL_LE = 48,                        /* LE  */
  YYSYMBOL_GE = 49,                        /* GE  */
  YYSYMBOL_NE = 50,                        /* NE  */
  YYSYMBOL_LIKE = 51,                      /* LIKE  */
  YYSYMBOL_IS = 52,                        /* IS  */
  YYSYMBOL_NOT = 53,                       /* NOT  */
  YYSYMBOL_UNIQUE = 54,                    /* UNIQUE  */
  YYSYMBOL_ORDER = 55,                     /* ORDER  */
  YYSYMBOL_GROUP = 56,                     /* GROUP  */
  YYSYMBOL_BY = 57,                        /* BY  */
  YYSYMBOL_HAVING = 58,                    /* HAVING  */
  YYSYMBOL_ASC = 59,                       /* ASC  */
  YYSYMBOL_MINUS = 60,                     /* MINUS  */
  YYSYMBOL_LENGTH = 61,                    /* LENGTH  */
  YYSYMBOL_ROUND = 62,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 63,               /* DATE_FORMAT  */
  YYSYMBOL_AS = 64,                        /* AS  */
  YYSYMBOL_IN = 65,                        /* IN  */
  YYSYMBOL_EXISTS = 66,                    /* EXISTS  */
  YYSYMBOL_COUNT = 67,                     /* COUNT  */
  YYSYMBOL_MIN = 68,                       /* MIN  */
  YYSYMBOL_MAX = 69,                       /* MAX  */
  YYSYMBOL_SUM = 70,                       /* SUM  */
  YYSYMBOL_AVG = 71,                       /* AVG  */
  YYSYMBOL_NUMBER = 72,                    /* NUMBER  */
  YYSYMBOL_DATE = 73,                      /* DATE  */
  YYSYMBOL_FLOAT = 74,                     /* FLOAT  */
  YYSYMBOL_ID = 75,                        /* ID  */
  YYSYMBOL_SSS = 76,                       /* SSS  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '*'  */
  YYSYMBOL_79_ = 79,                       /* '/'  */
  YYSYMBOL_UMINUS = 80,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_commands = 82,                  /* commands  */
  YYSYMBOL_command_wrapper = 83,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 84,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 85,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 86,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 87,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 88,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 89,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 90,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 91,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 92,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 93,         /* create_index_stmt  */
  YYSYMBOL_index_list = 94,                /* index_list  */
  YYSYMBOL_drop_index_stmt = 95,           /* drop_index_stmt  */
  YYSYMBOL_ids = 96,                       /* ids  */
  YYSYMBOL_create_table_stmt = 97,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 98,             /* attr_def_list  */
  YYSYMBOL_attr_def = 99,                  /* attr_def  */
  YYSYMBOL_nullable = 100,                 /* nullable  */
  YYSYMBOL_number = 101,                   /* number  */
  YYSYMBOL_type = 102,                     /* type  */
  YYSYMBOL_insert_stmt = 103,              /* insert_stmt  */
  YYSYMBOL_value_lists = 104,              /* value_lists  */
  YYSYMBOL_value_list = 105,               /* value_list  */
  YYSYMBOL_value = 106,                    /* value  */
  YYSYMBOL_expr_value = 107,               /* expr_value  */
  YYSYMBOL_delete_stmt = 108,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 109,              /* update_stmt  */
  YYSYMBOL_update_field_list = 110,        /* update_field_list  */
  YYSYMBOL_update_field = 111,             /* update_field  */
  YYSYMBOL_select_stmt = 112,              /* select_stmt  */
  YYSYMBOL_group_by = 113,                 /* group_by  */
  YYSYMBOL_having = 114,                   /* having  */
  YYSYMBOL_order_by = 115,                 /* order_by  */
  YYSYMBOL_order_by_list = 116,            /* order_by_list  */
  YYSYMBOL_calc_stmt = 117,                /* calc_stmt  */
  YYSYMBOL_expression_list = 118,          /* expression_list  */
  YYSYMBOL_set_expression = 119,           /* set_expression  */
  YYSYMBOL_expression = 120,               /* expression  */
  YYSYMBOL_rel_attr = 121,                 /* rel_attr  */
  YYSYMBOL_order_attr = 122,               /* order_attr  */
  YYSYMBOL_order_type = 123,               /* order_type  */
  YYSYMBOL_aggr_attr = 124,                /* aggr_attr  */
  YYSYMBOL_aggr_func = 125,                /* aggr_func  */
  YYSYMBOL_func = 126,                     /* func  */
  YYSYMBOL_alias = 127,                    /* alias  */
  YYSYMBOL_rel_list = 128,                 /* rel_list  */
  YYSYMBOL_innerJoin_list = 129,           /* innerJoin_list  */
  YYSYMBOL_inner_join = 130,               /* inner_join  */
  YYSYMBOL_where = 131,                    /* where  */
  YYSYMBOL_condition_list = 132,           /* condition_list  */
  YYSYMBOL_condition = 133,                /* condition  */
  YYSYMBOL_comp_op = 134,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 135,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 136,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 137,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 138             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  80
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   419

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  349

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    78,    77,     2,     2,     2,    79,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   246,   246,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   277,   283,   288,   294,   300,   306,   312,
     319,   325,   344,   358,   375,   381,   390,   400,   403,   407,
     423,   432,   442,   452,   463,   472,   484,   487,   500,   509,
     524,   527,   531,   537,   540,   541,   542,   543,   544,   547,
     557,   563,   571,   577,   584,   588,   592,   596,   600,   607,
     616,   621,   625,   629,   636,   645,   651,   663,   677,   683,
     690,   700,   767,   843,   875,   881,   884,   891,   894,   901,
     904,   911,   914,   919,   930,   941,   954,   959,   970,   975,
     985,  1002,  1018,  1034,  1050,  1066,  1078,  1085,  1091,  1102,
    1115,  1163,  1202,  1210,  1219,  1232,  1238,  1249,  1252,  1253,
    1256,  1264,  1272,  1280,  1289,  1300,  1303,  1309,  1312,  1315,
    1318,  1321,  1324,  1342,  1352,  1364,  1374,  1385,  1398,  1409,
    1421,  1435,  1447,  1459,  1473,  1488,  1491,  1497,  1539,  1542,
    1560,  1563,  1572,  1581,  1584,  1590,  1593,  1598,  1605,  1666,
    1683,  1751,  1752,  1753,  1754,  1755,  1756,  1757,  1758,  1759,
    1760,  1761,  1762,  1766,  1780,  1788,  1798,  1799
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "INNER", "JOIN",
  "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "VIEW", "LBRACE",
  "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T",
  "STRING_T", "FLOAT_T", "DATE_T", "NULL_T", "TEXT_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD",
  "INFILE", "EXPLAIN", "EQ", "LT", "GT", "LE", "GE", "NE", "LIKE", "IS",
  "NOT", "UNIQUE", "ORDER", "GROUP", "BY", "HAVING", "ASC", "MINUS",
  "LENGTH", "ROUND", "DATE_FORMAT", "AS", "IN", "EXISTS", "COUNT", "MIN",
  "MAX", "SUM", "AVG", "NUMBER", "DATE", "FLOAT", "ID", "SSS", "'+'",
  "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "index_list", "drop_index_stmt",
  "ids", "create_table_stmt", "attr_def_list", "attr_def", "nullable",
  "number", "type", "insert_stmt", "value_lists", "value_list", "value",
  "expr_value", "delete_stmt", "update_stmt", "update_field_list",
  "update_field", "select_stmt", "group_by", "having", "order_by",
  "order_by_list", "calc_stmt", "expression_list", "set_expression",
  "expression", "rel_attr", "order_attr", "order_type", "aggr_attr",
  "aggr_func", "func", "alias", "rel_list", "innerJoin_list", "inner_join",
  "where", "condition_list", "condition", "comp_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-249)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-133)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     339,    20,    46,   172,   103,   -61,    16,  -249,    -3,    87,
       8,  -249,  -249,  -249,  -249,  -249,    40,   339,    65,   125,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
      59,    61,    76,   132,    83,    93,   266,  -249,   266,   127,
     149,   163,   164,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
       0,  -249,    18,  -249,  -249,  -249,   -16,  -249,  -249,   166,
    -249,   150,   152,  -249,  -249,   115,   116,   153,   154,  -249,
    -249,  -249,  -249,     9,   157,     2,   120,  -249,   159,   -10,
     -31,    81,   137,   198,    42,    51,   126,  -249,  -249,  -249,
     172,   266,   266,   266,   266,    12,   129,   130,   167,   170,
     142,   206,   145,   213,  -249,   151,   155,   213,   183,   156,
    -249,   266,   204,  -249,    29,  -249,  -249,  -249,     4,  -249,
     208,    21,    88,    78,   205,   216,   217,    18,    18,  -249,
    -249,   -31,   -31,  -249,  -249,   230,  -249,    15,   231,   232,
      18,   235,   239,  -249,   211,    -1,  -249,  -249,   290,   238,
    -249,   237,   240,   242,  -249,   189,  -249,    -7,  -249,  -249,
    -249,    18,   200,    18,    18,   206,   202,    18,   206,   206,
     210,   206,    18,    18,  -249,  -249,  -249,    18,   212,    18,
     214,   170,   232,   206,   259,   222,   266,   340,  -249,   244,
      72,   142,  -249,  -249,  -249,  -249,  -249,  -249,    26,   145,
     269,   220,   155,   227,   277,  -249,  -249,   282,  -249,  -249,
     283,   117,  -249,   299,   301,   276,   302,  -249,  -249,  -249,
     303,  -249,    18,  -249,   314,   121,  -249,   310,   266,    28,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,   278,   -20,  -249,
     266,   239,   213,  -249,  -249,   273,  -249,   316,  -249,   238,
      14,  -249,   128,  -249,   213,   220,    18,    18,    18,   206,
      18,    18,   206,    18,    18,   232,   335,   170,   314,  -249,
     206,   206,    28,  -249,  -249,  -249,    28,  -249,   329,  -249,
     330,  -249,  -249,   213,  -249,  -249,   284,  -249,   138,  -249,
    -249,  -249,   337,  -249,  -249,   344,  -249,  -249,  -249,   285,
     306,  -249,  -249,   140,  -249,   -13,  -249,  -249,  -249,    18,
      18,   325,   311,   313,  -249,  -249,  -249,  -249,   239,   292,
     317,   312,  -249,    17,  -249,   351,   172,   239,  -249,  -249,
     300,  -249,  -249,   292,  -249,  -249,    22,  -249,  -249
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     173,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,   173,     0,   176,
      22,    21,    14,    15,    16,    17,     9,    10,    11,    12,
      13,     8,     5,     7,     6,     4,     3,    18,    19,    20,
       0,     0,     0,     0,     0,     0,     0,    75,     0,     0,
       0,     0,     0,   128,   129,   130,   131,    71,    74,    72,
     145,    73,   145,   107,   111,    94,    96,   108,   109,     0,
     110,     0,    83,    31,    30,     0,     0,     0,     0,   174,
       1,   177,     2,     0,     0,     0,     0,    29,     0,     0,
     106,     0,     0,     0,     0,     0,     0,   146,   112,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
     104,     0,     0,    70,     0,    64,    69,    66,     0,    68,
       0,     0,     0,     0,     0,     0,     0,   145,   145,   147,
      97,   101,   100,   102,   103,     0,   125,     0,     0,   148,
     145,     0,   155,    76,     0,   153,    78,   175,     0,    46,
      40,     0,    37,     0,    41,     0,    36,    98,   105,    65,
      67,   145,     0,   145,   145,     0,     0,   145,     0,     0,
       0,     0,   145,   145,   114,   113,   126,   145,     0,   145,
       0,   153,   148,     0,    59,     0,     0,     0,   154,   156,
       0,     0,    77,    54,    55,    56,    57,    58,    50,     0,
       0,     0,     0,     0,     0,    99,   133,     0,   135,   136,
       0,     0,   138,     0,     0,     0,     0,   121,   120,   122,
       0,   124,   145,    84,   150,     0,    62,     0,     0,   159,
     161,   162,   163,   164,   165,   166,   167,   169,     0,   171,
       0,   155,     0,    80,    79,     0,    51,     0,    49,    46,
      39,    34,     0,    38,     0,     0,   145,   145,   145,     0,
     145,   145,     0,   145,   145,   148,     0,   153,   150,    60,
       0,     0,   160,   170,   168,   172,   158,   157,     0,    53,
       0,    52,    47,     0,    45,    32,     0,    43,     0,   134,
     139,   137,     0,   141,   142,     0,   144,   123,   149,     0,
      89,   151,    63,     0,    81,    50,    44,    35,    33,   145,
     145,     0,     0,    85,    61,    48,   140,   143,   155,    91,
       0,    87,   152,   117,    90,    92,     0,   155,    82,   119,
       0,   118,   115,    91,    86,    88,   117,    93,   116
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -249,  -249,   359,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,   112,  -249,   168,  -249,   119,   173,    66,
    -249,  -249,  -249,  -249,   113,   -84,  -249,  -249,  -249,  -249,
     194,     1,  -249,  -249,  -249,    41,  -249,    -4,   229,   -44,
    -249,  -249,    52,  -249,  -249,  -249,   -52,  -176,   123,  -249,
    -150,  -248,  -249,  -249,  -249,  -249,  -249,  -249
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   262,    30,   163,    31,   210,   159,   258,
     290,   208,    32,   194,   235,   236,    63,    33,    34,   155,
     156,    64,   331,   338,   323,   334,    36,    65,   122,    66,
      67,   335,   342,    68,    69,    70,    98,   191,   277,   278,
     153,   198,   199,   250,    37,    38,    39,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    35,    89,   287,    90,   202,   100,   130,   132,   134,
      99,   120,   121,   145,    73,   121,   234,   256,    35,     4,
    -132,   201,   116,    74,     4,   171,    40,   157,    41,   112,
     339,   284,    75,   146,    95,   339,   187,   152,   172,    42,
     257,   233,   174,   175,   101,   285,   255,   103,   104,   188,
     101,   340,    44,   101,    45,   176,   256,   141,   142,   143,
     144,   102,   103,   104,    96,    80,   117,   102,   103,   104,
     102,   103,   104,   113,    43,    97,   341,   167,   293,   257,
     332,   341,    96,    77,   114,   184,   185,   147,   101,   345,
     148,   220,   252,    97,   223,   224,   140,   226,   192,   308,
     179,   169,   123,   170,    71,   102,   103,   104,   197,   177,
     178,   123,   180,     4,   160,    78,   253,   135,   164,   216,
     136,   218,   219,    46,    76,   222,   137,   310,    81,   138,
     227,   228,   124,    47,    83,   229,    84,   231,   268,   269,
      86,   124,   279,   280,   125,   126,   127,    91,   129,   295,
     296,    85,   239,   125,   126,   127,   128,   129,    87,   318,
     296,   324,   280,    48,    49,    50,    51,   123,    88,    92,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
     275,    62,     4,    93,    94,   302,   105,   106,   305,   107,
     108,   109,    46,   110,   282,   118,   312,   124,   115,   111,
     119,   139,    47,   151,   149,   150,   286,   197,   152,   125,
     126,   127,   131,   129,   299,   300,   301,   154,   303,   304,
     158,   306,   307,     4,   165,   168,   161,   181,   123,   173,
     162,   166,    48,    49,    50,    51,   123,   182,   183,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,     4,
      62,   186,   189,   288,   190,   193,   200,   211,   124,    46,
     209,   294,   212,   213,   214,   297,   124,   326,   327,    47,
     125,   126,   127,   133,   129,   217,     4,   221,   125,   126,
     127,   237,   129,   251,   197,   225,    46,   230,   238,   232,
     260,   264,   195,   197,   316,   261,    47,   265,   272,    48,
      49,    50,    51,   266,   267,   196,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   203,   204,   205,   206,
     270,   207,   271,   273,   274,   276,    48,    49,    50,    51,
     281,   283,   344,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,     1,     2,   289,   291,   309,     3,     4,
     314,   315,     5,     6,     7,     8,     9,    10,   319,   317,
     321,   322,    11,    12,    13,   320,   328,   333,   329,   330,
     337,    14,    15,   343,   336,   346,    79,   298,   292,    16,
     263,   325,   259,    17,   347,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   313,   254,   215,     0,   348,     0,
     101,   311,     0,     0,     0,   249,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104
};

static const yytype_int16 yycheck[] =
{
       4,     0,    46,   251,    48,   155,    22,    91,    92,    93,
      62,    21,    22,     1,    75,    22,   192,    30,    17,    10,
      20,    22,    20,     7,    10,    21,     6,   111,     8,    20,
      13,    51,    35,    21,    34,    13,    21,    38,    34,    19,
      53,   191,    21,    22,    60,    65,    20,    78,    79,    34,
      60,    34,     6,    60,     8,    34,    30,   101,   102,   103,
     104,    77,    78,    79,    64,     0,    64,    77,    78,    79,
      77,    78,    79,    64,    54,    75,    59,   121,    64,    53,
     328,    59,    64,    75,    83,   137,   138,    75,    60,   337,
      78,   175,    20,    75,   178,   179,   100,   181,   150,   275,
      22,    72,    30,    74,     1,    77,    78,    79,   152,    21,
      22,    30,    34,    10,   113,    75,   200,    75,   117,   171,
      78,   173,   174,    20,    37,   177,    75,   277,     3,    78,
     182,   183,    60,    30,    75,   187,    75,   189,    21,    22,
       8,    60,    21,    22,    72,    73,    74,    20,    76,    21,
      22,    75,   196,    72,    73,    74,    75,    76,    75,    21,
      22,    21,    22,    60,    61,    62,    63,    30,    75,    20,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     232,    78,    10,    20,    20,   269,    20,    37,   272,    37,
      75,    75,    20,    40,   238,    75,   280,    60,    41,    45,
      41,    75,    30,    36,    75,    75,   250,   251,    38,    72,
      73,    74,    75,    76,   266,   267,   268,    75,   270,   271,
      75,   273,   274,    10,    41,    21,    75,    22,    30,    21,
      75,    75,    60,    61,    62,    63,    30,    21,    21,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    10,
      78,    21,    21,   252,    22,    20,    45,    20,    60,    20,
      22,   260,    22,    21,    75,   264,    60,   319,   320,    30,
      72,    73,    74,    75,    76,    75,    10,    75,    72,    73,
      74,    22,    76,    39,   328,    75,    20,    75,    66,    75,
      21,    64,    53,   337,   293,    75,    30,    20,    22,    60,
      61,    62,    63,    21,    21,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    26,    27,    28,    29,
      21,    31,    21,    21,    21,    11,    60,    61,    62,    63,
      20,    53,   336,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,     4,     5,    72,    30,    12,     9,    10,
      21,    21,    13,    14,    15,    16,    17,    18,    21,    75,
      75,    55,    23,    24,    25,    21,    41,    75,    57,    56,
      58,    32,    33,    22,    57,    75,    17,   265,   259,    40,
     212,   315,   209,    44,   343,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   281,   201,   167,    -1,   346,    -1,
      60,   278,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    13,    14,    15,    16,    17,
      18,    23,    24,    25,    32,    33,    40,    44,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      95,    97,   103,   108,   109,   112,   117,   135,   136,   137,
       6,     8,    19,    54,     6,     8,    20,    30,    60,    61,
      62,    63,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    78,   107,   112,   118,   120,   121,   124,   125,
     126,     1,   118,    75,     7,    35,    37,    75,    75,    83,
       0,     3,   138,    75,    75,    75,     8,    75,    75,   120,
     120,    20,    20,    20,    20,    34,    64,    75,   127,   127,
      22,    60,    77,    78,    79,    20,    37,    37,    75,    75,
      40,    45,    20,    64,   112,    41,    20,    64,    75,    41,
      21,    22,   119,    30,    60,    72,    73,    74,    75,    76,
     106,    75,   106,    75,   106,    75,    78,    75,    78,    75,
     118,   120,   120,   120,   120,     1,    21,    75,    78,    75,
      75,    36,    38,   131,    75,   110,   111,   106,    75,    99,
     112,    75,    75,    96,   112,    41,    75,   120,    21,    72,
      74,    21,    34,    21,    21,    22,    34,    21,    22,    22,
      34,    22,    21,    21,   127,   127,    21,    21,    34,    21,
      22,   128,   127,    20,   104,    53,    66,   120,   132,   133,
      45,    22,   131,    26,    27,    28,    29,    31,   102,    22,
      98,    20,    22,    21,    75,   119,   127,    75,   127,   127,
     106,    75,   127,   106,   106,    75,   106,   127,   127,   127,
      75,   127,    75,   131,   128,   105,   106,    22,    66,   120,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    65,
     134,    39,    20,   106,   111,    20,    30,    53,   100,    99,
      21,    75,    94,    96,    64,    20,    21,    21,    21,    22,
      21,    21,    22,    21,    21,   127,    11,   129,   130,    21,
      22,    20,   120,    53,    51,    65,   120,   132,   112,    72,
     101,    30,    98,    64,   112,    21,    22,   112,    94,   127,
     127,   127,   106,   127,   127,   106,   127,   127,   128,    12,
     131,   129,   106,   105,    21,    21,   112,    75,    21,    21,
      21,    75,    55,   115,    21,   100,   127,   127,    41,    57,
      56,   113,   132,    75,   116,   122,    57,    58,   114,    13,
      34,    59,   123,    22,   118,   132,    75,   116,   123
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    93,    94,    94,    95,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    98,    98,    99,    99,
     100,   100,   100,   101,   102,   102,   102,   102,   102,   103,
     104,   104,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   107,   107,   107,   107,   107,   108,   109,   110,   110,
     111,   111,   112,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   116,   117,   118,   118,   118,   119,   119,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   121,   121,   121,   122,   122,   123,   123,   123,
     124,   124,   124,   124,   124,   124,   124,   125,   125,   125,
     125,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   127,   127,   127,   128,   128,
     129,   129,   130,   131,   131,   132,   132,   132,   133,   133,
     133,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   135,   136,   137,   138,   138
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     9,     1,     3,     5,     1,     3,     7,
       5,     5,     4,     8,     9,     8,     0,     3,     6,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     5,
       3,     5,     1,     3,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     5,     1,     3,
       3,     5,    11,     2,     6,     0,     3,     0,     2,     0,
       3,     0,     1,     3,     2,     2,     1,     3,     2,     3,
       3,     3,     3,     3,     3,     4,     2,     1,     1,     1,
       1,     1,     2,     4,     4,     2,     4,     0,     1,     1,
       5,     5,     5,     7,     5,     3,     4,     1,     1,     1,
       1,     1,     1,     5,     7,     5,     5,     7,     5,     7,
       9,     7,     7,     9,     7,     0,     1,     2,     0,     4,
       0,     2,     5,     0,     2,     0,     1,     3,     3,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     0,     2,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 247 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1908 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 277 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1917 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 283 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1925 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 288 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1933 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 294 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 300 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1949 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 306 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1957 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 312 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1967 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 319 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1975 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 325 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1985 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE index_list RBRACE  */
#line 345 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      if ((yyvsp[-1].index_list) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].index_list));
        delete (yyvsp[-1].index_list);
      }
      create_index.is_unique = false;
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2003 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE index_list RBRACE  */
#line 359 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      if ((yyvsp[-1].index_list) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].index_list));
        delete (yyvsp[-1].index_list);
      }
      create_index.is_unique = true;
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2021 "yacc_sql.cpp"
    break;

  case 34: /* index_list: ID  */
#line 376 "yacc_sql.y"
    {
        (yyval.index_list) = new std::vector<std::string>;
        (yyval.index_list)->push_back((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 2031 "yacc_sql.cpp"
    break;

  case 35: /* index_list: index_list COMMA ID  */
#line 382 "yacc_sql.y"
    {
        (yyval.index_list) = (yyvsp[-2].index_list);
        (yyval.index_list)->push_back((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 2041 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 391 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2053 "yacc_sql.cpp"
    break;

  case 37: /* ids: ID  */
#line 400 "yacc_sql.y"
    {

  }
#line 2061 "yacc_sql.cpp"
    break;

  case 38: /* ids: ID COMMA ids  */
#line 403 "yacc_sql.y"
               {

  }
#line 2069 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 408 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));
      create_table.use_select = false;
      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2089 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID AS select_stmt  */
#line 424 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      create_table.use_select = true;
    }
#line 2102 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE VIEW ID AS select_stmt  */
#line 433 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      std::reverse((yyval.sql_node)->selection.expressions.begin(),(yyval.sql_node)->selection.expressions.end());
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      create_table.is_view = true;
      free((yyvsp[-2].string));
    }
#line 2116 "yacc_sql.cpp"
    break;

  case 42: /* create_table_stmt: CREATE TABLE ID select_stmt  */
#line 443 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      create_table.use_select = true;
    }
#line 2129 "yacc_sql.cpp"
    break;

  case 43: /* create_table_stmt: CREATE VIEW ID LBRACE ids RBRACE AS select_stmt  */
#line 453 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      std::reverse((yyval.sql_node)->selection.expressions.begin(),(yyval.sql_node)->selection.expressions.end());
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      create_table.is_view = true;
      free((yyvsp[-5].string));
      create_table.use_select = true;
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 44: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt  */
#line 464 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));
      create_table.use_select = true;
    }
#line 2157 "yacc_sql.cpp"
    break;

  case 45: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt  */
#line 473 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));
      create_table.use_select = true;
    }
#line 2170 "yacc_sql.cpp"
    break;

  case 46: /* attr_def_list: %empty  */
#line 484 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 47: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 488 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2192 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 501 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);                // 没考虑 text 指定长度的情况
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-5].string));
    }
#line 2205 "yacc_sql.cpp"
    break;

  case 49: /* attr_def: ID type nullable  */
#line 510 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      if ((yyvsp[-1].number) == TEXTS)
        (yyval.attr_info)->length = 8;             // 等于 text 头部数据长度 4字节的length 和4字节的数据起始地址
      else
        (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-2].string));
    }
#line 2221 "yacc_sql.cpp"
    break;

  case 50: /* nullable: %empty  */
#line 524 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2229 "yacc_sql.cpp"
    break;

  case 51: /* nullable: NULL_T  */
#line 528 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2237 "yacc_sql.cpp"
    break;

  case 52: /* nullable: NOT NULL_T  */
#line 532 "yacc_sql.y"
    {
      (yyval.nullable) = false;
    }
#line 2245 "yacc_sql.cpp"
    break;

  case 53: /* number: NUMBER  */
#line 537 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2251 "yacc_sql.cpp"
    break;

  case 54: /* type: INT_T  */
#line 540 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2257 "yacc_sql.cpp"
    break;

  case 55: /* type: STRING_T  */
#line 541 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2263 "yacc_sql.cpp"
    break;

  case 56: /* type: FLOAT_T  */
#line 542 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2269 "yacc_sql.cpp"
    break;

  case 57: /* type: DATE_T  */
#line 543 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2275 "yacc_sql.cpp"
    break;

  case 58: /* type: TEXT_T  */
#line 544 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2281 "yacc_sql.cpp"
    break;

  case 59: /* insert_stmt: INSERT INTO ID VALUES value_lists  */
#line 548 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].value_lists));
      delete (yyvsp[0].value_lists);
      free((yyvsp[-2].string));
    }
#line 2293 "yacc_sql.cpp"
    break;

  case 60: /* value_lists: LBRACE value_list RBRACE  */
#line 558 "yacc_sql.y"
    {
      (yyval.value_lists) = new std::vector<std::vector<Value>>;
      (yyval.value_lists)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2303 "yacc_sql.cpp"
    break;

  case 61: /* value_lists: value_lists COMMA LBRACE value_list RBRACE  */
#line 564 "yacc_sql.y"
    {
      (yyval.value_lists) = (yyvsp[-4].value_lists);
      (yyval.value_lists)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2313 "yacc_sql.cpp"
    break;

  case 62: /* value_list: value  */
#line 572 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 63: /* value_list: value_list COMMA value  */
#line 577 "yacc_sql.y"
                             { 
      (yyval.value_list) = (yyvsp[-2].value_list);
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2333 "yacc_sql.cpp"
    break;

  case 64: /* value: NUMBER  */
#line 584 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2342 "yacc_sql.cpp"
    break;

  case 65: /* value: MINUS NUMBER  */
#line 588 "yacc_sql.y"
                   {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2351 "yacc_sql.cpp"
    break;

  case 66: /* value: FLOAT  */
#line 592 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2360 "yacc_sql.cpp"
    break;

  case 67: /* value: MINUS FLOAT  */
#line 596 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2369 "yacc_sql.cpp"
    break;

  case 68: /* value: SSS  */
#line 600 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      if (strlen(tmp) > 65535)
        return -1;
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2381 "yacc_sql.cpp"
    break;

  case 69: /* value: DATE  */
#line 607 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      bool check;
      (yyval.value) = new Value(tmp, &check);
      free(tmp);
      if (!check) {
        return -1;
      }
    }
#line 2395 "yacc_sql.cpp"
    break;

  case 70: /* value: NULL_T  */
#line 616 "yacc_sql.y"
            {
      (yyval.value) = new Value(AttrType::OBNULL);
    }
#line 2403 "yacc_sql.cpp"
    break;

  case 71: /* expr_value: NUMBER  */
#line 621 "yacc_sql.y"
           {
      (yyval.expr_value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2412 "yacc_sql.cpp"
    break;

  case 72: /* expr_value: FLOAT  */
#line 625 "yacc_sql.y"
           {
      (yyval.expr_value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2421 "yacc_sql.cpp"
    break;

  case 73: /* expr_value: SSS  */
#line 629 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      if (strlen(tmp) > 65535)
        return -1;
      (yyval.expr_value) = new Value(tmp);
      free(tmp);
    }
#line 2433 "yacc_sql.cpp"
    break;

  case 74: /* expr_value: DATE  */
#line 636 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      bool check;
      (yyval.expr_value) = new Value(tmp, &check);
      free(tmp);
      if (!check) {
        return -1;
      }
    }
#line 2447 "yacc_sql.cpp"
    break;

  case 75: /* expr_value: NULL_T  */
#line 645 "yacc_sql.y"
            {
      (yyval.expr_value) = new Value(AttrType::OBNULL);
    }
#line 2455 "yacc_sql.cpp"
    break;

  case 76: /* delete_stmt: DELETE FROM ID where  */
#line 652 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2469 "yacc_sql.cpp"
    break;

  case 77: /* update_stmt: UPDATE ID SET update_field_list where  */
#line 664 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      (yyval.sql_node)->update.fields.swap(*(yyvsp[-1].update_field_list));
      delete (yyvsp[-1].update_field_list);
      free((yyvsp[-3].string));
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 78: /* update_field_list: update_field  */
#line 678 "yacc_sql.y"
    {
      (yyval.update_field_list) = new std::vector<UpdateFieldNode>;
      (yyval.update_field_list)->emplace_back(*(yyvsp[0].update_field));
      delete (yyvsp[0].update_field);
    }
#line 2495 "yacc_sql.cpp"
    break;

  case 79: /* update_field_list: update_field_list COMMA update_field  */
#line 684 "yacc_sql.y"
    {
      (yyval.update_field_list) = (yyvsp[-2].update_field_list);
      (yyval.update_field_list)->emplace_back(*(yyvsp[0].update_field));
      delete (yyvsp[0].update_field);
    }
#line 2505 "yacc_sql.cpp"
    break;

  case 80: /* update_field: ID EQ value  */
#line 691 "yacc_sql.y"
    {
      (yyval.update_field) = new UpdateFieldNode();
      (yyval.update_field)->attribute_name = (yyvsp[-2].string);
      (yyval.update_field)->is_value = true;
      (yyval.update_field)->value = *(yyvsp[0].value);
      delete (yyvsp[0].value);
      free((yyvsp[-2].string));
    }
#line 2518 "yacc_sql.cpp"
    break;

  case 81: /* update_field: ID EQ LBRACE select_stmt RBRACE  */
#line 701 "yacc_sql.y"
    {
      (yyval.update_field) = new UpdateFieldNode();
      (yyval.update_field)->attribute_name = (yyvsp[-4].string);
      (yyval.update_field)->is_value = false;
      (yyval.update_field)->subSelect = (yyvsp[-1].sql_node)->selection;
      delete (yyvsp[-1].sql_node);
      free((yyvsp[-4].string));
    }
#line 2531 "yacc_sql.cpp"
    break;

  case 82: /* select_stmt: SELECT expression_list FROM ID alias rel_list innerJoin_list where order_by group_by having  */
#line 768 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->selection.select_string = token_name(sql_string, &(yyloc));
      if ((yyvsp[-1].group_by_list) != nullptr) {
        (yyval.sql_node)->selection.use_group_by = true;
        (yyval.sql_node)->selection.groupbys.swap(*(yyvsp[-1].group_by_list));
        std::reverse((yyval.sql_node)->selection.groupbys.begin(), (yyval.sql_node)->selection.groupbys.end());
        delete (yyvsp[-1].group_by_list);
      } else {
        (yyval.sql_node)->selection.use_group_by = false;
      }
      if ((yyvsp[-9].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-9].expression_list));
        for (const auto &expr : (yyval.sql_node)->selection.expressions) {
          for (const auto &attr : expr.attributes) {
            (yyval.sql_node)->selection.attributes.emplace_back(attr);
          }
          for (const auto &aggr : expr.aggregations) {
            (yyval.sql_node)->selection.aggregations.emplace_back(aggr);
          }
        }
        for (int i=0; i < (yyval.sql_node)->selection.aggregations.size(); i++) {
          if ((yyval.sql_node)->selection.use_group_by) {
            if ((yyval.sql_node)->selection.aggregations[i].relation_name.empty()) {
              (yyval.sql_node)->selection.attributes[i].relation_name = (yyvsp[-7].string);
            } else {
              (yyval.sql_node)->selection.attributes[i].relation_name = (yyval.sql_node)->selection.aggregations[i].relation_name;
            }
          } else {
            (yyval.sql_node)->selection.attributes[i].relation_name = (yyvsp[-7].string);
          }
        }
        delete (yyvsp[-9].expression_list);
      }

      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }
      RelSqlNode rel_node;
      rel_node.relation_name = (yyvsp[-7].string);
      free((yyvsp[-7].string));
      if ((yyvsp[-6].alias) != nullptr) {
        rel_node.alias = (yyvsp[-6].alias);
      }
      (yyval.sql_node)->selection.relations.push_back(rel_node);
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      // construct map
      for (const auto &[relation_name, alias] : (yyval.sql_node)->selection.relations) {
        (yyval.sql_node)->selection.rel_alias.insert(std::pair<std::string, std::string>(relation_name, alias));
      }

      if ((yyvsp[-4].inner_join_list) != nullptr) {
        (yyval.sql_node)->selection.innerJoins.swap(*(yyvsp[-4].inner_join_list));
        std::reverse((yyval.sql_node)->selection.innerJoins.begin(), (yyval.sql_node)->selection.innerJoins.end());
        delete (yyvsp[-4].inner_join_list);
      }
      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }
      if ((yyvsp[-2].order_by_list) != nullptr) {
        (yyval.sql_node)->selection.orderbys.swap(*(yyvsp[-2].order_by_list));
        std::reverse((yyval.sql_node)->selection.orderbys.begin(), (yyval.sql_node)->selection.orderbys.end());
        delete (yyvsp[-2].order_by_list);
      }
      // having conditon
      if ((yyvsp[0].having) != nullptr) {
        (yyval.sql_node)->selection.having_conditions.swap(*(yyvsp[0].having));
        delete (yyvsp[0].having);
      }
      aggregation_cnt = 0;
      // aggr_start_offset = 0;
    }
#line 2611 "yacc_sql.cpp"
    break;

  case 83: /* select_stmt: SELECT expression_list  */
#line 844 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 84: /* select_stmt: SELECT error FROM ID rel_list where  */
#line 876 "yacc_sql.y"
    {
      return -1;
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 85: /* group_by: %empty  */
#line 881 "yacc_sql.y"
    {
      (yyval.group_by_list) = nullptr;
    }
#line 2639 "yacc_sql.cpp"
    break;

  case 86: /* group_by: GROUP BY expression_list  */
#line 885 "yacc_sql.y"
    {
      (yyval.group_by_list) = (yyvsp[0].expression_list);
    }
#line 2647 "yacc_sql.cpp"
    break;

  case 87: /* having: %empty  */
#line 891 "yacc_sql.y"
    {
      (yyval.having) = nullptr;
    }
#line 2655 "yacc_sql.cpp"
    break;

  case 88: /* having: HAVING condition_list  */
#line 895 "yacc_sql.y"
    {
      (yyval.having) = (yyvsp[0].condition_list);
    }
#line 2663 "yacc_sql.cpp"
    break;

  case 89: /* order_by: %empty  */
#line 901 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2671 "yacc_sql.cpp"
    break;

  case 90: /* order_by: ORDER BY order_by_list  */
#line 905 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2679 "yacc_sql.cpp"
    break;

  case 91: /* order_by_list: %empty  */
#line 911 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2687 "yacc_sql.cpp"
    break;

  case 92: /* order_by_list: order_attr  */
#line 914 "yacc_sql.y"
                 {
      (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      (yyval.order_by_list)->emplace_back(*(yyvsp[0].order_attr));
      delete (yyvsp[0].order_attr);
    }
#line 2697 "yacc_sql.cpp"
    break;

  case 93: /* order_by_list: order_attr COMMA order_by_list  */
#line 919 "yacc_sql.y"
                                     {
      if ((yyvsp[0].order_by_list) != nullptr) {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else {
        (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      }
      (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_attr));
      delete (yyvsp[-2].order_attr);
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 94: /* calc_stmt: CALC expression_list  */
#line 931 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      // std::reverse($2->begin(), $2->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      std::reverse((yyval.sql_node)->calc.expressions.begin(), (yyval.sql_node)->calc.expressions.end());
      delete (yyvsp[0].expression_list);
    }
#line 2723 "yacc_sql.cpp"
    break;

  case 95: /* expression_list: '*' alias  */
#line 942 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<ExprSqlNode>;
      ExprSqlNode *expr_node = new ExprSqlNode;
      RelAttrSqlNode *rel_node = new RelAttrSqlNode;
      rel_node->attribute_name = "*";
      rel_node->relation_name = "";
      expr_node->attributes.push_back(*rel_node);
      expr_node->expression = nullptr;
      (yyval.expression_list)->emplace_back(*expr_node);
      delete rel_node;
      delete expr_node;
    }
#line 2740 "yacc_sql.cpp"
    break;

  case 96: /* expression_list: expression  */
#line 955 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<ExprSqlNode>;
      (yyval.expression_list)->emplace_back(*(yyvsp[0].expression));
    }
#line 2749 "yacc_sql.cpp"
    break;

  case 97: /* expression_list: expression COMMA expression_list  */
#line 960 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<ExprSqlNode>;
      }
      (yyval.expression_list)->emplace_back(*(yyvsp[-2].expression));
    }
#line 2762 "yacc_sql.cpp"
    break;

  case 98: /* set_expression: COMMA expression  */
#line 971 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<ExprSqlNode>;
      (yyval.expression_list)->emplace_back(*(yyvsp[0].expression));
    }
#line 2771 "yacc_sql.cpp"
    break;

  case 99: /* set_expression: COMMA expression set_expression  */
#line 975 "yacc_sql.y"
                                     {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<ExprSqlNode>;
      }
      (yyval.expression_list)->emplace_back(*(yyvsp[-1].expression));
    }
#line 2784 "yacc_sql.cpp"
    break;

  case 100: /* expression: expression '+' expression  */
#line 985 "yacc_sql.y"
                              {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression)->expression, (yyvsp[0].expression)->expression, sql_string, &(yyloc));
      // $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
      (yyval.expression)->aggregations.swap((yyvsp[0].expression)->aggregations);
      for (const auto &aggr : (yyvsp[-2].expression)->aggregations) {
        (yyval.expression)->aggregations.emplace_back(aggr);
      }
      (yyval.expression)->attributes.swap((yyvsp[0].expression)->attributes);
      for (const auto &rel : (yyvsp[-2].expression)->attributes) {
        (yyval.expression)->attributes.emplace_back(rel);
      }
      (yyval.expression)->functions.swap((yyvsp[0].expression)->functions);
      for (const auto &func : (yyvsp[-2].expression)->functions) {
        (yyval.expression)->functions.emplace_back(func);
      }
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 101: /* expression: expression MINUS expression  */
#line 1002 "yacc_sql.y"
                                  {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression)->expression, (yyvsp[0].expression)->expression, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[0].expression)->aggregations);
      for (const auto &aggr : (yyvsp[-2].expression)->aggregations) {
        (yyval.expression)->aggregations.emplace_back(aggr);
      }
      (yyval.expression)->attributes.swap((yyvsp[0].expression)->attributes);
      for (const auto &rel : (yyvsp[-2].expression)->attributes) {
        (yyval.expression)->attributes.emplace_back(rel);
      }
      (yyval.expression)->functions.swap((yyvsp[0].expression)->functions);
      for (const auto &func : (yyvsp[-2].expression)->functions) {
        (yyval.expression)->functions.emplace_back(func);
      }
    }
#line 2827 "yacc_sql.cpp"
    break;

  case 102: /* expression: expression '*' expression  */
#line 1018 "yacc_sql.y"
                                {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression)->expression, (yyvsp[0].expression)->expression, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[0].expression)->aggregations);
      for (const auto &aggr : (yyvsp[-2].expression)->aggregations) {
        (yyval.expression)->aggregations.emplace_back(aggr);
      }
      (yyval.expression)->attributes.swap((yyvsp[0].expression)->attributes);
      for (const auto &rel : (yyvsp[-2].expression)->attributes) {
        (yyval.expression)->attributes.emplace_back(rel);
      }
      (yyval.expression)->functions.swap((yyvsp[0].expression)->functions);
      for (const auto &func : (yyvsp[-2].expression)->functions) {
        (yyval.expression)->functions.emplace_back(func);
      }
    }
#line 2848 "yacc_sql.cpp"
    break;

  case 103: /* expression: expression '/' expression  */
#line 1034 "yacc_sql.y"
                                {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression)->expression, (yyvsp[0].expression)->expression, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[0].expression)->aggregations);
      for (const auto &aggr : (yyvsp[-2].expression)->aggregations) {
        (yyval.expression)->aggregations.emplace_back(aggr);
      }
      (yyval.expression)->attributes.swap((yyvsp[0].expression)->attributes);
      for (const auto &rel : (yyvsp[-2].expression)->attributes) {
        (yyval.expression)->attributes.emplace_back(rel);
      }
      (yyval.expression)->functions.swap((yyvsp[0].expression)->functions);
      for (const auto &func : (yyvsp[-2].expression)->functions) {
        (yyval.expression)->functions.emplace_back(func);
      }
    }
#line 2869 "yacc_sql.cpp"
    break;

  case 104: /* expression: LBRACE expression RBRACE  */
#line 1050 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      // set sub select aggr index begin from 0
      if ((yyval.expression)->expression->type() == ExprType::SUBSELECT) {
        SubSelectExpr *sub_expr = static_cast<SubSelectExpr *>((yyval.expression)->expression);
        int offset = 0;
        for (int i = 0; i < sub_expr->get_subsqlNode().aggregations.size(); i++) {
          AggregationExpr *aggr_expr = static_cast<AggregationExpr *>(sub_expr->get_subsqlNode().expressions[i].expression);
          if (i == 0) {
            offset = aggr_expr->index();
          }
          aggr_expr->set_index(aggr_expr->index() - offset);
        }
      }
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2890 "yacc_sql.cpp"
    break;

  case 105: /* expression: LBRACE expression set_expression RBRACE  */
#line 1067 "yacc_sql.y"
    {
      (yyvsp[-1].expression_list)->emplace_back(*(yyvsp[-2].expression));
      std::reverse((yyvsp[-1].expression_list)->begin(), (yyvsp[-1].expression_list)->end());
      (yyval.expression) = new ExprSqlNode;
      std::vector<Expression*> set;
      for (int i = 0; i < (yyvsp[-1].expression_list)->size(); i++){
        set.push_back(std::move((yyvsp[-1].expression_list)->at(i).expression));
      }
      (yyval.expression)->expression = new SetExpr(set);
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2906 "yacc_sql.cpp"
    break;

  case 106: /* expression: MINUS expression  */
#line 1078 "yacc_sql.y"
                       {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression)->expression, nullptr, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[0].expression)->aggregations);
      (yyval.expression)->attributes.swap((yyvsp[0].expression)->attributes);
      (yyval.expression)->functions.swap((yyvsp[0].expression)->functions);
    }
#line 2918 "yacc_sql.cpp"
    break;

  case 107: /* expression: expr_value  */
#line 1085 "yacc_sql.y"
                 {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new ValueExpr(*(yyvsp[0].expr_value));
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].expr_value);
    }
#line 2929 "yacc_sql.cpp"
    break;

  case 108: /* expression: rel_attr  */
#line 1091 "yacc_sql.y"
               {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new FieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name);
      if (!(yyvsp[0].rel_attr)->attribute_alias.empty()) {
        (yyval.expression)->expression->set_name((yyvsp[0].rel_attr)->attribute_alias);
      } else {
        (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      }
      (yyval.expression)->attributes.emplace_back(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr);
    }
#line 2945 "yacc_sql.cpp"
    break;

  case 109: /* expression: aggr_attr  */
#line 1102 "yacc_sql.y"
                {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new AggregationExpr((yyvsp[0].aggr_attr)->aggregation_name,(yyvsp[0].aggr_attr)->attribute_name);
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      (yyval.expression)->aggregations.emplace_back(*(yyvsp[0].aggr_attr));
      (yyval.expression)->expression->set_index(aggregation_cnt);
      aggregation_cnt++;
      RelAttrSqlNode *rel_node = new RelAttrSqlNode;
      rel_node->attribute_name = (yyvsp[0].aggr_attr)->attribute_name;
      (yyval.expression)->attributes.push_back(*rel_node);
      delete (yyvsp[0].aggr_attr);
      delete rel_node;
    }
#line 2963 "yacc_sql.cpp"
    break;

  case 110: /* expression: func  */
#line 1115 "yacc_sql.y"
           {
      (yyval.expression) = new ExprSqlNode;
      switch((yyvsp[0].func)->function_type) {
        case FunctionType::LENGTH_T: {
          if ((yyvsp[0].func)->is_attr) {
            (yyval.expression)->expression = new FunctionExpr((yyvsp[0].func)->relation_name, (yyvsp[0].func)->attribute_name, (yyvsp[0].func)->function_type);
            // $$->expression->set_name(token_name(sql_string, &@$));
            (yyval.expression)->functions.emplace_back(*(yyvsp[0].func));
          } else {
            (yyval.expression)->expression = new FunctionExpr((yyvsp[0].func)->value, (yyvsp[0].func)->function_type);
            // $$->expression->set_name(token_name(sql_string, &@$));
            (yyval.expression)->functions.emplace_back(*(yyvsp[0].func));
          }
        } break;
        case FunctionType::ROUND_T: {
          if ((yyvsp[0].func)->is_attr) {
            (yyval.expression)->expression = new FunctionExpr((yyvsp[0].func)->relation_name, (yyvsp[0].func)->attribute_name, (yyvsp[0].func)->function_type, (yyvsp[0].func)->param.get_int());
//$$->expression->set_name(token_name(sql_string, &@$));
            (yyval.expression)->functions.emplace_back(*(yyvsp[0].func));
          } else {
            (yyval.expression)->expression = new FunctionExpr((yyvsp[0].func)->value, (yyvsp[0].func)->function_type, (yyvsp[0].func)->param.get_int());
//$$->expression->set_name(token_name(sql_string, &@$));
            (yyval.expression)->functions.emplace_back(*(yyvsp[0].func));
          }
        } break;
        case FunctionType::DATE_FORMAT_T: {
          if ((yyvsp[0].func)->is_attr) {
            (yyval.expression)->expression = new FunctionExpr((yyvsp[0].func)->relation_name, (yyvsp[0].func)->attribute_name, (yyvsp[0].func)->function_type, (yyvsp[0].func)->param.get_string());
//$$->expression->set_name(token_name(sql_string, &@$));
            (yyval.expression)->functions.emplace_back(*(yyvsp[0].func));
          } else {
            (yyval.expression)->expression = new FunctionExpr((yyvsp[0].func)->value, (yyvsp[0].func)->function_type, (yyvsp[0].func)->param.get_string());
//$$->expression->set_name(token_name(sql_string, &@$));
            (yyval.expression)->functions.emplace_back(*(yyvsp[0].func));
          }
        } break;
        default: {
          return -1;
        } break;
      }
      if (!(yyvsp[0].func)->alias.empty()) {
        (yyval.expression)->expression->set_name((yyvsp[0].func)->alias);
      } else {
        (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      }
      delete (yyvsp[0].func);
    }
#line 3015 "yacc_sql.cpp"
    break;

  case 111: /* expression: select_stmt  */
#line 1163 "yacc_sql.y"
                  {
      (yyval.expression) = new ExprSqlNode;
      ParsedSqlNode * subsql_node = std::move((yyvsp[0].sql_node));
      (yyval.expression)->expression = new SubSelectExpr(subsql_node);   
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3026 "yacc_sql.cpp"
    break;

  case 112: /* rel_attr: ID alias  */
#line 1202 "yacc_sql.y"
             {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.rel_attr)->attribute_alias = (yyvsp[0].alias);
      }
      free((yyvsp[-1].string));
    }
#line 3039 "yacc_sql.cpp"
    break;

  case 113: /* rel_attr: ID DOT '*' alias  */
#line 1210 "yacc_sql.y"
                       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = "*";
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.rel_attr)->attribute_alias = (yyvsp[0].alias);
      }
      free((yyvsp[-3].string));
    }
#line 3053 "yacc_sql.cpp"
    break;

  case 114: /* rel_attr: ID DOT ID alias  */
#line 1219 "yacc_sql.y"
                      {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.rel_attr)->attribute_alias = (yyvsp[0].alias);
      }
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3068 "yacc_sql.cpp"
    break;

  case 115: /* order_attr: ID order_type  */
#line 1232 "yacc_sql.y"
                  {
      (yyval.order_attr) = new OrderBySqlNode;
      (yyval.order_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.order_attr)->order_type = (yyvsp[0].order_type);
      free((yyvsp[-1].string));
    }
#line 3079 "yacc_sql.cpp"
    break;

  case 116: /* order_attr: ID DOT ID order_type  */
#line 1238 "yacc_sql.y"
                           {
      (yyval.order_attr) = new OrderBySqlNode;
      (yyval.order_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.order_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.order_attr)->order_type = (yyvsp[0].order_type);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3092 "yacc_sql.cpp"
    break;

  case 117: /* order_type: %empty  */
#line 1249 "yacc_sql.y"
    {
      (yyval.order_type) = ASC_T;
    }
#line 3100 "yacc_sql.cpp"
    break;

  case 118: /* order_type: ASC  */
#line 1252 "yacc_sql.y"
          { (yyval.order_type) = ASC_T; }
#line 3106 "yacc_sql.cpp"
    break;

  case 119: /* order_type: DESC  */
#line 1253 "yacc_sql.y"
           { (yyval.order_type) = DESC_T; }
#line 3112 "yacc_sql.cpp"
    break;

  case 120: /* aggr_attr: COUNT LBRACE '*' RBRACE alias  */
#line 1256 "yacc_sql.y"
                                  {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = "count";
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = "*";
    }
#line 3125 "yacc_sql.cpp"
    break;

  case 121: /* aggr_attr: COUNT LBRACE ID RBRACE alias  */
#line 1264 "yacc_sql.y"
                                   {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = "count";
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = (yyvsp[-2].string);
    }
#line 3138 "yacc_sql.cpp"
    break;

  case 122: /* aggr_attr: aggr_func LBRACE ID RBRACE alias  */
#line 1272 "yacc_sql.y"
                                       {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = (yyvsp[-4].aggr_func);
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = (yyvsp[-2].string);
    }
#line 3151 "yacc_sql.cpp"
    break;

  case 123: /* aggr_attr: aggr_func LBRACE ID DOT ID RBRACE alias  */
#line 1280 "yacc_sql.y"
                                              {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = (yyvsp[-6].aggr_func);
      (yyval.aggr_attr)->relation_name =(yyvsp[-4].string);
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = (yyvsp[-2].string);
    }
#line 3165 "yacc_sql.cpp"
    break;

  case 124: /* aggr_attr: aggr_func LBRACE '*' RBRACE alias  */
#line 1289 "yacc_sql.y"
                                        {
      if (0 != strcmp((yyvsp[-4].aggr_func), "count")) {
        return -1;
      }
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = "count";
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = "*";
    }
#line 3181 "yacc_sql.cpp"
    break;

  case 125: /* aggr_attr: aggr_func LBRACE RBRACE  */
#line 1300 "yacc_sql.y"
                              {
      return -1;
    }
#line 3189 "yacc_sql.cpp"
    break;

  case 126: /* aggr_attr: aggr_func LBRACE error RBRACE  */
#line 1303 "yacc_sql.y"
                                    {
      return -1;
    }
#line 3197 "yacc_sql.cpp"
    break;

  case 127: /* aggr_func: COUNT  */
#line 1309 "yacc_sql.y"
          {
      (yyval.aggr_func) = "count";
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 128: /* aggr_func: MIN  */
#line 1312 "yacc_sql.y"
          {
      (yyval.aggr_func) = "min";
    }
#line 3213 "yacc_sql.cpp"
    break;

  case 129: /* aggr_func: MAX  */
#line 1315 "yacc_sql.y"
          {
      (yyval.aggr_func) = "max";
    }
#line 3221 "yacc_sql.cpp"
    break;

  case 130: /* aggr_func: SUM  */
#line 1318 "yacc_sql.y"
          {
      (yyval.aggr_func) = "sum";
    }
#line 3229 "yacc_sql.cpp"
    break;

  case 131: /* aggr_func: AVG  */
#line 1321 "yacc_sql.y"
          {
      (yyval.aggr_func) = "avg";
    }
#line 3237 "yacc_sql.cpp"
    break;

  case 132: /* aggr_func: ID  */
#line 1324 "yacc_sql.y"
         {
      if (0 == strcmp((yyvsp[0].string), "sum")) {
        (yyval.aggr_func) = "sum";
      } else if (0 == strcmp((yyvsp[0].string), "min")) {
        (yyval.aggr_func) = "min";
      } else if (0 == strcmp((yyvsp[0].string), "max")) {
        (yyval.aggr_func) = "max";
      } else if (0 == strcmp((yyvsp[0].string), "avg")) {
        (yyval.aggr_func) = "avg";
      } else if (0 == strcmp((yyvsp[0].string), "count")) {
        (yyval.aggr_func) = "count";
      }
      else {
        return -1;
      }
    }
#line 3258 "yacc_sql.cpp"
    break;

  case 133: /* func: LENGTH LBRACE ID RBRACE alias  */
#line 1342 "yacc_sql.y"
                                  {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::LENGTH_T;
      (yyval.func)->attribute_name = (yyvsp[-2].string);
      (yyval.func)->is_attr = true;
      free((yyvsp[-2].string));
    }
#line 3273 "yacc_sql.cpp"
    break;

  case 134: /* func: LENGTH LBRACE ID DOT ID RBRACE alias  */
#line 1352 "yacc_sql.y"
                                           {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::LENGTH_T;
      (yyval.func)->relation_name = (yyvsp[-4].string);
      (yyval.func)->attribute_name = (yyvsp[-2].string);
      (yyval.func)->is_attr = true;
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 3290 "yacc_sql.cpp"
    break;

  case 135: /* func: LENGTH LBRACE value RBRACE alias  */
#line 1364 "yacc_sql.y"
                                       {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::LENGTH_T;
      (yyval.func)->value = *(yyvsp[-2].value);
      (yyval.func)->is_attr = false;
      delete (yyvsp[-2].value);
    }
#line 3305 "yacc_sql.cpp"
    break;

  case 136: /* func: ROUND LBRACE ID RBRACE alias  */
#line 1374 "yacc_sql.y"
                                   {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::ROUND_T;
      (yyval.func)->attribute_name = (yyvsp[-2].string);
      (yyval.func)->param = Value(0);
      free((yyvsp[-2].string));
      (yyval.func)->is_attr = true;
    }
#line 3321 "yacc_sql.cpp"
    break;

  case 137: /* func: ROUND LBRACE ID DOT ID RBRACE alias  */
#line 1385 "yacc_sql.y"
                                          {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::ROUND_T;
      (yyval.func)->relation_name = (yyvsp[-4].string);
      (yyval.func)->attribute_name = (yyvsp[-2].string);
      (yyval.func)->is_attr = true;
      (yyval.func)->param = Value(0);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 3339 "yacc_sql.cpp"
    break;

  case 138: /* func: ROUND LBRACE value RBRACE alias  */
#line 1398 "yacc_sql.y"
                                      {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::ROUND_T;
      (yyval.func)->value = *(yyvsp[-2].value);
      (yyval.func)->is_attr = false;
      (yyval.func)->param = Value(0);
      delete (yyvsp[-2].value);
    }
#line 3355 "yacc_sql.cpp"
    break;

  case 139: /* func: ROUND LBRACE ID COMMA value RBRACE alias  */
#line 1409 "yacc_sql.y"
                                               {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::ROUND_T;
      (yyval.func)->attribute_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));
      (yyval.func)->param = *(yyvsp[-2].value);
      (yyval.func)->is_attr = true;
      delete (yyvsp[-2].value);
    }
#line 3372 "yacc_sql.cpp"
    break;

  case 140: /* func: ROUND LBRACE ID DOT ID COMMA value RBRACE alias  */
#line 1421 "yacc_sql.y"
                                                      {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::ROUND_T;
      (yyval.func)->relation_name = (yyvsp[-6].string);
      (yyval.func)->attribute_name = (yyvsp[-4].string);
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      (yyval.func)->param = *(yyvsp[-2].value);
      (yyval.func)->is_attr = true;
      delete (yyvsp[-2].value);
    }
#line 3391 "yacc_sql.cpp"
    break;

  case 141: /* func: ROUND LBRACE value COMMA value RBRACE alias  */
#line 1435 "yacc_sql.y"
                                                  {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::ROUND_T;
      (yyval.func)->value = *(yyvsp[-4].value);
      delete (yyvsp[-4].value);
      (yyval.func)->param = *(yyvsp[-2].value);
      (yyval.func)->is_attr = false;
      delete (yyvsp[-2].value);
    }
#line 3408 "yacc_sql.cpp"
    break;

  case 142: /* func: DATE_FORMAT LBRACE ID COMMA value RBRACE alias  */
#line 1447 "yacc_sql.y"
                                                     {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::DATE_FORMAT_T;
      (yyval.func)->attribute_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));
      (yyval.func)->param = *(yyvsp[-2].value);
      (yyval.func)->is_attr = true;
      delete (yyvsp[-2].value);
    }
#line 3425 "yacc_sql.cpp"
    break;

  case 143: /* func: DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE alias  */
#line 1459 "yacc_sql.y"
                                                            {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::DATE_FORMAT_T;
      (yyval.func)->relation_name = (yyvsp[-6].string);
      (yyval.func)->attribute_name = (yyvsp[-4].string);
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      (yyval.func)->param = *(yyvsp[-2].value);
      (yyval.func)->is_attr = true;
      delete (yyvsp[-2].value);
    }
#line 3444 "yacc_sql.cpp"
    break;

  case 144: /* func: DATE_FORMAT LBRACE value COMMA value RBRACE alias  */
#line 1473 "yacc_sql.y"
                                                        {
      (yyval.func) = new FuncSqlNode;
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.func)->alias = (yyvsp[0].alias);
      }
      (yyval.func)->function_type = FunctionType::DATE_FORMAT_T;
      (yyval.func)->value = *(yyvsp[-4].value);
      delete (yyvsp[-4].value);
      (yyval.func)->param = *(yyvsp[-2].value);
      (yyval.func)->is_attr = false;
      delete (yyvsp[-2].value);
    }
#line 3461 "yacc_sql.cpp"
    break;

  case 145: /* alias: %empty  */
#line 1488 "yacc_sql.y"
    {
      (yyval.alias) = nullptr;
    }
#line 3469 "yacc_sql.cpp"
    break;

  case 146: /* alias: ID  */
#line 1491 "yacc_sql.y"
         {
      if (0 == strcmp((yyvsp[0].string), "alias")) {
        return -1;
      }
      (yyval.alias) = (yyvsp[0].string);
    }
#line 3480 "yacc_sql.cpp"
    break;

  case 147: /* alias: AS ID  */
#line 1497 "yacc_sql.y"
            {
      if (0 == strcmp((yyvsp[0].string), "alias")) {
        return -1;
      }
      (yyval.alias) = (yyvsp[0].string);
    }
#line 3491 "yacc_sql.cpp"
    break;

  case 148: /* rel_list: %empty  */
#line 1539 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3499 "yacc_sql.cpp"
    break;

  case 149: /* rel_list: COMMA ID alias rel_list  */
#line 1542 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelSqlNode>;
      }

      RelSqlNode *rel_node = new RelSqlNode;
      rel_node->relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      if ((yyvsp[-1].alias) != nullptr) {
        rel_node->alias = (yyvsp[-1].alias);
      }
      (yyval.relation_list)->push_back(*rel_node);
    }
#line 3519 "yacc_sql.cpp"
    break;

  case 150: /* innerJoin_list: %empty  */
#line 1560 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3527 "yacc_sql.cpp"
    break;

  case 151: /* innerJoin_list: inner_join innerJoin_list  */
#line 1563 "yacc_sql.y"
                              {
      if ((yyvsp[0].inner_join_list) == nullptr)
        (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      else
        (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_join));
      delete (yyvsp[-1].inner_join);
    }
#line 3540 "yacc_sql.cpp"
    break;

  case 152: /* inner_join: INNER JOIN ID ON condition_list  */
#line 1572 "yacc_sql.y"
                                    {
      (yyval.inner_join) = new InnerJoinSqlNode;
      (yyval.inner_join)->relation = (yyvsp[-2].string);
      delete (yyvsp[-2].string);
      (yyval.inner_join)->conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3552 "yacc_sql.cpp"
    break;

  case 153: /* where: %empty  */
#line 1581 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3560 "yacc_sql.cpp"
    break;

  case 154: /* where: WHERE condition_list  */
#line 1584 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3568 "yacc_sql.cpp"
    break;

  case 155: /* condition_list: %empty  */
#line 1590 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3576 "yacc_sql.cpp"
    break;

  case 156: /* condition_list: condition  */
#line 1593 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3586 "yacc_sql.cpp"
    break;

  case 157: /* condition_list: condition AND condition_list  */
#line 1598 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3596 "yacc_sql.cpp"
    break;

  case 158: /* condition: expression comp_op expression  */
#line 1606 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expr_node = *(yyvsp[-2].expression);
      // left
      switch ((yyvsp[-2].expression)->expression->type()) {
        case ExprType::FIELD: {
          (yyval.condition)->left_con_type = ConditionType::CON_ATTR_T;
        } break;
        case ExprType::VALUE: {
          (yyval.condition)->left_con_type = ConditionType::CON_VALUE_T;
        } break;
        case ExprType::ARITHMETIC: {
          (yyval.condition)->left_con_type = ConditionType::CON_CALC_T;
        } break;
        case ExprType::AGGREGATION: {
          (yyval.condition)->left_con_type = ConditionType::CON_AGGR_T;
        } break;
        case ExprType::FUNCTION: {
          (yyval.condition)->left_con_type = ConditionType::CON_FUNC_T;
        } break;
        case ExprType::SUBSELECT: {
          (yyval.condition)->left_con_type = ConditionType::CON_SUBSELECT_T;
        } break;
        case ExprType::SET: {
          (yyval.condition)->left_con_type = ConditionType::CON_SET_T;
        } break;
        default: {
          return -1;
        } break;
      }
      // right
      (yyval.condition)->right_expr_node = *(yyvsp[0].expression);
      switch ((yyvsp[0].expression)->expression->type()) {
        case ExprType::FIELD: {
          (yyval.condition)->right_con_type = ConditionType::CON_ATTR_T;
        } break;
        case ExprType::VALUE: {
          (yyval.condition)->right_con_type = ConditionType::CON_VALUE_T;
        } break;
        case ExprType::ARITHMETIC: {
          (yyval.condition)->right_con_type = ConditionType::CON_CALC_T;
        } break;
        case ExprType::AGGREGATION: {
          (yyval.condition)->right_con_type = ConditionType::CON_AGGR_T;
        } break;
        case ExprType::FUNCTION: {
          (yyval.condition)->right_con_type = ConditionType::CON_FUNC_T;
        } break;
        case ExprType::SUBSELECT: {
          (yyval.condition)->right_con_type = ConditionType::CON_SUBSELECT_T;
        } break;
        case ExprType::SET: {
          (yyval.condition)->right_con_type = ConditionType::CON_SET_T;
        } break;
        default: {
          return -1;
        } break;
      }
    }
#line 3661 "yacc_sql.cpp"
    break;

  case 159: /* condition: EXISTS expression  */
#line 1667 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->comp = CompOp::EXISTS_OP;
      ExprSqlNode * left = new ExprSqlNode;
      left->expression = new ValueExpr(Value(1));
      left->expression->set_name("1");
      (yyval.condition)->left_expr_node = *left;
      (yyval.condition)->left_con_type = CON_VALUE_T;
      (yyval.condition)->right_expr_node = *(yyvsp[0].expression);
      if ((yyvsp[0].expression)->expression->type() == ExprType::SUBSELECT)
      {
        (yyval.condition)->right_con_type = CON_SUBSELECT_T;
      }
      else
        return -1; /// exists 目前只考虑后面是子查询语句的情况
    }
#line 3682 "yacc_sql.cpp"
    break;

  case 160: /* condition: NOT EXISTS expression  */
#line 1684 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->comp = CompOp::NOT_EXISTS_OP;
      ExprSqlNode * left = new ExprSqlNode;
      left->expression = new ValueExpr(Value(1));
      left->expression->set_name("1");
      (yyval.condition)->left_expr_node = *left;
      (yyval.condition)->left_con_type = CON_VALUE_T;
      (yyval.condition)->right_expr_node = *(yyvsp[0].expression);
      if ((yyvsp[0].expression)->expression->type() == ExprType::SUBSELECT)
      {
        (yyval.condition)->right_con_type = CON_SUBSELECT_T;
      }
      else
        return -1; /// exists 目前只考虑后面是子查询语句的情况
    }
#line 3703 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: EQ  */
#line 1751 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3709 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: LT  */
#line 1752 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3715 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: GT  */
#line 1753 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3721 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: LE  */
#line 1754 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3727 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: GE  */
#line 1755 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3733 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: NE  */
#line 1756 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3739 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: LIKE  */
#line 1757 "yacc_sql.y"
           {(yyval.comp) = LIKE_OP;}
#line 3745 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: NOT LIKE  */
#line 1758 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP;}
#line 3751 "yacc_sql.cpp"
    break;

  case 169: /* comp_op: IS  */
#line 1759 "yacc_sql.y"
         { (yyval.comp) = IS_OP;}
#line 3757 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: IS NOT  */
#line 1760 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_OP;}
#line 3763 "yacc_sql.cpp"
    break;

  case 171: /* comp_op: IN  */
#line 1761 "yacc_sql.y"
         {(yyval.comp) = IN_OP;}
#line 3769 "yacc_sql.cpp"
    break;

  case 172: /* comp_op: NOT IN  */
#line 1762 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP;}
#line 3775 "yacc_sql.cpp"
    break;

  case 173: /* load_data_stmt: %empty  */
#line 1766 "yacc_sql.y"
{}
#line 3781 "yacc_sql.cpp"
    break;

  case 174: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1781 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3790 "yacc_sql.cpp"
    break;

  case 175: /* set_variable_stmt: SET ID EQ value  */
#line 1789 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3802 "yacc_sql.cpp"
    break;


#line 3806 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1801 "yacc_sql.y"

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
