type ('i, 'f) ab_strict =
	| Feuille of 'f
	| Noeud of 'i * ('i, 'f) ab_strict * ('i, 'f) ab_strict

let rec hauteur_s arbre = match arbre with
    | Feuille _ -> 0
    | Noeud (_, g, d) -> 1 + max (hauteur_s g) (hauteur_s d)

let rec taille_s arbre = 
  match arbre with
    | Feuille _ -> 1
    | Noeud (_, g, d) -> 1 + taille_s g + taille_s d

let rec nb_feuilles_s arbre =
  match arbre with
    | Feuille _ -> 1
    | Noeud (_, g, d) -> nb_feuilles_s g + nb_feuilles_s d

let rec nb_noeuds_internes_s arbre = 
  match arbre with
    | Feuille _ -> 0
    | Noeud (_, g, d) -> 1 + nb_noeuds_internes_s g + nb_noeuds_internes_s d

let rec appartient_s arbre elt = 
  match arbre with
    | Feuille f -> f = elt
    | Noeud (e, g, d) -> elt = e || appartient_s g elt || appartient_s d elt 

type 'e ab =
	| Vide
	| N of 'e * 'e ab * 'e ab

let rec taille_ns arbre = match arbre with
	| Vide -> 0
	| N (_, g, d) -> 1 + taille_ns g + taille_ns d

let rec hauteur_ns arbre = match arbre with
	| Vide -> -1
	| N (_, g, d) -> 1 + max (hauteur_ns g) (hauteur_ns d)

let rec nb_feuilles_ns arbre = match arbre with
	| Vide -> 0
  | N (_, Vide, Vide) -> 1
	| N (_, g, d) -> nb_feuilles_ns g + nb_feuilles_ns d

let rec nb_noeuds_internes_ns arbre = match arbre with
	| Vide -> 0
  | N (_, Vide, Vide) -> 0
	| N (_, g, d) -> 1 + nb_noeuds_internes_ns g + nb_noeuds_internes_ns d

let rec appartient_ns arbre elt = match arbre with
	| Vide -> false
	| N (e, g, d) -> e = elt || appartient_ns g elt || appartient_ns d elt

let rec est_strict ab_ns = 
  match ab_ns with
    | Vide -> false
    | N (_, Vide, Vide) -> true
    | N (_, g, d) -> est_strict g && est_strict d

let rec egaux_strict_et_non_strict ab_s ab_ns = 
  est_strict ab_ns && match ab_s, ab_ns with
    | Feuille f, N(e, Vide, Vide) -> f = e
    | Noeud (e1, g1, d1), N (e2, g2, d2) -> e1 = e2 && egaux_strict_et_non_strict g1 g2 && egaux_strict_et_non_strict d1 d2
    | _ -> false

(*let _ =*)
(*  let strict =*)
(*    Noeud(0,*)
(*      Noeud(4,*)
(*          Feuille 11,*)
(*          Feuille 12),*)
(*      Noeud(2,*)
(*          Noeud(20,*)
(*              Feuille 36,*)
(*              Feuille 37),*)
(*          Feuille 22)) in*)
(*  let non_strict =*)
(*	  N(0,*)
(*        N(4,*)
(*            N(11, Vide, Vide),*)
(*            N(12, Vide, Vide)),*)
(*        N(2,*)
(*            N(20, Vide, Vide),*)
(*            N(22, Vide, Vide)))*)
(**)
(*  in *)
(**)
