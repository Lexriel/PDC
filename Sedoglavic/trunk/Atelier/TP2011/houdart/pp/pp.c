/**Eglantine HOUDART-
TP2 Pretty printer.*/

#include <stdio.h>
#include <stdlib.h>


void 
indenter
(int indentcour)
{
int i;int c;
for (i=0; i<indentcour; i++)
	{
	c= ' '; 
	putchar(c); 
	}
}

int
main()
{
int c;
int indentation =0;
int parouverte = 0;
int indentationfaite = 0;

enum {ETAT_DBT_LIGNE, ETAT_NORMAL,PAR_OUVERTE,COMMENTAIRE } 
etat = ETAT_DBT_LIGNE;
while ((c=getchar()) != EOF) 
{
switch (etat) 
	{
	case ETAT_DBT_LIGNE:
		switch (c) 
		{
			case ' ': indentation +=1;  break;
			case '\t': indentation +=4;break;
			case '/': c=getchar();
				/* C'est un commentaire*/
				if (c=='*') 
					{ 
					putchar('\n');
					indenter(indentation);
					putchar ('/'); 
					putchar('*'); 
					etat = COMMENTAIRE; 
					break;
					}
				else  /*Ce n'est pas un commentaire */
					{
					etat = ETAT_NORMAL; 
					putchar ('/'); 
					putchar(c); 
					break;
					}
			case '{': putchar ('\n'); 
				indentation+=4; 
				indenter(indentation); 
				putchar ('{'); 
				etat = PAR_OUVERTE; 
				parouverte += 1 ; 
				break;
			case '\n': putchar (c); 
				etat= ETAT_DBT_LIGNE; 
				break;				
			default:putchar(c);
				etat = ETAT_NORMAL;
				break;

		}
			break;
	case ETAT_NORMAL:
		switch (c)
			{
			case '\n': etat= ETAT_DBT_LIGNE; 
				break;
			case '/': c=getchar();
				/* C'est un commentaire*/
				if (c=='*') 
					{ 
					putchar('\n');
					indenter(indentation); 
					putchar ('/'); 
					putchar('*'); 
					etat = COMMENTAIRE; 
					break;
					}
				else  /*Ce n'est pas un commentaire */
					{
					etat = ETAT_NORMAL;
					putchar ('/'); 
					putchar(c); 
					break;
					}
			case '{': putchar ('\n'); 
				indentation+=4; 
				etat = PAR_OUVERTE; 
				parouverte += 1 ; 
				indenter(indentation); 
				putchar ('{');  
				etat = PAR_OUVERTE; 
				break;
			case '}': parouverte-=1; 
				putchar(c);			
			default: putchar(c);
				etat = ETAT_NORMAL; 
				break;
			}
			break;
	case COMMENTAIRE: /* Traitement du commentaire */
		switch(c)
			{
			case '*': if ((c=getchar()) == '/')
					{ 
					putchar('*'); 
					putchar(c); 
					etat = ETAT_DBT_LIGNE; 
					if ((c=getchar()) == '\n') 
						{
						} 
						else
						{  
						putchar(c);
						}  
					break; 
					}
				else 
				{
				putchar('*');
				break;
				}
			case '\n': putchar ('*');
				putchar('/'); 
				putchar (c); 
				indenter(indentation);
				putchar ('/'); 
				putchar('*'); 
				break;
			default: putchar(c);
				break;
			}
			break;				 	
	case PAR_OUVERTE: 
		switch (c)
			{
			case '\n': putchar(c);
				c=getchar(); 
				switch(c)
					{
					case ' ': indentation+=1;break;
					case'\t': indentation +=4;break;
					case '{':indentation+=4;
						indenter(indentation);
						putchar(c); 
						putchar('\n'); 
						parouverte+=1; 
						etat = PAR_OUVERTE;
						indentationfaite =0;
						break;
					case '}' : putchar('\n');
						indenter(indentation);
						putchar(c);
						indentation-=4;
						parouverte = parouverte -1;
						break;
						if (parouverte <0) 
							{ 
							fputs ("Il manque une parenthèse ouverte" ,stderr); 
							break;
							}
						if (parouverte ==0)
							{
							etat = ETAT_DBT_LIGNE;
							break;
							}
					default : indenter(indentation); 
						putchar(c); 
						indentationfaite =1;
						break;
					} 
					break;				
			case '}' : putchar('\n');
				indenter(indentation);
				putchar(c);
				indentation-=4;
				parouverte = parouverte -1;
				break;
				if (parouverte ==0)
					{
					etat = ETAT_DBT_LIGNE;
					break;
					}
			case '{':indentation+=4;
				putchar('\n');
				indenter(indentation);
				putchar(c); 
				putchar('\n'); 
				parouverte +=1;
				etat = PAR_OUVERTE;
				indentationfaite = 0;
				break;
			case '/':c=getchar();
				/* C'est un commentaire*/
				if (c=='*') 
					{
					putchar('\n');
					indenter(indentation); 
					putchar ('/'); 
					putchar('*');
					etat = COMMENTAIRE; 
					break;
					}
				else  /*Ce n'est pas un commentaire */
					{
					etat = PAR_OUVERTE; 
					putchar ('/'); 
					putchar(c); 
					break;
					}
			default: if (indentationfaite == 0)
					{
					indenter(indentation); 
					indentationfaite =1;
					} 
				putchar(c);
				break;
				}
			break;

	}
}
/* signalement des erreurs de parenthésage*/
if (parouverte >=1) 
	{
	fputs ("Il y a une (des) parenthèse(s) ouverte(s) en trop\n" ,stderr);
	}
if (parouverte <0) 
	{
	fputs ("Il y a une (des) parenthèse(s) fermée(s) en trop\n" ,stderr);
	}
exit(EXIT_SUCCESS);
}
