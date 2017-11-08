typedef struct Complexe {
  float partie_reelle ;
  float partie_imaginaire ;
} Complexe ;

void PrintComplexe ( Complexe a ){

  if (a.partie_reelle!=0)
    printf("%f",a.partie_reelle) ;

  if (a.partie_imaginaire>0)
    printf("+%f*I ",a.partie_imaginaire) ;

  if (a.partie_imaginaire<0)
    printf("-%f*I ",-a.partie_imaginaire) ;
}

Complexe  addComplexe ( Complexe a, Complexe b) {

  Complexe c ;

  c.partie_imaginaire = a.partie_imaginaire+b.partie_imaginaire ;
  c.partie_reelle = a.partie_reelle+b.partie_reelle ;
    
  return c ;
}

Complexe mulComplexe ( Complexe a, Complexe b) {

  Complexe c ;

  c.partie_reelle = a.partie_reelle*b.partie_reelle - a.partie_imaginaire*b.partie_imaginaire  ;
  c.partie_imaginaire = b.partie_reelle*a.partie_imaginaire+a.partie_reelle*b.partie_imaginaire ;
    
  return c ;
}

Complexe quoComplexe ( Complexe a, Complexe b) {

  Complexe d = {b.partie_reelle, -b.partie_imaginaire}  ;
  Complexe c = mulComplexe(a,d) ;

  d = mulComplexe(b,d) ;
 
  c.partie_reelle /= d.partie_reelle ;
  c.partie_imaginaire /= d.partie_reelle ;
    
  return c ;
}

 
