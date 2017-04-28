#ifndef YYSTYPE
typedef union {
	int ival;
	double dval;
	char* sval;	
//  struct symtab *symp;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

/* extern YYSTYPE yylval; */
YYSTYPE yylval;
