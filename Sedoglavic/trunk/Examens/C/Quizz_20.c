#include<stdio.h>
enum bool {
	false, true
};

int
main(void)
{
	enum bool       test;
	int             i, j;

	for (i = 2; i < 10; i++) {
		test = false;
		j = 2;
		while (!test && j < i) {
			if (i % j == 0)
				test = true;
			j++;
		}
		if (!test)
			putchar(i + '0');
	}
	putchar('\n');
	return 0;
}
