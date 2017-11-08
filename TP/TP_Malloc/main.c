#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

int main(int argc, char** argv)
{
  int i;
  int *tableau, *tableau2, *tableau3, *save;

  printf("\n-----------TEST MALLOC ET FREE SIMPLE----------- \n");
  tableau = mmalloc(10*sizeof(int));
  imprimerBiblio();
  mfree(tableau);
  imprimerBiblio();

  printf("\n-----------TEST MALLOC ET FREE PLUS COMPLEXE----------- \n");
  tableau =mmalloc(10);
  tableau2 =mmalloc(5);
  tableau3=mmalloc(8);
  imprimerBiblio();

  mfree(tableau3);
  mfree(tableau2);
  imprimerBiblio();
  mfree(tableau);
  imprimerBiblio();


  printf("\n-----------TEST LIBERATION D'UNE ADRESSE INVALIDE----------- \n");

  mfree(0); /*L'adresse 0 a peu de chance d'avoir étais allouée par un malloc */

  printf("\n-----------TEST DEPASSE DE MEMOIRE----------- \n");
  tableau = mmalloc(3);
  tableau[0] = 4;
  mfree(tableau);


  printf("\n-----------TEST CALLOC ET REALLOC-----------\n");


  tableau = mcalloc(30,sizeof(int));
	
  for(i=0;i<=29;i++)
    printf("tableau[%d] : %d\n",i,tableau[i]);
  printf ("\n......Remplissage en cours.....\n\n");
  for(i=0;i<=29;i++)
    tableau[i] = (i+1)*5;
  for(i=0;i<=29;i++)
    printf("tableau[%d] : %d\n",i,tableau[i]);
  imprimerBiblio();
  printf("\nappel a mrealloc pour réduire la taille du tableau a 10 case\n");
  tableau  = mrealloc(tableau,10*sizeof(int));
  for(i=0;i<=9;i++)
    printf("tableau[%d] : %d\n",i,tableau[i]);
  imprimerBiblio();
  printf("\nappel a mrealloc pour augmenter la taille du tableau a 20 cases\n");
  tableau = mrealloc(tableau,20*sizeof(int));
  for(i=0;i<=19;i++)
    printf("tableau[%d] : %d\n",i,tableau[i]);
  imprimerBiblio();
  mfree(tableau);

  printf("\n-----------TEST MALLOPT-----------\n");
  mmallopt(M_MXFAST,10);
  mmallopt(M_NMBLOCKS,50);

  for(i=0;i<=49;i++)
    save = mmalloc(10);
  imprimerBiblio();
  mfree(save);
  imprimerBiblio();
  mmallopt(M_MXFAST,1);
  mmalloc(10);
  mmalloc(10);
  imprimerBiblio();

  exit(EXIT_SUCCESS);
}
