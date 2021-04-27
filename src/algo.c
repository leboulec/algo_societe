#include "algo.h"
#include <stdlib.h>
#include <string.h>

size_t *algo_bon_sens(const matrice_adj_t *mat_in)
{
	size_t *liste_sommet = (size_t *)calloc(mat_in->taille_m, sizeof(size_t));
	if (liste_sommet == NULL) {
		printf("Impossible de créer la liste des sommets... Problème de mémoire ?");
		return NULL;
	}
	size_t ind_liste = 0;
	int connexion_sommet;
	int connexion_max = -1;
	size_t ind_sommet_con_max = -1;
	matrice_adj_t *mat = build_matrice(mat_in->taille_m, mat_in->taille_n);
	if (mat == NULL) {
		printf("Impossible de créer la matrice... Problème de mémoire ?");
		return NULL;
	}
	for (int i = 0; i < mat_in->taille_n; i++)
		memcpy(mat->contenu[i], mat_in->contenu[i], sizeof(int) * (mat_in->taille_m));

	do {
		connexion_sommet = 0;
		connexion_max = -1;
		ind_sommet_con_max = -1;
		for (int i = 0; i < mat->taille_m; i++) {
			connexion_sommet = nbre_connexions(mat->contenu[i],
							    mat->taille_m);
			if (connexion_sommet > connexion_max) {
				connexion_max = connexion_sommet;
				ind_sommet_con_max = i;
			}
		}
		if (connexion_max > 0) {
			retire_sommet(mat, ind_sommet_con_max);
			liste_sommet[ind_liste] = ind_sommet_con_max;
			ind_liste++;
		}
	} while (connexion_max > 0);
	delete_matrice(mat);

	size_t *liste_sommet_courte = realloc(liste_sommet, sizeof(size_t) * (ind_liste + 1));
	if (liste_sommet_courte == NULL)
		return liste_sommet;
	liste_sommet = liste_sommet_courte;
	liste_sommet[ind_liste] = -1;
	return liste_sommet;
}

int nbre_connexions(const int *connexion, size_t nbre_sommets)
{
	int n = 0;
	for (int i = 0; i < nbre_sommets; i++)
		if (connexion[i] == 1)
			n++;
	return n;
}

void retire_sommet(matrice_adj_t *mat, size_t ind_sommet)
{
	int i;
	for (i = 0; i < mat->taille_n; i++) {
		memmove(
		    mat->contenu[i] + ind_sommet, mat->contenu[i] + ind_sommet + 1,
     				   sizeof(int) * (mat->taille_m - ind_sommet - 1));
	}
	free(mat->contenu[ind_sommet]);
	for (i = ind_sommet; i < mat->taille_n - 1; i++) {
		mat->contenu[i] = mat->contenu[i+1];
	}
	mat->taille_m -= 1;
	mat->taille_n -= 1;
}