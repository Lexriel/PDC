#include <stdio.h>
char tab[3][4] = {"123","456","789"} ;
char *foo=NULL;
char bar=0 ;
int main(){
	foo = *(tab+1) ;
	bar = *(*(tab+2)) ;
	bar = foo[2] ;
	return 0 ;
}
