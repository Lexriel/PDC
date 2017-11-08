#include<stdio.h>

int main(void){

	int i, tab[10] ;

	int *tmp = (int *) (2 + (char *) tab) ;
	
	for(i=0 ; i<10 ; i++)
		*(tmp++) = 2*i ;

	tmp = (int *) (2 + (char *) tab) ;

	for(i=0;i<10;i++)
		printf("%d %d\n",tab[i],tmp[i]) ;
	
	return 0 ;
}
