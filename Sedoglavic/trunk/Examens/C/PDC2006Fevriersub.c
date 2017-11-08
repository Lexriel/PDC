#include "sub.h"
#include <stdio.h>
static int      a;
extern int      b;
void
f(int c)
{
	static int      d = 0;
	a = 0;
	b = 0;
	printf("%d %d %d %d\n", a, b, c, d);
	a += 10;
	b += 10;
	c += 10;
	d += 10;
	printf("%d %d %d %d\n", a, b, c, d);
}
