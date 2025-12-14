/*
CORRIGÉ PARTIEL DU TP : BASES DU C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

#include "librairies.h"


/* --------------------------------------------------------- */

/* FONCTIONS DU II. STRUCTURES DE CONTROLE */


// afficher proprement la valeur d'un booléen
void affiche_bool(bool b) {
    if (b) {
        printf("vrai");
    }
    else {
        printf("faux");
    }
}

// déterminer si un entier est pair/impair + indiquer s'il est nul
void est_pair(int n) {
    if (n % 2 == 0) {
        printf("L'entier %d est pair.\n", n);
    }
    else {
        printf("L'entier %d est impair.\n", n);
    }
    if (n == 0) {
        printf("De plus, il est nul.\n");    
    }
}

// déterminer à partir de quel entier n, le produit des entiers allant de 1 à n dépasse le seuil
int depasse_seuil(int seuil) {
    int i = 1;
    int produit = 1;
    while (produit <= seuil) {
        i += 1;
        produit *= i;
    }
    return i;
}

// renvoie la somme des entiers allant de 0 à n
int somme(int n) {
    int res = 0;
    for (int i = 0; i <= n; i += 1) {
        res += i;
    }
    return res;
}

// affiche entiers de m à n avec un for(;;)
void affiche_de_m_a_n(int m, int n) {
    if (m <= n) { // si m > n, il n'y a rien à afficher
        int i = m;
        for (;;) {
            printf("%d\n", i);
            i += 1;
            if (i > n) { // permet de sortir de la boucle quand on a atteint n
                break;
            }
        }
    }
    // CE GENRE DE CODE EST UNE TRES MAUVAISE PRATIQUE, IL EST COMPLETEMENT ILLISIBLE.
    // SI VOUS ÊTES AMENÉS À ÉCRIRE DU CODE AVEC UN « for (;;) », 
    // C'EST QUE VOTRE PROGRAMME EST MAL CONÇU.
}


/*---------------------------------------------------------*/

/* FONCTIONS DU III. EXERCICES */


// Quelques conditionnelles

void affiche_saison(int jour, int mois) {
    if ((mois == 12 && jour >= 21) || (mois == 1) || (mois == 2) || (mois == 3 && jour < 21)) {
        printf("Hiver.\n");
    } else if ((mois == 3 && jour >= 21) || (mois == 4) || (mois == 5) || (mois == 6 && jour < 21)) {
        printf("Printemps.\n");
    } else if ((mois == 6 && jour >= 21) || (mois == 7) || (mois == 8) || (mois == 9 && jour < 21)) {
        printf("Été.\n");
    } else {
        printf("Automne.\n");
    }
}

bool bissextile(int annee) {
    return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

bool date_valide(int jour, int mois, int annee) {
    if (mois < 1 || mois > 12 || jour < 1 ) {
        return false;
    }
    // mois avec 31 jours
    if (jour > 31 && (mois == 1 || mois == 3 || mois == 5 || mois == 7 || mois == 8 || mois == 10 || mois == 12)) {
        return false;
    }
    // mois avec 30 jours
    else if (jour > 30 && (mois == 4 || mois == 6 || mois == 9 || mois == 11)) {
        return false;
    }
    // février
    else if (mois == 2 && ((jour > 29 && bissextile(annee)) || (jour > 28 && !bissextile(annee)))) {
        return false;
    }
    return true;
}


// Quelques boucles

int factorielle(int n) {
    int res = 1;
    for (int i = 1; i <= n; i += 1) {
        res *= n;
    }
    return res;
}

int n_puissance_p(int n, int p) {
    int res = 1;
    for (int i = 0; i < p; i += 1) {
        res *= n;
    }
    return n;
}

int est_premier(int p) {
    for (int diviseur_potentiel = 2; diviseur_potentiel < p; diviseur_potentiel += 1) {
        if (p % diviseur_potentiel == 0) {
            return false;
        }
    }
    return true;
}

int plus_petit_k_tel_que_2_puissance_k_est_superieur_ou_egal_a_n(int n) {
    int k = 0;
    int deux_puissance_k = 1;
    while (deux_puissance_k < n) {
        k += 1;
        deux_puissance_k *= 2;
    }
    return k;
}


// Sommes

int somme1(int n) {
    int res = 0;
    for (int k = 1; k <= n; k +=1) {
        res += 2*k+1;
    }
    return res;
}

double somme2(int n) {
    double res = 0.0;
    for (int k = 1; k <= n; k +=1) {
        res += 1.0 / (k*k);
    }
    return res;
}

int somme3(int n) {
    int res = 0;
    for (int i = 1; i <= n; i +=1) {
        for (int j = 1; j <= n; j += 1) {
            res += i+j;
        }
    }
    return res;
}

int somme4(int n) {
    int res = 0;
    for (int i = 1; i <= n; i +=1) {
        for (int j = i; j <= n; j += 1) {
            res += i+j;
        }
    }
    return res;
}

int somme5(int n) {
    int res = 0;
    for (int i = 1; i <= n; i +=1) {
        for (int j = 1; j < i; j += 1) {
            res += i+j;
        }
    }
    return res;
}

/*
// Tests pour les sommes (à faire dans le main) :
for (int i = 0; i < 4; i += 1) {
    printf("S1(%d) = %d\n", i, somme1(i));
    printf("S2(%d) = %f\n", i, somme2(i));
    printf("S3(%d) = %d\n", i, somme3(i));
    printf("S4(%d) = %d\n", i, somme4(i));
    printf("S5(%d) = %d\n", i, somme5(i));
}
*/


// Petits affichages

int multiples_de_3_entre_1_et_100(void) {
    int nombre_multiples = 0;
    for (int i = 3; i <= 100; i += 3) {
        printf("%d\n", i);
        nombre_multiples += 1;
    }
    return nombre_multiples;
}

void compte_a_rebours_100_a_0(void) {
    for (int i = 100; i >= 0; i -= 1) {
        printf("%d\n", i);
    }
}

void table_multiplications_jusque_10(void) {
    for (int i = 1; i <= 10; i += 1) {
        for (int j = 1; j <= 10; j += 1) {
            printf("%d x %d = %d\n", i, j, i*j);
        }
        printf("\n");
    }
}

void ligne_n_caracteres_c(int n, char c) {
    for (int i = 0; i < n; i += 1) {
        printf("%c", c);
    }
    printf("\n");
}

void rectangle_m_lignes_n_colonnes(int n, int m, char c) {
    for (int j = 0; j < m; j += 1) {
        for (int i = 0; i < n; i += 1) {
            printf("%c", c);
        }
        printf("\n");
    }
}

void rectangle_creux_m_lignes_n_colonnes(int n, int m, char c) {
    for (int j = 0; j < m; j += 1) {
        // la première et dernière ligne doivent être pleines
        if (j == 0 || j == m-1) {
            for (int i = 0; i < n; i += 1) {
                printf("%c", c);
            }
        }
        // pour les autres lignes, on met des espaces au milieu
        else {
            printf("%c", c);
            for (int i = 0; i < n-2; i += 1) {
                printf(" ");
            }
            printf("%c", c);
        }
        printf("\n");
    }
}
