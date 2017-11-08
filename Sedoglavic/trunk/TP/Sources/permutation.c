void permuter (int *a, int *b){
  int tmp = *a;
  *a=*b; 
  *b = tmp;
}

int main(void){
  int a = 3;
  int b = 4;
  permuter(&a,&b) ;
  return 1 ;
}
 
