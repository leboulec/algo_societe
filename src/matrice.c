/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include  "matrice.h"

matrice_t *build_matrice(size_t m, size_t n)
{
	matrice_t *mat;
	int **contenu;
	size_t i;
	int *colonne;

	mat = (matrice_t *)malloc(sizeof(matrice_t)); 
	if (mat == NULL)
		return NULL;
	contenu = (int **)malloc(n * sizeof(int *));
	if (contenu == NULL) {
		free(mat);
		return NULL;
	}

	for (i = 0; i < n; i++) {
		colonne = (int *)calloc(m ,sizeof(int));
		if (colonne == NULL) {
			if (i != 0)
				for (--i; i >= 0; i--) {
					free(contenu[i]);
				}
			free(contenu);
			free(mat);
			return NULL;
		}
		contenu[i] = colonne;
	}
	mat->taille_m = m;
	mat->taille_n = n;
	mat->contenu = contenu;
	return mat;
}

matrice_adj_t *copy_matrice(matrice_adj_t* matrice){
	matrice_t *cpy;
	int **contenu;
	size_t i;
	int *colonne;

	cpy = (matrice_t *)malloc(sizeof(matrice_t)); 
	
	if (cpy == NULL)
		return NULL;
	
	contenu = (int **)malloc(matrice->taille_m * sizeof(int *));
	
	if (contenu == NULL) {
		free(cpy);
		return NULL;
	}

	for (i = 0; i < matrice->taille_n; i++) {

		colonne = (int *)malloc(matrice->taille_m*sizeof(int));

		if (colonne == NULL) {
			if (i != 0)
				for (--i; i >= 0; i--) {
					free(contenu[i]);
				}
			free(contenu);
			free(cpy);
			return NULL;
		}
		memcpy(colonne,matrice->contenu[i],matrice->taille_m*sizeof(int));
		contenu[i] = colonne;
	}

	cpy->taille_m = matrice->taille_m;
	cpy->taille_n = matrice->taille_n;
	cpy->contenu = contenu;
	return cpy;
}

matrice_adj_t *build_random_matrice_adj(size_t n)
{
	static int srand_called = 0;
	matrice_adj_t *mat = (matrice_adj_t *)build_matrice(n, n);
	if (!srand_called) {
		srand(time(NULL));
		srand_called = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			/* We suppose RAND_MAX is big enough for the distribution to be
			uniform */
			mat->contenu[i][j] = rand() % 2;
			mat->contenu[j][i] = mat->contenu[i][j];
		}
	}
	return mat;
}

void delete_matrice(matrice_t *mat)
{
	int i;
	for (i = 0; i < mat->taille_n; i++)
		free(mat->contenu[i]);
	free(mat->contenu);
	free(mat);
}

void print_matrice(matrice_t *mat)
{
	int i, j;
	for (i = 0; i < mat->taille_n; i++) {
		for (j = 0; j < mat->taille_m; j++) {
			printf("%d ", mat->contenu[i][j]);
		}
		printf("\n");
	}
}



FILE* createFileFromMatrice(matrice_t* mat,char* f){

	FILE* fPtr = fopen(f,"wb");
	
	if(fPtr == NULL)
		return NULL;
	
	fwrite(&mat->taille_m,sizeof(size_t),1,fPtr);
	fwrite(&mat->taille_n,sizeof(size_t),1,fPtr);
	
	for(int i = 0 ; i < mat->taille_m ; i++)
		for(int j = 0 ;j < mat->taille_n;
			fwrite(&(mat->contenu[i][j]),sizeof(int),1,fPtr) ,j++);	
	
	fclose(fPtr);
	return fPtr;
}

matrice_t * getMatriceFrom(char* f){

	size_t taille_m = 0, taille_n = 0;
	matrice_t* ret = NULL;
	FILE* fPtr = fopen(f,"rb");
	
	if(fPtr == NULL)
		return NULL;

	fread(&taille_m,sizeof(size_t),1,fPtr);
	fread(&taille_n,sizeof(size_t),1,fPtr);
	
	ret = build_matrice(taille_m,taille_n);

	for(int i = 0 ; i < taille_m ; i++)
		for(int j = 0 ; j < taille_n ; j++)
			fread(&ret->contenu[i][j],sizeof(int),1,fPtr);

	fclose(fPtr);
	return ret;
}

/* Inutile
matrice_inc_t *build_matrice_inc(int *liste_inc[2], size_t n_list, size_t n_vertex)
{
	int i;
	matrice_inc_t *mat = (matrice_inc_t *)build_matrice(n_list, n_vertex);
	if (mat == NULL)
		return NULL;
	for (i = 0; i < n_list; i++) {
		mat->contenu[i][liste_inc[i][0]];
	}
}
*/