#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void){

  int i ;

   FILE *fd = fopen("listeNbPremier","r") ;
   if (fd==NULL){ 
     perror("L'erreur suivante est survenue") ;
     return -1 ;
   }

  /* Lecture des nombres premiers */
   while(!feof(fd)){
     fscanf(fd,"%d",&i) ;
     printf("%d\n",i) ;
   }
   
   fclose(fd) ;
   return 0 ;
}

 
