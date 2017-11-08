/* lefils valentin */
#include <stdlib.h>
#include <stdio.h>
#include "swap.c"
#include "triABulleGen.c"

#define TABSIZE 100
 



void quicksort(void *base, int nelem, int size,int(*compar)(const void *, const void *)){
  int x,m,d,i;

  if (nelem<=4){
    triABulleGen(base,nelem,size,compar);
  }
  else{
    x=0;
    m=1;
    d=nelem-1;
    while (m<d){
      while (m<nelem && compar(base+m*size,base)<0){
	m++;
      }
      while (d>0 && compar(base,base+d*size)<=0){
	d--;
      }
      if (d<=m) break;
      swap(base+m*size,base+d*size,size);
    }
    swap(base+d*size,base+x*size,size);
    quicksort(base,d,size,compar);
    quicksort(base+(d+1)*size,nelem-d-1,size,compar);
  }
}
  

int compare_int(const void *a,const void *b){

  return *(int *)a-*(int *)b;
}



int main(){
  int tab[TABSIZE];
  int i;

  printf("-------------------------\n");
  srand(time(NULL));
  for(i=0;i<TABSIZE;++i){
    tab[i]=1 ;
    printf("%d\n",tab[i]);
  }

  printf("-------------------------\n");
  quicksort((void *)tab,TABSIZE,sizeof(int),compare_int);
  
  for(i=0;i<TABSIZE;++i){
    printf("%d\n",tab[i]);
  }

  return 0; 
}
 
