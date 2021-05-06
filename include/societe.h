#ifndef __SOCIETE_H__
#define __SOCIETE_H__

#include <stdio.h>
#include "matrice.h"

#define STE_DELIM ":"
#define GPE_DELIM "\n"
#define BFR_SZ (1<<7)

typedef struct {
    char* nom ;
    size_t nbSte;
    char** ste;
    
} gpe_t;

/*
 * char* f : le chemin du fichier
 * size_t : le nombre de groupe
 * matrice_adj_t : la matrice d'adjacence des participations
 */
gpe_t*  getGpeFrom(char* f,size_t * nbGpe);


/* gpes : Le tableau de groupes
 * nbGpe : le nombre de groupe
 * matrice_adj_t : la matrice d'adjacence des participations
 */
matrice_adj_t* getMatrixFrom(size_t nbGpe,gpe_t* gpes);


/* gpe_t : Le tableau de groupe
 * nbGpe : Le nombre de groupe
 */
void deleteGpes(gpe_t *gpes,size_t nbGpe);
#endif