(*
CORRIGÉ PARTIEL DU TP : TRIS EFFICACES (PARTIE EN OCAML)
Par J. BENOUWT
Licence CC BY-NC-SA
*)


(* --------------------------------------------------------- *)


(* Tri fusion d'une liste *)


let rec diviser l = match l with
    | x::y::xs ->   let l1, l2 = diviser xs in
                    x::l1, y::l2
    | _ -> l, []


let rec fusion l1 l2 = match l1, l2 with
    | [], _ -> l2
    | _, [] -> l1
    | x::xs, y::ys when x <= y -> x :: fusion xs l2
    | _, y::ys -> y :: fusion l1 ys


let rec tri_fusion l = match l with
    | [] | [_] -> l
    | _ ->  let l1, l2 = diviser l in
            fusion (tri_fusion l1) (tri_fusion l2)


(*  
La correction des 3 fonctions se montre par récurrence, comme elles sont récursives.

Concernant la complexité :

D(n) = complexité de la fonction diviser l avec l de taille n
D(0) = D(1) = O(1)
D(n) = D(n-2) + O(1) pour n > 1
On en déduit : D(n) = O(n/2) = O(n)

F(n1+n2) = complexité de la fusion de deux listes l1 et l2 de taille n1 et n2
F(n1+0) = F(0+n2) = O(1)
F(n1+n2) = F(n1+n2-1) + O(1) si n1 > 0 et n2 > 0
On en déduit min(n1,n2) ≤ F(n1+n2) ≤ n1+n2, donc F(n1+n2) = O(n1+n2).

On note C(n) la complexité du tri fusion d'une liste de n éléments.
C(2^k)  = 2 × C(2^(k-1)) + D(2^k) + F(2^(k-1) + 2^(k-1))
        = 2 × C(2^(k-1)) + O(2^k)
et C(0) = C(1) = 0
Donc C(2^k) = somme de i = 0 jusque k de (2^i × O(2^(k-i)))
            = somme de i = 0 jusque k de O(2^k)
            = O(k × 2^k)

On en déduit alors le cas général : le tri fusion est quasi-linéaire.
*)



(* --------------------------------------------------------- *)


(* Tri rapide d'une liste *)


let rec partition l pivot = match l with
    | [] -> [], []
    | x::xs ->  let inf, sup = partition xs pivot in
                if x <= pivot then
                    x::inf, sup
                else
                    inf, x::sup

let rec tri_rapide l = match l with
    | [] | [_] -> l
    | x::xs ->  let l1, l2 = partition xs x in
                tri_rapide l1 @ (x :: tri_rapide l2)


(*
Correction par récurrence toujours.
    
Complexité :

P(n) = complexité de la fonction partition sur une liste de taille n
P(0) = O(1)
P(n) = P(n-1) + O(1)
On en déduit P(n) = O(n).

On note C(n) la complexité du tri rapide d'une liste de n éléments.
Encadrement pour la relation de récurrence :
C(2^(k-1)) + C(2^(k-1) - 1) + P(2^k - 1) ≤ C(2^k) ≤ C(2^k - 1) + C(0) + P(2^k - 1)
(meilleur cas = la partition donne deux listes de taille presqu'égales
 pire cas = la partition donne une liste de taille 0 et l'autre contient donc tout sauf le pivot)

On en déduit :
- pire cas : C(n) = O(n^2)
- meilleur cas : C(n) = Ω(n log n)
*)



(* --------------------------------------------------------- *)


(* Tri fusion d'un tableau *)


let sous_tableau tab debut fin =
    Array.init (fin - debut + 1) (fun i -> tab.(debut + i))


let fusion_tableaux t1 t2 =
    let taille = Array.length t1 + Array.length t2 in
    let res = Array.make taille t1.(0) in
    let i_t1 = ref 0 in
    let i_t2 = ref 0 in
    (*
    Variant : taille - (!i_t1 + !i_t2)
    Inv(!i_t1, !i_t2) : res de 0 à !i_t1 + !i_t2 - 1 est trié
                        et contient les !i_t1 premiers éléments de t1
                        et les !i_t2 premiers éléments de t2 *)
    while !i_t1 + !i_t2 <> taille do
        if !i_t1 = Array.length t1 then
            begin res.(!i_t1 + !i_t2) <- t2.(!i_t2) ; incr i_t2 end
        else if !i_t2 = Array.length t2 then
            begin res.(!i_t1 + !i_t2) <- t1.(!i_t1) ; incr i_t1 end
        else if t1.(!i_t1) <= t2.(!i_t2) then
            begin res.(!i_t1 + !i_t2) <- t1.(!i_t1) ; incr i_t1 end
        else
            begin res.(!i_t1 + !i_t2) <- t2.(!i_t2) ; incr i_t2 end
    done ;
    res


let rec tri_fusion_tableau t = match Array.length t with
    | 0 | 1 -> t
    | n ->  let gauche = sous_tableau t 0 (n/2-1) in
            let droite = sous_tableau t (n/2) (n-1) in
            fusion_tableaux (tri_fusion_tableau gauche) (tri_fusion_tableau droite)


(* La complexité est la même que le tri fusion d'une 'a list *)
