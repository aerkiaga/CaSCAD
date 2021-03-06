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
    extern int yyparse();
    extern int yylex();
    extern void yyerror(char const *msg);
    ast_t outp;

#line 83 "parser.c"

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
#line 13 "parser.y"

    int i;
    double d;
    char *s;
    ast_t a;

#line 197 "parser.c"

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
  YYSYMBOL_module_call = 68,               /* module_call  */
  YYSYMBOL_assignment = 69,                /* assignment  */
  YYSYMBOL_include_statement = 70,         /* include_statement  */
  YYSYMBOL_use_statement = 71,             /* use_statement  */
  YYSYMBOL_import_path = 72                /* import_path  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 20 "parser.y"


#line 298 "parser.c"


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
#define YYLAST   727

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

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
static const yytype_int16 yyrline[] =
{
       0,   102,   102,   106,   107,   108,   112,   113,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   128,   130,
     134,   135,   136,   137,   138,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   176,   177,   178,   179,
     183,   184,   185,   188,   191,   194,   200,   204,   208,   212,
     216,   217,   218,   222,   223,   225,   226,   228,   232,   233,
     234,   235,   236,   240,   241,   242,   246,   250,   254,   258,
     262,   266,   267
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
  "module_call", "assignment", "include_statement", "use_statement",
  "import_path", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -82,     2,   231,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -44,   -42,     1,     5,     6,     9,    10,   -82,   276,
     276,   276,   276,   276,    37,    39,   -82,   -82,   265,   -23,
     -23,    38,    43,   195,   -30,   -30,   -30,   218,   195,   -82,
     -24,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,    27,
      27,   -82,   -82,   -82,   -82,   195,   149,   195,   195,   -82,
      45,    46,   458,     8,   -82,   195,   -82,    17,    67,    73,
      69,    70,    41,   341,    71,    82,   617,   276,     4,    78,
      91,    90,   482,   411,   103,    -4,    18,    80,    27,   218,
     -82,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   195,   -82,   -82,   -82,
     617,   -82,   -30,   -82,   -82,   218,   -82,   218,   -82,    27,
      72,    27,   276,   -82,   195,   195,   505,   195,   172,   -82,
      98,    99,   528,    20,    20,    80,    80,    20,    20,   692,
     692,   692,   692,   675,   675,   656,   637,   434,   -82,   -82,
     -82,   -82,   195,   -82,   -82,   388,   551,   -82,   312,   -82,
     617,   195,   -82,   -82,   195,   365,   195,   -82,   -82,   -82,
     195,   617,   617,   -82,   574,   597,   -82,   -82
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     6,    21,    22,    24,    23,    91,
      91,     0,     0,     0,     0,     0,     0,     0,     4,     0,
       0,     0,     0,     0,    20,     0,    19,     5,     0,    89,
      90,     0,     0,     0,    83,     0,    83,    78,     0,    11,
      12,    14,    15,    16,     9,     8,    10,     7,    92,    73,
      73,    51,    52,    58,    59,     0,    70,     0,     0,    50,
       0,    25,     0,    53,    47,     0,    26,     0,     0,    84,
       0,     0,    25,    79,     0,    80,    88,     0,    74,     0,
      75,     0,     0,    71,     0,     0,    44,    43,    73,    78,
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,    56,    57,
      55,    67,    83,    68,    69,    78,    87,    78,    13,    73,
       0,    73,     0,    27,     0,     0,     0,     0,     0,    60,
       0,     0,     0,    39,    41,    37,    38,    40,    42,    33,
      34,    35,    36,    31,    32,    30,    29,     0,    85,    81,
      82,    76,     0,    77,    18,     0,     0,    62,     0,    61,
      72,     0,    86,    45,     0,     0,     0,    48,    63,    64,
       0,    54,    28,    17,     0,     0,    49,    65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -82,   -82,   -82,   -82,    19,   -82,   -33,   -82,   -82,    28,
      57,   -82,     7,   -82,   -43,   -81,   -35,   -82,   -82,    51,
     -82,   -82,   107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    28,    18,    19,    73,    63,    64,    20,
      21,    22,    65,    85,    79,    74,    68,    66,    24,    25,
      26,    27,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      62,    71,     3,   128,    31,    76,    32,    81,   131,    23,
     129,   119,    33,   108,   109,    48,    34,    35,    67,    77,
      36,    37,    82,    83,    86,    87,    23,    23,    23,    23,
      23,    91,   110,    91,   149,    23,   150,    38,    39,    40,
      41,    42,    43,    38,    97,   130,    44,    47,    45,    49,
      38,   126,    89,   107,    50,   107,    88,    89,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,    38,    78,   151,   148,   153,   111,
     112,   113,   114,   116,    23,    69,    70,    69,    75,   117,
     120,   155,   156,    91,   158,   160,   118,    92,   121,    93,
      80,    80,   122,    96,    97,   152,    51,    52,    53,    54,
     161,   162,   127,    84,    55,   107,    56,    30,     0,   165,
       0,    57,     0,     0,     0,    58,     0,     0,   171,    23,
       0,   172,     0,   174,     0,     0,     0,   175,     0,    80,
      75,   154,    59,    60,     0,    13,     0,     0,     0,    16,
     125,    61,    51,    52,    53,    54,     0,     0,     0,     0,
      55,     0,    56,    69,     0,     0,    75,    57,    75,     0,
      80,    58,    80,     0,     0,    51,    52,    53,    54,     0,
       0,     0,     0,    55,     0,    56,   159,     0,    59,    60,
      57,     0,     0,    14,    58,    16,     0,    61,    51,    52,
      53,    54,     0,     0,     0,     0,    55,     0,    56,     0,
       0,    59,    60,    57,     0,     0,     0,    58,    16,     0,
      61,    51,    52,    53,    54,     0,     0,     0,     0,    55,
       0,    56,     0,     0,    59,    60,    57,     0,     0,     0,
      58,    16,     0,    61,     0,     0,     4,     0,     5,     6,
       7,     8,     0,     0,     0,     0,     0,    59,    60,     0,
       0,     0,     0,     0,    16,     0,    72,     9,    10,     0,
       0,    11,    12,    13,     0,    14,    15,    16,     0,    17,
       4,    46,     5,     6,     7,     8,     0,     0,     0,     0,
       0,     4,     0,     5,     6,     7,     8,     0,     0,     0,
       0,     9,     0,     0,     0,    11,    12,    13,     0,    14,
      15,    16,     9,    17,     0,     0,    11,    12,    13,     0,
      14,    15,    16,     0,    17,    91,   169,     0,     0,    92,
       0,    93,     0,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     0,   106,   107,   115,     0,
       0,     0,     0,     0,    91,   170,     0,     0,    92,     0,
      93,     0,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   173,   106,   107,     0,    91,     0,
       0,     0,    92,     0,    93,     0,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   166,   106,
     107,    91,   167,     0,     0,    92,     0,    93,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   124,   106,   107,    91,     0,     0,     0,    92,     0,
      93,     0,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   164,   106,   107,    91,     0,     0,
       0,    92,     0,    93,     0,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     0,   106,   107,
      90,    91,     0,     0,     0,    92,     0,    93,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,   106,   107,   123,    91,     0,     0,     0,    92,
       0,    93,     0,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     0,   106,   107,    91,   157,
       0,     0,    92,     0,    93,     0,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,     0,   106,
     107,    91,   163,     0,     0,    92,     0,    93,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,   106,   107,    91,   168,     0,     0,    92,     0,
      93,     0,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     0,   106,   107,    91,   176,     0,
       0,    92,     0,    93,     0,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     0,   106,   107,
      91,   177,     0,     0,    92,     0,    93,     0,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
      91,   106,   107,     0,    92,     0,    93,     0,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
      91,   106,   107,     0,    92,     0,    93,     0,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,    91,
       0,     0,   107,    92,     0,    93,     0,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     0,    91,     0,
       0,   107,    92,     0,    93,     0,    94,    95,    96,    97,
      98,    99,   100,   101,     0,    91,     0,     0,     0,    92,
     107,    93,     0,    94,    95,    96,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107
};

static const yytype_int16 yycheck[] =
{
      33,    36,     0,     7,    48,    38,    48,    50,    89,     2,
      14,     7,    11,     5,     6,    38,    11,    11,    48,    43,
      11,    11,    55,    56,    57,    58,    19,    20,    21,    22,
      23,    13,    65,    13,   115,    28,   117,    33,    19,    20,
      21,    22,    23,    33,    24,    88,     9,    28,     9,    11,
      33,    84,    11,    35,    11,    35,    11,    11,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    33,    48,   119,   112,   121,    12,
       7,    12,    12,    12,    77,    34,    35,    36,    37,     7,
      12,   124,   125,    13,   127,   128,    77,    17,     7,    19,
      49,    50,    12,    23,    24,    33,     3,     4,     5,     6,
      12,    12,    84,    56,    11,    35,    13,    10,    -1,   152,
      -1,    18,    -1,    -1,    -1,    22,    -1,    -1,   161,   122,
      -1,   164,    -1,   166,    -1,    -1,    -1,   170,    -1,    88,
      89,   122,    39,    40,    -1,    42,    -1,    -1,    -1,    46,
      47,    48,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      11,    -1,    13,   112,    -1,    -1,   115,    18,   117,    -1,
     119,    22,   121,    -1,    -1,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,    11,    -1,    13,    14,    -1,    39,    40,
      18,    -1,    -1,    44,    22,    46,    -1,    48,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    11,    -1,    13,    -1,
      -1,    39,    40,    18,    -1,    -1,    -1,    22,    46,    -1,
      48,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    11,
      -1,    13,    -1,    -1,    39,    40,    18,    -1,    -1,    -1,
      22,    46,    -1,    48,    -1,    -1,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    48,    36,    37,    -1,
      -1,    40,    41,    42,    -1,    44,    45,    46,    -1,    48,
      15,    16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    15,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      45,    46,    36,    48,    -1,    -1,    40,    41,    42,    -1,
      44,    45,    46,    -1,    48,    13,    14,    -1,    -1,    17,
      -1,    19,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,     7,    -1,
      -1,    -1,    -1,    -1,    13,    43,    -1,    -1,    17,    -1,
      19,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     9,    34,    35,    -1,    13,    -1,
      -1,    -1,    17,    -1,    19,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    10,    34,
      35,    13,    14,    -1,    -1,    17,    -1,    19,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    10,    34,    35,    13,    -1,    -1,    -1,    17,    -1,
      19,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    10,    34,    35,    13,    -1,    -1,
      -1,    17,    -1,    19,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      12,    13,    -1,    -1,    -1,    17,    -1,    19,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    13,    14,
      -1,    -1,    17,    -1,    19,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    13,    14,    -1,    -1,    17,    -1,    19,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    13,    14,    -1,    -1,    17,    -1,
      19,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    13,    14,    -1,
      -1,    17,    -1,    19,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      13,    14,    -1,    -1,    17,    -1,    19,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      13,    34,    35,    -1,    17,    -1,    19,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      13,    34,    35,    -1,    17,    -1,    19,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    13,
      -1,    -1,    35,    17,    -1,    19,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    13,    -1,
      -1,    35,    17,    -1,    19,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    13,    -1,    -1,    -1,    17,
      35,    19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    52,     0,    15,    17,    18,    19,    20,    36,
      37,    40,    41,    42,    44,    45,    46,    48,    54,    55,
      59,    60,    61,    62,    68,    69,    70,    71,    53,    72,
      72,    48,    48,    11,    11,    11,    11,    11,    33,    54,
      54,    54,    54,    54,     9,     9,    16,    54,    38,    11,
      11,     3,     4,     5,     6,    11,    13,    18,    22,    39,
      40,    48,    56,    57,    58,    62,    67,    48,    66,    69,
      69,    66,    48,    56,    65,    69,    56,    43,    48,    64,
      69,    64,    56,    56,    60,    63,    56,    56,    11,    11,
      12,    13,    17,    19,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    34,    35,     5,     6,
      56,    12,     7,    12,    12,     7,    12,     7,    54,     7,
      12,     7,    12,    12,    10,    47,    56,    59,     7,    14,
      64,    65,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    66,    65,
      65,    64,    33,    64,    54,    56,    56,    14,    56,    14,
      56,    12,    12,    14,    10,    56,    10,    14,    14,    14,
      43,    56,    56,     9,    56,    56,    14,    14
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    52,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    57,    57,    57,    57,
      58,    58,    58,    58,    58,    58,    59,    60,    61,    62,
      63,    63,    63,    64,    64,    64,    64,    64,    65,    65,
      65,    65,    65,    66,    66,    66,    67,    68,    69,    70,
      71,    72,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     0,     2,     2,     2,
       3,     2,     2,     4,     2,     2,     2,     8,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     2,     1,     5,     7,
       1,     1,     1,     1,     5,     2,     2,     2,     1,     1,
       3,     4,     4,     5,     5,     7,     4,     4,     4,     4,
       0,     1,     3,     0,     1,     1,     3,     3,     0,     1,
       1,     3,     3,     0,     1,     3,     4,     4,     3,     2,
       2,     0,     2
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
#line 102 "parser.y"
                   { outp = (yyvsp[0].a); }
#line 1480 "parser.c"
    break;

  case 3: /* top_statements: %empty  */
#line 106 "parser.y"
    { (yyval.a) = ast_statement_list(); }
#line 1486 "parser.c"
    break;

  case 4: /* top_statements: top_statements statement  */
#line 107 "parser.y"
                             { (yyval.a) = ast_append_child((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1492 "parser.c"
    break;

  case 5: /* top_statements: top_statements use_statement  */
#line 108 "parser.y"
                                 { (yyval.a) = ast_append_child((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1498 "parser.c"
    break;

  case 6: /* statements: %empty  */
#line 112 "parser.y"
    { (yyval.a) = ast_statement_list(); }
#line 1504 "parser.c"
    break;

  case 7: /* statements: statements statement  */
#line 113 "parser.y"
                         { (yyval.a) = ast_append_child((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1510 "parser.c"
    break;

  case 8: /* statement: assignment ';'  */
#line 117 "parser.y"
                   { (yyval.a) = (yyvsp[-1].a); }
#line 1516 "parser.c"
    break;

  case 9: /* statement: module_call ';'  */
#line 118 "parser.y"
                    { (yyval.a) = (yyvsp[-1].a); }
#line 1522 "parser.c"
    break;

  case 10: /* statement: '{' statements '}'  */
#line 119 "parser.y"
                       { (yyval.a) = (yyvsp[-1].a); }
#line 1528 "parser.c"
    break;

  case 11: /* statement: operator statement  */
#line 120 "parser.y"
                       { (yyval.a) = ast_append_child((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1534 "parser.c"
    break;

  case 12: /* statement: if_header statement  */
#line 121 "parser.y"
                                       { (yyval.a) = ast_if_statement((yyvsp[-1].a), (yyvsp[0].a), NULL); }
#line 1540 "parser.c"
    break;

  case 13: /* statement: if_header statement LEX_ELSE statement  */
#line 122 "parser.y"
                                           { (yyval.a) = ast_if_statement((yyvsp[-3].a), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1546 "parser.c"
    break;

  case 14: /* statement: for_header statement  */
#line 123 "parser.y"
                         { (yyval.a) = ast_for_statement((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1552 "parser.c"
    break;

  case 15: /* statement: intersection_for_header statement  */
#line 124 "parser.y"
                                      { (yyval.a) = ast_intersection_for_statement((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1558 "parser.c"
    break;

  case 16: /* statement: let_header statement  */
#line 125 "parser.y"
                         { (yyval.a) = ast_let_statement((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1564 "parser.c"
    break;

  case 17: /* statement: LEX_FUNCTION LEX_IDENTIFIER '(' proto_list ')' '=' expression ';'  */
#line 127 "parser.y"
        { (yyval.a) = ast_bind_statement(strdup((yyvsp[-6].s)), ast_function_literal((yyvsp[-4].a), (yyvsp[-1].a))); }
#line 1570 "parser.c"
    break;

  case 18: /* statement: LEX_MODULE LEX_IDENTIFIER '(' proto_list ')' statement  */
#line 129 "parser.y"
        { (yyval.a) = ast_bind_statement(strdup((yyvsp[-4].s)), ast_module_literal((yyvsp[-2].a), (yyvsp[0].a))); }
#line 1576 "parser.c"
    break;

  case 19: /* statement: include_statement  */
#line 130 "parser.y"
                      { (yyval.a) = (yyvsp[0].a); }
#line 1582 "parser.c"
    break;

  case 20: /* operator: module_call  */
#line 134 "parser.y"
                { (yyval.a) = ast_module_operator((yyvsp[0].a)); }
#line 1588 "parser.c"
    break;

  case 21: /* operator: '*'  */
#line 135 "parser.y"
        { (yyval.a) = ast_predefined_operator(OPERATOR_DISABLE); }
#line 1594 "parser.c"
    break;

  case 22: /* operator: '!'  */
#line 136 "parser.y"
        { (yyval.a) = ast_predefined_operator(OPERATOR_SHOWONLY); }
#line 1600 "parser.c"
    break;

  case 23: /* operator: '#'  */
#line 137 "parser.y"
        { (yyval.a) = ast_predefined_operator(OPERATOR_HIGHLIGHT); }
#line 1606 "parser.c"
    break;

  case 24: /* operator: '%'  */
#line 138 "parser.y"
        { (yyval.a) = ast_predefined_operator(OPERATOR_TRANSPARENT); }
#line 1612 "parser.c"
    break;

  case 25: /* expression: LEX_IDENTIFIER  */
#line 142 "parser.y"
                   { (yyval.a) = ast_identifier_expression((yyvsp[0].s)); }
#line 1618 "parser.c"
    break;

  case 26: /* expression: function_call  */
#line 143 "parser.y"
                  { (yyval.a) = (yyvsp[0].a); }
#line 1624 "parser.c"
    break;

  case 27: /* expression: '(' expression ')'  */
#line 144 "parser.y"
                       { (yyval.a) = (yyvsp[-1].a); }
#line 1630 "parser.c"
    break;

  case 28: /* expression: expression '?' expression ':' expression  */
#line 145 "parser.y"
                                                       { (yyval.a) = ast_if_expression((yyvsp[-4].a), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1636 "parser.c"
    break;

  case 29: /* expression: expression LEX_OR expression  */
#line 146 "parser.y"
                                 { (yyval.a) = ast_binary_expression(BINARY_OP_OR, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1642 "parser.c"
    break;

  case 30: /* expression: expression LEX_AND expression  */
#line 147 "parser.y"
                                  { (yyval.a) = ast_binary_expression(BINARY_OP_AND, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1648 "parser.c"
    break;

  case 31: /* expression: expression LEX_EQUAL expression  */
#line 148 "parser.y"
                                    { (yyval.a) = ast_binary_expression(BINARY_OP_EQUAL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1654 "parser.c"
    break;

  case 32: /* expression: expression LEX_NOT_EQUAL expression  */
#line 149 "parser.y"
                                        { (yyval.a) = ast_binary_expression(BINARY_OP_NOT_EQUAL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1660 "parser.c"
    break;

  case 33: /* expression: expression LEX_LESS_EQUAL expression  */
#line 150 "parser.y"
                                         { (yyval.a) = ast_binary_expression(BINARY_OP_LESS_EQUAL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1666 "parser.c"
    break;

  case 34: /* expression: expression '<' expression  */
#line 151 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_LESS, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1672 "parser.c"
    break;

  case 35: /* expression: expression LEX_MORE_EQUAL expression  */
#line 152 "parser.y"
                                         { (yyval.a) = ast_binary_expression(BINARY_OP_MORE_EQUAL, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1678 "parser.c"
    break;

  case 36: /* expression: expression '>' expression  */
#line 153 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_MORE, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1684 "parser.c"
    break;

  case 37: /* expression: expression '+' expression  */
#line 154 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_ADD, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1690 "parser.c"
    break;

  case 38: /* expression: expression '-' expression  */
#line 155 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_SUBTRACT, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1696 "parser.c"
    break;

  case 39: /* expression: expression '*' expression  */
#line 156 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_MULTIPLY, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1702 "parser.c"
    break;

  case 40: /* expression: expression '/' expression  */
#line 157 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_DIVIDE, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1708 "parser.c"
    break;

  case 41: /* expression: expression '%' expression  */
#line 158 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_MODULO, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1714 "parser.c"
    break;

  case 42: /* expression: expression '^' expression  */
#line 159 "parser.y"
                              { (yyval.a) = ast_binary_expression(BINARY_OP_RAISE, (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1720 "parser.c"
    break;

  case 43: /* expression: '-' expression  */
#line 160 "parser.y"
                   { (yyval.a) = ast_unary_expression(UNARY_OP_MINUS, (yyvsp[0].a)); }
#line 1726 "parser.c"
    break;

  case 44: /* expression: '!' expression  */
#line 161 "parser.y"
                   { (yyval.a) = ast_unary_expression(UNARY_OP_NOT, (yyvsp[0].a)); }
#line 1732 "parser.c"
    break;

  case 45: /* expression: expression '[' expression ']'  */
#line 162 "parser.y"
                                  { (yyval.a) = ast_vector_index((yyvsp[-3].a), (yyvsp[-1].a)); }
#line 1738 "parser.c"
    break;

  case 46: /* expression: expression LEX_DOT_INDEX  */
#line 163 "parser.y"
                             { (yyval.a) = ast_vector_index((yyvsp[-1].a), ast_number_literal((double) (yyvsp[0].i))); }
#line 1744 "parser.c"
    break;

  case 47: /* expression: vector  */
#line 164 "parser.y"
           { (yyval.a) = (yyvsp[0].a); }
#line 1750 "parser.c"
    break;

  case 48: /* expression: '[' expression ':' expression ']'  */
#line 165 "parser.y"
                                      { (yyval.a) = ast_range_literal((yyvsp[-3].a), ast_number_literal(1.0), (yyvsp[-1].a)); }
#line 1756 "parser.c"
    break;

  case 49: /* expression: '[' expression ':' expression ':' expression ']'  */
#line 166 "parser.y"
                                                     { (yyval.a) = ast_range_literal((yyvsp[-5].a), (yyvsp[-3].a), (yyvsp[-1].a)); }
#line 1762 "parser.c"
    break;

  case 50: /* expression: LEX_UNDEF  */
#line 167 "parser.y"
              { (yyval.a) = ast_undef_literal(); }
#line 1768 "parser.c"
    break;

  case 51: /* expression: LEX_NUM  */
#line 168 "parser.y"
            { (yyval.a) = ast_number_literal((yyvsp[0].d)); }
#line 1774 "parser.c"
    break;

  case 52: /* expression: LEX_BOOL  */
#line 169 "parser.y"
             { (yyval.a) = ast_bool_literal((yyvsp[0].i)); }
#line 1780 "parser.c"
    break;

  case 53: /* expression: string  */
#line 170 "parser.y"
           { (yyval.a) = ast_string_literal((yyvsp[0].s)); }
#line 1786 "parser.c"
    break;

  case 54: /* expression: LEX_FUNCTION '(' proto_list ')' expression  */
#line 171 "parser.y"
                                                                  { (yyval.a) = ast_function_literal((yyvsp[-2].a), (yyvsp[0].a)); }
#line 1792 "parser.c"
    break;

  case 55: /* expression: let_header expression  */
#line 172 "parser.y"
                                        { (yyval.a) = ast_let_expression((yyvsp[-1].a), (yyvsp[0].a)); }
#line 1798 "parser.c"
    break;

  case 56: /* string: string LEX_STR_FRAG  */
#line 176 "parser.y"
                        { (yyval.s) = append_string((yyvsp[-1].s), (yyvsp[0].s)); }
#line 1804 "parser.c"
    break;

  case 57: /* string: string LEX_STR_UNICODE  */
#line 177 "parser.y"
                           { (yyval.s) = append_string((yyvsp[-1].s), encode_utf8_escape((yyvsp[0].s))); }
#line 1810 "parser.c"
    break;

  case 58: /* string: LEX_STR_FRAG  */
#line 178 "parser.y"
                 { (yyval.s) = append_string(get_empty_string(), (yyvsp[0].s)); }
#line 1816 "parser.c"
    break;

  case 59: /* string: LEX_STR_UNICODE  */
#line 179 "parser.y"
                    { (yyval.s) = append_string(get_empty_string(), encode_utf8_escape((yyvsp[0].s))); }
#line 1822 "parser.c"
    break;

  case 60: /* vector: '[' expr_list ']'  */
#line 183 "parser.y"
                      { (yyval.a) = ast_vector_literal((yyvsp[-1].a)); }
#line 1828 "parser.c"
    break;

  case 61: /* vector: '[' expr_list ',' ']'  */
#line 184 "parser.y"
                          { (yyval.a) = ast_vector_literal((yyvsp[-2].a)); }
#line 1834 "parser.c"
    break;

  case 62: /* vector: '[' for_header expression ']'  */
#line 185 "parser.y"
                                  {
            (yyval.a) = ast_list_comprehension((yyvsp[-2].a), ast_bool_literal(1), 0, (yyvsp[-1].a));
        }
#line 1842 "parser.c"
    break;

  case 63: /* vector: '[' for_header LEX_EACH expression ']'  */
#line 188 "parser.y"
                                           {
            (yyval.a) = ast_list_comprehension((yyvsp[-3].a), ast_bool_literal(1), 1, (yyvsp[-1].a));
        }
#line 1850 "parser.c"
    break;

  case 64: /* vector: '[' for_header if_header expression ']'  */
#line 191 "parser.y"
                                                          {
            (yyval.a) = ast_list_comprehension((yyvsp[-3].a), (yyvsp[-2].a), 0, (yyvsp[-1].a));
        }
#line 1858 "parser.c"
    break;

  case 65: /* vector: '[' for_header if_header expression LEX_ELSE expression ']'  */
#line 194 "parser.y"
                                                               {
            (yyval.a) = ast_list_comprehension((yyvsp[-5].a), ast_bool_literal(1), 0, ast_if_expression((yyvsp[-4].a), (yyvsp[-3].a), (yyvsp[-1].a)));
        }
#line 1866 "parser.c"
    break;

  case 66: /* if_header: LEX_IF '(' expression ')'  */
#line 200 "parser.y"
                              { (yyval.a) = (yyvsp[-1].a); }
#line 1872 "parser.c"
    break;

  case 67: /* for_header: LEX_FOR '(' assignment_list ')'  */
#line 204 "parser.y"
                                    { (yyval.a) = (yyvsp[-1].a); }
#line 1878 "parser.c"
    break;

  case 68: /* intersection_for_header: LEX_INTERSECTION_FOR '(' assignment ')'  */
#line 208 "parser.y"
                                            { (yyval.a) = (yyvsp[-1].a); }
#line 1884 "parser.c"
    break;

  case 69: /* let_header: LEX_LET '(' assignment_list ')'  */
#line 212 "parser.y"
                                    { (yyval.a) = (yyvsp[-1].a); }
#line 1890 "parser.c"
    break;

  case 70: /* expr_list: %empty  */
#line 216 "parser.y"
    { (yyval.a) = ast_expression_list(); }
#line 1896 "parser.c"
    break;

  case 71: /* expr_list: expression  */
#line 217 "parser.y"
               { (yyval.a) = ast_append_child(ast_expression_list(), (yyvsp[0].a)); }
#line 1902 "parser.c"
    break;

  case 72: /* expr_list: expr_list ',' expression  */
#line 218 "parser.y"
                             { (yyval.a) = ast_append_child((yyvsp[-2].a), (yyvsp[0].a)); }
#line 1908 "parser.c"
    break;

  case 73: /* proto_list: %empty  */
#line 222 "parser.y"
    { (yyval.a) = ast_proto_list(); }
#line 1914 "parser.c"
    break;

  case 74: /* proto_list: LEX_IDENTIFIER  */
#line 224 "parser.y"
        { (yyval.a) = ast_append_child(ast_proto_list(), ast_bind_statement(strdup((yyvsp[0].s)), ast_undef_literal())); }
#line 1920 "parser.c"
    break;

  case 75: /* proto_list: assignment  */
#line 225 "parser.y"
               { (yyval.a) = ast_append_child(ast_proto_list(), (yyvsp[0].a)); }
#line 1926 "parser.c"
    break;

  case 76: /* proto_list: LEX_IDENTIFIER ',' proto_list  */
#line 227 "parser.y"
        { (yyval.a) = ast_append_child((yyvsp[0].a), ast_bind_statement(strdup((yyvsp[-2].s)), ast_undef_literal())); }
#line 1932 "parser.c"
    break;

  case 77: /* proto_list: assignment ',' proto_list  */
#line 228 "parser.y"
                              { (yyval.a) = ast_append_child((yyvsp[0].a), (yyvsp[-2].a)); }
#line 1938 "parser.c"
    break;

  case 78: /* param_list: %empty  */
#line 232 "parser.y"
    { (yyval.a) = ast_parameter_list(); }
#line 1944 "parser.c"
    break;

  case 79: /* param_list: expression  */
#line 233 "parser.y"
               { (yyval.a) = ast_append_child(ast_parameter_list(), (yyvsp[0].a)); }
#line 1950 "parser.c"
    break;

  case 80: /* param_list: assignment  */
#line 234 "parser.y"
               { (yyval.a) = ast_append_child(ast_parameter_list(), (yyvsp[0].a)); }
#line 1956 "parser.c"
    break;

  case 81: /* param_list: expression ',' param_list  */
#line 235 "parser.y"
                              { (yyval.a) = ast_append_child((yyvsp[0].a), (yyvsp[-2].a)); }
#line 1962 "parser.c"
    break;

  case 82: /* param_list: assignment ',' param_list  */
#line 236 "parser.y"
                              { (yyval.a) = ast_append_child((yyvsp[0].a), (yyvsp[-2].a)); }
#line 1968 "parser.c"
    break;

  case 83: /* assignment_list: %empty  */
#line 240 "parser.y"
    { (yyval.a) = ast_assignment_list(); }
#line 1974 "parser.c"
    break;

  case 84: /* assignment_list: assignment  */
#line 241 "parser.y"
               { (yyval.a) = ast_append_child(ast_assignment_list(), (yyvsp[0].a)); }
#line 1980 "parser.c"
    break;

  case 85: /* assignment_list: assignment ',' assignment_list  */
#line 242 "parser.y"
                                   { (yyval.a) = ast_append_child((yyvsp[0].a), (yyvsp[-2].a)); }
#line 1986 "parser.c"
    break;

  case 86: /* function_call: LEX_IDENTIFIER '(' param_list ')'  */
#line 246 "parser.y"
                                      { (yyval.a) = ast_function_call((yyvsp[-3].s), (yyvsp[-1].a)); }
#line 1992 "parser.c"
    break;

  case 87: /* module_call: LEX_IDENTIFIER '(' param_list ')'  */
#line 250 "parser.y"
                                      { (yyval.a) = ast_module_call((yyvsp[-3].s), (yyvsp[-1].a)); }
#line 1998 "parser.c"
    break;

  case 88: /* assignment: LEX_IDENTIFIER '=' expression  */
#line 254 "parser.y"
                                  { (yyval.a) = ast_bind_statement(strdup((yyvsp[-2].s)), (yyvsp[0].a)); }
#line 2004 "parser.c"
    break;

  case 89: /* include_statement: LEX_INCLUDE import_path  */
#line 258 "parser.y"
                            { (yyval.a) = ast_include_statement((yyvsp[0].s)); }
#line 2010 "parser.c"
    break;

  case 90: /* use_statement: LEX_USE import_path  */
#line 262 "parser.y"
                        { (yyval.a) = ast_use_statement((yyvsp[0].s)); }
#line 2016 "parser.c"
    break;

  case 91: /* import_path: %empty  */
#line 266 "parser.y"
    { (yyval.s) = get_empty_string(); }
#line 2022 "parser.c"
    break;

  case 92: /* import_path: import_path LEX_PATH_FRAG  */
#line 267 "parser.y"
                              { (yyval.s) = append_string((yyvsp[-1].s), (yyvsp[0].s)); }
#line 2028 "parser.c"
    break;


#line 2032 "parser.c"

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

#line 270 "parser.y"


ast_t parser_run() {
    yyrestart(NULL);
    yyparse();
    return outp;
}
