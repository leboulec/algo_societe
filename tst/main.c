#include "../algo.h"
#include "../matrice.h"
#define SZ_MATRIX 5
int main()
{
	matrice_adj_t *mat = build_matrice(SZ_MATRIX,SZ_MATRIX);
	
	if (mat == NULL)
		return -1;
	for (int i = 0; i < SZ_MATRIX; i++)
		for(int j = 0; j < SZ_MATRIX; j++)
			if (i != j)
				mat->contenu[i][j] = 1;

	mat->contenu[0][1] = 0;
	mat->contenu[1][0] = 0;
	print_matrice(mat);
	printf("*****************\n");

    listeSommet* n = algo_force_brute(mat);
	delete_matrice(mat);
	deleteList(n);
	return 0;
}
