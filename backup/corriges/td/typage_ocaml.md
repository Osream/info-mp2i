# TD : Bases d'OCaml

## Exercice 1

1. | code |  x   |  y   |  z   |
	| :--: | :--: | :--: | :--: |
	|  1   |  10  |  12  |      |
	|  2   |  2   |      |  5   |
	|  3   |  2   |  1   |      |
	|  4   |  4   |  10  |      |
	|  5   | 230  | 330  |      |
	|  6   |  1   |  12  |      |
	
2. 1. Impossible d'additionner une chaîne de caractères et un entier.
   2. Impossible de multiplier un entier avec un flottant.
   3. `f : int -> int -> int, u : int`.
   4. `g : int -> int, f : ('a -> int) -> 'a -> int, u : int`.
   5. Les deux expressions de la conditionnelle ont des types différents, ce qui est impossible.
   6. `x : int, y : int, z : int`.
   7. La condition de l'instruction conditionnelle n'est pas de type `bool`, ce qui est impossible.
   8. `y` est définie localement, impossible donc de l'utiliser dans la définition de `z`.

## Exercice 2

Pour vérifier vos réponses, vous pouvez entrer les filtrages dans le toplevel, il vous indiquera directement les avertissements s'il y en a (non exhaustivité et clauses inutilisées).

## Exercice 3

1. | code |      type de la fonction       |        version curryfiée        |
    | :--: | :----------------------------: | :-----------------------------: |
    |  1   |       `int * int -> int`       | `let f a b = (a + b) * (a - b)` |
    |  2   | `('a -> int) * 'a * 'a -> int` |    `let f a b c = a b + a c`    |
    |  3   |       `int * int -> int`       |     `let f a b = match ...`     |
    |  4   |    `float * float -> float`    |     `let f a b = match ...`     |
    |  5   |   `int * int * int -> bool`    |   `let f a b c = let q = ...`   |
    |  6   |        `'a * 'b -> 'a`         |         `let f a _ = a`         |

2. |       fonction curryfiée       |                   type                    |
    | :----------------------------: | :---------------------------------------: |
    |   `let f a x y = a (x + y)`    |     `(int -> 'a) -> int -> int -> 'a`     |
    |   `let g a b x = a x + b x`    | `('a -> int) -> ('a -> int) -> 'a -> int` |
    | `let h a b = fun x -> a (b x)` | `('a -> 'b) -> ('c -> 'a) -> ('c -> 'b)`  |

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
