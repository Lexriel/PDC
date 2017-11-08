# include <stdlib.h>
# include <stdio.h>

/* ===========================================================
   =            Fonction factorielle itérative               =
   =========================================================== */

unsigned int factorielle_tantque(unsigned int n){
  unsigned int res = 1;
  while (n>1)
    res *= n--;
  return res;
}

unsigned int factorielle_jusqua(unsigned int n){ /* n != 0 */
  unsigned int res = 1;
  do
    res *= n--;
  while (n>1);
  return res;
}

unsigned int factorielle_for(unsigned int n){
  int res = 1, j;
  for (j=n; j>1; j--)
    res *= j;
  return res;
}

/* ===========================================================
   =            Fonction factorielle récursive               =
   =========================================================== */

unsigned int factorielle_recu(unsigned int n){
  if (n<=1)
    return 1;
  else
    return n * factorielle_recu(n-1);
}

unsigned int factorielle_recu_case(unsigned int n){
  switch(n){
  case 0 ... 1:
    return 1;
  default:
    return n * factorielle_recu_case(n-1);
  }
}

unsigned int factorielle_recu_expr(unsigned int n){
  return (n <= 1) ? 1 : n * factorielle_recu_expr(n-1);
}

/* ===========================================================
   =                           MAIN                          =
   =========================================================== */

int main(){
  int n, res;
  printf("Donner un entier : ");
  scanf("%d", &n);
  res = factorielle_recu_case(n);
  printf("%d! = %d\n", n, res);

  exit(EXIT_SUCCESS);
}
