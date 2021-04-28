#include <stdlib.h>
#include <stdio.h>
#include "../include/matrice.h"

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