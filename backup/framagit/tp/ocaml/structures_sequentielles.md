# TP : Structures séquentielles en OCaml

Pour ce TP, nous allons apprendre à *compiler* et *exécuter* les fichiers depuis le terminal (comme nous le faisons en C depuis le début de l'année), ***VOUS N'UTILISEREZ DONC PAS LE TOPLEVEL***.



## I. Processus de compilation

Voici l'interface d'un type **pile** mutable (principe LIFO) :

* `creer : unit -> 'a pile` qui crée une pile vide
* `est_vide : 'a pile -> bool` qui est le test de vacuité
* `empiler : 'a -> 'a pile -> unit` qui ajoute un élément au sommet de la pile
* `depiler : 'a pile -> 'a` qui enlève et renvoie l'élément au sommet de la pile

> 1. Créez un fichier `pile.ml` et copiez-y les lignes suivantes :
>
>     ```ocaml
>     type 'a pile = 'a Stack.t
>                         
>     let creer () =
>         Stack.create ()
>                         
>     let est_vide p =
>         Stack.is_empty p
>                         
>     let empiler elt p =
>         Stack.push elt p
>                         
>     let depiler p =
>         Stack.pop p
>     ```
>

On peut vérifier les préconditions des fonctions à l'aide d'assertions. La fonction `assert` prend en paramètre une expression booléenne et :

* si elle est vérifiée, renvoie `unit` et passe à la suite du code ;
* si elle est fausse, lève une exception (`Assert_failure`).

> 2. On souhaite vérifier qu'on ne tente pas de dépiler une pile vide. Ajoutez une assertion dans la fonction `depiler`.

Le langage OCaml propose deux compilateurs : `ocamlc` qui produit du bytecode et `ocamlopt` qui produit du code natif (plus efficace mais moins transportable). Pour nous, cela ne fera pas vraiment de différence.

> 3. Exécutez la commande `ocamlc pile.ml`. Vous devriez voir apparaître 3 nouveaux fichiers :
>    * `pile.cmi` est l'interface compilée, générée automatiquement à partir du fichier d'implémentation
>     * `pile.cmo` est le bytecode
>     * `a.out` est l'exécutable (comme en C)
> 4. Supprimez les trois fichiers produits.
> 5. Exécutez maintenant la commande `ocamlopt pile.ml`. Vous devriez voir apparaître 4 fichiers :
>     * `pile.cmi` est l'interface compilée, générée automatiquement à partir du fichier d'implémentation
>     * `pile.o` est le code natif compilé
>     * `pile.cmx` contient les informations nécessaires à l'édition des liens
>     * `a.out` est l'exécutable
> 6. Supprimez tous les fichiers produits par les diverses compilations.

Contrairement au C, tous les fichiers intermédiaires du processus de compilation sont produits (à la fois avec `ocamlc` et `ocamlopt`).

Comme en C, il est possible de compiler en une seule étape (comme fait ci-dessus) ou détailler le processus de compilation d'abord avec l'option `-c` puis `-o`.

Ceci nous permet de faire de la programmation modulaire : on compile d'abord notre implémentation de la pile avec l'option `-c` puis on peut s'en servir dans d'autres programmes.

> 7. Créez un nouveau fichier `manips.ml` et copiez-y le code suivant :
>
>     ```ocaml
>     (* une fonction utilisant les piles *)
>     let sommet p =
>     	let res = Pile.depiler p in
>     	Pile.empiler res p ;
>     	res
>     
>     (* code qui se lancera à l'exécution *)
>     let _ =
>         let p = Pile.creer () in
>         Pile.empiler 1 p ;
>         Pile.empiler 2 p ;
>         let x = sommet p in
>         print_int x ;
>         print_newline ()
>     ```
>
> 8. Pour utiliser les piles dans `manips.ml`, il faut que `pile.ml` ait été compilé. Exécutez la commande `ocamlc -c pile.ml`. Quels fichiers obtenez-vous ?
>
> 9. Compilez ensuite le programme principal : `ocamlc -c manips.ml`. Quels fichiers obtenez-vous ?

On peut maintenant créer l'exécutable. Contrairement au C, l'ordre est important : comme `manips` utilise `pile`, il faut impérativement donner à `ocamlc` d'abord le fichier `pile.cmo` puis `manips.cmo`.

> 10. Créez l'exécutable : `ocamlc -o exec pile.cmo manips.cmo`.
> 11. Exécutez : `./exec`.

La compilation séparée est possible aussi avec `ocamlopt` : la dernière étape se fait alors avec les fichiers `cmx` au lieu de `cmo`.

> 12. Supprimez tous les fichiers produits lors du processus de compilation, puis recommencez les étapes avec `ocamlopt`.

Lorsqu'on compile un fichier `.ml` qui n'a pas d'interface correspondante `.mli`, le compilateur en génère une automatiquement (on a bien quand même un fichier `.cmi`).

Le problème, c'est qu'absolument tout est alors reporté dans l'interface. Dans notre cas, cela signifie que l'utilisateur sait qu'on a utilisé le module `Stack` pour implémenter nos piles. Cela peut être problématique, car il pourrait utiliser tout ce qu'il y a dans notre code, même si ce sont des types ou des fonctions qui n'étaient destinées qu'à nous : par exemple si nous avions besoin d'une fonction auxiliaire pour la récursivité, on ne voudrait pas que l'utilisateur y ait accès...

Pour éviter que l'utilisateur ait connaissance par défaut de tout notre fichier, nous allons donc créer nous-même un fichier d'interface `.mli` et c'est lui qui sera utilisé pour produire le `.cmi`.

> 13. Supprimez tous les fichiers produits lors des précédentes compilations.
>
> 14. Créez un fichier `pile.mli` et copiez-y le code suivant :
>
>     ```ocaml
>     (*
>     Représente une pile d'éléments
>     polymorphe, homogène, mutable
>     *)
>     type 'a pile
>     
>     (*
>     Entrée : aucune.
>     Précondition : aucune.
>     Sortie : une pile.
>     Postcondition : la pile renvoyée est vide.
>     *)
>     val creer : unit -> 'a pile
>     
>     (*
>     Entrée : une pile.
>     Précondition : aucune.
>     Sortie : un booléen.
>     Postcondition : renvoie true si la pile est vide, false sinon.
>     *)
>     val est_vide : 'a pile -> bool
>     
>     (*
>     Entrée : une pile et un élément du même type que le contenu de la pile.
>     Précondition : aucune.
>     Sortie : aucune.
>     Postcondition : la pile contient les mêmes éléments qu'avant dans le même ordre, plus le nouvel élément au sommet (effet de bord).
>     *)
>     val empiler : 'a -> 'a pile -> unit
>     
>     (*
>     Entrée : une pile.
>     Précondition : la pile n'est pas vide. Lève une Assert_failure en cas de non respect.
>     Sortie : un élément du même type que le contenu de la pile.
>     Postcondition : l'élément renvoyé est celui au sommet de la pile (dernier ajouté, principe LIFO) et la pile ne contient plus cet élément (effet de bord).
>     *)
>     val depiler : 'a pile -> 'a
>     ```
>
> 15. Essayez la commande suivante : `ocamlc -c pile.ml`. Que se passe-t-il ?
>
> 16. Le compilateur détecte qu'une interface existe, donc contrairement à avant il refuse de générer automatiquement le `.cmi`. Il faut donc compiler l'interface : `ocamlc pile.mli`. Quel fichier est produit ?
>
> 17. Compilez maintenant `pile.ml`, quel fichier est produit ?
>
> 18. En C, lorsqu'on souhaite fournir une structure de données à un utilisateur, on lui donner le fichier `.h` (interface) et le fichier `.o` (implémentation compilée). Que doit-on donner en OCaml ?

Voici l'interface d'un type **file** mutable (principe FIFO) :

* `creer : unit -> 'a file` qui crée une file vide
* `est_vide : 'a file -> bool` qui est le test de vacuité
* `enfiler : 'a -> 'a file -> unit` qui ajoute un élément au bout de la file
* `defiler : 'a file -> 'a` qui enlève et renvoie l'élément en tête de la file

> 19. En vous inspirant des codes ci-dessus, créez deux fichiers `file.mli` contenant l'interface d'une file (avec spécifications complètes) et `file.ml` contenant une implémentation d'une file (avec le module `Queue`).
> 20. Compilez les deux fichiers.



## II. Manipulations

Pour cette partie, on travaillera intégralement dans le fichier `manips.ml`.

> 1. Écrivez deux fonctions `affiche_pile : int pile -> unit` et `affiche_file : int file -> unit`.
>
>     Pour une file, l'affichage se fera sur une ligne, avec la prochaine donnée à défiler tout à gauche, et ainsi de suite. On séparera les données par des espaces. Par exemple, une file dans laquelle on a enfilé successivement les valeurs 2, puis 7, puis 4 sera affichée ainsi :
>
>     ```ocaml
>     2 7 4
>     ```
>
>     Pour une pile, l'affichage se fera sur une colonne, avec la prochaine donnée à dépiler tout en haut, et ainsi de suite. Par exemple, une pile dans laquelle on a empilé successivement les valeurs 2, puis 7, puis 4 sera affichée ainsi :
>
>     ```ocaml
>     4
>     7
>     2
>     ```
>
>     Les fonctions ne doivent pas avoir d'effet de bord. Ainsi, la pile / file doit avoir retrouvé son état d'origine une fois l'affichage terminé.
>
> 2. Modifiez alors le `let _ = ...`  pour créer la file et pile données en exemples ci-dessus et appeler vos fonctions d'affichage.
>
> 3. Compilez, testez !
>
> 4. Modifiez de nouveau le `let _ = ...` pour créer une pile et une file contenant tous les entiers passés en arguments du programme, puis les afficher.
>
>     On supposera que les arguments sont bien des entiers.
>
>     *On rappelle que `Sys.argv` permet de récupérer les arguments du programme (donnés sur la ligne de commande à l'exécution, comme en C).*
>
> 5. Compilez, testez !

Un **tableau associatif** est une structure permettant de stocker des associations entre des clés et des valeurs. Cette structure ressemble beaucoup aux tableaux classiques, sauf que pour accéder à une valeur, on n'utilise plus son indice, mais sa clé.

Le module `Hashtbl` d'OCaml implémente les tableaux associatifs (par des tables de hachage, comme son nom l'indique). On utilisera les fonctions :

* `Hashtbl.create : int -> ('a, 'b) Hashtbl.t` qui crée un tableau associatif vide.
* `Hashtbl.add : ('a, 'b) Hashtbl.t -> 'a -> 'b -> unit` qui ajoute une association clé / valeur à un tableau associatif.
* `Hashtbl.mem : ('a, 'b) Hashtbl.t -> 'a -> bool` qui réalise le test d'appartenance d'une clé à un tableau associatif.
* `Hashtbl.remove : ('a, 'b) Hashtbl.t -> 'a -> unit` qui supprime une association d'un tableau associatif (depuis sa clé).
* `Hashtbl.find : ('a, 'b) Hashtbl.t -> 'a -> 'b` qui renvoie la valeur associée à une clé d'un tableau associatif. L'exception `Not_found` est levée si la clé donnée n'est pas présente dans le tableau associatif.
* `Hashtbl.find_opt : ('a, 'b) Hashtbl.t -> 'a -> 'b option` qui a un fonctionnement similaire à `find` mais renvoie un type option (`None` si la clé n'appartient pas au tableau associatif, `Some` et la valeur sinon).

L'entier donné en paramètre de `create` est la taille initiale souhaitée pour la création de la table de hachage (qui est dynamique, donc sera de toute façon redimensionnée au besoin). Pour éviter de redimensionner trop souvent la table de hachage (ce qui est coûteux en temps) mais sans réserver trop de cases vides (ce qui est coûteux en espace), on essaie si possible de choisir un entier proportionnel au nombre d'éléments qu'il y aura dans le tableau associatif.

> 6. Écrivez une fonction `update : ('a, 'b) Hashtbl.t -> 'a -> 'b -> unit` qui modifie la valeur associée à une clé d'un tableau associatif. Si la clé n'est pas présente, on lèvera une exception.
> 7. Écrivez une fonction `mon_find` qui fait exactement la même chose que `find`, en utilisant la fonction `find_opt` (et sans appeler la fonction `find` bien entendu).
> 8. Modifiez le `let _ = ...` pour tester ces deux fonctions sur un tableau associatif contenant des associations de votre choix.

OCaml propose une dernière fonction bien utile : `Hashtbl.iter : ('a -> 'b -> unit) -> ('a, 'b) Hashtbl.t -> unit`. Comme pour les listes et les tableaux, cette fonction prend en paramètre une fonction `f` et applique `f` à chaque association du tableau associatif.

> 9. Écrivez une fonction `affiche_TA` qui utilise `iter` afin d'afficher l'ensemble des associations clé/valeur (une association par ligne) d'un tableau associatif. On supposera que l'ensemble des clés et des valeurs sont des entiers.

On cherche à déterminer s'il y a des doublons dans une pile ou une file.

> 10. Écrivez une fonction `mem_pile : 'a -> 'a pile -> bool` qui détermine si une valeur appartient à une pile. Cette fonction ne doit pas avoir d'effet de bord.
> 10. Écrivez une fonction `existe_doublons : 'a pile -> bool` qui détermine si une pile contient deux fois la même valeur, en utilisant la fonction `mem_pile`. Cette fonction ne doit pas avoir d'effet de bord.
> 11. Calculez la complexité de cette méthode de détection de doublons.
> 12. Si on disposait d'une fonction qui trie une pile ayant $n$ éléments en $`\mathcal O(n\log n)`$, pourrait-on s'en servir pour détecter plus efficacement des doublons ? Quelle serait la complexité ?

Une méthode plus efficace consiste à utiliser un tableau associatif. Pour cela, on regarde les éléments de la pile / file un par un et :

* si on ne l'avait jamais croisé, on le stocke comme clé dans un tableau associatif (les valeurs associées peuvent être n'importe quoi)
* sinon (on l'a déjà croisé, i.e. il est déjà dans le tableau associatif), il y a un doublon.

> 14. Écrivez une fonction `existe_doublons_v2 : 'a pile -> bool` utilisant la méthode décrite ci-dessus. Cette fonction ne doit pas avoir d'effet de bord.
> 14. Montrez la correction de votre fonction.
> 15. Expliquez brièvement pourquoi la fonction `mem` sur les tableaux associatifs implémentés par une table de hachage a une complexité amortie constante.
> 16. Calculez la complexité de la fonction `existe_doublons_v2`.

On peut également utiliser un tableau associatif pour compter efficacement le nombre d'occurrences de chaque élément d'une pile / file.

> 18. Écrivez une fonction `nb_occs : 'a file -> ('a, int) Hashtbl.t` qui renvoie un tableau associatif qui à chaque élément de la file associe son nombre d'occurrences. La complexité devra être linéaire en le nombre d'éléments de la file, et la fonction ne doit pas avoir d'effet de bord.
> 18. Écrivez une fonction `maxi_TA : ('a, int) Hashtbl.t -> 'a` qui renvoie la clé d'un tableau associatif dont la valeur associée est maximale. On pourra éventuellement se limiter à des clés de type `int`.
> 18. Déduisez-en une fonction `maxi_file : 'a file -> 'a` qui renvoie l'élément le plus fréquent d'une file.
> 18. Modifiez le `let _ = ...` pour créer un programme qui affiche l'argument le plus fréquent passé en argument (avec `Sys.argv`).

Le choix de la structure de donnée la plus appropriée est essentiel dans la conception d'un algorithme.



## III. Implémentations d'une pile et d'une file

Nous allons maintenant implémenter par nous-même les piles et files. Dans toute la suite, on interdit donc d'utiliser les modules `Stack` et `Queue`.

### 1. Avec un tableau

La première implémentation que nous réaliserons utilisera un tableau, en supposant que la taille de la structure ne dépasse jamais un entier `tAILLE_MAX`.

On se limitera exceptionnellement à des files d'entiers.

> 1. Les interfaces ne changent pas. Exécutez donc la commande `cp pile.mli pile_tableau.mli`. Copiez de même l'interface des files dans un fichier `file_tableau.mli`.
> 2. Créez deux fichiers `pile_tableau.ml` et `file_tableau.ml`, et définissez-y une constante `tAILLE_MAX` avec la valeur de votre choix.

Commençons par la file, voici son type :

```ocaml
type 'a file = {mutable debut : int; mutable fin : int; elts : 'a array}
```

Une file est donc définie par trois champs :

* le tableau `elts` qui contient les éléments de la file
* l'indice de début de la file (où est rangé le prochain élément à défiler)
* l'indice de fin de la file (où doit être rangé le prochain élément à enfiler)

Attention, on utilise un tableau circulaire, il est donc tout à fait possible d’avoir `fin < debut`. Une conséquence de ce choix est que l’égalité `fin = debut` ne permet pas de distinguer entre la file vide et la file pleine ; pour palier à ce problème, on s’interdit de remplir complètement le tableau : ainsi, on décrète qu’une file qui contient `tAILLE_MAX − 1` éléments est pleine, situation caractérisée par l’égalité : `(fin + 1) mod tAILLE_MAX = debut`.

> 3. Copiez la déclaration du type `'a file` ci-dessus dans le fichier `file_tableau.ml` puis implémentez les 4 fonctions de l'interface d'une file.
> 4. Ajoutez des assertions pour les fonctions `enfiler` (si le tableau est plein) et `defiler` (si la file est vide).

On peut implémenter une pile de manière très similaire :

```ocaml
type 'a pile = {mutable fin : int; elts : 'a array}
```

> 5. Pourquoi n'a-t-on pas besoin d'un indice `debut` comme pour les files ?
> 6. Copiez la déclaration du type `'a pile` ci-dessus dans le fichier p`ile_tableau.ml` puis implémentez les 4 fonctions de l'interface d'une pile. N'oubliez pas les assertions.

Pour valider un module en pratique, il faut toujours réaliser un fichier de tests. Voici par exemple des tests pour vos deux implémentations :

* [tests pour les piles](code/tests_pile_tableau.ml)
* [tests pour les files](code/tests_file_tableau.ml)

> 7. Téléchargez ces deux fichiers, compilez tout, et exécutez. Si rien n'apparaît, c'est que tous les tests sont passés : votre programme *semble* correct. Si une assertion est levée, c'est qu'il y a une erreur dans votre module.

### 2. Avec des maillons chaînés

La première implémentation que nous réaliserons utilisera des maillons chaînés (autrement dit le type `list` qui en OCaml est implémentée avec des maillons chaînés).

Commençons par la pile :

```ocaml
type 'a pile = {mutable chaine_maillons : 'a list}
```

> 8. Copiez de nouveau l'interface : `cp pile.mli pile_liste.mli`.
> 9. Dans un fichier `pile_liste.ml`, copiez le type ci-dessus puis implémentez les 4 fonctions de l'interface des piles. Pensez aux assertions.
> 10. Testez à l'aide du même fichier de tests que l'implémentation précédente (seule la ligne du « open » doit être modifiée).

Nous allons implémenter une file par deux chaînes distinctes de maillons :

```ocaml
type 'a file = {mutable sortie : 'a list; mutable entree : 'a list}
```

* Les nouveaux arrivants seront placés en tête de la liste entrée.
* Les premiers arrivés seront extraits en tête de la liste sortie.
* Lorsque la liste sortie est épuisée on retourne la liste entrée, on la place en sortie et on réinitialise la liste entrée à `[]`.

> 11. Écrivez une fonction `renverse : 'a list -> 'a list` qui renverse récursivement une liste, avec une complexité linéaire.
> 12. Implémentez une file avec ce type. Pensez à tester (même fichier de tests que l'implémentation précédente, seule la ligne du « open » doit être modifiée).
> 13. Calculez la complexité amortie de l'opération « défiler ».

### 3. Autres implémentations

> **Exercice 1**
>
> Définissons le type file à l’aide d’une liste chaînée pour laquelle on garde un accès à la fois au premier mais aussi au dernier maillon :
> 
>```ocaml
> type 'a maillon = Vide | Cons of {valeur: 'a; mutable suivant: 'a maillon}
> 
> type 'a file = {
> 	mutable premier: 'a maillon ;
> 	mutable dernier: 'a maillon
> }
> ```
> 
>On enfile au niveau du dernier maillon et on défile le premier.
> 
>Implémentez une file avec ce type.
> 
>*Remarque : vous devez avoir un fichier d'implémentation, un fichier d'interface, un fichier de tests. N'oubliez pas de compiler et de tester vos fonctions, y compris pour les cas où les préconditions ne sont pas respectées.*

> **Exercice 2**
>
> Implémentons une file avec deux piles :
>
> * Une pile "entrée" dans laquelle on ajoutera les éléments lors de l'opération "enfiler".
> * Une pile "sortie" dans laquelle on retirera les éléments lors de l'opération "défiler".
> * Si la "sortie" est vide quant on souhaite défiler, on transvasera le contenu de la pile "entrée" dans celle "sortie".
>
> ```ocaml
> type 'a file = {
> 	entree: 'a Pile.pile ;
> 	sortie: 'a Pile.pile
> }
> ```
>
> Implémentez une file avec ce type.
>
> *Remarque : vous devez avoir un fichier d'implémentation, un fichier d'interface, un fichier de tests. N'oubliez pas de compiler et de tester vos fonctions, y compris pour les cas où les préconditions ne sont pas respectées.*

## Pour aller plus loin

> 1. Vérifiez que vous retrouvez bien les mêmes complexités que celles vues en cours pour vos implémentations.
> 2. Réfléchissez à des implémentations de piles et files immuables.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*
