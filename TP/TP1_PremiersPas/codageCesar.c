# include <stdio.h> /* contient getchar, putchar */

int main()
{
  char c;

  /* "This program can be run with a file: run ./codageCesar < file.txt */
  while ((c = getchar()) != EOF) /* EOF: macro désignant un caractère de fin de fichier */
    putchar(c^'*');
  printf("\n");

  return 0;
}
