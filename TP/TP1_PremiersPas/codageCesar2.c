# include <stdio.h>  /* contient printf, putchar, fopen, fclose */
# include <stdlib.h> /* contient exit */
/* argc : nombre d'arguments sur la commande d'exécution "./codeCesar2 file.txt "
   argv[0] : ./codeCesar2 (nom de l'exécutable) 
   argv[1] : file.txt (nom du fichier) */
int main(int argc, char *argv[])
{
  char c;
  FILE *pfile; /* pointeur de fichier */

  /* Message d'erreur s'il manque un paramètre le fichier */
  if (argc != 2){
    printf("ERROR !\nMissing parameter. Run: ./codageCesar file.txt\n");
    exit(1); /* quitte l'exécutable avec le code d'erreur 1 */
  }

  pfile = fopen(argv[1], "r"); /* ouvre le fichier argv[1] en lecture (r comme read) */

  while ((c = fgetc(pfile)) != EOF) /* fgetc lit un caractère dans pfile */
    putchar(c^'*');
  putchar('\n');

  fclose(pfile);
  return 0;
}
