
#include<stdio.h>
#include<stdlib.h>

int main(void){

	int n,j,i;
	int **tab ;

	printf("Entrez la taille du carr\\'e magique => ");
	scanf("%d",&n) ;

	if (n%2==0){
		printf("Je ne sais pas faire avec une taille impair\n") ;
		return 1 ; 
	}

	/* on r\'eserve de la m\'emoire */
	tab = (int **) malloc(sizeof(int *)*(2*n-1)) ;

	for(i=0;i<2*n-1;i++)
		*(tab+i) = (int *) malloc(sizeof(int)*(2*n-1)) ;

	/* On commence par remplir les diagonales */

	for(i=0;i<n*n;i++)
		tab [i%n+i/n] [n-1-i/n+i%n] = i+1 ;

	for(i=0;i<2*n-1;i++){
	for(j=0;j<2*n-1;j++)
		printf("%3d ",*(*(tab+i)+j)) ;
	printf("\n") ;
	}
	return 0 ;
}
 
