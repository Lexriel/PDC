#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c;
    enum {ETAT_DBT_LIGNE, ETAT_NORMAL, ETAT_DEB_COM, ETAT_COM_TYP, ETAT_FIN_COM } etat = ETAT_DBT_LIGNE;

   /* int nbIndent = 0;*/

    while ((c=getchar()) != EOF) {
        switch (etat) {

        /*etat DEBUT LIGNE*/
        case ETAT_DBT_LIGNE:
            switch (c) {
            case ' ':
            case '\t':
                break;
            case '\\' :
                putchar(c);
                etat = ETAT_DEB_COM;
                break;
            default:
                putchar(c);
                etat = ETAT_NORMAL;
                break;
            }
            break;

        /*ETAT NORMAL*/
        case ETAT_NORMAL:
            switch (c) {
            case '\n':
            case '{' :
                putchar('\n');
                etat=ETAT_DBT_LIGNE;
                break;
            default :
                putchar(c);
                break;
            }
            break;

        /*ETAT DEBUT COM*/
        case ETAT_DEB_COM :
            switch(c)
            {
            case '*' :
                putchar(c);
                etat = ETAT_COM_TYP;
                break;
             default :
                putchar(c);
                etat = ETAT_NORMAL;
                break;
            }
            break;

            /*ETAT COM*/
          case ETAT_COM_TYP :
            switch(c)
            {
            case '\n':
                putchar(c);
                etat = ETAT_DBT_LIGNE;
                break;
            default :
                putchar(c);
                break;
            }
            break;


            /*ETAT FIN COM*/
          case ETAT_FIN_COM :
            switch(c)
            {
            case '\\':
                putchar(c);
                etat = ETAT_NORMAL;
                break;
            default :
                putchar(c);
                etat = ETAT_COM_TYP;
                break;
            }
            break;




        }
    }

    return 0;
}

void indent(int nb)
{
    int i;
    for(i = 0; i < nb ; i++ )
        putchar('\t');
}
