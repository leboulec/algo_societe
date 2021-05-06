#ifndef __ALGO_H__
#define __ALGO_H__

#include "matrice.h"
#include "listeSommet.h"
/* Construit une matrice totalement deconnexe a partir d'une matrice d'adjacence
 * mat_in <-- Matrice d'adjacence representant les interdependances des groupes
 *            de societes. A la fin de l'algorithme, la matrice ne contient que
 *            des 0.
 * Renvoie une liste des noeuds a enlever pour obtenir une matrice totalement
 * deconnexe
 */
listeSommet *algo_bon_sens(matrice_adj_t *mat_in);

/* Calcul le nombre de sommets connectes au sommet courant
 * connexion <-- colonne de la matrice d'adjacence
 * nbre_sommet <- taille de la colonne de la matrice d'adjacence (=nombre de
 *                groupes de societes)
 * Renvoie le nombre de sommets connectes au sommet courant
 */
int nbre_connexions(const int *connexion, size_t nbre_sommets);

/* Retire un sommet à une matrice
 * mat <-- matrice dont un sommet doit etre retire
 * mat --> matrice avec un sommet retire
 * ind_sommet <-- indice du sommet a retirer
 */
void retire_sommet(matrice_adj_t *mat, size_t ind_sommet);


/* Retire un sommet à une matrice et la redimensionne
 * mat <-- matrice dont un sommet doit etre retire
 * mat --> matrice avec un sommet retire
 * ind_sommet <-- indice du sommet a retirer
 */
void detruit_sommet(matrice_adj_t *mat, size_t ind_sommet);


/* Retire un sommet à une matrice et la redimensionne
 * mat <-- matrice dont un sommet doit etre retire
 * mat --> matrice avec un sommet retire
 * ind_sommet <-- indice du sommet a retirer
 */
listeSommet* algo_force_brute(matrice_adj_t *mat_in);
#endif
