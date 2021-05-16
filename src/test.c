/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */

#include <time.h>
#include "test.h"
#include "algo.h"
double tstAlgo(algo* alg, matrice_adj_t *toTest, int verbose){
    
    clock_t time ;
    double t = 0;
    matrice_adj_t* cpy = copy_matrice(toTest);
    listeSommet* aRetirer;

    if (verbose) {
        printf("\nMatrice utilisée\n");
    
        print_matrice(cpy);
    }

    time = clock();
    
    aRetirer = alg(cpy);

    if(alg == algo_force_brute){
        bruteListUpdate(aRetirer);

    }

    displayList(aRetirer);
    
    t =((double)(clock()- time))/CLOCKS_PER_SEC;
    
    deleteList(aRetirer);
    delete_matrice(cpy);
    

    return t;
}
