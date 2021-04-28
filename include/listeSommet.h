#ifndef __LISTE_SOMMET_H__
#define __LISTE_SOMMET_H__
/* Type liste sommet
 * taille : nombre de sommet
 * contenu[i] : i ligne 
 */
typedef struct {
	size_t taille;
	int *contenu;
} listeSommet;
listeSommet* createList(int sommet);
void appendList(listeSommet* l, int sommet);
void deleteList(listeSommet* sommets);
void catList(listeSommet* l1,listeSommet* l2);
void displayList(listeSommet* l);
#endif