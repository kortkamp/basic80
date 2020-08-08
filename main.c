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


//TODO load a file .bas
int main(){
	exec_ptr = 0;
	program_ptr = 0; 
	clear_vars();
	
	// Will store the input commands that do not have line specification.
	char cbuffer[MAX_INPUT_LENGHT] = {0}; 
	printf("Basic80 Interpreter\n");
	printf("%d bytes free\n", MEM_SIZE);
	printf("OK\n");

	while(1){
		error = 0;
		
		// Read input from user.
		scanf(" %80[^\n]s", cbuffer); 
		// Check line entering
		if(cbuffer[0] >= '0' && cbuffer[0] <= '9'){
			// Line starts with number.
			enter_line(cbuffer);
		}else{
			// Direct mode.
			exec_line(cbuffer);
			if(error != 0)
				printf("? %s\n",error_msg[error]);
			//printf("\n");
			printf("Ok\n");
		}

	}
	return(0);
}
