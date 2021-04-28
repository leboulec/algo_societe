#include "algo.h"
#include <stdlib.h>
#include <string.h>

size_t *algo_bon_sens(matrice_adj_t *mat)
{
	size_t *liste_sommet = (size_t *)calloc(mat->taille_m, sizeof(size_t));
	if (liste_sommet == NULL) {
		printf("Impossible de créer la liste des sommets... Problème de mémoire ?");
		return NULL;
	}
	size_t ind_liste = 0;
	int connexion_sommet;
	int connexion_max = -1;
	size_t ind_sommet_con_max = -1;
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

	liste_sommet[ind_liste] = -1;
	size_t *liste_sommet_courte = realloc(liste_sommet, sizeof(size_t) * (ind_liste + 1));
	if (liste_sommet_courte == NULL)
		return liste_sommet;
	liste_sommet = liste_sommet_courte;
	return liste_sommet;
}

matrice_adj_t ** getSubMatrix(matrice_adj_t *mat_in){
	matrice_adj_t ** mats = (matrice_adj_t **) malloc(mat_in->taille_m*sizeof(matrice_adj_t)); 
	if(mats == NULL)
		return NULL;
	for(size_t i = 0 ; i < mat_in->taille_m ; i++){		
			mats[i] = build_matrice(mat_in->taille_m, mat_in->taille_n);
			for (int j = 0; j < mat_in->taille_m; j++)
				memcpy(mats[i]->contenu[j], mat_in->contenu[j], sizeof(int) * (mat_in->taille_m));	
			retire_sommet(mats[i],i);
		}
	return mats;
}
// Tableau de sommet 
listeSommet* algo_force_brute(matrice_adj_t *mat_in)
{
	listeSommet* list = NULL,*tmpList = NULL,** solutions = NULL;
	matrice_adj_t **mats = NULL;
	int nbConnexion = 0;

	if(mat_in->taille_m > 1){
		
		mats = getSubMatrix(mat_in);
		if(mats == NULL)
			return NULL;
		
		solutions = malloc(sizeof(listeSommet*)*mat_in->taille_m);
		if(solutions == NULL)
			return NULL;
			
		// Pour chaque sous matrice
		for(size_t i = 0 ; i < mat_in->taille_m ; i++){

			nbConnexion = 0;
			for(size_t j = 0 ; j < mats[i]->taille_m ; j++)
				nbConnexion += nbre_connexions(mats[i]->contenu[j],mats[i]->taille_m);

			list = createList(i);
			
			if(nbConnexion){
				tmpList = algo_force_brute(mats[i]);
				delete_matrice(mats[i]);
				catList(list,tmpList);
				solutions[i] = list;
			}else{
				for(size_t k = 0 ; k < i ; k++)
					deleteList(solutions[k]);
				for(size_t k = 0 ; k < mat_in->taille_m ; k++)
					delete_matrice(mats[k]);
				free(solutions);
				free(mats);
				return list;
			}
		}
		list = solutions[0];

		for(size_t i = 1 ; i < mat_in->taille_m ; i++){
			if(solutions[i]->taille<list->taille)
				list = solutions[i];		
			deleteList(solutions[i]);
		}
		free(solutions);
		free(mats);
	}
	return list;
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
	for (int i = 0; i < mat->taille_m; i++) {
		mat->contenu[ind_sommet][i] = 0;
		mat->contenu[i][ind_sommet] = 0;
	}
}