# Fondamentaux du TP : Structures récursives en C

* Distinguer interface et implémentation (notamment être à l'aise avec l'organisation des fichiers quand on crée une structure de données).
* Utiliser des assertions (vérification des préconditions et vérification pour le `malloc`).
* Implémenter une liste chaînée en C :
    * créer une structure pour représenter un maillon ;
    * créer un alias `liste` étant un pointeur vers le premier maillon ;
    * implémenter les 6 fonctions de l'interface d'une liste : `liste creer_liste(void), bool est_vide_liste(liste), void ajouter_tete_liste(contenu, liste*), contenu tete_liste(liste), liste queue_liste(liste), void detruire_liste(liste)` ;
    * calculer la complexité de ces 6 fonctions.

* Écrire une fonction récursive qui parcourt une liste en utilisant uniquement les 6 fonctions de l'interface (par exemple pour calculer la taille d'une liste).


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
