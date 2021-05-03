#include "../include/societe.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * char* f : le chemin du fichier
 * matrice_adj_t : la matrice d'adjacence des participations
 */

matrice_adj_t* build_ste_matrice(gpe_t* gpes,size_t nbGpe){
    matrice_adj_t* mat= build_matrice(nbGpe,nbGpe);


    
    return mat;
}
void freeGpe(gpe_t *toFree){
    
    for(int i = 0 ; i < toFree->nbSte; i++)
        free(toFree->ste[i]);
    free(toFree->ste);
    free(toFree->nom);
}

matrice_adj_t*  matAdjacenceSociete(char* f){
    
    char //File read buffer 
        bfr[BFR_SZ] ={0},
        //strotk_r related variables
        *saveBfr =bfr , *tok = NULL,steBfr[BFR_SZ]={0},*saveSte = steBfr , *tmp = saveSte; 
    
    gpe_t *gpe = NULL;
    size_t nbGpe = 0,nbSte = 0 ,len=0;
    matrice_adj_t* mat= NULL;
    
    FILE * fPtr = fopen(f,"r");
    
    if(!fread(bfr,BFR_SZ*sizeof(char),1,fPtr))
        return NULL;
    
    do{ 
        

        while ((tok = strtok_r(saveBfr, GPE_DELIM, &saveBfr)) 
            && (len = strlen(tok) ) && isalnum(*tok)){
                
            bzero(steBfr,BFR_SZ-1);
            strncpy(steBfr,tok,len);
            saveSte = steBfr;
            tok = strtok_r(saveSte, STE_DELIM, &tmp);
            saveSte = tmp ;
            
            gpe = realloc(gpe,sizeof(gpe_t)*(nbGpe+1));
            gpe[nbGpe].nom = malloc(sizeof(char)*(len));
            gpe[nbGpe].nbSte = 0;
            gpe[nbGpe].ste = NULL;
            strncpy(gpe[nbGpe].nom,tok,len-1);
            
            while ((tok = strtok_r(saveSte, STE_DELIM, &tmp))){
                len = strlen(saveSte);
                
                gpe[nbGpe].ste = realloc(gpe[nbGpe].ste,sizeof(char*)*(gpe[nbGpe].nbSte+1)); 
               
                gpe[nbGpe].ste[gpe[nbGpe].nbSte] = malloc(len*sizeof(char));
                
                strncpy(gpe[nbGpe].ste[nbSte],saveSte,len-1);
                
                saveSte = tmp ;
                malloc(((strlen(saveSte)+1)*sizeof(char)));
                gpe[nbGpe].nbSte++;
            }
            nbGpe++;
        }

        bzero(bfr,BFR_SZ);

        if(!fread(bfr,BFR_SZ*sizeof(char),1,fPtr))
           break;
        free(tok);
    }while(bfr[BFR_SZ-1] != 0 );


    
    
    printf("NbGpe = %ld \t sizeof gpe\n",nbGpe);      
    // Struct
    mat = build_ste_matrice(gpe,nbGpe);
    
    for(int i = 0 ; i < nbGpe;freeGpe(gpe+i),++i);

    free(gpe);

    return mat;
};