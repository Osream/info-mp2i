# TP : Bases d'OCaml

Nous allons découvrir ici les bases de la syntaxe du langage OCaml permettant de programmer en respectant le paradigme de programmation fonctionnel.

**Le contenu de ce TP introduit le langage OCaml et doit ainsi être considéré comme du cours. Charge à vous de prendre en note les notions importantes.**

Pour programmer en OCaml, nous utiliserons l'IDE (environnement de développement) Visual Studio Code. VS Code a l'avantage de posséder un terminal intégré, ce qui vous permettra de tester votre code sans changer sans arrêt de fenêtre.

OCaml est un langage compilé, cependant il possède aussi une REPL (read-eval-print loop) qui permet de tester facilement des petits morceaux de code, sans avoir à compiler puis exécuter tout un programme. Il s'agit du *toplevel*. Pour accéder au toplevel, il suffit d'entrer la commande `utop` (ou bien `ledit ocaml`).

> 0. Depuis la machine virtuelle, ouvrez Visual Studio Code, puis ouvrez le terminal intégré (onglet "Terminal" tout en haut). Lancez alors le toplevel.

Le toplevel permet donc de saisir et d'exécuter interactivement du code OCaml. Dans le toplevel, toutes les instructions terminent par `;;`.

La syntaxe pour écrire un commentaire en OCaml est la suivante : `(* commentaire ici *)`. *N'hésitez pas à vous en servir pour garder une trace de vos réponses pendant les TP. À la fin du TP, vous pourrez enregistrer votre travail dans votre dépôt `framagit`. Ne laissez rien dans la machine virtuelle, n'importe qui peut y avoir accès !*

## I. Types de base

Nous allons commencer par tester un certain nombre d’instructions afin de comprendre les règles d’utilisation des entiers, flottants, booléens, caractères et chaînes de caractères.

> 1. Entrez chaque instruction suivante dans le toplevel et vérifiez la réponse d'OCaml (type et valeur).
>
>     ```ocaml
>     # 1 + 2 ;;
>     # 1 - 6 ;;
>     # 1.0 +. 2.0 ;;
>     # 1.0 + 2.0 ;;
>     # 1 +. 2 ;;
>     # 1.0 + 2 ;;
>     # 1. +. 2. ;;
>     # 1.0 +. float_of_int 2 ;;
>     # 1.0 +. float 2 ;;
>     # 1 + int_of_float 2. ;;
>     # 1 + int_of_float 2.8 ;;
>     # 5. /. 3. ;;
>     # 5 / 3 ;;
>     # 6 *. 4 ;;
>     # 3 * 2 + 1 ;;
>     # 31 mod 3 ;;
>     # -31 mod 3 ;;
>     # 2. ** 5. ;;
>     # 2 ** 5 ;;
>     # min_int ;;
>     # max_int ;;
>     # max_int + 1 ;;
>     # min_int - 1 ;;
>     # max_float ;;
>     # min_float ;;
>     # 10. *. max_float ;;
>     # 0.1 +. 0.2 ;;
>     ```
>
>     2. A-t-on toujours `float_of_int (int_of_float x) = x ;;` ?
>     3. Et `int_of_float (float_of_int x) = x ;;` ?

Les opérateurs `*`, `/` et `mod` sont prioritaires par rapport à `+` et `-`.

> 4. Ajoutez toutes les parenthèses implicites et vérifiez :
>
>     ```ocaml
>     # 1 + 1 * 2 ;;
>     # 4 / 2 / 2 + 2 / 2 / 2 ;;
>     # 1 + 42 mod 3 + 42 / 2 * 5 / 5 ;;
>     ```

Lorsque les parenthèses ne sont pas nécessaires, la règle est la suivante : *on écrit les parenthèses si et seulement si le code s’en trouve plus lisible*.

> 5. Entrez chaque instruction suivante dans le toplevel et vérifiez la réponse d'OCaml (type et valeur).
>
> 	```ocaml
> 	# not true ;;
> 	# 1 = 1 ;;
> 	# 1 = 2 ;;
> 	# not (2 < 3) ;;
> 	# 1 <> 1 ;;
> 	# 1 <> 2 ;;
> 	# 1 < 1 ;;
> 	# 1 <= 1 ;;
> 	# true || false ;;
> 	# true && false ;;
> 	# (not (1 = 2)) && (3/0 = 1) ;;
> 	# true && (1/0 = 1) ;;
> 	# false && (1/0 = 1) ;;
> 	# true || (1/0 = 1) ;;
> 	# (not (1 >= 2)) || (3/0 = 1) ;;
> 	```

Les opérateurs OCaml sur les entiers, flottants et booléens sont infixes mais on peut les transformer en opérateurs préfixes en les encadrant de parenthèses.

> 6. Testez :
>
> 	``` ocaml
> 	# (+) 13 4 ;;
> 	# (/.) 7. 2. ;;
> 	# (&&) true false ;;
> 	# ( * ) 4 3 ;;
> 	```
>
> 7. Expliquez pourquoi les espaces sont nécessaires pour la multiplication.

OCaml fait la distinction entre les caractères et les chaînes de caractères.

> 8. Entrez chaque instruction suivante dans le toplevel et vérifiez la réponse d'OCaml (type et valeur).
>
>	```ocaml
>	# 'a' ;;
>	# "a" ;;
>	# "abc" ;;
>	# 'abc' ;;
>	# "abc".[0] ;;
>	# "abc".[1] ;;
>	# "abc".[2] ;;
>	# "abc".[3] ;;
>	# String.length "abc" ;;
>	# "abc" ^ "def" ;;
>	# String.make 4 'a' ;;
>	# String.sub "abcdef" 2 3 ;;
>	# String.sub ((String.make 5 'a')^(String.make 3 'b')) 4 2 ;;
>	# String.length (String.sub ((String.make 7 'a')^(String.make 9 'b')) 1 2) ;;
>	# string_of_int 4 ;;
>	# string_of_float 4.9 ;;
>	# string_of_float 4.0 ;;
>	# int_of_string "1" ;;
>	# float_of_string "1.4" ;;
>	# int_of_string "1.0" ;;
>	```

On peut construire des tuples de valeurs de types différents.

> 9. Entrez chaque instruction suivante dans le toplevel et vérifiez la réponse d'OCaml (type et valeur).
>
>     ```ocaml
>     # (1, 2) ;;
>     # ("Zéro", '0', 0, 0.) ;;
>     # (2, 3) = (1 + 1, 3) ;;
>     # (2.0, 1) = (2, 1.0) ;;
>     ```

Le type d'un tuple `(val1, val2, ...)` est de la forme `type_de_val1 * type_de_val2 * ...`.

## II. Variables

L'instruction `let variable = valeur` définit une variable globale. L'instruction `let variable = valeur in expression` définit une variable locale.

Le terme "variable" est abusif en OCaml, puisqu'elles sont immuables : on déclare en réalité plutôt des constantes.

> 1. Testez dans le toplevel les instructions suivantes :
>
>     ```ocaml
>     # let x = 42 ;;
>     # x ;;
>     # x = x + 1 ;;
>     # let x = 17 in x + 1 ;;
>     # x ;;
>     # let x2 = 4 in x2 * x2 ;;
>     # x2 ;;
>     # let a = 4 in let b = 2 in a * b ;;
>     # let a = 2 in let b = a * a in a + b ;;
>     ```
>     
>2. Déduisez-en la différence entre variable globale et variable locale.
> 
>3. Dans l'instruction suivante, `x` et `y` sont- elles des liaisons globales ou locales ?
> 
>    ```ocaml
>     # let y = (let x = 2 in x * x) ;;
>    ```

Il est possible de réaliser des déclarations simultanées avec `and`.

> 4. Testez dans le toplevel les instructions suivantes :
>
>     ```ocaml
>     # let x = 0 and y = 1 ;;
>     # let x = 0 and y = 1 in x + y ;;
>     # let a = 1 and b = a + 2 in a + b ;;
>     ```
>
>     Transformez la dernière instruction en une déclaration locale valide.

On peut utiliser `let` pour déconstruire un tuple.

> 5. Testez dans le toplevel :
>
>     ```ocaml
>     # let paire = (3, 2) ;;
>     # let (x, y) = paire ;;
>     # let coordonnees = (3., 2., 10.) ;;
>     # let (abscisse, _, _) = coordonnees ;;
>     ```
>
> 6. Quel est l'intérêt du `_` ?

## III. Fonctions

On définit une fonction ainsi : `let nom_fonction paramètres_séparés_par_des_espaces = code_de_la_fonction`.

Le type d'une fonction est `type_du_premier_parametre -> type_du_second_parametre -> ... -> type_de_retour`.

> 1. Pour chaque instruction suivante, prévoyez la réponse d'OCaml (type et valeur) *puis* vérifiez.
>
>     ```ocaml
>     # let f x = x * x ;;
>     # f 2 ;;
>     # f (-2) ;;
>     # f -2 ;;
>     # f (f 5) ;;
>     # f f 5 ;;
>     # (f f) 5 ;;
>     ```
>
> 2. Testez dans le toplevel :
>
>     ```ocaml
>     # (fun x -> x * x) 4 ;;
>     # (fun x -> x +. 1.5) 7.0 ;;
>     ```

On utilise `fun` pour les fonctions *anonymes* (c'est-à-dire quand on ne souhaite pas donner de nom à une fonction).

> 3. Pour chaque instruction suivante, prévoyez la réponse d'OCaml (*type* et valeur) puis vérifiez.
>
>     ```ocaml
>     # let g x y = x + y ;;
>     # g 2 3 ;;
>     # g 2 ;;
>     # (g 2) 3 ;;
>     ```
>
>     `h` est une fonction qui attend 2 entiers et retourne un entier.
>
>     `h 2` est une *application partielle* de `h` : c'est une fonction qui attend 1 entier et retourne 1 entier.
>
> 4. Entrez chaque instruction suivante dans le toplevel et vérifiez la réponse d'OCaml (type et valeur).
>
>     ```ocaml
>     # let est_egal x y = (x = y) ;;
>     # est_egal 2 3 ;;
>     # est_egal 2. 2. ;;
>     # est_egal true false ;;
>     # est_egal 2.0 2 ;;
>     ```
>
>     `=` est un opérateur *polymorphe* donc le type de la fonction est polymorphe aussi : il utilise une variable de type `'a`.
>
> 5. Pour chaque instruction suivante, prévoyez la réponse d'OCaml (type et valeur) *puis* vérifiez.
>
>     ```ocaml
>     # let f x g = g x ;;
>     # f 2 (fun x -> x * x) ;;
>     ```
>     
>     `f` est dite *d'ordre supérieur* car elle admet une fonction comme l'un de ses paramètres.
>
> 6. Prévoyez le type des deux fonctions suivantes *puis* vérifiez.
>
>     ```ocaml
>     # let hc x y = x + y ;;
>     # let hd (x,y) = x + y ;;
>     ```
>
>     `hc` est une fonction *curryfiée*, `hd` est une fonction *décurryfiée* (elle n'a qu'un seul paramètre qui est un tuple).
>     
>     En OCaml, on *privilégie toujours l'écriture curryfiée* des fonctions.

Généralement, on définit les fonctions dans l'éditeur puis éventuellement on les évalue dans le toplevel. Pour cela, il suffit d'entrer dans le toplevel l'instruction `#use "nom_du_fichier_contenant_la_fonction" ;;`

> 7. * Quittez le toplevel (CTRL + D ou `#quit;;`).
>    * Depuis le terminal intégré à VS Code, créez un fichier appelé `bases_ocaml.ml`.
>     * Entrez la commande `code bases_ocaml.ml` pour l'ouvrir dans VS Code.
>     * Dans le fichier `bases_ocaml.ml`, écrivez `let a = 2` (Ctrl + S pour sauvegarder).
>     * Dans le toplevel, entrez alors `#use "bases_ocaml.ml" ;;`.
>     * Dans le toplevel, entrez `a + 1 ;;`.

Les définitions de variables et de fonctions ne terminent pas par `;;` lorsqu'on écrit le code dans l'éditeur, cela est réservé au toplevel.

> 8. * Ajoutez dans le fichier `bases_ocaml.ml` la définition de fonction suivante : `let somme x y = x + y`.
>     * Évaluez la fonction `somme` dans le toplevel avec les valeurs de votre choix.
> 7. * Écrivez dans l'éditeur une fonction qui prend en entrée deux entiers naturels n et p et calcule leur produit.
>         Évaluez cette fonction dans le toplevel.
>     * Écrivez dans l'éditeur une fonction qui prend en entrée trois entiers n, p et q et qui renvoie la somme de q avec le produit de n et de p (vous réutiliserez les fonctions précédentes). Évaluez cette fonction dans le toplevel.
> 10. * Donnez le type des trois fonctions précédentes.
>     * Quel aurait leur type si on avait décurryfié ces fonctions ?

## IV. Conditionnelles

Une instruction conditionnelle s'écrit `if condition then expression_si_vrai else expression_si_faux`.

> 1. Testez dans le toplevel :
>
>     ```ocaml
>     # if true then 1 else 0 ;;
>     # 1 + (if true then 1 else 0) ;;
>     # if true then 1.0 else 2 ;;
>     ```
>
> 2. Que pouvez-vous dire sur les types de `expression_si_vrai` et `expression_si_faux` ?
>
> Voici plusieurs fonctions qui testent si un entier `x` est le nombre 2 ou le nombre 4 :
>
> ```ocaml
> let code1 x =
>     if (x = 4) then
>         true
>     else
>         if (x = 2) then
>             true
>         else
>             false
> 
> let code2 x =
>     if (x =4) then
>         true
>     else if (x=2) then
>         true
>     else
>         false
> 
> let code3 x =
>     if (x=4)
>     then true
>     else
>     if (x=2)
>     then true
>     else false
> 
> let code4 x =
>     if (x=4) then true
>     else if (x=2) then true
>     else false
> 
> let code5 x =
> 	if (x=4) then true else if (x=2) then true else false
> 
> let code6 x =
>     if (x=4 || x=2) then
>         true
>     else
>         false
>         
> let code7 x = x = 4 || x = 2
> ```
> 
> 3. Copiez ces fonctions dans le fichier `bases_ocaml.ml`, puis testez les toutes dans le toplevel. Font-elles bien toutes la même chose ?
> 
> 4. Ajoutez les parenthèses et indentations nécessaires au code suivant pour le rendre lisible :
>
>      ```ocaml
>    let test =
>     if let x = 42. in x *. x > 1700. then
>    if "OCaml" > "Python" then 12 else 21
>     else if true then
>     0
>     else let y = 1 in 1 - y * y
>    ```

Les espaces, indentations et retour à la ligne n'ont pas d'influence sur le code en OCaml. Par contre, vous avez dû remarquer qu'il est plutôt désagréable de lire un code non indenté. *Ayez toujours à l'esprit la lisibilité de votre code quand vous programmez !*

> 5. Écrivez (dans le fichier `bases_ocaml.ml`) une fonction permettant de calculer le `XOR` (ou exclusif) de deux booléens `a` et `b` en utilisant une conditionnelle. Testez (dans le toplevel).
>
>     (Si besoin, voir ci-dessous la table de vérité du XOR)
>
>     | XOR  | FAUX | VRAI |
>     | :--: | :--: | :--: |
>     | FAUX | FAUX | VRAI |
>     | VRAI | VRAI | FAUX |

## V. Filtrage

Le filtrage (ou *pattern matching*) permet de réaliser une disjonction de cas sur la forme d'une expression. Il s'écrit :

```ocaml
match expression with
	| filtre_1 -> valeur_1
	| ...
	| filtre_n -> valeur_n
```

> 1. Que fait la fonction suivante ?
>
>     ```ocaml
>     let f x = match x with
>         | 0 -> true
>         | _ -> false
>     ```
>
> 2. Parmi les codes suivants, lesquels sont équivalents au code de la fonction ci-dessus ? Testez !
>
>     ```ocaml
>     (* code 1 *)
>     match x with
>     	| 0 -> true
>     	| y -> false
>
>     (* code 2 *)
>     match x with
>     	| y -> false
>     	| 0 -> true
>
>     (* code 3 *)
>     match x with
>     	| 0 -> true
>     	| y when y <> 0 -> false
>
>     (* code 4 *)
>     match x with
>     	| y when y = 0 -> true
>     	| z when z <> 0 -> false
>
>     (* code 5 *)
>     match x with
>     	| y when y = 0 -> true
>     	| _ -> false
>     ```
>
> 3. Expliquez les "Warning" reçus pour les codes 2, 3 et 4 précédents.

> 4. On rappelle la table de vérité de l'implication logique :
>
>     |  P   |  Q   | P => Q |
>     | :--: | :--: | :----: |
>     | FAUX | FAUX |  VRAI  |
>     | FAUX | VRAI |  VRAI  |
>     | VRAI | FAUX |  FAUX  |
>     | VRAI | VRAI |  VRAI  |
>
>     Donnez au moins deux filtrages réalisant l'implication logique. Vous proposerez un code naïf listant les quatre cas possibles puis un code optimisé contenant uniquement deux filtres.

`function` permet de créer des fonctions en utilisant directement un filtrage.

> 5. Testez :
>
>     ```ocaml
>     let f = function
>     	| 0 -> 1
>     	| x -> 0
>     ```
>     ```ocaml
>     # f 4 ;;
>     # f 0 ;;
>     ```
>
>     Le code suivant est-il équivalent ?
>
>     ```ocaml
>     let f y = match y with
>     	| 0 -> 1
>     	| x -> 0
>     ```

L'expression calculée par une fonction peut bien sûr être plus conséquente, et utiliser notamment des variables locales.

> 6. Que fait le code suivant ? Ajoutez des commentaires pour expliquez les principales instructions.
>
>     ```ocaml
>     let sup i =
>     	let mpsi = "MPSI" in 
>     	let mp2i = "MP2I" in
>     	let pcsi = "PCSI" in
>     	match i with 
>     		| 1 | 2 -> mpsi ^ "-" ^ (string_of_int i)
>             | 3 -> mp2i
>             | 4 | 5 -> pcsi ^ "-" ^ (string_of_int (i - 3)) 
>             | _ -> failwith "aucune sup de ce type"
>                                                                             
>     let best = "La meilleure sup est la " ^ (sup 3)
>     ```

## VI. Récursivité

Une fonction `f` est dite récursive lorsque dans la pile d'appels peuvent se trouver simultanément plusieurs appels à `f`.

Pour définir une fonction récursive, il suffit d'ajouter le mot-clef `rec` après `let`.

> **Factorielle**
>
> Les codes suivants sont trois tentatives d'implémenter une fonction `factorielle` avec un filtrage.
>
> ```ocaml
> let rec factorielle1 x = match x with
> 	| 0 -> 1
> 	| n -> n * factorielle1 (n - 1)
> 
> let rec factorielle2 x = match x with
> 	| 0 -> 1
> 	| _ -> x * factorielle2 (x - 1)
> 
> let rec factorielle3 x = match x with
> 	| 0 | 1 -> 1
> 	| _ -> x * factorielle3 (x - 1)
> ```
>
> 1. * Expliquez ce qu'il se passe lorsqu'on appelle `factorielle1 4`.
>     * Pour vérifier, entrez dans le toplevel `#trace factorielle1 ;;`. Appelez ensuite la fonction.
> 2. Les trois codes sont-ils équivalents ? Testez.
> 3. Donnez *une unique* instruction permettant de vérifier que les trois fonctions ont le même résultat pour 10! en appelant une seule fois chaque fonction.
> 4. Définissez une fonction `factorielle4` qui utilise cette fois le mot-clef `function`.
> 5. Définissez une fonction `factorielle5` qui utilise maintenant une conditionnelle.
> 7. Combien de multiplications un appel à `factorielle1 n` réalise-t-il ? à `factorielle3 n` ?
> 8. Quelle est la hauteur maximale de la pile d'appel lors d'un appel à `factorielle1 n` ?
> 9. Essayez d'appeler `factorielle1` avec un entier négatif. Expliquez.

Le fameux `stack overflow` indique un dépassement de la pile d'appels (trop d'appels en cours).

Une application classique de la récursivité est le calcul des termes d'une suite récurrente.

> 9. Définissez une fonction récursive `u n` traduisant la suite suivante : $`\begin{cases} u_n = 3u_{n-1} + 2 \;\; si \; n > 0 \\ u_0 = 5\end{cases}`$
> 11. Définissez une fonction récursive `v n` traduisant la suite suivante : $`\begin{cases} v_{n+1} = \sqrt{v_n} + 4 \;\; si \; n > 0 \\ v_1 = 5\end{cases}`$

La récursivité est aussi une manière plus élégante d'écrire certains algorithmes itératifs.

> 11. Écrivez une fonction récursive `somme_cubes n` qui calcule $`S_n = \displaystyle\sum_{k=1}^n k^3\text{ avec } n\in\mathbb{N^*}`$.
> 14. Implémentez l'algorithme d'Euclide. Pour rappel, il est défini ainsi :  $`\begin{cases} pgcd(u, 0) = u \\ pgcd(u, v) = pgcd(v, r) \; \; \text{avec } r \text{ le reste de la division euclidienne de }u\text{ par }v\end{cases}`$

Une fonction non récursive peut faire appel à une fonction auxiliaire qui elle est récursive.

> 13. On rappelle que le coefficient binomial peut se calculer ainsi : $`\binom n k = \frac {n!} {k!(n-k)!}`$. Définissez une fonction non récursive `binom n k` qui utilise une fonction locale récursive `factorielle` pour calculer le coefficient binomial.
> 16. Y aura t-il des chevauchements (appel avec la même valeur effectué plusieurs fois) dans l'arbre d'appels de cette fonction ?
> 17. Le coefficient binomial peut aussi se définir avec la formule de Pascal : $`\binom {n+1} {k+1} = \binom n k + \binom n {k+1}`$. Définissez une fonction récursive `binom_rec n k` qui utilise cette définition.
> 18. Dessinez l'arbre d'appels pour $`\binom 5 3`$. Y a-t-il des chevauchements ?

La récursivité n'est qu'un outil de programmation comme un autre, on ne l'utilise pas s'il y a plus efficace.

> On cherche à calculer $`S_n = \displaystyle\sum_{i=0}^n i\text{ avec } n\in\mathbb{N}`$
>
> 17. Écrire une fonction récursive `somme n`.
>20. Quelle formule connaissez-vous pour calculer $`S_n`$ ? En déduire une autre fonction (non récursive) pour calculer cette valeur.
> 21. Vérifiez sur trois exemples que les deux fonctions donnent le même résultat.
> 22. Laquelle de ces deux fonctions donne la meilleure complexité spatiale (hauteur de la pile d'appels minimale) ?

Deux ou plus fonctions récursives peuvent s'appeler mutuellement. Leurs déclarations doivent alors être simultanées, on utilise pour cela `and`.

> 21. Que font les deux fonctions suivantes ?
>
>     ```ocaml
>     let rec mystere1 n = match n with
>     	| 0 -> false
>     	| _ -> mystere2 (n-1)
>     and mystere2 n = match n with
>     	| 0 -> true
>     	| _ -> mystere1 (n-1)
>     ```
>
> 24. Expliquez pourquoi le `and` est nécessaire (pourquoi il n'est pas possible de définir ces deux fonctions l'une après l'autre).

> **Exponentiation rapide**
>
> L'objectif ici est de définir un opérateur permettant de calculer $`x^n`$, avec `x` flottant et `n` entier.
>
> 1. Peut-on utiliser l'opérateur `**` directement ?
> 2. Définissez une fonction `puissance_pos x n` avec $`n \geq 0`$ utilisant l'égalité $`x^n = \begin{cases} 1 \text{ si n = 0} \\ x \times x^{n-1} \text{ sinon}\end{cases}`$.
> 3. Définissez une fonction `puissance_neg x n` avec $`n < 0`$. Vous pouvez réutiliser la fonction précédente.
> 4. Définissez un opérateur `***` qui permet de calculer $`x^n \;\forall n \in \mathbb{Z}`$.
> 5. Combien de multiplications réalise la fonction `puissance_pos` ?
> 6. Écrivez une fonction `expo_rapide x n` utilisant l'algorithme d'exponentiation rapide suivant : $`x^n = \begin{cases} 1 \;\; \text{si n = 0} \\ (x^2)^{\frac n 2} \text{ si n est pair} \\ x \times (x^2)^{\frac {n-1} 2} \text{ si n est impair}\end{cases}`$.
> 7. Cette fonction réalise-t-elle plus ou moins de multiplications que `puissance_pos` ?
> 8. Redéfinissez l'opérateur `***` pour utiliser l'algorithme d'exponentiation rapide.

## VII. Exercices

Pour chaque exercice suivant, vous écrirez les fonctions, *vérifierez leur type* et *testerez sur plusieurs exemples*. Il faudra prendre l'habitude de le faire systématiquement tout au long de l'année.

> **Quelques fonctions simples**
>
> 1. Écrire une fonction `norme : float -> float -> float` telle que `norme a b` vaille $`\sqrt{a² + b²}`$. La fonction racine carrée est prédéfinie, c’est `sqrt : float -> float`.
> 2. Écrire une fonction `moyenne : float -> float -> float` telle que `moyenne a b` renvoie
>     $`\frac{a + b}{2}`$.
> 3. En utilisant une affectation locale, écrire une fonction qui calcule $`\frac{1 + \sqrt{x} + \sqrt{x}^3}{e^{\sqrt{x}} - 1}`$ avec `x` un entier.
> 4. Écrire une fonction `th : float -> float` qui calcule la fonction tangente hyperbolique $`\frac{e^x - e^{-x}}{e^x + e^{-x}}`$ en effectuant un unique appel à la fonction `exp`.
> 5. En définissant $`f : x \mapsto \sin(\ln(x))`$ comme une fonction locale, implémenter la fonction $`g : x \mapsto \frac{f(x)}{1+(f(x+1))^2}`$.

> **Puissance**
>
> 1. En utilisant l’opérateur `**` et les fonctions de conversions, écrire une fonction `puissance : int -> int -> int` telle que l’appel `puissance n k` renvoie la valeur $`n^k`$.
> 2. Quelle est la limite de cette approche ?
>
> Attention, c’est une horreur absolue qu’il ne faudra plus jamais reproduire ! On utilisera l'algorithme d'*exponentiation rapide* pour faire une puissance sur des entiers.

> **Min et Max**
>
> 1. Écrire les fonctions `min : 'a -> 'a -> 'a` et `max : 'a -> 'a -> 'a` qui renvoient respectivement le plus petit et le plus grand de leurs arguments.
> 2.  Pourquoi peut-on dire que les expressions `(max 0)` et `(min 0.0)` sont des fonctions ? Quel est leur type ? Que font-elles ?
> 3. Que pensez-vous de `let min_bis x y = -(max (-x) (-y))` ?

> **Valeur absolue**
>
> 1. Écrivez les fonctions `valeur_absolue : int -> int`  et `valeur_absolue_float : float -> float` qui calculent la valeur absolue de leur argument.

> **Ordre supérieur**
>
> Définir des fonctions prenant en entrée une fonction `f : float -> float` et renvoyant :
>
> 1. la valeur $`\frac{f(0) + f(1)}{2}`$
> 2. la fonction $`f \circ f`$ 
> 3. la fonction $`x \mapsto f (x + 1)`$

> **Couples**
>
> Voici plusieurs façons équivalentes de définir la fonction `fst : 'a * 'b -> 'a` qui renvoie le premier élément d’un couple :
>
> ```ocaml
> let fst = fun (a, b) -> a
> 
> let fst = fun (a, _) -> a
> 
> let fst (a, b) = a
> 
> let fst (a, _) = a
> 
> let fst couple =
> 	let (a, b) = couple in
> 	a
> 
> let fst couple =
> 	let a, b = couple in
> 	a
> 
> let fst couple =
> 	let a, _ = couple in
> 	a
> ```
>
> 1. Définir de même, c’est-à-dire de toutes ces façons équivalentes, la fonction `snd` qui renvoie le deuxième élément du couple. Commencez par prévoir son type !
> 2. Implémenter, *après avoir trouvé leur type*, les fonctions suivantes :
>     * La fonction `duplicate` qui sur un argument `a` s’évalue en le couple (a, a).
>     * La fonction `swap` qui sur un couple (a, b) s’évalue en le couple (b, a).
>     * La fonction `concat` qui sur deux couples (a, b) et (c, d) s’évalue en le quadruplet
>         (a, b, c, d).

> **Formes curryfiée et décurryfiée**
>
> 1. Proposer une fonction `decurryfier` qui prend en entrée une fonction curryfiée à deux arguments et qui renvoie la même fonction mais en version non-curryfiée.
> 2. Quel est le type de `decurryfier` ?
> 3. Proposer une fonction `curryfier` qui prend en entrée une fonction décurryfiée à deux arguments et qui renvoie la même fonction mais en version curryfiée.

> **Conditionnelles**
>
> 1. Remplacer les expressions conditionnelles suivantes par des expressions équivalentes contenant strictement moins de if.
>
>     ```ocaml
>     let simplifie1 x = if x > 3 then false else true
>     
>     let simplifie2 x y =
>         if x then
>             if y then false
>             else true
>         else
>             if y then true
>             else false
>     ```
>
> 2. Une année bissextile est une année dont le numéro est divisible par 4, sauf s'il est aussi divisible par 100… sauf s'il est aussi divisible par 400. Écrivez deux versions d'une fonction `bissextile : int -> bool` : la première avec des conditionnelles, la seconde avec uniquement des opérateurs booléens.

> **Opérateurs booléens et filtrage**
>
> Il est possible de définir des opérateurs infixes en les mettant entre parenthèses. Voici par exemple la définition de l'opérateur `+` sur les entiers :
>
> ```ocaml
> let ( + ) a b = a + b
> ```
>
> 1. En utilisant des filtrages, ré-écrivez les opérateurs booléens infixes `&&` et `||`.
>
> 2. En utilisant des filtrages, définissez les opérations `xor`, `nand` et `nor` avec l'opérateur infixe de votre choix.

> **Récursivité**
>
> 1. Implémentez la fonction suivante : $`f (n) = \begin{cases} n - 10 \text{ si }n > 100 \\ f (f (n+11)) \text{ sinon}\end{cases}`$
>
> 2. La suite de Syracuse d'un entier `d` est définie par $`u_0 = d \text{ et } \forall n \in \mathbb{N}, u_{n+1} = \begin{cases} \frac{u_n}{2} \;\; \text{si}\; u_n \;\text{est pair} \\ 3u_n + 1 \;\;\text{sinon}\end{cases}`$. Le temps de vol de `d` est le plus petit entier `t` tel que $`u_t = 1`$. Écrivez une fonction récursive `syracuse d` qui donne le temps de vol de `d`.
>
> 3. Définissez une fonction `renverse_chaine s` qui renverse une chaîne de caractères.
>
> 4. En utilisant une fonction locale récursive, définissez une fonction `premier n` non récursive qui vérifie si `n` est premier. Pour rappel, `n` est premier si aucun entier entre `2` et `n-1` ne le divise.
>
> 5. Deux employés Dean et Sam travaillent dans un entrepôt qui contient des colis et doit être vidé. Les deux employés travaillent en alternance. Chacun utilise une stratégie différente :
>
>     * À chaque étape, Dean enlève à chaque fois un seul colis.
>     * À chaque étape, Sam enlève deux colis si le nombre de colis qu'il reste est pair, et un seul colis sinon.
>
>     1. Écrire deux fonctions (une par employé) mutuellement récursives qui calculent le nombre d'étapes nécessaires pour vider l'entrepôt s'il contient initialement *n* colis. Vérifiez que l'entrepôt contenant 11 colis est vide après 10 étapes si Dean commence, et après 11 étapes si Sam commence.
>     2. Même question avec un troisième employé Adam qui enlève 3 colis s'il en reste plus de 10, et un seul colis sinon.




---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*

Inspirations : V. Monfleur, N. Pecheux, I. Klimann, Q. Fortier
