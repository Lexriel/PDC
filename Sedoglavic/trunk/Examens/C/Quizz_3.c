#include <stdio.h>
int
                main
                (void) {
	int             a[8] = {5, 15, 34, 54, 14, 2, 52, 72};
	int            *p = &a[1], *q = &a[5];

	printf("1) %d\n", *(p + 3));
	printf("2) %d\n", q - p);
	printf("3) %d\n", p < q);
	printf("4) %d\n", *p < *q);

	return 0;
}