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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include "ast.h"
    #include "lexer.h"
    #include "strutils.h"
    #include <stdlib.h>
    #include <string.h>
    ast_t outp;

#line 80 "parser.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    LEX_NUM = 258,                 /* LEX_NUM  */
    LEX_BOOL = 259,                /* LEX_BOOL  */
    LEX_STR_FRAG = 260,            /* LEX_STR_FRAG  */
    LEX_STR_UNICODE = 261,         /* LEX_STR_UNICODE  */
    LEX_LESS_EQUAL = 262,          /* LEX_LESS_EQUAL  */
    LEX_MORE_EQUAL = 263,          /* LEX_MORE_EQUAL  */
    LEX_EQUAL = 264,               /* LEX_EQUAL  */
    LEX_NOT_EQUAL = 265,           /* LEX_NOT_EQUAL  */
    LEX_AND = 266,                 /* LEX_AND  */
    LEX_OR = 267,                  /* LEX_OR  */
    LEX_DOT_INDEX = 268,           /* LEX_DOT_INDEX  */
    LEX_INCLUDE = 269,             /* LEX_INCLUDE  */
    LEX_USE = 270,                 /* LEX_USE  */
    LEX_PATH_FRAG = 271,           /* LEX_PATH_FRAG  */
    LEX_UNDEF = 272,               /* LEX_UNDEF  */
    LEX_FUNCTION = 273,            /* LEX_FUNCTION  */
    LEX_MODULE = 274,              /* LEX_MODULE  */
    LEX_IF = 275,                  /* LEX_IF  */
    LEX_ELSE = 276,                /* LEX_ELSE  */
    LEX_FOR = 277,                 /* LEX_FOR  */
    LEX_INTERSECTION_FOR = 278,    /* LEX_INTERSECTION_FOR  */
    LEX_LET = 279,                 /* LEX_LET  */
    LEX_EACH = 280,                /* LEX_EACH  */
    LEX_IDENTIFIER = 281,          /* LEX_IDENTIFIER  */
    NON_ELSE = 282                 /* NON_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define LEX_NUM 258
#define LEX_BOOL 259
#define LEX_STR_FRAG 260
#define LEX_STR_UNICODE 261
#define LEX_LESS_EQUAL 262
#define LEX_MORE_EQUAL 263
#define LEX_EQUAL 264
#define LEX_NOT_EQUAL 265
#define LEX_AND 266
#define LEX_OR 267
#define LEX_DOT_INDEX 268
#define LEX_INCLUDE 269
#define LEX_USE 270
#define LEX_PATH_FRAG 271
#define LEX_UNDEF 272
#define LEX_FUNCTION 273
#define LEX_MODULE 274
#define LEX_IF 275
#define LEX_ELSE 276
#define LEX_FOR 277
#define LEX_INTERSECTION_FOR 278
#define LEX_LET 279
#define LEX_EACH 280
#define LEX_IDENTIFIER 281
#define NON_ELSE 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 10 "parser.y"

    int i;
    double d;
    char *s;
    ast_t a;

#line 194 "parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LEX_NUM = 3,                    /* LEX_NUM  */
  YYSYMBOL_LEX_BOOL = 4,                   /* LEX_BOOL  */
  YYSYMBOL_LEX_STR_FRAG = 5,               /* LEX_STR_FRAG  */
  YYSYMBOL_LEX_STR_UNICODE = 6,            /* LEX_STR_UNICODE  */
  YYSYMBOL_7_ = 7,                         /* ','  */
  YYSYMBOL_8_ = 8,                         /* '.'  */
  YYSYMBOL_9_ = 9,                         /* ';'  */
  YYSYMBOL_10_ = 10,                       /* ':'  */
  YYSYMBOL_11_ = 11,                       /* '('  */
  YYSYMBOL_12_ = 12,                       /* ')'  */
  YYSYMBOL_13_ = 13,                       /* '['  */
  YYSYMBOL_14_ = 14,                       /* ']'  */
  YYSYMBOL_15_ = 15,                       /* '{'  */
  YYSYMBOL_16_ = 16,                       /* '}'  */
  YYSYMBOL_17_ = 17,                       /* '*'  */
  YYSYMBOL_18_ = 18,                       /* '!'  */
  YYSYMBOL_19_ = 19,                       /* '%'  */
  YYSYMBOL_20_ = 20,                       /* '#'  */
  YYSYMBOL_21_ = 21,                       /* '+'  */
  YYSYMBOL_22_ = 22,                       /* '-'  */
  YYSYMBOL_23_ = 23,                       /* '/'  */
  YYSYMBOL_24_ = 24,                       /* '^'  */
  YYSYMBOL_LEX_LESS_EQUAL = 25,            /* LEX_LESS_EQUAL  */
  YYSYMBOL_26_ = 26,                       /* '<'  */
  YYSYMBOL_LEX_MORE_EQUAL = 27,            /* LEX_MORE_EQUAL  */
  YYSYMBOL_28_ = 28,                       /* '>'  */
  YYSYMBOL_LEX_EQUAL = 29,                 /* LEX_EQUAL  */
  YYSYMBOL_LEX_NOT_EQUAL = 30,             /* LEX_NOT_EQUAL  */
  YYSYMBOL_LEX_AND = 31,                   /* LEX_AND  */
  YYSYMBOL_LEX_OR = 32,                    /* LEX_OR  */
  YYSYMBOL_33_ = 33,                       /* '='  */
  YYSYMBOL_34_ = 34,                       /* '?'  */
  YYSYMBOL_LEX_DOT_INDEX = 35,             /* LEX_DOT_INDEX  */
  YYSYMBOL_LEX_INCLUDE = 36,               /* LEX_INCLUDE  */
  YYSYMBOL_LEX_USE = 37,                   /* LEX_USE  */
  YYSYMBOL_LEX_PATH_FRAG = 38,             /* LEX_PATH_FRAG  */
  YYSYMBOL_LEX_UNDEF = 39,                 /* LEX_UNDEF  */
  YYSYMBOL_LEX_FUNCTION = 40,              /* LEX_FUNCTION  */
  YYSYMBOL_LEX_MODULE = 41,                /* LEX_MODULE  */
  YYSYMBOL_LEX_IF = 42,                    /* LEX_IF  */
  YYSYMBOL_LEX_ELSE = 43,                  /* LEX_ELSE  */
  YYSYMBOL_LEX_FOR = 44,                   /* LEX_FOR  */
  YYSYMBOL_LEX_INTERSECTION_FOR = 45,      /* LEX_INTERSECTION_FOR  */
  YYSYMBOL_LEX_LET = 46,                   /* LEX_LET  */
  YYSYMBOL_LEX_EACH = 47,                  /* LEX_EACH  */
  YYSYMBOL_LEX_IDENTIFIER = 48,            /* LEX_IDENTIFIER  */
  YYSYMBOL_NON_ELSE = 49,                  /* NON_ELSE  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_input = 51,                     /* input  */
  YYSYMBOL_top_statements = 52,            /* top_statements  */
  YYSYMBOL_statements = 53,                /* statements  */
  YYSYMBOL_statement = 54,                 /* statement  */
  YYSYMBOL_operator = 55,                  /* operator  */
  YYSYMBOL_expression = 56,                /* expression  */
  YYSYMBOL_string = 57,                    /* string  */
  YYSYMBOL_vector = 58,                    /* vector  */
  YYSYMBOL_if_header = 59,                 /* if_header  */
  YYSYMBOL_for_header = 60,                /* for_header  */
  YYSYMBOL_intersection_for_header = 61,   /* intersection_for_header  */
  YYSYMBOL_let_header = 62,                /* let_header  */
  YYSYMBOL_expr_list = 63,                 /* expr_list  */
  YYSYMBOL_proto_list = 64,                /* proto_list  */
  YYSYMBOL_param_list = 65,                /* param_list  */
  YYSYMBOL_assignment_list = 66,           /* assignment_list  */
  YYSYMBOL_function_call = 67,             /* function_call  */
  YYSYMBOL_assignment = 68,                /* assignment  */
  YYSYMBOL_include_statement = 69,         /* include_statement  */
  YYSYMBOL_use_statement = 70,             /* use_statement  */
  YYSYMBOL_import_path = 71                /* import_path  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 17 "parser.y"


#line 294 "parser.c"


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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   669

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


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
       2,     2,     2,    18,     2,    20,     2,    19,     2,     2,
      11,    12,    17,    21,     7,    22,     8,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    10,     9,
      26,    33,    28,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    13,     2,    14,    24,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    15,     2,    16,     2,     2,     2,     2,
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
       5,     6,    25,    27,    29,    30,    31,    32,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    99,    99,   103,   104,   105,   109,   110,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   126,   129,
     133,   134,   135,   136,   137,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   174,   175,   176,   177,   181,
     182,   183,   186,   189,   192,   198,   202,   206,   210,   214,
     215,   219,   220,   223,   227,   228,   229,   233,   234,   238,
     242,   246,   250,   254,   255
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LEX_NUM", "LEX_BOOL",
  "LEX_STR_FRAG", "LEX_STR_UNICODE", "','", "'.'", "';'", "':'", "'('",
  "')'", "'['", "']'", "'{'", "'}'", "'*'", "'!'", "'%'", "'#'", "'+'",
  "'-'", "'/'", "'^'", "LEX_LESS_EQUAL", "'<'", "LEX_MORE_EQUAL", "'>'",
  "LEX_EQUAL", "LEX_NOT_EQUAL", "LEX_AND", "LEX_OR", "'='", "'?'",
  "LEX_DOT_INDEX", "LEX_INCLUDE", "LEX_USE", "LEX_PATH_FRAG", "LEX_UNDEF",
  "LEX_FUNCTION", "LEX_MODULE", "LEX_IF", "LEX_ELSE", "LEX_FOR",
  "LEX_INTERSECTION_FOR", "LEX_LET", "LEX_EACH", "LEX_IDENTIFIER",
  "NON_ELSE", "$accept", "input", "top_statements", "statements",
  "statement", "operator", "expression", "string", "vector", "if_header",
  "for_header", "intersection_for_header", "let_header", "expr_list",
  "proto_list", "param_list", "assignment_list", "function_call",
  "assignment", "include_statement", "use_statement", "import_path", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-44)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -44,     1,   216,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,   -36,   -35,    -1,    17,    18,    27,    -3,   -44,   261,
     261,   261,   261,   261,     5,    35,   -44,   -44,   250,     7,
       7,    51,    58,   182,   -44,    23,   -44,   -44,   182,   -44,
      29,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -44,   -44,   182,   131,   182,   182,   -44,
      72,    73,   417,    -2,   -44,   182,   -44,     4,    60,    82,
      30,    80,   576,   261,    90,   107,   441,   370,    85,    -5,
       8,   128,   -44,   -44,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     -44,   -44,   -44,   576,    23,   -44,   -44,   -44,   202,   -44,
     -44,    47,    66,   261,   -44,   182,   182,   464,   182,   151,
     -44,   116,   487,    50,    50,   128,   128,    50,    50,    87,
      87,    87,    87,   634,   634,   615,   596,   393,   -44,   576,
     -44,    60,   -44,   182,   -44,   347,   510,   -44,   297,   -44,
     576,   182,   -44,   182,   324,   182,   -44,   -44,   -44,   182,
     576,   576,   -44,   533,   556,   -44,   -44
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     6,    21,    22,    24,    23,    83,
      83,     0,     0,     0,     0,     0,     0,     0,     4,     0,
       0,     0,     0,     0,    20,     0,    19,     5,     0,    81,
      82,     0,     0,     0,    77,     0,    77,    74,     0,    10,
      12,    14,    15,    16,     9,     8,    11,     7,    84,    71,
      71,    50,    51,    57,    58,     0,    69,     0,     0,    49,
       0,     0,     0,    52,    46,     0,    25,     0,     0,     0,
       0,     0,    80,     0,     0,     0,     0,     0,     0,     0,
      43,    42,    71,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    55,    56,    54,     0,    66,    67,    68,     0,    79,
      13,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      59,     0,     0,    38,    40,    36,    37,    39,    41,    32,
      33,    34,    35,    30,    31,    29,    28,     0,    78,    75,
      76,    72,    73,     0,    18,     0,     0,    61,     0,    60,
      70,     0,    44,     0,     0,     0,    47,    62,    63,     0,
      53,    27,    17,     0,     0,    48,    64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -44,   -44,   -44,   -44,    45,   -44,   -38,   -44,   -44,    34,
      64,   -44,     3,   -44,   -43,   -44,    65,    13,   -29,   -44,
     -44,   119
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    28,    18,    19,    62,    63,    64,    20,
      21,    22,    65,    79,    74,    71,    67,    66,    25,    26,
      27,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      72,     3,   119,   101,   102,    23,    69,    75,    37,   120,
      33,   104,    31,    32,    44,    24,   105,    76,    77,    80,
      81,    84,    23,    23,    23,    23,    23,   103,    34,    35,
      38,    23,    24,    24,    24,    24,    24,   104,    36,   121,
     117,    24,   107,   100,    45,    48,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,    49,    84,    39,    40,    41,    42,    43,    50,
     139,    68,    73,    47,    90,   138,    23,   145,   146,   140,
     148,   150,   142,    82,    37,   100,    24,   108,    51,    52,
      53,    54,   109,    38,   106,   141,    55,   111,    56,   143,
      84,    70,   112,    57,    85,   154,    86,    58,    87,    88,
      89,    90,   118,   160,   111,   161,    23,   163,   110,   113,
      78,   164,   100,   111,    59,    60,    24,    13,   151,    30,
       0,    16,   116,    61,    51,    52,    53,    54,     0,     0,
       0,    84,    55,     0,    56,    85,     0,    86,     0,    57,
       0,    89,    90,    58,    51,    52,    53,    54,   144,     0,
       0,     0,    55,   100,    56,   149,     0,     0,     0,    57,
      59,    60,     0,    58,     0,    14,     0,    16,     0,    61,
       0,     0,     0,     0,     0,    51,    52,    53,    54,     0,
      59,    60,     0,    55,     0,    56,     0,    16,     0,    61,
      57,     0,     0,     0,    58,    51,    52,    53,    54,     0,
       0,     0,     0,    55,     0,    56,     0,     0,     0,     0,
      57,    59,    60,     0,    58,     0,     0,     0,    16,     0,
      61,     4,     0,     5,     6,     7,     8,     0,     0,     0,
       0,    59,    60,     0,     0,     0,     0,     0,    16,     0,
      17,     0,     9,    10,     0,     0,    11,    12,    13,     0,
      14,    15,    16,     0,    17,     4,    46,     5,     6,     7,
       8,     0,     0,     0,     0,     0,     4,     0,     5,     6,
       7,     8,     0,     0,     0,     0,     9,     0,     0,     0,
      11,    12,    13,     0,    14,    15,    16,     9,    17,     0,
       0,    11,    12,    13,     0,    14,    15,    16,     0,    17,
      84,   158,     0,     0,    85,     0,    86,     0,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
       0,    99,   100,   162,     0,     0,     0,    84,     0,     0,
     159,    85,     0,    86,     0,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,   155,    99,   100,
      84,   156,     0,     0,    85,     0,    86,     0,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     115,    99,   100,    84,     0,     0,     0,    85,     0,    86,
       0,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,   153,    99,   100,    84,     0,     0,     0,
      85,     0,    86,     0,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     0,    99,   100,    83,
      84,     0,     0,     0,    85,     0,    86,     0,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
       0,    99,   100,   114,    84,     0,     0,     0,    85,     0,
      86,     0,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,     0,    99,   100,    84,   147,     0,
       0,    85,     0,    86,     0,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,     0,    99,   100,
      84,   152,     0,     0,    85,     0,    86,     0,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
       0,    99,   100,    84,   157,     0,     0,    85,     0,    86,
       0,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     0,    99,   100,    84,   165,     0,     0,
      85,     0,    86,     0,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     0,    99,   100,    84,
     166,     0,     0,    85,     0,    86,     0,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    84,
      99,   100,     0,    85,     0,    86,     0,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    84,
      99,   100,     0,    85,     0,    86,     0,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    84,     0,
       0,   100,    85,     0,    86,     0,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,     0,    84,     0,     0,
     100,    85,     0,    86,     0,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,     0,     0,     0,     0,   100
};

static const yytype_int16 yycheck[] =
{
      38,     0,     7,     5,     6,     2,    35,    50,    11,    14,
      11,     7,    48,    48,     9,     2,    12,    55,    56,    57,
      58,    13,    19,    20,    21,    22,    23,    65,    11,    11,
      33,    28,    19,    20,    21,    22,    23,     7,    11,    82,
      78,    28,    12,    35,     9,    38,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    11,    13,    19,    20,    21,    22,    23,    11,
     108,    48,    43,    28,    24,   104,    73,   115,   116,   108,
     118,   119,   111,    11,    11,    35,    73,     7,     3,     4,
       5,     6,    12,    33,    12,    48,    11,     7,    13,    33,
      13,    36,    12,    18,    17,   143,    19,    22,    21,    22,
      23,    24,    78,   151,     7,   153,   113,   155,    73,    12,
      56,   159,    35,     7,    39,    40,   113,    42,    12,    10,
      -1,    46,    47,    48,     3,     4,     5,     6,    -1,    -1,
      -1,    13,    11,    -1,    13,    17,    -1,    19,    -1,    18,
      -1,    23,    24,    22,     3,     4,     5,     6,   113,    -1,
      -1,    -1,    11,    35,    13,    14,    -1,    -1,    -1,    18,
      39,    40,    -1,    22,    -1,    44,    -1,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
      39,    40,    -1,    11,    -1,    13,    -1,    46,    -1,    48,
      18,    -1,    -1,    -1,    22,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,
      18,    39,    40,    -1,    22,    -1,    -1,    -1,    46,    -1,
      48,    15,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    39,    40,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      48,    -1,    36,    37,    -1,    -1,    40,    41,    42,    -1,
      44,    45,    46,    -1,    48,    15,    16,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    -1,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    45,    46,    36,    48,    -1,
      -1,    40,    41,    42,    -1,    44,    45,    46,    -1,    48,
      13,    14,    -1,    -1,    17,    -1,    19,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,     9,    -1,    -1,    -1,    13,    -1,    -1,
      43,    17,    -1,    19,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    10,    34,    35,
      13,    14,    -1,    -1,    17,    -1,    19,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      10,    34,    35,    13,    -1,    -1,    -1,    17,    -1,    19,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    10,    34,    35,    13,    -1,    -1,    -1,
      17,    -1,    19,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    12,    13,    -1,    -1,    -1,    17,    -1,
      19,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    13,    14,    -1,
      -1,    17,    -1,    19,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      13,    14,    -1,    -1,    17,    -1,    19,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    13,    14,    -1,    -1,    17,    -1,    19,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    13,    14,    -1,    -1,
      17,    -1,    19,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    13,
      14,    -1,    -1,    17,    -1,    19,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    13,
      34,    35,    -1,    17,    -1,    19,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    13,
      34,    35,    -1,    17,    -1,    19,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    13,    -1,
      -1,    35,    17,    -1,    19,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    13,    -1,    -1,
      35,    17,    -1,    19,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    52,     0,    15,    17,    18,    19,    20,    36,
      37,    40,    41,    42,    44,    45,    46,    48,    54,    55,
      59,    60,    61,    62,    67,    68,    69,    70,    53,    71,
      71,    48,    48,    11,    11,    11,    11,    11,    33,    54,
      54,    54,    54,    54,     9,     9,    16,    54,    38,    11,
      11,     3,     4,     5,     6,    11,    13,    18,    22,    39,
      40,    48,    56,    57,    58,    62,    67,    66,    48,    68,
      66,    65,    56,    43,    64,    64,    56,    56,    60,    63,
      56,    56,    11,    12,    13,    17,    19,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    34,
      35,     5,     6,    56,     7,    12,    12,    12,     7,    12,
      54,     7,    12,    12,    12,    10,    47,    56,    59,     7,
      14,    64,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    68,    56,
      68,    48,    68,    33,    54,    56,    56,    14,    56,    14,
      56,    12,    14,    10,    56,    10,    14,    14,    14,    43,
      56,    56,     9,    56,    56,    14,    14
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    52,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    58,
      58,    58,    58,    58,    58,    59,    60,    61,    62,    63,
      63,    64,    64,    64,    65,    65,    65,    66,    66,    67,
      68,    69,    70,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     0,     2,     2,     2,
       2,     3,     2,     4,     2,     2,     2,     8,     6,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     4,     2,     1,     5,     7,     1,
       1,     1,     1,     5,     2,     2,     2,     1,     1,     3,
       4,     4,     5,     5,     7,     4,     4,     4,     4,     0,
       3,     0,     3,     3,     0,     3,     3,     0,     3,     4,
       3,     2,     2,     0,     2
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* input: top_statements  */
#line 99 "parser.y"
                   { outp = (yyvsp[0].a); }
#line 1457 "parser.c"
    break;

  case 3: /* top_statements: %empty  */
#line 103 "parser.y"
    { (yyval.a) = ast_statement_list(); }
#line 1463 "parser.c"
    break;

  case 4: /* top_statements: top_statements statement  */
#line 104 "parser.y"
                             { (yyval.a) = ast_append_child((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1469 "parser.c"
    break;

  case 5: /* top_statements: top_statements use_statement  */
#line 105 "parser.y"
                                 { (yyval.a) = ast_append_child((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1475 "parser.c"
    break;

  case 6: /* statements: %empty  */
#line 109 "parser.y"
    { (yyval.a) = ast_statement_list(); }
#line 1481 "parser.c"
    break;

  case 7: /* statements: statements statement  */
#line 110 "parser.y"
                         { (yyval.a) = ast_append_child((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1487 "parser.c"
    break;

  case 8: /* statement: assignment ';'  */
#line 114 "parser.y"
                   { (yyval.a) = (yyvsp[-1].a); }
#line 1493 "parser.c"
    break;

  case 9: /* statement: function_call ';'  */
#line 115 "parser.y"
                      { (yyval.a) = (yyvsp[-1].a); }
#line 1499 "parser.c"
    break;

  case 10: /* statement: operator statement  */
#line 116 "parser.y"
                       { (yyval.a) = ast_append_child((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1505 "parser.c"
    break;

  case 11: /* statement: '{' statements '}'  */
#line 117 "parser.y"
                       { (yyval.a) = (yyvsp[-1].a); }
#line 1511 "parser.c"
    break;

  case 12: /* statement: if_header statement  */
#line 118 "parser.y"
                                       { (yyval.a) = ast_if_statement((yyvsp[-1].a), (yyvsp[0].a), NULL); }
#line 1517 "parser.c"
    break;

  case 13: /* statement: if_header statement LEX_ELSE statement  */
#line 119 "parser.y"
                                           { (yyval.a) = ast_if_statement((yyvsp[-3].a), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1523 "parser.c"
    break;

  case 14: /* statement: for_header statement  */
#line 120 "parser.y"
                         { (yyval.a) = ast_for_statement((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1529 "parser.c"
    break;

  case 15: /* statement: intersection_for_header statement  */
#line 121 "parser.y"
                                      { (yyval.a) = ast_intersection_for_statement((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1535 "parser.c"
    break;

  case 16: /* statement: let_header statement  */
#line 122 "parser.y"
                         { (yyval.a) = ast_let_statement((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1541 "parser.c"
    break;

  case 17: /* statement: LEX_FUNCTION LEX_IDENTIFIER '(' proto_list ')' '=' expression ';'  */
#line 123 "parser.y"
                                                                      {
            ast_bind_statement(strdup((yyvsp[-6].s)), ast_function_literal((yyvsp[-4].a), (yyvsp[-1].a))); 
        }
#line 1549 "parser.c"
    break;

  case 18: /* statement: LEX_MODULE LEX_IDENTIFIER '(' proto_list ')' statement  */
#line 126 "parser.y"
                                                           {
            ast_bind_statement(strdup((yyvsp[-4].s)), ast_module_literal((yyvsp[-2].a), (yyvsp[0].a))); 
        }
#line 1557 "parser.c"
    break;

  case 19: /* statement: include_statement  */
#line 129 "parser.y"
                      { (yyval.a) = (yyvsp[0].a); }
#line 1563 "parser.c"
    break;

  case 20: /* operator: function_call  */
#line 133 "parser.y"
                  { (yyval.a) = ast_function_operator((yyvsp[0].a)); }
#line 1569 "parser.c"
    break;

  case 21: /* operator: '*'  */
#line 134 "parser.y"
        { (yyval.a) = ast_predefined_operator(OPERATOR_DISABLE); }
#line 1575 "parser.c"
    break;

  case 22: /* operator: '!'  */
#line 135 "parser.y"
        { (yyval.a) = ast_predefined_operator(OPERATOR_SHOWONLY); }
#line 1581 "parser.c"
    break;

  case 23: /* operator: '#'  */
#line 136 "parser.y"
        { (yyval.a) = ast_predefined_operator(OPERATOR_HIGHLIGHT); }
#line 1587 "parser.c"
    break;

  case 24: /* operator: '%'  */
#line 137 "parser.y"
        { (yyval.a) = ast_predefined_operator(OPERATOR_TRANSPARENT); }
#line 1593 "parser.c"
    break;

  case 25: /* expression: function_call  */
#line 141 "parser.y"
                  { (yyval.a) = (yyvsp[0].a); }
#line 1599 "parser.c"
    break;

  case 26: /* expression: '(' expression ')'  */
#line 142 "parser.y"
                       { (yyval.a) = (yyvsp[-1].a); }
#line 1605 "parser.c"
    break;

  case 27: /* expression: expression '?' expression ':' expression  */
#line 143 "parser.y"
                                                       { (yyval.a) = ast_if_expression((yyvsp[-4].a), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1611 "parser.c"
    break;

  case 28: /* expression: expression LEX_OR expression  */
#line 144 "parser.y"
                                 { (yyval.a) = ast_binary_expression(BINARY_OP_OR, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1617 "parser.c"
    break;

  case 29: /* expression: expression LEX_AND expression  */
#line 145 "parser.y"
                                  { (yyval.a) = ast_binary_expression(BINARY_OP_AND, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1623 "parser.c"
    break;

  case 30: /* expression: expression LEX_EQUAL expression  */
#line 146 "parser.y"
                                    { (yyval.a) = ast_binary_expression(BINARY_OP_EQUAL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1629 "parser.c"
    break;

  case 31: /* expression: expression LEX_NOT_EQUAL expression  */
#line 147 "parser.y"
                                        { (yyval.a) = ast_binary_expression(BINARY_OP_NOT_EQUAL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1635 "parser.c"
    break;

  case 32: /* expression: expression LEX_LESS_EQUAL expression  */
#line 148 "parser.y"
                                         { (yyval.a) = ast_binary_expression(BINARY_OP_LESS_EQUAL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1641 "parser.c"
    break;

  case 33: /* expression: expression '<' expression  */
#line 149 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_LESS, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1647 "parser.c"
    break;

  case 34: /* expression: expression LEX_MORE_EQUAL expression  */
#line 150 "parser.y"
                                         { (yyval.a) = ast_binary_expression(BINARY_OP_MORE_EQUAL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1653 "parser.c"
    break;

  case 35: /* expression: expression '>' expression  */
#line 151 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_MORE, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1659 "parser.c"
    break;

  case 36: /* expression: expression '+' expression  */
#line 152 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_ADD, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1665 "parser.c"
    break;

  case 37: /* expression: expression '-' expression  */
#line 153 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_SUBTRACT, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1671 "parser.c"
    break;

  case 38: /* expression: expression '*' expression  */
#line 154 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_MULTIPLY, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1677 "parser.c"
    break;

  case 39: /* expression: expression '/' expression  */
#line 155 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_DIVIDE, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1683 "parser.c"
    break;

  case 40: /* expression: expression '%' expression  */
#line 156 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_MODULO, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1689 "parser.c"
    break;

  case 41: /* expression: expression '^' expression  */
#line 157 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_RAISE, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1695 "parser.c"
    break;

  case 42: /* expression: '-' expression  */
#line 158 "parser.y"
                   { (yyval.a) = ast_unary_expression(UNARY_OP_MINUS, (yyvsp[0].a)); }
#line 1701 "parser.c"
    break;

  case 43: /* expression: '!' expression  */
#line 159 "parser.y"
                   { (yyval.a) = ast_unary_expression(UNARY_OP_NOT, (yyvsp[0].a)); }
#line 1707 "parser.c"
    break;

  case 44: /* expression: expression '[' expression ']'  */
#line 160 "parser.y"
                                  { (yyval.a) = ast_vector_index((yyvsp[-3].a), (yyvsp[-1].a)); }
#line 1713 "parser.c"
    break;

  case 45: /* expression: expression LEX_DOT_INDEX  */
#line 161 "parser.y"
                             { (yyval.a) = ast_vector_index((yyvsp[-1].a), ast_number_literal((double) (yyvsp[0].i))); }
#line 1719 "parser.c"
    break;

  case 46: /* expression: vector  */
#line 162 "parser.y"
           { (yyval.a) = (yyvsp[0].a); }
#line 1725 "parser.c"
    break;

  case 47: /* expression: '[' expression ':' expression ']'  */
#line 163 "parser.y"
                                      { (yyval.a) = ast_range_literal((yyvsp[-3].a), ast_number_literal(1.0), (yyvsp[-1].a)); }
#line 1731 "parser.c"
    break;

  case 48: /* expression: '[' expression ':' expression ':' expression ']'  */
#line 164 "parser.y"
                                                     { (yyval.a) = ast_range_literal((yyvsp[-5].a), (yyvsp[-3].a), (yyvsp[-1].a)); }
#line 1737 "parser.c"
    break;

  case 49: /* expression: LEX_UNDEF  */
#line 165 "parser.y"
              { (yyval.a) = ast_undef_literal(); }
#line 1743 "parser.c"
    break;

  case 50: /* expression: LEX_NUM  */
#line 166 "parser.y"
            { (yyval.a) = ast_number_literal((yyvsp[0].d)); }
#line 1749 "parser.c"
    break;

  case 51: /* expression: LEX_BOOL  */
#line 167 "parser.y"
             { (yyval.a) = ast_bool_literal((yyvsp[0].i)); }
#line 1755 "parser.c"
    break;

  case 52: /* expression: string  */
#line 168 "parser.y"
           { (yyval.a) = ast_string_literal((yyvsp[0].s)); }
#line 1761 "parser.c"
    break;

  case 53: /* expression: LEX_FUNCTION '(' proto_list ')' expression  */
#line 169 "parser.y"
                                                                  { (yyval.a) = ast_function_literal((yyvsp[-2].a), (yyvsp[0].a)); }
#line 1767 "parser.c"
    break;

  case 54: /* expression: let_header expression  */
#line 170 "parser.y"
                                        { (yyval.a) = ast_let_expression((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1773 "parser.c"
    break;

  case 55: /* string: string LEX_STR_FRAG  */
#line 174 "parser.y"
                        { (yyval.s) = append_string((yyvsp[-1].s), (yyvsp[0].s)); }
#line 1779 "parser.c"
    break;

  case 56: /* string: string LEX_STR_UNICODE  */
#line 175 "parser.y"
                           { (yyval.s) = append_string((yyvsp[-1].s), encode_utf8_escape((yyvsp[0].s))); }
#line 1785 "parser.c"
    break;

  case 57: /* string: LEX_STR_FRAG  */
#line 176 "parser.y"
                 { (yyval.s) = append_string(get_empty_string(), (yyvsp[0].s)); }
#line 1791 "parser.c"
    break;

  case 58: /* string: LEX_STR_UNICODE  */
#line 177 "parser.y"
                    { (yyval.s) = append_string(get_empty_string(), encode_utf8_escape((yyvsp[0].s))); }
#line 1797 "parser.c"
    break;

  case 59: /* vector: '[' expr_list ']'  */
#line 181 "parser.y"
                      { (yyval.a) = ast_vector_literal((yyvsp[-1].a)); }
#line 1803 "parser.c"
    break;

  case 60: /* vector: '[' expr_list ',' ']'  */
#line 182 "parser.y"
                          { (yyval.a) = ast_vector_literal((yyvsp[-2].a)); }
#line 1809 "parser.c"
    break;

  case 61: /* vector: '[' for_header expression ']'  */
#line 183 "parser.y"
                                  {
            (yyval.a) = ast_list_comprehension((yyvsp[-2].a), ast_bool_literal(1), 0, (yyvsp[-1].a));
        }
#line 1817 "parser.c"
    break;

  case 62: /* vector: '[' for_header LEX_EACH expression ']'  */
#line 186 "parser.y"
                                           {
            (yyval.a) = ast_list_comprehension((yyvsp[-3].a), ast_bool_literal(1), 1, (yyvsp[-1].a));
        }
#line 1825 "parser.c"
    break;

  case 63: /* vector: '[' for_header if_header expression ']'  */
#line 189 "parser.y"
                                                          {
            (yyval.a) = ast_list_comprehension((yyvsp[-3].a), (yyvsp[-2].a), 0, (yyvsp[-1].a));
        }
#line 1833 "parser.c"
    break;

  case 64: /* vector: '[' for_header if_header expression LEX_ELSE expression ']'  */
#line 192 "parser.y"
                                                               {
            (yyval.a) = ast_list_comprehension((yyvsp[-5].a), ast_bool_literal(1), 0, ast_if_expression((yyvsp[-4].a), (yyvsp[-3].a), (yyvsp[-1].a)));
        }
#line 1841 "parser.c"
    break;

  case 65: /* if_header: LEX_IF '(' expression ')'  */
#line 198 "parser.y"
                              { (yyval.a) = (yyvsp[-1].a); }
#line 1847 "parser.c"
    break;

  case 66: /* for_header: LEX_FOR '(' assignment_list ')'  */
#line 202 "parser.y"
                                    { (yyval.a) = (yyvsp[-1].a); }
#line 1853 "parser.c"
    break;

  case 67: /* intersection_for_header: LEX_INTERSECTION_FOR '(' assignment ')'  */
#line 206 "parser.y"
                                            { (yyval.a) = (yyvsp[-1].a); }
#line 1859 "parser.c"
    break;

  case 68: /* let_header: LEX_LET '(' assignment_list ')'  */
#line 210 "parser.y"
                                    { (yyval.a) = (yyvsp[-1].a); }
#line 1865 "parser.c"
    break;

  case 69: /* expr_list: %empty  */
#line 214 "parser.y"
    { (yyval.a) = ast_expression_list(); }
#line 1871 "parser.c"
    break;

  case 70: /* expr_list: expr_list ',' expression  */
#line 215 "parser.y"
                             { (yyval.a) = ast_append_child((yyvsp[-2].a), (yyvsp[0].a)); }
#line 1877 "parser.c"
    break;

  case 71: /* proto_list: %empty  */
#line 219 "parser.y"
    { (yyval.a) = ast_proto_list(); }
#line 1883 "parser.c"
    break;

  case 72: /* proto_list: proto_list ',' LEX_IDENTIFIER  */
#line 220 "parser.y"
                                  {
            (yyval.a) = ast_append_child((yyvsp[-2].a), ast_bind_statement(strdup((yyvsp[0].s)), ast_undef_literal()));
        }
#line 1891 "parser.c"
    break;

  case 73: /* proto_list: proto_list ',' assignment  */
#line 223 "parser.y"
                              { (yyval.a) = ast_append_child((yyvsp[-2].a), (yyvsp[0].a)); }
#line 1897 "parser.c"
    break;

  case 74: /* param_list: %empty  */
#line 227 "parser.y"
    { (yyval.a) = ast_parameter_list(); }
#line 1903 "parser.c"
    break;

  case 75: /* param_list: param_list ',' expression  */
#line 228 "parser.y"
                              { (yyval.a) = ast_append_child((yyvsp[-2].a), (yyvsp[0].a)); }
#line 1909 "parser.c"
    break;

  case 76: /* param_list: param_list ',' assignment  */
#line 229 "parser.y"
                              { (yyval.a) = ast_append_child((yyvsp[-2].a), (yyvsp[0].a)); }
#line 1915 "parser.c"
    break;

  case 77: /* assignment_list: %empty  */
#line 233 "parser.y"
    { (yyval.a) = ast_assignment_list(); }
#line 1921 "parser.c"
    break;

  case 78: /* assignment_list: assignment_list ',' assignment  */
#line 234 "parser.y"
                                   { (yyval.a) = ast_append_child((yyvsp[-2].a), (yyvsp[0].a)); }
#line 1927 "parser.c"
    break;

  case 79: /* function_call: LEX_IDENTIFIER '(' param_list ')'  */
#line 238 "parser.y"
                                      { (yyval.a) = ast_function_call((yyvsp[-3].s), (yyvsp[-1].a)); }
#line 1933 "parser.c"
    break;

  case 80: /* assignment: LEX_IDENTIFIER '=' expression  */
#line 242 "parser.y"
                                  { (yyval.a) = ast_bind_statement(strdup((yyvsp[-2].s)), (yyvsp[0].a)); }
#line 1939 "parser.c"
    break;

  case 81: /* include_statement: LEX_INCLUDE import_path  */
#line 246 "parser.y"
                            { (yyval.a) = ast_include_statement((yyvsp[0].s)); }
#line 1945 "parser.c"
    break;

  case 82: /* use_statement: LEX_USE import_path  */
#line 250 "parser.y"
                        { (yyval.a) = ast_use_statement((yyvsp[0].s)); }
#line 1951 "parser.c"
    break;

  case 83: /* import_path: %empty  */
#line 254 "parser.y"
    { (yyval.s) = get_empty_string(); }
#line 1957 "parser.c"
    break;

  case 84: /* import_path: import_path LEX_PATH_FRAG  */
#line 255 "parser.y"
                              { (yyval.s) = append_string((yyvsp[-1].s), (yyvsp[0].s)); }
#line 1963 "parser.c"
    break;


#line 1967 "parser.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 258 "parser.y"


ast_t parser_run() {
    yyparse();
    return outp;
}
