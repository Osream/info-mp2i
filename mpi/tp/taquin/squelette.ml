(*Partie 1*)

type graphe = (int*int) list array

let g = [|[1,3;3,1];[2,1];[0,1;1,1];[1,1;2,4]|]

let dijkstra g s =
  let vu = Hashtbl.create 100 in
  let dist = Hashtbl.create 100 in
  Hashtbl.add dist s 0;
  let q = Heap.create () in
  Heap.insert q (s, 0);
  let rec loop () =
    match Heap.extract_min q with
      | None -> vu
      | Some (x, _) when Hashtbl.mem vu x->  loop()
      | Some (x,dx) ->( Hashtbl.add vu x dx;
                      let process (v,p) =
                        let dv = dx + p in
                        match Hashtbl.find_opt dist v with
                          | Some d when d <= dv -> ()
                          | _ ->(
                                Hashtbl.replace dist v dv;
                                Heap.insert_or_decrease q (v, dv); ) in
                      List.iter process g.(x);
                      loop () ) in
  loop ()

let rec reconstituer_chemin hashtbl t =
  match Hashtbl.find hashtbl t with
  | s when s = t -> [s]
  | x -> t::(reconstituer_chemin hashtbl x)

let astar g h s t =
  let parente = Hashtbl.create 100 in
  let dist = Hashtbl.create 100 in
  Hashtbl.add parente s s;
  Hashtbl.add dist s 0;
  let q = Heap.create () in
  Heap.insert q (s, 0);
  let rec loop () =
    match Heap.extract_min q with
      | None -> failwith "t n'est pas accessible"
      | Some (x, pds_t) when x = t -> reconstituer_chemin parente t
      | Some (x,_) ->(let process (v,p) =
                        let dv = Hashtbl.find dist x + p in
                        match Hashtbl.find_opt dist v with
                          | Some d when d <= dv -> ()
                          | _ ->(
                                Hashtbl.replace dist v dv;
                                Hashtbl.replace parente v x;
                                Heap.insert_or_decrease q (v, dv + h v); ) in
                      List.iter process g.(x);
                      loop () ) in
  loop ()


(*Partie 2*)

let n = 4

type state = {
  grid : int array array;
  mutable i : int;
  mutable j : int;
  mutable h : int;
}

let print_state state =
  for i = 0 to n - 1 do
    for j = 0 to n - 1 do
      if i = state.i && j = state.j then print_string "   "
      else Printf.printf "%2d " state.grid.(i).(j)
    done;
    print_newline ()
  done

type direction = U | D | L | R | No_move

let delta = function
  | U -> (-1, 0)
  | D -> (1, 0)
  | L -> (0, -1)
  | R -> (0, 1)
  | No_move -> assert false

let string_of_direction = function
  | U -> "Up"
  | D -> "Down"
  | L -> "Left"
  | R -> "Right"
  | No_move -> "No move"


(* Partie 3 *)

let possible_moves state =
  let res = match state.i with 
          | 0 -> [D]
          | n when n = Array.length state.grid -> [U]
          | _ -> [U; D]
  in match state.j with
  | 0 -> res @ [R]
  | n when n = Array.length state.grid -> res @ [L]
  | _ -> res @ [L; R]

let distance i j value =
  let i_target = value / n in
  let j_target = value mod n in
  abs (i - i_target) + abs (j - j_target)

let compute_h state =
  let sum = ref 0 in
  let n = Array.length state.grid in
  for k = 0 to n -1 do
    for p = 0 to n -1 do
      if k <> state.i || p <> state.j then
        sum := !sum + distance k p (state.grid.(k).(p))
    done
  done;
  state.h <- !sum


let delta_h state move =
  assert(List.exists (fun x -> x = move) (possible_moves state));
  let i, j = state.i , state.j in
  let di, dj = delta move in
  let i_prime, j_prime = i + di, j + dj in
  let case_echange = state.grid.(i_prime).(j_prime) in
  distance i j case_echange - distance i_prime j_prime case_echange
  

let apply state move =
  assert(List.exists (fun x -> x = move) (possible_moves state));
  let i, j = state.i , state.j in
  let di, dj = delta move in
  let i_prime, j_prime = i + di, j + dj in

  state.h <- delta_h state move;

  let tmp = state.grid.(i).(j) in
  state.grid.(i).(j) <- state.grid.(i_prime).(j_prime);
  state.grid.(i_prime).(j_prime) <- tmp;

  state.i <- i_prime;
  state.j <- j_prime



let copy state =
  let n = Array.length state.grid in
  let tbl = Array.make n [||] in
  for i = 0 to n-1 do
    tbl.(i) <- Array.copy state.grid.(i)
  done;
  {grid = tbl; i = state.i; j = state.j; h = state.h}

(* A few examples *)

(* the goal state *)
let final =
  let m = Array.make_matrix n n 0 in
  for i = 0 to n - 1 do
    for j = 0 to n - 1 do
      m.(i).(j) <- i * n + j
    done
  done;
  {grid = m; i = n - 1; j = n - 1; h = 0}

(* Generates a state by making nb_moves random moves from *)
(* the final state. Returns a state s such that *)
(*  d(initial, s) <= nb_moves (obviously). *)
let random_state nb_moves =
  let state = copy final in
  for i = 0 to nb_moves - 1 do
    let moves = possible_moves state in
    let n = List.length moves in
    apply state (List.nth moves (Random.int n))
  done;
  state

(* distance 10 *)
let ten =
  let moves = [U; U; L; L; U; R; D; D; L; L] in
  let state = copy final in
  List.iter (apply state) moves;
  state

(* distance 20 *)
let twenty =
  {grid =
    [| [|0; 1; 2; 3|];
      [|12; 4; 5; 6|];
      [|8; 4; 10; 11|];
      [|13; 14; 7; 9|] |];
   i = 1; j = 1; h = 14}

(* distance 30 *)
let thirty =
  {grid =
     [| [|8; 0; 3; 1|];
       [|8; 5; 2; 13|];
       [|6; 4; 11; 7|];
       [|12; 10; 9; 14|] |];
   i = 0; j = 0; h = 22}

(* distance 40 *)
let forty =
  {grid =
     [| [|7; 6; 0; 10|];
       [|1; 12; 11; 3|];
       [|8; 4; 2; 5|];
       [|8; 9; 13; 14|] |];
   i = 2; j = 0; h = 30}

(* distance 50 *)
let fifty =
  let s =
    {grid =
       [| [| 2; 3; 1; 6 |];
          [| 14; 5; 8; 4 |];
          [| 15; 12; 7; 9 |];
          [| 10; 13; 11; 0|] |];
     i = 2;
     j = 3;
     h = 0} in
  compute_h s;
  s

(* distance 64 *)
let sixty_four =
  let s =
    {grid =
       [| [| 15; 14; 11; 7|];
          [| 5; 9; 12; 4|];
          [| 3; 10; 13; 8|];
          [| 2; 6; 0; 1|] |];
     i = 0;
     j = 0;
     h = 0} in
  compute_h s;
  s


(* Partie 4 *)


let successors state =
  let lst = possible_moves state in
  let rec bcle lst = 
    match lst with
    | [] -> []
    | move::q -> let res = copy state in
                apply res move;
                res::(bcle q)
  in
  bcle lst

let mv_lst lst state =
  let mv_lst = possible_moves state in
  let rec bcle list mv_lst = 
    match list, mv_lst with
    | [], [] -> []
    | s::q1, mv::q2 -> (s, mv)::(bcle q1 q2)
    | _, _ -> failwith "pas possible"
  in
  bcle lst mv_lst

let rec reconstruct parents x =
  match Hashtbl.find parents x with
  | s when s = x -> [s]
  | t -> x::(reconstruct parents t)

exception No_path

let astar initial =
  let parente = Hashtbl.create 100 in
  let dist = Hashtbl.create 100 in
  Hashtbl.add parente initial initial;
  Hashtbl.add dist initial 0;
  let q = Heap.create () in
  compute_h initial ;
  Heap.insert q (initial, initial.h);
  let rec loop () =
    match Heap.extract_min q with
      | None -> raise No_path
      | Some (x, pds_t) when x.h = 0 -> reconstruct parente final
      | Some (x,_) ->(let process (v, mv) =
                        let dv = Hashtbl.find dist x + 1 in
                        let h = x.h + delta_h x mv in
                        match Hashtbl.find_opt dist v with
                          | Some d when d <= dv -> ()
                          | _ ->(
                                Hashtbl.replace dist v dv;
                                Hashtbl.replace parente v x;
                                v.h <- h;
                                Heap.insert_or_decrease q (v, dv + h); ) in
                      let lst = successors x in
                      let cpl_lst = mv_lst lst x in
                      List.iter process cpl_lst;
                      loop () ) in
  loop ()



(* Partie 5 

exception Found of int

let opposite = function
| L -> R
| R -> L
| U -> D
| D -> U
| No_move -> No_move



let idastar_length initial =
  let exception Found of int in
  let state = copy initial in
  let rec search depth bound =
    if depth + state.h > bound then depth + state.h
    else if state.h = 0 then raise (Found depth)
    else
    let minimum = ref max_int in
    let make_move direction =
        apply state direction;
        minimum := min !minimum (search (depth + 1) bound);
        apply state (opposite direction); in
    List.iter make_move (possible_moves state);
    !minimum in
  let rec loop bound =
    let m = search 0 bound in
    if m = max_int then None
    else loop m in
  try
  loop state.h
  with
  |Found depth -> Some depth





let idastar initial =
  failwith "TODO"

let print_direction_vector t =
  for i = 0 to Vector.length t - 1 do
    Printf.printf "%s " (string_of_direction (Vector.get t i))
  done;
  print_newline ()

let print_idastar state =
  match idastar state with
  | None -> print_endline "No path"
  | Some t ->
    Printf.printf "Length %d\n" (Vector.length t);
    print_direction_vector t
*)

let main () =
  let lst_state = astar sixty_four in
  List.iter print_state lst_state 

let () = main ()
