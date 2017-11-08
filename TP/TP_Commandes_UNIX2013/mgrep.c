# include <stdio.h>
# include <stdlib.h>
# include <string.h> 
# include "mcu_readl.h"
# include "mcu_fatal.h"
# include "tool.h"
# include "mcu_macros.h"

/* commande mgrep */
int main(int argc, char* argv[]){
  int n, i;
  int ligne[MAXLINE];
  int mot[MAXLINE];

  /* erreur de paramètres */
  if(argc != 2){
    printf("usage :\n");
    printf("./mgrep arg (avec arg le mot à rechercher). \n");
    exit(EXIT_FAILURE);
  }

  /* définition du mot */
  for (i=0; i<strlen(argv[1]); i++)
    mot[i] = argv[1][i];
  mot[i] = '\0';

  /* recherche d'argv[1] dans la ligne */
  while((n = readl(ligne)) != EOF){
    if(mon_strstr(ligne, mot) != NULL){
      for (i=0; i<n; i++)
    	putchar(ligne[i]);
      putchar('\n');
    }
  } 

  return 0;
}
