#include "../../libraries.h"

typedef int mat_adjacence[900]; // matrice (30,30) linéarisée

struct graphe_s {
    int nb_sommets; // nombre de sommets du graphe, toujours <= 30
    mat_adjacence mat;
};
typedef struct graphe_s graphe;

graphe mat_gno = {9,  { 0, 1, 0, 0, 1, 1, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0, 0,
    0, 1, 0, 0, 0, 1, 0, 0, 0,
    1, 0, 1, 0, 0, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 0, 0,
    0, 0, 1, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0 } };

int nb_arrêtes(graphe g){
    int somme = 0;
    for(int i = 0; i < g.nb_sommets; i++){
        for(int j = i; j < g.nb_sommets; j++){    
            somme = g.mat[g.nb_sommets*i + j];
        }
    }
    return somme;
}

bool sont_voisins(graphe g, int i, int j){
    return g.mat[g.nb_sommets*i + j];
}

bool verifie_orientation(graphe g){
    for(int i = 0; i < g.nb_sommets; i++){
        for(int j = i + 1; j < g.nb_sommets; j++){    
            if(g.mat[g.nb_sommets*j + i] != g.mat[g.nb_sommets*i + j]){
                return false;
            }
        }
    }
    return true;
}

int degre(graphe g, int i){
    int d = 0;
    for (int j = 0; j < g.nb_sommets; j++){
        d += g.mat[9*i + j];
    }
    return d;
}

int sommet_degre_max(graphe g){
    int d_max = 0;
    for (int i = 0; i < g.nb_sommets; i++){
        int d = degre(g, i);
        if( d_max < d){
            d_max = d;
        }
    }
    return d_max;
}

// Partie 2

typedef int lst_adjacence[30][31];
struct graph_s {
    int nb_sommets;
    lst_adjacence lst;
};
typedef struct graph_s graph; // graph sans 'e' pour ne pas avoir de conflit avec la représentation précédente


// PREMIÈRE POSSIBILITÉ : DEGRÉ
// La première case de chaque ligne i donne d(i).
// Si cette case contient un entier n, on sait donc qu'on ne doit parcourir que les cases de 1 à n :
// le tableau statique ne contient plus aucun voisin ensuite.
graph ex_v1 = {6,   { {2, 1, 2},
                      {2, 0, 2},
                      {2, 0, 1},
                      {1, 4},
                      {1, 3},
                      {0}       }  };

// DEUXIÈME POSSIBILITÉ : SENTINELLE
// La valeur -1, qui ne correspond à aucun numéro de sommet, peut par exemple servir de sentinelle.
// Dès que l'on croise cette valeur, on sait qu'on peut arrêter le parcours :
// le tableau statique ne contient plus aucun voisin ensuite.
graph ex_v2 = {6,   { {1, 2, -1},
                      {0, 2, -1},
                      {0, 1, -1},
                      {4, -1},
                      {3, -1},
                      {-1}       }  };



int nb_arcs_v1(graph g){
    int nb = 0;
    for (int i = 0; i < g.nb_sommets; i++){
        nb += g.lst[i][0];
    }
    return nb;
}

int nb_arcs_v2(graph g){
    int nb = 0;
    for(int i = 0; i<g.nb_sommets; i++){
        int j = 0;
        while(g.lst[i][j] != -1){
            j ++;
        }
        nb += j;
    }
    return nb;
}

bool possède_boucle_v1(graph g){
    bool res = true;
    for (int i = 0; i < g.nb_sommets && res; i++){
        bool boucle = false;
        for (int j = 0; j < g.lst[i][0]; j++ ){
            boucle |= g.lst[i][j+1] == i;
        }
        res &= boucle;
    }
    return res;
}

bool possède_boucle_v2(graph g){
    bool res = true;
    for (int i = 0; i < g.nb_sommets && res; i++){
        bool boucle = false;
        int j = 0;
        while (g.lst[i][j] != -1){
            boucle |= g.lst[i][j] == i;
            j++;
        }
        res &= boucle;
    }
    return res;
}



bool est_successeur_v1(graph g, int sj, int si) {
    for (int indice_successeur = 1; indice_successeur <= g.lst[si][0]; indice_successeur += 1) {
        if (g.lst[si][indice_successeur] == sj) {
            return true;
        }
    }
    return false;
}

bool est_successeur_v2(graph g, int sj, int si) {
    for (int indice_successeur = 0; g.lst[si][indice_successeur] != -1; indice_successeur += 1) {
        if (g.lst[si][indice_successeur] == sj) {
            return true;
        }
    }
    return false;
}

bool est_predecesseur_v1(graph g, int si, int sj) {
    return est_successeur_v1(g, sj, si);
}

bool est_predecesseur_v2(graph g, int si, int sj) { 
    return est_successeur_v2(g, sj, si);
}

void degres_v1(graph g, int sommet, int* degre_entrant, int* degre_sortant) {
    *degre_entrant = 0;
    *degre_sortant = g.lst[sommet][0];
    for (int i = 0; i < g.nb_sommets; i += 1) {
        for (int j = 1; j <= g.lst[i][0]; j += 1) {
            if (g.lst[i][j] == sommet) {
                *degre_entrant += 1;
            }
        }
    }
}

void degres_v2(graph g, int sommet, int* degre_entrant, int* degre_sortant) {
    *degre_entrant = 0;
    *degre_sortant = 0;
    for (int i = 0; i < g.nb_sommets; i += 1) {
        for (int j = 0; g.lst[i][j] != -1; j += 1) {
            if (g.lst[i][j] == sommet) {
                *degre_entrant += 1;
            }
            if (i == sommet) {
                *degre_sortant += 1;
            }
        }
    }
}

void serialise_mat(char* nom_fichier, graphe g) {
    FILE* fichier = fopen(nom_fichier, "w");
    assert (fichier != NULL);
    fprintf(fichier, "%d\n", g.nb_sommets);
    for (int i = 0; i < g.nb_sommets; i += 1) {
        for (int j = 0; j < g.nb_sommets; j += 1) {
            if (g.mat[i*g.nb_sommets+j] == 1) {
                fprintf(fichier, "%d,%d\n", i, j);
            }
        }
    }
    fclose(fichier);
}

graphe deserialise_mat(char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    assert (fichier != NULL);

    int nb_sommets;
    fscanf(fichier, "%d", &nb_sommets);
    graphe g = {nb_sommets, {0}};
    int i, j;
    while (fscanf(fichier, "%d,%d", &i, &j) != EOF) {
        g.mat[i*nb_sommets+j] = 1;
    }

    fclose(fichier);
    return g;
}


void serialise_lst(char* nom_fichier, graph g) {
    FILE* fichier = fopen(nom_fichier, "w");
    assert (fichier != NULL);
    fprintf(fichier, "%d\n", g.nb_sommets);
    for (int i = 0; i < g.nb_sommets; i += 1) {
        for (int j = 0; g.lst[i][j] != -1; j += 1) {
            fprintf(fichier, "%d,%d\n", i, g.lst[i][j]);
        }
    }
    fclose(fichier);
}

graph deserialise_lst(char* nom_fichier)  {
    FILE* fichier = fopen(nom_fichier, "r");
    assert (fichier != NULL);

    int nb_sommets;
    fscanf(fichier, "%d", &nb_sommets);

    graph g = {nb_sommets, {}};

    int degres[30] = {0};

    int i, j;
    while (fscanf(fichier, "%d,%d", &i, &j) != EOF) {

        g.lst[i][degres[i]] = j;

        degres[i] += 1;
    }
    for (int i = 0; i < nb_sommets; i += 1) {
        g.lst[i][degres[i]] = -1;
    }

    fclose(fichier);
    return g;
}



int main(){
    return 0;
}