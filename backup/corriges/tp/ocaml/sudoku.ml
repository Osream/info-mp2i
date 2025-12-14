(* CORRIGÉ PARTIEL DU TP : SUDOKU *)
(* Par J. BENOUWT et E. DETREZ *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* une case est soit vide soit une valeur entre 1 et 9*)
type case = V | C of int
(* une grille est une matrice de 'case' *)
type grille = case array array

(* quelques exemples de grilles
   (pour indication, ce sont celles de la partie "Pour aller plus loin") *)
let gr0 = [|[|  V; C 6;   V;   V;   V;   V; C 2;   V; C 5|];
            [| C 4;   V;   V; C 9; C 2; C 1;   V;   V;   V|];
            [|   V; C 7;   V;   V;   V; C 8;   V;   V; C 1|];
            [|   V;   V;   V;   V;   V; C 5;   V;   V; C 9|];
            [| C 6; C 4;   V;   V;   V;   V;   V; C 7; C 3|];
            [| C 1;   V;   V; C 4;   V;   V;   V;   V;   V|];
            [| C 3;   V;   V; C 7;   V;   V;   V; C 6;   V|];
            [|   V;   V;   V; C 1; C 4; C 6;   V;   V; C 2|];
            [| C 2;   V; C 6;   V;   V;   V;   V; C 1;   V|]|];;

let gr1 = [|[| C 5;   V;   V; C 2;   V; C 4;   V;   V;   V|];
            [|   V;   V;   V;   V; C 6;   V;   V; C 8;   V|];
            [| C 7;   V;   V; C 5;   V; C 8; C 4; C 3;   V|];
            [| C 1; C 5;   V; C 6;   V;   V; C 2;   V;   V|];
            [|   V; C 6; C 3;   V; C 2;   V; C 8; C 1;   V|];
            [|   V;   V; C 8;   V;   V; C 3;   V; C 6; C 9|];
            [|   V; C 9; C 5; C 3;   V; C 2;   V;   V; C 1|];
            [|   V; C 1;   V;   V; C 7;   V;   V;   V;   V|];
            [|   V;   V;   V; C 9;   V; C 5;   V;   V; C 8|]|];;

let gr2 = [|[|   V; C 4;   V;   V; C 7;   V;   V; C 3;   V|];
            [|   V;   V; C 3;   V; C 8; C 2;   V; C 1;   V|];
            [|   V;   V;   V;   V;   V;   V; C 8;   V; C 2|];
            [| C 9; C 1;   V; C 6; C 2;   V;   V;   V;   V|];
            [| C 8;   V;   V;   V;   V;   V;   V;   V; C 4|];
            [|   V;   V;   V;   V; C 1; C 5;   V; C 7; C 9|];
            [| C 3;   V; C 9;   V;   V;   V;   V;   V;   V|];
            [|   V; C 8;   V; C 9; C 4;   V; C 6;   V;   V|];
            [|   V; C 7;   V;   V; C 6;   V;   V; C 9;   V|]|];;

let gr3 = [|[| C 7;   V;   V;   V;   V;   V; C 4;   V;   V|];
            [|   V; C 2;   V;   V; C 7;   V;   V; C 8;   V|];
            [|   V;   V; C 3;   V;   V; C 8;   V;   V; C 9|];
            [|   V;   V;   V; C 5;   V;   V; C 3;   V;   V|];
            [|   V; C 6;   V;   V; C 2;   V;   V; C 4;   V|];
            [|   V;   V; C 1;   V;   V; C 7;   V;   V; C 6|];
            [|   V;   V;   V; C 3;   V;   V; C 9;   V;   V|];
            [|   V; C 3;   V;   V; C 4;   V;   V; C 6;   V|];
            [|   V;   V; C 9;   V;   V; C 1;   V;   V; C 5|]|];;

let gr4 = [|[|   V;   V;   V; C 7;   V;   V; C 8;   V;   V|];
            [|   V;   V;   V;   V; C 4;   V;   V; C 3;   V|];
            [|   V;   V;   V;   V;   V; C 9;   V;   V; C 1|];
            [| C 6;   V;   V; C 5;   V;   V;   V;   V;   V|];
            [|   V; C 1;   V;   V; C 3;   V;   V; C 4;   V|];
            [|   V;   V; C 5;   V;   V; C 1;   V;   V; C 7|];
            [| C 5;   V;   V; C 2;   V;   V; C 6;   V;   V|];
            [|   V; C 3;   V;   V; C 8;   V;   V; C 9;   V|];
            [|   V;   V; C 7;   V;   V;   V;   V;   V; C 2|]|];;


(* --------------------------------------------------------- *)

(* Gestion des conditions *)

let compatible_ligne gr i j k =
    let res = ref true in
    let col = ref 0 in
    while !res && !col < 9 do
        res := !col = j || gr.(i).(!col) <> C k ;
        incr col
    done ;
    !res

let compatible_colonne gr i j k =
    let res = ref true in
    let lig = ref 0 in
    while !res && !lig < 9 do
        res := !lig = i || gr.(!lig).(j) <> C k ;
        incr lig
    done ;
    !res

let compatible_carre gr i j k =
    let res = ref true in
    let i0, j0 = i - i mod 3, j - j mod 3 in (* coordonnées de la case en haut à gauche du carré contenant (i, j) *)
    for lig = i0 to i0 + 2 do
        for col = j0 to j0 + 2 do
            res := !res && ((lig = i && col = j) || gr.(lig).(col) <> C k)
        done
    done ;
    !res

let compatible gr i j k = 
    compatible_ligne gr i j k &&
    compatible_colonne gr i j k &&
    compatible_carre gr i j k


(* --------------------------------------------------------- *)

(* Remplissage d'une grille *)

let suivant i j =
    i + (j+1)/9, (j+1) mod 9

exception Solution

let rec remplir gr i j =
    if i = 9 then
        raise Solution
    else
        let i_suivant, j_suivant = suivant i j in
        match gr.(i).(j) with
            | C _ -> remplir gr i_suivant j_suivant
            | V ->  for k = 1 to 9 do
                        if compatible gr i j k then begin
                            gr.(i).(j) <- C k ;
                            remplir gr i_suivant j_suivant
                        end ;
                        gr.(i).(j) <- V
                    done

let resoudre gr =
    let gr_copie = Array.make 9 [||] in
    for i = 0 to 8 do
        gr_copie.(i) <- Array.copy gr.(i)
    done ;
    try
        remplir gr_copie 0 0 ;
        failwith "pas de solution"
    with Solution -> gr_copie


(* --------------------------------------------------------- *)

(* Compléments *)

let imprime grille =
    let tirets = " ----- ----- -----" in
    print_endline tirets ;
    for i = 0 to 8 do    
        print_string "|" ;
        for j = 0 to 8 do
            (match grille.(i).(j) with
                | V -> print_string " "
                | C n -> print_int n) ;
            if j mod 3 = 2 then
                print_string "|"
            else
                print_string " "
        done ;
        print_newline () ;
        if i mod 3 = 2 then
            print_endline tirets 
    done

let nb_sol gr =
    let nb = ref 0 in
    let rec remplir gr i j =
        if i = 9 then
            incr nb
        else
            let i_suivant, j_suivant = suivant i j in
            match gr.(i).(j) with
                | C _ -> remplir gr i_suivant j_suivant
                | V ->  for k = 1 to 9 do
                            if compatible gr i j k then begin
                                gr.(i).(j) <- C k ;
                                remplir gr i_suivant j_suivant
                            end ;
                            gr.(i).(j) <- V
                        done
    in remplir gr 0 0 ;
    !nb

let rec remplir_alea gr i j =
    if i = 9 then
        raise Solution
    else
        let i_suivant, j_suivant = suivant i j in
        match gr.(i).(j) with
            | C _ -> remplir_alea gr i_suivant j_suivant
            | V ->  let k0 = Random.int 9 in
                    for kplus = 0 to 8 do
                        let k = 1 + (k0 + kplus) mod 9 in
                        if compatible gr i j k then begin 
                            gr.(i).(j) <- C k ;
                            remplir_alea gr i_suivant j_suivant
                        end ;
                        gr.(i).(j) <- V
                    done

let resoudre_alea gr =
    Random.self_init () ;
    try
        remplir_alea gr 0 0;
        failwith "pas de solution"
    with Solution -> gr

let cree_grille () =
    let gr = resoudre_alea (Array.make_matrix 9 9 V) in
    let unique_solution = ref 0 in
    (* arbitrairement, je choisis de continuer de vider la grille
       tant qu'on n'a pas essayé d'enlever 15 chiffres sans succès *)
    while !unique_solution < 15 do
        let i, j = Random.int 9, Random.int 9 in
        let case_i_j = gr.(i).(j) in
        gr.(i).(j) <- V ;
        if nb_sol gr <> 1 then begin
            incr unique_solution ;
            gr.(i).(j) <- case_i_j
        end
    done ;
    gr

(* Si on ne veut pas plus de 'seuil' valeurs *)
let taille gr =
    let n = ref 0 in
    for i = 0 to 8 do
        for j = 0 to 8 do
            match gr.(i).(j) with
                | V -> ()
                | C _ -> incr n
        done
    done ;
    !n

let rec bonne_grille seuil = match cree_grille () with
    | gr when taille gr <= seuil -> gr
    | _ -> bonne_grille seuil


(*---------------------------------------------------------*)

(* Amélioration de la vérification *)

type sudoku = { grl : grille;
                lig: int array;
                col : int array;
                car : int array }

let sdk0 = { grl = gr0 ;
             lig = [|50; 267; 193; 272; 108; 9; 100; 43; 35|];
             col = [|47; 104; 32; 329; 10; 177; 2; 97; 279 |];
             car = [|104; 387; 19; 41; 24; 324; 38; 105; 35|] }

(*  Le singleton {k} est représenté par 2^(k-1), donc 1 lsl (k-1) *)

let ajouter sdk i j k = 
    let singleton = 1 lsl (k-1) in
    sdk.grl.(i).(j) <- C k;
    sdk.lig.(i) <- sdk.lig.(i) lor singleton;
    sdk.col.(j) <- sdk.col.(j) lor singleton;
    let c = (i - i mod 3) + j / 3 in
    sdk.car.(c) <- sdk.car.(c) lor singleton

let vers_sudoku gr = 
    let sdk = { grl = Array.make_matrix 9 9 V;
                lig = Array.make 9 0;
                col = Array.make 9 0;
                car = Array.make 9 0 } in
    for i = 0 to 8 do
        for j = 0 to 8 do
            match gr.(i).(j) with
                | V -> ()
                | C k -> ajouter sdk i j k
        done
    done ;
    sdk

let vider sdk i j =
    match sdk.grl.(i).(j) with
        | V -> ()
        | C k ->    let singleton = 1 lsl (k-1) in
                    sdk.grl.(i).(j) <- V ;
                    let c = (i - i mod 3) + j / 3 in
                    sdk.lig.(i) <- sdk.lig.(i) lxor singleton ;
                    sdk.col.(j) <- sdk.col.(j) lxor singleton ;
                    sdk.car.(c) <- sdk.car.(c) lxor singleton

let compatible_sdk sdk i j k =
    let singleton = 1 lsl (k-1) in
    let c = (i - i mod 3) + j / 3 in
    (sdk.lig.(i) land singleton = 0) &&
    (sdk.col.(j) land singleton = 0) &&
    (sdk.car.(c) land singleton = 0)

let resoudre_sdk gr =
    let sdk = vers_sudoku gr in
    let rec remplir_sdk sdk i j =
        if i = 9 then
            raise Solution
        else
            let i_suivant, j_suivant = suivant i j in
            match sdk.grl.(i).(j) with
                | C k -> remplir_sdk sdk i_suivant j_suivant
                | V ->  for k = 1 to 9 do
                            if compatible_sdk sdk i j k then begin 
                                ajouter sdk i j k ;
                                remplir_sdk sdk i_suivant j_suivant
                            end ;
                            vider sdk i j
                        done
    in try
        remplir_sdk sdk 0 0 ;
        failwith "pas de solution"
    with Solution -> sdk.grl
