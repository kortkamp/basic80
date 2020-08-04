#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE -1
#define FALSE 0
#define MEM_SIZE 0x7fff
#define MAX_INPUT_LENGHT 80
#define MAX_LINES 1000

// Number of commands in Basic.
#define COMMAND_NUM 20 

struct commands{
	char name[20];
	void (*function)(char*);

};
struct program{
	int line_number;
	char line[80];
};

struct program program_mem[MAX_LINES];
// Pointer to next free line space.
int program_ptr = 0; 


int icounter = 0; 

// A var must be identified by its first two letters.
long var[26][26] = {0};



// Return the value of a numeric var.
long get_var(char *name){
	return(var[name[0]-'a'][name[1]-'a']);
}
// Set a value for a var;
int set_var(char *name, long value){
	var[name[0] - 'a'][name[1]-'a'] = value;
}

// Evaluate Math.
int evaluate(char *arg){



}

// Test if we have a var attibution like  day = 10.
int test_attribution(char *buffer){
	int counter = 0;
	while(buffer[counter] != 0){
		if(buffer[counter] == '=')
			return(1);
		counter++;
	}
	return(0);

}
int exec_attribution(char *buffer){
	char var_name[20];
	long value;
	sscanf(buffer," %[^ =] =%ld",var_name,&value);
//	printf("new var (%s)= %ld\n",var_name,value);
	set_var(var_name,value);

	return(1);
}
// Verify if we have a line attibution like    10 print 1+1.
int test_line(char *buffer){



}
void print(char *arg){

	printf("%ld\n",get_var(arg));

}
void system_exit(){
	exit(0);
}
void clear(){
}
void run(){
}

void list(){
	for(int i = 0 ; i < program_ptr ; i ++)
		printf("%d %s\n", program_mem[i].line_number,program_mem[i].line);
}
// Array of name and pointer to functions.
struct commands command_list[COMMAND_NUM] = {
	{"print",&print},
	{"system", &system_exit},
	{"list", &list},
	{"clear",&clear},
	{"run", &run}
	
};

// Return a position index of a line in program_mem.
int find_line(int number){
	for(int i = 0 ; i < MAX_LINES; i++){
		if(program_mem[i].line_number == number) return(i);	
	}
	return(-1);
}

// Execute a command.
int exec_line(char *line){
	char command[10];
	long t_var; // Temporary var.
	char arg[50]; // Argument of command.
	sscanf(line,"%[^ ] %s",command,arg);
	//printf("%s >> %s\n",command, arg); 		
	if(test_attribution(line)) {
		exec_attribution(line);
	}
	for(int i = 0 ; i < COMMAND_NUM; i ++)
		if(!strcmp(command,command_list[i].name)) (command_list[i].function)(arg);

}

int drop_line(int index){
	// The line dont exists.
	if(index == -1) return(0);
	
	//drop code goes here

	program_ptr--;
}

// Write a line and number in index of program_mem.
int put_line(int index, int line_number, char *line){
	program_mem[index].line_number = line_number;
	strcpy(program_mem[index].line, line);
	program_ptr++;
}

char *get_line(int index){
	return(program_mem[index].line);
}

// Enter a line into program memory.
int enter_line(char *line_str){
	int line_number;
	char line[80];
	int line_index; // Index in program_mem
	int line_size;
	sscanf(line_str," %d %[^\n]\n",&line_number,line);
	line_size = strlen(line);
	line_index = find_line(line_number);
	
	// Empty line.
	if(line_size == 1){
	       	drop_line(line_index); 
		return(0);
	}

	// Line exists, substitute!
	if(line_index != -1) {
		put_line(line_index,line_number,line);
		program_ptr--;
		return(0);
	}
	
	// The entered line is the next in order
	if(line_number > program_mem[program_ptr -1].line_number){
		put_line(program_ptr,line_number,line);
		return(0);
	}
	// Entered line is between previous line,
	// make space for new line.
	//expand_line();
	//	printf("%d:%s size:%d\n",line_number, line, strlen(line));

}
int main(){

	// Will store the input commands that do not have line specification.
	char cbuffer[MAX_INPUT_LENGHT] = {0}; 
	
	printf("Basic80 Interpreter\n");
	printf("%d bytes free\n", MEM_SIZE);
	printf("OK\n");

	while(1){
		// Read input from user.
		scanf(" %80[^\n]s", cbuffer); 
		// Check line entering
		if(cbuffer[0] >= '0' && cbuffer[0] <= '9'){
			// Line starts with number.
			enter_line(cbuffer);
		}else{
			// Direct mode.
			exec_line(cbuffer);
		}

	}
	return(0);
}
