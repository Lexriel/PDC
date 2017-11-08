#include<stdio.h>
#include<stdlib.h>

char *int2string(int i){
  
  int d=1, l=1 ;
  while(i%d!=i) {
    l++ ;
    d*=10 ;
  }

  char *res = (char *) malloc(l*sizeof(char)) ;
  
  int j = 0 ;

  while(i!=0){
    d/=10 ;
    *(res+j++) = i/d +'0' ;
    i -= d*(i/d) ;
  }
  
  *(res+j) = 0 ;
  return res ;
}

int main(void){

  int i ;
  printf("Entrez un entier ");
  scanf("%d",&i);

  printf("Le r\\'esultat est %s\n",int2string(i)) ;
  return 0 ;
}
 
