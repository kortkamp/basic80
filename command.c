//TODO goto must acept line specification

#include "command.h"
#include "program.h"
#include <stdio.h>
#include <stdlib.h>

int set_break;

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


//TODO add printing in the same line with ';'
void print(char *arg){

	//printf("print(%s)\n",arg);
	long value = evaluate(arg);

//	if(!strchr(arg,';'))
//		printf("\n");
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
	exec_ptr = 0;
	clear_vars();
	cont();
}
// Resumes execution of a program.
void cont(){
	set_break = FALSE;
	while(exec_ptr < program_ptr && error == 0 && !set_break){
		exec_line(get_line(exec_ptr++));
		//printf("\n");
		//exec_ptr++;
	}
}

void new(){
	for(int i = 0 ; i < program_ptr; i ++)
		program_mem[i].line_number = 0;
	clear_vars();
	program_ptr = 0;
	exec_ptr = 0;
}
void list(char *arg){
	int start = 0;
	sscanf(arg,"%d",&start);
	for(int i = get_index(start) ; i < program_ptr ; i ++)
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
// TODO fazer funcionar backwards
void for_next(char *arg){
	//char arg[] = "for i = 2 to 14 step 1"; printf("%s\n",arg);
	long limit;
	long step = 0;
	long *var;
	int pos_to = 0;
	int pos_step = 0;
	int after_for_ptr = exec_ptr  ;
	int after_next_ptr;
	// direction 1 aftewards
	// direction -1 backwards
	int direction = 1; 
	while(strncmp(arg+pos_to,"to ",3) != 0) {
		pos_to++;
		// Found EOF without "to".
		if(arg[pos_to] == '\0') {
			error = SYNTAXERROR;
			//printf("to erro\n");
			return;
		}
	}
	arg[pos_to] = '\0';
	if(test_attribution(arg)){
		var = exec_attribution(arg);
		// size of '\0' + "to "
		pos_to += 3; 
		//printf("eval: %s, run:(%s)\n",arg, arg + pos);
		//exec_line(arg+pos);
	}else{
		printf("attribution failed\n");
		error = SYNTAXERROR;
		return;
	}

	pos_step = pos_to;
	while(strncmp(arg + pos_step,"step ",5) != 0) {
		// Found EOF without "step".
		if(arg[pos_step] == '\0') {
			//error = SYNTAXERROR;
			//printf("step erro\n");
			//return;
			step = 1;
			break;
		}

		pos_step++;
	}
	arg[pos_step] = '\0';
	limit  = evaluate(arg+pos_to);
	pos_step += 5;
	if(step == 0) step = evaluate(arg+pos_step);
//	printf("var:%ld ::limit(%d):%s=%ld  step(%d):%s=%ld\n",*var,pos_to,arg+pos_to,limit,pos_step,arg + pos_step,step);
	if(var > limit && step < 0 ) direction = -1;
	while((*var)*direction <= limit){
		//printf("exec_ptr:%d\n",exec_ptr);
		//run();
		cont();
		
		if(set_break == FALSE) {
			// Came back here without finding a next
			// actualy found the end os instructions
			return;
		}
		after_next_ptr = exec_ptr;
		exec_ptr = after_for_ptr;
		*var += step;
	}
	exec_ptr = after_next_ptr;
	set_break = FALSE;
	return;

}
// TODO add tratamento de var para retornar para o for correto
void next(char *arg){
	//printf("next\n");
	set_break = TRUE;
}
