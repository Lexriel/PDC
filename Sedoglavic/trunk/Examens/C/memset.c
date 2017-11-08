#include<stdio.h>

/**
* \brief implantation de la fonction memset
* \parameter void *s
*/

void           *
                memset
                (void *s, int c, int n) {
	int             i;
	for (i = 0; i < n; i++)
		((char *) s)[i] = c;

	return s;
}

int
                main
                (void) {
	char            tab[] = "C'est chouette";
	printf("%s\n", (char *) memset((void *) tab, '*', 14));
	return 0;
}
