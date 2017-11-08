#include<stdio.h>

int main(void){

	int X, A, C ;

	X=12 ; A = 20 ; C = -10 ;
	printf("%d \n", 5*X+2*3*C+4) ;
	X=12 ; A = 20 ; C = -10 ;
	printf("%d %d\n", X, X++*(A+C)) ;
	X=12 ; A = 20 ; C = -10 ;
	printf("%d %d\n", X, ++X*(A+C)) ;
	X=12 ; A = 20 ; C = -10 ;
	printf("%d %d %d\n", X, A, X=A++) ;
	X=12 ; A = 20 ; C = -10 ;
	printf("%d %d %d\n", X, A, X=++A) ;
	X=12 ; A = 20 ; C = -10 ;
	printf("%d %d %d\n", X, A, X==(A=5)) ;
			
	return 0 ;
}
