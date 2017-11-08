/*

Usage:
% gcc -D CASE3 Quizz_13.c && ./a.out
 avec X=1,2,3

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char           *
remplace(char c, int i)
{

#ifdef CASE1
	char            str[] = "C  fun";
#endif

#ifdef CASE2
	char           *str = (char *) malloc(7 * sizeof(char));
	strcpy(str, "C  fun");
#endif

#ifdef CASE3
	static char     str[] = "C  fun";
#endif

	/* C'est ici que l'on veut ins\'erer la ligne */
	str[i] = c;
	return str;
}

int
main(void)
{
	char           *chaine = remplace(' ', 2);
	chaine = remplace('n', 0);
	chaine = remplace('o', 1);
	printf("%s\n", chaine);
	return 0;
}
