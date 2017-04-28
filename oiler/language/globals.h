#ifndef LANGUAGE_GLOBALS_H
#define LANGUAGE_GLOBALS_H

#ifndef YYSTYPE
typedef union {
	int ival;
	char* sval;
	double dval;  
//  struct symtab *symp;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

/* extern YYSTYPE yylval; */
YYSTYPE yylval;

typedef struct {
	char* type;
	char* name;
} Object;

#endif//LANGUAGE_GLOBALS_H