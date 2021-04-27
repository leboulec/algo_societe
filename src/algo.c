#include "algo.h"
#include <stdlib.h>
#include <string.h>

matrice_adj_t *algo_bon_sens(matrice_adj_t *mat_in)
{
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
		if (connexion_max > 0)
			retire_sommet(mat, ind_sommet_con_max);
	} while (connexion_max > 0);
	return mat;
}

// Tableau de sommet 
int* algo_force_brute(matrice_adj_t *mat_in)
{
	int* noeud = NULL, liste = NULL;
	int connexion_sommet = -1 ;

	matrice_adj_t **mats = malloc((*mat)*mat_in->taille_m); 

	if(mat_in->taille_m > 1){
		for(size_t i = 0 ; i < mat_in->taille_m ; i++){			
			mats[i] = build_matrice(mat_in->taille_m, mat_in->taille_n);
			memcpy(mats[i]->contenu[i], mat_in->contenu[i], sizeof(int) * (mat_in->taille_m));	
			retire_sommet(mats[i],i);
		}

		for(size_t i = 0 ; i < mat_in->taille_m-1 ; i++){
			for(size_t j = 0 ; j < mat_in->taille_m-1 ; j++){
				connexion_sommet = 	nbre_connexions(mats[i]->contenu[j],mats[i]->taille_m);	
				if(connexion_sommet == 0){
					noeud = malloc(sizeof(int));
					if (noeud == NULL) {
						printf("Impossible de créer un noeud... Problème de mémoire ?");
						return NULL;
					}
					*noeud = i;
					//TOUT FREE
					for(size_t i = 0 ; i < mat_in->taille_m-1 ; i++){
						delete_matrice(mats[i]);
						free(mats);
					}
					return noeud;
				}
				else{
					// append liste précédente avec liste courante
					liste = (int**) malloc(sizeof(int*)*2);
					*(*liste) = i;
					*(*(liste+1)) = algo_force_brute(mats[i],mats[i]->taile_m-1);
					return liste;
				}
			}
		}
	}
	else{ 
		return NULL;
	}
}


int nbre_connexions(int *connexion, size_t nbre_sommets)
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