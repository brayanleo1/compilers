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
    ID = 258,
    CINT = 259,
    CFLOAT = 260,
    CBOOL = 261,
    CCHAR = 262,
    CSTRING = 263,
    CARRAY = 264,
    INT = 265,
    FLOAT = 266,
    BOOL = 267,
    CHAR = 268,
    GRAPH = 269,
    STRING = 270,
    CONST = 271,
    REGISTER = 272,
    MAIN = 273,
    T_BEGIN = 274,
    END = 275,
    IF = 276,
    ELIF = 277,
    ELSE = 278,
    SWITCH = 279,
    CASE = 280,
    DEFAULT = 281,
    FOR = 282,
    LOOP = 283,
    EXIT = 284,
    WHEN = 285,
    UNLESS = 286,
    PRINT = 287,
    NOT = 288,
    LBRACE = 289,
    RBRACE = 290,
    SEMICOLON = 291,
    COMMA = 292,
    COLON = 293,
    DO = 294,
    TYPE = 295,
    BREAK = 296,
    PROCEDURE = 297,
    FUNCTION = 298,
    RETURN = 299,
    DOT = 300,
    ASSIGN = 301,
    LBRACKET = 302,
    RBRACKET = 303,
    CALL = 304,
    PROGRAM = 305,
    ERROR = 306,
    OR = 307,
    AND = 308,
    PLUS = 309,
    MINUS = 310,
    MULTIPLY = 311,
    DIVIDE = 312,
    POWER = 313,
    LESSTHAN = 314,
    GREATERTHAN = 315,
    LESSTHANOREQUAL = 316,
    GREATERTHANOREQUAL = 317,
    EQUALS = 318,
    NOTEQUAL = 319,
    LPAREN = 320,
    RPAREN = 321,
    UNIPLUS = 322,
    UNIMINUS = 323
  };
#endif
/* Tokens.  */
#define ID 258
#define CINT 259
#define CFLOAT 260
#define CBOOL 261
#define CCHAR 262
#define CSTRING 263
#define CARRAY 264
#define INT 265
#define FLOAT 266
#define BOOL 267
#define CHAR 268
#define GRAPH 269
#define STRING 270
#define CONST 271
#define REGISTER 272
#define MAIN 273
#define T_BEGIN 274
#define END 275
#define IF 276
#define ELIF 277
#define ELSE 278
#define SWITCH 279
#define CASE 280
#define DEFAULT 281
#define FOR 282
#define LOOP 283
#define EXIT 284
#define WHEN 285
#define UNLESS 286
#define PRINT 287
#define NOT 288
#define LBRACE 289
#define RBRACE 290
#define SEMICOLON 291
#define COMMA 292
#define COLON 293
#define DO 294
#define TYPE 295
#define BREAK 296
#define PROCEDURE 297
#define FUNCTION 298
#define RETURN 299
#define DOT 300
#define ASSIGN 301
#define LBRACKET 302
#define RBRACKET 303
#define CALL 304
#define PROGRAM 305
#define ERROR 306
#define OR 307
#define AND 308
#define PLUS 309
#define MINUS 310
#define MULTIPLY 311
#define DIVIDE 312
#define POWER 313
#define LESSTHAN 314
#define GREATERTHAN 315
#define LESSTHANOREQUAL 316
#define GREATERTHANOREQUAL 317
#define EQUALS 318
#define NOTEQUAL 319
#define LPAREN 320
#define RPAREN 321
#define UNIPLUS 322
#define UNIMINUS 323

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
