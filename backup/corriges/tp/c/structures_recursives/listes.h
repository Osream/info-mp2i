/*
CORRIGÉ PARTIEL DU TP : STRUCTURES RÉCURSIVES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* Fichier d'interface des listes chaînées */


/* --------------------------------------------------------- */


#ifndef _LISTE_H_
#define _LISTE_H_


#include "../librairies.h"


// Définition des types
typedef int contenu;
typedef struct maillon_s maillon;
typedef maillon* liste;


/*
Entrée : aucune.
Précondition : aucune.
Sortie : une liste.
Postcondition : renvoie une liste vide.
Complexité : O(1)
*/
liste creer_liste();

/*
Entrée : une liste.
Précondition : aucune.
Sortie : un booléen.
Postcondition : renvoie true si la liste est vide, false sinon.
Complexité : O(1)
*/
bool est_vide_liste(liste);

/*
Entrée : un contenu, un pointeur vers une liste.
Précondition : le pointeur n'est pas NULL.
Sortie : aucune.
Postcondition : le contenu a été ajouté en tête de la liste.
Complexité : O(1)
*/
void ajouter_tete_liste(contenu, liste*);

/*
Entrée : une liste.
Précondition : la liste n'est pas vide.
Sortie : un contenu.
Postcondition : renvoie le contenu de la tête de la liste.
Complexité : O(1)
*/
contenu tete_liste(liste);

/*
Entrée : une liste.
Précondition : la liste n'est pas vide.
Sortie : une liste.
Postcondition : renvoie la queue de la liste.
Complexité : O(1)
*/
liste queue_liste(liste);

/*
Entrée : une liste.
Précondition : aucune.
Sortie : aucune.
Postcondition : toute la mémoire occupée par la liste a été libérée.
Complexité : O(taille de la liste)
*/
void detruire_liste(liste);


#endif
