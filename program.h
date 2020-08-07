#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "error.h"
#include "basic.h"
#include "command.h"

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

#endif
