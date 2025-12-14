# TD : Manipulations de piles et files

## Exercice 1 : manipulations générales (en pseudo-code)

1. Dessiner les évolutions de la pile / file pour chaque instruction des deux séquences suivantes :

    ```
            p <- pile vide									f <- file vide
            empiler(p, 7)									enfiler(f, 7)
            empiler(p, 4)									enfiler(f, 4)
            x <- depiler(p)									x <- defiler(f)
            y <- depiler(p)									y <- defiler(f)
            empiler(p, 2)									enfiler(f, 2)
            empiler(p, y)									enfiler(f, y)
            empiler(p, x)									enfiler(f, x)
            empiler(p, depiler(p))							enfiler(f, defiler(f))
    ```

On souhaite écrire un algorithme qui compte le nombre d'éléments d'une pile / file, en utilisant uniquement les fonctions de l'interface (autrement dit, on ne sait pas comment la structure est implémentée). Cet algorithme ne doit pas avoir d'effet de bord : la structure doit donc retrouver son état d'origine après le décompte.

2. À l'aide de schémas, expliquer comment on pourrait procéder pour déterminer la taille d'une file. En déduire un algorithme `taille(file f)`. Faire de même pour la taille d'une pile. Complexités ?

Pour une file, l'affichage se fera sur une ligne, avec la prochaine donnée à défiler tout à gauche, et ainsi de suite. On séparera les données par des espaces. Par exemple, une file dans laquelle on a enfilé successivement les valeurs 2, puis 7, puis 4 sera affichée ainsi : `<- 2 7 4 <-`. Pour une pile, l'affichage se fera sur une colonne, avec la prochaine donnée à dépiler tout en haut, et ainsi de suite.

3. Écrire deux algorithmes `affiche(pile p)` et `affiche(file f)`. Attention, vos algorithmes ne doivent pas avoir d'effet de bord. Complexités ?

On cherche à écrire un algorithme qui prend en entrée une pile / file et renvoie une nouvelle pile / file contenant les mêmes éléments, *dans le même ordre*. La pile / file d'origine ne doit pas être modifiée.

4. À l'aide de schémas, expliquer comment on pourrait procéder pour copier une file. En déduire un algorithme `copie(file f)`. Complexité ?
5. À l'aide de schémas, expliquer comment on pourrait procéder pour copier une pile, , en utilisant une unique pile intermédiaire (et rien d'autre). En déduire un algorithme `copie(pile p)`.
6. Même question pour copier une pile en utilisant une unique file intermédiaire (rien d'autre).
7. Comparer l'efficacité (temporelle + spatiale) des deux algorithmes de copies d'une pile.

On souhaite maintenant renverser une pile / file : l'élément qui devait être dépilé / défilé en premier se retrouve en dernier, et ainsi de suite.

8. Écrire un algorithme `renverse(pile p)` qui renvoie une pile renversée par rapport à celle passée en entrée (attention il ne doit pas y avoir d'effet de bord). Complexité ?
9. Même question pour une file. Il est conseillé de commencer par faire des schémas. Complexité ?
10. Ré-écrire l'algorithme `renverse(pile p)` qui renverse cette fois la pile elle-même (par effet de bord, on a donc aucune sortie). On écrira 2 versions : une utilisant uniquement des files intermédiaires, l'autre uniquement des piles. Il est conseillé de commencer par faire des schémas. Comparer l'efficacité (temporelle + spatiale) des deux versions.
11. *Facultatif :* Implémentez vos algorithmes en OCaml et/ou en C.

*Le choix de la structure de donnée la plus appropriée est essentiel dans la conception d'un algorithme.*

## Exercice 2 : dérécursiver un algorithme à l'aide d'une pile (en OCaml)

Tout algorithme récursif peut être transformé en algorithme impératif. Si l'algorithme est récursif terminal, c'est très simple : chaque paramètre devient une variable mutable, et on effectue une boucle `TANT QUE` avec comme condition de sortie le cas de base de l'algorithme récursif. Un exemple avec la factorielle :

```ocaml
    let fact_terminal n_initial =							let fact_derecursive n_initial =
        let rec fact_aux n res = match n with					let res = ref 1 in
            | 0 -> res											let n = ref n_initial in
            | _ -> fact_aux (n - 1) (res * n)					while not (!n = 0) do
        in fact_aux n_initial 1										res := !res * !n ;
                                                                    n := !n - 1
                                                                done ;
                                                                !res
```

1. Que fait l'algorithme suivant ? Utilisez la technique ci-dessus pour le dérécursiver.

    ```ocaml
    let mystere_terminal n_initial =
    	let rec mystere_aux n res = match n with
    		| 0 -> res
    		| _ -> mystere_aux (n / 10) (res + n mod 10)
    	in mystere_aux n_initial 0
    ```

2. Écrire une fonction récursive terminale implémentant l'exponentiation (simple, pas rapide), puis la dérécursiver.

Dans le cas des algorithmes récursifs non terminaux, nous allons avoir besoin d'une pile afin de simuler les appels récursifs et les instructions restantes après les appels. Reprenons la factorielle, récursive non terminale cette fois :

```ocaml
let rec fact n = match n with
 	| 0 -> 1
 	| _ -> let appel = fact (n-1) in appel * n
```

On voit que le cas récursif ce décompose en deux étapes : l'appel récursif fait en premier, puis la multiplication. Pour dérécursiver cet algorithme, nous allons donc devoir placer dans une pile :

* d'abord la multiplication par `n` (qui sera donc dépilée en dernier)
* puis l'appel récursif sur `n-1`

Lorsqu'on dépile un élément, il faudra alors regarder s'il s'agit :

* d'une multiplication : alors on effectue cette multiplication
* d'un appel : si c'est le cas de base, on initialise notre résultat ; sinon on empile la multiplication et l'appel suivant

```ocaml
let fact_pile n =
    let res = ref 0 in
    let p = Stack.create () in (* crée une pile vide *)
    Stack.push ("appel", n) p ; (* au début la pile contient uniquement l'appel initial *)
    while not (Stack.is_empty p) do (* tant que la pile n'est pas vide *)
    	let instr, n = Stack.pop p in
    	if instr = "appel" then
    		if n = 0 then (* cas de base : le résultat est initialisé à 1 *)
    			res := 1
    		else begin (* cas récursif : on empile la multiplication puis l'appel suivant *)
    			Stack.push ("mult", n) p ;
    			Stack.push ("appel", n-1) p
    		end
    	else (* si on dépile une multiplication *)
    		res := !res * n
    done ;
    !res
```

3. Dessiner les évolutions de la pile `p` et donner les valeurs de `res` pour chaque itération de l'appel à `fact_pile 4`.
4. Écrire une version non terminale de l'exponentiation (simple toujours) puis la dérécursiver.
5. Écrire une fonction récursive non terminale qui fait la somme des éléments d'une liste d'entiers, puis la dérécursiver.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
