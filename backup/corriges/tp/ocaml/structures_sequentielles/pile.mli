(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Interface d'une pile *)

(* --------------------------------------------------------- *)

(*
Représente une pile d'éléments
polymorphe, homogène, mutable
*)
type 'a pile

(*
Entrée : aucune.
Précondition : aucune.
Sortie : une pile.
Postcondition : la pile renvoyée est vide.
*)
val creer : unit -> 'a pile

(*
Entrée : une pile.
Précondition : aucune.
Sortie : un booléen.
Postcondition : renvoie true si la pile est vide, false sinon.
*)
val est_vide : 'a pile -> bool

(*
Entrée : une pile et un élément du même type que le contenu de la pile.
Précondition : aucune.
Sortie : aucune.
Postcondition : la pile contient les mêmes éléments qu'avant dans le même ordre, plus le nouvel élément au sommet (effet de bord).
*)
val empiler : 'a -> 'a pile -> unit

(*
Entrée : une pile.
Précondition : la pile n'est pas vide. Lève une Assert_failure en cas de non respect.
Sortie : un élément du même type que le contenu de la pile.
Postcondition : l'élément renvoyé est celui au sommet de la pile (dernier ajouté, principe LIFO) et la pile ne contient plus cet élément (effet de bord).
*)
val depiler : 'a pile -> 'a