/*
 * envsh_structs.h
 * Header file for defining word_list and string_list structs.
 * Author: Joel Lubrano
 */

#ifndef _ENVSH_STRUCTS_H_
#define _ENVSH_STRUCTS_H_

typedef struct word_list {
	struct word_list * next;
	char * word;
} WORD_LIST;

typedef struct string_list {
	struct string_list * next;
	char * string;
} STRING_LIST;

#endif /* _ENVSH_STRUCTS_H_DEFINED_  */
