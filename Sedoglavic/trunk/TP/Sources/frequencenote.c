#include <stdio.h>

#define NbNote 500
#define NoteMax 20

int main(void) {
  
  int resultat[NbNote] = {3, 7, 9,  0, 18, 5, 4, 19,  8, 3, 10, 7, 14, 13,
			  0, 18, 17, 5, 16, 4, 5, 1, 20, 6, 16, 10, 13, 12,
			  6, 5, 20, 8, 9, 15, 3, 17, 12, 10, 19, 3, 13, 4,
			  13, 14 , 17, 17, 15, 14, 18, 6, 17, 9, 9, 6, 15,
			  17, 11, 8, 8, 0, 19,  19, 13, 18, 11, 1,  16, 5,
			  16, 7, 18, 20, 3, 16, 3, 9, 1, 3, 20, 11, 6, 19,
			  0, 13, 10, 14, 13,  5, 1, 16, 2, 19, 10, 2, 14, 
			  6, 8, 15, 4, 6, 8, 20, 4, 2, 0, 18,  19, 20, 13, 
			  1, 13, 16, 12, 12, 7, 19, 13, 11, 3, 18, 10, 7,
			  20, 0, 4, 4, 16, 14, 19, 0, 0, 16, 4, 0, 7, 18, 
			  15, 8, 8, 6, 1, 12, 17,  9, 1, 4, 13,  0, 8, 15, 
			  19, 4,3, 1, 3, 1, 1, 1, 6, 10, 15, 8, 14, 17, 14,
			  3, 5, 0, 19, 6, 8, 13, 14,2, 1, 12, 4, 1, 10, 17, 
			  11, 7,  11, 12, 6, 10,  8, 18, 13, 15, 12, 14,8, 2,
			  2, 3, 17, 6,  9, 17, 9, 19,  16, 8, 18, 0, 10,  15,
			  2, 17, 2, 3,13, 19, 13, 12, 12, 2, 2, 4, 17, 17, 17,
			  2, 11, 19, 13, 8, 0, 9, 8, 5,4, 13, 9, 9, 19, 15, 
			  19, 1, 19, 10, 20, 1, 11, 8,  13, 0, 10, 6, 5, 1,
			  11, 0, 8, 13, 5, 0, 15, 9, 7, 0, 10, 0, 1,  12, 12, 
			  10,  19, 17, 0, 6,16, 12, 8, 12, 14, 13, 15, 20, 7, 
			  17, 1, 18, 15, 13, 6, 14, 18, 8, 13,14, 8, 14, 7, 
			  16, 2, 19, 14, 6, 17, 8, 11, 14, 16, 11,  19, 2, 20,
			  16,2, 13, 14, 20, 6, 13, 20, 9, 3, 19, 3, 0, 7, 0, 
			  16,  7, 4, 15, 16, 17,2, 14, 3, 15, 12, 16, 18, 1, 
			  5,  9, 2, 1, 5, 9,  5, 13, 10, 11, 16, 6,16, 8, 13, 
			  11, 6, 8, 2, 5, 2, 5, 9, 1,  7, 20, 19, 4, 14,  2, 
			  8, 9, 5,9, 9, 5, 15, 12, 3, 7, 15, 17, 6, 0, 7, 2, 
			  17, 19,  20, 15, 1, 11, 11,18, 9, 7, 1, 1, 17, 1, 
			  17, 10, 2, 5, 1,  14, 7, 2, 3, 0,  4, 2, 9, 17,3, 6,
			  7, 18, 14, 14,  4, 10, 3, 15,  16, 17, 6, 15, 12,  
			  17, 9, 5, 14,14, 6, 4, 4, 4, 17, 10, 10, 11, 13, 16,
			  3, 0, 2, 18, 3,  20, 5, 16, 6,0, 8, 3, 3, 10, 2, 0,
			  6, 11, 12, 9, 18, 8, 6, 2, 0, 0,  19, 12, 17, 5,19, 
			  12, 17, 4, 0, 20, 8, 3, 7,  6, 10, 0,  3, 4, 4,  6,
			  11, 0, 13, 14,18, 20, 12, 3, 18, 3, 13, 14};

 int frequence[NoteMax] ; /* Pour stocker la frequence des notes */

 int i,j ; /* Indices */

 int max=0,min=NoteMax  ; /* le minimun et le maximum */
 int maxInd=0, minInd=0 ; /* leurs indices */

 /* Initialisation du tableau de frequences */
 for(i=0;i<NoteMax;i++)
   frequence[i]=0 ;
 
 /* Saisie Des Frequences */
 for(i=0;i<NbNote;i++)
   frequence[resultat[i]] +=1 ;

 /* affichage de l'histogramme */
 for(i=0;i<NoteMax+1;i++) {
   for(j=0;j<frequence[i];j++) 
     printf("X") ;
   printf(" %d\n",i) ;
 }

 /* determination des extrema */
 for(i=0;i<NoteMax+1;i++) {
   if(max<frequence[i]){
     max=frequence[i] ; maxInd = i ;
   }
   if(min>frequence[i]){
     min=frequence[i] ; minInd = i ;
   }
 }

 /* affichage */
 printf("la note la plus frequente est %d avec %d occurences\n",maxInd,max) ;
 printf("la note la moins frequente est %d avec %d occurences\n",minInd,min) ;

 return 0 ;
}
 