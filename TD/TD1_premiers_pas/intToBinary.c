# include <stdio.h>
# include <stdlib.h>
# include <limits.h> /* contient la macro CHAR_BIT: nombre de bits par
			octets, à priori 8*/

/* Il est difficile d'afficher les bits d'un nombre de gauche à
   droite. Il va falloir recourir à une astuce qui ne s'improvise pas
   mais qui est intéressante à connaître. On va ici s'amuser à
   utiliser l'opérateur & (et bit-à-bit) pour obtenir les bits
   successifs du nombre entré. On va ainsi définir le nombre mask:
   mask = 100.....0 où le 1 est sur l'octet de poids le plus fort. À
   chaque étape de la boucle, on va faire l'opération & entre le
   nombre n et mask.

   Deux exemples avec valeurs de mask différentes : 
   n:        10011011      |     n:        10011011    
   mask:     10000000      |     mask:     00100000
   n & mask: 10000000      |     n & mask: 00000000

   Le seul endroit de n & mask où il peut y avoir un 1 est la colonne
   du 1 dans mask. Si cela vaut 1, on pourra afficher 1 avec putchar,
   si cela vaut 0, on affichera 0. On résume cela avec un unique
   putchar et un ternaire. Enfin on décale d'un rang vers la droite
   mask pour observer bit à bit l'affichage que l'on peut faire de
   gauche à droite. */

static void binaire(unsigned int n){
  int bit;
  unsigned int mask;

  mask = (unsigned int) 1 << ((sizeof(unsigned int) * CHAR_BIT) - 1);
  while (mask != 0){
    putchar(n & mask ? '1' : '0');
    mask>>=1;
  }
  putchar('\n');
}

int main(){
  int n;
  printf("Ce programme donne la représentation binaire d'un entier positif.\n");
  printf("Donnez un nombre entier positif : ");
  scanf("%d", &n);
  printf("L'écriture  binaire de %d est :\n", n);
  binaire(n);

  return 0;
}
