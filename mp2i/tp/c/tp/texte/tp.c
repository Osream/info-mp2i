#include "../../libraries.h"
#include <stdlib.h>


int** horspool(char* motif){
    int taille_motif = 0;
    for (int i = 0; motif[i] != '\0'; i++){
        taille_motif ++;
    }

    char* place_holder = malloc(taille_motif*sizeof(char));
    int nbre_character = 0;
    for (int i = 0; motif[i] != '\0'; i++){
        bool ajouter = true;
        for (int j = 0; j < nbre_character-1 && ajouter; j++){
            ajouter = ajouter && place_holder[j] != motif[i];
        }
        if (ajouter){
            place_holder[nbre_character] = motif[i];
            nbre_character ++;
        }
    }
    free(place_holder);

    int** resultat = malloc((taille_motif+2) * sizeof(int*));
    resultat[0] = malloc(sizeof(int));
    resultat[0][0] = -1;
    for (int i = 0; motif[i] != '\0'; i++){

        resultat[i+1] = malloc((nbre_character+1)*sizeof(int));
        int j = 0;
        bool entre_boucle = false;

        while(resultat[i][j] != -1){
            if(motif[resultat[i][j]] == motif[i]){
                resultat[i+1][j] = i;
                entre_boucle = true;
            }
            else{
                resultat[i+1][j] = resultat[i][j];
            }
            j++;
        }
        if (!entre_boucle && j < nbre_character){
            resultat[i+1][j] = i;
            entre_boucle = false;
            j++;
        }
        resultat[i+1][j] = -1;
    }
    resultat[taille_motif+1] = malloc(sizeof(int));
    resultat[taille_motif+1][0] = -1;
    return resultat;
}

int main(){
    char test[12] = "ABRACADABRA";
    int** a_print = horspool(test);
    for (int i = 1; a_print[i][0] != -1; i ++){
        for (int j = 0; a_print[i][j] != -1; j++){
            printf("%d ", a_print[i][j]);
        }
        printf("\n");
    }
    free(a_print[0]);
    int i = 1;
    while(a_print[i][0] != -1){
        free(a_print[i]);
        i++;
    }
    free(a_print[i]);
    free(a_print);
    return 0;
}