#ifndef _VAR_H
#define _VAR_H

#include "basic.h"
#include "error.h"
#include "math.h"
#include <stdio.h>

// A var must be identified by its first two letters.
float var[26][26+17];
void clear_vars();
float get_var(char*);
float *set_var(char*,float);
int test_attribution(char*);
float *exec_attribution(char*);
float *get_var_pointer(char*);

#endif
