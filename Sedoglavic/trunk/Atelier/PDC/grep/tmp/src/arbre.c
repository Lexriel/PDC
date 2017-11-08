#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"
#include "parse.h"
#include "automate.h"
#include "util.h"

NODE *root;

NODE *creer_noeud(TYPENODE type, char valeur, NODE *left, NODE *right){
	NODE *node = (NODE *)malloc(sizeof(NODE));

	node->type = type;
	node->value = valeur;
	node->left = left;
	node->right = right;

	return node;
}

NODE * creer_root(){
	NODE *node , *child;
	child = creer_noeud(DIESE, '#', NULL, NULL);
	node = creer_noeud(CONCAT, '.', NULL, child);
	node->left = expr();

	return node;
}

NODE *expr(){
	NODE *child, *node;

	child=concat(); 
	
	if (token == END) 
		return child;

	if (child == NULL)
		return_error();

	if (token==PIPE) {
		/*créer node type ALTER;*/
		node = creer_noeud(ALTER,'|', child, NULL);
		next_token();
		
		if(((node->right) = expr()) == NULL) 
			return_error();
		
		return node;
	}
	else return child;
}

NODE *concat() {
	NODE *child, *node;
	child=repet(); 
	
	if (token==END) 
		return child;

	if (child==NULL) return_error();

	if ((token==LBRACE) || (token==CAR)) {
		/*créer node type CONCAT;*/
		node = creer_noeud(CONCAT,'.',child,NULL);
		
		if ((node->right=concat())==NULL) 
			return_error();
			
		return node;
	}
	else return child;

	return node;
}

NODE *repet() {
	NODE *child, *node;
	child=simple(); 
	
	if (token==END) 
		return child;

	if (child==NULL) return_error();
	
	if (token==STAR) {
		/*créer node type STAR;*/
		node = creer_noeud(STAR,'*',child,NULL);
		next_token();
	
		return node;
	}
	else
		return child;
}

NODE *simple() {
	NODE *child, *node;
	
	if (token == LBRACE) {
		next_token();
	
		if ((child=expr())==NULL) return_error();
		
		if (token!=RBRACE) return_error();
		
		next_token();
		
		return child;
	} 
	else {
		if (token==END) return NULL;
		
		if (token!=CAR) return_error();

		/*créer node type LETTER;*/
		node = creer_noeud(LETTER, token_value, NULL, NULL);
		
		next_token();
	
		return node;
	}
}


void construit(NODE * node ){
	if(node != NULL ){
		construit(node->left);
		construit(node->right);
		node->isnul = nullable(node);
		node->alphabet = alphabet(node);
		node->initial = first(node);
		node->final = last(node);
		node->suivant = suivant(node);
	}		
}
void construit_root(NODE* node){
	node->alphabet = alphabet(node);
}

void construit_arbre(char **chaine){

}

int nullable(NODE * n){
	if( n->type == DIESE){
		return TRUE;
	}
	else if(n->type == CONCAT){
		return nullable(n->left) && nullable(n->right); 
	}
	else if(n->type == ALTER){
		return nullable(n->left) || nullable(n->right);
	}
	else if(n->type == REPET){
		return TRUE;
	}
	else{
		return FALSE;
	}
}



char_list * first(NODE * n){
	if( n->type == DIESE){
		return cons_lc('#');
	}
	else if(n->value == '.'){
		if(nullable(n->left)){
			char_list * tmp = first(n->left);
			tmp = ajouter_lc(tmp,first(n->right));
			return tmp;
		}
		else{
			return first(n->left);
		} 
	}
	else if(n->value == '|'){
		
		char_list * tmp = first(n->left);
		tmp->suivant = first(n->right);
		return tmp;

	}
	else if(n->value == '*'){

		return first(n->left);
	}
	else{
		return cons_lc(n->value);
	}
}

char_list * last(NODE * n){
	if(n->type == DIESE){
		return cons_lc('#');
	}
	else if(n->value == '.'){
		if(nullable(n->left)){
			char_list * tmp = last(n->left);
			tmp = ajouter_lc(tmp,last(n->right));
			return tmp;
		}
		else{
			return last(n->right);
		} 
	}
	else if(n->value == '|'){
		
		char_list * tmp = last(n->left);
		tmp->suivant = last(n->right);
		return tmp;

	}
	else if(n->value == '*'){

		return last(n->left);
	}
	else{
		return cons_lc(n->value);
	}
}



char_list * suivant(NODE * n){
	if(n->value == '.'){
		return NULL;
	}
	else if(n->value == '*'){
		return NULL;
	}
	else{
		return NULL;
	}
}


char_list * alphabet(NODE * n){
	if(n->type == CONCAT || n->type==ALTER){
		char_list *tmp;
		tmp = alphabet(n->left);
		tmp = ajouter_lc(tmp,alphabet(n->right));
		n->alphabet = tmp;
		return n->alphabet;
	}
	else 
		if(n->type == REPET){
		n-> alphabet = alphabet(n->left);	
		return n->alphabet;
	}
	else if(n->type == LETTER){
		n->alphabet = cons_lc(n->value);
		return n-> alphabet;
	}
	else if(n->type == DIESE){
		n->alphabet = cons_lc(n-> value);
		return n->alphabet;
	}
	else
		return NULL;
	
}
