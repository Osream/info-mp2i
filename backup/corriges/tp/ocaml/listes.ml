(* CORRIGÉ DU TP : LISTES OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Manipulations de listes *)

let head l = match l with
    | [] -> failwith "une liste vide n'a pas de tête !"
    | t::q -> t

let tail l = match l with
    | [] -> failwith "une liste vide n'a pas de queue !"
    | t::q -> q

let rec longueur l = match l with
    | [] -> 0
    | t::q -> 1 + longueur q

let rec somme l = match l with
    | []-> 0
    | t::q -> t + somme q

let moyenne l =
    let rec somme_float l = match l with
        | []-> 0.
        | t::q -> t +. somme_float q
    in
    somme_float l /. float_of_int (longueur l)

let rec appartient valeur l = match l with
    | [] -> false
    | t::q -> valeur = t || appartient valeur q

let rec croissant l = match l with
    | [] | [_] -> true
    | t1::t2::q -> t1 <= t2 && croissant (t2::q)

let rec trois_egaux l = match l with
    | [] | [_] | [_; _] -> false
    | t1::t2::t3::q -> (t1 = t2 && t2 = t3) || trois_egaux (t2::t3::q)

let rec insere element indice l = match l, indice with
    | _, 0 -> element::l
    | [], _ -> failwith "l'indice demandé pour l'insertion est invalide"
    | t::q, _ -> t::insere element (indice - 1) q

let rec concat l1 l2 = match l1 with
    | [] -> l2
    | t::q -> t::concat q l2

let rec miroir l = match l with
    | [] -> []
    | t::q -> miroir q @ [t]

let rec repete l n = match n with
    | 0 -> []
    | _ -> l @ repete l (n - 1)

let rec exists prop l = match l with (* détermine s'il existe au moins un élément de la liste qui satisfait la propriété *)
    | [] -> false
    | t::q -> prop t || exists prop q

let rec for_all prop l = match l with (* détermine si tous les éléments de la liste satisfont la propriété *)
    | [] -> true
    | t::q -> prop t && for_all prop q

let rec filter prop l = match l with (* crée une nouvelle liste ne contenant que les éléments de la liste qui satisfont la propriété *)
    | [] -> []
    | t::q when prop t -> t::filter prop q
    | _::q -> filter prop q

let rec map f l = match l with (* applique une fonction à tous les éléments d'une liste *)
    | [] -> []
    | t::q -> f t::map f q


(* --------------------------------------------------------- *)

(* Polynômes *)

type polynome = (int * int) list

let rec validation (p : polynome) = match p with
    | [] -> true
    | [(a, _)] -> a <> 0
    | (a1, n1)::(a2, n2)::ans -> a1 <> 0 && n1 > n2 && validation ((a2, n2)::ans)

let degre (p : polynome) = match p with
    | [] -> -1
    | (_, n)::_ -> n

let rec coefficient k (p : polynome) = match p with
    | [] -> 0
    | (a, n)::_ when n = k -> a
    | _::ans -> coefficient k ans

let rec expo_rapide x n = match n with (* je récupère la fonction d'exponentiation rapide du TP précédent *)
	| 0 -> 1
	| _ -> expo_rapide (x * x) (n / 2) * (if n mod 2 = 0 then 1 else x)

let rec evaluation (p : polynome) x = match p with
    | [] -> 0
    | (a, n)::ans -> a * (expo_rapide x n) + evaluation ans x

let rec composition k (p : polynome) : polynome = match p with
    | [] -> []
    | (a, n)::ans -> (a, k*n)::composition k ans

let rec dilatation b (p : polynome) : polynome = match p with
    | [] -> []
    | (a, n)::ans -> (a * (expo_rapide b n), n)::dilatation b ans

let rec plus (p1 : polynome) (p2 : polynome) =   match p1, p2 with
    | [], _ -> p2
    | _, [] -> p1
    | (a1, n1)::ans1, (a2, n2)::ans2 when n1 > n2 -> (a1 ,n1)::plus ans1 p2
    | (a1, n1)::ans1, (a2, n2)::ans2 when n1 < n2 -> (a2, n2)::plus p1 ans2
    | (a1, _)::ans1, (a2, _)::ans2 when a1 + a2 = 0 -> plus ans1 ans2 (* si le coefficient est 0 il ne doit plus figurer dans le polynome *)
    | (a1, n1)::ans1, (a2, _)::ans2 -> (a1 + a2, n1)::plus ans1 ans2
    
let ( +++ ) = plus

let rec fois (p1 : polynome) (p2 : polynome) =
    let rec fois_monome (a, n) p = match p with (* multiplie un monôme par un polynome *)
        | [] -> []
        | (a2, n2)::ans2 -> (a * a2, n + n2)::fois_monome (a, n) ans2 in
    match p1 with
        | [] -> []
        | monome::reste -> fois_monome monome p2 +++ fois reste p2 (* on multiplie chaque monome de p1 par p2 et on fait la somme des résultats *)
  
let ( *** ) = fois

let rec derivee (p : polynome) : polynome = match p with
    | [] -> []
    | [_, 0] -> []
    | (a, n)::ans -> (a * n, n - 1)::derivee ans

let rec tch n = match n with
    | 0 -> [1, 0]
    | 1 -> [1, 1]
    | _ -> ([2 , 1] *** (tch (n - 1))) +++ ([-1, 0] *** (tch (n - 2)))

(* La partie suivante était plus difficile, pas d'inquiétude si vous n'y êtes pas parvenus. *)

let rec division pA pB = match pA, pB with
    | _ , [] -> failwith "le polynome diviseur ne doit pas être vide"
    | [], _ -> [], []
    | (_, p)::_, (_, q)::_ when p < q -> [], pA (* Si p < q alors Q = polynome vide et R = A *)
    | (a, p)::_, (_, q)::_ -> (* Sinon, *)
            let a1 = pA +++ ([-a, p-q] *** pB ) in (* on calcule A1 *)
            let q1, r = division a1 pB in (* on calcule récursivement Q1 et R *)
            [a, p-q] +++ q1, r (* on obtient notre Q et R finaux *)

let ( /// ) = division

let rec cycloto n = match n with
  | 1 -> [(1, 1); (-1, 0)] (* polynome X - 1 *)
  | _ ->    let rec prod k p = match k with (* Au départ p est le polynome X^n - 1. *)
                | _ when k = n -> p
                | _ when n mod k = 0 -> (* Si k|n *)
                        let q, _ = p /// (cycloto k) in (* on récupère le quotient de la division de p par Phi_k *)
                        prod (k + 1) q
                | _ -> prod (k + 1) p in (* k ne divise pas n, on passe juste au suivant *)
            prod 1 [(1, n); (-1, 0)]

(* en remarquant que :
   - k|n n'est possible que si k <= n/2
   - [(1, n); (-1, 0)] avec n = 1 est le polynome X - 1
   on peut écrire une version optimisée de cycloto *)
let rec cycloto_v2 n =
    let rec prod k p =
        if k > n / 2 then
            p
        else if n mod k = 0 then
            let q, _ = p /// (cycloto_v2 k) in
            prod (k + 1) q
        else
            prod (k + 1) p in
    prod 1 [(1, n); (-1, 0)];;

let dilatation_v2 b = List.map ( fun (a , n) -> (a * (expo_rapide b n), n) )
