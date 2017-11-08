#include <stdio.h>

int convertion(char *txt){

	int res = 0 ;

	for(;*txt!=0;txt++)
		res = 10*res + (*txt-48) ;

	return res ;
}

int main (int argc, char ** argv){

  printf("%d\n",convertion(*(argv+1))) ;

  return 1 ;
}

 
