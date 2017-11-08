#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABSIZE 1457

/* Comme pivot, on a le choix entre la premi\`ere et la derni\`ere case du tableau */
#define PIVOT size-1 /* 0  */

/* Ce choix conditionne le code */
#if PIVOT==0
#define INSERTPLACE descendant
#else
#define INSERTPLACE montant
#endif

/* Quelques fonctions auxiliaires  en fin de  fichiers */
void affichetab(int *,int);
int IsSorted(int *tab,int);
int compar(int,int);

void 
quicksort_int
(int tab[], unsigned int size)
{
  int temp ;
  int montant,descendant;

  if(size<=1)
    return ;

  montant=-1; 
  descendant=size-1;

#if PIVOT==0
    montant++;
    descendant++ ;
#endif

  while(1)
    {

      do 
	  montant ++ ;
      while(compar(tab[montant],tab[PIVOT])<=0 && montant < size
#if !(PIVOT==0)
	      -1
#endif
	    )  ;

      do 
	  descendant -- ;
      while(compar(tab[descendant],tab[PIVOT])>0 && descendant  > 0
#if !(PIVOT==0)
	   -1
#endif
	    )  ;
      
      if (montant >= descendant)
	break ;

      temp=tab[descendant];
      tab[descendant]=tab[montant];
      tab[montant]=temp;
    }

  temp             = tab[INSERTPLACE] ;
  tab[INSERTPLACE] = tab[PIVOT]       ;
  tab[PIVOT]       = temp             ;

  quicksort_int(tab,INSERTPLACE) ;
  quicksort_int(tab+INSERTPLACE+1,size-INSERTPLACE-1);

  return ;
}

int
main
(void)
{
  int i, tab[TABSIZE];

  srand(time(NULL));

  for(i=0;i<TABSIZE;i++)
    tab[i]=rand();

  quicksort_int(tab,TABSIZE);

  if (IsSorted(tab,TABSIZE))
    return 0;

  return 1 ;
}


void
affichetab
(int * tab, int size)
{
  int i ;
  for(i=0;i<size;i++)
    printf("%d, ",tab[i]);
  printf("\n");
  return ;
}

int
IsSorted
(int *tab, int size)
{
  if(size<2)
    return 1 ;
  
  for(size--;size>0;size--) 
    if (tab[size]<tab[size-1])
      return 0 ;
  return 1 ;
}

Int
compar
(int x,int y)
{
  return x-y ;
}
