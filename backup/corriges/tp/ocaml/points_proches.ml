(* CORRIGÉ PARTIEL DU TP : DISTANCE MINIMALE DANS UN NUAGE DE POINTS OCAML *)
(* Par J. BENOUWT et E. DÉTREZ *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Étude du problème *)

type point = {x : float; y : float}

let distance p q = sqrt ((q.x -. p.x)**2.0 +. (q.y -. p.y)**2.0)

(* points de tests *)
let pts0 = [|{x = 10.3 ; y = 5.4}; {x =  1.2 ; y = 2.5}; {x =  3.4 ; y = 2.7}; {x = 10.7 ; y = 2.4}; 
             {x =  5.7 ; y = 1.1}; {x =  0.9 ; y = 5.7}; {x =  6.4 ; y = 7.8}; {x =  6.6 ; y = 4.1}; 
             {x = 11.3 ; y = 6.8}; {x =  8.7 ; y = 2.9}; {x =  5.6 ; y = 6.2}; {x =  9.1 ; y = 5.0}; 
             {x =  2.0 ; y = 8.9}; {x =  7.8 ; y = 2.2}; {x =  9.1 ; y = 0.1}; {x =  1.8 ; y = 5.0}; 
             {x =  3.7 ; y = 1.8}; {x =  7.5 ; y = 7.1}; {x = 10.4 ; y = 7.4}; {x =  4.1 ; y = 8.3}|]

type triplet = {mutable point1 : point; mutable point2 : point; mutable dist : float}

let best t1 t2 =
    if t1.dist < t2.dist then
        t1
    else
        t2            

let points_proches_v1 pts =
    let p1 = ref {x = 0.0; y = 0.0} in
    let p2 = ref {x = 0.0; y = 0.0} in
    let dist_min = ref max_float in
    let n = Array.length pts in
    for i = 0 to n - 2 do
        for j = i + 1 to n - 1 do
            let nouvelle_distance = distance pts.(i) pts.(j) in
            if nouvelle_distance < !dist_min then begin
                p1 := pts.(i);
                p2 := pts.(j);
                dist_min := nouvelle_distance
            end
        done
    done ;
    {point1 = !p1; point2 = !p2; dist = !dist_min}

(* On fait un calcul pour toute paire d'indices i et j avec 0 <= i < j < n.
   Il y a n(n-1)/2 tels couples. 
   La complexité est donc quadratique. *)


(* --------------------------------------------------------- *)

(* « Diviser pour régner » naïf *)

(* fonction de comparaison pour trier selon les abscisses *)
let compare_x p q  =
    if p.x = q.x then
        0
    else if p.x < q.x then
        -1
    else
        1

let _ = Array.stable_sort compare_x pts0

(* On commence par une fonction qui calcule la distance entre points les plus proche parmi 3 points *)
let pp3 pts =
    let p1 = pts.(0) in
    let p2 = pts.(1) in
    let p3 = pts.(2) in
    let t1 = {point1 = p1; point2 = p2; dist = distance p1 p2} in
    let t2 = {point1 = p2; point2 = p3; dist = distance p2 p3} in
    let t3 = {point1 = p3; point2 = p1; dist = distance p3 p1} in
    best (best t1 t2) t3

let sub tab debut taille =
    Array.init taille (fun i -> tab.(debut + i))

let rec points_proches_v2 pts = match Array.length pts with
    | 0 | 1 -> failwith "Il n'y a pas assez de points."
    | 2 -> {point1 = pts.(0); point2 = pts.(1); dist = distance pts.(0) pts.(1)}
    | 3 -> pp3 pts
    | n ->  let tg = points_proches_v2 (sub pts 0 (n/2)) in
            let td = points_proches_v2 (sub pts (n/2) (n - n/2)) in
            best tg td

(* Si C(n) est le nombre de calculs de distances pour n points 
   on a C(2) = 1, C(3) = 3 et C(n) = C(n/2) + C(n - n/2).
   On conclut par récurrence généralisée : C(n) <= n. *)

(* points_proches_v1 pts0 donne 0.94868...
   points_proches_v2 pts0 donne 1.08166... *)


(* --------------------------------------------------------- *)

(* « Diviser pour régner » correct *)

let bande pts p0 delta =
    let n = Array.length pts in
    (* On cherche l'indice du premier point dans la bande *)
    let i = ref 0 in
    while pts.(!i).x < p0.x -. delta do
        incr i
    done ;
    (* On cherche l'indice du premier point après la bande *)
    let j = ref (!i + 1) in
    while !j < n && pts.(!j).x <= p0.x +. delta do
        incr j
    done ;
    (* On crée la bande *)
    sub pts !i (!j - !i)

let compare_y p q  =
    if p.y = q.y then
        0
    else if p.y < q.y then
        -1
    else
        1

let points_proches_bande bde delta =
    let n = Array.length bde in
    let dist_min = ref max_float in
    let p1 = ref {x = 0.0; y = 0.0} in
    let p2 = ref {x = 0.0; y = 0.0} in
    for i = 0 to n - 2 do
        let j = ref (i + 1) in
        while !j < n && bde.(!j).y < bde.(i).y +. delta do
            let nouvelle_distance = distance bde.(i) bde.(!j) in
            if nouvelle_distance < !dist_min then begin
                p1 := bde.(i) ;
                p2 := bde.(!j) ;
                dist_min := nouvelle_distance
            end ;
            incr j
        done
    done ;
    {point1 = !p1; point2 = !p2; dist = !dist_min}

let rec points_proches_v3 pts = match Array.length pts with
    | 0 | 1 -> failwith "Il n'y a pas assez de points"
    | 2 -> {point1 = pts.(0); point2 = pts.(1); dist = distance pts.(0) pts.(1)}
    | 3 -> pp3 pts
    | n ->  let tg = points_proches_v3 (sub pts 0 (n/2)) in
            let td = points_proches_v3 (sub pts (n/2) (n - n/2)) in
            let t = best tg td in
            let bde = bande pts pts.(n/2) t.dist in
            Array.stable_sort compare_y bde ;
            best t (points_proches_bande bde t.dist)


(* --------------------------------------------------------- *)

(* « Diviser pour régner » amélioré *)

(* 1. nombre de calculs de distances *)

(* Il y a au plus 8 carrés dans lesquels il y a au plus un point 
   pour une ordonnée majorée par y + delta.
   
   On calcule au plus 8n distances dans la bande d'où l'inégalité.
   
   On applique ensuite la formule vue en cours pour obtenir le résultat. *)


(* 2. La complexité cachée *)

(* On recopie dans les deux sous-tableaux donc n copies.
   Pour créer la bande on fait n comparaisons et au plus n copies.
   Pour le tri, au plus 4nlog2(n) comparaisons et copies.
   Ainsi Cc(n) = Cc(m) + Cc(n-m) + O(n log2(n))
               
   On applique ensuite la formule vue en cours pour obtenir le résultat. *)


(* 3. Retour à la quasi-linéarité *)

(* Comme on ne veut plus trier la bande, on doit l'extraire de l'ensemble 
   mais alors on ne sait plus calculer le nombre d'éléments facilement. 
   Je choisis d'extraire dans une liste puis de convertir *)
let bande_sans_tri pts p0 delta =
    (* fonction qui récupère les points dont l'abscisse les place dans la bande *)
    let rec liste_points_dans_bande i = 
        if i = Array.length pts then
            [] (* tous les points ont été regardés *)
        else if pts.(i).x < p0.x -. delta || pts.(i).x > p0.x +. delta then
            liste_points_dans_bande (i+1) (* le i-ème point n'est pas dans la bande *)
        else
            pts.(i) :: liste_points_dans_bande (i+1) (* le i-ème point est dans la bande *)
    in
    (* fonction qui convertit une liste en tableau *)
    let rec array_of_list lst =
        let tab = Array.make (List.length lst) {x = 0.0; y = 0.0} in
        let rec remplit lst i = match lst with
            | [] -> tab
            | t::q -> tab.(i) <- t ; remplit q (i+1) in
        remplit lst 0
    in
    array_of_list (liste_points_dans_bande 0)
    

(* On a besoin d'écrire une fusion *)
let fusion t1 t2 =
    let n1 = Array.length t1 in
    let n2 = Array.length t2 in
    let t = Array.make (n1 + n2) {x = 0.0; y = 0.0} in
    let i1 = ref 0 in
    let i2 = ref 0 in
    for i = 0 to n1 + n2 - 1 do
        match (n1 - !i1), (n2 - !i2) with
            | 0, _ -> t.(i) <- t2.(!i2); incr i2 (* on est arrivés au bout de t1 *)
            | _, 0 -> t.(i) <- t1.(!i1); incr i1 (* on est arrivés au bout de t2 *)
            | _ when t1.(!i1).y < t2.(!i2).y -> t.(i) <- t1.(!i1); incr i1 (* l'élément courant de t1 est plus petit que l'élément courant de t2 *)
            | _ -> t.(i) <- t2.(!i2); incr i2 (* l'élément courant de t2 est plus petit que l'élément courant de t1 *)
    done ;
    t

let rec points_proches_v4 pts =
    let rec aux pts = match Array.length pts with
        | 0 -> failwith "Il n'y a pas assez de points"
        | 1 -> {point1 = {x = 0.0; y = 0.0}; point2 = {x = 0.0; y = 0.0}; dist = max_float}, [|pts.(0)|]
        | 2 -> {point1 = pts.(0); point2 = pts.(1); dist = distance pts.(0) pts.(1)}, (fusion [|pts.(0)|] [|pts.(1)|])
        | n ->  let tg, ptsg = aux (sub pts 0 (n/2)) in
                let td, ptsd = aux (sub pts (n/2) (n - n/2)) in
                let t = best tg td in
                let pts_fusion = fusion ptsg ptsd in
                let bde = bande_sans_tri pts_fusion pts.(n/2) t.dist in
                best t (points_proches_bande bde t.dist), pts_fusion
    in fst (aux pts)
