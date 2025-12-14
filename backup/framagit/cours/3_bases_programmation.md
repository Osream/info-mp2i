# Chapitre 3 : Bases de programmation

Résumé et compléments sur les bases de la programmation utilisées en TP.

## Partie A : Bases générales du C et du OCaml

### I. Fonctionnement général d'un programme

Brève présentation des deux langages. Le OCaml est un langage naturellement fonctionnel (qui autorise l'usage du paradigme impératif). Le C est un langage naturellement impératif (qui autorise l'usage du paradigme fonctionnel).

Organisation des différents fichiers composant un programme (code source, interface, fichier objet, exécutable).

En C, écriture d'un fichier d'entête idempotent (avec `#ifndef, #define, #endif`) et utilisation de bibliothèques (`#include`).

Différentes étapes du processus de compilation (préprocesseur, compilation, édition de liens).

Commandes pour la compilation. Possibilité d'utiliser le toplevel en OCaml.

Notion de commentaire, syntaxe pour les commentaires `//` et `/* */`en C, et `(* *)` en OCaml.

### II. Types de base

Caractéristiques du typage dans les deux langages (statique ou dynamique, fort ou faible, implicite ou explicite). Notion d'inférence des types en OCaml. Le type définit la taille mémoire de la variable.

#### 1. Caractères

Type `char`.

Notion de code ASCII.

Syntaxe avec des apostrophes.

Taille mémoire des caractères en C / en OCaml.

#### 2. Entiers

##### En OCaml :

Type `int`, opérateurs `+, -, *, /, mod`, exception `Division_by_zero`.

Taille mémoire, `min_int, max_int`, comportement en cas de dépassement de capacité d'entiers.

##### En C :

Entiers signés (`signed`) ou non (`unsigned`) de taille mémoire non explicite (`int`), ou entiers de taille explicite (`int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t`).

Comportements en cas de dépassement de capacité d'entiers signés  / non signés, `INT_MAX` et `INT_MIN`.

Opérateurs `+, -, *, /, %`.

#### 3. Flottants

##### En OCaml :

Type `float`, taille mémoire.

Opérateurs `+., -., *., /., **`, fonctions `floor, ceil, exp, log, sin, cos, sqrt`.

Représentation limitée.

##### En C :

Types `float`(32 bits) et `double` (64 bits)

Représentation limitée, on utilise `double` pour avoir plus de précision.

#### 4. Booléens

Type `bool`, valeurs `true` et `false`, taille mémoire.

Opérateurs logiques de conjonction `&&`, disjonction `||`, et négation `!` (en C) et `not` (en OCaml), et séquentialité de ces opérateurs.

Opérateurs de comparaison en C : `==, !=, <, <=, >, >=`.

Opérateurs de comparaison en OCaml : `=, <>, <, <=, >, >=`, polymorphisme de ces opérateurs.

#### 5. Exceptions

Définition d'une exception.

Gestion des exceptions en OCaml :

* Type `exn`.
* Lever une exception avec `raise` et `failwith`.
* Attraper une exception avec `try ... with`.
* Créer une exception avec `exception`.

### III. Conditions

#### 1. Instructions conditionnelles

Syntaxe pour écrire une instruction conditionnelle en C (`if, else`).

Syntaxe pour écrire une instruction conditionnelle en OCaml (`if, then, else`).

Type d'une conditionnelle en OCaml.

#### 2. Filtrages en OCaml

Intérêt des filtrages, fonctionnement général et type.

Syntaxe pour écrire un filtrage (`match ... with | ... -> ... | ...`), caractère joker `_`, clause multiple, clause gardée (`when`).

Avertissements causés par certains filtrages : non exhaustivité, clause non utilisée.

## Partie B : Éléments caractéristiques de la programmation fonctionnelle

### I. Variables

Définition d'une variable.

Le terme "variable" est abusif en programmation fonctionnelle, les variables sont immuables (leurs valeurs ne peuvent pas être modifiées).

#### 1. En C

Contraintes pour les identificateurs.

Déclaration et affectation de variables, mot-clef `const` pour les rendre immuable.

Portée des variables (`{ ... }`).

Conversions implicites et explicites.

#### 2. En OCaml

Contraintes pour les identificateurs.

Les variables sont immuables.

Déclaration d'une variable globale (`let`) et d'une variable locale (`let` combiné avec `in`).

Déclarations simultanées (`and`).

Fonctions de conversion `float, float_of_int, int_of_float, string_of_int, int_of_string, float_of_string, string_of_float`.

### II. Fonctions

#### 1. En C

Syntaxe pour la déclaration, pour la définition et pour l'appel d'une fonction.

`void` pour les fonctions sans `return`.

Passage par valeur des paramètres.

Fonction principale `main`.

#### 2. En OCaml

Syntaxes pour la définition d'une fonction : avec `let`, avec `fun`, avec `function`.

Type d'une fonction curryfiée.

Notion de polymorphisme.

Fonctions d'ordre supérieur (exemple de la composée de deux fonctions).

Application partielle.

### III. Structures de données

En OCaml uniquement.

#### 1. Tuples (`n`-uplets)

Séquence de valeurs dont le type est le produit cartésien du type de ses éléments.

Syntaxe pour la construction et la déconstruction d'un tuple.

Fonctions `fst` et `snd` pour les couples.

Définition d'une fonction décurryfiée.

#### 2. Listes chaînées

Type `'a list` et caractéristiques des listes.

Syntaxe pour la création et manipulation des listes.

Fonctions récursives pour parcourir une liste avec un filtrage.

Fonctions existantes sur le type `'a list`.

## Partie C : Éléments caractéristiques de la programmation impérative

### I. Séquence

Distinction entre expression et instruction.

#### 1. En C

Chaque instruction termine par un point-virgule.

Affectation composée.

#### 2. En OCaml

Type `unit`, valeur `()`. `unit` comme paramètre d'une fonction ou comme valeur de retour d'une fonction.

Références : type `'a ref`, mutable. Les références doivent être utilisées à bon escient. Opérations sur les références : création avec `ref`, dé-référencement avec `!`, affectation avec `:=`.

Opérateur de séquencement `;`, types des instructions d'une séquence et type de la séquence. Mots-clefs `begin ... end`.

### II. Boucles

#### 1. Boucle bornée (for)

En C :

```c
for (initialisation; condition_arret; modification) {
    instructions
}
```

En OCaml :

```ocaml
for compteur = debut to fin do (* ou « downto » *)
	instructions
done
```

Types des boucles en OCaml.

#### 2. Boucle non bornée (while)

En C :

```c
while (condition) {
    instructions
}
```

En OCaml :

```ocaml
while condition do
	instructions
done
```

Types des boucles en OCaml.

#### 3. Remarques

Instructions `break` et `continue` en C.

Sortie prématurée d'une boucle grâce aux exceptions en OCaml.

Rappels sur la portée des variables

### III. Gestion de la mémoire en C

Notion de pointeur, `type*`.

Pointeur `NULL`.

Opérateurs de référencement `&` et de dé-référencement `*`.

Allocation dynamique : `malloc, free, sizeof`, fuites de mémoire.

Intérêts des pointeurs et de l'allocation dynamique.

### IV. Structures de données impératives

#### 1. Tableaux

##### En C

Tableaux statiques : `type nom_tableau[taille_litérale] = {valeur1, valeur2, ...};`.

Tableaux dynamiques : voir l'allocation dynamique dans la partie précédente.

Accès et modification d'un élément du tableau `nom_tableau[indice]`.

`Segmentation fault` en cas d'indice invalide.

##### En OCaml

Type `'a array` (homogène, polymorphe, mutable, taille statique fixée à la création).

Syntaxe pour la création `[|elt1 ; elt2 ; ... |]`, pour l'accès à un élément `tableau.(indice)`, pour la modification d'un élément `<-`.

Fonctions existantes du module `Array`.

#### 2. Chaînes de caractères

##### En C

Chaînes de caractères : tableau contenant une sentinelle (caractère nul `\0`).

Fonctions `strlen, strcpy, strcat, strcmp` de la bibliothèque `string.h` et fonctions de conversions `atoi, atof`.

##### En OCaml

Type immuable `string`.

Opérations sur les chaînes : accès à un caractère `chaine.(indice)`, longueur d'une chaîne `String.length`, concaténation `^`, création d'une chaîne d'une certaine taille composée d'un même caractère `String.make`, extraction d'une sous-chaîne `String.sub`.

### V. Interactions avec l'utilisateur

#### 1. En C

Arguments en ligne de commande : `int main(int argc, char* argv[])`.

Entrée / sortie standard : `printf, scanf`.

Gestion de fichiers : type `FILE*`, fonctions `fopen, fclose, fprintf, fscanf`, valeur `EOF`.

#### 2. En OCaml

Arguments en ligne de commande : `Sys.argv`.

Entrée / sortie standard : `print_string`, `print_int`, `print_float`, `print_newline, print_endline, read_int, read_float, read_line`.

Gestion de fichiers : types `in_channel, out_channel`, fonctions `open_in, open_out, close_in, close_out, input_line, output_string`, exception `End_of_file`.



## Partie D : Déclaration de types

### I. En OCaml

#### 1. Type somme

Syntaxe, constructeurs.

Filtrages sur un type somme.

Polymorphisme.

Type somme existant : `'a option`.

#### 2. Type produit

Syntaxe, champs mutables ou non.

Accès et modification de la valeur d'un champ.

Polymorphisme.

Les références sont définies ainsi :`type 'a ref = {mutable contents : 'a}`.

#### 3. Types récursifs

Type somme récursif (exemple : redéfinition du type `'a list`).

Type produit récursif (exemple : arborescence de fichiers).

Types mutuellement récursifs.

### 2. En C

#### 1. Énumérations

Syntaxe : `enum, typedef`.

#### 2. Structures

Syntaxe : `struct, typedef`.

Accès à un champ avec `.`, ou `->` s'il s'agit d'un pointeur vers la structure.

Types structurés récursifs.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
