# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char *my_strcpy(char *dest, const char *src){
  char *d;
  d = dest;
  while (*src != '\0')
    *dest++ = * src++;
  *dest = '\0';
  return d;
}


int main(){
  char c[6] = "Hello";
  char *a, *b, *d;
  a = malloc(6*sizeof(char));
  b = malloc(6*sizeof(char));
  /* c = "Hello"; */
  a[0] = 'S';
  a[1] = 'a';
  a[2] = 'l';
  a[3] = 'u';
  a[4] = 't';
  a[5] = '\0';

  d = my_strcpy(b, a);
  printf("%s\n", d);
  my_strcpy(b, c);
  printf("%s\n", b);
  strcpy(b, a);
  printf("%s\n", b);
  strcpy(b, c);
  printf("%s\n", b);

  free(a);
  free(b);

  return 0;
}
