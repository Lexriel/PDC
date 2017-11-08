# include <unistd.h>
# include "monmalloc_infra.h"

extern liste_t freelist;
extern void *monmalloc(unsigned int);
extern void construirecellule(liste_t, unsigned int);

void etendrememoire(){
/* cette fonction demande un nouveau segment de m\'emoire, le
   transforme en une cellule qui sera ins\'er\'ee dans la liste des
   cellules libres */
  static unsigned int pos;
  unsigned int shmid;
  construirecellule((liste_t) sbrk(BUFFERSIZE), BUFFERSIZE);
  return;
}
