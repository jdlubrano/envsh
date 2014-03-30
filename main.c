#include <stdlib.h>
#include <stdio.h>
#include "envsh_structs.h"
#include "envsh.h"
#include "y.tab.h"

extern int yyparse(void);

int main(int argc, char * argv[])
{
	initCmdPrefix();
	printCmdPrompt();
	int status = yyparse();
	return status;
}
