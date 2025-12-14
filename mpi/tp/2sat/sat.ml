type clause = int * int
type formule = clause list
type valuation = int array
type sommets = int list
type graphe = sommets array


(* Création d'une formule aléatoire *)
let alea n =
  let i = 1 + Random.int n in
  if Random.int 2 = 0 then i else -i

let formule nbvars nbclauses seed : formule =
  Random.init seed;
  List.init nbclauses (fun _ -> (alea nbvars, alea nbvars))

let f0 = formule 25 41 569527135 

let f1 = formule 25 41 460731 

let m1 = [|0; -1; 2; 3; 4; -5; -6; 7; -8; -9; -10; -11; 12; -13; 14; 15; 16; -17; 18; 19; -20; 21; 22; -23; -24; 25|]

let f2 = formule 250 300 3

let f3 = formule 4 10 4727


(* fin du squelette *)

let check_clause (v:valuation) (c:clause) : bool = 
  let i1, i2 = c in
  v.(abs i1) = i1 || v.(abs i2) = i2

let rec interpretation (f:formule) (v:valuation) : bool =
  match f with
  | [] -> failwith "la clause est vide"
  | [t] -> check_clause v t
  | t::q -> check_clause v t && interpretation q v

let rec ajouter_liste lst elt =
  match lst with
  | [] -> [elt]
  | t::q when t = elt -> t::q
  | t::q -> t::(ajouter_liste q elt)

let graphe (f:formule) (n:int) : graphe =
  let g = Array.make (2*n + 1) ([]) in
  let rec parcour_form_aux (form:formule) =
    match form with
    | [] -> ()
    | (l1, l2)::q -> g.(n - l1) <- ajouter_liste g.(n - l1) (n + l2);
                     g.(n - l2) <- ajouter_liste g.(n - l2) (n + l1);
                     parcour_form_aux q
  in
  parcour_form_aux f;
  g

let graphe_t (f:formule) (n:int) : graphe =
  let g = Array.make (2*n + 1) ([]) in
  let rec parcour_form_aux (form:formule) =
    match form with
    | [] -> ()
    | (l1, l2)::q -> g.(n + l1) <- ajouter_liste g.(n + l1) (n - l2);
                     g.(n + l2) <- ajouter_liste g.(n + l2) (n - l1);
                     parcour_form_aux q
  in
  parcour_form_aux f;
  g

let print_graphe (g :graphe) =
  let nb_litt = Array.length g / 2 in
  let rec print_sommets (s: sommets) (n : int) =
    match s with
    | [] -> print_char ']';
          print_newline ()
    | t::[] ->print_int (t-n);
              print_sommets [] n
    | t::q ->print_int (t-n);
              print_string ";\t";
              print_sommets q n
  in
  for i = 0 to Array.length g - 1 do
    print_int (i-nb_litt);
    print_string "\t:\t[";
    print_sommets g.(i) nb_litt
  done

let rec explorer (lst : int list ref) (g: graphe) (vu : bool array) (s : int) =
  if not vu.(s) then begin
    vu.(s) <- true;
    List.iter (explorer lst g vu) g.(s);
    lst := !lst @ [s]
  end

let opi (g:graphe) (s:sommets) : sommets =
  let vu = Array.make (Array.length g) false 
  and res = ref [] in
  let rec parcours_somm (som_lst :sommets) =
    match som_lst with
    | [] -> ()
    | t::q -> explorer res g vu t;
            parcours_somm q
  in
  parcours_somm s;
  List.rev !res

let kosaraju_2sat (f:formule) (n:int) =
  let g = graphe f n
  and g_t = graphe_t f n
  in
  let opi1 = opi g_t (List.init (2*n) (fun i -> match i with | p when p < n ->p | _ -> i+1)) in
  opi g opi1

let model (op : sommets) :int array =
  let n = ((List.length op)/2) in
  let res = Array.make (n+1) 0 in
  let rec parcours_op (s: sommets) =
    match s with
    | [] -> ()
    | t::q -> if res.(abs (t-n)) == 0 then
                  res.(abs (t-n)) <- t-n;
              parcours_op q
  in
  parcours_op op;
  res
