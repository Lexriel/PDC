# include <stdio.h>
# include <stdlib.h>
# include "mcu_affiche_entier.h"
# include "mcu_readl.h"
# include "mcu_fatal.h"
# include "mcu_macros.h"


int sont_identiques(int line1[], int n1, int line2[], int n2){
  int i;
  /* si les lignes n'ont pas la même taille, on retourne faux */
  if (n1 != n2)
    return 0;
  /* on compare les caractères deux à deux et retourne faux si on en
     trouve deux distincts */
  for (i=0; i<n1; i++)
    if (line1[i] != line2[i])
      return 0;
  /* les deux chaînes sont identiques, on retourne vrai */
  return 1;
}


int main(int argc, char *argv[]){
  int i, n1, n2;
  int comp_line[MAXLINE+1];
  int new_line[MAXLINE+1];
  comp_line[0] = '\0';
  n1 = 0;
  while ((n2 = readl(new_line)) != EOF){
    /* Les lignes sont différentes */
    if (! sont_identiques(comp_line, n1, new_line, n2)){
      comp_line[n2] = '\0';
      n1 = n2;
      for (i=0; i<n2; i++){
	putchar(new_line[i]);
	comp_line[i] = new_line[i];
      }
      putchar('\n');
    }
  }
  
  return 0;
}
