(*Tri fusion*)

let rec diviser l = 
  match l with
  | t1::t2::q -> let l_res1, l_res2 = diviser q in t1::l_res1, t2::l_res2
  | _ -> l, []

let rec fusion l1 l2 =
  match l1, l2 with
    | [], t| t, [] -> t
    | t1::q1, t2::q2 when t1 < t2 -> let l_res = fusion q1 (t2::q2) in t1::l_res 
    | t1::q1, t2::q2 -> let l_res = fusion (t1::q1) q2 in t2::l_res


let rec tri_fusion l = 
  match l with
  | [] -> []
  | [t] -> [t]
  | _ -> let p1, p2 = diviser l in fusion (tri_fusion p1) (tri_fusion p2)

(*tri rapide*)

let rec partition l a = 
  match l with
  |[] -> ([], [])
  | t::q when t <= a -> let f, s = partition q a in (t::f, s)
  | t::q -> let f, s = partition q a in (f, t::s)

let rec tri_rapide l = 
  match l with
  | [] -> []
  | t::q -> let f, s = partition q t in (tri_rapide f) @ t::(tri_rapide s) 
