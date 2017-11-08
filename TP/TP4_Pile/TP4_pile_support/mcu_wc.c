# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

int main(int argc, char *argv[])
{
  int wc, c;
  wc = 0; /* number of characters */

  while ((c = getchar()) != EOF)
    wc++;

  printf("%d\n", wc);
  return 0;
}
