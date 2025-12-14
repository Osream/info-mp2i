(* CORRIGÉ DU TP : TABLEAUX EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Ré-écriture des fonctions du module Array *)

let array_mem elt tab =
    let trouve = ref false in
    for i = 0 to Array.length tab - 1 do
        if tab.(i) = elt then
            trouve := true
    done ;
    !trouve

let array_copy tab =
    let taille = Array.length tab in
    (* cas particulier du tableau vide *)
    if taille = 0 then
        [||]
    else begin
            (* on initialise le tableau avec une valeur au hasard (ici j'ai choisi la première) *)
            let res = Array.make taille tab.(0) in
            (* puis on le remplit correctement *)
            for i = 1 to taille - 1 do
                res.(i) <- tab.(i)
            done ;
            res
    end

let array_init taille f =
    let res = Array.make taille (f 0) in
    for i = 1 to taille - 1 do
        res.(i) <- f i
    done ;
    res

let array_exists prop tab =
    let existe_elt_verifiant_prop = ref false in
    for i = 0 to Array.length tab - 1 do
        if prop tab.(i) then
            existe_elt_verifiant_prop := true
    done ;
    !existe_elt_verifiant_prop

let array_for_all prop tab =
    let tous_elt_verifient_prop = ref true in
    for i = 0 to Array.length tab - 1 do
        if not (prop tab.(i)) then
            tous_elt_verifient_prop := false
    done ;
    !tous_elt_verifient_prop

let tab_map f tab =
    let taille = Array.length tab in
    if taille = 0 then
        [||]
    else begin
            let res = Array.make taille (f tab.(0)) in
            for i = 1 to taille - 1 do
                res.(i) <- f tab.(i)
            done ;
            res
    end

let tab_iter f tab =
    for i = 0 to Array.length tab - 1 do
        f tab.(i)
    done


(* versions plus concises *)

let mem elt tab =
    Array.exists (fun x -> x = elt) tab

let for_all prop tab =
    (*  « tous les éléments vérifient la propriété »
        équivaut à
        « il n'existe aucun élément ne vérifiant pas la propriété »
    *)
    not (Array.exists (fun x -> not (prop x)) tab)

let exists prop tab =
    not (Array.for_all (fun x -> not (prop x)) tab)

let copy tab =
    Array.init (Array.length tab) (fun i -> tab.(i))

let map f tab =
    Array.init (Array.length tab) (fun i -> f tab.(i))


(* --------------------------------------------------------- *)

(* Manipulations de tableaux multidimensionnels *)

let affiche_2d t =
    for i = 0 to Array.length t - 1 do
        for j = 0 to Array.length t.(i) - 1 do
            print_int t.(i).(j) ;
            print_string " " 
        done ;
        print_newline ()
    done

let array_make_matrix nb_lignes nb_cols val_init =
    (* tableau de tableaux vides *)
    let res = Array.make nb_lignes [||] in
    for i = 0 to nb_lignes - 1 do
        (* crée les tableux internes *)
        res.(i) <- Array.make nb_cols val_init
    done ;
    res

let copy_matrix m =
    let nb_lignes = Array.length m in
    let res = Array.make nb_lignes [||] in
    for i = 0 to nb_lignes - 1 do
        let nb_cols = Array.length m.(i) in
        if nb_cols = 0 then
            res.(i) <- [||]
        else begin
            res.(i) <- Array.make nb_cols m.(i).(0) ;
            for j = 0 to nb_cols - 1 do
                res.(i).(j) <- m.(i).(j)
            done
        end
    done ;
    res

let init_matrix nb_lignes nb_cols f =
    let res = Array.make_matrix nb_lignes nb_cols (f 0 0) in
    for i = 0 to nb_lignes - 1 do
        for j = 0 to nb_cols - 1 do
            res.(i).(j) <- f i j
        done
    done ;
    res


(* versions plus concises *)

let affiche_2d_concis tab =
    let affiche_entier i =
        print_int i ; print_string " "
    in
    Array.iter ( fun ligne ->
                    Array.iter affiche_entier ligne ;
                    print_newline () )
                tab

let make_matrix_concis nb_lignes nb_cols val_init =
    Array.init nb_lignes (fun _ -> Array.make nb_cols val_init)
                        
let copy_matrix_concis m =
    Array.init (Array.length m) (fun i -> Array.init (Array.length m.(i)) (fun j -> m.(i).(j)))
    
let init_matrix_concis nb_lignes nb_cols f =
    Array.init nb_lignes (fun i -> Array.init nb_cols (fun j -> f i j))
    

(* versions encore plus concises *)

let affiche_2d_plus_concis tab =
    Array.iter ( fun ligne -> Array.iter (fun i -> print_int i ; print_string " ") ligne ; print_newline () ) tab

let copy_matrix_plus_concis m = Array.map Array.copy m
 

(* --------------------------------------------------------- *)

(* Exercices *)


(* taille d'un tableau (moins efficace que Array.length) *)

let array_length tab = (*  *)
    let taille = ref 0 in
    (try
        while true do
            let _ = tab.(!taille) in
            incr taille
        done
    with Invalid_argument _ -> ()) ;
    !taille


(* création de tableaux multidimensionnels *)

let init_croissant_2d n =
    let t = Array.make_matrix n n 0 in 
    for i = 0 to  n - 1 do
        for j = 0 to n - 1 do
            t.(i).(j) <- j + 1
        done
    done ;
    t

let init_croissant_carre_2d n =
    let t = Array.make_matrix n n 0 in 
    for i = 0 to  n - 1 do
        for j = 0 to n - 1 do
            t.(i).(j) <- j + 1 + n * i
        done
    done ;
    t

let damier n =
    let t = Array.make_matrix n n 0 in
    for i = 0 to n - 1 do
        for j = 0 to n - 1 do
            if (i + j) mod 2 = 1 then
                t.(i).(j) <- 1
        done
    done;
    t

let make_tenseur x y z val_init = (* x y z sont les 3 dimensions du tenseur à créer *)
    let t = Array.make x [||] in
    for i = 0 to x - 1 do
        t.(i) <- Array.make_matrix y z val_init
    done ;
    t


(* sous-tableau *)

let sous_tableau tab i_depart taille =
    Array.init taille (fun i -> tab.(i_depart + i))

let sous_matrice m (i_depart, j_depart) (l, c) =
    Array.init l (fun i -> Array.init c (fun j -> m.(i_depart + i).(j_depart + j)))
      

(* recherche *)

let ppem t =
    let taille = Array.length t in
    (* pour chaque entier naturel compris entre 0 et la taille du tableau - 1 
       on conserve un booléen indiquant s'il est présent dans t *)
    let est_present = Array.make taille false in
    for i = 0 to taille - 1 do
        if 0 <= t.(i) && t.(i) < taille then
            (* si on a trouvé un entier naturel n on conserve le booléen true à l'indice n *)
            est_present.(t.(i)) <- true
    done ;
    let res = ref 0 in
    (* on parcourt nos booléens jusqu'à trouver un false,
       qui indique qu'un entier naturel n'est pas présent dans le tableau t *)
    while !res < taille && est_present.(!res) do
        incr res
    done ;
    !res

let ppem_matrix m =
    (* dimensions *)
    let n, p = Array.length m, Array.length m.(0) in
    (* même principe que pour un tableau simple,
       la seule différence est que les entiers naturels inclus dans m
       peuvent aller de 0 à n*p - 1 donc le tableau est_present est plus grand *)
    let est_present = Array.make (n*p) false in
    for i = 0 to n - 1 do
        for j = 0 to p - 1 do
            if 0 <= m.(i).(j) && m.(i).(j) < n*p then
                est_present.(m.(i).(j)) <- true
        done
    done ;
    let res = ref 0 in
    while !res < n*p && est_present.(!res) do
        incr res
    done ;
    !res

let mem_matrix val_cherchee m =
    let n, p = Array.length m, Array.length m.(0) in
    (* on parcourt notre tableau à partir de la case (0,0) *)
    let i = ref 0 in
    let j = ref 0 in
    let trouve = ref false in
    (* on lit les valeurs de chaque ligne une par une
       avant de passer à la ligne suivante, et ce
       tant qu'on a pas trouvé celle recherchée *)
    while !i < n && not !trouve do
        j := 0 ;
        while !j < p && not !trouve do
            if m.(!i).(!j) = val_cherchee then
                trouve := true
            else
                incr j
        done ;
        incr i
    done ;
    !trouve

let mem_matrix_efficace val_cherchee m =
    let n, p = Array.length m, Array.length m.(0) in
    (* on commence cette fois du coin en haut à droite *)
    let i = ref 0 in
    let j = ref (p - 1) in
    let trouve = ref false in
    (* tant qu'il reste des lignes ou colonnes à regarder
       et qu'on a pas trouvé la valeur recherchée *)
    while !i < n && !j >= 0 && not !trouve do
        if m.(!i).(!j) = val_cherchee then
            trouve := true
        (* si la valeur cherchée est supérieure à la case actuelle, 
           on passe à la ligne suivante *)
        else if m.(!i).(!j) < val_cherchee then
            incr i
        (* si la valeur cherchée est inférieure à la case actuelle, 
           on passe à la colonne précédente *)
        else
            decr j
    done ;
    !trouve
