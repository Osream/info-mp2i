(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Interface d'une file *)

(* --------------------------------------------------------- *)

(*
Représente une file d'éléments
polymorphe, homogène, mutable
*)
type 'a file

(*
Entrée : aucune.
Précondition : aucune.
Sortie : une file.
Postcondition : la file renvoyée est vide.
*)
val creer : unit -> 'a file

(*
Entrée : une file.
Précondition : aucune.
Sortie : un booléen.
Postcondition : renvoie true si la file est vide, false sinon.
*)
val est_vide : 'a file -> bool

(*
Entrée : une file et un élément du même type que le contenu de la file.
Précondition : aucune.
Sortie : aucune.
Postcondition : la file contient les mêmes éléments qu'avant dans le même ordre, plus le nouvel élément au bout (effet de bord).
*)
val enfiler : 'a -> 'a file -> unit

(*
Entrée : une file.
Précondition : la file n'est pas vide. Lève une Assert_failure en cas de non respect.
Sortie : un élément du même type que le contenu de la file.
Postcondition : l'élément renvoyé est celui en tête de la file (premier ajouté, principe FIFO) et la file ne contient plus cet élément (effet de bord).
*)
val defiler : 'a file -> 'a
