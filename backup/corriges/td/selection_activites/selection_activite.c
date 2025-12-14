/*
CORRIGÉ DU TD : SÉLECTION D'ACTIVITÉ (PARTIE EN C)
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*---------------------------------------------------------*/

struct requete_s {
    int numero;
    int debut;
    int fin;
};
typedef struct requete_s requete;

// fonction auxiliaire qui trie le tableau R entre les indices d et f
void tri_aux(requete R[], int d, int f) {
    if (d < f) {
        requete pivot = R[f];
        int futur_indice_pivot = d;
        for (int i = d; i < f; i += 1) {
            if (R[i].fin < pivot.fin) { // on trie par rapport aux temps de fin
                requete tmp = R[i];
                R[i] = R[futur_indice_pivot];
                R[futur_indice_pivot] = tmp;
                futur_indice_pivot += 1;
            }    
        }
        R[f] = R[futur_indice_pivot];
        R[futur_indice_pivot] = pivot;
        tri_aux(R, d, futur_indice_pivot-1);
        tri_aux(R, futur_indice_pivot+1, f);
    }
}

void tri(int n, requete R[n]) {
    tri_aux(R, 0, n-1);
}

bool* glouton(int n, requete R[n]) {
    tri(n, R); // tri par ordre croissant des temps de fin
    bool* res = malloc(n * sizeof(bool));
    res[R[0].numero] = true; // on sélectionne l'activité qui se termine en premier
    int indice_derniere_requete_choisie = 0;
    for (int i = 1; i < n; i += 1) {
        if (R[i].debut >= R[indice_derniere_requete_choisie].fin) { // si la requête est compatible avec celle d'avant
            res[R[i].numero] = true; // on la sélectionne
            indice_derniere_requete_choisie = i;
        }
        else {
            res[R[i].numero] = false; // sinon on ne la sélectionne pas
        }
    }
    return res;
}

int main() {
    // exemple du sujet :
    requete r0 = {0, 0, 4};
    requete r1 = {1, 5, 10};
    requete r2 = {2, 2, 6};
    requete r3 = {3, 8, 10};
    requete r4 = {4, 3, 4};
    requete r5 = {5, 5, 7};
    requete r6 = {6, 8, 12};
    requete r7 = {7, 3, 7};
    requete r8 = {8, 10, 12};
    requete R[9] = {r0, r1, r2, r3, r4, r5, r6, r7, r8};
    int n = 9;
    bool* resultat = glouton(n, R);
    int nombre_requetes_selectionnees_par_glouton = 0;
    for (int i = 0; i < n; i += 1) {
        if (resultat[i]) {
            nombre_requetes_selectionnees_par_glouton += 1;
        }
    }
    printf("Nombre de requêtes sélectionnées par le glouton : %d.\n", nombre_requetes_selectionnees_par_glouton);
    free(resultat);
}