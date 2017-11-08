#include <stdio.h>

void Hanoi(int,int,int);

int main(void){
  int disque ;
  printf("Combien de disque sur le premier piquet ?") ;
  scanf("%d",&disque) ;
  Hanoi(disque,1,3) ; 
  return 0 ;
}

void Hanoi(int n, int i, int j){
  if (n>0) {       
    Hanoi(n-1,i,6-(i+j))  ;
    printf("%d --> %d\n",i,j) ;     
    Hanoi(n-1,6-(i+j),j)  ;
  }
}
 
