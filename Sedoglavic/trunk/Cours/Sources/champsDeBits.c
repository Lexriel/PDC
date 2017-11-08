
struct {
  unsigned int est_mot_cle : 1;
  unsigned int est_externe : 1;
  unsigned int est_statique : 1;
} drapeaux = {
/* Mise a 1 */
   .est_externe = 1,
   .est_statique = 1 
	
};

int main(){
/* Mise a 0 */
   drapeaux.est_externe = 0 ;
  return 0 ;
} 
