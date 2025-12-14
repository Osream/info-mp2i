(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Implémentation d'une file avec un tableau *)

(* --------------------------------------------------------- *)

let tAILLE_MAX = 50
let valeur_pour_la_creation = 0

type 'a file = {mutable debut : int; mutable fin : int; elts : 'a array}

let creer () =
    {debut = 0; fin = 0; elts = Array.make tAILLE_MAX valeur_pour_la_creation}

let est_vide f =
    f.debut = f.fin

let est_pleine f =
    (f.fin + 1) mod tAILLE_MAX = f.debut

let enfiler elt f =
    assert (not (est_pleine f)) ;
    f.elts.(f.fin) <- elt ;
    f.fin <- (f.fin + 1) mod tAILLE_MAX

let defiler f =
    assert (not (est_vide f)) ;
    let tete = f.elts.(f.debut) in
    f.debut <- (f.debut + 1) mod tAILLE_MAX ;
    tete