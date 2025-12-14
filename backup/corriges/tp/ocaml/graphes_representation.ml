(* CORRIGÉ DU TP : REPRÉSENTATION DES GRAPHES (PARTIE EN OCAML) *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Matrice d'adjacence *)

type matrice_adjacence = int array array

let mat_go = [| [|0; 1; 0; 0; 0; 0; 0; 0; 0|];
                [|1; 0; 0; 1; 0; 0; 0; 0; 0|];
                [|0; 0; 0; 0; 1; 1; 0; 0; 0|];
                [|0; 0; 0; 0; 0; 0; 0; 0; 0|];
                [|1; 0; 0; 0; 0; 0; 0; 0; 1|];
                [|1; 0; 1; 1; 1; 0; 1; 0; 0|];
                [|0; 0; 1; 0; 0; 0; 0; 0; 0|];
                [|0; 0; 0; 0; 0; 0; 1; 0; 0|];
                [|0; 0; 0; 0; 0; 0; 0; 0; 0|] |]


let nb_sommets_arcs (g : matrice_adjacence) = (* O(|S|²) *)
    let nb_sommets = Array.length g in
    let nb_arcs = ref 0 in
    for si = 0 to nb_sommets - 1 do
        for sj = 0 to nb_sommets - 1 do
            nb_arcs := !nb_arcs + g.(si).(sj) (* nombre d'arcs = nombre de 1 dans la matrice *)
        done
    done ;
    nb_sommets, !nb_arcs

let possede_boucle (g : matrice_adjacence) = (* O(|S|) *)
    let boucle = ref false in
    for si = 0 to Array.length g - 1 do
        boucle := !boucle || g.(si).(si) = 1 (* on vérifie la diagonale *)
    done ;
    !boucle

let sj_est_successeur_de_si (g : matrice_adjacence) sj si = (* O(1) *)
    g.(si).(sj) = 1

let si_est_predecesseur_de_sj (g : matrice_adjacence) si sj = (* O(1) *)
    sj_est_successeur_de_si g sj si

let degres (g : matrice_adjacence) sommet = (* O(|S|) *)
    let sortant = ref 0 in
    let entrant = ref 0 in
    for si = 0 to Array.length g - 1 do
        entrant := !entrant + g.(si).(sommet) ; (* somme des 1 sur la colonne *)
        sortant := !sortant + g.(sommet).(si) (* somme des 1 sur la ligne *)
    done ;
    !sortant, !entrant


(* --------------------------------------------------------- *)

(* Liste d'adjacence *)

type liste_adjacence = int list array

let lst_gno = [| [1;4;5]; [0;3]; [4;5;6]; [1;5]; [0;2;5;8]; [0;2;3;4;6]; [2;5;7]; [6]; [4] |]


let nb_aretes (g : liste_adjacence) = (* O(|S|+|A|) *)
    let nb_aretes = ref 0 in
    (* somme des tailles des listes de chaque sommet = somme des degrés de chaque sommet *)
    Array.iter (fun lst -> nb_aretes := !nb_aretes + List.length lst) g ;
    (* la somme des degrés des sommets = 2*|A|, donc on divise par 2 pour retrouver |A| *)
    !nb_aretes / 2

let sont_voisins (g : liste_adjacence) si sj = (* O(d(si)) *)
    List.mem sj g.(si) (* ou bien List.mem si g.(sj) car g est non orienté *)

let verifie_orientation (g : liste_adjacence) = (* O(|S|×|A|) *)
    let est_gno = ref true in
    for si = 0 to Array.length g - 1 do
        (* vérifie que pour toute liaison si -> sj, il y a aussi sj -> si*)
        est_gno := !est_gno && List.for_all (fun sj -> List.mem si g.(sj)) g.(si)
    done ;
    !est_gno
    
let degre (g : liste_adjacence) sommet = (* O(d(sommet)) *)
    List.length g.(sommet)

let sommet_degre_max (g : liste_adjacence) = (* O(|S|+|A|) *)
    let res = ref (-1) in
    let degre_res = ref min_int in
    for sommet = 0 to Array.length g - 1 do
        let degre_sommet = degre g sommet in
        if degre_sommet > !degre_res then begin
            degre_res := degre_sommet ;
            res := sommet
        end
    done ;
    !res


(* --------------------------------------------------------- *)

(* Sérialisation *)

let decompose_arc (arc : string) =
    (* fonction auxiliaire qui prend une chaîne au format "i,j" et renvoie les entiers i et j *)
    let indice_virgule = ref 0 in
    while arc.[!indice_virgule] != ',' do incr indice_virgule done ;
    let avant_virgule = String.sub arc 0 !indice_virgule in
    let apres_virgule = String.sub arc (!indice_virgule + 1) (String.length arc - !indice_virgule - 1) in
    int_of_string avant_virgule, int_of_string apres_virgule

let serialise_mat (g : matrice_adjacence) nom_fichier =
    let nb_sommets = Array.length g in
    let fichier = open_out nom_fichier in
    (* la première ligne contient le nombre de sommets du graphe *)
    output_string fichier (string_of_int nb_sommets ^ "\n") ;
    (* les lignes suivantes contiennent des couples i,j signifiant qu'il y a un arc / une arête de i à j *)
    for i = 0 to nb_sommets - 1 do
        for j = 0 to nb_sommets - 1 do
            if g.(i).(j) = 1 then
                output_string fichier (string_of_int i ^ "," ^ string_of_int j ^ "\n")
        done
    done ;
    close_out fichier

let deserialise_mat nom_fichier : matrice_adjacence =
    let fichier = open_in nom_fichier in
    let nb_sommets = int_of_string (input_line fichier) in
    let g = Array.make_matrix nb_sommets nb_sommets 0 in
    try while true do
        let i, j = decompose_arc (input_line fichier) in
        g.(i).(j) <- 1
    done with End_of_file -> close_in fichier ;
    g

let serialise_lst (g : liste_adjacence) nom_fichier =
    let nb_sommets = Array.length g in
    let fichier = open_out nom_fichier in
    output_string fichier (string_of_int nb_sommets ^ "\n") ;
    for i = 0 to nb_sommets - 1 do
        List.iter (fun j -> output_string fichier (string_of_int i ^ "," ^ string_of_int j ^ "\n")) g.(i)
    done ;
    close_out fichier

let deserialise_lst nom_fichier : liste_adjacence =
    let fichier = open_in nom_fichier in
    let nb_sommets = int_of_string (input_line fichier) in
    let g = Array.make nb_sommets [] in
    (try while true do
        let i, j = decompose_arc (input_line fichier) in
        g.(i) <- j::g.(i)
    done with End_of_file -> close_in fichier) ;
    g
