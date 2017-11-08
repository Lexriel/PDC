# ifndef _GRAPHE_H_
# define _GRAPHE_H_

# define TAILLE_DICO 909
# define EMPTY_PILE ((Pile) 0)

typedef int MatriceAdjacence[TAILLE_DICO][TAILLE_DICO];

typedef struct pile_s *Pile;
struct pile_s{
  int indice;
  Pile next;
};

int forment_arete(char mot1[], char mot2[]);

void CreeMatriceAdjacence(MatriceAdjacence mat, char *dico_trie[TAILLE_DICO]);

int ConvertionMotIndice(char *mot, char *dico_trie[TAILLE_DICO]);

int estVide(Pile indices);

int empiler(Pile *pIndices, int ind);

int depiler(Pile *pIndices, int *ind);

int Chemin(int sommetcourant, int sommetdestination, MatriceAdjacence mat,
	   Pile *parcours, int dejaparcouru[]);

void erreurMots(char mot1[], char mot2[], char *dico_trie[TAILLE_DICO]);

void afficherChemin(Pile *parcours, char *dico_trie[TAILLE_DICO]);


# endif
