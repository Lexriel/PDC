# include <stdio.h>
# include <stdlib.h>
# define SIZE 100

int main(int argc, char* argv[]){
  enum etat {PREMIER, CANDIDAT, NON_PREMIER};
  int i, j, iter;
  int prime[SIZE];

  /* initialisation de prime */
  prime[0] = NON_PREMIER;
  prime[1] = NON_PREMIER;
  for (i=2; i<SIZE; i++)
    prime[i] = CANDIDAT;

  /* On cherche le prochain CANDIDAT itérativement sur la bouche iter,
     le prochain CANDIDAT n'ayant pas été un multiple des précédents PREMIER,
     est PREMIER. Ses multiples sont NON_PREMIER.  */
  for (iter=2; iter<SIZE; iter++)
    if (prime[iter] == CANDIDAT){
      prime[iter] = PREMIER;
      for (j=iter+1; j<SIZE; j++)
	if (j % iter == 0)
	  prime[j] = NON_PREMIER;
    }

  /* affichage des nombres premiers */
  i = 0;
  printf("Les nombres premiers compris entre 1 et %d sont :\n", SIZE);
  while (i < SIZE){
    if (prime[i] == PREMIER)
      printf("%d, ", i);
    i++;
  }
  printf("\n");

  exit(EXIT_SUCCESS);
}
