#include <stdio.h>
#include <stdlib.h>
#include "complexe.h"
#include "rationnel.h" 

  enum TypeNombre {entier, rationnel, flottant, complexe} ;
  typedef struct Nombre {
     enum TypeNombre tn ;
     union valeur {
       int nbentier ;
       Rationnel nbrationnel  ;
       float nbflottant ;
       Complexe nbcomplexe ;
     } valeur ;
  } Nombre ;

  typedef struct CoupleNombre {
       Nombre a ;
       Nombre b ;
  } CoupleNombre ;

void PrintNombre ( Nombre a ) {

  switch(a.tn){
  case entier : printf("%d",a.valeur.nbentier) ; break ;
  case flottant : printf("%f",a.valeur.nbflottant) ; break ;
  case rationnel : PrintRationnel( a.valeur.nbrationnel) ; break ;
  case complexe : PrintComplexe( a.valeur.nbcomplexe) ; break ;
  default : exit(-1) ; break ;
  }
}

CoupleNombre ConvertNombre (Nombre a, Nombre b){

  CoupleNombre c ;
  char foo ;

  if (a.tn==b.tn){
    c.a = a ;
    c.b = b ;
  }   
  else {
    foo = a.tn*10 + b.tn ;
    switch(foo){
    case 1 : {
      c.a.valeur.nbrationnel.numerateur = a.valeur.nbentier ;
      c.a.valeur.nbrationnel.denominateur = 1 ;
      c.b = b ;
      c.a.tn = c.b.tn ;
    } break ;
    case 2 : {
      c.a.valeur.nbflottant = (float) a.valeur.nbentier ;
      c.b = b ;
      c.a.tn = c.b.tn ;
      } break ;
    case 3 : {
      c.a.valeur.nbcomplexe.partie_reelle = (float) a.valeur.nbentier ;
      c.a.valeur.nbcomplexe.partie_imaginaire = 0.0 ;
      c.b = b ;
      c.a.tn = c.b.tn ;
    } break ;

    case 10 : {
      c.b.valeur.nbrationnel.numerateur = b.valeur.nbentier ;
      c.b.valeur.nbrationnel.denominateur = 1 ;
      c.a = a ;
      c.b.tn = c.a.tn ;
    } break ;
    case 20 : {
      c.b.valeur.nbflottant = (float) b.valeur.nbentier ;
      c.a = a ;
      c.b.tn = c.a.tn ;
    } break ;
    case 30 : {
      c.b.valeur.nbcomplexe.partie_reelle = (float) b.valeur.nbentier ;
      c.b.valeur.nbcomplexe.partie_imaginaire = 0.0 ;
      c.a = a ;
      c.b.tn = c.a.tn ;
    } break ;

    case 12 : {
      c.a.valeur.nbflottant = (float) a.valeur.nbrationnel.numerateur / 
	(float) a.valeur.nbrationnel.denominateur ;
      c.b = b ;
      c.a.tn = c.b.tn ;
    } break ;

    case 13 : {
      c.a.valeur.nbcomplexe.partie_reelle = (float) a.valeur.nbrationnel.numerateur / 
	(float) a.valeur.nbrationnel.denominateur ;
      c.a.valeur.nbcomplexe.partie_imaginaire = 0.0 ;
      c.b = b ;
      c.a.tn = c.b.tn ;
    } break ;

    case 21 : {
      c.b.valeur.nbflottant = (float) b.valeur.nbrationnel.numerateur / 
	(float) b.valeur.nbrationnel.denominateur ;
      c.a = a ;
      c.b.tn = c.a.tn ;
    } break ;
    case 31 : {
      c.b.valeur.nbcomplexe.partie_reelle = (float) b.valeur.nbrationnel.numerateur / 
	(float) b.valeur.nbrationnel.denominateur ;
      c.b.valeur.nbcomplexe.partie_imaginaire = 0.0 ;
      c.a = a ;
      c.b.tn = c.a.tn ;
    } break ;

    case 23 : {
      c.a.valeur.nbcomplexe.partie_imaginaire = a.valeur.nbflottant ;
      c.a.valeur.nbcomplexe.partie_imaginaire = 0.0 ;
      c.b = b ;
      c.a.tn = c.b.tn ;
    } break ;
    case 32 : {
      c.b.valeur.nbcomplexe.partie_imaginaire = b.valeur.nbflottant ;
      c.b.valeur.nbcomplexe.partie_imaginaire = 0.0 ;
      c.a = a ;
      c.b.tn = c.a.tn ;
    } break ;

    default : exit(-1) ; break ;
    }
  }
  return c ;
}

Nombre AddNombre( Nombre a, Nombre b) {

  Nombre c ;
  CoupleNombre ab = ConvertNombre(a,b) ;

  switch(ab.a.tn){
  case entier : c.valeur.nbentier = ab.a.valeur.nbentier + ab.b.valeur.nbentier ; break ;
  case rationnel : c.valeur.nbrationnel = addRationnel(ab.a.valeur.nbrationnel,
						       ab.b.valeur.nbrationnel) ; break ;
  case flottant : c.valeur.nbflottant = ab.a.valeur.nbflottant + ab.b.valeur.nbflottant ; break ;
  case complexe : c.valeur.nbcomplexe = addComplexe(ab.a.valeur.nbcomplexe,
						       ab.b.valeur.nbcomplexe) ; break ;
  default : exit(1) ; break ;
  }
  c.tn = ab.a.tn ;
  return c ;
}

Nombre MulNombre( Nombre a, Nombre b) {

  Nombre c ;
  CoupleNombre ab = ConvertNombre(a,b) ;

  switch(ab.a.tn){
  case entier : c.valeur.nbentier = ab.a.valeur.nbentier * ab.b.valeur.nbentier ; break ;
  case rationnel : c.valeur.nbrationnel = mulRationnel(ab.a.valeur.nbrationnel,
						       ab.b.valeur.nbrationnel) ; break ;
  case flottant : c.valeur.nbflottant = ab.a.valeur.nbflottant * ab.b.valeur.nbflottant ; break ;
  case complexe : c.valeur.nbcomplexe = mulComplexe(ab.a.valeur.nbcomplexe,
						       ab.b.valeur.nbcomplexe) ; break ;
  default : exit(-1) ; break ;
  }
  c.tn = ab.a.tn ;
  return c ;
}


Nombre QuoNombre( Nombre a, Nombre b) {

  Nombre c ;
  CoupleNombre ab = ConvertNombre(a,b) ;

  switch(ab.a.tn){
  case entier : c.valeur.nbentier = ab.a.valeur.nbentier / ab.b.valeur.nbentier ; break ;
  case rationnel : c.valeur.nbrationnel = quoRationnel(ab.a.valeur.nbrationnel,
						       ab.b.valeur.nbrationnel) ; break ;
  case flottant : c.valeur.nbflottant = ab.a.valeur.nbflottant / ab.b.valeur.nbflottant ; break ;
  case complexe : c.valeur.nbcomplexe = quoComplexe(ab.a.valeur.nbcomplexe,
						       ab.b.valeur.nbcomplexe) ; break ;
  default : exit(-1) ; break ;
  }
  c.tn = ab.a.tn ;
  return c ;
}


int main(void){

  Nombre var1, var2, var3 ;

  var1.tn = rationnel ;
  var1.valeur.nbrationnel.numerateur = 1 ;
  var1.valeur.nbrationnel.denominateur = 4 ;

  var2.tn = entier ;
  var2.valeur.nbentier= 4 ;

  var3.tn = complexe ;
  var3.valeur.nbcomplexe.partie_reelle = 2.54 ;
  var3.valeur.nbcomplexe.partie_imaginaire = 4.45 ;

  PrintNombre(var1) ;
  printf(" et ");
  PrintNombre(var2) ;
  printf(" et ");
  PrintNombre(var3) ;
  printf(".\n");


  PrintNombre(QuoNombre(MulNombre(var1,var2),var3)) ;
  printf(".\n");

  return 1 ;
}

 
