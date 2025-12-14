# Chapitre 12 : Ensemble Ordonnées et inductifs

## Partie 0: À savoir

### Vocabulaire à connaître

- __Ensembles ordonnés:__
  - reflexive, transitive, symétrie, anti-symétrie
  - relation d'équivalence
  - relation d'ordre
  - prédécesseur.successeur $\pm$ immédiat
  - ordre __total__
  - elt minimal / maximal
  - minimum / maxium
  - ensemble __bien fondé__
- __Ensembles inductifs:__
  - assertion, règle d'inférence
  - __dérivation__
  - __ambiguté__

### Savoir faire

- __Ensembles ordonnés:__
  - Dessiner le graphe associé à un ensemble ordonné (p.4 du poly)
- __Ensembles inductifs:__
  - définir un ensemble inductivement
  - preuves par induction structurelle
  - définition d'une fonction sur les ensembles inductifs

### À savoir par coeur

- ⚠️ Théorème page 6. "Ensemble bien fondé $\iff$ il n'existe pas de suite infinie strictement décroissante."
- Méthode pour la terminaison.

  1. Munir chaque {variable de boucle}/{paramètre de la fonction récursive}  d'un ordre bien fondé. Munir l'ensemble d'un ordre produit / lexicographique qui est par définition bien fondé.

  2. Montrer sa stricte décroissance {d'un appel rec au suivant}/{d'une itération à la suivante}.

  3. citer le théorème ci dessus pour justifier que le nombre {d'appels réc}/{d'itérations} est bien fini puis vérifier la terminaison du reste des instruction.
  
- Un ensemble inductif est toujours bien fondé.

__La suite du fichier donne la corréction de la plupart des exos du poly.__

## I. Ensembles ordonnées

### 2. Relation d'équivalence

- Tout sommet est accessible de lui même par un chemin de longueur 0. $\to R$ est reflexive.
- En mettant bout à bout les chemin on a la transitivité de $R$
- La symétrie est triviale.

### 3. Relations d'ordre

#### Exo 1. 2. $x \leadsto y \iff y \text{ accessible depuis } x$

- Même argument pour la réflexibilité.
- IDEM pour la transitivité.
- Comme le graphe est acyclique si 2 sommets $\neq$ alors on a un cycle ce qui n'est pas possible. D'où l'anti-symétrie.

#### Exo 2. Dessiner le graphe de la divisibilité dans $[\![1, 12]\!]$

![image](../ressources/chap_12/graphe_ensemble_ordonnée.png)

#### Exo 4. Preuve de la propriété

Par l'absurde: Si le graphe est cyclique.
Alors il existe un chemin de taille $n$ (non nul) tel que $s_1 s_2\dots s_n s_1$ soit un cycle.
Donc $s_2 \prec s_n$ et $s_n \prec s_2$, absurde.
Donc le graphe est acyclique.

### 5. Retour sur la terminaison des fonctions

#### b. terminaison d'une boucle

*Q1.*

$x \in \mathbb{N}$ et $y \in \mathbb{N}$ et $(\mathbb{N}, \leq)$ est bien fondé donc par définition l'ordre lexicographique sur $(x, y)$ est bien fondé.
Soit $\tilde x, \tilde y$ les valeurs de $x$ et $y$ en fin d'itération. Montrons que $(\tilde x, \tilde y) < (x, y)$ selon l'ordre lexicographique:

- 1er cas `SI` $\tilde x = x$ et $\tilde y = y -1$ or $(x, y-1) < (x, y)$
- 2eme cas `SINON` $\tilde x = x-1$ et $\tilde y = 4x + 7$ or $(x-1, 4x+7) < (x, y)$

Il n'existe pas de suite infinie strictement décroissante à valeurs dans un ensemble bien fondé. Donc le nombre d'itération de la boucle est finie. Le reste des instructions terminent trivialement, donc la boucle termine.

*Q2.*

$n \in \mathbb{N}$ et $m \in \mathbb{N}$ et $(\mathbb{N}, \leq)$ est bien fondé donc par définition l'ordre lexicographique sur $(n, m)$ est bien fondé.
Soit $\tilde n, \tilde m$ les valeurs de $n$ et $m$ en fin d'itération. Montrons que $(\tilde n, \tilde m) < (n, m)$ selon l'ordre lexicographique:

- 1er cas `SI` $\tilde n = n$ et $\tilde m = m - n$ or $(n, m-n) < (n, m)$
- 2eme cas `SINON` $\tilde n = n-1$ et $\tilde m = 2m$ or $(n-1, 2m) < (n, m)$

Il n'existe pas de suite infinie strictement décroissante à valeurs dans un ensemble bien fondé. Donc le nombre d'itération de la boucle est finie. Le reste des instructions terminent trivialement, donc la boucle termine.

*Q3.*

Ordre lexicographique avec $(l-i, c-j)$.

#### c. terminaison d'une fonction récursive

*Q1.*

$a \in \mathbb{N}$, $b \in \mathbb{N}$ et $c \in \mathbb{N}$ et $(\mathbb{N}, \leq)$ est bien fondé donc par définition l'ordre lexicographique sur $(a, b, c)$ est bien fondé.
Soit $\tilde a, \tilde b, \tilde c$ les valeurs de $a$, $b$ et $c$ en fin d'itération. Montrons que $(\tilde a, \tilde b, \tilde c) < (a, b, c)$ selon l'ordre lexicographique:

- Les 2 premier cas termine trivialement.
- 3eme cas `a = b + c`
  - 1er appel : $\tilde a = a$, $\tilde b = 0$ et $\tilde c = c-1$ or $(a, 0, c-1) < (a, b, c)$
  - 2eme appel : $\tilde a = a$, $\tilde b = b-1$ et $\tilde c = x \in \mathbb{N}$ or $(a, b-1, x) < (a, b, c)$
- 4eme cas `SINON`
  - 1er appel : $\tilde a = a$, $\tilde b = b-1$ et $\tilde c = c+1$ or $(a, b-1, c+1) < (a, b, c)$
  - 2eme appel : $\tilde a = a$, $\tilde b = b$ et $\tilde c = c-1$ or $(a, b, c-1) < (a, b, c)$
  - 3eme appel : $\tilde a = a-1$, $\tilde b = x \in \mathbb{N}$ et $\tilde c = y \in \mathbb{N}$ or $(a-1, x, y) < (a, b, c)$

Il n'existe pas de suite infinie strictement décroissante à valeurs dans un ensemble bien fondé. Donc le nombre d'itération de la boucle est finie. Le reste des instructions terminent trivialement, donc la boucle termine.

*Q2.*

Exercice laissé au soin du lecteur.

## II. Ensembles inductifs

### 1. définition des ensembles inductifs

#### Exercie d'application de la défintion

*Q1.*

- Assetion : $n = 0$ pour les entiers pairs $n = 1$ pour les impairs.
- Règle d'inférence : Soit $n$ un entier pair/impair $S = n \pm 2$.

*Q2.*

$\mathbb{Z}^*$

*Q3.*

Voir chapitre sur les arbres.

#### Application de la définition de la dérivation

On note $S_1 = x \mapsto 2x$, $S_2 = x \mapsto 2x + 1$ et $S_3 = x \mapsto -x$. Alors $-14 = S_3(S_2(S_1(S_1(\mathbb(1)))))$

#### Définition de l'ambiguité

1. Non ambigüe
2. ambigüe
3. ambigüe

### 3. Fonctions sur un ensemble inductif

#### Définition de fonctions sur un ensemble inductif

L'addition sur deux entier naturels :

- Pour $n \in \mathbb{N}$: $n + 0 = n$
- Soit $n$ et $n_2 \in \mathbb{N}$. On note $S(n_2) = n_2 + 1$. On a $n + S(n_2) = S(n + n_2)$

La multiplication deux deux entiers:

- Pour $n \in \mathbb{N}$: $n \times 0 = 0$
- Soit $m \in \mathbb{N}$, on note le $S(m)$ le suivant de $m$. Alors $n \times S(m) = n \times m + n$

La factorielle:

- Pour $n = 0$ : $0! = 1$
- Soit $n \in \mathbb{N}$. $S(n)! = S(n) \times n!$

#### Écriture des fonctions inductives

```Ocaml
type entier = Zero | S of entier

let rec somme n m = 
  match m with
  | Zero-> n
  | S m -> S (somme n m)
  
let rec produit n m =
  match m with
  | Zero -> Zero
  | S m -> somme (produit n m) n

let rec factorielle n =
  match n with
  | Zero -> S Zero
  | S n -> produit (S n) (factorielle n)
```
