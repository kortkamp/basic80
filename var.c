#include "var.h"




// Return the value of a numeric var.
long get_var(char *name){
	if(name[1] == '\0')
		// len of name = 1
		return(var[name[0]-'a'][0]);
	return(var[name[0]-'a'][name[1]-'a']);
}
// Set a value for a var;
int set_var(char *name, long value){
	//	printf("set_var:%s << %ld",name,value);
	if(name[1] == '\0'){
		var[name[0]-'a'][0] = value;
		return(0);
	}
	var[name[0] - 'a'][name[1]-'a'] = value;
	return(0);
}
void clear_vars(){
	for(int i = 0 ; i < 26 ; i++)
		for(int j = 0 ; j < 26 ; j ++)
			var[i][j] = 0;
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
	int size; // size of string read
	sscanf(buffer," %[^=] =%n",var_name,&size);
	if(var_name[1] == ' ') var_name[1] = '\0'; 
//i	printf("new var (%s)= %d, left:(%s),%ld\n",var_name,size,buffer+size,evaluate(buffer+size));
	set_var(var_name,evaluate(buffer+size));

	return(1);
}

