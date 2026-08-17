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
#line 1 "a5.y"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <vector>
    #include <string>
    #include <cstring>
    #include <iostream>
    #include "symbol_table.hh"
    #include "ast.hh"
    using namespace std;

    extern int yylineno;
    extern FILE *yyin;
    int yylex(void);
    int yyparse(void);
    int yyerror(const char *s);
    extern FILE *fp;
    extern int print_tokens;
    extern int check_semantics;
    extern int semantic_errors;
    SymbolTable symtab;
    Ast* ast_root = nullptr;
    string current_func_type = "";
    bool is_decl = false;

#line 98 "y.tab.c"

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

#line 247 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_VOID = 6,                       /* VOID  */
  YYSYMBOL_READ = 7,                       /* READ  */
  YYSYMBOL_PRINT = 8,                      /* PRINT  */
  YYSYMBOL_BOOL = 9,                       /* BOOL  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_DO = 12,                        /* DO  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_PLUS = 14,                      /* PLUS  */
  YYSYMBOL_MINUS = 15,                     /* MINUS  */
  YYSYMBOL_MULT = 16,                      /* MULT  */
  YYSYMBOL_DIV = 17,                       /* DIV  */
  YYSYMBOL_GT = 18,                        /* GT  */
  YYSYMBOL_GE = 19,                        /* GE  */
  YYSYMBOL_LT = 20,                        /* LT  */
  YYSYMBOL_LE = 21,                        /* LE  */
  YYSYMBOL_NE = 22,                        /* NE  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_AND = 24,                       /* AND  */
  YYSYMBOL_OR = 25,                        /* OR  */
  YYSYMBOL_COLON = 26,                     /* COLON  */
  YYSYMBOL_QUESTION_MARK = 27,             /* QUESTION_MARK  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_LEFT_ROUND_BRACKET = 29,        /* LEFT_ROUND_BRACKET  */
  YYSYMBOL_RIGHT_ROUND_BRACKET = 30,       /* RIGHT_ROUND_BRACKET  */
  YYSYMBOL_LEFT_CURLY_BRACKET = 31,        /* LEFT_CURLY_BRACKET  */
  YYSYMBOL_RIGHT_CURLY_BRACKET = 32,       /* RIGHT_CURLY_BRACKET  */
  YYSYMBOL_ASSIGN_OP = 33,                 /* ASSIGN_OP  */
  YYSYMBOL_SEMICOLON = 34,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 35,                     /* COMMA  */
  YYSYMBOL_RETURN = 36,                    /* RETURN  */
  YYSYMBOL_FLOAT_VAL = 37,                 /* FLOAT_VAL  */
  YYSYMBOL_INT_VAL = 38,                   /* INT_VAL  */
  YYSYMBOL_STR_CONST = 39,                 /* STR_CONST  */
  YYSYMBOL_NAME = 40,                      /* NAME  */
  YYSYMBOL_UMINUS = 41,                    /* UMINUS  */
  YYSYMBOL_IFX = 42,                       /* IFX  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_global_decl_statement_list = 45, /* global_decl_statement_list  */
  YYSYMBOL_func_decl = 46,                 /* func_decl  */
  YYSYMBOL_func_def_list = 47,             /* func_def_list  */
  YYSYMBOL_func_header = 48,               /* func_header  */
  YYSYMBOL_func_def = 49,                  /* func_def  */
  YYSYMBOL_50_1 = 50,                      /* $@1  */
  YYSYMBOL_51_2 = 51,                      /* $@2  */
  YYSYMBOL_formal_param_list = 52,         /* formal_param_list  */
  YYSYMBOL_formal_param = 53,              /* formal_param  */
  YYSYMBOL_optional_local_var_decl_stmt_list = 54, /* optional_local_var_decl_stmt_list  */
  YYSYMBOL_var_decl_stmt_list = 55,        /* var_decl_stmt_list  */
  YYSYMBOL_var_decl_stmt = 56,             /* var_decl_stmt  */
  YYSYMBOL_var_decl_item_list = 57,        /* var_decl_item_list  */
  YYSYMBOL_named_type = 58,                /* named_type  */
  YYSYMBOL_statement_list = 59,            /* statement_list  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_call_statement = 61,            /* call_statement  */
  YYSYMBOL_func_call = 62,                 /* func_call  */
  YYSYMBOL_actual_arg_list = 63,           /* actual_arg_list  */
  YYSYMBOL_non_empty_arg_list = 64,        /* non_empty_arg_list  */
  YYSYMBOL_return_statement = 65,          /* return_statement  */
  YYSYMBOL_if_condition = 66,              /* if_condition  */
  YYSYMBOL_if_statement = 67,              /* if_statement  */
  YYSYMBOL_do_while_statement = 68,        /* do_while_statement  */
  YYSYMBOL_while_statement = 69,           /* while_statement  */
  YYSYMBOL_compound_statement = 70,        /* compound_statement  */
  YYSYMBOL_assignment_statement = 71,      /* assignment_statement  */
  YYSYMBOL_print_statement = 72,           /* print_statement  */
  YYSYMBOL_read_statement = 73,            /* read_statement  */
  YYSYMBOL_expression = 74,                /* expression  */
  YYSYMBOL_rel_expression = 75             /* rel_expression  */
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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   380

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   118,   118,   123,   131,   132,   133,   134,   138,   147,
     158,   163,   171,   180,   179,   218,   217,   328,   334,   341,
     349,   350,   354,   355,   359,   372,   377,   385,   386,   387,
     388,   389,   393,   394,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   410,   414,   436,   437,   441,   446,   454,
     462,   473,   477,   478,   482,   486,   490,   494,   507,   523,
     530,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   568,   569,   570,   574,   575,   576,   577,
     578,   579
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
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER", "FLOAT",
  "STRING", "VOID", "READ", "PRINT", "BOOL", "IF", "ELSE", "DO", "WHILE",
  "PLUS", "MINUS", "MULT", "DIV", "GT", "GE", "LT", "LE", "NE", "EQ",
  "AND", "OR", "COLON", "QUESTION_MARK", "NOT", "LEFT_ROUND_BRACKET",
  "RIGHT_ROUND_BRACKET", "LEFT_CURLY_BRACKET", "RIGHT_CURLY_BRACKET",
  "ASSIGN_OP", "SEMICOLON", "COMMA", "RETURN", "FLOAT_VAL", "INT_VAL",
  "STR_CONST", "NAME", "UMINUS", "IFX", "$accept", "program",
  "global_decl_statement_list", "func_decl", "func_def_list",
  "func_header", "func_def", "$@1", "$@2", "formal_param_list",
  "formal_param", "optional_local_var_decl_stmt_list",
  "var_decl_stmt_list", "var_decl_stmt", "var_decl_item_list",
  "named_type", "statement_list", "statement", "call_statement",
  "func_call", "actual_arg_list", "non_empty_arg_list", "return_statement",
  "if_condition", "if_statement", "do_while_statement", "while_statement",
  "compound_statement", "assignment_statement", "print_statement",
  "read_statement", "expression", "rel_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-62)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-13)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      51,   -62,   -62,   -62,   -62,   -62,    23,    51,   -62,    51,
     -24,   -62,   -62,   -20,   -62,   -62,    51,   -62,    33,   -62,
      -6,     5,    34,   -32,   116,   -62,     4,    29,   -62,    25,
     -62,    38,   -62,    36,   -62,    45,    35,    51,   -62,   -62,
     -62,    51,   -62,    52,   -62,   -62,    51,   -62,    42,    51,
      60,   -62,   -62,   -62,    46,   124,    56,   105,    64,   -62,
     -62,   120,    -3,   -62,   -62,    55,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,    67,    61,   124,   124,   124,   -62,
     -62,   -62,   -62,   167,   -62,   124,   105,    81,   124,    98,
     -62,   188,   124,   140,   -62,   -62,   -62,   -62,   326,   230,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   -62,   247,    86,    72,   264,   -62,   -62,
      74,    79,   312,    73,    75,   209,   -62,    20,    20,   -62,
     -62,   156,   156,   156,   156,   359,   359,   349,   338,   298,
     -62,   105,   124,   105,   -62,   124,   -62,   -62,   124,   -62,
     281,   -62,   312,   312,    82,   -62
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    27,    28,    30,    31,    29,     0,     0,     7,     3,
       0,    11,     6,     0,     1,     5,     2,     4,     0,    10,
       0,     0,    26,     0,     0,    12,    15,     0,    18,     0,
      24,     0,    15,     0,     9,     0,    13,     0,    19,    25,
      13,    21,     8,     0,    17,    33,    20,    23,     0,    21,
       0,    22,    26,    33,     0,     0,     0,     0,     0,    33,
      16,     0,     0,    32,    41,     0,    42,    35,    36,    37,
      38,    34,    39,    40,     0,     0,     0,     0,     0,    74,
      73,    75,    72,     0,    71,     0,     0,     0,     0,     0,
      50,     0,    46,     0,    43,    14,    60,    65,    70,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,     0,    53,     0,     0,    56,    49,
       0,    45,    48,    72,     0,     0,    66,    61,    62,    63,
      64,    78,    79,    76,    77,    81,    80,    68,    69,     0,
      51,     0,     0,     0,    44,     0,    58,    57,     0,    52,
       0,    55,    47,    67,     0,    54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -62,   -62,   -62,   117,   119,     9,    13,   -62,   -62,    99,
      90,    83,   -62,     6,   -62,    12,   -52,   -53,   -62,    40,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -61,   -62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    10,    11,    43,    35,    27,
      28,    45,    46,    47,    23,    29,    50,    63,    64,    65,
     120,   121,    66,    86,    67,    68,    69,    70,    71,    72,
      73,    83,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      91,    74,    30,    31,    87,    21,    12,    89,     1,     2,
       3,     4,    13,    17,     5,    97,    98,    99,    18,    13,
      22,    20,    19,    14,   114,    18,    92,   117,    20,    19,
      93,   122,   125,   115,    25,    26,   102,   103,    34,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,    51,    48,     1,     2,     3,     4,    48,    36,
       5,    48,    24,   -12,    37,    38,    40,    54,    55,    42,
      56,    37,    57,    58,    54,    55,    41,    56,    39,    57,
      58,   150,    52,    49,   152,    85,    75,   153,   149,    94,
     151,    59,    60,    88,   116,    96,    61,   141,    59,    95,
      62,   142,    92,    61,   144,    54,    55,    62,    56,   146,
      57,    58,    54,    55,   145,    56,   155,    57,    58,     1,
       2,     3,     4,    33,    15,     5,    16,    44,     0,    59,
     118,     0,    53,   124,    61,    76,    59,     0,    62,    76,
       0,    61,     0,     0,     0,    62,    32,     0,    77,    78,
       0,     0,    77,    78,    90,    76,     0,    79,    80,    81,
      82,    79,    80,    81,    82,     0,     0,     0,    77,    78,
     100,   101,   102,   103,     0,     0,     0,    79,    80,    81,
     123,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,   112,     0,     0,     0,     0,     0,
       0,   113,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,   112,     0,     0,     0,     0,
       0,     0,   119,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     0,   112,     0,     0,     0,
       0,     0,     0,   147,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,     0,   112,     0,     0,
     126,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,   112,     0,     0,   140,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,   112,     0,     0,   143,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,     0,   112,     0,
       0,   154,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   148,   112,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,     0,   112,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   100,   101,   102,   103,   104,   105,   106,
     107
};

static const yytype_int16 yycheck[] =
{
      61,    53,    34,    35,    57,    29,     0,    59,     3,     4,
       5,     6,     0,     7,     9,    76,    77,    78,     9,     7,
      40,     9,     9,     0,    85,    16,    29,    88,    16,    16,
      33,    92,    93,    86,    40,    30,    16,    17,    34,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,    46,    41,     3,     4,     5,     6,    46,    30,
       9,    49,    29,    29,    35,    40,    30,     7,     8,    34,
      10,    35,    12,    13,     7,     8,    31,    10,    40,    12,
      13,   142,    40,    31,   145,    29,    40,   148,   141,    34,
     143,    31,    32,    29,    13,    34,    36,    11,    31,    32,
      40,    29,    29,    36,    30,     7,     8,    40,    10,    34,
      12,    13,     7,     8,    35,    10,    34,    12,    13,     3,
       4,     5,     6,    24,     7,     9,     7,    37,    -1,    31,
      32,    -1,    49,    93,    36,    15,    31,    -1,    40,    15,
      -1,    36,    -1,    -1,    -1,    40,    30,    -1,    28,    29,
      -1,    -1,    28,    29,    34,    15,    -1,    37,    38,    39,
      40,    37,    38,    39,    40,    -1,    -1,    -1,    28,    29,
      14,    15,    16,    17,    -1,    -1,    -1,    37,    38,    39,
      40,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    -1,    27,    -1,    -1,
      30,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    27,    -1,    -1,    30,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    27,    -1,    -1,    30,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    27,    -1,
      -1,    30,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    27,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    14,    15,    16,    17,    18,    19,    20,
      21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     9,    44,    45,    46,    47,
      48,    49,    56,    58,     0,    46,    47,    56,    48,    49,
      58,    29,    40,    57,    29,    40,    30,    52,    53,    58,
      34,    35,    30,    52,    34,    51,    30,    35,    40,    40,
      30,    31,    34,    50,    53,    54,    55,    56,    58,    31,
      59,    56,    40,    54,     7,     8,    10,    12,    13,    31,
      32,    36,    40,    60,    61,    62,    65,    67,    68,    69,
      70,    71,    72,    73,    59,    40,    15,    28,    29,    37,
      38,    39,    40,    74,    75,    29,    66,    60,    29,    59,
      34,    74,    29,    33,    34,    32,    34,    74,    74,    74,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    27,    34,    74,    60,    13,    74,    32,    34,
      63,    64,    74,    40,    62,    74,    30,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      30,    11,    29,    30,    30,    35,    34,    34,    26,    60,
      74,    60,    74,    74,    30,    34
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    45,    45,    46,    46,
      47,    47,    48,    50,    49,    51,    49,    52,    52,    53,
      54,    54,    55,    55,    56,    57,    57,    58,    58,    58,
      58,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    62,    63,    63,    64,    64,    65,
      65,    66,    67,    67,    68,    69,    70,    71,    71,    72,
      73,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      75,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     2,     1,     1,     5,     4,
       2,     1,     2,     0,     9,     0,     8,     3,     1,     2,
       1,     0,     2,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     4,     1,     0,     3,     1,     3,
       2,     3,     5,     3,     7,     5,     3,     4,     4,     3,
       3,     3,     3,     3,     3,     2,     3,     5,     3,     3,
       2,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3
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
  case 2: /* program: global_decl_statement_list func_def_list  */
#line 119 "a5.y"
      {
        ast_root = new Program_Ast(*(yyvsp[0].func_ast_list), symtab.decl_func);
        delete (yyvsp[0].func_ast_list);
      }
#line 1459 "y.tab.c"
    break;

  case 3: /* program: func_def_list  */
#line 124 "a5.y"
      {
        ast_root = new Program_Ast(*(yyvsp[0].func_ast_list));
        delete (yyvsp[0].func_ast_list);
      }
#line 1468 "y.tab.c"
    break;

  case 8: /* func_decl: func_header LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET SEMICOLON  */
#line 139 "a5.y"
    {
        if (!symtab.insert((yyvsp[-4].string_val), current_func_type, SymbolKind::FUNCTION, yylineno, *(yyvsp[-2].param_list), false) && check_semantics) {
            printf("Semantic Error: redeclaration of function '%s' at line %d\n", (yyvsp[-4].string_val), yylineno);
            semantic_errors = 1;
        }
        symtab.decl_func.push_back((yyvsp[-4].string_val));
        delete (yyvsp[-2].param_list);
    }
#line 1481 "y.tab.c"
    break;

  case 9: /* func_decl: func_header LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET SEMICOLON  */
#line 148 "a5.y"
    {
        if (!symtab.insert((yyvsp[-3].string_val), current_func_type, SymbolKind::FUNCTION, yylineno) && check_semantics) {
            printf("Semantic Error: redeclaration of function '%s' at line %d\n", (yyvsp[-3].string_val), yylineno);
            semantic_errors = 1;
        }
        symtab.decl_func.push_back((yyvsp[-3].string_val));
    }
#line 1493 "y.tab.c"
    break;

  case 10: /* func_def_list: func_def_list func_def  */
#line 159 "a5.y"
      {
          (yyvsp[-1].func_ast_list)->push_back((Function_Ast*)(yyvsp[0].ast));
          (yyval.func_ast_list) = (yyvsp[-1].func_ast_list);
      }
#line 1502 "y.tab.c"
    break;

  case 11: /* func_def_list: func_def  */
#line 164 "a5.y"
      {
          (yyval.func_ast_list) = new vector<Function_Ast*>();
          (yyval.func_ast_list)->push_back((Function_Ast*)(yyvsp[0].ast));
      }
#line 1511 "y.tab.c"
    break;

  case 12: /* func_header: named_type NAME  */
#line 172 "a5.y"
      {
          current_func_type = string((yyvsp[-1].string_val)); // Track for return semantic check
          (yyval.string_val) = (yyvsp[0].string_val);
      }
#line 1520 "y.tab.c"
    break;

  case 13: /* $@1: %empty  */
#line 180 "a5.y"
      {
        SymbolTableEntry *prev_def = symtab.lookup_all_scopes((yyvsp[-3].string_val));
        if (!prev_def) {
            symtab.insert((yyvsp[-3].string_val), current_func_type, SymbolKind::FUNCTION, yylineno, *(yyvsp[-1].param_list));
            is_decl = false;
        }
        else {
            if (prev_def->type != current_func_type && check_semantics) {
                printf("Semantic Error: return type mismatch in definition of '%s'\n", (yyvsp[-3].string_val));
                semantic_errors = 1;
            }
            if (prev_def->params_of_func.size() != (yyvsp[-1].param_list)->size() && check_semantics) {
                printf("Semantic Error: parameter count mismatch in '%s'\n", (yyvsp[-3].string_val));
                semantic_errors = 1;
            }
            for (size_t i = 0; i < (yyvsp[-1].param_list)->size(); i++) {
                if (prev_def->params_of_func[i].first != (*(yyvsp[-1].param_list))[i].first && check_semantics) {
                    printf("Semantic Error: parameter type mismatch in '%s'\n", (yyvsp[-3].string_val));
                    semantic_errors = 1;
                    break;
                }
            }
            is_decl = true;
        }
        symtab.enter_scope();
        for (auto &p : *(yyvsp[-1].param_list)) {
            symtab.insert(p.second, p.first, SymbolKind::PARAMETER, yylineno);
        }
      }
#line 1554 "y.tab.c"
    break;

  case 14: /* func_def: func_header LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET $@1 LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET  */
#line 210 "a5.y"
       {
        Sequence_Ast *seq = (yyvsp[-1].seq_ast);
        (yyval.ast) = new Function_Ast(string((yyvsp[-8].string_val)), current_func_type, *(yyvsp[-6].param_list), seq, is_decl, yylineno);
        symtab.save_current_scope(string((yyvsp[-8].string_val)));
        symtab.exit_scope();
        delete (yyvsp[-6].param_list);
      }
#line 1566 "y.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 218 "a5.y"
      {
        SymbolTableEntry *prev_def = symtab.lookup_all_scopes((yyvsp[-2].string_val));
        if (!prev_def) {
            symtab.insert((yyvsp[-2].string_val), current_func_type, SymbolKind::FUNCTION, yylineno);
            is_decl = false;
        }
        else {
            if (prev_def->type != current_func_type && check_semantics) {
                printf("Semantic Error: return type mismatch in definition of '%s'\n", (yyvsp[-2].string_val));
                semantic_errors = 1;
            }
            if (prev_def->params_of_func.empty() && check_semantics) {
                printf("Semantic Error: parameter count mismatch in '%s'\n", (yyvsp[-2].string_val));
                semantic_errors = 1;
            }
            is_decl = true;
        }
        symtab.enter_scope();
      }
#line 1590 "y.tab.c"
    break;

  case 16: /* func_def: func_header LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET $@2 LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET  */
#line 238 "a5.y"
      {
        Sequence_Ast *seq = (yyvsp[-1].seq_ast);
        vector<pair<string,string>> empty_params;
        (yyval.ast) = new Function_Ast(string((yyvsp[-7].string_val)), current_func_type, empty_params, seq, is_decl, yylineno);
        symtab.save_current_scope(string((yyvsp[-7].string_val)));
        symtab.exit_scope();
      }
#line 1602 "y.tab.c"
    break;

  case 17: /* formal_param_list: formal_param_list COMMA formal_param  */
#line 329 "a5.y"
    {
        (yyvsp[-2].param_list)->insert((yyvsp[-2].param_list)->begin(), (yyvsp[0].param_list)->begin(), (yyvsp[0].param_list)->end());
        delete (yyvsp[0].param_list);
        (yyval.param_list) = (yyvsp[-2].param_list);
    }
#line 1612 "y.tab.c"
    break;

  case 18: /* formal_param_list: formal_param  */
#line 335 "a5.y"
    {
        (yyval.param_list) = (yyvsp[0].param_list);
    }
#line 1620 "y.tab.c"
    break;

  case 19: /* formal_param: named_type NAME  */
#line 342 "a5.y"
    {
        (yyval.param_list) = new vector<pair<string,string>> ();
        (yyval.param_list)->push_back({string((yyvsp[-1].string_val)), string((yyvsp[0].string_val))});
    }
#line 1629 "y.tab.c"
    break;

  case 24: /* var_decl_stmt: named_type var_decl_item_list SEMICOLON  */
#line 360 "a5.y"
      {
        for (auto name : *(yyvsp[-1].id_list)) {
            if (!symtab.insert(name, (yyvsp[-2].string_val), SymbolKind::VARIABLE, yylineno) && check_semantics) {
                printf("Semantic Error: redeclaration of variable '%s' at line %d\n",name, yylineno);
                semantic_errors = 1;
            }
        }
        delete (yyvsp[-1].id_list);
      }
#line 1643 "y.tab.c"
    break;

  case 25: /* var_decl_item_list: var_decl_item_list COMMA NAME  */
#line 373 "a5.y"
      {
        (yyvsp[-2].id_list)->push_back((yyvsp[0].string_val));
        (yyval.id_list) = (yyvsp[-2].id_list);
      }
#line 1652 "y.tab.c"
    break;

  case 26: /* var_decl_item_list: NAME  */
#line 378 "a5.y"
      {
        (yyval.id_list) = new vector<char*>();
        (yyval.id_list)->push_back((yyvsp[0].string_val));
      }
#line 1661 "y.tab.c"
    break;

  case 27: /* named_type: INTEGER  */
#line 385 "a5.y"
              { (yyval.string_val) = strdup("int"); }
#line 1667 "y.tab.c"
    break;

  case 28: /* named_type: FLOAT  */
#line 386 "a5.y"
              { (yyval.string_val) = strdup("float"); }
#line 1673 "y.tab.c"
    break;

  case 29: /* named_type: BOOL  */
#line 387 "a5.y"
              { (yyval.string_val) = strdup("bool"); }
#line 1679 "y.tab.c"
    break;

  case 30: /* named_type: STRING  */
#line 388 "a5.y"
              { (yyval.string_val) = strdup("string"); }
#line 1685 "y.tab.c"
    break;

  case 31: /* named_type: VOID  */
#line 389 "a5.y"
              { (yyval.string_val) = strdup("void"); }
#line 1691 "y.tab.c"
    break;

  case 32: /* statement_list: statement_list statement  */
#line 393 "a5.y"
                               {(yyvsp[-1].seq_ast)->add_statement((yyvsp[0].ast)); (yyval.seq_ast) = (yyvsp[-1].seq_ast);}
#line 1697 "y.tab.c"
    break;

  case 33: /* statement_list: %empty  */
#line 394 "a5.y"
                               {(yyval.seq_ast) = new Sequence_Ast();}
#line 1703 "y.tab.c"
    break;

  case 34: /* statement: assignment_statement  */
#line 398 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1709 "y.tab.c"
    break;

  case 35: /* statement: if_statement  */
#line 399 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1715 "y.tab.c"
    break;

  case 36: /* statement: do_while_statement  */
#line 400 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1721 "y.tab.c"
    break;

  case 37: /* statement: while_statement  */
#line 401 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1727 "y.tab.c"
    break;

  case 38: /* statement: compound_statement  */
#line 402 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1733 "y.tab.c"
    break;

  case 39: /* statement: print_statement  */
#line 403 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1739 "y.tab.c"
    break;

  case 40: /* statement: read_statement  */
#line 404 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1745 "y.tab.c"
    break;

  case 41: /* statement: call_statement  */
#line 405 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1751 "y.tab.c"
    break;

  case 42: /* statement: return_statement  */
#line 406 "a5.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1757 "y.tab.c"
    break;

  case 43: /* call_statement: func_call SEMICOLON  */
#line 410 "a5.y"
                           { (yyval.ast) = (yyvsp[-1].ast); }
#line 1763 "y.tab.c"
    break;

  case 44: /* func_call: NAME LEFT_ROUND_BRACKET actual_arg_list RIGHT_ROUND_BRACKET  */
#line 415 "a5.y"
        {
          SymbolTableEntry* sym = symtab.lookup_all_scopes((yyvsp[-3].string_val));
          if (!sym && check_semantics) {
              printf("Semantic Error: undeclared function '%s' at line %d\n", (yyvsp[-3].string_val), yylineno);
              semantic_errors = 1;
          } 
          else if (sym && sym->sym_kind != SymbolKind::FUNCTION && check_semantics) {
              printf("Semantic Error: '%s' is not a function at line %d\n", (yyvsp[-3].string_val), yylineno);
              semantic_errors = 1;
          } 
          else if (sym && sym->params_of_func.size() != (yyvsp[-1].ast_list)->size() && check_semantics) {
              printf("Semantic Error: incorrect number of arguments for function '%s' at line %d\n", (yyvsp[-3].string_val), yylineno);
              semantic_errors = 1;
          }
          
          (yyval.ast) = new Function_Call_Ast(string((yyvsp[-3].string_val)), *(yyvsp[-1].ast_list), sym, yylineno);
          delete (yyvsp[-1].ast_list);
        }
#line 1786 "y.tab.c"
    break;

  case 45: /* actual_arg_list: non_empty_arg_list  */
#line 436 "a5.y"
                         { (yyval.ast_list) = (yyvsp[0].ast_list); }
#line 1792 "y.tab.c"
    break;

  case 46: /* actual_arg_list: %empty  */
#line 437 "a5.y"
                         { (yyval.ast_list) = new vector<Ast*>(); }
#line 1798 "y.tab.c"
    break;

  case 47: /* non_empty_arg_list: non_empty_arg_list COMMA expression  */
#line 442 "a5.y"
      {
          (yyvsp[-2].ast_list)->push_back((yyvsp[0].ast));
          (yyval.ast_list) = (yyvsp[-2].ast_list);
      }
#line 1807 "y.tab.c"
    break;

  case 48: /* non_empty_arg_list: expression  */
#line 447 "a5.y"
      {
          (yyval.ast_list) = new vector<Ast*>();
          (yyval.ast_list)->push_back((yyvsp[0].ast));
      }
#line 1816 "y.tab.c"
    break;

  case 49: /* return_statement: RETURN expression SEMICOLON  */
#line 455 "a5.y"
      {
          if (current_func_type == "void" && check_semantics) {
              printf("Semantic Error: void function returning a value at line %d\n", yylineno);
              semantic_errors = 1;
          }
          (yyval.ast) = new Return_Ast((yyvsp[-1].ast), yylineno);
      }
#line 1828 "y.tab.c"
    break;

  case 50: /* return_statement: RETURN SEMICOLON  */
#line 463 "a5.y"
      {
          if (current_func_type != "void" && check_semantics) {
              printf("Semantic Error: non-void function missing return value at line %d\n", yylineno);
              semantic_errors = 1;
          }
          (yyval.ast) = new Return_Ast(nullptr, yylineno);
      }
#line 1840 "y.tab.c"
    break;

  case 51: /* if_condition: LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET  */
#line 473 "a5.y"
                                                         {(yyval.ast) = (yyvsp[-1].ast);}
#line 1846 "y.tab.c"
    break;

  case 52: /* if_statement: IF if_condition statement ELSE statement  */
#line 477 "a5.y"
                                               {(yyval.ast) = new If_Else_Ast((yyvsp[-3].ast), (yyvsp[-2].ast), (yyvsp[0].ast), yylineno);}
#line 1852 "y.tab.c"
    break;

  case 53: /* if_statement: IF if_condition statement  */
#line 478 "a5.y"
                                           {(yyval.ast) = new If_Else_Ast((yyvsp[-1].ast), (yyvsp[0].ast), nullptr, yylineno);}
#line 1858 "y.tab.c"
    break;

  case 54: /* do_while_statement: DO statement WHILE LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET SEMICOLON  */
#line 482 "a5.y"
                                                                                     {(yyval.ast) = new Do_While_Ast((yyvsp[-2].ast), (yyvsp[-5].ast), yylineno);}
#line 1864 "y.tab.c"
    break;

  case 55: /* while_statement: WHILE LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET statement  */
#line 486 "a5.y"
                                                                        {(yyval.ast) = new While_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno);}
#line 1870 "y.tab.c"
    break;

  case 56: /* compound_statement: LEFT_CURLY_BRACKET statement_list RIGHT_CURLY_BRACKET  */
#line 490 "a5.y"
                                                            {(yyval.ast) = new Compound_Statement_Ast((yyvsp[-1].seq_ast), yylineno);}
#line 1876 "y.tab.c"
    break;

  case 57: /* assignment_statement: NAME ASSIGN_OP expression SEMICOLON  */
#line 495 "a5.y"
    {
        SymbolTableEntry* sym = symtab.lookup_all_scopes((yyvsp[-3].string_val));
        if (!sym && check_semantics) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n",(yyvsp[-3].string_val), yylineno);
            semantic_errors = 1;
            (yyval.ast) = nullptr;
        }
        else {
            Ast* lhs = new Name_Ast(string((yyvsp[-3].string_val)), sym->type, yylineno);
            (yyval.ast) = new Assignment_Ast(lhs, (yyvsp[-1].ast), yylineno);
        }
    }
#line 1893 "y.tab.c"
    break;

  case 58: /* assignment_statement: NAME ASSIGN_OP func_call SEMICOLON  */
#line 508 "a5.y"
    {
        SymbolTableEntry* sym = symtab.lookup_all_scopes((yyvsp[-3].string_val));
        if (!sym && check_semantics) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n", (yyvsp[-3].string_val), yylineno);
            semantic_errors = 1;
            (yyval.ast) = nullptr;
        } 
        else {
            Ast* lhs = new Name_Ast(string((yyvsp[-3].string_val)), sym->type, yylineno);
            (yyval.ast) = new Assignment_Ast(lhs, (yyvsp[-1].ast), yylineno);
        }
    }
#line 1910 "y.tab.c"
    break;

  case 59: /* print_statement: PRINT expression SEMICOLON  */
#line 524 "a5.y"
      {
          (yyval.ast) = new Print_Ast((yyvsp[-1].ast), yylineno);
      }
#line 1918 "y.tab.c"
    break;

  case 60: /* read_statement: READ NAME SEMICOLON  */
#line 531 "a5.y"
      {
          SymbolTableEntry* sym = symtab.lookup_all_scopes((yyvsp[-1].string_val));
          if (!sym) {
              printf("Semantic Error: undeclared variable '%s' at line %d\n",(yyvsp[-1].string_val), yylineno);
              (yyval.ast) = nullptr;
              semantic_errors = 1;
          } 
          else {
              (yyval.ast) = new Read_Ast(new Name_Ast(string((yyvsp[-1].string_val)), sym->type, yylineno), yylineno);
          }
      }
#line 1934 "y.tab.c"
    break;

  case 61: /* expression: expression PLUS expression  */
#line 545 "a5.y"
                                                             {(yyval.ast) = new Expression_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_ADD, yylineno);}
#line 1940 "y.tab.c"
    break;

  case 62: /* expression: expression MINUS expression  */
#line 546 "a5.y"
                                                             {(yyval.ast) = new Expression_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_SUB, yylineno);}
#line 1946 "y.tab.c"
    break;

  case 63: /* expression: expression MULT expression  */
#line 547 "a5.y"
                                                             {(yyval.ast) = new Expression_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_MULT, yylineno);}
#line 1952 "y.tab.c"
    break;

  case 64: /* expression: expression DIV expression  */
#line 548 "a5.y"
                                                             {(yyval.ast) = new Expression_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_DIV, yylineno);}
#line 1958 "y.tab.c"
    break;

  case 65: /* expression: MINUS expression  */
#line 549 "a5.y"
                                                             {(yyval.ast) = new Uminus_Ast((yyvsp[0].ast), yylineno);}
#line 1964 "y.tab.c"
    break;

  case 66: /* expression: LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET  */
#line 550 "a5.y"
                                                             {(yyval.ast) = (yyvsp[-1].ast);}
#line 1970 "y.tab.c"
    break;

  case 67: /* expression: expression QUESTION_MARK expression COLON expression  */
#line 551 "a5.y"
                                                             {(yyval.ast) = new Ternary_Ast((yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), yylineno);}
#line 1976 "y.tab.c"
    break;

  case 68: /* expression: expression AND expression  */
#line 552 "a5.y"
                                                             {(yyval.ast) = new Logical_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_AND, yylineno);}
#line 1982 "y.tab.c"
    break;

  case 69: /* expression: expression OR expression  */
#line 553 "a5.y"
                                                             {(yyval.ast) = new Logical_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_OR, yylineno);}
#line 1988 "y.tab.c"
    break;

  case 70: /* expression: NOT expression  */
#line 554 "a5.y"
                                                             {(yyval.ast) = new Logical_Not_Ast((yyvsp[0].ast), yylineno);}
#line 1994 "y.tab.c"
    break;

  case 72: /* expression: NAME  */
#line 557 "a5.y"
     {
        const SymbolTableEntry* sym = symtab.lookup_all_scopes((yyvsp[0].string_val));
        if (!sym) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n",(yyvsp[0].string_val), yylineno);
            (yyval.ast) = nullptr;
            semantic_errors = 1;
        } 
        else {
            (yyval.ast) = new Name_Ast(string((yyvsp[0].string_val)), sym->type, yylineno);
        }
     }
#line 2010 "y.tab.c"
    break;

  case 73: /* expression: INT_VAL  */
#line 568 "a5.y"
              { (yyval.ast) = new Int_Ast((yyvsp[0].int_val), yylineno);}
#line 2016 "y.tab.c"
    break;

  case 74: /* expression: FLOAT_VAL  */
#line 569 "a5.y"
                {(yyval.ast) = new Float_Ast((yyvsp[0].float_val), yylineno);}
#line 2022 "y.tab.c"
    break;

  case 75: /* expression: STR_CONST  */
#line 570 "a5.y"
                {(yyval.ast) = new String_Ast(std::string((yyvsp[0].string_val)), yylineno);}
#line 2028 "y.tab.c"
    break;

  case 76: /* rel_expression: expression LT expression  */
#line 574 "a5.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_LT, yylineno);}
#line 2034 "y.tab.c"
    break;

  case 77: /* rel_expression: expression LE expression  */
#line 575 "a5.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_LE, yylineno);}
#line 2040 "y.tab.c"
    break;

  case 78: /* rel_expression: expression GT expression  */
#line 576 "a5.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_GT, yylineno);}
#line 2046 "y.tab.c"
    break;

  case 79: /* rel_expression: expression GE expression  */
#line 577 "a5.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_GE, yylineno);}
#line 2052 "y.tab.c"
    break;

  case 80: /* rel_expression: expression EQ expression  */
#line 578 "a5.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_EQ, yylineno);}
#line 2058 "y.tab.c"
    break;

  case 81: /* rel_expression: expression NE expression  */
#line 579 "a5.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_NE, yylineno);}
#line 2064 "y.tab.c"
    break;


#line 2068 "y.tab.c"

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

#line 582 "a5.y"


int yyerror(const char *s) {
    fprintf(stderr, "Parse Error: %s at line %d\n", s, yylineno);
    return 1;
}

          // Note: Argument type checking against `sym->params_of_func` can be added here
        //   for (size_t i = 0; i < $3->size(); i++) {
        //       if (prev_def->params_of_func[i].first != (*$3)[i]->node_data_type() && check_semantics) {
        //           printf("Semantic Error: parameter type mismatch in '%s'\n", $2);
        //           semantic_errors = 1;
        //           break;
        //       }
        //   } 
