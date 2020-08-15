#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "error.h"
#include "basic.h"
#include "command.h"

#define CMD_SEPARATOR	0x80
#define LINE_SEPARATOR	0x81
#define LINE_INIT	0x81

#define PROGRAM_SIZE 20000


// Array used to store the program.
char program_space[PROGRAM_SIZE];

// Position to store next line.
long prog_store;

// Search position in program_space.
long prog_search;

// Position to exectute line or search line.
long prog_exec;

struct program{
	int line_number;
	char line[80];
};
struct program program_mem[MAX_LINES];


// Pointer to next free line space.
int program_ptr; 

// Pointer do next line to be executed.
int exec_ptr;

void  goto_line(char*);
int find_line(int);

int exec_line(char*);

int drop_line(int);

int put_line(int , int , char*);
int expand_lines(int ,char*);
int get_index(int );
char *get_line(int );
int enter_line(char*);
void test_program();

#endif
