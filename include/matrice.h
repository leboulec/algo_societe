/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */

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

// Matrice d'adjacence
typedef matrice_t matrice_adj_t;

/* Construit une matrice
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

/* Construit une matrice d'adjacence symetrique aleatoire
 * int n	--> taille de la matrice carre
 * Retourne la matrice construite
 */
matrice_adj_t *build_random_matrice_adj(size_t n);

/* crée un fichier binaire à partir d'une matrice
 * matrice_t* la matrice à inscrire 
 * char* f	--> le chemin du fichier
 * Retourne le pointeur de fichier
 */
FILE* createFileFromMatrice(matrice_t* m,char* f);

/* Récupère une matrice à partir d'un fichier .mat
 * char* f	--> le chemin du fichier
 * Retourne la matrice construite
 */
matrice_adj_t * getMatriceFrom(char* f);

/*
 * Supprime la matrice mat
 */
void delete_matrice(matrice_t *mat);

/*
 * Affiche la matrice mat
 */
void print_matrice(matrice_t *mat);

#endif