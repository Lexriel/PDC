#include <stdio.h>

int main(void){
     int op1, op2 ;
     
     printf("Entrez le premier entier ") ;
     scanf("%d",&op1) ;
     printf("Entrez le second entier ") ;
     scanf("%d",&op2) ;
     
     printf("Le plus grand est %d\n", plusgrand(op1,op2)) ;

     return 0 ;
}
 
