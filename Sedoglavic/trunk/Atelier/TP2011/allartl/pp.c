#include <stdio.h>
#include <stdlib.h>

typedef enum etat {ETAT_DEB_LIGNE, ETAT_NORMAL, ETAT_STRING, ETAT_MACRO, ETAT_DEB_COM, ETAT_FIN_COM, ETAT_COM, ETAT_COM_DEB_SPACE, ETAT_FIN_LIGNE} etat;

/* structure servant à se souvenir de l'état précédent */
typedef struct pp_struct
{
    etat etat;
    unsigned int accolades;
} pp_struct;

/* traite le caractère passé en paramètre, peut éventuellement envoyer un message d'erreur sur stderr */
void pp_next_char(pp_struct* pp_struct, int c);
/* traite l'état final de pp, affichant les erreurs sur strerr si nécessaire et renvoyant EXIT_SUCCESS ou EXIT_FAILURE */
int pp_end_state(pp_struct* pp_struct);

int main(int argc, char** argv)
{
    int c;

    pp_struct pp_struct;
    pp_struct.etat = ETAT_DEB_LIGNE;
    pp_struct.accolades = 0;

    while ((c=getchar()) != EOF)
    {
        pp_next_char(&pp_struct, c);
    }

    return pp_end_state(&pp_struct);
}

void pp_next_char(pp_struct* pp_struct, int c)
{
    int i;

    switch (pp_struct->etat)
    {
        /* Blancs -> supprimés
        * 1 tabulation par accolade ouvrante
        * fin instruction -> nouvelle ligne
        */
        case ETAT_DEB_LIGNE:
            switch (c) {
                case ' ':
                case '\t':
                    break;

                case '\n':
                    putchar(c);
                    break;

                case '/':
                    for (i = 0; i < pp_struct->accolades; ++i)
                        putchar('\t');
                    pp_struct->etat = ETAT_DEB_COM;
                    putchar(c);
                    break;

                case '}':
                    --pp_struct->accolades;
                    for (i = 0; i < pp_struct->accolades; ++i)
                        putchar('\t');
                    putchar(c);
                    pp_struct->etat = ETAT_FIN_LIGNE;
                    break;

                case '{':
                    for (i = 0; i < pp_struct->accolades; ++i)
                        putchar('\t');
                    ++pp_struct->accolades;
                    putchar(c);
                    pp_struct->etat = ETAT_FIN_LIGNE;
                    break;

                case '#':
                    putchar(c);
                    pp_struct->etat = ETAT_MACRO;
                    break;

                default:
                    for (i = 0; i < pp_struct->accolades; ++i)
                        putchar('\t');

                    /* On retraite le caractère avec le nouvel état */
                    pp_struct->etat = ETAT_NORMAL;
                    pp_next_char(pp_struct, c);
                    break;
            }
            break;

        /* changement d'états : début string, début commentaire, fin de ligne, fin d'instruction
        * nouvelle ligne si fin d'instruction
        */
        case ETAT_NORMAL:
            switch (c) {
                case '\n':
                    putchar(c);
                    pp_struct->etat = ETAT_DEB_LIGNE;
                    break;

                case '"':
                    putchar(c);
                    pp_struct->etat = ETAT_STRING;
                    break;

                case ';':
                    putchar(c);
                    pp_struct->etat = ETAT_FIN_LIGNE;
                    break;

                case '{':
                case '}':
                case '/':
                    putchar('\n');
                    pp_struct->etat = ETAT_DEB_LIGNE;
                    pp_next_char(pp_struct, c);
                    break;

                default :
                    putchar(c);
                    break;
            }
            break;

	/* On écrase le prochain '\n' ou en place un s'il n'existe pas. Cas particulier : les environnements qui utilisent CRLF */
        case ETAT_FIN_LIGNE:
            switch (c)
            {
                case '\n':
                    putchar(c);
                    pp_struct->etat = ETAT_DEB_LIGNE;
                    break;

		case '\r':
                    break;

                default:
                    putchar('\n');
                    pp_struct->etat = ETAT_DEB_LIGNE;
                    pp_next_char(pp_struct, c);
                    break;
            }
            break;

        /* fin de macro quand nouvelle ligne, char remis tel quoiqu'il arrive
        */
        case ETAT_MACRO:
            switch (c)
            {
                case '\n':
                    pp_struct->etat = ETAT_DEB_LIGNE;
                    putchar(c);
                    break;

                default:
                    putchar(c);
                    break;
            }
            break;

        /* changement d'état si le string est cloturé ou en cas de nouvelle ligne (erreur dans ce cas là)
        */
        case ETAT_STRING:
            switch (c)
            {
                case '\n':
                    fprintf(stderr, "warning: string non cloturé par un '\"'.\n");
                    pp_struct->etat = ETAT_DEB_LIGNE;
                    putchar(c);
                    break;

                case '"':
                    pp_struct->etat = ETAT_NORMAL;
                    putchar(c);
                    break;

                default:
                    putchar(c);
                    break;
            }
            break;

        /* On ouvre peut-être un commentaire, traitement normal sinon
        */
        case ETAT_DEB_COM:
            switch (c)
            {
                case '*':
                    pp_struct->etat = ETAT_COM_DEB_SPACE;
                    putchar(c);
                    putchar(' ');
                    break;

                default:
                    pp_struct->etat = ETAT_NORMAL;
                    pp_next_char(pp_struct, c);
                    break;
            }
            break;

        /* On ferme peut-être un commentaire, traitement pour commentaires sinon
        */
        case ETAT_FIN_COM:
            switch (c)
            {
                case '/':
                    pp_struct->etat = ETAT_FIN_LIGNE;
                    putchar(c);
                    break;

                default:
                    pp_struct->etat = ETAT_COM;
                    pp_next_char(pp_struct, c);
                    break;
            }
            break;

	/* On ignore les espaces en début de commentaire */
        case ETAT_COM_DEB_SPACE:
            switch (c)
            {
                case ' ':
                    break;

                default:
                    pp_struct->etat = ETAT_FIN_COM;
                    pp_next_char(pp_struct, c);
            }
        break;

	/* On remet tout tel quel, sauf en cas de retour à la ligne et si le symbole '*' apparait pour une fin de commentaire.
	Cas particulier : CRLF */
        case ETAT_COM:
            switch (c)
            {
		case '\r':
		    break;

                case '\n':
                    puts(" */");
                    pp_struct->etat = ETAT_DEB_LIGNE;
                    pp_next_char(pp_struct, '/');
                    pp_next_char(pp_struct, '*');
                    break;

                case '*':
                    pp_struct->etat = ETAT_FIN_COM;
                    putchar(c);
                    break;

                default:
                    putchar(c);
                    break;
            }
            break;


    }
}

int pp_end_state(pp_struct* pp_struct)
{
    int end_state = EXIT_SUCCESS;

    if (pp_struct->accolades > 0)
    {
        fprintf(stderr, "warning: accolade non fermée.\n");
        end_state = EXIT_FAILURE;
    }
    else if (pp_struct->accolades < 0)
    {
        fprintf(stderr, "warning: accolade fermante sans accolade ouvrante.\n");
        end_state = EXIT_FAILURE;
    }

    switch (pp_struct->etat)
    {
        case ETAT_STRING:
            fprintf(stderr, "warning: string non cloturé en fin de fichier.\n");
            end_state = EXIT_FAILURE;
            break;

        case ETAT_DEB_COM:
            fprintf(stderr, "warning: '/' en fin de fichier.\n");
            end_state = EXIT_FAILURE;
            break;

	case ETAT_COM_DEB_SPACE:
        case ETAT_COM:
        case ETAT_FIN_COM:
            fprintf(stderr, "warning: commentaire non cloturé en fin de fichier.\n");
            end_state = EXIT_FAILURE;
            break;

        default:
            break;
    }

    return end_state;
}
