#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ville.h"

static void init_camion (struct camion* truck)
{
    truck->num = 0;
    truck->velos = MAX_VELOS / 2;
}

void init_ville (struct ville* city, fonction_de_priorite_station* f, long seed)
{   int i;

    srand48 (seed);
    city->time = 0;
    init_file_priorite_station (&city->file, f);
    for (i = 0; i < NB_STATIONS; i++)
    {   init_station (&city->tab [i], i);
        enfiler_priorite_station (&city->file, &city->tab [i]);
    }
    init_camion (&city->truck);
}

void equilibre_camion_et_station (struct camion* C, struct station* S)
{   int m, n;

    m = (C->velos + S->velos) / 2;
    n = m - C->velos;
    C->velos += n;
    S->velos -= n;
}

void deplace_camion (struct ville* city, struct station* dest)
{   double dist, trend, delta, sigma, r1, r2;
    int i;

    dist = distance (&city->tab [city->truck.num], dest) + 1;
/*
   Si on tire un grand nombre de points dans le carré [0,1]x[0,1], la
   distance moyenne est approximativement 0.521405433
 */
    sigma = 2. * dist / (MAX_COORDINATES * 0.521405433);
    for (i = 0; i < NB_STATIONS; i++)
    {   struct station* s = &city->tab [i];
        trend = cos ((double)city->time*2.*M_PI/s->frequence);
        r1 = drand48 ();
        r2 = drand48 ();
/*
   Le nombre de vélos ajoutés ou retirés augmente avec la distance parcourue
   et donc le temps passé à changer de station.
 */
        delta = sigma*sqrt(-2.*log(r1))*cos(2.*M_PI*r2);
        ajouter_ou_retirer_velos (s, (int)(trend + delta));
        changement_priorite_station (s->indice, &city->file);
    }
    city->time += dist;

    dest->derniere_visite = city->time;
    city->truck.num = dest->num;
    changement_priorite_station (dest->indice, &city->file);
}

void enquete (struct ville* city, int* grrr)
{   int i;

    *grrr = 0;
    for (i = 0; i < NB_STATIONS; i++)
        *grrr += city->tab [i].insatisfaction;
}

