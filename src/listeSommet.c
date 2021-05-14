/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include  "listeSommet.h"

listeSommet* createList(size_t sommet){
	
	listeSommet* l = (listeSommet*) malloc(sizeof(listeSommet));
	
	if(l == NULL )
		return NULL;
    
	l->taille = 1;
	
	l->contenu = malloc(sizeof(size_t));

	if(l->contenu == NULL )
		return NULL;

	*(l->contenu) = sommet;
	
	return l;

}

void appendList(listeSommet* l, size_t sommet){

    l->taille++;

    l = realloc(l->contenu,sizeof(size_t)*(l->taille));
	
	l->contenu[l->taille-1]=sommet;
    
}

void deleteList(listeSommet* sommets){

	free(sommets->contenu);

	free(sommets);

}


void catList(listeSommet* l1,listeSommet* l2){
    
    if(l2!=NULL && l1 != NULL){
    
	    l1->contenu = realloc(l1->contenu,sizeof(size_t)*(l1->taille+l2->taille));
	
	    for(size_t i = 0 ; i < l2->taille;i++)
		    l1->contenu[i+l1->taille] =l2->contenu[i];
	
	    l1->taille += l2->taille;
        
		deleteList(l2);
    
	}   
}

void displayList(listeSommet* l){
    
	printf("\nListe de taille %ld\n",l->taille);
    
	for(size_t i = 0 ; i < l->taille ; i++)
        printf("%ld ",l->contenu[i]);

}

void bruteListUpdate(listeSommet* l){

	if(l->taille > 1){
			
			if(l->contenu[1] >=  *l->contenu)
					l->contenu[1] += 1;

			for(size_t i = 1 ; i < l->taille ; i++ ){
				if(l->contenu[i-1] >=  l->contenu[i])
					l->contenu[i] += i;
		}
	}
}