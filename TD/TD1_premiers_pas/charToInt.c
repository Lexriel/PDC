# include <stdio.h>
# include <stdlib.h>
# include <ctype.h> /* contient isdigit */

/* Compilation : gcc -o ex9 ex9.c */
/* La fonction isdigit() renvoie 1 si l'entier entré en paramètre
   correspond au code ascii d'un chiffre. Lire un nombre sous la forme
   d'une chaine de caractères, par ex. '286', se fait de gauche à
   droite. On lira d'abord '2', puis '8' puis '6'. Pour transcrire ces
   codes ascii en nombre, on leur soustrait le code ascii de '0', de
   ce fait '2'-'0'=2. Pour former le nombre, on met dans resu pour
   commencer le chiffre 2, puis avant de mettre le chiffre suivant, on
   transforme resu en 20, on ajoute 8 pour obtenir 28, on réitère ce
   procédé (280 puis 286) pour obtenir le nombre final. */

unsigned int lire_entier(){
  unsigned int resu = 0 ;
  int carac = getchar() ;

  while (isdigit(carac)){
    resu *= 10 ;
    resu += carac - '0' ;
    carac = getchar() ;
  }

  return resu ;
}

int main(){
  printf("lire_entier done : %d\n", lire_entier());
}
