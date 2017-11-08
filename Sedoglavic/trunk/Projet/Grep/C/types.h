#define NONMARQUER 0
#define MARQUER !NONMARQUER
#define FALSE 0
#define TRUE !FALSE

typedef enum{ ALTER, CONCAT, REPET, LETTER, RANGE, ALLBUT, EMPTY, ANYLETTER }
  TYPENODE;

typedef struct node_m NODE ;

struct set_m
{
  NODE *etiquette ;
  char marque ;
  struct set_m *next ;
} ;

typedef struct set_m set_t ;

struct transitiontable_m
{
  unsigned char letter ;
  NODE * transition ;
  struct transitiontable_m * next ;
} ;

typedef struct transitiontable_m transitiontable_t ;

struct node_m 
{
  /* arbre de syntaxe abstraite */
  TYPENODE type;
  unsigned char * alphabet;
  struct node_m *left, *right; 
  /* automate d\'eterministe */
  int nul ;
  set_t *initial ;
  set_t *final ;
  set_t *nextstates;
  transitiontable_t *transitiontable ;
 } ;


