#include "CarreMagique.h"

int
EstMagique
(unsigned int tab[TABSIZE][TABSIZE], unsigned int n) 
{
  unsigned int h,i,j,res ;

  /* v\'erifions que toutes les sommes sont \'egales */

  /* commen\c{c}ont par une diagonale */
  
  for(res=i=0;i<n;i++) 
    res +=tab[i][i] ;

  /* v\'erifions avec l'autre diagonale */
  for(j=i=0;i <n;i++)
    j += tab[n-1-i][i] ;

  if(j!=res) 
    return 1==0 ;

  /* puis les lignes  */
  for(i=0;i<n;i++)
    {
      for(h=j=0;j<n;j++)
	h+=tab[i][j] ; 
      if(h!=res)
	return 1==0 ;
    }
    
  /* puis les colonnes  */
  for(i=0;i<n;i++)
    {
      for(h=j=0;j<n;j++)
	h+=tab[j][i] ; 
      if(h!=res)
	return 1==0 ;
    }

  /* v\'erifions que tous les nombre de 1 \`a n^2 sont pr\'esents */
  /* soit on fait du malloc 
     int * complement = (int *) malloc(sizeof(int)*n*n) ;
     for(i=0;i<n*n;i++)
       complement[i]=0 ;
     for(i=0;i<n;i++)
       for(j=0; j<n; j++)
          complement[tab[i][j]] = 1 ;
   
     for(j=1,i=0;i<n*n;i++)
         j = j || complement[i] ;

     if(!j)
        return 1==0 ;

     soit on ne fait pas du malloc et on met de la complexit\'e pour compenser l'espace
   */
  for(res=h=0;h<n*n ; h++) 
    {
      for(i=0 ;i<n ;i++)
	for(j=0 ;j<n; j++)
	  if(tab[i][j] == h+1)
	    res++ ;
    }
  if(res!=n*n)
    return 1==0 ;
	
  
  return 1==1 ;
}
