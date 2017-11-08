# include <stdio.h>
# include <stdlib.h>
# include "structNobel.h"

int main(int argc, char *argv[])
{
  int n;
  Nomine nobels[TABSIZE];

  n = ConstruireTableaux(nobels);
  printf("nombre de champs : %d\n\n", n);

  afficheNomine(nobels[0]);
  putchar('\n');
  afficheNomine(nobels[1]);
  putchar('\n');
  afficheNomine(nobels[700]);
  putchar('\n');
  printf("Comparaison par date de naissance entre les nobels 4 et 16 du fichier :\n %d\n", CompareNomineParDateDeNaissance(&nobels[4], &nobels[16]));
  return 0;
}
