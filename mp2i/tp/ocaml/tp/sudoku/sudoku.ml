type case = V | C of int

exception Solution

type grille = case array array

let gr0 = [|[|V; C 6; V; V; V; V; C 2; V; C 5|];
          [|C 4; V; V; C 9; C 2; C 1; V; V; V|];
          [|V; C 7; V; V; V; C 8; V; V; C 1|];
          [|V; V; V; V; V; C 5; V; V; C 9|];
          [|C 6; C 4; V; V; V; V; V; C 7; C 3|];
          [|C 1; V; V; C 4; V; V; V; V; V|];
          [|C 3; V; V; C 7; V; V; V; C 6; V|];
          [|V; V; V; C 1; C 4; C 6; V; V; C 2|];
          [|C 2; V; C 6; V; V; V; V; C 1; V|]|]

let compatible_ligne (g :grille) k i j =
  try
    for n = 0 to Array.length g -1 do 
      match g.(n).(j) with
        | C p when p = k -> raise Exit
        | _ -> ()
    done;
    true
  with Exit -> false

let compatible_colone (g :grille) k i j =
  try
    for n = 0 to Array.length g -1 do 
      match g.(i).(n) with
      | C p when p = k -> raise Exit
      | _ -> ()
    done;
    true
  with Exit -> false

let coordonnees_sup i j = 
  (3*(i/3), 3*(j/3))

let compatible_carre (g: grille) k i j =
  let x, y = coordonnees_sup i j in
  try   
    for n = x to x + 2 do 
      for p = y to y + 2 do 
        match g.(n).(p) with
        | C m when m = k -> raise Exit
        | _ -> ()
      done
    done;
    true
  with Exit -> false

let compatible (g : grille) k i j = 
  compatible_ligne g k i j && compatible_colone g k i j && compatible_carre g k i j

let suivant i j = 
  (*on linéarise les indices puis on délinéarise*)
  if i <> 9 && j <> 9 then
    let i_lin = 9*i + j + 1 in
    let x, y = i_lin / 9, i_lin mod 9 in
    x, y
  else
    failwith "Il n'y a pas de suivant à cette case"

let rec remplir (g : grille) i j=
  if i = 9 && j = 0 then
    raise Solution
  else
    match g.(i).(j) with
    | C n -> let x,y = suivant i j in remplir g x y
    | V -> for k = 1 to 9 do 
              if compatible g k i j then begin
                g.(i).(j) <- C k;
                let x, y = suivant i j in
                remplir g x y;
                g.(i).(j) <- V
              end
            done

let resoudre grille_sudoku = 
  let grille_solution = Array.make_matrix 9 9 V in
  for i = 0 to 8 do
    for j = 0 to 8 do 
      grille_solution.(i).(j) <- grille_sudoku.(i).(j)
    done
  done;
  try
    remplir grille_solution 0 0;
    failwith "pas de solution"
  with Solution -> grille_solution


let imprime (g :grille) =
  for i = 0 to 2 do
    print_string " ----- ----- ----- ";
    print_newline ();
    for



let _ =
  let g = resoudre gr0 in
    for i = 0 to 8 do
      for j = 0 to 8 do 
        match g.(i).(j) with
        | C n -> print_int n; print_char ','
        | _ -> ()
      done;
      print_newline ()
    done