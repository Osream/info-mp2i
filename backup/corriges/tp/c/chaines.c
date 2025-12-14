/*
CORRIGÉ PARTIEL DU TP : CHAÎNES DE CARACTÈRES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

#include "librairies.h"
#include <string.h>



/* --------------------------------------------------------- */

/* Fonctions du fichier chaines.c */


// strlen
int taille_chaine(char chaine[]) {
    int i = 0;
    while (chaine[i] != '\0') {
        i += 1;
    }
    return i;
}

// strcpy
void copie_chaine(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    dest[i] = '\0'; // ne pas oublier de fermer la chaîne par une sentinelle
}

// strcat
void concatene_chaine(char dest[], char src[]) {
    int i = taille_chaine(dest);
    int j = 0;
    while (src[j] != '\0') {
        dest[i + j] = src[j];
        j += 1;
    }
    dest[i + j] = '\0';
}

// strcmp
int compare_chaine(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && s1[i] == s2[i]) {
        i += 1;
    }
    return (int)s1[i] - (int)s2[i];
}

// affiche les chaînes du tableau t séparées par des espaces
void affiche_tab_de_chaines(char* t[], int taille_t) {
    for (int i = 0; i < taille_t; i += 1) {
        printf("%s ", t[i]);
    }
    printf("\n");
}

// somme des tailles des chaînes du tableau t
int taille_totale(char* t[], int taille_t) {
    int res = 0;
    for (int i = 0; i < taille_t; i += 1) {
        res += strlen(t[i]);
    }
    return res;
}

// tableau contenant une fois sur 2 "OCaml" et une fois sur 2 "C"
char** tab_langages(int taille) {
    char** t = malloc(taille * sizeof(char*));
    for (int i = 0; i < taille; i += 1) {
        if (i % 2 == 0) {
            t[i] = "C"; 
        }
        else {
            t[i] = "OCaml";
        }
    }
    return t;
}



/* --------------------------------------------------------- */

/* Fonctions du fichier chaines_manip.c */


// 1. parcours de chaînes

void affiche_chaine_un_caractere_par_ligne(char s[]) {
    for (int i = 0; s[i] != '\0'; i += 1) {
        printf("%c\n", s[i]);
    }
}

void renverse_chaine(char sortie[], char entree[]) {
    int taille = taille_chaine(entree);
    for (int i = 0; i < taille; i += 1) {
        sortie[i] = entree[taille - 1 - i];
    }
    sortie[taille] = '\0';
}

bool palindrome(char chaine[]) {
    char* renversee = malloc((taille_chaine(chaine) + 1) * sizeof(char)); // + 1 pour le caractère nul
    renverse_chaine(renversee, chaine);
    int comparaison = compare_chaine(chaine, renversee);
    free(renversee); // attention aux fuites de mémoire
    return comparaison == 0;
}

void echange_2a2(char chaine[]) {
    for (int i = 0; chaine[i] != '\0' && chaine[i+1] != '\0'; i += 2) {
        char tmp = chaine[i];
        chaine[i] = chaine[i+1];
        chaine[i+1] = tmp;
    }
}


// 2. renvoi de chaînes

char* couleur(int r, int g, int b) {
    if ((r+g+b) / 3 < 128) {
        return "noir";
    }
    else {
        return "blanc";
    }
}

char* renverse(char chaine[]) {
    int taille = strlen(chaine);
    char* res = malloc((taille + 1)* sizeof(char)); // + 1 pour le caractère nul
    for (int i = 0; i < taille; i += 1) {
        res[i] = chaine[taille - 1 - i];
    }
    res[taille] = '\0';
    return res;
}

char* lit_chaine() {
    int taille;
    scanf("%d", &taille);
    char* c = malloc(taille * sizeof(char));
    scanf("%s", c);
    return c;
}

char* mot_bienvenue() {
    char texte[] = ", bienvenue au TP sur les chaînes de caractères ! J'espère que tu apprendras beaucoup de choses.";
    int taille = strlen(texte) + 1;
    char* nom = malloc((20 + taille) * sizeof(char));
    scanf("%s", nom);
    strcat(nom, texte);
    return nom;
}


// 3. code César

char* encode(char message[], int i) {
    int taille = strlen(message) + 1; // ne pas oublier la sentinelle
    char* res = malloc(taille * sizeof(char));
    for (int l = 0; l < taille; l += 1) {
        int nouveau = (int)message[l] + i; // décalage en utilsant le code ASCII
        if ('a' <= message[l] && message[l] <= 'z') { // minuscules
            if (nouveau > (int)'z') {
                nouveau -= 26;
            }
            res[l] = (char)nouveau;
        }
        else if ('A' <= message[l] && message[l] <= 'Z') { // majuscules
            if (nouveau > (int)'Z') {
                nouveau -= 26;
            }
            res[l] = (char)nouveau;
        }
        else { // autres caractères
            res[l] = message[l];
        }
    }
    return res;
}


// 4. recherche de motifs

bool est_fact_gauche(char s1[], char s2[]) {
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i += 1) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

bool est_fact(char s1[], char s2[]) {
    int t1 = strlen(s1), t2 = strlen(s2);
    int i, j;
    for (i = 0; i <= t2 - t1; i += 1) { // i désigne l'indice de chaque lettre de s2 pouvant commencer un facteur
        for (j = 0; j < t1; j += 1) {
            if (s1[j] != s2[i+j]) { // si on rencontre une lettre différente, ce n'est pas un facteur
                break;
            }
        }
        if (j == t1) { // si on a tout parcouru, on a trouvé s1 dans s2
            return true;
        }
    }
    return false;
}


// 5. un langage

bool appartient(char mot[], char** langage, int taille) {
    for (int i = 0; i < taille; i += 1) {
        if (strcmp(langage[i], mot) == 0) {
            return true;
        }
    }
    return false;
}

char** ajoute(char mot[], char** langage, int taille) {
    if (appartient(mot, langage, taille)) {
        return langage; // si le mot appartient déjà au langage on n'a rien à faire
    }
    char** res = malloc((taille + 1) * sizeof(char*));
    int i;
    for (i = 0; i < taille; i += 1) {
        res[i] = langage[i];
    }
    res[i] = mot;
    return res;
}

bool verifie(char** langage, int taille) {
    for (int i = 0; i < taille - 1; i += 1) {
        for (int j = i+1; j < taille; j += 1) {
            if (strcmp(langage[i], langage[j]) == 0) {
                return false;
            }
        }
    }
    return true;
}
