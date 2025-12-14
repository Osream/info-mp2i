#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

#include "dicos.h"

const double phi = 1.61803398875;

void liberer_liste(liste l){
    //Libère l'espace mémoire occupé par une liste.
    if (l != NULL){
        liberer_liste(l->suivant);
        free(l);
    }
}

liste cons(int x, liste l){
    //Crée une nouvelle liste étant donnée une tête et une queue.
    liste nouvelle_liste = malloc(sizeof(maillon));
    nouvelle_liste->val = x;
    nouvelle_liste->suivant = l;
    return nouvelle_liste;
}

void liberer_liste_couples(liste_couples l){
    //Libère l'espace mémoire occupé par une liste de couples.
    if (l != NULL){
        liberer_liste_couples(l->suivant);
        free(l);
    }
}

liste_couples cons_couple(int c, int v, liste_couples l){
    //Crée une nouvelle liste de couples étant donnée une tête et une queue.
    liste_couples nouvelle_liste = malloc(sizeof(maillon_couple));
    nouvelle_liste->cle = c;
    nouvelle_liste->valeur = v;
    nouvelle_liste->suivant = l;
    return nouvelle_liste;
}

void liberer_dico(dico* d){
    //Libère l'espace mémoire occupé par un dictionnaire.
    for (int i=0; i<d->capacite; i++){
        liberer_liste_couples(d->donnees[i]);
    }
    free(d->donnees);
    free(d);
}

dico* creer_dico(void){
    //Crée un dictionnaire vide.
    dico* d = malloc(sizeof(dico));
    d->capacite = 1;
    d->nb_elements = 0;
    liste_couples* donnees = malloc(sizeof(liste_couples) * d->capacite);
    for(int i = 0; i < d->capacite ; i++)
    {   
        donnees[i] = NULL;
    }
    d->donnees = donnees;
    return d;
}

int taille_dico(dico* d){
    //Renvoie le nombre d'éléments compris dans un dictionnaire.
    return d->nb_elements;
}

int hash(int capacite, int k){
    //Renvoie le haché d'un entier.
    double tmp_val = floor(capacite * k * phi);
    return ((int) tmp_val) % capacite;
}

bool appartient_liste_cle(liste_couples l, int c){
    //Teste l'appartenance d'un entier en tant que premier membre d'une liste de couples.
    while (l != NULL){
        if (l->cle == c){
            return true;
        }
        l = l->suivant;
    }
    return false;
}

bool appartient_cle(dico* d, int c){
    //Teste l'appartenance d'une clé à un dictionnaire.
    return appartient_liste_cle(d->donnees[hash(d->capacite, c)], c);
}

int valeur_associee(dico* d, int c){
    //Renvoie la valeur associée à une clé dans un dictionnaire.
    assert(appartient_cle(d, c));
    liste_couples liste_candidate = d->donnees[hash(d->capacite, c)];
    while (liste_candidate->cle != c){
        liste_candidate = liste_candidate->suivant;
    }
    return liste_candidate->valeur;
}

int obtenir_cle(dico* d){
    assert(taille_dico(d) > 0);
    //Renvoie une clé quelconque d'un dictionnaire.
    for (int i=0; i<d->capacite; i++){
        if (d->donnees[i] != NULL){
            return d->donnees[i]->cle;
        }
    }
    //N'arrive jamais grâce au assert initial
    return 0;
}


void ajoute_entree_base(dico* d, int c, int v){
    //Ajoute une association (clé, valeur) à un dictionnaire sans redimensionner
    assert(!appartient_cle(d, c));
    int dico_index = hash(d->capacite, c);
    d->donnees[dico_index] = cons_couple(c, v, d->donnees[dico_index]);
    d->nb_elements = d->nb_elements + 1;
}

void redimensionne(dico* d, int nouvelle_capacite){
    //Redimensionne la table de hachage d'un dictionnaire.   
    liste_couples* nouvelles_donnees = malloc(nouvelle_capacite * sizeof(liste_couples));
    for (int i=0; i<nouvelle_capacite; i++){
        nouvelles_donnees[i] = NULL;
    }
    liste_couples* anciennes_donnees = d->donnees;
    int ancienne_capacite = d->capacite;
    d->capacite = nouvelle_capacite;
    d->nb_elements = 0;
    d->donnees = nouvelles_donnees;
    for (int i=0; i<ancienne_capacite; i++){
        liste_couples donnees_locales = anciennes_donnees[i];
        while (donnees_locales != NULL){
            ajoute_entree_base(d, donnees_locales->cle, donnees_locales->valeur);
            donnees_locales = donnees_locales->suivant;
        }
        liberer_liste_couples(anciennes_donnees[i]);
    }
    free(anciennes_donnees);
}


void ajoute_entree(dico* d, int c, int v){
    //Ajoute une association (clé, valeur) à un dictionnaire.
    int n = d->capacite;
    if (n <= d->nb_elements)
    {
        redimensionne(d, 2*n+1);
    }
    ajoute_entree_base(d,c,v);
}

void supprime_entree(dico* d, int c){
    //Supprime une association d'un dictionnaire.
    //Remarque : on fait une double recherche et un double parcours de liste, c'est pas opti
    if (appartient_cle(d,c)){
        if (d->capacite > 4 * d->nb_elements)
        {
            redimensionne(d, d->capacite / 2);
        }
        int h = hash(d->capacite, c);
        liste_couples donnees_locales = d->donnees[h];
        if(donnees_locales->cle == c)
        {
            liste_couples tmp = donnees_locales->suivant;
            free(donnees_locales);
            d->donnees[h] = tmp;
        }
        else
        {
            while(donnees_locales->suivant->cle != c)
            {
                donnees_locales = donnees_locales->suivant;
            }   
            liste_couples fin_de_liste = donnees_locales->suivant->suivant;
            free(donnees_locales->suivant);
            donnees_locales->suivant = fin_de_liste;
        }   
        
        d->nb_elements = d->nb_elements -1;
    }
}

liste liste_cles(dico* d){
    //Renvoie la liste des clés d'un dictionnaire.
    liste l = NULL;
    for (int i=0; i<d->capacite; i++){
        liste_couples donnees_locales = d->donnees[i];
        while (donnees_locales != NULL){
            l = cons(donnees_locales->cle, l);
            donnees_locales = donnees_locales->suivant;
        }
    }
    return l;
}


