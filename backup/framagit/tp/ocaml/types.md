# TP : Déclaration de types en OCaml

Dans ce TP nous allons manipuler des types produits et des types sommes.

## I. Alias

Un alias permet de définir un type en "renommant" un type déjà existant.

Par exemple dans le TP sur les listes OCaml nous avons manipulé des polynômes qui étaient des `(int * int) list`. On aurait pu les définir ainsi :

```ocaml
type polynome = (int * int) list
```

La fonction `derivee` serait alors de type `polynome -> polynome`. Pour forcer l'utilisation de l'alias, on peut utiliser des annotations de type avec la syntaxe suivante :

```ocaml
let rec derivee (p : polynome) : polynome =
    match p with ...
```

> 1. Définissez un alias `date` pour un 3-uplets d'entiers (le jour, le mois et l'année).
> 2. Écrivez une fonction `nb_jours : date -> int` qui renvoie le nombre de jours que possède le mois actuel. On rappelle que février peut avoir 29 jours en cas d'année bissextile (année multiple de 400, ou bien multiple de 4 mais pas de 100). On s'assurera que le type de la fonction utilise bien l'alias défini.
> 3. Écrivez une fonction `demain : date -> date` qui renvoie la date du lendemain de la date passée en paramètre. On s'assurera que le type de la fonction utilise bien l'alias défini.

Dans la suite du TP, on veillera à utiliser des annotations de types afin que les fonctions utilisent bien les alias appropriés.

## II. Type produit

Le type produit permet de définir un nouveau type à plusieurs *champs*.

Voici un exemple :

```ocaml
type couleur = {rouge : float ; bleu : float ; jaune : float} (* création du type *)
let orange = {jaune = 50. ; rouge = 50. ; bleu = 0.} (* définition d'une valeur ayant ce type *)
let b = orange.rouge (* récupération de la valeur d'un champ *)
```

> 1. Créez une variable `vert` avec ce type.
> 2. Écrivez une fonction `taux_de_bleu : couleur -> float` qui renvoie le pourcentage de bleu dans la couleur donnée en paramètre.
> 3. Écrivez une fonction `melange : couleur -> couleur -> couleur` qui prend en entrée deux couleurs et renvoie la couleur obtenue en mélangeant les deux couleurs en quantité égales c’est-à-dire en déterminant le pourcentage de chaque couleur primaire dans le mélange des deux couleurs passées en argument.
>

Un filtrage sur un type produit ne doit pas nécessairement contenir tous les champs. Par exemple, on peut faire :

```ocaml
let a_du_bleu coul = match coul with
	| {bleu = x} when x > 0 -> true
	| _ -> false
```

Lorsqu'on écrit un programme respectant le paradigme impératif, les types produits peuvent posséder des champs mutables. On doit alors placer le mot-clef `mutable` devant le nom du champ dans la déclaration du type :

```ocaml
type mon_type = {champ1 : type_champ1 ; mutable champ2 : type_champ2 ; ...}
```

Ici le `champ1` est immuable et le `champ2` mutable.

On modifie la valeur d'un champ mutable ainsi :

```ocaml
variable.champ2 <- nouvelle_valeur
```

> 4. Définissez un type produit `personne` ayant un champ "prénom" immuable, un champ "nom" immuable, et un champ "age" mutable.
> 5. Créez une variable de ce type contenant les informations vous concernant.
> 6. Écrivez une fonction `anniversaire : personne -> unit` qui augmente de 1 l'âge de la personne donnée en paramètre.

La fonction précédente ne renvoie rien, mais elle modifie son paramètre : on dit qu'elle a un *effet de bord*. C'est très fréquent quand on écrit des programmes suivant le paradigme de programmation *impératif*, mais impossible avec le paradigme fonctionnel.

Dans le paradigme impératif, nous avons besoin de modifier les valeurs de nos variables. Les types produits peuvent nous permettre de représenter des variables mutables :

```ocaml
type 'a var_mutable = {mutable valeur : 'a}
```

> 7. Écrivez une fonction `incremente : int var_mutable -> unit`  qui incrémente la valeur de la variable mutable.
> 8. Écrivez une fonction `decremente : int var_mutable -> unit` .
> 9. Écrivez une fonction `echange_valeurs : 'a var_mutable -> 'a var_mutable -> unit` qui échange les valeurs de deux variables mutables.

Les variables mutables sont prédéfinies en OCaml, ce sont les *références*. Nous aurons l'occasion de les manipuler dans un prochain TP.

## III. Type somme

On définit un type somme en énumérant tous les cas possibles pour avoir ce type. Chaque cas est identifié par un *constructeur*.

Voici un exemple :

```ocaml
type valeur = As | Roi | Dame | Valet | Petite of int
let v = Valet
let deux = Petite 2
```

On manipule généralement ces types en utilisant des filtrages :

```ocaml
let int_of_valeur v = match v with
    | As -> 14
    | Roi -> 13
    | Dame -> 12
    | Valet -> 11
    | Petite i -> i
```

> 1. Écrivez une fonction `est_valide : valeur -> bool` qui renvoie `true` si la valeur de la carte est valide, `false` sinon (numéro d'une petite carte qui ne serait pas entre 2 et 10).
> 2. Écrivez une fonction `gagne : valeur -> valeur -> bool` qui renvoie `true` si la carte passée en premier paramètre est plus forte que la deuxième et `false` en cas de défaite ou d'égalité.
> 3. Définissez un type somme `symbole` pour les cartes (pique, trèfle, carreau, cœur).
> 4. Écrivez une fonction `est_rouge : symbole -> bool` qui renvoie `true` si la carte est rouge (cœur ou carreau), et `false` si elle est noire (pique ou trèfle).
> 5. Définissez un type alias `carte`  pour un couple (valeur, symbole).

Il existe un type somme prédéfini en OCaml, le type `'a option` :

```ocaml
type 'a option = None | Some of 'a
```

C'est un type très utile pour définir des fonctions qui peuvent ne pas avoir de résultat.

Attention, une valeur de type `'a option` n’est pas de type `'a` : il faut « déconstruire » l’option si l’on veut récupérer le `'a`.

> 6. Écrivez une fonction `indice : 'a -> 'a list -> int option` qui renvoie l'indice de la première occurrence d'un élément dans une liste sous la forme `Some i` ou `None` si l'élément n'est pas présent.
> 7. Écrivez une fonction `premier_indice : 'a -> 'a list -> 'a list -> int option` qui prend en paramètre un élément `x` et deux listes `l1` et `l2` et renvoie le minimum de `indice x l1` et `indice x l2`.

## IV. Types récursifs

Un type peut être récursif, c'est-à-dire faire appel à lui-même dans sa définition.

Voici un exemple de type somme récursif :

```ocaml
type itineraire = Arrive | Prendre of string * itineraire | Avancer of int * itineraire
let route = Prendre("rue des Acacias", Avancer(200, Prendre("boulevard Alan Turing", Avancer(70, Arrive))))
```

> 1. Écrivez une fonction `distance : itineraire -> int` qui indique le nombre de mètres total de l'itinéraire.
> 1. Écrivez une fonction `itineraire_complet : itineraire -> string` qui renvoie une chaîne lisible déroulant un itinéraire. Par exemple : `"prendre rue des Acacias, puis avancer de 200m, puis prendre boulevard Alan Turing, puis avancer de 70m, puis vous êtes arrivés."`.

Voici maintenant un exemple de type produit récursif :

```ocaml
type poupee = {taille : int ; contenu : poupee option}
let poupee_taille_2 = {taille = 2 ; contenu = Some {taille = 1 ; contenu = None}}
```

> 3. Pourquoi le champ contenu doit-il être de type `poupee option` ?
> 4. Écrivez une fonction `poupees_decr : poupee -> bool` qui vérifie que les poupées sont bien de tailles strictement décroissantes.
> 5. Écrivez une fonction `creer_poupees : int -> poupee` qui renvoie une poupée de taille `n` qui contient une poupée de taille `n - 1`, qui contient ... , qui contient une poupée de taille `1` vide.

Pour finir, il existe des types mutuellement récursifs, comme par exemple :

```ocaml
type magasin =
    | Boutique of string * string (* nom de la boutique, nom de la ville *)
    | Supermarche of string * string (* nom du supermarché, nom de la ville *)
    | Centre_commercial of centre
and centre = {nom : string ; ville : string ; magasins : magasin list}
```

> 6. Créez un centre commercial de nom V2, à Villeneuve d'Ascq, contenant
>     * Un autre centre commercial Heron Parc à Villeneuve d'Ascq contenant une boutique Cultura à Villeneuve d'Ascq
>     * Un supermarché Auchan à Villeneuve d'Ascq
>     * Une boutique Micromania à Villeneuve d'Ascq
> 7. Écrivez une fonction `verifie_villes : centre -> bool` qui vérifie que la ville d'un centre est bien la même que toutes les villes des magasins qui le compose.

## V. Exercices

Les exercices suivants permettent de s'entraîner sur les déclarations de types *non mutables*. On veillera à ce que chaque fonction soit conforme au paradigme fonctionnel.

> **Triplets** (alias)
>
> 1. Définissez un alias `triplet` pour un 3-uplet d'entiers.
> 2. Écrivez une fonction `rotation : triplet -> triplet` qui permute vers la droite un triplet d'entiers. Par exemple, `rotation (1, 2, 3) = (3, 1, 2)`. On s'assurera que le type de la fonction utilise bien l'alias défini.
> 3. Écrivez une fonction `rotations : triplet -> triplet list` qui renvoie la liste des 3 rotations du triplet donné.
> 4. Définissez un alias `permutation` correspondant à une liste de triplets d'entiers. Modifier la fonction précédente pour utiliser cet alias.
> 5. Écrivez une fonction `trouve_permutations : triplet -> permutation` qui prend en paramètre un triplet et renvoie la liste de toutes ses permutations possibles.
> 6. Écrivez une fonction `est_permutation : permutation -> triplet -> bool` qui prend en paramètre une liste de triplets et vérifie s'ils correspondent bien tous à une permutation possible du triplet donné en second paramètre.

> **Pixels** (type produit)
>
> Un pixel est défini par trois valeurs entières : son niveau de rouge, son niveau de vert, et son niveau de bleu. Chaque niveau doit être compris entre 0 et 255.
>
> 1. Définissez un type produit `pixel` à 3 champs correspondant aux couleurs d'un pixel selon le modèle RGB.
> 2. Écrivez une fonction `valide_pixel : pixel -> bool` qui vérifie que les valeurs des couleurs d'un pixel sont valides.
> 3. Écrivez une fonction `pixel_noir_blanc : pixel -> pixel` qui renvoie un pixel noir (tout à 0) ou blanc (tout à 255). Un pixel devient noir si la moyenne de ses trois niveaux est strictement inférieure à 128, blanc sinon.
> 4. Définissez un alias `image` pour une liste de listes de pixels.
> 5. Écrivez une fonction `image_noir_blanc : image -> image` qui transforme une image en noir et blanc.

> **Pierre - Feuille - Ciseaux** (type somme)
>
> 1. Définissez un type somme `coup` qui décrit les trois coups possibles de ce jeu.
> 2. Définissez un type somme `resultat` qui représente une victoire, une défaite, ou une égalité.
> 3. Définissez un alias `manche` pour un couple de coups (le coup du joueur, le coup de l'adversaire).
> 4. Définissez un alias `score` pour un couple d'entiers (le score du joueur, le score de l'adversaire).
> 5. Écrivez une fonction `tour : unit -> manche` qui renvoie une manche aléatoire. *Vous pourrez utiliser la fonction `Random.int`*.
> 6. Écrivez une fonction `resultat_tour : manche -> resultat` qui étant donné une manche, donne le résultat du point de vue du premier joueur.
> 7. Écrivez une fonction `maj_score : score -> resultat -> score` qui renvoie un score mis à jour en fonction du résultat d'une manche.
> 8. Écrivez une fonction `resultat_jeu : score -> resultat` qui étant donné le score actuel d'une partie, donne le résultat du point de vue du premier joueur.
> 9. Écrivez une fonction `jeu : int -> resultat` qui simule une partie dont le nombre de manches est passé en paramètre.

> **Dates**
>
> 1. Choisissez un type approprié pour représenter un mois.
> 2. Choisissez un type approprié pour représenter une date (jour, mois, année).
> 3. Écrivez une fonction qui vérifie si une date est valide.
> 4. Écrivez une fonction qui prend en paramètre une date et renvoie la date du lendemain.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*

