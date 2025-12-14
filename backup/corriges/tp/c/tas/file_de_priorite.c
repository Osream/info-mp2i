/*
CORRIGÉ PARTIEL DU TP : TAS (Implémentation d'une file de priorité)
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include "file_de_priorite.h"


/*---------------------------------------------------------*/

// TYPES NÉCESSAIRES

/*
On utilise un tas-min pour implémenter nos files de priorité,
les priorités stockées dans les nœuds doivent respecter la propriété d'ordre des tas-min.

J'ai choisi d'utiliser deux tableaux : un stockant les éléments, le second stockant leurs priorités.
L'élément « elements[i] » a comme priorité « priorites[i] ».

Il y a bien d'autres implémentations possibles, par exemple :
- créer une autre structure à deux champs, 1 pour l'élément et 1 pour la priorité,
  puis utiliser un tableau dont les cases sont du type de cette structure.
- créer un tableau bidimensionnel : une ligne par élément, et chaque ligne a 2 colonnes,
la première colonne contient l'élément et la deuxième colonne sa priorité.
- ...
Tout choix de structure donnant les mêmes complexités est accepté.
*/

struct file_prio_s {
    int* priorites; // tableau des priorité
    contenu* elements; // tableau des éléments
    int nb_elements; // nombre d'éléments dans la file de priorité
    int capacite_maximale; // taille de la zone allouée pour 'priorites' et 'elements'
};

// taille de la zone allouée lors de la création de la file de priorité
const int CAPACITE_MAX_INITIALE = 2;


/*---------------------------------------------------------*/

// FONCTIONS AUXILIAIRES

// fonction pour échanger deux éléments d'un tableau
void echange(int* t, int i, int j) {
    int tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
}

// fonction pour la réallocation de zones plus grandes / plus petites
void realloue(file_de_priorite* fp, int nouvelle_capacite) {
    // allocation des nouvelles zones
    fp->capacite_maximale = nouvelle_capacite;
    int* nouvelle_zone_priorites = malloc(fp->capacite_maximale * sizeof(int));
    contenu* nouvelle_zone_elements = malloc(fp->capacite_maximale * sizeof(contenu));
    // recopie du contenu actuel de la file de priorité
    for (int i = 0; i < fp->nb_elements; i += 1) {
        nouvelle_zone_priorites[i] = fp->priorites[i];
        nouvelle_zone_elements[i] = fp->elements[i];
    }
    // libération des anciennes zones
    free(fp->elements);
    free(fp->priorites);
    fp->elements = nouvelle_zone_elements;
    fp->priorites = nouvelle_zone_priorites;
}

// fonction pour la percolation vers le haut
void percolation_vers_le_haut(file_de_priorite* fp, int indice_mal_place) {
    int pere = (indice_mal_place - 1) / 2;
    if (indice_mal_place != 0 && fp->priorites[indice_mal_place] < fp->priorites[pere]) {
        echange(fp->priorites, indice_mal_place, pere);
        echange(fp->elements, indice_mal_place, pere);
        percolation_vers_le_haut(fp, pere);
    }
}

// fonction pour la percolation vers le bas
void percolation_vers_le_bas(file_de_priorite* fp, int indice_mal_place) {
    int fils_gauche = 2*indice_mal_place + 1;
    int fils_droit = 2*indice_mal_place + 2;
    int indice_avec_lequel_echanger = indice_mal_place;
    if (fils_gauche < fp->nb_elements && fp->priorites[indice_mal_place] > fp->priorites[fils_gauche]) {
        indice_avec_lequel_echanger = fils_gauche;
    }
    if (fils_droit < fp->nb_elements && fp->priorites[indice_avec_lequel_echanger] > fp->priorites[fils_droit]) {
        indice_avec_lequel_echanger = fils_droit;
    }
    if (indice_avec_lequel_echanger != indice_mal_place) {
        echange(fp->priorites, indice_avec_lequel_echanger, indice_mal_place);
        echange(fp->elements, indice_avec_lequel_echanger, indice_mal_place);
        percolation_vers_le_bas(fp, indice_avec_lequel_echanger);
    }
}


/*---------------------------------------------------------*/

// FONCTIONS DE L'INTERFACE PRINCIPALE


file_de_priorite* fp_creer(void) {
    file_de_priorite* fp = malloc(sizeof(file_de_priorite));
    fp->capacite_maximale = CAPACITE_MAX_INITIALE;
    fp->nb_elements = 0;
    fp->priorites = malloc(fp->capacite_maximale * sizeof(int));
    fp->elements = malloc(fp->capacite_maximale * sizeof(contenu));
    return fp;
}

bool fp_est_vide(file_de_priorite* fp) {
    return fp->nb_elements == 0;
}

void fp_enfiler(file_de_priorite* fp, contenu element, int priorite) {
    // si on doit enfiler un élément et que la zone allouée est pleine,
    // on réalloue une zone deux fois plus grande
    if (fp->nb_elements == fp->capacite_maximale) {
        realloue(fp, 2 * fp->capacite_maximale);
    }
    // on insère tout en bas à droite puis percolation vers le haut
    fp->elements[fp->nb_elements] = element;
    fp->priorites[fp->nb_elements] = priorite;
    fp->nb_elements += 1;
    percolation_vers_le_haut(fp, fp->nb_elements-1);
}

contenu fp_defiler(file_de_priorite* fp) {
    assert(fp->nb_elements != 0);
    // l'élément de priorité minimale se trouve à la racine
    contenu a_renvoyer = fp->elements[0];
    // on échange la racine avec l'élément tout en bas à droite puis percolation vers le bas
    fp->nb_elements -= 1;
    if (fp->nb_elements != 0) {
        echange(fp->elements, 0, fp->nb_elements);
        echange(fp->priorites, 0, fp->nb_elements);
        percolation_vers_le_bas(fp, 0);
    }
    // si on défile un élément et que moins d'un quart de la zone est utilisée,
    // on réalloue une zone deux fois plus petite
    if (fp->nb_elements < fp->capacite_maximale / 4) {
        realloue(fp, fp->capacite_maximale / 2);
    }
    return a_renvoyer;
}

void fp_detruire(file_de_priorite* fp) {
    free(fp->elements);
    free(fp->priorites);
    free(fp);
}