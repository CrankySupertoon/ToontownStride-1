/* A Bison parser, made by GNU Bison 3.5.2.  */

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
#define YYBISON_VERSION "3.5.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         cppyyparse
#define yylex           cppyylex
#define yyerror         cppyyerror
#define yydebug         cppyydebug
#define yynerrs         cppyynerrs

/* First part of user prologue.  */
#line 7 "dtool/src/cppparser/cppBison.yxx"


#include "cppBisonDefs.h"
#include "cppParser.h"
#include "cppClosureType.h"
#include "cppExpression.h"
#include "cppSimpleType.h"
#include "cppExtensionType.h"
#include "cppStructType.h"
#include "cppEnumType.h"
#include "cppFunctionType.h"
#include "cppTBDType.h"
#include "cppMakeProperty.h"
#include "cppMakeSeq.h"
#include "cppParameterList.h"
#include "cppInstance.h"
#include "cppClassTemplateParameter.h"
#include "cppTemplateParameterList.h"
#include "cppInstanceIdentifier.h"
#include "cppTypedefType.h"
#include "cppTypeDeclaration.h"
#include "cppVisibility.h"
#include "cppIdentifier.h"
#include "cppScope.h"
#include "cppTemplateScope.h"
#include "cppNamespace.h"
#include "cppUsing.h"

using std::stringstream;
using std::string;

////////////////////////////////////////////////////////////////////
// Defining the interface to the parser.
////////////////////////////////////////////////////////////////////

CPPScope *current_scope = nullptr;
CPPScope *global_scope = nullptr;
CPPPreprocessor *current_lexer = nullptr;

static CPPStructType *current_struct = nullptr;
static CPPEnumType *current_enum = nullptr;
static int current_storage_class = 0;
static CPPType *current_type = nullptr;
static CPPExpression *current_expr = nullptr;
static int publish_nest_level = 0;
static CPPVisibility publish_previous;
static YYLTYPE publish_loc;

static std::vector<CPPScope *> last_scopes;
static std::vector<int> last_storage_classes;
static std::vector<CPPStructType *> last_structs;

int yyparse();

#define YYERROR_VERBOSE

static void
yyerror(const string &msg) {
  current_lexer->error(msg, current_lexer->_last_token_loc);
}

static void
yyerror(YYLTYPE *loc, const string &msg) {
  current_lexer->error(msg, *loc);
}

static void
yyerror(const string &msg, YYLTYPE &loc) {
  current_lexer->error(msg, loc);
}

static void
yywarning(const string &msg, YYLTYPE &loc) {
  current_lexer->warning(msg, loc);
}

static int
yylex(YYSTYPE *lval, YYLTYPE *lloc) {
  CPPToken token = current_lexer->get_next_token();
  *lval = token._lval;
  *lloc = token._lloc;
  return token._token;
}

void
parse_cpp(CPPParser *cp) {
  CPPScope *old_scope = current_scope;
  CPPScope *old_global_scope = global_scope;
  CPPPreprocessor *old_lexer = current_lexer;

  current_scope = cp;
  global_scope = cp;
  current_lexer = cp;
  publish_nest_level = 0;
  yyparse();

  if (publish_nest_level != 0) {
    yyerror("Unclosed __begin_publish", publish_loc);
    publish_nest_level = 0;
  }

  current_scope = old_scope;
  global_scope = old_global_scope;
  current_lexer = old_lexer;

}

CPPExpression *
parse_const_expr(CPPPreprocessor *pp, CPPScope *new_current_scope,
                 CPPScope *new_global_scope) {
  CPPScope *old_scope = current_scope;
  CPPScope *old_global_scope = global_scope;
  CPPPreprocessor *old_lexer = current_lexer;
  CPPExpression *old_expr = current_expr;

  current_scope = new_current_scope;
  global_scope = new_global_scope;
  current_expr = nullptr;
  current_lexer = pp;
  yyparse();

  CPPExpression *result = current_expr;

  current_scope = old_scope;
  global_scope = old_global_scope;
  current_lexer = old_lexer;
  current_expr = old_expr;

  return result;
}

CPPType *
parse_type(CPPPreprocessor *pp, CPPScope *new_current_scope,
           CPPScope *new_global_scope) {
  CPPScope *old_scope = current_scope;
  CPPScope *old_global_scope = global_scope;
  CPPPreprocessor *old_lexer = current_lexer;
  CPPType *old_type = current_type;

  current_scope = new_current_scope;
  global_scope = new_global_scope;
  current_type = nullptr;
  current_lexer = pp;
  yyparse();

  CPPType *result = current_type;

  current_scope = old_scope;
  global_scope = old_global_scope;
  current_lexer = old_lexer;
  current_type = old_type;

  return result;
}

static void
push_scope(CPPScope *new_scope) {
  last_scopes.push_back(current_scope);
  if (new_scope != nullptr) {
    current_scope = new_scope;
  }
}

static void
pop_scope() {
  assert(!last_scopes.empty());
  current_scope = last_scopes.back();
  last_scopes.pop_back();
}

static void
push_storage_class(int new_storage_class) {
  last_storage_classes.push_back(current_storage_class);
  current_storage_class = new_storage_class;
}

static void
pop_storage_class() {
  assert(!last_storage_classes.empty());
  current_storage_class = last_storage_classes.back();
  last_storage_classes.pop_back();
}

static void
push_struct(CPPStructType *new_struct) {
  last_structs.push_back(current_struct);
  current_struct = new_struct;
}

static void
pop_struct() {
  assert(!last_structs.empty());
  current_struct = last_structs.back();
  last_structs.pop_back();
}


#line 273 "built/tmp/cppBison.yxx.c"

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
#ifndef YY_CPPYY_BUILT_TMP_CPPBISON_YXX_H_INCLUDED
# define YY_CPPYY_BUILT_TMP_CPPBISON_YXX_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int cppyydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    REAL = 258,
    INTEGER = 259,
    CHAR_TOK = 260,
    SIMPLE_STRING = 261,
    SIMPLE_IDENTIFIER = 262,
    STRING_LITERAL = 263,
    CUSTOM_LITERAL = 264,
    IDENTIFIER = 265,
    TYPENAME_IDENTIFIER = 266,
    TYPEPACK_IDENTIFIER = 267,
    SCOPING = 268,
    TYPEDEFNAME = 269,
    ELLIPSIS = 270,
    OROR = 271,
    ANDAND = 272,
    EQCOMPARE = 273,
    NECOMPARE = 274,
    LECOMPARE = 275,
    GECOMPARE = 276,
    LSHIFT = 277,
    RSHIFT = 278,
    POINTSAT_STAR = 279,
    DOT_STAR = 280,
    UNARY = 281,
    UNARY_NOT = 282,
    UNARY_NEGATE = 283,
    UNARY_MINUS = 284,
    UNARY_PLUS = 285,
    UNARY_STAR = 286,
    UNARY_REF = 287,
    POINTSAT = 288,
    SCOPE = 289,
    PLUSPLUS = 290,
    MINUSMINUS = 291,
    TIMESEQUAL = 292,
    DIVIDEEQUAL = 293,
    MODEQUAL = 294,
    PLUSEQUAL = 295,
    MINUSEQUAL = 296,
    OREQUAL = 297,
    ANDEQUAL = 298,
    XOREQUAL = 299,
    LSHIFTEQUAL = 300,
    RSHIFTEQUAL = 301,
    ATTR_LEFT = 302,
    ATTR_RIGHT = 303,
    KW_ALIGNAS = 304,
    KW_ALIGNOF = 305,
    KW_AUTO = 306,
    KW_BEGIN_PUBLISH = 307,
    KW_BLOCKING = 308,
    KW_BOOL = 309,
    KW_CATCH = 310,
    KW_CHAR = 311,
    KW_CHAR16_T = 312,
    KW_CHAR32_T = 313,
    KW_CLASS = 314,
    KW_CONST = 315,
    KW_CONSTEXPR = 316,
    KW_CONST_CAST = 317,
    KW_DECLTYPE = 318,
    KW_DEFAULT = 319,
    KW_DELETE = 320,
    KW_DOUBLE = 321,
    KW_DYNAMIC_CAST = 322,
    KW_ELSE = 323,
    KW_END_PUBLISH = 324,
    KW_ENUM = 325,
    KW_EXTENSION = 326,
    KW_EXTERN = 327,
    KW_EXPLICIT = 328,
    KW_PUBLISHED = 329,
    KW_FALSE = 330,
    KW_FINAL = 331,
    KW_FLOAT = 332,
    KW_FRIEND = 333,
    KW_FOR = 334,
    KW_GOTO = 335,
    KW_HAS_VIRTUAL_DESTRUCTOR = 336,
    KW_IF = 337,
    KW_INLINE = 338,
    KW_INT = 339,
    KW_IS_ABSTRACT = 340,
    KW_IS_BASE_OF = 341,
    KW_IS_CLASS = 342,
    KW_IS_CONSTRUCTIBLE = 343,
    KW_IS_CONVERTIBLE_TO = 344,
    KW_IS_DESTRUCTIBLE = 345,
    KW_IS_EMPTY = 346,
    KW_IS_ENUM = 347,
    KW_IS_FINAL = 348,
    KW_IS_FUNDAMENTAL = 349,
    KW_IS_POD = 350,
    KW_IS_POLYMORPHIC = 351,
    KW_IS_STANDARD_LAYOUT = 352,
    KW_IS_TRIVIAL = 353,
    KW_IS_UNION = 354,
    KW_LONG = 355,
    KW_MAKE_MAP_KEYS_SEQ = 356,
    KW_MAKE_MAP_PROPERTY = 357,
    KW_MAKE_PROPERTY = 358,
    KW_MAKE_PROPERTY2 = 359,
    KW_MAKE_SEQ = 360,
    KW_MAKE_SEQ_PROPERTY = 361,
    KW_MUTABLE = 362,
    KW_NAMESPACE = 363,
    KW_NEW = 364,
    KW_NOEXCEPT = 365,
    KW_NULLPTR = 366,
    KW_OPERATOR = 367,
    KW_OVERRIDE = 368,
    KW_PRIVATE = 369,
    KW_PROTECTED = 370,
    KW_PUBLIC = 371,
    KW_REGISTER = 372,
    KW_REINTERPRET_CAST = 373,
    KW_RETURN = 374,
    KW_SHORT = 375,
    KW_SIGNED = 376,
    KW_SIZEOF = 377,
    KW_STATIC = 378,
    KW_STATIC_ASSERT = 379,
    KW_STATIC_CAST = 380,
    KW_STRUCT = 381,
    KW_TEMPLATE = 382,
    KW_THREAD_LOCAL = 383,
    KW_THROW = 384,
    KW_TRUE = 385,
    KW_TRY = 386,
    KW_TYPEDEF = 387,
    KW_TYPEID = 388,
    KW_TYPENAME = 389,
    KW_UNDERLYING_TYPE = 390,
    KW_UNION = 391,
    KW_UNSIGNED = 392,
    KW_USING = 393,
    KW_VIRTUAL = 394,
    KW_VOID = 395,
    KW_VOLATILE = 396,
    KW_WCHAR_T = 397,
    KW_WHILE = 398,
    START_CPP = 399,
    START_CONST_EXPR = 400,
    START_TYPE = 401
  };
#endif
/* Tokens.  */
#define REAL 258
#define INTEGER 259
#define CHAR_TOK 260
#define SIMPLE_STRING 261
#define SIMPLE_IDENTIFIER 262
#define STRING_LITERAL 263
#define CUSTOM_LITERAL 264
#define IDENTIFIER 265
#define TYPENAME_IDENTIFIER 266
#define TYPEPACK_IDENTIFIER 267
#define SCOPING 268
#define TYPEDEFNAME 269
#define ELLIPSIS 270
#define OROR 271
#define ANDAND 272
#define EQCOMPARE 273
#define NECOMPARE 274
#define LECOMPARE 275
#define GECOMPARE 276
#define LSHIFT 277
#define RSHIFT 278
#define POINTSAT_STAR 279
#define DOT_STAR 280
#define UNARY 281
#define UNARY_NOT 282
#define UNARY_NEGATE 283
#define UNARY_MINUS 284
#define UNARY_PLUS 285
#define UNARY_STAR 286
#define UNARY_REF 287
#define POINTSAT 288
#define SCOPE 289
#define PLUSPLUS 290
#define MINUSMINUS 291
#define TIMESEQUAL 292
#define DIVIDEEQUAL 293
#define MODEQUAL 294
#define PLUSEQUAL 295
#define MINUSEQUAL 296
#define OREQUAL 297
#define ANDEQUAL 298
#define XOREQUAL 299
#define LSHIFTEQUAL 300
#define RSHIFTEQUAL 301
#define ATTR_LEFT 302
#define ATTR_RIGHT 303
#define KW_ALIGNAS 304
#define KW_ALIGNOF 305
#define KW_AUTO 306
#define KW_BEGIN_PUBLISH 307
#define KW_BLOCKING 308
#define KW_BOOL 309
#define KW_CATCH 310
#define KW_CHAR 311
#define KW_CHAR16_T 312
#define KW_CHAR32_T 313
#define KW_CLASS 314
#define KW_CONST 315
#define KW_CONSTEXPR 316
#define KW_CONST_CAST 317
#define KW_DECLTYPE 318
#define KW_DEFAULT 319
#define KW_DELETE 320
#define KW_DOUBLE 321
#define KW_DYNAMIC_CAST 322
#define KW_ELSE 323
#define KW_END_PUBLISH 324
#define KW_ENUM 325
#define KW_EXTENSION 326
#define KW_EXTERN 327
#define KW_EXPLICIT 328
#define KW_PUBLISHED 329
#define KW_FALSE 330
#define KW_FINAL 331
#define KW_FLOAT 332
#define KW_FRIEND 333
#define KW_FOR 334
#define KW_GOTO 335
#define KW_HAS_VIRTUAL_DESTRUCTOR 336
#define KW_IF 337
#define KW_INLINE 338
#define KW_INT 339
#define KW_IS_ABSTRACT 340
#define KW_IS_BASE_OF 341
#define KW_IS_CLASS 342
#define KW_IS_CONSTRUCTIBLE 343
#define KW_IS_CONVERTIBLE_TO 344
#define KW_IS_DESTRUCTIBLE 345
#define KW_IS_EMPTY 346
#define KW_IS_ENUM 347
#define KW_IS_FINAL 348
#define KW_IS_FUNDAMENTAL 349
#define KW_IS_POD 350
#define KW_IS_POLYMORPHIC 351
#define KW_IS_STANDARD_LAYOUT 352
#define KW_IS_TRIVIAL 353
#define KW_IS_UNION 354
#define KW_LONG 355
#define KW_MAKE_MAP_KEYS_SEQ 356
#define KW_MAKE_MAP_PROPERTY 357
#define KW_MAKE_PROPERTY 358
#define KW_MAKE_PROPERTY2 359
#define KW_MAKE_SEQ 360
#define KW_MAKE_SEQ_PROPERTY 361
#define KW_MUTABLE 362
#define KW_NAMESPACE 363
#define KW_NEW 364
#define KW_NOEXCEPT 365
#define KW_NULLPTR 366
#define KW_OPERATOR 367
#define KW_OVERRIDE 368
#define KW_PRIVATE 369
#define KW_PROTECTED 370
#define KW_PUBLIC 371
#define KW_REGISTER 372
#define KW_REINTERPRET_CAST 373
#define KW_RETURN 374
#define KW_SHORT 375
#define KW_SIGNED 376
#define KW_SIZEOF 377
#define KW_STATIC 378
#define KW_STATIC_ASSERT 379
#define KW_STATIC_CAST 380
#define KW_STRUCT 381
#define KW_TEMPLATE 382
#define KW_THREAD_LOCAL 383
#define KW_THROW 384
#define KW_TRUE 385
#define KW_TRY 386
#define KW_TYPEDEF 387
#define KW_TYPEID 388
#define KW_TYPENAME 389
#define KW_UNDERLYING_TYPE 390
#define KW_UNION 391
#define KW_UNSIGNED 392
#define KW_USING 393
#define KW_VIRTUAL 394
#define KW_VOID 395
#define KW_VOLATILE 396
#define KW_WCHAR_T 397
#define KW_WHILE 398
#define START_CPP 399
#define START_CONST_EXPR 400
#define START_TYPE 401

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int cppyyparse (void);

#endif /* !YY_CPPYY_BUILT_TMP_CPPBISON_YXX_H_INCLUDED  */



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
typedef yytype_int16 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  104
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7174

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  171
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  111
/* YYNRULES -- Number of rules.  */
#define YYNRULES  765
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1577

#define YYUNDEFTOK  2
#define YYMAXUTOK   401


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   169,     2,     2,     2,   162,   155,     2,
     165,   167,   160,   158,   148,   159,   164,   161,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   150,   149,
     156,   151,   157,   152,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   166,     2,   170,   154,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   147,   153,   168,   163,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   452,   452,   453,   457,   464,   465,   466,   470,   471,
     475,   479,   483,   496,   495,   507,   508,   509,   510,   511,
     512,   513,   526,   535,   539,   547,   551,   555,   576,   603,
     624,   653,   689,   732,   744,   765,   801,   835,   857,   893,
     915,   926,   940,   939,   954,   958,   963,   967,   978,   982,
     986,   990,   994,   998,  1002,  1006,  1010,  1014,  1018,  1022,
    1027,  1031,  1038,  1039,  1043,  1044,  1045,  1050,  1049,  1065,
    1075,  1074,  1091,  1099,  1107,  1118,  1134,  1133,  1148,  1163,
    1172,  1187,  1186,  1226,  1225,  1253,  1252,  1289,  1288,  1319,
    1318,  1337,  1336,  1357,  1356,  1388,  1387,  1413,  1426,  1430,
    1434,  1438,  1451,  1455,  1459,  1463,  1467,  1472,  1477,  1481,
    1485,  1489,  1496,  1500,  1504,  1508,  1512,  1516,  1520,  1524,
    1528,  1532,  1536,  1540,  1544,  1548,  1552,  1556,  1560,  1564,
    1568,  1572,  1576,  1580,  1584,  1588,  1592,  1596,  1600,  1604,
    1608,  1612,  1616,  1620,  1624,  1628,  1632,  1636,  1640,  1644,
    1648,  1655,  1656,  1657,  1661,  1663,  1662,  1670,  1671,  1675,
    1676,  1680,  1686,  1695,  1696,  1700,  1704,  1708,  1712,  1718,
    1724,  1730,  1737,  1742,  1751,  1755,  1760,  1768,  1780,  1784,
    1798,  1813,  1818,  1823,  1828,  1833,  1838,  1843,  1848,  1854,
    1853,  1884,  1894,  1904,  1908,  1912,  1921,  1925,  1933,  1937,
    1942,  1946,  1951,  1959,  1964,  1972,  1976,  1981,  1985,  1990,
    1998,  2003,  2011,  2015,  2022,  2026,  2033,  2037,  2041,  2045,
    2049,  2056,  2060,  2064,  2068,  2072,  2076,  2083,  2084,  2085,
    2089,  2092,  2093,  2094,  2098,  2103,  2109,  2115,  2120,  2126,
    2132,  2136,  2147,  2151,  2161,  2165,  2169,  2174,  2179,  2184,
    2189,  2194,  2199,  2207,  2211,  2215,  2220,  2225,  2230,  2235,
    2240,  2245,  2250,  2256,  2264,  2269,  2274,  2279,  2284,  2289,
    2294,  2299,  2304,  2309,  2315,  2323,  2327,  2332,  2337,  2342,
    2347,  2352,  2357,  2362,  2367,  2375,  2379,  2384,  2389,  2394,
    2399,  2404,  2409,  2414,  2419,  2424,  2430,  2437,  2444,  2454,
    2458,  2466,  2470,  2474,  2478,  2482,  2498,  2514,  2523,  2527,
    2537,  2544,  2555,  2559,  2567,  2571,  2575,  2579,  2583,  2599,
    2615,  2633,  2642,  2646,  2656,  2663,  2667,  2675,  2679,  2695,
    2711,  2720,  2730,  2737,  2741,  2749,  2753,  2758,  2762,  2770,
    2771,  2772,  2773,  2778,  2777,  2802,  2801,  2831,  2832,  2839,
    2840,  2844,  2845,  2849,  2853,  2857,  2861,  2865,  2869,  2873,
    2877,  2881,  2885,  2892,  2900,  2904,  2908,  2913,  2921,  2925,
    2932,  2933,  2938,  2945,  2946,  2951,  2959,  2963,  2967,  2974,
    2978,  2982,  2990,  2989,  3012,  3011,  3034,  3035,  3039,  3045,
    3052,  3061,  3062,  3063,  3067,  3071,  3075,  3079,  3083,  3087,
    3092,  3097,  3102,  3107,  3111,  3116,  3125,  3130,  3138,  3142,
    3146,  3154,  3164,  3164,  3174,  3175,  3179,  3180,  3181,  3182,
    3183,  3184,  3185,  3186,  3187,  3188,  3189,  3190,  3190,  3190,
    3191,  3191,  3191,  3191,  3192,  3192,  3192,  3192,  3192,  3193,
    3193,  3193,  3194,  3194,  3194,  3194,  3194,  3195,  3195,  3195,
    3195,  3195,  3196,  3196,  3197,  3197,  3197,  3197,  3197,  3198,
    3198,  3198,  3198,  3198,  3199,  3199,  3199,  3199,  3200,  3200,
    3200,  3200,  3200,  3201,  3201,  3201,  3201,  3201,  3202,  3202,
    3202,  3202,  3202,  3202,  3203,  3203,  3203,  3203,  3203,  3204,
    3204,  3204,  3204,  3205,  3205,  3205,  3205,  3206,  3206,  3206,
    3206,  3206,  3207,  3207,  3207,  3207,  3208,  3208,  3208,  3208,
    3208,  3209,  3209,  3209,  3209,  3210,  3210,  3210,  3210,  3210,
    3211,  3211,  3214,  3214,  3214,  3214,  3214,  3214,  3214,  3214,
    3214,  3214,  3214,  3215,  3215,  3215,  3215,  3215,  3215,  3215,
    3215,  3215,  3215,  3216,  3216,  3220,  3224,  3231,  3235,  3242,
    3246,  3253,  3257,  3261,  3265,  3269,  3273,  3277,  3281,  3293,
    3297,  3301,  3305,  3309,  3313,  3317,  3321,  3325,  3329,  3333,
    3337,  3341,  3345,  3349,  3353,  3357,  3361,  3365,  3369,  3373,
    3377,  3381,  3385,  3389,  3393,  3397,  3401,  3405,  3409,  3413,
    3421,  3425,  3429,  3433,  3437,  3441,  3445,  3455,  3465,  3471,
    3477,  3483,  3489,  3495,  3501,  3508,  3515,  3522,  3529,  3535,
    3541,  3545,  3557,  3561,  3565,  3569,  3573,  3584,  3595,  3599,
    3603,  3607,  3611,  3615,  3619,  3623,  3627,  3631,  3635,  3639,
    3643,  3647,  3651,  3655,  3659,  3663,  3667,  3671,  3675,  3679,
    3683,  3687,  3691,  3695,  3699,  3703,  3707,  3711,  3715,  3722,
    3726,  3730,  3734,  3738,  3742,  3746,  3750,  3754,  3760,  3766,
    3770,  3776,  3783,  3787,  3791,  3795,  3799,  3803,  3807,  3811,
    3815,  3819,  3823,  3827,  3831,  3835,  3839,  3843,  3847,  3861,
    3865,  3869,  3873,  3877,  3881,  3885,  3889,  3901,  3905,  3909,
    3913,  3917,  3928,  3939,  3943,  3947,  3951,  3955,  3959,  3963,
    3967,  3971,  3975,  3979,  3983,  3987,  3991,  3995,  3999,  4003,
    4007,  4011,  4015,  4019,  4023,  4027,  4031,  4035,  4039,  4043,
    4047,  4051,  4055,  4062,  4066,  4070,  4074,  4078,  4082,  4086,
    4090,  4094,  4100,  4106,  4114,  4118,  4122,  4126,  4133,  4143,
    4149,  4155,  4165,  4177,  4185,  4189,  4219,  4223,  4227,  4231,
    4235,  4239,  4245,  4249,  4253,  4257,  4261,  4272,  4276,  4280,
    4284,  4292,  4296,  4300,  4306,  4317
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "REAL", "INTEGER", "CHAR_TOK",
  "SIMPLE_STRING", "SIMPLE_IDENTIFIER", "STRING_LITERAL", "CUSTOM_LITERAL",
  "IDENTIFIER", "TYPENAME_IDENTIFIER", "TYPEPACK_IDENTIFIER", "SCOPING",
  "TYPEDEFNAME", "ELLIPSIS", "OROR", "ANDAND", "EQCOMPARE", "NECOMPARE",
  "LECOMPARE", "GECOMPARE", "LSHIFT", "RSHIFT", "POINTSAT_STAR",
  "DOT_STAR", "UNARY", "UNARY_NOT", "UNARY_NEGATE", "UNARY_MINUS",
  "UNARY_PLUS", "UNARY_STAR", "UNARY_REF", "POINTSAT", "SCOPE", "PLUSPLUS",
  "MINUSMINUS", "TIMESEQUAL", "DIVIDEEQUAL", "MODEQUAL", "PLUSEQUAL",
  "MINUSEQUAL", "OREQUAL", "ANDEQUAL", "XOREQUAL", "LSHIFTEQUAL",
  "RSHIFTEQUAL", "ATTR_LEFT", "ATTR_RIGHT", "KW_ALIGNAS", "KW_ALIGNOF",
  "KW_AUTO", "KW_BEGIN_PUBLISH", "KW_BLOCKING", "KW_BOOL", "KW_CATCH",
  "KW_CHAR", "KW_CHAR16_T", "KW_CHAR32_T", "KW_CLASS", "KW_CONST",
  "KW_CONSTEXPR", "KW_CONST_CAST", "KW_DECLTYPE", "KW_DEFAULT",
  "KW_DELETE", "KW_DOUBLE", "KW_DYNAMIC_CAST", "KW_ELSE", "KW_END_PUBLISH",
  "KW_ENUM", "KW_EXTENSION", "KW_EXTERN", "KW_EXPLICIT", "KW_PUBLISHED",
  "KW_FALSE", "KW_FINAL", "KW_FLOAT", "KW_FRIEND", "KW_FOR", "KW_GOTO",
  "KW_HAS_VIRTUAL_DESTRUCTOR", "KW_IF", "KW_INLINE", "KW_INT",
  "KW_IS_ABSTRACT", "KW_IS_BASE_OF", "KW_IS_CLASS", "KW_IS_CONSTRUCTIBLE",
  "KW_IS_CONVERTIBLE_TO", "KW_IS_DESTRUCTIBLE", "KW_IS_EMPTY",
  "KW_IS_ENUM", "KW_IS_FINAL", "KW_IS_FUNDAMENTAL", "KW_IS_POD",
  "KW_IS_POLYMORPHIC", "KW_IS_STANDARD_LAYOUT", "KW_IS_TRIVIAL",
  "KW_IS_UNION", "KW_LONG", "KW_MAKE_MAP_KEYS_SEQ", "KW_MAKE_MAP_PROPERTY",
  "KW_MAKE_PROPERTY", "KW_MAKE_PROPERTY2", "KW_MAKE_SEQ",
  "KW_MAKE_SEQ_PROPERTY", "KW_MUTABLE", "KW_NAMESPACE", "KW_NEW",
  "KW_NOEXCEPT", "KW_NULLPTR", "KW_OPERATOR", "KW_OVERRIDE", "KW_PRIVATE",
  "KW_PROTECTED", "KW_PUBLIC", "KW_REGISTER", "KW_REINTERPRET_CAST",
  "KW_RETURN", "KW_SHORT", "KW_SIGNED", "KW_SIZEOF", "KW_STATIC",
  "KW_STATIC_ASSERT", "KW_STATIC_CAST", "KW_STRUCT", "KW_TEMPLATE",
  "KW_THREAD_LOCAL", "KW_THROW", "KW_TRUE", "KW_TRY", "KW_TYPEDEF",
  "KW_TYPEID", "KW_TYPENAME", "KW_UNDERLYING_TYPE", "KW_UNION",
  "KW_UNSIGNED", "KW_USING", "KW_VIRTUAL", "KW_VOID", "KW_VOLATILE",
  "KW_WCHAR_T", "KW_WHILE", "START_CPP", "START_CONST_EXPR", "START_TYPE",
  "'{'", "','", "';'", "':'", "'='", "'?'", "'|'", "'^'", "'&'", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "'.'", "'('", "'['",
  "')'", "'}'", "'!'", "']'", "$accept", "grammar", "cpp",
  "constructor_inits", "constructor_init", "extern_c", "$@1",
  "declaration", "friend_declaration", "$@2", "storage_class",
  "attribute_specifiers", "attribute_specifier", "type_like_declaration",
  "$@3", "$@4", "multiple_instance_identifiers", "typedef_declaration",
  "$@5", "typedef_instance_identifiers", "constructor_prototype", "$@6",
  "$@7", "$@8", "function_prototype", "$@9", "$@10", "$@11", "$@12",
  "$@13", "function_post", "function_operator",
  "more_template_declaration", "template_declaration", "$@14",
  "template_formal_parameters", "template_nonempty_formal_parameters",
  "typename_keyword", "template_formal_parameter",
  "template_formal_parameter_type", "instance_identifier", "$@15",
  "instance_identifier_and_maybe_trailing_return_type",
  "maybe_trailing_return_type", "maybe_comma_identifier",
  "function_parameter_list", "function_parameters",
  "formal_parameter_list", "formal_parameters",
  "template_parameter_maybe_initialize", "maybe_initialize",
  "maybe_initialize_or_constructor_body",
  "maybe_initialize_or_function_body", "structure_init",
  "structure_init_body", "function_parameter", "formal_parameter",
  "not_paren_formal_parameter_identifier", "formal_parameter_identifier",
  "parameter_pack_identifier", "not_paren_empty_instance_identifier",
  "empty_instance_identifier", "type", "type_pack", "type_decl",
  "predefined_type", "var_type_decl", "full_type", "struct_attributes",
  "anonymous_struct", "$@16", "named_struct", "$@17", "maybe_final",
  "maybe_class_derivation", "class_derivation", "base_specification",
  "enum", "enum_decl", "enum_element_type", "enum_body_trailing_comma",
  "enum_body", "enum_keyword", "struct_keyword", "namespace_declaration",
  "$@18", "$@19", "using_declaration", "simple_type", "simple_int_type",
  "simple_float_type", "simple_void_type", "code", "$@20", "code_block",
  "element", "optional_const_expr", "optional_const_expr_comma",
  "const_expr_comma", "no_angle_bracket_const_expr", "const_expr",
  "const_operand", "formal_const_expr", "formal_const_operand",
  "capture_list", "capture", "class_derivation_name", "name",
  "name_no_final", "string_literal", "empty", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   123,    44,    59,
      58,    61,    63,   124,    94,    38,    60,    62,    43,    45,
      42,    47,    37,   126,    46,    40,    91,    41,   125,    33,
      93
};
# endif

#define YYPACT_NINF (-915)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-761)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     345,  -915,  3933,  5735,    55,  4767,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,   -46,   -80,   -47,   -21,     9,    17,
     -76,    30,    47,  -915,  -915,    43,    52,    59,    66,    70,
      77,    98,   102,   107,   135,   149,   156,   171,   177,   194,
     207,   216,   257,   278,  6049,  -915,  -915,   183,   280,   282,
      36,   300,  -915,   293,   299,   307,  3933,  3933,  3933,  3933,
    3933,  2032,  1182,  3933,  4564,  -915,   318,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  5846,   312,  -915,   -16,  -915,
    -915,  4228,  1440,  1440,  -915,  4566,   330,  -915,  1440,  -915,
    -915,   163,   163,  -915,  -915,  -915,  -915,   336,   114,  -915,
    -915,  -915,  -915,  -915,  -915,  6170,   332,  -915,  7033,  7033,
    7033,  -915,  7033,  5174,  7033,   349,  -915,  7018,   337,   341,
     356,   363,   378,   391,  7033,  1957,   358,   360,   380,  7033,
    7033,   395,  6825,  7033,  7033,  1536,  7033,  7033,  -915,  -915,
    -915,  -915,  2169,  -915,  -915,  -915,  -915,  -915,  3933,  3933,
    5735,  3933,  3933,  3933,  3933,  5735,  3933,  5735,  3933,  5735,
    3933,  5735,  5735,  5735,  5735,  5735,  5735,  5735,  5735,  5735,
    5735,  5735,  5735,  5735,  5735,  5735,  3933,  -915,  -915,   402,
    4566,   404,   406,  4566,  -915,  -915,  5735,  3933,  3933,   407,
    5332,  5735,  2032,  3933,  3933,    74,    74,    74,    74,    74,
     -46,   -47,   -21,     9,    17,    30,    43,    59,  6717,  1330,
    5687,  6769,   307,   390,   -86,  4564,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  4566,  4566,
    -104,   429,  -915,  -915,    74,  3933,  3933,  3933,  3933,  3933,
    3933,  3933,  3933,  3933,  3933,  3933,  3933,  3933,  3933,  3933,
    3933,  3933,  3933,  3933,  3933,  3933,  2988,  3933,  -915,  -915,
     163,   163,  3123,  -915,  -915,  -915,  1440,  -915,  -915,  -915,
    -915,  5735,  -915,   421,   428,   343,   163,   163,   343,   343,
    4881,   416,  -915,   417,  -915,  -915,  -915,  -915,  -915,  -915,
    1173,   436,  4037,  -915,  4566,   539,   443,   427,  2713,  5246,
    7033,  -915,  -915,  -915,  -915,  7033,  -915,  -915,  -915,  -915,
    6918,  4562,  -915,  4566,  4566,  4566,  4566,  4566,  4566,  -915,
    -915,   446,  -915,  -915,  -915,  -915,  -915,  3933,  -915,  1273,
    -915,   439,  -915,  4155,  -915,  4566,   233,  -915,  -915,   308,
     431,  -915,   432,  5933,  4566,   433,  -915,  4566,  -915,   -55,
     450,  -915,  -915,  -915,  -915,  1176,  -915,  -915,   434,   453,
    -915,   437,   438,   441,   442,   447,   452,   456,   461,   460,
     462,   463,   465,   467,   455,   469,   -85,   458,   472,   473,
     475,   476,   477,   478,   481,   482,   490,   491,   492,  3933,
    -915,  5735,  3933,  -915,  5921,   505,   496,   497,  4566,   498,
     499,   516,   507,  4282,   508,   509,  3933,  3933,  -915,   623,
    -915,  1121,   512,  3933,  -915,  -915,  3006,  4934,  5047,  5047,
     691,   691,   187,   187,  -915,  3280,  4950,  1753,  4991,   691,
     691,   259,   259,    74,    74,    74,  -915,  -915,   -83,  1707,
    -915,  -915,   511,  4303,   513,   343,   515,   519,  4566,   343,
     343,   343,   343,   343,   517,  -915,   416,  -915,   416,  -915,
     517,   517,  -915,   343,  6170,  5822,  5706,   343,   343,   518,
      22,  -915,  1107,   320,  -915,  3933,  4566,   525,  -915,  -915,
    -915,  -915,  1173,    -5,    -4,    21,  6170,   522,   136,  -915,
    -915,  -915,   534,  7033,  6170,  2201,   -46,   527,  4321,  -915,
    -915,  -915,   549,   550,   551,   552,   553,   556,   557,  6245,
    -915,  4224,  5482,     7,   532,   -55,  -915,  -915,   558,  -915,
    5735,  -915,    25,  3258,  6073,   352,  -915,  5735,  -915,   541,
     384,  -915,  -915,  2853,  -915,  -915,   873,  -915,   559,  4037,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   546,  -915,   554,
    -915,  -915,  -915,  -915,  5735,  -915,  5735,  -915,  5735,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    4340,   555,   563,  -915,   566,  -915,  -915,   567,  -915,  -915,
     568,  -915,  -915,  -915,  -915,    74,  4564,  -915,  4566,   429,
    5585,  1402,  -915,  4564,  3933,  -915,  -915,  -915,  -915,  -915,
     517,   343,  -915,   517,   517,   517,   517,   517,  3933,   -98,
     669,  5846,  1107,   320,  -915,   123,   250,  -915,  -915,  5614,
     561,  1107,  1107,  1107,  1107,  1107,  1107,   -87,  -915,  -915,
     575,  4566,   320,   320,   320,   320,   320,   320,    90,   548,
    4564,  -915,   -17,  -915,   589,   693,  2713,  -915,   663,  6170,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   579,   590,
     598,  -915,  -915,  6049,  -915,  -915,   599,    37,   603,  -915,
     595,  3933,  3933,  3933,  3933,  2032,  3933,   594,    31,  -915,
    -915,  4582,  -915,   318,  -915,  7033,  7033,  6318,  -915,   752,
     754,   759,   760,   761,   764,  -915,  -915,   382,   630,  -915,
    -915,  -915,  -915,  5293,  -915,   627,   632,  6752,  -915,  1068,
    -915,  -915,    34,  -915,   873,  -915,   636,  5585,   619,   628,
     873,  5585,   620,  4376,   352,   629,   352,   352,   352,   352,
     352,   261,  -915,  -915,   624,  6391,  -915,  -915,  -915,  4566,
     372,  -915,   626,  -915,   643,   649,  3393,  3550,   640,   873,
     873,  1553,   873,   873,   873,   873,  -915,   144,   178,  -915,
    1173,  -915,  3933,  3933,   639,   644,   645,  -915,  -915,  -915,
    3933,  -915,  3933,  -915,   650,  -915,  5962,  6170,  -915,  -915,
    -915,  -915,  -915,  -915,   638,  -915,  -915,   660,  -915,  4564,
     517,   648,   655,  5706,  1107,   320,   -87,    90,   656,   657,
    1402,  -915,  -915,  1107,   658,   658,   658,   658,   658,   302,
    3933,  -915,   320,  -915,   662,   662,   662,   662,   662,   359,
    3933,  -915,   664,  -915,  3933,  -915,   666,  4394,  6464,  -915,
     681,  -915,  -915,  5735,  5735,  5735,   670,  5735,   671,  5361,
    5735,  2032,    74,    74,    74,    74,   667,   -59,    74,  -915,
    -915,  4068,  3933,  3933,  3933,  3933,  3933,  3933,  3933,  3933,
    3933,  3933,  3933,  3933,  3933,  3933,  3933,  3933,  3933,  3933,
    3933,  3933,  3933,  3528,  3933,  -915,  -915,  -915,  -915,   689,
     -39,   690,   694,   695,   697,  6537,    42,  -915,  1068,  6991,
    5482,  4566,   688,   686,  1068,  1068,  1068,  1068,  1068,  1068,
     145,   662,  -915,   178,  -915,   674,   682,   873,   348,   692,
    -915,  -915,   371,   352,   698,   698,   698,   698,   698,  -915,
    3933,  -915,  -915,  5585,   680,   392,  -915,   -24,   709,   711,
    -915,  2545,  -915,  -915,  -915,  3393,   705,   713,  4564,  -915,
    -915,   873,   381,   381,   853,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,   699,   704,  -915,  -915,   381,   381,   381,   353,   861,
    -915,  3933,  -915,  2853,   728,  -915,   589,   -18,    14,  -915,
    -915,  -915,    51,    62,  -915,  6049,   163,   830,   365,  -915,
    -915,  5585,  -915,   -87,    90,  -915,  -915,  5585,  5585,  -915,
     658,   714,   712,   662,   716,   719,  3820,  -915,  -915,  -915,
    5573,   744,   762,  -915,   733,   750,   756,  3933,   763,  4566,
     742,   749,   766,   765,  4492,  3933,  -915,  -915,  -915,  3006,
    4934,  5047,  5047,   691,   691,   187,   187,  -915,  4546,  4950,
    1753,  4991,   691,   691,   259,   259,    74,    74,    74,  -915,
    -915,    85,  1771,  6610,   901,   911,   780,   921,   768,  -915,
     927,   929,   935,  -915,   800,   145,   662,  -915,  -915,  -915,
    -915,  -915,  -915,  5735,  1068,  1897,  -915,  -915,   803,  -915,
    -915,  -915,   387,   787,  -915,  -915,   698,  5585,   783,   788,
    -915,  -915,  4566,  3933,  3933,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   786,  -915,  3663,
     381,  -915,  -915,  -915,  -915,  -915,  2201,   789,  3550,   873,
    -915,  -915,  -915,  -915,  1402,   163,  -915,  -915,  -915,    24,
     790,   793,  -915,  -915,   794,   795,  5585,  -915,  5585,  -915,
    -915,  6082,  6142,  6156,  4566,   449,  -915,  -915,   948,  -915,
    5573,  -915,   801,   802,   798,   805,   806,  -915,  -915,   809,
    -915,  -915,    74,  3933,  -915,  -915,  -915,   808,   120,  -915,
     833,   829,   132,   817,   140,  -915,  -915,  -915,   823,   837,
     841,   842,    41,   843,  1897,  1897,  1897,  1897,  1897,  2032,
    1897,  4644,  -915,   873,  5179,  5585,   835,  -915,  5179,  5585,
     834,  -915,  -915,   839,  -915,   847,   844,  2377,  -915,  3393,
    4564,   851,  -915,  -915,   855,  -915,   852,  -915,  -915,  -915,
    -915,  -915,   856,   857,  5444,  -915,  5444,  -915,  5444,  -915,
    -915,  5444,  5444,  5444,  -915,  6683,  -915,  3933,  3933,  -915,
    3933,  -915,  3933,  4564,   860,  1010,   876,  1012,  -915,  1016,
     878,   880,  1020,   882,  5735,  5735,  5735,  5735,   867,  5453,
    5735,    89,    89,    89,    89,    89,   868,   150,    89,  1897,
    1897,  1897,  1897,  1897,  1897,  1897,  1897,  1897,  1897,  1897,
    1897,  1897,  1897,  1897,  1897,  1897,  1897,  1897,  3798,  3933,
    -915,   870,  -915,  5585,   872,  -915,  5179,  -915,  -915,  1019,
    -915,   874,  -915,  -915,  -915,  1402,  1402,  1402,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   164,   165,   174,
     190,  -915,   893,  -915,   877,   895,  -915,  -915,   206,  -915,
     903,   888,   914,   916,  4566,   908,   909,   920,  1897,  -915,
    4759,  4966,  5113,  5113,   782,   782,   236,   236,  -915,  4600,
    5007,  5024,  5033,   413,   413,    89,    89,    89,  -915,  -915,
     218,  2735,  -915,  5585,   915,  -915,  5179,  -915,  -915,  5179,
     900,  -915,  -915,  -915,  5179,  5179,  -915,  -915,  -915,  -915,
    1076,   922,   938,  1078,  1080,   942,  -915,   930,   931,   932,
     925,  -915,  -915,   933,    89,  1897,  -915,  -915,  5179,   934,
    -915,  5179,  -915,  -915,   945,  -915,   937,   220,  -915,  3933,
    3933,  3933,  -915,  3933,  4644,  -915,  1402,  -915,   951,  1092,
     956,   222,   226,   265,   266,  1402,  -915,  -915,   940,  -915,
    -915,  -915,  -915,  -915,  -915,   959,  -915
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   765,     0,     0,     0,   765,     5,   653,   649,   652,
     761,   762,   655,   656,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   651,   657,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   659,   658,     0,     0,     0,
       0,     0,   650,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   765,     0,     3,   590,   654,   300,   311,   310,
     394,   395,   397,   398,   379,     0,     0,   409,   376,   408,
     403,   400,   399,   402,   380,     0,     0,   381,   401,   411,
     396,   765,   765,     4,   302,   303,   304,     0,   365,   765,
     299,   391,   392,   393,     1,     0,     0,    21,   765,   765,
     765,    22,   765,   765,   765,     0,    42,   765,     0,     0,
       0,     0,     0,     0,   765,     0,     0,     0,     0,   765,
     765,     0,   765,   765,   765,     0,   765,   765,     6,    17,
       7,    19,     0,    15,    16,    18,    73,    44,   765,   765,
       0,   765,   765,   765,   765,     0,   765,     0,   765,     0,
     765,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   765,   326,   332,     0,
       0,     0,   614,     0,   765,   325,     0,   765,   765,     0,
       0,     0,     0,   765,   765,   623,   621,   620,   622,   619,
     300,   394,   395,   397,   398,   409,   408,   403,   400,   399,
     402,   401,   396,     0,     0,   549,   746,   747,   748,   756,
     749,   752,   750,   754,   753,   751,   755,   735,   736,     0,
       0,   765,   741,   734,   618,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   763,   764,
     765,   765,     0,   377,   378,   410,   400,   405,   404,   407,
     301,     0,   406,     0,   286,   765,   765,   765,   765,   765,
     765,     0,   335,   285,   337,   765,   757,   758,   759,   760,
       0,   367,     0,   339,     0,     0,    62,    64,     0,   765,
     765,    56,    45,    55,    57,   765,    46,   154,    51,    23,
     765,     0,    49,     0,     0,     0,     0,     0,     0,    54,
     765,     0,    26,    25,    24,    52,    48,     0,   158,     0,
     157,     0,    58,     0,    20,     0,     0,    50,    53,   334,
     313,   324,     0,     0,     0,     0,    13,     0,    70,     0,
     333,    67,   315,   316,   317,   365,   765,   312,     0,   548,
     547,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     327,     0,   765,   329,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   648,   739,
     742,     0,   765,     0,   737,   214,   632,   633,   634,   635,
     636,   637,   640,   641,   647,     0,   629,   630,   631,   638,
     639,   627,   628,   624,   625,   626,   646,   645,     0,     0,
     336,   338,     0,     0,     0,   765,   287,     0,   276,   765,
     765,   765,   765,   765,   292,   275,     0,   288,     0,   289,
     291,   290,   199,   765,     0,     0,     0,   765,   765,     0,
     200,   203,   765,     0,   198,   765,   373,     0,   370,   369,
     364,   368,     0,   746,   747,   748,     0,     0,   750,   343,
     305,   345,     0,   765,     0,   765,   313,     0,     0,    47,
      43,   765,     0,     0,     0,     0,     0,     0,     0,   765,
     382,     0,   765,   334,   313,     0,   333,    76,     0,   388,
       0,    81,    85,     0,     0,   765,   314,     0,   765,     0,
       0,   412,   221,     0,    72,    69,     0,   320,   367,     0,
     597,   596,   613,   603,   599,   601,   602,     0,   609,     0,
     608,   662,   598,   663,     0,   665,     0,   666,     0,   669,
     670,   671,   672,   673,   674,   675,   676,   677,   678,   605,
       0,     0,     0,   328,     0,   604,   607,     0,   611,   610,
       0,   616,   617,   606,   600,   591,   550,   740,     0,   765,
     765,   765,    98,   215,     0,   644,   643,   308,   307,   309,
     293,   765,   277,   282,   278,   279,   281,   280,   765,     0,
       0,     0,   765,     0,   240,     0,     0,   765,   202,     0,
       0,   765,   765,   765,   765,   765,   765,   765,   254,   253,
       0,   264,     0,     0,     0,     0,     0,     0,   765,     0,
     546,   545,   374,   363,   306,     0,     0,   765,   765,     0,
      59,    63,   727,   723,   726,   729,   730,   206,     0,     0,
       0,   725,   731,     0,   733,   732,     0,     0,     0,   724,
       0,     0,     0,     0,     0,     0,     0,     0,   207,   242,
     210,   243,   679,   728,   205,   765,   765,   765,   384,     0,
       0,     0,     0,     0,     0,   386,   765,     0,     0,   175,
     176,   177,   163,     0,   164,     0,   160,   165,   161,   765,
     174,   159,     0,    78,     0,   390,     0,   765,     0,     0,
       0,   765,     0,     0,   765,     0,   765,   765,   765,   765,
     765,     0,   245,   244,     0,   765,    87,   412,   216,     0,
       0,    71,     0,   765,     0,     0,   765,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    68,   765,   765,   178,
       0,   318,     0,     0,     0,     0,     0,   330,   331,   615,
       0,   612,     0,   738,     0,   105,     0,     0,    99,   107,
     102,   106,   101,   103,     0,   100,   104,     0,   193,   642,
     283,     0,     0,     0,   765,     0,   765,   765,     0,     0,
     765,   201,   204,   765,   259,   255,   256,   258,   257,     0,
     765,   234,     0,   265,   270,   266,   267,   269,   268,     0,
     765,   237,   294,   371,     0,   340,     0,     0,   765,   348,
     765,   347,    66,     0,     0,     0,   689,     0,     0,     0,
       0,     0,   697,   696,   695,   694,     0,     0,   693,    65,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    60,   387,   765,     0,
       0,   765,     0,     0,     0,   765,     0,    41,   765,   765,
       0,   168,   166,     0,   765,   765,   765,   765,   765,   765,
     765,   172,    77,   765,   389,     0,     0,     0,     0,     0,
     322,   321,     0,   765,   250,   246,   247,   249,   248,    93,
     765,   323,    14,   765,     0,     0,     8,     0,     0,     0,
     222,   413,   414,   224,   225,   765,     0,   228,   230,   227,
     223,     0,   185,   181,     0,   122,   123,   124,   125,   126,
     127,   130,   131,   146,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   150,   149,   133,   132,
     119,   121,   120,   128,   129,   117,   118,   114,   115,   116,
     113,     0,     0,   112,   179,   182,   184,   183,     0,     0,
     189,   765,   191,     0,     0,    74,   319,     0,     0,   664,
     667,   668,     0,     0,   765,     0,   765,     0,     0,   412,
     284,   765,   241,   765,   765,   235,   238,   765,   765,   295,
     260,   263,     0,   271,   274,     0,   375,   342,   341,   344,
       0,     0,   350,   349,     0,     0,     0,   765,     0,     0,
       0,     0,     0,     0,     0,     0,   722,   208,   211,   706,
     707,   708,   709,   710,   711,   714,   715,   721,     0,   703,
     704,   705,   712,   713,   701,   702,   698,   699,   700,   720,
     719,     0,     0,   765,     0,     0,     0,     0,     0,   196,
       0,     0,     0,   383,     0,   765,   173,   153,   151,   156,
     152,   162,   169,     0,   765,     0,   170,   212,     0,    79,
     765,    83,     0,     0,   765,    95,   251,   765,     0,     0,
     217,   412,     0,   765,   765,   219,   220,   416,   417,   421,
     418,   426,   419,   420,   422,   423,   424,   425,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   494,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   765,   538,   539,   540,   531,   543,   527,
     528,   526,   533,   534,   522,   523,   524,   525,   532,   530,
     537,   535,   541,   536,   529,   542,   415,     0,   226,   229,
     186,   180,   148,   147,   188,   192,   765,     0,   215,     0,
     594,   593,   595,   592,   765,   765,   194,   111,   108,     0,
       0,     0,   236,   239,     0,     0,   765,   261,   765,   272,
     372,   754,     0,   753,     0,     0,   351,   353,   743,   765,
       0,   688,     0,     0,     0,     0,     0,   686,   685,     0,
     691,   692,   680,     0,   718,   717,   385,     0,     0,    33,
     197,     0,     0,     0,     0,    40,   171,   167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   213,   551,     0,    82,   765,     0,    89,    86,   765,
       0,   252,   765,     0,     9,     0,     0,     0,   231,   765,
     232,     0,   187,    75,     0,   195,     0,   109,   660,   765,
     765,   765,     0,     0,     0,   356,     0,   355,     0,   354,
     744,     0,     0,     0,   745,   765,   352,     0,     0,   690,
       0,   687,     0,   716,     0,     0,     0,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   566,   564,   563,   565,   562,     0,     0,   561,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,     0,    91,   765,     0,   765,    88,   218,    12,    10,
     544,     0,   765,   412,   110,   765,   765,   765,   765,   765,
     362,   361,   360,   359,   358,   357,   346,     0,     0,     0,
       0,    36,   765,    34,     0,     0,    37,    39,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   589,
     575,   576,   577,   578,   579,   580,   581,   582,   588,     0,
     572,   573,   574,   570,   571,   567,   568,   569,   587,   586,
       0,     0,   765,   765,     0,   765,    94,    11,   233,   190,
       0,   298,   297,   296,   262,   273,   683,   682,   684,   681,
       0,     0,     0,     0,     0,     0,   560,     0,     0,     0,
       0,   558,   557,     0,   552,     0,   585,   584,    84,     0,
     765,    96,   661,   197,     0,    28,     0,     0,    30,     0,
       0,     0,   559,     0,   583,   765,   765,    35,     0,     0,
       0,     0,     0,     0,     0,   765,    90,    38,     0,    31,
     555,   554,   556,   553,    92,     0,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -915,  -915,  -317,  -915,    -3,  -915,  -915,   804,  -122,  -915,
       3,  -437,   466,  -121,  -915,  -915,  -148,  -915,  -915,  -217,
    -915,  -915,  -915,  -915,   792,  -915,  -915,  -915,  -915,  -915,
    -534,  -915,  -915,  -107,  -915,  -915,  -915,  -915,   231,   419,
    -650,  -915,  -702,  -755,  -336,  -495,  -915,  -126,  -915,    50,
    -560,  -915,  -485,  -914,  -915,  -459,   276,  -563,    29,  -227,
    -202,   -88,   -61,   -35,  -275,  -638,   822,   979,  -151,  -129,
    -915,  -108,  -915,  -915,  -915,  -915,  -153,  -101,  -915,  -454,
    -915,  -915,   -28,   -13,  -915,  -915,  -915,  -915,   -36,     5,
    -915,  -915,  -728,  -915,   -67,  -915,  -576,  -134,   -60,   471,
     812,   426,  -915,  -915,  -915,   746,  -377,  1291,    23,  -490,
      -1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,   925,   926,   139,   528,   140,   141,   310,
     142,   295,   296,   143,   536,   530,   756,   334,   714,   902,
     348,   717,  1335,   721,   349,   923,  1433,  1503,  1107,  1339,
     591,   984,  1089,   144,   331,   705,   706,   707,   708,   709,
     757,  1256,   758,   787,  1078,   469,   470,   677,   678,  1096,
     414,   741,   534,   936,   937,   471,   680,   731,   804,   814,
     281,   282,    91,    92,   350,   182,   351,    93,   292,    94,
     647,    95,   648,   830,  1031,  1032,  1286,    96,    97,   480,
     476,   477,    98,    99,   145,   696,   878,   146,   100,   101,
     102,   103,   742,   743,   931,  1246,   639,   358,   359,  1331,
     215,    65,   681,   682,   230,   231,  1287,  1288,   628,    66,
     147
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       6,   214,   992,   509,   284,   683,   307,   614,   185,   924,
     328,   330,   903,   352,   260,   361,   183,   363,   364,   365,
     366,  1247,   368,   497,   370,   836,   372,   610,   644,   773,
     713,   184,   791,   394,   353,   718,   679,   618,   719,  1356,
     261,   354,   388,   263,   411,  1019,   850,   719,   258,   645,
     259,   189,   838,   396,   397,   104,  1398,   651,   516,   404,
     405,   233,   407,   556,   413,   407,   412,   811,   608,   792,
     908,  -757,  -758,   454,   456,   458,   460,   461,   821,   810,
     155,   408,   557,   800,   595,   150,   267,   268,   269,   407,
     283,   283,   531,   272,   532,   774,   533,  -759,   293,   942,
     943,   148,   985,   986,   987,   988,   357,   243,  1046,  1075,
     264,   301,   302,   303,   355,   304,   306,   308,   151,   149,
     312,   291,  1417,  1113,   286,   287,   288,   319,  1076,   356,
     407,   823,   325,   326,   824,   329,   332,   333,  1006,   337,
     338,  1114,  -757,  -758,   152,  -757,  -758,   360,   360,  1260,
     360,   360,   360,   360,   -97,   360,   -97,   360,   -97,   360,
     802,   912,   407,   914,   915,   916,   917,   918,  -759,   352,
     619,  -759,   440,   441,   153,   360,   273,   776,   274,   851,
     275,  1261,   154,   293,   687,   720,   360,   360,   457,   459,
     353,  1357,   360,   360,   720,   156,   438,   354,   994,   407,
     352,   190,   839,   157,   352,   539,  1399,   886,   158,  1084,
     407,   735,  -760,   267,   268,   269,   272,   159,  1262,   472,
     243,   353,   905,   276,   160,   353,   909,   289,   354,  1263,
     415,   161,   354,   407,  1022,   162,  1015,  1016,   255,   256,
     257,   413,   163,   600,  1025,   473,   638,   603,   604,   605,
     606,   607,  1304,  1427,  1428,  1429,   820,  1102,   572,   283,
     283,   609,   357,   164,   290,   615,   616,   165,  1385,  1417,
     355,   267,   166,   995,   455,   283,   283,   455,   455,   474,
    1389,  1270,   525,  -760,   478,   356,  -760,  1386,  1392,   608,
     798,  1250,   243,   357,   989,   481,  1095,   357,   407,  1390,
     167,   355,   306,   312,   277,   355,   996,  1393,   499,   990,
     991,   810,   407,   407,   168,   491,   356,  1479,   278,     6,
     356,   169,   407,   279,   258,   531,   259,   532,   280,   993,
     828,  1516,  1517,   630,  1012,   631,   170,   632,   407,   186,
    1007,  1518,   171,  1098,  1108,   250,   251,   252,   253,   254,
    1106,   255,   256,   257,  1524,   293,   447,  1519,   448,   172,
     449,   683,   286,   287,   288,   725,   407,  1265,  1559,   726,
     407,   826,   173,  1525,   407,   216,   217,   218,   538,   885,
     633,   174,   519,  1343,   520,  1536,   797,  1560,    10,  1570,
      11,   360,   679,  1571,  1422,  1423,  1424,  1425,  1426,   790,
    1427,  1428,  1429,   450,   612,   472,   815,   816,   817,   818,
     819,   592,   727,   407,   407,  1257,   608,   799,  1099,   252,
     253,   254,   175,   255,   256,   257,   919,   920,  1109,   219,
     613,   473,  1572,  1573,   472,  1441,   928,   929,   216,   217,
     218,   220,   221,   176,   455,   187,  1417,   188,   455,   455,
     455,   455,   455,  1272,  1273,   -97,   191,   -97,   192,   -97,
     473,   634,   455,   724,   193,   289,   455,   455,   810,  1021,
    1264,   629,   194,   521,   641,   635,   710,   262,   222,   223,
     636,   224,   901,   285,   451,   637,   225,   481,   226,     1,
       2,     3,   219,   728,   684,   271,   650,   298,   452,   309,
       6,   627,   313,   453,   220,   221,   314,   729,   322,  1354,
     323,   711,   730,   990,   991,  1103,  1271,   352,   990,   991,
    1254,   315,  1274,  1275,   733,   820,  1024,     6,   316,   472,
     324,   737,  1268,   738,   739,   740,  1105,   920,   353,  1111,
    1112,   222,   223,   317,   224,   354,   990,   991,   732,   225,
     794,   226,   990,   991,  1336,   473,   318,   406,   472,   759,
     327,  1073,   491,  1371,  1372,  1373,  1334,   389,  1014,   391,
    1338,   392,   398,  1424,  1425,  1426,   795,  1427,  1428,  1429,
     413,   445,   475,  -275,   473,  1023,   482,   493,   415,   474,
     788,   494,   495,   510,  -276,   512,   522,   523,   527,   535,
     455,   407,   540,   554,   541,   542,   558,   641,   543,   544,
     357,   629,  1340,   547,   545,   847,   592,   549,   355,   546,
     629,   629,   629,   629,   629,   629,   415,   185,   548,   550,
     551,   903,   552,   356,   553,   183,   555,   415,   587,   559,
     560,   796,   561,   562,   563,   564,     6,   831,   565,   566,
     184,   805,   806,   807,   808,   809,   472,   567,   568,   569,
     472,  1086,   574,   575,   576,   578,   579,   710,   815,   816,
     817,   818,   819,   580,   581,   583,   584,   590,   597,   601,
     599,  -277,   473,   608,   649,   617,   473,   646,   875,   876,
    1511,  1512,  1513,   643,   685,     6,   688,   712,   689,   690,
     691,   692,   997,   998,   693,   694,   736,   715,   629,   760,
    1002,   762,  1003,   241,   242,  1510,   474,   793,   822,   763,
     474,   803,   768,   733,   243,   733,   733,   733,   733,   733,
     769,   770,   472,   772,   771,   812,  -366,   759,   900,   829,
     185,   825,   932,   759,   833,   939,   834,   732,   183,   732,
     732,   732,   732,   732,   835,   837,   788,   415,   473,   840,
     841,   849,   879,   184,   880,   481,   683,  1087,  1088,   881,
     882,   883,   759,   759,   884,   759,   759,   759,   759,   887,
     890,  1362,  1090,  1363,   889,   904,   906,   910,   907,   913,
     472,   921,   933,   629,   930,   415,   415,   679,   934,   788,
     941,  1566,   629,  1008,  1415,  1416,   999,  1009,  1436,   641,
    1574,  1000,  1001,  1071,    64,  1417,   473,  1004,  1010,   641,
    1011,  1017,  1018,  1013,   810,  1445,  1446,  1447,   820,  1033,
    -284,  1030,  1020,  1027,  1045,  1037,  1039,  1074,  1077,  1093,
    1431,  1100,  1080,  1081,  1434,  1082,  1094,  1101,  1110,   250,
     251,   252,   253,   254,   710,   255,   256,   257,  1115,  1104,
    1116,  1249,   472,  1251,   920,  1255,  1252,  1023,   195,   196,
     197,   198,   199,  1248,  1253,   234,  1259,     6,  1267,  1276,
    1079,  1278,  1277,   286,   287,   288,   748,   629,   473,  1279,
     749,  1289,   329,   629,   629,   629,   629,   629,   629,  1097,
    1291,  1506,   415,  1294,  1365,  1367,  1369,  1292,  1509,  1297,
    1290,  1307,   733,  1293,  1514,  1515,  1298,  1085,  1266,   641,
    1295,  1308,   474,  1299,   805,   806,   807,   808,   809,  1309,
     759,  1310,  1300,   750,   939,  1311,   732,  1312,  1504,  1313,
    1422,  1423,  1424,  1425,  1426,  1314,  1427,  1428,  1429,  1315,
     472,  1333,  1337,  1341,  1348,  1342,   472,   472,  1358,  1352,
    1359,  1360,  1361,  1374,   759,  1379,  1377,  1378,  1538,   185,
    1380,  1541,  1375,  1381,  1382,  1384,   473,   183,  1388,  1345,
    1346,  1387,   473,   473,  1391,   751,   289,  1450,  1394,  1451,
     641,  1452,   184,  1395,  1453,  1454,  1455,  1396,  1397,  1400,
    1432,  1435,  1443,   592,   403,   283,  1556,  1437,  1539,  1461,
     474,  1439,   415,   415,   752,  1438,   474,   474,  1442,  1444,
    1462,  1565,  1464,  1448,  1449,  1463,  1465,  1466,   753,  1467,
    1468,  1469,  1474,   754,  1507,  1478,   360,  1502,   755,  1505,
     213,  1520,  1508,  1523,  1522,  1527,   472,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,  1542,   439,
    1526,  1528,   473,  1529,   443,  1531,  1532,  1533,   286,   287,
     288,   893,  1540,   631,  1097,   894,  1543,  1545,  1546,  1544,
    1547,  1548,  1552,   629,  1557,  1549,  1550,  1551,  1553,   592,
    1567,  1555,  1568,   592,  1558,  1569,   474,  1575,  1576,  1344,
     498,  1353,   360,   360,   500,   832,  1430,   286,   287,   288,
     620,  1091,   888,  1020,   621,   515,  1521,  1048,   895,   362,
    1351,   216,   217,   218,   367,  1316,   369,  1376,   371,   511,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   517,  1347,   589,     0,     0,
       0,     0,     0,     0,     0,   395,     0,   622,     0,   400,
     401,   402,     0,     0,     0,     0,     0,  1355,     0,     0,
       0,   289,     0,     0,   479,   219,   483,   484,   485,     0,
       0,     0,   216,   217,   218,   472,     0,   220,   221,     0,
       0,   570,     0,     0,     0,     0,     0,     0,     0,   896,
       0,     0,     0,     0,     0,   472,     0,   472,   585,   586,
     289,   473,   932,   897,     0,   593,     0,    70,   898,    71,
      72,    73,     0,   899,   222,   223,     0,   224,     0,     0,
     219,   473,   225,   473,   226,     0,   219,     0,   623,     0,
     444,     0,   220,   221,     0,   684,     0,    80,   220,   221,
       0,     0,   624,   788,   283,     0,     0,   625,     0,  1407,
       0,     0,   626,   266,   472,   474,   588,   474,   472,     0,
       0,   229,   759,   339,   340,     0,     0,   640,     6,   488,
     223,     0,   224,    82,    83,   222,   223,   225,   224,   226,
     473,     0,     0,   225,   473,   226,     0,     0,     0,     0,
      88,     0,     0,     0,     0,    90,     0,  1457,  1458,     0,
    1459,     0,  1460,     0,   341,     0,   290,    70,     0,    71,
      72,    73,    74,   227,   474,   723,   342,   228,   474,    77,
       0,   592,   229,    78,     0,   747,     0,     0,   939,     0,
      79,     0,     0,   232,     0,     0,   759,    80,   592,   592,
     592,     0,     0,     0,     0,     0,     0,     0,  1500,     0,
     571,     0,   472,    81,     0,     0,   270,     0,     0,     0,
       0,     0,     0,     0,    70,   343,    71,    72,    73,     0,
       0,     0,     0,    82,    83,     0,   297,     0,   473,    84,
       0,     0,     0,     0,     0,     0,   789,   344,   345,    87,
      88,     0,     0,    89,    80,    90,   321,     0,     0,   775,
     640,     0,     0,     0,     0,     0,   336,     0,     0,     0,
     266,     0,   474,     0,   592,   776,   347,     0,     0,     0,
       0,   592,   472,     0,   788,   788,   788,   592,   592,   777,
      82,    83,     0,     0,     0,     0,     0,     0,   827,     0,
       0,  1079,   778,   779,     0,     0,     0,    88,   473,     0,
       0,   390,    90,     0,   393,     0,     0,     0,   780,     0,
       0,     0,     0,   842,   843,   844,   845,     0,   848,  1561,
    1562,  1563,     0,  1564,    70,   187,    71,    72,    73,   716,
       0,   592,   474,     0,   592,     0,   734,     0,     0,   781,
       0,     0,   782,     0,     0,   783,     0,     0,     0,   409,
     410,  1332,     0,     0,    80,     0,     0,     0,     0,     0,
       0,   784,     0,   764,     0,   765,     0,   766,     0,   592,
     266,     0,     0,   785,     0,     0,   216,   217,   218,     0,
       0,     0,     0,     0,   592,   788,     0,   786,   938,   944,
      82,    83,     0,     0,   788,   446,     0,     0,     0,   945,
     946,   947,   948,   949,   950,   951,   952,    88,     0,     0,
       0,     0,    90,   490,     0,   492,   953,     0,   954,   955,
     956,   957,   958,   959,   960,   961,   962,   963,   964,   965,
     219,     0,   502,     0,   503,   504,   505,   506,   507,   508,
       0,     0,   220,   221,     0,     0,     0,     0,   966,     0,
       0,     0,   640,     0,     0,     0,   518,     0,     0,     0,
       0,     0,   640,     0,     0,   526,  1026,     0,   529,     0,
       0,     0,     0,     0,   335,     0,   537,     0,     0,   222,
     223,     0,   224,  1044,   846,     0,     0,   225,     0,   226,
       0,     0,   967,     0,  1049,  1050,  1051,  1052,  1053,  1054,
    1055,  1056,  1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,
    1065,  1066,  1067,  1068,  1069,   573,  1072,     0,     0,   577,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   968,   232,     0,   969,     0,   970,   971,   972,   973,
     974,   975,   976,   977,   978,   979,   980,     0,   981,   982,
       0,     0,   983,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   640,     0,     0,     0,     0,     0,     0,   602,
     243,     0,     0,     0,     0,     0,     0,   938,     0,     0,
    1332,  1332,  1332,  1332,  1332,   297,  1332,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   642,     0,     0,
       0,   237,   238,   239,   240,   241,   242,   297,     0,     0,
       0,     0,     0,     0,     0,   297,   243,   235,   236,   237,
     238,   239,   240,   241,   242,  1401,  1402,  1403,  1404,  1405,
       0,  1408,     0,   640,   243,  1258,     0,     0,     0,     0,
       0,     0,  1034,  1035,  1036,     0,  1038,     0,  1041,  1042,
    1043,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     761,     0,     0,     0,     0,  1332,  1332,  1332,  1332,  1332,
    1332,  1332,  1332,  1332,  1332,  1332,  1332,  1332,  1332,  1332,
    1332,  1332,  1332,  1332,     0,     0,     0,  1302,     0,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
       0,   255,   256,   257,     0,     0,     0,   596,     0,   409,
    1480,  1481,  1482,  1483,  1484,  1485,  1486,  1487,  1488,  1489,
    1490,  1491,  1492,  1493,  1494,  1495,  1496,  1497,  1498,     0,
       7,     8,     9,    10,  1332,    11,    12,    13,   247,   248,
     249,   250,   251,   252,   253,   254,     0,   255,   256,   257,
       0,     0,   813,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,     0,   255,   256,   257,     0,     0,
     297,  1305,     0,     0,     0,     0,     0,  1318,     0,  1534,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1319,
       0,  1332,     0,     0,  1320,     0,     0,   216,   217,   218,
       0,     0,    23,    24,     0,     0,     0,     0,    26,     0,
       0,     0,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,     0,   892,     0,
       0,     0,     0,     0,     0,     0,  1554,     0,    45,     0,
      46,     0,     0,     0,     0,  1321,     0,     0,     0,  1322,
       0,   219,  1323,     0,     0,     0,     0,    52,     0,     0,
     927,     0,     0,   220,   221,     7,     8,     9,    10,     0,
      11,    12,    13,   200,    68,     0,     0,     0,     0,     0,
       0,     0,  1324,     0,     0,  1325,  1326,  1327,     0,     0,
    1328,  1350,  1329,    62,     0,     0,  1330,     0,   297,     0,
     222,   223,  1317,   224,     0,     0,     0,     0,   225,     0,
     226,     0,    15,    69,     0,     0,   201,     0,   202,   203,
     204,    74,    75,     0,    20,    76,     0,     0,   205,    22,
       0,     0,    78,     0,   320,     0,     0,    23,    24,   206,
       0,     0,     0,    26,     0,  1383,   207,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,   208,     0,     0,     0,     0,     0,     0,     0,
       0,    44,     0,    45,     0,    46,     0,     0,     0,     0,
      47,     0,   209,   210,    50,     0,     0,    51,    84,     0,
       0,   938,    52,     0,     0,    53,    85,    86,    87,   211,
       0,     0,    89,     0,   212,     0,     0,     0,     0,   339,
     340,     0,  1092,     0,     0,     0,     0,    56,     0,     0,
      57,    58,    59,     0,     0,    60,     0,    61,    62,     0,
       0,    63,     0,     0,   652,   653,   654,    10,     0,    11,
     655,   656,    67,    68,     0,     0,   657,     0,     0,     0,
     341,     0,     0,    70,     0,    71,    72,    73,    74,     0,
       0,     0,   342,     0,     0,    77,     0,     0,     0,    78,
       0,  1501,     0,     0,     0,     0,    79,     0,   464,     0,
       0,   658,    69,    80,     0,    70,     0,    71,    72,    73,
      74,   465,     0,   659,    76,     0,     0,    77,   660,    81,
       0,    78,     0,     0,     0,     0,   661,   662,    79,     0,
       0,   343,     0,     0,     0,    80,     0,     0,     0,    82,
      83,     0,     0,     0,     0,    84,     0,     0,     0,  1269,
       0,    81,     0,   344,   345,    87,    88,     0,  1406,    89,
     663,    90,   664,     0,   665,     0,   346,     0,   466,   666,
       0,    82,    83,   667,     0,     0,   668,    84,     0,     0,
    1296,   669,   347,     0,   670,    85,    86,    87,    88,     0,
       0,    89,     0,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   671,     0,     0,   672,
     673,     0,     0,     0,   674,     0,   675,     0,     0,     0,
     676,     0,     0,  1470,  1471,  1472,  1473,     0,  1476,  1477,
    1117,  1118,  1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,
    1127,     0,  1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,
    1136,  1137,  1138,   927,     0,     0,     0,     0,     0,     0,
    1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,
    1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,     0,
       0,  1158,  1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,
    1167,  1168,  1169,  1170,  1171,  1172,     0,  1173,     0,  1174,
    1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,     0,  1183,
    1184,  1185,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1186,     0,     0,
       0,     0,     0,     0,  1187,  1188,  1189,     0,  1190,  1191,
    1192,  1193,  1194,  1195,  1196,  1197,  1198,  1199,  1200,  1201,
    1202,  1203,  1204,  1205,  1206,  1207,  1208,  1209,  1210,  1211,
    1212,  1213,  1214,  1215,  1216,  1217,  1218,  1219,  1220,  1221,
    1222,     0,     0,     0,  1223,  1224,  1225,  1226,  1227,  1228,
    1229,  1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,  1238,
    1239,  1240,  1241,  1242,  1243,  1440,  1244,  1245,  1117,  1118,
    1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,     0,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,     0,     0,     0,     0,  1370,     0,     0,  1139,  1140,
    1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,  1149,  1150,
    1151,  1152,  1153,  1154,  1155,  1156,  1157,     0,     0,  1158,
    1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,  1167,  1168,
    1169,  1170,  1171,  1172,     0,  1173,     0,  1174,  1175,  1176,
    1177,  1178,  1179,  1180,  1181,  1182,     0,  1183,  1184,  1185,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1186,     0,     0,     0,     0,
       0,     0,  1187,  1188,  1189,     0,  1190,  1191,  1192,  1193,
    1194,  1195,  1196,  1197,  1198,  1199,  1200,  1201,  1202,  1203,
    1204,  1205,  1206,  1207,  1208,  1209,  1210,  1211,  1212,  1213,
    1214,  1215,  1216,  1217,  1218,  1219,  1220,  1221,  1222,     0,
       0,     0,  1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,
    1231,  1232,  1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,
    1241,  1242,  1243,     0,  1244,  1245,     7,     8,     9,    10,
       0,    11,    12,    13,   496,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   235,   236,   237,   238,   239,   240,   241,   242,     0,
       0,     0,     0,    15,   341,  1530,     0,   201,   243,   202,
     203,   204,    74,     0,     0,    20,   342,     0,     0,   205,
      22,     0,     0,    78,     0,     0,     0,     0,    23,    24,
     206,     0,     0,     0,    26,     0,     0,   207,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,   208,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,    45,     0,    46,     0,     0,     0,
       0,    47,     0,   209,   210,    50,     0,     0,    51,    84,
       0,     0,     0,    52,     0,     0,    53,   344,   345,    87,
     211,     0,     0,    89,     0,   212,     7,     8,     9,    10,
       0,    11,    12,    13,    14,     0,     0,     0,    56,     0,
       0,    57,    58,    59,     0,     0,    60,     0,    61,    62,
       0,     0,    63,     0,     0,     0,     0,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,     0,   255,
     256,   257,     0,    15,     0,  1537,     0,    16,     0,    17,
      18,    19,     0,     0,     0,    20,     0,   744,   745,    21,
      22,     0,     0,     0,     0,     0,     0,     0,    23,    24,
      25,     0,     0,     0,    26,     0,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,    45,     0,    46,     0,     0,     0,
       0,    47,     0,    48,    49,    50,     0,     0,    51,     0,
       0,     0,     0,    52,     0,     0,    53,     0,     0,     0,
      54,     7,     8,     9,    10,    55,    11,    12,    13,    14,
     746,     0,     0,     0,     0,     0,     0,     0,    56,     0,
       0,    57,    58,    59,     0,     0,    60,     0,    61,    62,
       0,     0,    63,   236,   237,   238,   239,   240,   241,   242,
       0,     0,     0,     0,     0,     0,     0,     0,    15,   243,
       0,     0,    16,     0,    17,    18,    19,     0,     0,     0,
      20,     0,     0,     0,    21,    22,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    25,     0,     0,     0,    26,
       0,     0,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,    45,
       0,    46,     0,     0,     0,     0,    47,     0,    48,    49,
      50,     0,     0,    51,     0,     0,     0,     0,    52,     0,
       0,    53,     0,     0,     0,    54,     7,     8,     9,    10,
      55,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,    57,    58,    59,     0,
       0,    60,     0,    61,    62,   437,     0,    63,     0,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,     0,
     255,   256,   257,    15,   442,     0,     0,    16,     0,    17,
      18,    19,     0,     0,     0,    20,     0,     0,     0,    21,
      22,     0,     0,     0,     0,     0,     0,     0,    23,    24,
      25,     0,     0,     0,    26,     0,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,    45,     0,    46,     0,     0,     0,
       0,    47,     0,    48,    49,    50,     0,     0,    51,     0,
       0,     0,     0,    52,     0,     0,    53,     0,     0,     0,
      54,     7,     8,     9,    10,    55,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,    56,     0,
       0,    57,    58,    59,     0,     0,    60,     0,    61,    62,
       0,     0,    63,     0,     0,     0,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,    15,   722,
       0,     0,    16,   243,    17,    18,    19,     0,     0,     0,
      20,     0,     0,     0,    21,    22,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    25,     0,     0,     0,    26,
       0,     0,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,    45,
       0,    46,     0,     0,     0,     0,    47,     0,    48,    49,
      50,     0,     0,    51,     0,     0,     0,     0,    52,     0,
       0,    53,     0,     0,     0,    54,     7,     8,     9,    10,
      55,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,    57,    58,    59,     0,
       0,    60,     0,    61,    62,     0,     0,    63,     0,     0,
     594,     0,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,    15,   255,   256,   257,    16,     0,    17,
      18,    19,     0,     0,     0,    20,     0,     0,     0,    21,
      22,     0,     0,     0,     0,     0,     0,     0,    23,    24,
      25,     0,     0,     0,    26,     0,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,    45,     0,    46,     0,     0,     0,
       0,    47,     0,    48,    49,    50,     0,     0,    51,     0,
       0,     0,     0,    52,     0,     0,    53,     0,     0,     0,
      54,     7,     8,     9,    10,    55,    11,    12,    13,    14,
     935,     0,     0,     0,     0,     0,     0,     0,    56,     0,
       0,    57,    58,    59,     0,     0,    60,     0,    61,    62,
       0,     0,    63,     0,     0,     0,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,    15,     0,
       0,     0,    16,   243,    17,    18,    19,     0,     0,     0,
      20,     0,     0,     0,    21,    22,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    25,     0,     0,     0,    26,
       0,     0,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,    45,
       0,    46,     0,     0,     0,     0,    47,     0,    48,    49,
      50,     0,     0,    51,     0,     0,     0,     0,    52,     0,
       0,    53,     0,     0,     0,    54,     7,     8,     9,    10,
      55,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,    57,    58,    59,     0,
       0,    60,     0,    61,    62,  1070,     0,    63,     0,   940,
       0,     0,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,    15,   255,   256,   257,    16,     0,    17,
      18,    19,     0,     0,     0,    20,     0,     0,     0,    21,
      22,     0,     0,     0,     0,     0,     0,     0,    23,    24,
      25,     0,     0,     0,    26,     0,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,    45,     0,    46,     0,     0,     0,
       0,    47,     0,    48,    49,    50,     0,     0,    51,     0,
       0,     0,     0,    52,     0,     0,    53,     0,     0,     0,
      54,     7,     8,     9,    10,    55,    11,    12,    13,    14,
    1349,     0,     0,     0,     0,     0,     0,     0,    56,     0,
       0,    57,    58,    59,     0,     0,    60,     0,    61,    62,
       0,     0,    63,     0,     0,     0,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,    15,     0,
       0,     0,    16,   243,    17,    18,    19,     0,     0,     0,
      20,     0,     0,     0,    21,    22,     0,     0,     0,     0,
       0,     0,     0,    23,    24,    25,     0,     0,     0,    26,
       0,     0,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,    45,
       0,    46,     0,     0,     0,     0,    47,     0,    48,    49,
      50,     0,     0,    51,     0,     0,     0,     0,    52,     0,
       0,    53,     0,     0,     0,    54,     7,     8,     9,    10,
      55,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,    57,    58,    59,     0,
       0,    60,     0,    61,    62,  1499,     0,    63,  1280,     0,
       0,     0,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,    15,   255,   256,   257,    16,     0,    17,
      18,    19,     0,     0,     0,    20,     0,     0,     0,    21,
      22,     0,     0,     0,     0,     0,     0,     0,    23,    24,
      25,     0,     0,     0,    26,     0,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,    45,     0,    46,   483,   484,   485,
       0,    47,     0,    48,    49,    50,     0,     0,    51,     0,
       0,     0,     0,    52,     0,     0,    53,     0,     0,     0,
      54,   652,   653,   654,    10,    55,    11,   655,   656,    67,
      68,     0,     0,  1047,   486,     0,   487,     0,    56,     0,
       0,    57,    58,    59,     0,     0,    60,     0,    61,    62,
       0,   219,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   220,   221,   464,     0,     0,   658,    69,
       0,     0,    70,     0,    71,    72,    73,    74,   465,     0,
     659,    76,     0,     0,    77,   660,     0,     0,    78,     0,
       0,     0,     0,   661,   662,    79,     0,     0,     0,     0,
     488,   223,    80,   224,     0,     0,     0,     0,   225,     0,
     226,     0,     0,     0,     0,   513,   514,     0,    81,     0,
       0,     0,     0,     0,     0,     0,     0,   663,     0,   664,
       0,   665,     0,     0,   489,   466,   666,     0,    82,    83,
     667,     0,     0,   668,    84,     0,     0,     0,   669,     0,
       0,   670,    85,    86,    87,    88,   341,     0,    89,    70,
      90,    71,    72,    73,    74,     0,     0,     0,   342,     0,
       0,    77,     0,   671,     0,    78,   672,   673,     0,     0,
       0,   674,    79,   675,     0,     0,     0,   676,     0,    80,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
       0,     0,     0,     0,     0,    81,     0,   243,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   343,     0,     0,
       0,     0,     0,     0,     0,    82,    83,     0,     0,     0,
       0,    84,    70,     0,    71,    72,    73,     0,     0,   344,
     345,    87,    88,     0,   265,    89,     0,    90,   235,   236,
     237,   238,   239,   240,   241,   242,     0,     0,     0,     0,
       0,     0,    80,     0,     0,   243,     0,     0,   347,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   266,     0,
       0,     0,     0,     0,     0,     0,   243,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,    82,    83,
       0,     0,     0,     0,   243,     0,   235,   236,   237,   238,
     239,   240,   241,   242,     0,    88,     0,     0,     0,     0,
      90,     0,   697,   243,     0,     0,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,   255,   256,
     257,   698,   235,   236,   237,   238,   239,   240,   241,   242,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   243,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   243,     0,     0,
       0,     0,     0,     0,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,     0,   255,   256,   257,   582,
       0,     0,     0,     0,     0,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,     0,   255,   256,   257,
     598,     0,     0,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,     0,   255,   256,   257,   686,     0,
       0,     0,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,     0,   255,   256,   257,   767,   235,   236,
     237,   238,   239,   240,   241,   242,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   243,     0,     0,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,     0,
     255,   256,   257,   911,     0,     0,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,   255,   256,
     257,  1028,   235,   236,   237,   238,   239,   240,   241,   242,
       0,     0,   216,   217,   218,     0,   216,   217,   218,   243,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   243,   852,   853,
     854,   855,   856,   857,   858,   859,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   860,  1409,  1410,  1411,  1412,
    1413,  1414,  1415,  1416,     0,     0,   219,     0,     0,     0,
     219,     0,     0,  1417,     0,     0,     0,     0,   220,   221,
       0,     0,   220,   221,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,     0,   255,   256,   257,  1301,
    1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,     0,     0,
       0,     0,     0,     0,     0,   222,   223,  1417,   224,   222,
     223,     0,   224,   225,     0,   226,     0,   225,     0,   226,
       0,     0,     0,     0,     0,     0,  1303,     0,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   501,
     255,   256,   257,     0,     0,     0,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,   255,   256,
     257,     0,     0,     0,   861,   862,   863,   864,   865,   866,
     867,   868,   869,   870,   871,     0,   872,   873,   874,     0,
    1535,     0,  1418,  1419,  1420,  1421,     0,     0,  1422,  1423,
    1424,  1425,  1426,     0,  1427,  1428,  1429,    -2,     0,     0,
       0,     0,     0,     0,     0,     0,  1410,  1411,  1412,  1413,
    1414,  1415,  1416,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1417,     0,     0,     0,  1418,  1419,  1420,  1421,
       0,     0,  1422,  1423,  1424,  1425,  1426,     0,  1427,  1428,
    1429,     0,     0,     0,   105,     0,   106,     0,     0,   107,
     108,     0,     0,     0,     0,     0,     0,   109,   110,     0,
       0,     0,     0,     0,     0,     0,   111,     0,   112,   113,
     114,   115,     0,     0,     0,   116,     0,     0,     0,     0,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,   126,   127,   128,   129,     0,     0,     0,     0,     0,
     130,   131,    67,    68,   132,   133,   462,     0,   463,   134,
       0,     0,     0,     0,     0,   135,   136,     0,   137,     0,
       0,     0,  1419,  1420,  1421,     0,   138,  1422,  1423,  1424,
    1425,  1426,     0,  1427,  1428,  1429,     0,     0,   464,     0,
       0,     0,    69,     0,     0,    70,     0,    71,    72,    73,
      74,   465,     0,     0,    76,     0,     0,    77,     0,     0,
       0,    78,   237,   238,   239,   240,   241,   242,    79,     0,
       0,     0,     0,     0,     0,    80,     0,   243,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,     0,     0,
       0,    81,     0,   243,  1411,  1412,  1413,  1414,  1415,  1416,
       0,     0,     0,     0,     0,     0,     0,     0,   466,  1417,
       0,    82,    83,     0,     0,     0,     0,    84,     0,   237,
     238,   239,   240,   241,   242,    85,    86,    87,    88,     0,
       0,    89,     0,    90,   243,  1411,  1412,  1413,  1414,  1415,
    1416,     0,     0,     0,     0,     0,   467,     0,     0,     0,
    1417,   468,  1411,  1412,  1413,  1414,  1415,  1416,     0,     0,
       0,  1411,  1412,  1413,  1414,  1415,  1416,  1417,     0,     0,
       0,     0,     0,     0,     0,     0,  1417,   239,   240,   241,
     242,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     243,     0,     0,     0,     0,     0,     0,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,   255,   256,
     257,     0,     0,     0,   246,   247,   248,   249,   250,   251,
     252,   253,   254,     0,   255,   256,   257,     0,     0,  1419,
    1420,  1421,     0,     0,  1422,  1423,  1424,  1425,  1426,     0,
    1427,  1428,  1429,  1413,  1414,  1415,  1416,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1417,   248,   249,   250,
     251,   252,   253,   254,     0,   255,   256,   257,     0,     0,
       0,  1420,  1421,     0,     0,  1422,  1423,  1424,  1425,  1426,
       0,  1427,  1428,  1429,     0,     0,     0,     0,     0,  1421,
     305,     0,  1422,  1423,  1424,  1425,  1426,     0,  1427,  1428,
    1429,  1422,  1423,  1424,  1425,  1426,   775,  1427,  1428,  1429,
       0,     0,     0,   248,   249,   250,   251,   252,   253,   254,
       0,   255,   256,   257,     0,     0,     0,     0,     0,     0,
       0,   105,     0,   106,     0,     0,   777,   108,     0,     0,
       0,     0,     0,     0,   109,   110,     0,     0,     0,   778,
     779,     0,     0,     0,     0,   112,   113,   114,     0,     0,
       0,     0,   305,     0,     0,   780,     0,   300,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1422,  1423,  1424,  1425,  1426,     0,  1427,  1428,  1429,
       0,   124,     0,     0,     0,     0,   781,     0,     0,   782,
       0,   129,   783,   105,     0,   106,     0,   130,     0,   108,
       0,   132,   133,   699,   700,   701,   109,   110,   784,     0,
       0,     0,     0,   136,     0,   137,     0,   112,   299,   114,
     785,     0,     0,     0,     0,     0,     0,     0,     0,   300,
       0,     0,     0,     0,   786,     0,     0,     0,     0,     0,
       0,     0,   399,    67,    68,     0,     0,    70,     0,    71,
      72,    73,     0,   124,     0,     0,     0,     0,     0,    77,
       0,     0,     0,   129,     0,     0,     0,     0,     0,   130,
      79,  1040,    67,    68,   133,     0,     0,    80,     0,     0,
       0,     0,     0,    69,     0,   136,    70,   137,    71,    72,
      73,    74,    75,    81,     0,    76,     0,     0,    77,     0,
       0,     0,    78,     0,     0,     0,     0,     0,     0,    79,
       0,     0,    69,    82,    83,    70,    80,    71,    72,    73,
      74,    75,     0,     0,    76,     0,     0,    77,     0,     0,
      88,    78,    81,    89,     0,    90,     0,     0,    79,     0,
       0,     0,     0,     0,     0,    80,     0,     0,     0,     0,
       0,     0,    82,    83,   216,   217,   218,     0,    84,     0,
       0,    81,     0,  1475,    67,    68,    85,    86,    87,    88,
       0,     0,    89,     0,    90,     0,     0,     0,     0,     0,
       0,    82,    83,     0,     0,     0,     0,    84,     0,     0,
       0,     0,   699,   700,   701,    85,    86,    87,    88,     0,
       0,    89,     0,    90,    69,     0,     0,    70,   219,    71,
      72,    73,    74,    75,     0,     0,    76,     0,     0,    77,
     220,   221,     0,    78,     0,     0,     0,     0,     0,     0,
      79,     0,     0,     0,     0,     0,    70,    80,    71,    72,
      73,   702,   703,     0,     0,     0,     0,     0,    77,     0,
       0,     0,     0,    81,     0,     0,     0,   222,   223,    79,
     224,     0,     0,     0,     0,   225,    80,   226,     0,     0,
       0,     0,     0,    82,    83,     0,     0,     0,  1284,    84,
       0,     0,    81,   216,   217,   218,     0,    85,    86,    87,
      88,     0,     0,    89,     0,    90,    67,    68,     0,     0,
     462,     0,    82,    83,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   704,     0,     0,    88,
       0,     0,    89,     0,    90,    67,    68,     0,     0,   801,
       0,     0,   464,     0,     0,     0,    69,   219,     0,    70,
       0,    71,    72,    73,    74,   465,     0,     0,    76,   220,
     221,    77,     0,     0,     0,    78,     0,     0,     0,     0,
       0,   464,    79,     0,     0,    69,     0,     0,    70,    80,
      71,    72,    73,    74,   465,     0,     0,    76,     0,     0,
      77,     0,     0,     0,    78,    81,   222,  1281,  1282,  1283,
       0,    79,     0,     0,   225,     0,   226,     0,    80,     0,
       0,     0,   466,     0,     0,    82,    83,  1284,     0,     0,
       0,    84,  1285,     0,    81,     0,     0,    67,    68,    85,
      86,    87,    88,     0,     0,    89,     0,    90,     0,     0,
       0,   466,     0,     0,    82,    83,     0,     0,     0,     0,
      84,    70,     0,    71,    72,    73,    67,    68,    85,    86,
      87,    88,     0,   464,    89,     0,    90,    69,     0,     0,
      70,     0,    71,    72,    73,    74,   465,     0,     0,    76,
       0,    80,    77,     0,     0,     0,    78,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    69,   266,     0,    70,
      80,    71,    72,    73,    74,    75,     0,     0,    76,     0,
       0,    77,     0,     0,     0,    78,    81,    82,    83,     0,
       0,     0,    79,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,   466,    88,     0,    82,    83,     0,    90,
       0,     0,    84,    67,    68,    81,     0,     0,     0,     0,
      85,    86,    87,    88,     0,     0,    89,     0,    90,     0,
       0,     0,   188,     0,     0,    82,    83,    67,    68,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    69,     0,    89,    70,    90,    71,    72,
      73,    74,     0,     0,     0,    76,     0,     0,    77,     0,
       0,     0,    78,     0,     0,     0,     0,    69,     0,    79,
      70,     0,    71,    72,    73,    74,    80,     0,     0,    76,
       0,     0,    77,     0,     0,     0,    78,     0,     0,     0,
       0,     0,    81,    79,     0,     0,     0,     0,     0,     0,
      80,   216,   217,   218,     0,     0,     0,     0,     0,   611,
       0,     0,    82,    83,    67,     0,    81,     0,    84,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
       0,     0,    89,     0,    90,     0,    82,    83,   486,     0,
     487,     0,    84,   177,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    69,   219,    89,    70,    90,    71,
      72,    73,    74,   524,     0,     0,    76,   220,   221,    77,
       0,     0,     0,    78,     0,     0,     0,     0,     0,     0,
      79,     0,     0,   178,     0,     0,    70,    80,    71,    72,
      73,    74,  1005,     0,     0,   179,     0,     0,    77,     0,
       0,     0,    78,    81,   222,   223,     0,   224,     0,    79,
       0,     0,   225,     0,   226,     0,    80,     0,     0,     0,
       0,     0,     0,    82,    83,     0,     0,     0,     0,    84,
     177,     0,    81,     0,     0,     0,     0,    85,    86,    87,
      88,     0,     0,    89,     0,    90,     0,     0,     0,     0,
       0,     0,    82,    83,    67,     0,     0,     0,    84,     0,
       0,     0,   216,   217,   218,     0,   180,   181,    87,    88,
     178,     0,    89,    70,    90,    71,    72,    73,    74,     0,
       0,     0,   179,     0,     0,    77,     0,     0,     0,    78,
       0,     0,     0,     0,    69,     0,    79,    70,     0,    71,
      72,    73,    74,    80,     0,     0,    76,     0,     0,    77,
       0,     0,     0,    78,     0,     0,   219,     0,     0,    81,
      79,     0,   216,   217,   218,     0,     0,    80,   220,   221,
       0,     0,     0,     0,     0,     0,   216,   217,   218,    82,
      83,     0,     0,    81,     0,    84,     0,     0,     0,     0,
     216,   217,   218,   180,   181,    87,    88,     0,     0,    89,
       0,    90,     0,    82,    83,   222,   223,     0,   224,    84,
       0,     0,     0,   225,     0,   226,   219,    85,    86,    87,
      88,     0,     0,    89,     0,    90,  1284,     0,   220,   221,
     219,  1364,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   220,   221,   219,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   220,   221,     0,     0,
       0,     0,     0,     0,     0,   222,   223,     0,   224,     0,
       0,     0,     0,   225,     0,   226,     0,     0,     0,   222,
     223,     0,   224,     0,     0,     0,  1284,   225,     0,   226,
       0,  1366,     0,   222,   223,     0,   224,     0,     0,     0,
    1284,   225,   105,   226,   106,  1368,     0,   107,   108,     0,
       0,     0,     0,     0,     0,   109,   110,     0,   294,     0,
       0,     0,     0,     0,   111,     0,   112,   113,   114,   115,
       0,     0,     0,   116,     0,     0,     0,     0,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,   126,
     127,   128,   129,     0,     0,   105,     0,   106,   130,   131,
     107,   108,   132,   133,     0,     0,     0,   134,   109,   110,
       0,     0,     0,   135,   136,     0,   137,   111,     0,   112,
     113,   114,   115,     0,   138,     0,   116,     0,     0,     0,
       0,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   695,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
       0,     0,   126,   127,   128,   129,     0,     0,   105,     0,
     106,   130,   131,   107,   108,   132,   133,     0,     0,     0,
     134,   109,   110,     0,     0,     0,   135,   136,     0,   137,
     111,     0,   112,   113,   114,   115,     0,   138,     0,   116,
       0,     0,     0,     0,   117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   877,     0,     0,     0,
       0,     0,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,   126,   127,   128,   129,     0,
       0,   105,     0,   106,   130,   131,   107,   108,   132,   133,
       0,     0,     0,   134,   109,   110,     0,     0,     0,   135,
     136,     0,   137,   111,     0,   112,   113,   114,   115,     0,
     138,     0,   116,     0,     0,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   922,
       0,     0,     0,     0,     0,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,     0,   126,   127,
     128,   129,     0,     0,   105,     0,   106,   130,   131,   107,
     108,   132,   133,     0,     0,     0,   134,   109,   110,     0,
       0,     0,   135,   136,     0,   137,   111,     0,   112,   113,
     114,   115,     0,   138,     0,   116,     0,     0,     0,     0,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1029,     0,     0,     0,     0,     0,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,   126,   127,   128,   129,     0,     0,   105,     0,   106,
     130,   131,   107,   108,   132,   133,     0,     0,     0,   134,
     109,   110,     0,     0,     0,   135,   136,     0,   137,   111,
       0,   112,   113,   114,   115,     0,   138,     0,   116,     0,
       0,     0,     0,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1083,     0,     0,     0,     0,
       0,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,     0,   126,   127,   128,   129,     0,     0,
     105,     0,   106,   130,   131,   107,   108,   132,   133,     0,
       0,     0,   134,   109,   110,     0,     0,     0,   135,   136,
       0,   137,   111,     0,   112,   113,   114,   115,     0,   138,
       0,   116,   216,   217,   218,     0,   117,   891,     0,     0,
       0,    70,     0,    71,    72,    73,     0,     0,  1306,     0,
       0,     0,     0,   265,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,   126,   127,   128,
     129,    80,     0,     0,     0,     0,   130,   131,     0,     0,
     132,   133,     0,     0,     0,   134,   219,   266,     0,     0,
       0,   135,   136,    70,   137,    71,    72,    73,   220,   221,
       0,     0,   138,     0,     0,     0,     0,    82,    83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1456,     0,    80,    88,     0,     0,     0,     0,    90,
       0,     0,     0,     0,     0,   222,   223,     0,   224,   266,
       0,     0,   105,   225,   106,   226,     0,     0,   108,     0,
       0,     0,   176,     0,     0,   109,   110,     0,     0,    82,
      83,     0,     0,     0,     0,     0,   112,   299,   114,     0,
       0,     0,     0,   116,     0,     0,    88,     0,   300,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   124,     0,   193,     0,     0,     0,     0,     0,
       0,     0,   129,     0,     0,     0,     0,     0,   130,     0,
       0,     0,     0,   133,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,   105,   137,   106,     0,     0,
     107,   108,     0,     0,     0,     0,     0,     0,   109,   110,
       0,  -155,     0,     0,     0,     0,     0,   111,     0,   112,
     113,   114,   115,     0,     0,     0,   116,     0,     0,     0,
       0,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
       0,     0,   126,   127,   128,   129,     0,     0,   105,     0,
     106,   130,   131,     0,   108,   132,   133,     0,     0,     0,
     134,   109,   110,     0,     0,     0,   135,   136,     0,   137,
       0,     0,   112,   113,   114,   105,     0,   106,     0,   116,
       0,   108,     0,     0,   300,     0,     0,     0,   109,   110,
     105,     0,   106,     0,     0,     0,   108,     0,     0,   112,
     299,   114,     0,   109,   110,     0,     0,     0,   124,     0,
       0,   300,     0,     0,   112,   299,   114,     0,   129,     0,
       0,     0,     0,     0,   130,     0,   300,     0,   132,   133,
       0,     0,     0,     0,     0,   124,   311,     0,     0,   135,
     136,     0,   137,     0,     0,   129,     0,     0,     0,     0,
     124,   130,     0,     0,     0,     0,   133,     0,     0,     0,
     129,     0,     0,     0,     0,     0,   130,   136,     0,   137,
       0,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   136,     0,   137
};

static const yytype_int16 yycheck[] =
{
       1,    61,   757,   320,    92,   495,   113,   466,    44,   737,
     132,   132,   714,   142,    75,   149,    44,   151,   152,   153,
     154,   935,   156,   298,   158,   663,   160,   464,   482,   589,
     515,    44,   608,   184,   142,    10,   495,    15,    13,    15,
      75,   142,   176,    59,   148,   800,    15,    13,     6,   486,
       8,    15,    15,   187,   188,     0,    15,   494,   333,   193,
     194,    62,   148,   148,   151,   148,   170,   627,   166,   167,
     720,    76,    76,   275,   276,   277,   278,   279,   638,   166,
     156,   167,   167,   617,   167,   165,    81,    82,    83,   148,
      91,    92,   147,    88,   149,   590,   151,    76,    99,   749,
     750,   147,   752,   753,   754,   755,   142,    33,   167,   148,
     126,   108,   109,   110,   142,   112,   113,   114,   165,   165,
     117,    98,    33,   147,    10,    11,    12,   124,   167,   142,
     148,   148,   129,   130,   151,   132,   133,   134,   776,   136,
     137,   165,   147,   147,   165,   150,   150,   148,   149,   167,
     151,   152,   153,   154,   147,   156,   149,   158,   151,   160,
     619,   724,   148,   726,   727,   728,   729,   730,   147,   298,
     148,   150,   260,   261,   165,   176,    13,    33,    15,   148,
      17,   167,   165,   184,   501,   160,   187,   188,   276,   277,
     298,   167,   193,   194,   160,   165,   256,   298,   758,   148,
     329,   165,   165,   156,   333,   356,   165,   697,   165,   167,
     148,   528,    76,   208,   209,   210,   211,   165,   167,   280,
      33,   329,   717,    60,   165,   333,   721,   113,   329,   167,
     231,   165,   333,   148,   810,   165,   796,   797,   164,   165,
     166,   151,   165,   445,   820,   280,   473,   449,   450,   451,
     452,   453,   167,   164,   165,   166,   166,   907,   392,   260,
     261,   463,   298,   165,   150,   467,   468,   165,   148,    33,
     298,   266,   165,   758,   275,   276,   277,   278,   279,   280,
     148,  1009,   343,   147,   285,   298,   150,   167,   148,   166,
     167,   941,    33,   329,   150,   290,   151,   333,   148,   167,
     165,   329,   299,   300,   141,   333,   760,   167,   305,   165,
     166,   166,   148,   148,   165,   292,   329,   167,   155,   320,
     333,   165,   148,   160,     6,   147,     8,   149,   165,   151,
     647,   167,   167,    13,   793,    15,   165,    17,   148,   156,
     777,   167,   165,   903,   920,   158,   159,   160,   161,   162,
     913,   164,   165,   166,   148,   356,    13,   167,    15,   165,
      17,   851,    10,    11,    12,    13,   148,  1005,   148,    17,
     148,   646,   165,   167,   148,    10,    11,    12,   355,   696,
      60,   165,   149,  1111,   151,   167,   613,   167,     6,   167,
       8,   392,   851,   167,   158,   159,   160,   161,   162,   601,
     164,   165,   166,    60,   465,   466,   633,   634,   635,   636,
     637,   412,    60,   148,   148,   991,   166,   167,   903,   160,
     161,   162,   165,   164,   165,   166,   165,   166,   923,    64,
     465,   466,   167,   167,   495,  1349,    64,    65,    10,    11,
      12,    76,    77,   165,   445,   165,    33,   165,   449,   450,
     451,   452,   453,  1013,  1014,   147,   156,   149,   165,   151,
     495,   141,   463,   524,   165,   113,   467,   468,   166,   167,
    1004,   472,   165,   165,   475,   155,   512,   165,   113,   114,
     160,   116,   709,   147,   141,   165,   121,   482,   123,   144,
     145,   146,    64,   141,   495,   165,   493,   165,   155,   150,
     501,   472,   165,   160,    76,    77,   165,   155,   150,  1264,
     150,   512,   160,   165,   166,   167,  1011,   646,   165,   166,
     167,   165,  1017,  1018,   525,   166,   167,   528,   165,   590,
     150,   147,   167,   149,   150,   151,   165,   166,   646,   147,
     148,   113,   114,   165,   116,   646,   165,   166,   525,   121,
     611,   123,   165,   166,   167,   590,   165,   167,   619,   536,
     165,   878,   539,   114,   115,   116,  1100,   165,   795,   165,
    1104,   165,   165,   160,   161,   162,   611,   164,   165,   166,
     151,   160,   166,   166,   619,   812,   150,    48,   589,   590,
     591,   148,   165,   147,   166,   156,   165,   165,   165,   149,
     601,   148,   168,   148,   167,   167,   148,   608,   167,   167,
     646,   612,  1107,   157,   167,   675,   617,   157,   646,   167,
     621,   622,   623,   624,   625,   626,   627,   663,   167,   167,
     167,  1333,   167,   646,   167,   663,   167,   638,    15,   167,
     167,   612,   167,   167,   167,   167,   647,   648,   167,   167,
     663,   622,   623,   624,   625,   626,   717,   167,   167,   167,
     721,   888,   157,   167,   167,   167,   167,   703,   895,   896,
     897,   898,   899,   157,   167,   167,   167,   165,   167,   160,
     167,   166,   717,   166,   150,   167,   721,   165,   685,   686,
    1445,  1446,  1447,   168,   167,   696,   147,   165,   148,   148,
     148,   148,   762,   763,   148,   148,   165,   149,   709,   150,
     770,   165,   772,    22,    23,  1443,   717,    48,   170,   165,
     721,   160,   167,   724,    33,   726,   727,   728,   729,   730,
     167,   165,   793,   165,   167,   160,   147,   714,   709,    76,
     776,    48,   743,   720,   165,   746,   156,   724,   776,   726,
     727,   728,   729,   730,   156,   156,   757,   758,   793,   156,
     165,   167,    10,   776,    10,   760,  1256,   889,   889,    10,
      10,    10,   749,   750,    10,   752,   753,   754,   755,   149,
     148,  1276,   889,  1278,   157,   149,   167,   167,   160,   160,
     851,   167,   149,   794,   168,   796,   797,  1256,   149,   800,
     160,  1556,   803,   165,    22,    23,   167,   147,  1342,   810,
    1565,   167,   167,   873,     2,    33,   851,   167,   170,   820,
     165,   165,   165,   794,   166,  1359,  1360,  1361,   166,   830,
     166,   150,   803,   167,   167,   165,   165,   148,   148,   151,
    1335,   167,   148,   148,  1339,   148,   160,   165,   168,   158,
     159,   160,   161,   162,   890,   164,   165,   166,   149,   167,
     149,   148,   923,    10,   166,     4,   167,  1094,    56,    57,
      58,    59,    60,   168,   170,    63,   148,   878,    48,   165,
     881,   165,   170,    10,    11,    12,    13,   888,   923,   170,
      17,   147,   889,   894,   895,   896,   897,   898,   899,   900,
     167,  1435,   903,  1037,  1281,  1282,  1283,   157,  1442,   167,
     148,    10,   913,   157,  1448,  1449,   167,   888,  1006,   920,
     157,    10,   923,   157,   895,   896,   897,   898,   899,   149,
     907,    10,   167,    60,   935,   167,   913,    10,  1433,    10,
     158,   159,   160,   161,   162,    10,   164,   165,   166,   149,
    1011,   148,   165,   170,   168,   167,  1017,  1018,   168,   170,
     167,   167,   167,    15,   941,   167,   165,   165,  1502,  1005,
     165,  1505,  1289,   167,   165,   167,  1011,  1005,   149,  1113,
    1114,   148,  1017,  1018,   167,   112,   113,  1364,   165,  1366,
     991,  1368,  1005,   156,  1371,  1372,  1373,   156,   156,   156,
     165,   167,   147,  1004,   192,  1006,  1540,   168,  1503,   149,
    1011,   167,  1013,  1014,   141,   168,  1017,  1018,   167,   167,
      10,  1555,    10,   167,   167,   149,    10,   149,   155,   149,
      10,   149,   165,   160,    15,   167,  1037,   167,   165,   167,
      61,   148,   168,   148,   167,   157,  1107,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   168,   257,
     167,   157,  1107,   157,   262,   167,   167,   157,    10,    11,
      12,    13,   167,    15,  1085,    17,    10,   149,    10,   167,
      10,   149,   167,  1094,   149,   165,   165,   165,   165,  1100,
     149,   167,    10,  1104,   167,   149,  1107,   167,   149,  1112,
     298,  1259,  1113,  1114,   310,   649,  1333,    10,    11,    12,
      13,   890,   703,  1094,    17,   333,  1462,   851,    60,   150,
    1256,    10,    11,    12,   155,  1085,   157,  1290,   159,   327,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   333,  1223,   411,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   186,    -1,    60,    -1,   190,
     191,   192,    -1,    -1,    -1,    -1,    -1,  1265,    -1,    -1,
      -1,   113,    -1,    -1,    11,    64,    10,    11,    12,    -1,
      -1,    -1,    10,    11,    12,  1256,    -1,    76,    77,    -1,
      -1,   389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
      -1,    -1,    -1,    -1,    -1,  1276,    -1,  1278,   406,   407,
     113,  1256,  1223,   155,    -1,   413,    -1,    54,   160,    56,
      57,    58,    -1,   165,   113,   114,    -1,   116,    -1,    -1,
      64,  1276,   121,  1278,   123,    -1,    64,    -1,   141,    -1,
     271,    -1,    76,    77,    -1,  1256,    -1,    84,    76,    77,
      -1,    -1,   155,  1264,  1265,    -1,    -1,   160,    -1,  1329,
      -1,    -1,   165,   100,  1335,  1276,   155,  1278,  1339,    -1,
      -1,   160,  1259,    10,    11,    -1,    -1,   475,  1289,   113,
     114,    -1,   116,   120,   121,   113,   114,   121,   116,   123,
    1335,    -1,    -1,   121,  1339,   123,    -1,    -1,    -1,    -1,
     137,    -1,    -1,    -1,    -1,   142,    -1,  1377,  1378,    -1,
    1380,    -1,  1382,    -1,    51,    -1,   150,    54,    -1,    56,
      57,    58,    59,   151,  1335,   523,    63,   155,  1339,    66,
      -1,  1342,   160,    70,    -1,   533,    -1,    -1,  1349,    -1,
      77,    -1,    -1,    62,    -1,    -1,  1333,    84,  1359,  1360,
    1361,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1428,    -1,
     391,    -1,  1433,   100,    -1,    -1,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,   112,    56,    57,    58,    -1,
      -1,    -1,    -1,   120,   121,    -1,   105,    -1,  1433,   126,
      -1,    -1,    -1,    -1,    -1,    -1,   594,   134,   135,   136,
     137,    -1,    -1,   140,    84,   142,   125,    -1,    -1,    17,
     608,    -1,    -1,    -1,    -1,    -1,   135,    -1,    -1,    -1,
     100,    -1,  1433,    -1,  1435,    33,   163,    -1,    -1,    -1,
      -1,  1442,  1503,    -1,  1445,  1446,  1447,  1448,  1449,    47,
     120,   121,    -1,    -1,    -1,    -1,    -1,    -1,   646,    -1,
      -1,  1462,    60,    61,    -1,    -1,    -1,   137,  1503,    -1,
      -1,   180,   142,    -1,   183,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,   671,   672,   673,   674,    -1,   676,  1549,
    1550,  1551,    -1,  1553,    54,   165,    56,    57,    58,   520,
      -1,  1502,  1503,    -1,  1505,    -1,   527,    -1,    -1,   107,
      -1,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,   228,
     229,  1095,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,   129,    -1,   554,    -1,   556,    -1,   558,    -1,  1540,
     100,    -1,    -1,   141,    -1,    -1,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,  1555,  1556,    -1,   155,   746,     6,
     120,   121,    -1,    -1,  1565,   274,    -1,    -1,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,   137,    -1,    -1,
      -1,    -1,   142,   292,    -1,   294,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      64,    -1,   311,    -1,   313,   314,   315,   316,   317,   318,
      -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,   810,    -1,    -1,    -1,   335,    -1,    -1,    -1,
      -1,    -1,   820,    -1,    -1,   344,   824,    -1,   347,    -1,
      -1,    -1,    -1,    -1,   108,    -1,   355,    -1,    -1,   113,
     114,    -1,   116,   841,   675,    -1,    -1,   121,    -1,   123,
      -1,    -1,   109,    -1,   852,   853,   854,   855,   856,   857,
     858,   859,   860,   861,   862,   863,   864,   865,   866,   867,
     868,   869,   870,   871,   872,   394,   874,    -1,    -1,   398,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,   411,    -1,   151,    -1,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,    -1,   165,   166,
      -1,    -1,   169,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,   920,    -1,    -1,    -1,    -1,    -1,    -1,   448,
      33,    -1,    -1,    -1,    -1,    -1,    -1,   935,    -1,    -1,
    1324,  1325,  1326,  1327,  1328,   464,  1330,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,    -1,    -1,
      -1,    18,    19,    20,    21,    22,    23,   486,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   494,    33,    16,    17,    18,
      19,    20,    21,    22,    23,  1324,  1325,  1326,  1327,  1328,
      -1,  1330,    -1,   991,    33,   993,    -1,    -1,    -1,    -1,
      -1,    -1,   833,   834,   835,    -1,   837,    -1,   839,   840,
     841,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     539,    -1,    -1,    -1,    -1,  1409,  1410,  1411,  1412,  1413,
    1414,  1415,  1416,  1417,  1418,  1419,  1420,  1421,  1422,  1423,
    1424,  1425,  1426,  1427,    -1,    -1,    -1,  1045,    -1,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
      -1,   164,   165,   166,    -1,    -1,    -1,   170,    -1,   588,
    1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,  1418,
    1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,  1427,    -1,
       3,     4,     5,     6,  1478,     8,     9,    10,   155,   156,
     157,   158,   159,   160,   161,   162,    -1,   164,   165,   166,
      -1,    -1,   631,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,    -1,   164,   165,   166,    -1,    -1,
     649,   170,    -1,    -1,    -1,    -1,    -1,    50,    -1,  1478,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,  1535,    -1,    -1,    67,    -1,    -1,    10,    11,    12,
      -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,   707,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1535,    -1,   111,    -1,
     113,    -1,    -1,    -1,    -1,   118,    -1,    -1,    -1,   122,
      -1,    64,   125,    -1,    -1,    -1,    -1,   130,    -1,    -1,
     739,    -1,    -1,    76,    77,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   155,    -1,    -1,   158,   159,   160,    -1,    -1,
     163,  1249,   165,   166,    -1,    -1,   169,    -1,   777,    -1,
     113,   114,  1093,   116,    -1,    -1,    -1,    -1,   121,    -1,
     123,    -1,    50,    51,    -1,    -1,    54,    -1,    56,    57,
      58,    59,    60,    -1,    62,    63,    -1,    -1,    66,    67,
      -1,    -1,    70,    -1,   147,    -1,    -1,    75,    76,    77,
      -1,    -1,    -1,    81,    -1,  1303,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   109,    -1,   111,    -1,   113,    -1,    -1,    -1,    -1,
     118,    -1,   120,   121,   122,    -1,    -1,   125,   126,    -1,
      -1,  1349,   130,    -1,    -1,   133,   134,   135,   136,   137,
      -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    10,
      11,    -1,   891,    -1,    -1,    -1,    -1,   155,    -1,    -1,
     158,   159,   160,    -1,    -1,   163,    -1,   165,   166,    -1,
      -1,   169,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    10,    11,    12,    -1,    -1,    15,    -1,    -1,    -1,
      51,    -1,    -1,    54,    -1,    56,    57,    58,    59,    -1,
      -1,    -1,    63,    -1,    -1,    66,    -1,    -1,    -1,    70,
      -1,  1429,    -1,    -1,    -1,    -1,    77,    -1,    47,    -1,
      -1,    50,    51,    84,    -1,    54,    -1,    56,    57,    58,
      59,    60,    -1,    62,    63,    -1,    -1,    66,    67,   100,
      -1,    70,    -1,    -1,    -1,    -1,    75,    76,    77,    -1,
      -1,   112,    -1,    -1,    -1,    84,    -1,    -1,    -1,   120,
     121,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,  1008,
      -1,   100,    -1,   134,   135,   136,   137,    -1,  1329,   140,
     109,   142,   111,    -1,   113,    -1,   147,    -1,   117,   118,
      -1,   120,   121,   122,    -1,    -1,   125,   126,    -1,    -1,
    1039,   130,   163,    -1,   133,   134,   135,   136,   137,    -1,
      -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,    -1,   158,
     159,    -1,    -1,    -1,   163,    -1,   165,    -1,    -1,    -1,
     169,    -1,    -1,  1394,  1395,  1396,  1397,    -1,  1399,  1400,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,  1112,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    -1,    70,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,    -1,    -1,    -1,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,  1284,    -1,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    -1,    70,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,    -1,
      -1,    -1,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,    -1,   169,   170,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    -1,    -1,    50,    51,  1474,    -1,    54,    33,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    66,
      67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,   111,    -1,   113,    -1,    -1,    -1,
      -1,   118,    -1,   120,   121,   122,    -1,    -1,   125,   126,
      -1,    -1,    -1,   130,    -1,    -1,   133,   134,   135,   136,
     137,    -1,    -1,   140,    -1,   142,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    -1,    -1,    -1,   155,    -1,
      -1,   158,   159,   160,    -1,    -1,   163,    -1,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    -1,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,    -1,   164,
     165,   166,    -1,    50,    -1,   170,    -1,    54,    -1,    56,
      57,    58,    -1,    -1,    -1,    62,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,   111,    -1,   113,    -1,    -1,    -1,
      -1,   118,    -1,   120,   121,   122,    -1,    -1,   125,    -1,
      -1,    -1,    -1,   130,    -1,    -1,   133,    -1,    -1,    -1,
     137,     3,     4,     5,     6,   142,     8,     9,    10,    11,
     147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,   159,   160,    -1,    -1,   163,    -1,   165,   166,
      -1,    -1,   169,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    33,
      -1,    -1,    54,    -1,    56,    57,    58,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,
      -1,   113,    -1,    -1,    -1,    -1,   118,    -1,   120,   121,
     122,    -1,    -1,   125,    -1,    -1,    -1,    -1,   130,    -1,
      -1,   133,    -1,    -1,    -1,   137,     3,     4,     5,     6,
     142,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   155,    -1,    -1,   158,   159,   160,    -1,
      -1,   163,    -1,   165,   166,   167,    -1,   169,    -1,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,    -1,
     164,   165,   166,    50,    51,    -1,    -1,    54,    -1,    56,
      57,    58,    -1,    -1,    -1,    62,    -1,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,   111,    -1,   113,    -1,    -1,    -1,
      -1,   118,    -1,   120,   121,   122,    -1,    -1,   125,    -1,
      -1,    -1,    -1,   130,    -1,    -1,   133,    -1,    -1,    -1,
     137,     3,     4,     5,     6,   142,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,   159,   160,    -1,    -1,   163,    -1,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    33,    56,    57,    58,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,
      -1,   113,    -1,    -1,    -1,    -1,   118,    -1,   120,   121,
     122,    -1,    -1,   125,    -1,    -1,    -1,    -1,   130,    -1,
      -1,   133,    -1,    -1,    -1,   137,     3,     4,     5,     6,
     142,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   155,    -1,    -1,   158,   159,   160,    -1,
      -1,   163,    -1,   165,   166,    -1,    -1,   169,    -1,    -1,
     150,    -1,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,    50,   164,   165,   166,    54,    -1,    56,
      57,    58,    -1,    -1,    -1,    62,    -1,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,   111,    -1,   113,    -1,    -1,    -1,
      -1,   118,    -1,   120,   121,   122,    -1,    -1,   125,    -1,
      -1,    -1,    -1,   130,    -1,    -1,   133,    -1,    -1,    -1,
     137,     3,     4,     5,     6,   142,     8,     9,    10,    11,
     147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,   159,   160,    -1,    -1,   163,    -1,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    54,    33,    56,    57,    58,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,
      -1,   113,    -1,    -1,    -1,    -1,   118,    -1,   120,   121,
     122,    -1,    -1,   125,    -1,    -1,    -1,    -1,   130,    -1,
      -1,   133,    -1,    -1,    -1,   137,     3,     4,     5,     6,
     142,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   155,    -1,    -1,   158,   159,   160,    -1,
      -1,   163,    -1,   165,   166,   167,    -1,   169,    -1,   149,
      -1,    -1,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,    50,   164,   165,   166,    54,    -1,    56,
      57,    58,    -1,    -1,    -1,    62,    -1,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,   111,    -1,   113,    -1,    -1,    -1,
      -1,   118,    -1,   120,   121,   122,    -1,    -1,   125,    -1,
      -1,    -1,    -1,   130,    -1,    -1,   133,    -1,    -1,    -1,
     137,     3,     4,     5,     6,   142,     8,     9,    10,    11,
     147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
      -1,   158,   159,   160,    -1,    -1,   163,    -1,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    54,    33,    56,    57,    58,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,
      -1,   113,    -1,    -1,    -1,    -1,   118,    -1,   120,   121,
     122,    -1,    -1,   125,    -1,    -1,    -1,    -1,   130,    -1,
      -1,   133,    -1,    -1,    -1,   137,     3,     4,     5,     6,
     142,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   155,    -1,    -1,   158,   159,   160,    -1,
      -1,   163,    -1,   165,   166,   167,    -1,   169,   148,    -1,
      -1,    -1,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,    50,   164,   165,   166,    54,    -1,    56,
      57,    58,    -1,    -1,    -1,    62,    -1,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,   111,    -1,   113,    10,    11,    12,
      -1,   118,    -1,   120,   121,   122,    -1,    -1,   125,    -1,
      -1,    -1,    -1,   130,    -1,    -1,   133,    -1,    -1,    -1,
     137,     3,     4,     5,     6,   142,     8,     9,    10,    11,
      12,    -1,    -1,    15,    47,    -1,    49,    -1,   155,    -1,
      -1,   158,   159,   160,    -1,    -1,   163,    -1,   165,   166,
      -1,    64,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    47,    -1,    -1,    50,    51,
      -1,    -1,    54,    -1,    56,    57,    58,    59,    60,    -1,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    70,    -1,
      -1,    -1,    -1,    75,    76,    77,    -1,    -1,    -1,    -1,
     113,   114,    84,   116,    -1,    -1,    -1,    -1,   121,    -1,
     123,    -1,    -1,    -1,    -1,    10,    11,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,
      -1,   113,    -1,    -1,   147,   117,   118,    -1,   120,   121,
     122,    -1,    -1,   125,   126,    -1,    -1,    -1,   130,    -1,
      -1,   133,   134,   135,   136,   137,    51,    -1,   140,    54,
     142,    56,    57,    58,    59,    -1,    -1,    -1,    63,    -1,
      -1,    66,    -1,   155,    -1,    70,   158,   159,    -1,    -1,
      -1,   163,    77,   165,    -1,    -1,    -1,   169,    -1,    84,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,    -1,    -1,    -1,
      -1,   126,    54,    -1,    56,    57,    58,    -1,    -1,   134,
     135,   136,   137,    -1,    66,   140,    -1,   142,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    33,    -1,    -1,   163,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,    -1,   120,   121,
      -1,    -1,    -1,    -1,    33,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,   137,    -1,    -1,    -1,    -1,
     142,    -1,   148,    33,    -1,    -1,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,    -1,   164,   165,
     166,   167,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,    -1,   164,   165,   166,   167,
      -1,    -1,    -1,    -1,    -1,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,    -1,   164,   165,   166,
     167,    -1,    -1,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,    -1,   164,   165,   166,   167,    -1,
      -1,    -1,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,    -1,   164,   165,   166,   167,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,    -1,
     164,   165,   166,   167,    -1,    -1,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,    -1,   164,   165,
     166,   167,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    10,    11,    12,    -1,    10,    11,    12,    33,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    64,    -1,    -1,    -1,
      64,    -1,    -1,    33,    -1,    -1,    -1,    -1,    76,    77,
      -1,    -1,    76,    77,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,    -1,   164,   165,   166,   167,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,    33,   116,   113,
     114,    -1,   116,   121,    -1,   123,    -1,   121,    -1,   123,
      -1,    -1,    -1,    -1,    -1,    -1,   150,    -1,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   147,
     164,   165,   166,    -1,    -1,    -1,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,    -1,   164,   165,
     166,    -1,    -1,    -1,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,    -1,   164,   165,   166,    -1,
     150,    -1,   152,   153,   154,   155,    -1,    -1,   158,   159,
     160,   161,   162,    -1,   164,   165,   166,     0,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    -1,   152,   153,   154,   155,
      -1,    -1,   158,   159,   160,   161,   162,    -1,   164,   165,
     166,    -1,    -1,    -1,    47,    -1,    49,    -1,    -1,    52,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,
      73,    74,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
     103,   104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,
      -1,   114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,
     123,   124,    11,    12,   127,   128,    15,    -1,    17,   132,
      -1,    -1,    -1,    -1,    -1,   138,   139,    -1,   141,    -1,
      -1,    -1,   153,   154,   155,    -1,   149,   158,   159,   160,
     161,   162,    -1,   164,   165,   166,    -1,    -1,    47,    -1,
      -1,    -1,    51,    -1,    -1,    54,    -1,    56,    57,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    -1,    -1,
      -1,    70,    18,    19,    20,    21,    22,    23,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    33,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   100,    -1,    33,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,    33,
      -1,   120,   121,    -1,    -1,    -1,    -1,   126,    -1,    18,
      19,    20,    21,    22,    23,   134,   135,   136,   137,    -1,
      -1,   140,    -1,   142,    33,    18,    19,    20,    21,    22,
      23,    -1,    -1,    -1,    -1,    -1,   155,    -1,    -1,    -1,
      33,   160,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    18,    19,    20,    21,    22,    23,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    20,    21,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,    -1,   164,   165,
     166,    -1,    -1,    -1,   154,   155,   156,   157,   158,   159,
     160,   161,   162,    -1,   164,   165,   166,    -1,    -1,   153,
     154,   155,    -1,    -1,   158,   159,   160,   161,   162,    -1,
     164,   165,   166,    20,    21,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,   156,   157,   158,
     159,   160,   161,   162,    -1,   164,   165,   166,    -1,    -1,
      -1,   154,   155,    -1,    -1,   158,   159,   160,   161,   162,
      -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,   155,
       6,    -1,   158,   159,   160,   161,   162,    -1,   164,   165,
     166,   158,   159,   160,   161,   162,    17,   164,   165,   166,
      -1,    -1,    -1,   156,   157,   158,   159,   160,   161,   162,
      -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    49,    -1,    -1,    47,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    71,    72,    73,    -1,    -1,
      -1,    -1,     6,    -1,    -1,    76,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   158,   159,   160,   161,   162,    -1,   164,   165,   166,
      -1,   107,    -1,    -1,    -1,    -1,   107,    -1,    -1,   110,
      -1,   117,   113,    47,    -1,    49,    -1,   123,    -1,    53,
      -1,   127,   128,    10,    11,    12,    60,    61,   129,    -1,
      -1,    -1,    -1,   139,    -1,   141,    -1,    71,    72,    73,
     141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,   155,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    10,    11,    12,    -1,    -1,    54,    -1,    56,
      57,    58,    -1,   107,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,
      77,    10,    11,    12,   128,    -1,    -1,    84,    -1,    -1,
      -1,    -1,    -1,    51,    -1,   139,    54,   141,    56,    57,
      58,    59,    60,   100,    -1,    63,    -1,    -1,    66,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    51,   120,   121,    54,    84,    56,    57,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    -1,    -1,
     137,    70,   100,   140,    -1,   142,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,
      -1,    -1,   120,   121,    10,    11,    12,    -1,   126,    -1,
      -1,   100,    -1,    10,    11,    12,   134,   135,   136,   137,
      -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,    10,    11,    12,   134,   135,   136,   137,    -1,
      -1,   140,    -1,   142,    51,    -1,    -1,    54,    64,    56,
      57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      76,    77,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    54,    84,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,   100,    -1,    -1,    -1,   113,   114,    77,
     116,    -1,    -1,    -1,    -1,   121,    84,   123,    -1,    -1,
      -1,    -1,    -1,   120,   121,    -1,    -1,    -1,   134,   126,
      -1,    -1,   100,    10,    11,    12,    -1,   134,   135,   136,
     137,    -1,    -1,   140,    -1,   142,    11,    12,    -1,    -1,
      15,    -1,   120,   121,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   134,    -1,    -1,   137,
      -1,    -1,   140,    -1,   142,    11,    12,    -1,    -1,    15,
      -1,    -1,    47,    -1,    -1,    -1,    51,    64,    -1,    54,
      -1,    56,    57,    58,    59,    60,    -1,    -1,    63,    76,
      77,    66,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    47,    77,    -1,    -1,    51,    -1,    -1,    54,    84,
      56,    57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    -1,    -1,    -1,    70,   100,   113,   114,   115,   116,
      -1,    77,    -1,    -1,   121,    -1,   123,    -1,    84,    -1,
      -1,    -1,   117,    -1,    -1,   120,   121,   134,    -1,    -1,
      -1,   126,   139,    -1,   100,    -1,    -1,    11,    12,   134,
     135,   136,   137,    -1,    -1,   140,    -1,   142,    -1,    -1,
      -1,   117,    -1,    -1,   120,   121,    -1,    -1,    -1,    -1,
     126,    54,    -1,    56,    57,    58,    11,    12,   134,   135,
     136,   137,    -1,    47,   140,    -1,   142,    51,    -1,    -1,
      54,    -1,    56,    57,    58,    59,    60,    -1,    -1,    63,
      -1,    84,    66,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    51,   100,    -1,    54,
      84,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    -1,    -1,    -1,    70,   100,   120,   121,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    -1,   117,   137,    -1,   120,   121,    -1,   142,
      -1,    -1,   126,    11,    12,   100,    -1,    -1,    -1,    -1,
     134,   135,   136,   137,    -1,    -1,   140,    -1,   142,    -1,
      -1,    -1,   165,    -1,    -1,   120,   121,    11,    12,    -1,
      -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,
     135,   136,   137,    51,    -1,   140,    54,   142,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    -1,    -1,    66,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    51,    -1,    77,
      54,    -1,    56,    57,    58,    59,    84,    -1,    -1,    63,
      -1,    -1,    66,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,   100,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,   117,
      -1,    -1,   120,   121,    11,    -1,   100,    -1,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   134,   135,   136,   137,
      -1,    -1,   140,    -1,   142,    -1,   120,   121,    47,    -1,
      49,    -1,   126,    11,    -1,    -1,    -1,    -1,    -1,    -1,
     134,   135,   136,   137,    51,    64,   140,    54,   142,    56,
      57,    58,    59,    60,    -1,    -1,    63,    76,    77,    66,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    51,    -1,    -1,    54,    84,    56,    57,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    -1,
      -1,    -1,    70,   100,   113,   114,    -1,   116,    -1,    77,
      -1,    -1,   121,    -1,   123,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,    -1,    -1,    -1,    -1,   126,
      11,    -1,   100,    -1,    -1,    -1,    -1,   134,   135,   136,
     137,    -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,
      -1,    -1,   120,   121,    11,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    10,    11,    12,    -1,   134,   135,   136,   137,
      51,    -1,   140,    54,   142,    56,    57,    58,    59,    -1,
      -1,    -1,    63,    -1,    -1,    66,    -1,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    51,    -1,    77,    54,    -1,    56,
      57,    58,    59,    84,    -1,    -1,    63,    -1,    -1,    66,
      -1,    -1,    -1,    70,    -1,    -1,    64,    -1,    -1,   100,
      77,    -1,    10,    11,    12,    -1,    -1,    84,    76,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    10,    11,    12,   120,
     121,    -1,    -1,   100,    -1,   126,    -1,    -1,    -1,    -1,
      10,    11,    12,   134,   135,   136,   137,    -1,    -1,   140,
      -1,   142,    -1,   120,   121,   113,   114,    -1,   116,   126,
      -1,    -1,    -1,   121,    -1,   123,    64,   134,   135,   136,
     137,    -1,    -1,   140,    -1,   142,   134,    -1,    76,    77,
      64,   139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,    -1,   116,    -1,
      -1,    -1,    -1,   121,    -1,   123,    -1,    -1,    -1,   113,
     114,    -1,   116,    -1,    -1,    -1,   134,   121,    -1,   123,
      -1,   139,    -1,   113,   114,    -1,   116,    -1,    -1,    -1,
     134,   121,    47,   123,    49,   139,    -1,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,   138,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    74,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,   104,
     105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,   114,
     115,   116,   117,    -1,    -1,    47,    -1,    49,   123,   124,
      52,    53,   127,   128,    -1,    -1,    -1,   132,    60,    61,
      -1,    -1,    -1,   138,   139,    -1,   141,    69,    -1,    71,
      72,    73,    74,    -1,   149,    -1,    78,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,   104,   105,   106,   107,   108,    -1,    -1,    -1,
      -1,    -1,   114,   115,   116,   117,    -1,    -1,    47,    -1,
      49,   123,   124,    52,    53,   127,   128,    -1,    -1,    -1,
     132,    60,    61,    -1,    -1,    -1,   138,   139,    -1,   141,
      69,    -1,    71,    72,    73,    74,    -1,   149,    -1,    78,
      -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   168,    -1,    -1,    -1,
      -1,    -1,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,   114,   115,   116,   117,    -1,
      -1,    47,    -1,    49,   123,   124,    52,    53,   127,   128,
      -1,    -1,    -1,   132,    60,    61,    -1,    -1,    -1,   138,
     139,    -1,   141,    69,    -1,    71,    72,    73,    74,    -1,
     149,    -1,    78,    -1,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   168,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,   104,   105,
     106,   107,   108,    -1,    -1,    -1,    -1,    -1,   114,   115,
     116,   117,    -1,    -1,    47,    -1,    49,   123,   124,    52,
      53,   127,   128,    -1,    -1,    -1,   132,    60,    61,    -1,
      -1,    -1,   138,   139,    -1,   141,    69,    -1,    71,    72,
      73,    74,    -1,   149,    -1,    78,    -1,    -1,    -1,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   101,   102,
     103,   104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,
      -1,   114,   115,   116,   117,    -1,    -1,    47,    -1,    49,
     123,   124,    52,    53,   127,   128,    -1,    -1,    -1,   132,
      60,    61,    -1,    -1,    -1,   138,   139,    -1,   141,    69,
      -1,    71,    72,    73,    74,    -1,   149,    -1,    78,    -1,
      -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,    -1,
      -1,    -1,    -1,    -1,   114,   115,   116,   117,    -1,    -1,
      47,    -1,    49,   123,   124,    52,    53,   127,   128,    -1,
      -1,    -1,   132,    60,    61,    -1,    -1,    -1,   138,   139,
      -1,   141,    69,    -1,    71,    72,    73,    74,    -1,   149,
      -1,    78,    10,    11,    12,    -1,    83,    15,    -1,    -1,
      -1,    54,    -1,    56,    57,    58,    -1,    -1,   168,    -1,
      -1,    -1,    -1,    66,   101,   102,   103,   104,   105,   106,
     107,   108,    -1,    -1,    -1,    -1,    -1,   114,   115,   116,
     117,    84,    -1,    -1,    -1,    -1,   123,   124,    -1,    -1,
     127,   128,    -1,    -1,    -1,   132,    64,   100,    -1,    -1,
      -1,   138,   139,    54,   141,    56,    57,    58,    76,    77,
      -1,    -1,   149,    -1,    -1,    -1,    -1,   120,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   168,    -1,    84,   137,    -1,    -1,    -1,    -1,   142,
      -1,    -1,    -1,    -1,    -1,   113,   114,    -1,   116,   100,
      -1,    -1,    47,   121,    49,   123,    -1,    -1,    53,    -1,
      -1,    -1,   165,    -1,    -1,    60,    61,    -1,    -1,   120,
     121,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    -1,
      -1,    -1,    -1,    78,    -1,    -1,   137,    -1,    83,    -1,
      -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,   165,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,   123,    -1,
      -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   138,   139,    47,   141,    49,    -1,    -1,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,   156,    -1,    -1,    -1,    -1,    -1,    69,    -1,    71,
      72,    73,    74,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,   104,   105,   106,   107,   108,    -1,    -1,    -1,
      -1,    -1,   114,   115,   116,   117,    -1,    -1,    47,    -1,
      49,   123,   124,    -1,    53,   127,   128,    -1,    -1,    -1,
     132,    60,    61,    -1,    -1,    -1,   138,   139,    -1,   141,
      -1,    -1,    71,    72,    73,    47,    -1,    49,    -1,    78,
      -1,    53,    -1,    -1,    83,    -1,    -1,    -1,    60,    61,
      47,    -1,    49,    -1,    -1,    -1,    53,    -1,    -1,    71,
      72,    73,    -1,    60,    61,    -1,    -1,    -1,   107,    -1,
      -1,    83,    -1,    -1,    71,    72,    73,    -1,   117,    -1,
      -1,    -1,    -1,    -1,   123,    -1,    83,    -1,   127,   128,
      -1,    -1,    -1,    -1,    -1,   107,   108,    -1,    -1,   138,
     139,    -1,   141,    -1,    -1,   117,    -1,    -1,    -1,    -1,
     107,   123,    -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,
     117,    -1,    -1,    -1,    -1,    -1,   123,   139,    -1,   141,
      -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,   141
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   144,   145,   146,   172,   173,   281,     3,     4,     5,
       6,     8,     9,    10,    11,    50,    54,    56,    57,    58,
      62,    66,    67,    75,    76,    77,    81,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   109,   111,   113,   118,   120,   121,
     122,   125,   130,   133,   137,   142,   155,   158,   159,   160,
     163,   165,   166,   169,   271,   272,   280,    11,    12,    51,
      54,    56,    57,    58,    59,    60,    63,    66,    70,    77,
      84,   100,   120,   121,   126,   134,   135,   136,   137,   140,
     142,   233,   234,   238,   240,   242,   248,   249,   253,   254,
     259,   260,   261,   262,     0,    47,    49,    52,    53,    60,
      61,    69,    71,    72,    73,    74,    78,    83,   101,   102,
     103,   104,   105,   106,   107,   108,   114,   115,   116,   117,
     123,   124,   127,   128,   132,   138,   139,   141,   149,   176,
     178,   179,   181,   184,   204,   255,   258,   281,   147,   165,
     165,   165,   165,   165,   165,   156,   165,   156,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,    11,    51,    63,
     134,   135,   236,   253,   254,   259,   156,   165,   165,    15,
     165,   156,   165,   165,   165,   271,   271,   271,   271,   271,
      11,    54,    56,    57,    58,    66,    77,    84,   100,   120,
     121,   137,   142,   238,   269,   271,    10,    11,    12,    64,
      76,    77,   113,   114,   116,   121,   123,   151,   155,   160,
     275,   276,   278,   281,   271,    16,    17,    18,    19,    20,
      21,    22,    23,    33,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   164,   165,   166,     6,     8,
     233,   234,   165,    59,   126,    66,   100,   260,   260,   260,
     278,   165,   260,    13,    15,    17,    60,   141,   155,   160,
     165,   231,   232,   281,   232,   147,    10,    11,    12,   113,
     150,   279,   239,   281,   138,   182,   183,   278,   165,    72,
      83,   181,   181,   181,   181,     6,   181,   204,   181,   150,
     180,   108,   181,   165,   165,   165,   165,   165,   165,   181,
     147,   278,   150,   150,   150,   181,   181,   165,   179,   181,
     184,   205,   181,   181,   188,   108,   278,   181,   181,    10,
      11,    51,    63,   112,   134,   135,   147,   163,   191,   195,
     235,   237,   240,   242,   248,   253,   254,   259,   268,   269,
     281,   268,   238,   268,   268,   268,   268,   238,   268,   238,
     268,   238,   268,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   238,   268,   165,
     278,   165,   165,   278,   239,   238,   268,   268,   165,    10,
     238,   238,   238,   271,   268,   268,   167,   148,   167,   278,
     278,   148,   170,   151,   221,   281,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   167,   269,   271,
     232,   232,    51,   271,   238,   160,   278,    13,    15,    17,
      60,   141,   155,   160,   231,   281,   231,   232,   231,   232,
     231,   231,    15,    17,    47,    60,   117,   155,   160,   216,
     217,   226,   233,   234,   281,   166,   251,   252,   281,    11,
     250,   260,   150,    10,    11,    12,    47,    49,   113,   147,
     278,   279,   278,    48,   148,   165,    11,   235,   271,   181,
     178,   147,   278,   278,   278,   278,   278,   278,   278,   173,
     147,   271,   156,    10,    11,   195,   235,   237,   278,   149,
     151,   165,   165,   165,    60,   233,   278,   165,   177,   278,
     186,   147,   149,   151,   223,   149,   185,   278,   279,   239,
     168,   167,   167,   167,   167,   167,   167,   157,   167,   157,
     167,   167,   167,   167,   148,   167,   148,   167,   148,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     271,   238,   268,   278,   157,   167,   167,   278,   167,   167,
     157,   167,   167,   167,   167,   271,   271,    15,   155,   276,
     165,   201,   281,   271,   150,   167,   170,   167,   167,   167,
     231,   160,   278,   231,   231,   231,   231,   231,   166,   231,
     182,   117,   233,   234,   226,   231,   231,   167,    15,   148,
      13,    17,    60,   141,   155,   160,   165,   229,   279,   281,
      13,    15,    17,    60,   141,   155,   160,   165,   230,   267,
     271,   281,   278,   168,   250,   182,   165,   241,   243,   150,
     181,   182,     3,     4,     5,     9,    10,    15,    50,    62,
      67,    75,    76,   109,   111,   113,   118,   122,   125,   130,
     133,   155,   158,   159,   163,   165,   169,   218,   219,   226,
     227,   273,   274,   280,   281,   167,   167,   173,   147,   148,
     148,   148,   148,   148,   148,   168,   256,   148,   167,    10,
      11,    12,    59,    60,   134,   206,   207,   208,   209,   210,
     259,   281,   165,   223,   189,   149,   238,   192,    10,    13,
     160,   194,    51,   271,   233,    13,    17,    60,   141,   155,
     160,   228,   279,   281,   238,   173,   165,   147,   149,   150,
     151,   222,   263,   264,    64,    65,   147,   271,    13,    17,
      60,   112,   141,   155,   160,   165,   187,   211,   213,   279,
     150,   278,   165,   165,   238,   238,   238,   167,   167,   167,
     165,   167,   165,   221,   216,    17,    33,    47,    60,    61,
      76,   107,   110,   113,   129,   141,   155,   214,   281,   271,
     231,   267,   167,    48,   233,   234,   229,   230,   167,   167,
     201,    15,   226,   160,   229,   229,   229,   229,   229,   229,
     166,   221,   160,   278,   230,   230,   230,   230,   230,   230,
     166,   221,   170,   148,   151,    48,   235,   271,   173,    76,
     244,   281,   183,   165,   156,   156,   236,   156,    15,   165,
     156,   165,   271,   271,   271,   271,   238,   269,   271,   167,
      15,   148,    16,    17,    18,    19,    20,    21,    22,    23,
      33,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   164,   165,   166,   181,   181,   168,   257,    10,
      10,    10,    10,    10,    10,   173,   280,   149,   210,   157,
     148,    15,   278,    13,    17,    60,   141,   155,   160,   165,
     229,   230,   190,   213,   149,   216,   167,   160,   211,   216,
     167,   167,   228,   160,   228,   228,   228,   228,   228,   165,
     166,   167,   168,   196,   263,   174,   175,   278,    64,    65,
     168,   265,   281,   149,   149,   147,   224,   225,   271,   281,
     149,   160,   211,   211,     6,    16,    17,    18,    19,    20,
      21,    22,    23,    33,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    65,   109,   148,   151,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   165,   166,   169,   202,   211,   211,   211,   211,   150,
     165,   166,   214,   151,   221,   223,   250,   269,   269,   167,
     167,   167,   269,   269,   167,    60,   236,   182,   165,   147,
     170,   165,   226,   229,   230,   221,   221,   165,   165,   214,
     229,   167,   267,   230,   167,   267,   271,   167,   167,   168,
     150,   245,   246,   281,   238,   238,   238,   165,   238,   165,
      10,   238,   238,   238,   271,   167,   167,    15,   227,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     167,   269,   271,   173,   148,   148,   167,   148,   215,   281,
     148,   148,   148,   168,   167,   229,   230,   179,   184,   203,
     204,   209,   278,   151,   160,   151,   220,   281,   221,   223,
     167,   165,   211,   167,   167,   165,   228,   199,   267,   216,
     168,   147,   148,   147,   165,   149,   149,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    70,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    82,    83,    84,   100,   107,   108,   109,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   169,   170,   266,   224,   168,   148,
     211,    10,   167,   170,   167,     4,   212,   267,   271,   148,
     167,   167,   167,   167,   201,   236,   232,    48,   167,   278,
     263,   216,   221,   221,   216,   216,   165,   170,   165,   170,
     148,   114,   115,   116,   134,   139,   247,   277,   278,   147,
     148,   167,   157,   157,   268,   157,   278,   167,   167,   157,
     167,   167,   271,   150,   167,   170,   168,    10,    10,   149,
      10,   167,    10,    10,    10,   149,   220,   238,    50,    62,
      67,   118,   122,   125,   155,   158,   159,   160,   163,   165,
     169,   270,   272,   148,   201,   193,   167,   165,   201,   200,
     216,   170,   167,   263,   175,   268,   268,   265,   168,   147,
     271,   218,   170,   187,   214,   232,    15,   167,   168,   167,
     167,   167,   216,   216,   139,   277,   139,   277,   139,   277,
     278,   114,   115,   116,    15,   173,   247,   165,   165,   167,
     165,   167,   165,   271,   167,   148,   167,   148,   149,   148,
     167,   167,   148,   167,   165,   156,   156,   156,    15,   165,
     156,   270,   270,   270,   270,   270,   238,   269,   270,    16,
      17,    18,    19,    20,    21,    22,    23,    33,   152,   153,
     154,   155,   158,   159,   160,   161,   162,   164,   165,   166,
     190,   216,   165,   197,   216,   167,   201,   168,   168,   167,
     168,   224,   167,   147,   167,   201,   201,   201,   167,   167,
     277,   277,   277,   277,   277,   277,   168,   269,   269,   269,
     269,   149,    10,   149,    10,    10,   149,   149,    10,   149,
     238,   238,   238,   238,   165,    10,   238,   238,   167,   167,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   167,
     269,   271,   167,   198,   216,   167,   201,    15,   168,   201,
     263,   214,   214,   214,   201,   201,   167,   167,   167,   167,
     148,   215,   167,   148,   148,   167,   167,   157,   157,   157,
     278,   167,   167,   157,   270,   150,   167,   170,   201,   216,
     167,   201,   168,    10,   167,   149,    10,    10,   149,   165,
     165,   165,   167,   165,   270,   167,   201,   149,   167,   148,
     167,   269,   269,   269,   269,   201,   214,   149,    10,   149,
     167,   167,   167,   167,   214,   167,   149
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   171,   172,   172,   172,   173,   173,   173,   174,   174,
     175,   175,   175,   177,   176,   178,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   180,   179,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   182,   182,   183,   183,   183,   185,   184,   184,
     186,   184,   184,   184,   187,   187,   189,   188,   188,   190,
     190,   192,   191,   193,   191,   194,   191,   196,   195,   197,
     195,   198,   195,   199,   195,   200,   195,   195,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   203,   203,   203,   204,   205,   204,   204,   204,   206,
     206,   207,   207,   208,   208,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   210,   210,   210,   210,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   212,
     211,   213,   213,   214,   214,   214,   215,   215,   216,   216,
     216,   216,   216,   217,   217,   218,   218,   218,   218,   218,
     219,   219,   220,   220,   221,   221,   222,   222,   222,   222,
     222,   223,   223,   223,   223,   223,   223,   224,   224,   224,
     225,   225,   225,   225,   226,   226,   226,   226,   226,   226,
     226,   226,   227,   227,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   234,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   236,   236,   236,   236,   236,
     236,   236,   236,   237,   237,   238,   238,   238,   238,   239,
     239,   239,   239,   241,   240,   243,   242,   244,   244,   245,
     245,   246,   246,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   248,   249,   249,   249,   249,   250,   250,
     251,   251,   251,   252,   252,   252,   253,   253,   253,   254,
     254,   254,   256,   255,   257,   255,   255,   255,   258,   258,
     258,   259,   259,   259,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   261,   261,
     261,   262,   264,   263,   265,   265,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   267,   267,   268,   268,   269,
     269,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   275,   275,   275,   275,   275,   276,
     276,   276,   276,   277,   277,   277,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   279,   279,   279,
     279,   280,   280,   280,   280,   281
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     2,     2,     1,     3,
       4,     5,     4,     0,     5,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     2,     2,     2,     8,    11,     9,
      11,    13,    15,     7,     9,    12,     9,     9,    13,     9,
       7,     5,     0,     3,     1,     2,     2,     3,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       5,     5,     1,     3,     1,     4,     4,     0,     4,     3,
       0,     4,     3,     1,     2,     4,     0,     4,     3,     2,
       4,     0,     6,     0,     9,     0,     6,     0,     7,     0,
      11,     0,    12,     0,     8,     0,     9,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     5,
       6,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     1,     1,     1,     2,     0,     6,     2,     2,     1,
       1,     1,     3,     1,     1,     1,     2,     4,     2,     3,
       3,     4,     2,     3,     1,     1,     1,     1,     1,     2,
       3,     2,     2,     2,     2,     2,     3,     4,     3,     0,
       6,     2,     3,     1,     3,     4,     1,     2,     1,     1,
       1,     3,     2,     1,     3,     1,     1,     1,     3,     2,
       1,     3,     1,     2,     1,     2,     1,     3,     5,     3,
       3,     1,     3,     3,     3,     3,     4,     1,     1,     2,
       1,     3,     3,     5,     3,     4,     5,     3,     4,     5,
       2,     4,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     3,     4,     1,     1,     2,     2,     2,     2,     2,
       3,     4,     7,     3,     1,     2,     2,     2,     2,     2,
       2,     3,     4,     7,     3,     1,     1,     2,     2,     2,
       2,     2,     2,     3,     4,     1,     1,     2,     2,     2,
       2,     2,     2,     3,     4,     5,     9,     9,     9,     1,
       1,     2,     1,     1,     1,     3,     4,     4,     4,     4,
       1,     1,     1,     1,     2,     1,     1,     1,     3,     4,
       2,     4,     4,     4,     1,     1,     1,     2,     3,     2,
       4,     4,     1,     1,     1,     2,     3,     2,     3,     1,
       4,     5,     5,     0,     6,     0,     9,     1,     1,     1,
       1,     2,     3,     1,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     4,     3,     1,     4,     2,     1,     1,
       1,     3,     5,     1,     2,     4,     1,     2,     2,     1,
       1,     1,     0,     6,     0,     7,     4,     5,     3,     5,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     1,     1,
       2,     1,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     1,     4,     7,     7,     7,     7,     4,     4,     5,
       4,     2,     2,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     4,     4,     3,     3,     3,     3,
       1,     4,     7,     7,     7,     7,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     5,     4,     2,     5,     4,     4,     2,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     4,     4,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       8,    11,     4,     4,     6,     4,     4,     6,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     1,
       4,     7,     7,     7,     7,     4,     4,     5,     4,     2,
       5,     4,     4,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     4,     4,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     2,
       3,     1,     2,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     0
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc);
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3:
#line 454 "dtool/src/cppparser/cppBison.yxx"
{
  current_expr = (yyvsp[0].u.expr);
}
#line 4142 "built/tmp/cppBison.yxx.c"
    break;

  case 4:
#line 458 "dtool/src/cppparser/cppBison.yxx"
{
  current_type = (yyvsp[0].u.type);
}
#line 4150 "built/tmp/cppBison.yxx.c"
    break;

  case 10:
#line 476 "dtool/src/cppparser/cppBison.yxx"
{
  delete (yyvsp[-1].u.expr);
}
#line 4158 "built/tmp/cppBison.yxx.c"
    break;

  case 11:
#line 480 "dtool/src/cppparser/cppBison.yxx"
{
  delete (yyvsp[-2].u.expr);
}
#line 4166 "built/tmp/cppBison.yxx.c"
    break;

  case 12:
#line 484 "dtool/src/cppparser/cppBison.yxx"
{
  delete (yyvsp[-1].u.expr);
}
#line 4174 "built/tmp/cppBison.yxx.c"
    break;

  case 13:
#line 496 "dtool/src/cppparser/cppBison.yxx"
{
  push_storage_class((current_storage_class & ~CPPInstance::SC_c_binding) |
                     ((yyvsp[-1].u.integer) & CPPInstance::SC_c_binding));
}
#line 4183 "built/tmp/cppBison.yxx.c"
    break;

  case 14:
#line 501 "dtool/src/cppparser/cppBison.yxx"
{
  pop_storage_class();
}
#line 4191 "built/tmp/cppBison.yxx.c"
    break;

  case 21:
#line 514 "dtool/src/cppparser/cppBison.yxx"
{
  if (publish_nest_level != 0) {
    yyerror("Unclosed __begin_publish", publish_loc);
    publish_nest_level = 0;
    current_scope->set_current_vis(V_public);
  }

  publish_previous = current_scope->get_current_vis();
  publish_loc = (yylsp[0]);
  publish_nest_level++;
  current_scope->set_current_vis(V_published);
}
#line 4208 "built/tmp/cppBison.yxx.c"
    break;

  case 22:
#line 527 "dtool/src/cppparser/cppBison.yxx"
{
  if (publish_nest_level != 1) {
    yyerror("Unmatched __end_publish", (yylsp[0]));
  } else {
    current_scope->set_current_vis(publish_previous);
  }
  publish_nest_level = 0;
}
#line 4221 "built/tmp/cppBison.yxx.c"
    break;

  case 23:
#line 536 "dtool/src/cppparser/cppBison.yxx"
{
  current_scope->set_current_vis(V_published);
}
#line 4229 "built/tmp/cppBison.yxx.c"
    break;

  case 24:
#line 540 "dtool/src/cppparser/cppBison.yxx"
{
  if (publish_nest_level > 0) {
    current_scope->set_current_vis(V_published);
  } else {
    current_scope->set_current_vis(V_public);
  }
}
#line 4241 "built/tmp/cppBison.yxx.c"
    break;

  case 25:
#line 548 "dtool/src/cppparser/cppBison.yxx"
{
  current_scope->set_current_vis(V_protected);
}
#line 4249 "built/tmp/cppBison.yxx.c"
    break;

  case 26:
#line 552 "dtool/src/cppparser/cppBison.yxx"
{
  current_scope->set_current_vis(V_private);
}
#line 4257 "built/tmp/cppBison.yxx.c"
    break;

  case 27:
#line 556 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *getter = (yyvsp[-3].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-3].u.identifier)->get_fully_scoped_name(), (yylsp[-3]));
  } else {
    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[-5].u.identifier), CPPMakeProperty::T_normal, current_scope, (yylsp[-7]).file);
    make_property->_get_function = getter->as_function_group();

    if ((yyvsp[-2].u.identifier) != nullptr) {
      CPPDeclaration *setter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
      if (setter == nullptr || setter->get_subtype() != CPPDeclaration::ST_function_group) {
        yyerror("Reference to non-existent or invalid setter: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
      } else {
        make_property->_set_function = setter->as_function_group();
      }
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-7]));
  }
}
#line 4282 "built/tmp/cppBison.yxx.c"
    break;

  case 28:
#line 577 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *getter = (yyvsp[-6].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-6].u.identifier)->get_fully_scoped_name(), (yylsp[-6]));

  } else {
    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[-8].u.identifier), CPPMakeProperty::T_normal, current_scope, (yylsp[-10]).file);
    make_property->_get_function = getter->as_function_group();

    CPPDeclaration *setter = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (setter == nullptr || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    } else {
      make_property->_set_function = setter->as_function_group();
    }

    CPPDeclaration *deleter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (deleter == nullptr || deleter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid delete method: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
    } else {
      make_property->_del_function = deleter->as_function_group();
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-10]));
  }
}
#line 4313 "built/tmp/cppBison.yxx.c"
    break;

  case 29:
#line 604 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *length_getter = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == nullptr || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    length_getter = nullptr;
  }

  CPPDeclaration *getter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
    getter = nullptr;
  }

  if (getter != nullptr && length_getter != nullptr) {
    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[-6].u.identifier), CPPMakeProperty::T_sequence, current_scope, (yylsp[-8]).file);
    make_property->_get_function = getter->as_function_group();
    make_property->_length_function = length_getter->as_function_group();
    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-8]));
  }
}
#line 4338 "built/tmp/cppBison.yxx.c"
    break;

  case 30:
#line 625 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *length_getter = (yyvsp[-6].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == nullptr || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[-6].u.identifier)->get_fully_scoped_name(), (yylsp[-6]));
    length_getter = nullptr;
  }

  CPPDeclaration *getter = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    getter = nullptr;
  }

  if (getter != nullptr && length_getter != nullptr) {
    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[-8].u.identifier), CPPMakeProperty::T_sequence, current_scope, (yylsp[-10]).file);
    make_property->_get_function = getter->as_function_group();
    make_property->_length_function = length_getter->as_function_group();

    CPPDeclaration *setter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (setter == nullptr || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
    } else {
      make_property->_set_function = setter->as_function_group();
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-10]));
  }
}
#line 4371 "built/tmp/cppBison.yxx.c"
    break;

  case 31:
#line 654 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *length_getter = (yyvsp[-8].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == nullptr || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[-8].u.identifier)->get_fully_scoped_name(), (yylsp[-8]));
    length_getter = nullptr;
  }

  CPPDeclaration *getter = (yyvsp[-6].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-6].u.identifier)->get_fully_scoped_name(), (yylsp[-6]));
    getter = nullptr;
  }

  if (getter != nullptr && length_getter != nullptr) {
    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[-10].u.identifier), CPPMakeProperty::T_sequence, current_scope, (yylsp[-12]).file);
    make_property->_get_function = getter->as_function_group();
    make_property->_length_function = length_getter->as_function_group();

    CPPDeclaration *setter = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (setter == nullptr || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    } else {
      make_property->_set_function = setter->as_function_group();
    }

    CPPDeclaration *deleter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (deleter == nullptr || deleter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid delete method: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
    } else {
      make_property->_del_function = deleter->as_function_group();
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-12]));
  }
}
#line 4411 "built/tmp/cppBison.yxx.c"
    break;

  case 32:
#line 690 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *length_getter = (yyvsp[-10].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == nullptr || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[-10].u.identifier)->get_fully_scoped_name(), (yylsp[-10]));
    length_getter = nullptr;
  }

  CPPDeclaration *getter = (yyvsp[-8].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-8].u.identifier)->get_fully_scoped_name(), (yylsp[-8]));
    getter = nullptr;
  }

  if (getter != nullptr && length_getter != nullptr) {
    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[-12].u.identifier), CPPMakeProperty::T_sequence, current_scope, (yylsp[-14]).file);
    make_property->_get_function = getter->as_function_group();
    make_property->_length_function = length_getter->as_function_group();

    CPPDeclaration *setter = (yyvsp[-6].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (setter == nullptr || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[-6].u.identifier)->get_fully_scoped_name(), (yylsp[-6]));
    } else {
      make_property->_set_function = setter->as_function_group();
    }

    CPPDeclaration *deleter = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (deleter == nullptr || deleter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid delete method: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    } else {
      make_property->_del_function = deleter->as_function_group();
    }

    CPPDeclaration *inserter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (inserter == nullptr || inserter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid append method: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
    } else {
      make_property->_insert_function = inserter->as_function_group();
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-14]));
  }
}
#line 4458 "built/tmp/cppBison.yxx.c"
    break;

  case 33:
#line 733 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *getter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid item getter method: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));

  } else {
    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[-4].u.identifier), CPPMakeProperty::T_mapping, current_scope, (yylsp[-6]).file);
    make_property->_get_function = getter->as_function_group();
    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-6]));
  }
}
#line 4474 "built/tmp/cppBison.yxx.c"
    break;

  case 34:
#line 745 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *getter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));

  } else {
    CPPMakeProperty *make_property;
    make_property = new CPPMakeProperty((yyvsp[-6].u.identifier), CPPMakeProperty::T_mapping, current_scope, (yylsp[-8]).file);
    make_property->_get_function = getter->as_function_group();

    CPPDeclaration *hasser = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (hasser == nullptr || hasser->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid has/find method: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    } else {
      make_property->_has_function = hasser->as_function_group();
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-8]));
  }
}
#line 4499 "built/tmp/cppBison.yxx.c"
    break;

  case 35:
#line 766 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *getter = (yyvsp[-5].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-5].u.identifier)->get_fully_scoped_name(), (yylsp[-5]));

  } else {
    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[-9].u.identifier), CPPMakeProperty::T_mapping, current_scope, (yylsp[-11]).file);
    make_property->_get_function = getter->as_function_group();

    CPPDeclaration *hasser = (yyvsp[-7].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (hasser == nullptr || hasser->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid has/find method: " + (yyvsp[-7].u.identifier)->get_fully_scoped_name(), (yylsp[-7]));
    } else {
      make_property->_has_function = hasser->as_function_group();
    }

    CPPDeclaration *setter = (yyvsp[-3].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (setter == nullptr || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[-3].u.identifier)->get_fully_scoped_name(), (yylsp[-3]));
    } else {
      make_property->_set_function = setter->as_function_group();
    }

    if ((yyvsp[-2].u.identifier) != nullptr) {
      CPPDeclaration *deleter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
      if (deleter == nullptr || deleter->get_subtype() != CPPDeclaration::ST_function_group) {
        yyerror("reference to non-existent or invalid delete method: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
      } else {
        make_property->_del_function = deleter->as_function_group();
      }
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-11]));
  }
}
#line 4539 "built/tmp/cppBison.yxx.c"
    break;

  case 36:
#line 802 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *length_getter = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == nullptr || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    length_getter = nullptr;
  }

  CPPDeclaration *getter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid getter: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
    getter = nullptr;
  }

  if (getter != nullptr && length_getter != nullptr) {
    CPPMakeProperty *make_property = nullptr;
    for (size_t i = 0; i < current_scope->_declarations.size(); ++i) {
      make_property = current_scope->_declarations[i]->as_make_property();
      if (make_property != nullptr) {
        if (make_property->get_fully_scoped_name() == (yyvsp[-6].u.identifier)->get_fully_scoped_name()) {
          break;
        } else {
          make_property = nullptr;
        }
      }
    }
    if (make_property != nullptr) {
      make_property->_get_key_function = getter->as_function_group();
      make_property->_length_function = length_getter->as_function_group();
    } else {
      yyerror("reference to non-existent MAKE_MAP_PROPERTY: " + (yyvsp[-6].u.identifier)->get_fully_scoped_name(), (yylsp[-6]));
    }
  }
}
#line 4577 "built/tmp/cppBison.yxx.c"
    break;

  case 37:
#line 836 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *getter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));

  } else {
    CPPMakeProperty *make_property;
    make_property = new CPPMakeProperty((yyvsp[-6].u.identifier), CPPMakeProperty::T_normal,
                                        current_scope, (yylsp[-8]).file);
    make_property->_get_function = getter->as_function_group();

    CPPDeclaration *hasser = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (hasser == nullptr || hasser->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid has/find method: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    } else {
      make_property->_has_function = hasser->as_function_group();
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-8]));
  }
}
#line 4603 "built/tmp/cppBison.yxx.c"
    break;

  case 38:
#line 858 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *getter = (yyvsp[-6].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == nullptr || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[-6].u.identifier)->get_fully_scoped_name(), (yylsp[-6]));

  } else {
    CPPMakeProperty *make_property;
    make_property = new CPPMakeProperty((yyvsp[-10].u.identifier), CPPMakeProperty::T_normal,
                                        current_scope, (yylsp[-12]).file);
    make_property->_get_function = getter->as_function_group();

    CPPDeclaration *hasser = (yyvsp[-8].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (hasser == nullptr || hasser->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid has/find method: " + (yyvsp[-8].u.identifier)->get_fully_scoped_name(), (yylsp[-8]));
    } else {
      make_property->_has_function = hasser->as_function_group();
    }

    CPPDeclaration *setter = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (setter == nullptr || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid setter: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    } else {
      make_property->_set_function = setter->as_function_group();
    }

    CPPDeclaration *clearer = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (clearer == nullptr || clearer->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid clear method: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-2]));
    } else {
      make_property->_clear_function = clearer->as_function_group();
    }

    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[-12]));
  }
}
#line 4643 "built/tmp/cppBison.yxx.c"
    break;

  case 39:
#line 894 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *length_getter = (yyvsp[-4].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == nullptr || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[-4].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    length_getter = nullptr;
  }

  CPPDeclaration *element_getter = (yyvsp[-2].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (element_getter == nullptr || element_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid element method: " + (yyvsp[-2].u.identifier)->get_fully_scoped_name(), (yylsp[-4]));
    element_getter = nullptr;
  }

  if (length_getter != nullptr && element_getter != nullptr) {
    CPPMakeSeq *make_seq = new CPPMakeSeq((yyvsp[-6].u.identifier),
                                          length_getter->as_function_group(),
                                          element_getter->as_function_group(),
                                          current_scope, (yylsp[-8]).file);
    current_scope->add_declaration(make_seq, global_scope, current_lexer, (yylsp[-8]));
  }
}
#line 4669 "built/tmp/cppBison.yxx.c"
    break;

  case 40:
#line 916 "dtool/src/cppparser/cppBison.yxx"
{
  CPPExpression::Result result = (yyvsp[-4].u.expr)->evaluate();
  if (result._type == CPPExpression::RT_error) {
    yywarning("static_assert requires a constant expression", (yylsp[-4]));
  } else if (!result.as_boolean()) {
    stringstream str;
    str << *(yyvsp[-2].u.expr);
    yywarning("static_assert failed: " + str.str(), (yylsp[-4]));
  }
}
#line 4684 "built/tmp/cppBison.yxx.c"
    break;

  case 41:
#line 927 "dtool/src/cppparser/cppBison.yxx"
{
  // This alternative version of static_assert was introduced in C++17.
  CPPExpression::Result result = (yyvsp[-2].u.expr)->evaluate();
  if (result._type == CPPExpression::RT_error) {
    yywarning("static_assert requires a constant expression", (yylsp[-2]));
  } else if (!result.as_boolean()) {
    yywarning("static_assert failed", (yylsp[-2]));
  }
}
#line 4698 "built/tmp/cppBison.yxx.c"
    break;

  case 42:
#line 940 "dtool/src/cppparser/cppBison.yxx"
{
  CPPScope *new_scope = new CPPScope(current_scope, CPPNameComponent("temp"),
                                     V_public);
  push_scope(new_scope);
}
#line 4708 "built/tmp/cppBison.yxx.c"
    break;

  case 43:
#line 946 "dtool/src/cppparser/cppBison.yxx"
{
  delete current_scope;
  pop_scope();
}
#line 4717 "built/tmp/cppBison.yxx.c"
    break;

  case 44:
#line 955 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = 0;
}
#line 4725 "built/tmp/cppBison.yxx.c"
    break;

  case 45:
#line 959 "dtool/src/cppparser/cppBison.yxx"
{
  // This isn't really a storage class, but it helps with parsing.
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_const;
}
#line 4734 "built/tmp/cppBison.yxx.c"
    break;

  case 46:
#line 964 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_extern;
}
#line 4742 "built/tmp/cppBison.yxx.c"
    break;

  case 47:
#line 968 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_extern;
  if ((yyvsp[-1].str) == "C") {
    (yyval.u.integer) |= (int)CPPInstance::SC_c_binding;
  } else if ((yyvsp[-1].str) == "C++") {
    (yyval.u.integer) &= ~(int)CPPInstance::SC_c_binding;
  } else {
    yywarning("Ignoring unknown linkage type \"" + (yyvsp[-1].str) + "\"", (yylsp[-1]));
  }
}
#line 4757 "built/tmp/cppBison.yxx.c"
    break;

  case 48:
#line 979 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_static;
}
#line 4765 "built/tmp/cppBison.yxx.c"
    break;

  case 49:
#line 983 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_inline;
}
#line 4773 "built/tmp/cppBison.yxx.c"
    break;

  case 50:
#line 987 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_virtual;
}
#line 4781 "built/tmp/cppBison.yxx.c"
    break;

  case 51:
#line 991 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_explicit;
}
#line 4789 "built/tmp/cppBison.yxx.c"
    break;

  case 52:
#line 995 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_register;
}
#line 4797 "built/tmp/cppBison.yxx.c"
    break;

  case 53:
#line 999 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_volatile;
}
#line 4805 "built/tmp/cppBison.yxx.c"
    break;

  case 54:
#line 1003 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_mutable;
}
#line 4813 "built/tmp/cppBison.yxx.c"
    break;

  case 55:
#line 1007 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_constexpr;
}
#line 4821 "built/tmp/cppBison.yxx.c"
    break;

  case 56:
#line 1011 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_blocking;
}
#line 4829 "built/tmp/cppBison.yxx.c"
    break;

  case 57:
#line 1015 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_extension;
}
#line 4837 "built/tmp/cppBison.yxx.c"
    break;

  case 58:
#line 1019 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer) | (int)CPPInstance::SC_thread_local;
}
#line 4845 "built/tmp/cppBison.yxx.c"
    break;

  case 59:
#line 1023 "dtool/src/cppparser/cppBison.yxx"
{
  // Ignore attribute specifiers for now.
  (yyval.u.integer) = (yyvsp[0].u.integer);
}
#line 4854 "built/tmp/cppBison.yxx.c"
    break;

  case 60:
#line 1028 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer);
}
#line 4862 "built/tmp/cppBison.yxx.c"
    break;

  case 61:
#line 1032 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[0].u.integer);
}
#line 4870 "built/tmp/cppBison.yxx.c"
    break;

  case 67:
#line 1050 "dtool/src/cppparser/cppBison.yxx"
{
  // We don't need to push/pop type, because we can't nest
  // type_like_declaration.
  if ((yyvsp[0].u.decl)->as_type_declaration()) {
    current_type = (yyvsp[0].u.decl)->as_type_declaration()->_type;
  } else {
    current_type = (yyvsp[0].u.decl)->as_type();
  }
  push_storage_class((yyvsp[-1].u.integer));
}
#line 4885 "built/tmp/cppBison.yxx.c"
    break;

  case 68:
#line 1061 "dtool/src/cppparser/cppBison.yxx"
{
  pop_storage_class();
}
#line 4893 "built/tmp/cppBison.yxx.c"
    break;

  case 69:
#line 1066 "dtool/src/cppparser/cppBison.yxx"
{
  // We don't really care about the storage class here.  In fact, it's
  // not actually legal to define a class or struct using a particular
  // storage class, but we require it just to help yacc out in its
  // parsing.

  current_scope->add_declaration((yyvsp[-1].u.decl), global_scope, current_lexer, (yylsp[-1]));
}
#line 4906 "built/tmp/cppBison.yxx.c"
    break;

  case 70:
#line 1075 "dtool/src/cppparser/cppBison.yxx"
{
  if ((yyvsp[0].u.instance) != nullptr) {
    // Push the scope so that the initializers can make use of things defined
    // in the class body.
    push_scope((yyvsp[0].u.instance)->get_scope(current_scope, global_scope));
    (yyvsp[0].u.instance)->_storage_class |= (current_storage_class | (yyvsp[-1].u.integer));
  }
}
#line 4919 "built/tmp/cppBison.yxx.c"
    break;

  case 71:
#line 1084 "dtool/src/cppparser/cppBison.yxx"
{
  if ((yyvsp[-2].u.instance) != nullptr) {
    pop_scope();
    current_scope->add_declaration((yyvsp[-2].u.instance), global_scope, current_lexer, (yylsp[-2]));
    (yyvsp[-2].u.instance)->set_initializer((yyvsp[0].u.expr));
  }
}
#line 4931 "built/tmp/cppBison.yxx.c"
    break;

  case 72:
#line 1092 "dtool/src/cppparser/cppBison.yxx"
{
  if ((yyvsp[-1].u.instance) != nullptr) {
    (yyvsp[-1].u.instance)->_storage_class |= (current_storage_class | (yyvsp[-2].u.integer));
    current_scope->add_declaration((yyvsp[-1].u.instance), global_scope, current_lexer, (yylsp[-1]));
    (yyvsp[-1].u.instance)->set_initializer((yyvsp[0].u.expr));
  }
}
#line 4943 "built/tmp/cppBison.yxx.c"
    break;

  case 74:
#line 1108 "dtool/src/cppparser/cppBison.yxx"
{
  if (current_storage_class & CPPInstance::SC_const) {
    (yyvsp[-1].u.inst_ident)->add_modifier(IIT_const);
  }
  CPPInstance *inst = new CPPInstance(current_type, (yyvsp[-1].u.inst_ident),
                                      current_storage_class,
                                      (yylsp[-1]).file);
  inst->set_initializer((yyvsp[0].u.expr));
  current_scope->add_declaration(inst, global_scope, current_lexer, (yylsp[-1]));
}
#line 4958 "built/tmp/cppBison.yxx.c"
    break;

  case 75:
#line 1119 "dtool/src/cppparser/cppBison.yxx"
{
  if (current_storage_class & CPPInstance::SC_const) {
    (yyvsp[-3].u.inst_ident)->add_modifier(IIT_const);
  }
  CPPInstance *inst = new CPPInstance(current_type, (yyvsp[-3].u.inst_ident),
                                      current_storage_class,
                                      (yylsp[-3]).file);
  inst->set_initializer((yyvsp[-2].u.expr));
  current_scope->add_declaration(inst, global_scope, current_lexer, (yylsp[-3]));
}
#line 4973 "built/tmp/cppBison.yxx.c"
    break;

  case 76:
#line 1134 "dtool/src/cppparser/cppBison.yxx"
{
  // We don't need to push/pop type, because we can't nest
  // multiple_var_declarations.
  if ((yyvsp[0].u.decl)->as_type_declaration()) {
    current_type = (yyvsp[0].u.decl)->as_type_declaration()->_type;
  } else {
    current_type = (yyvsp[0].u.decl)->as_type();
  }
  push_storage_class((yyvsp[-1].u.integer));
}
#line 4988 "built/tmp/cppBison.yxx.c"
    break;

  case 77:
#line 1145 "dtool/src/cppparser/cppBison.yxx"
{
  pop_storage_class();
}
#line 4996 "built/tmp/cppBison.yxx.c"
    break;

  case 78:
#line 1149 "dtool/src/cppparser/cppBison.yxx"
{
  if ((yyvsp[-1].u.instance) != nullptr) {
    CPPInstance *inst = (yyvsp[-1].u.instance)->as_instance();
    if (inst != nullptr) {
      inst->_storage_class |= (current_storage_class | (yyvsp[-2].u.integer));
      current_scope->add_declaration(inst, global_scope, current_lexer, (yylsp[-1]));
      CPPTypedefType *typedef_type = new CPPTypedefType(inst->_type, inst->_ident, current_scope);
      current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[-1]));
    }
  }
}
#line 5012 "built/tmp/cppBison.yxx.c"
    break;

  case 79:
#line 1164 "dtool/src/cppparser/cppBison.yxx"
{
  if (current_storage_class & CPPInstance::SC_const) {
    (yyvsp[-1].u.inst_ident)->add_modifier(IIT_const);
  }
  CPPType *target_type = current_type;
  CPPTypedefType *typedef_type = new CPPTypedefType(target_type, (yyvsp[-1].u.inst_ident), current_scope, (yylsp[-1]).file);
  current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[-1]));
}
#line 5025 "built/tmp/cppBison.yxx.c"
    break;

  case 80:
#line 1173 "dtool/src/cppparser/cppBison.yxx"
{
  if (current_storage_class & CPPInstance::SC_const) {
    (yyvsp[-3].u.inst_ident)->add_modifier(IIT_const);
  }
  CPPType *target_type = current_type;
  CPPTypedefType *typedef_type = new CPPTypedefType(target_type, (yyvsp[-3].u.inst_ident), current_scope, (yylsp[-3]).file);
  current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[-3]));
}
#line 5038 "built/tmp/cppBison.yxx.c"
    break;

  case 81:
#line 1187 "dtool/src/cppparser/cppBison.yxx"
{
  // Create a scope for this function.
  CPPScope *scope = new CPPScope((yyvsp[-1].u.identifier)->get_scope(current_scope, global_scope),
                                 (yyvsp[-1].u.identifier)->_names.back(), V_private);

  // It still needs to be able to pick up any template arguments, if this is
  // a definition for a method template.  Add a fake "using" declaration to
  // accomplish this.
  scope->_using.insert(current_scope);

  push_scope(scope);
}
#line 5055 "built/tmp/cppBison.yxx.c"
    break;

  case 82:
#line 1200 "dtool/src/cppparser/cppBison.yxx"
{
  CPPScope *scope = (yyvsp[-5].u.identifier)->get_scope(current_scope, global_scope);
  CPPType *type;
  std::string simple_name = (yyvsp[-5].u.identifier)->get_simple_name();
  if (!simple_name.empty() && simple_name[0] == '~') {
    // A destructor has no return type.
    type = new CPPSimpleType(CPPSimpleType::T_void);
  } else if (scope != nullptr && simple_name == scope->get_simple_name()) {
    // Neither does a constructor.
    type = new CPPSimpleType(CPPSimpleType::T_void);
  } else {
    // This isn't a constructor, so it has an implicit return type of
    // int.
    yywarning("function has no return type, assuming int", (yylsp[-5]));
    type = new CPPSimpleType(CPPSimpleType::T_int);
  }
  pop_scope();

  CPPInstanceIdentifier *ii = new CPPInstanceIdentifier((yyvsp[-5].u.identifier));
  ii->add_func_modifier((yyvsp[-2].u.param_list), (yyvsp[0].u.integer));

  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[-5]).file);
}
#line 5083 "built/tmp/cppBison.yxx.c"
    break;

  case 83:
#line 1226 "dtool/src/cppparser/cppBison.yxx"
{
  // Create a scope for this function.
  CPPScope *scope = new CPPScope((yyvsp[-2].u.identifier)->get_scope(current_scope, global_scope),
                                 (yyvsp[-2].u.identifier)->_names.back(), V_private);

  // It still needs to be able to pick up any template arguments, if this is
  // a definition for a method template.  Add a fake "using" declaration to
  // accomplish this.
  scope->_using.insert(current_scope);

  push_scope(scope);
}
#line 5100 "built/tmp/cppBison.yxx.c"
    break;

  case 84:
#line 1239 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
  CPPType *type = (yyvsp[-8].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[-8].u.identifier)->get_fully_scoped_name(), (yylsp[-8]));
  }
  assert(type != nullptr);

  CPPInstanceIdentifier *ii = new CPPInstanceIdentifier((yyvsp[-6].u.identifier));
  ii->add_func_modifier((yyvsp[-2].u.param_list), (yyvsp[0].u.integer));

  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[-8]).file);
}
#line 5118 "built/tmp/cppBison.yxx.c"
    break;

  case 85:
#line 1253 "dtool/src/cppparser/cppBison.yxx"
{
  // Create a scope for this function.
  CPPScope *scope = new CPPScope((yyvsp[-1].u.identifier)->get_scope(current_scope, global_scope),
                                 (yyvsp[-1].u.identifier)->_names.back(), V_private);

  // It still needs to be able to pick up any template arguments, if this is
  // a definition for a method template.  Add a fake "using" declaration to
  // accomplish this.
  scope->_using.insert(current_scope);

  push_scope(scope);
}
#line 5135 "built/tmp/cppBison.yxx.c"
    break;

  case 86:
#line 1266 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
  CPPType *type;
  if ((yyvsp[-5].u.identifier)->get_simple_name() == current_scope->get_simple_name()) {
    // This is a constructor, and has no return.
    type = new CPPSimpleType(CPPSimpleType::T_void);
  } else {
    // This isn't a constructor, so it has an implicit return type of
    // int.
    type = new CPPSimpleType(CPPSimpleType::T_int);
  }

  CPPInstanceIdentifier *ii = new CPPInstanceIdentifier((yyvsp[-5].u.identifier));
  ii->add_func_modifier((yyvsp[-2].u.param_list), (yyvsp[0].u.integer));

  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[-5]).file);
}
#line 5157 "built/tmp/cppBison.yxx.c"
    break;

  case 87:
#line 1289 "dtool/src/cppparser/cppBison.yxx"
{
  push_scope((yyvsp[-1].u.identifier)->get_scope(current_scope, global_scope));
}
#line 5165 "built/tmp/cppBison.yxx.c"
    break;

  case 88:
#line 1293 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
  if ((yyvsp[-5].u.identifier)->is_scoped()) {
    yyerror("Invalid destructor name: ~" + (yyvsp[-5].u.identifier)->get_fully_scoped_name(), (yylsp[-5]));
  } else {
    CPPIdentifier *ident =
      new CPPIdentifier("~" + (yyvsp[-5].u.identifier)->get_simple_name(), (yylsp[-5]));
    delete (yyvsp[-5].u.identifier);

    CPPType *type;
    type = new CPPSimpleType(CPPSimpleType::T_void);

    CPPInstanceIdentifier *ii = new CPPInstanceIdentifier(ident);
    ii->add_func_modifier((yyvsp[-2].u.param_list), (yyvsp[0].u.integer));

    (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[-5]).file);
  }
}
#line 5188 "built/tmp/cppBison.yxx.c"
    break;

  case 89:
#line 1319 "dtool/src/cppparser/cppBison.yxx"
{
  push_scope((yyvsp[-2].u.inst_ident)->get_scope(current_scope, global_scope));
}
#line 5196 "built/tmp/cppBison.yxx.c"
    break;

  case 90:
#line 1323 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
  CPPType *type = (yyvsp[-10].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[-10].u.identifier)->get_fully_scoped_name(), (yylsp[-10]));
  }
  assert(type != nullptr);

  CPPInstanceIdentifier *ii = (yyvsp[-7].u.inst_ident);
  ii->add_modifier(IIT_pointer);
  ii->add_func_modifier((yyvsp[-3].u.param_list), (yyvsp[-1].u.integer));
  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[-10]).file);
}
#line 5214 "built/tmp/cppBison.yxx.c"
    break;

  case 91:
#line 1337 "dtool/src/cppparser/cppBison.yxx"
{
  push_scope((yyvsp[-2].u.inst_ident)->get_scope(current_scope, global_scope));
}
#line 5222 "built/tmp/cppBison.yxx.c"
    break;

  case 92:
#line 1341 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
  CPPType *type = (yyvsp[-11].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[-11].u.identifier)->get_fully_scoped_name(), (yylsp[-11]));
  }
  assert(type != nullptr);

  CPPInstanceIdentifier *ii = (yyvsp[-7].u.inst_ident);
  ii->add_scoped_pointer_modifier((yyvsp[-9].u.identifier));
  ii->add_func_modifier((yyvsp[-3].u.param_list), (yyvsp[-1].u.integer));
  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[-11]).file);
}
#line 5240 "built/tmp/cppBison.yxx.c"
    break;

  case 93:
#line 1357 "dtool/src/cppparser/cppBison.yxx"
{
  if ((yyvsp[-3].u.identifier) != nullptr) {
    push_scope((yyvsp[-3].u.identifier)->get_scope(current_scope, global_scope));
  }
}
#line 5250 "built/tmp/cppBison.yxx.c"
    break;

  case 94:
#line 1363 "dtool/src/cppparser/cppBison.yxx"
{
  if ((yyvsp[-7].u.identifier) != nullptr) {
    pop_scope();
  }

  // We use formal_parameter_identifier, because that can match a type
  // name with or without an identifier, but especially without, which
  // is what follows the keyword "operator" in a typecast function.
  // As an added bonus, the type of the formal_parameter will be the
  // typecast type, i.e. the return type of the typecast function.

  // We give typecast operators the name "operator typecast <name>",
  // where <name> is a simple name of the type to be typecast.  Use
  // the method's return type to determine the full type description.
  string name = "operator typecast " + (yyvsp[-6].u.type)->get_simple_name();
  CPPIdentifier *ident = (yyvsp[-7].u.identifier);
  if (ident == nullptr) {
    ident = new CPPIdentifier(name, (yylsp[-6]));
  } else {
    ident->add_name(name);
  }
  (yyval.u.instance) = CPPInstance::make_typecast_function
    (new CPPInstance((yyvsp[-6].u.type), (yyvsp[-5].u.inst_ident), 0, (yylsp[-5]).file), ident, (yyvsp[-2].u.param_list), (yyvsp[0].u.integer));
}
#line 5279 "built/tmp/cppBison.yxx.c"
    break;

  case 95:
#line 1388 "dtool/src/cppparser/cppBison.yxx"
{
  if ((yyvsp[-4].u.identifier) != nullptr) {
    push_scope((yyvsp[-4].u.identifier)->get_scope(current_scope, global_scope));
  }
}
#line 5289 "built/tmp/cppBison.yxx.c"
    break;

  case 96:
#line 1394 "dtool/src/cppparser/cppBison.yxx"
{
  if ((yyvsp[-8].u.identifier) != nullptr) {
    pop_scope();
  }

  CPPIdentifier *ident = (yyvsp[-8].u.identifier);
  if (ident == nullptr) {
    ident = new CPPIdentifier("operator typecast", (yylsp[-5]));
  } else {
    ident->add_name("operator typecast");
  }
  (yyvsp[-5].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.instance) = CPPInstance::make_typecast_function
    (new CPPInstance((yyvsp[-6].u.type), (yyvsp[-5].u.inst_ident), 0, (yylsp[-5]).file), ident, (yyvsp[-2].u.param_list), (yyvsp[0].u.integer));
}
#line 5309 "built/tmp/cppBison.yxx.c"
    break;

  case 97:
#line 1414 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *decl =
    (yyvsp[0].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (decl != nullptr) {
    (yyval.u.instance) = decl->as_instance();
  } else {
    (yyval.u.instance) = nullptr;
  }
}
#line 5323 "built/tmp/cppBison.yxx.c"
    break;

  case 98:
#line 1427 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = 0;
}
#line 5331 "built/tmp/cppBison.yxx.c"
    break;

  case 99:
#line 1431 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-1].u.integer) | (int)CPPFunctionType::F_const_method;
}
#line 5339 "built/tmp/cppBison.yxx.c"
    break;

  case 100:
#line 1435 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-1].u.integer) | (int)CPPFunctionType::F_volatile_method;
}
#line 5347 "built/tmp/cppBison.yxx.c"
    break;

  case 101:
#line 1439 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-1].u.integer) | (int)CPPFunctionType::F_noexcept;
}
#line 5355 "built/tmp/cppBison.yxx.c"
    break;

  case 102:
#line 1452 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-1].u.integer) | (int)CPPFunctionType::F_final;
}
#line 5363 "built/tmp/cppBison.yxx.c"
    break;

  case 103:
#line 1456 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-1].u.integer) | (int)CPPFunctionType::F_override;
}
#line 5371 "built/tmp/cppBison.yxx.c"
    break;

  case 104:
#line 1460 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-1].u.integer) | (int)CPPFunctionType::F_lvalue_method;
}
#line 5379 "built/tmp/cppBison.yxx.c"
    break;

  case 105:
#line 1464 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-1].u.integer) | (int)CPPFunctionType::F_rvalue_method;
}
#line 5387 "built/tmp/cppBison.yxx.c"
    break;

  case 106:
#line 1468 "dtool/src/cppparser/cppBison.yxx"
{
  // Used for lambdas, currently ignored.
  (yyval.u.integer) = (yyvsp[-1].u.integer);
}
#line 5396 "built/tmp/cppBison.yxx.c"
    break;

  case 107:
#line 1473 "dtool/src/cppparser/cppBison.yxx"
{
  // Used for lambdas in C++17, currently ignored.
  (yyval.u.integer) = (yyvsp[-1].u.integer);
}
#line 5405 "built/tmp/cppBison.yxx.c"
    break;

  case 108:
#line 1478 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-3].u.integer);
}
#line 5413 "built/tmp/cppBison.yxx.c"
    break;

  case 109:
#line 1482 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-4].u.integer);
}
#line 5421 "built/tmp/cppBison.yxx.c"
    break;

  case 110:
#line 1486 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-5].u.integer);
}
#line 5429 "built/tmp/cppBison.yxx.c"
    break;

  case 111:
#line 1490 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.integer) = (yyvsp[-3].u.integer);
}
#line 5437 "built/tmp/cppBison.yxx.c"
    break;

  case 112:
#line 1497 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "!";
}
#line 5445 "built/tmp/cppBison.yxx.c"
    break;

  case 113:
#line 1501 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "~";
}
#line 5453 "built/tmp/cppBison.yxx.c"
    break;

  case 114:
#line 1505 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "*";
}
#line 5461 "built/tmp/cppBison.yxx.c"
    break;

  case 115:
#line 1509 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "/";
}
#line 5469 "built/tmp/cppBison.yxx.c"
    break;

  case 116:
#line 1513 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "%";
}
#line 5477 "built/tmp/cppBison.yxx.c"
    break;

  case 117:
#line 1517 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "+";
}
#line 5485 "built/tmp/cppBison.yxx.c"
    break;

  case 118:
#line 1521 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "-";
}
#line 5493 "built/tmp/cppBison.yxx.c"
    break;

  case 119:
#line 1525 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "|";
}
#line 5501 "built/tmp/cppBison.yxx.c"
    break;

  case 120:
#line 1529 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "&";
}
#line 5509 "built/tmp/cppBison.yxx.c"
    break;

  case 121:
#line 1533 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "^";
}
#line 5517 "built/tmp/cppBison.yxx.c"
    break;

  case 122:
#line 1537 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "||";
}
#line 5525 "built/tmp/cppBison.yxx.c"
    break;

  case 123:
#line 1541 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "&&";
}
#line 5533 "built/tmp/cppBison.yxx.c"
    break;

  case 124:
#line 1545 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "==";
}
#line 5541 "built/tmp/cppBison.yxx.c"
    break;

  case 125:
#line 1549 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "!=";
}
#line 5549 "built/tmp/cppBison.yxx.c"
    break;

  case 126:
#line 1553 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "<=";
}
#line 5557 "built/tmp/cppBison.yxx.c"
    break;

  case 127:
#line 1557 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = ">=";
}
#line 5565 "built/tmp/cppBison.yxx.c"
    break;

  case 128:
#line 1561 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "<";
}
#line 5573 "built/tmp/cppBison.yxx.c"
    break;

  case 129:
#line 1565 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = ">";
}
#line 5581 "built/tmp/cppBison.yxx.c"
    break;

  case 130:
#line 1569 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "<<";
}
#line 5589 "built/tmp/cppBison.yxx.c"
    break;

  case 131:
#line 1573 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = ">>";
}
#line 5597 "built/tmp/cppBison.yxx.c"
    break;

  case 132:
#line 1577 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "=";
}
#line 5605 "built/tmp/cppBison.yxx.c"
    break;

  case 133:
#line 1581 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = ",";
}
#line 5613 "built/tmp/cppBison.yxx.c"
    break;

  case 134:
#line 1585 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "++";
}
#line 5621 "built/tmp/cppBison.yxx.c"
    break;

  case 135:
#line 1589 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "--";
}
#line 5629 "built/tmp/cppBison.yxx.c"
    break;

  case 136:
#line 1593 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "*=";
}
#line 5637 "built/tmp/cppBison.yxx.c"
    break;

  case 137:
#line 1597 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "/=";
}
#line 5645 "built/tmp/cppBison.yxx.c"
    break;

  case 138:
#line 1601 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "%=";
}
#line 5653 "built/tmp/cppBison.yxx.c"
    break;

  case 139:
#line 1605 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "+=";
}
#line 5661 "built/tmp/cppBison.yxx.c"
    break;

  case 140:
#line 1609 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "-=";
}
#line 5669 "built/tmp/cppBison.yxx.c"
    break;

  case 141:
#line 1613 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "|=";
}
#line 5677 "built/tmp/cppBison.yxx.c"
    break;

  case 142:
#line 1617 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "&=";
}
#line 5685 "built/tmp/cppBison.yxx.c"
    break;

  case 143:
#line 1621 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "^=";
}
#line 5693 "built/tmp/cppBison.yxx.c"
    break;

  case 144:
#line 1625 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "<<=";
}
#line 5701 "built/tmp/cppBison.yxx.c"
    break;

  case 145:
#line 1629 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = ">>=";
}
#line 5709 "built/tmp/cppBison.yxx.c"
    break;

  case 146:
#line 1633 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "->";
}
#line 5717 "built/tmp/cppBison.yxx.c"
    break;

  case 147:
#line 1637 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "[]";
}
#line 5725 "built/tmp/cppBison.yxx.c"
    break;

  case 148:
#line 1641 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "()";
}
#line 5733 "built/tmp/cppBison.yxx.c"
    break;

  case 149:
#line 1645 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "new";
}
#line 5741 "built/tmp/cppBison.yxx.c"
    break;

  case 150:
#line 1649 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.str) = "delete";
}
#line 5749 "built/tmp/cppBison.yxx.c"
    break;

  case 155:
#line 1663 "dtool/src/cppparser/cppBison.yxx"
{
  push_scope(new CPPTemplateScope(current_scope));
}
#line 5757 "built/tmp/cppBison.yxx.c"
    break;

  case 156:
#line 1667 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
}
#line 5765 "built/tmp/cppBison.yxx.c"
    break;

  case 161:
#line 1681 "dtool/src/cppparser/cppBison.yxx"
{
  CPPTemplateScope *ts = current_scope->as_template_scope();
  assert(ts != nullptr);
  ts->add_template_parameter((yyvsp[0].u.decl));
}
#line 5775 "built/tmp/cppBison.yxx.c"
    break;

  case 162:
#line 1687 "dtool/src/cppparser/cppBison.yxx"
{
  CPPTemplateScope *ts = current_scope->as_template_scope();
  assert(ts != nullptr);
  ts->add_template_parameter((yyvsp[0].u.decl));
}
#line 5785 "built/tmp/cppBison.yxx.c"
    break;

  case 165:
#line 1701 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = CPPType::new_type(new CPPClassTemplateParameter(nullptr));
}
#line 5793 "built/tmp/cppBison.yxx.c"
    break;

  case 166:
#line 1705 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = CPPType::new_type(new CPPClassTemplateParameter((yyvsp[0].u.identifier)));
}
#line 5801 "built/tmp/cppBison.yxx.c"
    break;

  case 167:
#line 1709 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = CPPType::new_type(new CPPClassTemplateParameter((yyvsp[-2].u.identifier), (yyvsp[0].u.type)));
}
#line 5809 "built/tmp/cppBison.yxx.c"
    break;

  case 168:
#line 1713 "dtool/src/cppparser/cppBison.yxx"
{
  CPPClassTemplateParameter *ctp = new CPPClassTemplateParameter(nullptr);
  ctp->_packed = true;
  (yyval.u.decl) = CPPType::new_type(ctp);
}
#line 5819 "built/tmp/cppBison.yxx.c"
    break;

  case 169:
#line 1719 "dtool/src/cppparser/cppBison.yxx"
{
  CPPClassTemplateParameter *ctp = new CPPClassTemplateParameter((yyvsp[0].u.identifier));
  ctp->_packed = true;
  (yyval.u.decl) = CPPType::new_type(ctp);
}
#line 5829 "built/tmp/cppBison.yxx.c"
    break;

  case 170:
#line 1725 "dtool/src/cppparser/cppBison.yxx"
{
  CPPInstance *inst = new CPPInstance((yyvsp[-2].u.type), (yyvsp[-1].u.inst_ident), 0, (yylsp[-1]).file);
  inst->set_initializer((yyvsp[0].u.expr));
  (yyval.u.decl) = inst;
}
#line 5839 "built/tmp/cppBison.yxx.c"
    break;

  case 171:
#line 1731 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[-1].u.inst_ident)->add_modifier(IIT_const);
  CPPInstance *inst = new CPPInstance((yyvsp[-2].u.type), (yyvsp[-1].u.inst_ident), 0, (yylsp[-1]).file);
  inst->set_initializer((yyvsp[0].u.expr));
  (yyval.u.decl) = inst;
}
#line 5850 "built/tmp/cppBison.yxx.c"
    break;

  case 172:
#line 1738 "dtool/src/cppparser/cppBison.yxx"
{
  CPPInstance *inst = new CPPInstance((yyvsp[-1].u.type), (yyvsp[0].u.inst_ident), 0, (yylsp[0]).file);
  (yyval.u.decl) = inst;
}
#line 5859 "built/tmp/cppBison.yxx.c"
    break;

  case 173:
#line 1743 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[0].u.inst_ident)->add_modifier(IIT_const);
  CPPInstance *inst = new CPPInstance((yyvsp[-1].u.type), (yyvsp[0].u.inst_ident), 0, (yylsp[0]).file);
  (yyval.u.decl) = inst;
}
#line 5869 "built/tmp/cppBison.yxx.c"
    break;

  case 174:
#line 1752 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type((yyvsp[0].u.simple_type));
}
#line 5877 "built/tmp/cppBison.yxx.c"
    break;

  case 175:
#line 1756 "dtool/src/cppparser/cppBison.yxx"
{
  yywarning("Not a type: " + (yyvsp[0].u.identifier)->get_fully_scoped_name(), (yylsp[0]));
  (yyval.u.type) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_unknown));
}
#line 5886 "built/tmp/cppBison.yxx.c"
    break;

  case 176:
#line 1761 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.type) == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[0].u.identifier)->get_fully_scoped_name(), (yylsp[0]));
  }
  assert((yyval.u.type) != nullptr);
}
#line 5898 "built/tmp/cppBison.yxx.c"
    break;

  case 177:
#line 1769 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.type) == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[0].u.identifier)->get_fully_scoped_name(), (yylsp[0]));
  }
  assert((yyval.u.type) != nullptr);
}
#line 5910 "built/tmp/cppBison.yxx.c"
    break;

  case 178:
#line 1781 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[0].u.identifier));
}
#line 5918 "built/tmp/cppBison.yxx.c"
    break;

  case 179:
#line 1785 "dtool/src/cppparser/cppBison.yxx"
{
  // For an operator function.  We implement this simply by building a
  // ficticious name for the function; in other respects it's just
  // like a regular function.
  CPPIdentifier *ident = (yyvsp[-1].u.identifier);
  if (ident == nullptr) {
    ident = new CPPIdentifier("operator "+(yyvsp[0].str), (yylsp[0]));
  } else {
    ident->_names.push_back("operator "+(yyvsp[0].str));
  }

  (yyval.u.inst_ident) = new CPPInstanceIdentifier(ident);
}
#line 5936 "built/tmp/cppBison.yxx.c"
    break;

  case 180:
#line 1799 "dtool/src/cppparser/cppBison.yxx"
{
  // A C++11 literal operator.
  if (!(yyvsp[-1].str).empty()) {
    yyerror("expected empty string", (yylsp[-1]));
  }
  CPPIdentifier *ident = (yyvsp[-2].u.identifier);
  if (ident == nullptr) {
    ident = new CPPIdentifier("operator \"\" "+(yyvsp[0].u.identifier)->get_simple_name(), (yylsp[0]));
  } else {
    ident->_names.push_back("operator \"\" "+(yyvsp[0].u.identifier)->get_simple_name());
  }

  (yyval.u.inst_ident) = new CPPInstanceIdentifier(ident);
}
#line 5955 "built/tmp/cppBison.yxx.c"
    break;

  case 181:
#line 1814 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
#line 5964 "built/tmp/cppBison.yxx.c"
    break;

  case 182:
#line 1819 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
#line 5973 "built/tmp/cppBison.yxx.c"
    break;

  case 183:
#line 1824 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
#line 5982 "built/tmp/cppBison.yxx.c"
    break;

  case 184:
#line 1829 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
#line 5991 "built/tmp/cppBison.yxx.c"
    break;

  case 185:
#line 1834 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
#line 6000 "built/tmp/cppBison.yxx.c"
    break;

  case 186:
#line 1839 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[-2].u.identifier));
}
#line 6009 "built/tmp/cppBison.yxx.c"
    break;

  case 187:
#line 1844 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-3].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[-1].u.expr));
}
#line 6018 "built/tmp/cppBison.yxx.c"
    break;

  case 188:
#line 1849 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-1].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
}
#line 6027 "built/tmp/cppBison.yxx.c"
    break;

  case 189:
#line 1854 "dtool/src/cppparser/cppBison.yxx"
{
  // Create a scope for this function (in case it is a function)
  CPPScope *scope = new CPPScope((yyvsp[-1].u.inst_ident)->get_scope(current_scope, global_scope),
                                 CPPNameComponent(""), V_private);

  // It still needs to be able to pick up any template arguments, if this is
  // a definition for a method template.  Add a fake "using" declaration to
  // accomplish this.
  scope->_using.insert(current_scope);

  push_scope(scope);
}
#line 6044 "built/tmp/cppBison.yxx.c"
    break;

  case 190:
#line 1867 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
  (yyval.u.inst_ident) = (yyvsp[-5].u.inst_ident);
  if ((yyvsp[-2].u.param_list)->is_parameter_expr() && (yyvsp[0].u.integer) == 0) {
    // Oops, this must have been an instance declaration with a
    // parameter list, not a function prototype.
    (yyval.u.inst_ident)->add_initializer_modifier((yyvsp[-2].u.param_list));

  } else {
    // This was (probably) a function prototype.
    (yyval.u.inst_ident)->add_func_modifier((yyvsp[-2].u.param_list), (yyvsp[0].u.integer));
  }
}
#line 6062 "built/tmp/cppBison.yxx.c"
    break;

  case 191:
#line 1885 "dtool/src/cppparser/cppBison.yxx"
{
  // This is handled a bit awkwardly right now.  Ideally it'd be wrapped
  // up in the instance_identifier rule, but then more needs to happen in
  // order to avoid shift/reduce conflicts.
  if ((yyvsp[0].u.type) != nullptr) {
    (yyvsp[-1].u.inst_ident)->add_trailing_return_type((yyvsp[0].u.type));
  }
  (yyval.u.inst_ident) = (yyvsp[-1].u.inst_ident);
}
#line 6076 "built/tmp/cppBison.yxx.c"
    break;

  case 192:
#line 1895 "dtool/src/cppparser/cppBison.yxx"
{
  // Bitfield definition.
  (yyvsp[-2].u.inst_ident)->_bit_width = (yyvsp[0].u.integer);
  (yyval.u.inst_ident) = (yyvsp[-2].u.inst_ident);
}
#line 6086 "built/tmp/cppBison.yxx.c"
    break;

  case 193:
#line 1905 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = nullptr;
}
#line 6094 "built/tmp/cppBison.yxx.c"
    break;

  case 194:
#line 1909 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.inst_ident)->unroll_type((yyvsp[-1].u.type));
}
#line 6102 "built/tmp/cppBison.yxx.c"
    break;

  case 195:
#line 1913 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[0].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.type) = (yyvsp[0].u.inst_ident)->unroll_type((yyvsp[-1].u.type));
}
#line 6111 "built/tmp/cppBison.yxx.c"
    break;

  case 196:
#line 1922 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = nullptr;
}
#line 6119 "built/tmp/cppBison.yxx.c"
    break;

  case 197:
#line 1926 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = (yyvsp[0].u.identifier);
}
#line 6127 "built/tmp/cppBison.yxx.c"
    break;

  case 198:
#line 1934 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = new CPPParameterList;
}
#line 6135 "built/tmp/cppBison.yxx.c"
    break;

  case 199:
#line 1938 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = new CPPParameterList;
  (yyval.u.param_list)->_includes_ellipsis = true;
}
#line 6144 "built/tmp/cppBison.yxx.c"
    break;

  case 200:
#line 1943 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = (yyvsp[0].u.param_list);
}
#line 6152 "built/tmp/cppBison.yxx.c"
    break;

  case 201:
#line 1947 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = (yyvsp[-2].u.param_list);
  (yyval.u.param_list)->_includes_ellipsis = true;
}
#line 6161 "built/tmp/cppBison.yxx.c"
    break;

  case 202:
#line 1952 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = (yyvsp[-1].u.param_list);
  (yyval.u.param_list)->_includes_ellipsis = true;
}
#line 6170 "built/tmp/cppBison.yxx.c"
    break;

  case 203:
#line 1960 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = new CPPParameterList;
  (yyval.u.param_list)->_parameters.push_back((yyvsp[0].u.instance));
}
#line 6179 "built/tmp/cppBison.yxx.c"
    break;

  case 204:
#line 1965 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = (yyvsp[-2].u.param_list);
  (yyval.u.param_list)->_parameters.push_back((yyvsp[0].u.instance));
}
#line 6188 "built/tmp/cppBison.yxx.c"
    break;

  case 205:
#line 1973 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = new CPPParameterList;
}
#line 6196 "built/tmp/cppBison.yxx.c"
    break;

  case 206:
#line 1977 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = new CPPParameterList;
  (yyval.u.param_list)->_includes_ellipsis = true;
}
#line 6205 "built/tmp/cppBison.yxx.c"
    break;

  case 207:
#line 1982 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = (yyvsp[0].u.param_list);
}
#line 6213 "built/tmp/cppBison.yxx.c"
    break;

  case 208:
#line 1986 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = (yyvsp[-2].u.param_list);
  (yyval.u.param_list)->_includes_ellipsis = true;
}
#line 6222 "built/tmp/cppBison.yxx.c"
    break;

  case 209:
#line 1991 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = (yyvsp[-1].u.param_list);
  (yyval.u.param_list)->_includes_ellipsis = true;
}
#line 6231 "built/tmp/cppBison.yxx.c"
    break;

  case 210:
#line 1999 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = new CPPParameterList;
  (yyval.u.param_list)->_parameters.push_back((yyvsp[0].u.instance));
}
#line 6240 "built/tmp/cppBison.yxx.c"
    break;

  case 211:
#line 2004 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.param_list) = (yyvsp[-2].u.param_list);
  (yyval.u.param_list)->_parameters.push_back((yyvsp[0].u.instance));
}
#line 6249 "built/tmp/cppBison.yxx.c"
    break;

  case 212:
#line 2012 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 6257 "built/tmp/cppBison.yxx.c"
    break;

  case 213:
#line 2016 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 6265 "built/tmp/cppBison.yxx.c"
    break;

  case 214:
#line 2023 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 6273 "built/tmp/cppBison.yxx.c"
    break;

  case 215:
#line 2027 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 6281 "built/tmp/cppBison.yxx.c"
    break;

  case 216:
#line 2034 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 6289 "built/tmp/cppBison.yxx.c"
    break;

  case 217:
#line 2038 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 6297 "built/tmp/cppBison.yxx.c"
    break;

  case 218:
#line 2042 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 6305 "built/tmp/cppBison.yxx.c"
    break;

  case 219:
#line 2046 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_default());
}
#line 6313 "built/tmp/cppBison.yxx.c"
    break;

  case 220:
#line 2050 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_delete());
}
#line 6321 "built/tmp/cppBison.yxx.c"
    break;

  case 221:
#line 2057 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 6329 "built/tmp/cppBison.yxx.c"
    break;

  case 222:
#line 2061 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 6337 "built/tmp/cppBison.yxx.c"
    break;

  case 223:
#line 2065 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[-1].u.expr);
}
#line 6345 "built/tmp/cppBison.yxx.c"
    break;

  case 224:
#line 2069 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_default());
}
#line 6353 "built/tmp/cppBison.yxx.c"
    break;

  case 225:
#line 2073 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_delete());
}
#line 6361 "built/tmp/cppBison.yxx.c"
    break;

  case 226:
#line 2077 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 6369 "built/tmp/cppBison.yxx.c"
    break;

  case 230:
#line 2090 "dtool/src/cppparser/cppBison.yxx"
{
}
#line 6376 "built/tmp/cppBison.yxx.c"
    break;

  case 234:
#line 2099 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.instance) = new CPPInstance((yyvsp[-2].u.type), (yyvsp[-1].u.inst_ident), 0, (yylsp[-1]).file);
  (yyval.u.instance)->set_initializer((yyvsp[0].u.expr));
}
#line 6385 "built/tmp/cppBison.yxx.c"
    break;

  case 235:
#line 2104 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[-1].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.instance) = new CPPInstance((yyvsp[-2].u.type), (yyvsp[-1].u.inst_ident), 0, (yylsp[-1]).file);
  (yyval.u.instance)->set_initializer((yyvsp[0].u.expr));
}
#line 6395 "built/tmp/cppBison.yxx.c"
    break;

  case 236:
#line 2110 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[-1].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.instance) = new CPPInstance((yyvsp[-2].u.type), (yyvsp[-1].u.inst_ident), 0, (yylsp[-2]).file);
  (yyval.u.instance)->set_initializer((yyvsp[0].u.expr));
}
#line 6405 "built/tmp/cppBison.yxx.c"
    break;

  case 237:
#line 2116 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.instance) = new CPPInstance((yyvsp[-2].u.type), (yyvsp[-1].u.inst_ident), 0, (yylsp[-1]).file);
  (yyval.u.instance)->set_initializer((yyvsp[0].u.expr));
}
#line 6414 "built/tmp/cppBison.yxx.c"
    break;

  case 238:
#line 2121 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[-1].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.instance) = new CPPInstance((yyvsp[-2].u.type), (yyvsp[-1].u.inst_ident), 0, (yylsp[-1]).file);
  (yyval.u.instance)->set_initializer((yyvsp[0].u.expr));
}
#line 6424 "built/tmp/cppBison.yxx.c"
    break;

  case 239:
#line 2127 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[-1].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.instance) = new CPPInstance((yyvsp[-2].u.type), (yyvsp[-1].u.inst_ident), 0, (yylsp[-2]).file);
  (yyval.u.instance)->set_initializer((yyvsp[0].u.expr));
}
#line 6434 "built/tmp/cppBison.yxx.c"
    break;

  case 240:
#line 2133 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.instance) = (yyvsp[0].u.instance);
}
#line 6442 "built/tmp/cppBison.yxx.c"
    break;

  case 241:
#line 2137 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.instance) = (yyvsp[0].u.instance);
}
#line 6450 "built/tmp/cppBison.yxx.c"
    break;

  case 242:
#line 2148 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.instance) = (yyvsp[0].u.instance);
}
#line 6458 "built/tmp/cppBison.yxx.c"
    break;

  case 243:
#line 2152 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_parameter));
  (yyval.u.instance) = new CPPInstance(type, "expr");
  (yyval.u.instance)->set_initializer((yyvsp[0].u.expr));
}
#line 6469 "built/tmp/cppBison.yxx.c"
    break;

  case 244:
#line 2162 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier(nullptr);
}
#line 6477 "built/tmp/cppBison.yxx.c"
    break;

  case 245:
#line 2166 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[0].u.identifier));
}
#line 6485 "built/tmp/cppBison.yxx.c"
    break;

  case 246:
#line 2170 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
#line 6494 "built/tmp/cppBison.yxx.c"
    break;

  case 247:
#line 2175 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
#line 6503 "built/tmp/cppBison.yxx.c"
    break;

  case 248:
#line 2180 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
#line 6512 "built/tmp/cppBison.yxx.c"
    break;

  case 249:
#line 2185 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
#line 6521 "built/tmp/cppBison.yxx.c"
    break;

  case 250:
#line 2190 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
#line 6530 "built/tmp/cppBison.yxx.c"
    break;

  case 251:
#line 2195 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[-2].u.identifier));
}
#line 6539 "built/tmp/cppBison.yxx.c"
    break;

  case 252:
#line 2200 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-3].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[-1].u.expr));
}
#line 6548 "built/tmp/cppBison.yxx.c"
    break;

  case 253:
#line 2208 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier(nullptr);
}
#line 6556 "built/tmp/cppBison.yxx.c"
    break;

  case 254:
#line 2212 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[0].u.identifier));
}
#line 6564 "built/tmp/cppBison.yxx.c"
    break;

  case 255:
#line 2216 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
#line 6573 "built/tmp/cppBison.yxx.c"
    break;

  case 256:
#line 2221 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
#line 6582 "built/tmp/cppBison.yxx.c"
    break;

  case 257:
#line 2226 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
#line 6591 "built/tmp/cppBison.yxx.c"
    break;

  case 258:
#line 2231 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
#line 6600 "built/tmp/cppBison.yxx.c"
    break;

  case 259:
#line 2236 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
#line 6609 "built/tmp/cppBison.yxx.c"
    break;

  case 260:
#line 2241 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[-2].u.identifier));
}
#line 6618 "built/tmp/cppBison.yxx.c"
    break;

  case 261:
#line 2246 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-3].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[-1].u.expr));
}
#line 6627 "built/tmp/cppBison.yxx.c"
    break;

  case 262:
#line 2251 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-5].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[-2].u.param_list), (yyvsp[0].u.integer));
}
#line 6637 "built/tmp/cppBison.yxx.c"
    break;

  case 263:
#line 2257 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-1].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
}
#line 6646 "built/tmp/cppBison.yxx.c"
    break;

  case 264:
#line 2265 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier(nullptr);
  (yyval.u.inst_ident)->_packed = true;
}
#line 6655 "built/tmp/cppBison.yxx.c"
    break;

  case 265:
#line 2270 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[0].u.identifier));
  (yyval.u.inst_ident)->_packed = true;
}
#line 6664 "built/tmp/cppBison.yxx.c"
    break;

  case 266:
#line 2275 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
#line 6673 "built/tmp/cppBison.yxx.c"
    break;

  case 267:
#line 2280 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
#line 6682 "built/tmp/cppBison.yxx.c"
    break;

  case 268:
#line 2285 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
#line 6691 "built/tmp/cppBison.yxx.c"
    break;

  case 269:
#line 2290 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
#line 6700 "built/tmp/cppBison.yxx.c"
    break;

  case 270:
#line 2295 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
#line 6709 "built/tmp/cppBison.yxx.c"
    break;

  case 271:
#line 2300 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[-2].u.identifier));
}
#line 6718 "built/tmp/cppBison.yxx.c"
    break;

  case 272:
#line 2305 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-3].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[-1].u.expr));
}
#line 6727 "built/tmp/cppBison.yxx.c"
    break;

  case 273:
#line 2310 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-5].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[-2].u.param_list), (yyvsp[0].u.integer));
}
#line 6737 "built/tmp/cppBison.yxx.c"
    break;

  case 274:
#line 2316 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-1].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
}
#line 6746 "built/tmp/cppBison.yxx.c"
    break;

  case 275:
#line 2324 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier(nullptr);
}
#line 6754 "built/tmp/cppBison.yxx.c"
    break;

  case 276:
#line 2328 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier(nullptr);
  (yyval.u.inst_ident)->_packed = true;
}
#line 6763 "built/tmp/cppBison.yxx.c"
    break;

  case 277:
#line 2333 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[0].u.identifier));
  (yyval.u.inst_ident)->_packed = true;
}
#line 6772 "built/tmp/cppBison.yxx.c"
    break;

  case 278:
#line 2338 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
#line 6781 "built/tmp/cppBison.yxx.c"
    break;

  case 279:
#line 2343 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
#line 6790 "built/tmp/cppBison.yxx.c"
    break;

  case 280:
#line 2348 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
#line 6799 "built/tmp/cppBison.yxx.c"
    break;

  case 281:
#line 2353 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
#line 6808 "built/tmp/cppBison.yxx.c"
    break;

  case 282:
#line 2358 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
#line 6817 "built/tmp/cppBison.yxx.c"
    break;

  case 283:
#line 2363 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[-2].u.identifier));
}
#line 6826 "built/tmp/cppBison.yxx.c"
    break;

  case 284:
#line 2368 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-3].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[-1].u.expr));
}
#line 6835 "built/tmp/cppBison.yxx.c"
    break;

  case 285:
#line 2376 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier(nullptr);
}
#line 6843 "built/tmp/cppBison.yxx.c"
    break;

  case 286:
#line 2380 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier(nullptr);
  (yyval.u.inst_ident)->_packed = true;
}
#line 6852 "built/tmp/cppBison.yxx.c"
    break;

  case 287:
#line 2385 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[0].u.identifier));
  (yyval.u.inst_ident)->_packed = true;
}
#line 6861 "built/tmp/cppBison.yxx.c"
    break;

  case 288:
#line 2390 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
#line 6870 "built/tmp/cppBison.yxx.c"
    break;

  case 289:
#line 2395 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
#line 6879 "built/tmp/cppBison.yxx.c"
    break;

  case 290:
#line 2400 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
#line 6888 "built/tmp/cppBison.yxx.c"
    break;

  case 291:
#line 2405 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
#line 6897 "built/tmp/cppBison.yxx.c"
    break;

  case 292:
#line 2410 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
#line 6906 "built/tmp/cppBison.yxx.c"
    break;

  case 293:
#line 2415 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[0].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[-2].u.identifier));
}
#line 6915 "built/tmp/cppBison.yxx.c"
    break;

  case 294:
#line 2420 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-3].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[-1].u.expr));
}
#line 6924 "built/tmp/cppBison.yxx.c"
    break;

  case 295:
#line 2425 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = new CPPInstanceIdentifier(nullptr);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[-3].u.param_list), (yyvsp[-1].u.integer), (yyvsp[0].u.type));
}
#line 6934 "built/tmp/cppBison.yxx.c"
    break;

  case 296:
#line 2431 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-6].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[-3].u.param_list), (yyvsp[-1].u.integer), (yyvsp[0].u.type));
}
#line 6945 "built/tmp/cppBison.yxx.c"
    break;

  case 297:
#line 2438 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-6].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[-3].u.param_list), (yyvsp[-1].u.integer), (yyvsp[0].u.type));
}
#line 6956 "built/tmp/cppBison.yxx.c"
    break;

  case 298:
#line 2445 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.inst_ident) = (yyvsp[-6].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[-3].u.param_list), (yyvsp[-1].u.integer), (yyvsp[0].u.type));
}
#line 6967 "built/tmp/cppBison.yxx.c"
    break;

  case 299:
#line 2455 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type((yyvsp[0].u.simple_type));
}
#line 6975 "built/tmp/cppBison.yxx.c"
    break;

  case 300:
#line 2459 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.type) == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[0].u.identifier)->get_fully_scoped_name(), (yylsp[0]));
  }
  assert((yyval.u.type) != nullptr);
}
#line 6987 "built/tmp/cppBison.yxx.c"
    break;

  case 301:
#line 2467 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type(new CPPTBDType((yyvsp[0].u.identifier)));
}
#line 6995 "built/tmp/cppBison.yxx.c"
    break;

  case 302:
#line 2471 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type((yyvsp[0].u.struct_type));
}
#line 7003 "built/tmp/cppBison.yxx.c"
    break;

  case 303:
#line 2475 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type((yyvsp[0].u.struct_type));
}
#line 7011 "built/tmp/cppBison.yxx.c"
    break;

  case 304:
#line 2479 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type((yyvsp[0].u.enum_type));
}
#line 7019 "built/tmp/cppBison.yxx.c"
    break;

  case 305:
#line 2483 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != nullptr) {
    (yyval.u.type) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[-2].u.extension_enum), (yyvsp[0].u.identifier), current_scope, (yylsp[-2]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[0].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != nullptr) {
      scope->define_extension_type(et);
    }
    (yyval.u.type) = et;
  }
}
#line 7039 "built/tmp/cppBison.yxx.c"
    break;

  case 306:
#line 2499 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type = (yyvsp[-2].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != nullptr) {
    (yyval.u.type) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[-3].u.extension_enum), (yyvsp[-2].u.identifier), current_scope, (yylsp[-3]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[-2].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != nullptr) {
      scope->define_extension_type(et);
    }
    (yyval.u.type) = et;
  }
}
#line 7059 "built/tmp/cppBison.yxx.c"
    break;

  case 307:
#line 2515 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[-1].u.expr)->determine_type();
  if ((yyval.u.type) == nullptr) {
    stringstream str;
    str << *(yyvsp[-1].u.expr);
    yyerror("could not determine type of " + str.str(), (yylsp[-1]));
  }
}
#line 7072 "built/tmp/cppBison.yxx.c"
    break;

  case 308:
#line 2524 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_auto));
}
#line 7080 "built/tmp/cppBison.yxx.c"
    break;

  case 309:
#line 2528 "dtool/src/cppparser/cppBison.yxx"
{
  CPPEnumType *enum_type = (yyvsp[-1].u.type)->as_enum_type();
  if (enum_type == nullptr) {
    yyerror("an enumeration type is required", (yylsp[-1]));
    (yyval.u.type) = (yyvsp[-1].u.type);
  } else {
    (yyval.u.type) = enum_type->get_underlying_type();
  }
}
#line 7094 "built/tmp/cppBison.yxx.c"
    break;

  case 310:
#line 2538 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_auto));
}
#line 7102 "built/tmp/cppBison.yxx.c"
    break;

  case 311:
#line 2545 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.type) == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[0].u.identifier)->get_fully_scoped_name(), (yylsp[0]));
  }
  assert((yyval.u.type) != nullptr);
}
#line 7114 "built/tmp/cppBison.yxx.c"
    break;

  case 312:
#line 2556 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = CPPType::new_type((yyvsp[0].u.simple_type));
}
#line 7122 "built/tmp/cppBison.yxx.c"
    break;

  case 313:
#line 2560 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.decl) == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[0].u.identifier)->get_fully_scoped_name(), (yylsp[0]));
  }
  assert((yyval.u.decl) != nullptr);
}
#line 7134 "built/tmp/cppBison.yxx.c"
    break;

  case 314:
#line 2568 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = CPPType::new_type(new CPPTBDType((yyvsp[0].u.identifier)));
}
#line 7142 "built/tmp/cppBison.yxx.c"
    break;

  case 315:
#line 2572 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = CPPType::new_type((yyvsp[0].u.struct_type));
}
#line 7150 "built/tmp/cppBison.yxx.c"
    break;

  case 316:
#line 2576 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = new CPPTypeDeclaration(CPPType::new_type((yyvsp[0].u.struct_type)));
}
#line 7158 "built/tmp/cppBison.yxx.c"
    break;

  case 317:
#line 2580 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = new CPPTypeDeclaration(CPPType::new_type((yyvsp[0].u.enum_type)));
}
#line 7166 "built/tmp/cppBison.yxx.c"
    break;

  case 318:
#line 2584 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != nullptr) {
    (yyval.u.decl) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[-2].u.extension_enum), (yyvsp[0].u.identifier), current_scope, (yylsp[-2]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[0].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != nullptr) {
      scope->define_extension_type(et);
    }
    (yyval.u.decl) = et;
  }
}
#line 7186 "built/tmp/cppBison.yxx.c"
    break;

  case 319:
#line 2600 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type = (yyvsp[-2].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != nullptr) {
    (yyval.u.decl) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[-3].u.extension_enum), (yyvsp[-2].u.identifier), current_scope, (yylsp[-3]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[-2].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != nullptr) {
      scope->define_extension_type(et);
    }
    (yyval.u.decl) = et;
  }
}
#line 7206 "built/tmp/cppBison.yxx.c"
    break;

  case 320:
#line 2616 "dtool/src/cppparser/cppBison.yxx"
{
  yywarning(string("C++ does not permit forward declaration of untyped enum ") + (yyvsp[0].u.identifier)->get_fully_scoped_name(), (yylsp[-1]));

  CPPType *type = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != nullptr) {
    (yyval.u.decl) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[-1].u.extension_enum), (yyvsp[0].u.identifier), current_scope, (yylsp[-1]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[0].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != nullptr) {
      scope->define_extension_type(et);
    }
    (yyval.u.decl) = et;
  }
}
#line 7228 "built/tmp/cppBison.yxx.c"
    break;

  case 321:
#line 2634 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = (yyvsp[-1].u.expr)->determine_type();
  if ((yyval.u.decl) == nullptr) {
    stringstream str;
    str << *(yyvsp[-1].u.expr);
    yyerror("could not determine type of " + str.str(), (yylsp[-1]));
  }
}
#line 7241 "built/tmp/cppBison.yxx.c"
    break;

  case 322:
#line 2643 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_auto));
}
#line 7249 "built/tmp/cppBison.yxx.c"
    break;

  case 323:
#line 2647 "dtool/src/cppparser/cppBison.yxx"
{
  CPPEnumType *enum_type = (yyvsp[-1].u.type)->as_enum_type();
  if (enum_type == nullptr) {
    yyerror("an enumeration type is required", (yylsp[-1]));
    (yyval.u.decl) = (yyvsp[-1].u.type);
  } else {
    (yyval.u.decl) = enum_type->get_underlying_type();
  }
}
#line 7263 "built/tmp/cppBison.yxx.c"
    break;

  case 324:
#line 2657 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_auto));
}
#line 7271 "built/tmp/cppBison.yxx.c"
    break;

  case 325:
#line 2664 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type((yyvsp[0].u.simple_type));
}
#line 7279 "built/tmp/cppBison.yxx.c"
    break;

  case 326:
#line 2668 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.type) == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[0].u.identifier)->get_fully_scoped_name(), (yylsp[0]));
  }
  assert((yyval.u.type) != nullptr);
}
#line 7291 "built/tmp/cppBison.yxx.c"
    break;

  case 327:
#line 2676 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type(new CPPTBDType((yyvsp[0].u.identifier)));
}
#line 7299 "built/tmp/cppBison.yxx.c"
    break;

  case 328:
#line 2680 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != nullptr) {
    (yyval.u.type) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[-2].u.extension_enum), (yyvsp[0].u.identifier), current_scope, (yylsp[-2]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[0].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != nullptr) {
      scope->define_extension_type(et);
    }
    (yyval.u.type) = et;
  }
}
#line 7319 "built/tmp/cppBison.yxx.c"
    break;

  case 329:
#line 2696 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != nullptr) {
    (yyval.u.type) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[-1].u.extension_enum), (yyvsp[0].u.identifier), current_scope, (yylsp[-1]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[0].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != nullptr) {
      scope->define_extension_type(et);
    }
    (yyval.u.type) = et;
  }
}
#line 7339 "built/tmp/cppBison.yxx.c"
    break;

  case 330:
#line 2712 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[-1].u.expr)->determine_type();
  if ((yyval.u.type) == nullptr) {
    stringstream str;
    str << *(yyvsp[-1].u.expr);
    yyerror("could not determine type of " + str.str(), (yylsp[-1]));
  }
}
#line 7352 "built/tmp/cppBison.yxx.c"
    break;

  case 331:
#line 2721 "dtool/src/cppparser/cppBison.yxx"
{
  CPPEnumType *enum_type = (yyvsp[-1].u.type)->as_enum_type();
  if (enum_type == nullptr) {
    yyerror("an enumeration type is required", (yylsp[-1]));
    (yyval.u.type) = (yyvsp[-1].u.type);
  } else {
    (yyval.u.type) = enum_type->get_underlying_type();
  }
}
#line 7366 "built/tmp/cppBison.yxx.c"
    break;

  case 332:
#line 2731 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_auto));
}
#line 7374 "built/tmp/cppBison.yxx.c"
    break;

  case 333:
#line 2738 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.decl) = (yyvsp[0].u.decl);
}
#line 7382 "built/tmp/cppBison.yxx.c"
    break;

  case 334:
#line 2742 "dtool/src/cppparser/cppBison.yxx"
{
  yyerror(string("unknown type '") + (yyvsp[0].u.identifier)->get_fully_scoped_name() + "'", (yylsp[0]));

  (yyval.u.decl) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_unknown));
}
#line 7392 "built/tmp/cppBison.yxx.c"
    break;

  case 335:
#line 2750 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.inst_ident)->unroll_type((yyvsp[-1].u.type));
}
#line 7400 "built/tmp/cppBison.yxx.c"
    break;

  case 336:
#line 2754 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[0].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.type) = (yyvsp[0].u.inst_ident)->unroll_type((yyvsp[-1].u.type));
}
#line 7409 "built/tmp/cppBison.yxx.c"
    break;

  case 337:
#line 2759 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.inst_ident)->unroll_type((yyvsp[-1].u.type));
}
#line 7417 "built/tmp/cppBison.yxx.c"
    break;

  case 338:
#line 2763 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[0].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.type) = (yyvsp[0].u.inst_ident)->unroll_type((yyvsp[-1].u.type));
}
#line 7426 "built/tmp/cppBison.yxx.c"
    break;

  case 343:
#line 2778 "dtool/src/cppparser/cppBison.yxx"
{
  CPPVisibility starting_vis =
  ((yyvsp[-2].u.extension_enum) == CPPExtensionType::T_class) ? V_private : V_public;

  CPPScope *new_scope = new CPPScope(current_scope, CPPNameComponent("anon"),
                                     starting_vis);
  CPPStructType *st = new CPPStructType((yyvsp[-2].u.extension_enum), nullptr, current_scope,
                                        new_scope, (yylsp[-2]).file);
  new_scope->set_struct_type(st);

  push_scope(new_scope);
  push_struct(st);
}
#line 7444 "built/tmp/cppBison.yxx.c"
    break;

  case 344:
#line 2792 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.struct_type) = current_struct;
  current_struct->_incomplete = false;
  pop_struct();
  pop_scope();
}
#line 7455 "built/tmp/cppBison.yxx.c"
    break;

  case 345:
#line 2802 "dtool/src/cppparser/cppBison.yxx"
{
  CPPVisibility starting_vis =
  ((yyvsp[-2].u.extension_enum) == CPPExtensionType::T_class) ? V_private : V_public;

  CPPScope *scope = (yyvsp[0].u.identifier)->get_scope(current_scope, global_scope, current_lexer);
  if (scope == nullptr) {
    scope = current_scope;
  }
  CPPScope *new_scope = new CPPScope(scope, (yyvsp[0].u.identifier)->_names.back(),
                                     starting_vis);

  CPPStructType *st = new CPPStructType((yyvsp[-2].u.extension_enum), (yyvsp[0].u.identifier), current_scope,
                                        new_scope, (yylsp[-2]).file);
  new_scope->set_struct_type(st);
  current_scope->define_extension_type(st);

  push_scope(new_scope);
  push_struct(st);
}
#line 7479 "built/tmp/cppBison.yxx.c"
    break;

  case 346:
#line 2822 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.struct_type) = current_struct;
  current_struct->_incomplete = false;
  pop_struct();
  pop_scope();
}
#line 7490 "built/tmp/cppBison.yxx.c"
    break;

  case 348:
#line 2833 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->_final = true;
}
#line 7498 "built/tmp/cppBison.yxx.c"
    break;

  case 353:
#line 2850 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_unknown, false);
}
#line 7506 "built/tmp/cppBison.yxx.c"
    break;

  case 354:
#line 2854 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_public, false);
}
#line 7514 "built/tmp/cppBison.yxx.c"
    break;

  case 355:
#line 2858 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_protected, false);
}
#line 7522 "built/tmp/cppBison.yxx.c"
    break;

  case 356:
#line 2862 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_private, false);
}
#line 7530 "built/tmp/cppBison.yxx.c"
    break;

  case 357:
#line 2866 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_public, true);
}
#line 7538 "built/tmp/cppBison.yxx.c"
    break;

  case 358:
#line 2870 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_protected, true);
}
#line 7546 "built/tmp/cppBison.yxx.c"
    break;

  case 359:
#line 2874 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_private, true);
}
#line 7554 "built/tmp/cppBison.yxx.c"
    break;

  case 360:
#line 2878 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_public, true);
}
#line 7562 "built/tmp/cppBison.yxx.c"
    break;

  case 361:
#line 2882 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_protected, true);
}
#line 7570 "built/tmp/cppBison.yxx.c"
    break;

  case 362:
#line 2886 "dtool/src/cppparser/cppBison.yxx"
{
  current_struct->append_derivation((yyvsp[0].u.type), V_private, true);
}
#line 7578 "built/tmp/cppBison.yxx.c"
    break;

  case 363:
#line 2893 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.enum_type) = current_enum;
  current_enum = nullptr;
}
#line 7587 "built/tmp/cppBison.yxx.c"
    break;

  case 364:
#line 2901 "dtool/src/cppparser/cppBison.yxx"
{
  current_enum = new CPPEnumType((yyvsp[-2].u.extension_enum), nullptr, (yyvsp[0].u.type), current_scope, nullptr, (yylsp[-2]).file);
}
#line 7595 "built/tmp/cppBison.yxx.c"
    break;

  case 365:
#line 2905 "dtool/src/cppparser/cppBison.yxx"
{
  current_enum = new CPPEnumType((yyvsp[0].u.extension_enum), nullptr, current_scope, nullptr, (yylsp[0]).file);
}
#line 7603 "built/tmp/cppBison.yxx.c"
    break;

  case 366:
#line 2909 "dtool/src/cppparser/cppBison.yxx"
{
  CPPScope *new_scope = new CPPScope(current_scope, (yyvsp[-2].u.identifier)->_names.back(), V_public);
  current_enum = new CPPEnumType((yyvsp[-3].u.extension_enum), (yyvsp[-2].u.identifier), (yyvsp[0].u.type), current_scope, new_scope, (yylsp[-3]).file);
}
#line 7612 "built/tmp/cppBison.yxx.c"
    break;

  case 367:
#line 2914 "dtool/src/cppparser/cppBison.yxx"
{
  CPPScope *new_scope = new CPPScope(current_scope, (yyvsp[0].u.identifier)->_names.back(), V_public);
  current_enum = new CPPEnumType((yyvsp[-1].u.extension_enum), (yyvsp[0].u.identifier), current_scope, new_scope, (yylsp[-1]).file);
}
#line 7621 "built/tmp/cppBison.yxx.c"
    break;

  case 368:
#line 2922 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type((yyvsp[0].u.simple_type));
}
#line 7629 "built/tmp/cppBison.yxx.c"
    break;

  case 369:
#line 2926 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
}
#line 7637 "built/tmp/cppBison.yxx.c"
    break;

  case 371:
#line 2934 "dtool/src/cppparser/cppBison.yxx"
{
  assert(current_enum != nullptr);
  current_enum->add_element((yyvsp[-1].u.identifier)->get_simple_name(), nullptr, current_lexer, (yylsp[-1]));
}
#line 7646 "built/tmp/cppBison.yxx.c"
    break;

  case 372:
#line 2939 "dtool/src/cppparser/cppBison.yxx"
{
  assert(current_enum != nullptr);
  current_enum->add_element((yyvsp[-3].u.identifier)->get_simple_name(), (yyvsp[-1].u.expr), current_lexer, (yylsp[-3]));
}
#line 7655 "built/tmp/cppBison.yxx.c"
    break;

  case 374:
#line 2947 "dtool/src/cppparser/cppBison.yxx"
{
  assert(current_enum != nullptr);
  current_enum->add_element((yyvsp[0].u.identifier)->get_simple_name(), nullptr, current_lexer, (yylsp[0]));
}
#line 7664 "built/tmp/cppBison.yxx.c"
    break;

  case 375:
#line 2952 "dtool/src/cppparser/cppBison.yxx"
{
  assert(current_enum != nullptr);
  current_enum->add_element((yyvsp[-2].u.identifier)->get_simple_name(), (yyvsp[0].u.expr), current_lexer, (yylsp[-2]));
}
#line 7673 "built/tmp/cppBison.yxx.c"
    break;

  case 376:
#line 2960 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.extension_enum) = CPPExtensionType::T_enum;
}
#line 7681 "built/tmp/cppBison.yxx.c"
    break;

  case 377:
#line 2964 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.extension_enum) = CPPExtensionType::T_enum_class;
}
#line 7689 "built/tmp/cppBison.yxx.c"
    break;

  case 378:
#line 2968 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.extension_enum) = CPPExtensionType::T_enum_struct;
}
#line 7697 "built/tmp/cppBison.yxx.c"
    break;

  case 379:
#line 2975 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.extension_enum) = CPPExtensionType::T_class;
}
#line 7705 "built/tmp/cppBison.yxx.c"
    break;

  case 380:
#line 2979 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.extension_enum) = CPPExtensionType::T_struct;
}
#line 7713 "built/tmp/cppBison.yxx.c"
    break;

  case 381:
#line 2983 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.extension_enum) = CPPExtensionType::T_union;
}
#line 7721 "built/tmp/cppBison.yxx.c"
    break;

  case 382:
#line 2990 "dtool/src/cppparser/cppBison.yxx"
{
  CPPScope *scope = (yyvsp[-1].u.identifier)->find_scope(current_scope, global_scope, current_lexer);
  if (scope == nullptr) {
    // This must be a new namespace declaration.
    CPPScope *parent_scope =
      (yyvsp[-1].u.identifier)->get_scope(current_scope, global_scope, current_lexer);
    if (parent_scope == nullptr) {
      parent_scope = current_scope;
    }
    scope = new CPPScope(parent_scope, (yyvsp[-1].u.identifier)->_names.back(), V_public);
  }

  CPPNamespace *nspace = new CPPNamespace((yyvsp[-1].u.identifier), scope, (yylsp[-2]).file);
  current_scope->add_declaration(nspace, global_scope, current_lexer, (yylsp[-2]));
  current_scope->define_namespace(nspace);
  push_scope(scope);
}
#line 7743 "built/tmp/cppBison.yxx.c"
    break;

  case 383:
#line 3008 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
}
#line 7751 "built/tmp/cppBison.yxx.c"
    break;

  case 384:
#line 3012 "dtool/src/cppparser/cppBison.yxx"
{
  CPPScope *scope = (yyvsp[-1].u.identifier)->find_scope(current_scope, global_scope, current_lexer);
  if (scope == nullptr) {
    // This must be a new namespace declaration.
    CPPScope *parent_scope =
      (yyvsp[-1].u.identifier)->get_scope(current_scope, global_scope, current_lexer);
    if (parent_scope == nullptr) {
      parent_scope = current_scope;
    }
    scope = new CPPScope(parent_scope, (yyvsp[-1].u.identifier)->_names.back(), V_public);
  }

  CPPNamespace *nspace = new CPPNamespace((yyvsp[-1].u.identifier), scope, (yylsp[-2]).file);
  nspace->_is_inline = true;
  current_scope->add_declaration(nspace, global_scope, current_lexer, (yylsp[-2]));
  current_scope->define_namespace(nspace);
  push_scope(scope);
}
#line 7774 "built/tmp/cppBison.yxx.c"
    break;

  case 385:
#line 3031 "dtool/src/cppparser/cppBison.yxx"
{
  pop_scope();
}
#line 7782 "built/tmp/cppBison.yxx.c"
    break;

  case 388:
#line 3040 "dtool/src/cppparser/cppBison.yxx"
{
  CPPUsing *using_decl = new CPPUsing((yyvsp[-1].u.identifier), false, (yylsp[-2]).file);
  current_scope->add_declaration(using_decl, global_scope, current_lexer, (yylsp[-2]));
  current_scope->add_using(using_decl, global_scope, current_lexer);
}
#line 7792 "built/tmp/cppBison.yxx.c"
    break;

  case 389:
#line 3046 "dtool/src/cppparser/cppBison.yxx"
{
  // This is really just an alternative way to declare a typedef.
  CPPTypedefType *typedef_type = new CPPTypedefType((yyvsp[-1].u.type), (yyvsp[-3].u.identifier), current_scope);
  typedef_type->_using = true;
  current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[-4]));
}
#line 7803 "built/tmp/cppBison.yxx.c"
    break;

  case 390:
#line 3053 "dtool/src/cppparser/cppBison.yxx"
{
  CPPUsing *using_decl = new CPPUsing((yyvsp[-1].u.identifier), true, (yylsp[-3]).file);
  current_scope->add_declaration(using_decl, global_scope, current_lexer, (yylsp[-3]));
  current_scope->add_using(using_decl, global_scope, current_lexer);
}
#line 7813 "built/tmp/cppBison.yxx.c"
    break;

  case 394:
#line 3068 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_bool);
}
#line 7821 "built/tmp/cppBison.yxx.c"
    break;

  case 395:
#line 3072 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_char);
}
#line 7829 "built/tmp/cppBison.yxx.c"
    break;

  case 396:
#line 3076 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_wchar_t);
}
#line 7837 "built/tmp/cppBison.yxx.c"
    break;

  case 397:
#line 3080 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_char16_t);
}
#line 7845 "built/tmp/cppBison.yxx.c"
    break;

  case 398:
#line 3084 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_char32_t);
}
#line 7853 "built/tmp/cppBison.yxx.c"
    break;

  case 399:
#line 3088 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int,
                         CPPSimpleType::F_short);
}
#line 7862 "built/tmp/cppBison.yxx.c"
    break;

  case 400:
#line 3093 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int,
                         CPPSimpleType::F_long);
}
#line 7871 "built/tmp/cppBison.yxx.c"
    break;

  case 401:
#line 3098 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int,
                         CPPSimpleType::F_unsigned);
}
#line 7880 "built/tmp/cppBison.yxx.c"
    break;

  case 402:
#line 3103 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int,
                         CPPSimpleType::F_signed);
}
#line 7889 "built/tmp/cppBison.yxx.c"
    break;

  case 403:
#line 3108 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int);
}
#line 7897 "built/tmp/cppBison.yxx.c"
    break;

  case 404:
#line 3112 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = (yyvsp[0].u.simple_type);
  (yyval.u.simple_type)->_flags |= CPPSimpleType::F_short;
}
#line 7906 "built/tmp/cppBison.yxx.c"
    break;

  case 405:
#line 3117 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = (yyvsp[0].u.simple_type);
  if ((yyval.u.simple_type)->_flags & CPPSimpleType::F_long) {
    (yyval.u.simple_type)->_flags |= CPPSimpleType::F_longlong;
  } else {
    (yyval.u.simple_type)->_flags |= CPPSimpleType::F_long;
  }
}
#line 7919 "built/tmp/cppBison.yxx.c"
    break;

  case 406:
#line 3126 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = (yyvsp[0].u.simple_type);
  (yyval.u.simple_type)->_flags |= CPPSimpleType::F_unsigned;
}
#line 7928 "built/tmp/cppBison.yxx.c"
    break;

  case 407:
#line 3131 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = (yyvsp[0].u.simple_type);
  (yyval.u.simple_type)->_flags |= CPPSimpleType::F_signed;
}
#line 7937 "built/tmp/cppBison.yxx.c"
    break;

  case 408:
#line 3139 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_float);
}
#line 7945 "built/tmp/cppBison.yxx.c"
    break;

  case 409:
#line 3143 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_double);
}
#line 7953 "built/tmp/cppBison.yxx.c"
    break;

  case 410:
#line 3147 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_double,
                         CPPSimpleType::F_long);
}
#line 7962 "built/tmp/cppBison.yxx.c"
    break;

  case 411:
#line 3155 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_void);
}
#line 7970 "built/tmp/cppBison.yxx.c"
    break;

  case 412:
#line 3164 "dtool/src/cppparser/cppBison.yxx"
{
  current_lexer->_resolve_identifiers = false;
}
#line 7978 "built/tmp/cppBison.yxx.c"
    break;

  case 413:
#line 3168 "dtool/src/cppparser/cppBison.yxx"
{
  current_lexer->_resolve_identifiers = true;
}
#line 7986 "built/tmp/cppBison.yxx.c"
    break;

  case 521:
#line 3212 "dtool/src/cppparser/cppBison.yxx"
{
}
#line 7993 "built/tmp/cppBison.yxx.c"
    break;

  case 545:
#line 3221 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 8001 "built/tmp/cppBison.yxx.c"
    break;

  case 546:
#line 3225 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 8009 "built/tmp/cppBison.yxx.c"
    break;

  case 547:
#line 3232 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = nullptr;
}
#line 8017 "built/tmp/cppBison.yxx.c"
    break;

  case 548:
#line 3236 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 8025 "built/tmp/cppBison.yxx.c"
    break;

  case 549:
#line 3243 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 8033 "built/tmp/cppBison.yxx.c"
    break;

  case 550:
#line 3247 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(',', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8041 "built/tmp/cppBison.yxx.c"
    break;

  case 551:
#line 3254 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 8049 "built/tmp/cppBison.yxx.c"
    break;

  case 552:
#line 3258 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-2].u.type), (yyvsp[0].u.expr)));
}
#line 8057 "built/tmp/cppBison.yxx.c"
    break;

  case 553:
#line 3262 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_static_cast));
}
#line 8065 "built/tmp/cppBison.yxx.c"
    break;

  case 554:
#line 3266 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_dynamic_cast));
}
#line 8073 "built/tmp/cppBison.yxx.c"
    break;

  case 555:
#line 3270 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_const_cast));
}
#line 8081 "built/tmp/cppBison.yxx.c"
    break;

  case 556:
#line 3274 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_reinterpret_cast));
}
#line 8089 "built/tmp/cppBison.yxx.c"
    break;

  case 557:
#line 3278 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func((yyvsp[-1].u.type)));
}
#line 8097 "built/tmp/cppBison.yxx.c"
    break;

  case 558:
#line 3282 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *arg = (yyvsp[-1].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (arg == nullptr) {
    yyerror("undefined sizeof argument: " + (yyvsp[-1].u.identifier)->get_fully_scoped_name(), (yylsp[-1]));
  } else if (arg->get_subtype() == CPPDeclaration::ST_instance) {
    CPPInstance *inst = arg->as_instance();
    (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func(inst->_type));
  } else {
    (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func(arg->as_type()));
  }
}
#line 8113 "built/tmp/cppBison.yxx.c"
    break;

  case 559:
#line 3294 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_ellipsis_func((yyvsp[-1].u.identifier)));
}
#line 8121 "built/tmp/cppBison.yxx.c"
    break;

  case 560:
#line 3298 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::alignof_func((yyvsp[-1].u.type)));
}
#line 8129 "built/tmp/cppBison.yxx.c"
    break;

  case 561:
#line 3302 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_NOT, (yyvsp[0].u.expr));
}
#line 8137 "built/tmp/cppBison.yxx.c"
    break;

  case 562:
#line 3306 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_NEGATE, (yyvsp[0].u.expr));
}
#line 8145 "built/tmp/cppBison.yxx.c"
    break;

  case 563:
#line 3310 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_MINUS, (yyvsp[0].u.expr));
}
#line 8153 "built/tmp/cppBison.yxx.c"
    break;

  case 564:
#line 3314 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_PLUS, (yyvsp[0].u.expr));
}
#line 8161 "built/tmp/cppBison.yxx.c"
    break;

  case 565:
#line 3318 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_STAR, (yyvsp[0].u.expr));
}
#line 8169 "built/tmp/cppBison.yxx.c"
    break;

  case 566:
#line 3322 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_REF, (yyvsp[0].u.expr));
}
#line 8177 "built/tmp/cppBison.yxx.c"
    break;

  case 567:
#line 3326 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('*', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8185 "built/tmp/cppBison.yxx.c"
    break;

  case 568:
#line 3330 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('/', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8193 "built/tmp/cppBison.yxx.c"
    break;

  case 569:
#line 3334 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('%', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8201 "built/tmp/cppBison.yxx.c"
    break;

  case 570:
#line 3338 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('+', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8209 "built/tmp/cppBison.yxx.c"
    break;

  case 571:
#line 3342 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('-', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8217 "built/tmp/cppBison.yxx.c"
    break;

  case 572:
#line 3346 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('|', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8225 "built/tmp/cppBison.yxx.c"
    break;

  case 573:
#line 3350 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('^', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8233 "built/tmp/cppBison.yxx.c"
    break;

  case 574:
#line 3354 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('&', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8241 "built/tmp/cppBison.yxx.c"
    break;

  case 575:
#line 3358 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(OROR, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8249 "built/tmp/cppBison.yxx.c"
    break;

  case 576:
#line 3362 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(ANDAND, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8257 "built/tmp/cppBison.yxx.c"
    break;

  case 577:
#line 3366 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(EQCOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8265 "built/tmp/cppBison.yxx.c"
    break;

  case 578:
#line 3370 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(NECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8273 "built/tmp/cppBison.yxx.c"
    break;

  case 579:
#line 3374 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(LECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8281 "built/tmp/cppBison.yxx.c"
    break;

  case 580:
#line 3378 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(GECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8289 "built/tmp/cppBison.yxx.c"
    break;

  case 581:
#line 3382 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(LSHIFT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8297 "built/tmp/cppBison.yxx.c"
    break;

  case 582:
#line 3386 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(RSHIFT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8305 "built/tmp/cppBison.yxx.c"
    break;

  case 583:
#line 3390 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('?', (yyvsp[-4].u.expr), (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8313 "built/tmp/cppBison.yxx.c"
    break;

  case 584:
#line 3394 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('[', (yyvsp[-3].u.expr), (yyvsp[-1].u.expr));
}
#line 8321 "built/tmp/cppBison.yxx.c"
    break;

  case 585:
#line 3398 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[-3].u.expr), (yyvsp[-1].u.expr));
}
#line 8329 "built/tmp/cppBison.yxx.c"
    break;

  case 586:
#line 3402 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[-2].u.expr));
}
#line 8337 "built/tmp/cppBison.yxx.c"
    break;

  case 587:
#line 3406 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('.', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8345 "built/tmp/cppBison.yxx.c"
    break;

  case 588:
#line 3410 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(POINTSAT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8353 "built/tmp/cppBison.yxx.c"
    break;

  case 589:
#line 3414 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[-1].u.expr);
}
#line 8361 "built/tmp/cppBison.yxx.c"
    break;

  case 590:
#line 3422 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 8369 "built/tmp/cppBison.yxx.c"
    break;

  case 591:
#line 3426 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-2].u.type), (yyvsp[0].u.expr)));
}
#line 8377 "built/tmp/cppBison.yxx.c"
    break;

  case 592:
#line 3430 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_static_cast));
}
#line 8385 "built/tmp/cppBison.yxx.c"
    break;

  case 593:
#line 3434 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_dynamic_cast));
}
#line 8393 "built/tmp/cppBison.yxx.c"
    break;

  case 594:
#line 3438 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_const_cast));
}
#line 8401 "built/tmp/cppBison.yxx.c"
    break;

  case 595:
#line 3442 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_reinterpret_cast));
}
#line 8409 "built/tmp/cppBison.yxx.c"
    break;

  case 596:
#line 3446 "dtool/src/cppparser/cppBison.yxx"
{
  // A constructor call.
  CPPType *type = (yyvsp[-3].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[-3].u.identifier)->get_fully_scoped_name(), (yylsp[-3]));
  }
  assert(type != nullptr);
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8423 "built/tmp/cppBison.yxx.c"
    break;

  case 597:
#line 3456 "dtool/src/cppparser/cppBison.yxx"
{
  // Aggregate initialization.
  CPPType *type = (yyvsp[-3].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type == nullptr) {
    yyerror(string("internal error resolving type ") + (yyvsp[-3].u.identifier)->get_fully_scoped_name(), (yylsp[-3]));
  }
  assert(type != nullptr);
  (yyval.u.expr) = new CPPExpression(CPPExpression::aggregate_init_op(type, (yyvsp[-1].u.expr)));
}
#line 8437 "built/tmp/cppBison.yxx.c"
    break;

  case 598:
#line 3466 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8447 "built/tmp/cppBison.yxx.c"
    break;

  case 599:
#line 3472 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_char));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8457 "built/tmp/cppBison.yxx.c"
    break;

  case 600:
#line 3478 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_wchar_t));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8467 "built/tmp/cppBison.yxx.c"
    break;

  case 601:
#line 3484 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_char16_t));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8477 "built/tmp/cppBison.yxx.c"
    break;

  case 602:
#line 3490 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_char32_t));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8487 "built/tmp/cppBison.yxx.c"
    break;

  case 603:
#line 3496 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_bool));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8497 "built/tmp/cppBison.yxx.c"
    break;

  case 604:
#line 3502 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int,
                                        CPPSimpleType::F_short));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8508 "built/tmp/cppBison.yxx.c"
    break;

  case 605:
#line 3509 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int,
                                        CPPSimpleType::F_long));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8519 "built/tmp/cppBison.yxx.c"
    break;

  case 606:
#line 3516 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int,
                                        CPPSimpleType::F_unsigned));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8530 "built/tmp/cppBison.yxx.c"
    break;

  case 607:
#line 3523 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int,
                                        CPPSimpleType::F_signed));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8541 "built/tmp/cppBison.yxx.c"
    break;

  case 608:
#line 3530 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_float));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8551 "built/tmp/cppBison.yxx.c"
    break;

  case 609:
#line 3536 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_double));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[-1].u.expr)));
}
#line 8561 "built/tmp/cppBison.yxx.c"
    break;

  case 610:
#line 3542 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func((yyvsp[-1].u.type)));
}
#line 8569 "built/tmp/cppBison.yxx.c"
    break;

  case 611:
#line 3546 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *arg = (yyvsp[-1].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (arg == nullptr) {
    yyerror("undefined sizeof argument: " + (yyvsp[-1].u.identifier)->get_fully_scoped_name(), (yylsp[-1]));
  } else if (arg->get_subtype() == CPPDeclaration::ST_instance) {
    CPPInstance *inst = arg->as_instance();
    (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func(inst->_type));
  } else {
    (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func(arg->as_type()));
  }
}
#line 8585 "built/tmp/cppBison.yxx.c"
    break;

  case 612:
#line 3558 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_ellipsis_func((yyvsp[-1].u.identifier)));
}
#line 8593 "built/tmp/cppBison.yxx.c"
    break;

  case 613:
#line 3562 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::alignof_func((yyvsp[-1].u.type)));
}
#line 8601 "built/tmp/cppBison.yxx.c"
    break;

  case 614:
#line 3566 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::new_op((yyvsp[0].u.type)));
}
#line 8609 "built/tmp/cppBison.yxx.c"
    break;

  case 615:
#line 3570 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::new_op((yyvsp[-3].u.type), (yyvsp[-1].u.expr)));
}
#line 8617 "built/tmp/cppBison.yxx.c"
    break;

  case 616:
#line 3574 "dtool/src/cppparser/cppBison.yxx"
{
  CPPIdentifier ident("");
  ident.add_name("std");
  ident.add_name("type_info");
  CPPType *std_type_info = ident.find_type(current_scope, global_scope, false, current_lexer);
  if (!std_type_info) {
    yywarning("cannot use typeid before including <typeinfo>", (yylsp[-3]));
  }
  (yyval.u.expr) = new CPPExpression(CPPExpression::typeid_op((yyvsp[-1].u.type), std_type_info));
}
#line 8632 "built/tmp/cppBison.yxx.c"
    break;

  case 617:
#line 3585 "dtool/src/cppparser/cppBison.yxx"
{
  CPPIdentifier ident("");
  ident.add_name("std");
  ident.add_name("type_info");
  CPPType *std_type_info = ident.find_type(current_scope, global_scope, false, current_lexer);
  if (!std_type_info) {
    yywarning("cannot use typeid before including <typeinfo>", (yylsp[-3]));
  }
  (yyval.u.expr) = new CPPExpression(CPPExpression::typeid_op((yyvsp[-1].u.expr), std_type_info));
}
#line 8647 "built/tmp/cppBison.yxx.c"
    break;

  case 618:
#line 3596 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_NOT, (yyvsp[0].u.expr));
}
#line 8655 "built/tmp/cppBison.yxx.c"
    break;

  case 619:
#line 3600 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_NEGATE, (yyvsp[0].u.expr));
}
#line 8663 "built/tmp/cppBison.yxx.c"
    break;

  case 620:
#line 3604 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_MINUS, (yyvsp[0].u.expr));
}
#line 8671 "built/tmp/cppBison.yxx.c"
    break;

  case 621:
#line 3608 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_PLUS, (yyvsp[0].u.expr));
}
#line 8679 "built/tmp/cppBison.yxx.c"
    break;

  case 622:
#line 3612 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_STAR, (yyvsp[0].u.expr));
}
#line 8687 "built/tmp/cppBison.yxx.c"
    break;

  case 623:
#line 3616 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_REF, (yyvsp[0].u.expr));
}
#line 8695 "built/tmp/cppBison.yxx.c"
    break;

  case 624:
#line 3620 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('*', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8703 "built/tmp/cppBison.yxx.c"
    break;

  case 625:
#line 3624 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('/', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8711 "built/tmp/cppBison.yxx.c"
    break;

  case 626:
#line 3628 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('%', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8719 "built/tmp/cppBison.yxx.c"
    break;

  case 627:
#line 3632 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('+', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8727 "built/tmp/cppBison.yxx.c"
    break;

  case 628:
#line 3636 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('-', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8735 "built/tmp/cppBison.yxx.c"
    break;

  case 629:
#line 3640 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('|', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8743 "built/tmp/cppBison.yxx.c"
    break;

  case 630:
#line 3644 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('^', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8751 "built/tmp/cppBison.yxx.c"
    break;

  case 631:
#line 3648 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('&', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8759 "built/tmp/cppBison.yxx.c"
    break;

  case 632:
#line 3652 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(OROR, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8767 "built/tmp/cppBison.yxx.c"
    break;

  case 633:
#line 3656 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(ANDAND, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8775 "built/tmp/cppBison.yxx.c"
    break;

  case 634:
#line 3660 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(EQCOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8783 "built/tmp/cppBison.yxx.c"
    break;

  case 635:
#line 3664 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(NECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8791 "built/tmp/cppBison.yxx.c"
    break;

  case 636:
#line 3668 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(LECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8799 "built/tmp/cppBison.yxx.c"
    break;

  case 637:
#line 3672 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(GECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8807 "built/tmp/cppBison.yxx.c"
    break;

  case 638:
#line 3676 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('<', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8815 "built/tmp/cppBison.yxx.c"
    break;

  case 639:
#line 3680 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('>', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8823 "built/tmp/cppBison.yxx.c"
    break;

  case 640:
#line 3684 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(LSHIFT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8831 "built/tmp/cppBison.yxx.c"
    break;

  case 641:
#line 3688 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(RSHIFT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8839 "built/tmp/cppBison.yxx.c"
    break;

  case 642:
#line 3692 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('?', (yyvsp[-4].u.expr), (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8847 "built/tmp/cppBison.yxx.c"
    break;

  case 643:
#line 3696 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('[', (yyvsp[-3].u.expr), (yyvsp[-1].u.expr));
}
#line 8855 "built/tmp/cppBison.yxx.c"
    break;

  case 644:
#line 3700 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[-3].u.expr), (yyvsp[-1].u.expr));
}
#line 8863 "built/tmp/cppBison.yxx.c"
    break;

  case 645:
#line 3704 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[-2].u.expr));
}
#line 8871 "built/tmp/cppBison.yxx.c"
    break;

  case 646:
#line 3708 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('.', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8879 "built/tmp/cppBison.yxx.c"
    break;

  case 647:
#line 3712 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(POINTSAT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 8887 "built/tmp/cppBison.yxx.c"
    break;

  case 648:
#line 3716 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[-1].u.expr);
}
#line 8895 "built/tmp/cppBison.yxx.c"
    break;

  case 649:
#line 3723 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].u.integer));
}
#line 8903 "built/tmp/cppBison.yxx.c"
    break;

  case 650:
#line 3727 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(true);
}
#line 8911 "built/tmp/cppBison.yxx.c"
    break;

  case 651:
#line 3731 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(false);
}
#line 8919 "built/tmp/cppBison.yxx.c"
    break;

  case 652:
#line 3735 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].u.integer));
}
#line 8927 "built/tmp/cppBison.yxx.c"
    break;

  case 653:
#line 3739 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].u.real));
}
#line 8935 "built/tmp/cppBison.yxx.c"
    break;

  case 654:
#line 3743 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 8943 "built/tmp/cppBison.yxx.c"
    break;

  case 655:
#line 3747 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 8951 "built/tmp/cppBison.yxx.c"
    break;

  case 656:
#line 3751 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].u.identifier), current_scope, global_scope, current_lexer);
}
#line 8959 "built/tmp/cppBison.yxx.c"
    break;

  case 657:
#line 3755 "dtool/src/cppparser/cppBison.yxx"
{
  // A variable named "final".  C++11 explicitly permits this.
  CPPIdentifier *ident = new CPPIdentifier("final", (yylsp[0]));
  (yyval.u.expr) = new CPPExpression(ident, current_scope, global_scope, current_lexer);
}
#line 8969 "built/tmp/cppBison.yxx.c"
    break;

  case 658:
#line 3761 "dtool/src/cppparser/cppBison.yxx"
{
  // A variable named "override".  C++11 explicitly permits this.
  CPPIdentifier *ident = new CPPIdentifier("override", (yylsp[0]));
  (yyval.u.expr) = new CPPExpression(ident, current_scope, global_scope, current_lexer);
}
#line 8979 "built/tmp/cppBison.yxx.c"
    break;

  case 659:
#line 3767 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_nullptr());
}
#line 8987 "built/tmp/cppBison.yxx.c"
    break;

  case 660:
#line 3771 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[-6].u.closure_type)->_flags = (yyvsp[-4].u.integer);
  (yyvsp[-6].u.closure_type)->_return_type = (yyvsp[-3].u.type);
  (yyval.u.expr) = new CPPExpression(CPPExpression::lambda((yyvsp[-6].u.closure_type)));
}
#line 8997 "built/tmp/cppBison.yxx.c"
    break;

  case 661:
#line 3777 "dtool/src/cppparser/cppBison.yxx"
{
  (yyvsp[-9].u.closure_type)->_parameters = (yyvsp[-6].u.param_list);
  (yyvsp[-9].u.closure_type)->_flags = (yyvsp[-4].u.integer);
  (yyvsp[-9].u.closure_type)->_return_type = (yyvsp[-3].u.type);
  (yyval.u.expr) = new CPPExpression(CPPExpression::lambda((yyvsp[-9].u.closure_type)));
}
#line 9008 "built/tmp/cppBison.yxx.c"
    break;

  case 662:
#line 3784 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_HAS_VIRTUAL_DESTRUCTOR, (yyvsp[-1].u.type)));
}
#line 9016 "built/tmp/cppBison.yxx.c"
    break;

  case 663:
#line 3788 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_ABSTRACT, (yyvsp[-1].u.type)));
}
#line 9024 "built/tmp/cppBison.yxx.c"
    break;

  case 664:
#line 3792 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_CLASS, (yyvsp[-3].u.type), (yyvsp[-1].u.type)));
}
#line 9032 "built/tmp/cppBison.yxx.c"
    break;

  case 665:
#line 3796 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_CLASS, (yyvsp[-1].u.type)));
}
#line 9040 "built/tmp/cppBison.yxx.c"
    break;

  case 666:
#line 3800 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_CONSTRUCTIBLE, (yyvsp[-1].u.type)));
}
#line 9048 "built/tmp/cppBison.yxx.c"
    break;

  case 667:
#line 3804 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_CONSTRUCTIBLE, (yyvsp[-3].u.type), (yyvsp[-1].u.type)));
}
#line 9056 "built/tmp/cppBison.yxx.c"
    break;

  case 668:
#line 3808 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_CONVERTIBLE_TO, (yyvsp[-3].u.type), (yyvsp[-1].u.type)));
}
#line 9064 "built/tmp/cppBison.yxx.c"
    break;

  case 669:
#line 3812 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_DESTRUCTIBLE, (yyvsp[-1].u.type)));
}
#line 9072 "built/tmp/cppBison.yxx.c"
    break;

  case 670:
#line 3816 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_EMPTY, (yyvsp[-1].u.type)));
}
#line 9080 "built/tmp/cppBison.yxx.c"
    break;

  case 671:
#line 3820 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_ENUM, (yyvsp[-1].u.type)));
}
#line 9088 "built/tmp/cppBison.yxx.c"
    break;

  case 672:
#line 3824 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_FINAL, (yyvsp[-1].u.type)));
}
#line 9096 "built/tmp/cppBison.yxx.c"
    break;

  case 673:
#line 3828 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_FUNDAMENTAL, (yyvsp[-1].u.type)));
}
#line 9104 "built/tmp/cppBison.yxx.c"
    break;

  case 674:
#line 3832 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_POD, (yyvsp[-1].u.type)));
}
#line 9112 "built/tmp/cppBison.yxx.c"
    break;

  case 675:
#line 3836 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_POLYMORPHIC, (yyvsp[-1].u.type)));
}
#line 9120 "built/tmp/cppBison.yxx.c"
    break;

  case 676:
#line 3840 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_STANDARD_LAYOUT, (yyvsp[-1].u.type)));
}
#line 9128 "built/tmp/cppBison.yxx.c"
    break;

  case 677:
#line 3844 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_TRIVIAL, (yyvsp[-1].u.type)));
}
#line 9136 "built/tmp/cppBison.yxx.c"
    break;

  case 678:
#line 3848 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::type_trait(KW_IS_UNION, (yyvsp[-1].u.type)));
}
#line 9144 "built/tmp/cppBison.yxx.c"
    break;

  case 679:
#line 3862 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 9152 "built/tmp/cppBison.yxx.c"
    break;

  case 680:
#line 3866 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-2].u.type), (yyvsp[0].u.expr)));
}
#line 9160 "built/tmp/cppBison.yxx.c"
    break;

  case 681:
#line 3870 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_static_cast));
}
#line 9168 "built/tmp/cppBison.yxx.c"
    break;

  case 682:
#line 3874 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_dynamic_cast));
}
#line 9176 "built/tmp/cppBison.yxx.c"
    break;

  case 683:
#line 3878 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_const_cast));
}
#line 9184 "built/tmp/cppBison.yxx.c"
    break;

  case 684:
#line 3882 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[-4].u.type), (yyvsp[-1].u.expr), CPPExpression::T_reinterpret_cast));
}
#line 9192 "built/tmp/cppBison.yxx.c"
    break;

  case 685:
#line 3886 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func((yyvsp[-1].u.type)));
}
#line 9200 "built/tmp/cppBison.yxx.c"
    break;

  case 686:
#line 3890 "dtool/src/cppparser/cppBison.yxx"
{
  CPPDeclaration *arg = (yyvsp[-1].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (arg == nullptr) {
    yyerror("undefined sizeof argument: " + (yyvsp[-1].u.identifier)->get_fully_scoped_name(), (yylsp[-1]));
  } else if (arg->get_subtype() == CPPDeclaration::ST_instance) {
    CPPInstance *inst = arg->as_instance();
    (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func(inst->_type));
  } else {
    (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func(arg->as_type()));
  }
}
#line 9216 "built/tmp/cppBison.yxx.c"
    break;

  case 687:
#line 3902 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_ellipsis_func((yyvsp[-1].u.identifier)));
}
#line 9224 "built/tmp/cppBison.yxx.c"
    break;

  case 688:
#line 3906 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::alignof_func((yyvsp[-1].u.type)));
}
#line 9232 "built/tmp/cppBison.yxx.c"
    break;

  case 689:
#line 3910 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::new_op((yyvsp[0].u.type)));
}
#line 9240 "built/tmp/cppBison.yxx.c"
    break;

  case 690:
#line 3914 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::new_op((yyvsp[-3].u.type), (yyvsp[-1].u.expr)));
}
#line 9248 "built/tmp/cppBison.yxx.c"
    break;

  case 691:
#line 3918 "dtool/src/cppparser/cppBison.yxx"
{
  CPPIdentifier ident("");
  ident.add_name("std");
  ident.add_name("type_info");
  CPPType *std_type_info = ident.find_type(current_scope, global_scope, false, current_lexer);
  if (!std_type_info) {
    yywarning("cannot use typeid before including <typeinfo>", (yylsp[-3]));
  }
  (yyval.u.expr) = new CPPExpression(CPPExpression::typeid_op((yyvsp[-1].u.type), std_type_info));
}
#line 9263 "built/tmp/cppBison.yxx.c"
    break;

  case 692:
#line 3929 "dtool/src/cppparser/cppBison.yxx"
{
  CPPIdentifier ident("");
  ident.add_name("std");
  ident.add_name("type_info");
  CPPType *std_type_info = ident.find_type(current_scope, global_scope, false, current_lexer);
  if (!std_type_info) {
    yywarning("cannot use typeid before including <typeinfo>", (yylsp[-3]));
  }
  (yyval.u.expr) = new CPPExpression(CPPExpression::typeid_op((yyvsp[-1].u.expr), std_type_info));
}
#line 9278 "built/tmp/cppBison.yxx.c"
    break;

  case 693:
#line 3940 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_NOT, (yyvsp[0].u.expr));
}
#line 9286 "built/tmp/cppBison.yxx.c"
    break;

  case 694:
#line 3944 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_NEGATE, (yyvsp[0].u.expr));
}
#line 9294 "built/tmp/cppBison.yxx.c"
    break;

  case 695:
#line 3948 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_MINUS, (yyvsp[0].u.expr));
}
#line 9302 "built/tmp/cppBison.yxx.c"
    break;

  case 696:
#line 3952 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_PLUS, (yyvsp[0].u.expr));
}
#line 9310 "built/tmp/cppBison.yxx.c"
    break;

  case 697:
#line 3956 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(UNARY_REF, (yyvsp[0].u.expr));
}
#line 9318 "built/tmp/cppBison.yxx.c"
    break;

  case 698:
#line 3960 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('*', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9326 "built/tmp/cppBison.yxx.c"
    break;

  case 699:
#line 3964 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('/', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9334 "built/tmp/cppBison.yxx.c"
    break;

  case 700:
#line 3968 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('%', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9342 "built/tmp/cppBison.yxx.c"
    break;

  case 701:
#line 3972 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('+', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9350 "built/tmp/cppBison.yxx.c"
    break;

  case 702:
#line 3976 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('-', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9358 "built/tmp/cppBison.yxx.c"
    break;

  case 703:
#line 3980 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('|', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9366 "built/tmp/cppBison.yxx.c"
    break;

  case 704:
#line 3984 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('^', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9374 "built/tmp/cppBison.yxx.c"
    break;

  case 705:
#line 3988 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('&', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9382 "built/tmp/cppBison.yxx.c"
    break;

  case 706:
#line 3992 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(OROR, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9390 "built/tmp/cppBison.yxx.c"
    break;

  case 707:
#line 3996 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(ANDAND, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9398 "built/tmp/cppBison.yxx.c"
    break;

  case 708:
#line 4000 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(EQCOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9406 "built/tmp/cppBison.yxx.c"
    break;

  case 709:
#line 4004 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(NECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9414 "built/tmp/cppBison.yxx.c"
    break;

  case 710:
#line 4008 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(LECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9422 "built/tmp/cppBison.yxx.c"
    break;

  case 711:
#line 4012 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(GECOMPARE, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9430 "built/tmp/cppBison.yxx.c"
    break;

  case 712:
#line 4016 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('<', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9438 "built/tmp/cppBison.yxx.c"
    break;

  case 713:
#line 4020 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('>', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9446 "built/tmp/cppBison.yxx.c"
    break;

  case 714:
#line 4024 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(LSHIFT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9454 "built/tmp/cppBison.yxx.c"
    break;

  case 715:
#line 4028 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(RSHIFT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9462 "built/tmp/cppBison.yxx.c"
    break;

  case 716:
#line 4032 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('?', (yyvsp[-4].u.expr), (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9470 "built/tmp/cppBison.yxx.c"
    break;

  case 717:
#line 4036 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('[', (yyvsp[-3].u.expr), (yyvsp[-1].u.expr));
}
#line 9478 "built/tmp/cppBison.yxx.c"
    break;

  case 718:
#line 4040 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[-3].u.expr), (yyvsp[-1].u.expr));
}
#line 9486 "built/tmp/cppBison.yxx.c"
    break;

  case 719:
#line 4044 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[-2].u.expr));
}
#line 9494 "built/tmp/cppBison.yxx.c"
    break;

  case 720:
#line 4048 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression('.', (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9502 "built/tmp/cppBison.yxx.c"
    break;

  case 721:
#line 4052 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(POINTSAT, (yyvsp[-2].u.expr), (yyvsp[0].u.expr));
}
#line 9510 "built/tmp/cppBison.yxx.c"
    break;

  case 722:
#line 4056 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[-1].u.expr);
}
#line 9518 "built/tmp/cppBison.yxx.c"
    break;

  case 723:
#line 4063 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].u.integer));
}
#line 9526 "built/tmp/cppBison.yxx.c"
    break;

  case 724:
#line 4067 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(true);
}
#line 9534 "built/tmp/cppBison.yxx.c"
    break;

  case 725:
#line 4071 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(false);
}
#line 9542 "built/tmp/cppBison.yxx.c"
    break;

  case 726:
#line 4075 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].u.integer));
}
#line 9550 "built/tmp/cppBison.yxx.c"
    break;

  case 727:
#line 4079 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].u.real));
}
#line 9558 "built/tmp/cppBison.yxx.c"
    break;

  case 728:
#line 4083 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 9566 "built/tmp/cppBison.yxx.c"
    break;

  case 729:
#line 4087 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 9574 "built/tmp/cppBison.yxx.c"
    break;

  case 730:
#line 4091 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].u.identifier), current_scope, global_scope, current_lexer);
}
#line 9582 "built/tmp/cppBison.yxx.c"
    break;

  case 731:
#line 4095 "dtool/src/cppparser/cppBison.yxx"
{
  // A variable named "final".  C++11 explicitly permits this.
  CPPIdentifier *ident = new CPPIdentifier("final", (yylsp[0]));
  (yyval.u.expr) = new CPPExpression(ident, current_scope, global_scope, current_lexer);
}
#line 9592 "built/tmp/cppBison.yxx.c"
    break;

  case 732:
#line 4101 "dtool/src/cppparser/cppBison.yxx"
{
  // A variable named "override".  C++11 explicitly permits this.
  CPPIdentifier *ident = new CPPIdentifier("override", (yylsp[0]));
  (yyval.u.expr) = new CPPExpression(ident, current_scope, global_scope, current_lexer);
}
#line 9602 "built/tmp/cppBison.yxx.c"
    break;

  case 733:
#line 4107 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_nullptr());
}
#line 9610 "built/tmp/cppBison.yxx.c"
    break;

  case 734:
#line 4115 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.closure_type) = new CPPClosureType();
}
#line 9618 "built/tmp/cppBison.yxx.c"
    break;

  case 735:
#line 4119 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.closure_type) = new CPPClosureType(CPPClosureType::CT_by_value);
}
#line 9626 "built/tmp/cppBison.yxx.c"
    break;

  case 736:
#line 4123 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.closure_type) = new CPPClosureType(CPPClosureType::CT_by_reference);
}
#line 9634 "built/tmp/cppBison.yxx.c"
    break;

  case 737:
#line 4127 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.closure_type) = new CPPClosureType();
  (yyvsp[-1].u.capture)->_initializer = (yyvsp[0].u.expr);
  (yyval.u.closure_type)->_captures.push_back(*(yyvsp[-1].u.capture));
  delete (yyvsp[-1].u.capture);
}
#line 9645 "built/tmp/cppBison.yxx.c"
    break;

  case 738:
#line 4134 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.closure_type) = (yyvsp[-3].u.closure_type);
  (yyvsp[-1].u.capture)->_initializer = (yyvsp[0].u.expr);
  (yyval.u.closure_type)->_captures.push_back(*(yyvsp[-1].u.capture));
  delete (yyvsp[-1].u.capture);
}
#line 9656 "built/tmp/cppBison.yxx.c"
    break;

  case 739:
#line 4144 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.capture) = new CPPClosureType::Capture;
  (yyval.u.capture)->_name = (yyvsp[0].u.identifier)->get_simple_name();
  (yyval.u.capture)->_type = CPPClosureType::CT_by_reference;
}
#line 9666 "built/tmp/cppBison.yxx.c"
    break;

  case 740:
#line 4150 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.capture) = new CPPClosureType::Capture;
  (yyval.u.capture)->_name = (yyvsp[-1].u.identifier)->get_simple_name();
  (yyval.u.capture)->_type = CPPClosureType::CT_by_reference;
}
#line 9676 "built/tmp/cppBison.yxx.c"
    break;

  case 741:
#line 4156 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.capture) = new CPPClosureType::Capture;
  (yyval.u.capture)->_name = (yyvsp[0].u.identifier)->get_simple_name();
  if ((yyval.u.capture)->_name == "this") {
    (yyval.u.capture)->_type = CPPClosureType::CT_by_reference;
  } else {
    (yyval.u.capture)->_type = CPPClosureType::CT_by_value;
  }
}
#line 9690 "built/tmp/cppBison.yxx.c"
    break;

  case 742:
#line 4166 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.capture) = new CPPClosureType::Capture;
  (yyval.u.capture)->_name = (yyvsp[0].u.identifier)->get_simple_name();
  (yyval.u.capture)->_type = CPPClosureType::CT_by_value;
  if ((yyval.u.capture)->_name != "this") {
    yywarning("only capture name 'this' may be preceded by an asterisk", (yylsp[0]));
  }
}
#line 9703 "built/tmp/cppBison.yxx.c"
    break;

  case 743:
#line 4178 "dtool/src/cppparser/cppBison.yxx"
{
  CPPType *type = (yyvsp[0].u.identifier)->find_type(current_scope, global_scope, true);
  if (type == nullptr) {
    type = CPPType::new_type(new CPPTBDType((yyvsp[0].u.identifier)));
  }
  (yyval.u.type) = type;
}
#line 9715 "built/tmp/cppBison.yxx.c"
    break;

  case 744:
#line 4186 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.type) = CPPType::new_type(new CPPTBDType((yyvsp[0].u.identifier)));
}
#line 9723 "built/tmp/cppBison.yxx.c"
    break;

  case 745:
#line 4190 "dtool/src/cppparser/cppBison.yxx"
{
  CPPClassTemplateParameter *ctp = new CPPClassTemplateParameter((yyvsp[-1].u.identifier));
  ctp->_packed = true;
  (yyval.u.type) = CPPType::new_type(ctp);
}
#line 9733 "built/tmp/cppBison.yxx.c"
    break;

  case 746:
#line 4220 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = (yyvsp[0].u.identifier);
}
#line 9741 "built/tmp/cppBison.yxx.c"
    break;

  case 747:
#line 4224 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = (yyvsp[0].u.identifier);
}
#line 9749 "built/tmp/cppBison.yxx.c"
    break;

  case 748:
#line 4228 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = (yyvsp[0].u.identifier);
}
#line 9757 "built/tmp/cppBison.yxx.c"
    break;

  case 749:
#line 4232 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = new CPPIdentifier("final", (yylsp[0]));
}
#line 9765 "built/tmp/cppBison.yxx.c"
    break;

  case 750:
#line 4236 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = new CPPIdentifier("override", (yylsp[0]));
}
#line 9773 "built/tmp/cppBison.yxx.c"
    break;

  case 751:
#line 4240 "dtool/src/cppparser/cppBison.yxx"
{
  // This is not a keyword in Python, so it is useful to be able to use this
  // in MAKE_PROPERTY definitions, etc.
  (yyval.u.identifier) = new CPPIdentifier("signed", (yylsp[0]));
}
#line 9783 "built/tmp/cppBison.yxx.c"
    break;

  case 752:
#line 4246 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = new CPPIdentifier("float", (yylsp[0]));
}
#line 9791 "built/tmp/cppBison.yxx.c"
    break;

  case 753:
#line 4250 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = new CPPIdentifier("public", (yylsp[0]));
}
#line 9799 "built/tmp/cppBison.yxx.c"
    break;

  case 754:
#line 4254 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = new CPPIdentifier("private", (yylsp[0]));
}
#line 9807 "built/tmp/cppBison.yxx.c"
    break;

  case 755:
#line 4258 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = new CPPIdentifier("static", (yylsp[0]));
}
#line 9815 "built/tmp/cppBison.yxx.c"
    break;

  case 756:
#line 4262 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = new CPPIdentifier("default", (yylsp[0]));
}
#line 9823 "built/tmp/cppBison.yxx.c"
    break;

  case 757:
#line 4273 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = (yyvsp[0].u.identifier);
}
#line 9831 "built/tmp/cppBison.yxx.c"
    break;

  case 758:
#line 4277 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = (yyvsp[0].u.identifier);
}
#line 9839 "built/tmp/cppBison.yxx.c"
    break;

  case 759:
#line 4281 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = (yyvsp[0].u.identifier);
}
#line 9847 "built/tmp/cppBison.yxx.c"
    break;

  case 760:
#line 4285 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.identifier) = new CPPIdentifier("override", (yylsp[0]));
}
#line 9855 "built/tmp/cppBison.yxx.c"
    break;

  case 761:
#line 4293 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = new CPPExpression((yyvsp[0].str));
}
#line 9863 "built/tmp/cppBison.yxx.c"
    break;

  case 762:
#line 4297 "dtool/src/cppparser/cppBison.yxx"
{
  (yyval.u.expr) = (yyvsp[0].u.expr);
}
#line 9871 "built/tmp/cppBison.yxx.c"
    break;

  case 763:
#line 4301 "dtool/src/cppparser/cppBison.yxx"
{
  // The right string takes on the literal type of the left.
  (yyval.u.expr) = (yyvsp[-1].u.expr);
  (yyval.u.expr)->_str += (yyvsp[0].str);
}
#line 9881 "built/tmp/cppBison.yxx.c"
    break;

  case 764:
#line 4307 "dtool/src/cppparser/cppBison.yxx"
{
  // We have to check that the two literal types match up.
  (yyval.u.expr) = (yyvsp[-1].u.expr);
  if ((yyvsp[0].u.expr)->_type != CPPExpression::T_string && (yyvsp[0].u.expr)->_type != (yyvsp[-1].u.expr)->_type) {
    yywarning("cannot concatenate two string literals of different types", (yyloc));
  }
  (yyval.u.expr)->_str += (yyvsp[0].u.expr)->_str;
}
#line 9894 "built/tmp/cppBison.yxx.c"
    break;


#line 9898 "built/tmp/cppBison.yxx.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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