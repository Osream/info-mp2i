/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

/* Implémentation d'une file avec deux piles */

#include "file.h"
#include "pile.h"


/* --------------------------------------------------------- */


struct file_s {
    pile entree;
    pile sortie;
};


file creer_file(void) {
    file f = malloc(sizeof(struct file_s));
    assert(f != NULL);
    f->entree = creer_pile();
    f->sortie = creer_pile();
    return f;
}

bool est_vide_file(file f) {
    assert(f != NULL);
    return est_vide_pile(f->entree) && est_vide_pile(f->sortie);
}

void transfere_entree_dans_sortie(file f) {
    assert(f != NULL);
    while (!est_vide_pile(f->entree)) {
        empiler(f->sortie, depiler(f->entree));
    }
}

contenu_file tete_file(file f){
    assert(!est_vide_file(f));
    if (est_vide_pile(f->sortie)) {
        transfere_entree_dans_sortie(f);
    }
    return sommet_pile(f->sortie);
}

void enfiler(file f, contenu_file elt) {
    assert(f != NULL);
    empiler(f->entree, elt);
}

contenu_file defiler(file f) {
    assert(!est_vide_file(f));
    if (est_vide_pile(f->sortie)) {
        transfere_entree_dans_sortie(f);
    }
    return depiler(f->sortie);
}

void detruire_file(file f) {
    assert(f != NULL);
    detruire_pile(f->entree);
    detruire_pile(f->sortie);
    free(f);
}