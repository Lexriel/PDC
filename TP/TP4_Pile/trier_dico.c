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

/* Trie le dictionnaire dico dans dico4lettres.h et génère ce
   dictionnaire trié dans dicoTrie4lettres.h */
int main(int argc, char *argv[]){
  int i;
  FILE *pfile;

  /* tri du dictionnaire */
  qsort(dico, TAILLE_DICO, sizeof(dico[0]), &comparChaine);

  /* on ouvre le fichier dans lequel on stockera le nouveau
     dictionnaire */
  pfile = fopen("dicoTrie4lettres.h", "w");
  fprintf(pfile, "# ifndef _DICO_TRIE_H_\n# define _DICO_TRIE_H_\n\n");
  fprintf(pfile, "# define TAILLE_DICO 909\n\n");
  fprintf(pfile, "#ifndef _DICO_\n# define _DICO_\n");
  fprintf(pfile, "/* Un dictionnaire de mots de quatre lettres */\n");
  fprintf(pfile, "char *dico[] = { ");
  for (i=0; i<TAILLE_DICO-1; i++)
    fprintf(pfile, "\"%s\", ", dico[i]);
  fprintf(pfile, "\"%s\" };\n\n", dico[TAILLE_DICO-1]);
  fprintf(pfile, "# endif\n\n# endif\n");
  fclose(pfile);

  return 0;
}
