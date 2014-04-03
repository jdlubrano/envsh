/*
 * envsh.h
 * Header file for envsh
 * Contains structs for word_list, string_list
 * Contains function declarations for builtIn and userCmd
 * Author: Joel Lubrano
 */

#ifndef _ENVSH_H_
#define _ENVSH_H_

#include <stdlib.h>

void initCmdPrompt(void);
void printCmdPrompt(void);
void builtIn(int cmd, char * str, char * varName);
void userCmd(WORD_LIST * wordList);

ENVIRON_LIST * environList;

#endif /* _ENVSH_H_DEFINED_ */
