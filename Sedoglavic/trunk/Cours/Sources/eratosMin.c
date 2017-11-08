#include "eratosthene.h"
extern int prem [N] ;
   int min_is_candidate(void) {
     register int i = 0;
     while (prem[i] != IS_CANDIDATE) i++;
     return i;
   }

