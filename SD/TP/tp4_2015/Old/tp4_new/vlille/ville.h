#if ! defined (VILLE_H)
#define VILLE_H 1

#include "station.h"
#include "priorite_station.h"

struct camion {
    int num;
    int velos;
};

#define NB_STATIONS 20
struct ville {
    double time;
    struct station tab [NB_STATIONS];
    struct camion truck;
    struct file_priorite_station file;
};

extern void init_ville (struct ville*, fonction_de_priorite_station*, long);
extern void deplace_camion (struct ville*, struct station*);
extern void equilibre_camion_et_station (struct camion*, struct station*);
extern void enquete (struct ville*, int*);

#endif
