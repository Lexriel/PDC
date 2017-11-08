#include "tools.h"
#include "readl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv){
	int len , i, crcol;
	char delim;
	char buf[MAXLINE+1];
	char col[MAXLINE] = {0};
	fatal( (argc > 2) ,"nombre d'arguments incorrect" , EXIT_FAILURE);
	fatal( (strlen(argv[1])==1) , "delimiteur incorrect", EXIT_FAILURE);
	delim = argv[1][0];
	for(i=2;i<argc;i++)
		col[ atoi(argv[i])] = 1;

	while( (len = readl(buf))){
		fatal( (len != -1) , "ligne trop longue", EXIT_FAILURE);
		crcol = 0;
		for(i=0;i<len;i++){
			if(buf[i] == delim){
				crcol++;
				continue;
			}
			if(col[crcol])
				putchar(buf[i]);
		}	
	}
	return EXIT_SUCCESS;
}
