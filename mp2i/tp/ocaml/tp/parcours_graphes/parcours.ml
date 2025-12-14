type 'a graphe = ('a, 'a list) Hashtbl.t

let gno : 'a graphe = let g : int graphe = Hashtbl.create 9 in 
Hashtbl.add g 0 [1; 4; 5]; 
Hashtbl.add g 1 [0; 3]; 
Hashtbl.add g 2 [4; 5; 6]; 
Hashtbl.add g 3 [1; 5]; 
Hashtbl.add g 4 [0; 2; 5; 8]; 
Hashtbl.add g 5 [0; 2; 3; 4; 6]; 
Hashtbl.add g 6 [2; 5; 7]; 
Hashtbl.add g 7 [6]; 
Hashtbl.add g 8 [4]; g

let go : 'a graphe = let g : int graphe = Hashtbl.create 9 in 
Hashtbl.add g 0 [1; 5]; 
Hashtbl.add g 1 [0; 3]; 
Hashtbl.add g 2 [4; 5]; 
Hashtbl.add g 3 []; 
Hashtbl.add g 4 [0; 8]; 
Hashtbl.add g 5 [2; 3; 4; 6]; 
Hashtbl.add g 6 [2]; 
Hashtbl.add g 7 [6]; 
Hashtbl.add g 8 []; g

let parcours_profondeur (g : int graphe) dep =
  let vus = [|false; false; false; false; false; false; false; false; false|] in
  let rec explorer sommet = 
    if not vus.(sommet) then begin
      vus.(sommet) <- true;
      print_int sommet;
      List.iter explorer (Hashtbl.find g sommet); 
    end in
    explorer dep;
    print_newline ()

let parcours_largeur (g : int graphe) dep = 
  let vus = [|false; false; false; false; false; false; false; false; false|] in
  let a_traiter  = Queue.create () in
  let boucle sommet = 
    if not vus.(sommet) then begin
      vus.(sommet)<-true;
      Queue.push sommet a_traiter
    end
  in
  vus.(dep) <- true;
  Queue.push dep a_traiter;
  while not (Queue.is_empty a_traiter) do 
    let s = Queue.pop a_traiter in
    print_int s;
    List.iter boucle (Hashtbl.find g s)
  done
    
  let parcours_generique (g : int graphe) dep = 
    let vus = [|false; false; false; false; false; false; false; false; false|] in
    let a_traiter  = Stack.create () in
    let boucle sommet = Stack.push sommet a_traiter
    in
    Stack.push dep a_traiter;
    while not (Stack.is_empty a_traiter) do 
      let s = Stack.pop a_traiter in
      if not vus.(s) then begin
        vus.(s) <- true;
        print_int s;
        List.iter boucle (Hashtbl.find g s)
      end
    done


let _ = 
  parcours_profondeur go 0;
  parcours_profondeur gno 0;
  parcours_largeur go 0;
  parcours_largeur gno 0;


