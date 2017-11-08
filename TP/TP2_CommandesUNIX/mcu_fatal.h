/* Termine l'execution du programme sur une erreur fatale. Si assert
   est faux, affiche le message sur la sortie d'erreur et termine en
   retournant la valeur status a l'environnement. */
extern void fatal(int assert, const char message[], int status);
