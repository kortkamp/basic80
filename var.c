#include "var.h"


//TODO adicionar variáveis string
//TODO add Missing Operand error



// Return the value of a numeric var.
float get_var(char *name){
	if(name[1] == '\0' || name[1] == ' ')
		return(var[name[0]-'A'][0]);
	return(var[name[0]-'A'][name[1]-'0']);
}
// Set a value for a var;
float *set_var(char *name, float value){
	if(name[1] == '\0' || name[1] == ' '){
		var[name[0]-'A'][0] = value;
		return(&var[name[0]-'A'][0]);
	}
	var[name[0] - 'A'][name[1]-'0'] = value;
	return(&var[name[0] - 'A'][name[1]-'0']);
}
float *get_var_pointer(char *name){
	if(name[0] == '\0') 
		return(NULL);
	if(name[1] == '\0' || name[1] == ' '){
		return(&var[name[0]-'A'][0]);
	}
	return(&var[name[0] - 'A'][name[1]-'0']);
}
void clear_vars(){
	for(int i = 0 ; i < 26 ; i++)
		for(int j = 0 ; j < 26+17 ; j ++)
			var[i][j] = 0;
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

