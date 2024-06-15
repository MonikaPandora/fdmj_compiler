/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"


#include <stdio.h>
#include "fdmjast.h"

extern int yylex(); 
void yyerror(char*);
void myerror(char*);
int  yywrap();

extern void add_char();

void check_semi(char check, A_pos pos);
void check_parentheses(char check, A_pos pos);

extern A_prog root;


#line 89 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 206 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_MONIKA_COMPILER_FDMJ_COMPILER_BUILD_INCLUDE_FRONTEND_PARSER_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   741

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  254

#define YYUNDEFTOK  2
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,     2,     2,    46,     2,    48,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    47,
       2,    45,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
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
      35,    36,    37,    38,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    91,    91,    96,   102,   104,   108,   110,   113,   117,
     121,   125,   129,   133,   137,   141,   145,   149,   155,   157,
     164,   166,   170,   172,   176,   178,   182,   184,   186,   188,
     190,   194,   198,   202,   206,   210,   214,   218,   222,   226,
     230,   235,   242,   244,   247,   252,   254,   256,   258,   260,
     264,   268,   270,   272,   274,   276,   278,   282,   284,   286,
     288,   290,   292,   294,   296,   298,   300,   302,   304,   306,
     308,   310,   313,   315,   317,   319,   323,   325,   329,   331,
     335,   337,   341,   343,   347,   349,   353,   357,   359,   361,
     363,   365,   370,   372,   374,   381,   383,   385
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PUBLIC", "INT", "MAIN", "FLOAT",
  "CLASS", "NEW", "IF", "ELSE", "WHILE", "CONTINUE", "BREAK", "THIS",
  "EXTENDS", "RETURN", "PUTNUM", "PUTCH", "PUTARRAY", "STARTTIME",
  "STOPTIME", "LENGTH", "GETNUM", "GETCH", "GETARRAY", "ADD", "MINUS",
  "TIMES", "DIV", "OR", "AND", "LE", "LESS", "GE", "GREATER", "EQ", "NEQ",
  "NOT", "'('", "')'", "'['", "']'", "'{'", "'}'", "'='", "','", "';'",
  "'.'", "ID", "NUM", "BOOLTRUE", "BOOLFALSE", "UMINUS", "LOWER_THAN_ELSE",
  "$accept", "PROG", "MAINMETHOD", "VARDECLLIST", "CHECK_SEMI", "VARDECL",
  "CONST", "CONSTLIST", "CONSTREST", "STMLIST", "STM", "CHECK_PARENT",
  "EXP", "EXPLIST", "EXPREST", "CLASSDECLLIST", "CLASSDECL",
  "METHODDECLLIST", "METHODDECL", "TYPE", "FORMALLIST", "FORMALREST", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    40,
      41,    91,    93,   123,   125,    61,    44,    59,    46,   294,
     295,   296,   297,   298,   299
};
# endif

#define YYPACT_NINF (-193)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-93)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      69,    14,   107,   122,   121,  -193,    12,  -193,   122,    15,
      80,  -193,    63,    96,   103,    -3,  -193,  -193,  -193,   138,
      98,   138,   -28,    -2,   100,   248,   138,   109,   150,   114,
      16,   119,    19,   113,    88,   134,   139,    21,    21,  -193,
     287,   141,   152,   154,    15,    15,   155,    15,    15,   157,
     287,   287,   116,   248,  -193,  -193,  -193,  -193,   133,   248,
     314,  -193,   138,   182,   156,   150,   153,    54,    61,  -193,
    -193,   158,    61,  -193,    21,   117,   160,    15,   287,   287,
    -193,  -193,    86,   287,   287,   287,    21,    21,   287,  -193,
    -193,   287,    87,    87,   248,   337,   161,  -193,  -193,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   280,   287,   164,   150,   165,   169,   180,   183,  -193,
    -193,    22,  -193,  -193,   159,  -193,    21,    44,    21,  -193,
     287,   287,  -193,   360,   383,   287,   184,  -193,   406,   429,
     452,  -193,  -193,   475,   498,   187,  -193,  -193,   142,   142,
      87,    87,   659,   676,   210,   210,   210,   210,   693,   693,
     189,   521,    86,   196,   199,   198,   202,  -193,   206,   204,
    -193,  -193,  -193,   205,  -193,  -193,   544,   567,   248,   203,
     224,    21,    21,   287,  -193,  -193,   287,   231,  -193,  -193,
     287,  -193,  -193,  -193,   168,    61,    61,  -193,  -193,   239,
    -193,  -193,   287,  -193,  -193,   590,   613,   287,   636,   236,
     237,   229,   240,   233,   238,   241,   248,   243,    21,  -193,
     245,   287,  -193,     1,  -193,   235,   247,    61,  -193,    21,
      21,  -193,  -193,  -193,    21,   636,  -193,   178,  -193,   138,
     233,  -193,  -193,  -193,  -193,   244,   257,   248,  -193,  -193,
     235,   249,  -193,  -193
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    80,     0,     1,     0,     2,    80,     0,
       0,    81,     0,     0,     0,     0,    44,    43,    42,     4,
       0,     4,     0,     0,     0,    24,     4,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,    52,    45,    46,    47,     0,    24,
       0,     5,     4,     0,     0,    84,     0,     0,     0,     6,
      10,     0,     0,    16,     0,     0,     0,     0,     0,     0,
      34,    35,     0,     0,     0,     0,     0,     0,     0,    49,
      50,     0,    70,    69,    24,     0,     0,     3,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    84,    88,    89,     0,     0,    82,
      85,     0,     7,     8,     0,    18,     0,     0,     0,     9,
       0,     0,    56,     0,     0,     0,     0,    36,     0,     0,
       0,    40,    41,     0,     0,     0,    71,    26,    57,    58,
      59,    60,    61,    62,    64,    63,    66,    65,    67,    68,
       0,     0,     0,    73,     0,     0,     0,    87,     0,     0,
      12,    19,    11,     0,    14,    17,     0,     0,     0,     0,
      73,     0,     0,     0,    48,    51,     0,     0,    75,    31,
      76,    83,    90,    91,     0,    20,    20,    54,    55,    28,
      30,    29,    76,    37,    38,     0,     0,    76,    78,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,    72,
       0,     0,    77,     0,    94,    95,     0,     0,    21,     0,
       0,    27,    74,    39,     0,    78,    33,     0,    93,     4,
      22,    13,    15,    32,    79,     0,     0,    24,    23,    97,
      95,     0,    96,    86
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -193,  -193,  -193,   -21,   -31,  -193,   -64,   112,    52,   -50,
    -108,    55,   -26,  -192,    78,   288,  -193,   -54,  -193,  -144,
    -193,    65
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    25,    70,    26,   213,   214,   228,    58,
      59,    14,    60,   209,   222,     7,     8,    64,    65,   118,
     212,   238
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    73,    67,    96,   126,    61,    80,    81,   128,    98,
     217,   120,    20,    29,    82,   220,    12,    67,     4,    10,
      67,    30,    67,    67,    92,    93,    95,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,    31,
      21,   114,   -74,   129,   145,    67,   -74,    32,    69,   -74,
     211,   137,   133,   134,    13,   141,   142,   138,   139,   140,
     164,    68,   143,    69,    72,   144,    69,   169,    69,    69,
     199,   201,     1,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   161,   162,    67,   124,   173,
     170,    69,    75,   246,    76,   172,   174,   175,   122,    86,
      87,   123,    89,    90,   176,   177,    16,     5,   231,   161,
      17,   125,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,    34,     6,     9,   135,   135,    15,
      39,   189,   132,    69,   136,   136,    18,    77,    46,    47,
      48,    49,    22,    50,    23,    24,    19,    27,   200,    33,
     203,   204,    62,    63,    51,    52,    66,   205,   130,    94,
     206,    71,    74,   240,   208,    54,    55,    56,    57,   210,
     101,   102,   115,    78,   116,   117,   208,    97,    79,   245,
      83,   208,   115,   135,   116,   117,   115,   233,   116,   117,
     136,    84,   236,    85,    88,   235,    91,   251,   241,   242,
     119,   131,   121,   243,    67,   147,   165,   127,   -92,   171,
     166,    34,    35,   163,    36,    37,    38,    39,   247,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,   167,
      50,   186,   168,   180,   187,   190,    99,   100,   101,   102,
     192,    51,    52,   191,   193,   194,    53,   195,   196,   216,
      69,   135,    54,    55,    56,    57,    34,    35,   136,    36,
      37,    38,    39,   202,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,   207,    50,   223,   224,   225,   227,
     226,   237,   229,   232,   249,   230,    51,    52,    34,   234,
     239,    53,   248,   253,    39,    34,    11,    54,    55,    56,
      57,    39,    46,    47,    48,    49,   250,    50,   215,    46,
      47,    48,    49,   244,    50,   252,     0,     0,    51,    52,
       0,     0,   160,     0,     0,    51,    52,     0,     0,    54,
      55,    56,    57,     0,     0,     0,    54,    55,    56,    57,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,   111,     0,     0,     0,   112,
       0,     0,   113,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     0,     0,   146,   135,     0,
       0,     0,     0,     0,     0,   136,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     0,     0,
     178,   135,     0,     0,     0,     0,     0,     0,   136,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,   179,   135,     0,     0,     0,     0,     0,
       0,   136,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,   181,   135,     0,     0,
       0,     0,     0,     0,   136,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,   182,
     135,     0,     0,     0,     0,     0,     0,   136,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,   135,     0,     0,     0,     0,   183,     0,
     136,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,     0,     0,   184,   135,     0,     0,     0,
       0,     0,     0,   136,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,     0,     0,   185,   135,
       0,     0,     0,     0,     0,     0,   136,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     0,
       0,     0,   135,   188,     0,     0,     0,     0,     0,   136,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,   135,   197,     0,     0,     0,
       0,     0,   136,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     0,     0,     0,   135,   198,
       0,     0,     0,     0,     0,   136,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     0,     0,
     218,   135,     0,     0,     0,     0,     0,     0,   136,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,   219,   135,     0,     0,     0,     0,     0,
       0,   136,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,     0,   135,     0,     0,
       0,     0,   221,     0,   136,    99,   100,   101,   102,     0,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     135,     0,    99,   100,   101,   102,     0,   136,   105,   106,
     107,   108,   109,   110,     0,     0,     0,   135,     0,    99,
     100,   101,   102,     0,   136,   105,   106,   107,   108,     0,
       0,     0,     0,     0,   135,     0,     0,     0,     0,     0,
       0,   136
};

static const yytype_int16 yycheck[] =
{
      21,    32,     1,    53,    68,    26,    37,    38,    72,    59,
     202,    65,    15,    41,    40,   207,     1,     1,     4,     7,
       1,    49,     1,     1,    50,    51,    52,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    41,
      43,    62,    41,    74,    94,     1,    45,    49,    47,    48,
     194,    82,    78,    79,    39,    86,    87,    83,    84,    85,
     114,    45,    88,    47,    45,    91,    47,    45,    47,    47,
     178,   179,     3,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     1,    27,    45,
     121,    47,     4,   237,     6,   126,   127,   128,    44,    44,
      45,    47,    47,    48,   130,   131,    43,     0,   216,   135,
      47,    50,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     8,     3,     5,    41,    41,    49,
      14,   162,    77,    47,    48,    48,    40,    49,    22,    23,
      24,    25,     4,    27,     6,     7,    43,    49,   179,    49,
     181,   182,    43,     3,    38,    39,    42,   183,    41,    43,
     186,    42,    49,   227,   190,    49,    50,    51,    52,     1,
      28,    29,     4,    39,     6,     7,   202,    44,    39,     1,
      39,   207,     4,    41,     6,     7,     4,   218,     6,     7,
      48,    39,   223,    39,    39,   221,    39,   247,   229,   230,
      44,    41,    49,   234,     1,    44,    41,    49,    40,    50,
      41,     8,     9,    49,    11,    12,    13,    14,   239,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    49,
      27,    44,    49,    49,    45,    39,    26,    27,    28,    29,
      42,    38,    39,    44,    42,    39,    43,    43,    43,    10,
      47,    41,    49,    50,    51,    52,     8,     9,    48,    11,
      12,    13,    14,    39,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    43,    27,    40,    40,    49,    46,
      40,    46,    44,    40,    40,    44,    38,    39,     8,    44,
      43,    43,   240,    44,    14,     8,     8,    49,    50,    51,
      52,    14,    22,    23,    24,    25,    49,    27,   196,    22,
      23,    24,    25,   235,    27,   250,    -1,    -1,    38,    39,
      -1,    -1,    42,    -1,    -1,    38,    39,    -1,    -1,    49,
      50,    51,    52,    -1,    -1,    -1,    49,    50,    51,    52,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    41,    -1,    -1,    -1,    45,
      -1,    -1,    48,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    46,    -1,
      48,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    -1,    48,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    -1,    48,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    -1,    48,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    46,    -1,    48,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      41,    -1,    26,    27,    28,    29,    -1,    48,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    41,    -1,    26,
      27,    28,    29,    -1,    48,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    56,    57,     4,     0,     3,    70,    71,     5,
       7,    70,     1,    39,    66,    49,    43,    47,    40,    43,
      15,    43,     4,     6,     7,    58,    60,    49,    58,    41,
      49,    41,    49,    49,     8,     9,    11,    12,    13,    14,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      27,    38,    39,    43,    49,    50,    51,    52,    64,    65,
      67,    58,    43,     3,    72,    73,    42,     1,    45,    47,
      59,    42,    45,    59,    49,     4,     6,    49,    39,    39,
      59,    59,    67,    39,    39,    39,    66,    66,    39,    66,
      66,    39,    67,    67,    43,    67,    64,    44,    64,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    41,    45,    48,    58,     4,     6,     7,    74,    44,
      72,    49,    44,    47,    27,    50,    61,    49,    61,    59,
      41,    41,    66,    67,    67,    41,    48,    59,    67,    67,
      67,    59,    59,    67,    67,    64,    40,    44,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      42,    67,    67,    49,    72,    41,    41,    49,    49,    45,
      59,    50,    59,    45,    59,    59,    67,    67,    40,    40,
      49,    40,    40,    46,    40,    40,    44,    45,    42,    59,
      39,    44,    42,    42,    39,    43,    43,    42,    42,    65,
      59,    65,    39,    59,    59,    67,    67,    43,    67,    68,
       1,    74,    75,    61,    62,    62,    10,    68,    40,    40,
      68,    46,    69,    40,    40,    49,    40,    46,    63,    44,
      44,    65,    40,    59,    44,    67,    59,    46,    76,    43,
      61,    59,    59,    59,    69,     1,    74,    58,    63,    40,
      49,    64,    76,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    58,    58,    59,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    66,    66,    66,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    72,    73,    74,    74,    74,
      74,    74,    75,    75,    75,    76,    76,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     8,     0,     2,     1,     2,     2,     4,
       3,     5,     5,     9,     5,     9,     3,     5,     1,     2,
       0,     2,     0,     3,     0,     2,     3,     7,     5,     5,
       5,     4,     8,     7,     2,     2,     3,     5,     5,     7,
       3,     3,     2,     2,     2,     1,     1,     1,     4,     2,
       2,     4,     1,     1,     5,     5,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     6,     3,     6,     4,     0,     2,     0,     3,
       0,     2,     7,     9,     0,     2,    10,     2,     1,     1,
       3,     3,     0,     3,     2,     0,     4,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
  case 2:
#line 91 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                               {
  root = A_Prog(A_Pos((yyvsp[-1].mainMethod)->pos->line, (yyvsp[-1].mainMethod)->pos->pos), (yyvsp[-1].mainMethod), (yyvsp[0].classDeclList));
  (yyval.prog) = root;
}
#line 1643 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 3:
#line 96 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                                                     {
  check_parentheses((yyvsp[-4].check), (yyvsp[-7].pos));
  yyerrok;
  (yyval.mainMethod) = A_MainMethod((yyvsp[-7].pos), (yyvsp[-2].varDeclList), (yyvsp[-1].stmList));
}
#line 1653 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 4:
#line 102 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  (yyval.varDeclList) = NULL;
}
#line 1661 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 5:
#line 104 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  (yyval.varDeclList) = A_VarDeclList((yyvsp[-1].varDecl), (yyvsp[0].varDeclList));
}
#line 1669 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 6:
#line 108 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                 {
  (yyval.check) = 0;
}
#line 1677 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 7:
#line 110 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
              {
  add_char('}');
  (yyval.check) = 1;
}
#line 1686 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 8:
#line 113 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
              {
  (yyval.check) = 1;
}
#line 1694 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 9:
#line 117 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                {
  check_semi((yyvsp[0].check), (yyvsp[-1].exp)->pos);
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-3].pos), A_Type((yyvsp[-3].pos), A_idType, String((yyvsp[-2].exp)->u.v)), String((yyvsp[-1].exp)->u.v), NULL);
}
#line 1704 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 10:
#line 121 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                      {
  check_semi((yyvsp[0].check), (yyvsp[-1].exp)->pos);
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-2].pos), A_Type((yyvsp[-2].pos), A_intType, NULL), String((yyvsp[-1].exp)->u.v), NULL);
}
#line 1714 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 11:
#line 125 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                {
  check_semi((yyvsp[0].check), (yyvsp[-1].exp)->pos);
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-4].pos), A_Type((yyvsp[-4].pos), A_intType, NULL), String((yyvsp[-3].exp)->u.v), A_ExpList((yyvsp[-1].exp), NULL));
}
#line 1724 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 12:
#line 129 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                              {
  check_semi((yyvsp[0].check), (yyvsp[-1].exp)->pos);
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-4].pos), A_Type((yyvsp[-4].pos), A_intArrType, NULL), String((yyvsp[-1].exp)->u.v), NULL);
}
#line 1734 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 13:
#line 133 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                                    {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-8].pos), A_Type((yyvsp[-8].pos), A_intArrType, NULL), String((yyvsp[-5].exp)->u.v), (yyvsp[-2].expList));
}
#line 1744 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 14:
#line 137 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                {
  check_semi((yyvsp[0].check), (yyvsp[-1].exp)->pos);
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-4].pos), A_Type((yyvsp[-4].pos), A_floatArrType, NULL), String((yyvsp[-1].exp)->u.v), NULL);
}
#line 1754 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 15:
#line 141 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                                      {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-8].pos), A_Type((yyvsp[-8].pos), A_floatArrType, NULL), String((yyvsp[-5].exp)->u.v), (yyvsp[-2].expList));
}
#line 1764 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 16:
#line 145 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  check_semi((yyvsp[0].check), (yyvsp[-1].exp)->pos);
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-2].pos), A_Type((yyvsp[-2].pos), A_floatType, NULL), String((yyvsp[-1].exp)->u.v), NULL);
}
#line 1774 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 17:
#line 149 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                  {
  check_semi((yyvsp[0].check), (yyvsp[-1].exp)->pos);
  yyerrok;
  (yyval.varDecl) = A_VarDecl((yyvsp[-4].pos), A_Type((yyvsp[-4].pos), A_floatType, NULL), String((yyvsp[-3].exp)->u.v), A_ExpList((yyvsp[-1].exp), NULL));
}
#line 1784 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 18:
#line 155 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
            {
  (yyval.exp) = (yyvsp[0].exp);
}
#line 1792 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 19:
#line 157 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                           {
  (yyvsp[0].exp)->u.num = -(yyvsp[0].exp)->u.num;
  (yyvsp[0].exp)->pos->pos = (yyvsp[-1].pos)->pos;
  (yyvsp[0].exp)->pos->line = (yyvsp[-1].pos)->line;
  (yyval.exp) = (yyvsp[0].exp);
}
#line 1803 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 20:
#line 164 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  (yyval.expList) = NULL;
}
#line 1811 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 21:
#line 166 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                    {
  (yyval.expList) = A_ExpList((yyvsp[-1].exp), (yyvsp[0].expList));
}
#line 1819 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 22:
#line 170 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  (yyval.expList) = NULL;
}
#line 1827 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 23:
#line 172 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  (yyval.expList) = A_ExpList((yyvsp[-1].exp), (yyvsp[0].expList));
}
#line 1835 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 24:
#line 176 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                      {
  (yyval.stmList) = NULL;
}
#line 1843 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 25:
#line 178 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyval.stmList) = A_StmList((yyvsp[-1].stm), (yyvsp[0].stmList));
}
#line 1851 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 26:
#line 182 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                      {
  (yyval.stm) = A_NestedStm(A_Pos((yyvsp[-2].pos)->line, (yyvsp[-2].pos)->pos), (yyvsp[-1].stmList));
}
#line 1859 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 27:
#line 184 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                {
  (yyval.stm) = A_IfStm(A_Pos((yyvsp[-6].pos)->line, (yyvsp[-6].pos)->pos), (yyvsp[-4].exp), (yyvsp[-2].stm), (yyvsp[0].stm));
}
#line 1867 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 28:
#line 186 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                             {
  (yyval.stm) = A_IfStm(A_Pos((yyvsp[-4].pos)->line, (yyvsp[-4].pos)->pos), (yyvsp[-2].exp), (yyvsp[0].stm), NULL);
}
#line 1875 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 29:
#line 188 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                          {
  (yyval.stm) = A_WhileStm(A_Pos((yyvsp[-4].pos)->line, (yyvsp[-4].pos)->pos), (yyvsp[-2].exp), (yyvsp[0].stm));
}
#line 1883 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 30:
#line 190 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                 {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.stm) = A_WhileStm(A_Pos((yyvsp[-4].pos)->line, (yyvsp[-4].pos)->pos), (yyvsp[-2].exp), NULL);
}
#line 1893 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 31:
#line 194 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                           {
  check_semi((yyvsp[0].check), (yyvsp[-1].exp)->pos);
  yyerrok;
  (yyval.stm) = A_AssignStm(A_Pos((yyvsp[-3].exp)->pos->line, (yyvsp[-3].exp)->pos->pos), (yyvsp[-3].exp), (yyvsp[-1].exp));
}
#line 1903 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 32:
#line 198 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                              {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.stm) = A_ArrayInit(A_Pos((yyvsp[-7].exp)->pos->line, (yyvsp[-7].exp)->pos->pos), (yyvsp[-7].exp), (yyvsp[-2].expList));
}
#line 1913 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 33:
#line 202 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                          {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.stm) = A_CallStm(A_Pos((yyvsp[-6].exp)->pos->line, (yyvsp[-6].exp)->pos->pos), (yyvsp[-6].exp), String((yyvsp[-4].exp)->u.v), (yyvsp[-2].expList));
}
#line 1923 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 34:
#line 206 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.stm) = A_Continue(A_Pos((yyvsp[-1].pos)->line, (yyvsp[-1].pos)->pos));
}
#line 1933 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 35:
#line 210 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                     {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.stm) = A_Break(A_Pos((yyvsp[-1].pos)->line, (yyvsp[-1].pos)->pos));
}
#line 1943 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 36:
#line 214 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                          {
  check_semi((yyvsp[0].check), (yyvsp[-2].pos));
  yyerrok;
  (yyval.stm) = A_Return(A_Pos((yyvsp[-2].pos)->line, (yyvsp[-2].pos)->pos), (yyvsp[-1].exp));
}
#line 1953 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 37:
#line 218 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                  {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.stm) = A_Putnum((yyvsp[-4].pos), (yyvsp[-2].exp));
}
#line 1963 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 38:
#line 222 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                 {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.stm) = A_Putch((yyvsp[-4].pos), (yyvsp[-2].exp));
}
#line 1973 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 39:
#line 226 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                            {
  check_semi((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.stm) = A_Putarray((yyvsp[-6].pos), (yyvsp[-4].exp), (yyvsp[-2].exp));
}
#line 1983 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 40:
#line 230 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                      {
  check_parentheses((yyvsp[-1].check), (yyvsp[-2].pos));
  check_semi((yyvsp[0].check), (yyvsp[-2].pos));
  yyerrok;
  (yyval.stm) = A_Starttime((yyvsp[-2].pos));
}
#line 1994 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 41:
#line 235 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                     {
  check_parentheses((yyvsp[-1].check), (yyvsp[-2].pos));
  check_semi((yyvsp[0].check), (yyvsp[-2].pos));
  yyerrok;
  (yyval.stm) = A_Stoptime((yyvsp[-2].pos));
}
#line 2005 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 42:
#line 242 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                       {
  (yyval.check) = 0;
}
#line 2013 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 43:
#line 244 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
              {
  (yyval.check) = 1;
  add_char(';');
}
#line 2022 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 44:
#line 247 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
              {
  (yyval.check) = 1;
  add_char('{');
}
#line 2031 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 45:
#line 252 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
          {
  (yyval.exp) = (yyvsp[0].exp);
}
#line 2039 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 46:
#line 254 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
             {
  (yyval.exp) = (yyvsp[0].exp);
}
#line 2047 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 47:
#line 256 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
              {
  (yyval.exp) = (yyvsp[0].exp);
}
#line 2055 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 48:
#line 258 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                       {
  (yyval.exp) = A_LengthExp((yyvsp[-3].pos), (yyvsp[-1].exp));
}
#line 2063 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 49:
#line 260 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  check_parentheses((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.exp) = A_Getnum((yyvsp[-1].pos));
}
#line 2073 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 50:
#line 264 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                       {
  check_parentheses((yyvsp[0].check), (yyvsp[-1].pos));
  yyerrok;
  (yyval.exp) = A_Getch((yyvsp[-1].pos));
}
#line 2083 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 51:
#line 268 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                         {
  (yyval.exp) = A_Getarray((yyvsp[-3].pos), (yyvsp[-1].exp));
}
#line 2091 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 52:
#line 270 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
       {
  (yyval.exp) = (yyvsp[0].exp);
}
#line 2099 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 53:
#line 272 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
         {
  (yyval.exp) = A_ThisExp((yyvsp[0].pos));
}
#line 2107 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 54:
#line 274 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  (yyval.exp) = A_NewIntArrExp((yyvsp[-4].pos), (yyvsp[-1].exp));
}
#line 2115 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 55:
#line 276 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                          {
  (yyval.exp) = A_NewFloatArrExp((yyvsp[-4].pos), (yyvsp[-1].exp));
}
#line 2123 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 56:
#line 278 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                        {
  check_parentheses((yyvsp[0].check), (yyvsp[-2].pos));
  yyerrok;
  (yyval.exp) = A_NewObjExp((yyvsp[-2].pos), String((yyvsp[-1].exp)->u.v));
}
#line 2133 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 57:
#line 282 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_plus, (yyvsp[0].exp));
}
#line 2141 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 58:
#line 284 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                  {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_minus, (yyvsp[0].exp));
}
#line 2149 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 59:
#line 286 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                  {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_times, (yyvsp[0].exp));
}
#line 2157 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 60:
#line 288 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_div, (yyvsp[0].exp));
}
#line 2165 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 61:
#line 290 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
               {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_or, (yyvsp[0].exp));
}
#line 2173 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 62:
#line 292 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_and, (yyvsp[0].exp));
}
#line 2181 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 63:
#line 294 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                 {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_less, (yyvsp[0].exp));
}
#line 2189 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 64:
#line 296 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
               {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_le, (yyvsp[0].exp));
}
#line 2197 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 65:
#line 298 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                    {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_greater, (yyvsp[0].exp));
}
#line 2205 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 66:
#line 300 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
               {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_ge, (yyvsp[0].exp));
}
#line 2213 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 67:
#line 302 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
               {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_eq, (yyvsp[0].exp));
}
#line 2221 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 68:
#line 304 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyval.exp) = A_OpExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), A_ne, (yyvsp[0].exp));
}
#line 2229 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 69:
#line 306 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
            {
  (yyval.exp) = A_NotExp((yyvsp[-1].pos), (yyvsp[0].exp));
}
#line 2237 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 70:
#line 308 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                           {
  (yyval.exp) = A_MinusExp((yyvsp[-1].pos), (yyvsp[0].exp));
}
#line 2245 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 71:
#line 310 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyvsp[-1].exp)->pos = (yyvsp[-2].pos);
  (yyval.exp) = (yyvsp[-1].exp);
}
#line 2254 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 72:
#line 313 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                {
  (yyval.exp) = A_EscExp((yyvsp[-5].pos), (yyvsp[-3].stmList), (yyvsp[-1].exp));
}
#line 2262 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 73:
#line 315 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
               {
  (yyval.exp) = A_ClassVarExp(A_Pos((yyvsp[-2].exp)->pos->line, (yyvsp[-2].exp)->pos->pos), (yyvsp[-2].exp), String((yyvsp[0].exp)->u.v));
}
#line 2270 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 74:
#line 317 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                               {
  (yyval.exp) = A_CallExp(A_Pos((yyvsp[-5].exp)->pos->line, (yyvsp[-5].exp)->pos->pos), (yyvsp[-5].exp), String((yyvsp[-3].exp)->u.v), (yyvsp[-1].expList));
}
#line 2278 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 75:
#line 319 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                    {
  (yyval.exp) = A_ArrayExp(A_Pos((yyvsp[-3].exp)->pos->line, (yyvsp[-3].exp)->pos->pos), (yyvsp[-3].exp), (yyvsp[-1].exp));
}
#line 2286 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 76:
#line 323 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                      {
  (yyval.expList) = NULL;
}
#line 2294 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 77:
#line 325 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyval.expList) = A_ExpList((yyvsp[-1].exp), (yyvsp[0].expList));
}
#line 2302 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 78:
#line 329 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                      {
  (yyval.expList) = NULL;
}
#line 2310 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 79:
#line 331 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                    {
  (yyval.expList) = A_ExpList((yyvsp[-1].exp), (yyvsp[0].expList));
}
#line 2318 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 80:
#line 335 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                            {
  (yyval.classDeclList) = NULL;
}
#line 2326 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 81:
#line 337 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                            {
  (yyval.classDeclList) = A_ClassDeclList((yyvsp[-1].classDecl), (yyvsp[0].classDeclList));
}
#line 2334 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 82:
#line 341 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                                               {
  (yyval.classDecl) = A_ClassDecl((yyvsp[-6].pos), String((yyvsp[-4].exp)->u.v), NULL, (yyvsp[-2].varDeclList), (yyvsp[-1].methodDeclList));
}
#line 2342 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 83:
#line 343 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                                                  {
  (yyval.classDecl) = A_ClassDecl((yyvsp[-8].pos), String((yyvsp[-6].exp)->u.v), String((yyvsp[-4].exp)->u.v), (yyvsp[-2].varDeclList), (yyvsp[-1].methodDeclList));
}
#line 2350 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 84:
#line 347 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                             {
  (yyval.methodDeclList) = NULL;
}
#line 2358 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 85:
#line 349 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                              {
  (yyval.methodDeclList) = A_MethodDeclList((yyvsp[-1].methodDecl), (yyvsp[0].methodDeclList));
}
#line 2366 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 86:
#line 353 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                                                                           {
  (yyval.methodDecl) = A_MethodDecl((yyvsp[-9].pos), (yyvsp[-8].type), String((yyvsp[-7].exp)->u.v), (yyvsp[-5].formalList), (yyvsp[-2].varDeclList), (yyvsp[-1].stmList));
}
#line 2374 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 87:
#line 357 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyval.type) = A_Type((yyvsp[-1].pos), A_idType, String((yyvsp[0].exp)->u.v));
}
#line 2382 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 88:
#line 359 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
        {
  (yyval.type) = A_Type((yyvsp[0].pos), A_intType, NULL);
}
#line 2390 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 89:
#line 361 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
          {
  (yyval.type) = A_Type((yyvsp[0].pos), A_floatType, NULL);
}
#line 2398 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 90:
#line 363 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                {
  (yyval.type) = A_Type((yyvsp[-2].pos), A_intArrType, NULL);
}
#line 2406 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 91:
#line 365 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                  {
  (yyval.type) = A_Type((yyvsp[-2].pos), A_floatArrType, NULL);
}
#line 2414 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 92:
#line 370 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                         {
  (yyval.formalList) = NULL;
}
#line 2422 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 93:
#line 372 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                       {
  (yyval.formalList) = A_FormalList(A_Formal(A_Pos((yyvsp[-2].type)->pos->line, (yyvsp[-2].type)->pos->pos), (yyvsp[-2].type), String((yyvsp[-1].exp)->u.v)), (yyvsp[0].formalList));
}
#line 2430 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 94:
#line 374 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
              {
  add_char(')');
  fprintf(stderr, "Near line_%d: formal varible without type specified\n", (yyvsp[0].pos)->line);
  yyerrok;
  (yyval.formalList) = NULL;
}
#line 2441 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 95:
#line 381 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                         {
  (yyval.formalList) = NULL;
}
#line 2449 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 96:
#line 383 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                           {
  (yyval.formalList) = A_FormalList(A_Formal(A_Pos((yyvsp[-2].type)->pos->line, (yyvsp[-2].type)->pos->pos), (yyvsp[-2].type), String((yyvsp[-1].exp)->u.v)), (yyvsp[0].formalList));
}
#line 2457 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;

  case 97:
#line 385 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
                  {
  add_char(')');
  fprintf(stderr, "Near line_%d: formal varible without type specified\n", (yyvsp[-2].pos)->line);
  yyerrok;
  (yyval.formalList) = NULL;
}
#line 2468 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"
    break;


#line 2472 "/home/monika/compiler/fdmj_compiler/build/include/frontend/parser.c"

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (yymsgp);
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
                  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 392 "/home/monika/compiler/fdmj_compiler/src/lib/frontend/parser.yacc"
 /* 3. programs */
void yyerror(char *s) {
  fprintf(stderr, "%s\n",s);
}

void check_semi(char check, A_pos pos){
  if(check){
    fprintf(stderr, "Line_%d: \';\' expected\n", pos->line);
  }
}

void check_parentheses(char check, A_pos pos){
  if(check){
    fprintf(stderr, "Line_%d: missing or unpaired parentheses\n", pos->line);
  }
}


int yywrap() {
  return(1);
}
