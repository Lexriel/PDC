#include <stdio.h>
#include <stdlib.h>


void
indentation(int x) /* x etant le nombre de tabulation (4 espace) */
{
    int i;
    for(i=0; i<x; i++)
    {
        putchar(' ');
        putchar(' ');
        putchar(' ');
        putchar(' ');
    }
}

int
main()
{
    int exit;
    int indent;
    int c,previous_c;
    
    enum {ETAT_DBT_LIGNE, ETAT_NORMAL, ETAT_PE_COMMENTAIRE, ETAT_COMMENTAIRE, ETAT_PE_FIN_COMMENTAIRE} etat = ETAT_DBT_LIGNE, previous_etat;

    exit = EXIT_SUCCESS;
    indent = 0;

    while ((c=getchar()) != EOF) {
        switch (etat) {
        case ETAT_DBT_LIGNE:
            switch (c) {
            case '#':
                do
                {
                    putchar(c);
                    c=getchar();
                }
                while (c != '\n' && c != EOF);
                putchar(c);
                break;

            case '{':
                indentation(indent); /*indentation*/
                putchar(c);
                indent++;
                putchar('\n');
                break;

            case '}':
                indent--;
                indentation(indent); /*indentation*/
                putchar(c);
                putchar('\n');
                break;

            case '\n':
                switch(previous_c)
                {
                case '{':
                case '}':
                case ';':
                case '/':
                    break;
                default:
                    putchar('\n');
                    break;
                }
                break;

            case ' ':
            case '\t':
                break;
            
            case '/':
                previous_c = c;
                etat = ETAT_PE_COMMENTAIRE;
                break;

            default:
                indentation(indent); /*indentation*/
                putchar(c);
                etat = ETAT_NORMAL;
                break;
            }
            break;

        case ETAT_NORMAL:
            switch (c) {
            case '{':
                putchar('\n');
                indentation(indent); /*indentation*/
                putchar(c);
                indent++;
                putchar('\n');
                etat = ETAT_DBT_LIGNE;
                break;

            case '}':
                putchar('\n');
                indent--;
                indentation(indent); /*indentation*/
                putchar(c);
                break;

            case '\n':
                putchar('\n');
                etat=ETAT_DBT_LIGNE;
                break;

            case '\'':
                putchar('\'');
                break;

            case '/':
                previous_c = c;
                previous_etat = etat;
                etat = ETAT_PE_COMMENTAIRE;
                break;

            case ';':
                putchar(c);
                previous_c = c;
                putchar('\n');
                etat = ETAT_DBT_LIGNE;
                break;

            default :
                putchar(c);
                break;
            }
            break;
        case ETAT_PE_COMMENTAIRE:
            switch (c) {
            case '*':
                if(previous_etat == ETAT_NORMAL)
                    putchar('\n');
                indentation(indent); /*indentation*/
                putchar(previous_c); /* print '/' */
                putchar('*'); /* print '*' */
                etat=ETAT_COMMENTAIRE;
                break;
                
            case '\n':
                putchar(previous_c);
                putchar(c);
                etat = ETAT_DBT_LIGNE;
                break;

            default :
                putchar(previous_c);
                putchar(c);
                etat = ETAT_NORMAL;
                break;
            }
            break;

        case ETAT_COMMENTAIRE:
            switch (c) {
            case '\n':
                putchar(c);
                indentation(indent);
                break;
            
            case '*':
                putchar(c);
                etat = ETAT_PE_FIN_COMMENTAIRE;
                break;
                
            case '\t':
                break;

            default :
                putchar(c);
                break;
            }
            break;


        case ETAT_PE_FIN_COMMENTAIRE:
            switch (c) {
            case '/':               
                putchar(c);
                putchar('\n');
                previous_c = c;
                etat = ETAT_DBT_LIGNE;
                break;

            case '*':
                putchar('*');
                break;
            
            default :
                putchar(c);
                etat = ETAT_COMMENTAIRE;
                break;
            }
            break;
        
        }
    }
    switch (etat)
    {
    case ETAT_COMMENTAIRE:
    case ETAT_PE_FIN_COMMENTAIRE:
        fprintf(stderr, "Err: Commentaire non fermé.\n");
        exit = EXIT_FAILURE;
        break;
        
    default:
        break;
    }
    if (indent > 0)
    {
        fprintf(stderr, "Err: Bloc d'instruction non fermé.\n");
        exit = EXIT_FAILURE;
    }
    if (indent < 0)
    {
        fprintf(stderr, "Err: Il y a un '}' en trop.\n");
        exit = EXIT_FAILURE;
    }
    return exit;
}
