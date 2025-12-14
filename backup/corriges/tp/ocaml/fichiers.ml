(*
CORRIGÉ PARTIEL DU TP : GESTION DE FICHIERS (PARTIE EN OCAML)
Par J. BENOUWT
Licence CC BY-NC-SA
*)


(* --------------------------------------------------------- *)


(* Copie d'un fichier dans un autre *)

let copie f1 f2 =
    try
        (* On ouvre le fichier à lire et le fichier dans lequel copier *)
        let (fichier : in_channel) = open_in f1 in
        let (copie : out_channel) = open_out f2 in
        (* Tant qu'il reste des lignes à lire (c'est-à-dire tant que End_of_file n'est pas levée) : *)
        try
            while true do
                (* on lit une ligne du fichier, *)
                let ligne = input_line fichier ^ "\n" in
                (* on la copie dans le fichier ouvert en écriture. *)
                output_string copie ligne
            done
        with End_of_file -> (* Lorsque End_of_file est levée on a tout lu donc on peut fermer les fichiers.*) 
                            close_in fichier ;
                            close_out copie
    with Sys_error _ -> output_string stderr "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n"


(*
(* Pour tester la copie, décommentez un des deux codes suivants *)

(* 1) arguments en ligne de commande : *)
let _ =
    if Array.length Sys.argv <> 3 then
        output_string stderr "on attend deux arguments\n"
    else
        copie Sys.argv.(1) Sys.argv.(2)


(* 2) lecture sur l'entrée standard : *)
let _ =
    let f1 = read_line () in
    let f2 = read_line () in
    copie f1 f2
*)



(* --------------------------------------------------------- *)


(* Sérialisation de structures de données séquentielles *)


(* fonctions auxiliaires *)

let transvase_pile_vers_pile p1 p2 =
    while not (Stack.is_empty p1) do
        Stack.push (Stack.pop p1) p2
    done

let transvase_file_vers_file f1 f2 =
    while not (Queue.is_empty f1) do
        Queue.push (Queue.pop f1) f2
    done


(* sérialisation d'une pile *)

let serialise_pile p fic =
    try
        let fichier = open_out fic in
        let sauv = Stack.create () in
        while not (Stack.is_empty p) do
            let elt = Stack.pop p in
            output_string fichier (string_of_int elt ^ "\n") ;
            Stack.push elt sauv
        done ;
        transvase_pile_vers_pile sauv p ;
        close_out fichier
    with Sys_error _ -> output_string stderr "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n"

let deserialise_pile fic =
    let p = Stack.create () in
    begin
        try
            let p_a_l_envers = Stack.create () in
            let fichier = open_in fic in
            try
                while true do
                    let elt = int_of_string (input_line fichier) in
                    Stack.push elt p_a_l_envers
                done
            with End_of_file -> close_in fichier ;
                                transvase_pile_vers_pile p_a_l_envers p
        with Sys_error _ -> output_string stderr "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n"
    end ;
    p


(* sérialisation d'une file *)

let serialise_file f fic =
    try
        let fichier = open_out fic in
        let sauv = Queue.create () in
        while not (Queue.is_empty f) do
            let elt = Queue.pop f in
            output_string fichier (string_of_int elt ^ "\n") ;
            Queue.push elt sauv
        done ;
        transvase_file_vers_file sauv f ;
        close_out fichier
    with Sys_error _ -> output_string stderr "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n"

let deserialise_file fic =
    let f = Queue.create () in
    begin
        try
            let fichier = open_in fic in
            try
                while true do
                    let elt = int_of_string (input_line fichier) in
                    Queue.push elt f
                done
            with End_of_file -> close_in fichier
        with Sys_error _ -> output_string stderr "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n"
    end ;
    f



(* --------------------------------------------------------- *)


(* Exercices *)

let somme_de_n_entiers_saisis () =
    if Array.length Sys.argv <> 2 then
        output_string stderr "on attend un argument\n"
    else begin
        try
            let n = int_of_string Sys.argv.(1) in
            let somme = ref 0 in
            for i = 1 to n do
                let entier_lu = int_of_string (input_line stdin) in
                somme := !somme + entier_lu
            done ;
            output_string stdout (string_of_int !somme ^ "\n")
        with Failure _ -> output_string stderr "on attendait un entier\n"
    end


let serialise_tableau_associatif ta fic =
    try
        let fichier = open_out fic in
        Hashtbl.iter    ( fun cle valeur ->
                            output_string fichier (string_of_int cle ^ " " ^ string_of_int valeur ^ "\n")
                        ) ta ;
        close_out fichier
    with Sys_error _ -> output_string stderr "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n"


let deserialise_tableau_associatif fic =
    let rec trouver_espace chaine i = match chaine.[i] with
        | ' ' -> i
        | _ -> trouver_espace chaine (i+1) in
    let ta = Hashtbl.create 50 in (* taille arbitraire *)
    begin
        try
            let fichier = open_in fic in
            try
                while true do
                    let ligne = input_line fichier in
                    let indice_espace = trouver_espace ligne 0 in
                    let cle = String.sub ligne 0 indice_espace in
                    let valeur = String.sub ligne (indice_espace + 1) (String.length ligne - indice_espace - 1) in
                    Hashtbl.add ta (int_of_string cle) (int_of_string valeur)
                done
            with End_of_file -> close_in fichier
        with Sys_error _ -> output_string stderr "erreur lors de l'ouverture du fichier (vérifiez qu'il existe et que vous avez les droits)\n"
    end ;
    ta
