/*
CORRIGÉ PARTIEL DU TP : TRIS EFFICACES (PARTIE EN C)
Par J. BENOUWT
Licence CC BY-NC-SA
*/

/* --------------------------------------------------------- */

#include "librairies.h"
#include <limits.h> // pour INT_MAX et INT_MIN


/* --------------------------------------------------------- */


/* Tri rapide */


int partition_lomuto(int tab[], int debut, int fin) {
    int pivot = tab[fin];
    int k = debut;
    /*
    Variant : fin - i
    Inv(i, k) : les éléments d'indices debut à k-1 sont inférieurs au pivot et
                les éléments d'indices k à i sont supérieurs au pivot
    */
    for (int i = debut; i < fin; i += 1) {
        if (tab[i] < pivot) {
            int tmp = tab[i];
            tab[i] = tab[k];
            tab[k] = tmp;
            k += 1;
        }
    }
    tab[fin] = tab[k];
    tab[k] = pivot;
    return k;
}


void tri_rapide_aux(int tab[], int debut, int fin) {
    if (debut < fin) {
        int indice_pivot = partition_lomuto(tab, debut, fin);
        tri_rapide_aux(tab, debut, indice_pivot-1);
        tri_rapide_aux(tab, indice_pivot+1, fin);
    }
}


void tri_rapide(int tab[], int taille_tab) {
    tri_rapide_aux(tab, 0, taille_tab - 1);
}



/* --------------------------------------------------------- */


/* Tri rapide alternatif : partition de Hoare */


int partition_hoare(int tab[], int debut, int fin) {
    int i = debut, j = fin;
    int pivot = tab[debut];
    while (i < j) {
        while (tab[i] < pivot) {
            i += 1;
        }
        while (tab[j] > pivot) {
            j -= 1;
        }
        int tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }
    return j;
}



/* --------------------------------------------------------- */


/* Tri casier */

void min_max(int tab[], int taille_tab, int* min, int* max) {
    *min = INT_MAX;
    *max = INT_MIN;
    for (int i = 0; i < taille_tab; i += 1) {
        if (tab[i] < *min) {
            *min = tab[i];
        }
        if (tab[i] > *max) {
            *max = tab[i];
        }
    }
}


void tri_casier(int tab[], int taille_tab) {
    // On détermine le plus petit élément et le grand élément de la liste,
    // notés respectivement m et M.
    int m, M;
    min_max(tab, taille_tab, &m, &M);
    // On crée un tableau occ de taille M - m + 1 rempli initialement de zéros.
    int* occ = malloc((M - m + 1) * sizeof(int));
    for (int i = 0; i < M - m + 1; i += 1) {
        occ[i] = 0;
    }
    // On parcourt le tableau à trier afin de compléter occ de telle sorte que occ[i]
    // contienne le nombre de fois où la valeur m + i apparaît dans le tableau.
    for (int i = 0; i < taille_tab; i += 1) {
        occ[tab[i] - m] += 1;
    }
    // À l’aide de ces informations, on reconstitue la liste triée.
    int indice = 0;
    for (int i = 0; i < M - m + 1; i += 1) {
        for (int j = 0; j < occ[i]; j += 1) {
            tab[indice] = m + i;
            indice += 1;
        }
    }
    free(occ); // attention aux fuites de mémoire
}

/* Ce tri a une complexité linéaire dans le cas où M - m est une petite constante.
   Donc dans ce cas meilleur que les meilleurs tris par comparaisons qui sont quasi-linéaires.
   Sa complexité dépend cependant de M - m, et dans le cas où l'écart est grand
   la complexité temporelle et spatiale est très (trop ?) importante. 
   On ne l'utilise généralement que quand on connaît déjà les bornes
   et qu'elles sont nettement inférieures à la taille du tableau. */





