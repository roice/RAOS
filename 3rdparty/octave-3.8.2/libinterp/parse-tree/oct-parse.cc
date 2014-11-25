/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 1

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         OCTAVE_STYPE
/* Substitute the variable and function names.  */
#define yyparse         octave_parse
#define yypush_parse    octave_push_parse
#define yypull_parse    octave_pull_parse
#define yypstate_new    octave_pstate_new
#define yypstate_delete octave_pstate_delete
#define yypstate        octave_pstate
#define yylex           octave_lex
#define yyerror         octave_error
#define yydebug         octave_debug
#define yynerrs         octave_nerrs


/* Copy the first part of user declarations.  */
#line 29 "parse-tree/oct-parse.yy" /* yacc.c:339  */

#define YYDEBUG 1

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <map>
#include <sstream>

#include "Cell.h"
#include "Matrix.h"
#include "cmd-edit.h"
#include "cmd-hist.h"
#include "file-ops.h"
#include "file-stat.h"
#include "oct-env.h"
#include "oct-time.h"
#include "quit.h"

#include "comment-list.h"
#include "defaults.h"
#include "defun.h"
#include "dirfns.h"
#include "dynamic-ld.h"
#include "error.h"
#include "input.h"
#include "lex.h"
#include "load-path.h"
#include "oct-hist.h"
#include "oct-map.h"
#include "ov-fcn-handle.h"
#include "ov-usr-fcn.h"
#include "ov-null-mat.h"
#include "toplev.h"
#include "pager.h"
#include "parse.h"
#include "pt-all.h"
#include "pt-eval.h"
#include "symtab.h"
#include "token.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

// oct-parse.h must be included after pt-all.h
#include <oct-parse.h>

extern int octave_lex (YYSTYPE *, void *);

// Global access to currently active lexer.
// FIXME -- to be removed after more parser+lexer refactoring.
octave_base_lexer *LEXER = 0;

#if defined (GNULIB_NAMESPACE)
// Calls to the following functions appear in the generated output from
// Bison without the namespace tag.  Redefine them so we will use them
// via the gnulib namespace.
#define fclose GNULIB_NAMESPACE::fclose
#define fprintf GNULIB_NAMESPACE::fprintf
#define malloc GNULIB_NAMESPACE::malloc
#endif

// TRUE means we printed messages about reading startup files.
bool reading_startup_message_printed = false;

// List of autoloads (function -> file mapping).
static std::map<std::string, std::string> autoload_map;

// Forward declarations for some functions defined at the bottom of
// the file.

static void yyerror (octave_base_parser& parser, const char *s);

#define ABORT_PARSE \
  do \
    { \
      yyerrok; \
      if ((interactive || forced_interactive) \
          && ! lexer.input_from_eval_string ()) \
        YYACCEPT; \
      else \
        YYABORT; \
    } \
  while (0)

#define lexer parser.lexer
#define scanner lexer.scanner


#line 174 "parse-tree/oct-parse.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_OCTAVE_PARSE_TREE_OCT_PARSE_H_INCLUDED
# define YY_OCTAVE_PARSE_TREE_OCT_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef OCTAVE_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define OCTAVE_DEBUG 1
#  else
#   define OCTAVE_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define OCTAVE_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined OCTAVE_DEBUG */
#if OCTAVE_DEBUG
extern int octave_debug;
#endif

/* Token type.  */
#ifndef OCTAVE_TOKENTYPE
# define OCTAVE_TOKENTYPE
  enum octave_tokentype
  {
    ADD_EQ = 258,
    SUB_EQ = 259,
    MUL_EQ = 260,
    DIV_EQ = 261,
    LEFTDIV_EQ = 262,
    POW_EQ = 263,
    EMUL_EQ = 264,
    EDIV_EQ = 265,
    ELEFTDIV_EQ = 266,
    EPOW_EQ = 267,
    AND_EQ = 268,
    OR_EQ = 269,
    LSHIFT_EQ = 270,
    RSHIFT_EQ = 271,
    LSHIFT = 272,
    RSHIFT = 273,
    EXPR_AND_AND = 274,
    EXPR_OR_OR = 275,
    EXPR_AND = 276,
    EXPR_OR = 277,
    EXPR_NOT = 278,
    EXPR_LT = 279,
    EXPR_LE = 280,
    EXPR_EQ = 281,
    EXPR_NE = 282,
    EXPR_GE = 283,
    EXPR_GT = 284,
    LEFTDIV = 285,
    EMUL = 286,
    EDIV = 287,
    ELEFTDIV = 288,
    EPLUS = 289,
    EMINUS = 290,
    HERMITIAN = 291,
    TRANSPOSE = 292,
    PLUS_PLUS = 293,
    MINUS_MINUS = 294,
    POW = 295,
    EPOW = 296,
    NUM = 297,
    IMAG_NUM = 298,
    STRUCT_ELT = 299,
    NAME = 300,
    END = 301,
    DQ_STRING = 302,
    SQ_STRING = 303,
    FOR = 304,
    PARFOR = 305,
    WHILE = 306,
    DO = 307,
    UNTIL = 308,
    IF = 309,
    ELSEIF = 310,
    ELSE = 311,
    SWITCH = 312,
    CASE = 313,
    OTHERWISE = 314,
    BREAK = 315,
    CONTINUE = 316,
    FUNC_RET = 317,
    UNWIND = 318,
    CLEANUP = 319,
    TRY = 320,
    CATCH = 321,
    GLOBAL = 322,
    PERSISTENT = 323,
    FCN_HANDLE = 324,
    PROPERTIES = 325,
    METHODS = 326,
    EVENTS = 327,
    ENUMERATION = 328,
    METAQUERY = 329,
    SUPERCLASSREF = 330,
    GET = 331,
    SET = 332,
    FCN = 333,
    END_OF_INPUT = 334,
    LEXICAL_ERROR = 335,
    INPUT_FILE = 336,
    CLASSDEF = 337,
    UNARY = 338
  };
#endif
/* Tokens.  */
#define ADD_EQ 258
#define SUB_EQ 259
#define MUL_EQ 260
#define DIV_EQ 261
#define LEFTDIV_EQ 262
#define POW_EQ 263
#define EMUL_EQ 264
#define EDIV_EQ 265
#define ELEFTDIV_EQ 266
#define EPOW_EQ 267
#define AND_EQ 268
#define OR_EQ 269
#define LSHIFT_EQ 270
#define RSHIFT_EQ 271
#define LSHIFT 272
#define RSHIFT 273
#define EXPR_AND_AND 274
#define EXPR_OR_OR 275
#define EXPR_AND 276
#define EXPR_OR 277
#define EXPR_NOT 278
#define EXPR_LT 279
#define EXPR_LE 280
#define EXPR_EQ 281
#define EXPR_NE 282
#define EXPR_GE 283
#define EXPR_GT 284
#define LEFTDIV 285
#define EMUL 286
#define EDIV 287
#define ELEFTDIV 288
#define EPLUS 289
#define EMINUS 290
#define HERMITIAN 291
#define TRANSPOSE 292
#define PLUS_PLUS 293
#define MINUS_MINUS 294
#define POW 295
#define EPOW 296
#define NUM 297
#define IMAG_NUM 298
#define STRUCT_ELT 299
#define NAME 300
#define END 301
#define DQ_STRING 302
#define SQ_STRING 303
#define FOR 304
#define PARFOR 305
#define WHILE 306
#define DO 307
#define UNTIL 308
#define IF 309
#define ELSEIF 310
#define ELSE 311
#define SWITCH 312
#define CASE 313
#define OTHERWISE 314
#define BREAK 315
#define CONTINUE 316
#define FUNC_RET 317
#define UNWIND 318
#define CLEANUP 319
#define TRY 320
#define CATCH 321
#define GLOBAL 322
#define PERSISTENT 323
#define FCN_HANDLE 324
#define PROPERTIES 325
#define METHODS 326
#define EVENTS 327
#define ENUMERATION 328
#define METAQUERY 329
#define SUPERCLASSREF 330
#define GET 331
#define SET 332
#define FCN 333
#define END_OF_INPUT 334
#define LEXICAL_ERROR 335
#define INPUT_FILE 336
#define CLASSDEF 337
#define UNARY 338

/* Value type.  */
#if ! defined OCTAVE_STYPE && ! defined OCTAVE_STYPE_IS_DECLARED
typedef union OCTAVE_STYPE OCTAVE_STYPE;
union OCTAVE_STYPE
{
#line 149 "parse-tree/oct-parse.yy" /* yacc.c:355  */

  // The type of the basic tokens returned by the lexer.
  token *tok_val;

  // Comment strings that we need to deal with mid-rule.
  octave_comment_list *comment_type;

  // Types for the nonterminals we generate.
  char sep_type;
  tree *tree_type;
  tree_matrix *tree_matrix_type;
  tree_cell *tree_cell_type;
  tree_expression *tree_expression_type;
  tree_constant *tree_constant_type;
  tree_fcn_handle *tree_fcn_handle_type;
  tree_anon_fcn_handle *tree_anon_fcn_handle_type;
  tree_identifier *tree_identifier_type;
  tree_index_expression *tree_index_expression_type;
  tree_colon_expression *tree_colon_expression_type;
  tree_argument_list *tree_argument_list_type;
  tree_parameter_list *tree_parameter_list_type;
  tree_command *tree_command_type;
  tree_if_command *tree_if_command_type;
  tree_if_clause *tree_if_clause_type;
  tree_if_command_list *tree_if_command_list_type;
  tree_switch_command *tree_switch_command_type;
  tree_switch_case *tree_switch_case_type;
  tree_switch_case_list *tree_switch_case_list_type;
  tree_decl_elt *tree_decl_elt_type;
  tree_decl_init_list *tree_decl_init_list_type;
  tree_decl_command *tree_decl_command_type;
  tree_statement *tree_statement_type;
  tree_statement_list *tree_statement_list_type;
  octave_user_function *octave_user_function_type;
  void *dummy_type;

#line 425 "parse-tree/oct-parse.cc" /* yacc.c:355  */
};
# define OCTAVE_STYPE_IS_TRIVIAL 1
# define OCTAVE_STYPE_IS_DECLARED 1
#endif



#ifndef YYPUSH_MORE_DEFINED
# define YYPUSH_MORE_DEFINED
enum { YYPUSH_MORE = 4 };
#endif

typedef struct octave_pstate octave_pstate;

int octave_parse (octave_base_parser& parser);
int octave_push_parse (octave_pstate *ps, int pushed_char, OCTAVE_STYPE const *pushed_val, octave_base_parser& parser);
int octave_pull_parse (octave_pstate *ps, octave_base_parser& parser);
octave_pstate * octave_pstate_new (void);
void octave_pstate_delete (octave_pstate *ps);

#endif /* !YY_OCTAVE_PARSE_TREE_OCT_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 450 "parse-tree/oct-parse.cc" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined OCTAVE_STYPE_IS_TRIVIAL && OCTAVE_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  115
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1410

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  101
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  104
/* YYNRULES -- Number of rules.  */
#define YYNRULES  275
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  514

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   338

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      93,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      90,   100,     7,     6,    98,     5,    91,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,    96,
       2,     3,     2,     2,    99,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    94,     2,    95,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,    97,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89
};

#if OCTAVE_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   347,   347,   352,   358,   362,   364,   368,   370,   375,
     376,   380,   384,   386,   390,   392,   394,   406,   417,   419,
     430,   438,   442,   446,   448,   452,   454,   456,   460,   464,
     466,   480,   484,   486,   505,   506,   508,   510,   512,   514,
     518,   525,   532,   534,   536,   538,   543,   545,   547,   549,
     553,   560,   566,   568,   570,   572,   577,   582,   589,   593,
     595,   597,   599,   608,   617,   626,   635,   637,   639,   641,
     643,   645,   647,   649,   651,   653,   655,   657,   659,   661,
     663,   665,   667,   669,   671,   673,   675,   679,   681,   683,
     685,   694,   703,   712,   721,   723,   725,   727,   729,   731,
     733,   737,   741,   743,   754,   756,   758,   760,   762,   764,
     766,   768,   770,   772,   774,   776,   778,   782,   796,   798,
     800,   802,   804,   806,   808,   810,   812,   814,   816,   818,
     820,   822,   824,   828,   843,   845,   853,   855,   857,   859,
     861,   863,   865,   867,   875,   880,   887,   889,   897,   899,
     901,   912,   914,   922,   932,   934,   941,   947,   954,   962,
     970,   981,   982,   984,   986,   993,   995,  1002,  1006,  1016,
    1026,  1030,  1039,  1048,  1057,  1072,  1074,  1076,  1084,  1093,
    1102,  1117,  1144,  1157,  1164,  1171,  1180,  1181,  1197,  1199,
    1206,  1208,  1216,  1222,  1240,  1257,  1259,  1270,  1300,  1309,
    1315,  1323,  1332,  1338,  1346,  1356,  1358,  1362,  1371,  1411,
    1418,  1430,  1434,  1439,  1440,  1444,  1446,  1450,  1452,  1454,
    1460,  1461,  1465,  1467,  1469,  1471,  1475,  1477,  1479,  1481,
    1483,  1485,  1487,  1489,  1493,  1498,  1503,  1505,  1509,  1511,
    1515,  1519,  1523,  1525,  1529,  1533,  1537,  1539,  1543,  1547,
    1551,  1555,  1557,  1561,  1570,  1574,  1577,  1579,  1582,  1584,
    1586,  1588,  1593,  1594,  1599,  1600,  1604,  1606,  1610,  1612,
    1614,  1616,  1618,  1620,  1625,  1626
};
#endif

#if OCTAVE_DEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "':'", "'-'", "'+'", "'*'", "'/'",
  "ADD_EQ", "SUB_EQ", "MUL_EQ", "DIV_EQ", "LEFTDIV_EQ", "POW_EQ",
  "EMUL_EQ", "EDIV_EQ", "ELEFTDIV_EQ", "EPOW_EQ", "AND_EQ", "OR_EQ",
  "LSHIFT_EQ", "RSHIFT_EQ", "LSHIFT", "RSHIFT", "EXPR_AND_AND",
  "EXPR_OR_OR", "EXPR_AND", "EXPR_OR", "EXPR_NOT", "EXPR_LT", "EXPR_LE",
  "EXPR_EQ", "EXPR_NE", "EXPR_GE", "EXPR_GT", "LEFTDIV", "EMUL", "EDIV",
  "ELEFTDIV", "EPLUS", "EMINUS", "HERMITIAN", "TRANSPOSE", "PLUS_PLUS",
  "MINUS_MINUS", "POW", "EPOW", "NUM", "IMAG_NUM", "STRUCT_ELT", "NAME",
  "END", "DQ_STRING", "SQ_STRING", "FOR", "PARFOR", "WHILE", "DO", "UNTIL",
  "IF", "ELSEIF", "ELSE", "SWITCH", "CASE", "OTHERWISE", "BREAK",
  "CONTINUE", "FUNC_RET", "UNWIND", "CLEANUP", "TRY", "CATCH", "GLOBAL",
  "PERSISTENT", "FCN_HANDLE", "PROPERTIES", "METHODS", "EVENTS",
  "ENUMERATION", "METAQUERY", "SUPERCLASSREF", "GET", "SET", "FCN",
  "END_OF_INPUT", "LEXICAL_ERROR", "INPUT_FILE", "CLASSDEF", "UNARY",
  "'('", "'.'", "'{'", "'\\n'", "'['", "']'", "';'", "'}'", "','", "'@'",
  "')'", "$accept", "input", "simple_list", "simple_list1", "opt_list",
  "list", "list1", "statement", "word_list_cmd", "word_list", "identifier",
  "superclass_identifier", "meta_identifier", "string", "constant",
  "matrix", "matrix_rows", "cell", "cell_rows", "cell_or_matrix_row",
  "fcn_handle", "anon_fcn_handle", "primary_expr", "magic_colon",
  "magic_tilde", "arg_list", "indirect_ref_op", "oper_expr", "power_expr",
  "colon_expr", "colon_expr1", "simple_expr", "assign_lhs", "assign_expr",
  "expression", "command", "declaration", "decl1", "decl_param_init",
  "decl2", "select_command", "if_command", "if_cmd_list", "if_cmd_list1",
  "elseif_clause", "else_clause", "switch_command", "case_list",
  "case_list1", "switch_case", "default_case", "loop_command",
  "jump_command", "except_command", "push_fcn_symtab", "param_list_beg",
  "param_list_end", "param_list", "param_list1", "param_list2",
  "param_list_elt", "return_list", "return_list1", "file", "function_beg",
  "function", "fcn_name", "function1", "function2", "function_end",
  "classdef_beg", "classdef_end", "classdef1", "classdef", "opt_attr_list",
  "attr_list", "attr", "opt_superclasses", "superclasses", "class_body",
  "properties_beg", "properties_block", "properties_list",
  "class_property", "methods_beg", "methods_block", "methods_list",
  "events_beg", "events_block", "events_list", "class_event", "enum_beg",
  "enum_block", "enum_list", "class_enum", "stmt_begin", "stash_comment",
  "parse_error", "sep_no_nl", "opt_sep_no_nl", "opt_nl", "nl", "sep",
  "opt_sep", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    61,    58,    45,    43,    42,    47,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
      40,    46,   123,    10,    91,    93,    59,   125,    44,    64,
      41
};
# endif

#define YYPACT_NINF -400

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-400)))

#define YYTABLE_NINF -263

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     547,  -400,  1093,  1093,  1093,  1093,  1093,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,   -15,   -15,  -400,  -400,  -400,   -36,  -400,
    1110,   686,   686,  -400,  -400,   -31,    67,   -45,    16,  -400,
    -400,    -8,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
    -400,  1264,  -400,    68,  1309,  1348,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,    22,  -400,  -400,  -400,
      38,    28,  -400,  -400,    79,  -400,     7,  -400,    19,    19,
      19,    19,    19,  1127,  1183,  1110,    28,  1110,  1110,    28,
      28,    83,   -15,  -400,   -15,  -400,   981,    64,  -400,    74,
    -400,  1093,   816,   -44,  -400,  -400,  -400,    88,  -400,     2,
    -400,  -400,  -400,    20,  -400,  -400,  -400,  -400,   925,  -400,
      -8,  -400,  1093,  1093,  1093,  1093,  1093,  1093,  1093,  1093,
    1093,  1093,  -400,  -400,  -400,  -400,  1200,  1200,   618,  -400,
     720,   -13,  1093,  1093,  1093,  1093,  1093,  1093,  1093,  1093,
    1093,  1093,  1093,  1093,  1093,  1110,  1110,  1110,  1110,  1110,
    1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,  1110,
    -400,     5,    -4,   -15,  -400,  -400,  -400,    72,   112,  -400,
    -400,  1110,   231,   164,  1110,   178,  -400,   981,  -400,   146,
      61,    28,   981,   981,  -400,  -400,   129,  -400,    28,  -400,
    -400,  -400,   119,   686,  -400,   816,  -400,   686,  -400,  -400,
    -400,  -400,   121,   126,  -400,  1037,  -400,  -400,   245,   245,
      19,    19,    19,    19,    19,    19,   245,   245,  1200,  1200,
    1200,  1200,  1200,  -400,   -12,   -12,  -400,    96,  -400,    55,
    -400,  1110,  1264,  -400,  -400,   299,   279,   332,   199,   155,
     155,   155,   155,   155,   155,  -400,  -400,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
     151,   157,   -37,   243,   247,    37,  -400,   -15,   268,    97,
    -400,   250,  -400,  -400,  -400,  -400,  -400,  -400,  -400,    28,
      38,  -400,    38,  -400,    38,  -400,    38,  -400,  1368,  1110,
    1388,  1110,    28,   216,    28,  -400,  -400,  -400,  -400,  -400,
     173,   223,    -2,  1110,  -400,   869,  -400,   816,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,     9,  -400,   -12,   -12,   -12,
     -12,   -12,  -400,  -400,   652,   754,    -7,   816,  -400,  -400,
     186,   -15,   -15,  -400,  -400,    71,    34,    28,  -400,   981,
    -400,  -400,    -4,  -400,   -15,  -400,   267,  -400,  -400,  -400,
    -400,   112,    28,    28,    28,    28,  1110,  -400,  1110,  -400,
     981,  1110,   981,    28,    28,  -400,  -400,   244,   173,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,   120,  -400,
     143,  -400,  1110,  -400,  -400,  -400,  -400,   -15,  -400,  -400,
     981,    -1,  1110,  -400,   204,   -15,  -400,  -400,  -400,  -400,
     253,   -15,  -400,   -15,   -15,   208,    28,   219,    28,   266,
    -400,  -400,  1110,   981,    28,    28,  -400,  -400,  -400,    28,
      28,  -400,  -400,   221,  -400,    -1,  -400,  -400,  -400,  -400,
     -15,   233,  -400,  -400,   325,    28,  -400,  -400,    28,  -400,
      28,  -400,   248,    28,  -400,    28,   981,  1110,   981,  -400,
    -400,  -400,  1110,   981,   981,   981,  -400,  -400,  -400,   -15,
    -400,   193,   287,   218,  1110,   227,   981,   288,   251,   295,
      28,  -400,  -400,   296,   298,  -400,  1110,  -400,  -400,  -400,
    -400,  -400,  -400,   259,  -400,  -400,   301,  -400,    28,  -400,
     981,    28,  -400,  -400,   264,  -400,  -400,   981,  -400,   981,
    -400,   316,  -400,  -400
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   257,     0,     0,     0,     0,     0,    25,    26,    20,
      23,    24,   255,   255,   255,   255,   255,   255,   175,   176,
     177,   255,   255,     0,     0,    22,    21,   256,   264,   255,
       0,    34,    34,   259,   258,     0,     0,     0,   262,     7,
      16,    42,    48,    47,    27,    43,    45,    46,    44,   135,
      59,   102,   104,   101,   133,     0,   134,    14,    15,   136,
     137,   151,   152,   138,   139,   140,     0,   142,   255,   141,
     213,   274,   143,     4,   263,     5,     0,    42,    74,    73,
      72,    70,    71,     0,     0,     0,   274,     0,     0,   274,
     274,   149,   144,   146,   145,   266,     9,   265,   209,     0,
      50,    51,    35,     0,    32,    53,    54,    36,    52,     0,
      29,    40,   182,     0,   254,     1,     3,     2,   263,     6,
      17,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,    67,    60,    61,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     198,     0,     0,     0,   270,   269,   268,   275,     0,   261,
     260,     0,   117,     0,     0,     0,   254,     9,   254,     0,
     154,   274,     9,     9,   148,   147,     0,    10,   274,    12,
     267,    49,    38,    34,    31,    37,    28,    34,   185,    51,
     191,   190,     0,   187,   188,   181,     8,    19,    78,    77,
      79,    80,    85,    83,    84,    86,    81,    82,     0,     0,
       0,     0,     0,    87,    75,    76,    62,     0,    64,     0,
      68,     0,   103,   105,   106,   115,   116,   113,   114,   107,
     108,   109,   112,   110,   111,   118,   119,   120,   121,   122,
     123,   124,   127,   128,   129,   130,   131,   132,   125,   126,
       0,     0,     0,   201,     0,   274,   199,     0,   217,     0,
     215,   220,   273,   272,   271,   255,   255,   255,   255,   274,
     213,   226,   213,   227,   213,   228,   213,   229,     0,     0,
       0,     0,   274,     0,   274,   153,   255,   255,   157,   155,
     161,     0,     0,     0,   197,   275,    11,    39,    33,    55,
      56,    57,    30,   183,   184,     0,    41,   100,    99,    98,
      96,    97,    88,    89,     0,     0,     0,     0,    63,    65,
       0,     0,     0,   192,   195,     0,     0,   274,   204,     9,
     219,   148,     0,   214,     0,   211,   221,   234,   240,   244,
     249,   255,   274,   274,   274,   274,     0,   254,     0,   254,
       9,     0,     9,   274,   274,   255,   255,     0,   163,   165,
     162,   255,   180,   255,   150,    13,   189,    90,     0,    92,
       0,    94,     0,    69,   202,   203,   194,     0,   201,   200,
       9,     0,     0,   216,   223,     0,   230,   231,   232,   233,
       0,     0,   181,     0,     0,     0,   274,   118,   274,     0,
     170,   156,     0,     9,   274,   274,   160,   166,   164,   274,
     274,    91,    93,     0,   196,     0,   207,   208,   206,   218,
       0,   225,   210,   212,   238,   274,   236,   242,   274,   248,
     274,   246,     0,   274,   251,   274,     9,     0,     9,   169,
     254,   159,     0,     9,     9,     9,    95,   205,   222,     0,
     148,     0,   181,     0,     0,     0,     9,     0,     0,     0,
     274,   254,   168,     0,     0,   224,     0,   235,   237,   241,
     243,   245,   247,     0,   250,   252,     0,   171,   274,   173,
       9,   274,   178,   179,     0,   253,   172,     9,   158,     9,
     239,     0,   167,   174
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -400,  -400,  -400,  -400,    81,  -400,  -400,     1,  -400,  -400,
       0,  -400,  -400,   -30,  -400,  -400,  -400,  -400,  -400,   -27,
    -400,  -400,   -68,  -183,   -98,   -99,  -180,    14,  -128,  -400,
    -400,   740,   -76,  -400,    44,  -400,  -400,   345,  -345,   -82,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,    -3,
       4,  -400,  -400,  -400,  -400,  -400,  -400,   101,  -400,  -400,
      52,  -400,  -400,  -400,  -400,  -399,  -400,    39,  -400,   -55,
    -400,  -400,  -400,  -400,  -201,  -400,    31,  -400,  -400,  -400,
    -400,    23,  -400,   -85,  -400,    26,  -400,  -400,    29,  -400,
     -81,  -400,    30,  -400,   -80,  -184,    13,  -400,   355,   360,
    -400,  -400,   201,    69
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    36,    37,    38,   196,   197,   198,   199,    40,   120,
      77,    42,    43,    44,    45,    46,   109,    47,   103,   104,
      48,    49,    50,   105,   106,   107,   141,    51,   234,    52,
      53,    54,    55,    56,    57,    58,    59,    92,   313,    93,
      60,    61,   189,   190,   308,   309,    62,   377,   378,   379,
     380,    63,    64,    65,    66,   113,   324,   114,   212,   213,
     214,   274,   345,    67,    68,    69,   275,   276,   348,   438,
      70,   443,    71,    72,   173,   279,   280,   355,   356,   289,
     290,   291,   445,   446,   292,   293,   448,   294,   295,   450,
     451,   296,   297,   453,   454,   215,    83,    73,    74,    75,
      96,    97,   177,   178
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    39,   302,   202,   304,   110,   402,   183,   185,   235,
     195,   121,   195,   447,     9,   210,    78,    79,    80,    81,
      82,   208,   319,    91,    91,   277,    84,    85,    86,    87,
      88,   211,   332,   333,    89,    90,     9,   240,   209,   237,
     116,   239,    98,   391,   111,    10,    11,     9,   117,   209,
     382,   436,   203,   204,   336,   336,     9,    95,   343,   112,
       9,   132,   133,   134,   135,   136,   137,   115,   233,   233,
     383,     9,   142,   490,    99,   108,   108,   241,   334,   139,
     335,   171,   111,   392,   437,     9,   194,   270,   271,   362,
     217,   363,    91,   364,    91,   365,    41,   206,   207,   272,
     327,   328,   329,   330,   331,   298,   170,   320,   300,   138,
     139,   140,    33,    91,    34,    80,   270,   271,    41,   216,
    -186,   174,   306,   307,   175,   486,   176,   112,   172,   186,
     174,   188,   191,   175,   319,   176,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   108,   336,   336,   336,
     336,   336,   339,   337,   319,   187,   242,   200,   192,   193,
     233,   233,   233,   233,   233,   282,   396,   299,   283,   397,
     284,   273,   278,   281,   201,   179,   318,   180,   143,   144,
     322,   301,   108,   416,   108,   418,   205,    41,   285,   286,
     287,   288,    41,    41,   337,   352,   338,   353,   305,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   314,    41,   326,   317,   337,   320,
     431,   323,   143,   144,   325,    99,   147,   210,    99,   149,
     150,   151,   152,   153,   154,   388,   390,   375,   376,   320,
     432,   337,   341,   211,     9,   487,  -193,   108,   342,   321,
     346,   108,   124,   125,   143,   144,   145,   146,   147,   148,
     310,   149,   150,   151,   152,   153,   154,   316,   303,     9,
     491,   351,   344,   311,   312,   371,   480,   350,     9,   494,
     354,   126,   127,   128,   129,   340,   393,   132,   133,   134,
     135,   136,   137,   381,   405,   440,   426,   501,   357,   358,
     359,   360,   143,   144,   145,   442,   147,   148,   455,   149,
     150,   151,   152,   153,   154,    41,   385,   457,   459,   373,
     374,   466,   143,   144,   469,    91,   147,   148,   470,   149,
     150,   151,   152,   153,   154,   138,   139,   140,   474,   489,
     497,   394,   395,   367,   349,   369,   398,   499,   502,    41,
     503,   498,   278,   506,   404,   143,   144,   384,   361,   505,
     510,   321,   149,   150,   151,   152,   153,   154,   513,    94,
      41,   370,    41,   372,   410,   427,   347,   386,   108,   108,
     467,   321,   428,   403,   406,   399,   488,   407,   424,   425,
     408,   409,   492,   118,   429,   495,   430,   434,   119,   315,
      41,     0,     0,     0,     0,   441,     0,     0,     0,     0,
     415,   444,   417,   449,   452,   420,   400,     0,     0,     0,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
     401,   411,   412,   413,   414,     0,   433,     0,     0,     0,
     468,     0,   422,   423,     0,     0,   439,     0,     0,     0,
       0,   419,     0,   421,     0,     0,    41,     0,    41,     0,
       0,     0,     0,    41,    41,    41,   460,     0,     0,   485,
       0,   444,     0,   449,     0,   452,    41,     0,     0,     0,
       0,   435,     0,     0,     0,   456,     0,   458,     0,     0,
       0,     0,     0,   462,   463,     0,     0,     0,   464,   465,
      41,   478,     0,     0,   461,     0,   481,    41,     0,    41,
       0,     0,     0,     0,   471,     0,     0,   472,   493,   473,
       0,     0,   475,     0,   476,     0,     0,     0,     0,     0,
     504,     0,     0,     0,     0,     0,     0,   477,     0,   479,
       0,     0,     0,     0,   482,   483,   484,     0,     1,   500,
       0,     0,     2,     3,     0,     0,     0,   496,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   507,     0,     0,
     509,     0,     0,     0,     0,     0,     4,     0,     0,     0,
       0,   508,     0,     0,     0,     0,     0,     0,   511,     0,
     512,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      10,    11,    12,    13,    14,    15,     0,    16,     0,     0,
      17,     0,     0,    18,    19,    20,    21,     0,    22,     0,
      23,    24,   100,     2,     3,     0,     0,    25,    26,     0,
       0,  -181,  -262,    27,    28,    29,     0,    30,     0,    31,
    -262,    32,     0,    33,     0,    34,    35,   101,     0,     0,
       0,     0,     0,     0,     0,     0,   100,     2,     3,     0,
       0,     0,     5,     6,     0,     0,     7,     8,     0,     9,
       0,    10,    11,     0,     0,     0,     0,     0,     0,     0,
       0,   101,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     2,     3,     0,     0,     0,     5,     6,    25,    26,
       7,     8,     0,     9,     0,    10,    11,     0,    30,     0,
      31,     0,    32,     0,     0,   101,     0,    35,   236,     0,
       0,     0,     0,     0,   100,     2,     3,     0,     0,     0,
       5,     6,    25,    26,     7,     8,     0,     9,     0,    10,
      11,     0,    30,     0,    31,     0,    32,     0,     0,   101,
       0,    35,   387,     0,     0,     0,     0,     0,   100,     2,
       3,     0,     0,     0,     5,     6,    25,    26,     7,     8,
       0,     9,     0,    10,    11,     0,    30,     0,    31,     0,
      32,     0,     0,   101,   102,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
      25,    26,     7,     8,     0,     9,     0,    10,    11,     0,
      30,     0,    31,     0,    32,     0,     0,   238,     0,    35,
     100,     2,     3,   182,   182,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,    30,   101,    31,     0,    32,     0,
       0,   389,     0,    35,     0,     0,     0,     0,     0,     0,
       5,     6,     0,     0,     7,     8,     0,     9,     0,    10,
      11,     0,     0,     0,     2,     3,     0,     0,     0,     0,
       0,     0,     0,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,     0,    25,    26,     4,     0,
       0,     0,     0,     0,     0,     0,    30,     0,    31,     0,
      32,     0,     0,     5,     6,    35,     0,     7,     8,     0,
       9,     0,    10,    11,    12,    13,    14,    15,     0,    16,
       2,     3,    17,     0,     0,    18,    19,    20,    21,     0,
      22,     0,    23,    24,     0,     0,     0,     0,     0,    25,
      26,     0,     0,  -181,     4,     0,    28,    29,     0,    30,
       0,    31,   282,    32,     0,   283,     0,   284,    35,     5,
       6,     0,     0,     7,     8,     0,     9,     0,    10,    11,
      12,    13,    14,    15,     0,    16,     2,     3,    17,     0,
       0,    18,    19,    20,    21,     0,    22,     0,    23,    24,
       0,     0,     0,     0,     0,    25,    26,     0,     0,  -181,
       4,     0,    28,    29,     0,    30,     0,    31,     0,    32,
       0,   179,     0,   180,    35,     5,     6,     0,     0,     7,
       8,     0,     9,     0,    10,    11,    12,    13,    14,    15,
       0,    16,     2,     3,    17,     0,     0,    18,    19,    20,
      21,     0,    22,     0,    23,    24,     0,     0,     0,     0,
       0,    25,    26,     0,     0,  -181,     4,     0,    28,    29,
       0,    30,     0,    31,     0,    32,     0,     0,     0,     0,
      35,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      10,    11,    12,    13,    14,    15,     0,    16,     2,     3,
      17,     0,     0,    18,    19,    20,    21,     0,    22,     0,
      23,    24,     0,     0,     0,     2,     3,    25,    26,     0,
       0,     0,     4,     0,    28,    29,     0,    30,     0,    31,
       0,    32,     2,     3,     0,     0,    35,     5,     6,     4,
       0,     7,     8,     0,     9,     0,    10,    11,     0,     0,
       0,     0,     0,     0,     5,     6,     4,     0,     7,     8,
       0,     9,     0,    10,    11,     0,     0,     0,     0,     0,
       0,     5,     6,    25,    26,     7,     8,     0,     9,     0,
      10,    11,     0,    30,     0,    31,     0,    32,     2,     3,
      25,    26,    76,     0,     0,     0,     0,     0,     0,     0,
      30,     0,    31,     0,    32,   228,   229,    25,    26,    35,
       0,     0,     4,     0,     0,     0,     0,   181,     0,    31,
       0,    32,     0,     0,     0,     0,    76,     5,     6,   230,
       0,     7,     8,     0,     9,     0,    10,    11,     0,     0,
       0,     0,     0,     0,   231,   232,     0,     0,     7,     8,
       0,     9,     0,    10,    11,     0,     0,     0,     0,     0,
       0,     0,     0,    25,    26,     0,     0,     0,     0,   122,
     123,   124,   125,   184,     0,    31,     0,    32,     0,     0,
      25,    26,    76,     0,     0,     0,     0,     0,     0,     0,
      30,     0,    31,     0,    32,     0,     0,     0,     0,    76,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,  -117,     0,     0,     0,     0,     0,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,  -117,   143,   144,   145,   146,   147,   148,     0,   149,
     150,   151,   152,   153,   154,     0,     0,     0,     0,     0,
       0,   155,     0,     0,   138,   139,   140,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   366,     0,     0,     0,     0,     0,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   368,     0,     0,     0,     0,     0,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169
};

static const yytype_int16 yycheck[] =
{
       0,     0,   186,   102,   188,    32,   351,    83,    84,   137,
      92,    41,    94,   412,    51,   113,     2,     3,     4,     5,
       6,     1,   205,    23,    24,    29,    13,    14,    15,    16,
      17,   113,    44,    45,    21,    22,    51,    50,    29,   138,
      85,   140,    29,    50,    75,    53,    54,    51,    93,    29,
      52,    52,    96,    97,   234,   235,    51,    93,    95,    90,
      51,    42,    43,    44,    45,    46,    47,     0,   136,   137,
      72,    51,     4,   472,    30,    31,    32,    90,    90,    91,
      92,    68,    75,    90,    85,    51,     3,    82,    83,   290,
     120,   292,    92,   294,    94,   296,    96,    95,    96,    94,
     228,   229,   230,   231,   232,   181,    84,   205,   184,    90,
      91,    92,    96,   113,    98,   101,    82,    83,   118,   118,
     100,    93,    61,    62,    96,   470,    98,    90,    90,    85,
      93,    87,    88,    96,   317,    98,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   102,   327,   328,   329,
     330,   331,    97,    98,   337,    86,   142,    93,    89,    90,
     228,   229,   230,   231,   232,    93,    95,     3,    96,    98,
      98,   171,   172,   173,   100,    96,   203,    98,    23,    24,
     207,     3,   138,   367,   140,   369,    98,   187,    76,    77,
      78,    79,   192,   193,    98,    98,   100,   100,    52,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,    85,   215,   215,    98,    98,   317,
     100,   100,    23,    24,    98,   181,    27,   325,   184,    30,
      31,    32,    33,    34,    35,   334,   335,    64,    65,   337,
      97,    98,    91,   325,    51,    52,     3,   203,    91,   205,
       3,   207,     7,     8,    23,    24,    25,    26,    27,    28,
     191,    30,    31,    32,    33,    34,    35,   198,   187,    51,
      52,     3,   272,   192,   193,    59,   460,   277,    51,    52,
      30,    36,    37,    38,    39,   241,   100,    42,    43,    44,
      45,    46,    47,    70,    27,    91,    52,   481,   285,   286,
     287,   288,    23,    24,    25,    52,    27,    28,   100,    30,
      31,    32,    33,    34,    35,   315,   315,    98,    52,   306,
     307,   100,    23,    24,    91,   325,    27,    28,     3,    30,
      31,    32,    33,    34,    35,    90,    91,    92,    90,    52,
      52,   341,   342,   299,   275,   301,   346,    52,    52,   349,
      52,   100,   352,    52,   354,    23,    24,   313,   289,   100,
      96,   317,    30,    31,    32,    33,    34,    35,    52,    24,
     370,   302,   372,   304,   361,   378,   275,   325,   334,   335,
     435,   337,   378,   352,   361,   346,   471,   361,   375,   376,
     361,   361,   473,    38,   381,   475,   383,   397,    38,   198,
     400,    -1,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,
     366,   411,   368,   413,   414,   371,   347,    -1,    -1,    -1,
      -1,    -1,    -1,   423,    -1,    -1,    -1,    -1,    -1,    -1,
     349,   362,   363,   364,   365,    -1,   392,    -1,    -1,    -1,
     440,    -1,   373,   374,    -1,    -1,   402,    -1,    -1,    -1,
      -1,   370,    -1,   372,    -1,    -1,   456,    -1,   458,    -1,
      -1,    -1,    -1,   463,   464,   465,   422,    -1,    -1,   469,
      -1,   471,    -1,   473,    -1,   475,   476,    -1,    -1,    -1,
      -1,   400,    -1,    -1,    -1,   416,    -1,   418,    -1,    -1,
      -1,    -1,    -1,   424,   425,    -1,    -1,    -1,   429,   430,
     500,   457,    -1,    -1,   423,    -1,   462,   507,    -1,   509,
      -1,    -1,    -1,    -1,   445,    -1,    -1,   448,   474,   450,
      -1,    -1,   453,    -1,   455,    -1,    -1,    -1,    -1,    -1,
     486,    -1,    -1,    -1,    -1,    -1,    -1,   456,    -1,   458,
      -1,    -1,    -1,    -1,   463,   464,   465,    -1,     1,   480,
      -1,    -1,     5,     6,    -1,    -1,    -1,   476,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   498,    -1,    -1,
     501,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,   500,    -1,    -1,    -1,    -1,    -1,    -1,   507,    -1,
     509,    44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
      53,    54,    55,    56,    57,    58,    -1,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    68,    69,    -1,    71,    -1,
      73,    74,     4,     5,     6,    -1,    -1,    80,    81,    -1,
      -1,    84,    85,    86,    87,    88,    -1,    90,    -1,    92,
      93,    94,    -1,    96,    -1,    98,    99,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,    -1,
      -1,    -1,    44,    45,    -1,    -1,    48,    49,    -1,    51,
      -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       4,     5,     6,    -1,    -1,    -1,    44,    45,    80,    81,
      48,    49,    -1,    51,    -1,    53,    54,    -1,    90,    -1,
      92,    -1,    94,    -1,    -1,    29,    -1,    99,   100,    -1,
      -1,    -1,    -1,    -1,     4,     5,     6,    -1,    -1,    -1,
      44,    45,    80,    81,    48,    49,    -1,    51,    -1,    53,
      54,    -1,    90,    -1,    92,    -1,    94,    -1,    -1,    29,
      -1,    99,   100,    -1,    -1,    -1,    -1,    -1,     4,     5,
       6,    -1,    -1,    -1,    44,    45,    80,    81,    48,    49,
      -1,    51,    -1,    53,    54,    -1,    90,    -1,    92,    -1,
      94,    -1,    -1,    29,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      80,    81,    48,    49,    -1,    51,    -1,    53,    54,    -1,
      90,    -1,    92,    -1,    94,    -1,    -1,    97,    -1,    99,
       4,     5,     6,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    29,    92,    -1,    94,    -1,
      -1,    97,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,
      54,    -1,    -1,    -1,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,    -1,    80,    81,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    92,    -1,
      94,    -1,    -1,    44,    45,    99,    -1,    48,    49,    -1,
      51,    -1,    53,    54,    55,    56,    57,    58,    -1,    60,
       5,     6,    63,    -1,    -1,    66,    67,    68,    69,    -1,
      71,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    80,
      81,    -1,    -1,    84,    29,    -1,    87,    88,    -1,    90,
      -1,    92,    93,    94,    -1,    96,    -1,    98,    99,    44,
      45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,    54,
      55,    56,    57,    58,    -1,    60,     5,     6,    63,    -1,
      -1,    66,    67,    68,    69,    -1,    71,    -1,    73,    74,
      -1,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    84,
      29,    -1,    87,    88,    -1,    90,    -1,    92,    -1,    94,
      -1,    96,    -1,    98,    99,    44,    45,    -1,    -1,    48,
      49,    -1,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    60,     5,     6,    63,    -1,    -1,    66,    67,    68,
      69,    -1,    71,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    80,    81,    -1,    -1,    84,    29,    -1,    87,    88,
      -1,    90,    -1,    92,    -1,    94,    -1,    -1,    -1,    -1,
      99,    44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
      53,    54,    55,    56,    57,    58,    -1,    60,     5,     6,
      63,    -1,    -1,    66,    67,    68,    69,    -1,    71,    -1,
      73,    74,    -1,    -1,    -1,     5,     6,    80,    81,    -1,
      -1,    -1,    29,    -1,    87,    88,    -1,    90,    -1,    92,
      -1,    94,     5,     6,    -1,    -1,    99,    44,    45,    29,
      -1,    48,    49,    -1,    51,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    29,    -1,    48,    49,
      -1,    51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    80,    81,    48,    49,    -1,    51,    -1,
      53,    54,    -1,    90,    -1,    92,    -1,    94,     5,     6,
      80,    81,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    92,    -1,    94,     5,     6,    80,    81,    99,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    90,    -1,    92,
      -1,    94,    -1,    -1,    -1,    -1,    99,    44,    45,    29,
      -1,    48,    49,    -1,    51,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    48,    49,
      -1,    51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,     5,
       6,     7,     8,    90,    -1,    92,    -1,    94,    -1,    -1,
      80,    81,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    92,    -1,    94,    -1,    -1,    -1,    -1,    99,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     3,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    -1,    90,    91,    92,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     3,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     3,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,     6,    29,    44,    45,    48,    49,    51,
      53,    54,    55,    56,    57,    58,    60,    63,    66,    67,
      68,    69,    71,    73,    74,    80,    81,    86,    87,    88,
      90,    92,    94,    96,    98,    99,   102,   103,   104,   108,
     109,   111,   112,   113,   114,   115,   116,   118,   121,   122,
     123,   128,   130,   131,   132,   133,   134,   135,   136,   137,
     141,   142,   147,   152,   153,   154,   155,   164,   165,   166,
     171,   173,   174,   198,   199,   200,    99,   111,   128,   128,
     128,   128,   128,   197,   197,   197,   197,   197,   197,   197,
     197,   111,   138,   140,   138,    93,   201,   202,   197,   135,
       4,    29,    98,   119,   120,   124,   125,   126,   135,   117,
     120,    75,    90,   156,   158,     0,    85,    93,   199,   200,
     110,   114,     5,     6,     7,     8,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    90,    91,
      92,   127,     4,    23,    24,    25,    26,    27,    28,    30,
      31,    32,    33,    34,    35,     3,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      84,   197,    90,   175,    93,    96,    98,   203,   204,    96,
      98,    90,   132,   133,    90,   133,   135,   204,   135,   143,
     144,   135,   204,   204,     3,   140,   105,   106,   107,   108,
      93,   100,   126,    96,    97,    98,    95,    96,     1,    29,
     125,   140,   159,   160,   161,   196,   108,   114,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,     5,     6,
      29,    44,    45,   123,   129,   129,   100,   126,    97,   126,
      50,    90,   128,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
      82,    83,    94,   111,   162,   167,   168,    29,   111,   176,
     177,   111,    93,    96,    98,    76,    77,    78,    79,   180,
     181,   182,   185,   186,   188,   189,   192,   193,   133,     3,
     133,     3,   196,   105,   196,    52,    61,    62,   145,   146,
     204,   105,   105,   139,    85,   203,   204,    98,   120,   124,
     125,   135,   120,   100,   157,    98,   108,   129,   129,   129,
     129,   129,    44,    45,    90,    92,   127,    98,   100,    97,
     135,    91,    91,    95,   111,   163,     3,   158,   169,   204,
     111,     3,    98,   100,    30,   178,   179,   197,   197,   197,
     197,   204,   175,   175,   175,   175,     3,   135,     3,   135,
     204,    59,   204,   197,   197,    64,    65,   148,   149,   150,
     151,    70,    52,    72,   135,   108,   161,   100,   126,    97,
     126,    50,    90,   100,   111,   111,    95,    98,   111,   168,
     204,   105,   139,   177,   111,    27,   182,   186,   189,   193,
     197,   204,   204,   204,   204,   135,   196,   135,   196,   105,
     135,   105,   204,   204,   197,   197,    52,   150,   151,   197,
     197,   100,    97,   135,   111,   105,    52,    85,   170,   135,
      91,   111,    52,   172,   111,   183,   184,   166,   187,   111,
     190,   191,   111,   194,   195,   100,   204,    98,   204,    52,
     135,   105,   204,   204,   204,   204,   100,   170,   111,    91,
       3,   204,   204,   204,    90,   204,   204,   105,   135,   105,
     196,   135,   105,   105,   105,   111,   139,    52,   184,    52,
     166,    52,   191,   135,    52,   195,   105,    52,   100,    52,
     204,   196,    52,    52,   135,   100,    52,   204,   105,   204,
      96,   105,   105,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   101,   102,   102,   102,   103,   103,   104,   104,   105,
     105,   106,   107,   107,   108,   108,   108,   109,   110,   110,
     111,   112,   113,   114,   114,   115,   115,   115,   116,   117,
     117,   118,   119,   119,   120,   120,   120,   120,   120,   120,
     121,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   125,   126,   126,   126,   126,   126,   126,   127,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   135,   135,   135,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   138,   138,   139,   140,
     140,   141,   141,   142,   143,   143,   144,   144,   145,   146,
     147,   148,   148,   148,   148,   149,   149,   150,   151,   152,
     152,   152,   152,   152,   152,   153,   153,   153,   154,   154,
     154,   155,   156,   157,   158,   158,   159,   159,   160,   160,
     161,   161,   162,   162,   162,   163,   163,   164,   165,   166,
     166,   167,   167,   167,   168,   169,   169,   170,   170,   171,
     172,   173,   174,   175,   175,   176,   176,   177,   177,   177,
     178,   178,   179,   179,   179,   179,   180,   180,   180,   180,
     180,   180,   180,   180,   181,   182,   183,   183,   184,   184,
     185,   186,   187,   187,   188,   189,   190,   190,   191,   192,
     193,   194,   194,   195,   196,   197,   198,   198,   199,   199,
     199,   199,   200,   200,   201,   201,   202,   202,   203,   203,
     203,   203,   203,   203,   204,   204
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     2,     1,     3,     0,
       1,     2,     1,     3,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     1,     3,     0,     1,     1,     2,     2,     3,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     1,
       2,     2,     3,     4,     3,     4,     2,     2,     3,     5,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     2,     2,
       3,     4,     3,     4,     3,     5,     2,     2,     2,     2,
       2,     1,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     0,     1,
       4,     1,     1,     4,     1,     2,     4,     2,     7,     4,
       6,     0,     1,     1,     2,     1,     2,     7,     4,     7,
       6,     9,    10,     9,    12,     1,     1,     1,     9,     9,
       5,     0,     1,     1,     3,     2,     0,     1,     1,     3,
       1,     1,     2,     1,     3,     1,     3,     4,     2,     3,
       5,     1,     3,     3,     2,     4,     3,     1,     1,     2,
       1,     4,     6,     0,     3,     1,     3,     1,     4,     2,
       0,     1,     4,     2,     5,     3,     1,     1,     1,     1,
       3,     3,     3,     3,     2,     6,     1,     3,     1,     5,
       2,     6,     1,     3,     2,     6,     1,     3,     1,     2,
       6,     1,     3,     4,     0,     0,     1,     1,     1,     1,
       2,     2,     0,     1,     0,     1,     1,     2,     1,     1,
       1,     2,     2,     2,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if OCTAVE_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, parser); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, octave_base_parser& parser)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (parser);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, octave_base_parser& parser)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, octave_base_parser& parser)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, parser); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !OCTAVE_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !OCTAVE_DEBUG */


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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, octave_base_parser& parser)
{
  YYUSE (yyvaluep);
  YYUSE (parser);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 3: /* '='  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1830 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 4: /* ':'  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1836 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 5: /* '-'  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1842 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 6: /* '+'  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1848 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 7: /* '*'  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1854 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 8: /* '/'  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1860 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 9: /* ADD_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1866 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 10: /* SUB_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1872 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 11: /* MUL_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1878 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 12: /* DIV_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1884 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 13: /* LEFTDIV_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1890 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 14: /* POW_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1896 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 15: /* EMUL_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1902 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 16: /* EDIV_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1908 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 17: /* ELEFTDIV_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1914 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 18: /* EPOW_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1920 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 19: /* AND_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1926 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 20: /* OR_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1932 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 21: /* LSHIFT_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1938 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 22: /* RSHIFT_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1944 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 23: /* LSHIFT  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1950 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 24: /* RSHIFT  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1956 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 25: /* EXPR_AND_AND  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1962 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 26: /* EXPR_OR_OR  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1968 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 27: /* EXPR_AND  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1974 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 28: /* EXPR_OR  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1980 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 29: /* EXPR_NOT  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1986 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 30: /* EXPR_LT  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1992 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 31: /* EXPR_LE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 1998 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 32: /* EXPR_EQ  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2004 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 33: /* EXPR_NE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2010 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 34: /* EXPR_GE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2016 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 35: /* EXPR_GT  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2022 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 36: /* LEFTDIV  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2028 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 37: /* EMUL  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2034 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 38: /* EDIV  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2040 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 39: /* ELEFTDIV  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2046 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 40: /* EPLUS  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2052 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 41: /* EMINUS  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2058 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 42: /* HERMITIAN  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2064 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 43: /* TRANSPOSE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2070 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 44: /* PLUS_PLUS  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2076 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 45: /* MINUS_MINUS  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2082 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 46: /* POW  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2088 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 47: /* EPOW  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2094 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 48: /* NUM  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2100 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 49: /* IMAG_NUM  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2106 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 50: /* STRUCT_ELT  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2112 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 51: /* NAME  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2118 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 52: /* END  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2124 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 53: /* DQ_STRING  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2130 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 54: /* SQ_STRING  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2136 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 55: /* FOR  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2142 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 56: /* PARFOR  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2148 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 57: /* WHILE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2154 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 58: /* DO  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2160 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 59: /* UNTIL  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2166 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 60: /* IF  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2172 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 61: /* ELSEIF  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2178 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 62: /* ELSE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2184 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 63: /* SWITCH  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2190 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 64: /* CASE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2196 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 65: /* OTHERWISE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2202 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 66: /* BREAK  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2208 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 67: /* CONTINUE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2214 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 68: /* FUNC_RET  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2220 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 69: /* UNWIND  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2226 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 70: /* CLEANUP  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2232 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 71: /* TRY  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2238 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 72: /* CATCH  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2244 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 73: /* GLOBAL  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2250 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 74: /* PERSISTENT  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2256 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 75: /* FCN_HANDLE  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2262 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 76: /* PROPERTIES  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2268 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 77: /* METHODS  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2274 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 78: /* EVENTS  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2280 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 79: /* ENUMERATION  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2286 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 80: /* METAQUERY  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2292 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 81: /* SUPERCLASSREF  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2298 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 82: /* GET  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2304 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 83: /* SET  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2310 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 84: /* FCN  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2316 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 85: /* END_OF_INPUT  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2322 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 86: /* LEXICAL_ERROR  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2328 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 87: /* INPUT_FILE  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2334 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 88: /* CLASSDEF  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2340 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 89: /* UNARY  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2346 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 90: /* '('  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2352 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 91: /* '.'  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2358 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 92: /* '{'  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2364 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 93: /* '\n'  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2370 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 94: /* '['  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2376 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 95: /* ']'  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2382 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 96: /* ';'  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2388 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 97: /* '}'  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2394 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 98: /* ','  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2400 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 99: /* '@'  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2406 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 100: /* ')'  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2412 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 102: /* input  */
#line 306 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_type); }
#line 2418 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 103: /* simple_list  */
#line 329 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_statement_list_type); }
#line 2424 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 104: /* simple_list1  */
#line 329 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_statement_list_type); }
#line 2430 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 105: /* opt_list  */
#line 329 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_statement_list_type); }
#line 2436 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 106: /* list  */
#line 329 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_statement_list_type); }
#line 2442 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 107: /* list1  */
#line 329 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_statement_list_type); }
#line 2448 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 108: /* statement  */
#line 328 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_statement_type); }
#line 2454 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 109: /* word_list_cmd  */
#line 314 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_index_expression_type); }
#line 2460 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 110: /* word_list  */
#line 316 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_argument_list_type); }
#line 2466 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 111: /* identifier  */
#line 313 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_identifier_type); }
#line 2472 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 112: /* superclass_identifier  */
#line 313 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_identifier_type); }
#line 2478 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 113: /* meta_identifier  */
#line 313 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_identifier_type); }
#line 2484 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 114: /* string  */
#line 310 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_constant_type); }
#line 2490 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 115: /* constant  */
#line 310 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_constant_type); }
#line 2496 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 116: /* matrix  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2502 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 117: /* matrix_rows  */
#line 307 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_matrix_type); }
#line 2508 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 118: /* cell  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2514 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 119: /* cell_rows  */
#line 308 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_cell_type); }
#line 2520 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 120: /* cell_or_matrix_row  */
#line 316 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_argument_list_type); }
#line 2526 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 121: /* fcn_handle  */
#line 311 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_fcn_handle_type); }
#line 2532 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 122: /* anon_fcn_handle  */
#line 312 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_anon_fcn_handle_type); }
#line 2538 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 123: /* primary_expr  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2544 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 124: /* magic_colon  */
#line 310 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_constant_type); }
#line 2550 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 125: /* magic_tilde  */
#line 313 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_identifier_type); }
#line 2556 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 126: /* arg_list  */
#line 316 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_argument_list_type); }
#line 2562 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 127: /* indirect_ref_op  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2568 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 128: /* oper_expr  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2574 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 129: /* power_expr  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2580 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 130: /* colon_expr  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2586 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 131: /* colon_expr1  */
#line 315 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_colon_expression_type); }
#line 2592 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 132: /* simple_expr  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2598 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 133: /* assign_lhs  */
#line 316 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_argument_list_type); }
#line 2604 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 134: /* assign_expr  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2610 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 135: /* expression  */
#line 309 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_expression_type); }
#line 2616 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 136: /* command  */
#line 318 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_command_type); }
#line 2622 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 137: /* declaration  */
#line 327 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_decl_command_type); }
#line 2628 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 138: /* decl1  */
#line 326 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_decl_init_list_type); }
#line 2634 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 139: /* decl_param_init  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2640 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 140: /* decl2  */
#line 325 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_decl_elt_type); }
#line 2646 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 141: /* select_command  */
#line 318 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_command_type); }
#line 2652 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 142: /* if_command  */
#line 319 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_if_command_type); }
#line 2658 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 143: /* if_cmd_list  */
#line 321 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_if_command_list_type); }
#line 2664 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 144: /* if_cmd_list1  */
#line 321 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_if_command_list_type); }
#line 2670 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 145: /* elseif_clause  */
#line 320 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_if_clause_type); }
#line 2676 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 146: /* else_clause  */
#line 320 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_if_clause_type); }
#line 2682 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 147: /* switch_command  */
#line 322 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_switch_command_type); }
#line 2688 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 148: /* case_list  */
#line 324 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_switch_case_list_type); }
#line 2694 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 149: /* case_list1  */
#line 324 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_switch_case_list_type); }
#line 2700 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 150: /* switch_case  */
#line 323 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_switch_case_type); }
#line 2706 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 151: /* default_case  */
#line 323 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_switch_case_type); }
#line 2712 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 152: /* loop_command  */
#line 318 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_command_type); }
#line 2718 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 153: /* jump_command  */
#line 318 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_command_type); }
#line 2724 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 154: /* except_command  */
#line 318 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_command_type); }
#line 2730 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 155: /* push_fcn_symtab  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2736 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 156: /* param_list_beg  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2742 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 157: /* param_list_end  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2748 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 158: /* param_list  */
#line 317 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_parameter_list_type); }
#line 2754 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 159: /* param_list1  */
#line 317 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_parameter_list_type); }
#line 2760 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 160: /* param_list2  */
#line 317 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_parameter_list_type); }
#line 2766 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 161: /* param_list_elt  */
#line 325 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_decl_elt_type); }
#line 2772 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 162: /* return_list  */
#line 317 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_parameter_list_type); }
#line 2778 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 163: /* return_list1  */
#line 317 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_parameter_list_type); }
#line 2784 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 164: /* file  */
#line 318 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_command_type); }
#line 2790 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 165: /* function_beg  */
#line 301 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2796 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 166: /* function  */
#line 318 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_command_type); }
#line 2802 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 167: /* fcn_name  */
#line 313 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_identifier_type); }
#line 2808 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 168: /* function1  */
#line 330 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).octave_user_function_type); }
#line 2814 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 169: /* function2  */
#line 330 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).octave_user_function_type); }
#line 2820 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 170: /* function_end  */
#line 328 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_statement_type); }
#line 2826 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 171: /* classdef_beg  */
#line 302 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2832 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 172: /* classdef_end  */
#line 328 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_statement_type); }
#line 2838 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 173: /* classdef1  */
#line 330 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).octave_user_function_type); }
#line 2844 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 174: /* classdef  */
#line 318 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_command_type); }
#line 2850 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 175: /* opt_attr_list  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2856 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 176: /* attr_list  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2862 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 177: /* attr  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2868 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 178: /* opt_superclasses  */
#line 317 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_parameter_list_type); }
#line 2874 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 179: /* superclasses  */
#line 317 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).tree_parameter_list_type); }
#line 2880 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 180: /* class_body  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2886 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 181: /* properties_beg  */
#line 302 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2892 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 182: /* properties_block  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2898 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 183: /* properties_list  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2904 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 184: /* class_property  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2910 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 185: /* methods_beg  */
#line 302 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2916 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 186: /* methods_block  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2922 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 187: /* methods_list  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2928 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 188: /* events_beg  */
#line 302 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2934 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 189: /* events_block  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2940 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 190: /* events_list  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2946 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 191: /* class_event  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2952 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 192: /* enum_beg  */
#line 302 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2958 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 193: /* enum_block  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2964 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 194: /* enum_list  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2970 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 195: /* class_enum  */
#line 303 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2976 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 196: /* stmt_begin  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2982 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 197: /* stash_comment  */
#line 302 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2988 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 198: /* parse_error  */
#line 304 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 2994 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 199: /* sep_no_nl  */
#line 300 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 3000 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 200: /* opt_sep_no_nl  */
#line 300 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 3006 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 201: /* opt_nl  */
#line 300 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 3012 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 202: /* nl  */
#line 300 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 3018 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 203: /* sep  */
#line 300 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 3024 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;

    case 204: /* opt_sep  */
#line 300 "parse-tree/oct-parse.yy" /* yacc.c:1257  */
      { }
#line 3030 "parse-tree/oct-parse.cc" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}



struct yypstate
  {
    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;
    /* Used to determine if this is the first time this instance has
       been used.  */
    int yynew;
  };

int
yyparse (octave_base_parser& parser)
{
  return yypull_parse (YY_NULLPTR, parser);
}

int
yypull_parse (yypstate *yyps, octave_base_parser& parser)
{
  int yystatus;
  yypstate *yyps_local;
  int yychar;
  YYSTYPE yylval;
  if (yyps)
    yyps_local = yyps;
  else
    {
      yyps_local = yypstate_new ();
      if (!yyps_local)
        {
          yyerror (parser, YY_("memory exhausted"));
          return 2;
        }
    }
  do {
    yychar = yylex (&yylval, scanner);
    yystatus =
      yypush_parse (yyps_local, yychar, &yylval, parser);
  } while (yystatus == YYPUSH_MORE);
  if (!yyps)
    yypstate_delete (yyps_local);
  return yystatus;
}

/* Initialize the parser data structure.  */
yypstate *
yypstate_new (void)
{
  yypstate *yyps;
  yyps = (yypstate *) malloc (sizeof *yyps);
  if (!yyps)
    return YY_NULLPTR;
  yyps->yynew = 1;
  return yyps;
}

void
yypstate_delete (yypstate *yyps)
{
#ifndef yyoverflow
  /* If the stack was reallocated but the parse did not complete, then the
     stack still needs to be freed.  */
  if (!yyps->yynew && yyps->yyss != yyps->yyssa)
    YYSTACK_FREE (yyps->yyss);
#endif
  free (yyps);
}

#define octave_nerrs yyps->octave_nerrs
#define yystate yyps->yystate
#define yyerrstatus yyps->yyerrstatus
#define yyssa yyps->yyssa
#define yyss yyps->yyss
#define yyssp yyps->yyssp
#define yyvsa yyps->yyvsa
#define yyvs yyps->yyvs
#define yyvsp yyps->yyvsp
#define yystacksize yyps->yystacksize


/*---------------.
| yypush_parse.  |
`---------------*/

int
yypush_parse (yypstate *yyps, int yypushed_char, YYSTYPE const *yypushed_val, octave_base_parser& parser)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  if (!yyps->yynew)
    {
      yyn = yypact[yystate];
      goto yyread_pushed_token;
    }

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      if (!yyps->yynew)
        {
          YYDPRINTF ((stderr, "Return for a new token:\n"));
          yyresult = YYPUSH_MORE;
          goto yypushreturn;
        }
      yyps->yynew = 0;
yyread_pushed_token:
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yypushed_char;
      if (yypushed_val)
        yylval = *yypushed_val;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 348 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    parser.stmt_list = (yyvsp[-1].tree_statement_list_type);
                    YYACCEPT;
                  }
#line 3392 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 353 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.end_of_input = true;
                    parser.stmt_list = (yyvsp[-1].tree_statement_list_type);
                    YYACCEPT;
                  }
#line 3402 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 359 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { ABORT_PARSE; }
#line 3408 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 363 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = 0; }
#line 3414 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 365 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = parser.set_stmt_print_flag ((yyvsp[-1].tree_statement_list_type), (yyvsp[0].sep_type), false); }
#line 3420 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 369 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = parser.make_statement_list ((yyvsp[0].tree_statement_type)); }
#line 3426 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 371 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = parser.append_statement_list ((yyvsp[-2].tree_statement_list_type), (yyvsp[-1].sep_type), (yyvsp[0].tree_statement_type), false); }
#line 3432 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 375 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = new tree_statement_list (); }
#line 3438 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 377 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = (yyvsp[0].tree_statement_list_type); }
#line 3444 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 381 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = parser.set_stmt_print_flag ((yyvsp[-1].tree_statement_list_type), (yyvsp[0].sep_type), true); }
#line 3450 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 385 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = parser.make_statement_list ((yyvsp[0].tree_statement_type)); }
#line 3456 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 387 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_list_type) = parser.append_statement_list ((yyvsp[-2].tree_statement_list_type), (yyvsp[-1].sep_type), (yyvsp[0].tree_statement_type), true); }
#line 3462 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 391 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_type) = parser.make_statement ((yyvsp[0].tree_expression_type)); }
#line 3468 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 393 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_type) = parser.make_statement ((yyvsp[0].tree_command_type)); }
#line 3474 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 395 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_statement_type) = parser.make_statement ((yyvsp[0].tree_index_expression_type)); }
#line 3480 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 407 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_index_expression_type) = parser.make_index_expression ((yyvsp[-1].tree_identifier_type), (yyvsp[0].tree_argument_list_type), '(');
                    if (! (yyval.tree_index_expression_type))
                      {
                        // make_index_expression deleted $1 and $2.
                        ABORT_PARSE;
                      }
                  }
#line 3493 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 418 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[0].tree_constant_type)); }
#line 3499 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 420 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-1].tree_argument_list_type)->append ((yyvsp[0].tree_constant_type));
                    (yyval.tree_argument_list_type) = (yyvsp[-1].tree_argument_list_type);
                  }
#line 3508 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 431 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    symbol_table::symbol_record *sr = (yyvsp[0].tok_val)->sym_rec ();
                    (yyval.tree_identifier_type) = new tree_identifier (*sr, (yyvsp[0].tok_val)->line (), (yyvsp[0].tok_val)->column ());
                  }
#line 3517 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 439 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_identifier_type) = new tree_identifier ((yyvsp[0].tok_val)->line (), (yyvsp[0].tok_val)->column ()); }
#line 3523 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 443 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_identifier_type) = new tree_identifier ((yyvsp[0].tok_val)->line (), (yyvsp[0].tok_val)->column ()); }
#line 3529 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 447 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_constant_type) = parser.make_constant (DQ_STRING, (yyvsp[0].tok_val)); }
#line 3535 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 449 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_constant_type) = parser.make_constant (SQ_STRING, (yyvsp[0].tok_val)); }
#line 3541 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 453 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_constant_type) = parser.make_constant (NUM, (yyvsp[0].tok_val)); }
#line 3547 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 455 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_constant_type) = parser.make_constant (IMAG_NUM, (yyvsp[0].tok_val)); }
#line 3553 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 457 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_constant_type) = (yyvsp[0].tree_constant_type); }
#line 3559 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 461 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.finish_matrix ((yyvsp[-1].tree_matrix_type)); }
#line 3565 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 465 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_matrix_type) = (yyvsp[0].tree_argument_list_type) ? new tree_matrix ((yyvsp[0].tree_argument_list_type)) : 0; }
#line 3571 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 467 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if ((yyvsp[-2].tree_matrix_type))
                      {
                        if ((yyvsp[0].tree_argument_list_type))
                          (yyvsp[-2].tree_matrix_type)->append ((yyvsp[0].tree_argument_list_type));

                        (yyval.tree_matrix_type) = (yyvsp[-2].tree_matrix_type);
                      }
                    else
                      (yyval.tree_matrix_type) = (yyvsp[0].tree_argument_list_type) ? new tree_matrix ((yyvsp[0].tree_argument_list_type)) : 0;
                  }
#line 3587 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 481 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.finish_cell ((yyvsp[-1].tree_cell_type)); }
#line 3593 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 485 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_cell_type) = (yyvsp[0].tree_argument_list_type) ? new tree_cell ((yyvsp[0].tree_argument_list_type)) : 0; }
#line 3599 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 487 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if ((yyvsp[-2].tree_cell_type))
                      {
                        if ((yyvsp[0].tree_argument_list_type))
                          (yyvsp[-2].tree_cell_type)->append ((yyvsp[0].tree_argument_list_type));

                        (yyval.tree_cell_type) = (yyvsp[-2].tree_cell_type);
                      }
                    else
                      (yyval.tree_cell_type) = (yyvsp[0].tree_argument_list_type) ? new tree_cell ((yyvsp[0].tree_argument_list_type)) : 0;
                  }
#line 3615 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 505 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = 0; }
#line 3621 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 507 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = 0; }
#line 3627 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 509 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = (yyvsp[0].tree_argument_list_type); }
#line 3633 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 511 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = (yyvsp[-1].tree_argument_list_type); }
#line 3639 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 513 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = (yyvsp[0].tree_argument_list_type); }
#line 3645 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 515 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = (yyvsp[-1].tree_argument_list_type); }
#line 3651 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 519 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_fcn_handle_type) = parser.make_fcn_handle ((yyvsp[0].tok_val));
                    lexer.looking_at_function_handle--;
                  }
#line 3660 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 526 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_anon_fcn_handle_type) = parser.make_anon_fcn_handle ((yyvsp[-2].tree_parameter_list_type), (yyvsp[0].tree_statement_type));
                    lexer.nesting_level.remove ();
                  }
#line 3669 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 533 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_identifier_type); }
#line 3675 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 535 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_constant_type); }
#line 3681 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 537 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_fcn_handle_type); }
#line 3687 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 539 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.looking_at_matrix_or_assign_lhs = false;
                    (yyval.tree_expression_type) = (yyvsp[0].tree_expression_type);
                  }
#line 3696 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 544 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_expression_type); }
#line 3702 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 546 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_identifier_type); }
#line 3708 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 548 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_identifier_type); }
#line 3714 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 550 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[-1].tree_expression_type)->mark_in_parens (); }
#line 3720 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 554 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    octave_value tmp (octave_value::magic_colon_t);
                    (yyval.tree_constant_type) = new tree_constant (tmp);
                  }
#line 3729 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 561 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_identifier_type) = new tree_black_hole ();
                  }
#line 3737 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 567 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[0].tree_expression_type)); }
#line 3743 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 569 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[0].tree_constant_type)); }
#line 3749 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 571 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[0].tree_identifier_type)); }
#line 3755 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 573 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-2].tree_argument_list_type)->append ((yyvsp[0].tree_constant_type));
                    (yyval.tree_argument_list_type) = (yyvsp[-2].tree_argument_list_type);
                  }
#line 3764 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 578 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-2].tree_argument_list_type)->append ((yyvsp[0].tree_identifier_type));
                    (yyval.tree_argument_list_type) = (yyvsp[-2].tree_argument_list_type);
                  }
#line 3773 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 583 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-2].tree_argument_list_type)->append ((yyvsp[0].tree_expression_type));
                    (yyval.tree_argument_list_type) = (yyvsp[-2].tree_argument_list_type);
                  }
#line 3782 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 590 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { lexer.looking_at_indirect_ref = true; }
#line 3788 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 594 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_expression_type); }
#line 3794 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 596 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_postfix_op (PLUS_PLUS, (yyvsp[-1].tree_expression_type), (yyvsp[0].tok_val)); }
#line 3800 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 598 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_postfix_op (MINUS_MINUS, (yyvsp[-1].tree_expression_type), (yyvsp[0].tok_val)); }
#line 3806 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 600 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[-2].tree_expression_type), 0, '(');
                    if (! (yyval.tree_expression_type))
                      {
                        // make_index_expression deleted $1.
                        ABORT_PARSE;
                      }
                  }
#line 3819 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 609 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[-3].tree_expression_type), (yyvsp[-1].tree_argument_list_type), '(');
                    if (! (yyval.tree_expression_type))
                      {
                        // make_index_expression deleted $1 and $3.
                        ABORT_PARSE;
                      }
                  }
#line 3832 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 618 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[-2].tree_expression_type), 0, '{');
                    if (! (yyval.tree_expression_type))
                      {
                        // make_index_expression deleted $1.
                        ABORT_PARSE;
                      }
                  }
#line 3845 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 627 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[-3].tree_expression_type), (yyvsp[-1].tree_argument_list_type), '{');
                    if (! (yyval.tree_expression_type))
                      {
                        // make_index_expression deleted $1 and $3.
                        ABORT_PARSE;
                      }
                  }
#line 3858 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 636 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_postfix_op (HERMITIAN, (yyvsp[-1].tree_expression_type), (yyvsp[0].tok_val)); }
#line 3864 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 638 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_postfix_op (TRANSPOSE, (yyvsp[-1].tree_expression_type), (yyvsp[0].tok_val)); }
#line 3870 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 640 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_indirect_ref ((yyvsp[-2].tree_expression_type), (yyvsp[0].tok_val)->text ()); }
#line 3876 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 642 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_indirect_ref ((yyvsp[-4].tree_expression_type), (yyvsp[-1].tree_expression_type)); }
#line 3882 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 644 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op (PLUS_PLUS, (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 3888 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 646 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op (MINUS_MINUS, (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 3894 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 648 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op (EXPR_NOT, (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 3900 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 650 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op ('+', (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 3906 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 652 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op ('-', (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 3912 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 654 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (POW, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3918 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 656 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EPOW, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3924 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 658 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op ('+', (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3930 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 660 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op ('-', (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3936 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 662 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op ('*', (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3942 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 664 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op ('/', (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3948 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 666 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op ('+', (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3954 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 668 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op ('-', (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3960 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 670 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EMUL, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3966 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 672 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EDIV, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3972 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 674 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (LEFTDIV, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3978 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 676 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (ELEFTDIV, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 3984 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 680 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_expression_type); }
#line 3990 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 682 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_postfix_op (PLUS_PLUS, (yyvsp[-1].tree_expression_type), (yyvsp[0].tok_val)); }
#line 3996 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 684 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_postfix_op (MINUS_MINUS, (yyvsp[-1].tree_expression_type), (yyvsp[0].tok_val)); }
#line 4002 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 686 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[-2].tree_expression_type), 0, '(');
                    if (! (yyval.tree_expression_type))
                      {
                        // make_index_expression deleted $1.
                        ABORT_PARSE;
                      }
                  }
#line 4015 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 695 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[-3].tree_expression_type), (yyvsp[-1].tree_argument_list_type), '(');
                    if (! (yyval.tree_expression_type))
                      {
                        // make_index_expression deleted $1 and $3.
                        ABORT_PARSE;
                      }
                  }
#line 4028 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 704 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[-2].tree_expression_type), 0, '{');
                    if (! (yyval.tree_expression_type))
                      {
                        // make_index_expression deleted $1.
                        ABORT_PARSE;
                      }
                  }
#line 4041 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 713 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[-3].tree_expression_type), (yyvsp[-1].tree_argument_list_type), '{');
                    if (! (yyval.tree_expression_type))
                      {
                        // make_index_expression deleted $1 and $3.
                        ABORT_PARSE;
                      }
                  }
#line 4054 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 722 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_indirect_ref ((yyvsp[-2].tree_expression_type), (yyvsp[0].tok_val)->text ()); }
#line 4060 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 724 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_indirect_ref ((yyvsp[-4].tree_expression_type), (yyvsp[-1].tree_expression_type)); }
#line 4066 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 726 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op (PLUS_PLUS, (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 4072 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 728 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op (MINUS_MINUS, (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 4078 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 730 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op (EXPR_NOT, (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 4084 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 732 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op ('+', (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 4090 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 734 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_prefix_op ('-', (yyvsp[0].tree_expression_type), (yyvsp[-1].tok_val)); }
#line 4096 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 738 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.finish_colon_expression ((yyvsp[0].tree_colon_expression_type)); }
#line 4102 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 742 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_colon_expression_type) = new tree_colon_expression ((yyvsp[0].tree_expression_type)); }
#line 4108 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 744 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_colon_expression_type) = (yyvsp[-2].tree_colon_expression_type)->append ((yyvsp[0].tree_expression_type))))
                      {
                        delete (yyvsp[-2].tree_colon_expression_type);
                        delete (yyvsp[0].tree_expression_type);
                        ABORT_PARSE;
                      }
                  }
#line 4121 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 755 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_expression_type); }
#line 4127 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 757 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (LSHIFT, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4133 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 759 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (RSHIFT, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4139 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 761 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_LT, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4145 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 763 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_LE, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4151 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 765 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_EQ, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4157 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 767 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_GE, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4163 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 769 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_GT, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4169 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 771 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_NE, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4175 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 773 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_AND, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4181 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 775 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_OR, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4187 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 777 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_boolean_op (EXPR_AND_AND, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4193 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 779 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_boolean_op (EXPR_OR_OR, (yyvsp[-2].tree_expression_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4199 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 783 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_argument_list_type) = parser.validate_matrix_for_assignment ((yyvsp[0].tree_expression_type));

                    if ((yyval.tree_argument_list_type))
                      { lexer.looking_at_matrix_or_assign_lhs = false; }
                    else
                      {
                        // validate_matrix_for_assignment deleted $1.
                        ABORT_PARSE;
                      }
                  }
#line 4215 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 797 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op ('=', (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4221 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 799 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (ADD_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4227 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 801 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (SUB_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4233 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 803 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (MUL_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4239 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 805 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (DIV_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4245 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 807 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (LEFTDIV_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4251 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 809 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (POW_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4257 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 811 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (LSHIFT_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4263 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 813 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (RSHIFT_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4269 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 815 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (EMUL_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4275 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 817 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (EDIV_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4281 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 819 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (ELEFTDIV_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4287 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 821 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (EPOW_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4293 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 823 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (AND_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4299 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 825 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = parser.make_assign_op (OR_EQ, (yyvsp[-2].tree_argument_list_type), (yyvsp[-1].tok_val), (yyvsp[0].tree_expression_type)); }
#line 4305 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 829 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if ((yyvsp[0].tree_expression_type) && ((yyvsp[0].tree_expression_type)->is_matrix () || (yyvsp[0].tree_expression_type)->is_cell ()))
                      {
                        if (parser.validate_array_list ((yyvsp[0].tree_expression_type)))
                          (yyval.tree_expression_type) = (yyvsp[0].tree_expression_type);
                        else
                          {
                            delete (yyvsp[0].tree_expression_type);
                            ABORT_PARSE;
                          }
                      }
                    else
                      (yyval.tree_expression_type) = (yyvsp[0].tree_expression_type);
                  }
#line 4324 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 844 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_expression_type); }
#line 4330 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 846 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_expression_type) = (yyvsp[0].tree_anon_fcn_handle_type); }
#line 4336 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 854 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_decl_command_type); }
#line 4342 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 856 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_command_type); }
#line 4348 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 858 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_command_type); }
#line 4354 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 860 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_command_type); }
#line 4360 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 862 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_command_type); }
#line 4366 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 864 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_command_type); }
#line 4372 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 866 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_command_type); }
#line 4378 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 868 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_command_type); }
#line 4384 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 876 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_decl_command_type) = parser.make_decl_command (GLOBAL, (yyvsp[-1].tok_val), (yyvsp[0].tree_decl_init_list_type));
                    lexer.looking_at_decl_list = false;
                  }
#line 4393 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 881 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_decl_command_type) = parser.make_decl_command (PERSISTENT, (yyvsp[-1].tok_val), (yyvsp[0].tree_decl_init_list_type));
                    lexer.looking_at_decl_list = false;
                  }
#line 4402 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 888 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_decl_init_list_type) = new tree_decl_init_list ((yyvsp[0].tree_decl_elt_type)); }
#line 4408 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 890 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-1].tree_decl_init_list_type)->append ((yyvsp[0].tree_decl_elt_type));
                    (yyval.tree_decl_init_list_type) = (yyvsp[-1].tree_decl_init_list_type);
                  }
#line 4417 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 897 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { lexer.looking_at_initializer_expression = true; }
#line 4423 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 900 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[0].tree_identifier_type)); }
#line 4429 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 902 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.looking_at_initializer_expression = false;
                    (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[-3].tree_identifier_type), (yyvsp[0].tree_expression_type));
                  }
#line 4438 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 913 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_if_command_type); }
#line 4444 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 915 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = (yyvsp[0].tree_switch_command_type); }
#line 4450 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 923 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_if_command_type) = parser.finish_if_command ((yyvsp[-3].tok_val), (yyvsp[-1].tree_if_command_list_type), (yyvsp[0].tok_val), (yyvsp[-2].comment_type))))
                      {
                        // finish_if_command deleted $3.
                        ABORT_PARSE;
                      }
                  }
#line 4462 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 933 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_if_command_list_type) = (yyvsp[0].tree_if_command_list_type); }
#line 4468 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 935 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-1].tree_if_command_list_type)->append ((yyvsp[0].tree_if_clause_type));
                    (yyval.tree_if_command_list_type) = (yyvsp[-1].tree_if_command_list_type);
                  }
#line 4477 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 942 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-3].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    (yyval.tree_if_command_list_type) = parser.start_if_command ((yyvsp[-3].tree_expression_type), (yyvsp[0].tree_statement_list_type));
                  }
#line 4487 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 948 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-1].tree_if_command_list_type)->append ((yyvsp[0].tree_if_clause_type));
                    (yyval.tree_if_command_list_type) = (yyvsp[-1].tree_if_command_list_type);
                  }
#line 4496 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 955 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-3].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    (yyval.tree_if_clause_type) = parser.make_elseif_clause ((yyvsp[-6].tok_val), (yyvsp[-3].tree_expression_type), (yyvsp[0].tree_statement_list_type), (yyvsp[-5].comment_type));
                  }
#line 4506 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 963 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_if_clause_type) = new tree_if_clause ((yyvsp[0].tree_statement_list_type), (yyvsp[-2].comment_type)); }
#line 4512 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 971 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_switch_command_type) = parser.finish_switch_command ((yyvsp[-5].tok_val), (yyvsp[-3].tree_expression_type), (yyvsp[-1].tree_switch_case_list_type), (yyvsp[0].tok_val), (yyvsp[-4].comment_type))))
                      {
                        // finish_switch_command deleted $3 adn $5.
                        ABORT_PARSE;
                      }
                  }
#line 4524 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 981 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list (); }
#line 4530 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 983 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list ((yyvsp[0].tree_switch_case_type)); }
#line 4536 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 985 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_switch_case_list_type) = (yyvsp[0].tree_switch_case_list_type); }
#line 4542 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 987 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-1].tree_switch_case_list_type)->append ((yyvsp[0].tree_switch_case_type));
                    (yyval.tree_switch_case_list_type) = (yyvsp[-1].tree_switch_case_list_type);
                  }
#line 4551 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 994 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list ((yyvsp[0].tree_switch_case_type)); }
#line 4557 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 996 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-1].tree_switch_case_list_type)->append ((yyvsp[0].tree_switch_case_type));
                    (yyval.tree_switch_case_list_type) = (yyvsp[-1].tree_switch_case_list_type);
                  }
#line 4566 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 1003 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_switch_case_type) = parser.make_switch_case ((yyvsp[-6].tok_val), (yyvsp[-3].tree_expression_type), (yyvsp[0].tree_statement_list_type), (yyvsp[-5].comment_type)); }
#line 4572 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 1007 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_switch_case_type) = new tree_switch_case ((yyvsp[0].tree_statement_list_type), (yyvsp[-2].comment_type));
                  }
#line 4580 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 1017 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-4].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    if (! ((yyval.tree_command_type) = parser.make_while_command ((yyvsp[-6].tok_val), (yyvsp[-4].tree_expression_type), (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tok_val), (yyvsp[-5].comment_type))))
                      {
                        // make_while_command deleted $3 and $6.
                        ABORT_PARSE;
                      }
                  }
#line 4594 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 1027 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_command_type) = parser.make_do_until_command ((yyvsp[-1].tok_val), (yyvsp[-2].tree_statement_list_type), (yyvsp[0].tree_expression_type), (yyvsp[-4].comment_type));
                  }
#line 4602 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 1031 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (FOR, (yyvsp[-8].tok_val), (yyvsp[-6].tree_argument_list_type), (yyvsp[-4].tree_expression_type), 0,
                                                         (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tok_val), (yyvsp[-7].comment_type))))
                      {
                        // make_for_command deleted $3, $5, and $8.
                        ABORT_PARSE;
                      }
                  }
#line 4615 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 1040 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (FOR, (yyvsp[-9].tok_val), (yyvsp[-6].tree_argument_list_type), (yyvsp[-4].tree_expression_type), 0,
                                                         (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tok_val), (yyvsp[-8].comment_type))))
                      {
                        // make_for_command deleted $4, $6, and $9.
                        ABORT_PARSE;
                      }
                  }
#line 4628 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 1049 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (PARFOR, (yyvsp[-8].tok_val), (yyvsp[-6].tree_argument_list_type), (yyvsp[-4].tree_expression_type),
                                                         0, (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tok_val), (yyvsp[-7].comment_type))))
                      {
                        // make_for_command deleted $3, $5, and $8.
                        ABORT_PARSE;
                      }
                  }
#line 4641 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 1058 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (PARFOR, (yyvsp[-11].tok_val), (yyvsp[-8].tree_argument_list_type), (yyvsp[-6].tree_expression_type),
                                                         (yyvsp[-4].tree_expression_type), (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tok_val), (yyvsp[-10].comment_type))))
                      {
                        // make_for_command deleted $4, $6, $8, and $11.
                        ABORT_PARSE;
                      }
                  }
#line 4654 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 1073 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = parser.make_break_command ((yyvsp[0].tok_val)); }
#line 4660 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 1075 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = parser.make_continue_command ((yyvsp[0].tok_val)); }
#line 4666 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 1077 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = parser.make_return_command ((yyvsp[0].tok_val)); }
#line 4672 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 1086 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_command_type) = parser.make_unwind_command ((yyvsp[-8].tok_val), (yyvsp[-5].tree_statement_list_type), (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tok_val), (yyvsp[-7].comment_type), (yyvsp[-3].comment_type))))
                      {
                        // make_unwind_command deleted $4 and $8.
                        ABORT_PARSE;
                      }
                  }
#line 4684 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 1095 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_command_type) = parser.make_try_command ((yyvsp[-8].tok_val), (yyvsp[-5].tree_statement_list_type), (yyvsp[-2].sep_type), (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tok_val), (yyvsp[-7].comment_type), (yyvsp[-3].comment_type))))
                      {
                        // make_try_command deleted $4 and $8.
                        ABORT_PARSE;
                      }
                  }
#line 4696 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 1103 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (! ((yyval.tree_command_type) = parser.make_try_command ((yyvsp[-4].tok_val), (yyvsp[-1].tree_statement_list_type), 0, 0, (yyvsp[0].tok_val), (yyvsp[-3].comment_type), 0)))
                      {
                        // make_try_command deleted $4.
                        ABORT_PARSE;
                      }
                  }
#line 4708 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 1117 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    parser.curr_fcn_depth++;

                    if (parser.max_fcn_depth < parser.curr_fcn_depth)
                      parser.max_fcn_depth = parser.curr_fcn_depth;

                    lexer.symtab_context.push (symbol_table::alloc_scope ());

                    parser.function_scopes.push_back
                     (lexer.symtab_context.curr_scope ());

                    if (! lexer.reading_script_file
                        && parser.curr_fcn_depth == 1
                        && ! parser.parsing_subfunctions)
                      parser.primary_fcn_scope
                        = lexer.symtab_context.curr_scope ();

                    if (lexer.reading_script_file
                        && parser.curr_fcn_depth > 1)
                      parser.bison_error ("nested functions not implemented in this context");
                  }
#line 4734 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 1145 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.looking_at_parameter_list = true;

                    if (lexer.looking_at_function_handle)
                      {
                        lexer.symtab_context.push (symbol_table::alloc_scope ());
                        lexer.looking_at_function_handle--;
                        lexer.looking_at_anon_fcn_args = true;
                      }
                  }
#line 4749 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 1158 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.looking_at_parameter_list = false;
                    lexer.looking_for_object_index = false;
                  }
#line 4758 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 184:
#line 1165 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if ((yyvsp[-1].tree_parameter_list_type))
                      lexer.mark_as_variables ((yyvsp[-1].tree_parameter_list_type)->variable_names ());

                    (yyval.tree_parameter_list_type) = (yyvsp[-1].tree_parameter_list_type);
                  }
#line 4769 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 185:
#line 1172 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    parser.bison_error ("invalid parameter list");
                    (yyval.tree_parameter_list_type) = 0;
                    ABORT_PARSE;
                  }
#line 4779 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 186:
#line 1180 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = 0; }
#line 4785 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 187:
#line 1182 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[0].tree_parameter_list_type)->mark_as_formal_parameters ();
                    if ((yyvsp[0].tree_parameter_list_type)->validate (tree_parameter_list::in))
                      {
                        lexer.mark_as_variables ((yyvsp[0].tree_parameter_list_type)->variable_names ());
                        (yyval.tree_parameter_list_type) = (yyvsp[0].tree_parameter_list_type);
                      }
                    else
                      {
                        delete (yyvsp[0].tree_parameter_list_type);
                        ABORT_PARSE;
                      }
                  }
#line 4803 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 188:
#line 1198 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = new tree_parameter_list ((yyvsp[0].tree_decl_elt_type)); }
#line 4809 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 189:
#line 1200 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-2].tree_parameter_list_type)->append ((yyvsp[0].tree_decl_elt_type));
                    (yyval.tree_parameter_list_type) = (yyvsp[-2].tree_parameter_list_type);
                  }
#line 4818 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 190:
#line 1207 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_decl_elt_type) = (yyvsp[0].tree_decl_elt_type); }
#line 4824 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 191:
#line 1209 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[0].tree_identifier_type)); }
#line 4830 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 192:
#line 1217 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.looking_at_return_list = false;

                    (yyval.tree_parameter_list_type) = new tree_parameter_list ();
                  }
#line 4840 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 193:
#line 1223 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.looking_at_return_list = false;

                    tree_parameter_list *tmp = new tree_parameter_list ((yyvsp[0].tree_identifier_type));

                    // Even though this parameter list can contain only
                    // a single identifier, we still need to validate it
                    // to check for varargin or varargout.

                    if (tmp->validate (tree_parameter_list::out))
                      (yyval.tree_parameter_list_type) = tmp;
                    else
                      {
                        delete tmp;
                        ABORT_PARSE;
                      }
                  }
#line 4862 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 194:
#line 1241 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.looking_at_return_list = false;

                    // Check for duplicate parameter names, varargin,
                    // or varargout.

                    if ((yyvsp[-1].tree_parameter_list_type)->validate (tree_parameter_list::out))
                      (yyval.tree_parameter_list_type) = (yyvsp[-1].tree_parameter_list_type);
                    else
                      {
                        delete (yyvsp[-1].tree_parameter_list_type);
                        ABORT_PARSE;
                      }
                  }
#line 4881 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 195:
#line 1258 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = new tree_parameter_list (new tree_decl_elt ((yyvsp[0].tree_identifier_type))); }
#line 4887 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 196:
#line 1260 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyvsp[-2].tree_parameter_list_type)->append (new tree_decl_elt ((yyvsp[0].tree_identifier_type)));
                    (yyval.tree_parameter_list_type) = (yyvsp[-2].tree_parameter_list_type);
                  }
#line 4896 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 197:
#line 1271 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    if (lexer.reading_fcn_file)
                      {
                        // Delete the dummy statement_list we created
                        // after parsing the function.  Any function
                        // definitions found in the file have already
                        // been stored in the symbol table or in
                        // octave_base_parser::primary_fcn_ptr.

                        delete (yyvsp[-1].tree_statement_list_type);
                      }
                    else
                      {
                        tree_statement *end_of_script
                          = parser.make_end ("endscript", true,
                                             lexer.input_line_number,
                                             lexer.current_input_column);

                        parser.make_script ((yyvsp[-1].tree_statement_list_type), end_of_script);
                      }

                    (yyval.tree_command_type) = 0;
                  }
#line 4924 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 198:
#line 1301 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tok_val) = (yyvsp[0].tok_val);
                    if (lexer.reading_classdef_file
                        || lexer.parsing_classdef)
                      lexer.maybe_classdef_get_set_method = true;
                  }
#line 4935 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 199:
#line 1310 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_command_type) = parser.finish_function (0, (yyvsp[0].octave_user_function_type), (yyvsp[-1].comment_type), (yyvsp[-2].tok_val)->line (),
                                                 (yyvsp[-2].tok_val)->column ());
                    parser.recover_from_parsing_function ();
                  }
#line 4945 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 200:
#line 1316 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.tree_command_type) = parser.finish_function ((yyvsp[-2].tree_parameter_list_type), (yyvsp[0].octave_user_function_type), (yyvsp[-3].comment_type), (yyvsp[-4].tok_val)->line (),
                                                 (yyvsp[-4].tok_val)->column ());
                    parser.recover_from_parsing_function ();
                  }
#line 4955 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 201:
#line 1324 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    std::string id_name = (yyvsp[0].tree_identifier_type)->name ();

                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;

                    (yyval.tree_identifier_type) = (yyvsp[0].tree_identifier_type);
                  }
#line 4968 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 202:
#line 1333 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;
                    (yyval.tree_identifier_type) = (yyvsp[0].tree_identifier_type);
                  }
#line 4978 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 203:
#line 1339 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;
                    (yyval.tree_identifier_type) = (yyvsp[0].tree_identifier_type);
                  }
#line 4988 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 204:
#line 1347 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    std::string fname = (yyvsp[-1].tree_identifier_type)->name ();

                    delete (yyvsp[-1].tree_identifier_type);

                    (yyval.octave_user_function_type) = parser.frob_function (fname, (yyvsp[0].octave_user_function_type));
                  }
#line 5000 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 205:
#line 1357 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.octave_user_function_type) = parser.start_function ((yyvsp[-3].tree_parameter_list_type), (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tree_statement_type)); }
#line 5006 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 206:
#line 1359 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.octave_user_function_type) = parser.start_function (0, (yyvsp[-1].tree_statement_list_type), (yyvsp[0].tree_statement_type)); }
#line 5012 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 207:
#line 1363 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    parser.endfunction_found = true;
                    if (parser.end_token_ok ((yyvsp[0].tok_val), token::function_end))
                      (yyval.tree_statement_type) = parser.make_end ("endfunction", false,
                                            (yyvsp[0].tok_val)->line (), (yyvsp[0].tok_val)->column ());
                    else
                      ABORT_PARSE;
                  }
#line 5025 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 208:
#line 1372 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
// A lot of tests are based on the assumption that this is OK
//                  if (lexer.reading_script_file)
//                    {
//                      parser.bison_error ("function body open at end of script");
//                      YYABORT;
//                    }

                    if (parser.endfunction_found)
                      {
                        parser.bison_error ("inconsistent function endings -- "
                                 "if one function is explicitly ended, "
                                 "so must all the others");
                        YYABORT;
                      }

                    if (! (lexer.reading_fcn_file || lexer.reading_script_file
                           || lexer.input_from_eval_string ()))
                      {
                        parser.bison_error ("function body open at end of input");
                        YYABORT;
                      }

                    if (lexer.reading_classdef_file)
                      {
                        parser.bison_error ("classdef body open at end of input");
                        YYABORT;
                      }

                    (yyval.tree_statement_type) = parser.make_end ("endfunction", true,
                                          lexer.input_line_number,
                                          lexer.current_input_column);
                  }
#line 5063 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 209:
#line 1412 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    (yyval.comment_type) = 0;
                    lexer.parsing_classdef = true;
                  }
#line 5072 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 210:
#line 1419 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    {
                    lexer.parsing_classdef = false;

                    if (parser.end_token_ok ((yyvsp[0].tok_val), token::classdef_end))
                      (yyval.tree_statement_type) = parser.make_end ("endclassdef", false,
                                            (yyvsp[0].tok_val)->line (), (yyvsp[0].tok_val)->column ());
                    else
                      ABORT_PARSE;
                  }
#line 5086 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 211:
#line 1431 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.octave_user_function_type) = 0; }
#line 5092 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 212:
#line 1435 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_command_type) = 0; }
#line 5098 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 213:
#line 1439 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5104 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 214:
#line 1441 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5110 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 215:
#line 1445 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5116 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 216:
#line 1447 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5122 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 217:
#line 1451 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5128 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 218:
#line 1453 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5134 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 219:
#line 1455 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5140 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 220:
#line 1460 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = 0; }
#line 5146 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 221:
#line 1462 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = 0; }
#line 5152 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 222:
#line 1466 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = 0; }
#line 5158 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 223:
#line 1468 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = 0; }
#line 5164 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 224:
#line 1470 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = 0; }
#line 5170 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 225:
#line 1472 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.tree_parameter_list_type) = 0; }
#line 5176 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 226:
#line 1476 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5182 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 227:
#line 1478 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5188 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 228:
#line 1480 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5194 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 229:
#line 1482 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5200 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 230:
#line 1484 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5206 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 231:
#line 1486 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5212 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 232:
#line 1488 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5218 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 233:
#line 1490 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5224 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 234:
#line 1494 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.comment_type) = 0; }
#line 5230 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 235:
#line 1499 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5236 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 236:
#line 1504 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5242 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 237:
#line 1506 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5248 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 238:
#line 1510 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5254 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 239:
#line 1512 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5260 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 240:
#line 1516 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.comment_type) = 0; }
#line 5266 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 241:
#line 1520 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5272 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 242:
#line 1524 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5278 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 243:
#line 1526 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5284 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 244:
#line 1530 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.comment_type) = 0; }
#line 5290 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 245:
#line 1534 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5296 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 246:
#line 1538 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5302 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 247:
#line 1540 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5308 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 248:
#line 1544 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5314 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 249:
#line 1548 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.comment_type) = 0; }
#line 5320 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 250:
#line 1552 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5326 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 251:
#line 1556 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5332 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 252:
#line 1558 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5338 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 253:
#line 1562 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.dummy_type) = 0; }
#line 5344 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 254:
#line 1570 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { lexer.at_beginning_of_statement = true; }
#line 5350 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 255:
#line 1574 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.comment_type) = lexer.get_comment (); }
#line 5356 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 256:
#line 1578 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { parser.bison_error ("parse error"); }
#line 5362 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 258:
#line 1583 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = ','; }
#line 5368 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 259:
#line 1585 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = ';'; }
#line 5374 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 260:
#line 1587 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[-1].sep_type); }
#line 5380 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 261:
#line 1589 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[-1].sep_type); }
#line 5386 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 262:
#line 1593 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = 0; }
#line 5392 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 263:
#line 1595 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[0].sep_type); }
#line 5398 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 264:
#line 1599 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = 0; }
#line 5404 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 265:
#line 1601 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[0].sep_type); }
#line 5410 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 266:
#line 1605 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = '\n'; }
#line 5416 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 267:
#line 1607 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[-1].sep_type); }
#line 5422 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 268:
#line 1611 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = ','; }
#line 5428 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 269:
#line 1613 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = ';'; }
#line 5434 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 270:
#line 1615 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = '\n'; }
#line 5440 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 271:
#line 1617 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[-1].sep_type); }
#line 5446 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 272:
#line 1619 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[-1].sep_type); }
#line 5452 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 273:
#line 1621 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[-1].sep_type); }
#line 5458 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 274:
#line 1625 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = 0; }
#line 5464 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;

  case 275:
#line 1627 "parse-tree/oct-parse.yy" /* yacc.c:1646  */
    { (yyval.sep_type) = (yyvsp[0].sep_type); }
#line 5470 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
    break;


#line 5474 "parse-tree/oct-parse.cc" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (parser, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (parser, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, parser);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, parser);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  yyps->yynew = 1;

yypushreturn:
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1630 "parse-tree/oct-parse.yy" /* yacc.c:1906  */


// Generic error messages.

#undef lexer

static void
yyerror (octave_base_parser& parser, const char *s)
{
  parser.bison_error (s);
}

octave_base_parser::~octave_base_parser (void)
{
  delete stmt_list;

  delete &lexer;
}

void
octave_base_parser::reset (void)
{
  endfunction_found = false;
  autoloading = false;
  fcn_file_from_relative_lookup = false;
  parsing_subfunctions = false;
  max_fcn_depth = 0;
  curr_fcn_depth = 0;
  primary_fcn_scope = -1;
  curr_class_name = "";
  function_scopes.clear ();
  primary_fcn_ptr  = 0;
  subfunction_names.clear ();

  delete stmt_list;
  stmt_list = 0;

  lexer.reset ();
}

// Error mesages for mismatched end tokens.

void
octave_base_parser::end_error (const char *type, token::end_tok_type ettype,
                               int l, int c)
{
  static const char *fmt
    = "'%s' command matched by '%s' near line %d column %d";

  switch (ettype)
    {
    case token::simple_end:
      error (fmt, type, "end", l, c);
      break;

    case token::for_end:
      error (fmt, type, "endfor", l, c);
      break;

    case token::function_end:
      error (fmt, type, "endfunction", l, c);
      break;

    case token::classdef_end:
      error (fmt, type, "endclassdef", l, c);
      break;

    case token::if_end:
      error (fmt, type, "endif", l, c);
      break;

    case token::switch_end:
      error (fmt, type, "endswitch", l, c);
      break;

    case token::while_end:
      error (fmt, type, "endwhile", l, c);
      break;

    case token::try_catch_end:
      error (fmt, type, "end_try_catch", l, c);
      break;

    case token::unwind_protect_end:
      error (fmt, type, "end_unwind_protect", l, c);
      break;

    default:
      panic_impossible ();
      break;
    }
}

// Check to see that end tokens are properly matched.

bool
octave_base_parser::end_token_ok (token *tok, token::end_tok_type expected)
{
  bool retval = true;

  token::end_tok_type ettype = tok->ettype ();

  if (ettype != expected && ettype != token::simple_end)
    {
      retval = false;

      bison_error ("parse error");

      int l = tok->line ();
      int c = tok->column ();

      switch (expected)
        {
        case token::classdef_end:
          end_error ("classdef", ettype, l, c);
          break;

        case token::for_end:
          end_error ("for", ettype, l, c);
          break;

        case token::enumeration_end:
          end_error ("enumeration", ettype, l, c);
          break;

        case token::function_end:
          end_error ("function", ettype, l, c);
          break;

        case token::if_end:
          end_error ("if", ettype, l, c);
          break;

        case token::parfor_end:
          end_error ("parfor", ettype, l, c);
          break;

        case token::try_catch_end:
          end_error ("try", ettype, l, c);
          break;

        case token::switch_end:
          end_error ("switch", ettype, l, c);
          break;

        case token::unwind_protect_end:
          end_error ("unwind_protect", ettype, l, c);
          break;

        case token::while_end:
          end_error ("while", ettype, l, c);
          break;

        default:
          panic_impossible ();
          break;
        }
    }

  return retval;
}

// Maybe print a warning if an assignment expression is used as the
// test in a logical expression.

void
octave_base_parser::maybe_warn_assign_as_truth_value (tree_expression *expr)
{
  if (expr->is_assignment_expression ()
      && expr->paren_count () < 2)
    {
      if (lexer.fcn_file_full_name.empty ())
        warning_with_id
          ("Octave:assign-as-truth-value",
           "suggest parenthesis around assignment used as truth value");
      else
        warning_with_id
          ("Octave:assign-as-truth-value",
           "suggest parenthesis around assignment used as truth value near line %d, column %d in file '%s'",
           expr->line (), expr->column (), lexer.fcn_file_full_name.c_str ());
    }
}

// Maybe print a warning about switch labels that aren't constants.

void
octave_base_parser::maybe_warn_variable_switch_label (tree_expression *expr)
{
  if (! expr->is_constant ())
    {
      if (lexer.fcn_file_full_name.empty ())
        warning_with_id ("Octave:variable-switch-label",
                         "variable switch label");
      else
        warning_with_id
          ("Octave:variable-switch-label",
           "variable switch label near line %d, column %d in file '%s'",
           expr->line (), expr->column (), lexer.fcn_file_full_name.c_str ());
    }
}

static tree_expression *
fold (tree_binary_expression *e)
{
  tree_expression *retval = e;

  unwind_protect frame;

  frame.protect_var (error_state);
  frame.protect_var (warning_state);

  frame.protect_var (discard_error_messages);
  frame.protect_var (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *op1 = e->lhs ();
  tree_expression *op2 = e->rhs ();

  if (op1->is_constant () && op2->is_constant ())
    {
      octave_value tmp = e->rvalue1 ();

      if (! (error_state || warning_state))
        {
          tree_constant *tc_retval
            = new tree_constant (tmp, op1->line (), op1->column ());

          std::ostringstream buf;

          tree_print_code tpc (buf);

          e->accept (tpc);

          tc_retval->stash_original_text (buf.str ());

          delete e;

          retval = tc_retval;
        }
    }

  return retval;
}

static tree_expression *
fold (tree_unary_expression *e)
{
  tree_expression *retval = e;

  unwind_protect frame;

  frame.protect_var (error_state);
  frame.protect_var (warning_state);

  frame.protect_var (discard_error_messages);
  frame.protect_var (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *op = e->operand ();

  if (op->is_constant ())
    {
      octave_value tmp = e->rvalue1 ();

      if (! (error_state || warning_state))
        {
          tree_constant *tc_retval
            = new tree_constant (tmp, op->line (), op->column ());

          std::ostringstream buf;

          tree_print_code tpc (buf);

          e->accept (tpc);

          tc_retval->stash_original_text (buf.str ());

          delete e;

          retval = tc_retval;
        }
    }

  return retval;
}

// Finish building a range.

tree_expression *
octave_base_parser::finish_colon_expression (tree_colon_expression *e)
{
  tree_expression *retval = e;

  unwind_protect frame;

  frame.protect_var (error_state);
  frame.protect_var (warning_state);

  frame.protect_var (discard_error_messages);
  frame.protect_var (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *base = e->base ();
  tree_expression *limit = e->limit ();
  tree_expression *incr = e->increment ();

  if (base)
    {
      if (limit)
        {
          if (base->is_constant () && limit->is_constant ()
              && (! incr || (incr && incr->is_constant ())))
            {
              octave_value tmp = e->rvalue1 ();

              if (! (error_state || warning_state))
                {
                  tree_constant *tc_retval
                    = new tree_constant (tmp, base->line (), base->column ());

                  std::ostringstream buf;

                  tree_print_code tpc (buf);

                  e->accept (tpc);

                  tc_retval->stash_original_text (buf.str ());

                  delete e;

                  retval = tc_retval;
                }
            }
        }
      else
        {
          e->preserve_base ();
          delete e;

          // FIXME -- need to attempt constant folding here
          // too (we need a generic way to do that).
          retval = base;
        }
    }

  return retval;
}

// Make a constant.

tree_constant *
octave_base_parser::make_constant (int op, token *tok_val)
{
  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_constant *retval = 0;

  switch (op)
    {
    case NUM:
      {
        octave_value tmp (tok_val->number ());
        retval = new tree_constant (tmp, l, c);
        retval->stash_original_text (tok_val->text_rep ());
      }
      break;

    case IMAG_NUM:
      {
        octave_value tmp (Complex (0.0, tok_val->number ()));
        retval = new tree_constant (tmp, l, c);
        retval->stash_original_text (tok_val->text_rep ());
      }
      break;

    case DQ_STRING:
    case SQ_STRING:
      {
        std::string txt = tok_val->text ();

        char delim = op == DQ_STRING ? '"' : '\'';
        octave_value tmp (txt, delim);

        if (txt.empty ())
          {
            if (op == DQ_STRING)
              tmp = octave_null_str::instance;
            else
              tmp = octave_null_sq_str::instance;
          }

        retval = new tree_constant (tmp, l, c);

        if (op == DQ_STRING)
          txt = undo_string_escapes (txt);

        // FIXME -- maybe this should also be handled by
        // tok_val->text_rep () for character strings?
        retval->stash_original_text (delim + txt + delim);
      }
      break;

    default:
      panic_impossible ();
      break;
    }

  return retval;
}

// Make a function handle.

tree_fcn_handle *
octave_base_parser::make_fcn_handle (token *tok_val)
{
  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_fcn_handle *retval = new tree_fcn_handle (tok_val->text (), l, c);

  return retval;
}

// Make an anonymous function handle.

tree_anon_fcn_handle *
octave_base_parser::make_anon_fcn_handle (tree_parameter_list *param_list,
                                          tree_statement *stmt)
{
  // FIXME -- need to get these from the location of the @ symbol.
  int l = lexer.input_line_number;
  int c = lexer.current_input_column;

  tree_parameter_list *ret_list = 0;

  symbol_table::scope_id fcn_scope = lexer.symtab_context.curr_scope ();

  lexer.symtab_context.pop ();

  stmt->set_print_flag (false);

  tree_statement_list *body = new tree_statement_list (stmt);

  body->mark_as_anon_function_body ();

  tree_anon_fcn_handle *retval
    = new tree_anon_fcn_handle (param_list, ret_list, body, fcn_scope, l, c);
  // FIXME: Stash the filename.  This does not work and produces
  // errors when executed.
  //retval->stash_file_name (lexer.fcn_file_name);

  return retval;
}

// Build a binary expression.

tree_expression *
octave_base_parser::make_binary_op (int op, tree_expression *op1,
                                    token *tok_val, tree_expression *op2)
{
  octave_value::binary_op t = octave_value::unknown_binary_op;

  switch (op)
    {
    case POW:
      t = octave_value::op_pow;
      break;

    case EPOW:
      t = octave_value::op_el_pow;
      break;

    case '+':
      t = octave_value::op_add;
      break;

    case '-':
      t = octave_value::op_sub;
      break;

    case '*':
      t = octave_value::op_mul;
      break;

    case '/':
      t = octave_value::op_div;
      break;

    case EMUL:
      t = octave_value::op_el_mul;
      break;

    case EDIV:
      t = octave_value::op_el_div;
      break;

    case LEFTDIV:
      t = octave_value::op_ldiv;
      break;

    case ELEFTDIV:
      t = octave_value::op_el_ldiv;
      break;

    case LSHIFT:
      t = octave_value::op_lshift;
      break;

    case RSHIFT:
      t = octave_value::op_rshift;
      break;

    case EXPR_LT:
      t = octave_value::op_lt;
      break;

    case EXPR_LE:
      t = octave_value::op_le;
      break;

    case EXPR_EQ:
      t = octave_value::op_eq;
      break;

    case EXPR_GE:
      t = octave_value::op_ge;
      break;

    case EXPR_GT:
      t = octave_value::op_gt;
      break;

    case EXPR_NE:
      t = octave_value::op_ne;
      break;

    case EXPR_AND:
      t = octave_value::op_el_and;
      break;

    case EXPR_OR:
      t = octave_value::op_el_or;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_binary_expression *e
    = maybe_compound_binary_expression (op1, op2, l, c, t);

  return fold (e);
}

// Build a boolean expression.

tree_expression *
octave_base_parser::make_boolean_op (int op, tree_expression *op1,
                                     token *tok_val, tree_expression *op2)
{
  tree_boolean_expression::type t;

  switch (op)
    {
    case EXPR_AND_AND:
      t = tree_boolean_expression::bool_and;
      break;

    case EXPR_OR_OR:
      t = tree_boolean_expression::bool_or;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_boolean_expression *e
    = new tree_boolean_expression (op1, op2, l, c, t);

  return fold (e);
}

// Build a prefix expression.

tree_expression *
octave_base_parser::make_prefix_op (int op, tree_expression *op1,
                                    token *tok_val)
{
  octave_value::unary_op t = octave_value::unknown_unary_op;

  switch (op)
    {
    case EXPR_NOT:
      t = octave_value::op_not;
      break;

    case '+':
      t = octave_value::op_uplus;
      break;

    case '-':
      t = octave_value::op_uminus;
      break;

    case PLUS_PLUS:
      t = octave_value::op_incr;
      break;

    case MINUS_MINUS:
      t = octave_value::op_decr;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_prefix_expression *e
    = new tree_prefix_expression (op1, l, c, t);

  return fold (e);
}

// Build a postfix expression.

tree_expression *
octave_base_parser::make_postfix_op (int op, tree_expression *op1,
                                     token *tok_val)
{
  octave_value::unary_op t = octave_value::unknown_unary_op;

  switch (op)
    {
    case HERMITIAN:
      t = octave_value::op_hermitian;
      break;

    case TRANSPOSE:
      t = octave_value::op_transpose;
      break;

    case PLUS_PLUS:
      t = octave_value::op_incr;
      break;

    case MINUS_MINUS:
      t = octave_value::op_decr;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_postfix_expression *e
    = new tree_postfix_expression (op1, l, c, t);

  return fold (e);
}

// Build an unwind-protect command.

tree_command *
octave_base_parser::make_unwind_command (token *unwind_tok,
                                         tree_statement_list *body,
                                         tree_statement_list *cleanup_stmts,
                                         token *end_tok,
                                         octave_comment_list *lc,
                                         octave_comment_list *mc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::unwind_protect_end))
    {
      octave_comment_list *tc = lexer.comment_buf.get_comment ();

      int l = unwind_tok->line ();
      int c = unwind_tok->column ();

      retval = new tree_unwind_protect_command (body, cleanup_stmts,
                                                lc, mc, tc, l, c);
    }
  else
    {
      delete body;
      delete cleanup_stmts;
    }

  return retval;
}

// Build a try-catch command.

tree_command *
octave_base_parser::make_try_command (token *try_tok,
                                      tree_statement_list *body,
                                      char catch_sep,
                                      tree_statement_list *cleanup_stmts,
                                      token *end_tok,
                                      octave_comment_list *lc,
                                      octave_comment_list *mc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::try_catch_end))
    {
      octave_comment_list *tc = lexer.comment_buf.get_comment ();

      int l = try_tok->line ();
      int c = try_tok->column ();

      tree_identifier *id = 0;

      if (! catch_sep && cleanup_stmts && ! cleanup_stmts->empty ())
        {
          tree_statement *stmt = cleanup_stmts->front ();

          if (stmt)
            {
              tree_expression *expr = stmt->expression ();

              if (expr && expr->is_identifier ())
                {
                  id = dynamic_cast<tree_identifier *> (expr);

                  cleanup_stmts->pop_front ();

                  stmt->set_expression (0);
                  delete stmt;
                }
            }
        }

      retval = new tree_try_catch_command (body, cleanup_stmts, id,
                                           lc, mc, tc, l, c);
    }
  else
    {
      delete body;
      delete cleanup_stmts;
    }

  return retval;
}

// Build a while command.

tree_command *
octave_base_parser::make_while_command (token *while_tok,
                                        tree_expression *expr,
                                        tree_statement_list *body,
                                        token *end_tok,
                                        octave_comment_list *lc)
{
  tree_command *retval = 0;

  maybe_warn_assign_as_truth_value (expr);

  if (end_token_ok (end_tok, token::while_end))
    {
      octave_comment_list *tc = lexer.comment_buf.get_comment ();

      lexer.looping--;

      int l = while_tok->line ();
      int c = while_tok->column ();

      retval = new tree_while_command (expr, body, lc, tc, l, c);
    }
  else
    {
      delete expr;
      delete body;
    }

  return retval;
}

// Build a do-until command.

tree_command *
octave_base_parser::make_do_until_command (token *until_tok,
                                           tree_statement_list *body,
                                           tree_expression *expr,
                                           octave_comment_list *lc)
{
  maybe_warn_assign_as_truth_value (expr);

  octave_comment_list *tc = lexer.comment_buf.get_comment ();

  lexer.looping--;

  int l = until_tok->line ();
  int c = until_tok->column ();

  return new tree_do_until_command (expr, body, lc, tc, l, c);
}

// Build a for command.

tree_command *
octave_base_parser::make_for_command (int tok_id, token *for_tok,
                                      tree_argument_list *lhs,
                                      tree_expression *expr,
                                      tree_expression *maxproc,
                                      tree_statement_list *body,
                                      token *end_tok,
                                      octave_comment_list *lc)
{
  tree_command *retval = 0;

  bool parfor = tok_id == PARFOR;

  if (end_token_ok (end_tok, parfor ? token::parfor_end : token::for_end))
    {
      octave_comment_list *tc = lexer.comment_buf.get_comment ();

      lexer.looping--;

      int l = for_tok->line ();
      int c = for_tok->column ();

      if (lhs->length () == 1)
        {
          tree_expression *tmp = lhs->remove_front ();

          retval = new tree_simple_for_command (parfor, tmp, expr, maxproc,
                                                body, lc, tc, l, c);

          delete lhs;
        }
      else
        {
          if (parfor)
            bison_error ("invalid syntax for parfor statement");
          else
            retval = new tree_complex_for_command (lhs, expr, body,
                                                   lc, tc, l, c);
        }
    }
  else
    {
      delete lhs;
      delete expr;
      delete maxproc;
      delete body;
    }

  return retval;
}

// Build a break command.

tree_command *
octave_base_parser::make_break_command (token *break_tok)
{
  int l = break_tok->line ();
  int c = break_tok->column ();

  return new tree_break_command (l, c);
}

// Build a continue command.

tree_command *
octave_base_parser::make_continue_command (token *continue_tok)
{
  int l = continue_tok->line ();
  int c = continue_tok->column ();

  return new tree_continue_command (l, c);
}

// Build a return command.

tree_command *
octave_base_parser::make_return_command (token *return_tok)
{
  int l = return_tok->line ();
  int c = return_tok->column ();

  return new tree_return_command (l, c);
}

// Start an if command.

tree_if_command_list *
octave_base_parser::start_if_command (tree_expression *expr,
                                      tree_statement_list *list)
{
  maybe_warn_assign_as_truth_value (expr);

  tree_if_clause *t = new tree_if_clause (expr, list);

  return new tree_if_command_list (t);
}

// Finish an if command.

tree_if_command *
octave_base_parser::finish_if_command (token *if_tok,
                                       tree_if_command_list *list,
                                       token *end_tok,
                                       octave_comment_list *lc)
{
  tree_if_command *retval = 0;

  if (end_token_ok (end_tok, token::if_end))
    {
      octave_comment_list *tc = lexer.comment_buf.get_comment ();

      int l = if_tok->line ();
      int c = if_tok->column ();

      if (list && ! list->empty ())
        {
          tree_if_clause *elt = list->front ();

          if (elt)
            {
              elt->line (l);
              elt->column (c);
            }
        }

      retval = new tree_if_command (list, lc, tc, l, c);
    }
  else
    delete list;

  return retval;
}

// Build an elseif clause.

tree_if_clause *
octave_base_parser::make_elseif_clause (token *elseif_tok,
                                        tree_expression *expr,
                                        tree_statement_list *list,
                                        octave_comment_list *lc)
{
  maybe_warn_assign_as_truth_value (expr);

  int l = elseif_tok->line ();
  int c = elseif_tok->column ();

  return new tree_if_clause (expr, list, lc, l, c);
}

// Finish a switch command.

tree_switch_command *
octave_base_parser::finish_switch_command (token *switch_tok,
                                           tree_expression *expr,
                                           tree_switch_case_list *list,
                                           token *end_tok,
                                           octave_comment_list *lc)
{
  tree_switch_command *retval = 0;

  if (end_token_ok (end_tok, token::switch_end))
    {
      octave_comment_list *tc = lexer.comment_buf.get_comment ();

      int l = switch_tok->line ();
      int c = switch_tok->column ();

      if (list && ! list->empty ())
        {
          tree_switch_case *elt = list->front ();

          if (elt)
            {
              elt->line (l);
              elt->column (c);
            }
        }

      retval = new tree_switch_command (expr, list, lc, tc, l, c);
    }
  else
    {
      delete expr;
      delete list;
    }

  return retval;
}

// Build a switch case.

tree_switch_case *
octave_base_parser::make_switch_case (token *case_tok,
                                      tree_expression *expr,
                                      tree_statement_list *list,
                                      octave_comment_list *lc)
{
  maybe_warn_variable_switch_label (expr);

  int l = case_tok->line ();
  int c = case_tok->column ();

  return new tree_switch_case (expr, list, lc, l, c);
}

// Build an assignment to a variable.

tree_expression *
octave_base_parser::make_assign_op (int op, tree_argument_list *lhs,
                                    token *eq_tok, tree_expression *rhs)
{
  tree_expression *retval = 0;

  octave_value::assign_op t = octave_value::unknown_assign_op;

  switch (op)
    {
    case '=':
      t = octave_value::op_asn_eq;
      break;

    case ADD_EQ:
      t = octave_value::op_add_eq;
      break;

    case SUB_EQ:
      t = octave_value::op_sub_eq;
      break;

    case MUL_EQ:
      t = octave_value::op_mul_eq;
      break;

    case DIV_EQ:
      t = octave_value::op_div_eq;
      break;

    case LEFTDIV_EQ:
      t = octave_value::op_ldiv_eq;
      break;

    case POW_EQ:
      t = octave_value::op_pow_eq;
      break;

    case LSHIFT_EQ:
      t = octave_value::op_lshift_eq;
      break;

    case RSHIFT_EQ:
      t = octave_value::op_rshift_eq;
      break;

    case EMUL_EQ:
      t = octave_value::op_el_mul_eq;
      break;

    case EDIV_EQ:
      t = octave_value::op_el_div_eq;
      break;

    case ELEFTDIV_EQ:
      t = octave_value::op_el_ldiv_eq;
      break;

    case EPOW_EQ:
      t = octave_value::op_el_pow_eq;
      break;

    case AND_EQ:
      t = octave_value::op_el_and_eq;
      break;

    case OR_EQ:
      t = octave_value::op_el_or_eq;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = eq_tok->line ();
  int c = eq_tok->column ();

  if (lhs->is_simple_assign_lhs ())
    {
      tree_expression *tmp = lhs->remove_front ();

      retval = new tree_simple_assignment (tmp, rhs, false, l, c, t);

      delete lhs;
    }
  else if (t == octave_value::op_asn_eq)
    return new tree_multi_assignment (lhs, rhs, false, l, c);
  else
    bison_error ("computed multiple assignment not allowed");

  return retval;
}

// Define a script.

void
octave_base_parser::make_script (tree_statement_list *cmds,
                                 tree_statement *end_script)
{
  if (! cmds)
    cmds = new tree_statement_list ();

  cmds->append (end_script);

  octave_user_script *script
    = new octave_user_script (lexer.fcn_file_full_name,
                              lexer.fcn_file_name,
                              cmds, lexer.help_text);

  lexer.help_text = "";

  octave_time now;

  script->stash_fcn_file_time (now);

  primary_fcn_ptr = script;
}

// Begin defining a function.

octave_user_function *
octave_base_parser::start_function (tree_parameter_list *param_list,
                                    tree_statement_list *body,
                                    tree_statement *end_fcn_stmt)
{
  // We'll fill in the return list later.

  if (! body)
    body = new tree_statement_list ();

  body->append (end_fcn_stmt);

  octave_user_function *fcn
    = new octave_user_function (lexer.symtab_context.curr_scope (),
                                param_list, 0, body);

  if (fcn)
    {
      octave_comment_list *tc = lexer.comment_buf.get_comment ();

      fcn->stash_trailing_comment (tc);
      fcn->stash_fcn_end_location (end_fcn_stmt->line (),
                                   end_fcn_stmt->column ());
    }

  return fcn;
}

tree_statement *
octave_base_parser::make_end (const std::string& type, bool eof, int l, int c)
{
  return make_statement (new tree_no_op_command (type, eof, l, c));
}

// Do most of the work for defining a function.

octave_user_function *
octave_base_parser::frob_function (const std::string& fname,
                                   octave_user_function *fcn)
{
  std::string id_name = fname;

  // If input is coming from a file, issue a warning if the name of
  // the file does not match the name of the function stated in the
  // file.  Matlab doesn't provide a diagnostic (it ignores the stated
  // name).
  if (! autoloading && lexer.reading_fcn_file
      && curr_fcn_depth == 1 && ! parsing_subfunctions)
  {
    // FIXME -- should lexer.fcn_file_name already be
    // preprocessed when we get here?  It seems to only be a
    // problem with relative file names.

    std::string nm = lexer.fcn_file_name;

    size_t pos = nm.find_last_of (file_ops::dir_sep_chars ());

    if (pos != std::string::npos)
      nm = lexer.fcn_file_name.substr (pos+1);

    if (nm != id_name)
      {
        warning_with_id
          ("Octave:function-name-clash",
           "function name '%s' does not agree with function file name '%s'",
           id_name.c_str (), lexer.fcn_file_full_name.c_str ());

        id_name = nm;
      }
  }

  if (lexer.reading_fcn_file || lexer.reading_classdef_file || autoloading)
    {
      octave_time now;

      fcn->stash_fcn_file_name (lexer.fcn_file_full_name);
      fcn->stash_fcn_file_time (now);
      fcn->mark_as_system_fcn_file ();

      if (fcn_file_from_relative_lookup)
        fcn->mark_relative ();

      if (curr_fcn_depth > 1 || parsing_subfunctions)
        {
          fcn->stash_parent_fcn_name (lexer.fcn_file_name);

          if (curr_fcn_depth > 1)
            fcn->stash_parent_fcn_scope (function_scopes[function_scopes.size ()-2]);
          else
            fcn->stash_parent_fcn_scope (primary_fcn_scope);
        }

      if (lexer.parsing_class_method)
        {
          if (curr_class_name == id_name)
            fcn->mark_as_class_constructor ();
          else
            fcn->mark_as_class_method ();

          fcn->stash_dispatch_class (curr_class_name);
        }

      std::string nm = fcn->fcn_file_name ();

      file_stat fs (nm);

      if (fs && fs.is_newer (now))
        warning_with_id ("Octave:future-time-stamp",
                         "time stamp for '%s' is in the future", nm.c_str ());
    }
  else if (! input_from_tmp_history_file
           && ! lexer.force_script
           && lexer.reading_script_file
           && lexer.fcn_file_name == id_name)
    {
      warning ("function '%s' defined within script file '%s'",
               id_name.c_str (), lexer.fcn_file_full_name.c_str ());
    }

  fcn->stash_function_name (id_name);

  if (! lexer.help_text.empty () && curr_fcn_depth == 1
      && ! parsing_subfunctions)
    {
      fcn->document (lexer.help_text);

      lexer.help_text = "";
    }

  if (lexer.reading_fcn_file && curr_fcn_depth == 1
      && ! parsing_subfunctions)
    primary_fcn_ptr = fcn;

  return fcn;
}

tree_function_def *
octave_base_parser::finish_function (tree_parameter_list *ret_list,
                                     octave_user_function *fcn,
                                     octave_comment_list *lc,
                                     int l, int c)
{
  tree_function_def *retval = 0;

  if (ret_list)
    ret_list->mark_as_formal_parameters ();

  if (fcn)
    {
      std::string nm = fcn->name ();
      std::string file = fcn->fcn_file_name ();

      std::string tmp = nm;
      if (! file.empty ())
        tmp += ": " + file;

      symbol_table::cache_name (fcn->scope (), tmp);

      if (lc)
        fcn->stash_leading_comment (lc);

      fcn->define_ret_list (ret_list);

      if (curr_fcn_depth > 1 || parsing_subfunctions)
        {
          fcn->mark_as_subfunction ();
          fcn->stash_fcn_location (l, c);

          subfunction_names.push_back (nm);

          if (endfunction_found && function_scopes.size () > 1)
            {
              symbol_table::scope_id pscope
                = function_scopes[function_scopes.size ()-2];

              symbol_table::install_nestfunction (nm, octave_value (fcn),
                                                  pscope);
            }
          else
            symbol_table::install_subfunction (nm, octave_value (fcn),
                                               primary_fcn_scope);
        }

      if (curr_fcn_depth == 1 && fcn)
        symbol_table::update_nest (fcn->scope ());

      if (! lexer.reading_fcn_file && curr_fcn_depth == 1)
        {
          // We are either reading a script file or defining a function
          // at the command line, so this definition creates a
          // tree_function object that is placed in the parse tree.
          // Otherwise, it is just inserted in the symbol table,
          // either as a subfunction or nested function (see above),
          // or as the primary function for the file, via
          // primary_fcn_ptr (see also load_fcn_from_file,,
          // parse_fcn_file, and
          // symbol_table::fcn_info::fcn_info_rep::find_user_function).

          retval = new tree_function_def (fcn);
        }
    }

  return retval;
}

void
octave_base_parser::recover_from_parsing_function (void)
{
  lexer.symtab_context.pop ();

  if (lexer.reading_fcn_file && curr_fcn_depth == 1
      && ! parsing_subfunctions)
    parsing_subfunctions = true;

  curr_fcn_depth--;
  function_scopes.pop_back ();

  lexer.defining_func--;
  lexer.parsed_function_name.pop ();
  lexer.looking_at_return_list = false;
  lexer.looking_at_parameter_list = false;
}

// Make an index expression.

tree_index_expression *
octave_base_parser::make_index_expression (tree_expression *expr,
                                           tree_argument_list *args,
                                           char type)
{
  tree_index_expression *retval = 0;

  if (args && args->has_magic_tilde ())
    {
      bison_error ("invalid use of empty argument (~) in index expression");

      delete expr;
      delete args;

      return retval;
    }

  int l = expr->line ();
  int c = expr->column ();

  expr->mark_postfix_indexed ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (args, type);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, args, l, c, type);

  return retval;
}

// Make an indirect reference expression.

tree_index_expression *
octave_base_parser::make_indirect_ref (tree_expression *expr,
                                       const std::string& elt)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (elt);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, elt, l, c);

  lexer.looking_at_indirect_ref = false;

  return retval;
}

// Make an indirect reference expression with dynamic field name.

tree_index_expression *
octave_base_parser::make_indirect_ref (tree_expression *expr, tree_expression *elt)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (elt);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, elt, l, c);

  lexer.looking_at_indirect_ref = false;

  return retval;
}

// Make a declaration command.

tree_decl_command *
octave_base_parser::make_decl_command (int tok, token *tok_val,
                                       tree_decl_init_list *lst)
{
  tree_decl_command *retval = 0;

  int l = tok_val->line ();
  int c = tok_val->column ();

  switch (tok)
    {
    case GLOBAL:
      retval = new tree_global_command (lst, l, c);
      break;

    case PERSISTENT:
      if (curr_fcn_depth > 0)
        retval = new tree_persistent_command (lst, l, c);
      else
        {
          if (lexer.reading_script_file)
            warning ("ignoring persistent declaration near line %d of file '%s'",
                     l, lexer.fcn_file_full_name.c_str ());
          else
            warning ("ignoring persistent declaration near line %d", l);
        }
      break;

    default:
      panic_impossible ();
      break;
    }

  return retval;
}

bool
octave_base_parser::validate_array_list (tree_expression *e)
{
  bool retval = true;

  tree_array_list *al = dynamic_cast<tree_array_list *> (e);

  for (tree_array_list::iterator i = al->begin (); i != al->end (); i++)
    {
      tree_argument_list *row = *i;

      if (row && row->has_magic_tilde ())
        {
          retval = false;
          if (e->is_matrix ())
             bison_error ("invalid use of tilde (~) in matrix expression");
           else
             bison_error ("invalid use of tilde (~) in cell expression");
          break;
        }
    }

  return retval;
}

tree_argument_list *
octave_base_parser::validate_matrix_for_assignment (tree_expression *e)
{
  tree_argument_list *retval = 0;

  if (e->is_constant ())
    {
      octave_value ov = e->rvalue1 ();

      if (ov.is_empty ())
        bison_error ("invalid empty left hand side of assignment");
      else
        bison_error ("invalid constant left hand side of assignment");

      delete e;
    }
  else
    {
      bool is_simple_assign = true;

      tree_argument_list *tmp = 0;

      if (e->is_matrix ())
        {
          tree_matrix *mat = dynamic_cast<tree_matrix *> (e);

          if (mat && mat->size () == 1)
            {
              tmp = mat->front ();
              mat->pop_front ();
              delete e;
              is_simple_assign = false;
            }
        }
      else
        tmp = new tree_argument_list (e);

      if (tmp && tmp->is_valid_lvalue_list ())
        {
          lexer.mark_as_variables (tmp->variable_names ());
          retval = tmp;
        }
      else
        {
          bison_error ("invalid left hand side of assignment");
          delete tmp;
        }

      if (retval && is_simple_assign)
        retval->mark_as_simple_assign_lhs ();
    }

  return retval;
}

// Finish building an array_list.

tree_expression *
octave_base_parser::finish_array_list (tree_array_list *array_list)
{
  tree_expression *retval = array_list;

  unwind_protect frame;

  frame.protect_var (error_state);
  frame.protect_var (warning_state);

  frame.protect_var (discard_error_messages);
  frame.protect_var (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  if (array_list->all_elements_are_constant ())
    {
      octave_value tmp = array_list->rvalue1 ();

      if (! (error_state || warning_state))
        {
          tree_constant *tc_retval
            = new tree_constant (tmp, array_list->line (),
                                 array_list->column ());

          std::ostringstream buf;

          tree_print_code tpc (buf);

          array_list->accept (tpc);

          tc_retval->stash_original_text (buf.str ());

          delete array_list;

          retval = tc_retval;
        }
    }

  return retval;
}

// Finish building a matrix list.

tree_expression *
octave_base_parser::finish_matrix (tree_matrix *m)
{
  return (m
          ? finish_array_list (m)
          : new tree_constant (octave_null_matrix::instance));
}

// Finish building a cell list.

tree_expression *
octave_base_parser::finish_cell (tree_cell *c)
{
  return (c
          ? finish_array_list (c)
          : new tree_constant (octave_value (Cell ())));
}

void
octave_base_parser::maybe_warn_missing_semi (tree_statement_list *t)
{
  if (curr_fcn_depth > 0)
    {
      tree_statement *tmp = t->back ();

      if (tmp->is_expression ())
        warning_with_id
          ("Octave:missing-semicolon",
           "missing semicolon near line %d, column %d in file '%s'",
            tmp->line (), tmp->column (), lexer.fcn_file_full_name.c_str ());
    }
}

tree_statement_list *
octave_base_parser::set_stmt_print_flag (tree_statement_list *list,
                                         char sep, bool warn_missing_semi)
{
  tree_statement *tmp = list->back ();

  switch (sep)
    {
    case ';':
      tmp->set_print_flag (false);
      break;

    case 0:
    case ',':
    case '\n':
      tmp->set_print_flag (true);
      if (warn_missing_semi)
        maybe_warn_missing_semi (list);
      break;

    default:
      warning ("unrecognized separator type!");
      break;
    }

  // Even if a statement is null, we add it to the list then remove it
  // here so that the print flag is applied to the correct statement.

  if (tmp->is_null_statement ())
    {
      list->pop_back ();
      delete tmp;
    }

  return list;
}

// Finish building a statement.
template <class T>
tree_statement *
octave_base_parser::make_statement (T *arg)
{
  octave_comment_list *comment = lexer.get_comment ();

  return new tree_statement (arg, comment);
}

tree_statement_list *
octave_base_parser::make_statement_list (tree_statement *stmt)
{
  return new tree_statement_list (stmt);
}

tree_statement_list *
octave_base_parser::append_statement_list (tree_statement_list *list,
                                           char sep, tree_statement *stmt,
                                           bool warn_missing_semi)
{
  set_stmt_print_flag (list, sep, warn_missing_semi);

  list->append (stmt);

  return list;
}

void
octave_base_parser::bison_error (const char *s)
{
  int err_col = lexer.current_input_column - 1;

  std::ostringstream output_buf;

  if (lexer.reading_fcn_file || lexer.reading_script_file || lexer.reading_classdef_file)
    output_buf << "parse error near line " << lexer.input_line_number
               << " of file " << lexer.fcn_file_full_name;
  else
    output_buf << "parse error:";

  if (s && strcmp (s, "parse error") != 0)
    output_buf << "\n\n  " << s;

  output_buf << "\n\n";

  std::string curr_line = lexer.current_input_line;

  if (! curr_line.empty ())
    {
      size_t len = curr_line.length ();

      if (curr_line[len-1] == '\n')
        curr_line.resize (len-1);

      // Print the line, maybe with a pointer near the error token.

      output_buf << ">>> " << curr_line << "\n";

      if (err_col == 0)
        err_col = len;

      for (int i = 0; i < err_col + 3; i++)
        output_buf << " ";

      output_buf << "^";
    }

  output_buf << "\n";

  std::string msg = output_buf.str ();

  parse_error ("%s", msg.c_str ());
}

int
octave_parser::run (void)
{
  return octave_parse (*this);
}

octave_push_parser::~octave_push_parser (void)
{
  yypstate_delete (static_cast<yypstate *> (parser_state));
}

void
octave_push_parser::init (void)
{
  parser_state = yypstate_new ();
}

// Parse input from INPUT.  Pass TRUE for EOF if the end of INPUT should
// finish the parse.

int
octave_push_parser::run (const std::string& input, bool eof)
{
  int status = -1;

  dynamic_cast<octave_push_lexer&> (lexer).append_input (input, eof);

  do
    {   
      YYSTYPE lval;

      int token = octave_lex (&lval, scanner);

      if (token < 0)
        {
          if (! eof && lexer.at_end_of_buffer ())
            {
              status = -1;
              break;
            }
        }

      yypstate *pstate = static_cast<yypstate *> (parser_state);

      status = octave_push_parse (pstate, token, &lval, *this);
    }
  while (status == YYPUSH_MORE);

  return status;
}

static void
safe_fclose (FILE *f)
{
  if (f)
    fclose (static_cast<FILE *> (f));
}

static octave_function *
parse_fcn_file (const std::string& full_file, const std::string& file,
                const std::string& dispatch_type,
                bool require_file, bool force_script, bool autoload,    
                bool relative_lookup, const std::string& warn_for)
{
  unwind_protect frame;

  octave_function *fcn_ptr = 0;

  // Open function file and parse.

  FILE *in_stream = command_editor::get_input_stream ();

  frame.add_fcn (command_editor::set_input_stream, in_stream);

  frame.add_fcn (command_history::ignore_entries,
                 command_history::ignoring_entries ());

  command_history::ignore_entries ();

  FILE *ffile = 0;

  if (! full_file.empty ())
    ffile = gnulib::fopen (full_file.c_str (), "rb");

  frame.add_fcn (safe_fclose, ffile);

  if (ffile)
    {
      // octave_base_parser constructor sets this for us.
      frame.protect_var (LEXER);

      octave_parser parser (ffile);

      parser.curr_class_name = dispatch_type;
      parser.autoloading = autoload;
      parser.fcn_file_from_relative_lookup = relative_lookup;

      parser.lexer.force_script = force_script;
      parser.lexer.prep_for_file ();
      parser.lexer.parsing_class_method = ! dispatch_type.empty ();

      parser.lexer.fcn_file_name = file;
      parser.lexer.fcn_file_full_name = full_file;

      int status = parser.run ();

      fcn_ptr = parser.primary_fcn_ptr;

      if (fcn_ptr)
        {
          fcn_ptr->maybe_relocate_end ();

          if (parser.parsing_subfunctions)
            {
              if (! parser.endfunction_found)
                parser.subfunction_names.reverse ();

              fcn_ptr->stash_subfunction_names (parser.subfunction_names);
            }
        }

      if (status != 0)
        error ("parse error while reading file %s", full_file.c_str ());
    }
  else if (require_file)
    error ("no such file, '%s'", full_file.c_str ());
  else if (! warn_for.empty ())
    error ("%s: unable to open file '%s'", warn_for.c_str (),
           full_file.c_str ());

  return fcn_ptr;
}

std::string
get_help_from_file (const std::string& nm, bool& symbol_found,
                    std::string& full_file)
{
  std::string retval;

  full_file = fcn_file_in_path (nm);

  std::string file = full_file;

  size_t file_len = file.length ();

  if ((file_len > 4 && file.substr (file_len-4) == ".oct")
      || (file_len > 4 && file.substr (file_len-4) == ".mex")
      || (file_len > 2 && file.substr (file_len-2) == ".m"))
    {
      file = octave_env::base_pathname (file);
      file = file.substr (0, file.find_last_of ('.'));

      size_t pos = file.find_last_of (file_ops::dir_sep_str ());
      if (pos != std::string::npos)
        file = file.substr (pos+1);
    }

  if (! file.empty ())
    {
      symbol_found = true;

      octave_function *fcn
        = parse_fcn_file (full_file, file, "", true, false, false, false, "");

      if (fcn)
        {
          retval = fcn->doc_string ();

          delete fcn;
        }
    }

  return retval;
}

std::string
get_help_from_file (const std::string& nm, bool& symbol_found)
{
  std::string file;
  return get_help_from_file (nm, symbol_found, file);
}

std::string
lookup_autoload (const std::string& nm)
{
  std::string retval;

  typedef std::map<std::string, std::string>::const_iterator am_iter;

  am_iter p = autoload_map.find (nm);

  if (p != autoload_map.end ())
    retval = load_path::find_file (p->second);

  return retval;
}

string_vector
autoloaded_functions (void)
{
  string_vector names (autoload_map.size ());

  octave_idx_type i = 0;
  typedef std::map<std::string, std::string>::const_iterator am_iter;
  for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
    names[i++] = p->first;

  return names;
}

string_vector
reverse_lookup_autoload (const std::string& nm)
{
  string_vector names;

  typedef std::map<std::string, std::string>::const_iterator am_iter;
  for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
    if (nm == p->second)
      names.append (p->first);

  return names;
}

octave_function *
load_fcn_from_file (const std::string& file_name, const std::string& dir_name,
                    const std::string& dispatch_type,
                    const std::string& fcn_name, bool autoload)
{
  octave_function *retval = 0;

  unwind_protect frame;

  std::string nm = file_name;

  size_t nm_len = nm.length ();

  std::string file;

  bool relative_lookup = false;

  file = nm;

  if ((nm_len > 4 && nm.substr (nm_len-4) == ".oct")
      || (nm_len > 4 && nm.substr (nm_len-4) == ".mex")
      || (nm_len > 2 && nm.substr (nm_len-2) == ".m"))
    {
      nm = octave_env::base_pathname (file);
      nm = nm.substr (0, nm.find_last_of ('.'));

      size_t pos = nm.find_last_of (file_ops::dir_sep_str ());
      if (pos != std::string::npos)
        nm = nm.substr (pos+1);
    }

  relative_lookup = ! octave_env::absolute_pathname (file);

  file = octave_env::make_absolute (file);

  int len = file.length ();

  if (len > 4 && file.substr (len-4, len-1) == ".oct")
    {
      if (autoload && ! fcn_name.empty ())
        nm = fcn_name;

      retval = octave_dynamic_loader::load_oct (nm, file, relative_lookup);
    }
  else if (len > 4 && file.substr (len-4, len-1) == ".mex")
    {
      // Temporarily load m-file version of mex-file, if it exists,
      // to get the help-string to use.

      octave_function *tmpfcn = parse_fcn_file (file.substr (0, len - 2),
                                                nm, dispatch_type, false,
                                                autoload, autoload,
                                                relative_lookup, "");

      retval = octave_dynamic_loader::load_mex (nm, file, relative_lookup);

      if (tmpfcn)
        retval->document (tmpfcn->doc_string ());
      delete tmpfcn;
    }
  else if (len > 2)
    {
      retval = parse_fcn_file (file, nm, dispatch_type, true, autoload,
                               autoload, relative_lookup, "");
    }

  if (retval)
    {
      retval->stash_dir_name (dir_name);

      if (retval->is_user_function ())
        {
          symbol_table::scope_id id = retval->scope ();

          symbol_table::stash_dir_name_for_subfunctions (id, dir_name);
        }
    }

  return retval;
}

DEFUN (autoload, args, ,
  "-*- texinfo -*-\n\
@deftypefn  {Built-in Function} {@var{autoload_map} =} autoload ()\n\
@deftypefnx {Built-in Function} {} autoload (@var{function}, @var{file})\n\
@deftypefnx {Built-in Function} {} autoload (@dots{}, \"remove\")\n\
Define @var{function} to autoload from @var{file}.\n\
\n\
The second argument, @var{file}, should be an absolute file name or\n\
a file name in the same directory as the function or script from which\n\
the autoload command was run.  @var{file} @emph{should not} depend on the\n\
Octave load path.\n\
\n\
Normally, calls to @code{autoload} appear in PKG_ADD script files that\n\
are evaluated when a directory is added to Octave's load path.  To\n\
avoid having to hardcode directory names in @var{file}, if @var{file}\n\
is in the same directory as the PKG_ADD script then\n\
\n\
@example\n\
autoload (\"foo\", \"bar.oct\");\n\
@end example\n\
\n\
@noindent\n\
will load the function @code{foo} from the file @code{bar.oct}.  The above\n\
usage when @code{bar.oct} is not in the same directory, or usages such as\n\
\n\
@example\n\
autoload (\"foo\", file_in_loadpath (\"bar.oct\"))\n\
@end example\n\
\n\
@noindent\n\
are strongly discouraged, as their behavior may be unpredictable.\n\
\n\
With no arguments, return a structure containing the current autoload map.\n\
\n\
If a third argument @qcode{\"remove\"} is given, the function is cleared and\n\
not loaded anymore during the current Octave session.\n\
\n\
@seealso{PKG_ADD}\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      Cell func_names (dim_vector (autoload_map.size (), 1));
      Cell file_names (dim_vector (autoload_map.size (), 1));

      octave_idx_type i = 0;
      typedef std::map<std::string, std::string>::const_iterator am_iter;
      for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
        {
          func_names(i) = p->first;
          file_names(i) = p->second;

          i++;
        }

      octave_map m;

      m.assign ("function", func_names);
      m.assign ("file", file_names);

      retval = m;
    }
  else if (nargin == 2 || nargin == 3)
    {
      string_vector argv = args.make_argv ("autoload");

      if (! error_state)
        {
          std::string nm = argv[2];

          if (! octave_env::absolute_pathname (nm))
            {
              octave_user_code *fcn = octave_call_stack::caller_user_code ();

              bool found = false;

              if (fcn)
                {
                  std::string fname = fcn->fcn_file_name ();

                  if (! fname.empty ())
                    {
                      fname = octave_env::make_absolute (fname);
                      fname = fname.substr (0, fname.find_last_of (file_ops::dir_sep_str ()) + 1);

                      file_stat fs (fname + nm);

                      if (fs.exists ())
                        {
                          nm = fname + nm;
                          found = true;
                        }
                    }
                }
              if (! found)
                warning_with_id ("Octave:autoload-relative-file-name",
                                 "autoload: '%s' is not an absolute file name",
                                 nm.c_str ());
            }
          if (nargin == 2)
            autoload_map[argv[1]] = nm;
          else if (nargin == 3)
            {
              if (argv[3].compare ("remove") != 0)
                error_with_id ("Octave:invalid-input-arg",
                               "autoload: third argument can only be 'remove'");

              // Remove function from symbol table and autoload map.
              symbol_table::clear_dld_function (argv[1]);
              autoload_map.erase (argv[1]);
            }
        }
    }
  else
    print_usage ();

  return retval;
}

void
source_file (const std::string& file_name, const std::string& context,
             bool verbose, bool require_file, const std::string& warn_for)
{
  // Map from absolute name of script file to recursion level.  We
  // use a map instead of simply placing a limit on recursion in the
  // source_file function so that two mutually recursive scripts
  // written as
  //
  //   foo1.m:
  //   ------
  //   foo2
  //
  //   foo2.m:
  //   ------
  //   foo1
  //
  // and called with
  //
  //   foo1
  //
  // (for example) will behave the same if they are written as
  //
  //   foo1.m:
  //   ------
  //   source ("foo2.m")
  //
  //   foo2.m:
  //   ------
  //   source ("foo1.m")
  //
  // and called with
  //
  //   source ("foo1.m")
  //
  // (for example).

  static std::map<std::string, int> source_call_depth;

  std::string file_full_name = file_ops::tilde_expand (file_name);

  file_full_name = octave_env::make_absolute (file_full_name);

  unwind_protect frame;

  if (source_call_depth.find (file_full_name) == source_call_depth.end ())
    source_call_depth[file_full_name] = -1;

  frame.protect_var (source_call_depth[file_full_name]);

  source_call_depth[file_full_name]++;

  if (source_call_depth[file_full_name] >= Vmax_recursion_depth)
    {
      error ("max_recursion_depth exceeded");
      return;
    }

  if (! context.empty ())
    {
      if (context == "caller")
        octave_call_stack::goto_caller_frame ();
      else if (context == "base")
        octave_call_stack::goto_base_frame ();
      else
        error ("source: context must be \"caller\" or \"base\"");

      if (! error_state)
        frame.add_fcn (octave_call_stack::pop);
    }

  if (! error_state)
    {
      octave_function *fcn = parse_fcn_file (file_full_name, file_name,
                                             "", require_file, true,
                                             false, false, warn_for);

      if (! error_state)
        {
          if (fcn && fcn->is_user_script ())
            {
              octave_value_list args;

              if (verbose)
                {
                  std::cout << "executing commands from " << file_full_name << " ... ";
                  reading_startup_message_printed = true;
                  std::cout.flush ();
                }

              fcn->do_multi_index_op (0, args);

              if (verbose)
                std::cout << "done." << std::endl;

              delete fcn;
            }
        }
      else
        error ("source: error sourcing file '%s'",
               file_full_name.c_str ());
    }
}

DEFUN (mfilename, args, ,
  "-*- texinfo -*-\n\
@deftypefn  {Built-in Function} {} mfilename ()\n\
@deftypefnx {Built-in Function} {} mfilename (\"fullpath\")\n\
@deftypefnx {Built-in Function} {} mfilename (\"fullpathext\")\n\
Return the name of the currently executing file.\n\
\n\
When called from outside an m-file return the empty string.  Given the\n\
argument @qcode{\"fullpath\"}, include the directory part of the file name,\n\
but not the extension.  Given the argument @qcode{\"fullpathext\"}, include\n\
the directory part of the file name and the extension.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      print_usage ();
      return retval;
    }

  std::string arg;

  if (nargin == 1)
    {
      arg = args(0).string_value ();

      if (error_state)
        {
          error ("mfilename: expecting argument to be a character string");
          return retval;
        }
    }

  std::string fname;

  octave_user_code *fcn = octave_call_stack::caller_user_code ();

  if (fcn)
    {
      fname = fcn->fcn_file_name ();

      if (fname.empty ())
        fname = fcn->name ();
    }

  if (arg == "fullpathext")
    retval = fname;
  else
    {
      size_t dpos = fname.rfind (file_ops::dir_sep_char ());
      size_t epos = fname.rfind ('.');

      if (epos <= dpos)
        epos = std::string::npos;

      fname = (epos != std::string::npos) ? fname.substr (0, epos) : fname;

      if (arg == "fullpath")
        retval = fname;
      else
        retval = (dpos != std::string::npos) ? fname.substr (dpos+1) : fname;
    }

  return retval;
}

DEFUN (source, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} source (@var{file})\n\
Parse and execute the contents of @var{file}.\n\
\n\
This is equivalent to executing commands from a script file, but without\n\
requiring the file to be named @file{@var{file}.m}.\n\
@seealso{run}\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 1 || nargin == 2)
    {
      std::string file_name = args(0).string_value ();

      if (! error_state)
        {
          std::string context;

          if (nargin == 2)
            context = args(1).string_value ();

          if (! error_state)
            source_file (file_name, context);
          else
            error ("source: expecting context to be character string");
        }
      else
        error ("source: expecting file name as argument");
    }
  else
    print_usage ();

  return retval;
}

// Evaluate an Octave function (built-in or interpreted) and return
// the list of result values.  NAME is the name of the function to
// call.  ARGS are the arguments to the function.  NARGOUT is the
// number of output arguments expected.

octave_value_list
feval (const std::string& name, const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  octave_value fcn = symbol_table::find_function (name, args);

  if (fcn.is_defined ())
    retval = fcn.do_multi_index_op (nargout, args);
  else
    {
      maybe_missing_function_hook (name);
      if (! error_state)
        error ("feval: function '%s' not found", name.c_str ());
    }

  return retval;
}

octave_value_list
feval (octave_function *fcn, const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  if (fcn)
    retval = fcn->do_multi_index_op (nargout, args);

  return retval;
}

static octave_value_list
get_feval_args (const octave_value_list& args)
{
  return args.slice (1, args.length () - 1, true);
}


// Evaluate an Octave function (built-in or interpreted) and return
// the list of result values.  The first element of ARGS should be a
// string containing the name of the function to call, then the rest
// are the actual arguments to the function.  NARGOUT is the number of
// output arguments expected.

octave_value_list
feval (const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      octave_value f_arg = args(0);

      if (f_arg.is_string ())
        {
          std::string name = f_arg.string_value ();

          if (! error_state)
            {
              octave_value_list tmp_args = get_feval_args (args);

              retval = feval (name, tmp_args, nargout);
            }
        }
      else if (f_arg.is_function_handle ()
               || f_arg.is_anonymous_function ()
               || f_arg.is_inline_function ())
        {
          const octave_value_list tmp_args = get_feval_args (args);

          retval = f_arg.do_multi_index_op (nargout, tmp_args);
        }
      else
        error ("feval: first argument must be a string, inline function or a function handle");
    }

  return retval;
}

DEFUN (feval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} feval (@var{name}, @dots{})\n\
Evaluate the function named @var{name}.  Any arguments after the first\n\
are passed as inputs to the named function.  For example,\n\
\n\
@example\n\
@group\n\
feval (\"acos\", -1)\n\
     @result{} 3.1416\n\
@end group\n\
@end example\n\
\n\
@noindent\n\
calls the function @code{acos} with the argument @samp{-1}.\n\
\n\
The function @code{feval} can also be used with function handles of\n\
any sort (@pxref{Function Handles}).  Historically, @code{feval} was\n\
the only way to call user-supplied functions in strings, but\n\
function handles are now preferred due to the cleaner syntax they\n\
offer.  For example,\n\
\n\
@example\n\
@group\n\
@var{f} = @@exp;\n\
feval (@var{f}, 1)\n\
    @result{} 2.7183\n\
@var{f} (1)\n\
    @result{} 2.7183\n\
@end group\n\
@end example\n\
\n\
@noindent\n\
are equivalent ways to call the function referred to by @var{f}.  If it\n\
cannot be predicted beforehand whether @var{f} is a function handle,\n\
function name in a string, or inline function then @code{feval} can be used\n\
instead.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    retval = feval (args, nargout);
  else
    print_usage ();

  return retval;
}

DEFUN (builtin, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@dots{}] =} builtin (@var{f}, @dots{})\n\
Call the base function @var{f} even if @var{f} is overloaded to\n\
another function for the given type signature.\n\
\n\
This is normally useful when doing object-oriented programming and there\n\
is a requirement to call one of Octave's base functions rather than\n\
the overloaded one of a new class.\n\
\n\
A trivial example which redefines the @code{sin} function to be the\n\
@code{cos} function shows how @code{builtin} works.\n\
\n\
@example\n\
@group\n\
sin (0)\n\
  @result{} 0\n\
function y = sin (x), y = cos (x); endfunction\n\
sin (0)\n\
  @result{} 1\n\
builtin (\"sin\", 0)\n\
  @result{} 0\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      const std::string name (args(0).string_value ());

      if (! error_state)
        {
          octave_value fcn = symbol_table::builtin_find (name);

          if (fcn.is_defined ())
            retval = feval (fcn.function_value (), args.splice (0, 1),
                            nargout);
          else
            error ("builtin: lookup for symbol '%s' failed", name.c_str ());
        }
      else
        error ("builtin: function name (F) must be a string");
    }
  else
    print_usage ();

  return retval;
}

octave_value_list
eval_string (const std::string& eval_str, bool silent,
             int& parse_status, int nargout)
{
  octave_value_list retval;

  octave_parser parser (eval_str);

  do
    {
      parser.reset ();

      parse_status = parser.run ();

      if (parse_status == 0)
        {
          if (parser.stmt_list)
            {
              tree_statement *stmt = 0;

              if (parser.stmt_list->length () == 1
                  && (stmt = parser.stmt_list->front ())
                  && stmt->is_expression ())
                {
                  tree_expression *expr = stmt->expression ();

                  if (silent)
                    expr->set_print_flag (false);

                  bool do_bind_ans = false;

                  if (expr->is_identifier ())
                    {
                      tree_identifier *id
                        = dynamic_cast<tree_identifier *> (expr);

                      do_bind_ans = (! id->is_variable ());
                    }
                  else
                    do_bind_ans = (! expr->is_assignment_expression ());

                  retval = expr->rvalue (nargout);

                  if (do_bind_ans && ! (error_state || retval.empty ()))
                    bind_ans (retval(0), expr->print_result ());

                  if (nargout == 0)
                    retval = octave_value_list ();
                }
              else if (nargout == 0)
                parser.stmt_list->accept (*current_evaluator);
              else
                error ("eval: invalid use of statement list");

              if (error_state
                  || tree_return_command::returning
                  || tree_break_command::breaking
                  || tree_continue_command::continuing)
                break;
            }
          else if (parser.lexer.end_of_input)
            break;
        }
    }
  while (parse_status == 0);

  return retval;
}

octave_value
eval_string (const std::string& eval_str, bool silent, int& parse_status)
{
  octave_value retval;

  octave_value_list tmp = eval_string (eval_str, silent, parse_status, 1);

  if (! tmp.empty ())
    retval = tmp(0);

  return retval;
}

static octave_value_list
eval_string (const octave_value& arg, bool silent, int& parse_status,
             int nargout)
{
  std::string s = arg.string_value ();

  if (error_state)
    {
      error ("eval: expecting std::string argument");
      return octave_value (-1);
    }

  return eval_string (s, silent, parse_status, nargout);
}

void
cleanup_statement_list (tree_statement_list **lst)
{
  if (*lst)
    {
      delete *lst;
      *lst = 0;
    }
}

DEFUN (eval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn  {Built-in Function} {} eval (@var{try})\n\
@deftypefnx {Built-in Function} {} eval (@var{try}, @var{catch})\n\
Parse the string @var{try} and evaluate it as if it were an Octave\n\
program.  If that fails, evaluate the optional string @var{catch}.\n\
The string @var{try} is evaluated in the current context,\n\
so any results remain available after @code{eval} returns.\n\
\n\
The following example creates the variable @var{A} with the approximate\n\
value of 3.1416 in the current workspace.\n\
\n\
@example\n\
eval (\"A = acos(-1);\");\n\
@end example\n\
\n\
If an error occurs during the evaluation of @var{try} then the @var{catch}\n\
string is evaluated, as the following example shows:\n\
\n\
@example\n\
@group\n\
eval ('error (\"This is a bad example\");',\n\
      'printf (\"This error occurred:\\n%s\\n\", lasterr ());');\n\
     @print{} This error occurred:\n\
        This is a bad example\n\
@end group\n\
@end example\n\
\n\
Programming Note: if you are only using @code{eval} as an error-capturing\n\
mechanism, rather than for the execution of arbitrary code strings,\n\
Consider using try/catch blocks or unwind_protect/unwind_protect_cleanup\n\
blocks instead.  These techniques have higher performance and don't introduce\n\
the security considerations that the evaluation of arbitrary code does.\n\
@seealso{evalin}\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      unwind_protect frame;

      if (nargin > 1)
        {
          frame.protect_var (buffer_error_messages);
          buffer_error_messages++;
        }

      int parse_status = 0;

      octave_value_list tmp = eval_string (args(0), nargout > 0,
                                           parse_status, nargout);

      if (nargin > 1 && (parse_status != 0 || error_state))
        {
          error_state = 0;

          // Set up for letting the user print any messages from
          // errors that occurred in the first part of this eval().

          buffer_error_messages--;

          tmp = eval_string (args(1), nargout > 0, parse_status, nargout);

          if (nargout > 0)
            retval = tmp;
        }
      else if (nargout > 0)
        retval = tmp;
    }
  else
    print_usage ();

  return retval;
}

/*

%!shared x
%! x = 1;

%!assert (eval ("x"), 1)
%!assert (eval ("x;"))
%!assert (eval ("x;"), 1);

%!test
%! y = eval ("x");
%! assert (y, 1);

%!test
%! y = eval ("x;");
%! assert (y, 1);

%!test
%! eval ("x = 1;")
%! assert (x,1);

%!test
%! eval ("flipud = 2;");
%! assert (flipud, 2);

%!function y = __f ()
%!  eval ("flipud = 2;");
%!  y = flipud;
%!endfunction
%!assert (__f(), 2)

% bug #35645
%!test
%! [a,] = gcd (1,2);
%! [a,b,] = gcd (1, 2);

*/

DEFUN (assignin, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} assignin (@var{context}, @var{varname}, @var{value})\n\
Assign @var{value} to @var{varname} in context @var{context}, which\n\
may be either @qcode{\"base\"} or @qcode{\"caller\"}.\n\
@seealso{evalin}\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 3)
    {
      std::string context = args(0).string_value ();

      if (! error_state)
        {
          unwind_protect frame;

          if (context == "caller")
            octave_call_stack::goto_caller_frame ();
          else if (context == "base")
            octave_call_stack::goto_base_frame ();
          else
            error ("assignin: CONTEXT must be \"caller\" or \"base\"");

          if (! error_state)
            {
              frame.add_fcn (octave_call_stack::pop);

              std::string nm = args(1).string_value ();

              if (! error_state)
                {
                  if (valid_identifier (nm))
                    symbol_table::assign (nm, args(2));
                  else
                    error ("assignin: invalid variable name in argument VARNAME");
                }
              else
                error ("assignin: VARNAME must be a string");
            }
        }
      else
        error ("assignin: CONTEXT must be a string");
    }
  else
    print_usage ();

  return retval;
}

DEFUN (evalin, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn  {Built-in Function} {} evalin (@var{context}, @var{try})\n\
@deftypefnx {Built-in Function} {} evalin (@var{context}, @var{try}, @var{catch})\n\
Like @code{eval}, except that the expressions are evaluated in the\n\
context @var{context}, which may be either @qcode{\"caller\"} or\n\
@qcode{\"base\"}.\n\
@seealso{eval, assignin}\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      std::string context = args(0).string_value ();

      if (! error_state)
        {
          unwind_protect frame;

          if (context == "caller")
            octave_call_stack::goto_caller_frame ();
          else if (context == "base")
            octave_call_stack::goto_base_frame ();
          else
            error ("evalin: CONTEXT must be \"caller\" or \"base\"");

          if (! error_state)
            {
              frame.add_fcn (octave_call_stack::pop);

              if (nargin > 2)
                {
                  frame.protect_var (buffer_error_messages);
                  buffer_error_messages++;
                }

              int parse_status = 0;

              octave_value_list tmp = eval_string (args(1), nargout > 0,
                                                   parse_status, nargout);

              if (nargout > 0)
                retval = tmp;

              if (nargin > 2 && (parse_status != 0 || error_state))
                {
                  error_state = 0;

                  // Set up for letting the user print any messages from
                  // errors that occurred in the first part of this eval().

                  buffer_error_messages--;

                  tmp = eval_string (args(2), nargout > 0,
                                     parse_status, nargout);

                  retval = (nargout > 0) ? tmp : octave_value_list ();
                }
            }
        }
      else
        error ("evalin: CONTEXT must be a string");
    }
  else
    print_usage ();

  return retval;
}

DEFUN (__parser_debug_flag__, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn  {Built-in Function} {@var{val} =} __parser_debug_flag__ ()\n\
@deftypefnx {Built-in Function} {@var{old_val} =} __parser_debug_flag__ (@var{new_val})\n\
Query or set the internal flag that determines whether Octave's parser prints\n\
debug information as it processes an expression.\n\
@seealso{__lexer_debug_flag__}\n\
@end deftypefn")
{
  octave_value retval;

  bool debug_flag = octave_debug;

  retval = set_internal_variable (debug_flag, args, nargout,
                                  "__parser_debug_flag__");

  octave_debug = debug_flag;

  return retval;
}

DEFUN (__parse_file__, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} __parse_file__ (@var{file}, @var{verbose})\n\
Undocumented internal function.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 1 || nargin == 2)
    {
      std::string file = args(0).string_value ();
      
      std::string full_file = octave_env::make_absolute (file);

      size_t file_len = file.length ();

      if ((file_len > 4 && file.substr (file_len-4) == ".oct")
          || (file_len > 4 && file.substr (file_len-4) == ".mex")
          || (file_len > 2 && file.substr (file_len-2) == ".m"))
        {
          file = octave_env::base_pathname (file);
          file = file.substr (0, file.find_last_of ('.'));

          size_t pos = file.find_last_of (file_ops::dir_sep_str ());
          if (pos != std::string::npos)
            file = file.substr (pos+1);
        }

      if (! error_state)
        {
          if (nargin == 2)
            octave_stdout << "parsing " << full_file << std::endl;

          octave_function *fcn = parse_fcn_file (full_file, file, "",
                                                 true, false, false,
                                                 false, "__parse_file__");

          if (fcn)
            delete fcn;
        }
      else
        error ("__parse_file__: expecting file name as argument");
    }
  else
    print_usage ();

  return retval;
}
