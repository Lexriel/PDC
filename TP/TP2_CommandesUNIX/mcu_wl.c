# include <stdio.h>
# include <stdlib.h>
# include "mcu_affiche_entier.h"
# include "mcu_readl.h"
# include "mcu_fatal.h"
# include "mcu_macros.h"

int main(int argc, char *argv[]){
  int wl;
  int line[MAXLINE+1];
  wl = 0; /* number of lines */

  while (readl(line) != EOF)
    wl++;

  affiche_entier(wl);
  putchar('\n');
  return 0;
}
