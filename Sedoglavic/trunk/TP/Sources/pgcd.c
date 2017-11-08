#include <stdio.h>
 
int main (void) {
	int  A ;
	int  B ;
	int  R ;

	printf("Entrer A => ");
	scanf("%d",&A) ;
	printf("Entrer B => ");
	scanf("%d",&B) ; 

	while (B != 0) {
		R = A % B ;
		A = B ;	
		B = R ;
	} 

	printf("Le pgcd est %d\n",A) ;
	return 0 ;
}



 
