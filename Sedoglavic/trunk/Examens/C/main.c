#include <stdio.h>
extern int      x;
static int      y;

extern void
                affectation(void);
extern void
                choix(int);
extern void
                proc1(void);

void
proc2(void)
{
	printf("proc2: %d %d\n", x, y);
}

int
main(void)
{
	choix(0);
	affectation();
	choix(1);
	proc1();
	proc2();
	return 0;
}
