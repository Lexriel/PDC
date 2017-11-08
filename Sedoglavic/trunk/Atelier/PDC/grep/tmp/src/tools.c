#include<stdio.h>
#include<stdlib.h>
#include"tools.h"

extern void fatal(int assert, const char *message, int status){
	if((assert!=0))
		exit(status);
	else{
		fprintf(stderr,"%s",message);
		exit(status);
	}
}

