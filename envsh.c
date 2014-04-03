#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "envsh_structs.h"
#include "envsh.h"
#include "y.tab.h"

static char * cmdPrompt;
extern int INPUT_FROM_FILE;
extern ENVIRON_LIST * environList;

void initCmdPrompt()
{
	cmdPrompt = "envsh > ";
}

void printCmdPrompt()
{
	printf("\n");
	printf("%s", cmdPrompt);
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
			cmdPrompt = str;
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

void userCmd(WORD_LIST * wordList)
{
	/* 
	 * Count the number of entries in the 
	 * word list in order to size the array.
	 */
	int wordListSize = 0;
	int environListSize = 0;
	WORD_LIST * wordListIterator = wordList;
	/* Iterate through the word list to calculate the size */
	while(wordListIterator != NULL)
	{
		wordListSize++;
		wordListIterator = wordListIterator->next;
	}
	/* 
	 * Allocate a new array for the args in the word list 
	 * plus one for the NULL sentinel
	 */ 
	char ** argv = malloc((wordListSize + 1) * sizeof(char[INPUT_LIMIT]));
	/* Copy word list to argv */
	wordListIterator = wordList;
	int i = 0;
	while(wordListIterator != NULL)
	{
		argv[i] = wordListIterator->word;
		wordListIterator = wordListIterator->next;
		i++;
	}
	argv[i] = NULL;
	ENVIRON_LIST * environListIterator = environList;
	while(environListIterator != NULL)
	{
		environListSize++;
		environListIterator = environListIterator->next;
	}
	char ** environ = malloc((environListSize + 1) * sizeof(char[2*INPUT_LIMIT + 1]));
	/* 
	 * Create environ strings in VAR=VAL format for each variable
	 * in the environList.
	 */
	environListIterator = environList;
	i = 0;
	while(environListIterator != NULL)
	{
		environ[i] = environListIterator->varName;
		strcat(environ[i], "=");
		strcat(environ[i], environListIterator->varValue);
		environListIterator = environListIterator->next;
		i++;
	}
	environ[i] = NULL;
	execve(argv[0], argv, environ);
}
