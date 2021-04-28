#include "../include/algo.h"
#include "../include/matrice.h"

int main()
{
	int matsize = 7 ;
	matrice_adj_t *mat = build_matrice(matsize,matsize);

	if (mat == NULL)
		return -1;
	for (int i = 0; i < matsize; i++)
		for(int j = 0; j < matsize; j++)
			if (i != j)
				mat->contenu[i][j] = 1;

	mat->contenu[5][1] = 0;
	mat->contenu[1][5] = 0;
	/*mat->contenu[3][1] = 0;
	mat->contenu[1][3] = 0;
	mat->contenu[4][2] = 0;
	mat->contenu[2][4] = 0;
	mat->contenu[4][6] = 0;
	mat->contenu[6][4] = 0;
	mat->contenu[5][6] = 0;
	mat->contenu[6][5] = 0;*/
	
	print_matrice(mat);
	printf("*****************\n");
    listeSommet* n = algo_force_brute(mat);
	displayList(n);

	for(int i = 0 ; i < n->taille;i++){
		retire_sommet(mat,n->contenu[i]);
	}
	printf("\n");
	print_matrice(mat);
	delete_matrice(mat);
	//deleteList(n);
	return 0;
}