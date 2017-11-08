#include <stdio.h>
#define FAIL -1
#define SUCCESS 1
#define TOUTESLETTRES 67108863

/* nom      : pangramme 
   argument : un pointeur de caracteres pointant sur une chaine 
              Attention si ce n'est pas le cas, risque de boucle 
	      longue.
   sortie   : SUCCESS si la chaine de caracteres est un pangramme 
              FAIL    sinon 
   rem      : on utilise des operateurs de manipulations binaires 
              pour le fun
*/


int pangramme(char *ch1){

  /* On ne souhaite pas dans cette fonction utiliser  un tableau de 26
     octet.  En fait,  on n'utilisera qu'un entier  long non signe (32
     bits).

     a correspondra au premier bytes 0 si absent, 1 sinon~; 
     z au 26iemes, avec le meme codage~; 
     les autres seront mis a zero.

     Dans ce cas, l'entier correspondant a la presence de toutes les
     lettres est 67108863.
  */

  unsigned long int resultat = 0 ;

  for(;*ch1!=0;ch1++)
    if(*ch1 != ' '){ 
      if ('A'<*ch1 && *ch1<'Z')
	*ch1 += 32 ; // pour convertir les majuscules en minuscule
    
      if(*ch1<'a' && 'z'<*ch1)
	return FAIL ; // seules les lettres de l'alphabet peuvent
                      // composer un pengramme

      resultat |= 1 << (int) (*ch1-'a') ;
    }	

  /*   a | b correspond au ou exclusif bits a bits
       si a = 0101 et b = 1001 alors a | b = 1101
       1 << (int) (*ch1-`a`) correspond a un decalage a droite 
       a << 2 = 0100
       dans notre cas c'est une puissance de deux : 2^(*ch1-`a`) 
   */

  if (resultat==TOUTESLETTRES) 
    return SUCCESS ;
  else 
    return FAIL ;
}

int main(int argc, char **argv){

  if (pangramme(argv[1])==SUCCESS)
      printf("Cette chaine est bien un pangramme\n");
    else printf("Cette chaine n'est pas un pangramme\n");

/*   if(incluse(*(argv+1),*(argv+2))==FAIL) 
     printf("La chaine %s n'est pas incluse dans %s\n",
                       *(argv+1),            *(argv+2)) ;
     else
     printf("La chaine %s est bien incluse dans %s\n",
                       *(argv+1),            *(argv+2)) ; 
*/

  return SUCCESS ;
}
 
