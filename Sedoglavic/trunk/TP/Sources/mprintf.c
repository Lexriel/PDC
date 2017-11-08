#include<stdio.h>

typedef enum {BINAIRE=2, DECIMALE=10} Base_t ;

typedef struct Gauss_t {
  int re ;
  int im ;
  char *name ;
} Gauss_t ;

static void PrintString(char *s){
  
  for(;*s;s++)
    putchar((int) *s) ;  
}

static void PrintInt(int i, Base_t b){

  /*   On va se servir d'une pile pour calculer le mot codant
       l'entier~$i$ dans la base~$b$ */

   int Pile[33] ;

  /* sommet pointe sur la premi\`ere cellule libre de la pile */  

   int sommet = 0 ; 

  /* On stocke la valeur absolue de l'entier */
  
  int stck = (i<0) ? -i : i ;
  int tmp ;
  
  do {
    Pile[sommet++] = tmp = stck%b ;
    stck /= b  ;
  } while (stck) ;
    
  /* On v\'erifie s'il faut mettre un signe */

  if (i<0)
    Pile[sommet++] = '-'-'0' ; 

  /* Reste maintenat \`a faire l'affichage */

  while(sommet)
    putchar(Pile[--sommet] + '0') ;
}

void mprintf(const char *format, ... ){

  int foo = 0 ;
  int *ptr = &foo ;
  int base ; 
  char GaussTxt1[4] = " + " ;
  char GaussTxt2[4] = " I " ;

  /* On passe le pointeur de contexte, l'adresse de retour et un
     pointeur sur le param\`etre obligatoire */
  ptr += 4 ;

  /* Il nous faut parcourir la cha\^\i{}ne de format */
  for(;*format;format++)
    if( *format == '%')
      switch(*(++format)){
      case 'd' : PrintInt(*(ptr++), DECIMALE) ; break ;
      case 'b' : PrintInt(*(ptr++), BINAIRE) ; break ; 
      case 's' : PrintString((char *) *(ptr++)) ; break ; 
      case 'c' : putchar((int) *(ptr++)) ; break ; 
      case 'G' : {
	if (*(++format)== 'b')
	  base = BINAIRE ;
	else base = DECIMALE ; 
	PrintInt(*(ptr++), base) ;
	PrintString(GaussTxt1) ;
	PrintInt(*(ptr++), base) ;	  
	PrintString(GaussTxt2) ;
	ptr++ ; /* Pour passer le nom de l'entier de Gauss */
	break ;
      }
      default : putchar((int) *format) ; break ;
      }
    else putchar((int) *format) ;
}

int main(){

  char str[80] = "Vive PDC" ;

  struct Gauss_t gauss= {.re = 10, .im = 22, .name = str } ;

  char bar = 'x' ;
  int foo = 11 ;

  PrintString("Hello world\n") ;

  PrintInt(234124,DECIMALE) ;
  putchar('\n') ;
  PrintInt(234124,BINAIRE) ;
  putchar('\n') ;
  PrintInt(0,DECIMALE) ;
  putchar('\n') ;
  PrintInt(0,BINAIRE) ;
  putchar('\n') ;
  PrintInt(-1024,DECIMALE) ;
  putchar('\n') ;
  PrintInt(-1024,BINAIRE) ;
  putchar('\n') ;

  mprintf("o %c u %d e \n", bar, foo) ;
  mprintf("o %Gb ue", gauss) ;

  return 0 ;
}
