#include "command.h"
#include "program.h"
#include <stdio.h>
#include <stdlib.h>

// Array with name and pointer to functions.
struct commands command_list[COMMAND_NUM] = {
	{"print",&print},
	{"system", &system_exit},
		{"cls",&clear},
	{"list", &list},
	{"new", &new},
	{"run", &run},
	{"goto",&goto_line},
	{"if", &ifthen},
	{"for", &for_next},
	{"next",&next}
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
// TODO funcionar em qualquer SO
void clear(){
	system("clear");
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
// TODO substituir rotinas de busca por sscanf
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
// TODO substituir rotinas de busca por sscanf
void for_next(char *arg){
	//char arg[] = " i = 2 to 14 step 1"; printf("%s\n",arg);
	long limit;
	long step;
	int pos_to = 0;
	int pos_step = 0;
	while(strncmp(arg+pos_to,"to ",3) != 0) {
		pos_to++;
		// Found EOF without "to".
		if(arg[pos_to] == '\0') {
			error = SYNTAXERROR;
			printf("to erro\n");
			return;
		}
	}
	arg[pos_to] = '\0';
	if(test_attribution(arg)){
		exec_attribution(arg);
		// size of '\0' + "to "
		pos_to += 3; 
		//printf("eval: %s, run:(%s)\n",arg, arg + pos);
		//exec_line(arg+pos);
	}else{
		printf("attribution failed\n");
		error = SYNTAXERROR;
		return(-1);
	}

	pos_step = pos_to;
	while(strncmp(arg + pos_step,"step ",5) != 0) {
		// Found EOF without "step".
		if(arg[pos_step] == '\0') {
			error = SYNTAXERROR;
			printf("step erro\n");
			return;
		}

		pos_step++;
	}
	arg[pos_step] = '\0';
	limit  = evaluate(arg+pos_to);
	pos_step += 5;
	step = evaluate(arg+pos_step);
	printf("::limit(%d):%s=%ld  step(%d):%s=%ld\n",pos_to,arg+pos_to,limit,pos_step,arg + pos_step,step);
	
	return;

}

void next(){


}
