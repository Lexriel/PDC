

   int global = 1;                /* d\'efinition d'un variable 
				    globale (externe)                    */
   extern int extern_global ;    /* d\'eclaration d'une variable globale 
				    d'un autre fichier (externe)         */

   static int global_privee = 2 ; /* globale au fichier, invisible depuis
                                     d'autres fichiers (statique)        */

  int fonction(int param) {       /* param\`etre (automatique)           */
    int local = 3 ;               /* variable locale (automatique)       */
    static int local_static = 4 ; /* variable locale statique (static) 
                                     valeur inchang\'ee entre 2 appels   */
    register int i = 5 ;          /* variable locale registre (register) */
    return i++ ;
  }


