/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

/* Implémentation d'une file avec des maillons doublement chaînés circulaires */

#include "file.h"


/* --------------------------------------------------------- */


struct maillon_s {
    contenu_file valeur;
    struct maillon_s* precedent;
    struct maillon_s* suivant;
};
typedef struct maillon_s maillon;

struct file_s {
    maillon* tete;
};


file creer_file(void) {
    file f = malloc(sizeof(struct file_s));
    assert(f != NULL);
    f->tete = NULL;
    return f;
}

bool est_vide_file(file f) {
    assert(f != NULL);
    return f->tete == NULL;
}

contenu_file tete_file(file f){
    assert(!est_vide_file(f));
    return f->tete->valeur;
}

void enfiler(file f, contenu_file elt) {
    // on crée un maillon pour notre nouvel élément
    maillon* m = malloc(sizeof(maillon));
    assert(m != NULL);
    m->valeur = elt;
    if (est_vide_file(f)) {
        // la liste est doublement chaînée circulaire donc si m est le seul maillon, il pointe vers lui-même
        m->precedent = m;
        m->suivant = m;
        f->tete = m;
    }
    else {
        // f->tete est le premier maillon de la file, et f->tete->precedent est le dernier maillon
        // il faut changer tous les pointeurs pour insérer m entre le dernier et le premier maillon
        m->suivant = f->tete;
        m->precedent = f->tete->precedent;
        f->tete->precedent->suivant = m;
        f->tete->precedent = m;
    }
}

contenu_file defiler(file f) {
    assert(!est_vide_file(f));
    maillon* ancienne_tete = f->tete;
    contenu_file elt_a_renvoyer = ancienne_tete->valeur;
    // on rattache le suivant et le précédent de l'ancienne tête ensemble
    ancienne_tete->suivant->precedent = ancienne_tete->precedent;
    ancienne_tete->precedent->suivant = ancienne_tete->suivant;
    f->tete = ancienne_tete->suivant;
    // cas où on défile le dernier maillon
    if (f->tete == ancienne_tete) {
        f->tete = NULL;
    }
    free(ancienne_tete);
    return elt_a_renvoyer;
}

void detruire_file(file f) {
    while (!est_vide_file(f)) {
        defiler(f);
    }
    free(f);
}
