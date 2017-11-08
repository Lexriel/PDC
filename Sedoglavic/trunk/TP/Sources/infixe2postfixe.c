#include <stdio.h>
#define Max 30 

/* Definition d'une pile */

typedef struct Pile{

  int hauteur ;
  char tab[Max] ;

} Pile ;

/* les fonctions de manipulation des piles */

char sommet(Pile *pile){
  
  return pile->tab[pile->hauteur-1] ;
}

void vider(Pile *pile){

  pile->hauteur=0 ;
}

void empiler(char element, Pile *pile){

  pile->tab[pile->hauteur++]=element ;
}


char depiler(Pile *pile){

  return pile->tab[--pile->hauteur] ;
}

int estVide(Pile *pile){

  return pile->hauteur==0 ;
}

/* Les etats de notre automates */

void Etat_Analyse_et_Decision(Pile *src, Pile *tmp, Pile *res){

  int fin = 1 ;
  int choix ;

  while (fin){
    
    if (estVide(src))
      if (estVide(tmp))
	choix = 4 ;
      else if (sommet(tmp)==91)
	choix = 5 ;
      else choix = 2 ;
    else if (sommet(src)==91)
      choix = 1 ;
    else if (sommet(src)==45 || sommet(src)==43)
      if (estVide(tmp) || sommet(tmp)==91)
	choix = 1 ;
      else choix = 2 ;
    else if (sommet(src)==42 || sommet(src)==47)
      if (sommet(tmp)==42 || sommet(tmp)==47)
	choix = 2 ;
      else choix = 1 ;
    else if (sommet(src)==91)
      choix = 1 ;
    else if (sommet(src)==93)
      if (estVide(tmp))
	choix = 5 ;
      else if (sommet(tmp)==91)
	choix = 3 ;
      else choix = 2 ;
    else if (sommet(src)>47 && sommet(src)<58)
      choix = 6 ;
    else choix = 5 ;
    
    switch(choix){
    case 1 : empiler(depiler(src),tmp) ; break ;
    case 2 : empiler(depiler(tmp),res) ; break ;
    case 3 : depiler(src) ; depiler(tmp) ; break ;
    case 4 : fin = 0  ; break ;
    case 5 : printf("\n Erreur \n") ; fin = 0 ;  break ;
    case 6 : empiler(depiler(src),res) ; break ;
    default : printf("\n Erreur \n") ; fin = 0 ; break ;
    }
  }
}

int main (int argc, char **argv){

  /* Initialisation des piles */

  Pile tmp ;
  Pile src ;
  Pile res ;

  tmp.hauteur = 0 ;
  src.hauteur = 0 ;
  res.hauteur = 0 ;

  /* Comme on veut passer des arguments par adresses,
     on definit des pointeurs sur ces objets */

  Pile *p_tmp = &tmp ;
  Pile *p_src = &src ;
  Pile *p_res = &res ;
  
  /* On convertit l'entree dans une pile */

  if (argc==1){
    printf("Il faut fournir une expression\n") ;
    return -1;
  }

  int i ;

  for(i=0;*(*(argv+1)+i)!=0;i++) 
    empiler(*(*(argv+1)+i),p_tmp) ;
     
  while(tmp.hauteur!=0)
    empiler(depiler(p_tmp),p_src) ;
  
  vider(p_tmp) ;
     
  /* Le traitement proprement dit */
     
  Etat_Analyse_et_Decision(p_src,p_tmp,p_res) ;

  /* inversion de res */

  vider(p_tmp) ;

  while(res.hauteur!=0)
    empiler(depiler(p_res),p_tmp) ;
  
  /* affichage du resultat */
  
/*   while(tmp.hauteur!=0) */
/*     printf("%c",depiler(p_tmp)) ; */
/*   printf("\n") ; */

  /* calcul */

  char car ;
  int stck ;
  struct Pile_Result {
    int  hauteur ;
    int tab[Max] ;
  } result ;

  result.hauteur = 0 ;

  while(tmp.hauteur!=0){
    car =  depiler(p_tmp) ;
    if (car==43) {
      stck = result.tab[--result.hauteur] + result.tab[--result.hauteur] ;
      result.tab[result.hauteur++] = stck ;
    }
    else if (car==45)  {
      stck = result.tab[--result.hauteur] - result.tab[--result.hauteur] ;
      result.tab[result.hauteur++] = stck ;
    }
    else if (car==42)  {
      stck = result.tab[--result.hauteur] * result.tab[--result.hauteur] ;
      result.tab[result.hauteur++] = stck ;
    }
    else if (car>47 || car<58) 
      result.tab[result.hauteur++] = car - 48 ;
    else printf("Not Implemented Yet\n") ;
  }

  printf("le resultat est : %d\n",result.tab[0]) ;

  return 0 ;
}



 
