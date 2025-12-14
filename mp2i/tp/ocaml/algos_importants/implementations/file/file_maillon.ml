type 'a file = {mutable sortie : 'a list; mutable entree : 'a list}

        
let creer () =
    {sortie = []; entree = []}
        
let est_vide f =
    f.sortie = f.entree && f.sortie = []
        
let emfiler elt f =
    f.entree <- elt::f.entree
        
let renverse lst = 
    let rec aux lst lst_res =
        match lst with
        | [] -> lst_res
        | t::q -> aux q (t::lst_res)
    in
    aux lst []

let defiler f =
    match f.sortie with
        | [] -> (match renverse f.entree with
                | [] -> assert(false)
                | t::q -> f.sortie <- q; t)
        | t::q -> f.sortie <- q; t



