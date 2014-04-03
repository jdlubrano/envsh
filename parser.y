%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
/*
#include "envTable.h"
*/
#include "envsh_structs.h" 
#include "envsh.h"

extern void builtIn(int cmd, char * str, char * varName);
extern void userCmd(ARG_LIST * argList, char * inputRedirect, char * outputRedirect);
int yylex(void);
void yyerror(char * s);
void printArgList(ARG_LIST * argList);
ARG_LIST * makeArgList(char * arg, ARG_LIST * wordList);
int yydebug = 1;
/* static WORD_LIST * currentWordList = NULL; */

%}

/* Define the union for yylval */
%union {
	char * str;	/* string literals */
	char * word;	/* words */
	ARG_LIST * argList;
};

%token PROMPT SETENV UNSETENV LISTENV SETDIR BYE IOIN IOOUT NEWLINE
%token <str> STRING
%token <word> WORD
%type <argList> arg_list user_command
%type <str> command

%%

session:
	   	lines			{ /* Do nothing */ }	
	      | /* NULL */		{ /* Do nothing */ }
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
	      | SETENV WORD STRING	{ builtIn(SETENV, $3, $2); }
	      |	UNSETENV WORD		{ builtIn(UNSETENV, NULL, $2); }
	      |	LISTENV			{ builtIn(LISTENV, NULL, NULL); }
	      |	SETDIR WORD		{ builtIn(SETDIR, $2, NULL); }
	      |	BYE			{ builtIn(BYE, NULL, NULL); }
	      | user_command		{ 
						userCmd($1, NULL, NULL);
						free($1);
					}
	      | user_command IOIN WORD  	{
							userCmd($1, $3, NULL);
							free($1);
						}
	      | user_command IOOUT WORD		{
							userCmd($1, NULL, $3);
							free($1);
						}
	      | user_command IOIN WORD IOOUT WORD	{
								userCmd($1, $3, $5);
								free($1);
							}
	      ; 	

user_command:
	        WORD arg_list		{ 
						/*ARG_LIST * argList = makeArgList($1, $2);
						userCmd(argList); 
						free(argList);*/
						$$ = makeArgList($1, $2);
					}
	      | WORD			{ 
						/*ARG_LIST * argList = makeArgList($1, $2);
						userCmd(makeArgList($1, NULL)); 
						free(argList);*/
						$$ = makeArgList($1, NULL);
					}
	      ;

arg_list:
		WORD			{ $$ = makeArgList($1, NULL); }
	      |	STRING			{ $$ = makeArgList($1, NULL); }
	      | WORD arg_list		{ $$ = makeArgList($1, $2); }	
	      | STRING arg_list		{ $$ = makeArgList($1, $2); }
	      ;

%%

ARG_LIST * makeArgList(char * arg, ARG_LIST * argList)
{
	/* Add the current word or string to the front of the arg_list. */
	/* The parser actually reads the last argument first. */
	ARG_LIST * newEntry = malloc(sizeof(ARG_LIST));
	strncpy(newEntry->word, arg, sizeof(newEntry->word));
	newEntry->next = argList;
	argList = newEntry;
	return argList;
}

void printArgList(ARG_LIST * argList)
{
	ARG_LIST * currentArg = argList;
	printf("ARG_LIST:\n");
	while(currentArg != NULL)
	{	
		printf("%s\n", currentArg->word);	
		currentArg = currentArg->next;
	}
}

void yyerror(char * s)
{
	printf("Syntax error: %s\n", s);
}
