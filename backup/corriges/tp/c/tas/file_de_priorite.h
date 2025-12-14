#ifndef _FILE_PRIO_H_
#define _FILE_PRIO_H_

#include "../librairies.h"

typedef int contenu; // remplacer 'int' par le type des éléments de la file de priorité
typedef struct file_prio_s file_de_priorite;

/*
* Entrées et préconditions : aucune.
* Sorties et postconditions : une file de priorité vide.
*/
file_de_priorite* fp_creer(void);

/*
* Entrées et préconditions : une file de priorité.
* Sorties et postconditions : le booléen vrai si la file est vide, faux sinon.
*/
bool fp_est_vide(file_de_priorite*);

/*
* Entrées et préconditions : une file de priorité f, un élément e de type quelconque, une priorité p de type entier.
* Sorties et postconditions : aucune sortie, mais f contient un élément supplémentaire, e, associé à sa priorité p.
*/
void fp_enfiler(file_de_priorite*, contenu, int);

/*
* Entrées et préconditions : une file de priorité f non vide
* Sorties et postconditions : l'élément le plus prioritaire est renvoyé, et f​​​ ne contient plus cet élément.
*/
contenu fp_defiler(file_de_priorite*);

/*
* Entrées et préconditions : une file de priorité
* Sorties et postconditions : aucune sortie, mais toute la mémoire associée à la file est libérée.
*/
void fp_detruire(file_de_priorite*);

#endif