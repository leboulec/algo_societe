/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
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
	char c;
	int rflag = 0;
	size_t taille_matrice;
	int lflag = 1;
	int hflag = 1;
	int qflag = 0;
	
	/* Recupère une matrice depuis un fichier formaté 
	 * représentant les groupes de société et leurs
	 * participations
	 */
	printf("===Fin du monopole===\n");

	if(argc > 1 ) {
		while((c = getopt(argc, argv, "r:lhq")) != -1) {
			switch (c) {
			case 'r':
				rflag = 1;
				taille_matrice = atoll(optarg);
				break;
			case 'l':
				lflag = 1;
				hflag = 0;
				break;
			case 'h':
				lflag = 0;
				hflag = 1;
				break;
			case 'q':
				qflag = 1;
				break;
			case '?':
				if (optopt == 'r') {
					printf("Veuillez indiquer une taille\n");
					return -1;
				} else {
					printf("Option non reconnue\n");
				}
				break;
			}
		}
		if (rflag) {
			if (taille_matrice < 1) {
				printf("Veuillez indiquer une taille valide\n");
				return -1;
			}
			mat = build_random_matrice_adj(taille_matrice);
		} else {
			if (optind >= argc) {
				printf("Veuillez indiquer un nom de fichier\n");
				return -1;
			}
			gpes = getGpeFrom(argv[optind], &nbGpe);
			mat = getMatrixFrom(nbGpe, gpes);
		}
	// Comportement sans arguments
	} else {
		printf("Usage :\nmonopole fichier\tpour executer les algorithmes sur une matrice d'un fichier\n");
		printf("monopole -r n\t\tpour executer les algorithmes sur une matrice aleatoire de taille n\n");
		printf("\nOptions :\n");
		printf("-r n\t\tExecute l'algorithme sur une matrice aleatoire de taille n\n");
		printf("-l \t\tExecute seulement l'algorithme bon sens\n");
		printf("-h \t\tExecute seulement l'algorithme force brute\n");
		printf("-q \t\tN'affiche pas la matrice utilisee\n");
	}

	if (mat == NULL)
		return -1;

	if (lflag) {
		t = tstAlgo(algo_bon_sens, mat, !qflag);
		printf("\nTemps d'exécution algorithme bon sens : %fs\n", t);
	}

	if (hflag) {
		t = tstAlgo(algo_force_brute, mat, !qflag);
		printf("\nTemps d'exécution algorithme force brute : %fs\n", t);
	}
	delete_matrice(mat);
	
	if(gpes != NULL)
		deleteGpes(gpes,nbGpe);

	return 0;
}