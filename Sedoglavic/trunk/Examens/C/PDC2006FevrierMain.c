#include "sub.h"
#include <stdio.h>
int             a, b;
int
main(void)
{
	int             c;
	a = 1;
	b = 2;
	c = 3;
	{
		int             c;
		a = 5;
		b = 6;
		c = 7;
		printf("%d %d %d\n", a, b, c);
		f(c);
		printf("%d %d %d\n", a, b, c);
	}
	printf("%d %d %d\n", a, b, c);
	f(c);
	printf("%d %d %d\n", a, b, c);
	return 0;
}
