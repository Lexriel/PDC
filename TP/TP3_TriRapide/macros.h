# ifndef _MACROS_H_
# define _MACROS_H_
# define MAXLINE 100
# define TABSIZE 1000


/* typedef enum genre genre_e; */
/* enum genre {M, F, O}; */

typedef struct Nomine_s Nomine;
struct Nomine_s{
  int date_prix;
  int domaine;
  char nom[50];
  int jour_naissance;
  int mois_naissance;
  int annee_naissance;
  char nationalite[30];
  char genre;
};

# endif
