%{
	// yylval definition
	#include "globals.h"
    #include "oiler_parser.h"

    #include <string.h>
    #include <stdlib.h>
%}

%option noyywrap

/* Double Quoted State */
%x STATE_DOUBLE_QUOTED

%%

=														{ return EQUAL; }
;														{ return SEMICOLON; }
\{														{ return OPEN_BRACKET; }
\}														{ return CLOSE_BRACKET; }

OIL_VERSION												{ return OIL_VERSION; }

CPU														{ return CPU; }
(OS|TASK|COUNTER|ALARM|RESOURCE|EVENT|ISR|MESSAGE|COM|NM|APPMODE|IPDU) {
	yylval.sval = strdup(yytext);
	return LITERAL_OBJECT;
}

TRUE|FALSE {
	yylval.sval = strdup(yytext);
	return LITERAL_BOOLEAN;
}

[1-9][0-9]*	{
	yylval.ival = atoi(yytext);                                                 
	return LITERAL_INTEGER; 
}

[0-9]+\.[0-9]+ {
	yylval.dval = atof(yytext);
	return LITERAL_DECIMAL;
}

[_0-9a-zA-Z]+ {
	yylval.sval = strdup(yytext);
	return LITERAL_NAME;
}

[ \t\r\n]													{} // Whitespace


["]															{ BEGIN(STATE_DOUBLE_QUOTED); }
<STATE_DOUBLE_QUOTED>[^"]+ {
	yylval.sval = strdup( yytext );
}
<STATE_DOUBLE_QUOTED>["]									{ BEGIN(INITIAL); return LITERAL_STRING; }
<STATE_DOUBLE_QUOTED><<EOF>>								{ return -1; }

.															{} // Ignore everything else

%%


