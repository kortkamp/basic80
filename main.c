#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 0x7fff
#define MAX_INPUT_LENGHT 80



char cbuffer[MAX_INPUT_LENGHT] = {0}; //will store the input commands that do not have line specification
int icounter = 0; 


int test_attribution(char *buffer){//test if we have a var attibution like  day = 10
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
	int ivalue;
	float fvalue;
	char svalue[50];

	sscanf(buffer," %[^ =]s",var_name);
	printf("\nnew var (%s)\n",var_name);

	return(1);
}
int test_line(char *buffer){//verify if we have a line attibution like    10 print 1+1



}
int main(){
	printf("Basic80 Interpreter\n");
	printf("%d bytes free\n", MEM_SIZE);
	printf("OK\n");
	while(1){
		scanf(" %80[^\n]s", cbuffer);
		if(test_attribution(cbuffer)) exec_attribution(cbuffer);
	}
	return(0);
}
