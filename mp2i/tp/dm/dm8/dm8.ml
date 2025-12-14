let rec ecriture n b = 
  match n with
    | 0 -> []
    | _ -> (n mod b )::(ecriture (n/b) b)

let rec horner ecriture b =
  match ecriture with
  | [] -> 0
  | t::q -> t + b*(horner q b)

let _ =
  let res = ref (ecriture 141 8) in
  print_int (horner (!res) 8);
  while !res != [] do 
    let t::q = !res in
    print_int t;
    res := q
  done
