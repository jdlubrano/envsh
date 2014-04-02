/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROMPT = 258,
     SETENV = 259,
     UNSETENV = 260,
     LISTENV = 261,
     SETDIR = 262,
     BYE = 263,
     IOIN = 264,
     IOOUT = 265,
     NEWLINE = 266,
     STRING = 267,
     VAR_NAME = 268,
     WORD = 269
   };
#endif
/* Tokens.  */
#define PROMPT 258
#define SETENV 259
#define UNSETENV 260
#define LISTENV 261
#define SETDIR 262
#define BYE 263
#define IOIN 264
#define IOOUT 265
#define NEWLINE 266
#define STRING 267
#define VAR_NAME 268
#define WORD 269




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 23 "parser.y"

	char * str;	/* string literals */
	char * varName; /* environment variable names */
	char * word;	/* words */
	WORD_LIST * wordList;
	STRING_LIST * stringList;



/* Line 2068 of yacc.c  */
#line 88 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


