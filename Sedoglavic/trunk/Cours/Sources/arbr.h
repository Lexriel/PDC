typedef struct noeud_t {
  int v ;
  struct noeud_t *fg, *fd ;
} noeud_t ;

struct noeud_t *Abr;

void init(noeud_t *);
void inserer(noeud_t *, int);
void imprimer_croissant(noeud_t *);
void imprimer_decroissant(noeud_t *);
