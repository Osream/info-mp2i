# Chapitre 15 : Structures à l'aide d'arbres binaires

Objectif : étudier deux manières d'organiser les étiquettes d'un arbre binaire afin de réaliser certaines opérations plus efficacement, et d'implémenter efficacement plusieurs structures de données abstraites.

## I. Arbres binaires de recherche

Objectif : réaliser une structure abstraite où la recherche d'un élément est efficace.

### 1. Arbres binaires de recherche non équilibrés (ABR)

#### a. Définition

Principe des ABR et définition inductive de l’ensemble des ABR.

Théorème : parcours infixe d'un ABR.

Propriété : hauteur d'un ABR.

#### b. Opérations élémentaires

Recherche d'un extremum : principe, définition inductive, complexité.

Recherche d'un élément quelconque : principe, définition inductive, complexité.

Insertion : principe, définition inductive, complexité.

Suppression : méthode de la fusion et méthode de la remontée d'un extremum, définitions inductives, complexité.

#### c. Implémentation d'un tableau associatif

Le tableau associatif est une structure de données abstraite, constituée d'associations clé-valeur.

Principe de l'implémentation d'un tableau associatif par un ABR.

Complexités des opérations de l'interface du tableau associatif avec cette implémentation, et comparaison avec la table de hachage.

### 2. Arbres bicolores (ARN)

Objectif : "optimiser" la hauteur des arbres binaires de recherche afin de rendre les opérations efficaces.

Définition d'un arbre binaire équilibré.

#### a. Définition

Définition d'un arbre bicolore (ou arbre rouge-noir).

Définition de la « hauteur noire » d'un ARN.

Propriété (lien entre hauteur et hauteur noire) : la hauteur d'un ARN est inférieure ou égale à deux fois sa hauteur noire.

Propriété (lien entre taille et hauteur noire) : la taille d'un ARN est supérieure ou égale à deux puissance sa hauteur noire, moins 1.

Théorème : les arbres bicolores sont équilibrés.

#### b. Opérations élémentaires

Recherche d'un extremum ou d'un élément quelconque : même principe que pour les ABR non équilibrés, complexité logarithmique en la taille de l'arbre.

Rotations gauche et droite : principe, complexité.

Insertion : principe, correction des couleurs, définition inductive, complexité.

Suppression : remontée du maximum du sous-arbre gauche, correction des hauteurs noires, puis correction des nœuds rouges ayant un fils rouge, complexité.

## II. Tas

Objectif : réaliser une structure abstraite où l'extraction d'un extremum est efficace.

### 1. Définition

Définition d'un arbre binaire complet à gauche, rappels sur la représentation par un tableau.

Propriété d’ordre des tas.

Définition d'un tas comme d'un arbre binaire complet à gauche qui respecte la propriété d'ordre des tas, et plus particulièrement d'un tas-min et d'un tas-max.

Définition alternative d'un tas par induction.

Propriétés : étiquette de la racine d'un tas ; nombre de nœuds d'un tas de hauteur $h$ ; hauteur d'un tas de taille $n$.

### 2. Opérations élémentaires

Lecture de l'élément à la racine : complexité constante.

Percolation : définition, principe d'une percolation vers le haut et d'une percolation vers le bas, algorithmes, complexités.

Insertion d'un élément : placement du nouveau nœud puis percolation vers le haut, complexité.

Suppression de l'élément à la racine : échange avec le dernier nœud puis percolation vers le bas, complexité.

### 3. Tri par tas

Principe : transformer le tableau à trier en tas puis effectuer des extractions de la racine.

```
TRI_PAR_TAS(tableau T) :
	POUR i ALLANT DE ⌊(n-2)/2⌋ À 0 FAIRE
		PERCOLER_BAS(i)
	FIN POUR
	POUR i ALLANT DE n-1 À 0 FAIRE
		tmp <- T[0]
		T[0] <- T[i]
		T[i] <- tmp
		PERCOLER_BAS(0)
	FIN POUR
```

Preuve de correction, complexité spatiale et temporelle.

### 4. File de priorité

Définition d'une file de priorité, et interface des files de priorité.

Complexité des opérations avec une implémentation naïve utilisant une liste.

Complexité des opérations avec une implémentation utilisant un tas.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
