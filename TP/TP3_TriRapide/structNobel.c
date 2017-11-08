# include <stdio.h>
# include <stdlib.h>
# include "readl.h"
# include "fatal.h"
# include "macros.h"

/* Cette fonction lit le paramètre à la position pos dans line et le
   stocke dans param. Les positions sont définitions avec des ','
   comme séparateurs ','. */
void lireParametre(char param[], int n, int line[], int pos)
{
  int i, n_sep, j;
  i = 0;
  j = 0;
  n_sep = 0;
  /* On place i après la pos-ième virgule dans line */
  while ((n_sep < pos) && (line[i]))
    if (line[i++] == ',')
      n_sep++;
  fatal(!line[i], "Débordement de ligne", EXIT_FAILURE);
  fatal((n_sep < pos), "Il n'y a pas de donnée à la position proposée", EXIT_FAILURE);
  /* on remplit param par son champ à partir de line[i] */
  while ((line[i] != ',') && (line[i]) && (j<n-1))
    param[j++] = line[i++];
  fatal((j>=n), "Donnée à extraire trop volumineuse", EXIT_FAILURE);
  param[j] = '\0';
}

/* Cette fonction permet de remplir les champs de la structure nobel
   grâce aux paramètres définis dans line. */
void remplirNomine(Nomine *nobel, int line[])
{
  int pos;
  char nombre[10];

  for (pos=0; pos<8; pos++){
    switch(pos){
    case 0:
      lireParametre(nombre, 10, line, pos);
      nobel->date_prix = atoi(nombre);
      break;
    case 1:
      lireParametre(nombre, 10, line, pos);
      nobel->domaine = atoi(nombre);
      break;
    case 2:
      lireParametre(nobel->nom, 50, line, pos);
      break;
    case 3:
      lireParametre(nombre, 10, line, pos);
      nobel->jour_naissance = atoi(nombre);
      break;
    case 4:
      lireParametre(nombre, 10, line, pos);
      nobel->mois_naissance = atoi(nombre);
      break;
    case 5:
      lireParametre(nombre, 10, line, pos);
      nobel->annee_naissance = atoi(nombre);
      break;
    case 6:
      lireParametre(nobel->nationalite, 30, line, pos);
      break;
    case 7:
      lireParametre(nombre, 2, line, pos);
      nobel->genre = nombre[0];
      break;
    default:
      break;
    }
  }
}

/* Cette fonction affiche sur une ligne le contenu des champs de
   nobel. */
void afficheNomine(Nomine nobel)
{
  printf("%d,%d,%s,%d,%d,%d,%s,%c\n", nobel.date_prix, nobel.domaine, nobel.nom, nobel.jour_naissance, nobel.mois_naissance, nobel.annee_naissance, nobel.nationalite, nobel.genre);

}

/* Cette fonction remplit un tableaux de Nomine grâce à une
   redirection sur un fichier contenant des champs pour remplir chacun
   des nobels[i]. */
int ConstruireTableaux(Nomine *nobels)
{
  int n;
  int line[MAXLINE+1];

  n = 0;
  while (readl(line) != EOF)
    remplirNomine(&nobels[n++], line);

  return n;
}

/* Cette fonction permet de comparer deux Nomine en fonction des dates
   de naissances. */
int CompareNomineParDateDeNaissance(const void *nobel1, const void *nobel2)
{
  const Nomine *Nobel1, *Nobel2;
  int a, b;
  Nobel1 = (Nomine*) nobel1;
  Nobel2 = (Nomine*) nobel2;

  a = Nobel1->annee_naissance;
  b = Nobel2->annee_naissance;
  if (a != b)
    return (a>b)? 1: -1;
  a = Nobel1->mois_naissance;
  b = Nobel2->mois_naissance;
  if (a != b)
    return (a>b)? 1: -1;
  a = Nobel1->jour_naissance;
  b = Nobel2->jour_naissance;
  if (a != b)
    return (a>b)? 1: -1;
  return 0;
}
