# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "fatal.h"
# include "parcoursGraphe.h"


/* Renvoie 1 si mot1 et mot2 sont reliés par une arête, 0 sinon */
int forment_arete(char mot1[], char mot2[]){
  int nb_diff, i;
  nb_diff = 0;
  for(i=0; i<strlen(mot1); i++)
    if (mot1[i] != mot2[i])
      nb_diff++;
  return (nb_diff == 1);
}

/* Remplit la matrice d'adjacence à l'aide des mots du dictionnaire */
void CreeMatriceAdjacence(MatriceAdjacence mat, char *dico_trie[TAILLE_DICO]){
  int i, j;
  /* mat est symétrique, on peut commencer à j=i pour la remplir
     triangulairement, et par symétrie on remplit l'autre triangle */
  for (i=0; i<TAILLE_DICO; i++)
    for (j=i; j<TAILLE_DICO; j++){
      if (forment_arete(dico_trie[i], dico_trie[j])){
	mat[i][j] = 1;
	mat[j][i] = 1;
      }
      else{
	mat[i][j] = 0;
	mat[j][i] = 0;
      }
    }
}

/* Renvoie l'indice du mot passé en paramètre dans le dictionnaire
   trié ou -1 s'il n'est pas dans le dictionnaire */
int ConvertionMotIndice(char *mot, char *dico_trie[TAILLE_DICO]){
  int debut, fin, milieu , valeur;
  debut = 0;
  fin = TAILLE_DICO-1;
  
  while (debut <= fin){
    milieu = (debut+fin)/2;
    valeur = strcmp(mot, dico_trie[milieu]);
    if (valeur == 0)
      return milieu;
    else if (valeur>0)
      /* mot est après dico_trie[milieu] dans le dictionnaire */
      debut = milieu + 1;
    else
      /* mot est avant dico_trie[milieu] dans le dictionnaire */
      fin = milieu - 1;
  }
  
  /* cas où le mot n'existe pas dans le dictionnaire */
  return -1;
}

/* Renvoie 1 si la pile est vide, 0 sinon */
int estVide(Pile indices){
  return indices == EMPTY_PILE;
}

/* Ajoute l'indice au-dessus de la pile */
int empiler(Pile *pIndices, int ind){
  Pile new;

  new = malloc(sizeof(struct pile_s));
  if (!new){
    fprintf(stderr, "Echec d'allocation dans la fonction empiler.\n");
    return -1;
  }

  new->indice = ind;
  new->next = *pIndices;
  *pIndices = new;

  return 0;
}

/* Récupère l'indice sur le premier élément de la pile et déplace la
   pile sur l'élément suivant */
int depiler(Pile *pIndices, int *ind){
  Pile first;

  if (estVide(*pIndices))
    return -1;

  first = *pIndices;
  *ind = first->indice;
  *pIndices = first->next;

  free(first);
  return 0;
}

/* Détermine le chemin s'il existe entre le sommet courant et le
   sommet destination. Le parcours est sauvegardé dans parcours s'il
   existe, sinon la pile est vide. Cette fonction renvoie 1 si succès,
   0 sinon. */
int Chemin(int sommetcourant, int sommetdestination, MatriceAdjacence mat,
  Pile *parcours, int dejaparcouru[TAILLE_DICO]){
  int j, succes;
  
  if (sommetcourant == sommetdestination)
    return 1;

  for(j=0; j<TAILLE_DICO; j++){
    if ( (mat[sommetcourant][j] == 1) && (dejaparcouru[j] == 0) ){
      empiler(parcours, j);
      dejaparcouru[j] = 1;
      succes = Chemin(j, sommetdestination, mat, parcours, dejaparcouru);
      if (succes)
	return 1;
      else
	depiler(parcours, &j);
    }
  }
  return 0;
}

/* Cette fonction quitte le programme avec une erreur si les mots
   n'ont pas la bonne longueur ou s'ils ne sont pas dans le
   dictionnaire */
void erreurMots(char mot1[], char mot2[], char *dico_trie[TAILLE_DICO]){
  fatal( (strlen(mot1) != 4), "Le premier mot n'a pas la bonne longueur.)", 1 );
  fatal( (strlen(mot2) != 4), "Le deuxième mot n'a pas la bonne longueur.)", 1 );
  fatal( (ConvertionMotIndice(mot1, dico_trie) == -1), "Le premier mot n'est pas dans le dictionnaire.\n", 1);
  fatal( (ConvertionMotIndice(mot2, dico_trie) == -1), "Le deuxième mot n'est pas dans le dictionnaire.\n", 1);
}

/* affiche le chemin stocké dans la pile parcours */
void afficherChemin(Pile *parcours, char *dico_trie[TAILLE_DICO]){
  int ind;
  Pile bon_parcours; /* Pour remettre le parcours à l'endroit */
  bon_parcours = EMPTY_PILE;
  
  while (!estVide(*parcours)){
    depiler(parcours, &ind);
    empiler(&bon_parcours, ind);
  }


  if (!estVide(bon_parcours)){
    depiler(&bon_parcours, &ind);
    printf("%s", dico_trie[ind]);
  }
    

  while (!estVide(bon_parcours)){
    depiler(&bon_parcours, &ind);
    printf(" -> %s", dico_trie[ind]);
  }
  putchar('\n');
}
