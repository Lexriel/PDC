# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "fatal.h"
# define ASCII_SIZE 128

int main(int argc, char *argv[]){
  int size, err;
  FILE *fp;
  char *text;

  /* Ouverture du fichier en lecture */
  fatal((argc < 2), "ERREUR : donner un nom de fichier en paramètre", 1);
  fp = fopen(argv[1], "r");

  /* Recherche la taille du fichier */
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  rewind (fp); /* refait pointer fp au début du fichier */

  /* Récupère le contenu du fichier à l'aide d'un pointeur */
  text = malloc((size+1) * sizeof(char)); /* +1 pour ajouter '\0' */
  fatal(!text, "ERREUR : échec de l'allocation mémoire du texte", 1);
  err = fread(text, sizeof(char), size, fp);
  rewind(fp);
  fatal((err != size), "ERREUR : échec de la lecture", 1);

  /* Affiche deux fois le contenu du fichier sur la sortie standard */
  text[size] = '\0';
  printf("%s", text);
  printf("%s", text);

  fclose(fp);
  free(text);

  return 0;
}
