# Basic80 Makefile
 
all: basic
 
basic: main.o math.o
	gcc -lm -o basic main.o math.o
 
main.o: main.c
	gcc -o main.o main.c -lm -c -W -Wall -pedantic
 
math.o: math.c math.h
	gcc -o math.o math.c -lm -c -W -Wall -pedantic
 
clean:
	rm -rf *.o *~ basic
