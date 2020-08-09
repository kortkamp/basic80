#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "basic.h"
#include <string.h>


//TODO add math function 
//TODO add >= <= <> in operate
long operate(long op1, long op2, char op){
//	printf("operate: %ld %c %ld \n",op1, op ,op2);
	switch(op){
		case ':':
			return(op2);

		case '+':
			return(op1+op2);

		case '-':
			return(op1-op2);

		case '*':
			return(op1*op2);

		case '%':
			return(op1%op2);

		case '/':
			if(op2 == 0){
				error = DIVBYZERO;
				return(error);
			}
			return(op1/op2);
		case '^':
			return(pow(op1,op2));

		case '=':
			if(op1 == op2)
				return(-1);
			return(0);
		case '>':
			if(op1 > op2)
				return(-1);
			return(0);
		case '<':
			if(op1 < op2)
				return(-1);
			return(0);

	}
	error = MATHERROR;
	return(-1);
}
// Evaluate Math.
// tier is the priority of the step in evaluation 0 is the lowest
long  eval(char *arg, int tier){
	
	char tier_operator[4][4] = {
		"=><",	// tier 0 operators
		"+-",	// tier 1 operators
		"*/",	// tier 2 operators
		"^%"	// tier 3 operators
			// tier 4 numbers, vars , functions
	};

	char exp[255]; // expression to be passed to next function
	char operator = ':';
	int arg_pos = 0;
	int exp_pos = 0;
	long evalued = 0;
	long value = 0;
	int inside_bracket = 0; // false

	//for(int i = 0 ; i < tier; i++) printf("	"); 	
	//printf("tier: %d expression: %s \n",tier,arg); 

	// tier 4 returns numbers, vars and functions
	if(tier == 4){
		//for(int i = 0 ; i < tier; i++) printf("	"); 
		
		//printf("tier: %d expression: (%s) \n",tier,arg); 
		
		// If we got a expression inside brackets
		if(arg[0] == '('){
			// Restart tier to 0
			tier = 0;
			// Remove '('
			arg[0] = ' ';
			//if(arg[strlen(arg) - 1 ] != ')') error = SYNTAXERROR;
			// Remove ')'
			arg[strlen(arg) - 1 ] = '\0';
			return(eval(arg,0));
		}

		// Is number.
		if((arg[0] >= '0' && arg[0] <= '9')|| arg[0] == '-' )
			sscanf(arg,"%ld",&value);
		else if(arg[0] >= 'a' && arg[0] <= 'z')  {
			// Is function ???
			// code code code
			
			value = get_var(arg);
		}else {
			printf("arg[0] = '%c' ,  value:%d\n",arg[0],arg[0]);
			error = MATHERROR;
		}
	}else {
			while(arg[arg_pos] != '\0'){

			if(arg[arg_pos] == '(') {
				inside_bracket ++;
				//arg_pos++;
			}
			if(arg[arg_pos] == ')'){
				if(inside_bracket < 1) error = MATHERROR;
			       	inside_bracket --;
				//arg_pos++;
			}
			// Discard spaces.	
			if(arg[arg_pos] != ' '){ 
				exp[exp_pos] = arg[arg_pos];
				exp_pos++;
			}
			arg_pos++;
			if(!inside_bracket){
				if(strchr(tier_operator[tier],arg[arg_pos])!= NULL || arg[arg_pos] == '\0'){
					exp[exp_pos] = '\0';
					evalued = eval(exp,tier + 1);		
					//for(int i = 0 ; i < tier; i++) printf("	"); 	
					value = operate(value,evalued,operator);
					operator = arg[arg_pos];
					exp_pos = 0;
					if(arg[arg_pos] != '\0') arg_pos++;
				}
			}

		};
		// Terminou a string sem fechar o bracket
		if(inside_bracket != 0) error = MATHERROR;
	}
	//for(int i = 0 ; i < tier; i++) printf("	"); 	
	//printf(":::value:%ld\n",value);
	return(value);
}

long evaluate(char *arg){
	//char argt[] = "12*(3^2-456)*78+3+91";	
	//char argt[] = "2 * (2 + 2 * (1+ 3) ) + 3";	
	//printf("\navaluated expression %s = %ld \n",argt,eval(argt,0));
	return(eval(arg,0));
}
