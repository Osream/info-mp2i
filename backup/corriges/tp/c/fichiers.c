/*
CORRIGÉ PARTIEL DU TP : GESTION DE FICHIERS (PARTIE EN C)
Par J. BENOUWT
Licence CC BY-NC-SA
*/

/* --------------------------------------------------------- */

#include "piles_files/pile.h"
#include "piles_files/file.h"
#include <string.h>


/* --------------------------------------------------------- */


/* Copie d'un fichier dans un autre */


void copie(char* f1, char* f2) {
    char ligne[1024]; // on stockera ici les données lues

    FILE* fichier = fopen(f1, "r"); // ouvre le fichier en lecture
    if (fichier == NULL) {
        // si le pointeur est NULL c'est qu'une erreur s'est produite à l'ouverture
        fprintf(stderr, "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n");
        return;
    }

    FILE* copie = fopen(f2, "w"); // ouvre la copie en écriture
    if (copie == NULL) {
        // on vérifie à nouveau que l'ouverture s'est bien passée
        fprintf(stderr, "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n");
        fclose(fichier);
        return;
    }
    
    // on lit toutes les lignes du fichier, c'est-à-dire on lit tant que la valeur EOF (End Of File) n'est pas renvoyée
    while (fscanf(fichier, "%s", ligne) != EOF) {
        // on copie la ligne lue dans le fichier ouvert en écriture
        fprintf(copie, "%s\n", ligne);
    }
    // quand c'est terminé, on n'oublie pas de fermer nos deux fichiers
    fclose(fichier);
    fclose(copie);
}

/*
// Pour utiliser ce programme, décommentez le main suivant :
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "On attend deux arguments.\n");
        return 1;
    }
    copie(argv[1], argv[2]);
}
*/



/* --------------------------------------------------------- */


/* Sérialisation de structures de données séquentielles */


// fonctions auxiliaires

void transvase_pile_vers_pile(pile p1, pile p2) {
    while (!est_vide_pile(p1)) {
        empiler(p2, depiler(p1));
    }
}

void transvase_file_vers_file(file f1, file f2) {
    while (!est_vide_file(f1)) {
        enfiler(f2, defiler(f1));
    }
}


// sérialisation d'une pile

void serialise_pile(pile p, char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert.\n", nom_fichier);
        return;
    }
    pile sauv = creer_pile();
    while (!est_vide_pile(p)) {
        contenu_pile elt = depiler(p);
        fprintf(fichier, "%d\n", elt);
        empiler(sauv, elt);
    }
    transvase_pile_vers_pile(sauv, p);
    detruire_pile(sauv);
    fclose(fichier);
}

pile deserialise_pile(char* nom_fichier) {
    pile p = creer_pile();
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert.\n", nom_fichier);
    }
    else {
        pile p_a_l_envers = creer_pile();
        int elt;
        while (fscanf(fichier, "%d", &elt) != EOF) {
            empiler(p_a_l_envers, elt);
        }
        transvase_pile_vers_pile(p_a_l_envers, p);
        detruire_pile(p_a_l_envers);
        fclose(fichier);
    }
    return p;
}


// sérialisation d'une file

void serialise_file(file f, char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert.\n", nom_fichier);
        return;
    }
    file sauv = creer_file();
    while (!est_vide_file(f)) {
        contenu_file elt = defiler(f);
        fprintf(fichier, "%d\n", elt);
        enfiler(sauv, elt);
    }
    transvase_file_vers_file(sauv, f);
    detruire_file(sauv);
    fclose(fichier);
}

file deserialise_file(char* nom_fichier) {
    file f = creer_file();
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert.\n", nom_fichier);
    }
    else {
        int elt;
        while (fscanf(fichier, "%d", &elt) != EOF) {
            enfiler(f, elt);
        }
        fclose(fichier);
    }
    return f;
}



/* --------------------------------------------------------- */


/* Exercices */


void cat(int nb_fichiers, char** noms_fichiers) {
    for (int i = 0; i < nb_fichiers; i += 1) {
        FILE* fichier = fopen(noms_fichiers[i], "r");
        if (fichier == NULL) {
            fprintf(stderr, "Le fichier %s n'a pas pu être ouvert.\n", noms_fichiers[i]);
            continue;
        }
        // on propose ici une version qui lit des caractères et non des chaînes
        char caractere_lu;
        while (fscanf(fichier, "%c", &caractere_lu) != EOF) {
            fprintf(stdout, "%c", caractere_lu);
        }
        fclose(fichier);
    }
}

/*
// pour avoir un programme similaire à cat, décommentez le main suivant :
int main(int argc, char* argv[]) {
    cat(argc-1, argv+1);
}
*/


void wc(char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert.\n", nom_fichier);
        return;
    }
    char caractere_lu;
    int nb_lignes = 0, nb_mots = 0, nb_caracteres = 0;
    bool debut_mot = false; // cette variable indique si un mot est en cours de lecture
    /*
    on lit le fichier caractère par caractère avec trois compteurs pour
    - les caractères lus (incrémenté à chaque lecture)
    - les mots lus (incrémenté quand le caractère est un espace, une tabulation ou un saut de ligne et qu'un mot est en cours de lecture)
    - les lignes lues (incrémenté quand le caractère est un \n).
    */
    while (fscanf(fichier, "%c", &caractere_lu) != EOF) {
        nb_caracteres += 1;
        if (caractere_lu == '\n') {
            nb_lignes += 1;
            if (debut_mot) {
                nb_mots += 1;
            }
            debut_mot = false;
        }
        else if (caractere_lu == ' ' || caractere_lu == '\t') {
            if (debut_mot) {
                nb_mots += 1;
            }
            debut_mot = false;
        }
        else {
            debut_mot = true;
        }
    }
    fclose(fichier);
    fprintf(stdout, "%d %d %d %s\n", nb_lignes, nb_mots, nb_caracteres, nom_fichier);
}

/*
// pour avoir un programme similaire à wc, décommentez le main suivant :
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "On attend un argument.\n");
        return 1;
    }
    wc(argv[1]);
}
*/



/* Stéganographie */

struct image_s {
	int haut;
	int larg;
	int max_couleur;
	uint16_t** pix;
};
typedef struct image_s image;


image* charger_image(char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    assert(fichier != NULL);
    char ligne[1024];

    image *img = malloc(sizeof(image));
    fscanf(fichier, "%s", ligne);
    fscanf(fichier, "%d %d %d", &img->larg, &img->haut, &img->max_couleur);

    img->pix = malloc(img->haut * sizeof(uint16_t*));

    for (int i = 0; i < img->haut; i += 1) {
        img->pix[i] = malloc(img->larg * sizeof(uint16_t));
        for (int j = 0; j < img->larg; j += 1) {
            fscanf(fichier, " %hu", &img->pix[i][j]);
        }
    }
  
    fclose(fichier);
    return img;
}

char caractere(uint16_t *tab) {
    int b = 0;
    for (int i = 0; i < 8; i += 1) {
        b = 2*b + tab[i]%2;
    }
    return (char)b;
}

void message(image* img, FILE* fichier) {
    int h = 0;
    char c = caractere(img->pix[h]);
    while(c != '\0') {
        fprintf(fichier, "%c", c);
        h += 1;
        c = caractere(img->pix[h]);
    }
}

void inserer_caractere(uint16_t* tab, char c) {
    int n = (int)c;
    for (int i = 7; i >= 0; i -= 1){
        tab[i] = 2*(tab[i]/2) + (n % 2);
        n /= 2;
    }
}

image* cacher(image* img, char* message) {
    if (img->larg < (int)strlen(message)) {
        return NULL;
    }
    for (int i = 0; i <= (int)strlen(message); i += 1) {
        inserer_caractere(img->pix[i], message[i]);
    }
    return img;
}

int sauvegarder_image(char* nom_fichier, image *img) {
    if(img == NULL){
        fprintf(stderr, "problème d'image");
        return 1;
    }
  
    FILE* fichier = fopen(nom_fichier, "w");
    if(fichier == NULL){
        fprintf(stderr, "problème de fichier");
        return 2;
    }

    fprintf(fichier, "P2\n%d %d\n%d\n", img->larg, img->haut, img->max_couleur);
    for (int i = 0; i < img->haut; i += 1) {
        for (int j = 0; j < img->larg; j += 1) {
            fprintf(fichier, "%hu ", img->pix[i][j]);
        }
        fprintf(fichier, "\n");
    }
  
    fclose(fichier);
    return 0;
}

void libere_image(image* img) {
    for (int i = 0; i < img->haut; i += 1) {
        free(img->pix[i]);
    }
    free(img->pix);
    free(img);
}

/*
// Pour utiliser ce programme, décommentez le main suivant :

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Ce programme attend 1 argument\n");
        return 1;
    }

    printf("Entrez le nom du fichier contenant l'image : ");
    char nom_fichier[1024];
    fscanf(stdin, "%s", nom_fichier);

    if (strcmp(argv[1], "trouver") == 0) {
        image* img = charger_image(nom_fichier);
        printf("Le message caché est : ");
        message(img, stdout);
        printf("\n");
        libere_image(img);
        return 0;
    }

    else if (strcmp(argv[1], "cacher") == 0) {
        char tmp;
        scanf("%c", &tmp);
        printf("Entrez le message à cacher : ");
        char message[1024];
        fscanf(stdin, "%[^\n]", message);

        printf("Entrez le nom du fichier pour l'enregistrement : ");
        char nom_fichier_sauvegarde[1024];
        fscanf(stdin, "%s", nom_fichier_sauvegarde);

        image* origine = charger_image(nom_fichier);
        image* img = cacher(origine, message);

        if (img == NULL) {
            fprintf(stderr, "L'image est trop petite pour cacher le message\n");
            libere_image(origine);
            return 1;
        }

        int statut = sauvegarder_image(nom_fichier_sauvegarde, img);
        libere_image(img);
        return statut;
    }

    else {
        printf("Ce programme attend comme argument : 'trouver' ou 'cacher'\n");
        return 1;
    }
}
*/
