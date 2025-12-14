/*
CORRIGÉ PARTIEL DU TP : STRUCTURES RÉCURSIVES EN C
Par J. BENOUWT
Licence CC BY-NC-SA
*/


/* Fichier d'interface des poupées russes */


/* --------------------------------------------------------- */


#ifndef _POUPEES_H_
#define _POUPEES_H_


#include "../librairies.h"


typedef struct poupee_s poupee;


/*
Entrée : un entier correspondant à la taille de la poupée à créer.
Précondition : la taille donnée doit être strictement positive.
Sortie : un pointeur vers la poupée créée.
Postcondition : la poupée renvoyée est de taille t donnée en paramètre, et contient une poupée de taille t-1, contenant ... contenant une poupée de taille 1 vide.
*/
poupee* poupee_creer(int);

/*
Entrée : un pointeur vers une poupée.
Précondition : le pointeur n'est pas NULL.
Sortie : aucune.
Postcondition : tout le stockage induit par la poupée donnée en paramètre est libéré.
*/
void poupee_detruire(poupee*);

/*
Entrée : un pointeur vers une poupée.
Précondition : aucune.
Sortie : aucune.
Postcondition : la taille de la poupée est affichée, puis sur la ligne suivante la taille de son contenu est affichée, puis ... jusqu'à la dernière poupée.
*/
void poupee_afficher(poupee*);

/*
Entrée : un pointeur vers une poupée.
Précondition : le pointeur n'est pas NULL.
Sortie : un entier.
Postcondition : renvoie la taille de la poupée.
*/
int poupee_taille(poupee*);

/*
Entrée : un pointeur vers une poupée.
Précondition : le pointeur n'est pas NULL.
Sortie : un booléen.
Postcondition : on ne renvoie true que si les poupées sont bien de tailles strictement décroissantes.
*/
bool poupee_check(poupee*);

/*
Entrée : un pointeur vers une poupée et un entier.
Précondition : le pointeur n'est pas NULL, et l'entier est strictement positif et inférieur ou égal au nombre de poupées disponibles à l'intérieur de la poupée donnée.
Sortie : un pointeur vers une poupée.
Postcondition : en notant n l'entier, récupère la n-ième poupée à l'intérieur de celle donnée en paramètre.
*/
poupee* poupee_ouvre(poupee*, int);


#endif
