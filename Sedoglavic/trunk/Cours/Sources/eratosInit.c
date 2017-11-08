#include "eratosthene.h"

extern int prem [N] ;

void init (void) {
  register int i;
  prem[0]=prem[1]=IS_PRIME;
  for (i = 2; i < N; i++) 
    prem[i] = IS_CANDIDATE;
}
