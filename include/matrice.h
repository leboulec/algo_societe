#ifndef __MATRICE_H__
#define __MATRICE_H__

#include <stdio.h>

/* Type matrice
 * taille_m : nombre de colonne
 * taille_n : nombre de ligne
 * contenu[i][j] : i ligne j colonne
 */
typedef struct {
	size_t taille_m;
	size_t taille_n;
	int **contenu;
} matrice_t;

// Matrice d'incidence
typedef matrice_t matrice_inc_t;
// Matrice d'adjacence
typedef matrice_t matrice_adj_t;

/* Build a matrice
 * int m	 <-- nombre de colonnes
 * int n	 <-- nombre de lignes
 * Retourne la matrice construite
 */
matrice_t *build_matrice(size_t m, size_t n);


/* Cree une copie d'une matrice
 * matrice_adj_t*	--> matrice à copier
 * Retourne une copie de la matrice
 */
matrice_adj_t * copy_matrice(matrice_adj_t* matrice);

/* Build a random matrice d'adjacence symetrique
 * int n	--> taille de la matrice carre
 * Retourne la matrice construite
 */
matrice_adj_t *build_random_matrice_adj(size_t n);

/*
 * Delete the matrice mat
 */
void delete_matrice(matrice_t *mat);

/*
 * Print the matrice mat
 */
void print_matrice(matrice_t *mat);

/* Build a matrice d'incidence
 * int *list_inc[2]	<-- liste d'incidence
 * size_t n_list	<-- taille de la liste d'incidence
 * n_vertex		<-- nombre de sommets
matrice_inc_t *build_matrice_inc(int *liste_inc[2], size_t n_list, size_t n_vertex);
 */

#endif