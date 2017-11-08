#include<stdio.h>
#include<stdlib.h>

void 
puttab
(int countTab)
{
	int i;
	for(i=0;i<countTab;i++)
	{
		putchar(' ');
		putchar(' ');
		putchar(' ');
		putchar(' ');
	}
}

int
main
(void)
{
	int c;
	int countTab;
	int etat;
	
	countTab = 0;
	etat = 0;
	/*
	etat=0 : debut de ligne
	etat=1 : ligne normal
	*/
	
		while((c = getchar())!= EOF)
		{
			switch (etat) 
			{
				case 0:
	   				switch (c) 
	   				{
	   					case ' ':
	   					case '\t':
							puttab(countTab);
							putchar(c);
							break;
						default:
	   						putchar(c);
							etat = 1;
							break;
	  				}
	  				break;
	  			case 1:
					switch(c)
					{
						case '\n':
						    putchar('\n');
						    etat=0;
						    break;
						case ';':
							putchar(c);
							putchar('\n');
							puttab(countTab);
							break;
					
						case '{':
							putchar('\n');
							puttab(countTab);
							putchar(c);
							putchar('\n');
							countTab++;
							puttab(countTab);
							break;

						case '}':
							countTab--;
							putchar('\n');
							puttab(countTab);
							putchar(c);
							putchar('\n');
				   			puttab(countTab);
							break;

						default:
						  	putchar(c);
							break;
					}
			}
	}
	exit(EXIT_SUCCESS);
}