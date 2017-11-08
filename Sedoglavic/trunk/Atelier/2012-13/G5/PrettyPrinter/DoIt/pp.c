
#include <stdio.h>
#include <stdlib.h>

void indentation(int a){
int i;
for(i=0;i<a;i++)
	putchar(' ');
}

int 
main()
{
    int c;
    int g;
    int indent;
    indent=0;
    enum {ETAT_DBT_LIGNE, ETAT_NORMAL, ETAT_COMMENTAIRE} etat = ETAT_DBT_LIGNE;
  
    while ((c=getchar()) != EOF) {
        switch (etat) {
            case ETAT_DBT_LIGNE:
		
                switch (c) {
                    case ' ':
			break;
	       	    case '\n':
			break; 
                    case '\t':
			break;
		    case '/' :
/*a faire*/	
			break;
	       	    case '{':
		      putchar('\n');
		      indentation(indent);
                      indent+=4;
		      putchar(c);
		      putchar('\n');
		      etat = ETAT_NORMAL;
		      break; 
		    case '}':

		      putchar('\n');
		      indent-=4;
		      indentation(indent);
		      putchar(c);
		      etat = ETAT_NORMAL;
		      break;
                    default:  
			indentation(indent); 
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
		      indentation(indent);
		      indent+=4;
		      putchar(c);
		      putchar('\n');
		      etat = ETAT_DBT_LIGNE;
			break;
		    case '}':
		      putchar('\n');
		      indent-=4;
		      indentation(indent);
		      putchar(c);
		      putchar('\n');
		      etat = ETAT_DBT_LIGNE;
			break;
                    default :  
                      putchar(c);
                        break;
		}

	    case ETAT_COMMENTAIRE:

		switch (c) {


		}
	}
    }
	if(indent!=0){
	fprintf(stderr, "erreur d'accolade");
	exit(EXIT_FAILURE);
	}
    exit(EXIT_SUCCESS);
}
