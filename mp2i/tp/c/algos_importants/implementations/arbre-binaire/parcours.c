#include "arbre.h"
#include "../file/files.h"

void profondeur_prefixe(ab a){
  void parcours_aux(ab a){  
    if (est_feuille(a)){
      printf("%d "etiq_racine(a));
    }
    else{
      printf("%d " etiq_racine(a));
      parcours_aux(a->gauche);
      parcours_aux(a->droit);
    }
  }
  parcours_aux(a);
  printf("\n");
}

void profondeur_infixe(ab a){
  void parcours_aux(ab a){  
    if (est_feuille(a)){
      printf("%d "etiq_racine(a));
    }
    else{      
      parcours_aux(a->gauche);
      printf("%d " etiq_racine(a));
      parcours_aux(a->droit);
    }
  }
  parcours_aux(a);
  printf("\n");
}

void profondeur_prefixe(ab a){
  void parcours_aux(ab a){  
    if (est_feuille(a)){
      printf("%d "etiq_racine(a));
    }
    else{
      parcours_aux(a->gauche);
      parcours_aux(a->droit);
      printf("%d " etiq_racine(a));
    }
  }
  parcours_aux(a);
  printf("\n");
}

void parcours_largeur(ab a){
  file f = creer_file();
  enfiler(f, a);
  while(!est_vide_file(f)){
    ab iter = defiler(f);
    if (!est_feuille(iter)){
      enfiler(f, iter->gauche);
      enfiler(f, iter->droit);
    }
    printf("%d ", etiq_racine(iter));
  }
  printf("\n");
  detruire_file(f);
}
