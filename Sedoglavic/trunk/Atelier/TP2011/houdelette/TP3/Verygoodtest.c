#include<stdio.h>
int main(void)
{
	char c;
	/* Ceci est un commentaire. */
	while((c=getchar())!=EOF)
	{
		putchar(c);
		
	}
	putc('b',stderr);
	return 0;
	
}
