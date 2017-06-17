/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 1 "oiler_parser.lemon"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "globals.h"

#include "oiler_parser.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#define debug_print(...) do { if (DEBUG) fprintf(stdout, ##__VA_ARGS__); } while (0)
#define warning_print(...) do { fprintf(stdout, ##__VA_ARGS__); } while (0)	

#define OBJECT_NONE 0
#define OBJECT_OS 1
#define OBJECT_TASK 2
#define OBJECT_RESOURCE 3

void InitializeResource( Resource* a_resource, const char a_name[] ) {
	strcpy( a_resource->name, a_name );
	a_resource->type = RESOURCE_TYPE_UNDEFINED; 
	a_resource->priority = 0;	
}


int g_current_object = OBJECT_NONE;
Resource* g_current_resource = NULL;
#line 39 "oiler_parser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 35
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE  YYSTYPE 
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  double yy8;
  Object yy20;
  LiteralValue yy43;
  char* yy49;
  int yy60;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  OS* os ;
#define ParseARG_PDECL , OS* os 
#define ParseARG_FETCH  OS* os  = yypParser->os 
#define ParseARG_STORE yypParser->os  = os 
#define YYNSTATE 52
#define YYNRULE 31
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (64)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    40,   42,   49,   37,   36,   35,    6,   34,   27,   52,
 /*    10 */    32,   43,   41,   39,   38,   31,   45,   12,   17,   20,
 /*    20 */    48,    5,    9,   11,   33,    1,   35,   30,   35,   30,
 /*    30 */    24,   51,   22,   51,   50,   21,   51,   47,   18,   51,
 /*    40 */    23,   51,   16,   46,   49,   10,   84,   14,   44,    7,
 /*    50 */    30,   28,    3,    2,    4,   13,   25,   26,    8,   35,
 /*    60 */    15,   49,   29,   19,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    19,   20,    7,    8,    9,   10,   17,   12,   19,    0,
 /*    10 */    20,   30,   31,   32,   33,   25,   26,   27,    5,   29,
 /*    20 */    22,   23,    6,   25,    6,    2,   10,   11,   10,   11,
 /*    30 */    18,   19,   18,   19,    3,   18,   19,    3,   18,   19,
 /*    40 */    18,   19,    5,    3,    7,    6,   14,   15,    3,    2,
 /*    50 */    11,    3,   24,   24,   21,    4,   20,   16,   28,   10,
 /*    60 */     5,    7,   20,    1,
};
#define YY_SHIFT_USE_DFLT (-6)
#define YY_SHIFT_COUNT (26)
#define YY_SHIFT_MIN   (-5)
#define YY_SHIFT_MAX   (62)
static const signed char yy_shift_ofst[] = {
 /*     0 */    62,   -5,   18,   16,   39,   37,   54,   54,   54,   54,
 /*    10 */    54,   49,   55,   49,   51,   -6,   -6,   -6,   48,   47,
 /*    20 */    23,   45,   40,   34,   31,   13,    9,
};
#define YY_REDUCE_USE_DFLT (-20)
#define YY_REDUCE_COUNT (17)
#define YY_REDUCE_MIN   (-19)
#define YY_REDUCE_MAX   (42)
static const signed char yy_reduce_ofst[] = {
 /*     0 */    32,  -19,  -10,  -10,   -2,   22,   20,  -11,   17,   14,
 /*    10 */    12,   42,   30,   36,   41,   29,   28,   33,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    83,   83,   83,   83,   83,   55,   55,   83,   55,   55,
 /*    10 */    55,   83,   68,   83,   57,   64,   64,   60,   83,   83,
 /*    20 */    83,   83,   83,   83,   83,   83,   83,   54,   53,   63,
 /*    30 */    81,   71,   70,   69,   82,   80,   79,   78,   76,   75,
 /*    40 */    74,   73,   72,   67,   66,   65,   62,   61,   59,   77,
 /*    50 */    58,   56,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "OIL_VERSION",   "EQUAL",         "SEMICOLON",   
  "CPU",           "OPEN_BRACKET",  "CLOSE_BRACKET",  "LITERAL_STRING",
  "LITERAL_INTEGER",  "LITERAL_DECIMAL",  "LITERAL_NAME",  "LITERAL_OBJECT",
  "LITERAL_BOOLEAN",  "error",         "file",          "oil_version", 
  "application",   "version",       "description",   "string",      
  "name",          "object_list",   "object_definition",  "object_name", 
  "parameter_list",  "object",        "parameter",     "parameter_main",
  "parameter_sublist",  "attribute_name",  "attribute_value",  "boolean",     
  "integer",       "decimal",     
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "file ::= oil_version application",
 /*   1 */ "oil_version ::= OIL_VERSION EQUAL version description SEMICOLON",
 /*   2 */ "version ::= string",
 /*   3 */ "description ::=",
 /*   4 */ "description ::= string",
 /*   5 */ "application ::=",
 /*   6 */ "application ::= CPU name OPEN_BRACKET object_list CLOSE_BRACKET description SEMICOLON",
 /*   7 */ "object_list ::= object_list object_definition",
 /*   8 */ "object_list ::=",
 /*   9 */ "object_definition ::= object_name description SEMICOLON",
 /*  10 */ "object_definition ::= object_name OPEN_BRACKET parameter_list CLOSE_BRACKET description SEMICOLON",
 /*  11 */ "object_name ::= object name",
 /*  12 */ "parameter_list ::=",
 /*  13 */ "parameter_list ::= parameter_list parameter",
 /*  14 */ "parameter ::= parameter_main parameter_sublist description SEMICOLON",
 /*  15 */ "parameter_main ::= attribute_name EQUAL attribute_value",
 /*  16 */ "parameter_sublist ::=",
 /*  17 */ "parameter_sublist ::= OPEN_BRACKET parameter_list CLOSE_BRACKET",
 /*  18 */ "attribute_name ::= name",
 /*  19 */ "attribute_name ::= object",
 /*  20 */ "attribute_value ::= name",
 /*  21 */ "attribute_value ::= boolean",
 /*  22 */ "attribute_value ::= string",
 /*  23 */ "attribute_value ::= integer",
 /*  24 */ "attribute_value ::= decimal",
 /*  25 */ "string ::= LITERAL_STRING",
 /*  26 */ "integer ::= LITERAL_INTEGER",
 /*  27 */ "decimal ::= LITERAL_DECIMAL",
 /*  28 */ "name ::= LITERAL_NAME",
 /*  29 */ "object ::= LITERAL_OBJECT",
 /*  30 */ "boolean ::= LITERAL_BOOLEAN",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 15: /* oil_version */
{
#line 60 "oiler_parser.lemon"
 debug_print("destructor oil_version\n"); 
#line 443 "oiler_parser.c"
}
      break;
    case 16: /* application */
{
#line 86 "oiler_parser.lemon"
 debug_print("destructor application\n"); 
#line 450 "oiler_parser.c"
}
      break;
    case 17: /* version */
{
#line 66 "oiler_parser.lemon"
 debug_print( "destructor version: %s\n", (yypminor->yy49) ); 
#line 457 "oiler_parser.c"
}
      break;
    case 18: /* description */
{
#line 73 "oiler_parser.lemon"
 debug_print( "destructor description: %s\n", (yypminor->yy49) ); 
#line 464 "oiler_parser.c"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 14, 2 },
  { 15, 5 },
  { 17, 1 },
  { 18, 0 },
  { 18, 1 },
  { 16, 0 },
  { 16, 7 },
  { 21, 2 },
  { 21, 0 },
  { 22, 3 },
  { 22, 6 },
  { 23, 2 },
  { 24, 0 },
  { 24, 2 },
  { 26, 4 },
  { 27, 3 },
  { 28, 0 },
  { 28, 3 },
  { 29, 1 },
  { 29, 1 },
  { 30, 1 },
  { 30, 1 },
  { 30, 1 },
  { 30, 1 },
  { 30, 1 },
  { 19, 1 },
  { 32, 1 },
  { 33, 1 },
  { 20, 1 },
  { 25, 1 },
  { 31, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0: /* file ::= oil_version application */
#line 54 "oiler_parser.lemon"
{
  yy_destructor(yypParser,15,&yymsp[-1].minor);
  yy_destructor(yypParser,16,&yymsp[0].minor);
}
#line 793 "oiler_parser.c"
        break;
      case 1: /* oil_version ::= OIL_VERSION EQUAL version description SEMICOLON */
#line 61 "oiler_parser.lemon"
{
	debug_print( "OIL_VERSION = %s %s\n", yymsp[-2].minor.yy49, yymsp[-1].minor.yy49 ? yymsp[-1].minor.yy49 : "" );
}
#line 800 "oiler_parser.c"
        break;
      case 2: /* version ::= string */
#line 67 "oiler_parser.lemon"
{
	yygotominor.yy49 = yymsp[0].minor.yy49;
    debug_print( "version: %s\n", yygotominor.yy49 );
}
#line 808 "oiler_parser.c"
        break;
      case 3: /* description ::= */
#line 74 "oiler_parser.lemon"
{
    debug_print( "description: empty\n" );
}
#line 815 "oiler_parser.c"
        break;
      case 4: /* description ::= string */
#line 77 "oiler_parser.lemon"
{
	yygotominor.yy49 = yymsp[0].minor.yy49;
    debug_print( "description: %s\n", yygotominor.yy49 );
}
#line 823 "oiler_parser.c"
        break;
      case 6: /* application ::= CPU name OPEN_BRACKET object_list CLOSE_BRACKET description SEMICOLON */
#line 88 "oiler_parser.lemon"
{
	debug_print( "application OK: name=%s description=%s\n", yymsp[-5].minor.yy49, yymsp[-1].minor.yy49 );
}
#line 830 "oiler_parser.c"
        break;
      case 7: /* object_list ::= object_list object_definition */
#line 92 "oiler_parser.lemon"
{ debug_print( "object_list: object_list object_definition\n" ); }
#line 835 "oiler_parser.c"
        break;
      case 8: /* object_list ::= */
#line 93 "oiler_parser.lemon"
{ debug_print( "object_list: empty\n" ); }
#line 840 "oiler_parser.c"
        break;
      case 9: /* object_definition ::= object_name description SEMICOLON */
#line 95 "oiler_parser.lemon"
{
	debug_print( "object_definition(1): %s=%s\n", yymsp[-2].minor.yy20.type, yymsp[-2].minor.yy20.name );
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 848 "oiler_parser.c"
        break;
      case 10: /* object_definition ::= object_name OPEN_BRACKET parameter_list CLOSE_BRACKET description SEMICOLON */
#line 98 "oiler_parser.lemon"
{
	debug_print( "object_definition(2): %s=%s\n", yymsp[-5].minor.yy20.type, yymsp[-5].minor.yy20.name );
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 856 "oiler_parser.c"
        break;
      case 11: /* object_name ::= object name */
#line 103 "oiler_parser.lemon"
{
	yygotominor.yy20.type = yymsp[-1].minor.yy49;
	yygotominor.yy20.name = yymsp[0].minor.yy49;
	debug_print( "object_name: %s=%s\n", yymsp[-1].minor.yy49, yymsp[0].minor.yy49 );
	if( strcmp(yymsp[-1].minor.yy49, "OS") == 0 ) {
		g_current_object = OBJECT_OS;
	} else if( strcmp(yymsp[-1].minor.yy49, "TASK") == 0 ) {
		g_current_object = OBJECT_TASK;
		Task* l_task = &os->tasks[os->task_count];
		os->task_count++;
		strcpy( l_task->name, yymsp[0].minor.yy49 );
	} else if( strcmp(yymsp[-1].minor.yy49, "RESOURCE") == 0 ) {
		g_current_object = OBJECT_RESOURCE;
		Resource* l_resource = NULL;
		// Check if resource was already created
		int i;
		for( i = 0; i < os->resource_count; i++ ) {
			if( strcmp( os->resources[i].name, yymsp[0].minor.yy49 ) == 0 ) {
				l_resource = &os->resources[i];
				break;
			}
		}
		// Create a new resource, in case it doesn't exist yet.
		if( l_resource == NULL ) {
			l_resource = &os->resources[os->resource_count];
			os->resource_count++;
			InitializeResource( l_resource, yymsp[0].minor.yy49 );		
		}
		g_current_resource = l_resource;
	}
}
#line 891 "oiler_parser.c"
        break;
      case 14: /* parameter ::= parameter_main parameter_sublist description SEMICOLON */
#line 138 "oiler_parser.lemon"
{
  yy_destructor(yypParser,18,&yymsp[-1].minor);
}
#line 898 "oiler_parser.c"
        break;
      case 15: /* parameter_main ::= attribute_name EQUAL attribute_value */
#line 139 "oiler_parser.lemon"
{
	if( yymsp[0].minor.yy43.type == LITERAL_INTEGER ) {
		debug_print( "parameter: attribute[%s] = value[%i];\n", yymsp[-2].minor.yy49, yymsp[0].minor.yy43.value.ival );
	} else if( yymsp[0].minor.yy43.type == LITERAL_DECIMAL ) {
		debug_print( "parameter: attribute[%s] = value[%f];\n", yymsp[-2].minor.yy49, yymsp[0].minor.yy43.value.dval );
	} else {
		debug_print( "parameter: attribute[%s] = value[%s];\n", yymsp[-2].minor.yy49, yymsp[0].minor.yy43.value.sval );
	}
	if( g_current_object == OBJECT_TASK ) {
		Task* l_task = &os->tasks[os->task_count-1];
		if( strcmp( yymsp[-2].minor.yy49, "PRIORITY" ) == 0 ) {
			l_task->priority = yymsp[0].minor.yy43.value.ival;
		} else if( strcmp( yymsp[-2].minor.yy49, "SCHEDULE" ) == 0 ) {
			l_task->schedule = strcmp( yymsp[0].minor.yy43.value.sval, "FULL" ) == 0 ? 1 : 0;
		} else if( strcmp( yymsp[-2].minor.yy49, "ACTIVATION" ) == 0 ) {
			l_task->activation = yymsp[0].minor.yy43.value.ival;
		} else if( strcmp( yymsp[-2].minor.yy49, "AUTOSTART" ) == 0 ) {
			l_task->autostart = strcmp( yymsp[0].minor.yy43.value.sval, "TRUE" ) == 0 ? 1 : 0;
			// TODO: Implement this
		} else if( strcmp( yymsp[-2].minor.yy49, "RESOURCE" ) == 0 ) {
			// Setting up or finding the resource
			Resource* l_resource = NULL;
			int i;
			for( i = 0; i < os->resource_count; i++ ) {
				if( strcmp( os->resources[i].name, yymsp[0].minor.yy43.value.sval ) == 0 ) {
					l_resource = &os->resources[i];
					break;
				}
			}
			if( l_resource == NULL ) {
				l_resource = &os->resources[os->resource_count];				
				os->resource_count++;
				InitializeResource( l_resource, yymsp[0].minor.yy43.value.sval );
			}
			// Linking the resource to the task
			l_task->resources[l_task->resource_count] = l_resource;
			l_task->resource_count++;
		} else {
			warning_print( "WARNING: TASK PROPERTY[%s] NOT SUPPORTED!!!\n", yymsp[-2].minor.yy49 );
		}
	} else if( g_current_object == OBJECT_RESOURCE ) {		
		if( g_current_resource == NULL ) {
			warning_print( "WARNING: RESOURCE NOT FOUND!!!\n" );
		}
		if( strcmp( yymsp[-2].minor.yy49, "RESOURCEPROPERTY" ) == 0 ) {
			if( strcmp( yymsp[0].minor.yy43.value.sval, "STANDARD" ) == 0 ) {
				g_current_resource->type = RESOURCE_TYPE_STANDARD;
			} else if( strcmp( yymsp[0].minor.yy43.value.sval, "LINKED" ) == 0 ) {
				g_current_resource->type = RESOURCE_TYPE_LINKED;				
			} else if( strcmp( yymsp[0].minor.yy43.value.sval, "INTERNAL" ) == 0 ) {
				g_current_resource->type = RESOURCE_TYPE_INTERNAL;
			} else {
				warning_print( "WARNING: RESOURCE->RESOURCEPROPERTY = %s NOT SUPPORTED!!!\n", yymsp[0].minor.yy43.value.sval );
			}			
		} else {
			warning_print( "WARNING: RESOURCE PROPERTY[%s] NOT SUPPORTED!!!\n", yymsp[-2].minor.yy49 );
		}
	}
}
#line 961 "oiler_parser.c"
        break;
      case 16: /* parameter_sublist ::= */
#line 198 "oiler_parser.lemon"
{ debug_print( "FOO\n" ); }
#line 966 "oiler_parser.c"
        break;
      case 17: /* parameter_sublist ::= OPEN_BRACKET parameter_list CLOSE_BRACKET */
#line 199 "oiler_parser.lemon"
{ debug_print( "BAR\n" ); }
#line 971 "oiler_parser.c"
        break;
      case 18: /* attribute_name ::= name */
      case 19: /* attribute_name ::= object */ yytestcase(yyruleno==19);
#line 202 "oiler_parser.lemon"
{ yygotominor.yy49 = yymsp[0].minor.yy49; }
#line 977 "oiler_parser.c"
        break;
      case 20: /* attribute_value ::= name */
#line 206 "oiler_parser.lemon"
{ yygotominor.yy43.value.sval = yymsp[0].minor.yy49; yygotominor.yy43.type = LITERAL_NAME; }
#line 982 "oiler_parser.c"
        break;
      case 21: /* attribute_value ::= boolean */
#line 207 "oiler_parser.lemon"
{ yygotominor.yy43.value.sval = yymsp[0].minor.yy49; yygotominor.yy43.type = LITERAL_BOOLEAN; }
#line 987 "oiler_parser.c"
        break;
      case 22: /* attribute_value ::= string */
#line 208 "oiler_parser.lemon"
{ yygotominor.yy43.value.sval = yymsp[0].minor.yy49; yygotominor.yy43.type = LITERAL_STRING; }
#line 992 "oiler_parser.c"
        break;
      case 23: /* attribute_value ::= integer */
#line 209 "oiler_parser.lemon"
{ yygotominor.yy43.value.ival = yymsp[0].minor.yy60; yygotominor.yy43.type = LITERAL_INTEGER; }
#line 997 "oiler_parser.c"
        break;
      case 24: /* attribute_value ::= decimal */
#line 210 "oiler_parser.lemon"
{ yygotominor.yy43.value.dval = yymsp[0].minor.yy8; yygotominor.yy43.type = LITERAL_DECIMAL; }
#line 1002 "oiler_parser.c"
        break;
      case 25: /* string ::= LITERAL_STRING */
#line 217 "oiler_parser.lemon"
{
    yygotominor.yy49 = yymsp[0].minor.yy0.sval;
}
#line 1009 "oiler_parser.c"
        break;
      case 26: /* integer ::= LITERAL_INTEGER */
#line 222 "oiler_parser.lemon"
{
    yygotominor.yy60 = yymsp[0].minor.yy0.ival;
}
#line 1016 "oiler_parser.c"
        break;
      case 27: /* decimal ::= LITERAL_DECIMAL */
#line 227 "oiler_parser.lemon"
{
    yygotominor.yy8 = yymsp[0].minor.yy0.dval;
}
#line 1023 "oiler_parser.c"
        break;
      case 28: /* name ::= LITERAL_NAME */
#line 232 "oiler_parser.lemon"
{	
	yygotominor.yy49 = yymsp[0].minor.yy0.sval;
}
#line 1030 "oiler_parser.c"
        break;
      case 29: /* object ::= LITERAL_OBJECT */
      case 30: /* boolean ::= LITERAL_BOOLEAN */ yytestcase(yyruleno==30);
#line 237 "oiler_parser.lemon"
{
	yygotominor.yy49 = yymsp[0].minor.yy0.sval;
}
#line 1038 "oiler_parser.c"
        break;
      default:
      /* (5) application ::= */ yytestcase(yyruleno==5);
      /* (12) parameter_list ::= */ yytestcase(yyruleno==12);
      /* (13) parameter_list ::= parameter_list parameter */ yytestcase(yyruleno==13);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 36 "oiler_parser.lemon"

    fprintf(stderr, "Error parsing command\n");
	int n = sizeof( yyTokenName ) / sizeof( yyTokenName[0] );
	int i;
	for( i = 0; i < n; ++i ) {
		int a = yy_find_shift_action( yypParser, (YYCODETYPE)i );
		if( a < YYNSTATE + YYNRULE ) {
			printf( "\tpossible token: %s\n", yyTokenName[i] );
		}
	}
#line 1114 "oiler_parser.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
