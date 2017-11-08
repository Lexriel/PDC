#include <stdio.h>
#include "mcu_macros.h"
#include "mcu_fatal.h"
#include "mcu_readl.h"
#include "mcu_affiche_entier.h"

int main(){
  int line[MAXLINE];
  int i,j;
  /* on affiche une ligne de l'entrée standard */
  i = readl(line);
  j=0;
  while(line[j]) putchar(line[j++]) ;
  putchar('\n');
  /* on fait un affichage */
  affiche_entier(i);
  putchar('\n');
  /* on termine par un problème */
  fatal(1==1,"1==1 is true\n",2);
  return 0;
}
