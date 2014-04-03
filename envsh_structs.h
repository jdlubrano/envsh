/*
 * envsh_structs.h
 * Header file for defining word_list and string_list structs.
 * Author: Joel Lubrano
 */

#ifndef _ENVSH_STRUCTS_H_
#define _ENVSH_STRUCTS_H_

#define INPUT_LIMIT 256

typedef struct arg_list {
	struct arg_list * next;
	char word[INPUT_LIMIT];
} ARG_LIST;

typedef struct environ_list {
	struct environ_list * next;
	struct environ_list * prev;
	char varName[INPUT_LIMIT];
	char varValue[INPUT_LIMIT];
} ENVIRON_LIST;

#endif /* _ENVSH_STRUCTS_H_DEFINED_  */
