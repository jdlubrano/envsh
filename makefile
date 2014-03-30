# makefile
# Joel Lubrano
# Katie Taylor
# Creates envsh program for CS 485
# 03/30/2014

CC 	= gcc -Wall
OPTIONS = -lfl
FLEX	= /usr/bin/flex

envsh:
	bison -y -d parser.y
	flex scanner.l
	$(CC) -c y.tab.c lex.yy.c main.c envsh.c 
	$(CC) y.tab.o lex.yy.o main.o envsh.o -o envsh $(OPTIONS)
clean:
	rm -f *.o envsh
