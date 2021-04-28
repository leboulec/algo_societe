#include <stdlib.h>
#include "algo.h"
#include "matrice.h"

int main()
{
	/* TEST 1*/
	printf("===TEST 1===\n");
	matrice_adj_t *mat = build_matrice(3, 3);
	if (mat == NULL)
		return -1;
	for (int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if (i != j)
				mat->contenu[i][j] = 1;
	mat->contenu[0][1] = 0;
	mat->contenu[1][0] = 0;
	print_matrice(mat);
	printf("*****************\n");
	size_t *liste = algo_bon_sens(mat);
	if (liste == NULL) {
		delete_matrice(mat);
		return -1;
	}
	size_t *sommet = liste;
	printf("Sommets à retirer : ");
	while (*sommet != -1) {
		printf("%zd ", *sommet);
		sommet++;
	}
	printf("\n");
	delete_matrice(mat);
	free(liste);
	
	/* TEST 2*/
	printf("\n===TEST 2===\n");
	mat = build_random_matrice_adj(10);
	if (mat == NULL)
		return -1;
	print_matrice(mat);
	liste = algo_bon_sens(mat);
	if (liste == NULL) {
		delete_matrice(mat);
		return -1;
	}
	printf("*****************\n");
	printf("Sommets à retirer : ");
	sommet = liste;
	while (*sommet != -1) {
		printf("%zd ", *sommet);
		sommet++;
	}
	printf("\n");
	delete_matrice(mat);
	free(liste);
	return 0;
}