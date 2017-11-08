# include <stdio.h>

/* retourne sur la sortie standard grâce à putchar (cf. man) la chaîne
   de caractères représentant l'entier pris en paramètre. L'entier est
   plus petit que 81, on a donc au plus deux décimales. */
extern void affiche_entier(int n){
  int nbDecimales, tmp, P;
  if (n == 0){
    putchar('0');
    return;
  }
  tmp = n;
  nbDecimales = 0;
  P = 1;
  while (tmp){
    tmp /= 10;
    nbDecimales++;
    P *= 10;
  }
  P /= 10;

  while (P != 0){
    tmp = n/P;
    putchar('0'+tmp);
    n -= P*tmp;
    P /= 10;
  }
}
extern void affiche_entier2(int n){
  int dizaine, unite;

  dizaine = n/10;
  if (dizaine)
    putchar(dizaine + '0');
  unite = n % 10;
  putchar(unite + '0');
}
