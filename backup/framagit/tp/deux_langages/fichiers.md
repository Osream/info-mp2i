# TP : Gestion de fichiers

Ce TP sera l'occasion de manipuler des fichiers depuis un programme en C et en OCaml. On étudie le **fonctionnement général de la gestion de fichiers** dans les deux langages puis on verra une application : la **sérialisation** d'une structure de données.

## I. Syntaxe pour la gestion de fichiers

> 1. Créez un fichier `liste.txt` contenant une vingtaine de lignes avec les prénoms de vos camarades de classe de votre choix, et un fichier `liste2.txt` vide.

### 1. En OCaml

Les fonctions qui permettent de manipuler des fichiers en OCaml sont :

* `open_in : string -> in_channel` ouvre en lecture le fichier dont le nom est passé en paramètre
* `open_out : string -> out_channel` ouvre en écriture le fichier dont le nom est passé en paramètre (attention, tout son contenu actuel est effacé à l'ouverture)
* `close_in : in_channel -> unit` ferme un fichier qui avait été ouvert en lecture
* `close_out : out_channel -> unit` ferme un fichier qui avait été ouvert en écriture
* `input_line : in_channel -> string` lit une ligne du fichier (le "curseur" est avancé d'une ligne après la lecture, ainsi un deuxième appel à cette fonction sur le même fichier lira la deuxième ligne)
* `output_string : out_channel -> string -> unit` écrit le texte dans le fichier

> 2. Écrivez une fonction `copie10 : string -> string -> unit` telle que `copie10 f1 f2` lit les 10 premières lignes de `f1` et les écrit dans `f2`.
>
> 2. Ajoutez la ligne suivante dans votre fichier :
>
>     ```ocaml
>     let _ =
>         copie10 "liste.txt" "liste2.txt"
>     ```
>
>     Compilez le fichier (avec `ocamlc` ou `ocamlopt`) et exécutez le. Ouvrez `liste2.txt` pour vérifier que tout a fonctionné.
>
> 3. Modifiez le `let _ = ...` pour que le programme prenne *en argument* (avec `Sys.argv`) les noms des deux fichiers. Vous afficherez un message d'erreur approprié dans le cas où le nombre d'arguments donnés n'est pas celui attendu. Compilez, testez.

Lorsqu'on lit un fichier, si celui-ci est terminé (le "curseur" est tout au bout, i.e. on a tout lu), une exception `End_of_file` est levée.

Pour lire tout un fichier, on aura donc un code ressemblant à ceci :

```ocaml
(* ouvrir le fichier ici *)
try
	while true do
		(* lire une ligne du fichier ici *)
	done
with End_of_file -> (* fermer le fichier ici *)
```

> 5. Écrivez une fonction `copie : string -> string -> unit` similaire à `copie10` mais qui cette fois copie l'intégralité du fichier. Compilez, testez.
> 5. Que se passe-t-il si on tente d'ouvrir en lecture un fichier qui n'existe pas ? Et en écriture ? À part l'inexistence du fichier, quelle peut être la cause d'une erreur lors de l'ouverture d'un fichier ?
> 6. Modifiez votre fonction `copie` pour attraper l'exception `Sys_error` si `f1` ou `f2` ne peut pas être ouvert, et afficher un message d'erreur approprié dans ce cas.

Nous avons vu en C qu'il était possible de récupérer des données entrées par l'utilisateur de deux manières différentes, c'est la même chose en OCaml :

- soit en ligne de commande : dans `Sys.argv`
- soit en lisant sur l'entrée standard au cours de l'exécution : avec `read_line : unit -> string` (équivalent du `scanf` en C).

> 8. Modifiez le `let _ = ...` pour lire successivement sur l'entrée standard les noms des deux fichiers à utiliser pour la copie.

Pour les entrées et les sorties, on dispose toujours de trois canaux de communication qui correspondent au flux standard :

* l'entrée standard `stdin` ( de type `in_channel`)
* la sortie standard `stdout` ( de type `out_channel`)
* la sortie d'erreur `stderr `( de type `out_channel`)

> 9. Rappelez comment rediriger ces trois canaux depuis une commande du terminal.
> 9. Modifiez votre programme pour que les messages d'erreurs soit écrits sur la sortie d'erreur. On remarquera que `stderr` existe toujours, inutile de l'ouvrir ou de le fermer.
> 10. Compilez, testez (en redirigeant et sans rediriger).

En fin de compte, on peut considérer `stdin`, `stdout` et `stderr` comme des fichiers spéciaux : les manipulations sont les mêmes, ils existent simplement toujours.

### 2. En C

L'équivalent des types `in_channel` et `out_channel` en C est le type `FILE*` que l'on appelle flux de données. Les fonctions qui permettent de manipuler des fichiers en C sont `fopen`, `fclose`, `fscanf`, `fprintf`.

La fonction `fopen` prend en paramètres le nom du fichier à ouvrir ainsi qu'un mode d'ouverture : "r" pour lecture (*read*), "w" pour écriture (*write*) et "a" pour écriture après le contenu préexistant (*append*).

Les fonctions `fprintf` et `fscanf` ont un fonctionnement similaire à `printf` et `scanf`, on ajoute juste le flux de données en premier paramètre.

> 12. Écrivez une fonction `void copie10(char* f1, char* f2)` qui effectue 10 lectures dans le fichier de nom `f1` et les écrit dans le fichier de nom `f2`.

La fonction `fscanf` *renvoie* la valeur `EOF` (de type `int`) lorsqu'on arrive à la fin de la lecture d'un fichier.

> 13. Écrivez une fonction `void copie(char* f1, char* f2)` qui copie tout le contenu du fichier de nom `f1` dans le fichier de nom `f2`.

En cas d'erreur à l'ouverture, c'est le pointeur `NULL` qui est renvoyé.

De même qu'en OCaml, le flux standard (`stdin`, `stdout` et `stderr`) est ouvert directement, et on peut s'en servir en paramètres des fonctions `fprintf` et `fscanf`.

> 14. Modifiez la fonction `copie` pour afficher un message d'erreur sur `stderr` en cas de problème à l'ouverture, et arrêter l'exécution de la fonction.



## II. Sérialisation de structures de données séquentielles

**Sérialiser** une structure de données, c'est la stocker « à plat » dans un fichier. La sérialisation est bijective, on doit pouvoir reconstruire la structure sans équivoque à partir des données stockées.

### 1. Sérialisation d'une pile

Pour sérialiser une pile, on choisit de stocker une donnée par ligne du fichier. Le sommet de la pile sera stocké dans la première ligne du fichier, et ainsi de suite.

Par exemple, si on a empilé les entiers `2`, puis `7`, puis `4`, alors sérialiser la pile donne un fichier contenant 3 lignes :

```
4
7
2
```

> 1. Écrivez en OCaml une fonction `serialise_pile : int Stack.t -> string -> unit` qui prend en paramètre une pile d'entiers `p` et le nom d'un fichier `fic` et sérialise `p` dans `fic`. Attention aux effets de bord (la pile ne doit pas avoir été modifiée).
>2. Écrivez en OCaml une fonction `deserialise_pile : string -> int Stack.t` qui prend en paramètre le nom d'un fichier dans lequel une pile d'entiers a été sérialisée et renvoie la pile correspondante. Attention à l'ordre des éléments !
> 3. Récupérez l'une de vos implémentations d'une pile en C, et écrivez deux fonctions similaires pour sérialiser / dé-sérialiser une pile d'entiers en C.

### 2. Sérialisation d'une file

Pour sérialiser une file, on stocke également une donnée par ligne du fichier. La première ligne du fichier contiendra le premier élément enfilé, et ainsi de suite.

Par exemple, si on a enfilé les entiers `2`, puis `7`, puis `4`, alors sérialiser la file donne un fichier contenant 3 lignes :

```
2
7
4
```

> 4. Écrivez en OCaml une fonction `serialise_file : int Queue.t -> string -> unit` qui prend en paramètre une file d'entiers `f` et le nom d'un fichier `fic` et sérialise `f` dans `fic`. Attention aux effets de bord.
>5. Écrivez en OCaml une fonction `deserialise_file : string -> int Queue.t` qui prend en paramètre le nom d'un fichier dans lequel une file d'entiers a été sérialisée et renvoie la file correspondante. Attention à l'ordre des éléments !
> 6. Récupérez l'une de vos implémentations d'une file en C, et écrivez deux fonctions similaires pour sérialiser / dé-sérialiser une file d'entiers en C.



## III. Exercices

> **Petites manipulations**
>
> 1. Écrivez en OCaml un programme qui prend en *argument* un entier `n`, effectue `n` lectures d'entiers sur `stdin`, fait leur somme, et affiche le résultat sur `stdout`. On gérera toutes les erreurs possibles en affichant un message sur `stderr`.
> 2. Pour sérialiser un tableau associatif, on stocke une association par ligne du fichier. Pour chaque association, on stockera d'abord la clé puis la valeur, séparées par un espace. L'ordre de stockage des associations n'a pas d'importance. Proposez deux fonctions en OCaml pour sérialiser et dé-sérialiser un tableau associatif (`(int, int) Hashtbl.t`).
> 3. On souhaite réécrire la commande `cat`, qui prend en entrée un certain nombre de noms de fichiers et affiche la concaténation de leurs contenus. Écrivez un programme en C tel que la commande `./cat nom_fichier1 nom_fichier2 ...` ait le même effet que `cat nom_fichier1 nom_fichier2 ...`(avec `./cat` le nom de l'exécutable lié au programme).
> 4. Écrivez en C un programme similaire à la commande `wc` : on affiche sur la sortie standard le nombre de lignes, de mots et de caractères d'un fichier.

> **Stéganographie (en C)**
>
> La _stéganographie_ est l'art de cacher un objet dans un autre. On peut par exemple cacher un message dans une image.
>
> Le format d'image que nous allons utiliser est le format PGM ascii. Pour faire court, ce format contient une première ligne avec obligatoirement les deux caractères "P2", ce qui permet d’indiquer le format de l’image ; une deuxième avec la largeur puis la hauteur de l’image, séparées par un caractère d’espacement ; une troisième contenant la valeur maximale utilisée pour coder les niveaux de gris et ensuite une succession de valeurs associées à chaque pixel de l’image, ligne par ligne, de gauche à droite, de haut en bas. Vous pouvez regarder la [description du format](https://fr.wikipedia.org/wiki/Portable_pixmap#Fichier_ASCII_2) pour plus de détails si vous le souhaitez.
>
> Chaque niveau de gris est ainsi codé par une valeur entre 0 et la valeur maximale, proportionnellement à son intensité. Un pixel noir est codé par la valeur 0, un pixel blanc est codé par la valeur maximale.
>
> Nous utiliserons ce type :
>
> ```c
> struct image_s {
> 	int haut;
> 	int larg;
> 	int max_couleur;
> 	uint16_t** pix;
> };
> typedef struct image_s image;
> ```
>
> 1. Écrivez une fonction `image* charger_image(char*)` qui prend en entrée le nom d'un fichier et renvoie un pointeur vers une zone mémoire contenant les données de l'image. On suppose que l'image est bien au bon format sans le vérifier. On gérera le cas où le programme ne parvient pas à lire le fichier en renvoyant le pointeur `NULL` et en affichant un message sur la sortie standard d'erreur. On utilise `"%hu"` pour lire un `uint16_t`.
>
> L'image fournie [image_avec_secret.pgm](img/image_avec_secret.pgm) contient un message caché de la manière suivante :
>
> * Chaque ligne de l'image permet de cacher un caractère.
> * Dans une ligne donnée, ce sont les 8 premiers pixels qui permettent de cacher le caractère.
> * Pour chacun des 8 pixels : s'il est pair, c'est le bit `0` qui est caché, s'il est impair c'est le bit `1` qui est caché.
> * On reconstitue ainsi un nombre à 8 bits : le bit caché par le premier pixel est multiplié par $`2^7`$, le bit caché par le second pixel est multiplié par $`2^6`$, ..., le bit caché par le huitième pixel est multiplié par $`2^0`$ ; et on additionne le tout.
> * Le nombre reconstitué correspond au code ASCII du caractère caché sur cette ligne.
> * Le message se termine quand on rencontre le caractère `'\0'` de code ASCII 0.
>
> Ainsi une image qui contiendrait dans la première ligne de pixels les niveaux de gris `80,81,81,89,89,90,89,80` pour ses pixels cacherait sur cette ligne le caractère `z` qui a pour code ASCII 122 qui s'écrit en binaire `01111010`.
>
> 2. Écrivez une fonction `char caractere(uint16_t*)` qui prend en paramètre un tableau d’au moins 8 pixels et renvoie le caractère caché avec cette méthode.
> 3. Déduisez-en une fonction `void message(image*, FILE*)` qui prend en paramètres une
>     image et un flux de données et écrit le message caché dans l'image dans le fichier correspondant au flux.
> 4. Quel est le message caché dans [image_avec_secret.pgm](img/image_avec_secret.pgm) ?
>
> On souhaite maintenant cacher nos propres messages dans une image.
>
> 5. Écrivez une fonction `void inserer_caractere(uint16_t*, char)` qui prend en paramètres un tableau de pixels d’au moins 8 cases et un caractère, et insère le caractère dans le tableau en suivant les règles décrites ci-dessus.
> 6. Écrivez une fonction `image* cacher(image*, char*)` qui prend en paramètres une image et une chaîne de caractères, cache le message dans l'image (sans oublier le caractère `'\0'` final) et renvoie l'adresse de l'image si l'image était assez grande pour contenir le message ou `NULL` si ce n'est pas le cas.
> 7. Écrivez une fonction `int sauvegarder_image(char*, image*)` qui prend en paramètres un nom de fichier et une image et sauvegarde l'image au format PGM ASCII dans ce fichier. La fonction renverra 1 s’il y a un problème avec l’image, 2 s’il y a un problème d’ouverture du fichier et 0 sinon.
>
> Pour tester vos fonctions, vous pouvez utiliser [image_originale.pgm](img/image_originale.pgm).
>
> 8. Écrivez pour terminer un programme qui prend en argument la chaîne "trouver" ou la chaîne "cacher" puis suivant la situation :
>
>     * "trouver" : lit sur l'entrée standard un nom de fichier et affiche sur la sortie standard le message secret contenu dans le fichier
>     * "cacher" : lit sur l'entrée standard un nom de fichier d'entrée, une chaîne de caractères et un nom de fichier de sortie dans lequel il va stocker une version du fichier d'entrée dans lequel on cache le message.
>
>     On prendra soin de gérer proprement les erreurs potentielles grâce à la sortie standard d'erreur.
>
> Attention dans cet exercice à bien gérer la mémoire (vérifier que les allocations n'échouent pas avec une assertion, vérifier qu'il n'y a pas de fuite de mémoire...).
>



## Pour aller plus loin

> 1. La commande `convert entree.jpg -compress None -depth 16 sortie.pgm` permet de convertir une image du format `jpg` au format `pgm`. Vous pouvez vous amuser à cacher des messages dans n'importe quelle image !
> 1. On souhaite réécrire les commandes `head -n nom_fichier` et `tail -n nom_fichier` qui lisent respectivement les `n` premières et dernières lignes d’un fichier et les affichent sur la sortie standard. Écrivez en C et/ou en OCaml deux programmes implémentant respectivement ces deux commandes.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source : I. Klimann (stéganographie)
