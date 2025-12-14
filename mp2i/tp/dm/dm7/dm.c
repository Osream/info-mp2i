#include "dm.h"

void print_liste(liste l){
  if(!est_vide_liste(l)){
    printf("-\t%d\t- \n", tete_liste(l));
    print_liste(queue_liste(l));
  }
  else{
    printf("\n");
  }
}

void divise_impair(liste l, liste* pairs, liste* impairs){
  if (!est_vide_liste(l)){
    ajouter_tete_liste(tete_liste(l), impairs);
    divise(queue_liste(l), pairs, impairs);
  }
}

int main(){
  liste test = creer_liste();
  ajouter_tete_liste(1, &test);
  ajouter_tete_liste(1, &test);
  ajouter_tete_liste(1, &test);
  ajouter_tete_liste(1, &test);
  ajouter_tete_liste(1, &test);
  ajouter_tete_liste(1, &test);
  ajouter_tete_liste(1, &test);
  ajouter_tete_liste(1, &test);
  print_liste(test);
  liste fuss = tri_fusion(test);
  print_liste(fuss);
  liste part = tri_rapide(test);
  print_liste(part);
  detruire_liste(part);
  detruire_liste(fuss);
  detruire_liste(test);
}

void divise(liste l, liste* pairs, liste* impairs){
   if (!est_vide_liste(l)){
    ajouter_tete_liste(tete_liste(l), pairs);
    divise_impair(queue_liste(l), pairs, impairs);
  }
}

liste fusion(liste l1, liste l2){
  if (est_vide_liste(l1)){
    return copie_liste(l2);
  }
  else if (est_vide_liste(l2)){
    return copie_liste(l1);
  }
  else{
    if (tete_liste(l1) > tete_liste(l2)){
      liste suite = fusion(l1, queue_liste(l2));
      ajouter_tete_liste(tete_liste(l2), &suite);
      return suite;
    } 
    else { 
      liste suite = fusion(queue_liste(l1), l2);
      ajouter_tete_liste(tete_liste(l1), &suite);
      return suite;
    }
  }
}

liste tri_fusion(liste l){
  if (est_vide_liste(l)){
    return creer_liste();
  }
  else if(est_vide_liste(queue_liste(l))){
    return copie_liste(l);
  }
  else{
    liste pairs = creer_liste();
    liste impairs = creer_liste();
    divise(l, &pairs, &impairs);
    liste suite1 = tri_fusion(pairs);
    liste suite2 = tri_fusion(impairs);
    liste res = fusion(suite1, suite2);
    detruire_liste(pairs);
    detruire_liste(impairs);
    detruire_liste(suite2);
    detruire_liste(suite1);
    return res;
  }
}

void partition(liste l, int pivot, liste* inf, liste* sup){
  if(!est_vide_liste(l)){
    if (tete_liste(l) > pivot){
      ajouter_tete_liste(tete_liste(l), sup);
      partition(queue_liste(l), pivot, inf, sup);
    }
    else{
      ajouter_tete_liste(tete_liste(l), inf);
      partition(queue_liste(l), pivot, inf, sup);
    }
  }
}

liste tri_rapide(liste l){
  if(est_vide_liste(l)){
    return creer_liste();
  }
  else if(est_vide_liste(queue_liste(l))){
    return copie_liste(l);
  }
  else{
    liste inf = creer_liste();
    liste sup = creer_liste();
    partition(queue_liste(l), tete_liste(l), &inf, &sup);
    liste suite1 = tri_rapide(inf);
    liste suite2 = tri_rapide(sup);
    ajouter_tete_liste(tete_liste(l), &suite2);
    liste res = concat_liste(suite1, suite2);
    detruire_liste(inf);
    detruire_liste(sup);
    detruire_liste(suite1);
    detruire_liste(suite2);
    return res;
  }
}
