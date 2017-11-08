# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

/* typedef enum genre genre_e; */
/* enum genre {M, F, O}; */

void GetMatches ( const char * str, const char * format, ... )
{
  va_list args;
  va_start(args, format);
  vsscanf(str, format, args);
  va_end(args);
}

int main ()
{
  int date_prix, domaine, jour_naissance, mois_naissance, annee_naissance;
  char nom[50];
  char nationalite[30];
  char genre;

  GetMatches ( "1901,3,Jacobus Henricus van 't Hoff,30,8,1852,the Netherlands,M", "%d,%d,%s %*s,%d,%d,%d,%s,%c", &date_prix, &domaine, nom, &jour_naissance, &mois_naissance, &annee_naissance, nationalite, &genre);

  printf ("%d,%d,%s,%d,%d,%d,%s,%c\n", date_prix, domaine, nom, jour_naissance, mois_naissance, annee_naissance, nationalite, genre);

  return 0;
}
