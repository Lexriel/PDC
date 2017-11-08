# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <math.h>
# define GA_INITIAL_SIZE 8

enum {GA_OK,
      GA_NOMEM, /* can not allocate memory */
      GA_OOB,   /* access out of bound */
      GA_NULL,  /* invalid NULL pointer */
      GA_NDEF   /* valeur non définie */
};

typedef struct ga_s Ga;
struct ga_s{
  unsigned int taille;
  int *tableau;
};

void ga_afficher(Ga ga){
  int n, i;
  n = ga.taille;
  printf("ga = ");
  for (i=0; i<n; i++){
    if (ga.tableau[i])
      printf("%d, ", ga.tableau[i]);
    else
      printf("X, ");
  }
  putchar('\n');
}


Ga ga_init(void){
  Ga ga = {0,(int *) NULL};
  return ga;
}

/* ou alors :
Ga ga_init(void){
  Ga ga;
  ga.taille = 0;
  ga.tableau = (int *) NULL;
  return ga;
}
Attention : Ga ga; ga = {0,(int *) NULL}; est invalide !
*/

int ga_destroy(Ga *ga){
  if (!ga)
    return GA_NULL;
  if (ga->taille > 0)
    free(ga->tableau);
  return GA_OK;
}

int ga_get(Ga *ga, unsigned int index, int *val)
{
  if (!ga || !val)
    return GA_NULL;
  if (index >= ga->taille)
    return GA_OOB;
  if (!ga->tableau[index])
    return GA_NDEF;
  *val = ga->tableau[index];
  return GA_OK;
}

int maximum(int a, int b){
  return ((a > b) ? a : b);
}

int ga_set(Ga *ga, unsigned int index, int val)
{
  int size, *new, i;
  if (!ga)
    return GA_NULL;
  /* first allocation */
  if (ga->taille == 0) {
    size = maximum(index, GA_INITIAL_SIZE);
    ga->taille = size;
    ga->tableau = calloc(size, sizeof(int));
    if (!ga->tableau)
      return GA_NOMEM;
  }
  /* extended allocation */
  if (index >= ga->taille) {
    size = maximum(2*ga->taille, index+1);
    new = realloc(ga->tableau, size * sizeof(int));
    if (!new)
      return GA_NOMEM;
    for (i=ga->taille; i<size; i++)
      new[i] = 0;
    ga->tableau = new;
    ga->taille = size;
  }
  /* set the ga element */
  ga->tableau[index] = val;
  return GA_OK;
}

/* Question 2
# define GA_CHAINE_SIZE 32
typedef struct ga_chaine Ga_chaine;
struct ga_chaine{
  int tableau[GA_CHAINE_SIZE];
  Ga_chaine *next;
};

typedef struct ga_s Ga;
struct ga_s{
  int taille;
  Ga_chaine *premier_maillon;
};

avantage : on évite les recopies avec le realloc
inconvénient : l'accès aux indices n'est plus direct, on va
devoir parcourir les maillons (par ex l'indice 35 correspond
à l'indice 3 du tableau du deuxième maillon */


int main(int argc, char* argv[])
{
  Ga ga;
  int i, ind, val, code;

  ga = ga_init();
  printf("INITIALISATION :\n");
  ga_afficher(ga);
  printf("PREMIERS REMPLISSAGES :\n");
  for (i=1; i<5; i++)
    ga_set(&ga, i, 3*i/2+1);
  ga_afficher(ga);

  printf("REMPLISSAGE HORS INDICES :\n");
  ga_set(&ga, 8, 42);
  ga_afficher(ga);

  printf("Donner l'indice dans ga dont vous voulez la valeur : ");
  scanf("%d", &ind);
  code = ga_get(&ga, ind, &val);
  switch(code){
  case GA_NULL:
    printf("Opération impossible : ga est nul.\n");
    break;
  case GA_OOB:
    printf("Opération impossible : index inexistant.\n");
    break;
  case GA_NDEF:
    printf("Opération impossible : valeur non définie à l'index.\n");
    break;
  case GA_OK:
    printf("ga[%d] = %d\n", ind, val);
    break;
  default:
    ;
  }
  ga_destroy(&ga);

  return 0;
}
