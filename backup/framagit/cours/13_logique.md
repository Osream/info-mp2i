# Chapitre 13 : Logique

La logique définit formellement :

* le langage qu'on utilise = aspects syntaxiques
* son interprétation = aspects sémantiques

## I. Syntaxe des formules propositionnelles

### 1. Définition d'une formule propositionnelle

Définition d'une variable propositionnelle.

Définition des constantes logiques $`\top, \bot`$.

Définition inductive de l'ensemble des formules propositionnelles.

### 2. Représentation arborescente

Représentation arborescente d'une formule propositionnelle.

Lien entre l'écriture d'une formule et les parcours de l'arbre.

Arité d'un connecteur logique.

Implémentation des formules propositionnelles en C et en OCaml.

### 3. Fonctions sur l'ensemble inductif des formules propositionnelles

Définition inductive de la taille d'une formule propositionnelle.

Définition inductive de la hauteur d'une formule propositionnelle.

Définition inductive d'une sous-formule d'une formule propositionnelle.

Définition inductive de la substitution d'une variable propositionnelle $`x\in \mathcal V`$ par une formule $`\psi`$ dans une formule propositionnelle $`\varphi`$, notée $`\varphi[\psi/x]`$.

### 4. Logique du premier ordre

Définition d'un domaine comme d'un ensemble de variables, de fonctions et de prédicats.

Définition d'un terme et d'un atome.

Quantificateurs universel et existentiel.

Définition inductive d'une formule du premier ordre.

Variables liées, variables libres, portée.

## II. Sémantique du calcul propositionnel

### 1. Valeurs de vérité d'une formule propositionnelle

Valeurs de vérité V, F.

Définition d'une valuation, nombre de valuations d'une formule propositionnelle.

Fonctions booléennes associées aux connecteurs logiques $`\lnot, \lor, \land, \rightarrow, \leftrightarrow`$.

Table de vérité associée à une fonction booléenne, nombre de tables de vérité distinctes en fonction du nombre de variables propositionnelles des formules.

Définition inductive de l'évaluation d'une formule propositionnelle $`\varphi`$ par une valuation $v$, notée $`[\![\varphi]\!]_v`$.

Définition d'un modèle, d'un ensemble de modèles d'une formule propositionnelle.

Satisfiabilité d'une formule, tautologie, antilogie.

### 2. Équivalence et conséquence logique

Conséquence logique entre deux formules notée $`\varphi \vDash \psi`$, généralisation à un ensemble de formules $`\Gamma \vDash \psi`$.

Équivalence logique, notée $`\varphi \equiv \psi`$.

Propriétés : impact d'une substitution sur l'équivalence logique entre deux formules.

Équivalences fondamentales : lois de De Morgan, tiers exclus, décomposition de l'implication, etc.

### 3. Systèmes complets de connecteurs

Autres connecteurs usuels (nand, nor, xor, ...).

Définition d'un système complet de connecteurs.

Propriété : $`\{\lnot, \land, \lor\}`$ est un système complet de connecteurs.

## III. Problème SAT

### 1. Formes normales

#### a. Formes normales simples

Définitions : littéral, forme normale négative, clauses conjonctive et disjonctive, forme normale disjonctive (FND), forme normale conjonctive (FNC).

Mise sous forme normale.

Représentation des formes normales comme des listes de listes de littéraux.

#### b. Formes normales canoniques

Définitions : min-terme, max-terme, FND canonique, FNC canonique.

Mise sous forme normale canonique depuis la table de vérité d'une formule propositionnelle.

Si une formule est une tautologie, alors sa FNC canonique ne contient aucun max-terme. Si c'est une antilogie, alors sa FND canonique ne contient aucun min-terme.

Le nombre de min-termes dans la FND canonique additionné au nombre de max-termes dans la FNC canonique d'une formule propositionnelle à $n$ variables propositionnelles est égal à $`2^n`$.

### 2. Problème `k`-SAT

#### a. Définitions

Définition du problème SAT, du problème `k`-SAT.

Réduction d'un problème à SAT.

#### b. Cas particuliers de 1-SAT et 2-SAT

Problème 1-SAT : principe de la résolution et complexité.

Problème 2-SAT : représentation du problème par un graphe orienté.

Théorème (et preuve) : une instance de 2-SAT est satisfiable si et seulement si dans le graphe associé, aucune composante fortement connexe ne contient à la fois une variable propositionnelle et sa négation.

#### c. Algorithme de Quine

La résolution de `k`-SAT pour `k` > 2 a un complexité exponentielle : on utilise un algorithme de recherche exhaustive

* soit une recherche par force brute, qui consiste à dresser la table de vérité de la formule
* soit une recherche par retour sur trace (backtracking), c'est l'algorithme de Quine.

Principe de l'algorithme de Quine, représentation arborescente de l'algorithme.

Règles de simplification de Quine (pour éliminer les constantes).

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
