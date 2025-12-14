(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Implémentation d'une file avec deux listes chaînées *)

(* --------------------------------------------------------- *)

type 'a file = {mutable sortie : 'a list; mutable entree : 'a list}

let creer () =
    {sortie = []; entree = []}

let est_vide f =
    f.sortie = [] && f.entree = []

let renverse l = 
    (* fonction auxilaire qui renverse l dans l_renversee *)
    let rec aux l l_renversee = match l with
        | [] -> l_renversee
        | t::q -> aux q (t::l_renversee) in
    aux l []

let enfiler elt f =
    f.entree <- elt :: f.entree

let defiler f =
    if f.sortie = [] then begin
        f.sortie <- renverse f.entree ;
        f.entree <- []
    end ;
    match f.sortie with
        | [] -> assert false (* file vide *)
        | t::q -> f.sortie <- q ;
                  t
