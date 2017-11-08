#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(void){
  char * str = (char *) malloc(100);

  printf("%c\n",233) ;
  printf("Saisissez votre phrase~:") ;
  scanf("%s",str) ;

  printf(" Votre chaine \n %s \n",str) ;
  while(*str!=0) 
    printf("%d ",*(str++)) ;

  return 0 ;
}
 
