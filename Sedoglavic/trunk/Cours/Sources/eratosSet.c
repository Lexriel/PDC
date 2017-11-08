#include "eratosthene.h"
extern int prem [N] ;

   void set_non_prime(int start) {
     register int i = start + 1;
     for (;i < N; i = i + 1)
      if (i % start == 0) prem[i]=IS_NON_PRIME;
   }
