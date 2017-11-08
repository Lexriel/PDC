# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

/* pile stockant des décimales d'un nombre */
typedef struct pile_s *pile;
struct pile_s{
  int decimale;
  pile next;
};

/* affiche une chaine de caractère  */
void PrintString(char* s){
  while(*s)
    putchar(*s++);
}

/* affiche une chaine de caractère  */
int est_vide(pile p){
  return p == NULL;
}

/* ajoute 'valeur' sur la pile 'pp'  */
void empiler(pile *pp, int valeur){
  pile new;
  new = malloc(sizeof(pile));
  new->decimale = valeur;
  new->next = *pp;
  *pp = new;
}

/* récupère 'valeur' dans pp puis l'enlève de 'pp' */
void depiler(pile *pp, int *valeur){
  pile debut;
  if (!est_vide(*pp)){
    debut = *pp;
    *valeur = debut->decimale;
    *pp = debut->next;

    free(debut);
  }
  else
    PrintString("ERREUR : pile vide.\n");
}

/* crée une pile avec la valeur 'valeur' */
pile creer_pile(int valeur){
  pile p;
  p = malloc(sizeof(pile));
  p->decimale = valeur;
  p->next = NULL;
  return p;
}

/* convertit la valeur de m en une lettre si elle est au-dessus de 10 */
char convertBase(int m){
  if (m < 10)
    return '0' + m;
  else
    return 'A' + (m-10);
}

/* affiche un entier 'i' en base 'b' */
void PrintInt(int i, int b){
  pile p;
  int valeur;
  /* création de la pile avec le premier reste (première décimale) */
  p = creer_pile(i%b);
  /* remplissage de la pile avec les décimales suivantes */
  while ((i/=b) != 0)
    empiler(&p,i%b);
  /* récupération des décimales dans l'ordre décroissant grâce à la pile */
  while (p){
    depiler(&p, &valeur);
    putchar(convertBase(valeur));
  }
  if (b == 2)
    putchar('b');
  else if (b == 8)
    putchar('o');
  else if (b == 16)
    putchar('x');
}

typedef struct entierGauss_s entierGauss;
struct entierGauss_s{
  int reel;
  int im;
};

/* affiche un entier de Gauss 'G' en base 'b' */
void PrintGauss(entierGauss G, int b){
  pile p, adresse_signe;
  int valeur;
  int i;
  char signe;
  /* création de la pile avec les décimales imaginaires et le signe */
  i = G.im;
  signe = (i<0)?'-':'+';
  i = (i<0)?-i:i;
  p = creer_pile(i%b);
  while ((i/=b) != 0)
    empiler(&p,i%b);
  empiler(&p,(char)signe);
  adresse_signe = p;
  /* remplissage de la pile avec les décimales réelles */
  i = G.reel;
  empiler(&p,i%b);
  while ((i/=b) != 0)
    empiler(&p,i%b);
  /* récupération des décimales dans l'ordre décroissant grâce à la pile */
  while (p != adresse_signe){
    depiler(&p, &valeur);
    putchar(convertBase(valeur));
  }
  if (b == 2)
    putchar('b');
  else if (b == 8)
    putchar('o');
  else if (b == 16)
    putchar('x');
  /* affichage du signe */
  depiler(&p, &valeur);
  putchar((char) valeur);

  /* affichage de la partie imaginaire */
  while (p){
    depiler(&p, &valeur);
    putchar(convertBase(valeur));
  }
  if (b == 2)
    putchar('b');
  else if (b == 8)
    putchar('o');
  else if (b == 16)
    putchar('x');
  putchar('I');
}


enum {NORMAL, DEBUT_DIRECTIVE, DEBUT_BACKSLASH, DEBUT_G};

/* version basique d'une fonction équivalente à printf pour les champs %c, %s, %d, %b */
void mprintf(const char *format, ...){
  char c, lettre;
  char *chaine;
  int etat;
  va_list ap;
  int nombre;
  entierGauss G;
  etat = NORMAL;
  va_start(ap, format);
  /* Analyse de chaque lettre de 'format' */
  while ((c = *format++)){
    /* Dans l'état normal, on distingue les directives, backslash, retour chariot */
    if (etat == NORMAL)
      switch(c){
      case '%' :
	etat = DEBUT_DIRECTIVE;
	break;
      case '\\' : /**/
	etat = DEBUT_BACKSLASH;
	break;
      case '\n' : /* le retour chariot est un caractère qui peut être lu directement */
	putchar('\n');
	break;
      default :
	putchar(c);
	break;
      }
    else if (etat == DEBUT_DIRECTIVE)
      switch(c){
      case '%' :
	putchar('%');
	etat = NORMAL;
	break;
      case ' ' :
	putchar('%'); putchar(' ');
	etat = NORMAL;
	break;
      case 'c' :
	lettre = va_arg(ap,int);
	putchar(lettre);
	etat = NORMAL;
	break;
      case 's' :
	chaine = va_arg(ap, char*);
	PrintString(chaine);
	etat = NORMAL;
	break;
      case 'd' :
	nombre = va_arg(ap,int);
	PrintInt(nombre,10);
	etat = NORMAL;
	break;
      case 'b' :
	nombre = va_arg(ap,int);
	PrintInt(nombre,2);
	etat = NORMAL;
	break;
      case 'G' :
	etat = DEBUT_G;
	break;
      default :
	putchar('%'); putchar(c);
	etat = NORMAL;
	break;
      }
    else if (etat == DEBUT_BACKSLASH)
      switch(c){
      case '\\' :
	putchar('\\');
	etat = NORMAL;
	break;
      default :
	putchar('\\'); putchar(c);
	etat = NORMAL;
	break;
      }
    else /* (etat == DEBUT_G) */
      switch(c){
      case 'd' :
	G = va_arg(ap, entierGauss);
	PrintGauss(G,10);
	etat = NORMAL;
	break;
      case 'b' :
	G = va_arg(ap, entierGauss);
	PrintGauss(G,2);
	etat = NORMAL;
	break;
      case 'h' :
	G = va_arg(ap, entierGauss);
	PrintGauss(G,8);
	etat = NORMAL;
	break;
      case 'x' :
	G = va_arg(ap, entierGauss);
	PrintGauss(G,16);
	etat = NORMAL;
	break;
      default :
	putchar('%'); putchar('G'); putchar(c);
	etat = NORMAL;
	break;
      }
  }
  va_end(ap);
}

/* MAIN */
int main(int argc, char* argv[]){
  entierGauss G;
  char s[] = "ça va mes petits loups ?\n";

  PrintString("\nESSAIS DE PRINTSTRING :\n");
  PrintString("Bonjour les amis !\n");
  PrintString(s);

  PrintString("\nESSAIS DE PRINTINT :\n");
  PrintString("235 en base 10 : ");
  PrintInt(235,10);
  putchar('\n');
  PrintString("235 en base 2 : ");
  PrintInt(235,2);
  putchar('\n');
  PrintString("235 en base 8 : ");
  PrintInt(235,8);
  putchar('\n');
  PrintString("235 en base 16 : ");
  PrintInt(235,16);
  putchar('\n');

  mprintf("\nUSAGE :\n");
  mprintf("mprintf affiche sur 'stdout' le contenu de son premier paramètre, obligatoire.\n");
  mprintf("mprintf peut avoir des paramètres optionnels, correspondant à des directives apparaissant dans le premier paramètre.\n");
  mprintf("Les directives acceptées sont les suivantes :\n");
  mprintf("  * %%d : affiche un entier,\n");
  mprintf("  * %%b : affiche un entier en binaire,\n");
  mprintf("  * %%c : affiche un caractère,\n");
  mprintf("  * %%s : affiche une chaine de caractères.\n");
  mprintf("  * %%Gd : affiche un entier de Gauss.\n");
  mprintf("  * %%Gb : affiche un entier de Gauss en binaire.\n");

  mprintf("Attention, mprintf n'affiche pas d'erreur et s'exécute même s'il n'y a pas assez de paramètres.\n");
  
  mprintf("\nLA LIGNE DE CODE SUIVANTE ...\n");
  mprintf("mprintf(\"%%s Ton prénom commence par %%c et le nombre %%d en base 2 est %%b.\\n.\", 4, \"Salut Alex !\", 'a', 14, 14);\n");
  mprintf("\n... AFFICHE CECI A L'ECRAN :\n");
  mprintf("%s Ton prénom commence par %c et le nombre %d en base 2 est %b.\n", "Salut Alex !", 'a', 12, 12);
  putchar('\n');

  mprintf("GESTION DES ENTIERS DE GAUSS :\n");
  G.reel = 2; 
  G.im = -5;
  mprintf("EntiersGauss %Gd en binaire : %Gb.\n", G, G);

  G.reel = 22; 
  G.im = 0;
  mprintf("EntiersGauss %Gd en octal : %Gh.\n", G, G);

  G.reel = 1019; 
  G.im = 235;
  mprintf("EntiersGauss %Gd en hexadécimal : %Gx.\n", G, G);
  putchar('\n');

  return 0;
}
