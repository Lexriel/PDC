# include "monmalloc_infra.h"
# include <stdlib.h>
# include "monmalloc_afaire.h"

liste_t freelist = 0;

void construirecellule(liste_t tmp, unsigned int size){
  tmp -> magicnumber = MAGICNUMBER;
  tmp -> userspacestart = (void *) ((char *) tmp + sizeof(struct cell_m));	
  tmp -> userspacestop = (void *) (((char *) tmp->userspacestart) + size);
  inserer(&freelist, tmp);
  return;
}

void *monmalloc(unsigned int size){
  liste_t tmp, tmp2;

  if (size > BUFFERSIZE)
    /* si on demande une trop grande taille */
    exit(SIZE2BIG);

  /* on cherche dans la liste des cellules libres une cellule 
     ayant un espace utilisateur de taille suffisante */

  while(1){
    tmp = extraire(&freelist, size);

    if (tmp == 0)
      /* si aucune cellule libre n'est dans la liste des cellules
	 libres, on en place une en allant chercher un nouveau
	 segment*/
      etendrememoire();
    else
      break;
  }

  if (USS(tmp) == size)
    return tmp->userspacestart;

  if (USS(tmp) - sizeof(struct cell_m)+ 1 > size){
    /* on doit couper la cellule extraite, insérer dans la liste des
       cellules libres une cellule construite dans l'espace restant */
    tmp2 = (liste_t) (((char *) (tmp->userspacestart)) + size) ;
    construirecellule(tmp2, USS(tmp) - size);
    tmp->userspacestop = (void *) (((char *) tmp2));
  }
	
  /* et retourner à l'utilisateur un pointeur sur l'espace alloué */
  return tmp->userspacestart;
}

void monfree(void *ptr){
  liste_t cell = (liste_t) (((char *) ptr) - sizeof(struct cell_m));
  if (cell->magicnumber != MAGICNUMBER)
    exit(WRONGFREE);	
  inserer(&freelist, cell);
  return;
}
