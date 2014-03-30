%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/*
#include "envTable.h"
*/
#include "envsh_structs.h" 
#include "envsh.h"

extern void builtIn(int cmd, char * str, char * varName);
extern void userCmd(WORD_LIST * wordList, STRING_LIST * stringList);
int yylex(void);
void yyerror(char * s);
WORD_LIST * makeWordList(char * word, WORD_LIST * wordList);
STRING_LIST * makeStringList(char * word, STRING_LIST * stringList);

%}

/* Define the union for yylval */
%union {
	char * str;	/* string literals */
	char * varName; /* environment variable names */
	char * word;	/* words */
	WORD_LIST * wordList;
	STRING_LIST * stringList;
};

%token PROMPT SETENV UNSETENV LISTENV SETDIR BYE IOIN IOOUT NEWLINE
%token <str> STRING
%token <varName> VAR_NAME
%token <word> WORD
%type <wordList> word_list
%type <stringList> string_list 
%type <str> command

%%

session:
	   	lines			{ return 0; }
	      | /* NULL */	
	      ;

lines:
		line			{ /* Do nothing */ }
	      |	lines line		{ /* Do nothing */ }
	      ;

line:
		command NEWLINE		{ printCmdPrompt(); }
	      | NEWLINE			{ printCmdPrompt(); }
	      ;

command:
		PROMPT STRING		{ builtIn(PROMPT, $2, NULL); }
	      | SETENV VAR_NAME STRING	{ builtIn(SETENV, $3, $2); }
	      |	UNSETENV VAR_NAME	{ builtIn(UNSETENV, NULL, $2); }
	      |	LISTENV			{ builtIn(LISTENV, NULL, NULL); }
	      |	SETDIR WORD		{ builtIn(SETDIR, $2, NULL); }
	      |	BYE			{ builtIn(BYE, NULL, NULL); }
	      |	word_list string_list	{ userCmd($1, $2); }
	      ;

word_list:
		WORD			{ $$ = makeWordList($1, NULL); }
	      |	word_list WORD		{ $$ = makeWordList($2, $1); }
	      ;

string_list:
		STRING			{ $$ = makeStringList($1, NULL); }
	      | string_list STRING	{ $$ = makeStringList($2, $1); }
	      ;

%%

WORD_LIST * makeWordList(char * word, WORD_LIST * wordList)
{
	/* create new word and add it to the end of the list */
	return NULL;
}

STRING_LIST * makeStringList(char * str, STRING_LIST * stringList)
{
	return NULL;
}

void yyerror(char * s)
{
	printf("Syntax error: %s\n", s);
}
