/*
CORRIGÉ PARTIEL DU TP : TAS
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include "../librairies.h"


// fonction auxiliaire pour échanger deux éléments d'un tableau
void echange(int* t, int i, int j) {
    int tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
}


/*---------------------------------------------------------*/

// IMPLÉMENTATION DES TAS

struct tas_s {
    int* elements; // tableau représentant le tas
    int nb_elements; // nombre actuel de nœuds dans le tas
    int capacite_maximale; // nombre maximal de nœuds que peut contenir le tas
    bool est_tas_min; // true s'il s'agit d'un tas-min, false s'il s'agit d'un tas-max
};
typedef struct tas_s tas;


// Fonctions utilitaires pour récupérer le fils gauche / fils droit / père d'un nœud d'indice i

int fils_gauche(int i, int taille_tas) {
    assert(0 <= i && i < taille_tas);
    if (2*i + 1 >= taille_tas) {
        return -1;
    }
    return 2*i + 1;
}

int fils_droit(int i, int taille_tas) {
    assert(0 <= i && i < taille_tas);
    if (2*i + 2 >= taille_tas) {
        return -1;
    }
    return 2*i + 2;
}

int pere(int i, int taille_tas) {
    assert(0 <= i && i < taille_tas);
    if (i == 0) {
        return -1;
    }
    return (i - 1) / 2;
}


// Fonctions de création, initialisation et destruction d'un tas

tas* tas_vide(int capacite, bool type_de_tas) {
    tas* t = malloc(sizeof(tas));
    assert(t != NULL);
    t->elements = malloc(capacite * sizeof(int));
    assert(t->elements != NULL);
    t->nb_elements = 0;
    t->capacite_maximale = capacite;
    t->est_tas_min = type_de_tas;
    return t;
}

void tas_detruit(tas* t) {
    free(t->elements);
    free(t);
}

void tas_initialise(tas* t, int n, int tableau[n]) {
    assert(t->nb_elements == 0 && n <= t->capacite_maximale);
    for (int i = 0; i < n; i += 1) {
        t->elements[i] = tableau[i];
    }
    t->nb_elements = n;
}


// Fonctions de percolation (vers le haut / vers le bas)

void percolation_vers_le_haut(int* t, int taille_t, int indice_noeud_mal_place, bool tas_min) {
    int p = pere(indice_noeud_mal_place, taille_t);
    if (p != -1 && ((tas_min && t[indice_noeud_mal_place] < t[p])
                    ||
                    (!tas_min && t[indice_noeud_mal_place] > t[p]))) {
        echange(t, indice_noeud_mal_place, p);
        percolation_vers_le_haut(t, taille_t, p, tas_min);
    }
}

void percolation_vers_le_bas(int* t, int taille_t, int indice_noeud_mal_place, bool tas_min) {
    int fg = fils_gauche(indice_noeud_mal_place, taille_t);
    int fd = fils_droit(indice_noeud_mal_place, taille_t);
    int indice_avec_lequel_echanger = indice_noeud_mal_place;
    // on regarde si l'échange doit se faire avec le fils gauche du nœud mal placé
    if (fg != -1 && ((tas_min && t[indice_noeud_mal_place] > t[fg])
                     ||
                     (!tas_min && t[indice_noeud_mal_place] < t[fg]))) {
        indice_avec_lequel_echanger = fg;
    }
    // ou bien avec son fils droit
    if (fd != -1 && ((tas_min && t[indice_avec_lequel_echanger] > t[fd])
                     ||
                     (!tas_min && t[indice_avec_lequel_echanger] < t[fd]))) {
        indice_avec_lequel_echanger = fd;
    }
    // si un échange est nécessaire, on le fait et on continue la percolation vers le bas depuis ce nœud
    if (indice_noeud_mal_place != indice_avec_lequel_echanger) {
        echange(t, indice_noeud_mal_place, indice_avec_lequel_echanger);
        percolation_vers_le_bas(t, taille_t, indice_avec_lequel_echanger, tas_min);
    }
}


// Fonctions principales de l'interface des tas

int tas_lecture_minimum_ou_maximum(tas t) {
    assert (t.nb_elements > 0);
    return t.elements[0];
}

void tas_insertion(tas* t, int etiquette_a_inserer) {
    assert(t->nb_elements < t->capacite_maximale);
    t->elements[t->nb_elements] = etiquette_a_inserer;
    t->nb_elements += 1;
    percolation_vers_le_haut(t->elements, t->nb_elements, t->nb_elements - 1, t->est_tas_min);
}

int tas_extraction_racine(tas* t) {
    assert(t->nb_elements > 0);
    t->nb_elements -= 1;
    if (t->nb_elements != 0) {
        echange(t->elements, 0, t->nb_elements);
        percolation_vers_le_bas(t->elements, t->nb_elements, 0, t->est_tas_min);
    }
    return t->elements[t->nb_elements];
}


// Complexité des opérations

/*
Un tas contenant n éléments a une hauteur de ⌊log2 n⌋.

La complexité de la lecture du minimum (si tas-min) / maximum (si tas-max)
dans un tas de taille n est en O(1).

La complexité de l'insertion d'un élément dans un tas de taille n est en O(log(n)),
car le placement du nouveau nœud est en O(1), et la percolation est en O(hauteur du tas).

La complexité de l'extraction du minimum (si tas-min) / maximum (si tas-max) dans un tas
de taille n est en O(log(n)) (car tout est en O(1) sauf la percolation qui est logarithmique).
*/


/*---------------------------------------------------------*/

// TRI PAR TAS

void tri_par_tas(int* tableau_a_trier, int taille_tableau) {
    // 1ere étape : transformation du tableau en tas max
    for (int i = (taille_tableau-2) / 2; i >= 0; i -= 1) { // O(taille_tableau)
        percolation_vers_le_bas(tableau_a_trier, taille_tableau, i, false);
    }
    // 2ème étape : extractions du maximum
    for (int i = taille_tableau-1; i >= 1; i -= 1) { // O(taille_tableau * log(taille_tableau))
        echange(tableau_a_trier, 0, i);
        percolation_vers_le_bas(tableau_a_trier, i, 0, false);
    }
}

// Pour faire un tri dans l'ordre décroissant, on utilise un tas-min au lieu d'un tas-max.
// Il suffit donc de remplacer les deux 'false' par 'true'.


/*---------------------------------------------------------*/

// AUTRES OPÉRATIONS SUR LES TAS (EXERCICES)


// Vérification de la propriété de tas

bool verifie_indice_i(tas t, int i) {
    int fg = fils_gauche(i, t.nb_elements);
    int fd = fils_droit(i, t.nb_elements);
    bool verifie_gauche = true;
    bool verifie_droite = true;
    if (fg != -1) {
        if (t.est_tas_min) {
            verifie_gauche = t.elements[i] <= t.elements[fg];
        }
        else {
            verifie_gauche = t.elements[i] >= t.elements[fg];
        }
        verifie_gauche = verifie_gauche && verifie_indice_i(t, fg);       
    }
    if (fd != -1) {
        if (t.est_tas_min) {
            verifie_droite = t.elements[i] <= t.elements[fd];
        }
        else {
            verifie_droite = t.elements[i] >= t.elements[fd];
        }
        verifie_droite = verifie_droite && verifie_indice_i(t, fd);       
    }
    return verifie_gauche && verifie_droite;;
}

bool tas_verification(tas t) { // O(taille du tas)
    if (t.nb_elements == 0) {
        return true;
    }
    return verifie_indice_i(t, 0);
}


// Recherche d'un élément quelconque

int recherche_indice_i(tas t, int etiquette_a_rechercher, int i) {
    // cas où on a trouvé l'étiquette
    if (t.elements[i] == etiquette_a_rechercher) {
        return 0;
    }
    // cas où on sait que l'étiquette ne peut être dans aucun des sous-arbres de i car la propriété d'ordre des tas ne serait pas respectée
    if ((t.est_tas_min && etiquette_a_rechercher < t.elements[i])
        ||
        (!t.est_tas_min && etiquette_a_rechercher > t.elements[i])) {
            return -1;
    }
    // cas où on doit rechercher l'étiquette dans les deux sous-arbres (s'ils existent)
    int fg = fils_gauche(i, t.nb_elements);
    int fd = fils_droit(i, t.nb_elements);
    int recherche_gauche = -1;
    int recherche_droite = -1;
    if (fg != -1) {
        recherche_gauche = recherche_indice_i(t, etiquette_a_rechercher, fg);
    }
    if (fd != -1) {
        recherche_droite = recherche_indice_i(t, etiquette_a_rechercher, fd);
    }
    // on renvoie la profondeur minimale à laquelle on a trouvé l'étiquette
    if (recherche_gauche == -1 && recherche_droite == -1) {
        return -1;
    }
    else if (recherche_gauche == -1) {
        return 1 + recherche_droite;
    }
    else if (recherche_droite == -1) {
        return 1 + recherche_gauche;
    }
    else if (recherche_gauche < recherche_droite) {
        return 1 + recherche_gauche;
    }
    else {
        return 1 + recherche_droite;
    }
}

int tas_recherche(tas t, int etiquette_a_rechercher) { // O(taille du tas)
    return recherche_indice_i(t, etiquette_a_rechercher, 0);
}


// Modification de l'étiquette d'un nœud

void tas_modifie_indice(tas* t, int nouvelle_etiquette, int indice_a_modifier) { // O(log(taille du tas))
    assert(0 <= indice_a_modifier && indice_a_modifier < t->nb_elements);
    int ancienne_etiquette = t->elements[indice_a_modifier];
    t->elements[indice_a_modifier] = nouvelle_etiquette;
    if ((t->est_tas_min && ancienne_etiquette < nouvelle_etiquette)
        ||
        (!t->est_tas_min && ancienne_etiquette > nouvelle_etiquette)) {
        percolation_vers_le_bas(t->elements, t->nb_elements, indice_a_modifier, t->est_tas_min);
    }
    else if ((t->est_tas_min && ancienne_etiquette > nouvelle_etiquette)
        ||
        (!t->est_tas_min && ancienne_etiquette < nouvelle_etiquette)) {
        percolation_vers_le_haut(t->elements, t->nb_elements, indice_a_modifier, t->est_tas_min);
    }
}

void tas_modifie_etiquette(tas* t, int j, int i) { // O(taille du tas)
    int indice_a_modifier = 0;
    while (t->elements[indice_a_modifier] != i) {
        indice_a_modifier += 1;
        assert(indice_a_modifier < t->nb_elements);
    }
    tas_modifie_indice(t, j, indice_a_modifier);
}


// Comparaison de deux tas

bool tas_identiques(tas t1, tas t2) {
    bool res = t1.nb_elements == t2.nb_elements && t1.est_tas_min == t2.est_tas_min;
    int i = 0;
    while (res && i < t1.nb_elements) {
        res = res && t1.elements[i] == t2.elements[i];
        i += 1;
    }
    return res;
}

/* Pour déterminer si deux tas ont le même ensemble d'éléments,
le plus efficace est de les trier (avec le tri par tas)
puis de vérifier s'ils sont identiques avec la fonction précédente. */
