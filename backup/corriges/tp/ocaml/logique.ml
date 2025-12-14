(* CORRIGÉ DU TP : LOGIQUE PROPOSITIONNELLE *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Fonctions sur l'ensemble des formules propositionnelles *)

type formule =
	| Top
	| Bottom
	| Var of int
	| Non of formule
	| Ou of formule * formule
	| Et of formule * formule

let ex1 = Non (Ou (Et (Var 0, Var 1), Et (Var 0, Var 2)))
let ex2 = Ou (Et (Var 1, Bottom), Non (Var 3))
let ex3 = Et (Top, Non (Ou (Bottom, Et (Top, Non (Bottom)))))


(* Remarque : dans tout le code suivant, mes variables s'appellent
"f" pour la Formule initiale passée en paramètre,
"sf" pour la Sous Formule d'une négation, et
"sfg" et "sfd" pour les Sous Formule Gauche et Droite d'une conjonction ou disjonction. *)

let rec string_of_formule f = match f with
    (* Le parcours d'arbre qui donne la formule
       avec la syntaxe usuelle est le parcours infixe. *)
    | Top -> "⊤"
    | Bottom -> "⊥"
    | Var i -> "x_" ^ string_of_int i
    | Non sf -> "¬" ^ string_of_formule sf
    | Et (sfg, sfd) -> "(" ^ string_of_formule sfg ^ " ∧ " ^ string_of_formule sfd ^ ")"
    | Ou (sfg, sfd) -> "(" ^ string_of_formule sfg ^ " ∨ " ^ string_of_formule sfd ^ ")"

let nb_var_distinctes f =
    let variables = Hashtbl.create 20 in (* taille arbitraire *)
    let rec compte_variables f = match f with
        | Top | Bottom -> 0
        | Var i ->  (*  si on avait déjà croisé cette variable on ne la compte pas *)
                    if Hashtbl.mem variables i then
                        0
                    (*  sinon on indique qu'on l'a croisée et on la compte *)
                    else begin
                        Hashtbl.add variables i true ; (* valeur arbitraire *)
                        1
                    end
        | Non sf -> compte_variables sf
        | Et (sfg, sfd) | Ou (sfg, sfd) -> compte_variables sfg + compte_variables sfd
    in compte_variables f


let rec taille f = match f with
    | Non sf -> 1 + taille sf
    | Et (sfg, sfd) | Ou (sfg, sfd) -> 1 + taille sfg + taille sfd
    | _ -> 1

let rec hauteur f = match f with
    | Non sf -> 1 + hauteur sf
    | Et (sfg, sfd) | Ou (sfg, sfd) -> 1 + max (hauteur sfg) (hauteur sfd)
    | _ -> 0

let rec substitue phi x psi (* φ[ψ/x] *) = match phi with
    | Var i when i = x -> psi 
    | Non sf -> Non (substitue sf x psi)
    | Et (sfg, sfd) -> Et (substitue sfg x psi, substitue sfd x psi)
    | Ou (sfg, sfd) -> Ou (substitue sfg x psi, substitue sfd x psi)
    | _ -> phi

let rec ensemble_sous_formules f = match f with
    | Top | Bottom | Var _ -> [f]
    | Non sf -> f :: ensemble_sous_formules sf
    | Et (sfg, sfd) | Ou (sfg, sfd) -> f :: ensemble_sous_formules sfg @ ensemble_sous_formules sfd

let sous_formule f sf =
    List.mem sf (ensemble_sous_formules f)


(* --------------------------------------------------------- *)

(* Sémantique des formules propositionnelles *)

type valuation = bool array


let rec max_var f = match f with
    | Var i -> Some i
    | Non sf -> max_var sf
    | Et (sfg, sfd) | Ou (sfg, sfd) -> max (max_var sfg) (max_var sfd)
    | _ -> None

let peut_etre_evaluee f (v : valuation) = match max_var f with
    | None -> true
    | Some i -> i < Array.length v


let rec satisfait f (v : valuation) = match f with
    | Top -> true
    | Bottom -> false
    | Var i -> v.(i)
    | Non sf -> not (satisfait sf v)
    | Et (sfg, sfd) -> satisfait sfg v && satisfait sfd v
    | Ou (sfg, sfd) -> satisfait sfg v || satisfait sfd v

let rec consequence phi psi valuations (* φ ⊨ ψ *) = match valuations with
    | [] -> true
    (* toute valuation qui satisfait φ doit satisfaire ψ *)
    | t::q -> (if satisfait phi t then satisfait psi t else true) && consequence phi psi q

let equivalence phi psi valuations =
    consequence phi psi valuations && consequence psi phi valuations


let double_negation =
    equivalence (Var 0)
                (Non (Non (Var 0)))
                [[|false|]; [|true|]]
let premiere_loi_de_De_Morgan =
    equivalence (Non (Et (Var 0, Var 1)))
                (Ou (Non(Var 0), Non(Var 1)))
                [[|false;false|]; [|false;true|]; [|true;false|]; [|true;true|]]
let deuxieme_loi_de_De_Morgan =
    equivalence (Non (Ou (Var 0, Var 1)))
                (Et (Non(Var 0), Non(Var 1)))
                [[|false;false|]; [|false;true|]; [|true;false|]; [|true;true|]]


let quantificateur_universel x phi =
    Et (substitue phi x Top, substitue phi x Bottom)

let quantificateur_existentiel x phi =
    Ou (substitue phi x Top, substitue phi x Bottom)


(* --------------------------------------------------------- *)

(* Problème SAT *)

type arbre_quine =
    | Feuille of bool
    | Branchement of int * arbre_quine * arbre_quine


let rec elimine_constantes (f : formule) : formule = match f with
    | Non sf ->
        (match elimine_constantes sf with
            | Top -> Bottom
            | Bottom -> Top
            | sf' -> Non sf')
    | Et (sfg, sfd) ->
        (match elimine_constantes sfg, elimine_constantes sfd with
            | Top, sf' | sf', Top -> sf'
            | Bottom, _| _, Bottom -> Bottom
            | sfg', sfd' -> Et (sfg', sfd'))
    | Ou (sfg, sfd) ->
        (match elimine_constantes sfg, elimine_constantes sfd with
            | Top, _ | _, Top -> Top
            | Bottom, sf'| sf', Bottom -> sf'
            | sfg', sfd' -> Ou (sfg', sfd'))
    | _ -> f

let rec quine f = match elimine_constantes f with
    | Top -> Feuille true
    | Bottom -> Feuille false
    | f' -> match max_var f' with (* variable arbitraire, je choisis la plus grande *)
                | Some x -> Branchement (x, quine (substitue f' x Bottom), quine (substitue f' x Top))
                | None -> failwith "d'après les règles d'élimination, on n'arrivera jamais ici"


let satisfiable_quine f =
    (* fonction auxiliaire cherchant une feuille ⊤ dans l'arbre de Quine *)
    let rec existe_feuille_top arbre = match arbre with
        | Feuille f -> f
        | Branchement (_, sag, sad) -> existe_feuille_top sag || existe_feuille_top sad
    in existe_feuille_top (quine f)

let valuation_quine f =
    (* on crée la valuation, arbitrairement remplie de false pour commencer *)
    let taille_valuation = match max_var f with
        | Some i -> i + 1
        | None -> 0
    in let v = Array.make taille_valuation false in
    (* fonction auxiliaire cherchant une feuille ⊤ dans l'arbre de Quine *)
    let rec existe_feuille_top arbre = match arbre with
        | Feuille f -> f
        | Branchement (x, sag, sad) ->
            (match existe_feuille_top sag, existe_feuille_top sad with
                (* on regarde de quel côté de l'arbre se situe la feuille ⊤
                   pour savoir quelle valeur de vérité associer à la variable x *)
                | true, _ -> v.(x) <- false ; true
                | _, true -> v.(x) <- true ; true
                | _ -> false)
    in if existe_feuille_top (quine f) then Some v else None


let tautologie_quine f =
    (* une formule est une tautologie ssi toutes les feuilles de l'arbre de Quine valent ⊤ *)
    let rec toutes_feuilles_top arbre = match arbre with
        | Feuille f -> f
        | Branchement (x, sag, sad) -> toutes_feuilles_top sag && toutes_feuilles_top sad
    in toutes_feuilles_top (quine f)

let antilogie_quine f =
    (* on pourrait vérifier que toutes les feuilles de l'arbre de Quine sont ⊥, mais je choisis
       ici d'utiliser le fait qu'une formume est antilogique ssi elle n'est pas satisfiable *)
    not (satisfiable_quine f)


(* La formule présentée dans le TP est ((a ∨ b) ∧ (¬b ∨ ¬c)) ∧ ((¬a ∨ c) ∧ (a ∨ c))
   Je pose c = Var 0, b = Var 1, a = Var 2 afin d'obtenir le même arbre de Quine que celui du TP.
*)
let (exemple : formule) =   Et  (   Et  (   Ou (Var 2, Var 1),
                                            Ou (Non (Var 1), Non (Var 0))
                                        ),
                                    Et  (   Ou (Non (Var 2), Var 0),
                                            Ou (Var 2, Var 0)
                                        )
                                )
(* Le calcul de l'arbre de Quine à la main nous permet d'établir les tests suivants : *)
let _ =
    assert (satisfiable_quine exemple) ;
    assert (not (tautologie_quine (exemple))) ;
    assert (valuation_quine exemple = Some [|true; false; true|])


(* --------------------------------------------------------- *)

(* Exercices *)


(* exo 1 : portée des variables *)

type 'a formule_complete =
	| Top
	| Bottom
	| Var of 'a
	| Non of 'a formule_complete
    | Et of 'a formule_complete * 'a formule_complete
	| Ou of 'a formule_complete * 'a formule_complete
    | Imp of 'a formule_complete * 'a formule_complete
    | Equiv of 'a formule_complete * 'a formule_complete
    | Pour_tout of 'a * 'a formule_complete
    | Il_existe of 'a * 'a formule_complete

let ex_complet = Pour_tout ('x',   Imp (Il_existe ('y',  Equiv (Et (Var 'x', Var 'y'),
                                                                Var 'y')),
                                        Equiv (Var 'x', Top)))
                         
let rec est_liee f var = match f with
    | Non sf -> est_liee sf var
    | Et (sfg, sfd) | Ou (sfg, sfd) | Imp (sfg, sfd) | Equiv (sfg, sfd) -> est_liee sfg var || est_liee sfd var
    | Pour_tout (x, sf) | Il_existe (x, sf) -> x = var || est_liee sf var
    | _ -> false

let rec est_libre f var = match f with
    | Var x -> x = var
    | Pour_tout (x, sf) | Il_existe (x, sf) -> x <> var && est_libre sf var
    | Non sf -> est_libre sf var
    | Et (sfg, sfd) | Ou (sfg, sfd) | Imp (sfg, sfd) | Equiv (sfg, sfd) -> est_libre sfg var || est_libre sfd var
    | _ -> false

let rec portee f (b, i) = match f with
    | Pour_tout (x, sf) when b && x = i -> Some sf
    | Il_existe (x, sf) when (not b) && x = i -> Some sf
    | Non sf | Pour_tout (_, sf) | Il_existe (_, sf) -> portee sf (b, i)
    | Et (sfg, sfd) | Ou (sfg, sfd) | Imp (sfg, sfd) | Equiv (sfg, sfd) -> 
            (match portee sfg (b, i), portee sfd (b, i) with
                | None, portee_sfd -> portee_sfd
                | portee_sfg, _ -> portee_sfg)
    | _ -> None


(* exo 2 : résolution par force brute du problème SAT *)

exception Derniere_valuation
exception Break

let valuation_suivante (v : valuation) : unit =
    let i = ref (Array.length v - 1) in
    while !i >= 0 && v.(!i) do
        v.(!i) <- false ;
        decr i
    done ;
    if !i < 0 then
        (* tout valait true, v était la dernière valuation *)
        raise Derniere_valuation
    else
        v.(!i) <- true

let satisfiable_brute f =
    (* On commence par la valuation associant la valeur de vérité F à toutes les variables *)
    let taille_valuation = match max_var f with
        | Some i -> i + 1
        | None -> 0
    in let v = Array.make taille_valuation false in
    (* On vérifie successivement chaque valuation existante *)
    try while true do
        if satisfait f v then
            raise Break
        else
            valuation_suivante v
    done with
        (* sortie de boucle par Break = on a trouvé une valuation qui satisfait f *)
        | Break -> true
        (* sortie de boucle par Derniere_valuation = on a tout regardé, f n'a pas de modèle *)
        | Derniere_valuation -> false

let tautologie_brute f =
    (* On commence par la valuation associant la valeur de vérité F à toutes les variables *)
    let taille_valuation = match max_var f with
        | Some i -> i + 1
        | None -> 0
    in let v = Array.make taille_valuation false in
    (* On vérifie successivement chaque valuation existante *)
    try while true do
        if not (satisfait f v) then
            raise Break
        else
            valuation_suivante v
    done with
        (* sortie de boucle par Break = on a trouvé une valuation qui ne satisfait pas f *)
        | Break -> false
        (* sortie de boucle par Derniere_valuation = toutes les valuations sont des modèles *)
        | Derniere_valuation -> true

let antilogie_brute f =
    not (satisfiable_brute f)
