/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

/* Implémentation d'une file avec un tableau circulaire */

#include "file.h"


/* --------------------------------------------------------- */


const int TAILLE_MAX = 100;

struct file_s {
    int debut;
    int fin;
    contenu_file* elts;
};


file creer_file(void) {
    file f = malloc(sizeof(struct file_s));
    assert(f != NULL);
    f->debut = 0;
    f->fin = 0;
    f->elts = malloc(TAILLE_MAX * sizeof(contenu_file));
    return f;
}

bool est_vide_file(file f) {
    assert(f != NULL);
    return f->debut == f->fin;
}

bool est_pleine_file(file f) {
    assert(f != NULL);
    return (f->fin + 1) % TAILLE_MAX == f->debut;
}

contenu_file tete_file(file f){
    assert(!est_vide_file(f));
    return f->elts[f->debut];
}

void enfiler(file f, contenu_file elt) {
    assert(!est_pleine_file(f));
    f->elts[f->fin] = elt;
    f->fin = (f->fin + 1) % TAILLE_MAX;
}

contenu_file defiler(file f) {
    contenu_file t = tete_file(f);
    f->debut = (f->debut + 1) % TAILLE_MAX;
    return t;
}

void detruire_file(file f) {
    free(f->elts);
    free(f);
}
