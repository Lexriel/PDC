# include <stdio.h>
# include <stdlib.h>

/* Cette fonction affiche un tableau d'entiers. */
extern void afficherTableauInt(char nom[], int T[],unsigned int n)
{
  int i;
  printf("%s = ", nom);
  for(i=0 ; i<n; i++)
    printf("%d, ", T[i]);
  printf("\n");
}

/* Cette fonction permute deux entiers. */
extern void permuter_int(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

/* Fonction faisant partie du quicksort_int. */
extern int partitionner_int(int T[], int premier, int dernier, int pivot)
{
  int i, j;
  permuter_int(&T[pivot], &T[dernier]);
  j = premier;
  for (i=j; i<dernier; i++){
    if (T[i] <= T[dernier]){
      permuter_int(&T[i], &T[j]);
      j++;
    }
  }
  permuter_int(&T[dernier], &T[j]);
  return j;
}

/* Fonction quicksort_int. */  
extern void qsort_int(int T[], int premier, int dernier)
{
  int pivot;
  if (premier < dernier){
    pivot = premier; /* choix aléatoire d'un pivot dans [premier; dernier] */
    pivot = partitionner_int(T, premier, dernier, pivot);
    qsort_int(T, premier, pivot-1);
    qsort_int(T, pivot+1, dernier);
  }
}

/* Fonction appelante du quicksort_int, va trier un tableau d'entiers
   T de taille n. */
extern void quicksort_int(int T[], int n)
{
  qsort_int(T, 0, n-1);
}

/* Cette fonction affiche un tableau d'entiers T avant et après appel
   de quicksort_int. */
extern void test_quicksort_int(char nom[], int T[], int n)
{
  afficherTableauInt(nom, T, n);
  quicksort_int(T, n);
  afficherTableauInt(nom, T, n);
}
