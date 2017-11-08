#include <stdio.h>

#define Max 1000

int main(void){

  int tab[Max] ;
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

  /* Affichage des nombres premiers */
  for(i=0; i<Max; i++) 
    if (tab[i]!=0)
      printf("%d\n",tab[i]) ;

  return 0 ;
}
 
