#include <stdio.h>

void
f(int **i)
{
	*((*i)++) += 1;
}
int
main(void)
{
	int             i[5] = {0, 2, 4, 6, 8}, *p = i;
	for (; *p != 8;)
		f(&p);
	printf("%d %d\n", i[0], *p);
	return 0;
}