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
   } bibi = {

     .nom = "Moi",
     .prenom = "Idem",
     .age = 100,
     .adr.num = 39,
     .adr.rue = "Publique",
     .adr.code = 58000,
     .adr.ville = "Lille"
};

struct personne bobo;

int main(){

  bobo = bibi ;

  return 0 ;

}
