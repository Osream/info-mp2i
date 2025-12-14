/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET pileS EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

/* Tests pour l'implémentation des piles */

#include "pile.h"


/* --------------------------------------------------------- */


void tests_creer_pile() {
    pile f = creer_pile();
    assert(est_vide_pile(f));
    detruire_pile(f);
}

void tests_est_vide_pile() {
    pile f = creer_pile();
    assert(est_vide_pile(f));
    empiler(f, 4);
    assert(!est_vide_pile(f));
    detruire_pile(f);
}

void tests_sommet_pile() {
    pile f = creer_pile();
    empiler(f, 1);
    empiler(f, 2);
    assert(sommet_pile(f) == 2);
    assert(sommet_pile(f) == 2);
    detruire_pile(f);
}

void tests_empiler() {
    pile f = creer_pile();
    empiler(f, 1);
    assert(sommet_pile(f) == 1);
    empiler(f, 2);
    assert(sommet_pile(f) == 2);
    detruire_pile(f);
}

void tests_depiler() {
    pile f = creer_pile();
    empiler(f, 1);
    empiler(f, 2);
    assert(depiler(f) == 2);
    assert(depiler(f) == 1);
    assert(est_vide_pile(f));
    detruire_pile(f);
}

int main() {
    tests_creer_pile();
    tests_est_vide_pile();
    tests_sommet_pile();
    tests_empiler();
    tests_depiler();
}