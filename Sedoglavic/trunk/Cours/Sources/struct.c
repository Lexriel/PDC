   struct adresse {
     int num;
     char rue[40];
     long int code;
     char ville[20];
   };

   struct personne {
     char nom[20];
     char prenom[25];
     int age;
     struct adresse adr;
   } bibi ;

int main(){

  bibi.nom[0] = 'M' ;
  bibi.nom[1] = 'o' ;
  bibi.nom[2] = 'i' ;
  bibi.nom[3] = 0 ;

  bibi.prenom[0] = 'I' ;
  bibi.prenom[1] = 'd' ;
  bibi.prenom[2] = 'e' ;
  bibi.prenom[3] = 'm' ;
  bibi.prenom[4] = 0 ;

  bibi.age = 100 ;
  bibi.adr.num = 39 ;

  bibi.adr.rue[0] = 'P' ;
  bibi.adr.rue[1] = 'u' ;
  bibi.adr.rue[2] = 'b' ;
  bibi.adr.rue[3] = 'l' ;
  bibi.adr.rue[4] = 'i' ;
  bibi.adr.rue[5] = 'q' ;
  bibi.adr.rue[6] = 'u' ;
  bibi.adr.rue[7] = 'e' ;
  bibi.adr.rue[8] = 0 ; 


  bibi.adr.ville[0] = 'L' ;
  bibi.adr.ville[1] = 'i' ;
  bibi.adr.ville[2] = 'l' ;
  bibi.adr.ville[3] = 'l' ;
  bibi.adr.ville[4] = 'e' ;
  bibi.adr.ville[5] = 0 ;

  return 0 ;

}
