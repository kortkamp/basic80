#include "error.h"

// Error code.
int error;
// Line in which error ocurred.
int error_line;
// Error message.

char error_msg[6][30]= {
	"",
	"Division by zero error",
	"Math error",
	"Syntax Error",
	"Next without for error",
	"File Error"
};
	
		
