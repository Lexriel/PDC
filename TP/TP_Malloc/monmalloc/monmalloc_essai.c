# include "monmalloc.h"

int main(void){
  void *tmp;
  tmp = monmalloc(1000);
  monfree(tmp);

  return 0;
}
