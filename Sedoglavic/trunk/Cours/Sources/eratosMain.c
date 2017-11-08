#include <stdio.h>
#include "eratosthene.h"

void init (void) ;
int min_is_candidate(void) ; 
void set_non_prime(int) ;
int prem[N];
int main() {
     register int next_prime = 1, i;
     init();
     while (next_prime * next_prime < N) {
     next_prime = min_is_candidate();
     prem[next_prime]=IS_PRIME;
     set_non_prime(next_prime);
     }
     printf("Liste des nombres premiers inf\\'erieurs \\`a %d\n", N);
     for (i = 0; i < N; i++)
       if (prem[i] != IS_NON_PRIME) printf("%d ", i);
     printf("\n") ; 
     return 0 ;
   }
