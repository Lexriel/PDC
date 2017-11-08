# include "malloc.h"
/* R�alis� par Thomas Brunin et Alexis Pernet (L3 info) */

ListeChaine *liste;
int maxfast;
int numblks = 100;
char utilisationPossibleMallopt = TRUE;

/* Rajoute les 4 char "P", "O", "N" et "Y" a la fin d'un bloc de m�moire, qui sert a v�rifier s'il n'y a pas de d�passement de m�moire*/
void ponyficator(ListeChaine *l){ /* un pointeur sur l'entete du bloc de m�moire */
  char *ptr;
  ptr = (char*) l->adresse+l->taille;
  ptr -= 4;
  ptr[0] = 'P';
  ptr[1] = 'O';
  ptr[2] = 'N';
  ptr[3] = 'Y';
}
/* Alloue et renvoie un bloc de m�moire libre de "taille" et on le ratache � "suivant" */
ListeChaine *creeBloc(int taille, /* la taille du bloc � allouer */
		      ListeChaine *suivant){ /*Indique o� pointer l'attribut "next" */
  void *adresse;
  ListeChaine *nouvelleCellule;
  adresse = (void*) sbrk(taille + sizeof(ListeChaine)); /* on alloue un bloc de taille "taille" sans oublier d'ajouter la taille du type "ListeChaine" et 4 qui nous servirons a detecter les eventuels depassement de memoire */
  nouvelleCellule = adresse;
  nouvelleCellule->next = suivant;
  nouvelleCellule->taille = taille;
  nouvelleCellule->utilise = FALSE;
  nouvelleCellule->tab = NULL;
  nouvelleCellule->adresse = (char*) adresse + sizeof(ListeChaine); /*Cette ligne montre que les "ListeChaine" sont stock�s, suivi juste apr�s par un bloc d'adresse libre */
  ponyficator(nouvelleCellule);	
  return nouvelleCellule;
}

/*ajoute un element en modifiant l'attribut "next" de l par ce nouvel element */
void ajouterElement(ListeChaine *l, /* modifie l'atribut "next" de l pour y ajouter l'�lement */
		    size_t value){ /*la taille que l'on souhaite allouer */
  if ( (TAILLE_BLOC) >= (value + sizeof(ListeChaine)) ) /* Si la taille qu'on veux allouer (sans oubli� d'ajouter la taille du type "ListeChaine") est plus petit que TAILLE_BLOC, on cr�er le bloc */
    l->next = creeBloc(TAILLE_BLOC, l->next);
  else /* sinon, aulieu de cr�er un bloc de taille "TAILLE_BLOC", on cr�er directement un bloc de la taille demande */
    l->next = creeBloc(value, l->next);
}

/* Divise un bloc en deux */
void insererElement(ListeChaine *l, /* divise la ListeChaine o� pointe "l" */
		    int value){ /* la nouvelle taille de la ListeChaine */
  ListeChaine *nouvelleCellule; /*On cr�e une nouvelle ListeChaine, avec comme taille, la taille de "l" en retirant "value" + la taille du type "ListeChaine" ... Cela ne peut pas devenir un nombre negatif car ce cas est g�r� dans "malloc" */
		
  nouvelleCellule = (ListeChaine*) ((char*) l->adresse+value);
  nouvelleCellule->taille = (int) l->taille-value - sizeof(ListeChaine);
  nouvelleCellule->adresse = (char *) l->adresse + sizeof(ListeChaine) + value;
  nouvelleCellule->utilise = FALSE;
  nouvelleCellule->tab = NULL;
  nouvelleCellule->next = l->next;		
  l->next = nouvelleCellule;
  l->taille = value;
  l->utilise = TRUE;
  ponyficator(l);
}

/* Fusionne tous les blocs possible de fusionner */
void fusionnerBloc(){
  ListeChaine *listeEnCours;
  ListeChaine *prochaine;
  listeEnCours = liste;
  while (listeEnCours->next != liste){
    if ( (listeEnCours->utilise == FALSE) && (listeEnCours->next->utilise == FALSE) && (listeEnCours->next->adresse) == ((char*) listeEnCours->adresse+listeEnCours->taille+sizeof(ListeChaine)) ){ /* v�rifie si les 2 blocs ne sont pas utilis� et si leur adresse est continu dans la m�moire */
      prochaine = listeEnCours->next;
      listeEnCours->taille += prochaine->taille + sizeof(ListeChaine);
      listeEnCours->next = prochaine->next;
      prochaine = NULL;
    }
    else
      listeEnCours = listeEnCours->next;
  }
}

/* Cr�e un bloc initial */
void init(){
  liste = creeBloc(TAILLE_BLOC, NULL);
  liste->next = liste;
}

/* Retourne un pointeur sur une ListeChaine qui a pour attribut "adresse", l'adresse donn�e en parametre, retourne NULL si aucun bloc ne correspond */
ListeChaine *rechercheListeParAdresse(void *adresse){ /* l'adresse recherch�e */
  ListeChaine *res;
  res = liste;
  do
    {
      if (res->adresse == adresse)
	return res;
      res = res->next;
    } while (res != liste);
  return NULL;
}

/* Retourne un pointeur sur une ListeChaine qui a son attribut "tab" non NULL et pas rempli, retourne NULL s'il ne trouve pas */
ListeChaine *rechercheTabBlks(){
  ListeChaine *res;
  res = liste;
  do
    {
      if ( (res->tab != NULL) && (res->utilise != FULL) )
	return res;
      res = res->next;
    } while (res != liste);
  return NULL;
}

/* Retourne une pointeur sur une ListeChaine dont son attribu tab est non NULL et qui contient l'adresse donne en parametre, retourne NULL s'il ne trouve pas */
ListeChaine *rechercheTabBlksParAdresse(void *adresse) /* l'adresse recherche */
{
  ListeChaine *res;
  res = liste;
  do
    {
      if ( (res->tab != NULL) && ((char*) res->adresse <= (char*) adresse) && ((char*)adresse <= ((char *)res->adresse + res->taille)) ) /* verifie si c'est bien un tableau de "t_petitBloc" et qui contient l'adresse donne en parametre*/
	return res;
      res = res->next;
    } while (res != liste);
  return NULL;
}

/* Alloue de la m�moire et initialise un tableau de "t_petitBloc" de taille "numblks"*/
void initTabBlks(){
  void *adresse;
  int i;
  ListeChaine *temp;
  adresse = (void*) mmalloc(numblks*(maxfast+sizeof(t_petitBloc)));
  temp = rechercheListeParAdresse(adresse); /*On recherche la ListeChaine que l'ont viens juste de cr�er grace a l'adresse retourn�e par malloc */
  temp->tab = adresse; /* Et on initialise le tableau de "t_petitBloc" */
  for (i=0; i<numblks; i++){
    temp->tab[i].utilise = FALSE;
    temp->tab[i].adresse = (char*) adresse + ((sizeof(t_petitBloc)+maxfast)*i);
  }
}

/* Retourne un pointeur sur une ListeChaine assez grande pour contenir "size", elle ne retourne normalement jamais NULL */
ListeChaine *rechercheListeParTaille(size_t size){ /* la taille recherch�e */
  ListeChaine *listeEnCours;
  listeEnCours = liste;
  size += 4;
  do
    {
      if ( (listeEnCours->taille >= size) && (listeEnCours->taille <= (size+sizeof(ListeChaine))) && (listeEnCours->utilise == FALSE) ) /* Si on trouve un pointeur sur une ListeChaine avec une taille comprise entre "size" et "size"+la taille du type "ListeChaine" non utilise alors on retourne ce pointeur, car pour diviser un bloc, il faut au minimum un espace de taille assez grand pour stocker le type "ListeChaine" */
	return listeEnCours;
      else if ( (listeEnCours->taille >= size + sizeof(ListeChaine)) && (listeEnCours->utilise == FALSE)){ /* Si on trouve un bloc beaucoup trop gros, alors on le divise et on renvoi un bloc de taille "size" de disponible */
	insererElement(listeEnCours,size);
	return listeEnCours;
      }

      if (listeEnCours->next == liste) /* Si on a fait le tour de la liste, alors on rajoute un element */
	ajouterElement(listeEnCours,size);
      listeEnCours = listeEnCours->next;
    } while (listeEnCours != liste);
  return NULL;
}

/* Retourne une adresse qui pointe sur un bloc d'adresse que l'on a allou� */
void *bam_malloc (size_t size, /* la taille que l'on souhaite allouer */
		  char *filename,
		  unsigned line){
  ListeChaine *res;
  if (liste == NULL)  /* Si la liste de bloc est vide, alors on la creer */
    init();

  if ( (maxfast != 0) && (size <= maxfast) && (rechercheTabBlks() == NULL) ){ /* si on veux allouer un bloc de taille inf�rieur a "maxfast" et qu'aucun bloc avec un tableaux de "t_petit_bloc" est disponible, on en cr�er un nouveau*/
    utilisationPossibleMallopt = FALSE;
    initTabBlks();
  }


  if ( (maxfast != 0) && (size <= maxfast) ){ /* Si on veux allouer un bloc de taille inf�rieur a "maxfast", alors on recherche un bloc qui contient un tableau de taille "t_petitBloc" et on lui alloue une case qui est disponible */
    int i;
    ListeChaine *tabPetitBloc;
    tabPetitBloc = rechercheTabBlks();
    for (i=0; i<numblks; i++){
      if (tabPetitBloc->tab[i].utilise == FALSE){
	tabPetitBloc->tab[i].utilise = TRUE;
	if (i == numblks-1) /* si le bloc qu'on vient d'allouer correspond au dernier, alors on dit que le tableau est complet*/
	  tabPetitBloc->utilise = FULL;
	return tabPetitBloc->tab[i].adresse;
      }
    }
  }

  res = rechercheListeParTaille(size); /* Sinon, on recherche un bloc de taille "size" (qu'on divise s'il le faut), on met son attribut utilise a "TRUE" et on renvoie son adresse */
  res->utilise = TRUE;
	
  return res->adresse;
}

/* Change la taille d'un bloc precedement allou� et renvoi l'adresse correspondant au d�but du nouveau bloc */
void *mrealloc(void *base, /*l'adresse de la ou commence le bloc m�moire que l'ont souhaite changer de taille */
	       size_t size){ /* la nouvelle taille desir� */
  void *res;
  int i;
  char *ptr_base, *ptr_res;
  mfree(base); /* on commence par lib�r� l'espace m�moire (sans effacer son contenu cepedant, on en aura besoin par la suite */
  res = mmalloc(size); /* Alloue un bloc de taille "size" */

  ptr_base = (char*) base;
  ptr_res = (char*) res;
  if (ptr_base != ptr_res){ /* si on a pas reallou� exactement le m�me bloc (car cela peut arriver), on recopie le contenu de l'ancien bloc dans le nouveau */
    for (i=0; i<size; i++)
      ptr_res[i] = ptr_base[i];
  }
  return (void*) res;
}

/* Retourne une adresse qui pointe sur un bloc d'adresse que l'ont a alloue et dont on initialise chaque octet � 0*/
void *mcalloc(size_t nb_case, /* Nombre de case � allouer */
	      size_t taille_case){ /* Taille de chaque case */
  char *res;
  int i;
  res = mmalloc(nb_case*taille_case);

  for (i=0; i<nb_case*taille_case; i++)
    res[i] = 0;

  return (void*) res;
}

/* lis les 4 dernier octect d'un bloc memoire pour verifier qu'il n'y a pas eu de depassement de memoire */
char isPony(ListeChaine *l){ /* l'entete du bloc de memoire a verifier */
  char *ptr;
  ptr = (char*) l->adresse+l->taille;
  ptr -= 4;
  if ( (ptr[0] == 'P') && (ptr[1] == 'O') && (ptr[2] == 'N') && (ptr[3] == 'Y'))
    return 1;
  return 0;
}

/* Libere un bloc qui aura pour attribut adresse "adresse" */
void mfree(void *adresse){ /* l'adresse de la o� commence le bloc m�moire*/
  char aTrouveLeBloc;
  ListeChaine *listeEnCours;
  ListeChaine *listeALiberer;
  int caseTableauALiberer;

  aTrouveLeBloc = FALSE;
	
  listeEnCours = rechercheListeParAdresse(adresse);
  if ( (listeEnCours != NULL) && (listeEnCours->tab == NULL) ){ /*Si on trouve le bloc et que ce n'est pas un tableau de "t_petitBloc" */
    listeEnCours->utilise = FALSE;
    aTrouveLeBloc = TRUE;
    if ( !isPony(listeEnCours) )
      printf("Vous avez depasser la memoire alloue !\n");		
  }
  else{ /* Sinon, on va regarder quelle case du tableau est a lib�r�e */
    listeALiberer = rechercheTabBlksParAdresse(adresse);
    if (listeALiberer != NULL){
      caseTableauALiberer = (char*) adresse - ((char*)listeALiberer->adresse);
      if (caseTableauALiberer % (maxfast+sizeof(t_petitBloc)) == 0){ /* si le resultat est different de 0, cela veux dire que l'adresse donne en parametre ne correspond a aucun debut de case du tableau */
	caseTableauALiberer /= (maxfast+sizeof(t_petitBloc));

	listeALiberer->tab[caseTableauALiberer].utilise = FALSE;
	listeALiberer->utilise = TRUE; /* On met l'attribu de la ListeChaine a TRUE au cas ou sa valeur serais "FULL" */
	aTrouveLeBloc = TRUE;
      }
    }
  }
  if (aTrouveLeBloc == TRUE) /* Si aucun bloc ne correspond, alors la liste n'a pas chang� et il est donc inutile de tenter de fusionner les blocs */
    fusionnerBloc(); /* et on finit par fusionner les blocs si possible */
  else
    printf ("Adresse non valide \n");
}

/* change les valeurs de "maxfast" et "numblks" */
void mmallopt(int cmd, /* M_MXFAST, ou alors M_NMBLOCKS */
	      unsigned int val){ /* la nouvelle valeur */
  if (utilisationPossibleMallopt == TRUE){ /* S'il y a deja un tableau de "t_petitBloc" qui a �t� cr��, alors on ne peut plus utiliser mmallpot */
    if (cmd == M_MXFAST)
      maxfast = val;
    if (cmd == M_NMBLOCKS)
      numblks = val;
  }
  else
    printf("Les valeurs de mallopt ne peuvent plus etres modifie");
}

/* Affiche l'entete du bloc pass� en parametre */
void imprimerEntete(ListeChaine *liste){ /* la liste � imprimer */
  int nombreCaseUtilise;
  int i;
  if (liste->tab == NULL){
    printf("Bloc : taille bloc : %d, utilise : %d, adresse : %p\n", liste->taille, liste->utilise, liste->adresse);
  }
  else{
    nombreCaseUtilise = 0;
    for (i=0; i<numblks; i++)
      if (liste->tab[i].utilise == TRUE)
	nombreCaseUtilise++;
    printf("Tab petit bloc : nombre case utilise : %d, nombre case libre : %d\n", nombreCaseUtilise, numblks-nombreCaseUtilise);
  }
}

/* Imprime le contenu du bloc passe en parametre si celui ci contient des int (rajoute un 1498304336 qui correspond au 4 charactere de chaque fin de segment d'adresse */
void imprimerContenuInt(ListeChaine *liste){ /* le pointeur sur la liste dont on veux imprimer le contenu */
  int i;
  int *contenu;
  if (liste->tab == NULL){
    for (i=0; i<liste->taille; i+=sizeof(int)){
      contenu = (int*) liste->adresse + (i/sizeof(int));
      printf("%d\n", *contenu);
    }
  }
  else
    printf("Tableau de petit bloc");
  printf("\n");
}

/* Imprime le contenu du bloc passe en parametre si celui ci contient des char (rajoute un 'P', 'O', 'N', 'Y' qui correspond au 4 caract�res de chaque fin de segment d'adresse */
void imprimerContenuChar(ListeChaine *liste){ /* le pointeur sur la liste dont on veux imprimer le contenu */
  int i;
  char *contenu;
  if (liste->tab == NULL){
    for (i=0;i<liste->taille;i++){
      contenu = (char*) liste->adresse+(i/sizeof(int));
      printf("%c\n", *contenu);
    }
  }
  else
    printf("Tableau de petit bloc");
  printf("\n");
}

/* Imprime les entetes de tous les blocs */
void imprimerBiblio(){
  int i;
  ListeChaine *listeEnCours;
  listeEnCours = liste;
  printf("\n -----ENTETE----- \n");
  i=1;
  do
    {
      printf("%d : ", i);
      i++;
      imprimerEntete(listeEnCours);
      listeEnCours = listeEnCours->next;
    } while (listeEnCours != liste);
}
