(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Implémentation d'une pile avec le module Stack *)

(* --------------------------------------------------------- *)

type 'a pile = 'a Stack.t

let creer () =
    Stack.create ()

let est_vide p =
    Stack.is_empty p

let empiler elt p =
    Stack.push elt p

let depiler p =
    assert(not (est_vide p)) ;
    Stack.pop p
