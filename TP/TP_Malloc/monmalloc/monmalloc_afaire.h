# define USS(a) (((char *)((a)->userspacestop)) - ((char *)((a)->userspacestart))) 

void inserer(liste_t *, liste_t);
liste_t extraire(liste_t *, unsigned int);
