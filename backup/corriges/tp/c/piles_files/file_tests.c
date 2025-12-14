/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

/* Tests pour l'implémentation des files */

#include "file.h"


/* --------------------------------------------------------- */


void tests_creer_file() {
    file f = creer_file();
    assert(est_vide_file(f));
    detruire_file(f);
}

void tests_est_vide_file() {
    file f = creer_file();
    assert(est_vide_file(f));
    enfiler(f, 4);
    assert(!est_vide_file(f));
    detruire_file(f);
}

void tests_tete_file() {
    file f = creer_file();
    enfiler(f, 1);
    enfiler(f, 2);
    assert(tete_file(f) == 1);
    assert(tete_file(f) == 1);
    detruire_file(f);
}

void tests_enfiler() {
    file f = creer_file();
    enfiler(f, 1);
    assert(tete_file(f) == 1);
    enfiler(f, 2);
    assert(tete_file(f) == 1);
    defiler(f);
    enfiler(f, 3);
    assert(tete_file(f) == 2);
    detruire_file(f);
}

void tests_defiler() {
    file f = creer_file();
    enfiler(f, 1);
    enfiler(f, 2);
    assert(defiler(f) == 1);
    assert(defiler(f) == 2);
    assert(est_vide_file(f));
    detruire_file(f);
}

int main() {
    tests_creer_file();
    tests_est_vide_file();
    tests_tete_file();
    tests_enfiler();
    tests_defiler();
}