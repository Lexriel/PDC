# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "fatal.h"
# define ASCII_SIZE 128

typedef float Freq[1<<8];

/* Cette fonction rempli le tableau AsciiArray par le nombre
   d'occurence de chaque lettre stockee par l'indice de son code ascii
   dans le tableau */
int setAsciiArray(int AsciiArray[], char *text, int size){
  int nonAscii, c, i;
  nonAscii = 0;
  for (i=0; i<size; i++){
    c = (int) text[i];
    if (c<ASCII_SIZE)
      AsciiArray[c]++;
    else
      nonAscii++;
  }
  return nonAscii;
}

/* Cette fonction construit la distribution de frequences dans le
   fichier lu et la stocke dans FreqArray */
void distributionFrequence(Freq FreqArray, FILE* fp){
  int size, err, i;
  char *text;
  int AsciiArray[ASCII_SIZE] = {0};

  /* Recherche la taille du fichier */
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  rewind (fp); /* refait pointer fp au debut du fichier */

  /* Récupere le contenu du fichier a l'aide d'un pointeur */
  text = malloc(size * sizeof(char));
  fatal(!text, "ERREUR : échec de l'allocation mémoire du texte", 1);
  err = fread(text, sizeof(char), size, fp);
  rewind(fp);
  fatal((err != size), "ERREUR : échec de la lecture", 1);

  /* Remplissage du tableau des frequences */
  err = setAsciiArray(AsciiArray, text, size);
  for (i=0; i<ASCII_SIZE; i++)
    FreqArray[i] = AsciiArray[i]/((float) size);

  for (i=0; i<ASCII_SIZE; i++)
    printf("%f ", FreqArray[i]);
  printf("\n");

  free(text);
}

int main(int argc, char *argv[]){
  int size, err, i, sum;
  FILE *fp;
  char *text;
  int AsciiArray[ASCII_SIZE] = {0};
  float FreqArray[ASCII_SIZE] = {0.0};

  /* Ouverture du fichier en lecture */
  fatal((argc < 2), "ERREUR : donner un nom de fichier en paramètre", 1);
  fp = fopen(argv[1], "r");

  /* Recherche la taille du fichier */
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  rewind (fp); /* refait pointer fp au début du fichier */

  /* Récupère le contenu du fichier à l'aide d'un pointeur */
  text = malloc(size * sizeof(char));
  fatal(!text, "ERREUR : échec de l'allocation mémoire du texte", 1);
  err = fread(text, sizeof(char), size, fp);
  rewind(fp);
  fatal((err != size), "ERREUR : échec de la lecture", 1);

  /* Affiche deux fois le contenu du fichier sur la sortie standard */
  printf("%s", text);
  printf("%s", text);

  setAsciiArray(AsciiArray, text, size);

  sum = 0;
  for (i=0; i<ASCII_SIZE; i++){
    sum += AsciiArray[i];
    printf("%d ", AsciiArray[i]);
  }
  printf("\nSum = %d\n", sum);
  printf("%f\n", 17/((float) size));

  distributionFrequence(FreqArray, fp);

  fclose(fp);
  free(text);

  return 0;
}
