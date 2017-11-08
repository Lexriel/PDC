#include <stdio.h>  /* pour afficher et saisir au clavier scanf */

#define Prix_Petit_Dej       6
#define Prix_Chmb_1         40
#define Prix_Chmb_1_R       38
#define Prix_Chmb_2         60
#define Prix_Chmb_2_R       58
#define Prix_Enfant         30

int main(void){
	int NbChInd ;	
	int NbChDou ;	
	int NbEnf   ;	
	int NbNuit  ;	

	int PrixChInd ;
	int PrixChDou ;
	int PrixEnfant ;
	int PrixPetitDej ;
	int PrixTotal ;

	/* On collecte les donnees concernant le client */
	printf("nombre de chambre individuelle ? ") ;
	scanf("%d",&NbChInd) ;
	printf("nombre de chambre double ? ") ;
	scanf("%d",&NbChDou) ;
	printf("nombre d'enfants ? ") ;
	scanf("%d",&NbEnf) ;
	printf("nombre de nuits ? ") ;
	scanf("%d",&NbNuit) ;

	/* La partie de choix proprement dite */

	if (NbChInd < 3)
	  PrixChInd = NbChInd*Prix_Chmb_1 ;
	else	
	  PrixChInd = NbChInd*Prix_Chmb_1_R ;

	if (NbChDou < 4)
	  PrixChDou = NbChDou*Prix_Chmb_2 ;
	else
	  PrixChDou = NbChDou*Prix_Chmb_2_R ;

	if (NbEnf > 3)
	  PrixEnfant = (NbEnf-2)*Prix_Enfant ;
	else	
	  PrixEnfant = 0 ;

	PrixPetitDej = (NbChInd + 2*NbChDou + NbEnf)*Prix_Petit_Dej ;
	
	PrixTotal = (PrixChInd+PrixChDou+PrixEnfant+PrixPetitDej)* NbNuit ;

	/* L'affichage du resultat */
	printf("La somme a payer est %d\n",PrixTotal) ;
	return 1 ;
}
 
