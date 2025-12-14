# TP : Interface et implémentation de piles et de files en OCaml

Pour ce TP, nous allons apprendre à compiler et exécuter les fichiers depuis le terminal (comme nous le faisons en C depuis le début de l'année), **vous n'utiliserez donc pas le toplevel**.

## I. Compilation et fichiers d'interface

Dans ce TP, nous allons réaliser diverses implémentations des structures de piles et de files, mais leur *interface* ne va pas changer.

Voici par exemple l'interface d'un type pile mutable :

* `creer_pile : unit -> 'a pile` qui crée une pile vide
* `est_vide : 'a pile -> bool` qui est le test de vacuité
* `empiler : 'a pile -> 'a -> unit` qui ajoute un élément au sommet de la pile
* `depiler : 'a pile -> 'a` qui enlève et renvoie l'élément au sommet de la pile
* `sommet : 'a pile -> 'a` qui renvoie le sommet de la pile sans l'enlever

> **Fichier d'implémentation**
>
> 1. Créez un fichier `pile.ml` et ouvrez le dans VS Code.
>
> 2. Implémentez-y le type pile dont l'interface est donnée ci-dessus, en utilisant le module `Stack` :
>
>     ```ocaml
>     type 'a pile = 'a Stack.t
>     
>     let creer_pile () = Stack.create ()
>     
>     let est_vide p = Stack.is_empty p
>     
>     let empiler p elt = (* à compléter *)
>     
>     let depiler p = (* à compléter *)
>     
>     let sommet p = (* à compléter *)
>     ```
>
> 3. On souhaite vérifier qu'on ne tente pas d'accéder au sommet d'une pile vide. On peut pour cela utiliser une assertion : la fonction `assert` prend en paramètre une expression booléenne et :
>
>     * si elle est vérifiée, renvoie `unit` et passe à la suite du code ;
>     * si elle est fausse, lève une exception (`Assert_failure`).
>
>     Ajoutez une assertion dans les fonctions appropriées pour vérifier les préconditions.

Le langage OCaml propose deux compilateurs : `ocamlc` qui produit du bytecode et `ocamlopt` qui produit du code natif (plus efficace mais dont l’exécutable est moins transportable). Pour nous, cela ne fera pas vraiment de différence.

> **Compilation**
>
> 1. Exécutez la commande `ocamlc pile.ml`. Vous devriez voir apparaître 3 nouveaux fichiers :
>     * `pile.cmi` est l'interface compilée, générée automatiquement à partir du fichier d'implémentation
>     * `pile.cmo` est le bytecode
>     * `a.out` est l'exécutable (comme en C)
> 2. Supprimez les trois fichiers produits (avec `rm`).
> 3. Exécutez maintenant la commande `ocamlopt pile.ml`. Vous devriez voir apparaître 4 fichiers :
>     * `pile.cmi` est l'interface compilée, générée automatiquement à partir du fichier d'implémentation
>     * `pile.o` est le code natif compilé
>     * `pile.cmx` contient les informations nécessaires à l'édition des liens
>     * `a.out` est l'exécutable
> 4. Contrairement au C, tous les fichiers intermédiaires du processus de compilation sont produits, à la fois avec `ocamlc` et `ocamlopt`. Comme en C, il est possible de renommer l'exécutable, avec l'option `-o` : essayez la commande `ocamlopt -o pile pile.ml`.
> 5. Supprimez tous les fichiers produits par les diverses compilations.

Comme pour le C, on peut compiler en une seule étape ou détailler le processus de compilation d'abord avec l'option `-c` puis `-o`.

Ceci nous permet de faire de la programmation modulaire : on compile d'abord notre implémentation de la pile avec l'option `-c` puis on peut s'en servir dans d'autres programmes.

> **Compilation séparée**
>
> 1. Créez un nouveau fichier `manips.ml` et ouvrez-le dans VS Code.
>
> 2. Copiez-y le code suivant :
>
>     ```ocaml
>     let main () =
>         let p = Pile.creer_pile () in
>         Pile.empiler p Sys.argv.(0) ;
>         let x = Pile.depiler p in
>         print_endline x
>     
>     let _ = main ()
>     ```
>
>     Que fait-ce code ? On note que `Sys.argv` permet de récupérer les arguments du programme (donnés sur la ligne de commande à l'exécution, comme en C).
>
>     *Remarque : j'ai appelé la fonction principale `main` par correspondance avec le C, mais en OCaml ce n'est pas du tout obligatoire, vous pouvez la nommer comme vous le souhaitez.*
>
> 3. Pour utiliser les piles dans `manips.ml`, il faut que `pile` soit un module, c'est-à-dire qu'il ait été compilé. Exécutez la commande `ocamlc -c pile.ml`. Quels fichiers obtenez-vous ?
>
> 4. Normalement, VS Code soulignait en rouge le code de `manips.ml` car il ne connaissait pas le module `Pile`. Vérifiez que ce n'est plus le cas. Ceci est dû à la présence du fichier `pile.cmi` : l'interface est automatiquement détectée.
>
> 5. Compilons maintenant notre programme : `ocamlc -c manips.ml`. Quels fichiers obtenez-vous ?
>
> 6. Pour finir, créons notre exécutable : `ocamlc -o main pile.cmo manips.cmo`.
>
>     *Attention : contrairement au C, l'ordre est important : comme manips utilise pile, il faut impérativement donner à `ocamlc` d'abord le fichier `pile.cmo` puis `manips.cmo`*.
>
> 7. Exécutez : `./main`
>
>     *Remarque : La compilation séparée est possible aussi avec `ocamlopt` : la dernière étape se fait alors avec les fichiers `cmx` au lieu de `cmo`.*
>
> 9. Dans un fichier `somme.ml`, écrire un programme qui ajoute tous les arguments du programme (sauf le nom de l'exécutable) dans une pile, puis qui dépile tout en faisant la somme des arguments et affiche cette somme. On supposera que les arguments sont bien des entiers. Compilez, testez.

Lorsqu'on compile un fichier `.ml` qui n'a pas d'interface correspondante `.mli`, le compilateur en génère une automatiquement (on a bien quand même un fichier `.cmi`).

Le problème, c'est qu'absolument tout est alors reporté dans l'interface. Dans notre cas, cela signifie que l'utilisateur sait qu'on a utilisé le module `Stack` pour implémenter nos piles. Cela peut être problématique, car il pourrait utiliser tout ce qu'il y a dans notre code, même si ce sont des types ou des fonctions qui n'étaient destinées qu'à nous : par exemple si nous avions besoin d'une fonction auxiliaire pour la récursivité, on ne voudrait pas que l'utilisateur y ait accès...

Pour éviter que l'utilisateur ait connaissance par défaut de tout notre fichier, nous allons donc créer nous-même un fichier d'interface `.mli` et c'est lui qui sera utilisé pour produire le `.cmi`.

> **Fichier d'interface**
>
> 1. Si ce n'est pas déjà fait, supprimez tous les fichiers produits lors des précédentes compilations.
>
> 2. Créez un fichier `pile.mli` et ouvrez le dans VS Code, puis copiez-y la déclaration du type, puis pour chaque fonction sa signature et spécification complète :
>
>     ```ocaml
>     (** type 'a pile
>     	- représente une pile d'éléments
>         - polymorphe, homogène, mutable
>     *)
>     type 'a pile
>     
>     (** fonction creer_pile
>     	- entrée : rien
>     	- précondition : aucune
>     	- sortie : une pile
>     	- postcondition : la pile est vide, aucun effet de bord
>     *)
>     val creer_pile : unit -> 'a pile
>     
>     (** fonction est_vide
>     	- entrée : une pile
>     	- précondition : aucune
>     	- sortie : un booléen
>     	- postcondition : le booléen vaut true si la pile est vide et false sinon, aucun effet de bord
>     *)
>     val est_vide : 'a pile -> bool
>     
>     (** fonction empiler
>     	- entrée : une pile et un élément du même type que le contenu de la pile
>     	- précondition : aucune
>     	- sortie : aucune
>     	- postcondition : la pile contient les mêmes éléments qu'avant dans le même ordre, plus le nouvel élément au sommet (effet de bord)
>     *)
>     val empiler : 'a pile -> 'a -> unit
>     
>     (** fonction depiler
>     	- entrée : une pile
>     	- précondition : la pile ne doit pas être vide
>     	- sortie : un élément du même type que le contenu de la pile
>     	- postcondition : l'élément renvoyé est celui au sommet de la pile (dernier ajouté) et la pile ne contient plus cet élément (effet de bord)
>     	- lève une Assert_failure si les préconditions ne sont pas respectées
>     *)
>     val depiler : 'a pile -> 'a
>     
>     (** fonction sommet
>     	- entrée : une pile
>     	- précondition : la pile ne doit pas être vide
>     	- sortie : un élément du même type que le contenu de la pile
>     	- postcondition : l'élément renvoyé est celui au sommet de la pile (dernier ajouté), aucun effet de bord
>     	- lève une Assert_failure si les préconditions ne sont pas respectées
>     *)
>     val sommet : 'a pile -> 'a
>     ```
>
>     *Remarque : Pour les fonctions qui possèdent des assertions, il faut le préciser dans la spécification. Si des fonctions levaient d'autres types d'exceptions dans certains cas, il faudrait le préciser aussi.*
>
> 3. Essayez la commande suivante : `ocamlc -c pile.ml`. Que se passe-t-il ?
>
> 4. Le compilateur détecte qu'une interface existe, donc contrairement à avant il refuse de générer automatiquement le `.cmi`. Il faut donc compiler avant l'interface : `ocamlc -c pile.mli`. Quel fichier est produit ?
>
> 5. Compilez maintenant `pile.ml`, quel fichier est produit ? Créez enfin un exécutable avec `somme.ml` ou bien `manips.ml`.
>
> *Remarque : à nouveau, on aurait pu utiliser `ocamlopt` de la même manière.*

## II. Implémentation d'une pile avec une liste chaînée

Nous allons maintenant implémenter une pile sans utiliser le module `Stack`.

> 1. L'interface sera la même que pour l'implémentation précédente. Exécutez donc la commande `cp pile.mli pile_liste.mli`.
>
> 2. Créez un fichier `pile_liste.ml`, ouvrez le dans VS Code puis copiez-y la déclaration de type suivante :
>
>     ```ocaml
>     type 'a pile = 'a list ref
>     ```
>
> 3. Définissez dans ce fichier les 5 fonctions de l'interface d'une pile avec ce type. N'oubliez pas les assertions nécessaires.
>
> 4. Compilez l'interface puis l'implémentation.
>
> 5. Pour valider un programme en pratique, chaque fonction doit avoir un jeu de tests. Téléchargez [le fichier suivant](code/tests_pile_liste.ml), qui contient un jeu de tests pour le module `Pile_liste` que vous venez de programmer. Compilez le, puis exécutez. Si rien n'apparaît, c'est que tous les tests sont passés : votre programme semble correct. Si une assertion est levée, c'est qu'il y a une erreur dans votre module.

## III. Implémentation d'une file avec deux listes chaînées

Nous allons maintenant implémenter une file mutable, dont voici l'interface :

* `creer_file : unit -> 'a file` qui crée une file vide
* `est_vide : 'a file -> bool` qui est le test de vacuité
* `tete : 'a file -> 'a` qui renvoie la tête de la file sans l'enlever
* `enfiler : 'a file -> 'a -> unit` qui ajoute un élément en queue de la file
* `defiler : 'a file -> 'a` qui enlève et renvoie l'élément de tête de la file

> 1. Commencez par créer un fichier d'interface `file_liste.mli` avec spécifications complètes pour ce type.

Nous allons implémenter une file par un couple de listes : l’avant de la file, classée par ordre d’arrivée et l’arrière, classée par ordre inverse d’arrivée :

```ocaml
type 'a file = {mutable avant : 'a list; mutable arriere : 'a list}
```

* Les nouveaux arrivants seront placés en tête de la liste arrière.
* Les premiers arrivés seront extraits en tête de la liste avant.
* Lorsque la liste avant est épuisée on retourne la liste arrière, on la place à l’avant et on réinitialise la liste arrière à `[]`. Cette opération de retournement a une complexité linéaire en la taille de la liste arrière, donc le temps d’extraction du premier élément d’une file ainsi implémentée n’est pas constant, mais comme un élément de la file n’est retourné qu’au plus une fois, on obtient une complexité amortie constante.

> 2. Dans un fichier `file_liste.ml`, copiez la définition du type puis implémentez les 5 fonctions de l'interface.
> 3. Téléchargez [le fichier suivant](code/tests_file_liste.ml), qui contient un jeu de tests pour le module `File_liste` que vous venez de programmer. Compilez le, puis exécutez. Si rien n'apparaît, c'est que tous les tests sont passés : votre programme semble correct. Si une assertion est levée, c'est qu'il y a une erreur dans votre module.

## IV. Implémentation d'une pile et d'une file avec un tableau

Nous allons maintenant implémenter une pile et une file en utilisant un tableau, en supposant que la taille de la structure ne dépasse jamais un entier `tAILLE_MAX`.

Commençons par la file, voici son type :

```ocaml
type 'a file = {mutable debut : int; mutable fin : int; elts : 'a array}
```

Une file est donc définie par trois champs :

* le tableau `elts` qui contient les éléments de la file
* l'indice de début de la file (où est rangé le prochain élément à défiler)
* l'indice de fin de la file (où doit être rangé le prochain élément à enfiler)

Attention, on utilise un tableau circulaire, il est donc tout à fait possible d’avoir `fin < debut`. Une conséquence de ce choix est que l’égalité `fin = debut` ne permet pas de distinguer entre la file vide et la file pleine ; pour palier à ce problème, on s’interdit de remplir complètement le tableau : ainsi, on décrète qu’une file qui contient `tAILLE_MAX − 1` éléments est pleine, situation caractérisée par l’égalité : `(fin + 1) mod tAILLE_MAX = debut`.

> 1. Copiez l'interface d'une file dans un fichier `file_tableau.mli`.
>
> 2. Créez un fichier `file_tableau.ml`, définissez une constante `tAILLE_MAX` avec la valeur de votre choix, copiez-y la déclaration du type `file` ci-dessus puis implémentez les 5 fonctions de l'interface d'une file.
>
>     *Remarque : on pourra exceptionnellement se limiter aux files d'entiers.*
>
> 3. De manière similaire, implémentez une pile avec un tableau de taille maximale fixée. A-t-on besoin de 2 indices comme pour les files ?
>
> 4. Compilez, et testez vos deux modules avec les fichiers de tests de la partie précédente (seule la ligne du « open » doit être modifiée).

## V. Implémentations d'une file avec des variantes de listes chaînées

> **Exercice 1**
>
> Définissons le type file à l’aide d’une liste chaînée pour laquelle on garde un accès à la fois au premier
> mais aussi au dernier maillon :
>
> ```ocaml
> type 'a maillon = Vide | Cons of {valeur: 'a; mutable suivant: 'a maillon}
> 
> type 'a file = {
> 	mutable premier: 'a maillon ;
> 	mutable dernier: 'a maillon
> }
> ```
>
> On enfile au niveau du dernier maillon et on défile le premier.
>
> Implémentez une file avec ce type.
>
> *Remarque : vous devez avoir un fichier d'implémentation, un fichier d'interface, un fichier de tests. N'oubliez pas de compiler et de tester vos fonctions, y compris pour les cas où les préconditions ne sont pas respectées.*

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
> 	entree: 'a Stack.t ;
> 	sortie: 'a Stack.t
> }
> ```
>
> Implémentez une file avec ce type.
>
> *Remarque : vous devez avoir un fichier d'implémentation, un fichier d'interface, un fichier de tests. N'oubliez pas de compiler et de tester vos fonctions, y compris pour les cas où les préconditions ne sont pas respectées.*

## Pour aller plus loin

> 1. Vérifiez que vous retrouvez bien les mêmes complexités que celles vues en cours pour vos implémentations.
> 2. Réfléchissez à des implémentations de piles et files persistantes.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*
