type formule = int list list

type valuation = bool array

let rec clause list (v : valuation) =
  match list with
  | [] -> false
  | t::q when t > 0 -> v.(t) || clause q v
  | t::q when t < 0 -> v.(-t) || clause q v
  | _ -> failwith "Cas impossible"


let rec sat (phi : formule) (v : valuation) =
 match phi with
  | [] -> 0
  | c::rest -> match clause c v with
          | true -> 1 + sat rest v
          | false -> sat rest v

let rec inclause list (v : valuation) k =
  match list with
  | [] -> false
  | t::q when t > 0 -> (t > k || v.(t)) || inclause q v k
  | t::q when t < 0 -> (-t > k || v.(-t)) || inclause q v k
  | _ -> failwith "Cas impossible"

let insat (phi : formule) (v :valuation) k =
  match phi with
  | [] -> 0
  | c::rest -> match inclause c v k with
          | true -> 1 + sat rest v
          | false -> sat rest v

let maxsat (phi : formule) nbr_lit =
  let valu_opt = Array.make (nbr_lit + 1) false in
  let valu_curr = Array.make (nbr_lit + 1) false in
  let max = ref 0 in
  let rec aux phi k =
    if k = nbr_lit then
      (
      if insat phi valu_curr k >= !max then
        max := insat phi valu_curr k;
        for i = 1 to nbr_lit do
          valu_opt.(i) <- valu_curr.(i)
        done
      )
    else
      (
      if insat phi valu_curr k > !max then begin
        valu_curr.(k+1) <- false;
        aux phi (k+1);
        valu_curr.(k+1) <- true;
        aux phi (k+1);
      end
      )
    in
  aux phi 1;
  valu_curr.(1) <- true;
  aux phi 1;
  !max