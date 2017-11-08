#include "dico4lettres.h"
/* Cette procedure prend en argument deux chaines de caracteres 
   Elle renvoit 1 si les chaines ne different que par un caractere et 0 sinon */

int estSuccesseur(char a[4], char b[4]){

  int i,diff ;

  diff = 0 ;
  for(i=0;i<4;i++)
    if(a[i]-b[i]!=0)
      diff++ ;

  if (diff<2)
    return 1 ;
    
  return 0 ;
}

void CreeMatriceAdjacence(int **mat){

  int i,j ;

  // on parcours tous les mots du dictionnaires
  for(i=0; i<taille_dico;i++) 
    /* Pour chaque mots, on compare avec tout les autres mots pour savoir si ce 
       sont des successeurs. */
    for(j=i; j<taille_dico;j++) // la matrice d'incidence est symetrique
      mat[i][j]=estSuccesseur(dico[i],dico[j]) ;

 // il faut donc terminer par remplir le reste de la matrice
 for(i=1;i<taille_dico;i++)
         for(j=0;j<i;j++)
                 mat[i][j]=mat[j][i] ;
}
 
