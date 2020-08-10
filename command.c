//TODO goto must acept line specification

#include "command.h"
#include "program.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

int set_break;

// Pointer to var passed to next.
// If not passed var, return NULL
long *next_var;

// Array with name and pointer to functions.
struct commands command_list[COMMAND_NUM] = {
	{"print",&print},
	{"?",&print},
	{"system", &system_exit},
	{"cls",&clear},
	{"list", &list},
	{"new", &new},
	{"run", &run},
	{"goto",&goto_line},
	{"if", &ifthen},
	{"for", &for_next},
	{"next",&next},
	{"rem",&rem},
	{"let",&let},
	{"input",&input},
	{"end",&system_exit},
	{"load",&load}
};


//TODO add printing in the same line with ';'
//TODO add printing many args
void print(char *arg){
	
	int arg_pos = 0;
	int buff_pos = 0;
	char buff[255]; 
	long value;

	while(arg[arg_pos] != '\0' ){
		switch(arg[arg_pos]){
			case '"':
				// Discard " by adding 1 to arg_pos
				arg_pos++;
				if(buff_pos > 0){
					// we have a expression before start 
					// of a string, so print evaluation of
					// the expression
					buff[buff_pos] = '\0';
					value = evaluate(buff);
					printf(" %ld ",value);
					buff_pos = 0;
				}
				// If inside " , then print text
				while(arg[arg_pos] != '"' && arg[arg_pos] != '\0'){

					printf("%c",arg[arg_pos++]);
				}
				arg_pos++;
			break;

			case ';':
				// Discand ';'.
				arg_pos++;
			break;

			case ' ':
				// Dicard spaces.
				arg_pos++;
			break;

			default:
				buff[buff_pos++] = arg[arg_pos++];	

			break;	
		}
	}
			
	if(buff_pos > 0){
		// we have a expression before start 
		// of a string, so print evaluation of
		// the expression
		buff[buff_pos] = '\0';
		value = evaluate(buff);
		printf(" %ld",value);
		buff_pos = 0;
	}
	printf("\n");
	return;
}

void rem(){
	// Do nothing.
}
void let(char *arg){
	if(test_attribution(arg)) {
		exec_attribution(arg);
		return;
	}
}
void input(char *arg){

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
	if(error != 0) error_line = program_mem[exec_ptr - 1].line_number;
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
// TODO add else processing
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



// Returns the index pointer of the next "next" statement,
// if not found return 0;
int find_next_stm(){
	while(!strncmp("next",program_mem[exec_ptr].line,4 )){
		exec_ptr++;
		if(exec_ptr>=program_ptr) return(0);
	}
	//printf("found a next stm\n");
	return(exec_ptr);
}



// TODO substituir rotinas de busca por sscanf
void for_next(char *arg){
	//char arg[] = "for i = 2 to 14 step 1"; printf("%s\n",arg);
	long limit;
	long step = 0;
	long *var;
	int pos_to = 0;
	int pos_step = 0;
	int after_for_ptr = exec_ptr  ;
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
		//printf("var *%ld\n",var);
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

	if(*var > limit && step < 0 ) direction = -1;
	while((*var)*direction <= limit*direction){
		//printf("exec_ptr:%d\n",exec_ptr);
		// must be set to 1 bcuz in last while it could be set to 0; 	
		next_var = (long *)1;
		error = 0;
		// Points the execution pointer to instruction 
		// right behind the for statement
		exec_ptr = after_for_ptr;
		// call the continue untill a error or end of program ocurrs
		cont();
		// The cont stops if:
		// 1 next found
		// 2 end of program found
		// 3 error found
		if(error == NEXTERROR && (next_var == var || next_var == NULL)){
			//continue
		}else{
			error = 0;
			return;
		}	

		*var += step;
	}
	// Need clear error cuz 'while' stoped in a NEXTERROR error.
	error = 0;
	// While not end of program	
	while(exec_ptr < program_ptr)	{
		// Exec the next "next" statement to get and test next_var.
		exec_line(get_line(find_next_stm()));
		//printf("next 'next' ptr:%d\n",exec_ptr);	
		// If the correct next was found we must set 
		// exec_ptr to right after the "next" statement
		exec_ptr++;
		if(next_var == var || next_var == 0) return;	
	}
	// We didnt found a "next" statement
	// the exec_ptr was set to end of program_mem
	// and the execution will finish
	return;

}
// TODO add tratamento de var para retornar para o for correto
void next(char *arg){
	//printf("next\n");
	error = NEXTERROR;
	// Puts in the next_var the pointer to var passed to this "next" statement
	next_var = get_var_pointer(arg);
//	printf("var(%s) *%ld\n",arg,next_var);
	//set_break = TRUE;
}
