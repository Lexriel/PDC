#include<stdio.h>
#include<stdlib.h>

void afficheTab(int nombreTab){

int i;
	for(i=0;i<nombreTab;i++){
             putchar('\t');
        }


}


int main(void){
char c;
char tabTMP[10];
int tailleDeLaChaineCommentaire,nombreDeTabulation,debutCommentaire;
tailleDeLaChaineCommentaire =0;
nombreDeTabulation = 0;
debutCommentaire = 0;

	while((c = getchar())!= EOF){
		switch(c){
		case '/':
/*On test si c est / pour savoir si oui ou non on est dans un commentaire*/
			if((tabTMP[0] = getchar()) == '*'){/*si le commentaire suivant est * , on est dans un commentaire*/
				debutCommentaire = 1;/* on precise que c est un commentaire */
				putchar('\n');
				afficheTab(nombreDeTabulation);
				putchar(c);
				putchar(tabTMP[0]);
				putchar('\n');
				afficheTab(nombreDeTabulation);
			}
			else{/*sinon on affiche*/
				putchar(c);
				putchar(tabTMP[0]);
			}
			break;
		case '*':
			if((tabTMP[0] = getchar()) == '/' && debutCommentaire == 1){
				debutCommentaire = 0;/* on signifie que l on quitte le commentaire*/
				putchar('\n');
				afficheTab(nombreDeTabulation);
				putchar(c);
				putchar(tabTMP[0]);
				putchar('\n');
				afficheTab(nombreDeTabulation);
			}
			else{
				putchar(c);
				putchar(tabTMP[0]);
			}

			break;
		case '{':
			putchar('\n');
			/*On met les tabulations pour decaler { si besoin*/
	  		afficheTab(nombreDeTabulation);
			putchar(c);
			putchar('\n');
			/*on incremente le nombre de tabulation pour decaler apres une {*/
			nombreDeTabulation++;
			afficheTab(nombreDeTabulation);
			break;

        	case '}':
			/*on decremente le nombre de tabulation pour decaler } pour se
			retrouver au meme niveau que son } correspondant*/
			nombreDeTabulation--;
			putchar('\n');
			/*on affiche les tabulations*/
               		afficheTab(nombreDeTabulation);
			putchar(c);
                	putchar('\n');
   			afficheTab(nombreDeTabulation);
			break;

		case ';':
			putchar(c);
			putchar('\n');
			afficheTab(nombreDeTabulation);
			break;

		default:
			if(debutCommentaire == 1){/* si on est dans un commentaire,a chaque caracteres ont augemente la taille*/
				tailleDeLaChaineCommentaire++;

				if(tailleDeLaChaineCommentaire >= 50){/*si on est a 50 , on passe le commentaire a la ligne*/
					tailleDeLaChaineCommentaire=0;
					putchar(c);
					putchar('\n');
					afficheTab(nombreDeTabulation);
				}
				else{
					putchar(c);
				}
			}
			else{
				putchar(c);
        		}
			break;
		}
	}
return 0;

}
