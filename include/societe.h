#ifndef __SOCIETE_H__
#define __SOCIETE_H__

#include <stdio.h>
#include "matrice.h"

#define STE_DELIM ":"
#define GPE_DELIM "\n"
#define BFR_SZ (1<<7)

/*
 * char* f : le chemin du fichier
 * matrice_adj_t : la matrice d'adjacence des participations
 */
matrice_adj_t* matAdjacenceSociete(char* f);

typedef struct {
    char* nom ;
    size_t nbSte;
    char** ste;
} gpe_t;


void freeGpe(gpe_t *toFree);
#endif