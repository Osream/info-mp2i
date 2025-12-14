/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* Interface d'une pile */


/* --------------------------------------------------------- */


#ifndef _PILE_H_
#define _PILE_H_


#include "../../../libraries.h"


typedef int contenu_pile;
typedef struct pile_s* pile;


/*
Entrée : aucune.
Précondition : aucune.
Sortie : une pile.
Postcondition : la pile renvoyée est vide.
Complexité : O(1)
*/
pile creer_pile(void);

/*
Entrée : une pile.
Précondition : le pointeur n'est pas NULL.
Sortie : un booléen.
Postcondition : renvoie true si la pile est vide, false sinon.
Complexité : O(1)
*/
bool est_vide_pile(pile);

/*
Entrée : une pile et un contenu.
Précondition : le pointeur n'est pas NULL.
Sortie : aucune.
Postcondition : le contenu a été empilé dans la pile.
Complexité : O(1)
*/
void empiler(pile, contenu_pile);

/*
Entrée : une pile.
Précondition : le pointeur n'est pas NULL, la pile n'est pas vide.
Sortie : un contenu.
Postcondition : le contenu renvoyé est celui qui avait été ajouté en dernier dans la pile (principe LIFO), et la pile ne contient plus cet élément.
Complexité : O(1)
*/
contenu_pile depiler(pile);

/*
Entrée : une pile.
Précondition : le pointeur n'est pas NULL.
Sortie : aucune.
Postcondition : toute la mémoire occupée par la pile a été libérée.
Complexité : O(taille de la pile)
*/
void detruire_pile(pile);

/*
Entrée : une pile.
Précondition : le pointeur n'est pas NULL, la pile n'est pas vide.
Sortie : un contenu.
Postcondition : le contenu renvoyé est celui qui avait été ajouté en dernier dans la file (principe LIFO).
Complexité : O(1)
*/
contenu_pile sommet_pile(pile);


#endif
