# Chapitre 6 : Validation de programmes

« Beware of bugs in the above code ; I have only proven it correct, not tried it. » — Donald Knuth.

## I. Gestion de la mémoire

### 1. Mémoire physique $`\leftrightarrow`$ Mémoire virtuelle

Mémoire physique : gestion des registres par le compilateur, du cache par le processeur, de la RAM par le système d'exploitation.

Mémoire virtuelle : ensemble d'adresses virtuelles fournies à un processus, qui vit alors comme s'il était seul en mémoire.

Organisation de la mémoire virtuelle :

![](img/7_validation/gestion_memoire.png)

### 2. Durée de vie des variables

Définition de la portée syntaxique d'une variable (ou d'une fonction).

Les variables ont une portée syntaxique globale ou locale.

Définition de la durée de vie d'une variable, durée de vie des variables globales / locales.

*Pour valider un programme, il faut s'assurer qu'il ne contient aucune référence à une variable en dehors de sa portée syntaxique.*

### 3. Organisation de la pile et du tas

La pile et le tas ont une taille variable mais limitée.

Si l'allocation est statique, la donnée sera placée dans la pile ; si elle dynamique, dans le tas.

Organisation de la pile d'appels (blocs d'activation, indicateur de fond de pile).

*Pour valider un programme, il faut s'assurer qu'il n'y aurait pas de dépassement de capacité de la pile.*

Quand l'appel de fonction est terminé, le bloc d'activation est dépilé et tout ce qui appartenait à la fonction est détruit : les variables locales ont donc une durée de vie temporaire.

Passage des paramètres par valeur ou par référence.

Organisation du tas.

En OCaml la gestion est automatique (un ramasse-miettes s'occupe de la libération du tas).

*Pour valider un programme en C, il faut s'assurer que les allocations se sont bien passées, qu'il n'y a aucune fuite de mémoire, qu'on essaie pas de libérer une zone qui n'est pas sur le tas, qu'on essaie pas d'accéder à une adresse illicite* 

## II. Programmation défensive

### 1. Fichiers d'interface

Ce sont les `.mli` en OCaml et les `.h` en C.

On y place les déclarations des types et fonctions, associés à un texte explicatif (pour les fonctions, c'est leur spécification).

Exemple en OCaml.

### 2. Vérification des préconditions

Plus le langage est typé, plus on a de garanties quant au respect des préconditions.

Définition d'une assertion, fonctionnement de `assert` en C et en OCaml.

La programmation défensive n'est pas toujours applicable : une précondition peut être trop coûteuse voire impossible à vérifier.

## III. Jeu de tests

Définition d'un test, d'un jeu de tests.

« Program testing can be used to show the presence of bugs, but never to show their absence. » — Edsger Dijkstra.

### 1. Types de tests

Tests unitaires, tests de non régression, tests fonctionnels, tests de performance.

2 types de tests unitaires : boîte noire et boîte blanche.

Conception d'un jeu de tests unitaires « boîte noire » : test des limites, partitionnement du domaine d'entrée.

Conception d'un jeu de tests unitaires « boîte blanche » : graphe de flot de contrôle.

### 2. Graphes de flot de contrôle

Définition d'un graphe de flot de contrôle.

#### a. Construction d'un graphe de flot de contrôle.

* instruction conditionnelle `if b then c1 else c2` : ![](img/7_validation/flot_controle/if.png){width=40%}
* boucle non bornée `while b do c done` : ![](img/7_validation/flot_controle/while.png){width=40%}
* boucle bornée en C `for (c1;c2;c3) {c4}` : ![](img/7_validation/flot_controle/for_c.png){width=50%}
* boucle bornée en OCaml `for i = a to b do c done` : ![](img/7_validation/flot_controle/for_ocaml.png){width=50%}

Exemple sur un algorithme de calcul de PGCD par soustractions successives : ![](img/7_validation/flot_controle/pgcd.png){width=50%}

#### b. Critères de couverture

Définition d'un chemin dans un graphe de flot de contrôle; chemins faisables et infaisables.

Exemple de graphe avec un chemin infaisable : ![](img/7_validation/flot_controle/chemin_infaisable.png){width=50%}

Pour concevoir un jeu de tests, on choisit un critère de couverture, c'est-à-dire une condition que doit respecter un ensemble  de chemins du graphe.

Couverture des chemins, couverture des sommets, couvertures des arcs.

Test exhaustif d'une condition.

#### c. Conception du jeu de test

* On construit le graphe de flot de contrôle.
* On choisit un critère de couverture.
* On détermine un ensemble de chemins satisfaisant ce critère.
* Pour chaque chemin, on réalise une exécution symbolique du programme afin de trouver une entrée du programme possible pour ce chemin.

Exemple : graphe de flot de contrôle pour la suite de Syracuse et exécutions symboliques sur deux chemins :

![](img/7_validation/flot_controle/syracuse.png){width=30%}

![](img/7_validation/flot_controle/syracuse_tableaux.png){width=50%}




---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*
