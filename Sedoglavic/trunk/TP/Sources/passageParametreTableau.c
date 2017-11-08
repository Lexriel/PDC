#include<stdio.h>

void fct(char tab[]){
  tab[11] = 'm' ;
  tab[12] = 'o' ;
  tab[13] = 'c' ;
  tab[14] = 'h' ;
  tab[15] = 'e' ;
}

int main(void){

  char tab[] = "La vie est belle" ;

  unsigned int i = 0 ;

  fct(tab) ;

  do{
    putchar(tab[i++]);
  } while(tab[i]) ;

  putchar('\n') ;

  return 0 ;
}
