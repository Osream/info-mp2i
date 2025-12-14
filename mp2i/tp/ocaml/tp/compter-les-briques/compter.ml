let rec nombre_rangees_non_efficace n =
  match n with
  | 1 -> 0
  | 0 -> 1
  | n -> nombre_rangees_non_efficace (n-2) + nombre_rangees_non_efficace (n-3)

let nombre_rangees_top_down n =
  let mem = Array.make (n+1) (-1) in 
  let rec nbre_aux n =
    match n with
    | n when mem.(n) <> -1 -> mem.(n)
    | 1 -> mem.(n) <- 0; 0
    | 0 | 2 -> mem.(n) <- 1; 1
    | n -> let res = nbre_aux (n-2) + nbre_aux (n-3) in 
  mem.(n) <- res; res
  in nbre_aux n

let nombre_rangees_bottom_up n = 
  let array_mem = Array.make (n+1) (-1) in 
  array_mem.(0) <- 1;
  array_mem.(2) <- 1;
  array_mem.(1) <- 0;
  for i = 3 to n do 
    array_mem.(i) <- array_mem.(i-2) + array_mem.(i-3)
  done;
  array_mem.(n)

(*n'est pas correcte à revoir (j'ai pas le temps)*)
let nb_rangees n = 
  let rec pair_aux n res_pair res_impair =
    match n with
    | 0 -> res_pair
    | 2 -> res_pair
    | n -> impair_aux (n-1) res_pair (res_impair + res_pair)
  and impair_aux n res_pair res_impair =
    match n with
    | 1 -> res_impair
    | n -> pair_aux (n-1) (res_impair + res_pair) res_impair
  in match n with
  | n when n mod 2 = 0 -> pair_aux n 1 0
  | n -> impair_aux n 1 0

(*reviens à placer la dermarcation (+1) et déplacer le nombre binaire de 2 vers la gauche*)
let plus2 ligne = (ligne+1)*4

let plus3 ligne = (ligne+1)*8

let rec ajout_brique n nbre_liste = 
  match n, nbre_liste with
  | _, [] -> []
  | 2, t::q -> (plus2 t)::(ajout_brique q)
  | 3, t::q -> (plus3 t)::(ajout_brique q)
  | _, _ -> failwith "L'entier doit être égal à 2 ou 3"²

let _ = 
  print_int (nombre_rangees_bottom_up 75);
  print_newline ();
  print_int (nb_rangees 75);
  print_newline ();
