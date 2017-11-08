#include <stdlib.h>
struct point {
  int x, y;
};

struct point * reserve_n_cellules(int n){
  return (struct point *) malloc(sizeof(struct point)*n);
}

int main(void){
  struct point *p_point = reserve_n_cellules(10) ;
  return 0 ;
}
