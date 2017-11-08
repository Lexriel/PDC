# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include "quicksort.h"
# include "structNobel.h"
# include "readl.h"
# include "fatal.h"
# include "macros.h"

int main(int argc, char *argv[])
{
  int i, n;
  Nomine nobels[TABSIZE];

  /* Test */
  n = ConstruireTableaux(nobels);
  quicksort(nobels, n, sizeof(Nomine), &CompareNomineParDateDeNaissance);
  for (i=0; i<n; i++)
    afficheNomine(nobels[i]);

  return 0;
}
