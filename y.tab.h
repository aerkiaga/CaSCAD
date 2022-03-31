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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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

#line 128 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
