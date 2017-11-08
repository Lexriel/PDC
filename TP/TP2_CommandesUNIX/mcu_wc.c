# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include "mcu_affiche_entier.h"

int main(int argc, char *argv[]){
  int wc, c;
  wc = 0; /* number of characters */

  while ((c = getchar()) != EOF)
    wc++;

  affiche_entier(wc);
  putchar('\n');
  return 0;
}
