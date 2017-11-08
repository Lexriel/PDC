# include <stdio.h>
# include <stdlib.h> 
# include "mcu_readl.h"
# include "mcu_fatal.h"
# include "tool.h"
# include "mcu_macros.h"

/* La commande mcolrm */
int main(int argc, char* argv[]){
  int i, m, n;
  int ligne[MAXLINE];

  /* erreur de paramètres */
  if((argc != 2) && (argc != 3)){
    printf("usage :\n");
    printf("./mcolrm arg1 arg2 (avec arg1 numéro de la colonne à supprimer et arg2 nombre de colonnes à supprimer à partir de arg1 (optionnel)).\n");
    exit(EXIT_FAILURE);
  }

  /* nombre de colonnes à supprimer, vaut 1 par défaut */
  m = (argc != 3) ? 1 : atoi(argv[2]);

  /* suppression des colonnes */
  while((n = readl(ligne)) != EOF){
    sup_colonne(atoi(argv[1]), m, ligne, n);
    for (i=0; (ligne[i]) && (ligne[i] != '\0'); i++)
      putchar(ligne[i]);
    putchar('\n');
  }

return 0;
}
