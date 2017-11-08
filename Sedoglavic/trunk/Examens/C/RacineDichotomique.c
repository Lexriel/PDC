#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 5

typedef double  (*pfct_t) (double);



double
                fct
                (double x) {
	return (x - 2) * (x - 3) * (x - 1 / 100.);
	return (x + 0.99) * (x + 1.01) * (x - 0.99) * (x + 1.01) * (x + 1.4);
	return (x + 3.45) * (x - 0.2) * (x + 5.59) * (x - 1.22) * (x + 6.54);	/* (x - 11.4) * (x -
										 * 45.3)   */
}

char           *
                Double2Intervalle
                (double a, double b) {
	char           *dest;
	dest = (char *) malloc(37 * sizeof(char));
	sprintf(dest, " [%.10e,%.10e]\0", a,b);
	return dest;
}

char           *
                racine
                (double a, double b, double e, pfct_t f) {
	char           *res[n], *dest;
	int             i, j, k;

	if (a > b)
		exit(2);

	if (f(a) * f(b) > 0)
		return "";

	if ((b - a) < e)
		return Double2Intervalle(a, b);

	for (j = i = 0; i < n; i++) {
		res[i] = racine(((n - i) * a + i * b) / n, ((n - (i + 1)) * a + (i + 1) * b) / n, e, f);
		for (k = 0; res[i][k]; k++);
		j += k;
	}

	dest = (char *) malloc((j + 1) * sizeof(char));

	i = 0;
	for (k = 0; k < n; k++)
		for (j = 0; dest[i] = res[k][j]; j++, i++);

	for (i = 0; i < n; i++)
		if (res[i][0])
			free(res[i]);

	return dest;
}


int
                main
                (void) {
	printf("%s\n", racine(0, 6, 1. / 1000., fct));
	return 0;
}
