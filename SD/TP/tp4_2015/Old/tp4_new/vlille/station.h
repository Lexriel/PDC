#if ! defined (STATION_H)
#define STATION_H 1

#include <stdbool.h>

#define MAX_VELOS 20
#define MAX_COORDINATES 100
#define PAS_DE_VISITE -1
#define MIN_FREQUENCE 10
#define MAX_FREQUENCE 100
struct station {
    int num;
    int x, y;
    int velos;
    double derniere_visite;
    int insatisfaction;
    double frequence;
    int indice;         /* ce champ est utilisé par les files de priorité */
};

extern void init_station (struct station*, int);
extern void ajouter_ou_retirer_velos (struct station*, int);
extern double distance (struct station*, struct station*);
#endif
