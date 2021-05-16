/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */
#ifndef __LISTE_SOMMET_H__
#define __LISTE_SOMMET_H__
/* Type liste sommet
 * taille : nombre de sommet
 * contenu[i] : i ligne 
 */
typedef struct {
	size_t taille;
	size_t *contenu;
} listeSommet;

listeSommet* createList(size_t sommet);
void appendList(listeSommet* l, size_t sommet);
void deleteList(listeSommet* sommets);
void catList(listeSommet* l1,listeSommet* l2);
void displayList(listeSommet* l);

/* Post traitement de la liste des sommets retournés
 * par l'algorithme de force brute
 */
void bruteListUpdate(listeSommet* l);
#endif