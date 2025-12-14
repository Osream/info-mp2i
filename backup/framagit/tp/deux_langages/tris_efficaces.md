# TP : Algorithmes de tris efficaces (OCaml et C)

L'objectif de ce TP est d'étudier deux algorithmes de tris de structures de données séquentielles, respectant l'approche « diviser pour régner » : le tri fusion et le tri rapide.

> 0. Rappelez le principe des algorithmes de type « diviser pour régner ».

## I. Tris de listes

### 1. Tri fusion (OCaml)

Pour diviser une liste en deux sous-listes de tailles égales (à un élément près), il y a plusieurs manières : on peut par exemple prendre la première moitié (indices de 0 à la taille de la liste / 2) et la seconde moitié (le reste) ou encore prendre les éléments d'indices pairs et ceux d'indices impairs.

> 1. Laquelle de ces deux manières sera privilégiée pour une `'a list` ? Pourquoi ?
>
> 2. Écrivez une fonction `diviser : 'a list -> 'a list * 'a list` qui prend en entrée une liste `l` et renvoie deux listes contenant respectivement les éléments d'indices pairs et ceux d'indices impairs dans `l`.
>
>     ```ocaml
>     # diviser [4; 8; 2; 3; 7; 1; 5] ;;
>     ([4; 2; 7; 5], [8; 3; 1])
>     ```
>
> 3. Calculez rigoureusement la complexité de la fonction `diviser`.

Pour fusionner deux listes triées, il suffit de comparer leurs premiers éléments et de placer le plus petit en premier de la liste triée finale, et ainsi de suite.

> 4. Écrivez une fonction `fusion : 'a list -> 'a list -> 'a list` qui prend en entrée deux listes triées et les fusionne.
>
>     ```ocaml
>     # fusion [2; 4; 5; 7] [1; 3; 8] ;;
>     [1; 2; 3; 4; 5 ; 7; 8]
>     ```
>     
> 5. Calculez rigoureusement la complexité de la fonction `fusion`.

Finalement, l'algorithme du tri fusion (*merge sort*) consiste à :

* **Diviser.** Diviser la liste en deux sous-listes de tailles égales (à un élément près).
* **Régner.** Appliquer le tri fusion à chacune de ces deux sous-listes.
* **Combiner.** Fusionner les deux sous-listes triées.

> 6. À l'aide de schémas, déroulez un tri fusion des listes :
>     * `[4; 8; 2; 3; 7; 1; 5]`
>     * `[9; 1; 5; 4; 7; 2; 8; 3; 6]`.
> 7. Écrivez une fonction `tri_fusion : 'a list -> 'a list`.
> 8. Montrez la correction (totale) de votre algorithme de tri (autrement dit, des 3 fonctions `diviser, fusion, tri_fusion`).
> 9. Donnez une relation de récurrence pour $`C(2^k)`$, la complexité dans le pire des cas de  `tri_fusion` sur une liste de taille $`2^k`$.
> 10. Montrez alors que $`C(2^k) = \mathcal O(k\cdot2^k)`$.
> 11. Comme $`C`$ est croissante, on a donc dans le cas général $`C(2^{\lfloor \log_2 \,n\rfloor}) \leqslant C(n)\leqslant C(2^{\lceil \log_2 \,n\rceil})`$. Déduisez-en la complexité de `tri_fusion`.

Le tri fusion est un exemple d'algorithme de tri par comparaisons optimal (autrement dit, sans connaissance supplémentaire sur les données à trier, il n'existe pas d'algorithme de tri plus efficace dans le pire des cas).

### 2. Tri rapide (OCaml)

Le tri rapide est lui aussi basé sur la méthode « diviser pour régner ». Son principe :

* **Diviser.** Choisir un élément de la liste comme *pivot*, et partitionner le reste des éléments en deux sous-listes : une sous-liste contenant les éléments inférieurs au pivot, et une sous-liste contenant les autres.
* **Régner.** Appliquer le tri rapide aux deux sous-listes.
* **Combiner.** Concaténer la liste triée des éléments inférieurs au pivot, le pivot, la liste triée des éléments supérieurs au pivot.

> 12. Pour une liste chaînée, quel est l'élément le plus simple à choisir comme pivot ?
>
> 2. À l'aide de schémas, déroulez un tri rapide (en prenant comme pivot le premier élément) des listes :
>
>     * `[4; 8; 2; 3; 7; 1; 5]`
>     * `[9; 1; 5; 4; 7; 2; 8; 3; 6]`
>
> 3. Écrivez une fonction `partition : 'a list -> 'a -> 'a list * 'a list` qui prend en paramètre une liste `l` et un pivot et renvoie un couple contenant la liste des éléments de `l` inférieurs au pivot et celle des éléments supérieurs.
>
>     ```ocaml
>     # partition [8; 2; 3; 7; 1; 5] 4 ;;
>     ([2; 3; 1], [8; 7; 5])
>     ```
>
> 4. Écrivez une fonction `tri_rapide : 'a list -> 'a list`.
>
> 5. Montrez la correction des deux fonctions `partition` et `tri_rapide`.
>
> 6. Calculez la complexité de la fonction `partition`.
>
> 7. Dans le meilleur des cas, combien y a-t-il d'éléments dans chacune des deux partitions ? Pour quelle valeur du pivot obtient-on ce meilleur des cas ?
>
> 8. Même question pour le pire des cas.
>
> 9. Donnez un encadrement (avec des relations de récurrence) pour $`C(2^k)`$, la complexité du tri rapide sur une liste de taille $`2^k`$.
>
> 10. Déduisez-en la complexité dans le meilleur et dans le pire des cas du tri rapide.



## II. Tri de tableaux

### 1. Tri fusion (OCaml)

> 1. Écrivez une fonction `sous_tableau : 'a array -> int -> int -> 'a array` telle que `sous_tableau tab debut fin` renvoie un tableau composé des éléments de `tab` compris entre les indices `debut` et `fin` inclus.
> 2. Écrivez une fonction `fusion_tableaux 'a array -> 'a array -> 'a array` qui renvoie la fusion de deux tableaux triés.
> 3. Déduisez-en une fonction `tri_fusion_tableau : 'a array -> 'a array`.
> 4. Montrez soigneusement la correction (totale) de vos fonctions.
> 5. La complexité est-elle la même que le tri fusion d'une `'a list` ?

### 2. Tri rapide (C)

Un inconvénient des tris précédents est la gestion de la mémoire : on crée de nouvelles listes / tableaux à chaque appel récursif ce qui se révèle assez gourmand.

Nous allons implémenter un tri rapide d'un tableau en C. On cherchera à partitionner le tableau passé en entrée par effet de bord : on ne crée pas de nouveau tableau dans l’étape de partition mais on réorganise le tableau passé en entrée.

Une façon de partitionner le tableau entre les indices `debut` et `fin`, appelée **technique de Lomuto**, consiste à :

* On choisit `tab[fin]` comme pivot.

* On initialise une variable `k` à `debut`.

* Pour `i` allant de `debut` à `fin-1` on maintient l'invariant suivant :

    * les éléments d'indices `debut` à `k-1` sont inférieurs au pivot
    * les éléments d'indice `k` à `i` sont supérieurs au pivot

    (pour ce faire si `tab[i]` est supérieur au pivot on ne fait rien, sinon on échange les éléments d'indices `i` et `k` et on incrémente `k`).

* Quand la boucle est terminée, on place le pivot à sa place en échangeant les éléments aux indices `k` et `fin` et on renvoie `k`.

> 6. Écrivez une fonction `int partition_lomuto(int t[], int debut, int fin)` qui partitionne le tableau selon cette méthode.
> 7. Écrivez une fonction `void tri_rapide_aux(int tab[], int debut, int fin)` qui trie par effet de bord le tableau `tab` entre les indices `debut` et `fin` inclus.
> 8. Déduisez-en une fonction `void tri_rapide(int tab[], int taille_tab)`.
> 9. Montrez la correction totale de vos fonctions.

Le tri rapide est en $`\Theta(n\times\log_2n)`$. En pratique, il est même plus rapide que le tri fusion.

> 10. On suppose que l'on souhaite trier une liste composée des éléments de $`[\![0,n-1]\!]`$. Combien de listes possibles existe-t-il avec ces éléments ? Que faudrait-il donc faire pour calculer la complexité en moyenne du tri rapide sur une liste de taille $`n`$ ?
> 11. Quelle est la complexité dans le pire des cas du tri rapide ? Pour quel(s) type(s) de tableau survient-elle ?
> 12. Une méthode pour contourner ce problème consisterait à prendre le pivot au hasard dans le tableau. Cela permet-il de garantir un cas favorable ?
> 13. Quelle valeur du pivot permet de garantir un cas favorable ?
> 14. Il n’existe pas d’algorithme efficace qui permette de trouver la médiane, cependant on peut calculer une « pseudo-médiane » en temps linéaire, c’est-à-dire une valeur dont on sait qu’au moins une proportion significative de valeurs lui sont inférieures tout comme une proportion significative lui sont supérieures. Serait-ce pertinent de l'utiliser pour le tri rapide ?

## III. Exercices

> **Partition de Hoare (C)**
>
> *On supposera ici que le tableau ne contient pas de doublons.*
>
> Une seconde méthode (celle d'origine mais moins simple), de Hoare, pour partitionner le tableau entre les indices `debut` et `fin` consiste à :
>
> * On initialise deux indices `i` à `debut` et `j` à `fin`.
> * Ces indices vont se rejoindre (on progresse tant que $`i < j`$) en échangeant au fur et à mesure les éléments de gauche de valeurs supérieures au pivot et les éléments de droite de valeurs inférieures au pivot ; on maintient donc l'invariant suivant :
>     * les éléments d'indices `debut` à `i-1` sont inférieurs au pivot
>     * ceux d'indices `j+1` à `fin` sont supérieurs au pivot.
>
> 1. Écrivez une fonction `int partition_hoare(int tab[], int debut, int fin)` qui partitionne le tableau selon cette méthode.
> 2. La fonction `tri_rapide` change-t-elle ?

> **Tri casier (C)**
>
> Un tri dit *par comparaisons* est un tri qui ne peut utiliser que des tests de comparaison entre deux éléments pour les ordonner. Les 5 algorithmes de tris étudiés jusqu'à présent sont des tris par comparaisons. C'est la manière la plus courante et naturelle de trier les données.
>
> Nous verrons en cours une preuve du fait qu'un tri par comparaisons nécessite une complexité temporelle d'au moins $`\mathcal O (n\times\log_2 n)`$ dans le pire des cas. Cependant, si on dispose d'informations supplémentaires sur les données à trier, on peut parfois trier avec une meilleure complexité. 
>
> Un exemple de tri qui n'est pas par comparaison est le *tri casier*, qui ne fonctionne que pour ordonner des entiers. Son principe :
>
> * On détermine le plus petit élément et le grand élément de la liste, notés respectivement `m` et `M`.
> * On crée un tableau `occ` de taille `M - m + 1` rempli initialement de zéros.
> * On parcourt le tableau à trier afin de compléter `occ` de telle sorte que `occ[i]` contienne le nombre de fois où la valeur `m + i` apparaît dans le tableau.
> * À l’aide de ces informations, on reconstitue la liste triée.
>
> 	1. Écrivez en C une fonction `void min_max(int tab[], int taille_tab, int* min, int* max)` qui prend en entrée un tableau d'entiers et détermine le minimum et le maximum *en un seul parcours du tableau*.
> 	1. Écrivez en C une fonction `void tri_casier(int tab[], int taille_tab)` qui implémente le tri casier d'un tableau d'entiers.
> 	1. Calculez soigneusement la complexité temporelle du tri casier. Est-il plus efficace que les meilleurs tris par comparaisons ? Dans quel(s) cas est-il particulièrement efficace ? Quel est son inconvénient ?
>
> Dans certains cas donc, on peut écrire des algorithmes de tris plus efficaces que les algorithmes par comparaisons qui sont au mieux quasi-linéaires. Cependant, cela demande des connaissances sur les données que nous n'avons pas forcément. 



## Pour aller plus loin

> 1. Implémentez un tri casier sur une `int list` en OCaml.
> 2. Implémentez le tri fusion d'un tableau d'entiers en C.
> 3. Implémentez le tri rapide avec partition de Lomuto d'un tableau en OCaml.




---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
