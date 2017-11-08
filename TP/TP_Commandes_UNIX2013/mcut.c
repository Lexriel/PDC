# include <stdio.h>
# include <stdlib.h> 
# include "mcu_readl.h"
# include "mcu_fatal.h"
# include "tool.h"
# include "mcu_macros.h"

/* La commande mcut */
int main(int argc, char* argv[]){
  int i, n;
  int ligne[MAXLINE];
  int T[MAXLINE];

  /* erreur de paramètres */
  if ((argc < 3) || (argc > MAXLINE)){
    printf("usage :\n");
    printf("./mcut arg1 arg2 ... argN (avec arg1 le caractère délimiteur et les arguments suivants (optionnels) des numéros de colonnes à conserver (au max %d numéros).\n",MAXLINE);
    exit(EXIT_FAILURE);
  }

  /* On remplit dans T les numéros de colonnes à conserver */
  for(i = 0; i <argc-2; i++)
    T[i] = atoi(argv[i+2]);

  /* coupe chaque ligne du fichier, affiche les colonnes conservées */
  while((n = readl(ligne)) != EOF){
    sup_ensemble_colonnes(*argv[1], ligne, n, T, argc-2);
    for (i=0; (ligne[i]) && (ligne[i] != '\0'); i++)
      putchar(ligne[i]);
    putchar('\n');
  }

  return 0;
}
