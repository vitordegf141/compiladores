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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    KW_CARA = 258,
    KW_INTE = 259,
    KW_REAL = 260,
    KW_SE = 261,
    KW_ENTAUM = 262,
    KW_SENAUM = 263,
    KW_ENQUANTO = 264,
    KW_ENTRADA = 265,
    KW_ESCREVA = 266,
    KW_RETORNE = 267,
    OPERATOR_LE = 268,
    OPERATOR_GE = 269,
    OPERATOR_EQ = 270,
    OPERATOR_DIF = 271,
    TK_IDENTIFIER = 272,
    LIT_INTEIRO = 273,
    LIT_FLOAT = 274,
    LIT_CHAR = 275,
    LIT_STRING = 276,
    TOKEN_ERROR = 277
  };
#endif
/* Tokens.  */
#define KW_CARA 258
#define KW_INTE 259
#define KW_REAL 260
#define KW_SE 261
#define KW_ENTAUM 262
#define KW_SENAUM 263
#define KW_ENQUANTO 264
#define KW_ENTRADA 265
#define KW_ESCREVA 266
#define KW_RETORNE 267
#define OPERATOR_LE 268
#define OPERATOR_GE 269
#define OPERATOR_EQ 270
#define OPERATOR_DIF 271
#define TK_IDENTIFIER 272
#define LIT_INTEIRO 273
#define LIT_FLOAT 274
#define LIT_CHAR 275
#define LIT_STRING 276
#define TOKEN_ERROR 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "parser.y"

    Hash_node *symbol;
    Ast *ast;

#line 106 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
