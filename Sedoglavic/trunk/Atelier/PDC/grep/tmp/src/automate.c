#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "automate.h"

/*construit un noeud de l'automate */
char_list * cons_lc(char v){
	char_list * l = (char_list*) malloc(sizeof(struct char_list));
	l->val = v;
	l->suivant = NULL;
	return l;
}

/*ajoute un noeud a une liste de noeud */
char_list * ajouter_lc(char_list * p, char_list * s){
		while(p->suivant != NULL){
			p = p->suivant;
		}
		p->suivant = s;
		return p;
}

/* creation d'un nouvel automate */
automate * automate_new(int q, char_list * f, char_list ** d) {
	automate * a = (automate*) malloc(sizeof(struct automate));
        a->q0 = q;
        a->delta = d;
        a->finaux = f;
	return a;
}

/* verifie si une valeur appartient à l'automate */
int estDans(char_list * x, int v) {
    if (x == NULL)
        return 0;
    else
        return x->val == v || estDans(x->suivant, v);
}


/* accepter un mot par l'automate */
int accepter(char * mot, automate * a, int i, int q) {
    char_list * nv_q = NULL;

    if (i == strlen(mot))
        return estDans(a->finaux, q);
    else {
        int resultat = 0; 
        int c = mot[i];

        for (nv_q = &(a->delta[q][c]); nv_q != NULL; nv_q = nv_q->suivant)
            resultat = resultat || accepter(mot, a, i+1, nv_q->val);
	
        return resultat;
    }
}

int accepte(char * mot, automate * a) {
    return accepter(mot, a, 0, a->q0);
}

