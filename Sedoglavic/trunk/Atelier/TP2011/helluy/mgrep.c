#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readl.h"
#include "tools.h"

int main(int argc,char**args){
	char buf[MAXLINE] ;
	size_t len_w;
	int i, lu;
	char found;
	fatal( (argc == 2) ,"usage: mgrep word" , EXIT_FAILURE);
	len_w = strlen(args[1]);
	while((lu=readl(buf))>0){
		found = i = 0;
		do {
			while(buf[i] != args[1][0] && (i+len_w)<=lu)
				i++;
			if(!strncmp(args[1],buf+i,len_w))
				found = 1;
		} while(!found && (i+len_w)<=lu);
		if(found)
			printf("%s",buf);
	}
				
	return EXIT_SUCCESS;
}
