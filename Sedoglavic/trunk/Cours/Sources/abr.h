   typedef struct noeud {
             int v ;
             struct noeud *fg, *fd ;
           } noeud, *Abr;

   void init(Abr *a);
   void inserer(Abr *a, int v);
   void imprimer_croissant(Abr a);
   void imprimer_decroissant(Abr a);
