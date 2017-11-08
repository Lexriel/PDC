#include <stdio.h>

#define Stop 0

/* Nos echelles vont etre codee par des entiers */

#define Celsius    1
#define Fahrenheit 2
#define Kelvin     3

/* ces definitions ne sont pas utilisees par la suite mais
   cette presentation a le merite d'etre claire */

/* Passer d'une temperature a une autre revient a effectuer  
   une transformation affine du type A*tmp+B.

   on sait que Kelvin = Celsius +  273 
   et on determine sans peine que Celsius = (5 Fahrenheit - 160)/100
   on peut donc coder les differentes conversion par une relation
   lineaire du type 
                     Echelle Arrivee = A * Echelle Depart + B ;
   reste a determiner pour chaque conversion A et B.

   On regroupe dans les constantes suivantes les differents
   coefficients de conversion                                 */

#define C2FA 9.0/5.0
#define C2FB 160.0/5.0
#define F2CA 5.0/9.0
#define F2CB -160.0/9.0            
#define C2KA 1.0
#define C2KB 273.0 
#define K2CA 1.0
#define K2CB -273.0
#define F2KA 5.0/9.0 
#define F2KB 273.0 - 160.0/9.0
#define K2FA -9.0/5.0 
#define K2FB (9.0*273.0+160.0)/5.0 ;

int main(void) {

  int stop    ; /* 0 pour stop, 1 pour encore */
  int CodeEch ;  /* on va coder les echelles de depart et d'arrivee 
		    afin de se simplifier la vie.
		    Ainsi, CodeEch va etre
		    Code echelle de depart*10+ Code Echelle d'arrivee */

  float A,B  ; /* les coefficients de la relation lineaire */
  float stck ; /* une variable fourre tout */

  do {

    /* On collecte les donnees */
    printf("Temperature a convertir ? ") ;
    scanf("%f",&stck) ;

    printf(" 1 = Celsius, 2 = Fahrenheit, 3 = absolue\n") ;
    printf("A partir de quelle echelle ? ") ;
    scanf("%d",&CodeEch) ;

    CodeEch = CodeEch*10 ;

    printf("En quelle echelle ? ") ;
    scanf("%d",&stop) ; /* on ne devrait pas utiliser une variable destinee
			   a autre chose */
	
    CodeEch = CodeEch + stop ;

    switch(CodeEch){
    case 12 : A = C2FA ; B = C2FB ; break ;
    case 21 : A = F2CA ; B = F2CB ; break ;
    case 13 : A = C2KA ; B = C2KB ; break ;
    case 31 : A = K2CA ; B = K2CB ; break ;
    case 23 : A = F2KA ; B = F2KB ; break ;
    case 32 : A = K2FA ; B = K2FB ; break ;
    default : printf("Conversion impossible") ; 
      return -1 ; /* ce return interrompt le programme */
    }

    /* Le calcul proprement dit */
    stck = A*stck + B ;

    /* Affichage du resultat */
    printf("la conversion est %f\n",stck) ;

    /* Pour permettre une autre saisie */
    printf("Stop ou encore (0 pour stop, 1 pour encore) ") ;
    scanf("%d",&stop) ;

  } while(stop!=0) ;
  return 0;
}

 
