#include<stdio.h>
#include<stdlib.h>
#include"readl.h"
#include"tools.h"

extern int readl(char line[]){

	/*fgets(line, MAXLINE, stdin);
	*/
		int i=-1;

	do{
		i++;
		line[i] = getchar();
	}while(line[i] != EOF && line[i] != '\n');
	line[i] = '\0';

	return 0;
}

/*int main(){
	char tmp[MAXLINE];

	readl(tmp);
	fprintf(stdout,"%s",tmp);
	
	return 0;
}*/
