//TODO goto must acept line specification

#include "command.h"
#include "program.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

int set_break;

/* From error.c. */
extern int error;
extern int error_line;

// Array with name and pointer to functions.
struct commands command_list[COMMAND_NUM] = {
	{"PRINT",&print},
	{"?",&print},
	{"SYSTEM", &system_exit},
	{"CLS",&clear},
	{"LIST", &list_program},
	{"NEW", &new_program},
	{"RUN", &run},
	{"GOTO",&goto_line},
	{"IF", &ifthen},
	{"FOR", &for_to},
	{"NEXT",&next},
	{"REM",&rem},
	{"LET",&let},
	{"INPUT",&input},
	{"END",&system_exit},
	{"LOAD",&load},
	{"LINE",&line}
	
};


void print(char *arg){
	int arg_pos = 0;
	int buff_pos = 0;
	char buff[255]; 
	float value;
	char *chr_pos;
	int last_char;
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
					printf(" %g ",value);
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
		// we have a expression after end 
		// of a string, so print evaluation of
		// the expression
		buff[buff_pos] = '\0';
		
		chr_pos = strstr(buff,"CHR$");
		if(chr_pos != NULL){
			chr_pos += 4;
			int value = 0 + evaluate(chr_pos);
			printf("%c",value);
		}else {
			value = evaluate(buff);
			printf(" %g",value);
			buff_pos = 0;
		}
	}
	last_char = strlen(arg)-1;
	while(arg[last_char] == ' '){
		last_char--;
	}
	if(arg[last_char] != ';') printf("\n");
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
// Run a code from beggining (exec_ptr = 0)
void run(){
	exec_ptr = 0;
	clear_vars();
	resume();
}
// Resumes execution of a program.
void resume(){
	set_break = FALSE;
	while(exec_ptr < program_ptr && error == 0 && !set_break){
		//printf("%d\n",program_mem[exec_ptr].line_number);
		exec_line(get_line(exec_ptr));
		exec_ptr++;
		//printf("\n");
		//exec_ptr++;
	}
	if(error != 0) error_line = program_mem[exec_ptr - 1].line_number;
}
// Exec a single line passed in string format.
void line(char *arg){
	int line_number;
	sscanf(arg,"%d",&line_number);
	exec_line(get_line(get_index(line_number)));
	return;

}

void new_program(){
	for(int i = 0 ; i < program_ptr; i ++)
		program_mem[i].line_number = 0;
	clear_vars();
	program_ptr = 0;
	exec_ptr = 0;
}
void list_program(char *arg){
	int start = 0;
	sscanf(arg,"%d",&start);
	for(int i = get_index(start) ; i < program_ptr ; i ++)
		printf("%d %s\n", program_mem[i].line_number,program_mem[i].line);
}
// TODO substituir rotinas de busca por strstr()
void ifthen(char *arg){
	int pos_then = 0;
	int pos_else;
	while(strncmp(arg+pos_then,"THEN ",5) != 0) {
		pos_then++;
		// Found EOF without "THEN".
		if(arg[pos_then] == '\0') {
			error = SYNTAXERROR;
			return;
		}
	}
	pos_else = pos_then;
	while(strncmp(arg+pos_else,"ELSE ",5) != 0){
		pos_else++;
		if(arg[pos_else] == '\0') break;
	}
	// Separate strings for processing
	arg[pos_else] = '\0';
	pos_else += 5;
	arg[pos_then] = '\0';
	if(evaluate(arg) != 0){
		pos_then += 5; 
		exec_line(arg+pos_then);
	}else{
		exec_line(arg+pos_else);
	}
	return;
}


// Returns a pointer to var specified in FOR statement
// If not a FOR command, return NULL.
float *get_for_var(char *line){
	
	char *var = strstr(line,"FOR");
	if(var == NULL){
		return(NULL);
	}
	// Point to position right after the FOR statement.
	var += 3;
	// Dicard spaces after "FOR"
	while(var[0] == ' ') 
		var++;
	// Here we must not separate the var name because, in Basic,
	// only two first letters are used.
	return(get_var_pointer(var));
}

// Returns the assignment to var in a FOR statment.
float get_for_assignment(char *line){

	char assig_buffer[50];
	strcpy(assig_buffer,line);
	char *position_step = strstr(assig_buffer,"STEP");
	char *assignment = strstr(assig_buffer,"=");
	assignment += 1;	
	if(position_step != NULL)
		position_step[0] = '\0';
	return(evaluate(assignment));
}

// Returns the limit assigned in a FOR statement.
float get_for_limit(char *line){
	char limit_assignment[50];
	char *position_step;
	char *limit = strstr(line,"TO");
	if(var == NULL){
		error = SYNTAXERROR;
		return(0);
	}
	limit += 2;
	strcpy(limit_assignment,limit);
	position_step = strstr(limit_assignment,"STEP");	
	if(position_step != NULL)
		position_step[0] = '\0';

	return(evaluate(limit_assignment));
}

// Returns the value of STEP specified in FOR statement.
// If not specified returns 1.
float get_for_step(char *line){

	char *step = strstr(line,"STEP");
	if(step == NULL){
		// Step não especificado.
		if(get_for_limit(line) > get_for_assignment(line))
			return(1);
		return(-1);
	}
	// Position right after the "STEP " 
	step += 4;
	return(evaluate(step));
}

// Just execute the attribution in FOR_TO line
void for_to(char *arg){
	// In our aproach , the for statement does nothing
	// except attributin the value to the var.
	int pos_to = 0;
	
	while(strncmp(arg+pos_to,"TO ",3) != 0) {
		pos_to++;
		// Found EOF without "TO".
		if(arg[pos_to] == '\0') {
			error = SYNTAXERROR;
			return;
		}
	}
	arg[pos_to] = '\0';
	if(test_attribution(arg)){
		exec_attribution(arg);
	}else{
		error = SYNTAXERROR;
	}
	return;
}

// Tests a FOR loop. 
int test_for(char *line){

	// Indicates if a FOR statement goes forward or backward.
	float direction = 1;
	float *var = get_for_var(line);

	if(get_for_step(line) < 0) 
		direction = -1;	
	if(*var*direction > get_for_limit(line)*direction){
		return(FALSE);
	}
	return(TRUE);
}

// next should walk back each line and find its correspondent NEXT statement,
// test and do its work.
// TODO processo a FOR NEXT in the same line.
void next(char *arg){
	// pointer for search.
	int search_ptr = exec_ptr;
	// var passed in arg of NEXT
	float *var = get_var_pointer(arg);
	// Go back and find the respective FOR.
	while(search_ptr >= 0){
		if(get_for_var(get_line(search_ptr)) != NULL){
			// Found a FOR
			// Test if var in NEXT and FOR corresponds
			if(var == NULL || var == get_for_var(get_line(search_ptr))){
				// Found our FOR
				// Assign var in case we have a var == NULL.
				var = get_for_var(get_line(search_ptr));
				//make the test for limits
				*var += get_for_step(get_line(search_ptr));

				if(test_for(get_line(search_ptr))){
					exec_ptr = search_ptr;
				}
				
				return;
			}
		}
		search_ptr--;
	}	
	error = NEXTERROR;
	return;
}
