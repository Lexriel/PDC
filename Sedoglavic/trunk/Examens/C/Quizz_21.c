#include <stdio.h>
#define PRECEDENTE 1
#define ACTUELLE 2
#define PROCHAINE 3

/**
* \defgroup switch
* \brief illustre l'utilisation du break
* \ingroup switch
*/

void
                Quizz_21
                (void) {
	int             annee = ACTUELLE;
	switch (annee) {
	case PRECEDENTE:
		annee = 2007;
	case ACTUELLE:
		annee = 2008;
	case PROCHAINE:
		annee = 2009;
	default:
		annee = 2010;
	}
	printf("Bonne annee %d\n", annee);
	return 0;
}
