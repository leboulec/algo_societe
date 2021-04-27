#include <stdlib.h>
#include "algo.h"
#include "matrice.h"

int main()
{
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
	return 0;
}