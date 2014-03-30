# makefile
# Joel Lubrano
# Katie Taylor
# Creates envsh program for CS 485
# 03/30/2014

CC 	= gcc -Wall
OPTIONS = -lfl
FLEX	= /usr/bin/flex
OBJECTS = y.tab.o lex.yy.o main.o envsh.o

envsh: $(OBJECTS)
#	bison -y -d parser.y
#	flex scanner.l
	$(CC) $^ -o envsh $(OPTIONS)

y.tab.c:
	bison -y -d parser.y
lex.yy.c:
	flex scanner.l
%.o: %.c
	$(CC) -c $< -o $@
clean:
	rm -f lex.yy.* y.tab.* *.o envsh
