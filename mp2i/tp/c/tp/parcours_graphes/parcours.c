#include "../../libraries.h"
#include "pile/pile.h"
#include "file/file.h"

struct graphe_s {
    int nb_sommets;
    int liste[20][20]; // sentinelles pour marquer la fin des listes
};
typedef struct graphe_s graphe;

void explorer(int s, graphe G, int* vus){
    if (!vus[s]){
        vus[s] = 1;
        printf("%d", s);
        int i = 0;
        while (G.liste[s][i] != -1){
            explorer(G.liste[s][i], G, vus);
            i++;
        }
    }
}

void parcours_profondeur(graphe G, int dep){
    int vus[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0,};
    // vus peut être plus grand mais flm
    explorer(dep, G, vus);
    printf("\n");
}

void parcours_largeur(graphe G, int dep){
    int vus[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0,};
    file a_traiter = creer_file();
    vus[dep] = 1;
    enfiler(a_traiter, dep);
    while (!est_vide_file(a_traiter)){
        int sommet = defiler(a_traiter);
        printf("%d", sommet);
        int i = 0;
        while (G.liste[sommet][i] != -1){
            if (!vus[G.liste[sommet][i]]){
                vus[G.liste[sommet][i]] = !vus[G.liste[sommet][i]];
                enfiler(a_traiter, G.liste[sommet][i]);
            }
        }
    }
    detruire_file(a_traiter);
}

void parcours_largeur_pile(graphe G, int dep){
    int vus[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0,};
    pile a_traiter = creer_pile();
    vus[dep] = 1;
    empiler(a_traiter, dep);
    while (!est_vide_pile(a_traiter)){
        int sommet = depiler(a_traiter);
        printf("%d", sommet);
        int i = 0;
        while (G.liste[sommet][i] != -1){
            if (!vus[G.liste[sommet][i]]){
                vus[G.liste[sommet][i]] = !vus[G.liste[sommet][i]];
                empiler(a_traiter, G.liste[sommet][i]);
            }
            i ++;
        }
    }
    detruire_pile(a_traiter);
}

void parcours_generique(graphe G, int dep){
    int vus[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0,};
    file a_traiter = creer_file();
    enfiler(a_traiter, dep);
    while (!est_vide_file(a_traiter)){
        int sommet = defiler(a_traiter);
        if (!vus[sommet]){
            vus[sommet] = !vus[sommet];
            printf("%d", sommet);
            int i = 0;
            while (G.liste[sommet][i] != -1){
                enfiler(a_traiter, G.liste[sommet][i]);
                i++;
            }
        }
    }
    detruire_file(a_traiter);
}

int main(){
    graphe gno = {9, {
        {1, 4, 5, -1},
        {0, 3, -1},
        {4, 5, 6, -1},
        {1, 5, -1},
        {0, 2, 5, 8, -1},
        {0, 2, 3, 4, 6, -1},
        {2, 5,7, -1},
        {6, -1},
        {4, -1}
    }};
    graphe go = {9, {
        {1, 5, -1},
        {0, 3, -1},
        {4, 5, -1},
        {-1},
        {0, 8, -1},
        {2, 3, 4, 6, -1},
        {2, -1},
        {6, -1},
        {-1}
    }};
}