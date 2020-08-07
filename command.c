#include "command.h"
#include "program.h"
#include <stdio.h>
#include <stdlib.h>

// Array with name and pointer to functions.
struct commands command_list[COMMAND_NUM] = {
	{"print",&print},
	{"system", &system_exit},
	{"list", &list},
	{"new", &new},
	{"run", &run},
	{"goto",&goto_line},
	{"if", &ifthen}	
};

void print(char *arg){

	//printf("%ld\n",get_var(arg));
	long value = evaluate(arg);
	if(error == 0)
		printf(" %ld\n", value);
}
void system_exit(){
	exit(0);
}
void clear(){
}
void run(){
	while(exec_ptr < program_ptr && error == 0){

		exec_line(get_line(exec_ptr++));
		//exec_ptr++;
	}
		exec_ptr = 0;
}

void new(){
	for(int i = 0 ; i < program_ptr; i ++)
		program_mem[i].line_number = 0;
	clear_vars();
	program_ptr = 0;
	exec_ptr = 0;
}
void list(){
	for(int i = 0 ; i < program_ptr ; i ++)
		printf("%d %s\n", program_mem[i].line_number,program_mem[i].line);
}

void ifthen(char *arg){
	int pos = 0;
	while(strncmp(arg+pos,"then",4) != 0) {
		pos++;
		// Found EOF without "then".
		if(arg[pos] == '\0') {
			error = SYNTAXERROR;
			return;
		}
	}
	arg[pos] = '\0';
	if(evaluate(arg)){
		// size of '\0' + "then"
		pos += 5; 
		//printf("eval: %s, run:(%s)\n",arg, arg + pos);
		exec_line(arg+pos);
	}	
	return;
}
