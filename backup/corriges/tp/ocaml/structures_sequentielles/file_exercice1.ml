(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Implémentation d'une file avec pointeurs
   vers le premier et dernier maillon d'une liste chaînée *)

(* --------------------------------------------------------- *)

type 'a maillon = Vide | Cons of {valeur: 'a; mutable suivant: 'a maillon}

type 'a file = {
	mutable premier: 'a maillon ;
	mutable dernier: 'a maillon
}

let creer () =
    {premier = Vide ; dernier = Vide}

let est_vide f =
    f.premier = Vide && f.dernier = Vide
    
let enfiler elt f =
    let nouveau_maillon = Cons {valeur = elt ; suivant = Vide} in
    match f.dernier with
        (* la file était vide avant :
           le premier et le dernier maillon sont maintenant le même *)
        | Vide ->   f.premier <- nouveau_maillon ;
                    f.dernier <- nouveau_maillon
        (* m est le dernier maillon ajouté donc m.suivant était vide avant,
           maintenant il pointe vers le nouveau maillon *)
        | Cons m -> m.suivant <- nouveau_maillon ;
                    f.dernier <- nouveau_maillon
    
let defiler f = match f.premier with
    | Vide -> assert false ;
    | Cons m -> let tete = m.valeur in
                (* le premier élément de la file devient le suivant du premier,
                   cad le deuxième élément de la file *)
                f.premier <- m.suivant ;
                (* si on est arrivé au bout,
                   c'est qu'on vient de défiler le tout dernier élément,
                   donc le dernier maillon est lui aussi vide *)
                if f.premier = Vide then
                    f.dernier <- Vide ;
                tete