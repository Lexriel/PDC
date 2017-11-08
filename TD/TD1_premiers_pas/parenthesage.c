# include <stdio.h>
# include <stdlib.h>

int main (){
  int ouvertes = 0;
  int carac;
  while ( (carac = getchar()) != EOF )
    switch (carac){
    case '(':
      ouvertes++;
      break;
    case ')':
      if (ouvertes <= 0){
	printf("Erreur de fermeture\n");
	exit(EXIT_FAILURE);
      }
      else
	ouvertes--;
      break;
    default: ;
    }

  if (ouvertes != 0){
    printf ("Manque %d fermetures\n", ouvertes);
    exit(EXIT_FAILURE);
  }
  printf ("Parenthésage correct\n");
  
  exit(EXIT_SUCCESS) ;
}
