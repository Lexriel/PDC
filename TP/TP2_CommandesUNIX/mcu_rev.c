# include <stdio.h>
# include <stdlib.h>
# include "mcu_readl.h"
# include "mcu_fatal.h"
# include "mcu_macros.h"

int main(int argc, char *argv[]){
  int i, n;
  int line[MAXLINE+1];

  while ((n = readl(line)) != EOF){
    for (i=n; i>=0; i--)
      putchar(line[i]);
    putchar('\n');
  }
  return 0;
}
