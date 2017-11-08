#include <stdio.h>

int main(void){

  unsigned char bar = 'a' + 127 ;
  char foo = bar+256 ;

  printf("Le charact\\`ere %c correspond \\`a l'entier %d.\n",bar,(int) bar) ;
  printf("Le charact\\`ere %c correspond \\`a l'entier %d.\n",foo,(int) foo) ;

  return 0 ;
}
 
