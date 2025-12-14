(* CORRIGÉ PARTIEL DU TD : SÉLECTION D'ACTIVITÉ (PARTIE EN OCAML) *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

type requete = {numero : int;
                debut : int;
                fin : int}

let prog_dynamique r =
    (* fonction auxiliaire qui détermine si les requêtes i et j sont compatibles *)
    let compatible i j =
        i.debut >= j.fin || j.debut >= i.fin
    in
    (* fonction auxiliaire qui renvoie la liste des requêtes compatibles avec i dans r *)
    let rec comp r i = match r with   
        | [] -> []
        | x::xs when compatible x i -> x::comp xs i
        | _::xs -> comp xs i
    in
    (* tableau associatif pour la mémoïsation *)
    let memo = Hashtbl.create 100 in
    (* fonction auxiliaire récursive avec mémoïsation *)
    let rec remplir r =
        (* on ne fait les calculs que s'ils n'ont pas déjà été faits et stockés *)
        begin if not (Hashtbl.mem memo r) then
            match r with
                | [] -> Hashtbl.add memo r 0 (* cas de base *)
                | x::xs -> Hashtbl.add memo r (max (remplir xs) (1 + remplir (comp xs x))) (* cas récursif *)
        end ;
        Hashtbl.find memo r
    (* on appelle la fonction avec l'ensemble de requêtes qui nous intéresse *)
    in remplir r

let test_exemple_du_sujet () =
    let r0 = {numero = 0; debut = 0; fin = 4} in
    let r1 = {numero = 1; debut = 5; fin = 10} in
    let r2 = {numero = 2; debut = 2; fin = 6} in
    let r3 = {numero = 3; debut = 8; fin = 10} in
    let r4 = {numero = 4; debut = 3; fin = 4} in
    let r5 = {numero = 5; debut = 5; fin = 7} in
    let r6 = {numero = 6; debut = 8; fin = 12} in
    let r7 = {numero = 7; debut = 3; fin = 7} in
    let r8 = {numero = 8; debut = 10; fin = 12} in
    let r = [r0; r1; r2; r3; r4; r5; r6; r7; r8] in
    print_string "Nombre de requêtes sélectionnées avec la programmation dynamique : " ;
    print_int (prog_dynamique r) ;
    print_endline "."

let _ = test_exemple_du_sujet ()
