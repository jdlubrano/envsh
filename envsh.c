#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "envsh_structs.h"
#include "envsh.h"
#include "y.tab.h"

static char * cmdPrefix;
extern int INPUT_FROM_FILE;
extern ENVIRON_LIST * environList;

void initCmdPrompt()
{
	cmdPrefix = "envsh > ";
}

void printCmdPrompt()
{
	printf("\n");
	printf("%s", cmdPrefix);
}

void addToEnvironList(char * varName, char * varValue)
{
	/* Check if variable exists in ENVIRON_LIST */
	ENVIRON_LIST * currentEntry = environList;
	int found = 0;
	while(currentEntry != NULL && !found)
	{
		if(strcmp(currentEntry->varName, varName) == 0)
		{
			strncpy(currentEntry->varValue, varValue, 
					sizeof(currentEntry->varValue));
			found = 1;
	
		}
		currentEntry = currentEntry->next;
	}
	/* 
	 * If no existing entry was found, create a new entry
	 * at the start of the list
	 */
	if(!found)
	{
		/* Create new entry */
		ENVIRON_LIST * newEntry = malloc(sizeof(ENVIRON_LIST));
		strncpy(newEntry->varName, varName, sizeof(newEntry->varName));
		strncpy(newEntry->varValue, varValue, sizeof(newEntry->varValue));
		newEntry->prev = NULL;
		/* Point newEntry->next to start of global list */
		newEntry->next = environList;
		if(environList != NULL)
			environList->prev = newEntry;
		/* Change the global pointer to start at newEntry */
		environList = newEntry;
	}
}	

void listEnv()
{
	ENVIRON_LIST * currentEntry = environList;
	while(currentEntry != NULL)
	{
		printf("\n%s=%s", currentEntry->varName, currentEntry->varValue);
		currentEntry = currentEntry->next;
	}
}

void removeFromEnv(char * varName)
{
	ENVIRON_LIST * currentEntry = environList;
	/* 
	 * Set up while loop to prevent running
	 * off the end of linked list
	 */
	int removedEntry;
	removedEntry = 0;
	while(currentEntry != NULL && !removedEntry)
	{
		if(strcmp(currentEntry->varName, varName) == 0)
		{
			/* Check if the entry is the first in the list */
			if(currentEntry->prev == NULL)
			{
				/* Start the list at the second entry */
				environList = currentEntry->next;
				free(currentEntry);
				removedEntry = 1;
			}
			else
			{
				/* Change prev and next pointers to remove from list */
				(currentEntry->prev)->next = currentEntry->next;
				/* Check if current entry is the last in the list */
				if(currentEntry->next != NULL)
					(currentEntry->next)->prev = currentEntry->prev;
				removedEntry = 1;
			}
		}
		if(!removedEntry)
			currentEntry = currentEntry->next;
	}
	/* If no such entry was found, tell the user. */
	if(!removedEntry)
		printf("Could not find %s as an environment variable\n", varName);
}

void builtIn(int cmd, char * str, char * varName)
{
	switch(cmd) {
		case PROMPT: 
			cmdPrefix = str;
			break;
		case SETENV:
			addToEnvironList(varName, str);
			break;
		case UNSETENV:
			removeFromEnv(varName);
			break;
		case LISTENV:
			listEnv();
			break;
		case SETDIR:
			if(chdir(str) < 0)
				perror("setdir");
			break;
		case BYE:
			exit(0);
			break;
		case NEWLINE:
			/* Do nothing */
			break;
		default:
			printf("Unknown built-in command.\n");
	}
}

void userCmd(WORD_LIST * wordList, STRING_LIST * stringList)
{
	/* Do nothing for now */
}
