#include "liste_double.h"

int main ()
{   struct liste_double A, B;

    init_liste_double (&A);
    init_liste_double (&B);

    ajouter_en_tete_liste_double (&A, 3.14);
    ajouter_en_tete_liste_double (&A, 2.718);
/*
    set_liste_double (&B, &A);
 */
    B = A;
    imprimer_liste_double (&B);

    clear_liste_double (&A);
    clear_liste_double (&B);
    return 0;
}
