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




int exec_line(char*);

char *get_line(int );
	
int get_index(int );
	
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
// Pointer do next line to be executed.
int exec_ptr = 0;

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
	while(exec_ptr < program_ptr){

		exec_line(get_line(exec_ptr++));
		//exec_ptr++;
	}
		exec_ptr = 0;
}

void new(){
	for(int i = 0 ; i < program_ptr; i ++)
		program_mem[i].line_number = 0;
	program_ptr = 0;
	exec_ptr = 0;
}
void list(){
	for(int i = 0 ; i < program_ptr ; i ++)
		printf("%d %s\n", program_mem[i].line_number,program_mem[i].line);
}
void  goto_line(char *line_number_str){
	int line_number = 0;
	sscanf(line_number_str,"%d",&line_number);
	exec_ptr = get_index(line_number) ;
	
//	printf("line:%d index:%d\n",line_number,get_index(line_number));
}
// Return a position index of a line in program_mem.
int find_line(int number){
	for(int i = 0 ; i < MAX_LINES; i++){
		if(program_mem[i].line_number == number) return(i);	
	}
	return(-1);
}
// Array with name and pointer to functions.
struct commands command_list[COMMAND_NUM] = {
	{"print",&print},
	{"system", &system_exit},
	{"list", &list},
	{"clear",&clear},
	{"run", &run},
	{"new", &new},
	{"goto",&goto_line}
	
};

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
	for(int i = index; i < program_ptr; i ++){
		program_mem[i].line_number = program_mem[i+1].line_number;
		strcpy(program_mem[i].line, program_mem[i+1].line); 
	}	

	program_ptr--;
}

// Write a line and number in index of program_mem.
int put_line(int index, int line_number, char *line){
	program_mem[index].line_number = line_number;
	strcpy(program_mem[index].line, line);
}
int expand_lines(int line_number,char *line){
	int index = get_index(line_number);
	for(int i = program_ptr; i > index;  i--){
		program_mem[i].line_number = program_mem[i-1].line_number;
		strcpy(program_mem[i].line, program_mem[i-1].line); 
	}
	put_line(index,line_number,line);
	program_ptr++;
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
	int line_size;
	int num_args = sscanf(line_str," %d %[^\n]\n",&line_number,line);
	line_size = strlen(line);
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
