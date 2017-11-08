#include "readl.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
extern int readl(char * line){
	unsigned char c;
	int len;
	len = 0;
	do {
		c = getchar();
		line[len++] = c;
		fatal( (len < MAXLINE) , "len >= MAXLINE" , EXIT_FAILURE);
	} while(c != '\0' && c != '\n' && c!=0xff);
	if(c == 0xff)
		return 0;
	line[len] = '\0';
	return len;
}
