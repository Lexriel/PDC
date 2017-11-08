#include<stdio.h>
#include<stdlib.h>



/* Méthode permettant d'afficher le nombre de tabulations nécessaires au bon alignement du code. */
void afficheTab (int nombreTab)
{
	int i;
	for (i = 0; i < nombreTab; i++)
	{
 		putchar('\t');
    }
}



int main (void)
{
	char c;
	int nombreDeTabulation;
	int i;

	/* Pas de tabulation par défaut */
	nombreDeTabulation = 0;
	i = 0;

	/* On effectue les vérifications jusqu'à ce qu'on arrive à la fin du fichier. */
	while ((c = getchar()) != EOF)
	{
		switch (c)
		{
			/* 
			 * Si le caractère est une accolade ouvrante :
			 * On retourne à la ligne et on affiche le nombre de tabulations courant
			 * On affiche l'accolade
			 * On retourne à la ligne
			 * On affiche une tabulation supplémentaire
			 */
			case '{':
				putchar('\n');
	  			afficheTab(nombreDeTabulation);
				putchar(c);
				putchar('\n');
				nombreDeTabulation++;
				afficheTab(nombreDeTabulation);
				break;
			/* 
			 * Si le caractère est une accolade fermante :
			 * On retourne à la ligne
			 * On retire une tabulation
			 * On affiche l'accolade
			 * On retourne à la ligne
			 */
			case '}':
				putchar('\n');
				nombreDeTabulation--;
               	afficheTab(nombreDeTabulation);
				putchar(c);
                putchar('\n');
   				afficheTab(nombreDeTabulation);
				break;
			/* 
			 * Si le caractère est une fin d'instruction :
			 * On affiche le point virgule
			 * On retourne à la ligne
			 * On affiche le nombre de tabulations courant
			 */
			case ';':
				putchar(c);
				putchar('\n');
				afficheTab(nombreDeTabulation);
				break;
			/*
			 * Si le caractère est un #, on a une directive préprocesseur
			 */
			case '#':
				putchar(c);
				while (c != ';' && c != '>')
				{
					c = getchar();
					putchar(c);
				}
				putchar('\n');
				break;
			/*
			 * Si le caractère est un /, on vérifie s'il est suivi d'un *, auquel cas c'est un commentaire.
			 * On cherche la prochaine occurence de * suivi d'un /, on passe à la ligne et on aligne les tabulations.
			 */
			case '/':
				putchar(c);
				c = getchar();
				if (c == '*')
				{
					while (1 == 1)
					{
						putchar(c);
						c = getchar();
						if (c == '*')
						{
							putchar(c);
							c = getchar();
							if (c == '/')
							{
								putchar(c);
								putchar('\n');
								afficheTab(nombreDeTabulation);
								break;
							}
						}
					}
				}
				else
				{
					putchar(c);
				}
				break;
			/* 
			 * Si le caractère est un caractère "banal", on l'affiche sans le modifier
			 */
			default:
				putchar(c);
        		break;
		}
	}

	return 0;
}