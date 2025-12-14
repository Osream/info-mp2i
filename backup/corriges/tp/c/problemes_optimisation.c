/*
CORRIGÉ PARTIEL DU TP : PROBLÈMES D'OPTIMISATION
Par J. BENOUWT
Licence CC BY-NC-SA
*/


#include "librairies.h"
#include "structures_recursives/listes.h"



/* --------------------------------------------------------- */


// fonctions utiles pour la suite

int min2(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int min3(int a, int b, int c) {
   return min2(a, min2(b, c));
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}



/* --------------------------------------------------------- */


// Carré de 1 dans une matrice


/*
On cherche à maximiser une fonction (la fonction qui à un carré associe sa largeur)
sous contraintes (le carré doit être rempli de 1)
sur un ensemble donné (l'ensemble des carrés d'une matrice M).
Ce qui correspond donc à la définition des problèmes d'optimisation.
*/


int** matrice_moins_1(int l, int c) {
    // on alloue de la place pour chaque ligne
    int** memo = malloc(l * sizeof(int*));
    for (int i = 0; i < l; i += 1) {
        // dans chaque ligne, on alloue de la place pour chaque colonne
        memo[i] = malloc(c * sizeof(int));
        for (int j = 0; j < c; j += 1) {
            // et on remplit chaque colonne de la ligne de -1
            memo[i][j] = -1;
        }
    }
    return memo;
}


void libere_matrice(int l, int** memo) {
    for (int i = 0; i < l; i += 1) {
        free(memo[i]);
    }
    free(memo);
}


int remplir(int l, int c, int M[l][c], int** memo, int i, int j) {
    // on ne fait le calcul que s'il n'a pas déjà été fait
    if (memo[i][j] == -1) {
        // cas de base (première ligne ou première colonne)
        if (i == 0 || j == 0) {
            memo[i][j] = M[i][j];
        }
        // cas où M[i][j] vaut 0
        else if (M[i][j] == 0) {
            memo[i][j] = 0;
        }
        // cas où M[i][j] vaut 1
        else {
            memo[i][j] = 1 + min3(remplir(l, c, M, memo, i-1, j-1), remplir(l, c, M, memo, i, j-1), remplir(l, c, M, memo, i-1, j));
        }
    }
    return memo[i][j];
}


int** top_down(int l, int c, int M[l][c]) {
    int** memo = matrice_moins_1(l, c);
    for (int i = 0; i < l; i += 1) {
        for (int j = 0; j < c; j += 1) {
            remplir(l, c, M, memo, i, j);
        }
    }
    return memo;
}


int plus_grand_carre(int l, int c, int M[l][c], int* ligne, int* colonne) {
    int** memo = top_down(l, c, M);
    int res = -1;
    for (int i = 0; i < l; i += 1) {
        for (int j = 0; j < c; j += 1) {
            if (memo[i][j] > res) {
                res = memo[i][j];
                *ligne = i;
                *colonne = j;
            }
        }
    }
    libere_matrice(l, memo); // attention aux fuites de mémoire
    return res;

    /*
    COMPLEXITÉ :
    - SPATIALE : O(lc) due à "memo" (les autres variables sont en O(1)).
    - TEMPORELLE :
        - matrice_moins_1 est en O(lc).
        - top_down est en O(lc) car chaque case de memo est
          calculée une et une seule fois et le calcul est en O(1).
        - libere_matrice est en O(l).
        - plus_grand_carre est donc en O(lc) + O(1) + l*c*O(1) + O(l) = O(lc).
    */
}


int** bottom_up(int l, int c, int M[l][c]) {
    int** memo = matrice_moins_1(l, c);
    // initialisation des cas de base
    for (int i = 0; i < l; i += 1) {
        memo[i][0] = M[i][0];
    }
    for (int j = 0; j < c; j += 1) {
        memo[0][j] = M[0][j];
    }
    // boucles pour remplir le reste de memo
    for (int i = 1; i < l; i += 1) {
        for (int j = 1; j < c; j += 1) {
            if (M[i][j] == 0) {
                memo[i][j] = 0;
            }
            else {
                memo[i][j] = 1 + min3(memo[i-1][j-1], memo[i][j-1], memo[i-1][j]);
            }
        }
    }
    return memo;
}



/* --------------------------------------------------------- */


// Découpe optimale


/*
Il s'agit d'un problème d'optimisation, car on cherche à maximiser une fonction
(la somme des prix de vente des pièces) sur un ensemble (les ensembles de pièces qu'on
peut fabriquer à partir du ruban de tissu).

Pour les pièces {6, 3}, {8, 5} et
* T = 16, on peut fabriquer 2 pièces de 8cm pour un profit de 10€ qui est maximal.
* T = 21, on peut fabriquer 1 pièce de 8cm et 2 pièces de 6cm pour un profit maximal de 11€.

Pour un ruban de taille T, il y a T-1 endroits possibles où on peut découper
(on peut découper à 1cm du début, à 2cm, à 3cm, ..., à T-1cm).
À chaque endroit possible de découpe, on peut choisir de couper ou non (2 choix donc).
Il y a donc 2**(T-1) manières de découper le ruban.

Une stratégie « naïve » consisterait à calculer le profit obtenu pour chacune des
découpes possibles du ruban. On aurait donc une complexité au moins exponentielle
(due au nombre de découpes possibles, et on n'a même pas encore compté la complexité
pour calculer le profit d'une découpe...).
*/


struct piece_s {
    unsigned int longueur;
    unsigned int prix;
};
typedef struct piece_s piece;



// Glouton


bool ratio_inf(piece p1, piece p2) {
    double ratio_p1 = 1.0 * p1.prix / p1.longueur; // "1.0 *" est nécessaire sinon le / sur deux entiers fait la divison euclidienne
    double ratio_p2 = 1.0 * p2.prix / p2.longueur;
    return (ratio_p1 < ratio_p2);
}


// Fonction auxiliaire qui trie en place le tableau entre les indices debut et fin inclus.
void tri_rapide(piece pieces[], int debut, int fin) {
    // si on entre pas dans ce if c'est que l'intervalle à trier et de taille <= 1 donc déjà trié
    if (debut < fin) {
        // partition de Lomuto
        piece pivot = pieces[fin];
        int futur_indice_pivot = debut;
        for (int i = debut; i < fin; i += 1) {
            // quand on croise une pièce "plus petite" que la pièce pivot
            if (ratio_inf(pieces[i], pivot)) {
                // on place cette pièce avant le futur indice du pivot
                piece tmp = pieces[i];
                pieces[futur_indice_pivot] = pieces[i];
                pieces[i] = tmp;
                // et on incrémente l'indice du pivot (car il y a 1 pièce plus petite en plus)
                futur_indice_pivot += 1;
            }
        }
        // on place le pivot au bon endroit
        pieces[fin] = pieces[futur_indice_pivot];
        pieces[futur_indice_pivot] = pivot;
        // appels récursifs pour trier les éléments plus petits et plus grands que le pivot
        tri_rapide(pieces, debut, futur_indice_pivot-1);
        tri_rapide(pieces, futur_indice_pivot+1, fin);
    }
}


void tri(int p, piece pieces[p]) {
    tri_rapide(pieces, 0, p-1);
    // Complexité quadratique dans le pire des cas, mais quasi-linéaire dans le meilleur cas et le cas moyen.
}


int decoupe_optimale_glouton(int p, piece pieces[p], unsigned int T) {
    // on trie les pièces du plus petit au plus grand ratio.
    tri(p, pieces);
    int profit = 0;
    // le choix glouton consiste à prendre la pièce de ratio maximal parmi celles possibles à chaque étape,
    // on parcourt donc le tableau depuis la fin
    int indice_piece_etudiee = p - 1;
    while (indice_piece_etudiee >= 0) {
        // s'il est possible de prendre la pièce étudiée
        if (pieces[indice_piece_etudiee].longueur <= T) {
            // on la prend ce qui augmente le profit mais diminue la taille du ruban restant
            profit += pieces[indice_piece_etudiee].prix;
            T -= pieces[indice_piece_etudiee].longueur;
        }
        // sinon on passe à la pièce suivante
        else {
            indice_piece_etudiee -= 1;
        }
    }
    return profit;
}


/*
Avec T = 21 et les pièces {6, 3}, {8, 5}, on remarque que la stratégie gloutonne ne donne pas le résultat optimal.
*/



// Programmation dynamique


/*
V_0 = 0 (sans ruban on ne peut pas fabriquer de pièces...)

Si t > 0, considérons V_t le profit maximal pour un ruban de longueur t.
Soit (l_i, v_i) l'une des pièces fabriquées pour ce profit maximal V_t.
Alors :
    * l_i <= t car cette pièce a pu être fabriquée
    * sans cette pièce, on obtient un profit maximal avec un ruban de longueur t - l_i
    * le prix de vente de cette pièce v_i compte dans le profit maximal
Comme on doit choisir cette pièce maximisant le profit, on a la relation de récurrence donnée.

Soit x et y les longueurs de 2 des pièces qu'il est possible de fabriquer.
Supposons x + y <= T (taille initiale du ruban).
Pour calculer V_T, on devra calculer le profit maximal obtenu pour V_t avec t = T-x,
et pour calculer V_t on devra calculer V_{t-y}.
De même pour calculer V_T, on devra calculer le profit maximal obtenu pour V_t' avec t' = T-y,
et pour calculer V_t' on devra calculer V_{t'-x}.
Ainsi V_{T-x-y} sera calculé au moins 2 fois :
on a des chevauchements de sous-problèmes, la programmation dynamique est pertinente.

On va devoir calculer des V_t pour 0 <= t <= T, on peut donc utiliser
un tableau de taille T+1 pour lequel à chaque indice i est stocké V_i.
La complexité spatiale sera alors en O(T).

Pour remplir ce tableau, on peut le faire « de bas en haut » car on connaît l'ordre de résolution des sous-problèmes
(on calcule les V_t dans l'ordre croissant de t).
On peut aussi le faire récursivement avec de la mémoïsation.
Les deux approches donnent une complexité temporelle en O(T*p).

Cependant, comme tous les V_t ne sont pas forcément utilisés pour calculer V_T
(par exemple s'il n'existe pas de pièce de taille 1, alors V_{T-1} est inutile),
utiliser un tableau associatif et une approche top-down donnerait une meilleure complexité
(spatiale et temporelle).
*/


int decoupe_optimale_bottom_up(int p, piece pieces[p], unsigned int T) {
    // création de la structure de données
    int* tableau = malloc((T+1) * sizeof(int));
    // initialisation des cas de base
    tableau[0] = 0;
    // boucle pour remplir le reste de la structure
    for (unsigned int t = 1; t < T+1; t += 1) {
        tableau[t] = 0;
        for (int i = 0; i < p; i += 1) {
            if (pieces[i].longueur <= t) {
                tableau[t] = max(tableau[t], tableau[t-pieces[i].longueur] + pieces[i].prix);
            }
        }
    }
    // récupération du résultat dans la bonne case
    int resultat = tableau[T];
    free(tableau); // attention aux fuites de mémoire
    return resultat;
}


// fonction auxiliaire récursive avec mémoïsation
int remplir_tableau(int p, piece pieces[p], int* tableau, unsigned int t) {
    // on ne fait le calcul que s'il n'a pas déjà été fait
    if (tableau[t] == -1) {
        // cas de base
        if (t == 0) {
            tableau[t] = 0;
        }
        // cas récursif
        else {
            tableau[t] = 0;
            for (int i = 0; i < p; i += 1) {
                if (pieces[i].longueur <= t) {
                    tableau[t] = max(tableau[t], remplir_tableau(p, pieces, tableau, t-pieces[i].longueur) + pieces[i].prix);
                }
            }
        }
    }
    return tableau[t];
}


int decoupe_optimale_top_down(int p, piece pieces[p], unsigned int T) {
    // création de la structure de données
    int* tableau = malloc((T+1) * sizeof(int));
    for (unsigned int t = 0; t < T+1; t += 1) {
        tableau[t] = -1; // -1 indique que le calcul n'a pas encore été fait
    }
    // appel récursif sur la case qui nous intéresse pour récupérer le résultat
    int resultat = remplir_tableau(p, pieces, tableau, T);
    free(tableau); // attention aux fuites de mémoire
    return resultat;
}


liste reconstruit_decoupe_optimale(int p, piece pieces[p], unsigned int T, int* memo) {
    liste longueurs_pieces_selectionnees = creer_liste();
    while (memo[T] != 0) { // si le profit est 0, il n'y a plus de pièces à découper
        for (int i = 0; i < p; i += 1) {
            if (pieces[i].longueur <= T && memo[T-pieces[i].longueur] + (int)pieces[i].prix == memo[T]) { // on a trouvé la pièce qui nous donne le profit maximal
                ajouter_tete_liste(pieces[i].longueur, & longueurs_pieces_selectionnees);
                T -= pieces[i].longueur;
                break; // on passe à la suite (inutile de regarder les autres pièces)
            }
        }
    }
    return longueurs_pieces_selectionnees;
}
