#include <stdlib.h>
#include <string.h>
#include  "algo.h"
#include  "matrice.h"
#include  "societe.h"

int main()
{

	matrice_adj_t *mat = build_matrice(3, 3),
	*cpy = NULL;
	gpe_t* gpes ;
	size_t nbGpe ;

	gpes = getGpeFrom("tst/societe1.txt",&nbGpe);
	
	cpy = getMatrixFrom(nbGpe,gpes );
	
	print_matrice(cpy);
	/* TEST 1*/
	printf("===TEST 1===\n");
	
	/*
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
	*/
	listeSommet *liste = algo_force_brute(mat);
	
	if (liste == NULL) {
		delete_matrice(mat);
		return -1;
	}

	printf("Sommets à retirer : ");
	displayList(liste);


	delete_matrice(mat);
	deleteList(liste);
	
	/* TEST 2*/
	printf("\n===TEST 2===\n");
	mat = build_random_matrice_adj(10);
	if (mat == NULL)
		return -1;
	print_matrice(cpy);
	liste = algo_bon_sens(cpy);
	if (liste == NULL) {
		delete_matrice(mat);
		return -1;
	}
	displayList(liste);
	printf("\n");
	/*

	createFileFromMatrice(mat,"test.mat");

	cpy = getMatriceFrom("test.mat");
	print_matrice(cpy);

	printf("*****************\n");
	printf("Sommets à retirer : ");
	displayList(liste);
	printf("\n");
	delete_matrice(mat);
	deleteList(liste);
*/	

	delete_matrice(cpy);

	return 0;
}