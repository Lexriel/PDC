# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>


float f_sum_them_all(int nargs, ...){
  float sum;
  float *p;
  sum = 0.0;
  p = (float*) (&nargs + 1);
  while(nargs--)
    sum += *p++;
  return sum;
}

double f_sum_them_all_std(int nargs, ...){
  float sum;
  int i;
  va_list ap;
  va_start(ap, nargs);
  for (i=0; i<nargs; i++)
    sum += va_arg(ap, double);
  va_end(ap);
  return sum;
}


int sum_them_all(int nargs, ...){
  int sum;
  int *p;
  sum = 0;
  p = &nargs + 1;
  while(nargs--)
    sum += *p++;
  return sum;
}

int main(){
  int a, b, c;
  double d;

  c = sum_them_all(2, 5, 7);
  printf("5 + 7 = %d  ~ %d \n", 5+7, c);

  a = sum_them_all(3, 5, 6, 7);
  printf("5 + 6 + 7 = %d  ~ %d \n", 5+6+7, a);

  b = sum_them_all(5, 0, -1, 4, 3, -5);
  printf("0 - 1 + 4 + 3 - 5 = %d  ~ %d \n", 0-1+4+3-5, b);
  
  d = f_sum_them_all(2, 5.2, 7.1);
  printf("5.2 + 7.1 = %f  ~ %f \n", 5.2+7.1, d);

  d = f_sum_them_all_std(2, 5.2, 7.1);
  printf("5.2 + 7.1 = %f  ~ %f \n", 5.2+7.1, d);

  return 0;
}
