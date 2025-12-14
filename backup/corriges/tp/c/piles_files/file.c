/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

/* Implémentation d'une file avec des maillons chaînés */

#include "file.h"


/* --------------------------------------------------------- */

struct maillon_s {
    contenu_file valeur;
    struct maillon_s* suivant;
};
typedef struct maillon_s maillon;

struct file_s {
    maillon* premier;
    maillon* dernier;
};


file creer_file(void) {
    file f = malloc(sizeof(struct file_s));
    assert(f != NULL);
    // file vide = aucun premier ni dernier élément
    f->premier = NULL;
    f->dernier = NULL;
    return f;
}

bool est_vide_file(file f) {
    assert(f != NULL);
    return f->premier == NULL && f->dernier == NULL;
}

contenu_file tete_file(file f){
    assert(!est_vide_file(f));
    return f->premier->valeur;
}

void enfiler(file f, contenu_file elt) {
    assert(f != NULL);
    // on crée un maillon pour notre nouvel élément
    maillon* m = malloc(sizeof(maillon));
    assert(m != NULL);
    m->valeur = elt;
    m->suivant = NULL;
    // si la file était vide, m est le premier et aussi le dernier maillon
    if (est_vide_file(f)) {
        f->premier = m;
        f->dernier = m;
    }
    // sinon m est le dernier (et l'ancien dernier pointe vers m)
    else {
        f->dernier->suivant = m;
        f->dernier = m;
    }
}

contenu_file defiler(file f) {
    assert(!est_vide_file(f));
    // on récupère l'adresse du maillon actuellement en tête
    maillon* tete = f->premier;
    // et sa valeur pour pouvoir la renvoyer
    contenu_file elt_a_renvoyer = tete->valeur;
    // le deuxième maillon devient alors le premier
    f->premier = tete->suivant;
    // cas particulier où on aurait défilé le tout dernier maillon :
    if (f->premier == NULL) {
        f->dernier = NULL;
    }
    // on n'oublie pas de libérer l'ancien premier maillon
    free(tete);
    return elt_a_renvoyer;
}

void detruire_file(file f) {
    // on détruit tous les maillons
    while (!est_vide_file(f)) {
        defiler(f);
    }
    // puis la file elle-même
    free(f);
}
