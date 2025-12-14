#ifndef __ARBRE_H__
#define __ARBRE_H__
#include "../../../libraries.h"

typedef int etiq;
typedef struct noeud_s* ab;

ab cree_ab_vide(void);
ab noeud(etiq, ab, ab);
void libere_ab(ab);
bool est_vide_ab(ab);
etiq etiq_racine(ab);
ab sous_arbre_gauche(ab);
ab sous_arbre_droit(ab);
int taille_ab(ab);
int hauteur_ab(ab);

// Fonctions en plus
etiq somme_ab(ab);
bool egaux_ab(ab, ab);
bool appartient_ab(ab, etiq);

// def des arbres binaires stricts
ab feuille(etiq);
ab noeud_strict(etiq, ab, ab);
bool est_feuille(ab);
int nombre_de_feuilles(ab);
etiq derniere_feuille(ab);
bool est_strict_ab(ab);

#endif
