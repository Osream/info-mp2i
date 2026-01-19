type graphe = int array array
type chemin =int list


let exemple = 
  [|
    [|max_int; 2; max_int; max_int; max_int; 1; max_int; 1|];
    [|2; max_int; 1; max_int; 1; max_int; max_int; max_int|];
    [|max_int; 1; max_int; 1; max_int; max_int; max_int; 5|];
    [|max_int; max_int; 1; max_int; 2; max_int; 1; max_int|];
    [|max_int; 1; max_int; 2; max_int; 1; max_int; max_int|];
    [|1; max_int; max_int; max_int; 1; max_int; 2; max_int|];
    [|max_int; max_int; max_int; max_int; max_int; 2; 1; 1|];
    [|1; max_int; 5; max_int; max_int; max_int; 5; max_int|]
  |]


let rec supprimer k int_list =
  match int_list with
  | [] -> []
  | t::q when t = k -> supprimer k q
  | t::q -> t::(supprimer k q)


let rec poids_chemin_aux (g : graphe) (ch : chemin) aux = 
  match ch with
  | [] -> aux
  | t::[] -> aux
  | t1::t2::q -> if g.(t1).(t2) = max_int then
                  max_int
                else
                  poids_chemin_aux g (t2::q) (g.(t1).(t2) + aux)


let poids_chemin (g : graphe) (ch : chemin) =
  poids_chemin_aux g ch 0

let pvc (g : graphe) :chemin =
  let n = Array.length g in
  let min = ref max_int in
  let chemin_min = ref [] in

  let rec aux_pvc (grap: graphe) (c_tilde : chemin) taille_c_tilde =
    if taille_c_tilde = n then (
      if poids_chemin g c_tilde < !min then begin
        min := poids_chemin g c_tilde;
        chemin_min := c_tilde
      end
      )
    else (
      if poids_chemin grap c_tilde <= !min then
        for i = 0 to n-1 do
          if c_tilde = supprimer i c_tilde then
            aux_pvc grap (i::c_tilde) (taille_c_tilde + 1)
        done
      )
    in
  aux_pvc g [] 0;
  !chemin_min

