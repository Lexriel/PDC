#include <stdio.h>
int
p1(int a)
{
	a = a * 2;
	return a + 5;
}
int
p2(int *b)
{
	*b = *b * 2;
	return *b + 5;
}
int
p3(int *c)
{
	return p1(p2(c));
}
int
main(void)
{
	int             a = 2, b = 3, c = 4;
	int             ra, rb, rc;
	ra = p1(a);
	rb = p2(&b);
	rc = p3(&c);
	printf("%d, %d, %d\n", ra, rb, rc);
	return 0;
}
