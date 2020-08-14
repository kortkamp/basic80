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
// Execute a simgle command.
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

// Enter a line into program memory.
int enter_line(char *line_str){
	int line_number;
	char line[80];
	int line_index; // Index in program_mem
	int num_args = sscanf(line_str," %d %[^\n]\n",&line_number,line);
	line_index = find_line(line_number);
	
	// Empty line string.
	if(num_args < 2){
	       	drop_line(line_index); 
		return(0);
	}
	// Line exists, substitute!
	if(line_index != -1) {
		put_line(line_index,line_number,line);
		return(0);
	}
	
	// The entered line is the next in order
	if(line_number > program_mem[program_ptr -1].line_number){
		put_line(program_ptr,line_number,line);
		program_ptr++;
		return(0);
	}

	// Entered line is between previous line,
	// make space for new line.
	expand_lines(line_number,line);
	return(0);
}
