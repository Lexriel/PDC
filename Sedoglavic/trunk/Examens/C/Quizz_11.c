#include<stdio.h>
char           *
f0(char *a[][3])
{
	return (**a);
}
char           *
f1(char *a[][3])
{
	return (*(*(a + 1) + 2));
}
int
main(void)
{
	char           *(*fcts[2]) (char *tableau[][3]);
	static char    *tableau[][3] =
	{{"0", "1", "2"},
	{"3", "4", "5"},
	{"6", "7", "8"}};
	fcts[0] = &f0;
	fcts[1] = &f1;
	printf("%s\n", (**fcts) (tableau));
	printf("%s\n", (**(fcts + 1)) (tableau + 1));
	return 0;
}