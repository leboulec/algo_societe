/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */
#ifndef __TEST_HH__
#define __TEST_HH__

#include "listeSommet.h"
#include "matrice.h"

typedef listeSommet* algo(matrice_adj_t* mat);
double tstAlgo(algo* alg,matrice_adj_t *toTest);


#endif