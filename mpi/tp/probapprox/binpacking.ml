type instance = int * int list

type box = {mutable volume_disponible: int ; mutable boite: int list}

let next_fit (inst : instance) : box list =
  let capacity, elements = inst in
  let res_list = [{volume_disponible = capacity; boite = []}] in

  let rec aux box_list int_list =
    match int_list with
    | [] -> box_list
    | t::q -> match box_list with
            | [] -> failwith "impossible"
            | crate::list -> if t <= crate.volume_disponible then begin
                            crate.volume_disponible <- crate.volume_disponible - t;
                            crate.boite <- t::crate.boite;
                            aux box_list q
                      end
                      else
                        let nouv_boite = {volume_disponible = capacity - t; boite = [t]} in
                        aux (nouv_boite::box_list) q
  in
  aux res_list elements 

  let first_fit (inst : instance) : box list = 
    let capacity, elements = inst in
    let res_list = [] in

    let rec aux box_list int_list =
      match int_list with
      | [] -> box_list
      | t::q -> let crate, crate_list = parcours_list box_list t {volume_disponible = capacity; boite = []} in
        if crate.boite = [t] then
          aux (crate::crate_list) q
        else
          aux crate_list q
    and parcours_list box_list entier boite_possible= 
        match box_list with
          | [] -> boite_possible.volume_disponible <- boite_possible.volume_disponible - entier;
                  boite_possible.boite <- entier::boite_possible.boite;
                  (boite_possible, box_list)

          | crate::list -> 
            if entier <= crate.volume_disponible then
              let chest, crate_list = parcours_list list entier crate in
              chest, crate::crate_list
            else
              let chest, crate_list = parcours_list list entier boite_possible in
              chest, crate::crate_list
    in
    aux res_list elements 


let first_fit_decreasing (inst : instance) : box list =
  let capacity, elements = inst in
  let sorted = List.sort (fun x y -> -(x - y)) elements in
  first_fit (capacity, sorted) 
