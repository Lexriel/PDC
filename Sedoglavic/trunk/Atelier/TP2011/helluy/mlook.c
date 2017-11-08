#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readl.h"
#include "tools.h"

int main(int argc,char**args){
	char buf[MAXLINE] ;
	size_t len_w;
	fatal( (argc == 2) ,"usage: mlook word" , EXIT_FAILURE);
	len_w = strlen(args[1]);
	while(readl(buf)>=0)
		if(!strncmp(args[1],buf,len_w))
			puts(buf);
	return EXIT_SUCCESS;
}
