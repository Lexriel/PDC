#include <stdio.h>

int main(void){

   char foo = 'a' ;

   printf("le premier argument %c et le second %c\n",foo,foo++) ;

   char bar = 'a' ;

   printf("le premier argument %c et le second %c\n",bar,++bar) ;

   return 0 ;
}
 
