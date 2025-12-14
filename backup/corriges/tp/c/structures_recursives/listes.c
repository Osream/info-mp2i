/*
CORRIGÉ PARTIEL DU TP : STRUCTURES RÉCURSIVES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* Fichier d'implémentation des listes chaînées */


/* --------------------------------------------------------- */

#include "listes.h"

/* --------------------------------------------------------- */


struct maillon_s {
    contenu valeur;
    struct maillon_s* suivant;
};


liste creer_liste() {
    return NULL;
}

bool est_vide_liste(liste l) {
    return l == NULL;
}

void ajouter_tete_liste(contenu val, liste* l) {
    assert(l != NULL);
    maillon* m = malloc(sizeof(maillon));
    assert(m != NULL);
    m->valeur = val;
    m->suivant = *l;
    *l = m;
}

contenu tete_liste(liste l) {
    assert(!est_vide_liste(l));
    return l->valeur;
}

liste queue_liste(liste l) {
    assert(!est_vide_liste(l));
    return l->suivant;
}

void detruire_liste(liste l) {
    if (!est_vide_liste(l)) {
        detruire_liste(l->suivant);
        free(l);
    }
}

// Il faut impérativement savoir implémenter une liste chaînée rapidement !
// Entraînez-vous régulièrement à redéfinir les types maillon et liste,
// et à ré-écrire les six fonctions ci-dessus.