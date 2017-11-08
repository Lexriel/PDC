#include <stdio.h>
#include <string.h>

#define STOP 0

/* le nombre maximal de mots */
#define N 100

int main(void) {

  int i;
  int stop ;
  char chaine[32] ;

  /* Tableaux constituant la table */

  char *ABR[N] ;
  char *EXP[N] ;

  /* Initialisation de la table */

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
  ABR[10]="SCSI";
  EXP[10]="Small Computer System Interface";
  ABR[11]="ROM";
  EXP[11]="Read Only Memory";
  ABR[12]="RTFM";
  EXP[12]="Read The Fucking Manuel";
  ABR[13]="VLSI";
  EXP[13]="Very Large Scale Integration";

  do{

    /* Saisie de l'abreviation a chercher */
    printf("Abreviation a expliciter : ") ;
    scanf("%s",chaine) ;

    /* On place une sentinelle a la fin de la liste connu pour 
       assurer la bonne terminaison de notre programme          */

    EXP[14] = "Abreviation inconnu\n" ;
    ABR[14] = chaine ;

    /* La recherche proprement dit */
    for(i=1;strcmp(ABR[i],chaine);++i) ;

    /* l'affichage du resultat */
    printf(" => %s \n",EXP[i]) ;

    /* Pour permettre une autre saisie */
    printf("Stop ou encore (0 pour stop, 1 pour encore) ") ;
    scanf("%d",&stop) ;
    
  } while(stop!=STOP) ;

  return 1 ;

}

 
