%{
#define YY_NO_INPUT
#include <stdlib.h>
#include <string.h>
#include "envsh_structs.h"
#include "y.tab.h"
void yyerror(char * s);
%}

%option nounput

alpha 		[A-Za-z]

alphaAug	(_|/|-|.|{alpha})

digit		[0-9]

%%

[ \t]+		; /* Ignore whitespace */

"\n"		return NEWLINE; 

"prompt"	{ return PROMPT; }

"%".*		; /* Ignore comments */

"setenv"	{ return SETENV; }
"unsetenv"	{ return UNSETENV; }
"listenv"	{ return LISTENV; }
"setdir"	{ return SETDIR; }
"bye"		{ return BYE; }
"<"		{ return IOIN; }
">"		{ return IOOUT; }
\"(\\.|[^\\"])*\"  {	
			yylval.str = strdup(yytext);
			/* Strip the quotes from the string literal */
			/* Start the string beyond the first quote */
			yylval.str++;
			/* Replace the ending quote with null terminator */
			yylval.str[strlen(yylval.str)-1] = '\0';
			return STRING; 
		   }

[^><% \t\n\"]+		{
				yylval.word = strdup(yytext);
				return WORD;
			}

%%
