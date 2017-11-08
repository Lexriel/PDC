#include <stdio.h>
#include <stdlib.h>

int 
main(void)
{
    int c, i;
    enum {ETAT_DBT_LIGNE, ETAT_NORMAL, ETAT_COM } etat = ETAT_DBT_LIGNE;
  
    int cpt = 0;
    while ((c=getchar()) != EOF) {
    	switch (etat) {
        	case ETAT_DBT_LIGNE:
                switch (c) {
                    case ' ':
                    case '\t':
				    case '\n':
                        break;
				    case '{':
                      putchar('\n');
					  for (i = 0; i < cpt; i++)
						putchar(' ');
			          putchar(c);
	      			  putchar('\n');
					  cpt = cpt + 4;
					  etat = ETAT_DBT_LIGNE;
						break;
			
				   case '}':
					putchar('\n');
					cpt = cpt - 4;
					for (i = 0; i < cpt; i++)
			          putchar(' ');
					putchar(c);
					putchar('\n');
					etat = ETAT_DBT_LIGNE;
					  break;

				   case '/':
					for (i = 0; i < cpt; i++)
  					  putchar(' ');
					putchar(c);
					etat=ETAT_COM;
						break;

                  default:
					for (i = 0; i < cpt; i++)
						putchar(' ');
                    putchar(c);
                    etat = ETAT_NORMAL;
                        break;
                }
                break;

            case ETAT_NORMAL:
                switch (c) {
                    case '\n': 
                        putchar(c);
                        etat=ETAT_DBT_LIGNE;
                        break;
				    case '{':
						putchar('\n');
						for (i = 0; i < cpt; i++)
							putchar(' ');
						printf("bouh");
						putchar('\n');
						cpt = cpt + 4;
						printf("%d",cpt);
						etat = ETAT_DBT_LIGNE;
							break;
			
				   case '}':
						putchar('\n');
						cpt = cpt - 4;
						for (i = 0; i < cpt; i++)
							putchar(' ');
						printf("bouh3");
						putchar('\n');
						etat = ETAT_DBT_LIGNE;
							break;
			
				   case '/':
					  etat=ETAT_COM;
						break;

                   default :
					break;
                }

            case ETAT_COM:
				switch (c){
				    case '\n':
						etat=ETAT_DBT_LIGNE;
							break;

				   case '*':
		
        		    default :
                	   putchar(c);
	                   etat=ETAT_NORMAL;
    		               break; 	
				}
    	}
	}
    return 0;
}
