#ifndef _ERROR_H_
#define _ERROR_H_

	#define NORMALOPERATION	0
	#define DIVBYZERO	1
	#define MATHERROR	2
	#define SYNTAXERROR	3
	#define NEXTERROR	4

	// Global error vars.
	
	// Error code.
	int error;
	// Line in which error ocurred.
	int error_line;	
	// Error message.
	char  error_msg[5][30];
#endif
