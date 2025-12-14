/*
CORRIGÉ PARTIEL DU TP : PREMIERS ALGORITHMES DE TRIS (PARTIE EN C)
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

#include "librairies.h"


// fonction d'affichage utile pour les tests dans le main
void affiche_tableau_entiers(int t[], int taille_t) {
    for (int i = 0; i < taille_t - 1; i += 1) {
        printf("%d - ", t[i]);
    }
    printf("%d\n", t[taille_t-1]);
}


/*

    QUESTIONS D'ANALYSE :
    ---------------------

Pour chaque boucle, je donnerai systématiquement dans ce corrigé
les variants et invariants nécessaires aux preuves de terminaison / correction,
qui seront placés juste au dessus des boucles concernées.
Cependant, seules certaines preuves sont intégralement rédigées.
De même, seuls certains calculs de complexité sont rédigés.
Si vous avez un problème pour la rédaction des autres preuves / calculs, n'hésitez pas à me poser vos questions.


    NOTATIONS
    ---------

La notation X_i sert à désigner l'élément d'indice i du tableau X,
et X_{i -> j} sert à désigner la tranche du tableau X entre les indices i et j inclus.

*/


/* --------------------------------------------------------- */

/* Algorithmes de tris */


// fonction qui échange les éléments d'indices i et j de t (utile pour la suite)
// complexité : O(1)
void echange(int t[], int i, int j) {
    int tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
}


/* Tri par sélection */

// fonction qui renvoie l'indice du minimum de t_{debut -> fin}
// complexité : O(fin-debut)
int indice_minimum(int t[], int debut, int fin) {
    int i_mini = debut;
    // Variant : fin - i
    // Inv(i, i_mini) : i_mini = indice du minimum de t_{debut -> i-1}
    for (int i = debut + 1; i <= fin; i += 1) {
        if (t[i_mini] > t[i]) {
            i_mini = i;
        }
    }
    return i_mini;
}

// complexité : O(taille_tab²)
void tri_selection_en_place(int tab[], int taille_tab) {
    // Variant : taille_tab - i
    // Inv(i) : tab_{0 -> i-1} est trié et contient les i plus petits éléments de tab
    for (int i = 0; i < taille_tab; i += 1) {
        echange(tab, i, indice_minimum(tab, i, taille_tab - 1));
    }
}


/* Tri à bulles */

// complexité : O(taille_tab²)
void tri_a_bulles(int tab[], int taille_tab) {
    // Variant : i
    // Inv(i) : tab_{i+1 -> taille_tab-1} est trié et contient les plus grands éléments de tab
    for (int i = taille_tab - 1; i > 0; i -= 1) {
        // Variant : i - j
        // Inv(j) : le maximum de tab_{0 -> j-1} se situe à l'indice j-1
        for (int j = 0; j < i; j += 1) {
            if (tab[j] > tab[j+1]) {
                echange(tab, j, j+1);
            }
        }
    }
}


/* Tri par insertion */

// complexité : O(taille_tab²) ; Ω(taille_tab)
void tri_insertion(int tab[], int taille_tab) {
    // Variant : taille_tab - i
    // Inv(i) : tab_(0 -> i-1) est trié
    for (int i = 1; i < taille_tab; i += 1) {
        int j = i;
        // Variant : j
        // Inv(j) : tab_j < tous les éléments de tab entre j+1 et i
        while (j > 0 && tab[j] < tab[j-1]) {
            echange(tab, j, j-1);
            j -= 1;
        }
    }
}


/* --------------------------------------------------------- */

/* Inclusion d'ensembles */


/* Réponse au problème sans trier */

bool inclusion_v1(int E[], int taille_E, int F[], int taille_F) {
    bool res = true;
    for (int i = 0; i < taille_E; i += 1) {
        bool est_present = false;
        for (int j = 0; j < taille_F; j += 1) {
            est_present = est_present || (E[i] == F[j]);
        }
        res = res && est_present;
    }
    return res;
}

/*
        ----------------------------------------
        | ANALYSE DE LA FONCTION inclusion_v1. |
        ----------------------------------------

TERMINAISON ET CORRECTION DE LA BOUCLE "INTERNE".
-------------------------------------------------

Terminaison de la boucle interne.
Montrons que taille_F - j est un variant de boucle.
*   Avant la boucle, j = 0, et taille_F > 0 de par les préconditions, donc taille_F - j est positif.
*   Tant que la condition de boucle est vérifiée :
    j < taille_F de par la condition de boucle donc taille_F - j est positif.
*   En notant j' et taille_F' les valeurs respectives de j et taille_F à la fin d'une itération,
    on a j' = j + 1 et taille_F' = taille_F donc taille_F' - j' = taille_F - (j+1) < taille_F - j.
    Le variant est donc strictement décroissant.
Ainsi taille_F - j est un variant pour la boucle, et comme toutes les instructions
du corps de la boucle terminent, la boucle termine.

Correction de la boucle interne.
Montrons que « est_present = (E_i ∈ F_{0 -> j-1}) », noté Inv(j, est_present), est invariant de boucle.
*   Avant la boucle, j = 0 et est_present = false, or F_{0 -> j-1} est vide
    donc E_i n'appartient pas à F_{0 -> j-1}.
*   Supposons l'invariant vrai au début d'une itération : on a Inv(j, est_present).
    Montrons alors Inv(j', est_present') avec j' et est_present' les valeurs respectives de j et est_present à la fin de l'itération.
    j' = j + 1, et
    est_present' = est_present || (E_i = F_j)
                 = (E_i ∈ F_{0 -> j-1}) || (E_i = F_j) car on a supposé Inv(j, est_present) vrai
                 = E_i ∈ F_{0 -> j}
                 = E_i ∈ F_{0 -> j'-1}
    Donc si l'invariant est vrai au début d'une itération, il est toujours vrai en fin d'itération.
*   À la sortie de la boucle, on a j = taille_F donc l'invariant nous donne
    est_present = (E_i ∈ F_{0 -> taille_F-1}) = E_i ∈ F.


TERMINAISON ET CORRECTION DE LA BOUCLE "EXTERNE".
-------------------------------------------------

Terminaison de la boucle externe.
Montrons que taille_E - i est un variant de boucle.
*   Avant la boucle, i = 0, et taille_E > 0 de par les préconditions, donc taille_E - i est positif.
*   Tant que la condition de boucle est vérifiée :
    i < taille_E de par la condition de boucle donc taille_E - i est positif.
*   En notant i' et taille_E' les valeurs respectives de i et taille_E à la fin d'une itération,
    on a i' = i + 1 et taille_E' = taille_E donc taille_E' - i' = taille_E - (i+1) < taille_E - i.
    Le variant est donc strictement décroissant.
Ainsi taille_E - i est un variant pour la boucle, et comme toutes les instructions
du corps de la boucle terminent, la boucle termine.

Correction de la boucle externe.
Montrons que « res = (E_{0 -> i-1} ⊂ F) », noté Inv(i, res), est un invariant pour la boucle.
*   Avant la boucle, i = 0 et res = true, or E_{0 -> i-1} est vide
    donc tous ses éléments (puisqu'il y en a aucun) sont bien inclus dans F.
*   Supposons l'invariant vrai au début d'une itération : on a Inv(i, res).
    Montrons alors Inv(i', res') avec i' et res' les valeurs respectives de i et res à la fin de l'itération.
    i' = i + 1, et
    res' = res && est_present
         = res && (E_i ∈ F) de par l'invariant de la boucle interne.
         = (E_{0 -> i-1} ⊂ F) && (E_i ∈ F) car on a supposé Inv(i, res) vrai
         = E_{0 -> i} ⊂ F
         = E_{0 -> i'-1} ⊂ F
    Donc si l'invariant est vrai au début d'une itération, il est toujours vrai en fin d'itération.
*   À la sortie de la boucle, on a i = taille_E donc l'invariant nous donne
    res = (E_{0 -> taille_E-1} ⊂ F) = E ⊂ F.


CORRECTION DE LA FONCTION.
--------------------------

On a montré la correction totale des deux boucles,
les autres instructions sont totalement correctes trivialement,
et la fonction renvoie res qui indique si E ⊂ F de par l'invariant de la boucle externe,
donc la fonction est totalement correcte.


COMPLEXITÉ TEMPORELLE.
----------------------

C(taille_E, taille_F)
=
    O(1) +                                              // complexité des instructions avant les boucles
    somme de {i=0} jusque {taille_E-1} de (             // nombre d'itérations de la boucle externe
        somme de {j=0} jusque {taille_F-1} de (         // nombre d'itérations de la boucle interne
            O(1)                                        // complexité du corps de la boucle
        )
    ) +
    O(1)                                                // complexité des instructions après les boucles
=
    somme de {i=0} jusque {taille_E-1} de (
        O(taille_F)
    )

=
    O(taille_E × taille_F)

Remarque : il s'agit ici aussi de la complexité dans le meilleur des cas et le cas moyen
           puisqu'elle est toujours identique      
*/

bool inclusion_simple_v2(int E[], int taille_E, int F[], int taille_F) {
    bool res = true;
    for (int i = 0; i < taille_E; i += 1) {
        bool est_present = false;
        int j = 0;
        while (j < taille_F && !est_present) {
            est_present = est_present || (E[i] == F[j]);
            j += 1;
        }
        res = res && est_present;;
    }
    return res;
}

bool inclusion_simple_v3(int E[], int taille_E, int F[], int taille_F) {
    bool res = true;
    int i = 0;
    while (i < taille_E && res) {
        bool est_present = false;
        int j = 0;
        while (j < taille_F && !est_present) {
            est_present = est_present || (E[i] == F[j]);
            j += 1;
        }
        res = res && est_present;;
        i += 1;
    }
    return res;
}

/*
Les preuves de terminaison et correction pour inclusion_v2 et inclusion_v3 sont similaires à celles de inclusion_v1.
Le calcul de la complexité dans le pire des cas ne change pas non plus.
La différence d'efficacité entre ces trois versions tient dans le calcul du meilleur des cas :
inclusion_v1 est moins efficace que inclusion_v2 qui est elle-même moins efficace que inclusion_v3
(puisque inclusion_v2 permet éventuellement de réaliser moins d'itérations de la boucle interne,
et inclusion_v3 permet éventuellement de réaliser moins d'itérations des deux boucles).
*/


/* Réponse au problème en triant */

// complexité : O(taille_F² + taille_E × taille_F)
bool inclusion_tri_f(int E[], int taille_E, int F[], int taille_F) {
    tri_insertion(F, taille_F);
    bool res = true;
    for (int i = 0; i < taille_E; i += 1) {
        int j = 0;
        while (j < taille_F && E[i] > F[j]) {
            j += 1;
        }
        res = res && (j != taille_F && E[i] == F[j]);
    }
    return res;
}

// complexité : O(log(taille_tab))
bool recherche_dichotomique(int tab[], int taille_tab, int elt) {
    int debut = 0, fin = taille_tab - 1;
    // Variant : fin - debut
    // Inv(debut, fin) : (elt ∈ tab) <=> (elt ∈ tab_{debut -> fin})
    while (debut <= fin) {
        int milieu = (debut + fin) / 2;
        if (elt == tab[milieu]) {
            return true;
        }
        else if (elt < tab[milieu]) {
            fin = milieu - 1;
        }
        else {
            debut = milieu + 1;
        }
    }
    return false;
}

// complexité : O(taille_F² + taille_E × log(taille_F))
bool inclusion_tri_f_dichotomique(int E[], int taille_E, int F[], int taille_F) {
    tri_insertion(F, taille_F);
    for (int i = 0; i < taille_E; i += 1) {
        if (!recherche_dichotomique(F, taille_F, E[i])) {
            return false;
        }
    }
    return true;
}

// complexité : O(taille_F² + taille_E² + min(taille_F, taille_E))
bool inclusion_tris_ef(int E[], int taille_E, int F[], int taille_F) {
    tri_insertion(F, taille_F);
    tri_insertion(E, taille_E);
    int ind_e = 0, ind_f = 0; // ind_e désigne l'indice courant dans E, ind_f l'indice courant dans F
    // Variant : taille_E + taille_F - (ind_e + ind_f)
    // Inv(ind_e, ind_f) : E_{0 -> ind_e-1} ⊂ F et F_{ind_f-1} <= tous les éléments de E_{0 -> ind_e-1}
    while (ind_e < taille_E && ind_f < taille_F && E[ind_e] >= F[ind_f]) {
        // on a trouvé l'élément, on passe aux suivants
        if (E[ind_e] == F[ind_f]) {
            ind_e += 1;
            ind_f += 1;
        }
        // l'élément est supérieur à celui actuel dans f, on regarde donc dans la suite
        else {
            ind_f += 1;
        }
    }
    return ind_e == taille_E;
}

/*
En supposant avoir un tri en O(n log(n)) avec n la taille du tableau,
on arrive à un algorithme quasi-linéaire pour résoudre le problème d'inclusion.
*/
