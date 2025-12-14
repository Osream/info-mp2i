(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Implémentation d'une pile avec un tableau *)

(* --------------------------------------------------------- *)

let tAILLE_MAX = 50
let valeur_pour_la_creation = 0

type 'a pile = {mutable fin : int; elts : 'a array}

let creer () =
    {fin = 0; elts = Array.make tAILLE_MAX valeur_pour_la_creation}

let est_vide p =
    p.fin = 0

let est_pleine p =
    p.fin = tAILLE_MAX

let empiler elt p =
    assert (not (est_pleine p)) ;
    p.elts.(p.fin) <- elt ;
    p.fin <- p.fin + 1

let depiler p =
    assert (not (est_vide p)) ;
    p.fin <- p.fin - 1 ;
    p.elts.(p.fin)