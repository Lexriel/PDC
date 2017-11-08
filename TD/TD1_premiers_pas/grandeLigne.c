# include <stdio.h>
# include <stdlib.h>

static int maxl_line(){
  int c;              /* le caractère courant */
  int longueur = 0;   /* la longueur de la ligne courante */
  int maximum = 0;    /* le maximum actuel */
  
  while ((c=getchar()) != EOF){
    longueur++;
    if (c == '\n'){  /* fin de ligne */
      if (longueur > maximum)
	maximum = longueur;
      longueur = 0;
    }
  }

  return maximum-1;
}

int main(int argc, char *argv[]){
  int max;
  max = maxl_line();
  printf("La longueur de la plus longue ligne est %d.\n", max);

  exit(EXIT_SUCCESS);
}
