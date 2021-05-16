/* LEBOULENGER - LEFEBVRE
 * Projet Algorithmie avancée
 * Sujet : Fin du monopole
 */
#include  "societe.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * char* f : le chemin du fichier
 * matrice_adj_t : la matrice d'adjacence des participations
 */

matrice_adj_t* build_ste_matrice(gpe_t* gpes,size_t nbGpe){

	matrice_adj_t* mat = build_matrice(nbGpe,nbGpe);



	return mat;
}
void deleteGpe(gpe_t *toFree){

	for(int i = 0 ; i < toFree->nbSte; i++)
		free(toFree->ste[i]);

	free(toFree->ste);
	free(toFree->nom);
}
void deleteGpes(gpe_t *gpes,size_t nbGpe){
	for(int i = 0 ; i < nbGpe  ; i++)
		deleteGpe(gpes+i);

	free(gpes);
}
 matrice_adj_t* getMatrixFrom(size_t nbGpe,gpe_t* gpes){
	
	gpe_t curGpe ;
	char* curSte;
	matrice_adj_t* mat = build_ste_matrice(gpes,nbGpe);

	for(size_t gpe = 0 ; gpe < nbGpe ;gpe++){

		curGpe = gpes[gpe];
		for(size_t soc = 0 ; soc < curGpe.nbSte ;soc++){
			curSte = curGpe.ste[soc];
			for(size_t gpeCmp= 0 ; gpeCmp < nbGpe ; gpeCmp ++){
				
				if(gpe!=gpeCmp ){
					for(size_t steCmp = 0 ; steCmp < gpes[gpeCmp].nbSte ; steCmp ++){
						if(strcmp(curSte,gpes[gpeCmp].ste[steCmp] )==0 ){
							mat->contenu[gpe][gpeCmp] = 1;
							mat->contenu[gpeCmp][gpe] =1;
						}
					}
				}
			}
		}
	}

	return mat ;
}

gpe_t* getGpeFrom(char* f,size_t* nbGpe){

	char //File read buffer 
		bfr[BFR_SZ] ={0},
		//strotk_r related variables
		*saveBfr =bfr , *tok = NULL,steBfr[BFR_SZ]={0},
		*saveSte = steBfr , *tmp = saveSte; 
	
	gpe_t *gpe = NULL;

	size_t len=0,nbSte = 0;
	*nbGpe = 0;

	FILE * fPtr = fopen(f,"r");

	if(fPtr == NULL){
		printf("\nLe fichier n'a pas pu être ouvert");
		return NULL;
	}
	fread(bfr,BFR_SZ*sizeof(char),1,fPtr);


	bfr[BFR_SZ-1] = 0;
	do{ 
		while (
			(tok = strtok_r(saveBfr, GPE_DELIM, &saveBfr))
			&& (len = strlen(tok) ) 
			//&& isalnum(*tok)
			){

			bzero(steBfr,BFR_SZ-1);
			strncpy(steBfr,tok,len);
			saveSte = steBfr;
			tok = strtok_r(saveSte, STE_DELIM, &tmp);
			saveSte = tmp ;

			gpe = realloc(gpe,sizeof(gpe_t)*((*nbGpe)+1));

			gpe[*nbGpe].nom = malloc(sizeof(char)*(len));
			strncpy(gpe[*nbGpe].nom,tok,len-1);

			nbSte = 0;
			gpe[*nbGpe].ste = NULL;

			while ((tok = strtok_r(saveSte, STE_DELIM, &tmp))){

				len = strlen(saveSte);

				gpe[*nbGpe].ste = realloc(gpe[*nbGpe].ste,sizeof(char*)*(nbSte+1));

				gpe[*nbGpe].ste[nbSte] = malloc(len*sizeof(char)+1);

				strncpy(gpe[(*nbGpe)].ste[nbSte],tok,len);
				gpe[(*nbGpe)].ste[nbSte][len]=0;
				saveSte = tmp ;
				nbSte++;
			}
			gpe[*nbGpe].nbSte = nbSte;
			(*nbGpe)++;
		}

		bzero(bfr,BFR_SZ);

		if(!fread(bfr,BFR_SZ*sizeof(char),1,fPtr))
			break;
		free(tok);
	}while(bfr[BFR_SZ-1] != 0 );

	fclose(fPtr);

	return gpe;
};