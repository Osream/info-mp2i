type matrice_adjacence = int array array

let mat_go = [| [|0; 1; 0; 0; 0; 0; 0; 0; 0|];
[|1; 0; 0; 1; 0; 0; 0; 0; 0|];
[|0; 0; 0; 0; 1; 1; 0; 0; 0|];
[|0; 0; 0; 0; 0; 0; 0; 0; 0|];
[|1; 0; 0; 0; 0; 0; 0; 0; 1|];
[|1; 0; 1; 1; 1; 0; 1; 0; 0|];
[|0; 0; 1; 0; 0; 0; 0; 0; 0|];
[|0; 0; 0; 0; 0; 0; 1; 0; 0|];
[|0; 0; 0; 0; 0; 0; 0; 0; 0|] |]

let nb_sommets_arcs mat = 
  let taille = Array.length mat and
  somme = ref 0 in
  for i = 0 to taille -1 do 
    for j = 0 to taille -1 do 
      somme := !somme + mat.(i).(j)
    done
  done;
  (taille, !somme)

let possede_boucle mat =
  try
    for i = 0 to Array.length mat -1 do 
      if mat.(i).(i) = 1 then
        raise Exit
    done;
    false
  with Exit -> true

let est_successeur mat j i = 
  if mat.(i).(j) = 1 then
    true
  else
    false

let est_predecesseur mat i j = est_successeur mat j i

let degres mat i =
  let d_plus = ref 0 and d_moins = ref 0 in
  for j = 0 to Array.length mat -1 do 
    d_plus := !d_plus + mat.(i).(j);
    d_moins := !d_moins + mat.(j).(i)
  done;
  d_moins, d_plus

(*Partie 2*)

type liste_adjacence = int list array

let rec taille_liste l =
  match l with
  | [] -> 0
  | t::q -> 1 + taille_liste q

let nb_arretes lst = 
  let degre = ref 0 in
  for i = 0 to Array.length lst -1 do 
    degre := !degre + taille_liste lst.(i)
  done;
  (!degre/2)

let sont_voisins lst i j = List.mem j lst.(i)

let degre lst i = taille_liste lst.(i)

let verifie_orientation (g : liste_adjacence) =
  let est_gno = ref true in
  for si = 0 to Array.length g - 1 do
      est_gno := !est_gno && List.for_all (fun sj -> List.mem si g.(sj)) g.(si)
  done ;
  !est_gno
  

let sommet_degre_max (g : liste_adjacence) =
  let res = ref (-1) in
  let degre_res = ref min_int in
  for sommet = 0 to Array.length g - 1 do
      let degre_sommet = degre g sommet in
      if degre_sommet > !degre_res then begin
          degre_res := degre_sommet ;
          res := sommet
      end
  done ;
  !res

(* Sérialisation *)

let decompose_arc (arc : string) =
  let indice_virgule = ref 0 in
  while arc.[!indice_virgule] != ',' do incr indice_virgule done ;
  let avant_virgule = String.sub arc 0 !indice_virgule in
  let apres_virgule = String.sub arc (!indice_virgule + 1) (String.length arc - !indice_virgule - 1) in
  int_of_string avant_virgule, int_of_string apres_virgule

let serialise_mat (g : matrice_adjacence) nom_fichier =
  let nb_sommets = Array.length g in
  let fichier = open_out nom_fichier in
  output_string fichier (string_of_int nb_sommets ^ "\n") ;
  for i = 0 to nb_sommets - 1 do
      for j = 0 to nb_sommets - 1 do
          if g.(i).(j) = 1 then
              output_string fichier (string_of_int i ^ "," ^ string_of_int j ^ "\n")
      done
  done ;
  close_out fichier

let deserialise_mat nom_fichier : matrice_adjacence =
  let fichier = open_in nom_fichier in
  let nb_sommets = int_of_string (input_line fichier) in
  let g = Array.make_matrix nb_sommets nb_sommets 0 in
  try while true do
      let i, j = decompose_arc (input_line fichier) in
      g.(i).(j) <- 1
  done with End_of_file -> close_in fichier ;
  g

let serialise_lst (g : liste_adjacence) nom_fichier =
  let nb_sommets = Array.length g in
  let fichier = open_out nom_fichier in
  output_string fichier (string_of_int nb_sommets ^ "\n") ;
  for i = 0 to nb_sommets - 1 do
      List.iter (fun j -> output_string fichier (string_of_int i ^ "," ^ string_of_int j ^ "\n")) g.(i)
  done ;
  close_out fichier

let deserialise_lst nom_fichier : liste_adjacence =
  let fichier = open_in nom_fichier in
  let nb_sommets = int_of_string (input_line fichier) in
  let g = Array.make nb_sommets [] in
  try while true do
      let i, j = decompose_arc (input_line fichier) in
      g.(i) <- j::g.(i)
  done with End_of_file -> close_in fichier ;
  g



  