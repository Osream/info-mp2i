/*
CORRIGÉ PARTIEL DU TP : STRUCTURES RÉCURSIVES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* Fichier d'utilisation des listes chaînées */


/* --------------------------------------------------------- */

#include "listes.h"

/* --------------------------------------------------------- */

// Pour rappel, on ne peut manipuler les listes chaînées qu'avec
// les 6 fonctions de l'interface (cf. le fichier listes.h).


int list_length(liste l) {
    if (est_vide_liste(l)) {
        return 0;
    }
    else {
        return 1 + list_length(queue_liste(l));
    }
    // Soit C(n) la complexité de list_length pour une liste de taille n.
    // Relation de récurrence :
    // C(0) = O(1)
    // C(n) = O(1) + C(n-1) pour n > 0
    // On en déduit (suite arithmétique) :
    // C(n) = O(n)
}

bool list_mem(liste l, contenu val) {
    if (est_vide_liste(l)) {
        return false;
    }
    else {
        return tete_liste(l) == val || list_mem(queue_liste(l), val);
    }
    // Même raisonnement que list_length pour la complexité,
    // list_mem est linéaire en la taille de la liste.
}

bool egales(liste l1, liste l2) {
    if (est_vide_liste(l1)) {
        return est_vide_liste(l2);
    }
    if (est_vide_liste(l2)) {
        return false;
    }
    return tete_liste(l1) == tete_liste(l2) && egales(queue_liste(l1), queue_liste(l2));
    // Soit C(n, m) la complexité de egales pour des listes l1 de taille n et l2 de taille m.
    // Relation de récurrence :
    // C(0, m) = O(1)
    // C(n, 0) = O(1);
    // O(1) <= C(n, m) <= O(1) + C(n-1, m-1) pour n > 0 et m > 0
    // Distinguons les cas :
    // - si n < m alors C(n, m) = O(n)
    // - si n >= m alors C(n, m) = O(m)
    // Ainsi C(n, m) = O(min(n, m))
}

void afficher_interieur(liste l) {
    printf("%d", tete_liste(l));
    if (!est_vide_liste(queue_liste(l))) {
        printf("; ");
        afficher_interieur(queue_liste(l));
    }
}
void afficher(liste l) {
    printf("[");
    if (!est_vide_liste(l)) {
        afficher_interieur(l);
    }
    printf("]\n");
}


contenu acces_indice(liste l, int indice) {
    if (indice == 0) {
        return tete_liste(l);
    }
    else {
        return acces_indice(queue_liste(l), indice-1);
    }
}

bool est_triee(liste l) {
    if (est_vide_liste(l) || est_vide_liste(queue_liste(l))) {
        return true;
    }
    else {
        return tete_liste(l) <= tete_liste(queue_liste(l)) && est_triee(queue_liste(l));
    }
}

liste copie(liste l) {
    if (est_vide_liste(l)) {
        return creer_liste();
    }
    else {
        liste copie_queue = copie(queue_liste(l));
        ajouter_tete_liste(tete_liste(l), &copie_queue);
        return copie_queue;
    }
}

liste concatene(liste l1, liste l2) {
    if (est_vide_liste(l1)) {
        return copie(l2);
    }
    else {
        liste queue = concatene(queue_liste(l1), l2);
        ajouter_tete_liste(tete_liste(l1), &queue);
        return queue;
    }
}

liste renverse(liste l) {
    if (est_vide_liste(l)) {
        return creer_liste(l);
    }
    else {
        liste tete = creer_liste();
        ajouter_tete_liste(tete_liste(l), &tete);
        liste queue_renversee = renverse(queue_liste(l));
        liste concatenation = concatene(queue_renversee, tete);
        detruire_liste(tete);
        detruire_liste(queue_renversee);
        return concatenation;
    }
}

liste insere(liste l, contenu val, int indice) {
    if (indice == 0) {
        liste res = copie(l);
        ajouter_tete_liste(val, &res);
        return res;
    }
    else {
        liste res = insere(queue_liste(l), val, indice-1);
        ajouter_tete_liste(tete_liste(l), &res);
        return res;
    }
}