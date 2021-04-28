#include "../include/algo.h"
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
	listeSommet* list = NULL,*tmpList = NULL;
	listeSommet** solutions;
	matrice_adj_t **mats = NULL;
	int nbConnexion ;

	if(mat_in->taille_m > 1){
		
		/*printf("\nEnter");
		printf(" size %ld\n",mat_in->taille_m  );
*/
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
				catList(list,tmpList);
				solutions[i] = list;
			}else{	
				return list;
			}
		}
		list = solutions[0];
		for(size_t i = 1 ; i < mat_in->taille_m ; i++){
			if(solutions[i]->taille<list->taille)
				list = solutions[i];		
	}
			
	}
	return list;
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