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
    INTEGER = 258,                 /* INTEGER  */
    FLOAT = 259,                   /* FLOAT  */
    STRING = 260,                  /* STRING  */
    VOID = 261,                    /* VOID  */
    READ = 262,                    /* READ  */
    PRINT = 263,                   /* PRINT  */
    BOOL = 264,                    /* BOOL  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    DO = 267,                      /* DO  */
    WHILE = 268,                   /* WHILE  */
    PLUS = 269,                    /* PLUS  */
    MINUS = 270,                   /* MINUS  */
    MULT = 271,                    /* MULT  */
    DIV = 272,                     /* DIV  */
    GT = 273,                      /* GT  */
    GE = 274,                      /* GE  */
    LT = 275,                      /* LT  */
    LE = 276,                      /* LE  */
    NE = 277,                      /* NE  */
    EQ = 278,                      /* EQ  */
    AND = 279,                     /* AND  */
    OR = 280,                      /* OR  */
    COLON = 281,                   /* COLON  */
    QUESTION_MARK = 282,           /* QUESTION_MARK  */
    NOT = 283,                     /* NOT  */
    LEFT_ROUND_BRACKET = 284,      /* LEFT_ROUND_BRACKET  */
    RIGHT_ROUND_BRACKET = 285,     /* RIGHT_ROUND_BRACKET  */
    LEFT_CURLY_BRACKET = 286,      /* LEFT_CURLY_BRACKET  */
    RIGHT_CURLY_BRACKET = 287,     /* RIGHT_CURLY_BRACKET  */
    ASSIGN_OP = 288,               /* ASSIGN_OP  */
    SEMICOLON = 289,               /* SEMICOLON  */
    COMMA = 290,                   /* COMMA  */
    RETURN = 291,                  /* RETURN  */
    FLOAT_VAL = 292,               /* FLOAT_VAL  */
    INT_VAL = 293,                 /* INT_VAL  */
    STR_CONST = 294,               /* STR_CONST  */
    NAME = 295,                    /* NAME  */
    UMINUS = 296,                  /* UMINUS  */
    IFX = 297                      /* IFX  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INTEGER 258
#define FLOAT 259
#define STRING 260
#define VOID 261
#define READ 262
#define PRINT 263
#define BOOL 264
#define IF 265
#define ELSE 266
#define DO 267
#define WHILE 268
#define PLUS 269
#define MINUS 270
#define MULT 271
#define DIV 272
#define GT 273
#define GE 274
#define LT 275
#define LE 276
#define NE 277
#define EQ 278
#define AND 279
#define OR 280
#define COLON 281
#define QUESTION_MARK 282
#define NOT 283
#define LEFT_ROUND_BRACKET 284
#define RIGHT_ROUND_BRACKET 285
#define LEFT_CURLY_BRACKET 286
#define RIGHT_CURLY_BRACKET 287
#define ASSIGN_OP 288
#define SEMICOLON 289
#define COMMA 290
#define RETURN 291
#define FLOAT_VAL 292
#define INT_VAL 293
#define STR_CONST 294
#define NAME 295
#define UMINUS 296
#define IFX 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "a5.y"

    int int_val;
    float float_val;
    char *string_val;
    vector<char *> *id_list;
    Ast *ast;
    vector<Ast *> *ast_list;
    Sequence_Ast *seq_ast;
    vector<pair<string,string>> *param_list;
    vector<Function_Ast*> *func_ast_list;

#line 163 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
