# include <stdio.h>


int main()
{
  char c, d;
  int i;

  c = 'a';
  for (i=0; i<26; i++){
    d = c+i;
    printf("%c: ", d);
    putchar(d^'*');
    putchar('\n');
  }
  c = '0';
  for (i=0; i<10; i++){
    d = c+i;
    printf("%c: ", d);
    putchar(d^'*');
    putchar('\n');
  }

  return 0;
}
