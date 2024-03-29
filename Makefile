# Basic80 Makefile
 
all: basic
 
 basic: main.o math.o program.o command.o var.o error.o file.o
	gcc -o basic main.o math.o program.o command.o var.o error.o file.o -lm
 
main.o: main.c
	gcc -o main.o main.c -lm -c -W -Wall -pedantic
 
math.o: math.c math.h
	gcc -o math.o math.c -lm -c -W -Wall -pedantic

program.o: program.c program.h
	gcc -o program.o program.c -lm -c -W -Wall -pedantic

command.o: command.c command.h
	gcc -o command.o command.c -lm -c -W -Wall -pedantic

var.o: var.c var.h
	gcc -o var.o var.c -lm -c -W -Wall -pedantic

run:	all
	./basic

test:	all
	./basic TEST.BAS

error.o: error.c error.h
	gcc -o error.o error.c -lm -c -W -Wall -pedantic

files.o: file.c file.h
	gcc -o file.o file.c -lm -c -W -Wall -pedantic

clean:
	rm -rf *.o *~ basic
