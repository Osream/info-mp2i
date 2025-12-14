#include "liste.h"

struct maillon_s {
    contenu valeur;
    struct maillon_s* suivant;
};


liste creer_liste() {
    return NULL;
}

bool est_vide_liste(liste l) {
    return l == NULL;
}

void ajouter_tete_liste(contenu val, liste* l) {
    assert(l != NULL);
    maillon* m = malloc(sizeof(maillon));
    assert(m != NULL);
    m->valeur = val;
    m->suivant = *l;
    *l = m;
}

contenu tete_liste(liste l) {
    assert(!est_vide_liste(l));
    return l->valeur;
}

liste queue_liste(liste l) {
    assert(!est_vide_liste(l));
    return l->suivant;
}

void detruire_liste(liste l) {
    if (!est_vide_liste(l)) {
        detruire_liste(l->suivant);
        free(l);
    }
}


liste copie_liste(liste l){
  if (l == NULL){
    return NULL;
  }
  else {
    liste nouv = copie_liste(queue_liste(l)); 
    ajouter_tete_liste(tete_liste(l), &nouv); 
    return nouv;
  }
}

liste concat_liste(liste l1, liste l2){
  liste result = copie_liste(l2);
  liste concat_aux(liste l1, liste l2){ 
    if (l1 == NULL){
      return l2;
    }
    else { 
      liste suite = concat_aux(queue_liste(l1), l2);
      ajouter_tete_liste(tete_liste(l1), &suite);
      return suite;
    }
  }
  return concat_aux(l1, result);
}
