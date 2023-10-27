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


#line 115 "yacc_sql.cpp"

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
  YYSYMBOL_BY = 55,                        /* BY  */
  YYSYMBOL_ASC = 56,                       /* ASC  */
  YYSYMBOL_MINUS = 57,                     /* MINUS  */
  YYSYMBOL_IN = 58,                        /* IN  */
  YYSYMBOL_EXISTS = 59,                    /* EXISTS  */
  YYSYMBOL_NUMBER = 60,                    /* NUMBER  */
  YYSYMBOL_DATE = 61,                      /* DATE  */
  YYSYMBOL_FLOAT = 62,                     /* FLOAT  */
  YYSYMBOL_ID = 63,                        /* ID  */
  YYSYMBOL_SSS = 64,                       /* SSS  */
  YYSYMBOL_65_ = 65,                       /* '+'  */
  YYSYMBOL_66_ = 66,                       /* '*'  */
  YYSYMBOL_67_ = 67,                       /* '/'  */
  YYSYMBOL_UMINUS = 68,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_commands = 70,                  /* commands  */
  YYSYMBOL_command_wrapper = 71,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 72,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 73,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 74,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 75,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 76,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 77,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 78,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 79,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 80,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 81,         /* create_index_stmt  */
  YYSYMBOL_index_list = 82,                /* index_list  */
  YYSYMBOL_drop_index_stmt = 83,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 84,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 85,             /* attr_def_list  */
  YYSYMBOL_attr_def = 86,                  /* attr_def  */
  YYSYMBOL_nullable = 87,                  /* nullable  */
  YYSYMBOL_number = 88,                    /* number  */
  YYSYMBOL_type = 89,                      /* type  */
  YYSYMBOL_insert_stmt = 90,               /* insert_stmt  */
  YYSYMBOL_value_lists = 91,               /* value_lists  */
  YYSYMBOL_value_list = 92,                /* value_list  */
  YYSYMBOL_value = 93,                     /* value  */
  YYSYMBOL_expr_value = 94,                /* expr_value  */
  YYSYMBOL_delete_stmt = 95,               /* delete_stmt  */
  YYSYMBOL_update_stmt = 96,               /* update_stmt  */
  YYSYMBOL_update_field_list = 97,         /* update_field_list  */
  YYSYMBOL_update_field = 98,              /* update_field  */
  YYSYMBOL_select_stmt = 99,               /* select_stmt  */
  YYSYMBOL_order_by = 100,                 /* order_by  */
  YYSYMBOL_order_by_list = 101,            /* order_by_list  */
  YYSYMBOL_calc_stmt = 102,                /* calc_stmt  */
  YYSYMBOL_expression_list = 103,          /* expression_list  */
  YYSYMBOL_set_expression = 104,           /* set_expression  */
  YYSYMBOL_expression = 105,               /* expression  */
  YYSYMBOL_rel_attr = 106,                 /* rel_attr  */
  YYSYMBOL_order_attr = 107,               /* order_attr  */
  YYSYMBOL_order_type = 108,               /* order_type  */
  YYSYMBOL_aggr_attr = 109,                /* aggr_attr  */
  YYSYMBOL_rel_list = 110,                 /* rel_list  */
  YYSYMBOL_innerJoin_list = 111,           /* innerJoin_list  */
  YYSYMBOL_inner_join = 112,               /* inner_join  */
  YYSYMBOL_where = 113,                    /* where  */
  YYSYMBOL_condition_list = 114,           /* condition_list  */
  YYSYMBOL_condition = 115,                /* condition  */
  YYSYMBOL_comp_op = 116,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 117,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 118,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 119,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 120             /* opt_semicolon  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   262

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  138
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  249

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


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
       2,     2,    66,    65,     2,     2,     2,    67,     2,     2,
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
      68
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   219,   219,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   250,   256,   261,   267,   273,   279,   285,
     292,   298,   317,   331,   348,   354,   363,   373,   392,   395,
     408,   417,   429,   432,   436,   442,   445,   446,   447,   448,
     451,   461,   467,   475,   481,   488,   492,   496,   500,   504,
     509,   518,   523,   527,   531,   536,   545,   551,   563,   577,
     583,   590,   600,   667,   731,   737,   740,   747,   750,   755,
     766,   777,   790,   795,   806,   811,   821,   834,   846,   858,
     870,   874,   886,   892,   898,   905,   916,   955,   960,   970,
     976,   987,   990,   991,   994,  1003,  1010,  1019,  1022,  1062,
    1065,  1078,  1081,  1090,  1099,  1102,  1108,  1111,  1116,  1123,
    1153,  1170,  1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,
    1246,  1247,  1248,  1249,  1253,  1266,  1274,  1284,  1285
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
  "ORDER", "BY", "ASC", "MINUS", "IN", "EXISTS", "NUMBER", "DATE", "FLOAT",
  "ID", "SSS", "'+'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "index_list", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "nullable", "number",
  "type", "insert_stmt", "value_lists", "value_list", "value",
  "expr_value", "delete_stmt", "update_stmt", "update_field_list",
  "update_field", "select_stmt", "order_by", "order_by_list", "calc_stmt",
  "expression_list", "set_expression", "expression", "rel_attr",
  "order_attr", "order_type", "aggr_attr", "rel_list", "innerJoin_list",
  "inner_join", "where", "condition_list", "condition", "comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-176)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     160,     2,    13,    17,     4,   -43,    27,  -176,    14,    38,
      26,  -176,  -176,  -176,  -176,  -176,    29,    21,   160,   107,
     106,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,    50,    51,   108,    56,    61,    89,  -176,    89,  -176,
    -176,  -176,     3,  -176,  -176,  -176,  -176,  -176,    66,  -176,
    -176,    93,   105,  -176,  -176,    62,    78,   109,   100,   103,
    -176,  -176,  -176,  -176,   129,   115,    94,  -176,   117,    55,
     -29,     6,   104,    17,    89,    89,    89,    89,   118,   122,
     127,   130,   123,   150,    99,   124,   131,   132,   133,  -176,
      89,   148,   152,  -176,    -3,   172,  -176,  -176,   -29,   -29,
    -176,  -176,   159,   159,   174,    34,  -176,   151,    -8,  -176,
    -176,    40,  -176,  -176,  -176,  -176,  -176,   164,    24,   178,
     182,   139,  -176,    69,  -176,  -176,  -176,   141,  -176,   142,
     130,   195,   150,   187,   154,    89,   171,  -176,   188,    98,
     123,  -176,  -176,  -176,   203,  -176,  -176,  -176,  -176,    -4,
     124,   204,   163,   208,  -176,   210,   159,  -176,   219,   130,
     195,    64,  -176,   213,    89,    72,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,   181,   -26,  -176,    89,    34,   224,  -176,
    -176,   176,   175,  -176,   211,  -176,   178,  -176,  -176,    83,
     163,  -176,  -176,   179,   189,  -176,  -176,   150,   150,    72,
    -176,  -176,  -176,    72,  -176,   221,  -176,  -176,   225,  -176,
    -176,  -176,   183,    85,   205,   192,  -176,  -176,    90,  -176,
     -13,  -176,  -176,    34,   185,  -176,  -176,  -176,    -2,  -176,
     228,  -176,   190,  -176,  -176,   185,    32,  -176,  -176
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     137,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,    66,     0,    62,
      65,    63,    97,    64,    81,    93,    96,    80,    82,    94,
      95,     0,     0,    31,    30,     0,     0,     0,     0,     0,
     135,     1,   138,     2,     0,     0,     0,    29,     0,     0,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,     0,     0,     0,     0,     0,     0,     0,    90,
       0,     0,     0,   107,     0,     0,    98,    83,    87,    86,
      88,    89,   109,   109,     0,   116,    67,     0,   114,    69,
      61,     0,    55,    60,    57,    59,   136,     0,     0,    38,
       0,     0,    36,    84,    91,   108,   105,     0,   104,     0,
     114,   111,     0,    50,     0,     0,     0,   115,   117,     0,
       0,    68,    56,    58,     0,    46,    47,    48,    49,    42,
       0,     0,     0,     0,    85,     0,   109,    74,     0,   114,
     111,     0,    53,     0,     0,   120,   122,   123,   124,   125,
     126,   127,   128,   130,     0,   132,     0,   116,     0,    71,
      70,     0,     0,    43,     0,    41,    38,    37,    34,     0,
       0,   106,   110,     0,    75,   112,    51,     0,     0,   121,
     131,   129,   133,   119,   118,     0,   134,    45,     0,    44,
      39,    32,     0,     0,     0,     0,    73,    54,     0,    72,
      42,    35,    33,   116,    77,    52,    40,   113,   101,    76,
      78,   103,     0,   102,    99,    77,   101,    79,   100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -176,  -176,   232,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,    52,  -176,  -176,    58,    91,    25,  -176,
    -176,  -176,  -176,    48,   -92,  -176,  -176,  -176,  -176,   110,
       0,  -176,    12,  -176,    -1,   125,   -44,  -176,  -176,    15,
    -176,  -107,    92,  -176,  -109,  -175,  -176,  -176,  -176,  -176,
    -176,  -176
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   199,    31,    32,   161,   129,   195,   218,
     159,    33,   143,   171,   172,    55,    34,    35,   118,   119,
      56,   226,   239,    37,    57,   101,    58,    59,   240,   244,
      60,   140,   169,   170,   116,   147,   148,   186,    38,    39,
      40,    73
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      36,   126,    79,    62,    80,    61,   141,   102,    41,   151,
      42,   241,   214,   150,     4,   192,   193,   136,    36,    44,
      63,    45,    81,    46,   211,   193,   103,     4,   115,   137,
     242,   167,   212,    47,    64,    82,    46,    86,    87,   194,
     108,   109,   110,   111,     4,   241,    47,    65,   194,   155,
     156,   157,   158,    46,   243,    43,   133,   189,   237,   202,
     204,    48,    69,    47,    49,    50,    51,    52,    53,   104,
      54,   146,   105,    66,    48,    99,   100,    49,    50,    51,
      52,    53,   107,    54,   206,   207,   144,    83,   243,    67,
     100,    48,    68,   145,    49,    50,    51,    52,    53,     4,
     152,   175,   153,   221,   222,   232,   222,    71,    46,    72,
     235,   207,    84,    74,    75,   227,    76,   188,    47,    77,
      85,    86,    87,    84,    78,    90,    84,   120,    88,    84,
     209,    85,    86,    87,    85,    86,    87,    85,    86,    87,
      89,    91,   213,   146,    93,    94,    48,    92,    95,    49,
      50,    51,    52,    53,    96,   121,    98,    97,   122,   123,
     124,   114,   125,   127,     1,     2,   115,   106,   134,     3,
       4,   131,   135,     5,     6,     7,     8,     9,    10,   120,
     139,   112,    11,    12,    13,   113,   117,   128,   215,   146,
      14,    15,   138,   142,   130,   149,   132,   154,    16,   160,
      17,   162,   163,    18,   165,   166,   168,   121,   173,   191,
     122,   123,   124,   174,   125,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   197,   187,   198,   200,    84,   185,
     201,   203,   208,   210,     4,   217,    85,    86,    87,   216,
     219,   229,   224,   225,   233,   230,   231,   234,   238,   245,
      70,   196,   223,   246,   220,   236,   228,   247,   164,     0,
     190,   248,   205
};

static const yytype_int16 yycheck[] =
{
       0,    93,    46,     4,    48,     1,   113,     1,     6,   118,
       8,    13,   187,    21,    10,    19,    29,    20,    18,     6,
      63,     8,    19,    19,    50,    29,    20,    10,    36,    32,
      32,   140,    58,    29,     7,    32,    19,    66,    67,    52,
      84,    85,    86,    87,    10,    13,    29,    33,    52,    25,
      26,    27,    28,    19,    56,    53,   100,   149,   233,   166,
     169,    57,    41,    29,    60,    61,    62,    63,    64,    63,
      66,   115,    66,    35,    57,    20,    21,    60,    61,    62,
      63,    64,    83,    66,    20,    21,    52,    21,    56,    63,
      21,    57,    63,    59,    60,    61,    62,    63,    64,    10,
      60,   145,    62,    20,    21,    20,    21,     0,    19,     3,
      20,    21,    57,    63,    63,   207,     8,    19,    29,    63,
      65,    66,    67,    57,    63,    63,    57,    29,    35,    57,
     174,    65,    66,    67,    65,    66,    67,    65,    66,    67,
      35,    63,   186,   187,    44,    42,    57,    38,    19,    60,
      61,    62,    63,    64,    39,    57,    39,    63,    60,    61,
      62,    34,    64,    64,     4,     5,    36,    63,    20,     9,
      10,    39,    20,    13,    14,    15,    16,    17,    18,    29,
      21,    63,    22,    23,    24,    63,    63,    63,   188,   233,
      30,    31,    20,    19,    63,    44,    63,    33,    38,    21,
      40,    19,    63,    43,    63,    63,    11,    57,    21,     6,
      60,    61,    62,    59,    64,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    20,    37,    63,    19,    57,    58,
      20,    12,    19,    52,    10,    60,    65,    66,    67,    63,
      29,    20,    63,    54,    39,    20,    63,    55,    63,    21,
      18,   160,   200,    63,   196,   230,   208,   245,   133,    -1,
     150,   246,   170
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     9,    10,    13,    14,    15,    16,    17,
      18,    22,    23,    24,    30,    31,    38,    40,    43,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    83,    84,    90,    95,    96,    99,   102,   117,   118,
     119,     6,     8,    53,     6,     8,    19,    29,    57,    60,
      61,    62,    63,    64,    66,    94,    99,   103,   105,   106,
     109,     1,   103,    63,     7,    33,    35,    63,    63,    41,
      71,     0,     3,   120,    63,    63,     8,    63,    63,   105,
     105,    19,    32,    21,    57,    65,    66,    67,    35,    35,
      63,    63,    38,    44,    42,    19,    39,    63,    39,    20,
      21,   104,     1,    20,    63,    66,    63,   103,   105,   105,
     105,   105,    63,    63,    34,    36,   113,    63,    97,    98,
      29,    57,    60,    61,    62,    64,    93,    64,    63,    86,
      63,    39,    63,   105,    20,    20,    20,    32,    20,    21,
     110,   110,    19,    91,    52,    59,   105,   114,   115,    44,
      21,   113,    60,    62,    33,    25,    26,    27,    28,    89,
      21,    85,    19,    63,   104,    63,    63,   113,    11,   111,
     112,    92,    93,    21,    59,   105,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    58,   116,    37,    19,    93,
      98,     6,    19,    29,    52,    87,    86,    20,    63,    82,
      19,    20,   110,    12,   113,   111,    20,    21,    19,   105,
      52,    50,    58,   105,   114,    99,    63,    60,    88,    29,
      85,    20,    21,    82,    63,    54,   100,    93,    92,    20,
      20,    63,    20,    39,    55,    20,    87,   114,    63,   101,
     107,    13,    32,    56,   108,    21,    63,   101,   108
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    81,    82,    82,    83,    84,    85,    85,
      86,    86,    87,    87,    87,    88,    89,    89,    89,    89,
      90,    91,    91,    92,    92,    93,    93,    93,    93,    93,
      93,    93,    94,    94,    94,    94,    94,    95,    96,    97,
      97,    98,    98,    99,    99,   100,   100,   101,   101,   101,
     102,   103,   103,   103,   104,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   107,
     107,   108,   108,   108,   109,   109,   109,   109,   109,   110,
     110,   111,   111,   112,   113,   113,   114,   114,   114,   115,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   117,   118,   119,   120,   120
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     9,     1,     3,     5,     7,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       5,     3,     5,     1,     3,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     5,     1,
       3,     3,     5,     8,     6,     0,     3,     0,     1,     3,
       2,     1,     1,     3,     2,     3,     3,     3,     3,     3,
       3,     4,     2,     1,     1,     1,     1,     1,     3,     2,
       4,     0,     1,     1,     4,     4,     6,     3,     4,     0,
       3,     0,     2,     5,     0,     2,     0,     1,     3,     3,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     2,     7,     2,     4,     0,     1
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
#line 220 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1810 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 250 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1819 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 256 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1827 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 261 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1835 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 267 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1843 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 273 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1851 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 279 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1859 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 285 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1869 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 292 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1877 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 298 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1887 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE index_list RBRACE  */
#line 318 "yacc_sql.y"
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
#line 1905 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE index_list RBRACE  */
#line 332 "yacc_sql.y"
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
#line 1923 "yacc_sql.cpp"
    break;

  case 34: /* index_list: ID  */
#line 349 "yacc_sql.y"
    {
        (yyval.index_list) = new std::vector<std::string>;
        (yyval.index_list)->push_back((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 1933 "yacc_sql.cpp"
    break;

  case 35: /* index_list: index_list COMMA ID  */
#line 355 "yacc_sql.y"
    {
        (yyval.index_list) = (yyvsp[-2].index_list);
        (yyval.index_list)->push_back((yyvsp[0].string));
        free((yyvsp[0].string));
    }
#line 1943 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 364 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1955 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 374 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1975 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 392 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1983 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 396 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1997 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 409 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-5].string));
    }
#line 2010 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type nullable  */
#line 418 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-2].string));
    }
#line 2023 "yacc_sql.cpp"
    break;

  case 42: /* nullable: %empty  */
#line 429 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2031 "yacc_sql.cpp"
    break;

  case 43: /* nullable: NULL_T  */
#line 433 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 44: /* nullable: NOT NULL_T  */
#line 437 "yacc_sql.y"
    {
      (yyval.nullable) = false;
    }
#line 2047 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 442 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2053 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 445 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2059 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 446 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2065 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 447 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2071 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 448 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2077 "yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES value_lists  */
#line 452 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].value_lists));
      delete (yyvsp[0].value_lists);
      free((yyvsp[-2].string));
    }
#line 2089 "yacc_sql.cpp"
    break;

  case 51: /* value_lists: LBRACE value_list RBRACE  */
#line 462 "yacc_sql.y"
    {
      (yyval.value_lists) = new std::vector<std::vector<Value>>;
      (yyval.value_lists)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2099 "yacc_sql.cpp"
    break;

  case 52: /* value_lists: value_lists COMMA LBRACE value_list RBRACE  */
#line 468 "yacc_sql.y"
    {
      (yyval.value_lists) = (yyvsp[-4].value_lists);
      (yyval.value_lists)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2109 "yacc_sql.cpp"
    break;

  case 53: /* value_list: value  */
#line 476 "yacc_sql.y"
    {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2119 "yacc_sql.cpp"
    break;

  case 54: /* value_list: value_list COMMA value  */
#line 481 "yacc_sql.y"
                             { 
      (yyval.value_list) = (yyvsp[-2].value_list);
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2129 "yacc_sql.cpp"
    break;

  case 55: /* value: NUMBER  */
#line 488 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2138 "yacc_sql.cpp"
    break;

  case 56: /* value: MINUS NUMBER  */
#line 492 "yacc_sql.y"
                   {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2147 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 496 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2156 "yacc_sql.cpp"
    break;

  case 58: /* value: MINUS FLOAT  */
#line 500 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2165 "yacc_sql.cpp"
    break;

  case 59: /* value: SSS  */
#line 504 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2175 "yacc_sql.cpp"
    break;

  case 60: /* value: DATE  */
#line 509 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      bool check;
      (yyval.value) = new Value(tmp, &check);
      free(tmp);
      if (!check) {
        return -1;
      }
    }
#line 2189 "yacc_sql.cpp"
    break;

  case 61: /* value: NULL_T  */
#line 518 "yacc_sql.y"
            {
      (yyval.value) = new Value(AttrType::OBNULL);
    }
#line 2197 "yacc_sql.cpp"
    break;

  case 62: /* expr_value: NUMBER  */
#line 523 "yacc_sql.y"
           {
      (yyval.expr_value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2206 "yacc_sql.cpp"
    break;

  case 63: /* expr_value: FLOAT  */
#line 527 "yacc_sql.y"
           {
      (yyval.expr_value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2215 "yacc_sql.cpp"
    break;

  case 64: /* expr_value: SSS  */
#line 531 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.expr_value) = new Value(tmp);
      free(tmp);
    }
#line 2225 "yacc_sql.cpp"
    break;

  case 65: /* expr_value: DATE  */
#line 536 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      bool check;
      (yyval.expr_value) = new Value(tmp, &check);
      free(tmp);
      if (!check) {
        return -1;
      }
    }
#line 2239 "yacc_sql.cpp"
    break;

  case 66: /* expr_value: NULL_T  */
#line 545 "yacc_sql.y"
            {
      (yyval.expr_value) = new Value(AttrType::OBNULL);
    }
#line 2247 "yacc_sql.cpp"
    break;

  case 67: /* delete_stmt: DELETE FROM ID where  */
#line 552 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2261 "yacc_sql.cpp"
    break;

  case 68: /* update_stmt: UPDATE ID SET update_field_list where  */
#line 564 "yacc_sql.y"
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
#line 2277 "yacc_sql.cpp"
    break;

  case 69: /* update_field_list: update_field  */
#line 578 "yacc_sql.y"
    {
      (yyval.update_field_list) = new std::vector<UpdateFieldNode>;
      (yyval.update_field_list)->emplace_back(*(yyvsp[0].update_field));
      delete (yyvsp[0].update_field);
    }
#line 2287 "yacc_sql.cpp"
    break;

  case 70: /* update_field_list: update_field_list COMMA update_field  */
#line 584 "yacc_sql.y"
    {
      (yyval.update_field_list) = (yyvsp[-2].update_field_list);
      (yyval.update_field_list)->emplace_back(*(yyvsp[0].update_field));
      delete (yyvsp[0].update_field);
    }
#line 2297 "yacc_sql.cpp"
    break;

  case 71: /* update_field: ID EQ value  */
#line 591 "yacc_sql.y"
    {
      (yyval.update_field) = new UpdateFieldNode();
      (yyval.update_field)->attribute_name = (yyvsp[-2].string);
      (yyval.update_field)->is_value = true;
      (yyval.update_field)->value = *(yyvsp[0].value);
      delete (yyvsp[0].value);
      free((yyvsp[-2].string));
    }
#line 2310 "yacc_sql.cpp"
    break;

  case 72: /* update_field: ID EQ LBRACE select_stmt RBRACE  */
#line 601 "yacc_sql.y"
    {
      (yyval.update_field) = new UpdateFieldNode();
      (yyval.update_field)->attribute_name = (yyvsp[-4].string);
      (yyval.update_field)->is_value = false;
      (yyval.update_field)->subSelect = (yyvsp[-1].sql_node)->selection;
      delete (yyvsp[-1].sql_node);
      free((yyvsp[-4].string));
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT expression_list FROM ID rel_list innerJoin_list where order_by  */
#line 668 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        for (const auto &expr : (yyval.sql_node)->selection.expressions) {
          for (const auto &attr : expr.attributes) {
            (yyval.sql_node)->selection.attributes.emplace_back(attr);
          }
          for (const auto &aggr : expr.aggregations) {
            (yyval.sql_node)->selection.aggregations.emplace_back(aggr);
          }
        }
        for (int i=0; i < (yyval.sql_node)->selection.aggregations.size(); i++) {
          (yyval.sql_node)->selection.attributes[i].relation_name = (yyvsp[-4].string);
        }
        delete (yyvsp[-6].expression_list);
      }
      if ((yyvsp[-3].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-3].relation_list));
        delete (yyvsp[-3].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-4].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());
      if ((yyvsp[-2].inner_join_list) != nullptr) {
        (yyval.sql_node)->selection.innerJoins.swap(*(yyvsp[-2].inner_join_list));
        std::reverse((yyval.sql_node)->selection.innerJoins.begin(), (yyval.sql_node)->selection.innerJoins.end());
        delete (yyvsp[-2].inner_join_list);
      }
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      if ((yyvsp[0].order_by_list) != nullptr) {
        (yyval.sql_node)->selection.orderbys.swap(*(yyvsp[0].order_by_list));
        std::reverse((yyval.sql_node)->selection.orderbys.begin(), (yyval.sql_node)->selection.orderbys.end());
        delete (yyvsp[0].order_by_list);
      }
      free((yyvsp[-4].string));
    }
#line 2367 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT error FROM ID rel_list where  */
#line 732 "yacc_sql.y"
    {
      return -1;
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 75: /* order_by: %empty  */
#line 737 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2383 "yacc_sql.cpp"
    break;

  case 76: /* order_by: ORDER BY order_by_list  */
#line 741 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2391 "yacc_sql.cpp"
    break;

  case 77: /* order_by_list: %empty  */
#line 747 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2399 "yacc_sql.cpp"
    break;

  case 78: /* order_by_list: order_attr  */
#line 750 "yacc_sql.y"
                 {
      (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      (yyval.order_by_list)->emplace_back(*(yyvsp[0].order_attr));
      delete (yyvsp[0].order_attr);
    }
#line 2409 "yacc_sql.cpp"
    break;

  case 79: /* order_by_list: order_attr COMMA order_by_list  */
#line 755 "yacc_sql.y"
                                     {
      if ((yyvsp[0].order_by_list) != nullptr) {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else {
        (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      }
      (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_attr));
      delete (yyvsp[-2].order_attr);
    }
#line 2423 "yacc_sql.cpp"
    break;

  case 80: /* calc_stmt: CALC expression_list  */
#line 767 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      // std::reverse($2->begin(), $2->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      std::reverse((yyval.sql_node)->calc.expressions.begin(), (yyval.sql_node)->calc.expressions.end());
      delete (yyvsp[0].expression_list);
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 81: /* expression_list: '*'  */
#line 778 "yacc_sql.y"
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
#line 2452 "yacc_sql.cpp"
    break;

  case 82: /* expression_list: expression  */
#line 791 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<ExprSqlNode>;
      (yyval.expression_list)->emplace_back(*(yyvsp[0].expression));
    }
#line 2461 "yacc_sql.cpp"
    break;

  case 83: /* expression_list: expression COMMA expression_list  */
#line 796 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<ExprSqlNode>;
      }
      (yyval.expression_list)->emplace_back(*(yyvsp[-2].expression));
    }
#line 2474 "yacc_sql.cpp"
    break;

  case 84: /* set_expression: COMMA expression  */
#line 807 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<ExprSqlNode>;
      (yyval.expression_list)->emplace_back(*(yyvsp[0].expression));
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 85: /* set_expression: COMMA expression set_expression  */
#line 811 "yacc_sql.y"
                                     {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<ExprSqlNode>;
      }
      (yyval.expression_list)->emplace_back(*(yyvsp[-1].expression));
    }
#line 2496 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '+' expression  */
#line 821 "yacc_sql.y"
                              {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression)->expression, (yyvsp[0].expression)->expression, sql_string, &(yyloc));
      // $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
      (yyval.expression)->aggregations.swap((yyvsp[-2].expression)->aggregations);
      for (const auto &aggr : (yyvsp[0].expression)->aggregations) {
        (yyval.expression)->aggregations.emplace_back(aggr);
      }
      (yyval.expression)->attributes.swap((yyvsp[-2].expression)->attributes);
      for (const auto &rel : (yyvsp[0].expression)->attributes) {
        (yyval.expression)->attributes.emplace_back(rel);
      }
    }
#line 2514 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression MINUS expression  */
#line 834 "yacc_sql.y"
                                  {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression)->expression, (yyvsp[0].expression)->expression, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[-2].expression)->aggregations);
      for (const auto &aggr : (yyvsp[0].expression)->aggregations) {
        (yyval.expression)->aggregations.emplace_back(aggr);
      }
      (yyval.expression)->attributes.swap((yyvsp[-2].expression)->attributes);
      for (const auto &rel : (yyvsp[0].expression)->attributes) {
        (yyval.expression)->attributes.emplace_back(rel);
      }
    }
#line 2531 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '*' expression  */
#line 846 "yacc_sql.y"
                                {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression)->expression, (yyvsp[0].expression)->expression, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[-2].expression)->aggregations);
      for (const auto &aggr : (yyvsp[0].expression)->aggregations) {
        (yyval.expression)->aggregations.emplace_back(aggr);
      }
      (yyval.expression)->attributes.swap((yyvsp[-2].expression)->attributes);
      for (const auto &rel : (yyvsp[0].expression)->attributes) {
        (yyval.expression)->attributes.emplace_back(rel);
      }
    }
#line 2548 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '/' expression  */
#line 858 "yacc_sql.y"
                                {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression)->expression, (yyvsp[0].expression)->expression, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[-2].expression)->aggregations);
      for (const auto &aggr : (yyvsp[0].expression)->aggregations) {
        (yyval.expression)->aggregations.emplace_back(aggr);
      }
      (yyval.expression)->attributes.swap((yyvsp[-2].expression)->attributes);
      for (const auto &rel : (yyvsp[0].expression)->attributes) {
        (yyval.expression)->attributes.emplace_back(rel);
      }
    }
#line 2565 "yacc_sql.cpp"
    break;

  case 90: /* expression: LBRACE expression RBRACE  */
#line 870 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2574 "yacc_sql.cpp"
    break;

  case 91: /* expression: LBRACE expression set_expression RBRACE  */
#line 875 "yacc_sql.y"
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
#line 2590 "yacc_sql.cpp"
    break;

  case 92: /* expression: MINUS expression  */
#line 886 "yacc_sql.y"
                       {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression)->expression, nullptr, sql_string, &(yyloc));
      (yyval.expression)->aggregations.swap((yyvsp[0].expression)->aggregations);
      (yyval.expression)->attributes.swap((yyvsp[0].expression)->attributes);
    }
#line 2601 "yacc_sql.cpp"
    break;

  case 93: /* expression: expr_value  */
#line 892 "yacc_sql.y"
                 {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new ValueExpr(*(yyvsp[0].expr_value));
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].expr_value);
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 94: /* expression: rel_attr  */
#line 898 "yacc_sql.y"
               {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new FieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      (yyval.expression)->attributes.emplace_back(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr);
    }
#line 2624 "yacc_sql.cpp"
    break;

  case 95: /* expression: aggr_attr  */
#line 905 "yacc_sql.y"
                {
      (yyval.expression) = new ExprSqlNode;
      (yyval.expression)->expression = new AggregationExpr((yyvsp[0].aggr_attr)->aggregation_name,(yyvsp[0].aggr_attr)->attribute_name);
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
      (yyval.expression)->aggregations.emplace_back(*(yyvsp[0].aggr_attr));
      RelAttrSqlNode *rel_node = new RelAttrSqlNode;
      rel_node->attribute_name = (yyvsp[0].aggr_attr)->attribute_name;
      (yyval.expression)->attributes.push_back(*rel_node);
      delete (yyvsp[0].aggr_attr);
      delete rel_node;
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 96: /* expression: select_stmt  */
#line 916 "yacc_sql.y"
                 {
      (yyval.expression) = new ExprSqlNode;
      ParsedSqlNode * subsql_node = std::move((yyvsp[0].sql_node));
      (yyval.expression)->expression = new SubSelectExpr(subsql_node);   
      (yyval.expression)->expression->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2651 "yacc_sql.cpp"
    break;

  case 97: /* rel_attr: ID  */
#line 955 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 98: /* rel_attr: ID DOT ID  */
#line 960 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2673 "yacc_sql.cpp"
    break;

  case 99: /* order_attr: ID order_type  */
#line 970 "yacc_sql.y"
                  {
      (yyval.order_attr) = new OrderBySqlNode;
      (yyval.order_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.order_attr)->order_type = (yyvsp[0].order_type);
      free((yyvsp[-1].string));
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 100: /* order_attr: ID DOT ID order_type  */
#line 976 "yacc_sql.y"
                           {
      (yyval.order_attr) = new OrderBySqlNode;
      (yyval.order_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.order_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.order_attr)->order_type = (yyvsp[0].order_type);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 2697 "yacc_sql.cpp"
    break;

  case 101: /* order_type: %empty  */
#line 987 "yacc_sql.y"
    {
      (yyval.order_type) = ASC_T;
    }
#line 2705 "yacc_sql.cpp"
    break;

  case 102: /* order_type: ASC  */
#line 990 "yacc_sql.y"
          { (yyval.order_type) = ASC_T; }
#line 2711 "yacc_sql.cpp"
    break;

  case 103: /* order_type: DESC  */
#line 991 "yacc_sql.y"
           { (yyval.order_type) = DESC_T; }
#line 2717 "yacc_sql.cpp"
    break;

  case 104: /* aggr_attr: ID LBRACE '*' RBRACE  */
#line 994 "yacc_sql.y"
                         {
      if (strcmp((yyvsp[-3].string), "count") != 0) {
        return -1;
      }
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = "count";
      (yyval.aggr_attr)->attribute_name   = "*";
      free((yyvsp[-3].string));
    }
#line 2731 "yacc_sql.cpp"
    break;

  case 105: /* aggr_attr: ID LBRACE ID RBRACE  */
#line 1003 "yacc_sql.y"
                          {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = (yyvsp[-3].string);
      (yyval.aggr_attr)->attribute_name   = (yyvsp[-1].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 2743 "yacc_sql.cpp"
    break;

  case 106: /* aggr_attr: ID LBRACE ID DOT ID RBRACE  */
#line 1010 "yacc_sql.y"
                               {
      (yyval.aggr_attr) = new AggrAttrSqlNode;
      (yyval.aggr_attr)->aggregation_name = (yyvsp[-5].string);
      (yyval.aggr_attr)->relation_name =(yyvsp[-3].string);
      (yyval.aggr_attr)->attribute_name =(yyvsp[-1].string);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 2757 "yacc_sql.cpp"
    break;

  case 107: /* aggr_attr: ID LBRACE RBRACE  */
#line 1019 "yacc_sql.y"
                       {
      return -1;
    }
#line 2765 "yacc_sql.cpp"
    break;

  case 108: /* aggr_attr: ID LBRACE error RBRACE  */
#line 1022 "yacc_sql.y"
                             {
      return -1;
    }
#line 2773 "yacc_sql.cpp"
    break;

  case 109: /* rel_list: %empty  */
#line 1062 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2781 "yacc_sql.cpp"
    break;

  case 110: /* rel_list: COMMA ID rel_list  */
#line 1065 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2796 "yacc_sql.cpp"
    break;

  case 111: /* innerJoin_list: %empty  */
#line 1078 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 2804 "yacc_sql.cpp"
    break;

  case 112: /* innerJoin_list: inner_join innerJoin_list  */
#line 1081 "yacc_sql.y"
                              {
      if ((yyvsp[0].inner_join_list) == nullptr)
        (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      else
        (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_join));
      delete (yyvsp[-1].inner_join);
    }
#line 2817 "yacc_sql.cpp"
    break;

  case 113: /* inner_join: INNER JOIN ID ON condition_list  */
#line 1090 "yacc_sql.y"
                                    {
      (yyval.inner_join) = new InnerJoinSqlNode;
      (yyval.inner_join)->relation = (yyvsp[-2].string);
      delete (yyvsp[-2].string);
      (yyval.inner_join)->conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 114: /* where: %empty  */
#line 1099 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2837 "yacc_sql.cpp"
    break;

  case 115: /* where: WHERE condition_list  */
#line 1102 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2845 "yacc_sql.cpp"
    break;

  case 116: /* condition_list: %empty  */
#line 1108 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2853 "yacc_sql.cpp"
    break;

  case 117: /* condition_list: condition  */
#line 1111 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2863 "yacc_sql.cpp"
    break;

  case 118: /* condition_list: condition AND condition_list  */
#line 1116 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 119: /* condition: expression comp_op expression  */
#line 1124 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expr_node = *(yyvsp[-2].expression);
      if ((yyvsp[-2].expression)->expression->type() == ExprType::SUBSELECT)
      {
        (yyval.condition)->left_type = CON_SUBSELECT_T;
      }else if((yyvsp[-2].expression)->expression->type() == ExprType::SET){
        (yyval.condition)->left_type = CON_SET_T;
      }
      else if ((yyvsp[-2].expression)->attributes.size() > 0) {
        (yyval.condition)->left_type = CON_ATTR_T;
      } else {
        (yyval.condition)->left_type = CON_VALUE_T;
      }
      
      (yyval.condition)->right_expr_node = *(yyvsp[0].expression);
      if ((yyvsp[0].expression)->expression->type() == ExprType::SUBSELECT)
      {
        (yyval.condition)->right_type = CON_SUBSELECT_T;
      }else if((yyvsp[0].expression)->expression->type() == ExprType::SET){
        (yyval.condition)->right_type = CON_SET_T;
      }
      else if ((yyvsp[0].expression)->attributes.size() > 0) {
        (yyval.condition)->right_type = CON_ATTR_T;
      } else {
        (yyval.condition)->right_type = CON_VALUE_T;
      }
    }
#line 2907 "yacc_sql.cpp"
    break;

  case 120: /* condition: EXISTS expression  */
#line 1154 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->comp = CompOp::EXISTS_OP;
      ExprSqlNode * left = new ExprSqlNode;
      left->expression = new ValueExpr(Value(1));
      left->expression->set_name("1");
      (yyval.condition)->left_expr_node = *left;
      (yyval.condition)->left_type = CON_VALUE_T;
      (yyval.condition)->right_expr_node = *(yyvsp[0].expression);
      if ((yyvsp[0].expression)->expression->type() == ExprType::SUBSELECT)
      {
        (yyval.condition)->right_type = CON_SUBSELECT_T;
      }
      else
        return -1; /// exists 目前只考虑后面是子查询语句的情况
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 121: /* condition: NOT EXISTS expression  */
#line 1171 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->comp = CompOp::NOT_EXISTS_OP;
      ExprSqlNode * left = new ExprSqlNode;
      left->expression = new ValueExpr(Value(1));
      left->expression->set_name("1");
      (yyval.condition)->left_expr_node = *left;
      (yyval.condition)->left_type = CON_VALUE_T;
      (yyval.condition)->right_expr_node = *(yyvsp[0].expression);
      if ((yyvsp[0].expression)->expression->type() == ExprType::SUBSELECT)
      {
        (yyval.condition)->right_type = CON_SUBSELECT_T;
      }
      else
        return -1; /// exists 目前只考虑后面是子查询语句的情况
    }
#line 2949 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: EQ  */
#line 1238 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2955 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: LT  */
#line 1239 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2961 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: GT  */
#line 1240 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2967 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: LE  */
#line 1241 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2973 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: GE  */
#line 1242 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2979 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: NE  */
#line 1243 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2985 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: LIKE  */
#line 1244 "yacc_sql.y"
           {(yyval.comp) = LIKE_OP;}
#line 2991 "yacc_sql.cpp"
    break;

  case 129: /* comp_op: NOT LIKE  */
#line 1245 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP;}
#line 2997 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: IS  */
#line 1246 "yacc_sql.y"
         { (yyval.comp) = IS_OP;}
#line 3003 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: IS NOT  */
#line 1247 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_OP;}
#line 3009 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: IN  */
#line 1248 "yacc_sql.y"
         {(yyval.comp) = IN_OP;}
#line 3015 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: NOT IN  */
#line 1249 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP;}
#line 3021 "yacc_sql.cpp"
    break;

  case 134: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1254 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3035 "yacc_sql.cpp"
    break;

  case 135: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1267 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3044 "yacc_sql.cpp"
    break;

  case 136: /* set_variable_stmt: SET ID EQ value  */
#line 1275 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3056 "yacc_sql.cpp"
    break;


#line 3060 "yacc_sql.cpp"

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

#line 1287 "yacc_sql.y"

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
