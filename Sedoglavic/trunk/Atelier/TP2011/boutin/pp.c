#include <stdio.h>
#include <stdlib.h>

int 
main()
{
    int c;
    int j;
    int tab = 0;
    enum {ETAT_DBT_LIGNE, ETAT_NORMAL, ETAT_ACO, ETAT_COM, ETAT_SLASH } etat = ETAT_DBT_LIGNE;
  
    while ((c=getchar()) != EOF) {
        switch (etat) {
            case ETAT_DBT_LIGNE:
                switch (c) {
                    case ' ':

                    case '\t':
                        break;

		    case '\n':
			putchar(c);
			break;

		    case '{':
			for(j = 0; j != tab; j++) putchar('\t');
			putchar(c);
                        etat = ETAT_ACO;
			tab++;
			break;

		    case '}':
  			tab--;
			for(j = 0; j != tab; j++) putchar('\t');
			putchar(c);
                        etat = ETAT_ACO;
			break;

                    default:   
			for(j = 0; j != tab; j++) putchar('\t');
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
			putchar('\n');
			for(j = 0; j != tab; j++) putchar('\t');
			putchar(c);
                        etat = ETAT_ACO;
			tab++;
			break;

 		    case '}':
			putchar('\n');
			tab--;
			for(j = 0; j != tab; j++) putchar('\t');
			putchar(c);
                        etat = ETAT_ACO;
			break;
		    case '/':
  			etat= ETAT_SLASH;
			break;
                    default :  
                        putchar(c);
                        break;
                }
		break;

	 case ETAT_ACO:
		switch (c) {
                    case '\n':
			putchar('\n');
                        etat=ETAT_DBT_LIGNE;
                        break;

		    default : 
			putchar('\n'); 
			for(j = 0; j != tab; j++) putchar('\t');
                        putchar(c);
			etat = ETAT_NORMAL;
                        break;
		}
		break;
	case ETAT_SLASH:
		switch (c) {
                    case '*':
			putchar('\n');
			for(j = 0; j != tab; j++) putchar('\t');
			putchar('/'); 
			putchar(c);
			etat = ETAT_COM;
			break;

		    default : 
			putchar('/'); 
			putchar(c);
			etat = ETAT_NORMAL;
                        break;
		}
		break;
	case ETAT_COM:
		switch (c) {

                    case '\n':
			putchar('*');
			putchar('/');
			putchar(c);
			for(j = 0; j != tab; j++) putchar('\t');
			putchar('/'); 
			putchar('*');
			break;

		    case '*':
			if(( c= getchar()) == '/')
			{
				putchar('*');
				putchar(c);
				putchar('\n');
				etat = ETAT_DBT_LIGNE;
			}
			else
			{
				putchar('*');
				putchar(c);
			}
			break;

		    default :  
			putchar(c);
                        break;
		}
		break;
        }
    }

    exit(EXIT_SUCCESS);
}

