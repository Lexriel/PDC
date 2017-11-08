#ifndef _AUTOMATE__H
#define _AUTOMATE__H

typedef struct char_list{
	char val;
	struct char_list * suivant;
}char_list;

typedef struct automate {
	int q0; 	
    char_list ** delta;
    char_list * finaux;
}automate;


char_list * cons_lc(char v);
char_list * ajouter_lc(char_list * p, char_list * s);
automate * automate_new(int q, char_list * f, char_list ** d);
void afficher_lc(char_list * c);
int accepte(char * mot, automate * a);
#endif
