# TP : Listes chaînées en OCaml

Désormais, et ce pour tous les TP, vous écrirez vos fonctions dans un fichier `.ml` dans VS Code, puis vous prévoirez leur type avant de les évaluer. Le toplevel ne vous servira qu'à tester vos fonctions.

On rappelle qu'on peut importer les fonctions définies dans un fichier dans le toplevel avec l'instruction `#use "nom_du_fichier_contenant_les_fonctions" ;;`.

> 0. Créez un fichier `listes.ml` pour ce TP.

## I. Manipulations de listes

Le **type `'a list`** en OCaml implémente les listes chaînées.

Une liste chaînée de type `'a list` est :

* soit vide : notée **`[]`**
* soit constituée d'une tête (valeur `t : 'a`) et d'une queue (liste `q : 'a list`)  : notée **`t::q`**

Une liste est **homogène** (tous ses éléments sont de même type) et **immuable** (on ne peut pas la modifier).

> **Création de listes**
>
> Pour chaque instruction suivante, prévoyez la réponse d'OCaml (type et valeur) *puis* vérifiez dans le toplevel.
>
> ```ocaml
> # [] ;;
> # 1::[] ;;
> # 1::2::3::[] ;;
> # [1; 2; 3] ;;
> # 1::[2; 3] ;;
> # [8.6; 7.; 3.2; 4.; 1.0] ;;
> # [4.2; 3] ;;
> ```

> **Tête et queue**
>
> Il existe une fonction `List.hd` qui renvoie la tête d'une liste.
>
> 1. Testez dans le toplevel : `List.hd [1; 2; 3] ;;`.
>
> 2. Copiez la fonction suivante dans votre fichier `listes.ml` :
>
>     ```ocaml
>     let head l = match l with
>         | [] -> failwith "une liste vide n'a pas de tête !"
>         | t::q -> t
>     ```
>
>     Expliquez comment marche cette fonction. Quel est son type ? Testez la dans le toplevel.
>
> Il existe aussi une fonction `List.tl` qui renvoie la queue d'une liste.
>
> 3. Testez dans le toplevel `List.tl [1; 2; 3] ;;`.
> 4. Implémentez une fonction `tail : 'a list -> 'a list` en utilisant un filtrage.
>
> 5. Donnez une instruction permettant de récupérer la valeur `2` de `[1; 2; 3]` en utilisant `List.hd` et `List.tl`.
> 6. Même question pour `3`.
>
> Ces deux fonctions sont en réalité très peu utilisées, puisqu'on peut facilement récupérer la tête et la queue d'une liste avec un filtrage.

Pour accéder au dernier élément d'une liste chaînée, nous sommes obligés de parcourir toute la liste.

On parcourt les listes à l'aide de fonctions récursives et de filtrages.

> **Fonctions classiques**
>
> 1. Complétez la fonction `longueur : 'a list -> int` suivante, qui renvoie la longueur (nombre d’éléments) d’une liste :
>
>     ```ocaml
>     let rec longueur l = match l with
>     	| [] -> (* COMPLETER ICI *)
>     	| t::q -> (* COMPLETER ICI *)
>     ```
>
> 2. Écrivez une fonction `somme : int list -> int` qui calcule la somme des éléments d’une liste d'entiers.
>
> 3. Écrivez une fonction `moyenne : float list -> float `qui calcule la moyenne des éléments d’une liste de flottants.
>
> 4. Écrivez une fonction `appartient : 'a -> 'a list -> bool` qui teste si une valeur est présente dans la liste.

La fonction `longueur` existe déjà en OCaml : c'est `List.length l`. Tout comme votre propre code, cette fonction doit parcourir toute la liste pour trouver sa taille : ce n'est pas très efficace, il faut éviter de l'utiliser. Par contre, la version d'OCaml est récursive terminale.

La fonction `appartient` existe également en OCaml : c'est `List.mem x l`.

> **Filtrages plus élaborés**
>
> 1. Écrivez une fonction `croissant : 'a list -> bool` qui détermine si une liste est croissante (au sens large). Notez qu’une liste contenant zéro ou un élément est toujours croissante.
>
>     *Pour filtrer les listes contenant au moins deux éléments et récupérer les deux premiers éléments ainsi que le reste de la liste, on pourra utiliser un motif de la forme :*
>
>     ```ocaml
>     | t1::t2::q -> ... (* t1 est l'élément de tête, t2 le deuxième, q le reste de la liste *)
>     ```
>
> 2. Quelle propriété de l'opérateur `<=` rend l'écriture de cette fonction possible ?
>
> 3. Écrivez une fonction `trois_egaux : 'a list -> bool` qui détermine si une liste possède trois éléments consécutifs égaux.
>
> 4. Écrire une fonction `insere` qui prend en paramètre une liste, un élément et un indice et qui insère l'élément à l'indice donné. On lèvera une exception si l'indice est strictement supérieur à la taille de la liste. Par exemple :
>
>     ```ocaml
>     insere "a" 1 ["x"; "y"; "z"] = ["x"; "a"; "y"; "z"]
>     insere 7 3 [1; 2; 3] = [1; 2; 3; 7]
>     ```
>
>     Quel est le type de cette fonction ?

L'opérateur de concaténation sur les listes se note `@` en OCaml.

> **Concaténation**
>
> 1. Testez dans le toplevel : `[1; 3; 5] @ [4; 2; 8; 10] ;;`.
> 2. Donnez le type de l'opérateur `@`.
> 3. Écrivez une fonction récursive `concat : 'a list -> 'a list -> 'a list` telle que `concat u v` renvoie `u @ v`. On s’interdira bien sûr d’utiliser l’opérateur `@` dans l’écriture de cette fonction.
> 4. En utilisant la fonction `concat` (ou l’opérateur `@`, ce qui revient au même), écrivez une fonction `miroir : 'a list -> 'a list` qui renverse une liste. Par exemple, `miroir [4; 8; 8; 1; 2]` renvoie `[2; 1; 8; 8; 4]`.
> 5. Écrivez une fonction `repete : 'a list -> int -> 'a list` telle que `repete l n` soit égal à `l @ l @ ... @ l` (`n` fois).
>
> *Remarque : l'opérateur `@` n'est pas très efficace, puisque comme le fait votre fonction `concat`, toute la liste est parcourue et recopiée. On évite donc de l'utiliser.*

> **Fonctions d'ordre supérieur sur les listes**
>
> 1. Regardez ce que font les quatre fonctions suivantes, et testez les sur plusieurs exemples :
>
> * `List.exists`
>* `List.for_all`
> * `List.filter`
> * `List.map`
> 
> 2. Implémentez vos propres versions de ces fonctions.

## II. Polynômes

Dans cette partie, nous allons manipuler les polynômes en choisissant une représentation *creuse* : on ne garde que les coefficients non nuls. On se restreint à des polynômes à coefficients *entiers*, on évite ainsi les opérations `+., -., *., /.`.

* Un polynôme est représenté par une liste de couples d'entiers `((int * int) list)`.
* Le polynôme $`a_pX^{n_p} + a_{p-1}X^{n_{p-1}} + ... + a_1X^{n_1} + a_0X^{n_0}`$, avec les conditions $`a_i\ne 0 \; \forall i`$ et $`n_p > n_{p-1} > ... > n_1 > n_0\ge 0`$, est représenté en OCaml par `[(ap, np); ...; (a1, n1); (a0, n0)]`.
* Par exemple $`P=1-2X+4X^3`$ est représenté par `[(4, 3); (-2, 1); (1, 0)]`.
* En particulier le polynôme nul est représenté par la liste vide `[]`.

> 1. Donnez le polynôme représenté par la liste `[(7, 4); (1, 2); (4, 1); (-1, 0)]`.
> 2. Donnez la liste représentant le polynôme $`P = 4 + 2X^2 - 7X^3 - 3X^7`$.

*Rappel sur les filtrages :*

Dans certaines fonctions, le cas de base de la récursivité sera le cas d'une liste à un seul élément, la liste vide est simplement traitée à part. On utilisera alors un filtrage avec 3 motifs :

```ocaml
match liste with 
	| [] -> ...
	| [t] -> ... (* cas où la liste ne contient qu'un élément *)
	| t::q -> ...
```

Dans le cas d'une liste composée de types structurés comme ici, on peut rechercher un motif plus spécialisé ainsi :

```ocaml
match liste with
	| [] -> ...
	| (a, n)::q -> ... (* cas où la tête de la liste est un couple *)
```

On accède alors aux éléments du couple sans avoir besoin d'utiliser `fst` et `snd`.

### 1. Premières fonctions

> 3. Écrire une fonction `validation p` qui vérifie qu'une liste de couples d'entiers est une bonne représentation d'un polynôme : non nullité des coefficients et stricte décroissance des puissances.

Dans toute la suite on supposera que les listes de couples d'entiers sont valides sans avoir besoin de le vérifier.

> 4. Écrire une fonction `degre p` qui renvoie le degré du polynôme. On convient de renvoyer `-1` pour le polynôme nul.
> 3. Écrire une fonction `coefficient k p` qui renvoie le coefficient de $`X^k`$ du polynôme. Ce coefficient sera nul si le polynôme ne contient pas de terme de la forme `(a, k)`.
> 4. Écrire une fonction `evaluation p x` qui renvoie la valeur en `x` du polynôme `p` . Vous utiliserez la fonction `expo_rapide x n` définie lors du TP précédent, en la modifiant légèrement pour avoir `x` entier.
> 5. Écrire une fonction `composition k p` où `p`désigne un polynôme $`\displaystyle P =\sum_{i=0}^d a_i X^i`$ et `k` un entier strictement positif et qui renvoie la liste représentant le polynôme $`\displaystyle P(X^k) =\sum_{i=0}^d a_i X^{ik}`$.
> 6. Écrire une fonction `dilatation b p` où `p` désigne un polynôme et `b` un entier et qui renvoie la liste représentant le polynôme $`\displaystyle P(bX) = \sum_{i=0}^d a_i b^i X^{i}`$. Vous utiliserez la fonction `expo_rapide`.

### 2. Opérations

> 9. Écrire une fonction `plus p1 p2` qui renvoie la représentation de la somme des polynômes représentés respectivement par `p1` et `p2`.
>
> 2. Écrire une fonction `fois p1 p2` qui calcule une représentation du produit des polynômes représentés respectivement par `p1` et `p2`.
>     Il peut être utile d'écrire une fonction qui calcule le produit d'un monôme par un polynôme, le monôme étant représenté par un couple d'entiers.
>
> 3. Définir deux opérateurs infixes `+++` et `***` qui réalisent respectivement la somme et le produit de deux polynômes.
>
> 4. Écrire une fonction `derivee p` qui renvoie une représentation de `p'`.

Les polynômes de Tchebychev sont définis par $`T_n(\cos(x)) = \cos(nx)`$.

On peut prouver qu'on a $`T_0 = 1, T_1 =X \text{ et } T_{n} = 2X\,T_{n-1}-T_{n-2} \text{ pour }n\geq 2`$.

> 13. Écrire une fonction récursive `tch n` qui renvoie une représentation de $`T_n`$.

### 3. Division euclidienne

Dans cette partie nous étudions la division de polynômes. Nous supposerons que le polynôme diviseur est non nul et *unitaire*, le coefficient du terme de plus haut degré doit être 1.

La division euclidienne du polynôme `A` par le polynôme `B` est le couple de polynômes `Q` et `R` tels que `A = B.Q + R` et `deg(R) < deg (B)`.

On admet que de tels polynômes existent et sont uniques.

Pour calculer les termes de la division euclidienne de `A` par `B` :

1.  On détermine les degrés de `A` (appelé `p`) et de `B` (appelé `q`).

2.  Si on a `p < q` alors `Q = 0` et `R = A`,

3.  Sinon,

    1.  On détermine le coefficient de plus haut degré de `A` (appelé `a`).

    2.  On calcule $`A_1 = A - aX^{p-q}B`$,

    3.  On calcule récursivement $`A_1 = B\,Q_1 + R`$.

    4.  On a $`A = (a.X^{p-q} +Q_1).B + R`$.

La récursivité est possible car le degré de $`A_1`$ est strictement inférieur à celui de $`A`$.

> 14. Écrire une fonction `division a b` qui renvoie deux listes représentant le quotient et le reste de la division euclidienne de `A`  par `B`.

Les polynômes cyclotomiques sont des polynômes définis par C.F. Gauss en 1801.

Ils sont employés dans plusieurs domaines mathématiques : théorie de Galois, construction à la règle et au compas... Ils sont définis par $`\displaystyle \Phi_n = \prod_{k = 1, k \wedge n=1}^{n} (X - e^{2ik\pi/n})`$.

On prouve que ce sont des polynômes à coefficients entiers, irréductibles dans $`{\mathcal Q}[X]`$.

On peut les construire récursivement, à l'aide de la propriété :
$`\Phi_1 = X - 1 \quad\quad \Phi_n = \frac{X^n - 1}{\displaystyle \prod_{k|n, k < n}\Phi_k}`$

> 15. Écrire une fonction `cycloto n` qui renvoie $`\Phi_n`$.

### 4. Application d'une fonction à une liste

Dans l'usage des listes, il y a des motifs de fonctions qui se répètent. Les fonctions `composition` et `dilatation` de la partie `1.` reviennent toutes deux à appliquer une fonction `f` à tous les termes de la liste. Par exemple, dans la fonction `composition`, on applique la fonction `let f (a, n) -> (a, k*n)` à tous les termes de la liste. On peut donc l'écrire sous la forme :

```ocaml
let composition k p =
	let f (a, n) = (a, k*n) in
	let rec aux f l =
		match l with
			| [] -> []
			| t::q -> (f t)::(aux f q) in
	aux f p
```

On reconnaît `List.map` dans la fonction auxiliaire. On peut alors écrire (on notera la disparition de `rec`) :

```ocaml
let composition k p =
	let f (a, n) = (a, k*n) in
	List.map f p
```

Souvent la fonction à utiliser n'aura pas d'existence en dehors de son usage : on peut dans ce cas créer une fonction *anonyme* avec `fun` :

```ocaml
let composition k p =
	List.map (fun (a, n) -> (a, k*n)) p
```

Voire même :

```ocaml
let composition k = List.map (fun (a, n) -> (a, k*n))
```

> 16. Ré-écrire ainsi la fonction `dilatation` de la partie `1.`.

> **Pour aller plus loin**
>
> 17. Proposer une ré-écriture de la fonction `derivee` de la partie `2.`.
> 18. Elle n'est pas tout-à-fait ce que l'on attend : pourquoi ?
> 19. Pour avoir une définition fonctionnelle, utilisez `List.filter`.


---

Par *Justine BENOUWT*, *Éric DÉTREZ*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*

