(* CORRIGÉ DU TD : PLUS COURT CHEMIN DANS UN GRAPHE *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)



(* IMPLEMENTATION DE FLOYD-WARSHALL *)


(* --------------------------------------------------------- *)

(* types pour représenter les matrices *)

type coeff = Infini | Valeur of int
type matrice = coeff array array


(* --------------------------------------------------------- *)
    
(* fonctions auxiliaires pour manipuler le type coefficient *)
    
let addition c1 c2 (* c1 + c2 *) = match c1, c2 with
    | Infini, _ | _, Infini -> Infini
    | Valeur v1, Valeur v2 -> Valeur (v1 + v2)

let compare c1 c2 (* c1 < c2 *) = match c1, c2 with
    | Infini, _ -> false
    | _, Infini -> true
    | Valeur v1, Valeur v2 -> v1 < v2


(* --------------------------------------------------------- *)       
                                             
(* algorithme de Floyd-Warshall *)

let floyd_warshall (g : matrice) =
    (* n = nombre de sommets *)
    let n = Array.length g in
    (* initialisation des matrices des distances et des prédécesseurs *)
    let distances = Array.map Array.copy g in
    let predecesseurs = Array.init n (fun i -> Array.init n (fun j -> if i = j ||  g.(i).(j) = Infini then None else Some i)) in
    (* mises à jour de la matrice pour prendre en compte le sommet k = 0, puis k = 1, puis ..., puis k = n-1 *)  
    for k = 0 to n-1 do
        for i = 0 to n-1 do
            for j = 0 to n-1 do
                let potentielle_meilleure_distance = addition distances.(i).(k) distances.(k).(j) in
                (* cas où la mise à jour est nécessaire *)
                if compare potentielle_meilleure_distance distances.(i).(j) then begin
                    distances.(i).(j) <- potentielle_meilleure_distance ;
                    predecesseurs.(i).(j) <- predecesseurs.(k).(j)
                end
            done
        done
    done ;
    distances, predecesseurs


(* --------------------------------------------------------- *)  
  
(* exemples *)

let graphe_question_5 =
  [| [| Valeur 0; Infini; Valeur 2; Valeur 4 |];
     [| Valeur 1; Valeur 0; Valeur 5; Infini |];
     [| Valeur 2; Valeur (-1); Valeur 0; Valeur 7|];
     [| Infini; Infini; Valeur (-3); Valeur 0 |] |]

let graphe_question_12 (* a = 0, b = 1, etc. *) =
  [| [| Valeur 0; Valeur 1; Valeur 5; Infini; Infini; Infini; Valeur 5 |];
     [| Valeur 1; Valeur 0; Infini; Valeur 2; Infini; Infini; Valeur 3 |];
     [| Valeur 5; Infini; Valeur 0; Valeur 3; Valeur 4; Valeur 2; Infini |];
     [| Infini; Valeur 2; Valeur 3; Valeur 0; Infini; Valeur 1; Infini |];
     [| Infini; Infini; Valeur 4; Infini; Valeur 0; Infini; Valeur 5 |];
     [| Infini; Infini; Valeur 2; Valeur 1; Valeur 5; Valeur 0; Infini |];
     [| Valeur 5; Valeur 3; Infini; Infini; Infini; Infini; Valeur 0 |] |]

let print_coeff c = match c with
    | Infini -> print_string "∞\t"
    | Valeur v -> print_int v ; print_string "\t"

let print_option c = match c with
    | None -> print_string "×\t"
    | Some v -> print_int v ; print_string "\t"

let affiche_matrice mat fct_affichage =
    Array.iter (fun ligne -> Array.iter fct_affichage ligne ; print_newline ()) mat
    

let _ =
    print_string "\n ----- FLOYD-WARSHALL -----\n\n" ;
    let dist5, pred5 = floyd_warshall graphe_question_5 in
    let dist12, pred12 = floyd_warshall graphe_question_12 in
    print_string "Matrice des distances obtenue pour le graphe de la question 5 du TD :\n" ;
    affiche_matrice dist5 print_coeff ;
    print_string "\nMatrice des prédecesseurs obtenue pour le graphe de la question 5 du TD :\n" ;
    affiche_matrice pred5 print_option ;
    print_string "\nMatrice des distances obtenue pour le graphe de la question 12 du TD :\n" ;
    affiche_matrice dist12 print_coeff ;
    print_string "\nMatrice des prédecesseurs obtenue pour le graphe de la question 12 du TD :\n" ;
    affiche_matrice pred12 print_option
