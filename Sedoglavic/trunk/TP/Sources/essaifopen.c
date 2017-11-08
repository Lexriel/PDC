#include <stdio.h>
#include <errno.h>

int main(){

   FILE *fd = fopen("fichierquinexistepas","r") ;
   if (fd==NULL){ 
     perror("L'erreur suivante est survenue") ;
     return -1 ;
   }

   fclose(fd) ;
   return 0 ;
}
 
