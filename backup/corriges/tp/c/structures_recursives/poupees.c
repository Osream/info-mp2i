/*
CORRIGÉ PARTIEL DU TP : STRUCTURES RÉCURSIVES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* Fichier d'implémentation des poupées russes */


/* --------------------------------------------------------- */

#include "poupees.h"

/* --------------------------------------------------------- */


struct poupee_s {
    int taille; // taille de la poupée
    struct poupee_s* contenu; // pointeur vers la poupée à l'intérieur
};


poupee* poupee_creer(int t) {
    // vérification des préconditions
    assert(t > 0);
    // allocation pour la première poupée
    poupee* p = malloc(sizeof(poupee));
    // vérification que l'allocation s'est bien passée
    assert(p != NULL);
    // la taille de la poupée est t
    p->taille = t;
    // cas de base : la poupée créée est vide
    if (t == 1) {
        p->contenu = NULL;
    }
    // cas récursif : on crée récursivement les poupées à l'intérieur
    else {
        p->contenu = poupee_creer(t-1);
    }
    return p;
}

void poupee_detruire(poupee* p) {
    // vérification du respect des préconditions
    assert(p != NULL);
    // si nécessaire, on libère récursivement tout le contenu
    if (p->contenu != NULL) {
        poupee_detruire(p->contenu);
    }
    // puis on libère la poupée elle-même
    free(p);
}

void poupee_afficher(poupee* p) {
    // si la poupée n'est pas vide
    if (p != NULL) {
        // on affiche sa taille
        printf("%d\n", p->taille);
        // puis on affiche récursivement son contenu
        poupee_afficher(p->contenu);
    }
}

int poupee_taille(poupee* p) {
    assert(p != NULL);
    return p->taille;
}

bool poupee_check(poupee* p) {
    assert(p != NULL);
    // cas de base : on est arrivé à la plus petite poupée possible
    if (p->contenu == NULL) {
        return true;
    }
    // cas récursif : on vérifie que la poupée est de taille supérieure à celle intérieure
    //                et on continue récursivement la vérification dans la suite des poupées
    else {
        return (p->taille > p->contenu->taille) && poupee_check(p->contenu);
    }
}

poupee* poupee_ouvre(poupee* p, int n) {
    assert(n > 0 && p != NULL && p->contenu != NULL); // préconditions
    if (n == 1) {
        return p->contenu;
    }
    else {
        return poupee_ouvre(p->contenu, n-1);
    }
}
