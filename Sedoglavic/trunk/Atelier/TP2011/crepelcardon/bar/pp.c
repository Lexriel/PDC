#include <stdio.h>
#include <stdlib.h>

int 
main()
{
    	int c;
	unsigned int nbtab,i;
	nbtab=0;

    enum {ETAT_DBT_LIGNE, ETAT_NORMAL, COMM} etat = ETAT_DBT_LIGNE;
  
    while ((c=getchar()) != EOF) {
        switch (etat) {
            case ETAT_DBT_LIGNE:
                switch (c) {
                    case ' ':
                    case '\t':
                        break;
		    case '{':
			nbtab++;
			putchar('{');
			putchar('\n');
			etat = ETAT_DBT_LIGNE;
			break;
		    case '}':
			nbtab--;
			putchar('\n');
			for (i=0; i< nbtab; i++) {
				putchar('\t');
			}
			putchar('}');
			putchar('\n');
			etat = ETAT_DBT_LIGNE;
			break;
		    case '/':
			c=getchar();
			if (c=='*'){
				etat=COMM;
				putchar('/');
				putchar(c);
			} else {
				putchar('/');
				putchar(c);
			}
			break;
                    default: 
			for (i=0; i< nbtab; i++) {
				putchar('\t');
			}
                        putchar(c);
                        etat = ETAT_NORMAL;
                        break;
                }
                break;
            case ETAT_NORMAL:
                switch (c) {
		    case '{':
			nbtab++;
			putchar('{');
			putchar('\n');
			etat = ETAT_DBT_LIGNE;
			break;
		    case '}':
			nbtab--;
			putchar('\n');
			for (i=0; i< nbtab; i++) {
				putchar('\t');
			}
			putchar('}');
			putchar('\n');
			etat = ETAT_DBT_LIGNE;
			break;
                    case '\n':
                        putchar('\n');
                        etat=ETAT_DBT_LIGNE;
                        break;
		    case '/':
			c=getchar();
			if (c=='*'){
				etat=COMM;
				putchar('\n');
				putchar('/');
				putchar(c);
			} else {
				putchar('/');
				putchar(c);
			}
			break;
                    default :  
                        putchar(c);
                        break;
                }
		break;
	   case COMM:
		  if (c=='*'){
			c=getchar();
			if (c=='/'){
				putchar('*');
				putchar('/');
				putchar('\n');
				etat=ETAT_DBT_LIGNE;
			break;
			}
		     }
		  putchar(c);
		  break;
			
	    }
    }

    exit(EXIT_SUCCESS);
}
