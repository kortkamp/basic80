#ifndef _VAR_H
#define _VAR_H

#include "error.h"
#include "math.h"
#include <stdio.h>

// A var must be identified by its first two letters.
long var[26][26];
void clear_vars();
long get_var(char*);
int set_var(char*,long);
int test_attribution(char*);
int exec_attribution(char*);


#endif
