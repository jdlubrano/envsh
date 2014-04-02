#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "envsh_structs.h"
#include "envsh.h"
#include "y.tab.h"

extern int yyparse(void);

int main(int argc, char * argv[])
{
	initCmdPrompt();
	printCmdPrompt();
	int status = yyparse();
	printf("\n");
	return status;
}
