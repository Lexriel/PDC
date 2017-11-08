# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

int main(int argc, char *argv[])
{
  int ww, c;
  enum {DANS_UN_MOT, HORS_MOT} etat;
  ww = 0; /* number of words */
  etat = HORS_MOT;

  while ((c = getchar()) != EOF)
    {
      switch(etat)
	{
	case HORS_MOT:
	  if (isalpha(c)) /* On rentre dans un mot, on le compte. */
	    {

	      ww++;
	      etat = DANS_UN_MOT;
	    }
	case DANS_UN_MOT:
	  if (!isalpha(c)) /* On sort d'un mot */
	    etat = HORS_MOT;
	}
    }

  printf("%d\n", ww);
  return 0;
}
