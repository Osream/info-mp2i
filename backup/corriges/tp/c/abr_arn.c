/*
CORRIGÉ DU TP : ABR ET ARN
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include "librairies.h"


/* --------------------------------------------------------- */

// ARBRES BINAIRES DE RECHERCHE


// implémentation

struct noeud_s {
    int etiq;
    struct noeud_s* gauche;
    struct noeud_s* droit;
    struct noeud_s* pere;
};
typedef struct noeud_s* abr;


abr construit(int e, abr g, abr d) {
    abr racine = malloc(sizeof(struct noeud_s));
    assert(racine != NULL);

    racine->etiq = e;
    racine->gauche = g;
    racine->droit = d;
    racine->pere = NULL;

    if (g != NULL) {
        g->pere = racine;
    }
    if (d != NULL) {
        d->pere = racine;
    }

    return racine;
}

void detruit(abr a) {
    if (a != NULL) {
        detruit(a->gauche);
        detruit(a->droit);
        free(a);
    }
}


void affiche_croissant(abr a) {
    // le parcours infixe donne les étiquettes dans l'ordre croissant
    if (a != NULL) {
        affiche_croissant(a->gauche);
        printf("%d ", a->etiq);
        affiche_croissant(a->droit);
    }
}


// recherche dans un ABR

bool recherche_abr(abr a, int e) {
    if (a == NULL) {
        return false;
    }
    else if (a->etiq == e) {
        return true;
    }
    else if (a->etiq < e) {
        return recherche_abr(a->droit, e);
    }
    else {
        return recherche_abr(a->gauche, e);
    }
}

bool recherche_abr_imperatif(abr a, int e) {
    while (a != NULL) {
        if (a->etiq == e) {
            return true;
        }
        else if (a->etiq < e) {
            a = a->droit;
        }
        else {
            a = a->gauche;
        }
    }
    return false;
}


int maximum(abr a) {
    // le maximum est tout à droite
    if (a->droit == NULL) {
        return a->etiq;
    }
    else {
        return maximum(a->droit);
    }
}

int minimum(abr a) {
    // le minimum est tout à gauche
    if (a->gauche == NULL) {
        return a->etiq;
    }
    else {
        return minimum(a->gauche);
    }
}


// insertion dans un ABR

void insertion_abr(abr* a, int e) {

    // si l'arbre était vide, il devient une feuille d'étiquette e
    if (*a == NULL) {
        *a = construit(e, NULL, NULL);
    }

    // si l'insertion de e doit se faire à droite
    else if ((*a)->etiq < e) {
        // si (*a) n'a pas de sous-arbre droit, on insère ici
        if ((*a)->droit == NULL) {
            (*a)->droit = construit(e, NULL, NULL);
            (*a)->droit->pere = *a;
        }
        // sinon on insère récursivement dans le sous-arbre droit
        else {
            insertion_abr(&(*a)->droit, e);
        }
    }

    // si l'insertion de e doit se faire à gauche
    else if ((*a)->etiq > e) {
        if ((*a)->gauche == NULL) {
            (*a)->gauche = construit(e, NULL, NULL);
            (*a)->gauche->pere = *a;
        }
        else {
            insertion_abr(&(*a)->gauche, e);
        }
    }
}


// suppression par la méthode de la fusion dans un ABR

abr fusion(abr x1, abr x2) {
    if (x1 == NULL) {
        return x2;
    }
    else if (x2 == NULL) {
        return x1;
    }
    else {
        // on suit le schéma
        abr f = fusion(x1->droit, x2->gauche);
        x1->droit = x2;
        x2->pere = x1;
        x2->gauche = f;
        if (f != NULL) {
            f->pere = x2;
        }
        return x1;
    }
}

abr noeud_a_supprimer(abr a, int e) {
    // on est arrivé au bon endroit
    if (a == NULL || a->etiq == e) {
        return a;
    }
    // le nœud à supprimer est à droite
    else if (a->etiq < e) {
        return noeud_a_supprimer(a->droit, e);
    }
    // le nœud à supprimer est à gauche
    else {
        return noeud_a_supprimer(a->gauche, e);
    }
}

void suppression_abr_fusion(abr* a, int e) {
    // on récupère le nœud à supprimer
    abr a_supprimer = noeud_a_supprimer(*a, e);
    if (a_supprimer != NULL) {
        abr pere_du_noeud_supprime = a_supprimer->pere;

        // on fusionne ses fils, et on les raccroche dans l'arbre
        abr f = fusion(a_supprimer->gauche, a_supprimer->droit);
        if (f != NULL) {
            f->pere = pere_du_noeud_supprime;
        }

        // si on a supprimé la racine, la fusion des fils devient notre nouvelle racine
        if (pere_du_noeud_supprime == NULL) {
            *a = f;
        }
        else {
            // sinon on rattache la fusion des fils au père du bon côté
            if (pere_du_noeud_supprime->etiq < e) {
                pere_du_noeud_supprime->droit = f;
            }
            else {
                pere_du_noeud_supprime->gauche = f;
            }
        }

        // on libère le nœud
        free(a_supprimer);
    }
}



/* --------------------------------------------------------- */

// ARBRES BICOLORES


// implémentation

enum couleur_e {rouge, noir};
typedef enum couleur_e couleur;

struct arn_s {
    int etiq;
    couleur coul;
    struct arn_s* gauche;
    struct arn_s* droit;
};
typedef struct arn_s* arn;


arn construit_arn(int e, couleur c, arn g, arn d) {
    arn racine = malloc(sizeof(struct arn_s));
    assert(racine != NULL);
    racine->etiq = e;
    racine->coul = c;
    racine->gauche = g;
    racine->droit = d;
    return racine;
}

void detruit_arn(arn a) {
    if (a != NULL) {
        detruit_arn(a->gauche);
        detruit_arn(a->droit);
        free(a);
    }
}


// les rotations

arn rotation_droite(arn x) {
    arn y = x->gauche;
    x->gauche = y->droit;
    y->droit = x;
    return y;
}

arn rotation_gauche(arn y) {
    arn x = y->droit;
    y->droit = x->gauche;
    x->gauche = y;
    return x;
}


// insertion

arn corrige_rouge(arn a) {
    arn y = a;
    // je traite les 4 cas problématiques dans le même ordre
    // que celui du schéma présenté dans le TP
    if (a != NULL && a->coul == noir) {
        if (a->gauche != NULL && a->gauche->coul == rouge) {
            if (a->gauche->gauche != NULL && a->gauche->gauche->coul == rouge) {
                y = rotation_droite(a);
            }
            else if (a->gauche->droit != NULL && a->gauche->droit->coul == rouge) {
                y = rotation_gauche(a->gauche);
                a->gauche = y;
                y = rotation_droite(a);
            }
        }
        else if (a->droit != NULL && a->droit->coul == rouge) {
            if (a->droit->gauche != NULL && a->droit->gauche->coul == rouge) {
                y = rotation_droite(a->droit);
                a->droit = y;
                y = rotation_gauche(a);
            }
            else if (a->droit->droit != NULL && a->droit->droit->coul == rouge) {
                y = rotation_gauche(a);
            }
        }
    }
    // une fois les rotations faites il suffit de mettre les bonnes couleurs
    if (y != a) {
        y->coul = rouge;
        y->gauche->coul = noir;
        y->droit->coul = noir;
    }
    return y;
}

void insere_en_corrigeant_rouge(arn* a, int e) {
    // insère une feuille rouge
    if (*a == NULL) {
        *a = construit_arn(e, rouge, NULL, NULL);
    }
    // on insère à droite et on corrige les couleurs
    else if ((*a)->etiq < e) {
        insere_en_corrigeant_rouge(&(*a)->droit, e);
        *a = corrige_rouge(*a);
    }
    // idem à gauche
    else if ((*a)->etiq > e) {
        insere_en_corrigeant_rouge(&(*a)->gauche, e);
        *a = corrige_rouge(*a);
    }  
}

void insertion_arn(arn* a, int e) {
    // on insère puis on remet la racine en noir
    insere_en_corrigeant_rouge(a, e);
    (*a)->coul = noir;
}



/* --------------------------------------------------------- */

// EXERCICES


// suppression par la méthode de la remontée du minimum dans un ABR

abr* a_supprimer(abr* a, int e) {
    // on est arrivé au bon endroit
    if (*a == NULL || (*a)->etiq == e) {
        return a;
    }
    // le nœud à supprimer est à droite
    else if ((*a)->etiq < e) {
        return a_supprimer(&(*a)->droit, e);
    }
    // le nœud à supprimer est à gauche
    else {
        return a_supprimer(&(*a)->gauche, e);
    }
}

void supprime_feuille(abr* z) {
    free(*z);
    *z = NULL;
}

void supprime_noeud_a_un_fils(abr* z) {
    // on récupère l'unique fils de z
    abr fils_a_rattacher;
    if ((*z)->gauche != NULL) {
        fils_a_rattacher = (*z)->gauche;
    }
    else {
        fils_a_rattacher = (*z)->droit;
    }
    // on rattache le fils à son nouveau père
    abr pere_de_z = (*z)->pere;
    fils_a_rattacher->pere = pere_de_z;
    // on libère le nœud z
    free(*z);
    // on rattache le père à son fils du bon côté
    if (pere_de_z == NULL) {
        // cas où le nœud supprimé n'a pas de père (c'était la racine)
        *z = fils_a_rattacher;
    }
    else if (pere_de_z->etiq < fils_a_rattacher->etiq) {
        pere_de_z->droit = fils_a_rattacher;
    }
    else {
        pere_de_z->gauche = fils_a_rattacher;
    }
}

abr* minimum_noeud(abr* a) { // même chose que la fonction minimum mais renvoie le nœud et non l'étiquette
    if ((*a)->gauche == NULL) {
        return a;
    }
    else {
        return minimum_noeud(&(*a)->gauche);
    }
}

void supprime_noeud_a_deux_fils(abr* z) {
    // on trouve le minimum et on recopie son étiquette à la place du nœud à supprimer
    abr* mini = minimum_noeud(&(*z)->droit);
    (*z)->etiq = (*mini)->etiq;
    // on supprime le nœud du minimum
    if ((*mini)->droit == NULL) {
        supprime_feuille(mini);
    }
    else {
        supprime_noeud_a_un_fils(mini);
    }
}

void suppression_abr_remontee_minimum(abr* a, int e) {
    // on recherche le nœud z à supprimer
    abr* z = a_supprimer(a, e);
    if (*z != NULL) {
        // 1er cas : z est une feuille
        if ((*z)->gauche == NULL && (*z)->droit == NULL) {
            supprime_feuille(z);
        }
        // 2ème cas : z a un seul fils
        else if ((*z)->gauche == NULL || (*z)->droit == NULL) {
            supprime_noeud_a_un_fils(z);
        }
        // 3ème cas : z a deux fils
        else {
            supprime_noeud_a_deux_fils(z);
        }
    }
}


// tri via un ABR

void infixe(abr a, int* tableau, int* indice) {
    if (a != NULL) {
        infixe(a->gauche, tableau, indice);
        tableau[*indice] = a->etiq;
        *indice += 1;
        infixe(a->droit, tableau, indice);
    }
}

void tri_via_abr(int n, int tableau[n]) {
    // on insère tout dans un ABR
    abr a = NULL;
    for (int i = 0; i < n; i += 1) {
        insertion_abr(&a, tableau[i]);
    }
    // puis le parcours infixe permet de parcourir dans l'ordre croissant
    int indice = 0;
    infixe(a, tableau, &indice);
    detruit(a);
}

// Ce tri serait plus efficace avec un ARN car l'insertion dans un ABR dépend de la hauteur.
