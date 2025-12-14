#ifndef __GESTION_H__
#define __GESTION_H__
#include "../../libraries.h"

/*Fonction qui a un nom de ficher copie ses 10 premières lignes dans le second.
Entrees : 2 noms de fichier
Sorties : Aucune
Pre-condition : les fichiers existent
Post-condition : le 2eme fichier est modifié*/
void copie10(char* f1, char* f2);

/*Fonction qui a copie du premier fichier en paramètre toutes les lignes dans le 2nd
Entrees : 2 noms de fichier
Sorties : Aucune
Pre-condition : le premier fichier existe
Post-conditoon : Copie le premier fichier dans le 2eme (ou crée un fichier)
*/
void copie(char* f1, char* f2);

#endif