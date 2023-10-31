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
  YYSYMBOL_LBRACE = 19,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 20,                    /* RBRACE  */
  YYSYMBOL_COMMA = 21,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 22,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 23,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 24,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 25,                     /* INT_T  */
  YYSYMBOL_STRING_T = 26,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 27,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 28,                    /* DATE_T  */
  YYSYMBOL_NULL_T = 29,                    /* NULL_T  */
  YYSYMBOL_HELP = 30,                      /* HELP  */
  YYSYMBOL_EXIT = 31,                      /* EXIT  */
  YYSYMBOL_DOT = 32,                       /* DOT  */
  YYSYMBOL_INTO = 33,                      /* INTO  */
  YYSYMBOL_VALUES = 34,                    /* VALUES  */
  YYSYMBOL_FROM = 35,                      /* FROM  */
  YYSYMBOL_WHERE = 36,                     /* WHERE  */
  YYSYMBOL_AND = 37,                       /* AND  */
  YYSYMBOL_SET = 38,                       /* SET  */
  YYSYMBOL_ON = 39,                        /* ON  */
  YYSYMBOL_LOAD = 40,                      /* LOAD  */
  YYSYMBOL_DATA = 41,                      /* DATA  */
  YYSYMBOL_INFILE = 42,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 43,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 44,                        /* EQ  */
  YYSYMBOL_LT = 45,                        /* LT  */
  YYSYMBOL_GT = 46,                        /* GT  */
  YYSYMBOL_LE = 47,                        /* LE  */
  YYSYMBOL_GE = 48,                        /* GE  */
  YYSYMBOL_NE = 49,                        /* NE  */
  YYSYMBOL_LIKE = 50,                      /* LIKE  */
  YYSYMBOL_IS = 51,                        /* IS  */
  YYSYMBOL_NOT = 52,                       /* NOT  */
  YYSYMBOL_UNIQUE = 53,                    /* UNIQUE  */
  YYSYMBOL_ORDER = 54,                     /* ORDER  */
  YYSYMBOL_GROUP = 55,                     /* GROUP  */
  YYSYMBOL_BY = 56,                        /* BY  */
  YYSYMBOL_HAVING = 57,                    /* HAVING  */
  YYSYMBOL_ASC = 58,                       /* ASC  */
  YYSYMBOL_MINUS = 59,                     /* MINUS  */
  YYSYMBOL_LENGTH = 60,                    /* LENGTH  */
  YYSYMBOL_ROUND = 61,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 62,               /* DATE_FORMAT  */
  YYSYMBOL_AS = 63,                        /* AS  */
  YYSYMBOL_IN = 64,                        /* IN  */
  YYSYMBOL_EXISTS = 65,                    /* EXISTS  */
  YYSYMBOL_COUNT = 66,                     /* COUNT  */
  YYSYMBOL_MIN = 67,                       /* MIN  */
  YYSYMBOL_MAX = 68,                       /* MAX  */
  YYSYMBOL_SUM = 69,                       /* SUM  */
  YYSYMBOL_AVG = 70,                       /* AVG  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_DATE = 72,                      /* DATE  */
  YYSYMBOL_FLOAT = 73,                     /* FLOAT  */
  YYSYMBOL_ID = 74,                        /* ID  */
  YYSYMBOL_SSS = 75,                       /* SSS  */
  YYSYMBOL_76_ = 76,                       /* '+'  */
  YYSYMBOL_77_ = 77,                       /* '*'  */
  YYSYMBOL_78_ = 78,                       /* '/'  */
  YYSYMBOL_UMINUS = 79,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_commands = 81,                  /* commands  */
  YYSYMBOL_command_wrapper = 82,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 83,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 84,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 85,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 86,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 87,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 88,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 89,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 90,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 91,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 92,         /* create_index_stmt  */
  YYSYMBOL_index_list = 93,                /* index_list  */
  YYSYMBOL_drop_index_stmt = 94,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 95,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 96,             /* attr_def_list  */
  YYSYMBOL_attr_def = 97,                  /* attr_def  */
  YYSYMBOL_nullable = 98,                  /* nullable  */
  YYSYMBOL_number = 99,                    /* number  */
  YYSYMBOL_type = 100,                     /* type  */
  YYSYMBOL_insert_stmt = 101,              /* insert_stmt  */
  YYSYMBOL_value_lists = 102,              /* value_lists  */
  YYSYMBOL_value_list = 103,               /* value_list  */
  YYSYMBOL_value = 104,                    /* value  */
  YYSYMBOL_expr_value = 105,               /* expr_value  */
  YYSYMBOL_delete_stmt = 106,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 107,              /* update_stmt  */
  YYSYMBOL_update_field_list = 108,        /* update_field_list  */
  YYSYMBOL_update_field = 109,             /* update_field  */
  YYSYMBOL_select_stmt = 110,              /* select_stmt  */
  YYSYMBOL_group_by = 111,                 /* group_by  */
  YYSYMBOL_having = 112,                   /* having  */
  YYSYMBOL_order_by = 113,                 /* order_by  */
  YYSYMBOL_order_by_list = 114,            /* order_by_list  */
  YYSYMBOL_calc_stmt = 115,                /* calc_stmt  */
  YYSYMBOL_expression_list = 116,          /* expression_list  */
  YYSYMBOL_set_expression = 117,           /* set_expression  */
  YYSYMBOL_expression = 118,               /* expression  */
  YYSYMBOL_rel_attr = 119,                 /* rel_attr  */
  YYSYMBOL_order_attr = 120,               /* order_attr  */
  YYSYMBOL_order_type = 121,               /* order_type  */
  YYSYMBOL_aggr_attr = 122,                /* aggr_attr  */
  YYSYMBOL_aggr_func = 123,                /* aggr_func  */
  YYSYMBOL_func = 124,                     /* func  */
  YYSYMBOL_alias = 125,                    /* alias  */
  YYSYMBOL_rel_list = 126,                 /* rel_list  */
  YYSYMBOL_innerJoin_list = 127,           /* innerJoin_list  */
  YYSYMBOL_inner_join = 128,               /* inner_join  */
  YYSYMBOL_where = 129,                    /* where  */
  YYSYMBOL_condition_list = 130,           /* condition_list  */
  YYSYMBOL_condition = 131,                /* condition  */
  YYSYMBOL_comp_op = 132,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 133,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 134,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 135,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 136             /* opt_semicolon  */
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
#define YYFINAL  81
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   412

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  172
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  343

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


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
       2,     2,    77,    76,     2,     2,     2,    78,     2,     2,
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
      75,    79
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   244,   244,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   275,   281,   286,   292,   298,   304,   310,
     317,   323,   342,   356,   373,   379,   388,   398,   414,   423,
     432,   441,   453,   456,   469,   478,   490,   493,   497,   503,
     506,   507,   508,   509,   512,   522,   528,   536,   542,   549,
     553,   557,   561,   565,   570,   579,   584,   588,   592,   597,
     606,   612,   624,   638,   644,   651,   661,   728,   799,   831,
     837,   840,   847,   850,   857,   860,   867,   870,   875,   886,
     897,   910,   915,   926,   931,   941,   958,   974,   990,  1006,
    1022,  1034,  1041,  1047,  1059,  1072,  1120,  1159,  1167,  1176,
    1189,  1195,  1206,  1209,  1210,  1213,  1221,  1229,  1237,  1246,
    1257,  1260,  1266,  1269,  1272,  1275,  1278,  1281,  1299,  1309,
    1321,  1331,  1342,  1355,  1366,  1378,  1392,  1404,  1416,  1430,
    1445,  1448,  1454,  1496,  1499,  1517,  1520,  1529,  1538,  1541,
    1547,  1550,  1555,  1562,  1623,  1640,  1708,  1709,  1710,  1711,
    1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,  1723,  1736,
    1744,  1754,  1755
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
  "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "NULL_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN",
  "EQ", "LT", "GT", "LE", "GE", "NE", "LIKE", "IS", "NOT", "UNIQUE",
  "ORDER", "GROUP", "BY", "HAVING", "ASC", "MINUS", "LENGTH", "ROUND",
  "DATE_FORMAT", "AS", "IN", "EXISTS", "COUNT", "MIN", "MAX", "SUM", "AVG",
  "NUMBER", "DATE", "FLOAT", "ID", "SSS", "'+'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "index_list", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "nullable", "number",
  "type", "insert_stmt", "value_lists", "value_list", "value",
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

#define YYPACT_NINF (-244)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-128)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     333,     9,   100,   162,    93,   -26,    54,  -244,    51,    52,
      24,  -244,  -244,  -244,  -244,  -244,    31,    61,   333,   110,
     115,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,    39,    47,   125,    50,    66,   261,  -244,   261,   126,
     132,   139,   150,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
       4,  -244,   -32,  -244,  -244,  -244,   -12,  -244,  -244,   157,
    -244,   147,   151,  -244,  -244,   129,   131,   152,   165,   173,
    -244,  -244,  -244,  -244,    11,   186,   138,  -244,   187,    -8,
     -37,    64,   145,   237,   -22,   -21,   153,  -244,  -244,  -244,
     162,   261,   261,   261,   261,    23,   164,   166,   207,   208,
     169,    75,   171,   175,   235,  -244,   176,   213,   180,  -244,
     261,   227,  -244,    28,  -244,  -244,  -244,    13,  -244,   233,
       7,    60,    14,   234,   236,   238,   -32,   -32,  -244,  -244,
     -37,   -37,  -244,  -244,   242,  -244,    18,   243,   244,   -32,
     245,   232,  -244,   223,    -7,  -244,  -244,   239,   170,   247,
    -244,   250,   196,  -244,    -5,  -244,  -244,  -244,   -32,   199,
     -32,   -32,    75,   200,   -32,    75,    75,   201,    75,   -32,
     -32,  -244,  -244,  -244,   -32,   202,   -32,   203,   208,   244,
      75,   258,   216,   261,   334,  -244,   246,   112,   169,  -244,
     276,  -244,  -244,  -244,  -244,    90,   175,   265,   212,   269,
    -244,  -244,   275,  -244,  -244,   293,   108,  -244,   294,   295,
     296,   298,  -244,  -244,  -244,   299,  -244,   -32,  -244,   305,
     123,  -244,   306,   261,   116,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,   272,   -30,  -244,   261,   232,   235,  -244,  -244,
     266,   268,  -244,   312,  -244,   247,    12,  -244,   136,   212,
     -32,   -32,   -32,    75,   -32,   -32,    75,   -32,   -32,   244,
     332,   208,   305,  -244,    75,    75,   116,  -244,  -244,  -244,
     116,  -244,   325,  -244,  -244,   338,  -244,  -244,   235,  -244,
    -244,   278,   158,  -244,  -244,  -244,   339,  -244,  -244,   340,
    -244,  -244,  -244,   279,   300,  -244,  -244,   179,  -244,    -3,
    -244,  -244,  -244,   -32,   -32,   322,   309,   307,  -244,  -244,
    -244,  -244,   232,   292,   311,   313,  -244,     5,  -244,   347,
     162,   232,  -244,  -244,   301,  -244,  -244,   292,  -244,  -244,
      19,  -244,  -244
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     171,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,   123,   124,   125,   126,    66,    69,    67,
     140,    68,   140,   102,   106,    89,    91,   103,   104,     0,
     105,     0,    78,    31,    30,     0,     0,     0,     0,     0,
     169,     1,   172,     2,     0,     0,     0,    29,     0,     0,
     101,     0,     0,     0,     0,     0,     0,   141,   107,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   148,
       0,     0,     0,     0,     0,    39,     0,     0,     0,    99,
       0,     0,    65,     0,    59,    64,    61,     0,    63,     0,
       0,     0,     0,     0,     0,     0,   140,   140,   142,    92,
      96,    95,    97,    98,     0,   120,     0,     0,   143,   140,
       0,   150,    71,     0,   148,    73,   170,     0,     0,    42,
      38,     0,     0,    36,    93,   100,    60,    62,   140,     0,
     140,   140,     0,     0,   140,     0,     0,     0,     0,   140,
     140,   109,   108,   121,   140,     0,   140,     0,   148,   143,
       0,    54,     0,     0,     0,   149,   151,     0,     0,    72,
       0,    50,    51,    52,    53,    46,     0,     0,     0,     0,
      94,   128,     0,   130,   131,     0,     0,   133,     0,     0,
       0,     0,   116,   115,   117,     0,   119,   140,    79,   145,
       0,    57,     0,     0,   154,   156,   157,   158,   159,   160,
     161,   162,   164,     0,   166,     0,   150,     0,    75,    74,
       0,     0,    47,     0,    45,    42,    37,    34,     0,     0,
     140,   140,   140,     0,   140,   140,     0,   140,   140,   143,
       0,   148,   145,    55,     0,     0,   155,   165,   163,   167,
     153,   152,     0,   168,    49,     0,    48,    43,     0,    41,
      32,     0,     0,   129,   134,   132,     0,   136,   137,     0,
     139,   118,   144,     0,    84,   146,    58,     0,    76,    46,
      40,    35,    33,   140,   140,     0,     0,    80,    56,    44,
     135,   138,   150,    86,     0,    82,   147,   112,    85,    87,
       0,   150,    77,   114,     0,   113,   110,    86,    81,    83,
     112,    88,   111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -244,  -244,   351,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,   113,  -244,  -244,   119,   181,    68,  -244,
    -244,  -244,  -244,   114,   -86,  -244,  -244,  -244,  -244,   190,
       1,  -244,  -244,  -244,    53,  -244,    -4,   228,   -44,  -244,
    -244,    55,  -244,  -244,  -244,   -54,  -178,   122,  -244,  -144,
    -243,  -244,  -244,  -244,  -244,  -244,  -244
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   258,    31,    32,   207,   159,   254,   285,
     205,    33,   191,   230,   231,    63,    34,    35,   154,   155,
      64,   325,   332,   317,   328,    37,    65,   121,    66,    67,
     329,   336,    68,    69,    70,    98,   188,   271,   272,   152,
     195,   196,   245,    38,    39,    40,    83
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    36,    89,   281,    90,   129,   131,   133,    99,   100,
     199,   229,   119,   120,   198,    41,   120,    42,   333,    36,
     278,     4,     4,  -127,   144,   156,   252,   171,   172,   151,
     113,    96,   333,   168,   279,   176,    95,   334,   184,   173,
     103,   104,    97,   145,   228,   169,   177,   101,    73,   253,
     185,   101,   134,   136,   101,   135,   137,   140,   141,   142,
     143,    74,    43,   335,   102,   103,   104,    96,   102,   103,
     104,   102,   103,   104,   114,   288,   164,   335,    97,   326,
     174,   175,   181,   182,    75,   115,   215,    76,   339,   218,
     219,   302,   221,   122,    71,   189,   139,   146,    77,   166,
     147,   167,    79,     4,   122,    78,    44,   194,    45,   251,
      81,   248,    46,    84,   211,   160,   213,   214,    82,   252,
     217,    85,    47,   123,    87,   222,   223,   304,   262,   263,
     224,   247,   226,    86,   123,   124,   125,   126,   127,   128,
      88,   122,   253,   273,   274,    91,   124,   125,   126,   234,
     128,    92,    48,    49,    50,    51,   290,   291,    93,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    94,
      62,   123,     4,   269,   122,   101,   105,   296,   312,   291,
     299,    46,   106,   124,   125,   126,   107,   128,   306,   276,
     110,    47,   102,   103,   104,   201,   202,   203,   204,   318,
     274,   280,   194,   108,   123,   109,   293,   294,   295,   111,
     297,   298,   117,   300,   301,   112,   124,   125,   126,   130,
     128,    48,    49,    50,    51,   116,   118,   138,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,   148,    62,
     149,   150,     4,   153,   151,     4,   157,   165,   282,   158,
     161,    46,   162,   170,   163,   178,   179,   289,   180,   320,
     321,    47,   183,   186,   190,   187,   122,   197,   206,   208,
     209,     4,   200,   212,   216,   220,   225,   227,   194,   232,
      46,   233,   250,   246,   192,   256,   257,   194,   259,   310,
      47,    48,    49,    50,    51,   260,   123,   193,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,   124,   125,
     126,   132,   128,   261,   264,   265,   270,   266,   267,   268,
      48,    49,    50,    51,   277,   275,   338,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,     1,     2,   284,
     283,   286,     3,     4,   303,   308,     5,     6,     7,     8,
       9,    10,   311,   315,   316,    11,    12,    13,   309,   313,
     314,   322,   324,    14,    15,   323,   327,   330,   337,    80,
     331,    16,   292,    17,   287,   340,    18,   319,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   255,   249,   307,
     341,     0,   210,   101,   305,   342,     0,     0,   244,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     102,   103,   104
};

static const yytype_int16 yycheck[] =
{
       4,     0,    46,   246,    48,    91,    92,    93,    62,    21,
     154,   189,    20,    21,    21,     6,    21,     8,    13,    18,
      50,    10,    10,    19,     1,   111,    29,    20,    21,    36,
      19,    63,    13,    20,    64,    21,    32,    32,    20,    32,
      77,    78,    74,    20,   188,    32,    32,    59,    74,    52,
      32,    59,    74,    74,    59,    77,    77,   101,   102,   103,
     104,     7,    53,    58,    76,    77,    78,    63,    76,    77,
      78,    76,    77,    78,    63,    63,   120,    58,    74,   322,
      20,    21,   136,   137,    33,    84,   172,    35,   331,   175,
     176,   269,   178,    29,     1,   149,   100,    74,    74,    71,
      77,    73,    41,    10,    29,    74,     6,   151,     8,    19,
       0,   197,    19,    74,   168,   114,   170,   171,     3,    29,
     174,    74,    29,    59,    74,   179,   180,   271,    20,    21,
     184,    19,   186,     8,    59,    71,    72,    73,    74,    75,
      74,    29,    52,    20,    21,    19,    71,    72,    73,   193,
      75,    19,    59,    60,    61,    62,    20,    21,    19,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    19,
      77,    59,    10,   227,    29,    59,    19,   263,    20,    21,
     266,    19,    35,    71,    72,    73,    35,    75,   274,   233,
      38,    29,    76,    77,    78,    25,    26,    27,    28,    20,
      21,   245,   246,    74,    59,    74,   260,   261,   262,    44,
     264,   265,    74,   267,   268,    42,    71,    72,    73,    74,
      75,    59,    60,    61,    62,    39,    39,    74,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    74,    77,
      74,    34,    10,    74,    36,    10,    75,    20,   247,    74,
      74,    19,    39,    20,    74,    21,    20,   256,    20,   313,
     314,    29,    20,    20,    19,    21,    29,    44,    21,    19,
      74,    10,    33,    74,    74,    74,    74,    74,   322,    21,
      19,    65,     6,    37,    52,    20,    74,   331,    19,   288,
      29,    59,    60,    61,    62,    20,    59,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    71,    72,
      73,    74,    75,    20,    20,    20,    11,    21,    20,    20,
      59,    60,    61,    62,    52,    19,   330,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,     4,     5,    71,
      74,    29,     9,    10,    12,    20,    13,    14,    15,    16,
      17,    18,    74,    74,    54,    22,    23,    24,    20,    20,
      20,    39,    55,    30,    31,    56,    74,    56,    21,    18,
      57,    38,   259,    40,   255,    74,    43,   309,    44,    45,
      46,    47,    48,    49,    50,    51,    52,   206,   198,   275,
     337,    -1,   164,    59,   272,   340,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    13,    14,    15,    16,    17,
      18,    22,    23,    24,    30,    31,    38,    40,    43,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    94,    95,   101,   106,   107,   110,   115,   133,   134,
     135,     6,     8,    53,     6,     8,    19,    29,    59,    60,
      61,    62,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    77,   105,   110,   116,   118,   119,   122,   123,
     124,     1,   116,    74,     7,    33,    35,    74,    74,    41,
      82,     0,     3,   136,    74,    74,     8,    74,    74,   118,
     118,    19,    19,    19,    19,    32,    63,    74,   125,   125,
      21,    59,    76,    77,    78,    19,    35,    35,    74,    74,
      38,    44,    42,    19,    63,   110,    39,    74,    39,    20,
      21,   117,    29,    59,    71,    72,    73,    74,    75,   104,
      74,   104,    74,   104,    74,    77,    74,    77,    74,   116,
     118,   118,   118,   118,     1,    20,    74,    77,    74,    74,
      34,    36,   129,    74,   108,   109,   104,    75,    74,    97,
     110,    74,    39,    74,   118,    20,    71,    73,    20,    32,
      20,    20,    21,    32,    20,    21,    21,    32,    21,    20,
      20,   125,   125,    20,    20,    32,    20,    21,   126,   125,
      19,   102,    52,    65,   118,   130,   131,    44,    21,   129,
      33,    25,    26,    27,    28,   100,    21,    96,    19,    74,
     117,   125,    74,   125,   125,   104,    74,   125,   104,   104,
      74,   104,   125,   125,   125,    74,   125,    74,   129,   126,
     103,   104,    21,    65,   118,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    64,   132,    37,    19,   104,   109,
       6,    19,    29,    52,    98,    97,    20,    74,    93,    19,
      20,    20,    20,    21,    20,    20,    21,    20,    20,   125,
      11,   127,   128,    20,    21,    19,   118,    52,    50,    64,
     118,   130,   110,    74,    71,    99,    29,    96,    63,   110,
      20,    21,    93,   125,   125,   125,   104,   125,   125,   104,
     125,   125,   126,    12,   129,   127,   104,   103,    20,    20,
     110,    74,    20,    20,    20,    74,    54,   113,    20,    98,
     125,   125,    39,    56,    55,   111,   130,    74,   114,   120,
      56,    57,   112,    13,    32,    58,   121,    21,   116,   130,
      74,   114,   121
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    92,    93,    93,    94,    95,    95,    95,
      95,    95,    96,    96,    97,    97,    98,    98,    98,    99,
     100,   100,   100,   100,   101,   102,   102,   103,   103,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   105,   105,
     105,   106,   107,   108,   108,   109,   109,   110,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   114,   114,   115,
     116,   116,   116,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   119,   119,   119,
     120,   120,   121,   121,   121,   122,   122,   122,   122,   122,
     122,   122,   123,   123,   123,   123,   123,   123,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   125,   125,   126,   126,   127,   127,   128,   129,   129,
     130,   130,   130,   131,   131,   131,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   133,   134,
     135,   136,   136
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     9,     1,     3,     5,     7,     5,     4,
       9,     8,     0,     3,     6,     3,     0,     1,     2,     1,
       1,     1,     1,     1,     5,     3,     5,     1,     3,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     5,     1,     3,     3,     5,    11,     2,     6,
       0,     3,     0,     2,     0,     3,     0,     1,     3,     2,
       2,     1,     3,     2,     3,     3,     3,     3,     3,     3,
       4,     2,     1,     1,     1,     1,     1,     2,     4,     4,
       2,     4,     0,     1,     1,     5,     5,     5,     7,     5,
       3,     4,     1,     1,     1,     1,     1,     1,     5,     7,
       5,     5,     7,     5,     7,     9,     7,     7,     9,     7,
       0,     1,     2,     0,     4,     0,     2,     5,     0,     2,
       0,     1,     3,     3,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     2,     7,     2,
       4,     0,     1
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
#line 245 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1906 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 275 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1915 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 281 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1923 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 286 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1931 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 292 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1939 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 298 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1947 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 304 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1955 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 310 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1965 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 317 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1973 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 323 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1983 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE index_list RBRACE  */
#line 343 "yacc_sql.y"
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
#line 2001 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE index_list RBRACE  */
#line 357 "yacc_sql.y"
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
#line 2019 "yacc_sql.cpp"
    break;

  case 34: /* index_list: ID  */
#line 374 "yacc_sql.y"
    {
        (yyval.index_list) = new std::vector<std::string>;
        (yyval.index_list)->push_back((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 2029 "yacc_sql.cpp"
    break;

  case 35: /* index_list: index_list COMMA ID  */
#line 380 "yacc_sql.y"
    {
        (yyval.index_list) = (yyvsp[-2].index_list);
        (yyval.index_list)->push_back((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 389 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2051 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 399 "yacc_sql.y"
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
#line 2071 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID AS select_stmt  */
#line 415 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      create_table.use_select = true;
    }
#line 2084 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID select_stmt  */
#line 424 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      create_table.use_select = true;
    }
#line 2097 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt  */
#line 433 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));
      create_table.use_select = true;
    }
#line 2110 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt  */
#line 442 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE_SELECT;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));
      create_table.use_select = true;
    }
#line 2123 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: %empty  */
#line 453 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2131 "yacc_sql.cpp"
    break;

  case 43: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 457 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2145 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 470 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-5].string));
    }
#line 2158 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type nullable  */
#line 479 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-2].string));
    }
#line 2171 "yacc_sql.cpp"
    break;

  case 46: /* nullable: %empty  */
#line 490 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2179 "yacc_sql.cpp"
    break;

  case 47: /* nullable: NULL_T  */
#line 494 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2187 "yacc_sql.cpp"
    break;

  case 48: /* nullable: NOT NULL_T  */
#line 498 "yacc_sql.y"
    {
      (yyval.nullable) = false;
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 49: /* number: NUMBER  */
#line 503 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2201 "yacc_sql.cpp"
    break;

  case 50: /* type: INT_T  */
#line 506 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2207 "yacc_sql.cpp"
    break;

  case 51: /* type: STRING_T  */
#line 507 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2213 "yacc_sql.cpp"
    break;

  case 52: /* type: FLOAT_T  */
#line 508 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2219 "yacc_sql.cpp"
    break;

  case 53: /* type: DATE_T  */
#line 509 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2225 "yacc_sql.cpp"
    break;

  case 54: /* insert_stmt: INSERT INTO ID VALUES value_lists  */
#line 513 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].value_lists));
      delete (yyvsp[0].value_lists);
      free((yyvsp[-2].string));
    }
#line 2237 "yacc_sql.cpp"
    break;

  case 55: /* value_lists: LBRACE value_list RBRACE  */
#line 523 "yacc_sql.y"
    {
      (yyval.value_lists) = new std::vector<std::vector<Value>>;
      (yyval.value_lists)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2247 "yacc_sql.cpp"
    break;

  case 56: /* value_lists: value_lists COMMA LBRACE value_list RBRACE  */
#line 529 "yacc_sql.y"
    {
      (yyval.value_lists) = (yyvsp[-4].value_lists);
      (yyval.value_lists)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2257 "yacc_sql.cpp"
    break;

  case 57: /* value_list: value  */
#line 537 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2267 "yacc_sql.cpp"
    break;

  case 58: /* value_list: value_list COMMA value  */
#line 542 "yacc_sql.y"
                             { 
      (yyval.value_list) = (yyvsp[-2].value_list);
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2277 "yacc_sql.cpp"
    break;

  case 59: /* value: NUMBER  */
#line 549 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2286 "yacc_sql.cpp"
    break;

  case 60: /* value: MINUS NUMBER  */
#line 553 "yacc_sql.y"
                   {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2295 "yacc_sql.cpp"
    break;

  case 61: /* value: FLOAT  */
#line 557 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2304 "yacc_sql.cpp"
    break;

  case 62: /* value: MINUS FLOAT  */
#line 561 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2313 "yacc_sql.cpp"
    break;

  case 63: /* value: SSS  */
#line 565 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 64: /* value: DATE  */
#line 570 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      bool check;
      (yyval.value) = new Value(tmp, &check);
      free(tmp);
      if (!check) {
        return -1;
      }
    }
#line 2337 "yacc_sql.cpp"
    break;

  case 65: /* value: NULL_T  */
#line 579 "yacc_sql.y"
            {
      (yyval.value) = new Value(AttrType::OBNULL);
    }
#line 2345 "yacc_sql.cpp"
    break;

  case 66: /* expr_value: NUMBER  */
#line 584 "yacc_sql.y"
           {
      (yyval.expr_value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2354 "yacc_sql.cpp"
    break;

  case 67: /* expr_value: FLOAT  */
#line 588 "yacc_sql.y"
           {
      (yyval.expr_value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2363 "yacc_sql.cpp"
    break;

  case 68: /* expr_value: SSS  */
#line 592 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.expr_value) = new Value(tmp);
      free(tmp);
    }
#line 2373 "yacc_sql.cpp"
    break;

  case 69: /* expr_value: DATE  */
#line 597 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      bool check;
      (yyval.expr_value) = new Value(tmp, &check);
      free(tmp);
      if (!check) {
        return -1;
      }
    }
#line 2387 "yacc_sql.cpp"
    break;

  case 70: /* expr_value: NULL_T  */
#line 606 "yacc_sql.y"
            {
      (yyval.expr_value) = new Value(AttrType::OBNULL);
    }
#line 2395 "yacc_sql.cpp"
    break;

  case 71: /* delete_stmt: DELETE FROM ID where  */
#line 613 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2409 "yacc_sql.cpp"
    break;

  case 72: /* update_stmt: UPDATE ID SET update_field_list where  */
#line 625 "yacc_sql.y"
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
#line 2425 "yacc_sql.cpp"
    break;

  case 73: /* update_field_list: update_field  */
#line 639 "yacc_sql.y"
    {
      (yyval.update_field_list) = new std::vector<UpdateFieldNode>;
      (yyval.update_field_list)->emplace_back(*(yyvsp[0].update_field));
      delete (yyvsp[0].update_field);
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 74: /* update_field_list: update_field_list COMMA update_field  */
#line 645 "yacc_sql.y"
    {
      (yyval.update_field_list) = (yyvsp[-2].update_field_list);
      (yyval.update_field_list)->emplace_back(*(yyvsp[0].update_field));
      delete (yyvsp[0].update_field);
    }
#line 2445 "yacc_sql.cpp"
    break;

  case 75: /* update_field: ID EQ value  */
#line 652 "yacc_sql.y"
    {
      (yyval.update_field) = new UpdateFieldNode();
      (yyval.update_field)->attribute_name = (yyvsp[-2].string);
      (yyval.update_field)->is_value = true;
      (yyval.update_field)->value = *(yyvsp[0].value);
      delete (yyvsp[0].value);
      free((yyvsp[-2].string));
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 76: /* update_field: ID EQ LBRACE select_stmt RBRACE  */
#line 662 "yacc_sql.y"
    {
      (yyval.update_field) = new UpdateFieldNode();
      (yyval.update_field)->attribute_name = (yyvsp[-4].string);
      (yyval.update_field)->is_value = false;
      (yyval.update_field)->subSelect = (yyvsp[-1].sql_node)->selection;
      delete (yyvsp[-1].sql_node);
      free((yyvsp[-4].string));
    }
#line 2471 "yacc_sql.cpp"
    break;

  case 77: /* select_stmt: SELECT expression_list FROM ID alias rel_list innerJoin_list where order_by group_by having  */
#line 729 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
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
          if ((yyval.sql_node)->selection.aggregations[i].relation_name.empty()) {
            (yyval.sql_node)->selection.attributes[i].relation_name = (yyvsp[-7].string);
          } else {
            (yyval.sql_node)->selection.attributes[i].relation_name = (yyval.sql_node)->selection.aggregations[i].relation_name;
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
      if ((yyvsp[-1].group_by_list) != nullptr) {
        (yyval.sql_node)->selection.use_group_by = true;
        (yyval.sql_node)->selection.groupbys.swap(*(yyvsp[-1].group_by_list));
        std::reverse((yyval.sql_node)->selection.groupbys.begin(), (yyval.sql_node)->selection.groupbys.end());
        delete (yyvsp[-1].group_by_list);
      } else {
        (yyval.sql_node)->selection.use_group_by = false;
      }
      // having conditon
      if ((yyvsp[0].having) != nullptr) {
        (yyval.sql_node)->selection.having_conditions.swap(*(yyvsp[0].having));
        delete (yyvsp[0].having);
      }
      aggregation_cnt = 0;
      aggr_start_offset = 0;
    }
#line 2546 "yacc_sql.cpp"
    break;

  case 78: /* select_stmt: SELECT expression_list  */
#line 800 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2558 "yacc_sql.cpp"
    break;

  case 79: /* select_stmt: SELECT error FROM ID rel_list where  */
#line 832 "yacc_sql.y"
    {
      return -1;
    }
#line 2566 "yacc_sql.cpp"
    break;

  case 80: /* group_by: %empty  */
#line 837 "yacc_sql.y"
    {
      (yyval.group_by_list) = nullptr;
    }
#line 2574 "yacc_sql.cpp"
    break;

  case 81: /* group_by: GROUP BY expression_list  */
#line 841 "yacc_sql.y"
    {
      (yyval.group_by_list) = (yyvsp[0].expression_list);
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 82: /* having: %empty  */
#line 847 "yacc_sql.y"
    {
      (yyval.having) = nullptr;
    }
#line 2590 "yacc_sql.cpp"
    break;

  case 83: /* having: HAVING condition_list  */
#line 851 "yacc_sql.y"
    {
      (yyval.having) = (yyvsp[0].condition_list);
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 84: /* order_by: %empty  */
#line 857 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2606 "yacc_sql.cpp"
    break;

  case 85: /* order_by: ORDER BY order_by_list  */
#line 861 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2614 "yacc_sql.cpp"
    break;

  case 86: /* order_by_list: %empty  */
#line 867 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2622 "yacc_sql.cpp"
    break;

  case 87: /* order_by_list: order_attr  */
#line 870 "yacc_sql.y"
                 {
      (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      (yyval.order_by_list)->emplace_back(*(yyvsp[0].order_attr));
      delete (yyvsp[0].order_attr);
    }
#line 2632 "yacc_sql.cpp"
    break;

  case 88: /* order_by_list: order_attr COMMA order_by_list  */
#line 875 "yacc_sql.y"
                                     {
      if ((yyvsp[0].order_by_list) != nullptr) {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else {
        (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      }
      (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_attr));
      delete (yyvsp[-2].order_attr);
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 89: /* calc_stmt: CALC expression_list  */
#line 887 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      // std::reverse($2->begin(), $2->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      std::reverse((yyval.sql_node)->calc.expressions.begin(), (yyval.sql_node)->calc.expressions.end());
      delete (yyvsp[0].expression_list);
    }
#line 2658 "yacc_sql.cpp"
    break;

  case 90: /* expression_list: '*' alias  */
#line 898 "yacc_sql.y"
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
#line 2675 "yacc_sql.cpp"
    break;

  case 91: /* expression_list: expression  */
#line 911 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<ExprSqlNode>;
      (yyval.expression_list)->emplace_back(*(yyvsp[0].expression));
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 92: /* expression_list: expression COMMA expression_list  */
#line 916 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<ExprSqlNode>;
      }
      (yyval.expression_list)->emplace_back(*(yyvsp[-2].expression));
    }
#line 2697 "yacc_sql.cpp"
    break;

  case 93: /* set_expression: COMMA expression  */
#line 927 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<ExprSqlNode>;
      (yyval.expression_list)->emplace_back(*(yyvsp[0].expression));
    }
#line 2706 "yacc_sql.cpp"
    break;

  case 94: /* set_expression: COMMA expression set_expression  */
#line 931 "yacc_sql.y"
                                     {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<ExprSqlNode>;
      }
      (yyval.expression_list)->emplace_back(*(yyvsp[-1].expression));
    }
#line 2719 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '+' expression  */
#line 941 "yacc_sql.y"
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
#line 2741 "yacc_sql.cpp"
    break;

  case 96: /* expression: expression MINUS expression  */
#line 958 "yacc_sql.y"
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
#line 2762 "yacc_sql.cpp"
    break;

  case 97: /* expression: expression '*' expression  */
#line 974 "yacc_sql.y"
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
#line 2783 "yacc_sql.cpp"
    break;

  case 98: /* expression: expression '/' expression  */
#line 990 "yacc_sql.y"
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
#line 2804 "yacc_sql.cpp"
    break;

  case 99: /* expression: LBRACE expression RBRACE  */
#line 1006 "yacc_sql.y"
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
#line 2825 "yacc_sql.cpp"
    break;

  case 100: /* expression: LBRACE expression set_expression RBRACE  */
#line 1023 "yacc_sql.y"
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
#line 2841 "yacc_sql.cpp"
    break;

  case 101: /* expression: MINUS expression  */
#line 1034 "yacc_sql.y"
                       {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression)->expression, nullptr, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[0].expression)->aggregations);
      (yyval.expression)->attributes.swap((yyvsp[0].expression)->attributes);
      (yyval.expression)->functions.swap((yyvsp[0].expression)->functions);
    }
#line 2853 "yacc_sql.cpp"
    break;

  case 102: /* expression: expr_value  */
#line 1041 "yacc_sql.y"
                 {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new ValueExpr(*(yyvsp[0].expr_value));
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].expr_value);
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 103: /* expression: rel_attr  */
#line 1047 "yacc_sql.y"
               {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new FieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name);
      if (!(yyvsp[0].rel_attr)->attribute_alias.empty()) {
        (yyval.expression)->expression->set_name((yyvsp[0].rel_attr)->attribute_alias);
      } else {
        (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      }
      (yyval.expression)->attributes.emplace_back(*(yyvsp[0].rel_attr));
      aggr_start_offset++;
      delete (yyvsp[0].rel_attr);
    }
#line 2881 "yacc_sql.cpp"
    break;

  case 104: /* expression: aggr_attr  */
#line 1059 "yacc_sql.y"
                {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new AggregationExpr((yyvsp[0].aggr_attr)->aggregation_name,(yyvsp[0].aggr_attr)->attribute_name);
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      (yyval.expression)->aggregations.emplace_back(*(yyvsp[0].aggr_attr));
      (yyval.expression)->expression->set_index(aggregation_cnt+aggr_start_offset);
      aggregation_cnt++;
      RelAttrSqlNode *rel_node = new RelAttrSqlNode;
      rel_node->attribute_name = (yyvsp[0].aggr_attr)->attribute_name;
      (yyval.expression)->attributes.push_back(*rel_node);
      delete (yyvsp[0].aggr_attr);
      delete rel_node;
    }
#line 2899 "yacc_sql.cpp"
    break;

  case 105: /* expression: func  */
#line 1072 "yacc_sql.y"
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
#line 2951 "yacc_sql.cpp"
    break;

  case 106: /* expression: select_stmt  */
#line 1120 "yacc_sql.y"
                  {
      (yyval.expression) = new ExprSqlNode;
      ParsedSqlNode * subsql_node = std::move((yyvsp[0].sql_node));
      (yyval.expression)->expression = new SubSelectExpr(subsql_node);   
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2962 "yacc_sql.cpp"
    break;

  case 107: /* rel_attr: ID alias  */
#line 1159 "yacc_sql.y"
             {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.rel_attr)->attribute_alias = (yyvsp[0].alias);
      }
      free((yyvsp[-1].string));
    }
#line 2975 "yacc_sql.cpp"
    break;

  case 108: /* rel_attr: ID DOT '*' alias  */
#line 1167 "yacc_sql.y"
                       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = "*";
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.rel_attr)->attribute_alias = (yyvsp[0].alias);
      }
      free((yyvsp[-3].string));
    }
#line 2989 "yacc_sql.cpp"
    break;

  case 109: /* rel_attr: ID DOT ID alias  */
#line 1176 "yacc_sql.y"
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
#line 3004 "yacc_sql.cpp"
    break;

  case 110: /* order_attr: ID order_type  */
#line 1189 "yacc_sql.y"
                  {
      (yyval.order_attr) = new OrderBySqlNode;
      (yyval.order_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.order_attr)->order_type = (yyvsp[0].order_type);
      free((yyvsp[-1].string));
    }
#line 3015 "yacc_sql.cpp"
    break;

  case 111: /* order_attr: ID DOT ID order_type  */
#line 1195 "yacc_sql.y"
                           {
      (yyval.order_attr) = new OrderBySqlNode;
      (yyval.order_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.order_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.order_attr)->order_type = (yyvsp[0].order_type);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 3028 "yacc_sql.cpp"
    break;

  case 112: /* order_type: %empty  */
#line 1206 "yacc_sql.y"
    {
      (yyval.order_type) = ASC_T;
    }
#line 3036 "yacc_sql.cpp"
    break;

  case 113: /* order_type: ASC  */
#line 1209 "yacc_sql.y"
          { (yyval.order_type) = ASC_T; }
#line 3042 "yacc_sql.cpp"
    break;

  case 114: /* order_type: DESC  */
#line 1210 "yacc_sql.y"
           { (yyval.order_type) = DESC_T; }
#line 3048 "yacc_sql.cpp"
    break;

  case 115: /* aggr_attr: COUNT LBRACE '*' RBRACE alias  */
#line 1213 "yacc_sql.y"
                                  {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = "count";
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = "*";
    }
#line 3061 "yacc_sql.cpp"
    break;

  case 116: /* aggr_attr: COUNT LBRACE ID RBRACE alias  */
#line 1221 "yacc_sql.y"
                                   {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = "count";
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = (yyvsp[-2].string);
    }
#line 3074 "yacc_sql.cpp"
    break;

  case 117: /* aggr_attr: aggr_func LBRACE ID RBRACE alias  */
#line 1229 "yacc_sql.y"
                                       {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = (yyvsp[-4].aggr_func);
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = (yyvsp[-2].string);
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 118: /* aggr_attr: aggr_func LBRACE ID DOT ID RBRACE alias  */
#line 1237 "yacc_sql.y"
                                              {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = (yyvsp[-6].aggr_func);
      (yyval.aggr_attr)->relation_name =(yyvsp[-4].string);
      if ((yyvsp[0].alias) != nullptr) {
        (yyval.aggr_attr)->alias = (yyvsp[0].alias);
      }
      (yyval.aggr_attr)->attribute_name = (yyvsp[-2].string);
    }
#line 3101 "yacc_sql.cpp"
    break;

  case 119: /* aggr_attr: aggr_func LBRACE '*' RBRACE alias  */
#line 1246 "yacc_sql.y"
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
#line 3117 "yacc_sql.cpp"
    break;

  case 120: /* aggr_attr: aggr_func LBRACE RBRACE  */
#line 1257 "yacc_sql.y"
                              {
      return -1;
    }
#line 3125 "yacc_sql.cpp"
    break;

  case 121: /* aggr_attr: aggr_func LBRACE error RBRACE  */
#line 1260 "yacc_sql.y"
                                    {
      return -1;
    }
#line 3133 "yacc_sql.cpp"
    break;

  case 122: /* aggr_func: COUNT  */
#line 1266 "yacc_sql.y"
          {
      (yyval.aggr_func) = "count";
    }
#line 3141 "yacc_sql.cpp"
    break;

  case 123: /* aggr_func: MIN  */
#line 1269 "yacc_sql.y"
          {
      (yyval.aggr_func) = "min";
    }
#line 3149 "yacc_sql.cpp"
    break;

  case 124: /* aggr_func: MAX  */
#line 1272 "yacc_sql.y"
          {
      (yyval.aggr_func) = "max";
    }
#line 3157 "yacc_sql.cpp"
    break;

  case 125: /* aggr_func: SUM  */
#line 1275 "yacc_sql.y"
          {
      (yyval.aggr_func) = "sum";
    }
#line 3165 "yacc_sql.cpp"
    break;

  case 126: /* aggr_func: AVG  */
#line 1278 "yacc_sql.y"
          {
      (yyval.aggr_func) = "avg";
    }
#line 3173 "yacc_sql.cpp"
    break;

  case 127: /* aggr_func: ID  */
#line 1281 "yacc_sql.y"
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
#line 3194 "yacc_sql.cpp"
    break;

  case 128: /* func: LENGTH LBRACE ID RBRACE alias  */
#line 1299 "yacc_sql.y"
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
#line 3209 "yacc_sql.cpp"
    break;

  case 129: /* func: LENGTH LBRACE ID DOT ID RBRACE alias  */
#line 1309 "yacc_sql.y"
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
#line 3226 "yacc_sql.cpp"
    break;

  case 130: /* func: LENGTH LBRACE value RBRACE alias  */
#line 1321 "yacc_sql.y"
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
#line 3241 "yacc_sql.cpp"
    break;

  case 131: /* func: ROUND LBRACE ID RBRACE alias  */
#line 1331 "yacc_sql.y"
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
#line 3257 "yacc_sql.cpp"
    break;

  case 132: /* func: ROUND LBRACE ID DOT ID RBRACE alias  */
#line 1342 "yacc_sql.y"
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
#line 3275 "yacc_sql.cpp"
    break;

  case 133: /* func: ROUND LBRACE value RBRACE alias  */
#line 1355 "yacc_sql.y"
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
#line 3291 "yacc_sql.cpp"
    break;

  case 134: /* func: ROUND LBRACE ID COMMA value RBRACE alias  */
#line 1366 "yacc_sql.y"
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
#line 3308 "yacc_sql.cpp"
    break;

  case 135: /* func: ROUND LBRACE ID DOT ID COMMA value RBRACE alias  */
#line 1378 "yacc_sql.y"
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
#line 3327 "yacc_sql.cpp"
    break;

  case 136: /* func: ROUND LBRACE value COMMA value RBRACE alias  */
#line 1392 "yacc_sql.y"
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
#line 3344 "yacc_sql.cpp"
    break;

  case 137: /* func: DATE_FORMAT LBRACE ID COMMA value RBRACE alias  */
#line 1404 "yacc_sql.y"
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
#line 3361 "yacc_sql.cpp"
    break;

  case 138: /* func: DATE_FORMAT LBRACE ID DOT ID COMMA value RBRACE alias  */
#line 1416 "yacc_sql.y"
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
#line 3380 "yacc_sql.cpp"
    break;

  case 139: /* func: DATE_FORMAT LBRACE value COMMA value RBRACE alias  */
#line 1430 "yacc_sql.y"
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
#line 3397 "yacc_sql.cpp"
    break;

  case 140: /* alias: %empty  */
#line 1445 "yacc_sql.y"
    {
      (yyval.alias) = nullptr;
    }
#line 3405 "yacc_sql.cpp"
    break;

  case 141: /* alias: ID  */
#line 1448 "yacc_sql.y"
         {
      if (0 == strcmp((yyvsp[0].string), "alias")) {
        return -1;
      }
      (yyval.alias) = (yyvsp[0].string);
    }
#line 3416 "yacc_sql.cpp"
    break;

  case 142: /* alias: AS ID  */
#line 1454 "yacc_sql.y"
            {
      if (0 == strcmp((yyvsp[0].string), "alias")) {
        return -1;
      }
      (yyval.alias) = (yyvsp[0].string);
    }
#line 3427 "yacc_sql.cpp"
    break;

  case 143: /* rel_list: %empty  */
#line 1496 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3435 "yacc_sql.cpp"
    break;

  case 144: /* rel_list: COMMA ID alias rel_list  */
#line 1499 "yacc_sql.y"
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
#line 3455 "yacc_sql.cpp"
    break;

  case 145: /* innerJoin_list: %empty  */
#line 1517 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3463 "yacc_sql.cpp"
    break;

  case 146: /* innerJoin_list: inner_join innerJoin_list  */
#line 1520 "yacc_sql.y"
                              {
      if ((yyvsp[0].inner_join_list) == nullptr)
        (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      else
        (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_join));
      delete (yyvsp[-1].inner_join);
    }
#line 3476 "yacc_sql.cpp"
    break;

  case 147: /* inner_join: INNER JOIN ID ON condition_list  */
#line 1529 "yacc_sql.y"
                                    {
      (yyval.inner_join) = new InnerJoinSqlNode;
      (yyval.inner_join)->relation = (yyvsp[-2].string);
      delete (yyvsp[-2].string);
      (yyval.inner_join)->conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3488 "yacc_sql.cpp"
    break;

  case 148: /* where: %empty  */
#line 1538 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3496 "yacc_sql.cpp"
    break;

  case 149: /* where: WHERE condition_list  */
#line 1541 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3504 "yacc_sql.cpp"
    break;

  case 150: /* condition_list: %empty  */
#line 1547 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3512 "yacc_sql.cpp"
    break;

  case 151: /* condition_list: condition  */
#line 1550 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3522 "yacc_sql.cpp"
    break;

  case 152: /* condition_list: condition AND condition_list  */
#line 1555 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3532 "yacc_sql.cpp"
    break;

  case 153: /* condition: expression comp_op expression  */
#line 1563 "yacc_sql.y"
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
#line 3597 "yacc_sql.cpp"
    break;

  case 154: /* condition: EXISTS expression  */
#line 1624 "yacc_sql.y"
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
#line 3618 "yacc_sql.cpp"
    break;

  case 155: /* condition: NOT EXISTS expression  */
#line 1641 "yacc_sql.y"
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
#line 3639 "yacc_sql.cpp"
    break;

  case 156: /* comp_op: EQ  */
#line 1708 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3645 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: LT  */
#line 1709 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3651 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: GT  */
#line 1710 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3657 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: LE  */
#line 1711 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3663 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: GE  */
#line 1712 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3669 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: NE  */
#line 1713 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3675 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: LIKE  */
#line 1714 "yacc_sql.y"
           {(yyval.comp) = LIKE_OP;}
#line 3681 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: NOT LIKE  */
#line 1715 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP;}
#line 3687 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: IS  */
#line 1716 "yacc_sql.y"
         { (yyval.comp) = IS_OP;}
#line 3693 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: IS NOT  */
#line 1717 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_OP;}
#line 3699 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: IN  */
#line 1718 "yacc_sql.y"
         {(yyval.comp) = IN_OP;}
#line 3705 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: NOT IN  */
#line 1719 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP;}
#line 3711 "yacc_sql.cpp"
    break;

  case 168: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1724 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3725 "yacc_sql.cpp"
    break;

  case 169: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1737 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3734 "yacc_sql.cpp"
    break;

  case 170: /* set_variable_stmt: SET ID EQ value  */
#line 1745 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3746 "yacc_sql.cpp"
    break;


#line 3750 "yacc_sql.cpp"

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

#line 1757 "yacc_sql.y"

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
