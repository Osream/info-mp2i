/*
CORRIGÉ PARTIEL DU TP : LIGNE DE COMMANDE ET DÉCLARATION DE TYPES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* --------------------------------------------------------- */

#include "librairies.h"
#include <string.h>
#include <math.h>


/* --------------------------------------------------------- */

/* LIGNE DE COMMANDE */


// programme qui prend en arguments un entier et un réel et affiche leur somme :

/*
int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Mauvais arguments, on attend : %s entier réél\n", argv[0]);
        return 1; // pour signaler l'erreur
    }
    int entier_recupere = atoi(argv[1]);
    double reel_recupere = atof(argv[2]);
    printf("La somme des deux arguments est %f.\n", (double)entier_recupere + reel_recupere);
}
*/


/* --------------------------------------------------------- */

/* DÉCLARATION DE TYPES : ALIAS */


// grands entiers

typedef int64_t grand_entier;


// réels

typedef double reel; // ligne à placer dans le .h pour pouvoir utiliser le type "reel" depuis d'autres fichiers

reel produit_reels(reel a, reel b) {
    return a * b;
}



/* --------------------------------------------------------- */

/* DÉCLARATION DE TYPES ÉNUMÉRÉS */


enum booleen_e {faux, vrai}; // le _e à la fin du nom est optionnel mais vivement conseillé
typedef enum booleen_e booleen;

void affiche_booleen(booleen b) {
    if (b == vrai) {
        printf("Vrai.\n");
    }
    else {
        printf("Faux.\n");
    }
}

booleen est_pair(int n) {
    if (n % 2 == 0) {
        return vrai;
    }
    else {
        return faux;
    }
}


/* --------------------------------------------------------- */

/* DÉCLARATION DE TYPES STRUCTURÉS */


// déclaration du type couleur et de l'alias associé

struct couleur_s { // le _s à la fin du nom est optionnel mais très fortement recommandé
    double rouge;
    double bleu;
    double jaune;
};

typedef struct couleur_s couleur; // (à placer dans le .h si on veut s'en servir depuis d'autres fichiers)


// main qui crée une couleur depuis 3 flottants donnés en argument

/*
int main(int argc, char* argv[]) {
    // création de couleurs orange, bleu et vert
    couleur orange = {.rouge = 50., .jaune = 50., .bleu = 0};
    couleur bleu = {0., 100., 0.};
    couleur vert;
    vert.rouge = 0.;
    vert.jaune = 50.;
    vert.bleu = 50.;

    // prend en arguments 3 flottants et crée la couleur correspondante
    if (argc != 4) {
        // on vérifie que l'utilisateur donne bien 3 arguments
        printf("Mauvais arguments, on attend : %s réel_jaune réel_bleu réel_rouge\n", argv[0]);
        return 1;
    }
    double taux_jaune = atof(argv[1]), taux_bleu = atof(argv[2]), taux_rouge = atof(argv[3]);
    if (taux_jaune + taux_bleu + taux_rouge != 100.) {
        // on vérifie qu'avec le total des flottants on arrive bien à 100
        printf("Mauvais arguments, le total doit donner 100%%.\n");
        return 2; // code d'erreur différent de celui où le nombre d'arguments est incorrect pour pouvoir les différencier
    }
    couleur c = {.jaune = taux_jaune, .bleu = taux_bleu, .rouge = taux_rouge};   
}
*/


// fonctions de mélange de deux couleurs

// version avec passage par valeur des paramètres
couleur melange(couleur c1, couleur c2) {
    couleur mel = { .rouge = (c1.rouge + c2.rouge) / 2,
                    .bleu = (c1.bleu + c2.bleu) / 2,
                    .jaune = (c1.jaune + c2.jaune) / 2};
    return mel;
}

// version avec passage par référence des paramètres
couleur* melange2(couleur* c1, couleur* c2) {
    couleur* mel = malloc(sizeof(couleur));
    mel->rouge = (c1->rouge + c2->rouge) / 2; // on utilise des -> pour l'accès aux champs car on manipule des pointeurs vers des structures
    mel->bleu = (c1->bleu + c2->bleu) / 2;
    mel->jaune = (c1->jaune + c2->jaune) / 2;
    return mel; // il faudra penser à libérer mel après appel à cette fonction
}


/* --------------------------------------------------------- */

/* EXERCICES */


// Ligne de commande

int operation (char op, int a, int b) {
    if (op == '+') { return a + b; }
    else if (op == '-') { return a - b; }
    else if (op == 'x') { return a * b; }
    else if (op == '/') { return a / b; }
    else { return a % b; }
}

/*
// main pour tester 'opération'
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Mauvais arguments. On attend : %s entier operateur entier\n", argv[0]);
        return 1; // pour signaler l'erreur
    }
    printf("Le résultat est %d.\n", operation(argv[2][0], atoi(argv[1]), atoi(argv[3])));
}
*/

int operation_chaine (char op[], int a, int b) {
    // rappel : on ne peut pas comparer des chaînes avec ==
    // car ce sont des tableaux (contenant un '\0')
    if (strcmp(op, "somme") == 0) { return a + b; }
    else if (strcmp(op, "difference") == 0) { return a - b; }
    else if (strcmp(op, "produit") == 0) { return a * b; }
    else if (strcmp(op, "quotient") == 0) { return a / b; }
    else return a % b;
}


// couleurs

typedef reel coul[3]; // ligne à placer dans le .h pour pouvoir utiliser le type coul depuis d'autres fichiers

void melange_couleurs(coul c1, coul c2, coul melange) {
    for (int i = 0; i < 3; i += 1) {
        melange[i] = (c1[i] + c2[i]) / 2;
    }
}


// Signes

enum signe_e { positif, negatif, nul};
typedef enum signe_e signe;

signe signe_int(int n) {
    if (n > 0) {
        return positif;
    }
    else if (n < 0) {
        return negatif;
    }
    else {
        return nul;
    }
}

signe signe_produit(signe s1, signe s2) {
    if (s1 == nul || s2 == nul) {
        return nul;
    }
    else if (s1 == s2) {
        return positif;
    }
    else {
        return negatif;
    }
}


// Pixels

struct pixel_s {
    int rouge;
    int vert;
    int bleu;
};
typedef struct pixel_s pixel;

bool valide_pixel(pixel p) {
    return p.rouge >= 0 && p.rouge < 256 && p.bleu >= 0 && p.bleu < 256 && p.vert >= 0 && p.vert < 256;
}

pixel pixel_noir_blanc(pixel p) {
    pixel blanc = {255,255,255};
    pixel noir = {0,0,0};
    if ((p.bleu + p.rouge + p.vert) / 3 < 128) {
        return noir;
    }
    else {
        return blanc;
    }
}

void devient_pixel_noir_blanc(pixel* p) {
    // cette fonction doit modifier le pixel par effet de bord
    // il faut donc nécessairement avoir un pointeur vers ce pixel !
    if ((p->bleu + p->rouge + p->vert) / 3 < 128) {
        p->bleu = 0;
        p->rouge = 0;
        p->vert = 0;
    }
    else {
        p->bleu = 255;
        p->rouge = 255;
        p->vert = 255;
    }
}


// Dates


enum mois_e {janvier, fevrier, mars, avril, mai, juin, juillet, aout, septembre, octobre, novembre, decembre};

enum mois_e mois_suivant(enum mois_e m) {
    if (m == janvier) { return fevrier; }
    if (m == fevrier) { return mars; }
    if (m == mars) { return avril; }
    if (m == avril) { return mai; }
    if (m == mai) { return juin; }
    if (m == juin) { return juillet; }
    if (m == juillet) { return aout; }
    if (m == aout) { return septembre; }
    if (m == septembre) { return octobre; }
    if (m == octobre) { return novembre; }
    if (m == novembre) { return decembre; }
    return janvier; // dernier cas, m == decembre
}

struct date_s {
    int jour;
    enum mois_e mois;
    int annee;
};
typedef struct date_s date;

bool bissextile(int annee) {
    return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

bool est_valide(date d) {
    if (d.mois == fevrier) {
        if (bissextile(d.annee)) {
            return d.jour >= 1 && d.jour <= 29;
        }
        else {
            return d.jour >= 1 && d.jour <= 28;
        }
    }
    else if (d.mois == avril || d.mois == juin || d.mois == septembre || d.mois == novembre) {
        return d.jour >= 1 && d.jour <= 30;
    }
    else {
        return d.jour >= 1 && d.jour <= 31;
    }
}

date lendemain(date d) {
    date demain = {d.jour + 1, d.mois, d.annee};
    if (est_valide(demain)) {
        return demain;
    }
    demain.jour = 1;
    demain.mois = mois_suivant(d.mois);
    if (d.mois == decembre) {
        demain.annee += 1;
    }
    return demain;
}

enum saison_e {hiver, printemps, ete, automne};


// Complexes

struct complexe_s {
  double reel;
  double imag;
};
typedef struct complexe_s complexe;

void affiche_complexe(complexe z) {
    if (z.imag >= 0) {
        printf("%f + %f*i", z.reel, z.imag);
    }
    else {
        printf("%f - %f*i", z.reel, -z.imag);
    }
}

complexe addition(complexe z1, complexe z2) {
  complexe res;
  res.reel = z1.reel + z2.reel;
  res.imag = z1.imag + z2.imag;
  return res;
}

complexe mult_const(complexe z, double a) {
  complexe res;
  res.reel = a * z.reel;
  res.imag = a * z.imag;
  return res;
}

complexe soustraction(complexe z1, complexe z2) {
  return addition(z1, mult_const(z2, -1.0));
}

complexe produit(complexe z1, complexe z2) {
  complexe res;
  res.reel = z1.reel * z2.reel - z1.imag * z2.imag;
  res.imag = z1.reel * z2.imag + z1.imag * z2.reel;
  return res;
}

double module(complexe z) {
  return sqrt(z.reel * z.reel + z.imag * z.imag); // il faudra compiler avec -lm
}

complexe conjugue(complexe z) {
  complexe z_bar = z; // l'opérateur = fait bien une copie indépendante sur les struct
  z_bar.imag *= -1;
  return z_bar;
}

void conjugue_en_place(complexe* z) { // pointeur car on veut avoir un effet de bord
  z->imag *= -1;
}

complexe division(complexe z1, complexe z2) {
  double m2 = module(z2);
  complexe p = produit(z1, conjugue(z2));
  return mult_const(p, 1/(m2*m2));
}
