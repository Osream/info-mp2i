(* CORRIGÉ PARTIEL DU TP : COMPTER LES BRIQUES *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Rangées possibles *)

let rec nb_rangees_non_efficace n = match n with
    (* cas de base *)
    | 1 -> 0
    | 2 | 3 -> 1
    (* cas récursif *)
    | _ -> nb_rangees_non_efficace (n-2) + nb_rangees_non_efficace (n-3)


let nb_rangees_top_down n =
    (* création de la structure de données *)
    let memo = Array.make (n+1) (-1) in
    (* fonction auxiliaire récursive avec mémoïsation *)
    let rec remplir i =
        (* s'il n'a pas déjà été fait, on fait et on stocke le calcul *)
        begin if memo.(i) = -1 then match i with
            (* cas de base *)
            | 1 -> memo.(i) <- 0
            | 2 | 3 -> memo.(i) <- 1
            (* cas récursif *)
            | _ -> memo.(i) <- remplir (i-2) + remplir (i-3)
        end ;
        (* on renvoie le résultat stocké *)
        memo.(i)
    (* on renvoie finalement la valeur qui nous intéresse *)
    in remplir n


let nb_rangees_bottom_up n =
    (* création de la structure de données *)
    let memo = Array.make (n+1) (-1) in
    (* initialisation des cas de base *)
    memo.(1) <- 0 ;
    memo.(2) <- 1 ;
    memo.(3) <- 1 ;
    (* boucle pour remplir les cas récursifs *)
    for i = 4 to n do
        memo.(i) <- memo.(i-2) + memo.(i-3)
    done ;
    (* on renvoie finalement la valeur qui nous intéresse *)
    memo.(n)


let nb_rangees n =
    if n = 1 then
        0
    else if n = 2 then
        1
    else begin
        (*  i = taille de la rangée considérée 
            res_i = nombre de rangées de taille i
            res_i_moins_1 = nombre de rangées de taille i-1
            res_i_moins_2 = nombre de rangées de taille i-2 *)
        let i = ref 3 in
        let res_i = ref 1 in
        let res_i_moins_1 = ref 1 in
        let res_i_moins_2 = ref 0 in
        while !i <> n do
            let nouveau_res_i = !res_i_moins_1 + !res_i_moins_2 in
            res_i_moins_2 := !res_i_moins_1 ;
            res_i_moins_1 := !res_i ;
            res_i := nouveau_res_i ;
            incr i
        done ;
        !res_i
        end


let nb_rangees_v2 n = (* même chose que 'nb_rangees' mais en récursif terminal *)
    let rec aux i res_i_moins_2 res_i_moins_1 res_i =
        if i = n then
            res_i
        else
            aux (i+1) res_i_moins_1 res_i (res_i_moins_2 + res_i_moins_1)
    in if n = 1 then
        0
    else if n = 2 then
        1
    else
        aux 3 0 1 1


let decaler t r =
    (* ajoute une brique de taille t à droite de la rangée représentée par l'entier r *)
    (r+1) lsl t

let plus2 = decaler 2
let plus3 = decaler 3


let ajout_brique t l =
    (* ajoute une brique de taille t à droite de toutes les rangées de la liste l *)
    if t = 2 then
        List.map plus2 l
    else
        List.map plus3 l


let rangees n =
    (* Même principe que la fonction 'nb_rangees_v2' mais 
       on conserve maintenant les listes de rangées et non leur nombre.
       On pouvait bien sûr aussi adapter nb_rangees pour écrire une fonction impérative. *)
    let rec aux i res_i_moins_2 res_i_moins_1 res_i =
        if i = n then
            res_i
        else
          (* pour construire une rangée de taille i + 1 :
             - soit on ajoute une brique de taille 3 à une rangée de taille i-2
             - soit on ajoute une brique de taille 2 à une rangée de taille i-1
          *)
            aux (i+1) res_i_moins_1 res_i ((ajout_brique 3 res_i_moins_2) @ (ajout_brique 2 res_i_moins_1))
    in if n = 1 then
        []
    else if n = 2 then
        [0]
    else
        aux 3 [] [0] [0]



(* --------------------------------------------------------- *)

(* Nombre de murs *)

let compatibles rangee1 rangee2 =
    rangee1 land rangee2 = 0


let nb_murs_non_efficace larg haut =
    let rg = rangees larg in
    (* la fonction aux compte le nombre de murs de hauteur 'h'
       qu'on peut construire au dessus de la rangée 'base' *)
    let rec aux h base =
        (* la fonction parcourt toutes les rangées de largeur 'larg' possibles
           et si on en trouve une compatible avec la base actuelle,
           on continue de construire au dessus *)
        let rec parcours rangees_possibles = match rangees_possibles with
                | [] -> 0
                | t::q ->   if compatibles base t then
                                aux (h-1) t + parcours q
                            else
                                parcours q
        in if h = 0 then
            1
        else
            parcours rg
    in aux haut 0



(* --------------------------------------------------------- *)

(* Tables de hachage *)


let taille = 5003

let hash h r =
    r/4 + h*178543 (* arbitraire *)


let rec mem h r liste = match liste with
    | [] -> false
    | (x, y, _)::reste -> (x = h && y = r) || mem h r reste


let rec assoc h r liste = match liste with
    | [] -> failwith "l'élément n'est pas dans la table"
    | (x, y, nb)::reste ->  if x = h && y = r then
                                nb
                            else
                                assoc h r reste


let cree_table_h () =
    Array.make taille []

let existe h r table_h =
    let i = (hash h r) mod taille in
    mem h r table_h.(i)

let valeur h r table_h =
    let i = (hash h r) mod taille in
    assoc h r table_h.(i)

let ajoute h r nb table_h =
    if not (existe h r table_h) then
        let i = (hash h r) mod taille in
	    table_h.(i) <- (h, r, nb) :: table_h.(i)


let nb_murs larg haut =
   let rg = rangees larg in
   let tableau_associatif = cree_table_h () in
   let rec aux h base =
        if existe h base tableau_associatif then
            valeur h base tableau_associatif
        else begin
            let rec parcours rangees_possibles = match rangees_possibles with
                | [] -> 0
                | t::q ->  if compatibles base t then
                                aux (h-1) t + parcours q
                            else
                            parcours q
            in
            let res = if h = 0 then 1 else parcours rg in
            ajoute h base res tableau_associatif ;
            res
        end           
   in aux haut 0
