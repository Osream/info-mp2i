# Chapitre 7 : Décomposition d'un problème en sous-problèmes

## I. Diviser pour régner

### 1. Principe

Principe des algorithmes de type « diviser pour régner » :

* **diviser** : décomposer le problème initial en plusieurs sous-problèmes indépendants de taille significativement inférieure
* **régner** : résoudre récursivement les sous-problèmes
* **combiner** : reconstituer la solution au problème initial à partir des solutions des sous-problèmes

Exemple pour lequel cette méthode est pertinente : l'algorithme de recherche dichotomique.

Exemple pour lequel cette méthode n'est pas pertinente : la recherche du maximum d'un tableau.

### 2. Complexité

Avec $`n`$ la taille du problème initial, si on divise le problème en $`a`$ sous-problèmes de taille $`\frac n b`$ (en omettant les parties entières), on obtient une relation de la forme suivante pour la complexité :

$`C(n) = a\times C(\frac n b) + f(n), \text{ avec }f\text{ la complexité des étapes \it{diviser} et \it{combiner}}`$

On commence toujours l'analyse pour le cas où $`n = b^k`$ : $`C(b^k) = a\times C(b^{k-1})+f(b^k)`$.

On trouve $`C(b^k) = \displaystyle\sum_{i=0}^k {a^if(b^{k-i})}`$, résultat expliqué par le schéma suivant :

![](img/div_regner_arbre.png)

On déduit le cas général en remarquant que $`C(b^{\lfloor \log_b n \rfloor}) \leqslant C(n) \leqslant C(b^{\lceil \log_b n \rceil})`$.

### 3. Tri fusion

Principe du tri fusion.

Complexité du tri fusion.

### 4. Rencontre au milieu

Principe des algorithmes de type « rencontre au milieu ».

Comparaison avec la méthode « diviser pour régner ».

## II. Algorithmes gloutons

### 1. Principe

Définition d'un problème d'optimisation.

Principe des algorithmes de type « gloutons » : la solution est décomposée en une série de choix successifs localement optimaux sur lesquels on ne revient jamais et sans anticipation des choix futurs.

Avantage en terme de complexité.

Inconvénient : la solution globale n'est pas toujours optimale.

### 2. Le problème de rendu de monnaie

Énoncé du problème.

Choix glouton localement optimal pour ce problème.

Écriture de l'algorithme.

Étude de l'optimalité de la solution.

## III. Programmation dynamique

### 1. Exemples introductifs

Suite de Fibonacci : complexité de la fonction récursive « simple » ; mise en place de la mémoïsation ; construction de la suite de bas en haut ; complexité optimale.

Impact de la programmation dynamique sur la complexité temporelle.

Coefficients binomiaux avec la formule de Pascal : programmation dynamique avec un tableau bidimensionnel ; puis avec un tableau associatif.

Impact de la programmation dynamique sur la complexité spatiale.

### 2. Principe

La programmation dynamique s'utilise typiquement pour résoudre des problèmes de combinatoire et d'optimisations.

Méthodologie pour la mise en place de la programmation dynamique :

* identification des sous-problèmes
* chevauchement des sous-problèmes
* choix de la structure de donnée pour le stockage des résultats
* écriture de l'algorithme de bas en haut ou récursif avec mémoïsation
* reconstruction de la solution optimale à partir de l'information calculée

### 3. Le problème de rendu de monnaie

Mise en place de la méthodologie sur un problème concret.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : J.B. Bianquis
