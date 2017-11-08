#include <stdio.h>

int main(void) { 

	unsigned int indent;
	unsigned int accOuv;
	unsigned int accFer;
	int i;
	char c;

	enum {ETAT_DIRECTIVE, ETAT_COMMENTAIRE_DEBUT, ETAT_COMMENTAIRE, ETAT_COMMENTAIRE_FIN, ETAT_CHAINE, ETAT_NORMAL, ETAT_DEBUT_LIGNE} etat = ETAT_DEBUT_LIGNE;

	indent = 0;
	accOuv = 0;
	accFer = 0;
	i = 0;

	while((c = getchar()) != EOF) {
		switch(etat) {
			case ETAT_DEBUT_LIGNE:
				switch(c) {
					case ' ':
					case '\t':
					case '\n':
						break;
					case '#':
						putchar(c);
						etat = ETAT_DIRECTIVE;
						break;
					case '{':
						for(i = 0; i < indent; i++) putchar('\t');
						putchar(c);
						putchar('\n');
						accOuv++;
						indent++;
						break;
					case '}':
						for(i = 0; i < indent - 1; i++) putchar('\t');
						putchar(c);
						putchar('\n');
						accFer++;
						indent--;
						break;
					case '/':
						for(i = 0; i < indent; i++) putchar('\t');
						putchar(c);
						etat = ETAT_COMMENTAIRE_DEBUT;
						break;
					default:
						for(i = 0; i < indent; i++) putchar('\t');
						putchar(c);
						etat = ETAT_NORMAL;
						break;
				}
			break;
			case ETAT_DIRECTIVE:
				switch(c) {
					case '\n':
						putchar('\n');
						etat = ETAT_DEBUT_LIGNE;
						break;
					default:
						putchar(c);
						break;
				}
			break;
			case ETAT_NORMAL:
				switch(c) {
					case '{':
						putchar('\n');
						for(i = 0; i < indent; i++) putchar('\t');
						putchar(c);
						putchar('\n');
						accOuv++;
						indent++;
						etat = ETAT_DEBUT_LIGNE;
						break;
					case '}':
						putchar('\n');
						for(i = 0; i < indent - 1; i++) putchar('\t');
						putchar(c);
						putchar('\n');
						accFer++;
						indent--;
						etat = ETAT_DEBUT_LIGNE;
						break;
					case '\'':
					case '"':
						putchar(c);
						etat = ETAT_CHAINE;
						break;
					case '/':
						putchar('\n');
						for(i = 0; i < indent; i++) putchar('\t');
						putchar(c);
						etat = ETAT_COMMENTAIRE_DEBUT;
						break;
					case '\n':
						putchar('\n');
						etat = ETAT_DEBUT_LIGNE;
						break;
					default:
						putchar(c);
						break;
				}
			break;
			case ETAT_COMMENTAIRE_DEBUT:
				switch(c) {
					case '*':
						putchar(c);
						etat = ETAT_COMMENTAIRE;
						break;
					default:
						putchar(c);
						etat = ETAT_NORMAL;
						break;
				}
			break;
			case ETAT_COMMENTAIRE:
				switch(c) {
					case ' ':
					case '\t':
					case '\n':
					case '\r':
						break;
					default:
						putchar(' ');
						putchar(c);
						etat = ETAT_COMMENTAIRE_FIN;
						break;						
				}
			break;
			case ETAT_COMMENTAIRE_FIN:
				switch(c) {
					case '\n':
					case '\r':
						putchar(' ');
						putchar('*');
						putchar('/');
						putchar('\n');
						for(i = 0; i < indent; i++) putchar('\t');
						putchar('/');
						putchar('*');
						etat = ETAT_COMMENTAIRE;
						break;
					case '/':
						putchar(c);
						putchar('\n');
						etat = ETAT_DEBUT_LIGNE;
						break;
					default:
						putchar(c);
						break;
				}
			break;
			case ETAT_CHAINE:
				switch(c) {
					case '\'':
					case '"':
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
	
	if(accOuv != accFer)
		printf("\nErreur : accolades\n");
	if(etat == ETAT_COMMENTAIRE_DEBUT || etat == ETAT_COMMENTAIRE || etat == ETAT_COMMENTAIRE_FIN)
		printf("\nErreur : commentaires\n");
		
	return 0;

}
