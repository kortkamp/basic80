#include "var.h"

// Array used to store all string vars.
char string_space[STRING_SPACE_SIZE];
long string_space_pos;

// A var must be identified by its first two letters.
float var[26][26+17];
char *str_var[26][26+17];


//TODO adicionar variáveis string
//TODO add Missing Operand error


char null_string[10] = "not found";

// Return the value of a numeric var.
float get_var(char *name){
	if(name[1] == '\0' || name[1] == ' ' || name[1] == '=')
		return(var[name[0]-'A'][0]);
	return(var[name[0]-'A'][name[1]-'0']);
}
// Set a value for a var;
float *set_var(char *name, float value){
	if(name[1] == '\0' || name[1] == ' ' || name[1] == '='){
		var[name[0]-'A'][0] = value;
		return(&var[name[0]-'A'][0]);
	}
	var[name[0] - 'A'][name[1]-'0'] = value;
	return(&var[name[0] - 'A'][name[1]-'0']);
}
float *get_var_pointer(char *name){
	if(name[0] == '\0') 
		return(NULL);
	if(name[1] == '\0' || name[1] == ' ' || name[1] == '='){
		return(&var[name[0]-'A'][0]);
	}
	return(&var[name[0] - 'A'][name[1]-'0']);
}
void clear_vars(){
	for(int i = 0 ; i < 26 ; i++)
		for(int j = 0 ; j < 26+17 ; j ++){
			var[i][j] = 0;
		}
	for(long i = 0 ; i < STRING_SPACE_SIZE; i++)
		string_space[i] = 0;
	string_space_pos = 0;
}

// Set a string var.
// A var name must be ended with '$'
int set_str_var(char *name, char *str){
	// Format of string in string_space:
	// name$content_of_string|
	
	// General counter.
	int name_pos = 0;
	long str_pos = 0;
	
	// Dicard spaces before name of var.
	while(name[name_pos] == ' ')
		name_pos++;	
	while(name[name_pos] != '$')
		string_space[string_space_pos++] = name[name_pos++];
	string_space[string_space_pos++] = '$';
	while(str[str_pos] != '\0')
		string_space[string_space_pos++] = str[str_pos++];
	// Add a null to terminate sting content.
	string_space[string_space_pos++] = '|';
	//printf("new string_space_pos: %ld\n",string_space_pos);
	return(0);
}
// Return a pointer to content of a var string, 
// if the string doesnt exist, return a pointer to a NULL string
// A var name must be ended with '$'
char *get_str_var(char *name){
	char *content;
	int name_pos = 0;	
	// Dicard spaces before name of var.
	while(name[name_pos] == ' ')
		name_pos++;	
	content = strstr(string_space,name + name_pos);
	
	if(content == NULL)
		return(null_string);
	content = strstr(content,"$") + 1;
	return(content);
}

// Print a string var.
void print_str_var(char *name){
	char *content = get_str_var(name);
	int position = 0;
	while(content[position] != '|')
		printf("%c", content[position++]);
}

// Test if we have a var attibution like  day = 10.
int test_attribution(char *buffer){
	int counter = 0;
	while(buffer[counter] != 0){
		if(buffer[counter] == '=')
			return(TRUE);
		counter++;
	}
	return(FALSE);

}
//TODO verificar se a variável é um string e chamar a função correspondente
//TODO set Missing operand error 
float *exec_attribution(char *buffer){
	char var_name[20];
	int size; // size of string read
	sscanf(buffer," %[^=] =%n",var_name,&size);
	if(var_name[1] == ' ') var_name[1] = '\0'; 
	return(set_var(var_name,evaluate(buffer+size)));

}

