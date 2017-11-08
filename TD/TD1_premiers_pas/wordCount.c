# include <stdlib.h>
# include <stdio.h>
# include <ctype.h> /* contient la fonction isalpha */

# define ETAT_IN_WORD  1 /* un enum serait préférable */
# define ETAT_OUT_WORD 2

/* Compilation : gcc -o ex8 ex8.c */
/* La difficulté de cet exercice est de définir ce qu'est un mot. On
   peut considérer qu'un mot est défini par les lettres de 'a' à 'z' et
   de 'A' à 'Z' (caractères alphanumériques). C'est ce que fait la
   fonction isalpha, elle détermine si l'entier en paramètre représente
   le code ascii d'un caractère alphanumérique. */
int main(){
  int wc = 0; /* word count */
  int c;
  int etat = ETAT_OUT_WORD;

  while ((c=getchar()) != EOF){
    switch (etat){
    case ETAT_OUT_WORD:
      if (isalpha(c)){
	/* on entre dans un mot, on le compte */
	etat = ETAT_IN_WORD;
	wc++;
      }
    case ETAT_IN_WORD:
      if (! isalpha(c)){
	/* on sort d’un mot */
	etat = ETAT_OUT_WORD;
      }
    }
  }

  printf("%d mots\n", wc);

  exit(EXIT_SUCCESS);
}
