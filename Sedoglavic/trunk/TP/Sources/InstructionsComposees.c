
#include <stdio.h>

char foo = 'c' ;

int main(void){
  printf(" %c \n",foo) ;

  char foo = 'a' ;
  printf(" %c \n",foo) ;

  {
  char foo = 'b' ;
  printf(" %c \n",foo) ;
  }

  printf(" %c \n",foo) ;
  
  return 0 ;
}
 
