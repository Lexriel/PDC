#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define Max 1000

void 
eratosthene
(int *tab)
{

  int i,j ;

  /* Initialisation du tableau des entiers */
  for (i=0; i<Max; i++) 
    tab[i]=i+2 ;
  
  /* Determination des multiples */

  for(i = 0 ; i<Max; i++)
    if (tab[i]!=0){
      for(j = 2 ;tab[i]*j-2<Max;j++) 
	tab[tab[i]*j-2]=0 ;
    }
  /* chaque cellule de tab contient soit 0 soit un nombre premier */
}

int 
main
(void)
{

  int *tab=(int *) malloc(Max*sizeof(int)) ; 
                 /* pour stocker les nombres premiers et utiliser le 
                   crible d'Eratosthene */
  int i ;

  eratosthene(tab) ;

   FILE *fd = fopen("listeNbPremier","w") ;
   if (fd==NULL){ 
     perror("L'erreur suivante est survenue") ;
     return -1 ;
   }

  /* Sauvegarde des nombres premiers */
  for(i=0; i<Max; i++) 
    if (tab[i]!=0)
      fprintf(fd,"%d\n",tab[i]) ;

   fclose(fd) ;
   return 0 ;
}

 
