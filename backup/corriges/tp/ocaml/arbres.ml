(* CORRIGÉ PARTIEL DU TP : ARBRES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)



(* --------------------------------------------------------- *)


(* Fonctions élémentaires sur les arbres binaires *)



(* arbres binaires stricts *)

type ('i, 'f) ab_strict =
	| Feuille of 'f
	| Noeud of 'i * ('i, 'f) ab_strict * ('i, 'f) ab_strict

let rec hauteur arbre = match arbre with
    | Feuille _ -> 0
    | Noeud (_, g, d) -> 1 + max (hauteur g) (hauteur d)

let rec taille arbre = match arbre with
    | Feuille _ -> 1
    | Noeud (_, g, d) -> 1 + taille g + taille d

let rec nb_feuilles arbre = match arbre with
    | Feuille _ -> 1
    | Noeud (_, g, d) -> nb_feuilles g + nb_feuilles d

let rec nb_noeuds_internes arbre = match arbre with
    | Feuille _ -> 0
    | Noeud (_, g, d) -> 1 + nb_noeuds_internes g + nb_noeuds_internes d

let rec appartient arbre etiq = match arbre with
    | Feuille e -> e = etiq
    | Noeud (e, g, d) -> e = etiq || appartient g etiq || appartient d etiq

    

(* arbres binaires non stricts *)

type 'e ab =
	| Vide
	| N of 'e * 'e ab * 'e ab

let rec hauteur2 arbre = match arbre with
    | Vide -> -1
    | N (_, g, d) -> 1 + max (hauteur2 g) (hauteur2 d)

let rec taille2 arbre = match arbre with
    | Vide -> 0
    | N (_, g, d) -> 1 + taille2 g + taille2 d

let rec nb_feuilles2 arbre = match arbre with
    | Vide -> 0
    | N (_, Vide, Vide) -> 1
    | N (_, g, d) -> nb_feuilles2 g + nb_feuilles2 d

let rec nb_noeuds_internes2 arbre = match arbre with
    | Vide | N (_, Vide, Vide)  -> 0
    | N (_, g, d) -> 1 + nb_noeuds_internes2 g + nb_noeuds_internes2 d

let rec appartient2 arbre etiq = match arbre with
    | Vide -> false
    | N (e, g, d) -> e = etiq || appartient2 g etiq || appartient2 d etiq



(* strict / non strict *)

let rec est_strict arbre = match arbre with
    | Vide -> false
    | N(_, Vide, Vide) -> true
    | N (_, _, Vide) | N (_, Vide, _) -> false
    | N(_, g, d) -> est_strict g && est_strict d

let rec egaux_strict_et_non_strict strict non_strict = match strict, non_strict with
    | Feuille f, N (e, Vide, Vide) -> f = e
    | Noeud (e1, g1, d1), N (e2, g2, d2) -> e1 = e2 && egaux_strict_et_non_strict g1 g2 && egaux_strict_et_non_strict d1 d2
    | _ -> false



(* --------------------------------------------------------- *)


(* Fonctions élémentaires sur les arbres d'arité quelconque *)


type 'a arbre_aq = {etiquette : 'a ; fils : 'a arbre_aq list}



(* fonctions de base *)

let taille3 arbre =
    (* fonction auxiliaire qui calcule la taille totale d'une forêt d'arbres *)
    let rec taille_foret foret = match foret with
        | [] -> 0
        | t::q -> (1 + taille_foret t.fils) (* taille de t *) + taille_foret q (* taille du reste *)
    in taille_foret [arbre]

let hauteur3 arbre =
    (* fonction auxiliaire qui calcule la hauteur maximale des arbres d'une forêt *)
    let rec hauteur_foret foret = match foret with
        | [] -> -1
        | t::q -> max (1 + hauteur_foret t.fils) (* hauteur de t *) (hauteur_foret q) (* hauteur du reste *)
    in hauteur_foret [arbre]

let arite arbre =
    (* fonction auxiliaire qui calcule l'arité maximale des arbres d'une forêt *)
    let rec arite_foret foret = match foret with
        | [] -> -1
        | t::q -> max (max (List.length t.fils) (arite_foret t.fils) (* arité de t *)) (arite_foret q) (* arité du reste *)
    in arite_foret [arbre]

(* pour retrouver une complexité linéaire en la taille de l'arbre,
on peut enlever l'appel à List.length et calculer la taille également
dans la fonction auxiliaire : *)
let arite2 arbre =
    let rec length_et_arite_foret foret = match foret with
        | [] -> 0, -1
        | t::q ->   let length_q, arite_max_q = length_et_arite_foret q in 
                    let length_fils_t, arite_max_fils_t = length_et_arite_foret t.fils in 
                    1 + length_q, max (max length_fils_t arite_max_fils_t) arite_max_q
    in snd (length_et_arite_foret [arbre])

let egaux arbre1 arbre2 =
    (* fonction auxiliaire qui détermine si deux forêts sont égales *)
    let rec egaux_foret foret1 foret2 = match foret1, foret2 with
        | [], [] -> true
        | t1::q1, t2::q2 -> t1.etiquette = t2.etiquette && egaux_foret t1.fils t2.fils && egaux_foret q1 q2
        | _ -> false
    in egaux_foret [arbre1] [arbre2]



(* représentation LCRS *)

let binarise arbre =
    let rec aux foret = match foret with
        | [] -> Vide
        | t::q -> N (t.etiquette, aux t.fils, aux q)
    in aux [arbre]

let debinarise arbre =
    let rec aux arbre = match arbre with
        | Vide -> []
        | N (e, g, d) -> {etiquette = e; fils = aux g} :: aux d
    in List.hd (aux arbre)  



(* types alternatifs si les arbres peuvent être vides *)

type 'e arbre_aq_v2 = 'e arbre_aq option

type 'e arbre_aq_v3 =
    | Empty
    | Node of 'e * 'e arbre_aq_v3 list



(* --------------------------------------------------------- *)


(* Parcours *)



(* parcours en largeur avec affichage des étiquettes *)

let largeur_strict arbre =
    let file = Queue.create () in
    Queue.push arbre file ;
    while not (Queue.is_empty file) do
        match Queue.pop file with
            | Feuille f -> print_int f ; print_string " "
            | Noeud (e, g, d) ->    print_int e ;
                                    print_string " " ;
                                    Queue.push g file ;
                                    Queue.push d file
    done

let largeur_non_strict arbre =
    let file = Queue.create () in
    Queue.push arbre file ;
    while not (Queue.is_empty file) do
        match Queue.pop file with
            | Vide -> ()
            | N (e, g, d) ->    print_int e ;
                                print_string " " ;
                                Queue.push g file ;
                                Queue.push d file
    done

let largeur arbre =
    let file = Queue.create () in
    Queue.push arbre file ;
    while not (Queue.is_empty file) do
        let a = Queue.pop file in
        print_int a.etiquette ;
        print_string " " ;
        List.iter (fun f -> Queue.push f file) a.fils
    done



(* parcours en profondeur avec affichage des étiquettes *)

let rec profondeur_prefixe_strict arbre = match arbre with
    | Feuille f -> print_int f ; print_string " "
    | Noeud (e, g, d) ->    print_int e ;
                            print_string " " ;
                            profondeur_prefixe_strict g ;
                            profondeur_prefixe_strict d

let rec profondeur_infixe_strict arbre = match arbre with
    | Feuille f -> print_int f ; print_string " "
    | Noeud (e, g, d) ->    profondeur_infixe_strict g ;
                            print_int e ;
                            print_string " " ;
                            profondeur_infixe_strict d

let rec profondeur_postfixe_strict arbre = match arbre with
    | Feuille f -> print_int f ; print_string " "
    | Noeud (e, g, d) ->    profondeur_postfixe_strict g ;
                            profondeur_postfixe_strict d ;
                            print_int e ;
                            print_string " "

let rec profondeur_prefixe_non_strict arbre = match arbre with
    | Vide -> ()
    | N (e, g, d) ->    print_int e ;
                        print_string " " ;
                        profondeur_prefixe_non_strict g ;
                        profondeur_prefixe_non_strict d

let rec profondeur_infixe_non_strict arbre = match arbre with
    | Vide -> ()
    | N (e, g, d) ->    profondeur_infixe_non_strict g ;
                        print_int e ;
                        print_string " " ;
                        profondeur_infixe_non_strict d

let rec profondeur_postfixe_non_strict arbre = match arbre with
    | Vide -> ()
    | N (e, g, d) ->    profondeur_postfixe_non_strict g ;
                        profondeur_postfixe_non_strict d ;
                        print_int e ;
                        print_string " "

let rec profondeur_prefixe arbre =
    print_int arbre.etiquette ;
    print_string " " ;
    List.iter profondeur_prefixe arbre.fils

let rec profondeur_postfixe arbre =
    List.iter profondeur_postfixe arbre.fils ;
    print_int arbre.etiquette ;
    print_string " "



(* versions alternatives des parcours d'arbres binaires renvoyant les étiquettes dans une liste *)

let rec profondeur_prefixe_liste_strict arbre = match arbre with
    | Feuille f -> [f]
    | Noeud (e, g, d) -> e :: profondeur_prefixe_liste_strict g @ profondeur_prefixe_liste_strict d

let rec profondeur_infixe_liste_strict arbre = match arbre with
    | Feuille f -> [f]
    | Noeud (e, g, d) -> profondeur_infixe_liste_strict g @ (e :: profondeur_infixe_liste_strict d)

let rec profondeur_postfixe_liste_strict arbre = match arbre with
    | Feuille f -> [f]
    | Noeud (e, g, d) -> profondeur_postfixe_liste_strict g @ profondeur_postfixe_liste_strict d @ [e]

let largeur_liste_strict arbre =
    (* Remarque :
    J'ai choisi de remplacer le « while not (Queue.is_empty file) »
    par une fonction récursive (avec appels récursifs tant que la file n'est pas vide),
    simplement car la boucle imposerait de faire une référence vers une liste
    pour la remplir au fur et à mesure de la boucle while...
    et il faut *vraiment* éviter les références vers des structures non mutables !
    *)
    let file = Queue.create () in
    Queue.push arbre file ;
    let rec aux file =
        if (Queue.is_empty file) then
            []
        else match Queue.pop file with
            | Feuille f -> f :: aux file
            | Noeud (e, g, d) -> Queue.push g file ; Queue.push d file ; e :: aux file in
    aux file

(*  À cause de l'usage de l'opérateur de concaténation @,
    les complexités des parcours en profondeur sur les arbres binaires
    quand on renvoie une liste d'étiquettes sont quadratiques en la taille de l'arbre
    (au lieu de linéaire en la taille de l'arbre quand on affiche juste).
    Le parcours en largeur par contre garde la même complexité puisqu'on utilise
    uniquement le constructeur :: qui a une complexité constante. *)



(* versions alternatives des parcours d'abres d'arité quelconque renvoyant les étiquettes dans une liste *)

(* fonction auxiliaire qui prend en paramètre une liste contenant des listes [l1; l2; l3; ...]
   et les concatène en une seule liste l1 @ l2 @ l3 @ ... *)
let rec concat l = match l with
   | [] -> []
   | t::q -> t @ concat q

let rec profondeur_prefixe_liste arbre =
   arbre.etiquette :: concat (List.map profondeur_prefixe_liste arbre.fils)

let rec profondeur_postfixe_aq_liste arbre =
   concat (List.map profondeur_postfixe_aq_liste arbre.fils) @ [arbre.etiquette]

let largeur_aq_liste arbre =
   let file = Queue.create () in
   Queue.push arbre file ;
   (* Mêmes problèmes que pour les arbres binaires avec la boucle while,
      je préfère donc utiliser de la récursivité. *)
   let rec aux file =
       if (Queue.is_empty file) then
           []
       else begin
           let a = Queue.pop file in
           List.iter (fun f -> Queue.push f file) a.fils ;
           a.etiquette :: aux file
       end in
   aux file



(* sérialisation d'arbres binaires stricts *)

let serialise_avec_prefixe arbre nom_fichier =
    let fichier = open_out nom_fichier in
    let rec prefixe arbre = match arbre with
        | Feuille f ->      output_string fichier "0\n" ;
                            output_string fichier (f ^ "\n")
        | Noeud(e, g, d) -> output_string fichier "1\n" ;
                            output_string fichier (e ^ "\n") ;
                            prefixe g ;
                            prefixe d in
    prefixe arbre ;
    close_out fichier

let deserialise_depuis_prefixe nom_fichier =
    let fichier = open_in nom_fichier in
    let rec prefixe () =
        let est_feuille = input_line fichier in
        let etiquette = input_line fichier in
        if est_feuille = "0" then
            Feuille etiquette
        else begin
            let g = prefixe () in
            let d = prefixe () in
            Noeud (etiquette, g, d) 
        end in
    let arbre = prefixe () in
    close_in fichier ;
    arbre
