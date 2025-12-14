# TP : Tableaux en OCaml

Nous allons manipuler les tableaux OCaml, à une dimension (`'a array`) et à deux dimensions (`'a array array`). Les tableaux étant des structures de données impératives, toutes les fonctions de ce TP devront nécessairement respecter le paradigme de programmation impératif.

## I. Ré-écriture des fonctions du module `Array`

Dans cette partie, vous veillerez bien à ce que vos fonctions aient le bon type (notamment, on travaille toujours sur des `'a array`, si le type obtenu est moins général, il y a un problème).

> Pour ces fonctions, seules les fonctions `Array.length` et `Array.make` sont autorisées.
>
> 1. Écrivez une fonction similaire à `Array.mem`.
> 2. Écrivez une fonction similaire à `Array.copy`.
> 3. Écrivez une fonction similaire à `Array.init`.
> 4. Écrivez une fonction similaire à `Array.exists`.
> 5. Écrivez une fonction similaire à `Array.for_all`.
> 6. Écrivez une fonction similaire à `Array.map`.
> 7. Écrivez une fonction similaire à `Array.iter`.
>
> *Vous devez impérativement être capables de ré-écrire toutes ces fonctions rapidement.*

Il est possible de ré-écrire certaines de ces fonctions de manière un peu plus concise en utilisant les fonctions d'ordre supérieur du module `Array`.

> 8. Écrivez une fonction similaire à `Array.mem` en utilisant `Array.exists` (et aucune boucle).
> 9. Écrivez une fonction similaire à `Array.for_all` en utilisant `Array.exists` (et aucune boucle).
> 10. Écrivez une fonction similaire à `Array.exists` en utilisant `Array.for_all` (et aucune boucle).
> 11. Écrivez une fonction similaire à `Array.copy` avec uniquement d'autres fonctions du module `Array` (et aucune boucle).
> 12. Écrivez une fonction similaire à `Array.map` avec uniquement d'autres fonctions du module `Array` (et aucune boucle).

## II. Manipulations de tableaux multidimensionnels

Il est possible de créer des tableaux multidimensionnels.

> 1. Pour chaque instruction suivante, prévoyez la réponse d'OCaml (type et valeur) *puis* vérifiez :
>
>     ```ocaml
>     # let t = [| [|1; 2; 3|]; [|4; 5; 6|] |] ;;
>     # t.(0) ;;
>     # t.(0).(0) ;;
>     # t.(1).(2) ;;
>     # t.(2).(1) ;;
>     # t.(0).(1) <- 99 ;;
>     # t ;;
>     ```
>
> 2. En utilisant `Array.length`, comment trouver le nombre de lignes d'un tableau à 2 dimensions ? de colonnes ?
>
> 3. Est-il possible de créer un tableau à 2 dimensions dont toutes les lignes n'ont pas le même nombre de colonnes ?
>
> 4. Les éléments des tableaux "intérieurs" d'un tableau multidimensionnel peuvent-ils être de types différents ?
>
> 5. Créez un tableau de flottants à 3 dimensions avec les valeurs que vous voulez. Quel est son type ?

On parcourt un tableau multidimensionnel avec des boucles, souvent imbriquées.

> 6. Écrivez une fonction `affiche_2d : int array array -> unit` qui affiche proprement un tableau d'entiers à deux dimensions (espaces entre les entiers d'une même ligne, retours à la ligne entre chaque ligne), en parcourant le tableau avec une double boucle.
>
>     ```ocaml
>     # affiche_2d [| [|1; 2; 3|]; [|4|]; [|5; 6; 7|]; [|8; 9|] |] ;;
>     1 2 3
>     4
>     5 6 7
>     8 9
>     ```

Il faut être vigilent à la façon dont on crée un tableau multidimensionnel.

> 7. Testez dans le toplevel :
>
>     ```ocaml
>     # let ligne = [|1; 2; 3|] ;;
>     # let t = [|ligne; ligne|] ;;
>     # t.(0).(0) <- 1111 ;;
>     # t ;;
>     # ligne.(1) <- 2222 ;;
>     # t ;;
>     # let t2 = Array.make 2 [|1; 2; 3|] ;;
>     # t2.(0).(0) <- 99 ;;
>     # t2 ;;
>     ```
>
> 2. Un élève peu attentif propose la fonction suivante, censée implémenter la fonction `Array.make_matrix`.
>
>     ```ocaml
>     let array_make_matrix nb_lignes nb_cols val_init =
>     	Array.make nb_lignes (Array.make nb_cols val_init)
>     ```
>
>     Qu'en pensez-vous ?
>
> 3. Écrivez votre propre version correcte de `make_matrix` (seules les fonctions `Array.length` et `Array.make` sont autorisées).
>
>     *Vous devez impérativement être capables de ré-écrire cette fonction rapidement.*

La copie d'un tableau multidimensionnel peut aussi poser problème.

> 10. Testez dans le toplevel :
>
>     ```ocaml
>     # let t = [| [|1; 2; 3|]; [|4; 5; 6|] |] ;;
>     # let t2 = Array.copy t ;;
>     # t.(0).(0) <- 111 ;;
>     # t2 ;;
>     # t.(1) <- [|7; 8; 9|] ;;
>     # t2 ;;
>     ```
>
>     Pourquoi dit-on que la copie est *superficielle* ?
>
> 11. Écrivez une fonction `copy_matrix : 'a array array -> 'a array array` qui renvoie une copie d'un tableau à 2 dimensions. Attention aux points suivants :
>
>     * la copie doit être indépendante de l'origine ;
>     * les tailles des tableaux "internes" peuvent être différentes ;
>     * seules les fonctions `Array.length` et `Array.make` sont autorisées.
>
>     Pour tester votre fonction :
>
>     ```ocaml
>     # let t = [| [|0; 1; 2|]; [|7; 4; 6; 5|]; [|1|] |] ;;
>     # let t2 = copy_matrix t ;;
>     # t.(0).(0) <- 999 ;;
>     # t2 = [| [|0; 1; 2|]; [|7; 4; 6; 5|]; [|1|] |] ;; (* doit donner true *)
>     ```
>

Il est possible d'adapter les fonctions sur les tableaux à une dimension pour les appliquer à des tableaux multidimensionnels.

> 12. Écrivez une fonction `init_matrix : int -> int -> (int -> int -> 'a) -> 'a array array` qui crée un tableau à 2 dimensions à la manière de `Array.make_matrix` mais dont les valeurs sont initialisées grâce à une fonction de manière similaire à ce que fait `Array.init`.

Il est possible de ré-écrire toutes ces fonctions de manière un peu plus concise.

> 13. Ré-écrivez la fonction `affiche_2d` sans aucune boucle, avec uniquement des fonctions du module `Array`.
> 14. Ré-écrivez une fonction similaire à `Array.make_matrix` en utilisant `Array.init`  (et aucune boucle).
> 15. Ré-écrivez la fonction `copy_matrix` sans aucune boucle, uniquement des fonctions du module `Array`.
> 16. Ré-écrivez la fonction `init_matrix` sans aucune boucle, uniquement des fonctions du module `Array`.

## III. Exercices

> **Taille d'un tableau**
>
> Il est possible de ré-écrire la fonction `Array.length`, cependant la complexité de notre version sera linéaire (parcours entier du tableau) alors que celle d'OCaml est constante (aucun calcul, la taille est stockée).
>
> 1. Quelle est l'exception levée lorsqu'on tente d'accéder à un indice invalide d'un tableau ?
> 2. En utilisant une attrapée d'exception, écrivez une fonction qui renvoie la taille d'un tableau sans utiliser `Array.length`.

> **Création de tableaux multidimensionnels**
>
> Pour les questions de cet exercice, vous n'utiliserez pas de fonction d'ordre supérieur.
>
> 1. Écrivez une fonction qui prend en paramètre un entier `n` et renvoie un tableau de taille `n * n` dont les valeurs de chaque ligne sont les entiers de `1` à `n` dans l'ordre croissant.
>
>     ```ocaml
>     # init_croissant_2d 3 ;;
>     - : int array array = [| [|1; 2; 3|]; [|1; 2; 3|]; [|1; 2; 3|] |]
>     ```
>
> 2. Même question mais avec les valeurs de `1` à $`n^2`$ :
>
>     ```ocaml
>     # init_croissant_carre_2d 3 ;;
>     - : int array array = [| [|1; 2; 3|]; [|4; 5; 6|]; [|7; 8; 9|] |]
>     ```
>
> 3. Écrivez une fonction `damier : int -> int array array` qui prend en paramètre un entier `n` et crée un tableau de dimensions `n * n` alternant les valeurs `0` et `1`.
>
>     ```ocaml
>     # damier 3;;
>     - : int array array = [| [|0; 1; 0|]; [|1; 0; 1|]; [|0; 1; 0|] |]
>     ```
>
> 4. Écrivez une fonction `make_tenseur : int -> int -> int -> 'a -> 'a array array array` qui crée et initialise un tableau à trois dimensions.

> **Sous-tableau**
>
> 1. Écrivez une fonction `sous_tableau : 'a array -> int -> int -> 'a array` qui prend en paramètres un tableau, un indice de départ `i` et une taille `t` et renvoie un tableau de taille `t` contenant les valeurs du tableau d'origine à partir de `i`.
>
>     Vous écrirez 2 versions de cette fonction :
>
>     * la première utilisant une boucle ;
>     * la seconde n'utilisant aucune boucle, uniquement des fonctions du module `Array`.
>
> 2. Écrivez une fonction `sous_matrice : int array array -> (int * int) -> (int * int) -> int array array` qui prend en paramètres une matrice `m`, des indices de départ `(i, j)` et des tailles souhaitées `(l, c)` et renvoie une matrice ayant `l` lignes et `c` colonnes contenant les valeurs de `m` à partir de la ligne `i`, colonne `j`.
>
>     ```ocaml
>     # sous_matrice [| [|1; 2; 3|]; [|4; 5; 6|]; [|7; 8; 9|]; [|10; 11; 12|] |] (1,0) (3,2) ;;
>     - : int array array = [| [|4; 5|]; [|7; 8|]; [|10; 11|] |]
>     ```
>
>     Vous écrirez 2 versions de cette fonction :
>
>     * la première utilisant des boucles ;
>     * la seconde n'utilisant aucune boucle, uniquement des fonctions du module `Array`.

> **Recherche**
>
> 1. Écrivez une fonction `ppem : int array -> int` qui renvoie le plus petit entier naturel qui n’apparaît pas dans le tableau. On ne cherchera pas à être efficace.
> 2. Ré-écrivez la fonction pour ne parcourir le tableau d'origine qu'une seule et unique fois.
> 3. Écrivez une fonction similaire `ppem_matrix : int array array -> int` qui renvoie le plus petit entier naturel qui n'apparaît pas dans la matrice. Vous parcourrez une seule et unique fois la matrice. On suppose que toutes les lignes ont le même nombre de colonnes.
>
> On travaille désormais sur une matrice carrée triée : chaque ligne de la matrice est croissante et chaque colonne est croissante. Par exemple, `[| [|1; 4|]; [|2; 5|] |]` est triée.
>
> 4. Écrivez une fonction `mem_matrix : 'a -> 'a array array -> bool` qui détermine si une valeur est présente dans une matrice carrée triée. On ne cherchera pas à être efficace.
>
> 5. Écrivez une fonction similaire qui réalise au plus `2n` comparaisons d'une case avec la valeur cherchée (avec `n` le nombre de lignes et de colonnes).
>
>     *Indice : commencez la recherche dans le coin supérieur droit de la matrice.*

## Pour aller plus loin

> 1. Il existe une fonction équivalente à `Array.iter` sur les listes : `List.iter`. Regardez comment elle fonctionne et ré-implémentez là (avec une fonction récursive).
> 2. Reprenez vos implémentations des fonctions similaires à `mem`, `exists` et `for_all` et utilisez des exceptions afin de sortir de la boucle dès que possible.
> 3. Écrivez une fonction `est_matrice_carree : 'a array array -> bool` qui détermine si un tableau à 2 dimensions est une matrice carrée (toutes les lignes ont le même nombre de colonnes, et le nombre de ligne est égal au nombre de colonnes).
> 4. Écrivez une fonction `est_triee : 'a array array -> bool `qui détermine si la matrice carrée donnée en paramètre est triée (chaque ligne de la matrice est croissante et chaque colonne est croissante).


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
