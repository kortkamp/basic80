#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "error.h"
#include "math.h"
#include "basic.h"
#include "program.h"
#include "command.h"
#include "var.h"
#include "file.h"

//TODO load a file .bas
int main(int argc, char *argv[]){
	exec_ptr = 0;
	program_ptr = 0; 
	clear_vars();
	
	// Will store the input commands that do not have line specification.
	char cbuffer[MAX_INPUT_LENGHT] = {0}; 
	printf("Basic80 Interpreter\n");
	printf("%d bytes free\n", MEM_SIZE);
	printf("OK\n");
	
	if(argc > 1) {
		load(argv[1]);
		run();
	}
	
	if(error == FILEERROR)
		printf("%s\n",error_msg[FILEERROR]);

	while(1){
		error = 0;
		
		// Read input from user.
		scanf(" %80[^\n]s", cbuffer); 
		// Convert all to UpperCase
		for(size_t i = 0 ; i < strlen(cbuffer);i++)
			if(cbuffer[i] >= 'a' && cbuffer[i] <= 'z')
				cbuffer[i] += 'A' - 'a';
		//printf("%s\n",cbuffer);
		// Check line entering
		if(cbuffer[0] >= '0' && cbuffer[0] <= '9'){
			// Line starts with number.
			enter_line(cbuffer);
		}else{
			// Direct mode.
			exec_line(cbuffer);
			if(error != 0)
				printf("? %s in line %d\n",error_msg[error],error_line);
			//printf("\n");
			printf("Ok\n");
		}

	}
	return(0);
}
