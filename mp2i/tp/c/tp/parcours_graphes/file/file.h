/*
CORRIGÉ PARTIEL DU TP : IMPLÉMENTATION DE PILES ET FILES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* Interface d'une file */


/* --------------------------------------------------------- */


#ifndef _FILE_H_
#define _FILE_H_


#include "../../../libraries.h"


typedef int contenu_file;
typedef struct file_s* file;


/*
Entrée : aucune.
Précondition : aucune.
Sortie : une file.
Postcondition : la file renvoyée est vide.
Complexité : O(1)
*/
file creer_file(void);

/*
Entrée : une file.
Précondition : le pointeur n'est pas NULL.
Sortie : un booléen.
Postcondition : renvoie true si la file est vide, false sinon.
Complexité : O(1)
*/
bool est_vide_file(file);

/*
Entrée : une file et un contenu.
Précondition : le pointeur n'est pas NULL.
Sortie : aucune.
Postcondition : le contenu a été enfilé dans la file.
Complexité : O(1)
*/
void enfiler(file, contenu_file);

/*
Entrée : une file.
Précondition : le pointeur n'est pas NULL, la file n'est pas vide.
Sortie : un contenu.
Postcondition : le contenu renvoyé est celui qui avait été ajouté en premier dans la file (principe FIFO), et la file ne contient plus cet élément.
Complexité : O(1)
*/
contenu_file defiler(file);

/*
Entrée : une file.
Précondition : le pointeur n'est pas NULL.
Sortie : aucune.
Postcondition : toute la mémoire occupée par la file a été libérée.
Complexité : O(taille de la file)
*/
void detruire_file(file);

/*
Entrée : une file.
Précondition : le pointeur n'est pas NULL, la file n'est pas vide.
Sortie : un contenu.
Postcondition : le contenu renvoyé est celui qui avait été ajouté en premier dans la file (principe FIFO).
Complexité : O(1)
*/
contenu_file tete_file(file);


#endif
