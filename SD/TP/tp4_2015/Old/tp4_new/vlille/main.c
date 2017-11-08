#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ville.h"

struct station* station_courante;

#define TMAX (1000 * MAX_COORDINATES * 0.521405433)
#define SCENARIO 65467868

static bool chacun_son_tour (struct station* A, struct station* B)
{
    à écrire !
}

int main ()
{   struct ville city;
    int grrr;

    station_courante = &city.tab [0];
    init_ville (&city, &chacun_son_tour, SCENARIO);
    while (city.time < TMAX)
    {   station_courante = defiler_priorite_station (&city.file); 
        deplace_camion (&city, station_courante);
        equilibre_camion_et_station (&city.truck, station_courante);
        enfiler_priorite_station (&city.file, station_courante);
        enquete (&city, &grrr);
        printf ("%f %d\n", city.time, grrr);
    }
    return 0;
}

