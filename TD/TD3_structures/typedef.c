# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define SIZE 100

int main()
{
  typedef int entier;
  typedef char chaine[SIZE];
  typedef struct fraction fraction;
  struct fraction{
    int numerateur;
    int denominateur;
  };
  /* Un raccourci sympa :
     typedef struct{
       int numerateur;
       int denominateur;
     } fraction; */

  entier a = 15;
  fraction x = {3,4};
  chaine s = "Vers l'infini et l'angle droit ! Buzz l'équerre.";
  printf("Entier: %d\nFraction: %d/%d\nChaine: %s\n", a, x.numerateur, x.denominateur, s);
  return 0;
}
