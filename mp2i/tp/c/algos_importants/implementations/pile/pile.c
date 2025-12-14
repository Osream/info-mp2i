/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

/* Implémentation d'une pile avec des maillons chaînés */

#include "pile.h"


/* --------------------------------------------------------- */

struct maillon_s {
    contenu_pile valeur;
    struct maillon_s* suivant;
};
typedef struct maillon_s maillon;

struct pile_s {
    maillon* sommet;
};

pile creer_pile(void) {
    pile p = malloc(sizeof(struct pile_s));
    assert(p != NULL);
    p->sommet = NULL;
    return p;
}

bool est_vide_pile(pile p) {
    assert(p != NULL);
    return p->sommet == NULL;
}

contenu_pile sommet_pile(pile p) {
    assert(!est_vide_pile(p));
    return p->sommet->valeur;
}

void empiler(pile p, contenu_pile elt) {
    assert(p != NULL);
    // on alloue un maillon pour notre nouveau sommet
    maillon* m = malloc(sizeof(maillon));
    assert(m != NULL);
    m->valeur = elt;
    // il pointe vers l'ancien maillon au sommet
    m->suivant = p->sommet;
    // le sommet est maintenant m
    p->sommet = m;
}

contenu_pile depiler(pile p) {
    assert(!est_vide_pile(p));
    // on récupère l'adresse du maillon actuellement au sommet
    maillon* s = p->sommet;
    // et sa valeur pour pouvoir la renvoyer
    contenu_pile elt_a_renvoyer = s->valeur;
    // le deuxième maillon devient alors le sommet
    p->sommet = s->suivant;
    // on n'oublie pas de libérer l'ancien premier maillon
    free(s);
    return elt_a_renvoyer;
}

void detruire_pile(pile p) {
    // on détruit tous les maillons
    while (!est_vide_pile(p)) {
        depiler(p);
    }
    // puis la pile elle-même
    free(p);
}
