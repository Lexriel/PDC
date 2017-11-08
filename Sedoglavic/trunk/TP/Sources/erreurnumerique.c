#include "erreurnumerique.h"

int
compar
(const void *a, const void *b)
{
	return *((float *)a)<*((float *)b) ;
}

int 
main
(void)
{
  int i;
  float res=0;
  float tab[N];
  srand((unsigned int) time(NULL));
  for (i=0; i<N; i+=4)
    {
      tab[i]=rand()%VB;
      tab[i+1]=rand()%S;
      tab[i+2]=rand()%A;
      tab[i+3]=rand()%B;
    }
  for (i=0; i<N; i++)
    res+=tab[i];
  printf("Result before sorting\n%f\n",res);
  qsort(tab,N-1,sizeof(float),compar );
  for (res=0,i=0; i<N; i++)
    res+=tab[i];
  printf("Result after sorting\n%f\n",res);
  return 0;
}
