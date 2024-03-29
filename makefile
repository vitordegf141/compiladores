#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#
etapa4: hash.o verification.c ast.o tacs.o y.tab.c lex.yy.c main.c parser.y
	gcc hash.o ast.o tacs.o lex.yy.c -o etapa5

y.tab.c: parser.y
	yacc -d -v parser.y

lex.yy.c: scanner.l
	lex scanner.l

hash.o: hash.c
	gcc -c hash.c

tacs.o: tacs.c
	gcc -c tacs.c

ast.o: ast.c
	gcc -c ast.c

clean:
	rm y.tab.c y.tab.h lex.yy.c etapa5 hash.o ast.o tacs.o