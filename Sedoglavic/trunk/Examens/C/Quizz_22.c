#include<stdio.h>
char           *string = "La vie est belle\n";
char            otherstring[] = "La vie est belle\n";
int
                main
                (void) {
	if (string == otherstring)
		return 1;
	return 0;
}
