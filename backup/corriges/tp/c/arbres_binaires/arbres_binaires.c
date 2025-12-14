/*
CORRIGÉ PARTIEL DU TP : ARBRES BINAIRES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include "../librairies.h"
#include "file.h" // le typedef 'contenu_file' a été modifié



// fonction utile pour la suite :

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}



/* --------------------------------------------------------- */

/* Implémentation d'arbres binaires */ 


/*
L'arbre donné en image s'obtient ainsi :
N(10, N(4, N(3, ⊥, ⊥), N(8, N(5, ⊥, ⊥), ⊥)), N(20, N(15, ⊥, ⊥), ⊥))
L'étiquette de sa racine est 10.
Sa taille est 7 et sa hauteur est 3.
Son nombre de feuilles est 3 et de nœuds internes est 4.
La profondeur du nœud d'étiquette 20 est 1, son arité est 1.
La taille du sous-arbre enraciné en le nœud d'étiquette 4 est 4, sa hauteur est 2.
*/


typedef int etiq; // type des étiquettes des nœuds

struct noeud_s {
    etiq etiquette;
    struct noeud_s* gauche;
    struct noeud_s* droit;
};

typedef struct noeud_s* ab; // un arbre binaire est un pointeur vers le nœud à la racine



// interface des arbres binaires non stricts

ab vide(void) {
    return NULL;
}

ab noeud(etiq e, ab sag, ab sad) {
    ab a = malloc(sizeof(struct noeud_s));
    assert(a != NULL);
    a->etiquette = e;
    a->gauche = sag;
    a->droit = sad;
    return a;
}

void libere_ab(ab a) {
    if (a != NULL) {
        libere_ab(a->gauche);
        libere_ab(a->droit);
        free(a);
    }
}

bool est_vide_ab(ab a) {
    return a == NULL;
}

etiq etiq_racine(ab a) {
    assert(!est_vide_ab(a));
    return a->etiquette;
}

ab sous_arbre_gauche(ab a) {
    assert(!est_vide_ab(a));
    return a->gauche;
}

ab sous_arbre_droit(ab a) {
    assert(!est_vide_ab(a));
    return a->droit;
}



// fonctions sur les arbres binaires non stricts

int taille(ab a) {
    if (est_vide_ab(a)) { // T(⊥) = 0
        return 0;
    }
    else { // T(N(e, g, d)) = 1 + T(g) + T(d)
        return 1 + taille(sous_arbre_gauche(a)) + taille(sous_arbre_droit(a));
    }
}

int hauteur(ab a) {
    if (est_vide_ab(a)) { // h(⊥) = -1
        return -1;
    }
    else { // h(N(e, g, d)) = 1 + max(h(g), h(d))
        return 1 + max(hauteur(sous_arbre_gauche(a)), hauteur(sous_arbre_droit(a)));
    }
}

etiq somme(ab a) {
    if (est_vide_ab(a)) { // somme(⊥) = 0
        return 0;
    }
    else { // somme(N(e, g, d)) = e + somme(g) + somme(d)
        return etiq_racine(a) + somme(sous_arbre_gauche(a)) + somme(sous_arbre_droit(a));
    }
}

bool egaux(ab a1, ab a2) {
    // Deux arbres binaires non stricts sont égaux si
    return  (est_vide_ab(a1) && est_vide_ab(a2)) || // ils sont sont tous deux vides, ou bien
            (!est_vide_ab(a1) && !est_vide_ab(a2) && // tous deux non vides
             etiq_racine(a1) == etiq_racine(a2) && // avec la même racine
             egaux(sous_arbre_gauche(a1), sous_arbre_gauche(a2)) && // le même sous-arbre gauche
             egaux(sous_arbre_droit(a1), sous_arbre_droit(a2))); // et le même sous-arbre droit.
}

bool appartient(ab a, etiq e) {
    return  !est_vide_ab(a) &&
            (etiq_racine(a) == e || appartient(sous_arbre_gauche(a), e) || appartient(sous_arbre_droit(a), e));

    /*
    Analyse de la fonction :
    

    - Complexité :
    Soit C(a) le nombre de comparaisons effectuées dans le pire des cas
    pour déterminer si une étiquette est présente dans l'arbre a.

    On a la relation suivante :
    C(⊥) = 0 ;
    C(N(e, g, d)) = 1 + C(g) + C(d).

    On reconnaît ici la fonction inductive de la taille d'un arbre.
    Ainsi C(a) = T(a). La fonction appartient est linéaire en la taille de l'arbre.


    - Correction :
    Montrons par induction structurelle la propriété suivante :
    P(a) = « la fonction appartient termine et est correcte pour l'arbre a et pour toute etiquette e ».

    Assertion.
    ----------
    Si l'arbre est vide, !est_vide(a) donne false donc comme && est un opérateur paresseux
    la fonction appartient termine en renvoyant false.
    Or une étiquette ne peut pas être présente dans un arbre vide.
    Donc P(⊥) est vraie.

    Règle d'inférence.
    ------------------
    Supposons P(g) et P(d) vraies pour deux arbres g et d.
    Soit e une étiquette, et a = N(e, g, d). Montrons P(a).
    Si une étiquette est présente dans a, alors il y a trois cas possibles :
    - il s'agit de l'étiquette de la racine de a;
    - il s'agit de l'étiquette d'un des nœuds de g ;
    - il s'agit de l'étiquette d'un des nœuds de d.
    Or la fonction appartient termine et renvoie bien true dans le premier cas,
    ainsi que dans le deuxième et dans le troisième cas par hypothèse d'induction.
    Et la fonction appartient termine en renvoyant false si aucun des trois cas n'est vrai.
    Donc P(a) est vrai.

    Conclusion.
    -----------
    La propriété est vraie pour l'assertion et reste vraie pour les arbres construits
    par application de la règle d'inférence, ainsi elle est vraie pour tout arbre.
    Donc la fonction est totalement correcte.
    */
}



// interface des arbres binaires stricts

ab feuille(etiq e) {
    ab a = malloc(sizeof(struct noeud_s));
    assert(a != NULL);
    a->etiquette = e;
    a->gauche = NULL;
    a->droit = NULL;
    return a;
}

ab noeud_strict(etiq e, ab sag, ab sad) {
    assert(sag != NULL && sad != NULL);
    ab a = malloc(sizeof(struct noeud_s));
    assert(a != NULL);
    a->etiquette = e;
    a->gauche = sag;
    a->droit = sad;
    return a;
}

bool est_feuille(ab a) {
    return a != NULL && a->gauche == NULL && a->droit == NULL;
    // Remarque : techniquement, on pourrait ne faire que : return a->gauche == NULL;
    // (puisqu'un arbre strict ne peut être construit qu'avec les fonctions 'feuille' et 'noeud_strict')
}



// fonctions sur les arbres binaires stricts

int nombre_de_feuilles(ab a) {
    if (est_feuille(a)) {
        return 1;
    }
    else {
        return nombre_de_feuilles(sous_arbre_gauche(a)) + nombre_de_feuilles(sous_arbre_droit(a));
    }
}

etiq derniere_feuille(ab a) {
    if (est_feuille(a)) {
        return etiq_racine(a);
    }
    else {
        return derniere_feuille(sous_arbre_droit(a));
    }
}

// Les fonctions hauteur et taille écrites plus haut pour les arbres binaires non stricts
// fonctionnent techniquement encore pour les arbres binaires stricts.
// Cependant, le cas de base 'arbre vide' n'a aucun sens pour les arbres stricts.
// On les ré-écrit donc ainsi :
int taille_strict(ab a) {
    if (est_feuille(a)) {
        return 1;
    }
    else {
        return 1 + taille_strict(sous_arbre_gauche(a)) + taille_strict(sous_arbre_droit(a));
    }
}
int hauteur_strict(ab a) {
    if (est_feuille(a)) {
        return 0;
    }
    else {
        return 1 + max(hauteur_strict(sous_arbre_gauche(a)), hauteur_strict(sous_arbre_droit(a)));
    }
}

bool est_strict(ab a) {
    // Dans un arbre binaire strict, on ne peut pas avoir un nœud qui a
    // un de ses deux sous-arbres vide et l'autre non.
    return  !est_vide_ab(a) &&
            ( (est_vide_ab(sous_arbre_gauche(a)) && est_vide_ab(sous_arbre_droit(a))) ||
               (est_strict(sous_arbre_gauche(a)) && est_strict(sous_arbre_droit(a))) );
}



// Décommentez ce main pour faire quelques tests :
/*
int main () {

    // Arbre binaire non strict donné en exemple dans le TP :
    ab ab_ex =  noeud(10,
                    noeud(4,
                        noeud(3, vide(), vide()),
                        noeud(8,
                            noeud(5, vide(), vide()),
                            vide()
                        )
                    ),
                    noeud(20,
                        noeud(15, vide(), vide()),
                        vide()
                    )
                );

    printf("Taille : %d\n", taille(ab_ex));
    printf("Hauteur : %d\n", hauteur(ab_ex));
    printf("Somme : %d\n", somme(ab_ex));
    printf("Appartient (5) : %d\n", appartient(ab_ex, 5));
    printf("Appartient (20) : %d\n", appartient(ab_ex, 20));
    printf("Appartient (3) : %d\n", appartient(ab_ex, 3));
    printf("Appartient (7) : %d\n", appartient(ab_ex, 7));
    printf("Est strict : %d\n", est_strict(ab_ex));

    // Deux arbres non égaux :
    ab ab_1 =   noeud(1,
                    noeud(2, vide(), vide()),
                    vide()
                );
    ab ab_2 =   noeud(1,
                    vide(),
                    noeud(2, vide(), vide())
                );

    printf("Egaux : %d\n", egaux(ab_1, ab_2));
    libere_ab(ab_ex);
    libere_ab(ab_1);
    libere_ab(ab_2);
}
*/



/* --------------------------------------------------------- */

/* Parcours d'arbres binaires */

void profondeur_prefixe(ab a) {
    if (est_feuille(a)) {
        printf("%d ", etiq_racine(a));
    }
    else {
        printf("%d ", etiq_racine(a));
        profondeur_prefixe(sous_arbre_gauche(a));
        profondeur_prefixe(sous_arbre_droit(a));
    }
}

void profondeur_infixe(ab a) {
    if (est_feuille(a)) {
        printf("%d ", etiq_racine(a));
    }
    else {
        profondeur_infixe(sous_arbre_gauche(a));
        printf("%d ", etiq_racine(a));
        profondeur_infixe(sous_arbre_droit(a));
    }
}

void profondeur_postixe(ab a) {
    if (est_feuille(a)) {
        printf("%d ", etiq_racine(a));
    }
    else {
        profondeur_postixe(sous_arbre_gauche(a));
        profondeur_postixe(sous_arbre_droit(a));
        printf("%d ", etiq_racine(a));
    }
}

void largeur(ab a) {
    file f = creer_file();
    enfiler(f, a);
    while (!est_vide_file(f)) {
        a = defiler(f);
        if (est_feuille(a)) {
            printf("%d ", etiq_racine(a));
        }
        else {
            printf("%d ", etiq_racine(a));
            enfiler(f, sous_arbre_gauche(a));
            enfiler(f, sous_arbre_droit(a));
        }
    }
    detruire_file(f);
}



// Décommentez ce main pour faire quelques tests :
/*
int main () {
    // Arbre binaire strict donné en exemple dans le TP :
    ab ab_ex =  noeud_strict(1,
                    noeud_strict(2,
                        feuille(4),
                        noeud_strict(5,
                            feuille(8),
                            feuille(9)
                        )
                    ),
                    noeud_strict(3,
                        feuille(6),
                        feuille(7)
                    )
                );

    profondeur_prefixe(ab_ex); printf("\n");
    profondeur_infixe(ab_ex); printf("\n");
    profondeur_postixe(ab_ex); printf("\n");
    largeur(ab_ex); printf("\n");
    libere_ab(ab_ex);
}
*/



/* --------------------------------------------------------- */

/* Sérialisation d'arbres binaires */


// fonction auxiliaire pour la sérialisation : stocke les étiquettes dans l'ordre préfixe
void serialise_prefixe(ab a, FILE* fichier) {
    if (est_feuille(a)) {
        fprintf(fichier, "0 %d\n", etiq_racine(a)); // un 0 indique qu'il s'agit de l'étiquette d'une feuille
    }
    else {
        fprintf(fichier, "1 %d\n", etiq_racine(a)); // un 1 de celle d'un nœud interne
        serialise_prefixe(sous_arbre_gauche(a), fichier);
        serialise_prefixe(sous_arbre_droit(a), fichier);
    }
}

// fonction principale pour la sérialisation : ouvre le fichier et appelle la fonction auxiliaire
void serialise(ab a, char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    assert(fichier != NULL);
    serialise_prefixe(a, fichier);
    fclose(fichier);
}


// fonction auxiliaire pour la désérialisation
ab reconstruit_arbre_depuis_prefixe(FILE* fichier) {
    int est_feuille, etiquette;
    fscanf(fichier, "%d %d", &est_feuille, &etiquette);
    if (est_feuille == 0) {
        return feuille(etiquette);
    }
    else {
        ab g = reconstruit_arbre_depuis_prefixe(fichier);
        ab d = reconstruit_arbre_depuis_prefixe(fichier);
        return noeud_strict(etiquette, g, d);
    }
}

// fonction principale pour la désérialisation : ouvre le fichier et appelle la fonction auxiliaire
ab deserialise(char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    assert(fichier != NULL);
    ab a = reconstruit_arbre_depuis_prefixe(fichier);
    fclose(fichier);
    return a;
}



// Décommentez ce main pour faire quelques tests :
/*
int main() {
    // Arbre donné en exemple pour la sérialisation :
    ab ab_ex =  noeud_strict(10,
                    noeud_strict(4,
                        feuille(3),
                        noeud_strict(8,
                            feuille(5),
                            feuille(55)
                        )
                    ),
                    noeud_strict(20,
                        feuille(15),
                        feuille(51)
                    )
                );
    
    printf("Nom du fichier pour la sérialisation : ");
    char fichier[1024];
    fscanf(stdin, "%s", fichier);

    serialise(ab_ex, fichier);
    ab ab_ex_deserialise = deserialise(fichier);
    assert(egaux(ab_ex, ab_ex_deserialise));

    libere_ab(ab_ex);
    libere_ab(ab_ex_deserialise);
}
*/
