#include <stdio.h>
int             x;
static int      y;
void
affectation(void)
{
	x = 2;
	y = 3;
}
void
choix(int a)
{
	int             x = 1;
	static int      y;
	if (a == 0)
		y = 0;
	else
		y += x;
	printf("choix: %d %d\n", x, y);
}

void 
proc1(void)
{
	printf("proc1: %d %d\n", x, y);
}
