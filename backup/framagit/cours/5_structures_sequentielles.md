# Chapitre 5 : Structures de données séquentielles

La conception d'un algorithme va de pair avec la conception d'une structure de données adéquate permettant de minimiser les complexités des opérations fréquentes.

## I. Abstraction / Implémentation

### 1. Définitions

Définitions d'abstraction, d'interface, d'implémentation d'une structure de données.

Notion de programmation modulaire.

Différents types des opérations de l'interface : constructeur, accesseur, transformateur, destructeur.

Caractéristiques des structures de données : mutable / immuable, dynamique / statique.

### 2. Un exemple : les tableaux

Interface et caractéristiques de la structure de tableau.

Implémentation des tableaux en OCaml et en C.

## II. Listes

### 1. Interface

Fonctions de l'interface principale d'une liste.

### 2. Implémentation par maillons chaînés

Définition d'un maillon et d'une liste chaînée, schémas.

Complexité des opérations de l'interface avec cette implémentation.

Implémentation d'une liste chaînée en C.

### 3. Implémentation avec un tableau

Implémentation avec un tableau de taille statique : schémas, complexité des opérations de l'interface.

Implémentation avec un tableau de taille dynamique : schémas, complexité des opérations de l'interface.

Comparaison des deux implémentations.

### 4. Variantes

Listes doublement chaînées, listes chaînées circulaires, tableau circulaire, listes auto-organisées.

## III. Piles et Files

### 1. Intérêt

Exemples de problèmes et besoins en termes de structures de données pour les résoudre.

Principes LIFO (dernier entré premier sorti) et FIFO (premier entré premier sorti).

### 2. Structure de pile

Interface d'une pile et schémas.

Implémentation avec des maillons chaînés ; complexité des opérations.

Implémentation avec un tableau ; complexité des opérations.

### 3. Structure de file

Interface d'une file et schémas.

Implémentation avec des maillons chaînés et pointeurs vers le premier et dernier maillon ; complexité des opérations.

Implémentation avec deux listes simplement chaînées ; complexité des opérations.

Implémentation avec un tableau circulaire ; complexité des opérations.

### 4. Piles et files en OCaml

Types `'a Stack.t` et `'a Queue.t`.

Fonctions `create, is_empty, push, pop`, exception `Empty`.

Implémentations.

## IV. Tableaux associatifs

### 1. Abstraction

Définition d'un tableau associatif.

Interface de la structure.

L'ensemble des clés doit être totalement ordonné.

### 2. Implémentation

Implémentation naïve avec des maillons chaînés.

Implémentation avec un tableau si l'ensemble des clés est $`\mathbb N`$.

Implémentation avec une table de hachage : fonction de hachage, hash des clés, taille variable de la table de hachage, gestion des collisions ; complexité des opérations avec cette implémentation.

### 3. Tableaux associatifs en OCaml

Type `('a, 'b) Hashtbl.t`.

Fonctions `create, add, remove, mem, find, find_opt, iter`, exception `Not_found`.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
