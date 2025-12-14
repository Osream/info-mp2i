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

let rec string_of_formule (form :formule) = 
  match form with
  | Top -> "⊤"
	| Bottom -> "⊥"
	| Var n -> "x_" ^ (string_of_int n)
	| Non f -> "¬" ^(string_of_formule f)
	| Ou (f1, f2) -> "(" ^ (string_of_formule f1) ^ " ∨ " ^ (string_of_formule f2) ^ ")"
	| Et (f1, f2) -> "(" ^ (string_of_formule f1) ^ " ∧ " ^ (string_of_formule f2) ^ ")"

let rec nb_var_distinctes (form : formule) = (*ne fonctionne pas*)
  match form with
  | Top -> 0
	| Bottom -> 0
	| Var n -> 1
	| Non f -> nb_var_distinctes f 
	| Ou (f1, f2) -> nb_var_distinctes f1 + nb_var_distinctes f2
	| Et (f1, f2) -> nb_var_distinctes f1 + nb_var_distinctes f2

let rec taille (form : formule) =
  match form with
  | Top -> 1
	| Bottom -> 1
	| Var n -> 1
	| Non f -> 1 + taille f 
	| Ou (f1, f2) -> 1 + taille f1 + taille f2
	| Et (f1, f2) -> 1 + taille f1 + taille f2

let rec hauteur (form : formule) =
  match form with
  | Top -> 0
	| Bottom -> 0
	| Var n -> 0
	| Non f -> 1 + hauteur f
	| Ou (f1, f2) -> 1 + max (hauteur f1) (hauteur f2)
	| Et (f1, f2) -> 1 + max (hauteur f1)  (hauteur f2)

let rec substitution (form : formule) n (psi : formule) =
  match form with
	| Var n1 when n1 = n -> psi
	| Non f -> Non (substitution f n psi)
	| Ou (f1, f2) -> Ou ((substitution f1 n psi), (substitution f2 n psi))
	| Et (f1, f2) -> Et ((substitution f1 n psi), (substitution f2 n psi))
  | _ -> form

let rec ensemble_sous_formule (form : formule) =
  match form with
	| Non f -> (Non f)::(ensemble_sous_formule f)
	| Ou (f1, f2) -> (Ou (f1,f2))::(ensemble_sous_formule f1) @ (ensemble_sous_formule f2)
	| Et (f1, f2) -> (Et (f1,f2))::(ensemble_sous_formule f1) @ (ensemble_sous_formule f2)
  | _ -> [form]

let sous_formule (sous_form : formule) (form : formule) =
  let form_list = ensemble_sous_formule form and
  booleen = ref false in
  let egalite form1 = booleen := !booleen || form1 = form in
  List.iter egalite form_list;
  !booleen

type valuation = bool array

let rec max_var (form : formule) = 
  match form with
  | Top -> None
	| Bottom -> None
	| Var n -> Some n
	| Non f -> max_var f
	| Ou (f1, f2) -> max (max_var f1) (max_var f2)
	| Et (f1, f2) -> max (max_var f1) (max_var f2)

let rec peut_etre_evaluee (form : formule) (v : valuation) = 
  match form with
  | Top -> true
	| Bottom -> true
	| Var n ->  n < Array.length v
	| Non f -> peut_etre_evaluee f v
	| Ou (f1, f2) -> peut_etre_evaluee f1 v && peut_etre_evaluee f2 v
	| Et (f1, f2) -> peut_etre_evaluee f1 v && peut_etre_evaluee f2 v

let satisfait (form : formule) (v : valuation) =
  if peut_etre_evaluee form v then
    let rec parcours form valuation =
      match form with
      | Top -> true
    	| Bottom -> false
	    | Var n ->  v.(n)
	    | Non f -> not (parcours f v)
	    | Ou (f1, f2) -> parcours f1 v || parcours f2 v
	    | Et (f1, f2) -> parcours f1 v && parcours f2 v
    in
    parcours form v
  else
    false

let consequence (phi : formule) (psi : formule) v_list =
  let booleen = ref true in
  let parcours v =
    if (satisfait phi v) then
      booleen := !booleen && (satisfait psi v)
    in
  List.iter parcours v_list;
  !booleen

let equivalence (phi : formule) (psi : formule) v_list =
  consequence phi psi v_list && consequence psi phi v_list

