# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* EXERCICE 3.1 */
/* Ces paramètres doivent être des pointeurs de type int*
   ou char* selon le format. */

/* EXERCICE 3.2 */
int ScanString(char *s, unsigned int stringsize){
  stringsize--; /* pour pouvoir placer un 0 en fin */
  while(1){
    if (!stringsize)
      return 1;
    *s = (char) getchar();
    switch(*s){
    case EOF:
      ;
    case '\n':
      *s = 0;
    case 0:
      break;
    };
    s++;
    stringsize--;
  }
  return 0;
}

/* EXERCICE 3.3 */
int ScanInt(int b, unsigned int *res){
  int c;
  *res = 0;
  while( ((c=(char)getchar()) != EOF || c != '\n') && ( (c=c-'0')>-1 && c <=b)){
    *res *= b;
    *res += c;
  }
  return (int) c;
}

/* EXERCICE 2.4 */
int mscanf(const char *str, ...){
  /* on positionne un pointeur sur le premier paramètre */
  void *tmp = (void*) str;
  int message = 1;
  tmp++;
  while(*str){
    str++;
    /* on cherche le premier format */
    if(*(str-1) != '%')
      continue;
    switch(*str){
    case 'c':
      message *= ScanString((char*) tmp++, 1);
      break;
    case 's':
      message *= ScanString((char*) tmp++, 1<<16);
      break;
    case 'b':
      message *= ScanInt(2, (unsigned int*) tmp++);
      break;
    case 'd':
      message *= ScanInt(10, (unsigned int*) tmp++);
      break;
    default:
      continue;
    }
    if(!message)
      break;
  }
  return message+'0';
}




int main(int argc, char* argv[]){
  int n, b, k;
  char s[] = "%d %b";

  printf("ATTENTION: Ce programme ne fonctionne pas sur des ordinateurs ");
  printf("64 bits.");
  printf("Entrez un entier en base 10 puis un entier en base 2: ");
  k = mscanf(s, &n, &b);

  printf("Les entiers rentrés sont: %d, %d\n", n, b);

  return 0;
}
