/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

/* Implémentation d'une pile avec un tableau */

#include "pile.h"


/* --------------------------------------------------------- */


const int TAILLE_MAX = 100;

struct pile_s {
    int fin;
    contenu_pile* elts;
};


pile creer_pile(void) {
    pile p = malloc(sizeof(struct pile_s));
    assert(p != NULL);
    p->fin = 0;
    p->elts = malloc(TAILLE_MAX * sizeof(contenu_pile));
    return p;
}

bool est_vide_pile(pile p) {
    return p->fin == 0;
}

bool est_pleine_pile(pile p) {
    return p->fin == TAILLE_MAX;
}

contenu_pile sommet_pile(pile p) {
    assert(!est_vide_pile(p));
    return p->elts[p->fin - 1];
}

void empiler(pile p, contenu_pile elt) {
    assert(!est_pleine_pile(p));
    p->elts[p->fin] = elt;
    p->fin += 1;
}

contenu_pile depiler(pile p) {
    assert(!est_vide_pile(p));
    p->fin -= 1;
    return p->elts[p->fin];
}

void detruire_pile(pile p) {
    free(p->elts);
    free(p);
}
