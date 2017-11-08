# include <stdio.h>

/* Cette fonction permute a et b quels que soient leur types. */
extern void permuter(void *a, void *b, int size)
{
  char *copy_a, *copy_b;
  int i;
  char tmp;
  copy_a = a;
  copy_b = b;
  for(i=0; i<size; i++){
    tmp = *copy_a;
    *copy_a = *copy_b;
    *copy_b = tmp;
    copy_a++;
    copy_b++;
  }
}

/* Fonction faisant partie du quicksort. */
extern int partitionner(void *base, int size, int premier, int dernier, int pivot, int (*compar) (const void *,const void *))
{
  int i, j;
  char *base1, *base2;
  base1 =(((char *)base) + pivot*size);
  base2 =(((char *)base) + dernier*size);
  permuter(base1, base2, size);
  j = premier;
  for (i=j; i<dernier; i++){
    base1 = (((char *)base) + i*size);
    base2 = (((char *)base) + dernier*size);
    if ( (*compar) (base2, base1) >= 0 ){
      base1 = (((char *)base) + i*size);
      base2 = (((char *)base) + j*size);
      permuter(base1, base2, size);
      j++;
    }
  }
  base1 = (((char *)base) + dernier*size);
  base2 = (((char *)base) + j*size);
  permuter(base1, base2, size);
  return j;
}

/* Fonction quicksort. */  
extern void my_qsort(void *base, int size, int premier, int dernier, int (*compar) (const void *,const void *))
{
  int pivot;
  if (premier < dernier){
    pivot = premier; /* choix aléatoire d'un pivot dans [premier; dernier] */
    pivot = partitionner(base, size, premier, dernier, pivot, compar);
    my_qsort(base, size, premier, pivot-1, compar);
    my_qsort(base, size, pivot+1, dernier, compar);
  }
}

/* Fonction appelante du quicksort, va trier un tableau base ayant
   nelem éléments selon la fonction de comparaison compar. La taille
   du type des données est de taille size. */
extern void quicksort(void *base, int nelem, int size, int (*compar) (const void *,const void *))
{
  my_qsort(base, size, 0, nelem-1, compar);
}
