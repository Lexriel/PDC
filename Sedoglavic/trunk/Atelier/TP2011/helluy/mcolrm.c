#include "tools.h"
#include "readl.h"
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char**argv){
	int min , max, len , i;
	char buf[MAXLINE+1];
	fatal( (argc>1 && argc < 4) ,"nombre d'arguments incorrect" , EXIT_FAILURE);
        min = atoi(argv[1]);
	if(argc==3)
		max = atoi(argv[2]);
	else 
		max = MAXLINE;
	fatal( (min < max) , "arguments incorrects", EXIT_FAILURE);

	while( (len = readl(buf))){
		fatal( (len != -1) , "ligne trop longue", EXIT_FAILURE);
		for(i=0;i<min-1;i++)
			putchar(buf[i]);
		for(i=max;buf[i];i++)
			putchar(buf[i]);
	}
	return EXIT_SUCCESS;
}
