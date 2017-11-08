#include"automate.h"

#define FALSE 0
#define TRUE !FALSE

typedef enum {
	ALTER, CONCAT, REPET, LETTER
}TYPENODE;

typedef struct node{
	TYPENODE type;
	char value;
	struct node *left, *right;
	int isnul;
	char_list * alphabet;
	char_list * initial;
	char_list * final;
	char_list * suivant;
} NODE;

NODE *creer_noeud(TYPENODE type, char valeur, NODE *left, NODE *right);

NODE *creer_root();

NODE *expr();

NODE *concat();

NODE *repet();

NODE *simple();

int nullable(NODE *node);
void construit(NODE *node);
void construit_root(NODE *node);
void construit_arbre(char **chaine);
void affiche(NODE *node);
void affiche_abr(NODE *abr);
void afficher(NODE* node, int esp); 
void abr_display(NODE * node );

char_list *first(NODE *node);
char_list *last(NODE *node);
char_list *suivant(NODE *node);
char_list *alphabet(NODE *node);
