#include <stdio.h>

void indenter(int indent)
{
	int i;
	for (i = 0; i < indent; ++i)
		putchar('\t');
}

int main()
{
	char c;
	int indent;
	enum {ETAT_DBT_LIGNE, ETAT_NORMAL } etat = ETAT_DBT_LIGNE;
	enum {COMM_AUCUN, COMM_DBT_POSSIBLE, COMM_EN_COURS, COMM_FIN_POSSIBLE } commentaires = COMM_AUCUN;
	
	indent = 0;

	while ((c = getchar()) != EOF)
	{
		if (commentaires == COMM_DBT_POSSIBLE && c != '*')
		{
			putchar('/');
			commentaires = COMM_AUCUN;
		}
		if (commentaires == COMM_FIN_POSSIBLE && c != '/')
		{
			putchar('*');
			commentaires = COMM_AUCUN;
		}

		switch(c)
		{
			case '\n':
				if (commentaires == COMM_EN_COURS)
				{
					putchar(' '); putchar('*'); putchar('/');
					putchar(c);
					indenter(indent);
					putchar('/'); putchar('*'); putchar(' ');
					etat = ETAT_DBT_LIGNE;
				}
				else
				{
					etat = ETAT_DBT_LIGNE;
					putchar(c);
				}
				break;
			case ' ':
			case '\t':
				if (etat == ETAT_NORMAL)
					putchar(c);
				break;
			case '{':
				if (etat == ETAT_NORMAL)
				{
					putchar('\n');
				}
				indenter(indent);
				putchar(c);
				putchar('\n');
				++indent;
				etat = ETAT_DBT_LIGNE;
				break;
			case '}':
				--indent;
				if (etat == ETAT_NORMAL)
				{
					putchar('\n');
					indenter(indent);
				}
				
				putchar(c);
				putchar('\n');
				etat = ETAT_DBT_LIGNE;
				break;
			case '/':
				if (commentaires == COMM_FIN_POSSIBLE)
				{
					commentaires = COMM_AUCUN;
                    putchar(' '); putchar('*'); putchar(c); putchar('\n');
                    indenter(indent);
                    etat = ETAT_DBT_LIGNE;
				}
				else
					commentaires = COMM_DBT_POSSIBLE;
				break;
			case '*':
				if (commentaires == COMM_DBT_POSSIBLE)
				{
					commentaires = COMM_EN_COURS;
					if (etat == ETAT_NORMAL)
					{
						putchar('\n');
						indenter(indent);
					}
                    putchar('/'); putchar(c); putchar(' ');
				}
				else
					commentaires = COMM_FIN_POSSIBLE;
				break;
			default:
				if (etat == ETAT_DBT_LIGNE)
				{
					if (commentaires != COMM_EN_COURS)
						indenter(indent);
					etat = ETAT_NORMAL;
				}
				putchar(c);
		}
		
	}
	return 0;
}
