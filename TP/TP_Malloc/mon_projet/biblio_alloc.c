# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FAUX 0
# define VRAI (!FAUX)

typedef int bool;           /* définition d'un type booléen */

/* Definition du type bloc */
typedef struct bloc_s Bloc;
struct bloc_s{
  void* adresse_espace_alloue;    /* adresse d'espace alloué */
  int   taille;                   /* taille  d'espace alloué */
  bool  est_libre;                /* l'espace mémoire est-il libre ? */
  Bloc* next;                     /* pointe sur le bloc suivant */
  Bloc* prev;                     /* pointe sur le bloc precédent */
};

# define sizeBloc (sizeof(Bloc))

static Bloc* biblio = NULL; /* bibliothèque d'allocation mémoire */
static void* debut = NULL;  /* adresse début de bibliothèque */
static void* fin = NULL;    /* adresse fin de bibliothèque */


/* Transfert <size> octets commençant en mémoire à l'adresse pointée par <src> dans le segment de mémoire commençant par l'adresse pointée par <dest> */
void transfert(void *src,void *dest, int size){
  char *cpy_src, *cpy_dest;
  int i;
  cpy_src = src;
  cpy_dest = dest;
  for(i=0; i<size; i++){
    *cpy_dest = *cpy_src;
    cpy_src++;
    cpy_dest++;
  }
}


/* Création d'un nouveau bloc mémoire de taille <nbOctets>   
   Bloc créé :
   ________________________________________________
   |        |                                       |
   |        |                                       |
   | entete |        espace mémoire alloué          |
   |        |        (de taille nbOctets)           |
   |        |                                       |
   |________|_______________________________________|        */
static Bloc* creer_nouveau_bloc(int nbOctets){
  void* espaceMem;

  espaceMem = sbrk(sizeBloc + nbOctets);

  /* Définit l'entête */
  ((Bloc*) espaceMem)->adresse_espace_alloue = ((char*) espaceMem) + sizeBloc;
  ((Bloc*) espaceMem)->taille = nbOctets;
  ((Bloc*) espaceMem)->est_libre = VRAI;
  ((Bloc*) espaceMem)->next = espaceMem;
  ((Bloc*) espaceMem)->prev = espaceMem;

  /* Retourne le pointeur sur le début du bloc */
  return ((Bloc*) espaceMem);
}


/* Recherche le bloc qui serait le précédent de <bloc> dans <biblio> si on 
   souhaite l'insérer dans <biblio> */
static Bloc* recherche_bloc_adresse(Bloc* bloc){
  Bloc* courant;
  Bloc* precedent;

  if (biblio == NULL)
    return NULL;
  else{
    courant = biblio;

    /* le bloc précédent à bloc est le précédent du premier de <biblio> */
    if (bloc <= courant)
      precedent = courant->prev;
     
    /* il faut avancer de bloc en bloc pour trouver le bloc précédent à 
       <bloc> dans biblio, pour savoir où on l'insèrera */
    else{ /* (bloc > courant) */
      courant = courant->next;
      while ((bloc > courant) && (courant != biblio))
	courant = courant->next;
      precedent = courant->prev;
    }

    return precedent;
  }
}


/* Ajoute un bloc <bloc> dans <biblio> et renvoie <bloc> */
static Bloc* inserer_bloc_dans_biblio(Bloc* bloc){
  Bloc* bloc_gauche;
  Bloc* bloc_droite;
  
  /* dans ce cas, on met simplement bloc dans biblio */
  if (biblio == NULL){ /* donc precedent == NULL */
    biblio = bloc;
    bloc->next = bloc;
    bloc->prev = bloc;
    /* on précise les valeurs de debut et fin */
    if ((debut == NULL) || (debut > (void*) bloc))
      debut = (void*) bloc;
    if ((fin == NULL)   || (fin  <= (void*) bloc))
      fin   = (void*) (((char*)bloc) + sizeBloc + bloc->taille);

    return bloc;
  }

  else{
    /* on cherche le bloc qui sera le précédent de <bloc> */
    bloc_gauche = recherche_bloc_adresse(bloc);

    if (bloc_gauche != NULL){
      bloc_droite = bloc_gauche->next;
      /* on met à jour la liste chaînée <biblio> */
      bloc->prev = bloc_gauche;
      bloc->next = bloc_droite;
      bloc_droite->prev = bloc;
      bloc_gauche->next = bloc;

      /* on met à jour les valeurs de <biblio>, <debut> et <fin>
	 dans les cas où bloc se situe avant ou après <biblio> */
      if (bloc <= biblio)
	biblio = bloc;
      if ((debut == NULL) || (debut > (void*) bloc))
	debut = (void*) bloc;
      if ((fin == NULL)   || (fin  <= (void*) bloc))
	fin   = (void*) (((char*)bloc) + sizeBloc + bloc->taille);
    }
	 
    return bloc;	
  }
}


/* Recherche un bloc de taille suffisante pour y stocker nbOctets, retourne 
   NULL si la recherche est infructueuse */
static Bloc* recherche_bloc_taille_suffisante(int nbOctets){
  Bloc* courant;

  if (biblio == NULL)
    return NULL;
  
  /* si le premier bloc de <biblio> suffit, on le prend */
  courant = biblio;
  if ((courant->taille >= nbOctets) && (courant->est_libre))
    return courant;

  /* sinon on cherche, jusqu'à trouver ou retourner au début de <biblio> */
  courant = courant->next;
  while((courant->taille < nbOctets) && (!courant->est_libre) && (courant != biblio))
    courant = courant->next;
  if ((courant != biblio) && (courant->est_libre))
    return courant;
  else
    return NULL;  
}


/* enlève un bloc de la bibliothèque <biblio> */
static void enlever_bloc(Bloc* bloc){
  Bloc* bloc_gauche;
  Bloc* bloc_droite;

  if (biblio == NULL)
    return;

  /* on réévalue <biblio> si le bloc est au début de <biblio> */
  if (biblio == bloc){
    if (biblio == bloc->next){ /* et donc == bloc->prev aussi */
      biblio = NULL;
      return; /* <biblio> contient 1 seul bloc, qu'on a enlevé */
    }
    else
      biblio = bloc->next;
  }

  /* on récupère les blocs précédents et suivants de <bloc> */
  bloc_gauche = bloc->prev;
  bloc_droite = bloc->next;

  /* on change les adresses pour ne plus pouvoir accéder à <bloc> */
  bloc_gauche->next = bloc->next;
  bloc_droite->prev = bloc->prev;

  /* maintenant, on considère ce bloc comme libre */
  bloc->est_libre = FAUX;

  return;
}


/* Extrait un bloc de taille <nbOctets> de <biblio>, cela peut créer des scissions de blocs */
static Bloc* extraire_bloc(int nbOctets){
  Bloc* courant;
  Bloc* nouveau;
  Bloc* resultat;

  courant = recherche_bloc_taille_suffisante(nbOctets);
  
  /* si la recherche est infructueuse, on crée un bloc, qu'on insère dans 
     la bibliothèque */
  if (courant == NULL){
    nouveau = creer_nouveau_bloc(2*nbOctets);
    courant = inserer_bloc_dans_biblio(nouveau);
  }

  /* on copie courant dans resultat, et on enlève le bloc de <biblio> */
  resultat = courant;
  enlever_bloc(courant);

  /* on crée un nouveau bloc dans <biblio>, le reste de la mémoire s'il y en a */
  if ((resultat->taille) > nbOctets + sizeBloc){
    nouveau = (Bloc*) (((char*) resultat) + nbOctets + sizeBloc);
    nouveau->next = resultat->next;
    nouveau->prev = resultat->prev;
    nouveau->est_libre = VRAI;
    nouveau->taille = resultat->taille - nbOctets - sizeBloc;
    inserer_bloc_dans_biblio(nouveau);

    /* on met à jour la taille de résultat */
    resultat->taille -= nouveau->taille + sizeBloc;
  }

  return resultat;
}


/* Retourne un pointeur vers un bloc d'espace mémoire d'au-moins <size> octets */
void* mon_malloc(unsigned int size){
  Bloc* bloc;
  void* res;

  bloc = extraire_bloc(size);
  res = ((char*) bloc) + sizeBloc; /* on doit commencer à pointer après l'entête */

  return res;
}


/* Afficher la bibliothèque */
void affichage_bibliotheque(){
  Bloc* courant;
  int i;
  i = 0;

  if (biblio == NULL)
    return;

  courant = biblio;
  printf("------ AFFICHAGE de LA BIBLIOTHEQUE d'ALLOCATION MEMOIRE ------\n\n");
  printf("  Bloc #%d :  adresse = %p,  taille = %d\n", ++i, (void*) courant, courant->taille);

  courant = courant->next;
  while(courant != biblio){
    printf("  Bloc #%d :  adresse = %p,  taille = %d\n", ++i, (void*) courant, courant->taille);
    courant = courant->next;
  }
  printf("\n---------------------------------------------------------------\n\n");
}


/*
  static Bloc* rendre_bloc(Bloc* bloc)
  {
  void *debut_bloc, *fin_bloc;
  void *debut_prev, *fin_prev;
  Bloc* precedent;

  début et fin du bloc
  debut_bloc = (void*) bloc;
  fin_bloc   = ((char*) bloc) + bloc->taille + sizeBloc;

  Bloc hors de la bibliothèque 
  if (debut_bloc < debut || fin_bloc > fin)
  return NULL;

  Bloc précédent 
  precedent = bloc->prev;
  if (precedent == NULL)
  return NULL;

  début et fin du bloc précédent 
  debut_prev = (void*) prev;
  fin_prev   = ((char*) prev) + prev->taille + sizeBloc;

  Si le précédent est le seul bloc de la bibliothèque 
  if(precedent->next == biblio)  <=> 1 seul bloc dans <biblio> 
  {
  if ((fin_bloc <= debut_prev) || (fin_prev <= debut_bloc))
  return precedent;
  return NULL;
  }

  Cas où il y a au moins deux blocs dans la bibliothèque 
  if ((fin_prev <= debut_bloc) && (fin_bloc <= (void *) precedent->suivant))
  return precedent;
  return NULL;
  }*/


/* Fusionne <bloc> avec <bloc->next> s'ils sont contigus en mémoire */
static void fusion(Bloc* bloc){
  void* fin_bloc;

  if(bloc != NULL){
    /* fusion éventuelle de <bloc> avec <bloc->next> */
    fin_bloc = ((char*) bloc) + bloc->taille + sizeBloc;
    if(fin_bloc == bloc->next){
      bloc->taille += sizeBloc + (bloc->next)->taille;
      bloc->next = (bloc->next)->next;
    }
    bloc->est_libre = VRAI;
  }
}


/* Rend à la bibliothèque l'espace mémoire pointé par <ptr> */
void mon_free(void* ptr){
  Bloc* bloc_rendu;
  bloc_rendu = (Bloc*) ((char *)ptr - sizeBloc);
  /*precedent = rendre_bloc(bloc_rendu);*/
  inserer_bloc_dans_biblio(bloc_rendu);
  fusion(bloc_rendu);
  fusion(bloc_rendu->prev);
}



int main(int argc, char* argv[]){
  int i;
  Bloc *bloc, *bloc2, *bloc3, *tmp;
  int* T;

  /* Créer des blocs */
  bloc  = creer_nouveau_bloc(200);
  bloc2 = creer_nouveau_bloc(100);
  bloc3 = creer_nouveau_bloc(300);


  /* Insérer des blocs */
  tmp = inserer_bloc_dans_biblio(bloc);
  tmp = inserer_bloc_dans_biblio(bloc2);
  tmp = inserer_bloc_dans_biblio(bloc3);
  

  /* Afficher les infos des blocs de <biblio> */
  /*  i = 0;
      tmp = biblio;
      printf("BLOC %d :\n  taille = %d\n  est_libre = %d\n  adresse_espace_alloue = %p\n  next = %p\n  prev = %p\n  adresse_entete = %p\n\n", i, tmp->taille, tmp->est_libre, tmp->adresse_espace_alloue, (void*) tmp->next, (void*) tmp->prev, (void*) tmp);
  
      tmp = tmp->next;
      while (tmp != biblio)
      {
      printf("BLOC %d :\n  taille = %d\n  est_libre = %d\n  adresse_espace_alloue = %p\n  next = %p\n  prev = %p\n  adresse_entete= %p\n\n", ++i, tmp->taille, tmp->est_libre, tmp->adresse_espace_alloue, (void*) tmp->next, (void*) tmp->prev, (void*) tmp);
      tmp = tmp->next;
      }
  */
  
  
  /* Recherche bloc de taille suffisante */
  tmp = recherche_bloc_taille_suffisante(100); tmp++; tmp--;
  /*  if (tmp)
      printf("BLOC de taille 100 cherché :\n  taille = %d\n  est_libre = %d\n  adresse_entete = %p\n\n", tmp->taille, tmp->est_libre, (void*) tmp);
      else
      printf("BLOC de taille 100 non trouvé car tmp est NULL.\n\n");
  
      tmp = recherche_bloc_taille_suffisante(400);
      if (tmp)
      printf("BLOC de taille 400 cherché :\n  taille = %d\n  est_libre = %d\n  adresse_entete = %p\n\n", tmp->taille, tmp->est_libre, (void*) tmp);
      else
      printf("BLOC de taille 400 non trouvé car tmp est NULL.\n\n");
  
      tmp = recherche_bloc_taille_suffisante(250);
      if (tmp)
      printf("BLOC de taille 250 cherché :\n  taille = %d\n  est_libre = %d\n  adresse_entete = %p\n\n", tmp->taille, tmp->est_libre, (void*) tmp);
      else
      printf("BLOC de taille 250 non trouvé car tmp est NULL.\n\n"); */
  
  /*affichage_bibliotheque();*/

  /* Extraire bloc */
  /*tmp = extraire_bloc(500);
    printf("sizeof(Bloc) = %ld\n", sizeBloc);
    affichage_bibliotheque();
    tmp++;*/


  /* Enlever bloc */
  /*enlever_bloc(bloc2); */

  printf("Avant le malloc :\n");
  affichage_bibliotheque();

  T = mon_malloc(10*sizeof(int));

  printf("Après le malloc :\n");
  affichage_bibliotheque();

  printf("Mon tableau T a pour valeurs : ");
  for (i=0; i<10; i++)
    T[i] = i*i;
  for (i=0; i<10; i++)
    printf("%d ", *(T+i));
  printf("\n\n");

  mon_free(T);

  printf("Après le free :\n");
  affichage_bibliotheque();

  return 0;
}
