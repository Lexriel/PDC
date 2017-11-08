#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

extern void fatal(int assert, const char *message, int status){
	if(assert)
		return;
	fprintf(stderr,"%s\n",message);
	exit(status);
}

