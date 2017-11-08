# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "fatal.h"
# include "parcoursGraphe.h"
# include "dicoTrie4lettres.h"

int main(int argc, char *argv[]){
  char mot1[5], mot2[5];
  int ind1, ind2, i, cheminExiste;
  MatriceAdjacence M;
  int dejaparcouru[TAILLE_DICO];
  Pile parcours;

  /* Vérification que les mots donnés en paramètre sont corrects */
  fatal((argc < 3), "Donner deux mots en paramètre.", 1);
  strcpy(mot1, argv[1]);
  strcpy(mot2, argv[2]);
  erreurMots(mot1, mot2, dico);

  /* Converti les mots en indices */
  ind1 = ConvertionMotIndice(mot1, dico);
  ind2 = ConvertionMotIndice(mot2, dico);

  /* Création de la matrice d'adjacence */
  CreeMatriceAdjacence(M, dico);

  /* Initialisation du tableau dejaparcouru et de la pile parcours */
  parcours = EMPTY_PILE;
  empiler(&parcours, ind1);
  for (i=0; i<TAILLE_DICO; i++)
    dejaparcouru[i] = 0;
  dejaparcouru[ind1] = 1;

  /* Recherche d'un chemin */
  printf("%s\n", dico[ind1]);
  cheminExiste = Chemin(ind1, ind2, M, &parcours, dejaparcouru);

  if (cheminExiste)
    afficherChemin(&parcours, dico);
  else
    printf("Pas de chemin entre %s et %s.\n", mot1, mot2);

  return 0;
}
