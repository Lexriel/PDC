# include <stdio.h>
# include <stdlib.h>
# include "fatal.h"
# include "macros.h"
 
/* Lit une ligne sur l'entrée standard grâce à getchar (cf. man).   
   Cette ligne doit comporter moins de MAXLINE caractères.
   Le résultat est retourné dans line (passage de paramètre
   par référence). Un \0 est écrit en fin de la chaîne.
   Ainsi, le tableau line doit être de taille au moins MAXLINE+1.
   Retourne le nombre de caractères lus, non compris le \0 final.
   Retourne EOF si la fin de fichier est atteinte.
   Termine le programme sur une erreur si rencontre une ligne de plus
   de MAXLINE caractères et retourne 1 grâce à la fonction exit
   (cf. man). */

extern int readl(int line[])
{
  int c, n;
  n = 0;

  while ((c = getchar()) != EOF)
    {
      if ((c == '\n') || (c == '\0'))
	break;
      line[n] = c;
      fatal((n >= MAXLINE), "Ligne trop longue", EXIT_FAILURE);
      n++;
    }
  line[n] = '\0';

  if(c == EOF)
    return EOF;
  return n;
}
