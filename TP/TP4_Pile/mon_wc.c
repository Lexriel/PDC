# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "macros.h"
# include "readl.h"
# include "fatal.h"

/* définition de types pour avoir le nombre de lignes, mots,
   caractères ou les trois */
enum {WL, WW, WC, WLWC};

/* Identifie le paramètre donné en entrée s'il est correctement rentré, quitte une erreur sinon */
int identifyOption(char param[]){
  int type, test;
  char s[MAXLINE];

  /* Le paramètre devrait commencer par - et n'être suivi que d'une
     lettre */
  test = (param[0] != '-') && (param[2] != '\0');
  sprintf(s, "mcu_wc: illegal option %s\nusage: ./mcu_wc [-clw]", param);
  if (test)
    fatal(test, s, 1);

  /* On détermine le type à renvoyer */
  if (param[1] == 'l')
    type = WL;
  else if (param[1] == 'w')
    type = WW;
  else if (param[1] == 'c')
    type = WC;
  else
    fatal(1==1, s, 1);
  return type;
}

/* Commande "équivalente" à wc */
int main(int argc, char *argv[])
{
  int c, wc, ww, wl, i, type;
  int line[MAXLINE+1];
  enum {DANS_UN_MOT, HORS_MOT} etat;
  wc = 0; /* number of characters */
  ww = 0; /* number of words */
  wl = 0; /* number of lines */
  etat = HORS_MOT;
  type = WLWC;

  if (argc > 1)
    type = identifyOption(argv[1]);

  /* calcul du nombre de lignes, mots et caractères en simultané */
  while (readl(line) != EOF){
    wl++;
    i = 0;
    while ( ((c = line[i]) != '\0') && line[i] ){
      wc++;
      switch(etat){
      case HORS_MOT:
	if (isalpha(c)){ /* On rentre dans un mot, on le compte. */
	  ww++;
	  etat = DANS_UN_MOT;
	}
      case DANS_UN_MOT:
	if (!isalpha(c)) /* On sort d'un mot */
	  etat = HORS_MOT;
      }
      i++;
    }
    wc++; /* pour le retour chariot qui n'existe pas dans line */
  }

  /* Affichage selon le type de paramètre */
  switch(type){
  case WL:
    printf("%d\n", wl);
    break;
  case WW:
    printf("%d\n", ww);
    break;
  case WC:
    printf("%d\n", wc);
    break;
  case WLWC:
    printf("%d %d %d\n", wl, ww, wc);
    break;
  default:
    ;
  }
  return 0;
}
