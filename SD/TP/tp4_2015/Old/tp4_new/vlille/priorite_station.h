#if ! defined (PRIORITE_STATION_H)
#define PRIORITE_STATION_H 1

#include <stdbool.h>
#include "station.h"

/* 
 * Type « file de priorité » d'une capacité max. SIZE_FILE_PRIORITE_STATION
 * La file contient des adresses d'objets de type « struct station »
 */

#define SIZE_FILE_PRIORITE_STATION 1000

/* 
 * Le type « file de priorité » est paramétré par une fonction qui permet
 * de décider si un élément est plus prioritaire qu'un autre.
 * Cette fonction est du type suivant :
 */

typedef bool fonction_de_priorite_station (
    struct station*,
    struct station*);

/* 
 * Le tableau qui implante la file. Il est structuré en tas.
 */

struct file_priorite_station {
    int n;                   /* le nombre d'éléments effectivement présents */
    struct station* tab[SIZE_FILE_PRIORITE_STATION];
    fonction_de_priorite_station* est_prioritaire;
};

extern void init_file_priorite_station (
    struct file_priorite_station*,
    fonction_de_priorite_station*);

extern void clear_file_priorite_station (struct file_priorite_station*);

extern void enfiler_priorite_station (
    struct file_priorite_station*,
    struct station*);

extern struct station* defiler_priorite_station (struct file_priorite_station*);

extern void changement_priorite_station (
    int,
    struct file_priorite_station*);

#endif
