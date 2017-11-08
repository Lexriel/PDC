#include <stdlib.h>
#include <math.h>
#include "station.h"

void init_station (struct station* s, int num)
{
    s->num = num;
    s->x = (int)(MAX_COORDINATES * drand48 ());
    s->y = (int)(MAX_COORDINATES * drand48 ());
    s->velos = MAX_VELOS / 2;
    s->derniere_visite = PAS_DE_VISITE;
    s->insatisfaction = 0;
    s->frequence = MIN_FREQUENCE + (MAX_FREQUENCE - MIN_FREQUENCE)*drand48 ();
}

void ajouter_ou_retirer_velos (struct station* s, int n)
{
    s->velos += n;
    if (s->velos < 0)
    {   s->insatisfaction -= s->velos;
        s->velos = 0;
    } else if (s->velos > MAX_VELOS)
    {   s->insatisfaction += s->velos - MAX_VELOS;
        s->velos = MAX_VELOS;
    }
}

double distance (struct station* a, struct station* b)
{
    return sqrt (pow (a->x - b->x, 2) + pow (a->y - b->y, 2));
}

