#include "arbre.h"


struct noeud_s{
  etiq etiquette;
  struct noeud_s* gauche;
  struct noeud_s* droit;
};

ab cree_ab_vide(void){
  return NULL;
}

ab noeud(etiq e, ab g, ab d){
  ab res = malloc(sizeof(struct noeud_s));
  assert(res != NULL);
  res->etiquette = e;
  res->gauche = g;
  res->droit = d;
  return res;
}

void libere_ab(ab a){
  if(a != NULL){
    libere_ab(a->gauche);
    libere_ab(a->droit);
    free(a);
  }
}

bool est_vide_ab(ab a){
  return NULL == a;
}

etiq etiquette_racine(ab a){
  assert(a != NULL);
  return a->etiquette;
}

ab sous_arbre_gauche(ab a){
  assert(a != NULL);
  return a->gauche;
}

ab sous_arbre_droit(ab a){
  assert(a != NULL);
  return a->droit;
}

int taille_ab(ab a){
  if (a == NULL){
    return 0;
  }
  else{
    return 1 + taille_ab(a->droit) + taille_ab(a->gauche);
  }
}

int hauteur_ab(ab a){
  if(a == NULL){
    return -1;
  }
  else{
    int suite_gauche = hauteur_ab(a->gauche);
    int suite_droit = hauteur_ab(a->droit);
    if (suite_gauche> suite_droit){
      return 1 + suite_gauche;
    }
    else{
      return 1 + suite_droit;
    }
  }
}

// Quelques fonctions en plus :

etiq somme_ab(ab a){
  if(a == NULL){
    return 0; 
  }
  else{
    return a->etiquette + somme_ab(a->gauche) + somme_ab(a->droit);
  }
}

bool egaux_ab(ab a1, ab a2){
  if (a1 == NULL || a2 == NULL){
    return a1 == a2;
  }
  else{
    return (a1->etiquette == a2->etiquette) 
    && egaux_ab(a1->gauche, a2->gauche) 
    && egaux_ab(a1->droit, a2->droit);
  }
}


bool appartient_ab(ab a, etiq e){
  if (a == NULL){
    return false;
  }
  else if (a->etiquette == e){
    return true;
  }
  else{
    return appartient_ab(a->gauche, e) || appartient_ab(a->droit, e);
  }
}

// Fonctions des Arbres Binaires stricts
ab feuille(etiq e){
    return noeud(e, NULL, NULL);
}

ab noeud_strict(etiq e, ab g, ab d){
  assert(g != NULL && d != NULL);
  return noeud(e, g, d);
}

bool est_feuille(ab a){
  assert(a != NULL);
  return a->droit == a->gauche && a->gauche == NULL;
}

int nombre_de_fauilles(ab a){
  assert(a != NULL);
  int comptage_aux(ab a){
    if(a->gauche == NULL && a->droit == NULL){
      return 1;
    }
    else {
      return comptage_aux(a->gauche) + comptage_aux(a->droit);
    }
  }
  return comptage_aux(a);
}

etiq derniere_feuille(ab a){
  assert(a != NULL);
  etiq parcours_aux(ab a){
    if(a->droit == NULL){
      return a->etiquette;
    }
    else{
      return parcours_aux(a->droit);
    }
  }
  return parcours_aux(a);
}

bool est_strict_ab(ab a){
  if(a == NULL){
    return false;
  }
  else if(a->droit == a->gauche && a->gauche==NULL){
    return true;
  }
  else{
    return est_strict_ab(a->gauche) && est_strict_ab(a->droit);
  }
}
