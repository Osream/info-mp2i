(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Implémentation d'une file avec le module Queue *)

(* --------------------------------------------------------- *)

type 'a file = 'a Queue.t

let creer () =
    Queue.create ()

let est_vide f =
    Queue.is_empty f

let enfiler elt f =
    Queue.push elt f

let defiler f =
    assert(not (est_vide f)) ;
    Queue.pop f
