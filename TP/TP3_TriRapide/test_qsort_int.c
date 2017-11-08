# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include "quicksort_int.h"
# include "quicksort.h"
# include "structNobel.h"
# include "readl.h"
# include "fatal.h"
# include "macros.h"

/* Cette fonction compare deux entiers. */
int comparEntiers(const void *n1, const void *n2)
{
  int a, b;
  a = *((int *) n1);
  b = *((int *) n2);
  return a - b;
}

/* Cette fonction affiche un tableau d'entiers avant et après un
   quicksort. */
void  test_quicksort_int2(char nom[], int T[], int n)
{
  afficherTableauInt(nom, T, n);
  quicksort(T, n, sizeof(int), &comparEntiers);
  afficherTableauInt(nom, T, n);
}

int main(int argc, char *argv[])
{
  int i, n;
  /* Définition des tableaux de test */
  int T1[TABSIZE];
  int T2[TABSIZE];
  
  n = TABSIZE;
  if (argc != 1)
    n = atoi(argv[1]);
  /* Remplissage des tableaux T1 et T2 aléatoirement */
  srand(time(NULL));
  for(i=0; i<n; i++)
    T1[i] = rand() % 100;
  for(i=0; i<n; i++)
    T2[i] = T1[i];

  /* Tests */
  printf("T1 avant et après le quicksort_int:\n");
  test_quicksort_int("T1", T1, n);
  printf("T2 avant et après le quicksort générique:\n");
  test_quicksort_int2("T2", T2, n);

  return 0;
}
