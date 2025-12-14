/*
CORRIGÉ DU TP : PARCOURS DE GRAPHES (PARTIE EN C)
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include "librairies.h"
#include "piles_files/file.h"
#include "piles_files/pile.h"


struct graphe_s {
    int nb_sommets;  // <= 20
    int liste[20][20]; // sentinelles pour marquer la fin des listes
};
typedef struct graphe_s graphe;


graphe gno = {9,  { {1, 4, 5, -1},
                    {0, 3, -1},
                    {4, 5, 6,-1},
                    {1, 5, -1},
                    {0, 2, 5, 8, -1},
                    {0, 2, 3, 4, 6, -1},
                    {2, 5, 7, -1},
                    {6, -1},
                    {4, -1} } };

graphe go =  {9,  { {1, 5, -1},
                    {0, 3, -1},
                    {4, 5, -1},
                    {-1},
                    {0, 8, -1},
                    {2, 3, 4, 6, -1},
                    {2, -1},
                    {6, -1},
                    {-1} } };



/* --------------------------------------------------------- */

/* Implémentation des parcours */

// La complexité temporelle des trois algorithmes est O(|S|+|A|).
// La complexité spatiale est O(|A|) pour l'algo générique et O(|S|) pour les deux autres.


void explorer(graphe G, int s, bool vus[20]) {
    if (!vus[s]) {
        vus[s] = true;
        //printf("%d ", s);
        for (int indice_v = 0; G.liste[s][indice_v] != -1; indice_v += 1) {
            explorer(G, G.liste[s][indice_v], vus);
        }
    }
}
void parcours_profondeur(graphe G, int dep) {
    bool vus[20] = {false}; // comme false = 0 en C, on a bien un tableau rempli de false
    explorer(G, dep, vus);
}


void parcours_largeur(graphe G, int dep) {
    bool vus[20] = {false};
    vus[dep] = true;
    file a_traiter = creer_file();
    enfiler(a_traiter, dep);
    while (!est_vide_file(a_traiter)) {
        int s = defiler(a_traiter);
        //printf("%d ", s);
        for (int indice_v = 0; G.liste[s][indice_v] != -1; indice_v += 1) {
            int v = G.liste[s][indice_v];
            if (!vus[v]) {
                vus[v] = true;
                enfiler(a_traiter, v);
            }
        }
    }
    detruire_file(a_traiter); // attention aux fuites de mémoire
}


void parcours_generique(graphe G, int dep) {
    // on peut remplacer la pile par une file (ou n'importe quelle structure en fait)
    bool vus[20] = {false};
    pile a_traiter = creer_pile();
    empiler(a_traiter, dep);
    while (!est_vide_pile(a_traiter)) {
        int s = depiler(a_traiter);
        if (!vus[s]) {
            //printf("%d ", s);
            vus[s] = true;
            for (int indice_v = 0; G.liste[s][indice_v] != -1; indice_v += 1) {
                empiler(a_traiter, G.liste[s][indice_v]);
            }
        }
    }
    detruire_pile(a_traiter);
}



/* --------------------------------------------------------- */

/* Applications des parcours */


bool est_connexe(graphe G) {
    // on peut faire un parcours depuis n'importe quel sommet de départ, je prends 0 ici
    int dep = 0;
    // copié-collé de l'algo générique
    bool vus[20] = {false};
    pile a_traiter = creer_pile();
    empiler(a_traiter, dep);
    while (!est_vide_pile(a_traiter)) {
        int s = depiler(a_traiter);
        if (!vus[s]) {
            vus[s] = true;
            for (int indice_v = 0; G.liste[s][indice_v] != -1; indice_v += 1) {
                empiler(a_traiter, G.liste[s][indice_v]);
            }
        }
    }
    detruire_pile(a_traiter);
    // on vérfie que tous les sommets ont été vus
    for (int i = 0; i < G.nb_sommets; i += 1) {
        if (!vus[i]) {
            return false;
        }
    }
    return true;
}


void distances(graphe G, int dep, int dist[20]) {
    // on suppose dist initialement rempli de -1
    dist[dep] = 0;
    // parcours en largeur
    bool vus[20] = {false};
    vus[dep] = true;
    file a_traiter = creer_file();
    enfiler(a_traiter, dep);
    while (!est_vide_file(a_traiter)) {
        int s = defiler(a_traiter);
        for (int indice_v = 0; G.liste[s][indice_v] != -1; indice_v += 1) {
            int v = G.liste[s][indice_v];
            if (!vus[v]) {
                vus[v] = true;
                enfiler(a_traiter, v);
                // le chemin jusque v de longueur minimale va jusque s + 1 arête de s à v 
                dist[v] = dist[s] + 1;
            }
        }
    }
    detruire_file(a_traiter);
}


void explorer_tri_topologique(graphe G, int s, bool vus[20], pile exploration_finie) {
    if (!vus[s]) {
        vus[s] = true;
        for (int i = 0; G.liste[s][i] != -1; i += 1) {
            explorer_tri_topologique(G, G.liste[s][i], vus, exploration_finie);
        }
        // une fois tous les voisins explorés, juste avant de sortir de l'appel récursif,
        // on indique que l'exploration de s est finie en l'ajoutant à la pile
        empiler(exploration_finie, s);
    }
}
void tri_topologique(graphe G, int topo[20]) {
    // la pile exploration_finie contiendra tous les sommets explorés,
    // dans l'ordre décroissant des dates de fin d'exploration
    // (au sommet de la pile, le sommet dont l'exploration s'est finie en dernier, etc)
    pile exploration_finie = creer_pile();
    // on lance le parcours depuis chaque sommet du graphe
    bool vus[20] = {false};
    for (int s = 0; s < G.nb_sommets; s += 1) {
        explorer_tri_topologique(G, s, vus, exploration_finie);
    }
    // on remplit alors le tableau en dépilant exploration_finie
    for (int i = 0; i < G.nb_sommets; i += 1) {
        topo[i] = depiler(exploration_finie);
    }
    detruire_pile(exploration_finie);
}


void explorer_arborescence(graphe G, int s, int pred, bool vus[20], int peres[20]) {
    // le paramètre pred est le sommet depuis lesquel l'exploration de s a été lancée
    if (!vus[s]) {
        vus[s] = true;
        peres[s] = pred;
        for (int i = 0; G.liste[s][i] != -1; i += 1) {
            explorer_arborescence(G, G.liste[s][i], s, vus, peres);
        }
    }
}
graphe arborescence_profondeur(graphe G, int dep) {
    // pour chaque sommet du graphe, on stocke le sommet depuis lequel on l'a parcouru
    // ce sera donc son père dans l'arborescence
    int peres[20];
    bool vus[20] = {false};
    explorer_arborescence(G, dep, -1, vus, peres);
    // on peut alors facilement construire l'arborescence
    graphe arbo = {G.nb_sommets, {}};
    int degres[20] = {0};
    // en reliant chaque sommet à son père
    for (int i = 0; i < G.nb_sommets; i += 1) {
        int pere_de_i = peres[i];
        if (pere_de_i != -1) {
            arbo.liste[pere_de_i][degres[pere_de_i]] = i;
            degres[pere_de_i] += 1;
        }
    }
    // on place les sentinelles
    for (int i = 0; i < G.nb_sommets; i += 1) {
        arbo.liste[i][degres[i]] = -1;
    }
    return arbo;
}



void explorer_composantes(graphe G, int s, int comp[20], int num_composante) {
    if (comp[s] == -1) { // sommet appartenant à aucune composante pour l'instant
        comp[s] = num_composante; // on place le sommet parcouru dans la composante actuelle
        for (int indice_v = 0; G.liste[s][indice_v] != -1; indice_v += 1) {
            explorer_composantes(G, G.liste[s][indice_v], comp, num_composante);
        }
    }
}
void composantes_connexes(graphe G, int comp[20]) {
    // aucun sommet n'est placé au départ
    for (int i = 0; i < G.nb_sommets; i += 1) {
        comp[i] = -1;
    }
    // numéro de la composante dans laquelle placer les prochains sommets parcourus
    int composante_actuelle = 0;
    // on parcourt les sommets, s'ils sont déjà vus ils ont déjà été mis dans une composante,
    // sinon on explore toute leur composante connexe et il y a donc une composante en plus
    for (int i = 0; i < G.nb_sommets; i += 1) {
        if (comp[i] == -1) {
            explorer_composantes(G, i, comp, composante_actuelle);
            composante_actuelle += 1;
        }
    }
}


bool cyclique(graphe G) {
    // pour chaque sommet, on vérifie s'il y a un cycle impliquant ce sommet
    pile a_traiter = creer_pile();
    for (int dep = 0; dep < G.nb_sommets; dep += 1) {
        // j'ai repris ici (arbitrairement) l'algo générique
        bool vus[20] = {false};
        empiler(a_traiter, dep);
        while (!est_vide_pile(a_traiter)) {
            int s = depiler(a_traiter);
            if (!vus[s]) {
                vus[s] = true;
                for (int indice_v = 0; G.liste[s][indice_v] != -1; indice_v += 1) {
                    empiler(a_traiter, G.liste[s][indice_v]);
                    // si on retombe sur dep, il y a un cycle
                    if (G.liste[s][indice_v] == dep) {
                        detruire_pile(a_traiter);
                        return true;
                    }
                }
            }
        }
    }
    detruire_pile(a_traiter);
    return false;
}
