/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include  "algo.h"
#include  "matrice.h"
#include  "societe.h"
#include  "test.h"
int main(int argc,char** argv)
{

	matrice_adj_t *mat = NULL;
	gpe_t* gpes = NULL;
	size_t nbGpe ;
	double t = 0;
	
	/* Recupère une matrice depuis un fichier formaté 
	 * représentant les groupes de société et leurs
	 * participations
	 */
	printf("===Fin du monopole===\n");

	if(argc > 1 ){
		//Création d'un matrice de taille argv[1]
		if(isdigit((int)(*(argv[1])))){
			sscanf(argv[1],"%ld",&nbGpe);
			mat = build_random_matrice_adj(nbGpe);
		}
		/*Création d'une matrice depuis le 
		 * fichier avec le nom passé en paramètre */
		else{
			gpes = getGpeFrom(argv[1],&nbGpe);
			mat = getMatrixFrom(nbGpe,gpes);
		}
	}
	// Comportement sans arguments
	else{
		gpes = getGpeFrom("tst/societe1.txt",&nbGpe);
		mat = getMatrixFrom(nbGpe,gpes);
	}

	if (mat == NULL)
		return -1;

	t = tstAlgo(algo_bon_sens,mat);
	
	printf("\nTemps d'exécution algorithme bon sens : %fs\n", t);

	t = tstAlgo(algo_force_brute,mat);

	printf("\nTemps d'exécution algorithme force brute : %fs\n", t);
		
	delete_matrice(mat);
	
	if(gpes != NULL)
		deleteGpes(gpes,nbGpe);

	return 0;
}