/*
TRIS PAR INSERTION, PAR SÉLECTION, À BULLES, DE LISTES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include "listes.h"


/* --------------------------------------------------------- */


/* Fonctions utilitaires (copie, test d'égalité) */


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


bool egales(liste l1, liste l2) {
    if (est_vide_liste(l1)) {
        return est_vide_liste(l2);
    }
    if (est_vide_liste(l2)) {
        return false;
    }
    return tete_liste(l1) == tete_liste(l2) && egales(queue_liste(l1), queue_liste(l2));
}



/* --------------------------------------------------------- */


/* Tri par sélection */


contenu minimum(liste l) {
    if (est_vide_liste(queue_liste(l))) {
        return tete_liste(l);
    }
    else {
        contenu mini_queue = minimum(queue_liste(l));
        if (tete_liste(l) > mini_queue) {
            return mini_queue;
        }
        else {
            return tete_liste(l);
        }
    }
}


liste supprime(liste l, contenu elt) {
    if (est_vide_liste(l)) {
        return creer_liste();
    }
    else {
        liste res = supprime(queue_liste(l), elt);
        if (tete_liste(l) != elt) {
            ajouter_tete_liste(tete_liste(l), &res);
        }
        return res;
    }
}


liste tri_selection(liste l) {
    if (est_vide_liste(l)) {
        return creer_liste();
    }
    else {
        contenu min = minimum(l);
        liste sans_min = supprime(l, min);
        liste res = tri_selection(sans_min);
        ajouter_tete_liste(min, &res);
        detruire_liste(sans_min);
        return res;
    }
}



/* --------------------------------------------------------- */


/* Tri par insertion */


liste insere(liste l, contenu elt) {
    if (est_vide_liste(l)) {
        liste res = creer_liste();
        ajouter_tete_liste(elt, &res);
        return res;
    }
    else {
        if (elt < tete_liste(l)) {
            liste res = copie(l);
            ajouter_tete_liste(elt, &res);
            return res;
        }
        else {
            liste res = insere(queue_liste(l), elt);
            ajouter_tete_liste(tete_liste(l), &res);
            return res;
        }
    }
}


liste tri_insertion(liste l) {
    if (est_vide_liste(l)) {
        return creer_liste(l);
    }
    else {
        liste queue_triee = tri_insertion(queue_liste(l));
        liste res = insere(queue_triee, tete_liste(l));
        detruire_liste(queue_triee);
        return res;
    }
}



/* --------------------------------------------------------- */


/* Tri à bulles */


liste un_tour(liste l) {
    if (est_vide_liste(l) || est_vide_liste(queue_liste(l))) {
        return copie(l);
    }
    else {
        contenu t1 = tete_liste(l);
        contenu t2 = tete_liste(queue_liste(l));
        if (t1 < t2) {
            liste res = un_tour(queue_liste(l));
            ajouter_tete_liste(t1, &res);
            return res;
        }
        else {
            liste tout_sauf_t2 = copie(queue_liste(queue_liste(l)));
            ajouter_tete_liste(t1, &tout_sauf_t2);
            liste res = un_tour(tout_sauf_t2);
            ajouter_tete_liste(t2, &res);
            detruire_liste(tout_sauf_t2);
            return res;
        }
    }
}


liste tri_bulles(liste l) {
    liste l_apres_un_tour = un_tour(l);
    if (egales(l, l_apres_un_tour)) {
        return l_apres_un_tour;
    }
    else {
        liste res =  tri_bulles(l_apres_un_tour);
        detruire_liste(l_apres_un_tour);
        return res;
    }
}
