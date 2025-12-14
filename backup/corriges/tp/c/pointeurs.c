/*
CORRIGÉ PARTIEL DU TP : POINTEURS ET GESTION DE LA MÉMOIRE EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

#include "librairies.h"


/* --------------------------------------------------------- */


void produits_successifs_de_30_entiers(void) {
    int produit, entier;
    scanf("%d", &produit);
    for (int i = 1; i < 30; i += 1) {
        scanf("%d", &entier);
        produit *= entier;
        printf("Produit actuel : %d.\n", produit);
    }
}


void produits_successifs_jusque_saisie_de_0(void) {
    int produit, entier;
    scanf("%d", &produit);
    while (produit != 0) {
        scanf("%d", &entier);
        produit *= entier;
        printf("Produit actuel : %d.\n", produit);
    }
}


void echange(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void incr(int* i) {
    *i += 1;
}


int* alloue_t_entiers_1_contigus(int t) {
    int* p = malloc(t * sizeof(int));
    for (int i = 0; i < t; i += 1) {
        *(p + i) = 1;
    }
    return p;
    // il ne faudra pas oublier de free dans le main après appel à cette fonction
}


int division_v1(int a, int b, int* r) {
    *r = a % b;
    return a / b;
}


int* division_v2(int a, int b) {
    int* q_et_r = malloc(2 * sizeof(int));
    *q_et_r = a / b;
    *(q_et_r + 1) = a % b;
    return q_et_r;
}



/* --------------------------------------------------------- */

/* Exercices */


// Exercice 1 :
// Un objet de type t** est un pointeur vers un pointeur vers un objet de type t.
// Donc si p est de type t**, *p est de type t* et **p de type t.


// Exercice 7
void n_sommes_de_p_nombres() {
    int n, p;
    int code_retour;
    code_retour = scanf("%d %d", &n, &p);
    if (code_retour != 2) {
        return ; // permet d'arrêter la fonction si le scanf échoue
    }
    for (int i = 0; i < n; i += 1) {
        double somme = 0.;
        for (int j = 0; j < p; j += 1) {
            double val;
            code_retour = scanf("%lf",&val);
            if (code_retour != 1) {
                return ;
            }
            somme += val;
        }
        printf("%.1f\n", somme);
    }
}

