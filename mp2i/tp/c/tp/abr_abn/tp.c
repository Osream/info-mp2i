#include "../../libraries.h"
#include <stdio.h>
#include <string.h>
#include <threads.h>

struct noeud_s{
    int etiquette;
    struct noeud_s* sag;
    struct noeud_s* sad;
    struct noeud_s* pere;
};

typedef struct noeud_s* abr ;

abr construit (int e, abr g, abr d){
    abr res = malloc(sizeof(struct noeud_s));
    assert(res != NULL);
    res->etiquette = e;
    res->pere = NULL;
    res->sag = g;
    res->sad = d;

    if(g != NULL){
        g->pere = res;
    }

    if (d != NULL){
        d->pere = res;
    }

    return res;
}

void detruit (abr a){
    if (a != NULL){
        detruit(a->sag);
        detruit(a->sad);
        free(a);
    }
}

void affiche_aux(abr a){
    if (a != NULL){
        affiche_aux(a->sag);
        printf(" %d ", a->etiquette);
        affiche_aux(a->sad);
    }
}

void affiche_croissant(abr a){
    affiche_aux(a);
    printf("\n");
}

bool recherche_abr(abr a, int i){
    if (a == NULL){
        return false;
    }
    else if (a->etiquette == i){
        return true;
    }
    else if(a->etiquette > i){
        return recherche_abr(a->sag, i);
    }
    else{
        return recherche_abr(a->sad, i);
    }
}

bool recherche_abr_imprative(abr a, int i){
    abr pt = a;
    while (pt != NULL){
        if(pt->etiquette == i){
            return true;
        }
        else if (pt->etiquette > i){
            pt = pt->sag;
        }
        else{
            pt = pt->sad;
        }
    }
    return false;
}

int minimum_abr(abr a){
    assert(a != NULL);
    abr pt = a;
    while(pt->sag != NULL){
        pt = pt->sag;
    }
    return pt->etiquette;
}



int maximum_abr(abr a){
    assert(a != NULL);
    abr pt = a;
    while(pt->sad != NULL){
        pt = pt->sad;
    }
    return pt->etiquette;
}

// Insertion par effet de bord de l'étiquette e dans l'ABR (*a)
void insertion_abr(abr* a, int e) {
                        
    // si l'arbre était vide, il devient une feuille d'étiquette e
    if (*a == NULL) {
        *a = construit(e, NULL, NULL);
    }
                        
    // si l'insertion de e doit se faire à droite
    else if ((*a)->etiquette < e) {
        // si (*a) n'a pas de sous-arbre droit, on insère ici
        if ((*a)->sad == NULL) {
            abr sad = construit(e, NULL, NULL);
            sad->pere = *a;
            (*a)->sad = sad;
        }
        // sinon on insère récursivement dans le sous-arbre droit
        else {
            insertion_abr(&((*a)->sad), e);
        }
    }
                        
    // si l'insertion de e doit se faire à gauche
    else {
        // si (*a) n'a pas de sous-arbre gauche, on insère ici
        if ((*a)->sag == NULL) {
            abr sag = construit(e, NULL, NULL);
            sag->pere = *a;
            (*a)->sag = sag;
        }
        // sinon on insère récursivement dans le sous-arbre gauche 
        else {
            insertion_abr(&((*a)->sag), e);
        }
    }
}

abr fusion(abr x1, abr x2){
    if (x1 == NULL){
        return x2;
    }
    else if (x2 == NULL){
        return x1;
    }
    else {
        abr d1 = x1->sad;
        abr g2 = x2->sag;

        x1->sad = x2;
        x2->pere = x1;

        x2->sag = fusion(d1, g2);
        x2->sag->pere = x1;

        return x1;
    }
}

abr noeud_a_supprimer(abr a, int e){
    if (a == NULL){
        return NULL;
    }
    else if (a->etiquette == e){
        return a;
    }
    else if(a->etiquette > e){
        return noeud_a_supprimer(a->sag, e);
    }
    else{
        return noeud_a_supprimer(a->sad, e);
    }
}

void suppression_abr_fusion(abr* a, int e){
    assert(a != NULL);
    abr x = noeud_a_supprimer(*a, e);
    abr parent = x->pere;

    abr fus = fusion(x->sag, x->sad);
    if (fus != NULL){
        fus->pere = parent;
    }

    if (parent != NULL){
        if (parent->sag->etiquette == x->etiquette){
            parent->sag = fus;
        }
        else{
            parent->sad = fus; 
        }
    }
    free(x);
}

enum couleur_e{
    rouge,
    noire,
}; typedef enum couleur_e couleur ;

struct noeud_colore_s{
    int etiquette;
    couleur coul;
    struct noeud_colore_s* sag;
    struct noeud_colore_s* sad;
};
typedef struct noeud_colore_s* arn ;

arn construit_arn(int e, couleur c, arn g, arn d){
    arn res = malloc(sizeof(struct noeud_colore_s));
    assert(res != NULL);

    res->etiquette = e;
    res->sag = g;
    res->sad = d;
    res->coul = c;

    return res;
}

void detruit_arn(arn a){
    if (a != NULL){
        detruit_arn(a->sag);
        detruit_arn(a->sad);
        free(a);
    }
}

arn rotation_droite(arn x){
    arn y = x->sag;
    assert(y != NULL);
    x->sag = y->sad;
    y->sad = x;
    return y;
}

arn rotation_gauche(arn y){
    arn x = y->sad;
    assert(y != NULL);
    y->sad = x->sag;
    x->sag = y;
    return x;
}

arn corrige_rouge(arn a){
    if (a->coul == noire){
        if (a->sag != NULL && a->sag->sag != NULL){
            if(a->sag->coul == rouge && a->sag->sag->coul == rouge){
                arn rot_a = rotation_droite(a);
                rot_a->sag->coul = noire;
                return rot_a;
            }
        }
        else if (a->sag != NULL && a->sag->sad != NULL){
            if(a->sag->coul == rouge && a->sag->sad->coul == rouge){
                a->sag = rotation_gauche(a->sag);
                arn rot_a = rotation_droite(a);
                rot_a->sag->coul = noire;
                return rot_a;
            }
        }
        else if (a->sad != NULL && a->sad->sag != NULL){
            if(a->sad->coul == rouge && a->sad->sag->coul == rouge){
                a->sad = rotation_droite(a->sad);
                arn rot_a = rotation_gauche(a);
                rot_a->sad->coul = noire;
                return rot_a;
            }
        }
        else if (a->sad != NULL && a->sad->sad != NULL){
            if(a->sad->coul == rouge && a->sad->sad->coul == rouge){
                arn rot_a = rotation_gauche(a);
                rot_a->sad->coul = noire;
                return rot_a;
            }
        }
    }
    return a;
}

void insertion_arn(arn* a, int e){
                        
    // si l'arbre était vide, il devient une feuille d'étiquette e
    if (*a == NULL) {
        *a = construit_arn(e, noire, NULL, NULL);
    }
                        
    // si l'insertion de e doit se faire à droite
    else if ((*a)->etiquette < e) {
        // si (*a) n'a pas de sous-arbre droit, on insère ici
        if ((*a)->sad == NULL) {
            (*a)->sad = construit_arn(e, rouge,  NULL, NULL);
        }
        // sinon on insère récursivement dans le sous-arbre droit
        else {
            insertion_arn(&((*a)->sad), e);
            corrige_rouge(*a);
        }
    }
                        
    // si l'insertion de e doit se faire à gauche
    else {
        // si (*a) n'a pas de sous-arbre gauche, on insère ici
        if ((*a)->sag == NULL) {
            (*a)->sag = construit_arn(e, rouge,  NULL, NULL);
        }
        // sinon on insère récursivement dans le sous-arbre gauche 
        else {
            insertion_arn(&((*a)->sag), e);
            corrige_rouge(*a);
        }
    }
}


int main() {
    arn un = construit_arn(1, noire, NULL, NULL);
    arn quatre = construit_arn(4, rouge, NULL, NULL);
    arn six = construit_arn(6, rouge, NULL, NULL);
    arn cinq = construit_arn(5, noire, quatre, six);
    arn trois = construit_arn(3, rouge, un, cinq);
    arn onze = construit_arn(11, noire, NULL, NULL);
    arn dix = construit_arn(10, noire, trois, onze); 
    
    detruit_arn(dix);
}