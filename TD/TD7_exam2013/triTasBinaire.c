# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# define NB_ENTIERS 10

void permuter(int *a, int *b){
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void percolation(int *tete, int *queue){
  int pere;
  if (queue == tete)
    return;
  /* (T+2i+1-T -1) / 2 = i
     (T+2i+2-T -1) / 2 = i */
  pere = (queue - tete - 1) / 2;
  if (tete[pere] >= *queue)
    return;
  permuter(tete+pere, queue);
  percolation(tete, tete+pere);
}

void ConstruireTas(int *tete, int *queue){
  int *tmp;
  tmp = tete;
  while (tmp <= queue)
    percolation(tete, tmp++);
}

void tamissage(int *tete, int *queue){
  int courant, max, filsG, filsD;
  courant = 0;
  while (tete + 2*courant + 1 < queue){
    filsG = 2*courant + 1;
    filsD = 2*(courant + 1);
    /* chercher avec qui permuter */
    max = 0;
    if (tete[filsG] > tete[courant])
      max = filsG;
    if (tete + filsD < queue){
      if (max){
	if (tete[filsD] > tete[filsG])
	  max = filsD;
      }
      else{
	if (tete[filsD] > tete[courant])
	  max = filsD;
      }
    }
    /* permuter ou sortir */
    if (!max)
      return;
    else
      permuter(tete+courant, tete+max);
    /* réactualiser la position de l'élément que l'on tamise */
    courant = max;
  }
  return;
}

void Trier(int *tete, int *queue){
  ConstruireTas(tete, queue);
  while(queue > tete){
    permuter(tete, queue);
    tamissage(tete, queue);
    queue--;
  }
  return;
}

void afficherTableau(char message[], int *T, int n){
  int i;
  printf("%s : ", message);
  for (i=0; i<n; i++)
    printf("%d, ", T[i]);
  printf("\n");
}

int *creerTableau(int n){
  int i;
  int *res;
  srand(time(NULL));
  res = malloc(n * sizeof(int));
  for (i=0; i<n; i++)
    res[i] = rand() % 100;
  return res;
}

int main(int argc, char *argv[]){
  int n = NB_ENTIERS;
  int T[] = {12, 9, 6, 2, 7, 5, 15};
  int *U;

  afficherTableau("Tableau initial  ", T, 7);
  ConstruireTas(T, T+6);
  afficherTableau("Tableau après construireTas ", T, 7);
  Trier(T, T + 7 - 1);
  afficherTableau("Tableau après tri", T, 7);

  U = creerTableau(n);
  afficherTableau("Tableau initial  ", U, n);
  Trier(U, U + n-1);
  afficherTableau("Tableau après tri", U, n);
  free(U);

  return 0;
}
