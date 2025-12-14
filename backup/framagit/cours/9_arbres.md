# Chapitre 9 : Arbres

## I. Généralités

Les arbres sont des structures de données hiérarchiques.

### 1. Vocabulaire

Nœuds, nœuds internes, feuilles, racine.

Liens de parenté : père, fils, frères, ancêtres, descendance.

Sous-arbre enraciné en un nœud.

Étiquettes des nœuds et/ou des arcs.

Arité d'un nœud, d'un arbre.

Profondeur d'un nœud, hauteur d'un arbre.

Taille d'un arbre.

### 2. Définition mathématique

Définition d'un arbre comme un ensemble non vide muni d'une relation binaire vérifiant certaines propriétés.

Définition des feuilles, nœuds internes, racine, profondeur d'un nœud, hauteur d'un arbre, et sous-arbre enraciné selon la définition mathématique des arbres.

### 3. Exemples d'utilisation

Arbre d'une expression arithmétique, notation infixe, polonaise et polonaise inversée. Exemple :

![](img/10_arbres/arithmetique.png){width=15%}

Trie : fonctionnement, utilité. Exemple pour l'ensemble {diane, diantre, dire, diva, divan, divin, do, dodo, dodu, don, donc, dont} :

![](img/10_arbres/trie.png){width=40%}

Arbre syntaxique : fonctionnement, utilité. Exemple :

![](img/10_arbres/syntaxique.jpg){width=40%}

Autres exemples : arbre de décision, de classification, systèmes de fichier, arbre d'appels récursifs, etc.

## II. Définition inductive des arbres binaires

Les définitions peuvent varier légèrement d'un sujet à l'autre, il faut être vigilant.

### 1. Notion d'induction structurelle

Définition d'un ensemble inductif par des assertions et des règles d'inférence.

Définition d'une fonction sur un ensemble inductif.

Preuve par induction structurelle.

Une preuve par récurrence est un cas particulier de preuve par induction structurelle, sur l'ensemble inductif des entiers naturels.

### 2. Définitions inductives des arbres binaires stricts et non stricts

Définition inductive d'un arbre binaire strict.

Définition inductive d'un arbre binaire non strict.

Les arbres sont positionnels.

Notion de sous-arbre gauche et de sous-arbre droit.

Profondeur d'un nœud dans un arbre binaire.

### 3. Fonctions sur l'ensemble inductif des arbres binaires

Définition inductive de la taille d'un arbre binaire.

Définition inductive de la hauteur d'un arbre binaire.

Théorème sur le lien entre hauteur d'un arbre et profondeur de ses nœuds, preuve du théorème par induction structurelle.

## III. Propriétés des arbres binaires

### 1. Arbres filiformes

Définition d'un arbre filiforme.

Propriétés sur les arbres filiformes et preuves par induction structurelle de ces propriétés.

Peignes gauche et droit.

### 2. Arbres complets

Arbres complets et notamment complets à gauche.

Arbres parfaits et propriétés sur les arbres parfaits (preuves par induction structurelle de ces propriétés).

### 3. Dénombrement sur les arbres binaires

Quelques propriétés sur les arbres binaires : relations entre taille et hauteur, relation entre nombre de nœuds internes et nombre de feuilles, etc.

Nombres de Catalan et rapport avec le nombre d'arbres binaires stricts de taille fixée.

Borne inférieure pour la complexité dans le pire des cas des tris par comparaison.

## IV. Parcours d'arbres binaires

Objectifs des parcours d'arbre.

### 1. Parcours en profondeur

Principe général, ordre préfixe, infixe et postfixe.

![](img/10_arbres/parcours_profondeur.png){width=40%}

Algorithmes.

Reconstruction d'un arbre binaire depuis l'énumération de ses nœuds dans l'ordre préfixe ou postfixe.

Sérialisation d'un arbre binaire strict.

### 2. Parcours en largeur

Principe général.

![](img/10_arbres/parcours_largeur.png){width=40%}

Algorithme.

Notion de forêt.

## V. Arbres d'arité quelconque

### 1. Définition, vocabulaire et parcours

Définition inductive des arbres d'arité quelconque.

Vocabulaire des arbres binaires adaptés aux arbres d'arité quelconque.

Parcours en largeur, parcours en profondeur (ordres préfixe et postfixe).

### 2. Conversion d'un arbre d'arité quelconque en un arbre binaire et inversement

Tout arbre d'arité quelconque peut être transformé en arbre binaire, la transformation doit être bijective.

Représentation « LCRS ».

![](img/10_arbres/lcrs.png){width=50%} 

Algorithmes de conversions.

### 3. Représentation informatique des arbres

Types pour représenter les arbres binaires (stricts et non stricts) et les arbres d'arité quelconque en OCaml et en C.

Représentation des arbres binaires complets à gauche dans un tableau.

![](img/10_arbres/repr_ab_complet_tableau.png){width=40%}

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*, J.B. Bianquis
