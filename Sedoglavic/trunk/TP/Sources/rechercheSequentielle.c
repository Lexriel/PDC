#include <stdio.h>
#include <string.h> 

#define STOP 0

/* le nombre maximal de mots */
#define N 100

int main(void) {

  int fin      ;  /*  fin de la table                            */
  int i        ;  /*  parcourir la table                        */
  int stop     ;  /* Pour saisir l'instruction de l'utilisateur */

  char chaine[32] ;

  /* Tableaux constituant la table */

  char *ABR[N] ;
  char *EXP[N] ;

  /* Initialisation de la table 
     les tableaux devraint commencer par 0 */

  ABR[1]="ANSI";
  EXP[1]="American National Standards Institute";
  ABR[2]="ASCII";
  EXP[2]="American Standard Code for Information Interchange";
  ABR[3]="BIOS";
  EXP[3]="Basic Input/Output System";
  ABR[4]="GRUB";
  EXP[4]="Grand Unified Bootloader";
  ABR[5]="IDE";
  EXP[5]="Integrated Drive Electronics";
  ABR[6]="ISA";
  EXP[6]="Instruction Set Architecture";
  ABR[7]="ISO";
  EXP[7]="International Standards Organization";
  ABR[8]="OS";
  EXP[8]="Operating System";
  ABR[9]="PCI";
  EXP[9]="Peripheral Component Interconnect";
  ABR[10]="ROM";
  EXP[10]="Read Only Memory";
  ABR[11]="RTFM";
  EXP[11]="Read The Fucking Manuel";
  ABR[12]="SCSI";
  EXP[12]="Small Computer System Interface";
  ABR[13]="VLSI";
  EXP[13]="Very Large Scale Integration";

  fin = 14 ;    
  EXP[fin] = "Abreviation inconnu\n" ;   
  ABR[fin] = "foo" ;   

  do{

    /* Saisie de l'abreviation a chercher */
    printf("Abreviation a expliciter : ") ;
    scanf("%s",chaine) ;

    /* La recherche proprement dit */
     for( i=1; strcmp(ABR[i],chaine) ; ++i) ; 

    /* l'affichage du resultat */
    printf(" => %s \n",EXP[i]) ;  

    /* Pour permettre une autre saisie */
    printf("Stop ou encore (0 pour stop, 1 pour encore, 2 pour saisir) ") ;
    scanf("%d",&stop) ;

    if (stop==2)
      if (fin<N){
        /* Gestion de la sentinelle */
        fin++ ;    
        EXP[fin] = "Abreviation inconnu\n" ;   
        ABR[fin] = "foo" ;   
        
        /* Saisie de la nouvelle donnee dans la table */
        printf("Entrer l'abreviation ") ;
        scanf("%s",chaine) ;
        ABR[fin-1]=chaine ;
        printf("Entrer son sens ") ;
        scanf("%s",chaine) ;
        EXP[fin-1]=chaine ;
      }
      else printf("Plus de place dans le tableau") ;
  } while(stop!=STOP) ;
  return 1 ;
}
 
