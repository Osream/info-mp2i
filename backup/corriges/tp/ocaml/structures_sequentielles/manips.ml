(* CORRIGÉ PARTIEL DU TP : STRUCTURES SÉQUENTIELLES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Diverses manipulations *)

(* --------------------------------------------------------- *)

(* sommet d'une pile *)

let sommet p =
	let res = Pile.depiler p in
	Pile.empiler res p ;
	res


(* --------------------------------------------------------- *)

(* affichages de piles et files *)

let affiche_file f =
    let sauv = File.creer () in
    (* on affiche chaque élément
       tout en sauvegardant les valeurs dans une file intermédiaire *)
    while not (File.est_vide f) do
        let tete = File.defiler f in
        print_int tete ;
        print_string " " ;
        File.enfiler tete sauv
    done ;
    print_newline () ;
    (* on remet tout dans la file d'origine *)
    while not (File.est_vide sauv) do
        File.enfiler (File.defiler sauv) f
    done


let affiche_pile p =
    let sauv = Pile.creer () in
    (* on affiche chaque élément
        tout en sauvegardant les valeurs dans une pile intermédiaire *)
    while not (Pile.est_vide p) do
        let sommet = Pile.depiler p in
        print_int sommet ;
        print_newline () ;
        Pile.empiler sommet sauv
    done ;
    (* on remet tout dans la pile d'origine *)
    while not (Pile.est_vide sauv) do
        Pile.empiler (Pile.depiler sauv) p
    done


(* code qui se lancera à l'exécution : *)
(* crée une pile et une file contenant tous les entiers
   passés en arguments du programme, puis les affiche *)
let _ =
    let p = Pile.creer () in
    let f = File.creer () in
    for i = 1 to Array.length Sys.argv - 1 do
        Pile.empiler (int_of_string Sys.argv.(i)) p ;
        File.enfiler (int_of_string Sys.argv.(i)) f
    done ;
    print_string "Pile contenant les arguments :\n" ;
    affiche_pile p ;
    print_string "File contenant les arguments :\n" ;
    affiche_file f


(* --------------------------------------------------------- *)

(* tableaux associatifs *)

let update ta cle valeur =
    Hashtbl.remove ta cle ;
    Hashtbl.add ta cle valeur


let mon_find ta cle = match Hashtbl.find_opt ta cle with
    | None -> raise Not_found
    | Some valeur -> valeur


let affiche_TA ta =
    Hashtbl.iter (fun cle valeur -> print_int cle ;
                                    print_string " ";
                                    print_int valeur ;
                                    print_newline ()   ) ta


(* --------------------------------------------------------- *)

(* recherche de doublons dans une pile *)

let mem_pile elt p =
    let sauv = Pile.creer () in
    let appartient = ref false in
    (* on dépile tout en regardant si on trouve elt *)
    while not (Pile.est_vide p) do
        let sommet = Pile.depiler p in
        appartient := !appartient || sommet = elt ;
        Pile.empiler sommet sauv
    done ;
    (* on remet tout dans la pile d'origine *)
    while not (Pile.est_vide sauv) do
        Pile.empiler (Pile.depiler sauv) p
    done ;
    !appartient


let existe_doublons p =
    let sauv = Pile.creer () in
    let doublons = ref false in
    (* on dépile tout en regardant si on croise un élément déjà vu *)
    while not (Pile.est_vide p) do
        let sommet = Pile.depiler p in
        doublons := !doublons || mem_pile sommet sauv ;
        Pile.empiler sommet sauv
    done ;
    (* on remet tout dans la pile d'origine *)
    while not (Pile.est_vide sauv) do
        Pile.empiler (Pile.depiler sauv) p
    done ;
    !doublons


let existe_doublons_v2 p =
    let deja_croises = Hashtbl.create 100 in (* taille aléatoire *)
    let sauv = Pile.creer () in
    let doublons = ref false in
    while not (Pile.est_vide p) do
        let sommet = Pile.depiler p in
        if Hashtbl.mem deja_croises sommet then
            doublons := true
        else
            Hashtbl.add deja_croises sommet 0 ;
        Pile.empiler sommet sauv
    done ;
    while not (Pile.est_vide sauv) do
        Pile.empiler (Pile.depiler sauv) p
    done ;
    !doublons
    (* La première méthode est quadratique, celle-ci est linéaire en
       la taille de la pile, c'est donc mieux. Ceci est dû au fait
       que mem est très efficace sur les tableaux associatifs. *)


(* --------------------------------------------------------- *)

(* valeur d'occurrence maximale dans une file *)

let nb_occs f =
    let nb_occurrences = Hashtbl.create 100 in
    let sauv = File.creer () in
    while not (File.est_vide f) do
        let tete = File.defiler f in
        if Hashtbl.mem nb_occurrences tete then
            update nb_occurrences tete (Hashtbl.find nb_occurrences tete + 1) (* trouvé 1 fois de plus *)
        else
            Hashtbl.add nb_occurrences tete 1 ; (* trouvé 1 seule fois *)
        File.enfiler tete sauv
    done ;
    while not (File.est_vide sauv) do
        File.enfiler (File.defiler sauv) f
    done ;
    nb_occurrences


let maxi_TA ta =
    let cle_max = ref None in
    let valeur_max = ref min_int in
    Hashtbl.iter (fun cle valeur -> if valeur > !valeur_max then begin
                                        cle_max := Some cle ;
                                        valeur_max := valeur
                                    end                                 ) ta;
    
    match !cle_max with
        | None -> failwith "tableau associatif vide"
        | Some cle -> cle


let maxi_file f =
    maxi_TA (nb_occs f)