#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

const char * _reg = NULL;

char next_token() {
	char c = getchar();
	char token_value;
	
	token_value = c;

	if ((c==EOF) || (c=='\n')) 
		token=END;
	else {
		switch (c) {
			case '|': token = PIPE; break;
			case '*': token = STAR; break;
			case '(': token = LBRACE; break;
			case ')': token = RBRACE; break;
			case '#': token = DIESE; break;
			default: token = CAR;
		}
	}

	return c;
}

void init_token(const char * s){
	if(s==NULL){
		exit(0);
	}
	_reg = s;
	fprintf(stdout,"chaine = %s\n",_reg);
}
