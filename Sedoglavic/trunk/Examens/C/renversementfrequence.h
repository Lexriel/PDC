#define MaxPile 255

struct cellulecode_s
{
  char caractere ;
  struct cellulecode_s *next ;
} ;

struct cellule_s
{
  char caractere ;
  float frequence ;
  struct cellulecode_s *listecirculaire ;
  struct cellule_s *next ;
} ;


struct pile_s
{
  unsigned int sommet ;
  char tab[MaxPile] ;
} ;
