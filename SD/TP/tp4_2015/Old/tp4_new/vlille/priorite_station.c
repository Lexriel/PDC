#include <assert.h>
#include <stdio.h>
#include "priorite_station.h"

void init_file_priorite_station 
        (struct file_priorite_station* F, fonction_de_priorite_station* p)
{
    F->n = 0;
    F->est_prioritaire = p;
}

void clear_file_priorite_station (struct file_priorite_station* F)
{
}

static bool diminution_priorite_station
        (int pos, struct station* X, struct file_priorite_station* F)
{   int pere, gauche, droit, max;
    bool fini, diminution_effective;

    diminution_effective = false;
    pere = pos;
    gauche = 2*pos + 1;
    droit = gauche + 1;
/* Invariant : l'emplacement vide est au niveau du père */
    do
    {   fini = true;
        if (gauche < F->n)
        {   if (droit < F->n)
            {   if ((*F->est_prioritaire) (F->tab [gauche], F->tab [droit]))
                    max = gauche;
                else
                    max = droit;
            } else
                max = gauche;
            if ((*F->est_prioritaire) (F->tab [max], X))
            {   
/*
 * On descend l'emplacement vide au niveau du fils le plus prioritaire.
 * On remonte le fils le plus prioritaire au niveau du père
 */
                F->tab [pere] = F->tab [max];
                F->tab [pere]->indice = pere; 
                pere = max;
                gauche = 2*pere + 1;
                droit = gauche + 1;
                diminution_effective = true;
                fini = false;
            }
        }
    } while (!fini);
    F->tab [pere] =X;
    F->tab [pere]->indice = pere;
    return diminution_effective;
}

static bool augmentation_priorite_station
        (int pos, struct station* X, struct file_priorite_station* F)
{   int fils, pere;
    bool augmentation_effective;

    augmentation_effective = false;
    fils = pos;
    pere = (fils - 1) / 2;
/* Invariant : l'emplacement vide est au niveau du fils */
    while (fils > 0 && (*F->est_prioritaire) (X, F->tab [pere]))
    {   
/* On remonte l'emplacement vide au niveau du père */
        F->tab [fils] = F->tab [pere];
        F->tab [fils]->indice = fils;
        fils = pere;
        pere = (fils - 1) / 2;
        augmentation_effective = true;
    }
    F->tab [fils] = X;
    F->tab [fils]->indice = fils;
    return augmentation_effective;
}

void enfiler_priorite_station
                (struct file_priorite_station* F, struct station* X)
{
    assert (F->n < SIZE_FILE_PRIORITE_STATION);
    F->n += 1;
    augmentation_priorite_station (F->n - 1, X, F);
}

struct station* defiler_priorite_station (struct file_priorite_station* F)
{   struct station* X;

    assert (F->n > 0);
    X = F->tab [0];
    F->n -= 1;
    diminution_priorite_station (0, F->tab [F->n], F);
    return X;
}

void changement_priorite_station (int pos, struct file_priorite_station* F)
{   struct station* X;

    assert (pos >= 0 && pos < F->n);
    X = F->tab [pos];
    if (! augmentation_priorite_station (pos, X, F))
        diminution_priorite_station (pos, X, F);
}
