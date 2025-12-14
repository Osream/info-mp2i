/* CORRIGÉ DU TD : PLUS COURT CHEMIN DANS UN GRAPHE
   Par J. BENOUWT
   Licence CC BY-NC-SA */



/* IMPLEMENTATION DE DIJKSTRA */


#include "limits.h" // pour INT_MAX qui représentera +∞


/* --------------------------------------------------------- */

/* implémentation des files de priorités */

// Les files de priorités ont déjà été implémentées via un tas-min en TP
#include "../../tp/c/tas/file_de_priorite.h"
//#include "../../tp/c/tas/file_de_priorite.h"


/* --------------------------------------------------------- */

/* types pour représenter les listes d'adjacence */

struct voisin_s {
    int sommet;
    int poids;
};
typedef struct voisin_s voisin;

struct graphe_s {
    int nb_sommets;  // <= 20
    voisin liste[20][20]; // sentinelles pour marquer la fin des listes
};
typedef struct graphe_s graphe;


/* --------------------------------------------------------- */

/* algorithme de Dijkstra */

void dijkstra(graphe G, int depart, int* distances, int* predecesseurs) {
    // initialisation de distances et prédécesseurs
    for (int sommet = 0; sommet < G.nb_sommets; sommet += 1) {
        distances[sommet] = INT_MAX; // INT_MAX représentera +∞
        predecesseurs[sommet] = -1; // -1 désignera "pas de prédécesseur" (possible car les sommets sont numéros à partir de 0)
    }
    distances[depart] = 0;
    // code de l'algo générique
    file_de_priorite* a_traiter = fp_creer();
    fp_enfiler(a_traiter, depart, 0);
    int vus[20] = {false};
    while (!fp_est_vide(a_traiter)) {
        int s = fp_defiler(a_traiter);
        if (!vus[s]) {
            vus[s] = true;
            for (int indice_voisin = 0; G.liste[s][indice_voisin].sommet != -1; indice_voisin += 1) {
                int voisin = G.liste[s][indice_voisin].sommet;
                // mise à jour des distances si nécessaire
                if (distances[voisin] > distances[s] + G.liste[s][indice_voisin].poids) {
                    distances[voisin] = distances[s] + G.liste[s][indice_voisin].poids;
                    predecesseurs[voisin] = s;
                    fp_enfiler(a_traiter, voisin, distances[voisin]);
                }
            }
        }
    }
    fp_detruire(a_traiter);
}


/* --------------------------------------------------------- */

/* exemple */

graphe graphe_question_11 = { 5, // nombre de sommets
                              { {{1, 9}, {4, 5}, {-1, -1}}, // successeurs de 0
                                {{2, 1}, {4, 2}, {-1, -1}}, // successeurs de 1
                                {{3, 4}, {-1, -1}}, // successeurs de 2
                                {{0, 7}, {2, 6}, {-1, -1}}, // successeurs de 3
                                {{1, 3}, {2, 9}, {3, 2}, {-1, -1}} // successeurs de 4
                              }
                            };

void affiche_tableau(int taille, int tab[taille]) {
    for (int i = 0; i < taille; i += 1){
        printf("%d\t", tab[i]);
    }
    printf("\n\n");
}

int main() {
    printf("\n ----- DIJKSTRA -----\n\n");
    int dist11[20];
    int pred11[20];
    dijkstra(graphe_question_11, 0, dist11, pred11);
    printf("Tableau des distances obtenu pour le graphe de la question 11 du TD :\n");
    affiche_tableau(graphe_question_11.nb_sommets, dist11);
    printf("Tableau des prédécesseurs obtenu pour le graphe de la question 11 du TD :\n");
    affiche_tableau(graphe_question_11.nb_sommets, pred11);
}
