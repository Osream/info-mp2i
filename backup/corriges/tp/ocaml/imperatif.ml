(* CORRIGÉ PARTIEL DU TP : PROGRAMMATION IMPÉRATIVE EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Références *)

let incremente x =
    x := !x + 1

let decremente x =
    x := !x - 1

let echange refa refb =
    let tmp = !refa in
    refa := !refb ;
    refb := tmp

let (ref1 : bool ref) = ref true
let (ref2 : int ref ref) = ref (ref 4)
let (ref3 : (float * float) ref) = ref (1.2, 3.4)
let (ref4 : (int -> bool) ref) = ref (fun x -> x < 0)


(* --------------------------------------------------------- *)

(* Boucles *)

let affiche_0_n n =
    for i = 0 to n - 1 do
        print_int i ;
        print_string "-"
    done ;
    print_int n ;
    print_newline ()

let affiche_n_0 n =
    for i = n downto 1 do
        print_int i ;
        print_string "-"
    done ;
    print_endline "0"

let affiche_0_n_while n =
    let i = ref 0 in
    while !i < n do
        print_int !i ;
        print_string "-" ;
        incr i
    done ;
    print_int n ;
    print_newline ()

let rec factorielle_rec n = match n with
    | 0 -> 1
    | _ -> n * factorielle_rec (n-1)

let factorielle_for n =
    let res = ref 1 in
    for i = 2 to n do
        res := !res * i
    done ;
    !res

let factorielle_while n =
    let res = ref 1 in
    let i = ref 2 in
    while !i <= n do
        res := !res * !i ;
        incr i
    done ;
    !res


(* --------------------------------------------------------- *)

(* Tableaux *)

let remplace_valeur_indice_i t i valeur =
    t.(i) <- valeur (* effet de bord *)


let affiche_tableau_flottants t =
    for i = 0 to Array.length t - 1 do
        print_float t.(i) ;
        print_string " "
    done ;
    print_newline ()

let affiche_tableau_flottants_avec_ordre_superieur t =
    Array.iter (fun x -> print_float x ; print_string " ") t ;
    print_newline ()

let init_croissant n =
    let t = Array.make n 0 in
    for i = 0 to n - 1 do
        t.(i) <- i
    done ;
    t

let init_croissant_avec_ordre_superieur n =
    Array.init n (fun i -> i)


(* --------------------------------------------------------- *)

(* Retour sur les exceptions *)

let i_eme_element t i =
    (* si le i-ème élément existe, il est renvoyé *)
    try
        Some t.(i)
    (* sinon (indice invalide) on attrape l'exception et on renvoie None *)
    with Invalid_argument _ -> None

exception Diviseur_trouve
let est_premier n =
    try
        (* on regarde tous les diviseurs potentiels de n *)
        for i = 2 to n - 1 do
            (*  si on trouve un diviseur pour n,
                alors n n'est pas premier,
                on peut donc sortir de la boucle *)
            if n mod i = 0 then
                raise Diviseur_trouve
        done ;
        (*  arrivé ici la boucle s'est terminée normalement,
            ce qui signifie que n ne possède aucun diviseur
            donc il est premier *)
        true
    with Diviseur_trouve -> false (* sortie de la boucle par l'exception = n n'est pas premier *)


exception Element_trouve
let array_mem elt tab =
    try
        for i = 0 to Array.length tab - 1 do
            if tab.(i) = elt then
                (* on a trouvé l'élément recherché,
                   on lève l'exception pour sortir de la boucle,
                   et l'exception va être attrapée pour renvoyer true *)
                raise Element_trouve
        done ;
        (* si on arrive ici c'est que la boucle s'est exécutée entièrement
           donc que l'élément n'a pas été trouvé *)
        false
    with Element_trouve -> true

exception Continue
let affiche_sauf_mult n m =
    (* affiche les entiers de 1 à n sauf les multiples de m *)
    for i = 1 to n do
        try
            if i mod m = 0 then
                (* si la valeur est un multiple de m
                    on passe directement à la suivante *)
                raise Continue
            else
                begin
                    print_int i ;
                    print_newline ()
                end
        with Continue -> ()
    done

exception Break
let affiche_jusque_mult n m =
    (* affiche les entiers de 1 à n jusqu'au premier multiple de m *)
    try
        for i = 1 to n do
            if i mod m = 0 then
                (* si la valeur est un multiple de m
                on sort de la boucle *)
                raise Break
            else
                begin
                    print_int i ;
                    print_newline ()
                end
        done
    with Break -> ()


(* --------------------------------------------------------- *)

(* Exercices *)


(* boucles for *)

let somme_entiers_entre_m_et_n m n =
    let res = ref 0 in
    for i = m to n do
        res := !res + i
    done ;
    !res

let somme_carres_entiers_pairs_entre_m_et_n m n =
    let res = ref 0 in
    for i = m to n do
        if i mod 2 = 0 then
            res := !res + (i * i)
    done ;
    !res

let s1 n =
    let res = ref 0. in
    for k = 1 to n do
        res := !res +. (1. /. float_of_int (k * k))
    done ;
    !res

let s2 n =
    let res = ref 0 in
    for i = 1 to n do
        for j = 1 to n do
            res := !res + i + j
        done
    done ;
    !res

let s3 n =
    let res = ref 0 in
    for i = 1 to n do
        for j = i to n do
            res := !res + i + j
        done
    done ;
    !res

let s4 n =
    let res = ref 0 in
    for i = 1 to n do
        for j = 1 to i-1 do
            res := !res + i + j
        done
    done ;
    !res


(* boucles while *)

let ( *** ) x n = (* x puissance n avec l'algo d'exponentiation rapide *)
    let res = ref 1 in
    let ref_x = ref x in
    let ref_n = ref n in
    while !ref_n > 0 do
        if !ref_n mod 2 = 1 then
            res := !res * !ref_x ;
        ref_n := !ref_n / 2 ;
        ref_x := !ref_x * !ref_x
    done ;
    !res

let nb_chiffres n = (* on compte le nombre de divisions par 10 nécessaires *)
    let res = ref 0 in
    let ref_n = ref n in
    while !ref_n <> 0 do
        incr res ;
        ref_n := !ref_n / 10
    done ;
    if n = 0 then 1 else !res (* attention au cas particulier du 0 *)

let racine x epsilon =
    let u = ref 1. in
    while abs_float(!u -. x /. !u) >= epsilon do
        u := 0.5 *. (!u +. x /. !u)
    done ;
    !u


(* algorithmes sur les tableaux (à maîtriser absolument) *)

let somme_tab t =
    let s = ref 0 in
    for i = 0 to Array.length t - 1 do
        s := !s + t.(i)
    done ;
    !s

let moyenne_tab t =
    float_of_int (somme_tab t) /. float_of_int (Array.length t)

let nombre_occurrences t valeur =
    let res = ref 0 in
    for i = 0 to Array.length t - 1 do
        if t.(i) = valeur then
            incr res
    done ;
    !res

let premier_indice_valeur t valeur =
    let res = ref (-1) in
    for i = 0 to Array.length t - 1 do
        if !res = -1 && t.(i) = valeur then
            res := i
    done ;
    !res

let dernier_indice_valeur t valeur =
    let res = ref (-1) in
    for i = 0 to Array.length t - 1 do
        if t.(i) = valeur then
            res := i
    done ;
    !res

let minimum_et_maximum t = 
    let maxi = ref t.(0) in
    let mini = ref t.(0) in
    for i = 1 to Array.length t - 1 do
        maxi := max t.(i) !maxi ;
        mini := min t.(i) !mini
    done ;
    !mini ; !maxi

let indices_minimum_maximum t =
    let i_mini = ref 0 in
    let i_maxi = ref 0 in
    for i = 1 to Array.length t - 1 do
        if t.(i) < t.(!i_mini) then
            i_mini := i ;
        if t.(i) > t.(!i_maxi) then
            i_maxi := i
    done ;
    !i_mini, !i_maxi

let est_croissant t =
    let croissant = ref true in
    for i = 0 to Array.length t - 2 do
        croissant := !croissant && (t.(i) <= t.(i + 1))
    done ;
    !croissant


(* construction de tableaux *)

let init_decroissant n =
    let t = Array.make n 0 in
    for i = 0 to n - 1 do
        t.(i) <- n - 1 - i
    done ;
    t

let init_decroissant_avec_ordre_superieur n =
    Array.init n (fun i -> n - 1 - i)

let renverse t =
    let n = Array.length t in
    Array.init n (fun i -> t.(n-1-i))

let renverse2 t =
    let n = Array.length t in
    for i = 0 to n / 2 - 1 do
        let tmp = t.(i) in
        t.(i) <- t.(n-1-i) ;
        t.(n-1-i) <- tmp
    done
    

(* exceptions *)

let nieme l n =
    try
        Some (List.nth l n)
    with  Invalid_argument _ -> None
        | Failure _ -> None

exception Depassement
let incremente x =
    if !x = max_int then
        raise Depassement
    else
        x := !x + 1
        
let decremente x =
    if !x = min_int then
        raise Depassement
    else
        x := !x - 1
