#include <stdio.h>
#include <stdlib.h>

void
indent
(int nbIndent)
{
    int i;
    i = 0;
    for (i = 0; i < nbIndent; i++)
    {
        putchar ('\t');
    }
}

int
main
(void)
{
    typedef enum {ETAT_DBT_LIGNE, ETAT_NORMAL, OUVERT, FERMER, CHAR} etatsPossibles;
    etatsPossibles etat, etat_prec; 
    int nbIndent;
    char c;
	
	etat = ETAT_DBT_LIGNE;
	
    nbIndent = 0;
	c = getchar ();
	
    while (c != EOF)
    {
        switch(etat)
        {
        case ETAT_DBT_LIGNE : 
            switch(c)
            {
            case ' ' :
            case '\t' :
                break;
            case '\n' :
                putchar(c);
                break;
            case '{' :
            	indent(nbIndent);
                etat = OUVERT;
                continue;
            case '}' :
            	indent(nbIndent);
                etat = FERMER;
                continue;
            case '\'' :
            	indent(nbIndent);
                etat = CHAR;
                continue;
            default :
            	indent(nbIndent);
                etat = ETAT_NORMAL;
                continue;
            }
            etat_prec = ETAT_DBT_LIGNE;
            break;
        case ETAT_NORMAL :
            switch(c)
            {
            case '\n' :
                etat = ETAT_DBT_LIGNE;
                continue;
            case '{' :
                etat = OUVERT;
                continue;
            case '}' :
                etat = FERMER;
                continue;
            case '\'' :
                etat = CHAR;
                continue;
            default :
                putchar(c);
                break;
            }
            etat_prec = ETAT_NORMAL;
            break;
        case OUVERT :
        	switch(c)
            {
            case ' ' :
            case '\t' :
                break;
            case '\n' :
                etat = ETAT_DBT_LIGNE;
                continue;
            case '{' :
            	if (etat_prec != ETAT_DBT_LIGNE)
            	{
            		putchar('\n');
            		indent(nbIndent);
            	}
                putchar(c);
                nbIndent++;
                break;
            case '}' :
                etat = FERMER;
                continue;
            case '\'' :
                etat = CHAR;
                continue;
            default :
                etat = ETAT_NORMAL;
                continue;
            }
            etat_prec = OUVERT;
            break;
        case FERMER :
            switch(c)
            {
            case ' ' :
            case '\t' :
                break;
            case '\n' :
                etat = ETAT_DBT_LIGNE;
                continue;
            case '{' :
                etat = OUVERT;
                continue;
            case '}' :
            	nbIndent--;
            	if (etat_prec != ETAT_DBT_LIGNE)
            	{
            		putchar('\n');
            		indent(nbIndent);
            	}
                putchar(c);
                break;
            case '\'' :
                etat = CHAR;
                continue;
            default :
            	putchar('\n');
                etat = ETAT_DBT_LIGNE;
                continue;
            }
            etat_prec = FERMER;
            break;
        case CHAR :
            switch(c)
            {
            case '\'' :
            	putchar(c);
                etat = ETAT_NORMAL;
                break;
            default :
                putchar(c);
                break;
            }
            etat_prec = CHAR;
            break;
        }
        c = getchar ();
    }
    exit (EXIT_SUCCESS);
}
