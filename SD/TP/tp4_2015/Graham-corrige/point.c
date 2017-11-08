#include "point.h"

void init_point (struct point* P, double x, double y, char c)
{
    P->x = x;
    P->y = y;
    P->ident = c;
}

/* 
 * Voir question 3
 */

int compare_points (const void* A0, const void* B0)
{   struct point* A = (struct point*)A0;
    struct point* B = (struct point*)B0;
    double det = A->x * B->y - A->y * B->x;
    if (det > 0)
        return -1;
    else if (det == 0)
        return 0;
    else
        return 1;
}

/*
 * Retourne true si le chemin A, B, C tourne à gauche en B
 */

bool tourne_a_gauche (struct point* A, struct point* B, struct point* C)
{   double det = 
        (B->x - A->x) * (C->y - A->y) - (B->y - A->y) * (C->x - A->x);
    return det > 0;
}

