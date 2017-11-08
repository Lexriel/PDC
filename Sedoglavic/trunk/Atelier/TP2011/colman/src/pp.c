#include <stdio.h>
#include <stdlib.h>

void indent(int degresIndent) {
    int i = 0;

    if(degresIndent > 0) {
        for(i ; i < (degresIndent*4) ; i++) {
            putchar(' ');
        }
    }
}

int main()
{
    int c;
    int nbAcolOuvrante = 0, nbAcolFermante = 0;
    int degresIndent = 0;
    int commentaire = 0;
    enum {ETAT_DBT_LIGNE, ETAT_NORMAL, COMMENTAIRE, CH_LIT, CARAC} etat = ETAT_DBT_LIGNE;

    while ((c=getchar()) != EOF) {
        switch (etat) {
            case ETAT_DBT_LIGNE:
                switch (c) {
                    case ' ':
                        break;
                    case '\t':
                        break;
                    case '\n':
                        putchar(c);
                        break;
                    case '{':
                        nbAcolOuvrante++;
                        indent(degresIndent);
                        putchar(c);
                        putchar('\n');
                        degresIndent++;
                        break;
                    case '}':
                        nbAcolFermante++;
                        degresIndent--;
                        indent(degresIndent);
                        putchar(c);
                        putchar('\n');
                        break;
                    case '/':
                        commentaire++;
                        indent(degresIndent);
                        putchar(c);
                        etat = COMMENTAIRE;
                        break;
                    default:
                        indent(degresIndent);
                        putchar(c);
                        etat = ETAT_NORMAL;
                        break;
               }
                break;
            case ETAT_NORMAL:
                switch (c) {
                    case '\n':
                        putchar('\n');
                        etat=ETAT_DBT_LIGNE;
                        break;
                    case '{':
                        nbAcolOuvrante++;
                        putchar('\n');
                        indent(degresIndent);
                        putchar(c);
                        putchar('\n');
                        degresIndent++;
                        etat = ETAT_DBT_LIGNE;
                        break;
                    case '}':
                        nbAcolFermante++;
                        degresIndent--;
                        putchar('\n');
                        indent(degresIndent);
                        putchar(c);
                        putchar('\n');
                        etat = ETAT_DBT_LIGNE;
                        break;
                    case '/':
                        commentaire++;
                        putchar('\n');
                        indent(degresIndent);
                        putchar(c);
                        etat = COMMENTAIRE;
                        break;
                    case '"':
                        putchar(c);
                        etat = CH_LIT;
                        break;
                    case '\'':
                        putchar(c);
                        etat = CARAC;
                        break;

                    default :
                        putchar(c);
                        etat = ETAT_NORMAL;
                        break;
                }
                break;
            case COMMENTAIRE:
                switch(c) {
                    case '/':
                        commentaire++;
                        putchar(c);
                        putchar('\n');
                        etat = ETAT_NORMAL;
                        break;
                    case '\n':
                        putchar('*');
                        putchar('/');
                        putchar(c);
                        indent(degresIndent);
                        putchar('/');
                        putchar('*');
                        break;
                    default:
                        putchar(c);
                        break;
                }
                break;
            /* Case chaine littérale */
            case CH_LIT:
                switch(c) {
                    case '"':
                        putchar(c);
                        etat = ETAT_NORMAL;
                        break;
                    default:
                        putchar(c);
                        break;
                }
                break;
            case CARAC:
                switch(c) {
                    case '\\':
                        putchar(c);
                        c = getchar();
                        putchar(c);
                        break;
                    case'\'':
                        putchar(c);
                        etat = ETAT_NORMAL;
                        break;
                    default:
                        putchar(c);
                        break;
                }
                break;

        }

    }
    if((commentaire%2) != 0) {
        fprintf(stderr, "Texte mal commenté : %s\n");
    }
    if(nbAcolOuvrante != nbAcolFermante) {
        fprintf(stderr, "Texte mal 'acolladé' : %s\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
    return 0;
}
