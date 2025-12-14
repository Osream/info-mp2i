#include "../../../c-mp2i/libraries.h"
#include <stdlib.h>

// Question 1

struct arbre_s{
    char etiquette;
    struct arbre_s* fils_gauche;
    struct arbre_s* fils_droit;
};
typedef struct arbre_s* arbre;

void parcours_prefixe(arbre ab){
    if (ab != NULL){
        printf("%c \n", ab->etiquette);
        parcours_prefixe(ab->fils_gauche);
        parcours_prefixe(ab->fils_droit);
    }
}

arbre deserialise(char* parcours, int taille_parcours){
    arbre res = malloc(sizeof(struct arbre_s));
    res->etiquette = parcours[1];
    res->fils_gauche = NULL;
    res->fils_droit = NULL;
    arbre* presque_pile = malloc(taille_parcours*sizeof(arbre));
    presque_pile[0] = res;
    int indice_pile = 0;
    for (int i = 2; i < taille_parcours; i+=2){}
            arbre suivant = malloc(sizeof(struct arbre_s));
            suivant->etiquette = parcours[i+1];
        if(!parcours[i]){    
            presque_pile[indice_pile] = suivant;
            indice_pile ++;
        }
        else{
            arbre feuille = malloc(sizeof(struct arbre_s));
            feuille->
        }
    }
    free(presque_pile);
    return res;
}




int main(){
    char parcours_pref[15] = "0L0D1G0M1A1B1T";
    const int taille_par = 14;
    return 0;
}