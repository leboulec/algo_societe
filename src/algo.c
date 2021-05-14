/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */
#include  "algo.h"
#include <stdlib.h>
#include <string.h>

listeSommet *algo_bon_sens(matrice_adj_t *mat)
{
	size_t *liste_sommet = (size_t *)calloc(mat->taille_m, sizeof(size_t));
	if (liste_sommet == NULL) {
		printf("Impossible de creer la liste des sommets... Problème de memoire ?");
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

	size_t *liste_sommet_courte = realloc(liste_sommet, sizeof(size_t) * (ind_liste));
	if (liste_sommet_courte == NULL)
		return NULL;
	liste_sommet = liste_sommet_courte;
	listeSommet *liste = (listeSommet *)malloc(sizeof(listeSommet));
	liste->contenu = liste_sommet;
	liste->taille = ind_liste;
	return liste;
}

matrice_adj_t ** getSubMatrix(matrice_adj_t *mat_in){
	matrice_adj_t ** mats = (matrice_adj_t **) malloc(mat_in->taille_m*sizeof(matrice_adj_t)); 
	if(mats == NULL)
		return NULL;
	for(size_t i = 0 ; i < mat_in->taille_m ; i++){		
			mats[i] = build_matrice(mat_in->taille_m, mat_in->taille_n);
			for (int j = 0; j < mat_in->taille_m; j++)
				memcpy(mats[i]->contenu[j], mat_in->contenu[j], sizeof(int) * (mat_in->taille_m));	
			detruit_sommet(mats[i],i);
		}
	return mats;
}

listeSommet* algo_force_brute(matrice_adj_t *mat_in)
{
	listeSommet* list = NULL,*tmpList = NULL,** solutions = NULL;
	
	matrice_adj_t **mats = NULL;

	size_t nbConnexion = 0;

	if(mat_in->taille_m > 2){
		
		mats = getSubMatrix(mat_in);
		
		if(mats == NULL)
			return NULL;
		
		solutions = malloc(sizeof(listeSommet*)*mat_in->taille_m);
		
		if(solutions == NULL)
			return NULL;
			
		// Pour chaque sous matrice
		for(size_t i = 0 ; i < mat_in->taille_n; nbConnexion = 0,i++){
			
			list = createList(i);
			
			for(size_t j = 0 ; j < mats[i]->taille_m ; 
				nbConnexion += (size_t) nbre_connexions(mats[i]->contenu[j],mats[i]->taille_m),j++);
				
			if(nbConnexion){
		
				tmpList = algo_force_brute(mats[i]);	

				// L'indice est relatif à la matrice considérée
				// il faut donc l'incrémenter

				catList(list,tmpList);

				delete_matrice(mats[i]);
		
				solutions[i] = list;
		
			}else{

				for(size_t k = 0 ; k < i ; k++)
					deleteList(solutions[k]);
					
				for(size_t j = i ; j < mat_in->taille_m ; j++)
						delete_matrice(mats[j]);
					
				free(solutions);
		
				free(mats);
		
				return list;
			}
		}

		list = solutions[0];
		
		for(size_t i = 1 ; i < mat_in->taille_m ; i++){
			
			if(solutions[i]->taille < list->taille 
				&& (solutions[i]->contenu) != NULL){
			
					deleteList(list);
			
					list = solutions[i];
			
				}		
			else		
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

void detruit_sommet(matrice_adj_t *mat, size_t ind_sommet)
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
