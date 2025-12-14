(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Implémentation d'une file avec deux piles *)

(* --------------------------------------------------------- *)

type 'a file = {
	entree: 'a Pile.pile ;
	sortie: 'a Pile.pile
}

let creer () =
    {entree = Pile.creer () ; sortie = Pile.creer ()}

let est_vide f =
    Pile.est_vide f.entree && Pile.est_vide f.sortie
   
let enfiler elt f =
    Pile.empiler elt f.entree
    
let transvase_pile_vers_pile p1 p2 =
    while not (Pile.est_vide p1) do
        Pile.empiler (Pile.depiler p1) p2
    done

let defiler f =
    assert (not (est_vide f)) ;
    if Pile.est_vide f.sortie then
        transvase_pile_vers_pile f.entree f.sortie ;
    Pile.depiler f.sortie