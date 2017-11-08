/*
** Clément LEFEVRE - L3 info Groupe 2
** TP Pretty Printer
*/

#include <stdio.h>


void
indenter(int n) {
	/*
	** Fonction indentant du nombre de tabulations nécessaires.
	** @param n nombre d'indentations à effectuer
	*/
	while(n-- != 0)
		putchar('\t');
}


int
main(void) {

	char c;
	enum {
		ETAT_DEBUT_LIGNE,
		ETAT_NORMAL,
		ETAT_DEBUT_COMMENTAIRE_POSSIBLE,
		ETAT_COMMENTAIRE,
		ETAT_FIN_COMMENTAIRE_POSSIBLE,
		ETAT_PREPROCESSEUR,
		ETAT_CARACTERE,
		ETAT_CHAINE
	} etat = ETAT_DEBUT_LIGNE;
	
	int dernier_etat;
	
/* Enumération des états possibles */
	
	
	unsigned int par, indent;
	par = 0;
	indent = 0;

	while((c = getchar()) != EOF) {
		/* Tant que la fin de l'entrée n'est pas atteinte */
		
		switch(etat) {

			case ETAT_DEBUT_LIGNE :
				switch(c) {
				
					case '#' :
						etat = ETAT_PREPROCESSEUR;
						putchar(c);
					 break;
					
					case '/' :
						etat = ETAT_DEBUT_COMMENTAIRE_POSSIBLE;
						dernier_etat = ETAT_DEBUT_LIGNE;
					 break;
					
					case '\n' :
					 break;
					
					case '{' :
						
						indenter(indent);
						putchar('{');
						indent++;
						putchar('\n');
					 break;
					
					case '}' :
						indent--;
						indenter(indent);
						putchar('}');
						putchar('\n');
					 break;
					
					
					case '(' :
						indenter(indent);
						putchar(c);
						par ++;
					 break;
					
					case ')' :
						indenter(indent);
						putchar(c);
						par--;
					 break;
					
					case ';' :
						indenter(indent);
						putchar(';');
						putchar('\n');
					 break;
					
					case ' ' :
					case  '\t' :
					 break;
					
					
					default :
						indenter(indent);
						putchar(c);
						etat = ETAT_NORMAL;
					 break;
				}
			
			 break;
			
			
			case ETAT_NORMAL :
			
				switch(c) {
					
					case '/' :
						etat = ETAT_DEBUT_COMMENTAIRE_POSSIBLE;
						dernier_etat = ETAT_NORMAL;
					 break;
					
					case '\'' :
						etat = ETAT_CARACTERE;
						putchar('\'');
					 break;
					
					case ';' :
						putchar(c);
						if(!par) {
							putchar('\n');
							etat = ETAT_DEBUT_LIGNE;
						}
					 break;
					
					case '(' :
						putchar(c);
						par ++;
					 break;
					
					case ')' :
						putchar(c);
						par--;
					 break;
					
					case '{' :
					
						putchar('\n');
						indenter(indent);
						putchar('{');
						indent++;
						putchar('\n');
						etat = ETAT_DEBUT_LIGNE;
					 break;
					
					case '}' :
						indent--;
						indenter(indent);
						putchar('}');
						putchar('\n');
						etat = ETAT_DEBUT_LIGNE;
					 break;
					
					
					default :
						putchar(c);
					 break;
					
					
				}
				
			 break;
			
			case ETAT_DEBUT_COMMENTAIRE_POSSIBLE :
				
				switch(c) {
				
					case '*' :
						etat = ETAT_COMMENTAIRE;
						putchar('\n');
						indenter(indent);
						putchar('/');
						putchar('*');
					 break;
					
					default :
						putchar('/');
						putchar(c);
						etat = dernier_etat;
					 break;
					
				}
			
			 break;
			
			
			case ETAT_COMMENTAIRE :
				
				switch(c) {
				
					case '*' :
						etat = ETAT_FIN_COMMENTAIRE_POSSIBLE;
					 break;
					
					case '\n' :
						putchar('*');
						putchar('/');
						putchar('\n');
						indenter(indent);
						putchar('/');
						putchar('*');
					 break;
					
					default :
						putchar(c);
					 break;
					
				}
			
			 break;
			
			
			case ETAT_FIN_COMMENTAIRE_POSSIBLE :
				
				switch(c) {
				
					case '/' :
						etat = ETAT_DEBUT_LIGNE;
						putchar('*');
						putchar('/');
						putchar('\n');
					 break;
					
					default :
						putchar('*');
						putchar(c);
						etat = ETAT_COMMENTAIRE;
					 break;
					
				}
			
			 break;
			
			case ETAT_PREPROCESSEUR :
			
				do {
					putchar(c);
					c= getchar();
				} while (c  != '\n');
				putchar(c);
				etat = ETAT_DEBUT_LIGNE;
				
			 break;
			
			
			case ETAT_CARACTERE :
			
				while(c != '\'') {
					putchar(c);
					c = getchar();
				}
				putchar('\'');
				etat = ETAT_NORMAL;
				
			 break;
			
			
			case ETAT_CHAINE :
			
				while(c != '"') {
					putchar(c);
					c = getchar();
				}
				putchar('"');
				etat = ETAT_NORMAL;
				
			 break;
			
			
			
				
			
		}


	}
	
	putchar(EOF);
	
	if(indent != 0 || par != 0)
		fprintf (stderr, "Erreur d'équilibrage des paranthèses ou accolades. \n");

	return 0;

}

