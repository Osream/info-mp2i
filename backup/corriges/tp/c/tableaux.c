/*
CORRIGÉ PARTIEL DU TP : TABLEAUX EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

#include "librairies.h"



/* --------------------------------------------------------- */

/* Fonctions du fichier tableaux.c */


void affiche_tableau(int tab[], int taille) {
    for (int i = 0; i < taille ; i += 1) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void initialise_0(int tab[], int taille) {
    for (int i = 0; i < taille ; i += 1) {
        tab[i] = 0;
    }
}

int* cree_n_x(int n, int x) {
    int* t = malloc(n * sizeof(int));
    for (int i = 0; i < n; i += 1) {
        t[i] = x;
    }
    return t;
}

int** cree_tableau_dynamique_bidimensionnel(int nb_lignes, int nb_colonnes, int val) {
    int** t = malloc(nb_lignes * sizeof(int*));
    for (int i = 0; i < nb_lignes; i += 1) {
        t[i] = malloc(nb_colonnes * sizeof(int));
        for (int j = 0; j < nb_colonnes; j += 1) {
            t[i][j] = val;
        }
    }
    return t;
}

int* linearise(int** t, int nb_lignes, int nb_colonnes) {
    int* res = malloc(nb_colonnes * nb_lignes * sizeof(int));
    for (int i = 0; i < nb_lignes; i += 1) {
        for (int j = 0; j < nb_colonnes; j+= 1) {
            res[i * nb_colonnes + j] = t[i][j];
        }
    }
    return res;
}

int** delinearise(int* t, int nb_lignes, int nb_colonnes) {
    int** res = malloc(nb_lignes * sizeof(int* ));
    for (int i = 0; i < nb_lignes; i += 1) {
        res[i] = malloc(nb_colonnes * sizeof(int));
        for (int j = 0; j < nb_colonnes; j += 1) {
            res[i][j] = t[i * nb_colonnes + j];
        }
    }
    return res;
}



/* --------------------------------------------------------- */

/* Fonctions du fichier algorithmique_tableaux.c */


// 1. algorithmes simples

int somme (int t[], int taille) {
    int s = 0;
    for (int i = 0; i < taille; i += 1) {
        s += t[i]; // additionne chaque valeur du tableau
    }
    return s;
}

int nombre_occurrences(int t[], int taille, int val) {
    int res = 0;
    for (int i = 0; i < taille; i += 1) {
        if (t[i] == val) {
            res += 1; // on a trouvé la valeur une fois de plus
        }
    }
    return res;
}

int premier_indice(int t[], int taille, int valeur_cherchee) {
    for (int i = 0; i < taille; i += 1) {
        if (t[i] == valeur_cherchee) {
            return i; // on renvoie l'indice dès qu'on trouve la valeur
        }
    }
    return -1; // non trouvé
}

int dernier_indice_v1(int t[], int taille, int valeur_cherchee) {
    // on parcourt du début à la fin en gardant en mémoire
    // le dernier indice où on a croisé la valeur cherchée
    int indice = -1;
    for (int i = 0; i < taille; i += 1) {
        if (t[i] == valeur_cherchee) {
            indice = i;
        }
    }
    return indice;
}

int dernier_indice_v2(int t[], int taille, int valeur_cherchee) {
    // on parcourt en partant de la fin du tableau
    for (int i = taille - 1; i >= 0; i -= 1) {
        if (t[i] == valeur_cherchee) {
            return i; // on s'arrête dès qu'on a trouvé
        }
    }
    return -1; // non trouvé
}

int minimum_et_maximum (int t[], int taille, int* maxi) {
    int mini = t[0]; // par défaut le minimum/maximum est la première valeur
    *maxi = t[0];
    for (int i = 1; i < taille; i += 1) {
        if (t[i] < mini) { // si on trouve une valeur plus petite
            mini = t[i]; // cela devient notre nouveau minimum
        }
        if (t[i] > *maxi) {
            *maxi = t[i];
        }
    }
    return mini;
}

int indice_maximum (int t[], int taille) {
    int i_maxi = 0; // on conserve l'indice cette fois, plus la valeur
    for (int i = 1; i < taille; i += 1) {
        if (t[i] > t[i_maxi]) {
            i_maxi = i;
        }
    }
  return i_maxi;
}

int est_croissant(int t[], int taille) {
    for (int i = 1; i < taille; i += 1) {
        if (t[i] < t[i-1]) {
            return false; // on a trouvé 2 valeurs consécutives non correctement ordonnées
        }
    }
    return true;
}


// 2. copie de tableaux

void copie_tableau(int tab_original[], int tab_copie[], int taille) {
    for (int i = 0; i < taille; i += 1) {
        tab_copie[i] = tab_original[i];
    }
}

int* copie(int tab[], int n) {
    int* tab_copie = malloc(n * sizeof(int));
    for (int i = 0; i < n; i += 1) {
        tab_copie[i] = tab[i];
    }
    return tab_copie;
}

int** copie_tableau_bidimensionnel(int** tab, int nb_lignes, int nb_colonnes) {
    int** tab_copie = malloc(nb_lignes * sizeof(int*));
    for (int i = 0; i < nb_lignes; i += 1) {
        tab_copie[i] = malloc(nb_colonnes * sizeof(int));
        for (int j = 0; j < nb_colonnes; j += 1) {
            tab_copie[i][j] = tab[i][j];
        }
    }
    return tab_copie;
}


// 3. initialisation de tableaux statiques

void initialise_croissant(int tab[], int taille) {
    for (int i = 0; i < taille ; i += 1) {
        tab[i] = i;
    }
}

void initialise_decroissant(int tab[], int taille) {
    for (int i = 0; i < taille ; i += 1) {
        tab[i] = taille - 1 - i;
    }
}

void initialise_lecture(int tab[], int taille) {
    int valeur_pour_initialisation;
    scanf("%d", &valeur_pour_initialisation);
    for (int i = 0; i < taille ; i += 1) {
        tab[i] = valeur_pour_initialisation;
    }
}

void initialise_aleatoire(int tab[], int taille) {
    for (int i = 0; i < taille ; i += 1) {
        tab[i] = rand() % taille;
    }
}


// 4. renvoi de tableaux dynamiques

double* premiers_termes(double u0, double a, double b, int n) {
    double* t = malloc(n * sizeof(double));
    for (int i = 0; i < n; i += 1) {
        t[i] = u0;
        u0 = a * u0 + b;
    }
    return t;
}

int* cree_tableau_taille_et_valeur_lues(int* taille) {
    // on passe en paramètre un pointeur vers la taille
    // pour qu'après l'appel à la fonction
    // on puisse connaître la taille du tableau renvoyé
    printf("Entrez la valeur puis la taille :\n");
    int valeur_pour_initialisation;
    scanf("%d", &valeur_pour_initialisation);
    scanf("%d", taille);
    int* t = malloc(*taille * sizeof(int));
    for (int i = 0; i < *taille ; i += 1) {
        t[i] = valeur_pour_initialisation;
    }
    return t;
}

int* cree_tableau_taille_et_valeur_lues_une_par_une(int* taille) {
    printf("Entrez la taille puis les valeurs :\n");
    scanf("%d", taille);
    int* t = malloc(*taille * sizeof(int));
    for (int i = 0; i < *taille ; i += 1) {
        int valeur_pour_initialisation;
        scanf("%d", &valeur_pour_initialisation);
        t[i] = valeur_pour_initialisation;
    }
    return t;
}


// 5. triangle de pascal

int* prochaine_ligne(int t[], int n) {
    int* t_suivant = malloc((n+1) * sizeof(int));
    t_suivant[0] = t_suivant[n] = 1;
    for (int i = 1; i < n; i += 1) {
        t_suivant[i] = t[i-1] + t[i];
    }
    return t_suivant;
}

int** triangle_de_pascal(int n) {
    int* t0 = malloc(sizeof(int));
    t0[0] = 1;
    int** triangle = malloc(n * sizeof(int*));
    triangle[0] = t0;
    for (int i = 1; i < n; i += 1) {
        triangle[i] = prochaine_ligne(triangle[i-1], i);
    }
    return triangle;
}