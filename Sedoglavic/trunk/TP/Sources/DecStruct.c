#include<stdio.h>

int main(void){
	typedef struct complexe {
		int re ;
		int im ;
	} complexe ;

	struct complexe nombre = { .re = 1, .im = 1} ;

	{
	  int toto = 3 ;	
	}
	printf(" %d %d \n",nombre.re,nombre.im) ;
	
	return 0 ;
}
 
