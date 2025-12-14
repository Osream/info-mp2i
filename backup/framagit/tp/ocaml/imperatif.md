# TP : Programmation impérative en OCaml

Ce TP est une première approche du paradigme impératif en OCaml : références, boucles, tableaux.

## I. Références

Les variables en OCaml sont immuables. Mais quand on programme dans le paradigme impératif, on a généralement besoin de modifier nos variables : on utilise alors des références, de type `'a ref`.

* On crée une référence avec la fonction `ref` (type `'a -> 'a ref`).
* On récupère une valeur référencée avec l'opérateur préfixe `!` (type `'a ref -> 'a`).
* On affecte une valeur à une référence avec l'opérateur infixe `:=` (type `'a ref -> 'a -> unit`).

> 1. Dans le toplevel directement, testez les instructions suivantes :
>
>     ```ocaml
>     # let x = ref 4 ;;
>     # x ;;
>     # !x ;;
>     # x := 1 ;;
>     # !x ;;
>     # let y = ref !x ;;
>     # y := !y + 2 ;;
>     # !x ;;
>     # !y ;;
>     # let z = x ;;
>     # z := 9 ;;
>     # !x ;;
>     # !z ;;
>     ```
>
> 2. Si `a` est une référence et qu'on réalise l'affectation `let b = a`, qu'arrive-t-il à l'une des références si l'autre est modifiée ?
>
> 4. Écrivez deux fonctions `incremente : int ref -> unit` et `decremente  : int ref -> unit` qui prennent en paramètre une référence vers un entier et ajoute (resp. retire) 1 à sa valeur.
>
>     *Remarque : ces fonctions existent déjà, ce sont `incr` et `decr`.*
>
> 5. Écrivez une fonction `echange : 'a ref -> 'a ref -> unit` qui échange les valeurs des deux références passées en paramètre.
>
> 6. Pour chacun des types suivants, définissez une variable qui correspond :
>
>     ```ocaml
>     1. bool ref
>     2. int ref ref
>     3. (float * float) ref
>     4. (int -> bool) ref
>     ```

Attention, les références sont propres au paradigme impératif : on ne met ***jamais*** de références dans une fonction récursive ! on n'utilise ***jamais*** de références avec des listes !

Le paradigme fonctionnel reste généralement le plus naturel en OCaml. **L'usage abusif de références** dans des programmes qui n'en n'ont pas besoin **est fortement pénalisé**.

## II. Boucles

Voici la syntaxe pour écrire une boucle bornée en OCaml :

```ocaml
(* va de debut à fin inclus en augmentant de 1 à chaque itération *)
for compteur = debut to fin do
	expression_de_type_unit
done

(* va de debut à fin inclus en diminuant de 1 à chaque itération *)
for compteur = debut downto fin do
	expression_de_type_unit
done
```

> 1. Écrivez une fonction qui prend en paramètre un entier `n`  et affiche tous les nombres de 0 à `n`, séparés par des tirets, en retournant à la ligne à la fin.
>2. Même question, à rebours cette fois.

Voici la syntaxe pour écrire une boucle non bornée en OCaml :

```ocaml
while condition do
	expression_de_type_unit
done
```

> 3. Avec une boucle `while`cette fois, écrivez une fonction qui prend en paramètre un entier `n`  et affiche tous les nombres de 0 à `n`, séparés par des tirets, en retournant à la ligne à la fin.

De manière générale, il ne faut pas abuser des références et boucles et s'entraîner à penser et écrire récursivement en OCaml.

> 4. Écrivez trois versions d'une fonction qui calcule `n!` : la première avec une boucle for, la seconde avec un while, et la troisième récursive.
> 5. Laquelle des 3 est la plus claire et concise ? Comprenez-vous pourquoi le paradigme fonctionnel est plus naturel que l'impératif en OCaml ?

**L'usage abusif de boucles et références** dans des programmes en OCaml n'en ayant pas besoin **est fortement pénalisé.** Rares seront les TP en OCaml utilisant le paradigme impératif. Dans la suite de ce TP cependant, vous utiliserez systématiquement des boucles, en choisissant le type de boucle le plus adapté à chaque fois.

## III. Tableaux

OCaml possède un module `Array` permettant de manipuler les tableaux.

> 1. Pour chaque instruction suivante, essayez de prévoir la réponse d'OCaml (type et valeur) *puis* vérifiez :
>
>     ```ocaml
>     # [|1; 2; 3|] ;;
>     # [|8.6; 7.; 3.2; 4.; 1.0|] ;;
>     # [||] ;;
>     # [|4.2; 3|] ;;
>     # let t = [|5; 7; 2; 3|] ;;
>     # t.(0) ;;
>     # t.(4) ;;
>     # t.(-1) ;;
>     # t.(0) <- 8 ;;
>     # t ;;
>     ```

Lorsqu'on passe un tableau en paramètre d'une fonction, cette dernière peut le modifier. C'est ce qu'on appelle un *effet de bord*.

> 2. Écrivez une fonction qui prend en paramètre un tableau, un indice et une valeur, et remplace la valeur à l'indice donné dans le tableau par celle fournie. Cette fonction ne doit rien renvoyer (mais elle a un effet de bord). Quel est son type ?

L'expression `let t1 = t2` ne permet pas de créer une copie d'un tableau. Les deux variables désignent le même objet en mémoire (comme pour les références).

> 3. Testez dans le toplevel :
>
>     ```ocaml
>     # let t1 = [|5; 7; 2; 3|] ;;
>     # let t2 = t1 ;;
>     # t1.(0) <- 99 ;;
>     # t1 ;;
>     # t2 ;;
>     ```

Il existe un certain nombres de fonctions sur les tableaux définies dans le module `Array`, que vous devez connaître et savoir utiliser :

* `Array.length : 'a array -> int` donne la taille d'un tableau
* `Array.make : int -> 'a -> 'a array` construit un tableau de taille donnée, rempli de la valeur donnée
* `Array.make_matrix : int -> int -> 'a -> 'a array array` construit une matrice
* `Array.copy : 'a array -> 'a array` renvoie une copie superficielle d'un tableau (ne fonctionne pas si le contenu du tableau est mutable)
* `Array.mem : 'a -> 'a array -> bool` détermine si une valeur appartient à un tableau
* `Array.init`, `Array.exists`, `Array.for_all`, `Array.map`, `Array.iter` sont des fonctions d'ordre supérieur (`init` crée et initialise un tableau avec une fonction, `exists` détermine s'il existe un élément vérifiant une propriété, `for_all` détermine si tous les éléments vérifient une propriété, `map` renvoie un tableau dont les éléments sont le résultat de l'application d'une fonction, `iter` applique une fonction ayant des effets de bord aux éléments du tableau).

> 4. Testez dans le toplevel :
>
>     ```ocaml
>     # Array.length [||] ;;
>     # let t = [|5; 7; 2; 3|] ;;
>     # Array.length t ;;
>     # let t_10_2 = Array.make 10 2 ;;
>     # Array.mem 2 t_10_2 ;;
>     # Array.mem 4 t_10_2 ;;
>     # Array.make_matrix 5 3 0 ;;
>     # let tt = Array.copy t ;;
>     # t.(0) <- 99 ;;
>     # tt ;;
>     # let tref1 = [|ref 1; ref 2|] ;;
>     # let tref2 = Array.copy tref1 ;;
>     # tref1.(0) := 99 ;;
>     # tref2 ;;
>     ```
>
> 5. Testez dans le toplevel :
>
>     ```ocaml
>     # let t = [|5; -7; 2; 3|] ;;
>     # Array.exists (fun x -> x > 0) t ;;
>     # Array.for_all (fun x -> x > 0) t ;;
>     # Array.map (fun x -> x + 1) t ;;
>     # Array.iter (fun x -> print_int x ; print_newline ()) t ;;
>     # Array.init 10 (fun i -> i*2) ;;
>     ```

Pour parcourir un tableau, on utilise une boucle :

```ocaml
for i = 0 to Array.length tableau - 1 do
	...
done
```

> 6. Écrivez une fonction qui affiche les éléments d'un tableau de flottants, séparés par des espaces, en utilisant une boucle.
> 7. Donnez une expression permettant de faire la même chose mais sans boucle, avec une fonction du module `Array`.
> 8. Écrivez une fonction qui prend en paramètre un entier `n` et renvoie un tableau dont les valeurs sont les entiers de `0` à `n-1` dans l'ordre croissant ; sans utiliser de fonction d'ordre supérieur.
> 9. Donnez une expression permettant de faire la même chose avec une fonction d'ordre supérieur.

## IV. Retour sur les exceptions

Une exception peut être levée automatiquement lorsqu'une erreur survient à l'exécution. On peut aussi lever soi-même une exception. Par exemple :

```ocaml
# [|1;2;3|].(7);; (* exception automatique *)
Exception: Invalid_argument "index out of bounds".
# failwith "message d'erreur" ;; (* message d'erreur personnalisé *)
Exception: Failure "message d'erreur".
# raise Division_by_zero ;; (* exception existante *)
Exception: Division_by_zero.
```

Une exception interrompt l'exécution du programme. Pour empêcher cela, on peut les attraper :

```ocaml
try
    expression
with  Exception_a_attraper_1 -> ...
    | Exception_a_attraper_2 -> ...
    | ...
```

Par exemple, la fonction suivante prend en paramètre un entier et renvoie son inverse s'il existe, et `max_int` sinon :

```ocaml
let inverse x =
	(* Si 1 / x ne lève pas d'exception, il est renvoyé *)
    try
        1 / x
    (* Si 1 / x lève l'exception Division_by_zero, on renvoie max_int à la place *)
    with Division_by_zero -> max_int
```

> 1. Écrivez une fonction utilisant une attrapée d'exception `i_eme_element : 'a array -> int -> 'a option` qui prend en paramètre un tableau et un indice, et renvoie l'élément du tableau se situant à cet indice s'il existe, et `None` sinon. 

Il est possible de définir sa propre exception :

```ocaml
exception Mon_exception
```

Les exceptions ne servent pas qu'à gérer les erreurs.

> 2. Expliquez ce que fait le programme suivant :
>
>     ```ocaml
>     exception Diviseur_trouve
>     let mystere n =
>         try
>             for i = 2 to n - 1 do
>                 if n mod i = 0 then
>                 	raise Diviseur_trouve
>             done ;
>             true
>         with Diviseur_trouve -> false
>     ```

Il n'est pas possible en OCaml de renvoyer un résultat à l'intérieur d'une boucle (pas de "return" qui pourrait interrompre la boucle comme en C). Pour renvoyer un résultat sans terminer les itérations restantes de la boucle, on doit lever une exception.

> 3. Écrivez une fonction `array_mem` de même spécification que `Array.mem`. On utilisera une exception pour sortir de la boucle dès que l'élément est trouvé.

Contrairement au C, les instructions `break` et `continue` n'existe pas en OCaml. On peut procéder ainsi à la place :

```ocaml
(* Sortie prématurée d'une boucle *)
exception Break
try
    for ... do
        ....
        raise Break (* sortie *)
        ...
    done ;
    ...
with Break -> ...

(* Sortie prématurée d'une itération *)
exception Continue
for ... do
    try
        ...
        raise Continue 
        ...
    with Continue -> ()
done ;
...
```

> 4. Écrivez à l'aide des exceptions `Break` et `Continue` deux fonctions qui prennent en paramètres deux entiers naturels `n` et `m`, et affichent respectivement les entiers allant de 1 à `n` *sauf* les multiples de `m` et *jusqu'au premier* multiple de `m`.

## V. Exercices

> **Typage**
>
> Pour chaque type suivant, définissez une variable qui correspond :
>
> ```ocaml
> 1. int array ref
> 2. int ref array
> 3. float ref array ref
> 4. (int ref -> int ref array) ref
> 5. ((float * float) ref -> float array ref) array ref
> ```

> **Boucles for**
>
> 1. Écrivez une fonction qui prend en paramètre deux entiers `m` et `n` et renvoie la somme des entiers compris entre `m` et `n`.
>
> 2. Écrivez une fonction qui prend en paramètre deux entiers `m` et `n` et renvoie la somme des carrés des entiers pairs compris entre `m` et `n`.
>
> 3. Écrivez des fonctions calculant les sommes suivantes :
>
>     $`\displaystyle S_1(n) = \sum_{k=1}^n \frac 1 {k^2}`$
>
>     $`\displaystyle S_2(n) = \sum_{i=1}^n \sum_{j=1}^n (i+j)`$
>
>     $`\displaystyle S_3(n) = \sum_{i=1}^n \sum_{j=i}^n (i+j)`$
>
>     $`\displaystyle S_4(n) = \sum_{i=1}^n \sum_{j=1}^{i-1} (i+j)`$

> **Boucles while**
>
> 1. Définissez un opérateur infixe pour la puissance entre deux entiers, utilisant l'algorithme d'exponentiation rapide.
>
> 2. Écrivez une fonction renvoyant le nombre de chiffres d’un entier naturel :
>
>     ```ocaml
>     # nb_chiffres 5952 ;;
>     - : int = 4
>     ```
>
> 3. Écrivez une fonction qui prend en paramètre deux flottants `x`  et $`\epsilon`$  et renvoie $`\sqrt x`$ avec une précision de $`\epsilon`$, en utilisant l'algorithme de Babylone qui consiste à calculer les termes de la suite suivante (on s'arrête lorsque $`\left| u_n - \frac x {u_n}\right| < \epsilon`$) :
>
>     $`\begin{cases} u_0 = 1 \\ u_{n+1} = \frac 1 2 \bigl( u_n + \frac x {u_n}\bigr) \end{cases}`$.
>
>     *Remarque : vous pouvez utiliser la fonction `abs_float`*.
>

> **Algorithmes sur les tableaux**
>
> Pour chacun des problèmes suivants, écrivez une fonction qui renvoie la solution. On travaille à chaque fois sur un tableau non vide.
>
> 1. Calculer la somme des éléments d'un tableau d'entiers.
> 2. Calculer la moyenne (flottante) des éléments d'un tableau d'entiers.
> 3. Trouver le nombre d'occurrences d'une valeur dans un tableau.
> 4. Trouver le premier indice d'une valeur dans un tableau.
> 5. Trouver le dernier indice d'une valeur dans un tableau.
> 6. Trouver le minimum et le maximum d'un tableau.
> 7. Trouver l'indice du minimum et l'indice du maximum d'un tableau.
> 8. Déterminer si le tableau est trié dans l'ordre croissant.
>
> *Vous devez impérativement être capables de ré-écrire toutes ces fonctions rapidement.*

> **Construction de tableaux**
>
> 1. Écrivez une fonction qui prend en paramètre un entier `n` et renvoie un tableau dont les valeurs sont les entiers de `0` à `n-1` dans l'ordre *dé*croissant ; sans utiliser de fonction d'ordre supérieur.
>
>     Donnez une expression permettant de faire la même chose avec une fonction d'ordre supérieur.
>
> 3. Écrivez une fonction `renverse : ’a array -> ’a array` qui étant donné un tableau renvoie un nouveau tableau composé des mêmes éléments mais rangés dans l’ordre inverse ; sans utiliser de fonction d'ordre supérieur.
>
>     Donnez une expression permettant de faire la même chose avec une fonction d'ordre supérieur.
>
> 9. Écrivez une fonction `renverse2 : ’a array -> unit` qui étant donné un tableau le modifie de sorte que ses éléments soient rangés dans l’ordre inverse. Quelle est la différence avec la question précédente ?

> **Exceptions**
>
> 1. La fonction `List.nth : 'a list -> int -> 'a` renvoie le `n-ième` élément d'une liste. Elle peut lever les exceptions `Invalid_argument` et `Failure` si le `n-ième` élément n'existe pas. Écrivez une fonction `nth_option : 'a list -> int -> 'a option` qui renvoie `None` si le `n-ième` élément n'existe pas, et sa valeur sinon, en utilisant une attrapée d'exception.
> 2. Définissez une exception pour les dépassements de capacité. Ré-écrivez ensuite vos fonctions `incremente : int ref -> unit` et `decremente  : int ref -> unit` pour qu'elles lèvent cette exception si un dépassement survient.
> 3. Écrivez une fonction qui détermine si le tableau passé en paramètre est un palindrome. On essaiera de limiter le nombre de comparaisons effectuées en sortant de la boucle dès que possible.

## Pour aller plus loin

> **Retour sur les opérateurs de comparaison**
>
> Les opérateurs d'égalité  `=` et `==` permettent de faire la distinction entre deux objets différents de même valeur et deux mêmes objets. Pour la différence, on utilise respectivement `<>` et `!=`.
>
> Testez par exemple :
>
> ```ocaml
> # let t1 = [|5; 7; 2; 3|] ;;
> # let t2 = t1 ;;
> # let t3 = [|5; 7; 2; 3|] ;;
> # t1 = t2 ;;
> # t1 = t3 ;;
> # t1 == t2 ;;
> # t1 == t3 ;;
> # t1 <> t3 ;;
> # t1 != t3 ;;
> # t1 != t2 ;;
> # let r1 = ref 4 ;;
> # let r2 = r1 ;;
> # let r3 = ref !r1 ;;
> # r1 = r2 ;;
> # r1 = r3 ;;
> # r1 == r2 ;;
> # r1 == r3 ;;
> # r1 != r2 ;;
> # r1 != r3 ;;
> ```
>
> Comprenez-vous l'importance de ne pas confondre les opérateurs de comparaison ?
>
> **Failwith**
>
> Voici comment `failwith` est défini en OCaml :
>
> ```ocaml
>exception Failure of string
> let failwith message = raise (Failure message)
>```
> 
> Expliquez cette syntaxe.
> 
> **Ré-écrire les fonctions du module Array**
>
> Si vous avez terminé, vous pouvez ré-écrire par vous-même les fonctions d'ordre supérieur sur les tableaux (sans utiliser les fonctions en question bien évidemment !).


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*

