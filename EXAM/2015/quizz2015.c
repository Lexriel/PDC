# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* EXERCICE 1.1 */
int Mallows(int n){
  int a;
  if (n<3)
    return 1;
  a = Mallows(n-2);
  return Mallows(a + Mallows(n-a));
}

/* EXERCICE 1.2 */
/* Le programme suivant affiche 1 2 0 2 5 */
int main(){
  int tab[5] = {1,2,3,4,5};
  int *p, *q, i;

  i = 2; tab[i++] = 0; /* réalise tab[2] = 0 puis i = 3 */
  p = tab; q = p + i - 1; /* q pointe sur &tab[2] */
  *(q+1) = tab[i-1] + (q-p); /* tab[4] = tab[2] + 2 = 2 */

  for (i=0; i<5; i++)
    printf("%d ", tab[i]);
  printf("\n");
  return 0;
}
