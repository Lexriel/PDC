int  comparaisondechaine (char *ch1, char * ch2){
/* cette fonction renvoie un entier
 * cet entier est strictement positif si ch1 > ch2
 * cet entier est strictement negatif si ch2 > ch1
 * 0 sinon
 */
  int cmp = *ch1-*ch2 ;
    
  while(*ch1!=0 && *ch2!=0){
    if (cmp!=0)
      return cmp ;

    cmp = *(ch1++)-*(ch2++) ;
  }

  return cmp ;
}
 
