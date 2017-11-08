/* lefils valentin */
#include <stdlib.h>
#include <stdio.h>
#include "triABulle.c"
#include "swap.c"

#define TABSIZE 100

void int_sort(int tab[], int size){
  int x,m,d,tmp,i;
 

  if (size<=4){
    triAbulle(tab,size);
  }
  else{
    x=0;
    m=1;
    d=size-1;
    while (m<d){
      while (m<size && tab[m]<tab[x]){
	m++;
      }
      while (d>0 && tab[x]<=tab[d]){
	d--;
      }

      if (d<=m) break;
      swap(&tab[d],&tab[m],4);
    }
    swap(&tab[d],&tab[x],4);
    int_sort(tab,d);
    int_sort(&tab[d+1],size-d-1);
  }
}

int main(){
  int tab[TABSIZE];
  int i;

  printf("-------------------------\n");
  srand(time(NULL));
  for(i=0;i<TABSIZE;++i){
    tab[i]=rand()%2000;
    printf("%d\n",tab[i]);
  }

  printf("-------------------------\n");
  int_sort(tab,TABSIZE);
  
  for(i=0;i<TABSIZE;++i){
    printf("%d\n",tab[i]);
  }

  return 0; 
}
