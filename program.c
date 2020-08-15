#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "program.h"



void  goto_line(char *line_number_str){
	int line_number = 0;
	sscanf(line_number_str,"%d",&line_number);
	// we need to decrement by 1 becouse
	// run() function adds 1 right after execution
	// of the instruction
	exec_ptr = get_index(line_number) - 1 ;
	
//	printf("line:%d index:%d\n",line_number,get_index(line_number));
}
// Return a position index of a line in program_mem.
int find_line(int number){
	for(int i = 0 ; i < MAX_LINES; i++){
		if(program_mem[i].line_number == number) return(i);	
	}
	return(-1);
}
// Execute a single command.
int exec_single(char *line){
	//printf("exec_single:(%s)\n",line);
	char command[10];
	char arg[50] = {0}; // Argument of command.
	sscanf(line,"%[^ ] %[^\n]s",command,arg);
	//printf("%s >> %s\n",command, arg); 		
	for(int i = 0 ; i < COMMAND_NUM; i ++)
		if(!strcmp(command,command_list[i].name)){
		       	(command_list[i].function)(arg);
			return(0);	
		}
	// Command not found.
	
	// Test if statement is a attribution "x = 3"
	if(test_attribution(line)) {
		exec_attribution(line);
		return(0);
	}
	error = SYNTAXERROR;
	return(-1);
}
// Exec multiples commands in a line.
int exec_line(char *line){
	int line_pos = 0;
	int buff_pos = 0;
	char buffer[255];	
	while( line[line_pos] != 0){
		buffer[buff_pos++] = line[line_pos++];
		if(line[line_pos] == ':' || line[line_pos] == '\0'|| line[line_pos] == 13){
			buffer[buff_pos] = '\0';
			//for(int i = 0 ; i < 10;i++) printf("%d ",buffer[i]);printf("\n");
			exec_single(buffer);
			if(line[line_pos] == '\0'){
				return(0);
			}
			// Restart a new buffer.
			buff_pos = 0;
			line_pos++;
			// Dicard spaces in start of a new command.
			while(line[line_pos] == ' ') line_pos++;
		}
	}
	return(0);
}


int drop_line(int index){
	// The line dont exists.
	if(index == -1) return(0);

	//drop code goes here
	for(int i = index; i < program_ptr; i ++){
		program_mem[i].line_number = program_mem[i+1].line_number;
		strcpy(program_mem[i].line, program_mem[i+1].line); 
	}	

	program_ptr--;
	return(0);
}

// Write a line and number in index of program_mem.
int put_line(int index, int line_number, char *line){
	program_mem[index].line_number = line_number;
	strcpy(program_mem[index].line, line);
	return(0);
}
int expand_lines(int line_number,char *line){
	int index = get_index(line_number);
	for(int i = program_ptr; i > index;  i--){
		program_mem[i].line_number = program_mem[i-1].line_number;
		strcpy(program_mem[i].line, program_mem[i-1].line); 
	}
	put_line(index,line_number,line);
	program_ptr++;
	return(0);
}
int get_index(int line_number){
	int index = 0;
	while(program_mem[index].line_number < line_number && index < program_ptr){
		index++;
	}
	return(index);
}
char *get_line(int index){
	return(program_mem[index].line);
}

// Return a pointer to start of next line.
// If end of program_space found return NULL.
char *get_next_line(){
	while(prog_exec < PROGRAM_SIZE)
		if(program_space[prog_exec++] == LINE_SEPARATOR)
			return(program_space + prog_exec);
	return(NULL);

}
// Return a pointer to start of previous line.
// If start of program_space found return NULL.
char *get_prev_line(){
	prog_exec -= 2;	
	while(prog_exec >= 0)
		if(program_space[prog_exec--] == LINE_SEPARATOR){
			prog_exec += 2;
			return(program_space + prog_exec);
		}
	return(NULL);
}

// Returns the line number of a string.
int get_line_number(char *line){
	int number = 0;
	if(line == NULL)
		return(0);	
	sscanf(line, " %d",&number);
	return(number);
}	

// Expand a position in program_space to open space for a new line
int expand(long position, long count){


}
// List all entries in program_space.
void list(){




}
// Clear all positions in program_space.
void program_space_clear(){
	memset(program_space, 0,PROGRAM_SIZE);
}
// Enter a line into program memory.
int enter_line(char *line){
	int line_number = get_line_number(line);;
	int search_number = 0;
	int size = strlen(line);
	int line_pos = 0;
	char *search;
	search = strchr(program_space, LINE_INIT);
	while(search != NULL){
		search++;
		search_number = get_line_number(search);
		printf("number = %d\n",search_number);
		if(search_number > line_number){


		}

		search = strchr(search, LINE_INIT);
	}
	expand(prog_exec,size + 2);
	
	program_space[prog_exec++] = LINE_INIT;

	// Add separator.
	while(line[line_pos] != ' '){
		line_pos++;
	}	
	line[line_pos] == CMD_SEPARATOR;
	
	for(int i = 0; i <= size; i++){
		// Add separator.
		if(line[i] == ':') 
			line[i] = CMD_SEPARATOR;
		
		program_space[prog_exec++] = line[i];
	}	

	return(0);
}

void test_program(){
	program_space_clear();
	printf("TEST NEW PROGRAM STRUCTURE\n");
	enter_line("10 PRINT 10");
	enter_line("20 PRINT 20");
	enter_line("30 PRINT 30");
	
}
