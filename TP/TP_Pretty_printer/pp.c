#include <stdio.h>
#include <stdlib.h>
#define INDENT 2

/* indent(n) imprime sur la sortie standard l'équivalent de n*INDENT blancs où IDENT est le nombre de blancs correspondant à une indentation */
void indent(unsigned int n){
  int i;
  for(i = 0; i<n*INDENT ; i++){
    putchar(' ');
  }
}

/* pp() prend un ficher texte contenant un programme C sur l'entrée standard et renvoie le même fichier texte mis en forme : filtre pretty-printer */

int main(){
  int c, decalage, valide;
  /* Les différents états de l'automate */
  enum {DEBUT_LIGNE, LIGNE_COURANTE, DEB_COM, DEB_COM_LIGNE, DANS_COM, FIN_COM, SANS_ESPACE, DIESE, CHAINE_CARACTERE, DANS_CHAINE, CARACTERE, DANS_CARACTERE, RETOUR_LIGNE} etat;
  
  /* valide vaut 0 dès qu'on a une accolade fermante ne correspondant pas à une accolade ouvrante dans le programme */
  valide = 1;
  /* decalage correspond à l'identation courante, il est incrementé à chaque accolade ouvrante et décrémenté à chaque accolade fermante */
  decalage = 0;
  /* etat initial de l'automate */
  etat = DEBUT_LIGNE;

  /* On fait tourner l'automate jusqu'à la lecture de la fin du fichier */
  while((c=getchar()) != EOF) {
    switch (etat) {


      /* Etat initial de l'automate, on retourne sur cet état lors de la lecture d'un retour à la ligne (non forcé par le programme). */
    case DEBUT_LIGNE :
      switch(c){

	/* On filtre les espaces et les tabulations afin de respecter l'indentation. */
      case ' ':

      case '\t':
	break;

	/* A la lecture d'une accolade ouvrante, on effectue l'indentation afin de bien placer l'accolade, on met à jour l'indentation courante puis on passe sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '{':
	indent(decalage);
	decalage++;
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'une accolade fermante, on met à jour l'indentation courante, on l'effectue afin de bien placer l'accolade puis on reste sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '}':
	/* On teste si il existe une accolade ouvrante correspondante */
	if(decalage){
	  decalage--;
	  indent(decalage);
	}
	else{
	  valide = 0;
	  fprintf(stderr,"Trop d'accolades fermantes.\n");
	}
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'un point virgule, on effectue l'indentation afin de bien placer le point virgule puis on passe sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */
      case ';':
	indent(decalage);
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'un dièse, on l'imprime et on passe sur l'état DIESE pour traitement particulier des directives sans effectuer l'indentation. */
      case '#':
	putchar(c);
	etat = DIESE;
	break;

	/* A la lecture d'une double quote, on effectue l'indentation, on l'imprime et on passe à l'état CHAINE_CARACTERE pour traitement particulier des chaînes de caractères. */
      case '"':
	indent(decalage);
	putchar(c);
	etat = CHAINE_CARACTERE;
	break;

	/* A la lecture d'une quote, on effectue l'indentation, on l'imprime et on passe à l'état CARACTERE pour traitement particulier des caractères. */
      case '\'':
	indent(decalage);
	putchar(c);
	etat = CARACTERE;
	break;

	/* A la lecture d'un slash, on ne l'imprime pas et on passe dans l'état DEB_COM en attente d'un éventuel début de commentaire. */
      case'/':
	etat = DEB_COM;
	break;

	/* A la lecture d'un retour à la ligne, on l'imprime sans effectuer d'indentation et on reste dans cet état */
      case '\n':
	putchar(c);
	break;

	/* Par défaut, on imprime le caractère et on passe à l'état LIGNE_COURANTE afin de ne pas refaire une indentation. */
      default:
	indent(decalage);
	putchar(c);
	etat = LIGNE_COURANTE;
	break;
      }
      break;


      /* On se trouve sur cet état si on n'est pas en début de ligne, ni dans une chaîne de caractères, ni dans une directive, ni dans un commentaire. */
      /* Dans cet état, on ne considère plus le dièse comme un début de directive, on ne filtre plus les espaces et on n'effectue aucune indentation. */
    case LIGNE_COURANTE :
      switch(c){

	/* A la lecture d'une accolade ouvrante, on va à la ligne, on effectue l'indentation afin de bien placer l'accolade, on met à jour l'indentation courante puis on passe sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '{':
	putchar('\n');
	indent(decalage);
	decalage++;
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'une accolade fermante, on va à la ligne, on met à jour l'indentation courante, on l'effectue afin de bien placer l'accolade puis on reste sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '}':
	putchar('\n');
	/* On teste si il existe une accolade ouvrante correspondante */
	if(decalage){
	  decalage--;
	  indent(decalage);
	}
	else{
	  valide = 0;
	  fprintf(stderr,"Trop d'accolades fermantes.\n");
	}
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'un point virgule, on l'imprime puis on passe sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */
      case ';':
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'une double quote, on l'imprime et on passe à l'état CHAINE_CARACTERE pour traitement particulier des chaînes de caractères. */
      case '"':
	putchar(c);
	etat = CHAINE_CARACTERE;
	break;

	/* A la lecture d'une quote, on l'imprime et on passe à l'état CARACTERE pour traitement particulier des caractères. */
      case '\'':
	putchar(c);
	etat = CARACTERE;
	break;

	/* A la lecture d'un slash, on n'imprime pas celui-ci et on passe dans l'état DEB_COM_LIGNE en attente d'un éventuel début de commentaire. */
      case'/':
	indent(decalage);
	etat = DEB_COM_LIGNE;
	break;

	/* A la lecture d'un retour à la ligne, on l'imprime et on retourne dans l'état DEBUT_LIGNE */
      case '\n':
	putchar(c);
	etat = DEBUT_LIGNE;
	break;

	/* Par défaut, on imprime le caractère et on reste sur le même état. */
      default:
	putchar(c);
	break;
      }
      break;


      /* On se trouve sur cet état si le dernier caractère connu est un slash lu en début de ligne. */
      /* On veut donc savoir si on a effectivement un début de commentaire ou non.  */
    case DEB_COM :
      switch(c){

	/* A la lecture de l'étoile, on sait qu'on rentre dans un commentaire, on effectue donc l'indentation (puisque l'on se trouve en début de ligne), on imprime le slash en attente et l'étoile puis on passe dans l'état DANS_COM. */
      case '*':
	indent(decalage);
	putchar('/');
	putchar(c);
	etat = DANS_COM;
	break;

	/* A la lecture d'un slash, on effectue l'indentation, on imprime le slash en attente et on passe à l'état DEB_COM_LIGNE puisqu'on va lire un commentaire qui ne se trouve pas en début de ligne. */
      case '/':
        indent(decalage);
	putchar(c);
	etat = DEB_COM_LIGNE;
	break;

	/* A la lecture d'une accolade ouvrante, on effectue l'indentation et on imprime le slash en attente, on va à la ligne, on effectue l'indentation afin de bien placer l'accolade, on met à jour l'indentation courante puis on passe sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '{':
	indent(decalage);
	putchar('/');
	putchar('\n');
	indent(decalage);
	decalage++;
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'une accolade fermante, on effectue l'indentation et on imprime le slash en attente, on va à la ligne, on met à jour l'indentation courante, on l'effectue afin de bien placer l'accolade puis on reste sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '}':
	indent(decalage);
	putchar('/');
	putchar('\n');
	/* On teste si il existe une accolade ouvrante correspondante */
	if(decalage){
	  decalage--;
	  indent(decalage);
	}
	else{
	  valide = 0;
	  fprintf(stderr,"Trop d'accolades fermantes.\n");
	}
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'un point virgule, on effectue l'indentation, on imprime le slash en attente puis le point virgule. On passe sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */
      case ';':
	indent(decalage);
	putchar('/');
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'un retour à la ligne, on effectue l'indentation puiqu'on se trouve en début de ligne, on imprime le slash en attente, le retour à la ligne puis on repasse à l'état DEBUT_LIGNE. */
      case '\n':
	indent(decalage);
	putchar('/');
	putchar(c);
	etat = DEBUT_LIGNE;
	break;

	/* A la lecture d'une double quote, on effectue l'indentation, on imprime le slash en attente puis la double quote et on passe à l'état CHAINE_CARACTERE pour traitement particulier des chaînes de caractères. */
      case '"':
	indent(decalage);
	putchar('/');
	putchar(c);
	etat = CHAINE_CARACTERE;
	break;

	/* A la lecture d'une quote, on effectue l'indentation, on imprime le slash en attente puis la quote et on passe à l'état CARACTERE pour traitement particulier des caractères. */
      case '\'':
	indent(decalage);
	putchar('/');
	putchar(c);
	etat = CARACTERE;
	break;

	/* Par défaut, on sait que le slash n'indique pas un début de commentaire, on effectue l'identation (puisque l'on se trouve en début de ligne), on imprime le slash en attente et le caractère courant puis on passe dans l'état LIGNE_COURANTE car on a deux caractères sur la ligne courante. */
      default:
	indent(decalage);
	putchar('/');
	putchar(c);
	etat = LIGNE_COURANTE;
	break;
      }

      break;


      /* On se trouve sur cet état si le dernier caractère connu est un slash non lu en début de ligne, on n'effectura donc aucune indentation. */
      /* On veut donc savoir si on a effectivement un début de commentaire ou non. */
    case DEB_COM_LIGNE :
      switch(c){

	/* A la lecture de l'étoile, on sait qu'on rentre dans un commentaire. Puisque nous ne sommes pas en début de ligne, on imprime un retour à la ligne, on imprime le slash en attente et l'étoile puis on passe dans l'état DANS_COM. */
      case '*':
	putchar('\n');
	indent(decalage);
	putchar('/');
	putchar(c);
	etat = DANS_COM;
	break;

	/* A la lecture d'un slash, on imprime le slash en attente et on reste dans le même état car on peut lire un début de commentaire par la suite. */
      case '/':
	putchar(c);
	break;

	/* A la lecture d'une accolade ouvrante, on imprime le slash en attente, on va à la ligne, on effectue l'indentation afin de bien placer l'accolade, on met à jour l'indentation courante puis on passe sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '{':
	putchar('/');
	putchar('\n');
	indent(decalage);
	decalage++;
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'une accolade fermante, on imprime le slash en attente, on va à la ligne, on met à jour l'indentation courante, on l'effectue afin de bien placer l'accolade puis on reste sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */
      case '}':
	putchar('/');
	putchar('\n');
	/* On teste si il existe une accolade ouvrante correspondante */
	if(decalage){
	  decalage--;
	  indent(decalage);
	}
	else{
	  valide = 0;
	  fprintf(stderr,"Trop d'accolades fermantes.\n");
	}
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'un point virgule, on imprime le slash en attente puis le point virgule. On passe sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */
      case ';':
	putchar('/');
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* A la lecture d'un retour à la ligne, on effectue l'indentation puiqu'on se trouve en début de ligne, on imprime le slash en attente, le retour à la ligne puis on repasse à l'état DEBUT_LIGNE. */
      case '\n':
	putchar('/');
	putchar(c);
	etat = DEBUT_LIGNE;
	break;

	/* A la lecture d'une double quote, on imprime le slash en attente puis la double quote et on passe à l'état CHAINE_CARACTERE pour traitement particulier des chaînes de caractères. */
      case '"':
	putchar('/');
	putchar(c);
	etat = CHAINE_CARACTERE;
	break;

	/* A la lecture d'une quote, on imprime le slash en attente puis la quote et on passe à l'état CARACTERE pour traitement particulier des caractères. */
      case '\'':
	putchar('/');
	putchar(c);
	etat = CARACTERE;
	break;

	/* Par défaut, on sait que le slash n'indique pas un début de commentaire, on imprime le slash en attente et le caractère courant puis on repasse dans l'état LIGNE_COURANTE. */
      default:
	putchar('/');
	putchar(c);
	etat = LIGNE_COURANTE;
	break;
      }

      break;


      /* On se trouve dans cet état lorsque l'on a lu un début de commentaire et que le précédent caractère lu n'est pas une étoile. */
      /* On ignore tous les caractères spéciaux sauf l'étoile et le retour à la ligne puisque nous sommes dans un commentaire. Il n'y a aucune indentation à effectuer. */
    case DANS_COM :
      switch(c){

	/* A la lecture d'une étoile, on imprime celle-ci et on se prépare à lire une éventuelle fin de commentaire en passant dans l'état FIN_COM. */
      case '*':
	putchar(c);
	etat = FIN_COM;
	break;

	/* A la lecture d'un retour à la ligne, on ferme le commentaire courant et on passe à la ligne. On effectue l'indentation puis on ouvre un nouveau commentaire en forçant un espace, enfin on passe à l'état SANS_ESPACE afin de filtrer les espaces en début du nouveau commentaire (l'utilisateur ayant pu effectuer l'indentation). */
      case '\n':
	printf("*/\n");
	indent(decalage);
	printf("/* ");
	etat = SANS_ESPACE;
	break;

	/* Par défaut, on imprime le caractère lu et on reste dans le commentaire. */
      default:
	putchar(c);
	break;
      }

      break;


      /* On se trouve dans cet état après avoir lu un retour à la ligne dans un commentaire. */
      /* On ignore tous les caractères spéciaux sauf l'étoile et le retour à la ligne puisque nous sommes dans un commentaire. Il n'y a aucune indentation à effectuer. */
    case SANS_ESPACE :
      switch(c){

	/* On filtre les espaces et les tabulations afin de conserver un unique espace entre le debut du nouveau commentaire et le premier caractère du texte. */
      case ' ':

      case '\t':
	break;

	/* A la lecture d'une étoile, on imprime celle-ci et on se prépare à lire une éventuelle fin de commentaire en passant dans l'état FIN_COM. */
      case '*':
	putchar(c);
	etat = FIN_COM;
	break;

	/* A la lecture d'un retour à la ligne, on ferme le commentaire courant et on passe à la ligne. On effectue l'indentation puis on ouvre un nouveau commentaire en forçant un espace, enfin on reste à l'état SANS_ESPACE afin de filtrer les espaces en début du nouveau commentaire (l'utilisateur ayant pu effectuer l'indentation). */
      case '\n':
	printf("*/\n");
	indent(decalage);
	printf("/* ");
	etat = SANS_ESPACE;
	break;

	/* Par défaut, on imprime le caractère lu et on retourne dans l'état DANS_COM afin de ne pas filtrer les futurs espaces et tabulations. */
      default:
	putchar(c);
	etat = DANS_COM;
	break;
      }

      break;


      /* On se trouve dans cet état après avoir lu une étoile dans un commentaire. */
      /* On ignore tous les caractères spéciaux sans l'étoile, le slash et le retour à la ligne puisque nous sommes encore dans un commentaire. Il n'y a aucune indentation à effectuer. */
    case FIN_COM :
      switch(c){

	/* A la lecture d'une étoile, on l'imprime et on reste dans le même état car on peut lire une fin de commentaire par la suite. */
      case '*':
	putchar(c);
	break;

	/* A la lecture d'un slash, on sait que l'on sort d'un commentaire, on l'imprime et on passe dans l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */
      case '/':
	putchar(c);
	etat = RETOUR_LIGNE;
	break;

	/* Par défaut, on sait que l'étoile n'indique pas une fin de commentaire, on imprime donc le caractère lu et on retourne à l'état DANS_COM. */
      default:
	putchar(c);
	etat = DANS_COM;
	break;
      }

      break;


      /* On se trouve dans cet état lorque l'on a lu un dièse en début de ligne courante : directive au pré-processeur. */
      /* On ignore tous les caractères spéciaux sauf le retour à la ligne puisque nous sommes dans une directive. Il n'y a aucune indentation à effectuer. */
    case DIESE :
      switch(c){

	/* A la lecture d'un retour à la ligne, on l'imprime et on retourne à l'état DEBUT_LIGNE car la déclaration de la directive est terminée. */
      case '\n':
	etat = DEBUT_LIGNE;

	/* Par défaut, on imprime le caractère lu et on reste dans la déclaration de la directive. */
      default :
	putchar(c);
	break;
      }

      break;


      /* On se trouve dans cet état lorsqu'on a lu une double quote non contenue dans un commentaire ou une directive au pré-processeur. */
      /* On ignore tous les caractères spéciaux sauf la double quote et l'anti-slash puisque nous sommes dans une chaîne de caractères. Il n'y a aucune indentation à effectuer. */
    case CHAINE_CARACTERE :
      switch(c){

	/* A la lecture d'une double quote, on sait que la chaîne de caractères est terminée, on repasse donc sur l'état LIGNE_COURANTE puisqu'on a au moins une chaîne de caractères vide sur la ligne courante. */
      case '"':
	putchar(c);
	etat = LIGNE_COURANTE;
	break;

	/* A la lecture d'un anti-slash, on souhaite ignorer une éventuelle fin de chaîne de caractères (lecture d'une double quote), on passe dans sur l'état DANS_CHAINE. */
      case '\\':
	etat = DANS_CHAINE;

	/* Par défaut, on imprime le caractère courant et on reste dans la chaîne de caractères. */
      default:
	putchar(c);
	break;
      }

      break;


      /* On se trouve dans cet état lorsqu'on a lu une quote non contenue dans un commentaire ou une directive au pré-processeur. */
      /* On ignore tous les caractères spéciaux sauf la quote et l'anti-slash puisque nous sommes dans un caractère. Il n'y a aucune indentation à effectuer. */
    case CARACTERE :
      switch(c){

	/* A la lecture d'une quote, on sait que le caractère est terminé, on repasse donc sur l'état LIGNE_COURANTE puisqu'on a au moins une caractère vide sur la ligne courante. */
      case '\'':
	putchar(c);
	etat = LIGNE_COURANTE;
	break;

	/* A la lecture d'un anti-slash, on souhaite ignorer une éventuelle fin de caractère (lecture d'une quote), on passe dans sur l'état DANS_CARACTERE. */
      case '\\':
	etat = DANS_CARACTERE;

	/* Par défaut, on imprime le caractère courant et on reste dans le caractère. */
      default:
	putchar(c);
	break;
      }

      break;


      /* On se trouve dans cet état lorsqu'on lit un anti-slash dans une chaîne de caractères. */
      /* On ignore donc tous les caractères spéciaux puisque nous sommes dans une chaîne de caractères et que l'on vient de lire un anti-slash. Il n'y a aucune indentation à effectuer. */
    case DANS_CHAINE :
      switch(c){

	/* Dans tous les cas, on imprime le caractère lu et on retourne dans l'état CHAINE_CARACTERE puisque le prochain caractère doit être traité normalement. */
      default:
	etat = CHAINE_CARACTERE;
	putchar(c);
	break;
      }

      break;


      /* On se trouve dans cet état lorsqu'on lit un anti-slash dans un caractère. */
      /* On ignore donc tous les caractères spéciaux puisque nous sommes dans un caractère et que l'on vient de lire un anti-slash. Il n'y a aucune indentation à effectuer. */
    case DANS_CARACTERE :
      switch(c){

	/* Dans tous les cas, on imprime le caractère lu et on retourne dans l'état CARACTERE puisque la prochaine quote doit être traité normalement. */
      default:
	etat = CARACTERE;
	putchar(c);
	break;
      }

      break;


      /* On se trouve dans ce état lorque l'on veut forcer un retour à la ligne, c'est-à-dire après la lecture d'une accolade ouvrante ou fermante, d'une fin de commentaire ou d'un point virgule : le caractère suivant nous permet de savoir si l'utilisateur a déjà inséré un saut de ligne ou non. */
    case RETOUR_LIGNE :
      switch(c){

	/* A la lecture d'un retour à la ligne, on l'imprime car on a pas ainsi à forcer le retour à la ligne. On passe à l'état DEBUT_LIGNE. */
      case '\n':
	putchar(c);
	etat = DEBUT_LIGNE;
	break;

	/* On filtre les espaces et les tabulations car on ne veut pas d'une ligne de textes avec des blancs inutiles. */
      case ' ':

      case '\t':
	break;

	/* A la lecture d'une accolade ouvrante, on force le retour à la ligne, on effectue l'indentation afin de bien placer l'accolade, on met à jour l'indentation courante puis on reste sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '{':
	putchar('\n');
	indent(decalage);
	decalage++;
	putchar(c);
	break;

	/* A la lecture d'une accolade fermante, on va à la ligne, on met à jour l'indentation courante, on l'effectue afin de bien placer l'accolade puis on reste sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case '}':
	putchar('\n');
	/* On teste si il existe une accolade ouvrante correspondante */
	if(decalage){
	  decalage--;
	  indent(decalage);
	}
	else{
	  valide = 0;
	  fprintf(stderr,"Trop d'accolades fermantes.\n");
	}
	putchar(c);
	break;

	/* A la lecture d'un point virgule, on force le retour à la ligne, on effectue l'indentation afin de bien placer le point virgule puis on reste sur l'état RETOUR_LIGNE car on ne sait pas si le caractère suivant est un retour à la ligne. */ 
      case ';':
	putchar('\n');
	indent(decalage);
	putchar(c);
	break;

	/* A la lecture d'un dièse, on force le retour à la ligne, on l'imprime et on passe sur l'état DIESE pour traitement particulier des directives sans effectuer l'indentation. */
      case '#':
	putchar('\n');
	putchar(c);
	etat = DIESE;
	break;

	/* A la lecture d'une double quote, on force le retour à la ligne, on effectue l'indentation, on imprime la double quote et on passe à l'état CHAINE_CARACTERE pour traitement particulier des chaînes de caractères. */
      case '"':
	putchar('\n');
	indent(decalage);
	putchar(c);
	etat = CHAINE_CARACTERE;
	break;

	/* A la lecture d'une quote, on force le retour à la ligne, on effectue l'indentation, on imprime la quote et on passe à l'état CARACTERE pour traitement particulier des caractères. */
      case '\'':
	putchar('\n');
	indent(decalage);
	putchar(c);
	etat = CARACTERE;
	break;

	/* A la lecture d'un slash, on force le retour à la ligne, on effectue l'indentation sans imprimer celui-ci et on passe dans l'état DEB_COM en attente d'un éventuel début de commentaire. */
      case'/':
	putchar('\n');
	etat = DEB_COM;
	break;

	/* Par défaut, on force le retour à la ligne, on imprime le caractère et on passe à l'état LIGNE_COURANTE afin de ne pas refaire une indentation. */
      default:
	putchar('\n');
	indent(decalage);
	putchar(c);
	etat = LIGNE_COURANTE;
	break;
      }
      break;
    }
  }

  /* Test si le nombre d'accolades ouvrantes correspond au nombre d'accolades fermantes */
  if(decalage != 0){
    valide = 0;
    fprintf(stderr,"Accolade(s) ouvrante(s) non fermée(s).\n");
  }

  /* Test si le programme se finit par un commentaire non fermé */
  if((etat == DANS_COM)||(etat == FIN_COM)||(etat == SANS_ESPACE)){
    valide = 0;
    fprintf(stderr,"Commentaire non fermé.\n");
  }

  /* Test si le programme se finit par une chaîne de caractères non fermée : l'execution de la commande ne se finit pas par un echec dans ce cas */
  if((etat == CHAINE_CARACTERE)||(etat == DANS_CHAINE)){
    fprintf(stderr,"Chaîne de caractères non fermée.\n");
  }

  /* Test si le programme se finit par un caractère non fermé : l'execution de la commande ne se finit pas par un echec dans ce cas */
  if((etat == CARACTERE)||(etat == DANS_CARACTERE)){
    fprintf(stderr,"Caractère non fermé.\n");
  }

  /* Fin de l'execution de la fonction pp */
  if(valide){
    exit(EXIT_SUCCESS);
  }
  else{
    exit(EXIT_FAILURE);
  }
}
