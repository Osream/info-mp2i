/*
CORRIGÉ DU TP : REPRÉSENTATION DES GRAPHES (PARTIE EN C)
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include "librairies.h"


/* --------------------------------------------------------- */

/* Matrice d'adjacence */

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


int nb_aretes(graphe g) { // O(|S|²)
    int nombre_de_1 = 0;
    for (int i = 0; i < g.nb_sommets * g.nb_sommets; i += 1) {
            nombre_de_1 += g.mat[i];
    }
    return nombre_de_1 / 2; // chaque arête est comptée deux fois
}

bool sont_voisins(graphe g, int si, int sj) { // O(1)
    return g.mat[si*g.nb_sommets+sj] == 1; // on regarde le coefficient (si, sj)
}

bool verifie_orientation(graphe g) { // O(|S|²)
    for (int si = 0; si < g.nb_sommets; si += 1) {
        for (int sj = 0; sj < g.nb_sommets; sj += 1) {
            // la matrice d'un graphe non orienté est symétrique
            if (g.mat[si*g.nb_sommets+sj] != g.mat[sj*g.nb_sommets+si]) {
                return false;
            }
        }
    }
    return true;
}

int degre(graphe g, int sommet) { // O(|S|)
    int nb_voisins = 0;
    for (int potentiel_voisin = 0; potentiel_voisin < g.nb_sommets; potentiel_voisin += 1) {
        if (sont_voisins(g, sommet, potentiel_voisin)) {
            nb_voisins += 1;
        }
    }
    return nb_voisins;
}

int sommet_degre_max(graphe g) { // O(|S|²)
    int res = -1;
    int degre_res = -1;
    for (int sommet = 0; sommet < g.nb_sommets; sommet += 1) {
        int degre_sommet = degre(g, sommet);
        if (degre_sommet > degre_res) {
            degre_res = degre_sommet;
            res = sommet;
        }
    }
    return res;
}


/* --------------------------------------------------------- */

/* Liste d'adjacence */

typedef int lst_adjacence[30][31];
struct graph_s {
    int nb_sommets;
    lst_adjacence lst;
};
typedef struct graph_s graph; // graph sans 'e' pour ne pas avoir de conflit avec la représentation précédente

graph lst_go_v1 =  // version avec degré sortant
    {9,  {  {1, 1},
            {2, 0, 3},
            {2, 4, 5},
            {0},
            {2, 0, 8},
            {5, 0, 2, 3, 4, 6},
            {1, 2},
            {1, 6},
            {0}                }  };

graph lst_go_v2 = // version avec sentinelle
    {9,  {  {1, -1},
            {0, 3, -1},
            {4, 5, -1},
            {-1},
            {0, 8, -1},
            {0, 2, 3, 4, 6, -1},
            {2, -1},
            {6, -1},
            {-1}                }  };


// pour chaque fonction suivante, la version :
// _v1 travaille sur une liste d'adjacence stockée avec les degrés sortants aux indices 0
// _v2 travaille sur une liste d'adjacence stockée avec les sentinelles

int nb_arcs_v1(graph g) { // O(|S|)
    int somme_degre_sortants = 0;
    for (int sommet = 0; sommet < g.nb_sommets; sommet += 1) {
        somme_degre_sortants += g.lst[sommet][0];
    }
    return somme_degre_sortants; // = |A|
}

int nb_arcs_v2(graph g) { // O(|S|+|A|)
    int somme_degre_sortants = 0;
    for (int sommet = 0; sommet < g.nb_sommets; sommet += 1) {
        for (int successeur = 0; g.lst[sommet][successeur] != -1; successeur += 1) {
            somme_degre_sortants += 1;
        }
    }
    return somme_degre_sortants;
}

bool possede_boucle_v1(graph g) { // O(|S|+|A|)
    for (int sommet = 0; sommet < g.nb_sommets; sommet += 1) {
        for (int indice_successeur = 1; indice_successeur <= g.lst[sommet][0]; indice_successeur += 1) {
            if (sommet == g.lst[sommet][indice_successeur]) {
                return true;
            }
        }
    }
    return false;
}

bool possede_boucle_v2(graph g) { // O(|S|+|A|)
    for (int sommet = 0; sommet < g.nb_sommets; sommet += 1) {
        for (int indice_successeur = 0; g.lst[sommet][indice_successeur] != -1; indice_successeur += 1) {
            if (sommet == g.lst[sommet][indice_successeur]) {
                return true;
            }
        }
    }
    return false;
}

bool sj_est_successeur_de_si_v1(graph g, int sj, int si) { // O(d+(si))
    for (int indice_successeur = 1; indice_successeur <= g.lst[si][0]; indice_successeur += 1) {
        if (g.lst[si][indice_successeur] == sj) {
            return true;
        }
    }
    return false;
}

bool sj_est_successeur_de_si_v2(graph g, int sj, int si) { // O(d+(si))
    for (int indice_successeur = 0; g.lst[si][indice_successeur] != -1; indice_successeur += 1) {
        if (g.lst[si][indice_successeur] == sj) {
            return true;
        }
    }
    return false;
}

bool si_est_predecesseur_de_sj_v1(graph g, int si, int sj) { // O(d+(si))
    return sj_est_successeur_de_si_v1(g, sj, si);
}

bool si_est_predecesseur_de_sj_v2(graph g, int si, int sj) { // O(d+(si))
    return sj_est_successeur_de_si_v2(g, sj, si);
}

void degres_v1(graph g, int sommet, int* degre_entrant, int* degre_sortant) { // O(|S|+|A|)
    // le résultat est stocké aux adresses passées en paramètre car on ne peut pas renvoyer de couple en C
    *degre_entrant = 0;
    *degre_sortant = g.lst[sommet][0];
    for (int i = 0; i < g.nb_sommets; i += 1) { // on regarde tous les potentiels prédécesseurs du sommet, autrement dit tous les sommets i
        for (int j = 1; j <= g.lst[i][0]; j += 1) {
            // on vérifie si le sommet appartient aux successeurs du sommet i
            if (g.lst[i][j] == sommet) {
                *degre_entrant += 1;
            }
        }
    }
}

void degres_v2(graph g, int sommet, int* degre_entrant, int* degre_sortant) { // O(|S|+|A|)
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


/* --------------------------------------------------------- */

/* Sérialisation */

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
    graphe g = {nb_sommets, {0}}; // rappel : avec les tableaux statiques, écrire {0} permet d'initialiser toutes les cases à 0
    
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
        // version avec la sentinelle :
        for (int j = 0; g.lst[i][j] != -1; j += 1) {
        // pour la version avec le degré, remplacez le for de la ligne précédente par :
        // for (int j = 1; j <= g.lst[i][0]; j += 1) {
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

    // création du graphe, les listes d'adjacence sont pour l'instant vide
    graph g = {nb_sommets, {}};

    // on conserve en mémoire le degré de chaque sommet du graphe
    // au début il n'y a aucun voisin donc le degré de tous les sommets est 0
    int degres[30] = {0};

    int i, j;
    while (fscanf(fichier, "%d,%d", &i, &j) != EOF) {

        // version avec la sentinelle :
        g.lst[i][degres[i]] = j;
        // pour la version avec le degré, remplacez la ligne précédente par :
        // g.lst[i][degres[i]+1] = j;

        degres[i] += 1;
    }

    // pour finir on place les sentinelles
    for (int i = 0; i < nb_sommets; i += 1) {
        g.lst[i][degres[i]] = -1;
        // pour l'autre version, remplacez la ligne précédente par :
        // g.lst[i][0] = degres[i];
    }

    fclose(fichier);
    return g;
}
