# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "dico4lettres.h"

/* Cette fonction compare deux chaines. */
int comparChaine(const void *s1, const void *s2)
{
  const char *copy_s1, *copy_s2;
  copy_s1 = *((char **) s1);
  copy_s2 = *((char **) s2);
  return strcmp(copy_s1, copy_s2);
}

/* Cette fonction trie le dictionnaire en entrée */
void trierDico(char *dicoNonTrie[], int (*compar)(const void*, const void*)){
  /* Utiliser la fonction qsort de la bibliothèque stdlib.h par exemple, ou celle implémentée dans le TP précédent */
  /*qsort(..., ..., sizeof(dico[0]), ...); */
}

/* exemple d'écriture dans un fichier */
void remplir_fichier(char nom_fichier[]){
  FILE *pfile; /* On déclare un pointeur sur un fichier */
  char s[] = "L'informatique, c'est fantastique";
  /* on ouvre le fichier en écriture (w) */
  pfile = fopen(nom_fichier, "w");
  /* on écrit dans le fichier pfile */
  fprintf(pfile, "Bienvenue dans ce fichier\n");
  fprintf(pfile, "Ici j'affiche un entier  : %d.\n", 52);
  fprintf(pfile, "Ici j'affiche une chaine : %s.\n", s);
  fprintf(pfile, "Ici j'affiche le flottant %f et le caractère %c.\n", 3.14, 'k');
  /* on ferme le fichier */
  fclose(pfile);
}
