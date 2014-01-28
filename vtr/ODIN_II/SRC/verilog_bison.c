
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "SRC/verilog_bison.y"

/*
Copyright (c) 2009 Peter Andrew Jamieson (jamieson.peter@gmail.com)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "parse_making_ast.h"
 
#define PARSE {printf("here\n");}

#ifndef YYLINENO
int yylineno;
#define YYLINENO yylineno
#else
extern int yylineno;
#endif

void yyerror(const char *str);
int yywrap();
int yyparse();
int yylex(void);

 // RESPONCE in an error
void yyerror(const char *str)
{
	fprintf(stderr,"error in parsing: %s - on line number %d\n",str, yylineno);
	exit(-1);
}
 
// point of continued file reading
int yywrap()
{
	return 1;
}



/* Line 189 of yacc.c  */
#line 134 "SRC/verilog_bison.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     vSYMBOL_ID = 258,
     vNUMBER_ID = 259,
     vDELAY_ID = 260,
     vALWAYS = 261,
     vAND = 262,
     vASSIGN = 263,
     vBEGIN = 264,
     vCASE = 265,
     vDEFAULT = 266,
     vDEFINE = 267,
     vELSE = 268,
     vEND = 269,
     vENDCASE = 270,
     vENDMODULE = 271,
     vIF = 272,
     vINOUT = 273,
     vINPUT = 274,
     vMODULE = 275,
     vNAND = 276,
     vNEGEDGE = 277,
     vNOR = 278,
     vNOT = 279,
     vOR = 280,
     vOUTPUT = 281,
     vPARAMETER = 282,
     vPOSEDGE = 283,
     vREG = 284,
     vWIRE = 285,
     vXNOR = 286,
     vXOR = 287,
     vDEFPARAM = 288,
     voANDAND = 289,
     voOROR = 290,
     voLTE = 291,
     voGTE = 292,
     voSLEFT = 293,
     voSRIGHT = 294,
     voEQUAL = 295,
     voNOTEQUAL = 296,
     voCASEEQUAL = 297,
     voCASENOTEQUAL = 298,
     voXNOR = 299,
     voNAND = 300,
     voNOR = 301,
     vNOT_SUPPORT = 302,
     UOR = 303,
     UAND = 304,
     UNOT = 305,
     UNAND = 306,
     UNOR = 307,
     UXNOR = 308,
     UXOR = 309,
     ULNOT = 310,
     UADD = 311,
     UMINUS = 312,
     LOWER_THAN_ELSE = 313
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 61 "SRC/verilog_bison.y"

	char *id_name;
	char *num_value;
	ast_node_t *node;



/* Line 214 of yacc.c  */
#line 236 "SRC/verilog_bison.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 248 "SRC/verilog_bison.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1333

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNRULES -- Number of states.  */
#define YYNSTATES  311

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,     2,    82,     2,    59,    52,     2,
      60,    61,    57,    55,    80,    56,    83,    58,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    49,    79,
      53,    81,    54,    48,    84,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,    50,    63,    66,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    19,    28,
      38,    46,    49,    51,    53,    55,    57,    59,    61,    63,
      65,    67,    69,    73,    77,    81,    85,    89,    93,    97,
      99,   101,   108,   120,   129,   133,   137,   141,   145,   149,
     153,   157,   161,   165,   174,   182,   189,   195,   198,   204,
     214,   219,   228,   232,   234,   240,   242,   246,   248,   254,
     256,   260,   262,   265,   268,   274,   282,   289,   291,   295,
     300,   304,   309,   312,   314,   318,   322,   326,   329,   331,
     336,   341,   345,   347,   349,   352,   355,   357,   360,   363,
     366,   369,   372,   375,   378,   381,   384,   387,   391,   395,
     399,   403,   407,   411,   415,   419,   423,   427,   431,   435,
     439,   443,   447,   451,   455,   459,   463,   467,   471,   475,
     479,   485,   489,   496,   503,   505,   507,   512,   519,   523,
     527
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      86,     0,    -1,    87,    -1,    87,    89,    -1,    87,    88,
      -1,    89,    -1,    88,    -1,    12,     3,     4,    -1,    20,
       3,    60,    97,    61,    79,    90,    16,    -1,    20,     3,
      60,    97,    80,    61,    79,    90,    16,    -1,    20,     3,
      60,    61,    79,    90,    16,    -1,    90,    91,    -1,    91,
      -1,    92,    -1,    93,    -1,    94,    -1,    95,    -1,    96,
      -1,    99,    -1,   100,    -1,   102,    -1,   108,    -1,    27,
      97,    79,    -1,    19,    97,    79,    -1,    26,    97,    79,
      -1,    18,    97,    79,    -1,    30,    97,    79,    -1,    29,
      97,    79,    -1,    97,    80,    98,    -1,    98,    -1,     3,
      -1,    64,   119,    49,   119,    65,     3,    -1,    64,   119,
      49,   119,    65,     3,    64,   119,    49,   119,    65,    -1,
      64,   119,    49,   119,    65,     3,    81,   120,    -1,     3,
      81,   120,    -1,     8,   110,    79,    -1,     7,   101,    79,
      -1,    21,   101,    79,    -1,    23,   101,    79,    -1,    24,
     101,    79,    -1,    25,   101,    79,    -1,    31,   101,    79,
      -1,    32,   101,    79,    -1,     3,    60,   119,    80,   119,
      80,   119,    61,    -1,    60,   119,    80,   119,    80,   119,
      61,    -1,     3,    60,   119,    80,   119,    61,    -1,    60,
     119,    80,   119,    61,    -1,     3,   103,    -1,     3,    60,
     104,    61,    79,    -1,    82,    60,   106,    61,     3,    60,
     104,    61,    79,    -1,     3,    60,    61,    79,    -1,    82,
      60,   106,    61,     3,    60,    61,    79,    -1,   104,    80,
     105,    -1,   105,    -1,    83,     3,    60,   119,    61,    -1,
     119,    -1,   106,    80,   107,    -1,   107,    -1,    83,     3,
      60,   119,    61,    -1,   119,    -1,     6,   116,   109,    -1,
     114,    -1,   110,    79,    -1,   111,    79,    -1,    17,    60,
     119,    61,   109,    -1,    17,    60,   119,    61,   109,    13,
     109,    -1,    10,    60,   119,    61,   112,    15,    -1,    79,
      -1,   120,    81,   119,    -1,   120,    81,     5,   119,    -1,
     120,    36,   119,    -1,   120,    36,     5,   119,    -1,   112,
     113,    -1,   113,    -1,   119,    49,   109,    -1,    11,    49,
     109,    -1,     9,   115,    14,    -1,   115,   109,    -1,   109,
      -1,    84,    60,   117,    61,    -1,    84,    60,    57,    61,
      -1,   117,    25,   118,    -1,   118,    -1,   120,    -1,    28,
       3,    -1,    22,     3,    -1,   120,    -1,    55,   119,    -1,
      56,   119,    -1,    66,   119,    -1,    52,   119,    -1,    50,
     119,    -1,    45,   119,    -1,    46,   119,    -1,    44,   119,
      -1,    67,   119,    -1,    51,   119,    -1,   119,    51,   119,
      -1,   119,    57,   119,    -1,   119,    58,   119,    -1,   119,
      59,   119,    -1,   119,    55,   119,    -1,   119,    56,   119,
      -1,   119,    52,   119,    -1,   119,    50,   119,    -1,   119,
      45,   119,    -1,   119,    46,   119,    -1,   119,    44,   119,
      -1,   119,    53,   119,    -1,   119,    54,   119,    -1,   119,
      39,   119,    -1,   119,    38,   119,    -1,   119,    40,   119,
      -1,   119,    41,   119,    -1,   119,    36,   119,    -1,   119,
      37,   119,    -1,   119,    42,   119,    -1,   119,    43,   119,
      -1,   119,    35,   119,    -1,   119,    34,   119,    -1,   119,
      48,   119,    49,   119,    -1,    60,   119,    61,    -1,    62,
     119,    62,   119,    63,    63,    -1,    62,   119,    62,   121,
      63,    63,    -1,     4,    -1,     3,    -1,     3,    64,   119,
      65,    -1,     3,    64,   119,    49,   119,    65,    -1,    62,
     121,    63,    -1,   121,    80,   119,    -1,   119,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   121,   131,   132,   133,   136,   139,   140,
     141,   144,   145,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   160,   163,   166,   169,   172,   173,   176,   177,
     180,   181,   182,   183,   184,   187,   191,   192,   193,   194,
     195,   196,   197,   200,   201,   202,   203,   207,   210,   211,
     212,   213,   216,   217,   220,   221,   224,   225,   228,   229,
     233,   236,   237,   238,   239,   240,   241,   242,   245,   246,
     249,   250,   253,   254,   257,   258,   261,   264,   265,   268,
     269,   273,   274,   277,   278,   279,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   321,   322,   325,   326,   327,   328,   329,   332,
     333
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "vSYMBOL_ID", "vNUMBER_ID", "vDELAY_ID",
  "vALWAYS", "vAND", "vASSIGN", "vBEGIN", "vCASE", "vDEFAULT", "vDEFINE",
  "vELSE", "vEND", "vENDCASE", "vENDMODULE", "vIF", "vINOUT", "vINPUT",
  "vMODULE", "vNAND", "vNEGEDGE", "vNOR", "vNOT", "vOR", "vOUTPUT",
  "vPARAMETER", "vPOSEDGE", "vREG", "vWIRE", "vXNOR", "vXOR", "vDEFPARAM",
  "voANDAND", "voOROR", "voLTE", "voGTE", "voSLEFT", "voSRIGHT", "voEQUAL",
  "voNOTEQUAL", "voCASEEQUAL", "voCASENOTEQUAL", "voXNOR", "voNAND",
  "voNOR", "vNOT_SUPPORT", "'?'", "':'", "'|'", "'^'", "'&'", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "')'", "'{'", "'}'", "'['",
  "']'", "'~'", "'!'", "UOR", "UAND", "UNOT", "UNAND", "UNOR", "UXNOR",
  "UXOR", "ULNOT", "UADD", "UMINUS", "LOWER_THAN_ELSE", "';'", "','",
  "'='", "'#'", "'.'", "'@'", "$accept", "source_text", "items", "define",
  "module", "list_of_module_items", "module_item", "parameter_declaration",
  "input_declaration", "output_declaration", "inout_declaration",
  "net_declaration", "variable_list", "variable", "continuous_assign",
  "gate_declaration", "gate_instance", "module_instantiation",
  "module_instance", "list_of_module_connections", "module_connection",
  "list_of_module_parameters", "module_parameter", "always", "statement",
  "blocking_assignment", "non_blocking_assignment", "case_item_list",
  "case_items", "seq_block", "stmt_list", "delay_control",
  "event_expression_list", "event_expression", "expression", "primary",
  "expression_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,    63,    58,
     124,    94,    38,    60,    62,    43,    45,    42,    47,    37,
      40,    41,   123,   125,    91,    93,   126,    33,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,    59,
      44,    61,    35,    46,    64
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    87,    87,    88,    89,    89,
      89,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    93,    94,    95,    96,    96,    97,    97,
      98,    98,    98,    98,    98,    99,   100,   100,   100,   100,
     100,   100,   100,   101,   101,   101,   101,   102,   103,   103,
     103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   109,   109,   109,   109,   109,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   120,   120,   120,   120,   121,
     121
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     3,     8,     9,
       7,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     6,    11,     8,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     8,     7,     6,     5,     2,     5,     9,
       4,     8,     3,     1,     5,     1,     3,     1,     5,     1,
       3,     1,     2,     2,     5,     7,     6,     1,     3,     4,
       3,     4,     2,     1,     3,     3,     3,     2,     1,     4,
       4,     3,     1,     1,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     3,     6,     6,     1,     1,     4,     6,     3,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     6,     5,     0,     0,     1,
       4,     3,     7,     0,    30,     0,     0,     0,    29,     0,
       0,   125,   124,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    86,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    94,
      92,    93,    91,    96,    90,    87,    88,     0,   130,     0,
      89,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
     130,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    10,    11,     0,   121,     0,   128,     0,
     119,   118,   114,   115,   111,   110,   112,   113,   116,   117,
     107,   105,   106,     0,     0,   104,    97,   103,   108,   109,
     101,   102,    98,    99,   100,     0,     0,     0,     0,     0,
       0,     0,     0,    67,    60,     0,     0,    61,     0,     0,
       0,    36,    35,     0,    25,     0,    23,    37,    38,    39,
      40,    24,    22,    27,    26,    41,    42,     0,   126,   130,
       0,   129,     0,     0,     8,     0,     0,     0,     0,    53,
      55,     0,     0,    57,    59,     0,     0,     0,     0,    82,
      83,    78,     0,     0,     0,    62,    63,     0,     0,     0,
       0,    68,     0,     0,     0,   120,    31,     9,    50,     0,
       0,     0,     0,     0,     0,    85,    84,    80,     0,    79,
      76,    77,     0,     0,     0,    70,     0,     0,    69,   127,
     122,   123,     0,     0,     0,    48,    52,     0,     0,    56,
      81,     0,     0,    71,     0,    46,     0,     0,    33,     0,
       0,     0,     0,     0,    73,     0,    64,    45,     0,     0,
       0,    54,    58,     0,     0,     0,    66,    72,     0,     0,
       0,    44,     0,    51,     0,    75,    74,    65,    43,    32,
      49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    57,    58,    59,    60,    61,
      62,    63,    17,    18,    64,    65,   118,    66,   113,   208,
     209,   212,   213,    67,   174,   175,   176,   283,   284,   177,
     222,   115,   218,   219,   210,    36,    79
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -167
static const yytype_int16 yypact[] =
{
      46,    24,    28,    37,    46,  -167,  -167,    53,    38,  -167,
    -167,  -167,  -167,    -1,    26,    21,   380,   -52,  -167,    50,
     816,    49,  -167,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,  1040,  -167,    31,     3,   380,
    -167,    19,    39,     5,    50,     4,     4,     5,     5,     5,
       5,     4,     4,     4,     4,     5,     5,   726,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,   380,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,  -167,   844,   815,    42,
    -167,  -167,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   816,    68,  -167,
    1144,    88,    93,  -167,    94,    35,   100,   380,    80,    86,
      47,   -46,   -18,    90,    96,    98,   104,    40,    51,    55,
      64,   106,   111,  -167,  -167,   540,  -167,   380,  -167,   380,
    1194,  1170,   180,   180,    82,    82,  1274,  1274,  1274,  1274,
    1242,  1266,  1242,  1066,   572,  1218,  1242,  1266,   180,   180,
     123,   123,  -167,  -167,  -167,   756,   816,   112,   142,   114,
      35,   131,   136,  -167,  -167,   120,   121,  -167,    14,   380,
     476,  -167,  -167,   286,  -167,     4,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,  -167,   380,  -167,   668,
      45,  1144,   380,   198,  -167,   786,   126,   203,   -37,  -167,
    1144,   204,   -32,  -167,  1144,   209,   210,   154,    -2,  -167,
    -167,  -167,    32,   380,   380,  -167,  -167,   330,   507,   380,
     380,  1144,   604,   157,   158,  1144,   -34,  -167,  -167,   162,
     144,   261,   164,   223,   142,  -167,  -167,  -167,    99,  -167,
    -167,  -167,   872,   900,   380,  1144,   380,   414,  1144,  -167,
    -167,  -167,   380,    50,   380,  -167,  -167,   380,   167,  -167,
    -167,   361,    35,  1144,   445,  -167,   380,  1092,  -167,   928,
     956,   242,   179,   311,  -167,  1118,   217,  -167,   380,   984,
     380,  -167,  -167,   153,   -29,    35,  -167,  -167,    35,    35,
    1012,  -167,   636,  -167,   155,  -167,  -167,  -167,  -167,  -167,
    -167
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -167,  -167,  -167,   229,   236,   -67,   -56,  -167,  -167,  -167,
    -167,  -167,   215,   -33,  -167,  -167,   353,  -167,  -167,   -39,
       6,  -167,     8,  -167,  -166,   206,  -167,  -167,   -35,  -167,
    -167,  -167,  -167,     7,   -13,   -19,   119
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      40,   134,    14,    35,   221,   109,    14,    14,   116,    37,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      80,    81,   111,   248,   240,   120,   110,     7,    38,   243,
     262,     8,   304,   184,   185,    21,    22,     9,    21,    22,
     165,   170,   171,   241,   170,   171,   250,   263,   244,   172,
     227,   241,   172,    21,    22,   135,   251,    12,     1,   249,
      15,   186,   185,    16,   108,   117,     2,    16,    16,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,    39,   183,   178,    39,    13,   205,
      20,   112,    21,    22,   180,   138,   286,    19,   234,   134,
     107,   173,    39,    68,   173,    21,    22,    21,    22,   191,
     185,   215,   139,   114,   199,   139,   201,   216,   183,   305,
     192,   185,   306,   307,   193,   185,   215,   102,   103,   104,
     105,   106,   216,   194,   185,    21,    22,   166,   167,   134,
     220,   178,   109,   168,   169,   214,    23,    24,    25,   181,
     179,    39,    26,    27,    28,   182,   228,    29,    30,   187,
     231,   217,    31,   206,    32,   188,    39,   189,    33,    34,
     104,   105,   106,   190,   232,   195,    23,    24,    25,   235,
     196,   223,    26,    27,    28,   207,   224,    29,    30,   225,
     226,   236,    31,   178,    32,   238,   239,   242,    33,    34,
     252,   253,   245,   246,   255,   247,   257,   258,    86,    87,
     260,   261,   264,   265,   267,   211,   268,   281,   295,   220,
     299,   214,   303,    10,   310,   102,   103,   104,   105,   106,
      11,   273,   294,   274,   278,    21,    22,   266,   297,   277,
     119,   279,   269,   178,   280,   270,   200,     0,   285,     0,
     121,   122,     0,   289,    21,    22,   127,   128,   129,   130,
     285,     0,     0,     0,     0,   300,   178,   302,     0,   178,
     178,     0,     0,     0,     0,     0,    23,    24,    25,    21,
      22,   230,    26,    27,    28,     0,     0,    29,    30,     0,
       0,     0,    31,   293,    32,    23,    24,    25,    33,    34,
       0,    26,    27,    28,    21,    22,    29,    30,     0,     0,
       0,    31,   282,    32,     0,   207,   296,    33,    34,     0,
      23,    24,    25,    21,    22,   254,    26,    27,    28,     0,
       0,    29,    30,     0,   207,     0,    31,     0,    32,     0,
       0,     0,    33,    34,     0,    23,    24,    25,     0,     0,
       0,    26,    27,    28,    21,    22,    29,    30,     0,     0,
       0,    31,   282,    32,    23,    24,    25,    33,    34,     0,
      26,    27,    28,    21,    22,    29,    30,     0,     0,     0,
      31,     0,    32,     0,     0,     0,    33,    34,     0,     0,
     123,   124,   125,   126,     0,    23,    24,    25,   131,   132,
       0,    26,    27,    28,     0,     0,    29,    30,     0,     0,
       0,    31,     0,    32,    23,    24,    25,    33,    34,     0,
      26,    27,    28,     0,     0,    29,    30,     0,     0,     0,
      31,     0,    32,     0,     0,     0,    33,    34,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,     0,    95,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,   275,     0,     0,     0,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,     0,    95,   276,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,     0,   287,     0,     0,     0,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,    95,   288,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,     0,     0,     0,
       0,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,     0,    95,   229,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,     0,     0,     0,
       0,     0,     0,     0,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,   256,    95,   197,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
       0,     0,     0,     0,     0,   198,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
      95,     0,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     0,     0,     0,     0,     0,   203,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,     0,    95,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,     0,     0,     0,     0,   259,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,    95,     0,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,     0,     0,     0,
       0,   309,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,    95,     0,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,     0,    41,
       0,   233,    42,    43,    44,     0,     0,     0,     0,     0,
       0,     0,   133,     0,    45,    46,     0,    47,     0,    48,
      49,    50,    51,    52,     0,    53,    54,    55,    56,    41,
       0,     0,    42,    43,    44,     0,     0,     0,     0,     0,
       0,     0,   204,     0,    45,    46,     0,    47,     0,    48,
      49,    50,    51,    52,     0,    53,    54,    55,    56,    41,
       0,     0,    42,    43,    44,     0,     0,     0,     0,     0,
       0,     0,   237,     0,    45,    46,     0,    47,     0,    48,
      49,    50,    51,    52,     0,    53,    54,    55,    56,    41,
       0,     0,    42,    43,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,    46,     0,    47,     0,    48,
      49,    50,    51,    52,     0,    53,    54,    55,    56,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,     0,    95,     0,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,     0,     0,   137,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,     0,    95,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,   136,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
      95,     0,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     0,   271,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,    95,     0,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
       0,   272,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,    95,     0,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,     0,   291,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,    95,     0,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,   292,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,     0,    95,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,   301,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
      95,     0,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     0,   308,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,    95,   202,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
      95,   290,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,    95,   298,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,     0,    95,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    82,     0,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,    84,    85,
      86,    87,    88,    89,    90,    91,     0,    93,     0,     0,
       0,     0,     0,     0,    99,   100,   101,   102,   103,   104,
     105,   106,    84,    85,    86,    87,    88,    89,    90,    91,
      84,    85,    86,    87,     0,     0,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   106,     0,   100,   101,   102,
     103,   104,   105,   106
};

static const yytype_int16 yycheck[] =
{
      19,    57,     3,    16,   170,    38,     3,     3,     3,    61,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     3,    25,    61,    44,    39,     3,    80,    61,
      64,     3,    61,    79,    80,     3,     4,     0,     3,     4,
     107,     9,    10,    80,     9,    10,    14,    81,    80,    17,
      36,    80,    17,     3,     4,    68,   222,     4,    12,    61,
      61,    79,    80,    64,    61,    60,    20,    64,    64,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    62,    81,   115,    62,    60,   166,
      79,    82,     3,     4,   117,    63,   272,    81,    63,   165,
      79,    79,    62,    64,    79,     3,     4,     3,     4,    79,
      80,    22,    80,    84,   137,    80,   139,    28,    81,   295,
      79,    80,   298,   299,    79,    80,    22,    55,    56,    57,
      58,    59,    28,    79,    80,     3,     4,    79,    60,   205,
     169,   170,   185,    60,    60,   168,    44,    45,    46,    79,
      60,    62,    50,    51,    52,    79,   179,    55,    56,    79,
     183,    57,    60,    61,    62,    79,    62,    79,    66,    67,
      57,    58,    59,    79,   197,    79,    44,    45,    46,   202,
      79,    60,    50,    51,    52,    83,    60,    55,    56,    79,
      79,     3,    60,   222,    62,    79,     3,     3,    66,    67,
     223,   224,     3,     3,   227,    61,   229,   230,    38,    39,
      63,    63,    60,    79,    60,    83,     3,    60,    49,   248,
      13,   244,    79,     4,    79,    55,    56,    57,    58,    59,
       4,   254,   281,   256,   263,     3,     4,   241,   283,   262,
      44,   264,   244,   272,   267,   248,   137,    -1,   271,    -1,
      45,    46,    -1,   276,     3,     4,    51,    52,    53,    54,
     283,    -1,    -1,    -1,    -1,   288,   295,   290,    -1,   298,
     299,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,     3,
       4,     5,    50,    51,    52,    -1,    -1,    55,    56,    -1,
      -1,    -1,    60,    61,    62,    44,    45,    46,    66,    67,
      -1,    50,    51,    52,     3,     4,    55,    56,    -1,    -1,
      -1,    60,    11,    62,    -1,    83,    15,    66,    67,    -1,
      44,    45,    46,     3,     4,     5,    50,    51,    52,    -1,
      -1,    55,    56,    -1,    83,    -1,    60,    -1,    62,    -1,
      -1,    -1,    66,    67,    -1,    44,    45,    46,    -1,    -1,
      -1,    50,    51,    52,     3,     4,    55,    56,    -1,    -1,
      -1,    60,    11,    62,    44,    45,    46,    66,    67,    -1,
      50,    51,    52,     3,     4,    55,    56,    -1,    -1,    -1,
      60,    -1,    62,    -1,    -1,    -1,    66,    67,    -1,    -1,
      47,    48,    49,    50,    -1,    44,    45,    46,    55,    56,
      -1,    50,    51,    52,    -1,    -1,    55,    56,    -1,    -1,
      -1,    60,    -1,    62,    44,    45,    46,    66,    67,    -1,
      50,    51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,
      60,    -1,    62,    -1,    -1,    -1,    66,    67,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    61,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    80,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    61,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    80,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    48,    80,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    80,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    65,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      48,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    65,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    65,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,     3,
      -1,    63,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    18,    19,    -1,    21,    -1,    23,
      24,    25,    26,    27,    -1,    29,    30,    31,    32,     3,
      -1,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    18,    19,    -1,    21,    -1,    23,
      24,    25,    26,    27,    -1,    29,    30,    31,    32,     3,
      -1,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    18,    19,    -1,    21,    -1,    23,
      24,    25,    26,    27,    -1,    29,    30,    31,    32,     3,
      -1,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    18,    19,    -1,    21,    -1,    23,
      24,    25,    26,    27,    -1,    29,    30,    31,    32,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    61,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      48,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    61,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    48,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    61,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    61,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    61,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    61,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      48,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    61,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    34,    -1,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    36,    37,    38,    39,    40,    41,    42,    43,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    -1,    53,    54,    55,
      56,    57,    58,    59
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    20,    86,    87,    88,    89,     3,     3,     0,
      88,    89,     4,    60,     3,    61,    64,    97,    98,    81,
      79,     3,     4,    44,    45,    46,    50,    51,    52,    55,
      56,    60,    62,    66,    67,   119,   120,    61,    80,    62,
     120,     3,     6,     7,     8,    18,    19,    21,    23,    24,
      25,    26,    27,    29,    30,    31,    32,    90,    91,    92,
      93,    94,    95,    96,    99,   100,   102,   108,    64,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   121,
     119,   119,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    79,    61,    98,
     119,     3,    82,   103,    84,   116,     3,    60,   101,   110,
     120,    97,    97,   101,   101,   101,   101,    97,    97,    97,
      97,   101,   101,    16,    91,   119,    61,    62,    63,    80,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,    90,    79,    60,    60,    60,
       9,    10,    17,    79,   109,   110,   111,   114,   120,    60,
     119,    79,    79,    81,    79,    80,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    49,    65,   119,
     121,   119,    49,    65,    16,    90,    61,    83,   104,   105,
     119,    83,   106,   107,   119,    22,    28,    57,   117,   118,
     120,   109,   115,    60,    60,    79,    79,    36,   119,    80,
       5,   119,   119,    63,    63,   119,     3,    16,    79,     3,
      61,    80,     3,    61,    80,     3,     3,    61,    25,    61,
      14,   109,   119,   119,     5,   119,    80,   119,   119,    65,
      63,    63,    64,    81,    60,    79,   105,    60,     3,   107,
     118,    61,    61,   119,   119,    61,    80,   119,   120,   119,
     119,    60,    11,   112,   113,   119,   109,    61,    80,   119,
      49,    61,    61,    61,   104,    49,    15,   113,    49,    13,
     119,    61,   119,    79,    61,   109,   109,   109,    61,    65,
      79
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 118 "SRC/verilog_bison.y"
    {next_parsed_verilog_file((yyvsp[(1) - (1)].node));;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 121 "SRC/verilog_bison.y"
    {
											if ((yyvsp[(1) - (2)].node) != NULL)
											{
												(yyval.node) = newList_entry((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
											}
											else
											{
												(yyval.node) = newList(FILE_ITEMS, (yyvsp[(2) - (2)].node));
											}
										;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 131 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (2)].node);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 132 "SRC/verilog_bison.y"
    {(yyval.node) = newList(FILE_ITEMS, (yyvsp[(1) - (1)].node));;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 133 "SRC/verilog_bison.y"
    {(yyval.node) = NULL;;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 136 "SRC/verilog_bison.y"
    {(yyval.node) = NULL; newConstant((yyvsp[(2) - (3)].id_name), (yyvsp[(3) - (3)].num_value), yylineno);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 139 "SRC/verilog_bison.y"
    {(yyval.node) = newModule((yyvsp[(2) - (8)].id_name), (yyvsp[(4) - (8)].node), (yyvsp[(7) - (8)].node), yylineno);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 140 "SRC/verilog_bison.y"
    {(yyval.node) = newModule((yyvsp[(2) - (9)].id_name), (yyvsp[(4) - (9)].node), (yyvsp[(8) - (9)].node), yylineno);;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 141 "SRC/verilog_bison.y"
    {(yyval.node) = newModule((yyvsp[(2) - (7)].id_name), NULL, (yyvsp[(6) - (7)].node), yylineno);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 144 "SRC/verilog_bison.y"
    {(yyval.node) = newList_entry((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 145 "SRC/verilog_bison.y"
    {(yyval.node) = newList(MODULE_ITEMS, (yyvsp[(1) - (1)].node));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 148 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 149 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 150 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 151 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 152 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 153 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 154 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 155 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 156 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 160 "SRC/verilog_bison.y"
    {(yyval.node) = markAndProcessSymbolListWith(PARAMETER, (yyvsp[(2) - (3)].node));;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 163 "SRC/verilog_bison.y"
    {(yyval.node) = markAndProcessSymbolListWith(INPUT, (yyvsp[(2) - (3)].node));;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 166 "SRC/verilog_bison.y"
    {(yyval.node) = markAndProcessSymbolListWith(OUTPUT, (yyvsp[(2) - (3)].node));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 169 "SRC/verilog_bison.y"
    {(yyval.node) = markAndProcessSymbolListWith(INOUT, (yyvsp[(2) - (3)].node));;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 172 "SRC/verilog_bison.y"
    {(yyval.node) = markAndProcessSymbolListWith(WIRE, (yyvsp[(2) - (3)].node));;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 173 "SRC/verilog_bison.y"
    {(yyval.node) = markAndProcessSymbolListWith(REG, (yyvsp[(2) - (3)].node));;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 176 "SRC/verilog_bison.y"
    {(yyval.node) = newList_entry((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 177 "SRC/verilog_bison.y"
    {(yyval.node) = newList(VAR_DECLARE_LIST, (yyvsp[(1) - (1)].node));;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 180 "SRC/verilog_bison.y"
    {(yyval.node) = newVarDeclare((yyvsp[(1) - (1)].id_name), NULL, NULL, NULL, NULL, NULL, yylineno);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 181 "SRC/verilog_bison.y"
    {(yyval.node) = newVarDeclare((yyvsp[(6) - (6)].id_name), (yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node), NULL, NULL, NULL, yylineno);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 182 "SRC/verilog_bison.y"
    {(yyval.node) = newVarDeclare((yyvsp[(6) - (11)].id_name), (yyvsp[(2) - (11)].node), (yyvsp[(4) - (11)].node), (yyvsp[(8) - (11)].node), (yyvsp[(10) - (11)].node), NULL, yylineno);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 183 "SRC/verilog_bison.y"
    {(yyval.node) = newVarDeclare((yyvsp[(6) - (8)].id_name), (yyvsp[(2) - (8)].node), (yyvsp[(4) - (8)].node), NULL, NULL, (yyvsp[(8) - (8)].node), yylineno);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 184 "SRC/verilog_bison.y"
    {(yyval.node) = newVarDeclare((yyvsp[(1) - (3)].id_name), NULL, NULL, NULL, NULL, (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 187 "SRC/verilog_bison.y"
    {(yyval.node) = newAssign((yyvsp[(2) - (3)].node), yylineno);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 191 "SRC/verilog_bison.y"
    {(yyval.node) = newGate(BITWISE_AND, (yyvsp[(2) - (3)].node), yylineno);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 192 "SRC/verilog_bison.y"
    {(yyval.node) = newGate(BITWISE_NAND, (yyvsp[(2) - (3)].node), yylineno);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 193 "SRC/verilog_bison.y"
    {(yyval.node) = newGate(BITWISE_NOR, (yyvsp[(2) - (3)].node), yylineno);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 194 "SRC/verilog_bison.y"
    {(yyval.node) = newGate(BITWISE_NOT, (yyvsp[(2) - (3)].node), yylineno);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 195 "SRC/verilog_bison.y"
    {(yyval.node) = newGate(BITWISE_OR, (yyvsp[(2) - (3)].node), yylineno);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 196 "SRC/verilog_bison.y"
    {(yyval.node) = newGate(BITWISE_XNOR, (yyvsp[(2) - (3)].node), yylineno);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 197 "SRC/verilog_bison.y"
    {(yyval.node) = newGate(BITWISE_XOR, (yyvsp[(2) - (3)].node), yylineno);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 200 "SRC/verilog_bison.y"
    {(yyval.node) = newGateInstance((yyvsp[(1) - (8)].id_name), (yyvsp[(3) - (8)].node), (yyvsp[(5) - (8)].node), (yyvsp[(7) - (8)].node), yylineno);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 201 "SRC/verilog_bison.y"
    {(yyval.node) = newGateInstance(NULL, (yyvsp[(2) - (7)].node), (yyvsp[(4) - (7)].node), (yyvsp[(6) - (7)].node), yylineno);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 202 "SRC/verilog_bison.y"
    {(yyval.node) = newGateInstance((yyvsp[(1) - (6)].id_name), (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node), NULL, yylineno);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 203 "SRC/verilog_bison.y"
    {(yyval.node) = newGateInstance(NULL, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), NULL, yylineno);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 207 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleInstance((yyvsp[(1) - (2)].id_name), (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 210 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleNamedInstance((yyvsp[(1) - (5)].id_name), (yyvsp[(3) - (5)].node), NULL, yylineno);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 211 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleNamedInstance((yyvsp[(5) - (9)].id_name), (yyvsp[(7) - (9)].node), (yyvsp[(3) - (9)].node), yylineno); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 212 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleNamedInstance((yyvsp[(1) - (4)].id_name), NULL, NULL, yylineno);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 213 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleNamedInstance((yyvsp[(5) - (8)].id_name), NULL, (yyvsp[(3) - (8)].node), yylineno);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 216 "SRC/verilog_bison.y"
    {(yyval.node) = newList_entry((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 217 "SRC/verilog_bison.y"
    {(yyval.node) = newList(MODULE_CONNECT_LIST, (yyvsp[(1) - (1)].node));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 220 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleConnection((yyvsp[(2) - (5)].id_name), (yyvsp[(4) - (5)].node), yylineno);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 221 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleConnection(NULL, (yyvsp[(1) - (1)].node), yylineno);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 224 "SRC/verilog_bison.y"
    {(yyval.node) = newList_entry((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 225 "SRC/verilog_bison.y"
    {(yyval.node) = newList(MODULE_PARAMETER_LIST, (yyvsp[(1) - (1)].node));;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 228 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleParameter((yyvsp[(2) - (5)].id_name), (yyvsp[(4) - (5)].node), yylineno);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 229 "SRC/verilog_bison.y"
    {(yyval.node) = newModuleParameter(NULL, (yyvsp[(1) - (1)].node), yylineno);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 233 "SRC/verilog_bison.y"
    {(yyval.node) = newAlways((yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 236 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 237 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (2)].node);;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 238 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (2)].node);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 239 "SRC/verilog_bison.y"
    {(yyval.node) = newIf((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL, yylineno);;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 240 "SRC/verilog_bison.y"
    {(yyval.node) = newIf((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), yylineno);;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 241 "SRC/verilog_bison.y"
    {(yyval.node) = newCase((yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node), yylineno);;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 242 "SRC/verilog_bison.y"
    {(yyval.node) = NULL;;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 245 "SRC/verilog_bison.y"
    {(yyval.node) = newBlocking((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 246 "SRC/verilog_bison.y"
    {(yyval.node) = newBlocking((yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node), yylineno);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 249 "SRC/verilog_bison.y"
    {(yyval.node) = newNonBlocking((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 250 "SRC/verilog_bison.y"
    {(yyval.node) = newNonBlocking((yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node), yylineno);;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 253 "SRC/verilog_bison.y"
    {(yyval.node) = newList_entry((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 254 "SRC/verilog_bison.y"
    {(yyval.node) = newList(CASE_LIST, (yyvsp[(1) - (1)].node));;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 257 "SRC/verilog_bison.y"
    {(yyval.node) = newCaseItem((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 258 "SRC/verilog_bison.y"
    {(yyval.node) = newDefaultCase((yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 261 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 264 "SRC/verilog_bison.y"
    {(yyval.node) = newList_entry((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 265 "SRC/verilog_bison.y"
    {(yyval.node) = newList(BLOCK, (yyvsp[(1) - (1)].node));;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 268 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(3) - (4)].node);;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 269 "SRC/verilog_bison.y"
    {(yyval.node) = NULL;;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 273 "SRC/verilog_bison.y"
    {(yyval.node) = newList_entry((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 274 "SRC/verilog_bison.y"
    {(yyval.node) = newList(DELAY_CONTROL, (yyvsp[(1) - (1)].node));;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 277 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 278 "SRC/verilog_bison.y"
    {(yyval.node) = newPosedgeSymbol((yyvsp[(2) - (2)].id_name), yylineno);;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 279 "SRC/verilog_bison.y"
    {(yyval.node) = newNegedgeSymbol((yyvsp[(2) - (2)].id_name), yylineno);;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 282 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 283 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(ADD, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 284 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(MINUS, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 285 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(BITWISE_NOT, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 286 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(BITWISE_AND, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 287 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(BITWISE_OR, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 288 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(BITWISE_NAND, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 289 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(BITWISE_NOR, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 290 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(BITWISE_XNOR, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 291 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(LOGICAL_NOT, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 292 "SRC/verilog_bison.y"
    {(yyval.node) = newUnaryOperation(BITWISE_XOR, (yyvsp[(2) - (2)].node), yylineno);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 293 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(BITWISE_XOR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 294 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(MULTIPLY, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 295 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(DIVIDE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 296 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(MODULO, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 297 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(ADD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 298 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(MINUS, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 299 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(BITWISE_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 300 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(BITWISE_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 301 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(BITWISE_NAND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 302 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(BITWISE_NOR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 303 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(BITWISE_XNOR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 304 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(LT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 305 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(GT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 306 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(SR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 307 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(SL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 308 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(LOGICAL_EQUAL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 309 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(NOT_EQUAL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 310 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(LTE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 311 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(GTE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 312 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(CASE_EQUAL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 313 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(CASE_NOT_EQUAL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 314 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(LOGICAL_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 315 "SRC/verilog_bison.y"
    {(yyval.node) = newBinaryOperation(LOGICAL_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yylineno);;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 316 "SRC/verilog_bison.y"
    {(yyval.node) = newIfQuestion((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), yylineno);;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 317 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 321 "SRC/verilog_bison.y"
    {(yyval.node) = newListReplicate( (yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node) ); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 322 "SRC/verilog_bison.y"
    {(yyval.node) = newListReplicate( (yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node) ); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 325 "SRC/verilog_bison.y"
    {(yyval.node) = newNumberNode((yyvsp[(1) - (1)].num_value), yylineno);;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 326 "SRC/verilog_bison.y"
    {(yyval.node) = newSymbolNode((yyvsp[(1) - (1)].id_name), yylineno);;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 327 "SRC/verilog_bison.y"
    {(yyval.node) = newArrayRef((yyvsp[(1) - (4)].id_name), (yyvsp[(3) - (4)].node), yylineno);;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 328 "SRC/verilog_bison.y"
    {(yyval.node) = newRangeRef((yyvsp[(1) - (6)].id_name), (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node), yylineno);;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 329 "SRC/verilog_bison.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node); ((yyvsp[(2) - (3)].node))->types.concat.num_bit_strings = -1;;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 332 "SRC/verilog_bison.y"
    {(yyval.node) = newList_entry((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); /* note this will be in order lsb = greatest to msb = 0 in the node child list */;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 333 "SRC/verilog_bison.y"
    {(yyval.node) = newList(CONCATENATE, (yyvsp[(1) - (1)].node));;}
    break;



/* Line 1455 of yacc.c  */
#line 2840 "SRC/verilog_bison.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 336 "SRC/verilog_bison.y"


