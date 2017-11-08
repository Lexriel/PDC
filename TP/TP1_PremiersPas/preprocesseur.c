# include <stdio.h>

/* Ces constantes définissent si on est hors d'un commentaire (0),
   dedans (2) ; que l'on a un potentiel début de commentaire (1), une
   potentielle sortie de commentaire (3).
   Au choix : utiliser les define ou les enum. */
/* # define ETAT_HORS_COMM 0 */
/* # define ETAT_SLASH_DEBUT_COMM 1 */
/* # define ETAT_COMM 2 */
/* # define ETAT_ETOILE_FIN_COMM 3 */
/* # define ETAT_RETOUR_LIGNE 4 */


/* Ce code peut encore être amélioré mais représente déjà suffisamment
   les notions nécessaires pour l'exercice */
int main()
{
  char c;
  enum {
    ETAT_HORS_COMM, ETAT_SLASH_DEBUT_COMM, ETAT_COMM, ETAT_ETOILE_FIN_COMM, ETAT_RETOUR_LIGNE
  } etat;

  etat = ETAT_HORS_COMM;
  while ((c = getchar()) != EOF){
    switch(etat){
    case ETAT_HORS_COMM:
      if (c == '/')
	etat = ETAT_SLASH_DEBUT_COMM;
      else
	putchar(c);
      break;
    case ETAT_SLASH_DEBUT_COMM:
      if (c == '*')
	etat = ETAT_COMM;
      else{
	etat = ETAT_HORS_COMM;
	putchar('/');
	putchar(c);
      }
      break;
    case ETAT_COMM:
      if (c == '*')
	etat = ETAT_ETOILE_FIN_COMM;
      break;
    case ETAT_ETOILE_FIN_COMM:
      if (c == '/')
	etat = ETAT_RETOUR_LIGNE;
      else
	etat = ETAT_COMM;
      break;
    case ETAT_RETOUR_LIGNE:
      etat = ETAT_HORS_COMM;
      if (c != '\n')
	putchar(c);
      break;
    }
  }

  return 0;
}
