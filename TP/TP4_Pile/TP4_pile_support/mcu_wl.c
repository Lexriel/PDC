# include <stdio.h>
# include <stdlib.h>
# include "readl.h"
# include "fatal.h"
# include "macros.h"

int main(int argc, char *argv[])
{
  int wl;
  int line[MAXLINE+1];
  wl = 0; /* number of lines */

  while (readl(line) != EOF)
    wl++;

  printf("%d\n", wl);
  return 0;
}
