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

#ifndef YY_YY_HOME_MONIKA_COMPILER_FDMJ_COMPILER_BUILD_INCLUDE_FRONTEND_PARSER_H_INCLUDED
# define YY_YY_HOME_MONIKA_COMPILER_FDMJ_COMPILER_BUILD_INCLUDE_FRONTEND_PARSER_H_INCLUDED
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
    PUBLIC = 258,
    INT = 259,
    MAIN = 260,
    FLOAT = 261,
    CLASS = 262,
    NEW = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    CONTINUE = 267,
    BREAK = 268,
    THIS = 269,
    EXTENDS = 270,
    RETURN = 271,
    PUTNUM = 272,
    PUTCH = 273,
    PUTARRAY = 274,
    STARTTIME = 275,
    STOPTIME = 276,
    LENGTH = 277,
    GETNUM = 278,
    GETCH = 279,
    GETARRAY = 280,
    ADD = 281,
    MINUS = 282,
    TIMES = 283,
    DIV = 284,
    OR = 285,
    AND = 286,
    LE = 287,
    LESS = 288,
    GE = 289,
    GREATER = 290,
    EQ = 291,
    NEQ = 292,
    NOT = 293,
    ID = 294,
    NUM = 295,
    BOOLTRUE = 296,
    BOOLFALSE = 297,
    UMINUS = 298,
    LOWER_THAN_ELSE = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"

  A_pos pos;
  A_type type;
  A_prog prog;
  A_mainMethod mainMethod;
  A_varDeclList varDeclList;
  A_varDecl varDecl;
  A_stmList stmList;
  A_stm stm;
  A_expList expList;
  A_exp exp;
  A_classDeclList classDeclList;
  A_classDecl classDecl;
  A_methodDeclList methodDeclList;
  A_methodDecl methodDecl;
  A_formalList formalList;
  A_formal formal;
  char check;

#line 122 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_MONIKA_COMPILER_FDMJ_COMPILER_BUILD_INCLUDE_FRONTEND_PARSER_H_INCLUDED  */
