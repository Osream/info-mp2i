# Chapitre 4 : Analyse d'algorithmes

## I. Introduction à l'algorithmique

### 1. Objectifs de l'algorithmique

Définition de la notion d'« algorithmique ».

Divers aspects de l'algorithmique : conception de nouveaux algorithmes, amélioration d'algorithmes existants, analyse des algorithmes.

Objectif : éviter les bugs (ex : dépassement de capacité, boucle infinie, cas particulier non prévu, ...).

### 2. Spécification des algorithmes

Pour prouver formellement qu'un algorithme est correct, on doit connaître sa spécification.

Entrées, sorties, préconditions, postconditions.

La spécification définit strictement le contrat que doit respecter l'algorithme.

### 3. Généralités sur l'analyse d'un algorithme

On analyse les algorithmes en supposant que les préconditions sont vérifiées.

On analyse les propriétés suivantes des algorithmes : terminaison, correction, complexité (temporelle et spatiale).

#### a) Terminaison

Définition de la terminaison d'un algorithme.

Le nombre d'étapes après lequel l'algorithme doit renvoyer sa sortie est fini mais non borné.

La terminaison de certaines instructions est immédiate (ex : affectation), d'autres peuvent ne pas terminer (boucles, fonctions récursives).

Montrer la terminaison d'un algorithme revient à montrer la terminaison de toutes les boucles et fonctions récursives impliquées dans l'algorithme.

#### b) Correction

La correction d'un algorithme s'intéresse à ses postconditions : l'algorithme renvoie-t-il le bon résultat ? a-t-il le bon effet de bord ?

Définition de la correction partielle et de la correction totale d'un algorithme.

Distinction entre correction partielle et correction totale sur un exemple simple.

La correction de certaines instructions est immédiate (ex : affectation), d'autres demandent un travail supplémentaire (boucles, fonctions récursives).

Montrer la correction partielle d'un algorithme revient à montrer la correction partielle de toutes les boucles et fonctions récursives impliquées dans l'algorithme. Montrer la correction totale d'un algorithme revient à montrer la correction partielle et la terminaison de toutes les boucles et fonctions récursives impliquées dans l'algorithme.

#### c) Complexité

Définition du terme « complexité ».

Comment mesurer le temps d'exécution d'un algorithme ? la mémoire utilisée par cet algorithme ?

Définition de la complexité spatiale d'un algorithme.

Définition de la complexité temporelle d'un algorithme.

On exprime les complexités en fonction de la taille des entrées.

## II. Preuves de terminaison et correction

### 1. Décidabilité des deux problèmes

Peut-on écrire un algorithme qui prend en entrée un autre algorithme et détermine s'il termine pour une entrée donnée ?

Preuve par l'absurde qu'un tel algorithme n'existe pas.

Cet algorithme n'est pas calculable, le problème de l'arrêt n'est donc pas décidable.

Peut-on écrire un algorithme qui prend en entrée un autre algorithme et détermine s'il est correct pour une entrée donnée ? Non : de manière générale, toute question sémantique (non triviale) au sujet d'un algorithme est indécidable.

### 2. Terminaison et correction des boucles

#### a) Non terminaison et non correction

Montrer la non terminaison d’une boucle revient à exhiber une situation pour laquelle la boucle ne termine pas.

Exemples de boucles qui ne terminent pas.

Montrer la non correction d’une boucle revient à exhiber une situation pour laquelle le résultat en sortie de boucle n'est pas celui attendu.

Exemples de boucles non correctes.

### b) Terminaison

Définition d'un variant de boucle.

Théorème (et preuve) : Une boucle composée d'instructions qui terminent et admettant un variant termine.

Pour montrer qu'une quantité entière est bien un variant de boucle, on montre que sa valeur est positive juste avant la boucle, reste positive tant que la condition de la boucle est vérifiée, et décroît strictement à chaque itération.

Exemples de preuves de terminaison sur certains algorithmes du programme.

### c) Correction

Définition d'un invariant de boucle.

Théorème: Une boucle composée d'instructions correctes et admettant un invariant est partiellement correcte. Si en plus elle termine, elle est totalement correcte.

Pour montrer qu'une boucle est correcte, il faut trouver un invariant et montrer qu'il est vrai juste avant la boucle, et que s'il est vrai au début d'une itération il l'est toujours à la fin de cette itération. À la sortie de la boucle, l'invariant est donc toujours vrai et il doit permettre de justifier que la boucle a eu l'effet voulu sur les postconditions.

Exemples de preuves de correction sur certains algorithmes du programme.

### 3. Terminaison et correction des fonctions récursives

Les preuves de terminaison et correction se font par récurrence.

Exemples de preuves sur certains algorithmes du programme.

## III. Complexités temporelle et spatiale

### 1. Types de complexité

#### a) Différents cas

Définitions : complexité temporelle dans le pire des cas, complexité temporelle dans le meilleur des cas, complexité temporelle dans le cas moyen.

Définitions : complexité spatiale dans le pire des cas, complexité spatiale dans le meilleur des cas, complexité spatiale dans le cas moyen.

Par défaut, on s'intéresse à la complexité temporelle dans le pire des cas, en étudiant le comportement asymptotique de la suite.

#### b) Notations de Landau

Définition des notations $`\mathcal O, \Omega, \Theta`$.

Liens entre les notations et les types de complexité.

Opérations sur les $`\mathcal O`$.

#### c) Complexités usuelles

Complexités usuelles : constante, logarithmique, linéaire, quasi-linéaire, quadratique, polynomiale, exponentielle.

Complexités temporelles des opérateurs et fonctions (OCaml et C) à connaître.

#### d) Notion de complexité amortie

Situation pour laquelle le calcul d'une complexité amortie est pertinent.

Méthodologie pour le calcul.

Exemple sur les tableaux de taille dynamique comme le type `list` de Python.

### 2. Calculs de complexité

#### a) Complexité spatiale

Méthodologie pour le calcul de la complexité spatiale d'un algorithme.

Exemples de calculs de complexité spatiale sur certains algorithmes du programme.

#### b) Complexité temporelle des algorithmes impératifs

Règles de calculs pour chaque instruction des algorithmes impératifs.

Exemples de calculs de complexités de boucles bornées et non bornées.

Complexité temporelle de l’algorithme de recherche dichotomique.

#### c) Complexité temporelle des algorithmes fonctionnels

On obtient naturellement une relation de récurrence pour la complexité, il s'agit ensuite de retrouver le terme général.

Exemples de calculs de complexités de fonctions récursives.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*
