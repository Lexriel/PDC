#include <stdio.h>
#define N 10

int
                main
                (void) {
	int             i;
	int             tab[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int            *p = &tab[0], *q = &tab[N - 1], temp;
	while (p < q) {
		temp = *p;
		*(p++) = *q;
		*(q--) = temp;
	}

	for (i = 0; i < N; i++)
		printf("%d ", tab[i]);

	putchar('\n');
	return 0;
}