# include <stdio.h>

/* Supprime n de colonnes en commençant par la colonne index sur la
ligne line de taille size.  Si n nul, aucune colonne supprimée. Si n +
index - 1 > size, on supprime les colonnes depuis index (si possible)
jusqu'à la fin la ligne.  */
extern void sup_colonne(unsigned int index, unsigned int n, int line[], unsigned int size){
  int i;
  if( (index < size) && (n != 0) ){
    for(i=index+n; i<size; i++)
      line[i-n] = line[i];
    line[i-n] = '\0';

    /* if(size > index + n) */
    /*   line[size-n] = '\0'; */
    /* else */
    /*   line[index] = '\0'; */
  }
}

/* Retourne l'indice de la prochaine occurence du caractère delim dans
   line de taille size à partir de index (compris), ou -1 si non
   trouvé */
extern int prochaine_occurence(unsigned int index, char delim, int line[], unsigned int size){
  int i;
  i = index;
  while(i < size){
    if(line[i] == delim){
      return i;
    }
    i++;
  }
  return -1;
}

/* Retourne 0 si element non présent dans le tableau T de taille size, 1 sinon */
extern int est_present(int element, int T[], int size){
  int i;
  i = 0;
  while(i < size){
    if(T[i] == element)
      return 1;
    i++;
  }
  return 0;
}

/* Supprime de la ligne line de taille size les colonnes séparée par
   delim dont le numéro n'apparait pas dans le tableau T de taille
   size */
extern void sup_ensemble_colonnes(char delim, int line[], unsigned int size, int T[], unsigned int n){
  int index;
  int num_colonne;
  int index_delim;
  index = 0;
  index_delim = 0;
  num_colonne = 1;

  /* On recherche le prochaine delimiteur s'il existe et s'il reste des colonnes à conserver */
  while( (index_delim = prochaine_occurence(index, delim, line, size)) != -1 ){
    /* Test si on garde la colonne */
    if( est_present(num_colonne, T, n) )
      index = index_delim + 1;
    /* On supprime la colonne car non présente dans T */
    else{
      sup_colonne(index, index_delim - index + 1, line, size);
      size -= index_delim - index + 1;
    }
    num_colonne ++;
  }

  /* On supprime la colonne car non présente dans T */
  if( !est_present(num_colonne, T, n) )
    sup_colonne(index, size - index, line, size);
}

/* renvoie un pointeur à la première occurrence de str2 dans str1, ou un pointeur null si non rencontré */
extern int *mon_strstr(int *str1, int *str2){
  int i, n, cpt;
  int *adr;
  if ((str2 == NULL) || (str1 == NULL))
    return NULL;

  n = 0;
  while (str2[n] != '\0')
    n++;

  i = 0;
  cpt = 0;
  adr = str1;
  while (str1[i]){
    if (str2[cpt++] == str1[i]){
      if (cpt == n)
	return adr;
    }
    else{
      cpt = 0;
      adr = &str1[i];
    }
    i++;
  }
  return NULL;
}
