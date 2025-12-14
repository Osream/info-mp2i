(* CORRIGÉ DU TP : PARCOURS DE GRAPHES (PARTIE EN OCAML) *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


type 'a graphe = ('a, 'a list) Hashtbl.t


let (gno : int graphe) =    let t = Hashtbl.create 20 in
                            Hashtbl.add t 0 [1; 4; 5] ;
                            Hashtbl.add t 1 [0; 3] ;
                            Hashtbl.add t 2 [4; 5; 6] ;
                            Hashtbl.add t 3 [1; 5] ;
                            Hashtbl.add t 4 [0; 2; 5; 8] ;
                            Hashtbl.add t 5 [0; 2; 3; 4; 6] ;
                            Hashtbl.add t 6 [2; 5; 7] ;
                            Hashtbl.add t 7 [6] ;
                            Hashtbl.add t 8 [4] ;
                            t

let (go : int graphe) =     let t = Hashtbl.create 20 in
                            Hashtbl.add t 0 [1; 5] ;
                            Hashtbl.add t 1 [0; 3] ;
                            Hashtbl.add t 2 [4; 5] ;
                            Hashtbl.add t 3 [] ;
                            Hashtbl.add t 4 [0; 8] ;
                            Hashtbl.add t 5 [2; 3; 4; 6] ;
                            Hashtbl.add t 6 [2] ;
                            Hashtbl.add t 7 [6] ;
                            Hashtbl.add t 8 [] ;
                            t



(* --------------------------------------------------------- *)

(* Implémentation des parcours *)

(* La complexité temporelle des trois algorithmes est O(|S|+|A|). *)
(* La complexité spatiale est O(|A|) pour l'algo générique et O(|S|) pour les deux autres. *)


let parcours_profondeur (g : 'a graphe) dep =
    let vus = Hashtbl.create 20 in (* taille arbitraire *)
    let rec explorer s =
        if not (Hashtbl.mem vus s) then begin
            Hashtbl.add vus s true ; (* valeur arbitraire *)
            (* print_int s ; print_string " " ; *)
            List.iter explorer (Hashtbl.find g s)
        end
    in explorer dep


let parcours_largeur (g : 'a graphe) dep =
    let vus = Hashtbl.create 20 in
    Hashtbl.add vus dep true ;
    let a_traiter = Queue.create () in
    Queue.push dep a_traiter ;
    while not (Queue.is_empty a_traiter) do
        let s = Queue.pop a_traiter in
        (* print_int s ; print_string " " ; *)
        List.iter (fun v -> if not (Hashtbl.mem vus v) then begin
                                Hashtbl.add vus v true ;
                                Queue.push v a_traiter
                            end
                  ) (Hashtbl.find g s)
    done


let parcours_generique (g : 'a graphe) dep =
    (* le mot-clef module est hors programme mais permet de changer
    le type de structure utilisé pour a_traiter d'un coup plutôt que
    de devoir renommer tous les Stack en Queue ou inversement *)
    let module Type = Stack (* ou Queue *) in
    let vus = Hashtbl.create 20 in
    let a_traiter = Type.create () in
    Type.push dep a_traiter ;
    while not (Type.is_empty a_traiter) do
        let s = Type.pop a_traiter in
        if not (Hashtbl.mem vus s) then begin
            Hashtbl.add vus s true ;
            (* print_int s ; print_string " " ; *)
            List.iter (fun v -> Type.push v a_traiter) (Hashtbl.find g s)
        end
    done



(* --------------------------------------------------------- *)

(* Applications des parcours *)


let est_connexe (g : 'a graphe) =
    (* sommet aléatoire pour le départ du parcours *)
    let recupere_un_sommet_quelconque (g : 'a graphe) =
        let sommet = ref None in
        Hashtbl.iter (fun s _ -> sommet := Some s) g ;
        match !sommet with
            | None -> failwith "un graphe a au moins un sommet"
            | Some s -> s
    in let dep = (recupere_un_sommet_quelconque g) in
    (* copié-collé de l'algo générique *)
    let module Type = Stack (* ou Queue *) in
    let vus = Hashtbl.create 20 in
    let a_traiter = Type.create () in
    Type.push dep a_traiter ;
    while not (Type.is_empty a_traiter) do
        let s = Type.pop a_traiter in
        if not (Hashtbl.mem vus s) then begin
            Hashtbl.add vus s true ;
            List.iter (fun v -> Type.push v a_traiter) (Hashtbl.find g s)
        end
    done ;
    (* on vérifie que tout les sommets ont été vus *)
    let tout_vu = ref true in
    Hashtbl.iter (fun s _ -> tout_vu := !tout_vu && Hashtbl.mem vus s) g ;
    !tout_vu


let distances (g : 'a graphe) dep =
    (* tableau associatif pour les distances *)
    let dist = Hashtbl.create 20 in
    Hashtbl.add dist dep 0 ;
    (* parcours en largeur *)
    let vus = Hashtbl.create 20 in
    Hashtbl.add vus dep true ;
    let a_traiter = Queue.create () in
    Queue.push dep a_traiter ;
    while not (Queue.is_empty a_traiter) do
        let s = Queue.pop a_traiter in
        List.iter (fun v -> if not (Hashtbl.mem vus v) then begin
                                Hashtbl.add vus v true ;
                                Queue.push v a_traiter ;
                                (* le chemin jusque v de longueur minimale va jusque s + 1 arête de s à v *)
                                Hashtbl.add dist v (Hashtbl.find dist s + 1)
                            end
                  ) (Hashtbl.find g s)
    done ;
    dist


let tri_topologique (g : 'a graphe) =
    let topo = ref [] in
    (* parcours en profondeur *)
    let vus = Hashtbl.create 20 in
    let rec explorer s =
        if not (Hashtbl.mem vus s) then begin
            Hashtbl.add vus s true ;
            List.iter (fun v -> explorer v) (Hashtbl.find g s) ;
            (* une fois tous les voisins explorés, juste avant de sortir de l'appel récursif,
            l'exploration de s est finie donc on l'ajoute au tri topologique *)
            topo := s :: !topo
        end
    in
    (* on explore tous les sommets (pour qu'ils soient tous dans le tri topologique) *)
    Hashtbl.iter (fun s _ -> explorer s) g ;
    !topo


let arborescence_largeur (g : 'a graphe) dep : 'a graphe = 
    let arbo = Hashtbl.create 20 in
    (* parcours en largeur *)
    let vus = Hashtbl.create 20 in
    Hashtbl.add vus dep true ;
    let a_traiter = Queue.create () in
    Queue.push dep a_traiter ;
    while not (Queue.is_empty a_traiter) do
        let s = Queue.pop a_traiter in
        (* aucun sommet découvert depuis s pour l'instant *)
        Hashtbl.add arbo s [] ;
        List.iter (fun v -> if not (Hashtbl.mem vus v) then begin
                                Hashtbl.add vus v true ;
                                Queue.push v a_traiter ;
                                (* on a découvert v depuis s donc on ajoute l'arc s->v dans l'arborescence *)
                                let successeurs_s = Hashtbl.find arbo s in
                                Hashtbl.remove arbo s ;
                                Hashtbl.add arbo s (v :: successeurs_s)
                            end
                  ) (Hashtbl.find g s)
    done ;
    arbo


let composantes_connexes (g : 'a graphe) =
    (* n'importe quel parcours convient, j'ai pris en profondeur ici *)
    let vus = Hashtbl.create 20 in
    let rec explorer s num_composante =
        if not (Hashtbl.mem vus s) then begin
            Hashtbl.add vus s num_composante ; (* on associe au sommet sa composante *)
            List.iter (fun v -> explorer v num_composante) (Hashtbl.find g s) ;
        end
    in
    (* on parcourt les sommets, s'ils sont déjà vus ils ont déjà été mis dans une composante,
    sinon on explore toute leur composante connexe et il y a donc une composante en plus *)
    let composante_actuelle = ref 0 in
    Hashtbl.iter (fun s _ ->    if not (Hashtbl.mem vus s) then begin
                                    explorer s !composante_actuelle ;
                                    incr composante_actuelle
                                end
                 ) g ;
    vus


let cyclique (g : 'a graphe) =
    (* variable qui vaut true si on a trouvé un cycle dans le graphe orienté g, false sinon *)
    let cycle = ref false in
    (* fonction basée sur un parcours générique déterminant si dep fait partie d'un cycle *)
    let cycle_dep g dep =
        (* copié-collé du parcours générique*)
        let module Type = Stack in
        let vus = Hashtbl.create 20 in
        let a_traiter = Type.create () in
        Type.push dep a_traiter ;
        while not (Type.is_empty a_traiter) do
            let s = Type.pop a_traiter in
            if not (Hashtbl.mem vus s) then begin
                Hashtbl.add vus s true ;
                List.iter (fun v -> Type.push v a_traiter ;
                                    (* on vérifie ici si on retombe sur le départ *)
                                    if v = dep then cycle := true
                          ) (Hashtbl.find g s)
            end
        done
    in Hashtbl.iter (fun s _ -> cycle_dep g s) g ;
    !cycle
