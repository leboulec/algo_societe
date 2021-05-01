#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/listeSommet.h"

listeSommet* createList(int sommet){
	
	listeSommet* l = (listeSommet*) malloc(sizeof(listeSommet));
	
	if(l == NULL )
		return NULL;
    
	l->taille = 1;
	
	l->contenu = malloc(sizeof(int));

	if(l->contenu == NULL )
		return NULL;

	*(l->contenu) = sommet;
	
	return l;

}

void appendList(listeSommet* l, int sommet){

    l->taille++;

    l = realloc(l->contenu,sizeof(int)*(l->taille));
	
	l->contenu[l->taille-1]=sommet;
    
}

void deleteList(listeSommet* sommets){

	free(sommets->contenu);

	free(sommets);

}


void catList(listeSommet* l1,listeSommet* l2){
    
    if(l2!=NULL && l1 != NULL){
    
	    l1->contenu = realloc(l1->contenu,sizeof(int)*(l1->taille+l2->taille));
	
	    for(int i = 0 ; i < l2->taille;i++)
		    l1->contenu[i+l1->taille] =l2->contenu[i];
	
	    l1->taille += l2->taille;
        
		deleteList(l2);
    
	}   
}

void displayList(listeSommet* l){
    
	printf("\nListe de taille %ld\n",l->taille);
    
	for(int i = 0 ; i < l->taille ; i++)
        printf("%d ",l->contenu[i]);

}