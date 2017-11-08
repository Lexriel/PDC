#include <stdio.h>

int main(){

  FILE * foo ;

  foo = fopen("structureFILE.c","r") ;
  
  if (foo==NULL) {
    printf("Erreur lors de l'ouverture du fichier\n") ;
    return -1 ;
  }

  printf("fichier numero : %d\n",foo->_fileno) ;
  printf("taille du bloc : %d\n",foo->_blksize) ;

  fclose(foo) ;

}
 
