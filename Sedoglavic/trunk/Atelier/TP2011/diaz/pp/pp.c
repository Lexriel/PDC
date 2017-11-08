#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c,dernierChar;
	int indentation=0;
	int commentaire=0;
	int ecrireIndentation=0;
	
    enum {ETAT_DBT_LIGNE, ETAT_NORMAL, ETAT_DIESE, ETAT_CHAINE } etat = ETAT_DBT_LIGNE;
  
    while ((c=getchar()) != EOF)
	{
		switch (etat)
		{
			case ETAT_DBT_LIGNE:
				if(ecrireIndentation == 1)
				{
					int i=0;
					for(i=0;i<indentation*4;i++)
						putchar(' ');
					ecrireIndentation=0;
					if (commentaire==1)
					{
					putchar('/');
                    putchar('*');
					}
				}
			    switch (c)
				{
					case'\n':
					break;
					case ' ':
					break;
					case '\t':
					break;
					default:  
						if(commentaire == 1)
						{
							putchar('/');
							putchar('*');
						}
						putchar(c);
						dernierChar=c;
						etat = ETAT_NORMAL;
					break;
				}
			break;
			case  ETAT_NORMAL:
				switch (c) {
					case ';' :
						putchar(c);
						dernierChar=c;
						putchar('\n');
						ecrireIndentation=1;
						etat=ETAT_DBT_LIGNE;
					break;
                    case '\n' : 
						if(commentaire ==1)
						{
							putchar('*');
							putchar('/');
                        }
						putchar(c);
						dernierChar=c;
						ecrireIndentation=1;
                        etat=ETAT_DBT_LIGNE;
                    break;
					case '"' :
						putchar(c);
						dernierChar=c;
						etat = ETAT_CHAINE;
					break;
					case '#' :
						putchar(c);
						dernierChar=c;
						etat=ETAT_DIESE;
					break;
					case '{':
						if(commentaire ==0)
						{
							putchar(c);
							putchar('\n');
							dernierChar=c;
							indentation++;
							ecrireIndentation=1;
							etat=ETAT_DBT_LIGNE;
						}
						else
						{
							putchar(c);
							dernierChar=c;
						}
					break;
					case '}':
						if(commentaire ==0)
						{						
							putchar(c);
							dernierChar=c;
							putchar('\n');
							indentation--;
							ecrireIndentation=1;
							etat=ETAT_DBT_LIGNE;
						}
						else
						{
							putchar(c);
						}
					break;
					case'/':
						putchar(c);
						if(dernierChar == '*')
						{
							commentaire=0;
							putchar('\n');
							ecrireIndentation=1;
							etat=ETAT_DBT_LIGNE;
						}
						dernierChar=c;
					break;
					case'*':
						putchar(c);
						dernierChar=c;
						if(dernierChar == '/')
						{
							commentaire=1;
						}
					break;
                    default : 
                        putchar(c);
                        dernierChar=c;
					break;
                }
			break;
			case ETAT_DIESE:
			switch(c)
				{
					case('\n'):

						ecrireIndentation=1;
						etat = ETAT_DBT_LIGNE;
						putchar(c);
						dernierChar=c;
						break;
					default:
						putchar(c);
						dernierChar=c;
						break;
				}
			break;
			case ETAT_CHAINE:
			switch(c)
			{
				case('"'):
					putchar(c);
					etat = ETAT_NORMAL;
				break;
				case('\''):
				break;
				case('\n'):
					ecrireIndentation=1;
					etat = ETAT_DBT_LIGNE;
					putchar(c);
				break;
				default:
					putchar(c);
				break;
			}
			break;
		}
	}
	return(1);
}