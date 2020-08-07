#ifndef _COMMAND_H
#define _COMMAND_H

#include <string.h>
#include "error.h"
#include "basic.h"
#include "math.h"

struct commands{
	char name[20];
	void (*function)(char*);
};

struct commands command_list[COMMAND_NUM]; 

void print(char*);
void system_exit();
void run();
void new();
void list();
void clear();
void ifthen(char*);

#endif
