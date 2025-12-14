#include "../../libraries.h"
#include <stdio.h>

int fils_gauche(int i, int n){
    if (0 <= i && 2*i + 1 < n){
        return 2 * i + 1;
    }
    else{
        return -1;
    }
}

int fils_droit(int i, int n){
    if (0 <= i && 2*i + 2 < n){
        return 2 * i + 2;
    }
    else{
        return -1;
    }
}

int pere(int i, int n){
    if (0 < i && i < n){
        return (i-1)/2;
    }
    else{
        return -1;
    }
}

struct tas_s {
    int* elements; // tableau représentant le tas
    int nb_elements; // nombre actuel de nœuds dans le tas
    int capacite_maximale; // nombre maximal de nœuds que peut contenir le tas
    bool est_tas_min; // true s'il s'agit d'un tas-min, false s'il s'agit d'un tas-max
};
typedef struct tas_s tas;

tas* tas_vide(int capacite, bool est_min){
    tas* res = malloc(sizeof(tas));
    assert(res != NULL);

    res->nb_elements = 0;
    res->elements = malloc(capacite*sizeof(int));
    assert(res->elements != NULL);
    res->capacite_maximale = capacite;
    res->est_tas_min = est_min;
    return res;
}

void tas_detruit(tas* t){
    if(t != NULL){
        free(t->elements);
        free(t);
    }
}

void tas_initialise(tas* t, int n, int tableau[n]) {
    // préconditions : le tas est vide, et de capacité suffisante
    for (int i = 0; i < n; i += 1) {
        t->elements[i] = tableau[i];
    }
    t->nb_elements = n;
}

int tas_lecture_minimum_ou_maximum(tas t){
    assert(t.nb_elements != 0);
    return t.elements[0];
}

void percolation_haut_min(tas* t , int i){
    int i_pere = pere(i, t->nb_elements);
    if (t->elements[i_pere] > t->elements[i]){
        int tmp = t->elements[i];
        t->elements[i] = t->elements[i_pere];
        t->elements[i_pere] = tmp;
        percolation_haut_min(t, i_pere);
    }
}

void percolation_haut_max(tas* t , int i){
    int i_pere = pere(i, t->nb_elements);
    if (t->elements[i_pere] < t->elements[i]){
        int tmp = t->elements[i];
        t->elements[i] = t->elements[i_pere];
        t->elements[i_pere] = tmp;
        percolation_haut_max(t, i_pere);
    }
}

void percolation_haut_tas(tas* t, int i){
    assert(t!=NULL);
    if (t->est_tas_min){
        percolation_haut_min(t, i);
    }
    else{
        percolation_haut_max(t, i);
    }
}

void tas_insertion(tas* t, int etiquette_a_inserer){
    assert(t!=NULL);
    if (t->nb_elements < t->capacite_maximale){
        t->elements[t->nb_elements] = etiquette_a_inserer;
        t->nb_elements ++;
        percolation_haut_tas(t, t->nb_elements-1);
    }
}

void percolation_bas_min(tas* t, int i){
    int i_gauche = fils_gauche(i, t->nb_elements);
    int i_droit = fils_droit(i, t->nb_elements);
    if(i_droit != -1){
        int i_min = i_gauche;
        if(t->elements[i_gauche] > t->elements[i_droit]){
            i_min = i_droit;
        }
        if(t->elements[i] > t->elements[i_min]){
            int tmp = t->elements[i];
            t->elements[i] = t->elements[i_min];
            t->elements[i_min] = tmp;
            percolation_bas_min(t, i_min);
        }
    }
    else if(i_gauche != -1){
        if(t->elements[i] > t->elements[i_gauche]){
            int tmp = t->elements[i];
            t->elements[i] = t->elements[i_gauche];
            t->elements[i_gauche] = tmp;
            percolation_bas_min(t, i_gauche);
        }
    }
}

void percolation_bas_max(tas* t, int i){
    int i_gauche = fils_gauche(i, t->nb_elements);
    int i_droit = fils_droit(i, t->nb_elements);
    if(i_droit != -1){
        int i_max = i_gauche;
        if(t->elements[i_gauche] < t->elements[i_droit]){
            i_max = i_droit;
        }
        if(t->elements[i] < t->elements[i_max]){
            int tmp = t->elements[i];
            t->elements[i] = t->elements[i_max];
            t->elements[i_max] = tmp;
            percolation_bas_max(t, i_max);
        }
    }
    else if(i_gauche != -1){
        if(t->elements[i] < t->elements[i_gauche]){
            int tmp = t->elements[i];
            t->elements[i] = t->elements[i_gauche];
            t->elements[i_gauche] = tmp;
            percolation_bas_max(t, i_gauche);
        }
    }
}

void percolation_bas_tas(tas* t, int i){
    assert(t != NULL);
    if (t->est_tas_min){
        percolation_bas_min(t, i);
    }
    else{
        percolation_bas_max(t, i);
    }
}

int tas_extraction_racine(tas* t){
    assert(t!= NULL);
    int tmp = t->elements[0];
    t->elements[0] = t->elements[t->nb_elements-1];
    t->elements[t->nb_elements-1] = tmp;
    t->nb_elements --;
    percolation_bas_tas(t, 0);
    return tmp; 
}

// Fonctions du tri par tas

void percolation_haut_min_arr(int* t , int i, int len_t){
    int i_pere = pere(i, len_t);
    if (t[i_pere] > t[i]){
        int tmp = t[i];
        t[i] = t[i_pere];
        t[i_pere] = tmp;
        percolation_haut_min_arr(t, i_pere, len_t);
    }
}

void percolation_haut_max_arr(int* t , int i, int len_t){
    int i_pere = pere(i, len_t);
    if (t[i_pere] < t[i]){
        int tmp = t[i];
        t[i] = t[i_pere];
        t[i_pere] = tmp;
        percolation_haut_max_arr(t, i_pere, len_t);
    }
}

void percolation_bas_min_arr(int* t, int i, int len_t){
    int i_gauche = fils_gauche(i, len_t);
    int i_droit = fils_droit(i, len_t);
    if(i_droit != -1){
        int i_min = i_gauche;
        if(t[i_gauche] > t[i_droit]){
            i_min = i_droit;
        }
        if(t[i] > t[i_min]){
            int tmp = t[i];
            t[i] = t[i_min];
            t[i_min] = tmp;
            percolation_bas_min_arr(t, i_min, len_t);
        }
    }
    else if(i_gauche != -1){
        if(t[i] > t[i_gauche]){
            int tmp = t[i];
            t[i] = t[i_gauche];
            t[i_gauche] = tmp;
            percolation_bas_min_arr(t, i_gauche,len_t);
        }
    }
}

void percolation_bas_max_arr(int* t, int i, int len_t){
    int i_gauche = fils_gauche(i, len_t);
    int i_droit = fils_droit(i, len_t);
    if(i_droit != -1){
        int i_max = i_gauche;
        if(t[i_gauche] < t[i_droit]){
            i_max = i_droit;
        }
        if(t[i] < t[i_max]){
            int tmp = t[i];
            t[i] = t[i_max];
            t[i_max] = tmp;
            percolation_bas_max_arr(t, i_max, len_t);
        }
    }
    else if(i_gauche != -1){
        if(t[i] < t[i_gauche]){
            int tmp = t[i];
            t[i] = t[i_gauche];
            t[i_gauche] = tmp;
            percolation_bas_max_arr(t, i_gauche,len_t);
        }
    }
}

void tri_par_tas_aux(int* tableau_a_trier, int taille_tableau){
    if(taille_tableau > 0){
        int tmp = tableau_a_trier[0];
        tableau_a_trier[0] = tableau_a_trier[taille_tableau-1];
        tableau_a_trier[taille_tableau-1] = tmp;
        percolation_bas_max_arr(tableau_a_trier, 0, taille_tableau-1);
        tri_par_tas_aux(tableau_a_trier, taille_tableau-1);
    }
}

void tri_par_tas(int* tableau_a_trier, int taille_tableau){
    for(int i = 1; i < taille_tableau; i++){
        percolation_haut_max_arr(tableau_a_trier, i, taille_tableau);
    }
    tri_par_tas_aux(tableau_a_trier, taille_tableau);
}

int main() {
     int tmp[6] = {20, 13, 16, 7, 8, 1};
     tri_par_tas(tmp, 6);
     for(int i = 0; i<6; i++){
        printf("%d ", tmp[i]);
     }
     printf("\n");
     return 0;
}