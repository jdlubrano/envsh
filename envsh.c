#include <stdlib.h>
#include <stdio.h>
#include "envsh_structs.h"
#include "envsh.h"
#include "y.tab.h"

static char * cmdPrefix;

void initCmdPrefix()
{
	cmdPrefix = "envsh";
}

void printCmdPrompt()
{
	printf("%s> ", cmdPrefix);
}

void builtIn(int cmd, char * str, char * varName)
{
	switch(cmd) {
		case PROMPT:
			cmdPrefix = str;
			break;
		case SETENV:
			break;
		case UNSETENV:
			break;
		case LISTENV:
			break;
		case SETDIR:
			break;
		case BYE:
			exit(0);
			break;
		case NEWLINE:
			break;
		default:
			printf("Unknown built-in command.\n");
	}
}

void userCmd(WORD_LIST * wordList, STRING_LIST * stringList)
{
	/* Do nothing for now */
}
