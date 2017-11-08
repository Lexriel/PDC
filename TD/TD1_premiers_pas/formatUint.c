# include <stdio.h>
# include <stdlib.h>

/* Compilation : gcc -o ex10 ex10.c */
/* On remarque que 0 est codé en binaire par une suite de zéros et que
   1 est codé en binaire par une suite de zéros suivie d'un unique
   1. Pour déterminer de façon simple le nombre de bits sur lequel
   sont codés les unsigned int, on peut décaler d'un rang vers la
   gauche le 1 du nombre 1 jusqu'à tant qu'il sorte de la taille d'un
   unsigned int, donnant de ce fait 0. */
int longint(){
  unsigned int V = 1;
  int nb_decal = 0;

  while (V != 0){
    V <<= 1; /* décalage de V d'un bit vers la gauche */
    nb_decal ++;
  }

  return nb_decal;
}

int main(){
  printf("Sur cette machine, unsigned int est codé sur %d bits.\n", longint());
  return 0;
}
