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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         eggyyparse
#define yylex           eggyylex
#define yyerror         eggyyerror
#define yydebug         eggyydebug
#define yynerrs         eggyynerrs
#define yylval          eggyylval
#define yychar          eggyychar

/* First part of user prologue.  */
#line 7 "panda/src/egg/parser.yxx"


#include "pandabase.h"
#include "config_egg.h"
#include "parserDefs.h"
#include "lexerDefs.h"
#include "eggObject.h"
#include "eggGroup.h"
#include "eggVertex.h"
#include "eggVertexPool.h"
#include "eggVertexUV.h"
#include "eggVertexAux.h"
#include "eggPolygon.h"
#include "eggCompositePrimitive.h"
#include "eggTriangleFan.h"
#include "eggTriangleStrip.h"
#include "eggPatch.h"
#include "eggPoint.h"
#include "eggLine.h"
#include "eggNurbsSurface.h"
#include "eggNurbsCurve.h"
#include "eggTable.h"
#include "eggSAnimData.h"
#include "eggXfmSAnim.h"
#include "eggXfmAnimData.h"
#include "eggTexture.h"
#include "eggMaterial.h"
#include "eggComment.h"
#include "eggCoordinateSystem.h"
#include "eggExternalReference.h"
#include "eggData.h"
#include "eggAnimPreload.h"
#include "eggTransform.h"
#include "pt_EggTexture.h"
#include "pt_EggMaterial.h"

#include "string_utils.h"
#include "filename.h"
#include "luse.h"
#include "lmatrix.h"
#include "coordinateSystem.h"
#include "pvector.h"
#include "dcast.h"
#include "thread.h"

// Because our token type contains objects of type string, which
// require correct copy construction (and not simply memcpying), we
// cannot use bison's built-in auto-stack-grow feature.  As an easy
// solution, we ensure here that we have enough yacc stack to start
// with, and that it doesn't ever try to grow.
#define YYINITDEPTH 1000
#define YYMAXDEPTH 1000

using std::istream;
using std::ostringstream;
using std::string;

// We need a stack of EggObject pointers.  Each time we encounter a
// nested EggObject of some kind, we'll allocate a new one of these
// and push it onto the stack.  At any given time, the top of the
// stack is the EggObject we are currently scanning.

typedef pvector< PT(EggObject) > EggStack;
static EggStack egg_stack;

// This is used just when parsing a <Transform> or <DefaultPose> entry.
static EggTransform *egg_top_transform;

// There's one "top-level" egg node, which is where we should parent
// things (e.g. implicit textures) encountered in the egg file that
// don't have an explicit place in the tree.  If this is NULL, such
// things won't be parented anywhere.
static EggGroupNode *egg_top_node;

// We need a table mapping vertex pool names to vertex pools.
typedef pmap<string,  PT(EggVertexPool) > VertexPools;
static VertexPools vertex_pools;

// And another one mapping texture names to textures.
typedef pmap<string,  PT_EggTexture > Textures;
static Textures textures;

// And again for material names to materials.
typedef pmap<string,  PT_EggMaterial > Materials;
static Materials materials;

// Group names to groups.
typedef pmap<string,  PT(EggGroup) > Groups;
static Groups groups;

// We need to be able to save the index number requested for a vertex
// temporarily.
static int vertex_index;


////////////////////////////////////////////////////////////////////
// Defining the interface to the parser.
////////////////////////////////////////////////////////////////////

void
egg_init_parser(istream &in, const string &filename,
                EggObject *tos, EggGroupNode *top_node) {
  egg_init_lexer(in, filename);

  egg_stack.clear();
  vertex_pools.clear();
  textures.clear();
  materials.clear();
  groups.clear();

  egg_stack.push_back(tos);
  egg_top_node = top_node;
}

void
egg_cleanup_parser() {
  // Check for undefined vertex pools.
  VertexPools::const_iterator vpi;
  for (vpi = vertex_pools.begin(); vpi != vertex_pools.end(); ++vpi) {
    EggVertexPool *pool = (*vpi).second;
    if (pool->has_forward_vertices()) {
      if (!pool->has_defined_vertices()) {
        eggyyerror("Undefined vertex pool " + pool->get_name());
      } else {
        eggyyerror("Undefined vertices in pool " + pool->get_name());

        egg_cat.error(false)
          << "Undefined vertex index numbers:";
        EggVertexPool::const_iterator vi;
        for (vi = pool->begin(); vi != pool->end(); ++vi) {
          EggVertex *vertex = (*vi);
          if (vertex->is_forward_reference()) {
            egg_cat.error(false)
              << " " << vertex->get_index();
          }
        }
        egg_cat.error(false)
          << "\n";
      }
    }
  }

  // Clean these out after we're done, so we don't keep big memory
  // structures around needlessly.
  egg_stack.clear();
  vertex_pools.clear();
  textures.clear();
  materials.clear();
  groups.clear();
}


#line 230 "built/tmp/parser.yxx.c"

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
#ifndef YY_EGGYY_BUILT_TMP_PARSER_YXX_H_INCLUDED
# define YY_EGGYY_BUILT_TMP_PARSER_YXX_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int eggyydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EGG_NUMBER = 258,
    EGG_ULONG = 259,
    EGG_STRING = 260,
    ANIMPRELOAD = 261,
    BEZIERCURVE = 262,
    BFACE = 263,
    BILLBOARD = 264,
    BILLBOARDCENTER = 265,
    BINORMAL = 266,
    BUNDLE = 267,
    CLOSED = 268,
    COLLIDE = 269,
    COMMENT = 270,
    COMPONENT = 271,
    COORDSYSTEM = 272,
    CV = 273,
    DART = 274,
    DNORMAL = 275,
    DRGBA = 276,
    DUV = 277,
    DXYZ = 278,
    DCS = 279,
    DISTANCE = 280,
    DTREF = 281,
    DYNAMICVERTEXPOOL = 282,
    EXTERNAL_FILE = 283,
    GROUP = 284,
    DEFAULTPOSE = 285,
    JOINT = 286,
    KNOTS = 287,
    INCLUDE = 288,
    INSTANCE = 289,
    LINE = 290,
    LOOP = 291,
    MATERIAL = 292,
    MATRIX3 = 293,
    MATRIX4 = 294,
    MODEL = 295,
    MREF = 296,
    NORMAL = 297,
    NURBSCURVE = 298,
    NURBSSURFACE = 299,
    OBJECTTYPE = 300,
    ORDER = 301,
    OUTTANGENT = 302,
    PATCH = 303,
    POINTLIGHT = 304,
    POLYGON = 305,
    REF = 306,
    RGBA = 307,
    ROTATE = 308,
    ROTX = 309,
    ROTY = 310,
    ROTZ = 311,
    SANIM = 312,
    SCALAR = 313,
    SCALE = 314,
    SEQUENCE = 315,
    SHADING = 316,
    SWITCH = 317,
    SWITCHCONDITION = 318,
    TABLE = 319,
    TABLE_V = 320,
    TAG = 321,
    TANGENT = 322,
    TEXLIST = 323,
    TEXTURE = 324,
    TLENGTHS = 325,
    TRANSFORM = 326,
    TRANSLATE = 327,
    TREF = 328,
    TRIANGLEFAN = 329,
    TRIANGLESTRIP = 330,
    TRIM = 331,
    TXT = 332,
    UKNOTS = 333,
    UV = 334,
    AUX = 335,
    VKNOTS = 336,
    VERTEX = 337,
    VERTEXANIM = 338,
    VERTEXPOOL = 339,
    VERTEXREF = 340,
    XFMANIM = 341,
    XFMSANIM = 342,
    START_EGG = 343,
    START_GROUP_BODY = 344,
    START_TEXTURE_BODY = 345,
    START_PRIMITIVE_BODY = 346
  };
#endif
/* Tokens.  */
#define EGG_NUMBER 258
#define EGG_ULONG 259
#define EGG_STRING 260
#define ANIMPRELOAD 261
#define BEZIERCURVE 262
#define BFACE 263
#define BILLBOARD 264
#define BILLBOARDCENTER 265
#define BINORMAL 266
#define BUNDLE 267
#define CLOSED 268
#define COLLIDE 269
#define COMMENT 270
#define COMPONENT 271
#define COORDSYSTEM 272
#define CV 273
#define DART 274
#define DNORMAL 275
#define DRGBA 276
#define DUV 277
#define DXYZ 278
#define DCS 279
#define DISTANCE 280
#define DTREF 281
#define DYNAMICVERTEXPOOL 282
#define EXTERNAL_FILE 283
#define GROUP 284
#define DEFAULTPOSE 285
#define JOINT 286
#define KNOTS 287
#define INCLUDE 288
#define INSTANCE 289
#define LINE 290
#define LOOP 291
#define MATERIAL 292
#define MATRIX3 293
#define MATRIX4 294
#define MODEL 295
#define MREF 296
#define NORMAL 297
#define NURBSCURVE 298
#define NURBSSURFACE 299
#define OBJECTTYPE 300
#define ORDER 301
#define OUTTANGENT 302
#define PATCH 303
#define POINTLIGHT 304
#define POLYGON 305
#define REF 306
#define RGBA 307
#define ROTATE 308
#define ROTX 309
#define ROTY 310
#define ROTZ 311
#define SANIM 312
#define SCALAR 313
#define SCALE 314
#define SEQUENCE 315
#define SHADING 316
#define SWITCH 317
#define SWITCHCONDITION 318
#define TABLE 319
#define TABLE_V 320
#define TAG 321
#define TANGENT 322
#define TEXLIST 323
#define TEXTURE 324
#define TLENGTHS 325
#define TRANSFORM 326
#define TRANSLATE 327
#define TREF 328
#define TRIANGLEFAN 329
#define TRIANGLESTRIP 330
#define TRIM 331
#define TXT 332
#define UKNOTS 333
#define UV 334
#define AUX 335
#define VKNOTS 336
#define VERTEX 337
#define VERTEXANIM 338
#define VERTEXPOOL 339
#define VERTEXREF 340
#define XFMANIM 341
#define XFMSANIM 342
#define START_EGG 343
#define START_GROUP_BODY 344
#define START_TEXTURE_BODY 345
#define START_PRIMITIVE_BODY 346

/* Value type.  */


extern YYSTYPE eggyylval;

int eggyyparse (void);

#endif /* !YY_EGGYY_BUILT_TMP_PARSER_YXX_H_INCLUDED  */



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
#define YYLAST   1388

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  127
/* YYNRULES -- Number of rules.  */
#define YYNRULES  278
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  765

#define YYUNDEFTOK  2
#define YYMAXUTOK   346


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,    93,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   235,   235,   236,   237,   238,   249,   250,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   295,   318,   333,
     332,   360,   361,   716,   728,   727,   754,   755,   876,   883,
     904,   903,   943,   944,   956,   955,   967,   966,  1012,  1016,
    1020,  1024,  1029,  1028,  1044,  1043,  1058,  1059,  1060,  1068,
    1087,  1091,  1095,  1103,  1111,  1119,  1127,  1135,  1143,  1160,
    1161,  1175,  1179,  1187,  1205,  1209,  1217,  1236,  1235,  1261,
    1260,  1282,  1281,  1306,  1307,  1455,  1467,  1472,  1479,  1485,
    1498,  1505,  1518,  1524,  1530,  1536,  1541,  1547,  1548,  1549,
    1550,  1551,  1560,  1574,  1604,  1605,  1628,  1627,  1644,  1643,
    1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,
    1674,  1675,  1676,  1680,  1687,  1694,  1701,  1708,  1715,  1722,
    1729,  1736,  1743,  1750,  1754,  1755,  1767,  1771,  1772,  1794,
    1827,  1831,  1856,  1868,  1873,  1891,  1890,  1910,  1909,  1929,
    1928,  1948,  1947,  1967,  1966,  1986,  1985,  2005,  2004,  2024,
    2023,  2043,  2044,  2045,  2056,  2058,  2057,  2078,  2079,  2080,
    2081,  2082,  2083,  2084,  2085,  2160,  2161,  2162,  2163,  2164,
    2165,  2166,  2167,  2168,  2169,  2170,  2171,  2177,  2178,  2244,
    2245,  2246,  2247,  2248,  2249,  2250,  2251,  2252,  2253,  2254,
    2325,  2342,  2382,  2399,  2403,  2411,  2429,  2433,  2441,  2459,
    2475,  2506,  2524,  2544,  2564,  2569,  2580,  2586,  2605,  2621,
    2643,  2642,  2666,  2665,  2686,  2687,  2691,  2695,  2699,  2703,
    2719,  2718,  2739,  2740,  2752,  2767,  2766,  2787,  2788,  2805,
    2820,  2819,  2840,  2841,  2856,  2872,  2871,  2892,  2893,  2917,
    2921,  2935,  2939,  2953,  2974,  2995,  3020,  3041,  3046,  3058,
    3070,  3075,  3086,  3090,  3104,  3108,  3112,  3125,  3129,  3145,
    3149,  3163,  3164,  3179,  3185,  3191,  3208,  3216,  3222
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EGG_NUMBER", "EGG_ULONG", "EGG_STRING",
  "ANIMPRELOAD", "BEZIERCURVE", "BFACE", "BILLBOARD", "BILLBOARDCENTER",
  "BINORMAL", "BUNDLE", "CLOSED", "COLLIDE", "COMMENT", "COMPONENT",
  "COORDSYSTEM", "CV", "DART", "DNORMAL", "DRGBA", "DUV", "DXYZ", "DCS",
  "DISTANCE", "DTREF", "DYNAMICVERTEXPOOL", "EXTERNAL_FILE", "GROUP",
  "DEFAULTPOSE", "JOINT", "KNOTS", "INCLUDE", "INSTANCE", "LINE", "LOOP",
  "MATERIAL", "MATRIX3", "MATRIX4", "MODEL", "MREF", "NORMAL",
  "NURBSCURVE", "NURBSSURFACE", "OBJECTTYPE", "ORDER", "OUTTANGENT",
  "PATCH", "POINTLIGHT", "POLYGON", "REF", "RGBA", "ROTATE", "ROTX",
  "ROTY", "ROTZ", "SANIM", "SCALAR", "SCALE", "SEQUENCE", "SHADING",
  "SWITCH", "SWITCHCONDITION", "TABLE", "TABLE_V", "TAG", "TANGENT",
  "TEXLIST", "TEXTURE", "TLENGTHS", "TRANSFORM", "TRANSLATE", "TREF",
  "TRIANGLEFAN", "TRIANGLESTRIP", "TRIM", "TXT", "UKNOTS", "UV", "AUX",
  "VKNOTS", "VERTEX", "VERTEXANIM", "VERTEXPOOL", "VERTEXREF", "XFMANIM",
  "XFMSANIM", "START_EGG", "START_GROUP_BODY", "START_TEXTURE_BODY",
  "START_PRIMITIVE_BODY", "'{'", "'}'", "$accept", "grammar", "egg",
  "node", "coordsystem", "comment", "texture", "$@1", "texture_body",
  "material", "$@2", "material_body", "external_reference", "vertex_pool",
  "$@3", "vertex_pool_body", "vertex", "$@4", "$@5", "vertex_body", "$@6",
  "$@7", "vertex_uv_body", "vertex_aux_body", "vertex_normal_body",
  "vertex_color_body", "group", "$@8", "joint", "$@9", "instance", "$@10",
  "group_body", "cs_type", "collide_flags", "transform", "$@11",
  "default_pose", "$@12", "transform_body", "translate2d", "translate3d",
  "rotate2d", "rotx", "roty", "rotz", "rotate3d", "scale2d", "scale3d",
  "uniform_scale", "matrix3", "matrix3_body", "matrix4", "matrix4_body",
  "group_vertex_ref", "group_vertex_membership", "switchcondition",
  "switchcondition_body", "polygon", "$@13", "trianglefan", "$@14",
  "trianglestrip", "$@15", "patch", "$@16", "point_light", "$@17", "line",
  "$@18", "nurbs_surface", "$@19", "nurbs_curve", "$@20",
  "primitive_component_body", "primitive_body", "$@21",
  "nurbs_surface_body", "nurbs_curve_body", "primitive_tref_body",
  "primitive_texture_body", "primitive_material_body",
  "primitive_normal_body", "primitive_color_body", "primitive_bface_body",
  "primitive_vertex_ref", "nurbs_surface_order_body",
  "nurbs_surface_uknots_body", "nurbs_surface_vknots_body",
  "nurbs_surface_trim_body", "nurbs_surface_trim_loop_body",
  "nurbs_curve_order_body", "nurbs_curve_knots_body", "table", "$@22",
  "bundle", "$@23", "table_body", "sanim", "$@24", "sanim_body", "xfmanim",
  "$@25", "xfmanim_body", "xfm_s_anim", "$@26", "xfm_s_anim_body",
  "anim_preload", "$@27", "anim_preload_body", "integer_list", "real_list",
  "texture_name", "material_name", "vertex_pool_name", "group_name",
  "required_name", "optional_name", "required_string", "optional_string",
  "string", "repeated_string", "repeated_string_body", "real",
  "real_or_string", "integer", "empty", YY_NULLPTR
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
     345,   346,   123,   125
};
# endif

#define YYPACT_NINF (-430)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     211,  -430,  -430,  -430,  -430,    14,  1060,  -430,  1206,  -430,
     141,  -430,   495,  -430,  -430,  -430,  -430,  -430,   329,   329,
     -55,   329,   329,   329,   329,   329,   329,   329,   329,   329,
     329,   329,   329,   329,   329,   329,   329,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,    70,    10,    22,
     329,    68,   114,  -430,   119,   125,   134,   329,   150,   152,
     329,   164,  -430,   169,  -430,  -430,  -430,  -430,  -430,   329,
    -430,   172,   185,   174,   175,   180,   329,   182,   191,   192,
    -430,  -430,  -430,  -430,  -430,   203,   329,   215,  -430,  -430,
    -430,  -430,   220,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,   226,  -430,  -430,  -430,   329,   329,   255,   228,   347,
     374,   230,   185,   329,   329,   235,   185,    99,   236,   185,
     243,  -430,   244,   185,  -430,  -430,   247,   329,   255,   255,
     249,   329,   329,  -430,   253,   329,    57,  -430,  -430,   329,
     261,   273,   274,   279,  -430,   283,   290,   300,   303,   313,
     323,   329,   326,   331,   333,   334,   184,  -430,  -430,   255,
     329,   188,   210,   251,   254,  -430,   262,   287,   328,  -430,
     385,   335,   337,   338,   329,   345,  -430,   185,  -430,   385,
     346,  -430,  -430,   348,  -430,  -430,    29,   255,    23,   255,
     385,   349,  -430,   352,  -430,  -430,   131,  -430,  -430,   353,
     329,  -430,  -430,   356,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,   329,
    -430,   255,  -430,  -430,  -430,  -430,  -430,  -430,   381,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,   361,  -430,   255,  -430,
     362,  -430,   441,   170,  -430,  -430,   365,  -430,  -430,  -430,
      69,  -430,   255,    73,  -430,   255,   366,  -430,  -430,   369,
      74,  -430,  -430,  -430,  -430,   789,   983,  1133,   221,   140,
    -430,   145,  -430,   167,  -430,   288,   375,   435,   189,  -430,
    -430,   827,   864,    75,  -430,   376,   378,     4,  -430,   380,
     383,   386,   389,   391,   393,   396,   397,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,   255,  -430,  -430,   398,   329,  -430,    59,  -430,   329,
     399,  -430,   329,   400,   255,  -430,   329,   329,  -430,  -430,
    -430,  -430,  -430,   329,  -430,   406,   407,   409,   414,   418,
     420,   329,   425,   426,  -430,  -430,   427,   429,   434,   437,
     438,   329,   439,   440,   443,   446,   447,  -430,  -430,  -430,
    -430,  -430,  -430,   329,   329,   329,   329,  -430,  -430,  -430,
    -430,  -430,  -430,   123,  -430,  -430,   185,  -430,  -430,  -430,
    -430,  -430,  -430,   255,   255,   255,   255,   255,   255,   255,
     255,    76,   329,   448,   449,   450,  -430,   255,   255,   255,
     255,  -430,   451,  -430,   453,   454,   185,  -430,   329,   255,
     185,   255,   456,   329,   329,   185,   329,   255,   185,   255,
     457,   329,   329,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,   458,  -430,   459,   255,  -430,   461,   255,  -430,     7,
     462,   463,   469,    44,   255,   471,    80,   472,   385,   255,
     255,   255,   255,   255,   255,   476,   385,   385,   477,   478,
     255,  -430,   479,    32,   480,  -430,    86,   385,   483,   485,
     488,   490,    43,   491,   185,    92,   385,   492,   493,    53,
    -430,   494,   255,   497,   255,   499,   500,   501,   506,   255,
     508,  -430,   255,  -430,   255,  -430,   255,  -430,  -430,  -430,
    -430,    47,    52,   255,   512,   513,   514,    55,    97,   255,
     255,   255,   255,  -430,   515,   516,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,   518,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,   519,  -430,  -430,   522,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,   263,   255,   255,   255,   255,   255,  -430,
     523,  -430,   524,   255,   255,  -430,  -430,  -430,  -430,   525,
     526,   255,   255,  -430,  -430,  -430,  -430,  -430,   223,   157,
    -430,   162,  -430,   138,  -430,    79,   528,   531,   329,   329,
    -430,   255,   269,   255,   255,   533,  -430,  -430,   255,   255,
    -430,  -430,   536,   537,    61,  -430,  -430,   329,   532,  -430,
     329,   540,  -430,   329,  -430,  -430,   329,   541,   255,   255,
     542,   543,   255,  -430,   255,   255,  -430,   544,   255,  -430,
    -430,  -430,  -430,   546,  -430,   547,  -430,   548,   255,   255,
      83,   255,   100,   255,  -430,  -430,  -430,   255,   255,   550,
     552,   385,    54,   385,    56,   385,   255,   255,    82,  -430,
     255,    88,  -430,   255,   255,   255,   255,   255,  -430,   554,
     555,  -430,   556,  -430,   560,   255,   255,   329,   564,  -430,
     329,   565,   255,    77,   255,   568,   255,   255,   255,  -430,
    -430,  -430,  -430,   569,   571,   255,   255,   255,   255,  -430,
     566,    91,   573,  -430,   255,  -430,   255,  -430,   255,  -430,
    -430,   255,   255,   255,   255,   255,   329,   580,   255,  -430,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
    -430,   255,   584,   587,   255,   255,   255,   255,   255,   255,
     255,  -430,  -430,   588,   589,   593,    58,    63,    66,   255,
    -430,  -430,  -430,  -430,   595,  -430,   599,  -430,   600,   255,
    -430,  -430,  -430,   255,  -430
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   278,   278,   278,   278,     0,     2,     6,     3,    83,
       4,    31,     5,   164,     1,   264,   265,   266,   278,   278,
       0,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
     278,     0,     0,   108,     0,     0,     0,   278,     0,     0,
     278,     0,   106,     0,   102,    97,    98,    99,   100,   278,
      33,     0,     0,     0,     0,     0,   278,     0,     0,     0,
     170,   245,   259,   263,   262,     0,   278,     0,    77,    79,
      81,   155,     0,   258,   257,   159,   157,   151,   153,   145,
     220,     0,   147,   149,    40,   278,     0,     0,     0,     0,
       0,     0,     0,   278,   278,     0,     0,     0,     0,     0,
       0,   278,     0,     0,   276,   277,     0,   278,     0,     0,
       0,   278,   278,   278,     0,   278,     0,   261,   260,   278,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,   278,     0,     0,     0,     0,     0,   271,   272,     0,
       0,     0,     0,     0,     0,   278,     0,     0,     0,   256,
       0,     0,     0,     0,   278,     0,   278,   278,   249,     0,
       0,   209,   165,     0,   202,   254,     0,     0,     0,     0,
       0,     0,   201,     0,   200,   253,     0,   278,   269,     0,
     268,   267,    27,     0,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,    29,   278,   278,   278,   278,
      85,     0,   278,   103,    91,    90,    89,    88,     0,   110,
      94,    93,   101,   273,   274,   275,     0,    92,     0,   142,
       0,    96,     0,     0,   250,   140,     0,   173,   278,   169,
       0,   171,     0,     0,   172,     0,     0,   168,   167,     0,
       0,   247,    28,   270,    38,     0,     0,     0,     0,     0,
      36,     0,   189,     0,   175,     0,     0,     0,     0,   224,
     278,     0,     0,     0,    42,     0,     0,     0,   104,     0,
       0,     0,     0,     0,     0,     0,     0,   109,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      84,     0,    95,   107,     0,   278,    32,     0,   161,     0,
       0,   203,     0,     0,     0,   174,   278,   278,   246,    78,
      80,    82,   156,   278,    35,     0,     0,     0,     0,     0,
       0,   278,     0,     0,   160,   193,     0,     0,     0,     0,
       0,   278,     0,     0,     0,     0,     0,   158,   186,   179,
     152,   154,   146,   278,   278,   278,   278,   221,   225,   226,
     227,   228,   229,     0,   148,   150,    44,    41,    43,    39,
      86,    87,   105,   278,   278,     0,     0,     0,     0,     0,
       0,     0,   278,     0,     0,     0,   166,     0,     0,     0,
       0,   206,     0,   255,     0,     0,     0,   278,   278,     0,
       0,     0,     0,   278,   278,     0,   278,     0,     0,     0,
       0,   278,   278,   278,   278,   278,   222,   230,   235,   240,
      30,     0,    46,     0,     0,   134,     0,     0,   137,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     219,   251,     0,     0,     0,   218,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     214,     0,   212,     0,   213,     0,     0,     0,     0,     0,
       0,   133,     0,   136,     0,   125,     0,   126,   127,   128,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   210,     0,     0,   196,   198,   252,   192,
     194,   197,   195,     0,   191,   190,   182,   178,   180,   183,
     211,   181,     0,   177,   176,     0,   187,   184,   185,   278,
     278,   278,   278,     0,    48,     0,     0,     0,     0,   130,
       0,   123,     0,     0,     0,   139,   141,   162,   163,     0,
       0,     0,     0,   248,    37,   199,   188,   278,     0,     0,
     232,     0,   237,     0,   242,     0,     0,     0,   278,   278,
      45,    49,     0,     0,     0,     0,   131,   124,     0,     0,
     205,   204,     0,     0,     0,   216,   223,   278,     0,   231,
     278,     0,   236,   278,   241,   244,     0,     0,     0,     0,
       0,     0,    50,    47,     0,     0,   129,     0,     0,   208,
     207,   215,   217,     0,   278,     0,   278,     0,     0,     0,
       0,     0,     0,     0,    52,    54,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    56,
       0,     0,    57,     0,     0,    69,     0,     0,   143,     0,
       0,   234,     0,   239,     0,     0,     0,     0,     0,    71,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
     233,   238,   243,     0,     0,     0,     0,     0,     0,    74,
       0,     0,     0,    53,    60,    55,     0,   135,     0,    59,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    72,     0,     0,     0,     0,     0,     0,     0,
      76,    75,    64,    67,     0,    65,     0,    62,     0,     0,
      68,    66,    63,     0,   138
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -430,  -430,  -430,   160,  -430,  -430,  -430,  -430,  -106,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -242,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,   193,  -430,  -430,    -9,  -430,  -430,  -430,   341,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -279,  -430,  -430,   137,  -430,  -430,  -430,  -200,
    -184,  -177,  -296,  -291,  -297,  -154,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -285,  -430,  -430,  -430,   -76,   -50,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
     408,  -429,  -430,  -430,   213,  -430,   252,    11,   -96,  -430,
      -6,   359,  -430,     3,  -169,   -14,   752
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,    74,    38,    39,    40,   290,    10,    41,
     218,   279,    42,    43,   164,   293,   388,   441,   500,   553,
     664,   665,   683,   685,   640,   642,    44,   150,    45,   151,
      46,   152,     8,   232,   297,    75,   130,    76,   121,   238,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   443,   319,   446,    77,   253,    78,   183,    47,   159,
      48,   162,    49,   163,    50,   157,    51,   158,    52,   153,
      53,   156,    54,   155,   327,    12,   258,   283,   281,   203,
     201,   193,   196,   198,   190,    90,   483,   491,   493,   489,
     604,   474,   469,    55,   160,   379,   495,   288,   380,   496,
     579,   381,   497,   581,   382,   498,   583,    56,   144,   270,
     187,   470,   204,   194,   412,   178,   195,    91,   146,    92,
     103,   209,   210,   528,   246,   191,   104
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    80,    57,   378,   368,   492,   494,    15,    16,    17,
     167,   168,    93,    93,    14,    93,    93,    93,    93,    93,
     256,    93,    93,    93,    93,    93,    93,   177,    93,    93,
      95,   266,    97,    98,    99,   100,   101,    96,   105,   106,
     107,   108,   109,   110,   263,   112,   113,   167,   168,   260,
     167,   168,   260,   213,    93,   167,   168,   167,   168,   167,
     168,   167,   168,   260,    93,   225,   167,   168,   136,   167,
     168,   118,    15,    16,    17,   260,    15,    16,    17,   167,
     168,   128,    15,    16,    17,    15,    16,    17,   700,   545,
     147,    15,    16,    17,    15,    16,    17,   391,   115,   701,
     505,   404,   116,   658,    27,   172,   174,   263,   176,    93,
     166,   405,   181,   263,   117,   185,   264,   147,   263,   468,
     169,   661,   261,   473,   182,   530,   165,   355,   480,   369,
     476,   482,   337,   295,   134,   135,   538,   510,   485,   208,
     559,   197,   199,   147,   702,   561,   546,   671,   567,   673,
     212,   753,   406,   345,   631,   147,   755,   386,   455,   757,
     119,   329,   514,   517,   233,   332,    37,   338,   387,   518,
     703,   616,   231,   254,   677,   356,   659,   346,   208,   532,
     680,    79,   269,   716,   383,   541,   347,   348,   134,   135,
     568,   349,   254,   662,    72,   374,   613,   350,   343,    79,
     262,   373,   265,   351,   273,   652,   120,   654,   357,   358,
      27,   122,    72,   359,   352,   607,   440,   123,   353,   360,
     610,   324,   608,   147,   479,   361,   124,   611,   325,    81,
      89,   614,   488,   344,   296,   373,   362,    82,   354,   478,
     363,   472,   126,   364,   127,   365,   374,   487,   366,   481,
     609,   321,    89,    32,   330,   612,   129,   333,   167,   168,
     367,   131,    83,    84,   133,   331,   137,   138,   334,    57,
      57,    57,   139,    85,   141,   375,   376,   230,   102,    86,
     374,   234,   377,   142,   143,   111,   585,    32,   114,   516,
      87,   392,   585,   378,    88,   145,    81,   524,   525,     1,
       2,     3,     4,   235,    82,   586,    89,   149,   533,   375,
     376,   586,   154,   592,   342,   587,   606,   542,   161,   125,
     170,   587,   175,   407,   401,   632,   409,   180,   184,    83,
      84,   132,    15,    16,    17,   186,   189,   411,   140,   192,
      85,   200,   588,   589,   236,   207,    86,   237,   588,   589,
     134,   135,   171,   214,   278,   240,   590,    87,   285,   286,
     287,    88,   623,   291,   292,   215,   216,    93,    93,    93,
      93,   217,   442,    89,    80,   219,   179,   134,   135,   173,
     241,   370,   220,    81,   436,   437,   438,   439,   243,   244,
     245,    82,   221,   202,   205,   222,   444,   447,   449,   450,
     451,   452,   453,   454,   456,   223,   475,   275,   276,   277,
     461,   462,   463,   464,   484,   224,    83,    84,   226,   299,
     300,   242,   197,   227,   199,   228,   229,    85,   247,   248,
     197,   249,   199,    86,   301,   302,   303,   304,   251,   257,
     305,   259,   267,    81,    87,   268,   272,   502,    88,   274,
     504,    82,   506,   306,   320,   322,   511,   512,   326,   335,
      89,   336,   197,   199,   519,   520,   521,   522,   371,   389,
     540,   390,   393,   578,   307,   394,    83,    84,   395,   299,
     300,   396,   670,   397,   672,   398,   674,    85,   399,   400,
     402,   408,   410,    86,   301,   302,   303,   304,   416,   417,
     305,   418,   554,    81,    87,   556,   419,   557,    88,   558,
     420,    82,   421,   306,   560,   562,   563,   423,   424,   425,
      89,   426,   569,   570,   571,   572,   427,   252,   372,   428,
     429,   431,   432,   615,   323,   433,    83,    84,   434,   435,
     458,   459,   460,   250,   465,   466,   467,    85,   477,   486,
     499,   206,   501,    86,   503,   507,   508,   591,   554,   593,
     594,   595,   509,   513,    87,   515,   598,   599,    88,   523,
     526,   527,   529,   531,   602,   603,   534,   403,   535,   617,
      89,   536,    93,   537,   539,   543,   544,   547,   413,   414,
     548,   549,   550,   551,   622,   415,   624,   625,   552,   620,
     555,   627,   628,   422,   564,     0,   565,   566,   573,   574,
     638,   575,   576,   430,   577,   457,   596,   597,   600,   601,
     618,   641,   643,   619,   634,   646,   626,   647,   648,   629,
     630,   650,   636,   639,   644,   645,     0,   649,   651,   653,
     655,   656,   657,   668,   660,   669,   663,   689,   690,   691,
     666,   667,   678,   692,   413,   681,   696,   698,   715,   675,
     676,   705,   709,   679,   710,   718,   682,   684,   686,   687,
     688,   695,   728,     0,   697,   202,   205,   741,   693,   694,
     742,   750,   751,   202,   205,   699,   752,   704,   760,   706,
     707,   708,   761,   762,     0,   717,     0,     0,   711,   712,
     713,   714,     0,     0,     0,     0,     0,   719,     0,   720,
     727,   721,     0,     0,   722,   723,   724,   725,   726,     0,
       0,   729,     0,   730,   731,   732,   733,   734,   735,   736,
     737,   738,   739,     0,   740,     0,     0,   743,   744,   745,
     746,   747,   748,   749,     0,     0,     0,     0,     0,   754,
     756,   758,   759,     7,     9,    11,    13,     0,     0,     0,
       0,     0,   763,     0,     0,     0,   764,     0,     0,     0,
      94,    94,     0,    94,    94,    94,    94,    94,     0,    94,
      94,    94,    94,    94,    94,     0,    94,    94,     0,     0,
       0,     0,    15,    16,    17,    18,     0,     0,    58,    59,
       0,     0,     0,    60,    19,     0,    20,     0,    61,     0,
       0,     0,    94,    62,     0,     0,     0,    21,    22,    63,
      23,     0,    94,    24,    25,     0,    26,     0,     0,    64,
       0,     0,    27,    28,    65,    81,     0,    29,    30,    31,
      66,   621,     0,    82,     0,     0,     0,    67,   148,     0,
       0,    68,    69,    32,     0,    70,     0,    71,    33,   633,
      72,     0,   635,    34,    35,   637,     0,    94,    83,    84,
       0,     0,    81,    36,    73,   148,     0,     0,     0,    85,
      82,     0,   339,   188,     0,    86,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   188,    87,   211,     0,     0,
      88,   148,     0,     0,     0,    83,    84,     0,     0,     0,
       0,     0,    89,   148,     0,     0,    85,     0,     0,     0,
     384,     0,    86,     0,     0,     0,     0,   239,     0,     0,
       0,     0,     0,    87,     0,     0,   211,    88,   239,   255,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
       0,     0,     0,     0,     0,     0,     0,   385,     0,   271,
       0,     0,     0,     0,     0,     0,     9,     9,     9,    13,
     280,   282,   284,    13,    13,    13,   289,     0,    13,    13,
     294,   148,     0,     0,   298,     0,    15,    16,    17,    18,
       0,     0,    58,    59,     0,     0,     0,    60,    19,     0,
      20,     0,    61,     0,     0,     0,     0,    62,     0,     0,
     328,    21,    22,    63,    23,     0,     0,    24,    25,     0,
      26,     0,     0,    64,     0,     0,    27,    28,    65,     0,
       0,    29,    30,    31,    66,     0,     0,     0,     0,     0,
       0,    67,    11,     0,     0,    68,    69,    32,     0,    70,
       0,    71,    33,     0,    72,     0,     0,    34,    35,     0,
       0,     0,     0,    15,    16,    17,    18,    36,    73,     0,
       0,     0,     0,     0,     0,    19,   340,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
       0,    23,     0,     0,    24,    25,     0,    26,     0,     0,
       0,     0,     0,    27,    28,     0,     0,     0,    29,    30,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,    94,    94,    94,    94,    33,
       0,     0,     0,     0,    34,    35,    15,    16,    17,    18,
       0,     0,    58,    59,    36,   445,   448,    60,    19,     0,
      20,     0,    61,     0,     0,     0,     0,    62,     0,     0,
       0,    21,    22,    63,    23,     0,     0,    24,    25,   471,
      26,     0,     0,    64,     0,     0,    27,    28,    65,     0,
       0,    29,    30,    31,    66,   490,   471,   471,     0,     0,
       0,    67,     0,     0,     0,    68,    69,    32,     0,    70,
       0,    71,    33,     0,    72,     0,     0,    34,    35,    15,
      16,    17,    18,     0,     0,    58,    59,    36,    73,     0,
      60,    19,     0,    20,     0,    61,   341,     0,     0,     0,
      62,     0,     0,     0,    21,    22,    63,    23,     0,     0,
      24,    25,     0,    26,     0,     0,    64,     0,     0,    27,
      28,    65,     0,     0,    29,    30,    31,    66,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,    68,    69,
      32,     0,    70,     0,    71,    33,     0,    72,     0,     0,
      34,    35,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    73,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   289,   580,   582,   584,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   605,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   471,     0,   471
};

static const yytype_int16 yycheck[] =
{
       6,    10,     8,   288,   283,   434,   435,     3,     4,     5,
       3,     4,    18,    19,     0,    21,    22,    23,    24,    25,
     189,    27,    28,    29,    30,    31,    32,   123,    34,    35,
      19,   200,    21,    22,    23,    24,    25,    92,    27,    28,
      29,    30,    31,    32,    21,    34,    35,     3,     4,    20,
       3,     4,    20,   149,    60,     3,     4,     3,     4,     3,
       4,     3,     4,    20,    70,   161,     3,     4,    82,     3,
       4,    60,     3,     4,     5,    20,     3,     4,     5,     3,
       4,    70,     3,     4,     5,     3,     4,     5,    11,    36,
      96,     3,     4,     5,     3,     4,     5,    93,    28,    22,
      93,    42,    92,    20,    43,   119,   120,    21,   122,   115,
     116,    52,   126,    21,    92,   129,    93,   123,    21,   416,
     117,    21,    93,   419,    25,    93,   115,   281,   425,   283,
     421,   427,    58,   229,     3,     4,    93,    93,   429,   145,
      93,   138,   139,   149,    67,    93,    93,    93,    93,    93,
      93,    93,    93,     8,    93,   161,    93,    82,    82,    93,
      92,    92,    82,   459,   170,    92,     6,    93,    93,   460,
      93,    92,   169,   187,    92,     8,    93,    32,   184,    93,
      92,    58,    51,    92,   290,    93,    41,    42,     3,     4,
      93,    46,   206,    93,    71,    57,    58,    52,    58,    58,
     197,    12,   199,    58,   210,   634,    92,   636,    41,    42,
      43,    92,    71,    46,    69,    58,    93,    92,    73,    52,
      58,    51,    65,   229,   424,    58,    92,    65,    58,     8,
      85,    93,   432,    93,   231,    12,    69,    16,    93,   423,
      73,   418,    92,    76,    92,    78,    57,   431,    81,   426,
      93,   248,    85,    64,   260,    93,    92,   263,     3,     4,
      93,    92,    41,    42,    92,   262,    92,    92,   265,   275,
     276,   277,    92,    52,    92,    86,    87,    93,    26,    58,
      57,    93,    93,    92,    92,    33,    23,    64,    36,   458,
      69,   297,    23,   578,    73,    92,     8,   466,   467,    88,
      89,    90,    91,    93,    16,    42,    85,    92,   477,    86,
      87,    42,    92,   555,    93,    52,    93,   486,    92,    67,
      92,    52,    92,   329,   321,   604,   332,    92,    92,    41,
      42,    79,     3,     4,     5,    92,    92,   334,    86,    92,
      52,    92,    79,    80,    93,    92,    58,    93,    79,    80,
       3,     4,     5,    92,   217,    93,    93,    69,   221,   222,
     223,    73,    93,   226,   227,    92,    92,   373,   374,   375,
     376,    92,   386,    85,   383,    92,   124,     3,     4,     5,
      93,    93,    92,     8,   373,   374,   375,   376,     3,     4,
       5,    16,    92,   141,   142,    92,   393,   394,   395,   396,
     397,   398,   399,   400,   401,    92,   420,   214,   215,   216,
     407,   408,   409,   410,   428,    92,    41,    42,    92,    38,
      39,    93,   419,    92,   421,    92,    92,    52,    93,    92,
     427,    93,   429,    58,    53,    54,    55,    56,    93,    93,
      59,    93,    93,     8,    69,    93,    93,   444,    73,    93,
     447,    16,   449,    72,    93,    93,   453,   454,    93,    93,
      85,    92,   459,   460,   461,   462,   463,   464,    93,    93,
     484,    93,    92,   549,    93,    92,    41,    42,    92,    38,
      39,    92,   651,    92,   653,    92,   655,    52,    92,    92,
      92,    92,    92,    58,    53,    54,    55,    56,    92,    92,
      59,    92,   499,     8,    69,   502,    92,   504,    73,   506,
      92,    16,    92,    72,   511,   512,   513,    92,    92,    92,
      85,    92,   519,   520,   521,   522,    92,   186,    93,    92,
      92,    92,    92,   583,    93,    92,    41,    42,    92,    92,
      92,    92,    92,   184,    93,    92,    92,    52,    92,    92,
      92,   143,    93,    58,    93,    93,    93,   554,   555,   556,
     557,   558,    93,    92,    69,    93,   563,   564,    73,    93,
      93,    93,    93,    93,   571,   572,    93,   325,    93,   585,
      85,    93,   588,    93,    93,    93,    93,    93,   336,   337,
      93,    92,    92,    92,   591,   343,   593,   594,    92,   588,
      92,   598,   599,   351,    92,    -1,    93,    93,    93,    93,
     616,    93,    93,   361,    92,   402,    93,    93,    93,    93,
      92,   618,   619,    92,    92,   622,    93,   624,   625,    93,
      93,   628,    92,    92,    92,    92,    -1,    93,    92,    92,
      92,   638,   639,    93,   641,    93,   643,    93,    93,    93,
     647,   648,   658,    93,   402,   661,    92,    92,    92,   656,
     657,    93,    93,   660,    93,    92,   663,   664,   665,   666,
     667,   677,    92,    -1,   680,   423,   424,    93,   675,   676,
      93,    93,    93,   431,   432,   682,    93,   684,    93,   686,
     687,   688,    93,    93,    -1,   701,    -1,    -1,   695,   696,
     697,   698,    -1,    -1,    -1,    -1,    -1,   704,    -1,   706,
     716,   708,    -1,    -1,   711,   712,   713,   714,   715,    -1,
      -1,   718,    -1,   720,   721,   722,   723,   724,   725,   726,
     727,   728,   729,    -1,   731,    -1,    -1,   734,   735,   736,
     737,   738,   739,   740,    -1,    -1,    -1,    -1,    -1,   746,
     747,   748,   749,     1,     2,     3,     4,    -1,    -1,    -1,
      -1,    -1,   759,    -1,    -1,    -1,   763,    -1,    -1,    -1,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    -1,    -1,     9,    10,
      -1,    -1,    -1,    14,    15,    -1,    17,    -1,    19,    -1,
      -1,    -1,    60,    24,    -1,    -1,    -1,    28,    29,    30,
      31,    -1,    70,    34,    35,    -1,    37,    -1,    -1,    40,
      -1,    -1,    43,    44,    45,     8,    -1,    48,    49,    50,
      51,   589,    -1,    16,    -1,    -1,    -1,    58,    96,    -1,
      -1,    62,    63,    64,    -1,    66,    -1,    68,    69,   607,
      71,    -1,   610,    74,    75,   613,    -1,   115,    41,    42,
      -1,    -1,     8,    84,    85,   123,    -1,    -1,    -1,    52,
      16,    -1,    93,   131,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   143,    69,   145,    -1,    -1,
      73,   149,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    -1,    85,   161,    -1,    -1,    52,    -1,    -1,    -1,
      93,    -1,    58,    -1,    -1,    -1,    -1,   175,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,   184,    73,   186,   187,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,   207,
      -1,    -1,    -1,    -1,    -1,    -1,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,    -1,   226,   227,
     228,   229,    -1,    -1,   232,    -1,     3,     4,     5,     6,
      -1,    -1,     9,    10,    -1,    -1,    -1,    14,    15,    -1,
      17,    -1,    19,    -1,    -1,    -1,    -1,    24,    -1,    -1,
     258,    28,    29,    30,    31,    -1,    -1,    34,    35,    -1,
      37,    -1,    -1,    40,    -1,    -1,    43,    44,    45,    -1,
      -1,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    58,   290,    -1,    -1,    62,    63,    64,    -1,    66,
      -1,    68,    69,    -1,    71,    -1,    -1,    74,    75,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    84,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    93,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    31,    -1,    -1,    34,    35,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,   373,   374,   375,   376,    69,
      -1,    -1,    -1,    -1,    74,    75,     3,     4,     5,     6,
      -1,    -1,     9,    10,    84,   393,   394,    14,    15,    -1,
      17,    -1,    19,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    28,    29,    30,    31,    -1,    -1,    34,    35,   417,
      37,    -1,    -1,    40,    -1,    -1,    43,    44,    45,    -1,
      -1,    48,    49,    50,    51,   433,   434,   435,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    62,    63,    64,    -1,    66,
      -1,    68,    69,    -1,    71,    -1,    -1,    74,    75,     3,
       4,     5,     6,    -1,    -1,     9,    10,    84,    85,    -1,
      14,    15,    -1,    17,    -1,    19,    93,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    28,    29,    30,    31,    -1,    -1,
      34,    35,    -1,    37,    -1,    -1,    40,    -1,    -1,    43,
      44,    45,    -1,    -1,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    63,
      64,    -1,    66,    -1,    68,    69,    -1,    71,    -1,    -1,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   549,   550,   551,   552,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   577,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     588,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   634,    -1,   636
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    88,    89,    90,    91,    95,    96,   220,   126,   220,
     102,   220,   169,   220,     0,     3,     4,     5,     6,    15,
      17,    28,    29,    31,    34,    35,    37,    43,    44,    48,
      49,    50,    64,    69,    74,    75,    84,    97,    98,    99,
     100,   103,   106,   107,   120,   122,   124,   152,   154,   156,
     158,   160,   162,   164,   166,   187,   201,   214,     9,    10,
      14,    19,    24,    30,    40,    45,    51,    58,    62,    63,
      66,    68,    71,    85,    97,   129,   131,   148,   150,    58,
     129,     8,    16,    41,    42,    52,    58,    69,    73,    85,
     179,   211,   213,   214,   220,   211,    92,   211,   211,   211,
     211,   211,   210,   214,   220,   211,   211,   211,   211,   211,
     211,   210,   211,   211,   210,    28,    92,    92,   211,    92,
      92,   132,    92,    92,    92,   210,    92,    92,   211,    92,
     130,    92,   210,    92,     3,     4,   219,    92,    92,    92,
     210,    92,    92,    92,   202,    92,   212,   214,   220,    92,
     121,   123,   125,   163,    92,   167,   165,   159,   161,   153,
     188,    92,   155,   157,   108,   211,   214,     3,     4,   217,
      92,     5,   219,     5,   219,    92,   219,   212,   209,   210,
      92,   219,    25,   151,    92,   219,    92,   204,   220,    92,
     178,   219,    92,   175,   207,   210,   176,   217,   177,   217,
      92,   174,   210,   173,   206,   210,   204,    92,   214,   215,
     216,   220,    93,   212,    92,    92,    92,    92,   104,    92,
      92,    92,    92,    92,    92,   212,    92,    92,    92,    92,
      93,   217,   127,   214,    93,    93,    93,    93,   133,   220,
      93,    93,    93,     3,     4,     5,   218,    93,    92,    93,
     215,    93,   133,   149,   219,   220,   218,    93,   170,    93,
      20,    93,   217,    21,    93,   217,   218,    93,    93,    51,
     203,   220,    93,   214,    93,   126,   126,   126,   169,   105,
     220,   172,   220,   171,   220,   169,   169,   169,   191,   220,
     101,   169,   169,   109,   220,   212,   217,   128,   220,    38,
      39,    53,    54,    55,    56,    59,    72,    93,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   146,
      93,   217,    93,    93,    51,    58,    93,   168,   220,    92,
     214,   217,    92,   214,   217,    93,    92,    58,    93,    93,
      93,    93,    93,    58,    93,     8,    32,    41,    42,    46,
      52,    58,    69,    73,    93,   179,     8,    41,    42,    46,
      52,    58,    69,    73,    76,    78,    81,    93,   166,   179,
      93,    93,    93,    12,    57,    86,    87,    93,   187,   189,
     192,   195,   198,   102,    93,    93,    82,    93,   110,    93,
      93,    93,   214,    92,    92,    92,    92,    92,    92,    92,
      92,   217,    92,   210,    42,    52,    93,   214,    92,   214,
      92,   217,   208,   210,   210,   210,    92,    92,    92,    92,
      92,    92,   210,    92,    92,    92,    92,    92,    92,    92,
     210,    92,    92,    92,    92,    92,   211,   211,   211,   211,
      93,   111,   219,   145,   217,   220,   147,   217,   220,   217,
     217,   217,   217,   217,   217,    82,   217,   208,    92,    92,
      92,   217,   217,   217,   217,    93,    92,    92,   178,   186,
     205,   220,   175,   176,   185,   219,   177,    92,   174,   173,
     178,   175,   176,   180,   219,   177,    92,   174,   173,   183,
     220,   181,   205,   182,   205,   190,   193,   196,   199,    92,
     112,    93,   217,    93,   217,    93,   217,    93,    93,    93,
      93,   217,   217,    92,    82,    93,   218,   176,   177,   217,
     217,   217,   217,    93,   218,   218,    93,    93,   217,    93,
      93,    93,    93,   218,    93,    93,    93,    93,    93,    93,
     219,    93,   218,    93,    93,    36,    93,    93,    93,    92,
      92,    92,    92,   113,   217,    92,   217,   217,   217,    93,
     217,    93,   217,   217,    92,    93,    93,    93,    93,   217,
     217,   217,   217,    93,    93,    93,    93,    92,   191,   194,
     220,   197,   220,   200,   220,    23,    42,    52,    79,    80,
      93,   217,   113,   217,   217,   217,    93,    93,   217,   217,
      93,    93,   217,   217,   184,   220,    93,    58,    65,    93,
      58,    65,    93,    58,    93,   192,    92,   214,    92,    92,
     211,   210,   217,    93,   217,   217,    93,   217,   217,    93,
      93,    93,   166,   210,    92,   210,    92,   210,   214,    92,
     118,   217,   119,   217,    92,    92,   217,   217,   217,    93,
     217,    92,   205,    92,   205,    92,   217,   217,    20,    93,
     217,    21,    93,   217,   114,   115,   217,   217,    93,    93,
     218,    93,   218,    93,   218,   217,   217,    92,   214,   217,
      92,   214,   217,   116,   217,   117,   217,   217,   217,    93,
      93,    93,    93,   217,   217,   214,    92,   214,    92,   217,
      11,    22,    67,    93,   217,    93,   217,   217,   217,    93,
      93,   217,   217,   217,   217,    92,    92,   214,    92,   217,
     217,   217,   217,   217,   217,   217,   217,   214,    92,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,    93,    93,   217,   217,   217,   217,   217,   217,   217,
      93,    93,    93,    93,   217,    93,   217,    93,   217,   217,
      93,    93,    93,   217,   217
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    95,    95,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    98,    99,   101,
     100,   102,   102,   102,   104,   103,   105,   105,   106,   106,
     108,   107,   109,   109,   111,   110,   112,   110,   113,   113,
     113,   113,   114,   113,   115,   113,   113,   113,   113,   113,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   118,   118,   118,   119,   119,   119,   121,   120,   123,
     122,   125,   124,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   127,   128,   128,   130,   129,   132,   131,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   145,   146,   147,   147,   148,
     149,   149,   150,   151,   151,   153,   152,   155,   154,   157,
     156,   159,   158,   161,   160,   163,   162,   165,   164,   167,
     166,   168,   168,   168,   169,   170,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     173,   174,   175,   176,   176,   176,   177,   177,   177,   178,
     179,   180,   181,   182,   183,   183,   184,   184,   185,   186,
     188,   187,   190,   189,   191,   191,   191,   191,   191,   191,
     193,   192,   194,   194,   194,   196,   195,   197,   197,   197,
     199,   198,   200,   200,   200,   202,   201,   203,   203,   204,
     204,   205,   205,   206,   207,   208,   209,   210,   210,   211,
     212,   212,   213,   213,   214,   214,   214,   215,   215,   216,
     216,   217,   217,   218,   218,   218,   219,   219,   220
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     5,     0,
       7,     1,     6,     2,     0,     6,     1,     6,     5,     6,
       0,     6,     1,     2,     0,     5,     0,     6,     1,     2,
       3,     4,     0,     7,     0,     7,     5,     5,     8,     8,
       2,     3,     7,     8,     7,     7,     8,     7,     8,     0,
       4,     3,     8,     8,     4,     9,     9,     0,     6,     0,
       6,     0,     6,     1,     6,     5,     7,     7,     5,     5,
       5,     5,     5,     5,     5,     6,     5,     2,     2,     2,
       2,     5,     2,     1,     1,     2,     0,     5,     0,     5,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     5,     6,     4,     4,     4,     4,     7,
       5,     6,     4,     4,     1,     9,     4,     1,    16,     9,
       1,     6,     4,    11,    12,     0,     6,     0,     6,     0,
       6,     0,     6,     0,     6,     0,     6,     0,     6,     0,
       6,     1,     5,     5,     1,     0,     7,     5,     5,     5,
       2,     5,     5,     5,     6,     1,     5,     5,     5,     2,
       5,     5,     5,     5,     5,     5,     2,     5,     6,     1,
       5,     5,     5,     2,     5,     5,     5,     5,     5,     6,
       1,     1,     1,     3,     8,     8,     4,     9,     9,     1,
       8,     2,     1,     1,     1,     5,     1,     2,     1,     1,
       0,     6,     0,     6,     1,     2,     2,     2,     2,     2,
       0,     6,     1,     6,     5,     0,     6,     1,     6,     5,
       0,     6,     1,     6,     2,     0,     6,     1,     6,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     0
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
  case 7:
#line 251 "panda/src/egg/parser.yxx"
{
  assert(!egg_stack.empty());
  DCAST(EggData, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[0]._egg)));
}
#line 2288 "built/tmp/parser.yxx.c"
    break;

  case 27:
#line 296 "panda/src/egg/parser.yxx"
{
  string strval = (yyvsp[-1]._string);
  EggCoordinateSystem *cs = new EggCoordinateSystem;

  CoordinateSystem f = parse_coordinate_system_string(strval);
  if (f == CS_invalid) {
    eggyywarning("Unknown coordinate system " + strval);
  } else {
    cs->set_value(f);
  }
  (yyval._egg) = cs;
}
#line 2305 "built/tmp/parser.yxx.c"
    break;

  case 28:
#line 319 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = new EggComment((yyvsp[-3]._string), (yyvsp[-1]._string));
}
#line 2313 "built/tmp/parser.yxx.c"
    break;

  case 29:
#line 333 "panda/src/egg/parser.yxx"
{
  string tref_name = (yyvsp[-2]._string);
  Filename filename = (yyvsp[0]._string);
  EggTexture *texture = new EggTexture(tref_name, filename);

  if (textures.find(tref_name) != textures.end()) {
    eggyywarning("Duplicate texture name " + tref_name);
  }
  textures[tref_name] = texture;

  egg_stack.push_back(texture);
}
#line 2330 "built/tmp/parser.yxx.c"
    break;

  case 30:
#line 346 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 2339 "built/tmp/parser.yxx.c"
    break;

  case 32:
#line 362 "panda/src/egg/parser.yxx"
{
  EggTexture *texture = DCAST(EggTexture, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);
  string strval = (yyvsp[-1]._string);

  if (cmp_nocase_uh(name, "type") == 0) {
    EggTexture::TextureType tt = EggTexture::string_texture_type(strval);
    if (tt == EggTexture::TT_unspecified) {
      eggyywarning("Unknown texture texture_type " + strval);
    } else {
      texture->set_texture_type(tt);
    }

  } else if (cmp_nocase_uh(name, "format") == 0) {
    EggTexture::Format f = EggTexture::string_format(strval);
    if (f == EggTexture::F_unspecified) {
      eggyywarning("Unknown texture format " + strval);
    } else {
      texture->set_format(f);
    }

  } else if (cmp_nocase_uh(name, "compression") == 0) {
    EggTexture::CompressionMode w = EggTexture::string_compression_mode(strval);
    if (w == EggTexture::CM_default) {
      eggyywarning("Unknown texture compression mode " + strval);
    } else {
      texture->set_compression_mode(w);
    }

  } else if (cmp_nocase_uh(name, "wrap") == 0) {
    EggTexture::WrapMode w = EggTexture::string_wrap_mode(strval);
    if (w == EggTexture::WM_unspecified) {
      eggyywarning("Unknown texture wrap mode " + strval);
    } else {
      texture->set_wrap_mode(w);
    }

  } else if (cmp_nocase_uh(name, "wrapu") == 0) {
    EggTexture::WrapMode w = EggTexture::string_wrap_mode(strval);
    if (w == EggTexture::WM_unspecified) {
      eggyywarning("Unknown texture wrap mode " + strval);
    } else {
      texture->set_wrap_u(w);
    }

  } else if (cmp_nocase_uh(name, "wrapv") == 0) {
    EggTexture::WrapMode w = EggTexture::string_wrap_mode(strval);
    if (w == EggTexture::WM_unspecified) {
      eggyywarning("Unknown texture wrap mode " + strval);
    } else {
      texture->set_wrap_v(w);
    }

  } else if (cmp_nocase_uh(name, "minfilter") == 0) {
    EggTexture::FilterType f = EggTexture::string_filter_type(strval);
    if (f == EggTexture::FT_unspecified) {
      eggyywarning("Unknown texture filter type " + strval);
    } else {
      texture->set_minfilter(f);
    }

  } else if (cmp_nocase_uh(name, "magfilter") == 0) {
    EggTexture::FilterType f = EggTexture::string_filter_type(strval);
    if (f == EggTexture::FT_unspecified) {
      eggyywarning("Unknown texture filter type " + strval);
    } else {
      texture->set_magfilter(f);
    }

  } else if (cmp_nocase_uh(name, "anisotropic_degree") == 0) {
    texture->set_anisotropic_degree((int)value);

  } else if (cmp_nocase_uh(name, "envtype") == 0) {
    EggTexture::EnvType e = EggTexture::string_env_type(strval);
    if (e == EggTexture::ET_unspecified) {
      eggyywarning("Unknown texture env type " + strval);
    } else {
      texture->set_env_type(e);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb") == 0) {
    EggTexture::CombineMode cm = EggTexture::string_combine_mode(strval);
    if (cm == EggTexture::CM_unspecified) {
      eggyywarning("Unknown combine mode " + strval);
    } else {
      texture->set_combine_mode(EggTexture::CC_rgb, cm);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-source0") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_rgb, 0, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-operand0") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_rgb, 0, co);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-source1") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_rgb, 1, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-operand1") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_rgb, 1, co);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-source2") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_rgb, 2, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-operand2") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_rgb, 2, co);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha") == 0) {
    EggTexture::CombineMode cm = EggTexture::string_combine_mode(strval);
    if (cm == EggTexture::CM_unspecified) {
      eggyywarning("Unknown combine mode " + strval);
    } else {
      texture->set_combine_mode(EggTexture::CC_alpha, cm);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-source0") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_alpha, 0, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-operand0") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_alpha, 0, co);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-source1") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_alpha, 1, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-operand1") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_alpha, 1, co);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-source2") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_alpha, 2, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-operand2") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_alpha, 2, co);
    }

  } else if (cmp_nocase_uh(name, "saved_result") == 0) {
    texture->set_saved_result(((int)value) != 0);

  } else if (cmp_nocase_uh(name, "tex_gen") == 0) {
    EggTexture::TexGen tex_gen = EggTexture::string_tex_gen(strval);
    if (tex_gen == EggTexture::TG_unspecified) {
      eggyywarning("Unknown tex-gen " + strval);
    } else {
      texture->set_tex_gen(tex_gen);
    }

  } else if (cmp_nocase_uh(name, "quality_level") == 0) {
    EggTexture::QualityLevel quality_level = EggTexture::string_quality_level(strval);
    if (quality_level == EggTexture::QL_unspecified) {
      eggyywarning("Unknown quality-level " + strval);
    } else {
      texture->set_quality_level(quality_level);
    }

  } else if (cmp_nocase_uh(name, "stage_name") == 0) {
    texture->set_stage_name(strval);

  } else if (cmp_nocase_uh(name, "priority") == 0) {
    texture->set_priority((int)value);

  } else if (cmp_nocase_uh(name, "multiview") == 0) {
    texture->set_multiview(((int)value) != 0);

  } else if (cmp_nocase_uh(name, "num_views") == 0) {
    int int_value = (int)value;
    if (int_value < 1) {
      eggyyerror("Invalid num-views value " + strval);
    } else {
      texture->set_num_views(int_value);
    }

  } else if (cmp_nocase_uh(name, "blendr") == 0) {
    LColor color = texture->get_color();
    color[0] = value;
    texture->set_color(color);

  } else if (cmp_nocase_uh(name, "blendg") == 0) {
    LColor color = texture->get_color();
    color[1] = value;
    texture->set_color(color);

  } else if (cmp_nocase_uh(name, "blendb") == 0) {
    LColor color = texture->get_color();
    color[2] = value;
    texture->set_color(color);

  } else if (cmp_nocase_uh(name, "blenda") == 0) {
    LColor color = texture->get_color();
    color[3] = value;
    texture->set_color(color);

  } else if (cmp_nocase_uh(name, "borderr") == 0) {
    LColor border_color = texture->get_border_color();
    border_color[0] = value;
    texture->set_border_color(border_color);

  } else if (cmp_nocase_uh(name, "borderg") == 0) {
    LColor border_color = texture->get_border_color();
    border_color[1] = value;
    texture->set_border_color(border_color);

  } else if (cmp_nocase_uh(name, "borderb") == 0) {
    LColor border_color = texture->get_border_color();
    border_color[2] = value;
    texture->set_border_color(border_color);

  } else if (cmp_nocase_uh(name, "bordera") == 0) {
    LColor border_color = texture->get_border_color();
    border_color[3] = value;
    texture->set_border_color(border_color);

  } else if (cmp_nocase_uh(name, "uv_name") == 0) {
    texture->set_uv_name(strval);

  } else if (cmp_nocase_uh(name, "rgb_scale") == 0) {
    int int_value = (int)value;
    if (int_value != 1 && int_value != 2 && int_value != 4) {
      eggyyerror("Invalid rgb-scale value " + strval);
    } else {
      texture->set_rgb_scale(int_value);
    }

  } else if (cmp_nocase_uh(name, "alpha_scale") == 0) {
    int int_value = (int)value;
    if (int_value != 1 && int_value != 2 && int_value != 4) {
      eggyyerror("Invalid alpha-scale value " + strval);
    } else {
      texture->set_alpha_scale(int_value);
    }

  } else if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      texture->set_alpha_mode(a);
    }

  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      texture->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      texture->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      texture->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    texture->set_depth_offset((int)value);

  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    texture->set_draw_order((int)value);

  } else if (cmp_nocase_uh(name, "bin") == 0) {
    texture->set_bin(strval);

  } else if (cmp_nocase_uh(name, "alpha_file") == 0) {
    texture->set_alpha_filename(strval);

  } else if (cmp_nocase_uh(name, "alpha_file_channel") == 0) {
    texture->set_alpha_file_channel((int)value);

  } else if (cmp_nocase_uh(name, "read_mipmaps") == 0) {
    texture->set_read_mipmaps(((int)value) != 0);

  } else if (cmp_nocase_uh(name, "min_lod") == 0) {
    texture->set_min_lod(value);

  } else if (cmp_nocase_uh(name, "max_lod") == 0) {
    texture->set_max_lod(value);

  } else if (cmp_nocase_uh(name, "lod_bias") == 0) {
    texture->set_lod_bias(value);

  } else {
    eggyywarning("Unsupported texture scalar: " + name);
  }
}
#line 2698 "built/tmp/parser.yxx.c"
    break;

  case 34:
#line 728 "panda/src/egg/parser.yxx"
{
  string mref_name = (yyvsp[-1]._string);
  EggMaterial *material = new EggMaterial(mref_name);

  if (materials.find(mref_name) != materials.end()) {
    eggyywarning("Duplicate material name " + mref_name);
  }
  materials[mref_name] = material;

  egg_stack.push_back(material);
}
#line 2714 "built/tmp/parser.yxx.c"
    break;

  case 35:
#line 740 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 2723 "built/tmp/parser.yxx.c"
    break;

  case 37:
#line 756 "panda/src/egg/parser.yxx"
{
  EggMaterial *material = DCAST(EggMaterial, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);

  if (cmp_nocase_uh(name, "baser") == 0) {
    LColor base = material->get_base();
    base[0] = value;
    material->set_base(base);
  } else if (cmp_nocase_uh(name, "baseg") == 0) {
    LColor base = material->get_base();
    base[1] = value;
    material->set_base(base);
  } else if (cmp_nocase_uh(name, "baseb") == 0) {
    LColor base = material->get_base();
    base[2] = value;
    material->set_base(base);
  } else if (cmp_nocase_uh(name, "basea") == 0) {
    LColor base = material->get_base();
    base[3] = value;
    material->set_base(base);

  } else if (cmp_nocase_uh(name, "diffr") == 0) {
    LColor diff = material->get_diff();
    diff[0] = value;
    material->set_diff(diff);
  } else if (cmp_nocase_uh(name, "diffg") == 0) {
    LColor diff = material->get_diff();
    diff[1] = value;
    material->set_diff(diff);
  } else if (cmp_nocase_uh(name, "diffb") == 0) {
    LColor diff = material->get_diff();
    diff[2] = value;
    material->set_diff(diff);
  } else if (cmp_nocase_uh(name, "diffa") == 0) {
    LColor diff = material->get_diff();
    diff[3] = value;
    material->set_diff(diff);

  } else if (cmp_nocase_uh(name, "ambr") == 0) {
    LColor amb = material->get_amb();
    amb[0] = value;
    material->set_amb(amb);
  } else if (cmp_nocase_uh(name, "ambg") == 0) {
    LColor amb = material->get_amb();
    amb[1] = value;
    material->set_amb(amb);
  } else if (cmp_nocase_uh(name, "ambb") == 0) {
    LColor amb = material->get_amb();
    amb[2] = value;
    material->set_amb(amb);
  } else if (cmp_nocase_uh(name, "amba") == 0) {
    LColor amb = material->get_amb();
    amb[3] = value;
    material->set_amb(amb);

  } else if (cmp_nocase_uh(name, "emitr") == 0) {
    LColor emit = material->get_emit();
    emit[0] = value;
    material->set_emit(emit);
  } else if (cmp_nocase_uh(name, "emitg") == 0) {
    LColor emit = material->get_emit();
    emit[1] = value;
    material->set_emit(emit);
  } else if (cmp_nocase_uh(name, "emitb") == 0) {
    LColor emit = material->get_emit();
    emit[2] = value;
    material->set_emit(emit);
  } else if (cmp_nocase_uh(name, "emita") == 0) {
    LColor emit = material->get_emit();
    emit[3] = value;
    material->set_emit(emit);

  } else if (cmp_nocase_uh(name, "specr") == 0) {
    LColor spec = material->get_spec();
    spec[0] = value;
    material->set_spec(spec);
  } else if (cmp_nocase_uh(name, "specg") == 0) {
    LColor spec = material->get_spec();
    spec[1] = value;
    material->set_spec(spec);
  } else if (cmp_nocase_uh(name, "specb") == 0) {
    LColor spec = material->get_spec();
    spec[2] = value;
    material->set_spec(spec);
  } else if (cmp_nocase_uh(name, "speca") == 0) {
    LColor spec = material->get_spec();
    spec[3] = value;
    material->set_spec(spec);

  } else if (cmp_nocase_uh(name, "shininess") == 0) {
    material->set_shininess(value);

  } else if (cmp_nocase_uh(name, "roughness") == 0) {
    material->set_roughness(value);

  } else if (cmp_nocase_uh(name, "metallic") == 0) {
    material->set_metallic(value);

  } else if (cmp_nocase_uh(name, "ior") == 0) {
    material->set_ior(value);

  } else if (cmp_nocase_uh(name, "local") == 0) {
    material->set_local(value != 0.0);

  } else {
    eggyywarning("Unsupported material scalar: " + name);
  }
}
#line 2837 "built/tmp/parser.yxx.c"
    break;

  case 38:
#line 877 "panda/src/egg/parser.yxx"
{
  string node_name = (yyvsp[-3]._string);
  Filename filename = (yyvsp[-1]._string);
  EggExternalReference *ref = new EggExternalReference(node_name, filename);
  (yyval._egg) = ref;
}
#line 2848 "built/tmp/parser.yxx.c"
    break;

  case 39:
#line 884 "panda/src/egg/parser.yxx"
{
  if (cmp_nocase_uh((yyvsp[-5]._string), "group") != 0) {
    eggyyerror("keyword 'group' expected");
  }
  string node_name = (yyvsp[-3]._string);
  Filename filename = (yyvsp[-1]._string);
  EggExternalReference *ref = new EggExternalReference(node_name, filename);
  (yyval._egg) = ref;
}
#line 2862 "built/tmp/parser.yxx.c"
    break;

  case 40:
#line 904 "panda/src/egg/parser.yxx"
{
  string name = (yyvsp[0]._string);
  EggVertexPool *pool = nullptr;

  VertexPools::const_iterator vpi = vertex_pools.find(name);
  if (vpi != vertex_pools.end()) {
    pool = (*vpi).second;
    if (pool->has_defined_vertices()) {
      eggyywarning("Duplicate vertex pool name " + name);
      pool = new EggVertexPool(name);
      // The egg syntax starts counting at 1 by convention.
      pool->set_highest_index(0);
      vertex_pools[name] = pool;
    }
  } else {
    pool = new EggVertexPool(name);
    // The egg syntax starts counting at 1 by convention.
    pool->set_highest_index(0);
    vertex_pools[name] = pool;
  }

  egg_stack.push_back(pool);
}
#line 2890 "built/tmp/parser.yxx.c"
    break;

  case 41:
#line 928 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 2899 "built/tmp/parser.yxx.c"
    break;

  case 44:
#line 956 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggVertex);
}
#line 2907 "built/tmp/parser.yxx.c"
    break;

  case 45:
#line 960 "panda/src/egg/parser.yxx"
{
  PT(EggVertex) vtx = DCAST(EggVertex, egg_stack.back());
  egg_stack.pop_back();

  DCAST(EggVertexPool, egg_stack.back())->add_vertex(vtx);
}
#line 2918 "built/tmp/parser.yxx.c"
    break;

  case 46:
#line 967 "panda/src/egg/parser.yxx"
{
  vertex_index = (int)(yyvsp[0]._number);
  EggVertexPool *pool = DCAST(EggVertexPool, egg_stack.back());

  if (vertex_index < 0) {
    ostringstream errmsg;
    errmsg << "Ignoring invalid vertex index " << vertex_index
           << " in vertex pool " << pool->get_name() << std::ends;
    eggyywarning(errmsg);
    vertex_index = -1;

  } else if (pool->has_vertex(vertex_index)) {
    ostringstream errmsg;
    errmsg << "Ignoring duplicate vertex index " << vertex_index
           << " in vertex pool " << pool->get_name() << std::ends;
    eggyywarning(errmsg);
    vertex_index = -1;
  }

  // Even if we didn't like the vertex index number, we still need to
  // go ahead and parse the vertex.  We just won't save it.

  egg_stack.push_back(new EggVertex);
}
#line 2947 "built/tmp/parser.yxx.c"
    break;

  case 47:
#line 992 "panda/src/egg/parser.yxx"
{
  PT(EggVertex) vtx = DCAST(EggVertex, egg_stack.back());
  egg_stack.pop_back();

  EggVertexPool *pool = DCAST(EggVertexPool, egg_stack.back());
  if (vertex_index != -1) {
    pool->add_vertex(vtx, vertex_index);
  }
}
#line 2961 "built/tmp/parser.yxx.c"
    break;

  case 48:
#line 1013 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertex, egg_stack.back())->set_pos((yyvsp[0]._number));
}
#line 2969 "built/tmp/parser.yxx.c"
    break;

  case 49:
#line 1017 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertex, egg_stack.back())->set_pos(LPoint2d((yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 2977 "built/tmp/parser.yxx.c"
    break;

  case 50:
#line 1021 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertex, egg_stack.back())->set_pos(LPoint3d((yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 2985 "built/tmp/parser.yxx.c"
    break;

  case 51:
#line 1025 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertex, egg_stack.back())->set_pos(LPoint4d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 2993 "built/tmp/parser.yxx.c"
    break;

  case 52:
#line 1029 "panda/src/egg/parser.yxx"
{
  EggVertex *vertex = DCAST(EggVertex, egg_stack.back());
  EggVertexUV *uv = new EggVertexUV((yyvsp[-1]._string), LTexCoordd::zero());
  egg_stack.push_back(uv);
  if (vertex->has_uv((yyvsp[-1]._string))) {
    eggyywarning("Ignoring repeated UV name " + (yyvsp[-1]._string));
  } else {
    vertex->set_uv_obj(uv);
  }
}
#line 3008 "built/tmp/parser.yxx.c"
    break;

  case 53:
#line 1040 "panda/src/egg/parser.yxx"
{
  egg_stack.pop_back();
}
#line 3016 "built/tmp/parser.yxx.c"
    break;

  case 54:
#line 1044 "panda/src/egg/parser.yxx"
{
  EggVertex *vertex = DCAST(EggVertex, egg_stack.back());
  EggVertexAux *aux = new EggVertexAux((yyvsp[-1]._string), LVecBase4d::zero());
  egg_stack.push_back(aux);
  if (vertex->has_aux((yyvsp[-1]._string))) {
    eggyywarning("Ignoring repeated Aux name " + (yyvsp[-1]._string));
  } else {
    vertex->set_aux_obj(aux);
  }
}
#line 3031 "built/tmp/parser.yxx.c"
    break;

  case 55:
#line 1055 "panda/src/egg/parser.yxx"
{
  egg_stack.pop_back();
}
#line 3039 "built/tmp/parser.yxx.c"
    break;

  case 58:
#line 1061 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertex, egg_stack.back())->_dxyzs.
    insert(EggMorphVertex((yyvsp[-5]._string), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-5]._string));
  }
}
#line 3051 "built/tmp/parser.yxx.c"
    break;

  case 59:
#line 1069 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertex, egg_stack.back())->_dxyzs.
    insert(EggMorphVertex((yyvsp[-4]._string), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-4]._string));
  }
}
#line 3063 "built/tmp/parser.yxx.c"
    break;

  case 60:
#line 1088 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertexUV, egg_stack.back())->set_uv(LTexCoordd((yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 3071 "built/tmp/parser.yxx.c"
    break;

  case 61:
#line 1092 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertexUV, egg_stack.back())->set_uvw(LVecBase3d((yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 3079 "built/tmp/parser.yxx.c"
    break;

  case 62:
#line 1096 "panda/src/egg/parser.yxx"
{
  if (DCAST(EggVertexUV, egg_stack.back())->has_tangent()) {
    eggyywarning("Ignoring repeated tangent");
  } else {
    DCAST(EggVertexUV, egg_stack.back())->set_tangent(LNormald((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)));
  }
}
#line 3091 "built/tmp/parser.yxx.c"
    break;

  case 63:
#line 1104 "panda/src/egg/parser.yxx"
{
  if (DCAST(EggVertexUV, egg_stack.back())->has_tangent()) {
    eggyywarning("Ignoring repeated tangent");
  } else {
    DCAST(EggVertexUV, egg_stack.back())->set_tangent4(LVecBase4d((yyvsp[-4]._number), (yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)));
  }
}
#line 3103 "built/tmp/parser.yxx.c"
    break;

  case 64:
#line 1112 "panda/src/egg/parser.yxx"
{
  if (DCAST(EggVertexUV, egg_stack.back())->has_binormal()) {
    eggyywarning("Ignoring repeated binormal");
  } else {
    DCAST(EggVertexUV, egg_stack.back())->set_binormal(LNormald((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)));
  }
}
#line 3115 "built/tmp/parser.yxx.c"
    break;

  case 65:
#line 1120 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertexUV, egg_stack.back())->_duvs.
    insert(EggMorphTexCoord((yyvsp[-4]._string), LVector3d((yyvsp[-2]._number), (yyvsp[-1]._number), 0.0))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-4]._string));
  }
}
#line 3127 "built/tmp/parser.yxx.c"
    break;

  case 66:
#line 1128 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertexUV, egg_stack.back())->_duvs.
    insert(EggMorphTexCoord((yyvsp[-5]._string), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-5]._string));
  }
}
#line 3139 "built/tmp/parser.yxx.c"
    break;

  case 67:
#line 1136 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertexUV, egg_stack.back())->_duvs.
    insert(EggMorphTexCoord((yyvsp[-3]._string), LVector3d((yyvsp[-2]._number), (yyvsp[-1]._number), 0.0))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-3]._string));
  }
}
#line 3151 "built/tmp/parser.yxx.c"
    break;

  case 68:
#line 1144 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertexUV, egg_stack.back())->_duvs.
    insert(EggMorphTexCoord((yyvsp[-4]._string), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-4]._string));
  }
}
#line 3163 "built/tmp/parser.yxx.c"
    break;

  case 70:
#line 1162 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertexAux, egg_stack.back())->set_aux(LVecBase4d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 3171 "built/tmp/parser.yxx.c"
    break;

  case 71:
#line 1176 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertex, egg_stack.back())->set_normal(LNormald((yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 3179 "built/tmp/parser.yxx.c"
    break;

  case 72:
#line 1180 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertex, egg_stack.back())->_dnormals.
    insert(EggMorphNormal((yyvsp[-5]._string), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-5]._string));
  }
}
#line 3191 "built/tmp/parser.yxx.c"
    break;

  case 73:
#line 1188 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertex, egg_stack.back())->_dnormals.
    insert(EggMorphNormal((yyvsp[-4]._string), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-4]._string));
  }
}
#line 3203 "built/tmp/parser.yxx.c"
    break;

  case 74:
#line 1206 "panda/src/egg/parser.yxx"
{
  DCAST(EggVertex, egg_stack.back())->set_color(LColor((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 3211 "built/tmp/parser.yxx.c"
    break;

  case 75:
#line 1210 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertex, egg_stack.back())->_drgbas.
    insert(EggMorphColor((yyvsp[-6]._string), LVector4((yyvsp[-4]._number), (yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-6]._string));
  }
}
#line 3223 "built/tmp/parser.yxx.c"
    break;

  case 76:
#line 1218 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggVertex, egg_stack.back())->_drgbas.
    insert(EggMorphColor((yyvsp[-5]._string), LVector4((yyvsp[-4]._number), (yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-5]._string));
  }
}
#line 3235 "built/tmp/parser.yxx.c"
    break;

  case 77:
#line 1236 "panda/src/egg/parser.yxx"
{
  EggGroup *group = new EggGroup((yyvsp[0]._string));
  egg_stack.push_back(group);
}
#line 3244 "built/tmp/parser.yxx.c"
    break;

  case 78:
#line 1241 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  (yyval._egg) = group;
  egg_stack.pop_back();
  if (group->has_name()) {
    groups[group->get_name()] = group;
  }
  Thread::consider_yield();
}
#line 3258 "built/tmp/parser.yxx.c"
    break;

  case 79:
#line 1261 "panda/src/egg/parser.yxx"
{
  EggGroup *group = new EggGroup((yyvsp[0]._string));
  group->set_group_type(EggGroup::GT_joint);
  egg_stack.push_back(group);
}
#line 3268 "built/tmp/parser.yxx.c"
    break;

  case 80:
#line 1267 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3277 "built/tmp/parser.yxx.c"
    break;

  case 81:
#line 1282 "panda/src/egg/parser.yxx"
{
  EggGroup *group = new EggGroup((yyvsp[0]._string));
  group->set_group_type(EggGroup::GT_instance);
  egg_stack.push_back(group);
}
#line 3287 "built/tmp/parser.yxx.c"
    break;

  case 82:
#line 1288 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  (yyval._egg) = group;
  egg_stack.pop_back();
  if (group->has_name()) {
    groups[group->get_name()] = group;
  }
}
#line 3300 "built/tmp/parser.yxx.c"
    break;

  case 84:
#line 1308 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);
  unsigned long ulong_value = (yyvsp[-1]._ulong);
  string strval = (yyvsp[-1]._string);

  if (cmp_nocase_uh(name, "fps") == 0) {
    group->set_switch_fps(value);

  } else if (cmp_nocase_uh(name, "no_fog") == 0) {
    group->set_nofog_flag(value != 0);

  } else if (cmp_nocase_uh(name, "decal") == 0) {
    group->set_decal_flag(value != 0);

  } else if (cmp_nocase_uh(name, "direct") == 0) {
    group->set_direct_flag(value != 0);

  } else if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      group->set_alpha_mode(a);
    }

  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      group->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      group->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      group->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    group->set_depth_offset(ulong_value);

  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    group->set_draw_order(ulong_value);

  } else if (cmp_nocase_uh(name, "bin") == 0) {
    group->set_bin(strval);

  } else if (cmp_nocase_uh(name, "collide_mask") == 0) {
    group->set_collide_mask(group->get_collide_mask() | ulong_value);

  } else if (cmp_nocase_uh(name, "from_collide_mask") == 0) {
    group->set_from_collide_mask(group->get_from_collide_mask() | ulong_value);

  } else if (cmp_nocase_uh(name, "into_collide_mask") == 0) {
    group->set_into_collide_mask(group->get_into_collide_mask() | ulong_value);

  } else if (cmp_nocase_uh(name, "portal") == 0) {
    group->set_portal_flag(value != 0);

  } else if (cmp_nocase_uh(name, "occluder") == 0) {
    group->set_occluder_flag(value != 0);

  } else if (cmp_nocase_uh(name, "polylight") == 0) {
    group->set_polylight_flag(value != 0);

  } else if (cmp_nocase_uh(name, "indexed") == 0) {
    group->set_indexed_flag(value != 0);

  } else if (cmp_nocase_uh(name, "scroll_u") == 0) {
    group->set_scroll_u(value);

  } else if (cmp_nocase_uh(name, "scroll_v") == 0) {
    group->set_scroll_v(value);

  } else if (cmp_nocase_uh(name, "scroll_w") == 0) {
    group->set_scroll_w(value);

  } else if (cmp_nocase_uh(name, "scroll_r") == 0) {
    group->set_scroll_r(value);

  } else if (cmp_nocase_uh(name, "blend") == 0) {
    EggGroup::BlendMode blend_mode =
      EggGroup::string_blend_mode(strval);
    if (blend_mode == EggGroup::BM_unspecified) {
      eggyywarning("Unknown blend mode " + strval);
    } else {
      group->set_blend_mode(blend_mode);
    }

  } else if (cmp_nocase_uh(name, "blendop_a") == 0) {
    EggGroup::BlendOperand blend_operand =
      EggGroup::string_blend_operand(strval);
    if (blend_operand == EggGroup::BO_unspecified) {
      eggyywarning("Unknown blend operand " + strval);
    } else {
      group->set_blend_operand_a(blend_operand);
    }

  } else if (cmp_nocase_uh(name, "blendop_b") == 0) {
    EggGroup::BlendOperand blend_operand =
      EggGroup::string_blend_operand(strval);
    if (blend_operand == EggGroup::BO_unspecified) {
      eggyywarning("Unknown blend operand " + strval);
    } else {
      group->set_blend_operand_b(blend_operand);
    }

  } else if (cmp_nocase_uh(name, "blendr") == 0) {
    LColor color = group->get_blend_color();
    color[0] = value;
    group->set_blend_color(color);

  } else if (cmp_nocase_uh(name, "blendg") == 0) {
    LColor color = group->get_blend_color();
    color[1] = value;
    group->set_blend_color(color);

  } else if (cmp_nocase_uh(name, "blendb") == 0) {
    LColor color = group->get_blend_color();
    color[2] = value;
    group->set_blend_color(color);

  } else if (cmp_nocase_uh(name, "blenda") == 0) {
    LColor color = group->get_blend_color();
    color[3] = value;
    group->set_blend_color(color);

  } else {
    eggyywarning("Unknown group scalar " + name);
  }
}
#line 3452 "built/tmp/parser.yxx.c"
    break;

  case 85:
#line 1456 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[-1]._string);

  EggGroup::BillboardType f = EggGroup::string_billboard_type(strval);
  if (f == EggGroup::BT_none) {
    eggyywarning("Unknown billboard type " + strval);
  } else {
    group->set_billboard_type(f);
  }
}
#line 3468 "built/tmp/parser.yxx.c"
    break;

  case 86:
#line 1468 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  group->set_billboard_center(LPoint3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)));
}
#line 3477 "built/tmp/parser.yxx.c"
    break;

  case 87:
#line 1473 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string name = (yyvsp[-4]._string);

  group->set_collision_name(name);
}
#line 3488 "built/tmp/parser.yxx.c"
    break;

  case 88:
#line 1480 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[-1]._number);
  group->set_dcs_type(value!=0 ? EggGroup::DC_default : EggGroup::DC_none);
}
#line 3498 "built/tmp/parser.yxx.c"
    break;

  case 89:
#line 1486 "panda/src/egg/parser.yxx"
{
  // The special flavor of DCS, with { sync } or { nosync }.
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[-1]._string);

  EggGroup::DCSType f = EggGroup::string_dcs_type(strval);
  if (f == EggGroup::DC_unspecified) {
    eggyywarning("Unknown DCS type " + strval);
  } else {
    group->set_dcs_type(f);
  }
}
#line 3515 "built/tmp/parser.yxx.c"
    break;

  case 90:
#line 1499 "panda/src/egg/parser.yxx"
{
  // The traditional flavor of DART, with { 0 } or { 1 }.
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[-1]._number);
  group->set_dart_type(value!=0 ? EggGroup::DT_default : EggGroup::DT_none);
}
#line 3526 "built/tmp/parser.yxx.c"
    break;

  case 91:
#line 1506 "panda/src/egg/parser.yxx"
{
  // The special flavor of DART, with { sync } or { nosync }.
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[-1]._string);

  EggGroup::DartType f = EggGroup::string_dart_type(strval);
  if (f == EggGroup::DT_none) {
    eggyywarning("Unknown dart type " + strval);
  } else {
    group->set_dart_type(f);
  }
}
#line 3543 "built/tmp/parser.yxx.c"
    break;

  case 92:
#line 1519 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[-1]._number);
  group->set_switch_flag(value!=0);
}
#line 3553 "built/tmp/parser.yxx.c"
    break;

  case 93:
#line 1525 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string type = (yyvsp[-1]._string);
  group->add_object_type(type);
}
#line 3563 "built/tmp/parser.yxx.c"
    break;

  case 94:
#line 1531 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[-1]._number);
  group->set_model_flag(value!=0);
}
#line 3573 "built/tmp/parser.yxx.c"
    break;

  case 95:
#line 1537 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  group->set_tag((yyvsp[-3]._string), (yyvsp[-1]._string));
}
#line 3582 "built/tmp/parser.yxx.c"
    break;

  case 96:
#line 1542 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[-1]._number);
  group->set_texlist_flag(value!=0);
}
#line 3592 "built/tmp/parser.yxx.c"
    break;

  case 101:
#line 1552 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  if (group->get_group_type() != EggGroup::GT_instance) {
    eggyyerror("<Ref> valid only within <Instance>");
  } else if ((yyvsp[-1]._egg) != nullptr) {
    group->add_group_ref(DCAST(EggGroup, (yyvsp[-1]._egg)));
  }
}
#line 3605 "built/tmp/parser.yxx.c"
    break;

  case 102:
#line 1561 "panda/src/egg/parser.yxx"
{
  DCAST(EggGroup, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[0]._egg)));
}
#line 3613 "built/tmp/parser.yxx.c"
    break;

  case 103:
#line 1575 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[0]._string);

  EggGroup::CollisionSolidType f = EggGroup::string_cs_type(strval);
  if (f == EggGroup::CST_none) {
    eggyywarning("Unknown collision solid type " + strval);
  } else {
    if (f == EggGroup::CST_polyset && group->get_cs_type() != EggGroup::CST_none) {
      // By convention, a CST_polyset doesn't replace any existing
      // contradictory type, so ignore it if this happens.  This
      // allows the artist to place, for instance, <ObjectType> {
      // sphere } and <ObjectType> { trigger } together.

    } else {
      group->set_cs_type(f);
    }
  }
}
#line 3637 "built/tmp/parser.yxx.c"
    break;

  case 105:
#line 1606 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[0]._string);

  EggGroup::CollideFlags f = EggGroup::string_collide_flags(strval);
  if (f == EggGroup::CF_none) {
    eggyywarning("Unknown collision flag " + strval);
  } else {
    group->set_collide_flags(group->get_collide_flags() | f);
  }
}
#line 3653 "built/tmp/parser.yxx.c"
    break;

  case 106:
#line 1628 "panda/src/egg/parser.yxx"
{
  egg_top_transform = egg_stack.back()->as_transform();
  egg_top_transform->clear_transform();
}
#line 3662 "built/tmp/parser.yxx.c"
    break;

  case 108:
#line 1644 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  if (group->get_group_type() != EggGroup::GT_joint) {
    eggyywarning("Unexpected <DefaultPose> outside of <Joint>");
  }
  egg_top_transform = &group->modify_default_pose();
  egg_top_transform->clear_transform();
}
#line 3675 "built/tmp/parser.yxx.c"
    break;

  case 123:
#line 1681 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_translate2d(LVector2d((yyvsp[-2]._number), (yyvsp[-1]._number)));
}
#line 3683 "built/tmp/parser.yxx.c"
    break;

  case 124:
#line 1688 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_translate3d(LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)));
}
#line 3691 "built/tmp/parser.yxx.c"
    break;

  case 125:
#line 1695 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_rotate2d((yyvsp[-1]._number));
}
#line 3699 "built/tmp/parser.yxx.c"
    break;

  case 126:
#line 1702 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_rotx((yyvsp[-1]._number));
}
#line 3707 "built/tmp/parser.yxx.c"
    break;

  case 127:
#line 1709 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_roty((yyvsp[-1]._number));
}
#line 3715 "built/tmp/parser.yxx.c"
    break;

  case 128:
#line 1716 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_rotz((yyvsp[-1]._number));
}
#line 3723 "built/tmp/parser.yxx.c"
    break;

  case 129:
#line 1723 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_rotate3d((yyvsp[-4]._number), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)));
}
#line 3731 "built/tmp/parser.yxx.c"
    break;

  case 130:
#line 1730 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_scale2d(LVecBase2d((yyvsp[-2]._number), (yyvsp[-1]._number)));
}
#line 3739 "built/tmp/parser.yxx.c"
    break;

  case 131:
#line 1737 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_scale3d(LVecBase3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)));
}
#line 3747 "built/tmp/parser.yxx.c"
    break;

  case 132:
#line 1744 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_uniform_scale((yyvsp[-1]._number));
}
#line 3755 "built/tmp/parser.yxx.c"
    break;

  case 135:
#line 1758 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_matrix3
    (LMatrix3d((yyvsp[-8]._number), (yyvsp[-7]._number), (yyvsp[-6]._number),
               (yyvsp[-5]._number), (yyvsp[-4]._number), (yyvsp[-3]._number),
               (yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 3766 "built/tmp/parser.yxx.c"
    break;

  case 138:
#line 1776 "panda/src/egg/parser.yxx"
{
  egg_top_transform->add_matrix4
    (LMatrix4d((yyvsp[-15]._number), (yyvsp[-14]._number), (yyvsp[-13]._number), (yyvsp[-12]._number),
               (yyvsp[-11]._number), (yyvsp[-10]._number), (yyvsp[-9]._number), (yyvsp[-8]._number),
               (yyvsp[-7]._number), (yyvsp[-6]._number), (yyvsp[-5]._number), (yyvsp[-4]._number),
               (yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 3778 "built/tmp/parser.yxx.c"
    break;

  case 139:
#line 1795 "panda/src/egg/parser.yxx"
{
  if ((yyvsp[-2]._egg) != nullptr) {
    EggVertexPool *pool = DCAST(EggVertexPool, (yyvsp[-2]._egg));
    EggGroup *group = DCAST(EggGroup, egg_stack.back());
    PTA_double nums = (yyvsp[-6]._number_list);
    double membership = (yyvsp[-5]._number);

    for (int i = 0; i < (int)nums.size(); i++) {
      int index = (int)nums[i];
      EggVertex *vertex = pool->get_forward_vertex(index);
      if (vertex == nullptr) {
        ostringstream errmsg;
        errmsg << "No vertex " << index << " in pool " << pool->get_name()
               << std::ends;
        eggyyerror(errmsg);
      } else {
        group->ref_vertex(vertex, membership);
      }
    }
  }
}
#line 3804 "built/tmp/parser.yxx.c"
    break;

  case 140:
#line 1828 "panda/src/egg/parser.yxx"
{
  (yyval._number) = 1.0;
}
#line 3812 "built/tmp/parser.yxx.c"
    break;

  case 141:
#line 1832 "panda/src/egg/parser.yxx"
{
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);
  double result = (yyvsp[-5]._number);

  if (cmp_nocase_uh(name, "membership") == 0) {
    result = value;
  } else {
    eggyywarning("Unknown group vertex scalar " + name);
  }

  (yyval._number) = result;
}
#line 3830 "built/tmp/parser.yxx.c"
    break;

  case 143:
#line 1869 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  group->set_lod(EggSwitchConditionDistance((yyvsp[-8]._number), (yyvsp[-7]._number), LPoint3d((yyvsp[-4]._number), (yyvsp[-3]._number), (yyvsp[-2]._number))));
}
#line 3839 "built/tmp/parser.yxx.c"
    break;

  case 144:
#line 1874 "panda/src/egg/parser.yxx"
{
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  group->set_lod(EggSwitchConditionDistance((yyvsp[-9]._number), (yyvsp[-8]._number), LPoint3d((yyvsp[-4]._number), (yyvsp[-3]._number), (yyvsp[-2]._number)), (yyvsp[-7]._number)));
}
#line 3848 "built/tmp/parser.yxx.c"
    break;

  case 145:
#line 1891 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggPolygon((yyvsp[0]._string)));
}
#line 3856 "built/tmp/parser.yxx.c"
    break;

  case 146:
#line 1895 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3865 "built/tmp/parser.yxx.c"
    break;

  case 147:
#line 1910 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggTriangleFan((yyvsp[0]._string)));
}
#line 3873 "built/tmp/parser.yxx.c"
    break;

  case 148:
#line 1914 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3882 "built/tmp/parser.yxx.c"
    break;

  case 149:
#line 1929 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggTriangleStrip((yyvsp[0]._string)));
}
#line 3890 "built/tmp/parser.yxx.c"
    break;

  case 150:
#line 1933 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3899 "built/tmp/parser.yxx.c"
    break;

  case 151:
#line 1948 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggPatch((yyvsp[0]._string)));
}
#line 3907 "built/tmp/parser.yxx.c"
    break;

  case 152:
#line 1952 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3916 "built/tmp/parser.yxx.c"
    break;

  case 153:
#line 1967 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggPoint((yyvsp[0]._string)));
}
#line 3924 "built/tmp/parser.yxx.c"
    break;

  case 154:
#line 1971 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3933 "built/tmp/parser.yxx.c"
    break;

  case 155:
#line 1986 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggLine((yyvsp[0]._string)));
}
#line 3941 "built/tmp/parser.yxx.c"
    break;

  case 156:
#line 1990 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3950 "built/tmp/parser.yxx.c"
    break;

  case 157:
#line 2005 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggNurbsSurface((yyvsp[0]._string)));
}
#line 3958 "built/tmp/parser.yxx.c"
    break;

  case 158:
#line 2009 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3967 "built/tmp/parser.yxx.c"
    break;

  case 159:
#line 2024 "panda/src/egg/parser.yxx"
{
  egg_stack.push_back(new EggNurbsCurve((yyvsp[0]._string)));
}
#line 3975 "built/tmp/parser.yxx.c"
    break;

  case 160:
#line 2028 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 3984 "built/tmp/parser.yxx.c"
    break;

  case 165:
#line 2058 "panda/src/egg/parser.yxx"
{
  if (!egg_stack.back()->is_of_type(EggCompositePrimitive::get_class_type())) {
    eggyyerror("Not a composite primitive; components are not allowed here.");
  } else {
    PT(EggCompositePrimitive) comp = DCAST(EggCompositePrimitive, egg_stack.back());
    if ((yyvsp[-1]._number) < 0 || (yyvsp[-1]._number) >= comp->get_num_components()) {
      eggyyerror("Invalid component number");
    }
  }
  // We temporarily add an EggPolygon to the stack, just to receive
  // the component attributes.
  egg_stack.push_back(new EggPolygon);
}
#line 4002 "built/tmp/parser.yxx.c"
    break;

  case 166:
#line 2072 "panda/src/egg/parser.yxx"
{
  PT(EggPrimitive) prim = DCAST(EggPrimitive, egg_stack.back());
  egg_stack.pop_back();
  PT(EggCompositePrimitive) comp = DCAST(EggCompositePrimitive, egg_stack.back());
  comp->set_component((int)(yyvsp[-4]._number), prim);
}
#line 4013 "built/tmp/parser.yxx.c"
    break;

  case 174:
#line 2086 "panda/src/egg/parser.yxx"
{
  EggPrimitive *primitive = DCAST(EggPrimitive, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);
  string strval = (yyvsp[-1]._string);

  if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      primitive->set_alpha_mode(a);
    }
  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      primitive->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      primitive->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      primitive->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    primitive->set_depth_offset((int)value);
  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    primitive->set_draw_order((int)value);
  } else if (cmp_nocase_uh(name, "bin") == 0) {
    primitive->set_bin(strval);
  } else if (cmp_nocase_uh(name, "thick") == 0) {
    if (primitive->is_of_type(EggLine::get_class_type())) {
      DCAST(EggLine, primitive)->set_thick(value);
    } else if (primitive->is_of_type(EggPoint::get_class_type())) {
      DCAST(EggPoint, primitive)->set_thick(value);
    } else {
      eggyywarning("scalar thick is only meaningful for points and lines.");
    }
  } else if (cmp_nocase_uh(name, "perspective") == 0) {
    if (primitive->is_of_type(EggPoint::get_class_type())) {
      DCAST(EggPoint, primitive)->set_perspective(value != 0);
    } else {
      eggyywarning("scalar perspective is only meaningful for points.");
    }
  } else {
    eggyywarning("Unknown scalar " + name);
  }
}
#line 4082 "built/tmp/parser.yxx.c"
    break;

  case 186:
#line 2172 "panda/src/egg/parser.yxx"
{
  EggNurbsCurve *curve = DCAST(EggNurbsCurve, (yyvsp[0]._egg));
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  nurbs->_curves_on_surface.push_back(curve);
}
#line 4092 "built/tmp/parser.yxx.c"
    break;

  case 188:
#line 2179 "panda/src/egg/parser.yxx"
{
  EggNurbsSurface *primitive = DCAST(EggNurbsSurface, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);
  string strval = (yyvsp[-1]._string);

  if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      primitive->set_alpha_mode(a);
    }
  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      primitive->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      primitive->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      primitive->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    primitive->set_depth_offset((int)value);
  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    primitive->set_draw_order((int)value);
  } else if (cmp_nocase_uh(name, "bin") == 0) {
    primitive->set_bin(strval);
  } else if (cmp_nocase_uh(name, "u_subdiv") == 0) {
    primitive->set_u_subdiv((int)value);
  } else if (cmp_nocase_uh(name, "v_subdiv") == 0) {
    primitive->set_v_subdiv((int)value);
  } else {
    eggyywarning("Unknown scalar " + name);
  }
}
#line 4151 "built/tmp/parser.yxx.c"
    break;

  case 199:
#line 2255 "panda/src/egg/parser.yxx"
{
  EggNurbsCurve *primitive = DCAST(EggNurbsCurve, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);
  string strval = (yyvsp[-1]._string);

  if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      primitive->set_alpha_mode(a);
    }
  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      primitive->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      primitive->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      primitive->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    primitive->set_depth_offset((int)value);
  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    primitive->set_draw_order((int)value);
  } else if (cmp_nocase_uh(name, "bin") == 0) {
    primitive->set_bin(strval);
  } else if (cmp_nocase_uh(name, "subdiv") == 0) {
    primitive->set_subdiv((int)value);
  } else if (cmp_nocase_uh(name, "type") == 0) {
    EggCurve::CurveType a = EggCurve::string_curve_type(strval);
    if (a == EggCurve::CT_none) {
      eggyywarning("Unknown curve type " + strval);
    } else {
      primitive->set_curve_type(a);
    }

  } else {
    eggyywarning("Unknown scalar " + name);
  }
}
#line 4216 "built/tmp/parser.yxx.c"
    break;

  case 200:
#line 2326 "panda/src/egg/parser.yxx"
{
  if ((yyvsp[0]._egg) != nullptr) {
    EggTexture *texture = DCAST(EggTexture, (yyvsp[0]._egg));
    DCAST(EggPrimitive, egg_stack.back())->add_texture(texture);
  }
}
#line 4227 "built/tmp/parser.yxx.c"
    break;

  case 201:
#line 2343 "panda/src/egg/parser.yxx"
{
  EggTexture *texture = nullptr;

  // Defining a texture on-the-fly.
  Filename filename = (yyvsp[0]._string);
  string tref_name = filename.get_basename();

  Textures::iterator vpi = textures.find(tref_name);
  if (vpi == textures.end()) {
    // The texture was not yet defined.  Define it.
    texture = new EggTexture(tref_name, filename);
    textures[tref_name] = texture;

    if (egg_top_node != nullptr) {
      egg_top_node->add_child(texture);
    }

  } else {
    // The texture already existed.  Use it.
    texture = (*vpi).second;
    if (filename != texture->get_filename()) {
      eggyywarning(string("Using previous path: ") +
                   texture->get_filename().get_fullpath());
    }
  }

  nassertr(texture != nullptr, 0);
  DCAST(EggPrimitive, egg_stack.back())->add_texture(texture);
}
#line 4261 "built/tmp/parser.yxx.c"
    break;

  case 202:
#line 2383 "panda/src/egg/parser.yxx"
{
  if ((yyvsp[0]._egg) != nullptr) {
    EggMaterial *material = DCAST(EggMaterial, (yyvsp[0]._egg));
    DCAST(EggPrimitive, egg_stack.back())->set_material(material);
  }
}
#line 4272 "built/tmp/parser.yxx.c"
    break;

  case 203:
#line 2400 "panda/src/egg/parser.yxx"
{
  DCAST(EggPrimitive, egg_stack.back())->set_normal(LNormald((yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 4280 "built/tmp/parser.yxx.c"
    break;

  case 204:
#line 2404 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggPrimitive, egg_stack.back())->_dnormals.
    insert(EggMorphNormal((yyvsp[-5]._string), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-5]._string));
  }
}
#line 4292 "built/tmp/parser.yxx.c"
    break;

  case 205:
#line 2412 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggPrimitive, egg_stack.back())->_dnormals.
    insert(EggMorphNormal((yyvsp[-4]._string), LVector3d((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-4]._string));
  }
}
#line 4304 "built/tmp/parser.yxx.c"
    break;

  case 206:
#line 2430 "panda/src/egg/parser.yxx"
{
  DCAST(EggPrimitive, egg_stack.back())->set_color(LColor((yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number), (yyvsp[0]._number)));
}
#line 4312 "built/tmp/parser.yxx.c"
    break;

  case 207:
#line 2434 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggPrimitive, egg_stack.back())->_drgbas.
    insert(EggMorphColor((yyvsp[-6]._string), LVector4((yyvsp[-4]._number), (yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-6]._string));
  }
}
#line 4324 "built/tmp/parser.yxx.c"
    break;

  case 208:
#line 2442 "panda/src/egg/parser.yxx"
{
  bool inserted = DCAST(EggPrimitive, egg_stack.back())->_drgbas.
    insert(EggMorphColor((yyvsp[-5]._string), LVector4((yyvsp[-4]._number), (yyvsp[-3]._number), (yyvsp[-2]._number), (yyvsp[-1]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[-5]._string));
  }
}
#line 4336 "built/tmp/parser.yxx.c"
    break;

  case 209:
#line 2460 "panda/src/egg/parser.yxx"
{
  EggPrimitive *primitive = DCAST(EggPrimitive, egg_stack.back());
  int value = (int)(yyvsp[0]._number);
  primitive->set_bface_flag(value!=0);
}
#line 4346 "built/tmp/parser.yxx.c"
    break;

  case 210:
#line 2476 "panda/src/egg/parser.yxx"
{
  if ((yyvsp[-2]._egg) != nullptr) {
    EggVertexPool *pool = DCAST(EggVertexPool, (yyvsp[-2]._egg));
    EggPrimitive *prim = DCAST(EggPrimitive, egg_stack.back());
    PTA_double nums = (yyvsp[-5]._number_list);

    for (int i = 0; i < (int)nums.size(); i++) {
      int index = (int)nums[i];
      EggVertex *vertex = pool->get_forward_vertex(index);
      if (vertex == nullptr) {
        ostringstream errmsg;
        errmsg << "No vertex " << index << " in pool " << pool->get_name()
               << std::ends;
        eggyyerror(errmsg);
      } else {
        prim->add_vertex(vertex);
      }
    }
  }
}
#line 4371 "built/tmp/parser.yxx.c"
    break;

  case 211:
#line 2507 "panda/src/egg/parser.yxx"
{
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  int u_order = (int)(yyvsp[-1]._number);
  int v_order = (int)(yyvsp[0]._number);
  nurbs->set_u_order(u_order);
  nurbs->set_v_order(v_order);
}
#line 4383 "built/tmp/parser.yxx.c"
    break;

  case 212:
#line 2525 "panda/src/egg/parser.yxx"
{
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  PTA_double nums = (yyvsp[0]._number_list);

  nurbs->set_num_u_knots(nums.size());
  for (int i = 0; i < (int)nums.size(); i++) {
    nurbs->set_u_knot(i, nums[i]);
  }
}
#line 4397 "built/tmp/parser.yxx.c"
    break;

  case 213:
#line 2545 "panda/src/egg/parser.yxx"
{
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  PTA_double nums = (yyvsp[0]._number_list);

  nurbs->set_num_v_knots(nums.size());
  for (int i = 0; i < (int)nums.size(); i++) {
    nurbs->set_v_knot(i, nums[i]);
  }
}
#line 4411 "built/tmp/parser.yxx.c"
    break;

  case 214:
#line 2565 "panda/src/egg/parser.yxx"
{
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  nurbs->_trims.push_back(EggNurbsSurface::Trim());
}
#line 4420 "built/tmp/parser.yxx.c"
    break;

  case 216:
#line 2581 "panda/src/egg/parser.yxx"
{
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  nassertr(!nurbs->_trims.empty(), 0);
  nurbs->_trims.back().push_back(EggNurbsSurface::Loop());
}
#line 4430 "built/tmp/parser.yxx.c"
    break;

  case 217:
#line 2587 "panda/src/egg/parser.yxx"
{
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  nassertr(!nurbs->_trims.empty(), 0);
  nassertr(!nurbs->_trims.back().empty(), 0);
  EggNurbsCurve *curve = DCAST(EggNurbsCurve, (yyvsp[0]._egg));
  nurbs->_trims.back().back().push_back(curve);
}
#line 4442 "built/tmp/parser.yxx.c"
    break;

  case 218:
#line 2606 "panda/src/egg/parser.yxx"
{
  EggNurbsCurve *nurbs = DCAST(EggNurbsCurve, egg_stack.back());
  int order = (int)(yyvsp[0]._number);
  nurbs->set_order(order);
}
#line 4452 "built/tmp/parser.yxx.c"
    break;

  case 219:
#line 2622 "panda/src/egg/parser.yxx"
{
  EggNurbsCurve *nurbs = DCAST(EggNurbsCurve, egg_stack.back());
  PTA_double nums = (yyvsp[0]._number_list);

  nurbs->set_num_knots(nums.size());
  for (int i = 0; i < (int)nums.size(); i++) {
    nurbs->set_knot(i, nums[i]);
  }
}
#line 4466 "built/tmp/parser.yxx.c"
    break;

  case 220:
#line 2643 "panda/src/egg/parser.yxx"
{
  EggTable *table = new EggTable((yyvsp[0]._string));
  table->set_table_type(EggTable::TT_table);
  egg_stack.push_back(table);
}
#line 4476 "built/tmp/parser.yxx.c"
    break;

  case 221:
#line 2649 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
  Thread::consider_yield();
}
#line 4486 "built/tmp/parser.yxx.c"
    break;

  case 222:
#line 2666 "panda/src/egg/parser.yxx"
{
  EggTable *table = new EggTable((yyvsp[0]._string));
  table->set_table_type(EggTable::TT_bundle);
  egg_stack.push_back(table);
}
#line 4496 "built/tmp/parser.yxx.c"
    break;

  case 223:
#line 2672 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 4505 "built/tmp/parser.yxx.c"
    break;

  case 225:
#line 2688 "panda/src/egg/parser.yxx"
{
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[0]._egg)));
}
#line 4513 "built/tmp/parser.yxx.c"
    break;

  case 226:
#line 2692 "panda/src/egg/parser.yxx"
{
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[0]._egg)));
}
#line 4521 "built/tmp/parser.yxx.c"
    break;

  case 227:
#line 2696 "panda/src/egg/parser.yxx"
{
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[0]._egg)));
}
#line 4529 "built/tmp/parser.yxx.c"
    break;

  case 228:
#line 2700 "panda/src/egg/parser.yxx"
{
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[0]._egg)));
}
#line 4537 "built/tmp/parser.yxx.c"
    break;

  case 229:
#line 2704 "panda/src/egg/parser.yxx"
{
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[0]._egg)));
}
#line 4545 "built/tmp/parser.yxx.c"
    break;

  case 230:
#line 2719 "panda/src/egg/parser.yxx"
{
  EggSAnimData *anim_data = new EggSAnimData((yyvsp[0]._string));
  egg_stack.push_back(anim_data);
}
#line 4554 "built/tmp/parser.yxx.c"
    break;

  case 231:
#line 2724 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 4563 "built/tmp/parser.yxx.c"
    break;

  case 233:
#line 2741 "panda/src/egg/parser.yxx"
{
  EggSAnimData *anim_data = DCAST(EggSAnimData, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);

  if (cmp_nocase_uh(name, "fps") == 0) {
    anim_data->set_fps(value);
  } else {
    eggyywarning("Unsupported S$Anim scalar: " + name);
  }
}
#line 4579 "built/tmp/parser.yxx.c"
    break;

  case 234:
#line 2753 "panda/src/egg/parser.yxx"
{
  DCAST(EggSAnimData, egg_stack.back())->set_data((yyvsp[-1]._number_list));
}
#line 4587 "built/tmp/parser.yxx.c"
    break;

  case 235:
#line 2767 "panda/src/egg/parser.yxx"
{
  EggXfmAnimData *anim_data = new EggXfmAnimData((yyvsp[0]._string));
  egg_stack.push_back(anim_data);
}
#line 4596 "built/tmp/parser.yxx.c"
    break;

  case 236:
#line 2772 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 4605 "built/tmp/parser.yxx.c"
    break;

  case 238:
#line 2789 "panda/src/egg/parser.yxx"
{
  EggXfmAnimData *anim_data = DCAST(EggXfmAnimData, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);
  string strval = (yyvsp[-1]._string);

  if (cmp_nocase_uh(name, "fps") == 0) {
    anim_data->set_fps(value);
  } else if (cmp_nocase_uh(name, "order") == 0) {
    anim_data->set_order(strval);
  } else if (cmp_nocase_uh(name, "contents") == 0) {
    anim_data->set_contents(strval);
  } else {
    eggyywarning("Unsupported Xfm$Anim scalar: " + name);
  }
}
#line 4626 "built/tmp/parser.yxx.c"
    break;

  case 239:
#line 2806 "panda/src/egg/parser.yxx"
{
  DCAST(EggXfmAnimData, egg_stack.back())->set_data((yyvsp[-1]._number_list));
}
#line 4634 "built/tmp/parser.yxx.c"
    break;

  case 240:
#line 2820 "panda/src/egg/parser.yxx"
{
  EggXfmSAnim *anim_group = new EggXfmSAnim((yyvsp[0]._string));
  egg_stack.push_back(anim_group);
}
#line 4643 "built/tmp/parser.yxx.c"
    break;

  case 241:
#line 2825 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 4652 "built/tmp/parser.yxx.c"
    break;

  case 243:
#line 2842 "panda/src/egg/parser.yxx"
{
  EggXfmSAnim *anim_group = DCAST(EggXfmSAnim, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);
  string strval = (yyvsp[-1]._string);

  if (cmp_nocase_uh(name, "fps") == 0) {
    anim_group->set_fps(value);
  } else if (cmp_nocase_uh(name, "order") == 0) {
    anim_group->set_order(strval);
  } else {
    eggyywarning("Unsupported Xfm$Anim_S$ scalar: " + name);
  }
}
#line 4671 "built/tmp/parser.yxx.c"
    break;

  case 244:
#line 2857 "panda/src/egg/parser.yxx"
{
  DCAST(EggXfmSAnim, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[0]._egg)));
}
#line 4679 "built/tmp/parser.yxx.c"
    break;

  case 245:
#line 2872 "panda/src/egg/parser.yxx"
{
  EggAnimPreload *anim_preload = new EggAnimPreload((yyvsp[0]._string));
  egg_stack.push_back(anim_preload);
}
#line 4688 "built/tmp/parser.yxx.c"
    break;

  case 246:
#line 2877 "panda/src/egg/parser.yxx"
{
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
#line 4697 "built/tmp/parser.yxx.c"
    break;

  case 248:
#line 2894 "panda/src/egg/parser.yxx"
{
  EggAnimPreload *anim_preload = DCAST(EggAnimPreload, egg_stack.back());
  string name = (yyvsp[-3]._string);
  double value = (yyvsp[-1]._number);

  if (cmp_nocase_uh(name, "fps") == 0) {
    anim_preload->set_fps(value);
  } else if (cmp_nocase_uh(name, "frames") == 0) {
    anim_preload->set_num_frames((int)value);
  } else {
    eggyywarning("Unsupported AnimPreload scalar: " + name);
  }
}
#line 4715 "built/tmp/parser.yxx.c"
    break;

  case 249:
#line 2918 "panda/src/egg/parser.yxx"
{
  (yyval._number_list) = PTA_double::empty_array(0);
}
#line 4723 "built/tmp/parser.yxx.c"
    break;

  case 250:
#line 2922 "panda/src/egg/parser.yxx"
{
  (yyval._number_list).push_back((double)(yyvsp[0]._number));
}
#line 4731 "built/tmp/parser.yxx.c"
    break;

  case 251:
#line 2936 "panda/src/egg/parser.yxx"
{
  (yyval._number_list) = PTA_double::empty_array(0);
}
#line 4739 "built/tmp/parser.yxx.c"
    break;

  case 252:
#line 2940 "panda/src/egg/parser.yxx"
{
  (yyval._number_list).push_back((yyvsp[0]._number));
}
#line 4747 "built/tmp/parser.yxx.c"
    break;

  case 253:
#line 2954 "panda/src/egg/parser.yxx"
{
  string name = (yyvsp[0]._string);
  Textures::iterator vpi = textures.find(name);
  if (vpi == textures.end()) {
    eggyyerror("Unknown texture " + name);
    (yyval._egg) = PT(EggObject)();
  } else {
    (yyval._egg) = (*vpi).second;
  }
}
#line 4762 "built/tmp/parser.yxx.c"
    break;

  case 254:
#line 2975 "panda/src/egg/parser.yxx"
{
  string name = (yyvsp[0]._string);
  Materials::iterator vpi = materials.find(name);
  if (vpi == materials.end()) {
    eggyyerror("Unknown material " + name);
    (yyval._egg) = PT(EggObject)();
  } else {
    (yyval._egg) = (*vpi).second;
  }
}
#line 4777 "built/tmp/parser.yxx.c"
    break;

  case 255:
#line 2996 "panda/src/egg/parser.yxx"
{
  string name = (yyvsp[0]._string);
  VertexPools::iterator vpi = vertex_pools.find(name);
  if (vpi == vertex_pools.end()) {
    // This will become a forward reference.
    EggVertexPool *pool = new EggVertexPool(name);
    // The egg syntax starts counting at 1 by convention.
    pool->set_highest_index(0);
    vertex_pools[name] = pool;
    (yyval._egg) = pool;
  } else {
    (yyval._egg) = (*vpi).second;
  }
}
#line 4796 "built/tmp/parser.yxx.c"
    break;

  case 256:
#line 3021 "panda/src/egg/parser.yxx"
{
  string name = (yyvsp[0]._string);
  Groups::iterator vpi = groups.find(name);
  if (vpi == groups.end()) {
    eggyyerror("Unknown group " + name);
    (yyval._egg) = PT(EggObject)();
  } else {
    (yyval._egg) = (*vpi).second;
  }
}
#line 4811 "built/tmp/parser.yxx.c"
    break;

  case 257:
#line 3042 "panda/src/egg/parser.yxx"
{
  eggyyerror("Name required.");
  (yyval._string) = "";
}
#line 4820 "built/tmp/parser.yxx.c"
    break;

  case 260:
#line 3071 "panda/src/egg/parser.yxx"
{
  eggyyerror("String required.");
  (yyval._string) = "";
}
#line 4829 "built/tmp/parser.yxx.c"
    break;

  case 262:
#line 3087 "panda/src/egg/parser.yxx"
{
  (yyval._string) = "";
}
#line 4837 "built/tmp/parser.yxx.c"
    break;

  case 264:
#line 3105 "panda/src/egg/parser.yxx"
{
  (yyval._string) = (yyvsp[0]._string);
}
#line 4845 "built/tmp/parser.yxx.c"
    break;

  case 265:
#line 3109 "panda/src/egg/parser.yxx"
{
  (yyval._string) = (yyvsp[0]._string);
}
#line 4853 "built/tmp/parser.yxx.c"
    break;

  case 267:
#line 3126 "panda/src/egg/parser.yxx"
{
  (yyval._string) = "";
}
#line 4861 "built/tmp/parser.yxx.c"
    break;

  case 268:
#line 3130 "panda/src/egg/parser.yxx"
{
  (yyval._string) = (yyvsp[0]._string);
}
#line 4869 "built/tmp/parser.yxx.c"
    break;

  case 269:
#line 3146 "panda/src/egg/parser.yxx"
{
  (yyval._string) = (yyvsp[0]._string);
}
#line 4877 "built/tmp/parser.yxx.c"
    break;

  case 270:
#line 3150 "panda/src/egg/parser.yxx"
{
  (yyval._string) = (yyvsp[-1]._string) + "\n" + (yyvsp[0]._string);
}
#line 4885 "built/tmp/parser.yxx.c"
    break;

  case 272:
#line 3165 "panda/src/egg/parser.yxx"
{
  (yyval._number) = (yyvsp[0]._ulong);
}
#line 4893 "built/tmp/parser.yxx.c"
    break;

  case 273:
#line 3180 "panda/src/egg/parser.yxx"
{
  (yyval._number) = (yyvsp[0]._number);
  (yyval._ulong) = (unsigned long)(yyvsp[0]._number);
  (yyval._string) = (yyvsp[0]._string);
}
#line 4903 "built/tmp/parser.yxx.c"
    break;

  case 274:
#line 3186 "panda/src/egg/parser.yxx"
{
  (yyval._number) = (yyvsp[0]._ulong);
  (yyval._ulong) = (yyvsp[0]._ulong);
  (yyval._string) = (yyvsp[0]._string);
}
#line 4913 "built/tmp/parser.yxx.c"
    break;

  case 275:
#line 3192 "panda/src/egg/parser.yxx"
{
  (yyval._number) = 0.0;
  (yyval._ulong) = 0;
  (yyval._string) = (yyvsp[0]._string);
}
#line 4923 "built/tmp/parser.yxx.c"
    break;

  case 276:
#line 3209 "panda/src/egg/parser.yxx"
{
  int i = (int)(yyvsp[0]._number);
  if ((double)i != (yyvsp[0]._number)) {
    eggyywarning("Integer expected.");
    (yyval._number) = (double)i;
  }
}
#line 4935 "built/tmp/parser.yxx.c"
    break;

  case 277:
#line 3217 "panda/src/egg/parser.yxx"
{
  (yyval._number) = (yyvsp[0]._ulong);
}
#line 4943 "built/tmp/parser.yxx.c"
    break;


#line 4947 "built/tmp/parser.yxx.c"

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