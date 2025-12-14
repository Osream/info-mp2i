#include "tp.h"
#include <stdio.h>
#include <stdlib.h>


struct afnd_s {
    int nLettres;
    int nEtats;
    liste** Delta;
    bool* initiaux;
    bool* finaux;
};


// Question 1
void liberer(afnd aut){
    for (int i = 0; i < aut->nEtats; i++){
        for (int j = 0; j< aut->nLettres; j++){
            liberer_liste(aut->Delta[i][j]);
        }
        free(aut->Delta[i]);
    }
    free(aut->Delta);
    free(aut->finaux);
    free(aut->initiaux);
    free(aut);
}


// Question 2
afnd init(int nl, int ne){
    afnd aut = malloc(sizeof(struct afnd_s));
    aut->initiaux = malloc(ne * sizeof(bool));
    aut->finaux = malloc(ne * sizeof(bool));
    aut->nEtats = ne;
    aut->nLettres = nl;
    aut->Delta = malloc(ne * sizeof(liste*));

    for (int i = 0; i < ne; i++){
        aut->Delta[i] = malloc(nl * sizeof(liste));
        for (int j = 0; j< nl; j++){
            aut->Delta[i][j] = NULL;
        }
        aut->finaux[i] = false;
        aut->initiaux[i] = false;
    }
    return aut;
}

// Question 3
void ajout_transition(afnd aut, int s, char x, int t){
    int x_i = (int) x - a0;
    aut->Delta[s][x_i] = cons(t, aut->Delta[s][x_i]);
}

// Question 4
afnd text2afnd(char* nom){
    FILE* fich = fopen(nom, "r");
    int nl;
    fscanf(fich, "%d\n", &nl);
    int ne;
    fscanf(fich, "%d\n", &ne);
    afnd res = init(nl, ne);

    int nombre_init;
    fscanf(fich, "%d\n", &nombre_init);
    int s_i;
    for (int i = 0; i < nombre_init; i++){
        fscanf(fich, "%d\n", &s_i);
        res->initiaux[s_i] = true;
    }

    int nombre_finaux;
    fscanf(fich, "%d\n", &nombre_finaux);
    int s_f;
    for (int j = 0; j < nombre_finaux; j++){
        fscanf(fich, "%d\n", &s_f);
        res->initiaux[s_f] = true;
    }

    int etat_dep;
    char lettre;
    int etat_fin;

    while(
    fscanf(fich, "%d %c %d\n", &etat_dep, &lettre, &etat_fin) != EOF){
        ajout_transition(res, etat_dep, lettre, etat_fin);
    }

    fclose(fich);
    return res;
}


void afnd2dot(afnd aut, char* nom){
    // On ouvre la communication avec le fihier
    FILE* canal = fopen(nom, "w");
    // On crée un graphe orienté
    fprintf(canal, "digraph TP3 {\n");
    // Il sera écrit de gauche à droite (LeftRight)
    fprintf(canal, "rankdir = LR;\n");
    // On crée les états 
    for (int s = 0; s < aut->nEtats; s++){
        if (aut->finaux[s]){
            fprintf(canal, "node [shape = doublecircle, label = %d] %d;\n", s, s);}
        else{fprintf(canal, "node [shape = circle, label = %d] %d;\n", s, s);
            if (aut->initiaux[s]){
              // il faut une flèche, on crée le point de départ
              fprintf(canal, "node [shape = point] IN%d;\n", s);
              }
        }
    }
    // On place les transition avec leur étiquette
    for (int s = 0; s < aut->nEtats; s++){
        if (aut->initiaux[s]){
            // La flèche pour état initial
            fprintf(canal, "IN%d -> %d;\n", s, s);} 
        for (int x = 0; x < aut->nLettres; x++){
            // Toutes les transitions depuis s d'étiquette x
            liste l = aut->Delta[s][x];
            while(l != NULL){
                int t = l->val;
                l = l->suivant;
                char xl = (char) (x + a0);
                fprintf(canal, "%d -> %d [label = \"%c\"];\n", s, t, xl);
            }
        }
    }
    //On ferme le graphe
    fprintf(canal, "}");
    // On ferme le canal
    fclose(canal);
}

// Question 5
// #flm


// Question 6
// #flm

// Question 7
bool* Delta_partie(afnd aut, bool* entree, int k){
    int ne = aut->nEtats;
    bool* res = malloc(ne*sizeof(bool));
    for(int i = 0; i < ne; i++){
        res[i] = false;
        if(entree[i]){
            for(liste lst = aut->Delta[i][k]; lst != NULL; lst = lst->suivant){
                int etat_fin = lst->val;
                res[etat_fin] = true;
            }
        }
    }
    return res;
}

// Question 8
int code_lettre(char c){return (int) c - a0;}

void parcours_delta(liste* lst, afnd aut, int etat, char* u, int i){
    if (u[i] != '\0'){
        liste transition = aut->Delta[etat][code_lettre(u[i])];
        if(transition != NULL){
            i++;
            for(; transition != NULL; transition = transition->suivant){
                parcours_delta(lst, aut, transition->val, u, i);
            }
        }
    }
    else{
        cons(etat, *lst);
    }
}

liste Delta_etoile_etat(afnd aut, int etat, char * u){
    liste res = NULL;
    parcours_delta(&res, aut, etat, u, 0);
    return res;
}

bool* Delta_etoile(afnd aut, bool* entree, char* u){
    int ne = aut->nEtats;
    bool* res = malloc(ne*sizeof(bool));
    for(int i = 0; i < ne; i++){
        res[i] = false;
        if(entree[i]){
            for(liste lst = Delta_etoile_etat(aut, i, u); lst != NULL; lst = lst->suivant){
                int etat_fin = lst->val;
                res[etat_fin] = true;
            }
        }
    }
    return res;
}


// Question 9
bool reconnu(afnd aut, char* u){
    bool* a_parcourir = Delta_etoile(aut, aut->initiaux, u);
    for (int i = 0; i<aut->nEtats; i++){
        if(aut->finaux[i] && a_parcourir[i]){
            return true;
        }
    }
    return false;
}

// Question 10
// #flm

// Question 12
int partie2entier(bool* etats, int taille){
    int somme = 0;
    int puissance = 1;
    for(int i = 0; i < taille; i++){
        if(etats[i]){
            somme += puissance;
        }
        puissance *= 2;
    }
    return somme;
}

// Question 12
bool* entier2partie(int n, int taille){
    bool* partie = malloc(taille*sizeof(bool));
    int puissance = 1;
    for (int i = 0; i<taille; i++){
        partie[i] = false;
        if(n%puissance == 0){
            n-=puissance;
            partie[i] = true;
        }
    }
    return partie;
}

// Question 13
dico* accessible(afnd aut);

// Question 14
afnd determinise(afnd aut);

// Question 15



int main(void){
    afnd res = text2afnd("ab.txt");
    liberer(res);
    printf("ok\n");
    return 0;
}


