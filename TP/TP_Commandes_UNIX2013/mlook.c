# include <stdio.h>
# include <stdlib.h>
# include <string.h> 
# include "mcu_readl.h"
# include "mcu_fatal.h"
# include "tool.h"
# include "mcu_macros.h"

/* commande mlook */
int main(int argc, char* argv[]){
  int n, i;
  int ligne[MAXLINE];
  int mot[MAXLINE];
  int *debut;

  /* On s'assure qu'on a donné le bon nombre d'arguments à la commande mlook */
  if (argc != 2){
    printf("usage :\n");
    printf("./mlook arg (avec arg le mot à rechercher en début de ligne).\n");
    exit(EXIT_FAILURE);
  }

  /* définition du mot */
  for (i=0; i<strlen(argv[1]); i++)
    mot[i] = argv[1][i];
  mot[i] = '\0';

  /* recherche d'argv[1] dans la ligne */
  while((n = readl(ligne)) != EOF){
    debut = mon_strstr(ligne, mot);
    if(debut == ligne){ /* le mot est au début de la ligne */
      for (i=0; i<n; i++)
    	putchar(ligne[i]);
      putchar('\n');
    }
  }

  return 0;
}
