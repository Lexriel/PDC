# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <math.h>
# define GA_INITIAL_SIZE 8


typedef struct pool_s Pool;
struct pool_s{
  Pool *next;
};

static Pool *pool;

typedef struct point struct_t;
struct point{
  int x;
  int y;
  int z;
};

void create_pool(){
  if (sizeof(struct_t) < sizeof(Pool)){
    printf("sizeof(struct_t) < sizeof(Pool) = VRAI\n");
    printf("Erreur, impossible de gérer le pool...\n");
    exit(1);
  }
  printf("sizeof(struct_t) < sizeof(Pool) = FAUX\n");
  pool = (Pool *) NULL;
}

void destroy_pool(){
  Pool *p;
  while (pool){
    p = pool->next;
    free(pool);
    pool = p;
  }
}

struct_t *new_struct(){
  struct_t *res;
  if (pool){
    /* return the first pool_s */
    res = (struct_t *) pool;
    pool = pool->next;
    return res;
  }
  else
    /* no more pool_s, mallocate one */
    return malloc(sizeof(struct_t));
}

void free_struct(struct_t *s){
  ((Pool *) s)->next = pool;
  pool = (Pool *) s;
}

void afficher_pool(char message[]){
  Pool *tmp;
  tmp = pool;
  printf("%s ", message);
  if (!tmp)
    printf("vide");
  while (tmp){
    printf("%p, ", tmp);
    tmp = tmp -> next;
  }
  putchar('\n');
}

void afficher_point(struct_t *point, char lettre){
  if (point)
    printf("%c : {%d, %d, %d}\n", lettre, point->x, point->y, point->z);
}

int main(int argc, char* argv[])
{
  int i, ind, val, code;
  struct_t *A, *B, *C, *D, *E, *F;
  //= {1.0, 2.3}, B = {2.6, -1.4}, C = {2.0, 0.0};

  printf("%ld, %ld\n", sizeof(Pool), sizeof(struct_t));

  create_pool();
  afficher_pool("POOL APRES CREATION :");
  A = new_struct(); B = new_struct(); C = new_struct();
  D = new_struct(); D->x = 0; D->y = 1; D->z = 3;
  E = new_struct(); E->x = 1; E->y = 2; E->z = 0;
  afficher_pool("POOL APRES AJOUT DE A, B, C, D, E :");
  free_struct(A);
  afficher_pool("POOL APRES SUPPRESSION DE A :");
  free_struct(B); free_struct(C);
  afficher_pool("POOL APRES SUPPRESSION DE B, C :");
  F = new_struct(); F->x = 1; F->y = 1; F->z = 1;
  afficher_pool("POOL APRES AJOUT DE F :");
  free_struct(E);
  afficher_pool("POOL APRES SUPPRESSION DE E :");


  afficher_point(D, 'D');
  afficher_point(F, 'F');

  destroy_pool();
  afficher_pool("POOL APRES DESTRUCTION :");

  return 0;
}
