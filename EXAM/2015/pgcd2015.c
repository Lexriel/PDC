# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* EXERCICE 2.1 */
typedef struct cell_s cell_t;
struct cell_s{
  unsigned int entier;
  cell_t* next;
};

/* EXERCICE 2.2 */
cell_t* liste_des_diviseurs(unsigned int n){
  cell_t *liste, *new_cell;
  int i;

  liste = (cell_t*) NULL;
  for (i=1; i<=n; i++){
    if (n % i == 0){
      /* création d'une nouvelle cellule */
      new_cell = malloc(sizeof(struct cell_s));
      new_cell->entier = i;
      new_cell->next = liste;
      /* on pointe sur la nouvelle cellule créée */
      liste = new_cell;
    }
  }
  return liste;
}

/* EXERCICE 2.3 */
int estDansListe(unsigned int n, cell_t* liste){
  if (!liste)
    return 0;
  if (liste->entier == n)
    return 1;
  if (liste->next)
    return estDansListe(n, liste->next);
  else
    return 0;
}

cell_t* elements_communs(cell_t* liste1, cell_t* liste2){
  int N;
  cell_t *liste, *tmp, *new_cell;
  liste = (cell_t*) NULL;

  /* Identifie les valeurs de liste1 dans liste2 et détruit liste1 */
  while (liste1){
    N = liste1->entier;
    if (estDansListe(N, liste2)){
      new_cell = malloc(sizeof(struct cell_s));
      new_cell->entier = N;
      new_cell->next = liste;
      liste = new_cell; 
    }
    tmp = liste1;
    liste1 = liste1->next;
    free(tmp);
  }

  /* Destruction de liste2 */
  while (liste2){
    tmp = liste2;
    liste2 = liste2->next;
    free(tmp);
  }
  
  return liste;
}


/* EXERCICE 2.4 */
unsigned int plus_grand_element(cell_t* liste){
  int N;
  cell_t* tmp;
  
  N = 0;
  tmp = liste;
  
  while (liste){
    if (liste->entier > N)
      N = liste->entier;
    tmp = liste;
    liste = liste->next;
    free(tmp);
  }
  return N;
}

void afficher_liste(cell_t* liste){
  if (liste != (cell_t*) NULL){
    printf("%d ", liste->entier);
    liste->next ? afficher_liste(liste->next) : putchar('\n');
  }
}


int main(int argc, char* argv[]){
  unsigned int m, n, d;
  cell_t *liste, *liste1, *liste2;

  m = 24;
  n = 36;
  if (argc>1)
    m = (unsigned int) atoi(argv[1]);
  if (argc>2)
    n = (unsigned int) atoi(argv[2]);

  printf("CALCULS: avec liste_des_diviseurs(...)\n");
  liste1 = liste_des_diviseurs(m);
  printf("Les diviseurs de %d sont : ", m);
  afficher_liste(liste1); putchar('\n');
  liste2 = liste_des_diviseurs(n);
  printf("Les diviseurs de %d sont : ", n);
  afficher_liste(liste2); putchar('\n');

  printf("CALCULS: avec elements_communs(...)\n");
  liste = elements_communs(liste1, liste2);
  printf("Les diviseurs communs de %d et %d sont : ", m, n);
  afficher_liste(liste); putchar('\n');

  d = plus_grand_element(liste);
  printf("PGCD(%d,%d) = %d  --- calculé avec plus_grand_element(...)\n", m, n, d);
  /* afficher_liste_destructif(liste); */

  return 0;
}
