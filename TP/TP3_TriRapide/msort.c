# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "readl.h"
# include "quicksort.h"
# include "macros.h"

/* Cette fonction compare deux chaines. */
int comparChaine(const void *s1, const void *s2)
{
  const char *copy_s1, *copy_s2;
  copy_s1 = *((char **) s1);
  copy_s2 = *((char **) s2);
  return strcmp(copy_s1, copy_s2);
}

/* Retourne une copie fraîchement allouée de la chaîne de caractères
   str */
int *strdup(const int *s, int size){
  int i;
  int *res;
  res = malloc((size+1) * sizeof(int));
  for (i=0; i<size; i++)
    res[i] = s[i];
  return res;
}

/* Cette fonction affiche une chaine de caractères stockée dans un
   tableau d'entiers. */
void affiche_chaine(int line[])
{
  int i;
  i = 0;
  while (line[i])
    putchar(line[i++]);
  putchar('\n');

}

/* Cette fonction affiche un tableaux de chaines. */
void affiche_tableau_chaine(int *s[], int n)
{
  int i;
  for (i=0; i<n; i++)
    affiche_chaine(s[i]);
}

/* Commande msort */
int main(int argc, char* argv[])
{
  int n, size;
  int line[MAXLINE+1];
  int *s[MAXLINE];

  n = 0;
  while( ((size = readl(line)) != EOF) && (n<TABSIZE) )
    s[n++] = strdup(line, size);

  quicksort(s, n, sizeof(s[0]), &comparChaine);
  affiche_tableau_chaine(s, n);

  return 0;
} 
