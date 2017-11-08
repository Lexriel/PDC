# include <stdio.h>
# include <stdlib.h>
# define SIZE 100

/* Compilation : gcc -o dicho dicho.c */

int search_iterative(float x, float v[], int n){
  int debut, fin, milieu;
  debut = 0;
  fin = n-1;

  while (debut <= milieu){
      milieu = (debut+fin)/2;
      if (v[milieu] == x)
	return milieu;
      else if (v[milieu]>x)
	/* recherche dans la moitié gauche */
	fin = milieu - 1;
      else
	/* recherche dans la moitié droite */
	debut = milieu + 1;
    }

  /* si le code arrive ici, x n'a pas été trouvé dans le tableau */
  return -1;
}

/* La version récursive pose un problème pour retourner -1 dans le cas
   où x n'est pas dans le tableau, ceci justifie l'ajout d'un
   paramètre pos, qui doit valoir 0 au premier appel de cette
   fonction. Le n-n/2 se justifie par le fait que la division entière
   pose le problème suivant : n/2+(n-n/2)=n mais n/2+n/2!=n (si n est
   impair). */
int search_recursive(float x, float v[], int n, int pos){
  if (n==1)
    if (v[0] == x)
      return 0;
    else
      return -pos-1;
  else if (x<v[n/2])
    return search(x,v,n/2, pos);
  else
    return n/2 + search(x, &v[n/2], n-n/2, pos+n/2);
}

/* Après compilation, lancer: ./dicho 5.7 (ou tout autre
   flottant). 5.7 est ici un argument stocké dans argv[1] en tant que
   chaine de caractères. */
int main(int argc, char* argv[]){
  int pos;
  float a;
  float s[] = {0., 2.5, 4.2, 5.1, 6.9, 7.8, 10.9, 11.};
  a = atof(argv[1]); /* convertit la chaine de caractère '5.8' en flottant */
  pos = search_recursive(a, s, 8, 0);
  /* pos = search_iterative(a, s, 8); */
  printf("%d\n", pos);

  exit(EXIT_SUCCESS);
}
