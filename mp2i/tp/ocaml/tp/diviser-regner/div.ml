type point = {x : float; y : float}

type triplet = {mutable point1 : point; mutable point2 : point; mutable dist : float}

let distance pt1 pt2 = sqrt((pt1.x -. pt2.x)*.(pt1.x -. pt2.x) +. (pt1.y -. pt2.y)*.(pt1.y -. pt2.y))

let best trip1 trip2 = 
  let d1 = distance trip1.point1 trip2.point1 and
  d2 = distance trip1.point2 trip2.point2 and
  d3 = distance trip1.point2 trip2.point1 in
  match trip1.dist, trip2.dist with 
  | a, b when a<=d1 && a <= d2 && a <= d3 && a <= b && a<>0.-> trip1
  | a, b when b<=d1 && b <= d2 && b <= d3 && b <= a && b<>0.-> trip2
  | a, b when d1<=a && d1 <= d2 && d1 <= d3 && d1 <= b && d1<>0.-> {point1 = trip1.point1; point2 = trip2.point1; dist = d1}
  | a, b when d2<=a && d2 <= d1 && d2 <= d3 && d2 <= b && d2<>0.-> {point1 = trip1.point2; point2 = trip2.point2; dist = d2}
  | a, b when d3<=a && d3 <= d1 && d3 <= d2 && d3 <= b && d3<>0. -> {point1 = trip1.point2; point2 = trip2.point1; dist = d3}
  | a, b when a >b -> trip2
  | _ -> trip2

let bande pts p0 delta = 
  let taille = ref 0 in
  for i = 0 to Array.length pts -1 do
    if pts.(i).x <= p0.x +.delta && pts.(i).x >= p0.x -.delta then
      incr taille
  done;
  let res = Array.make (!taille) p0 in
  for i = 0 to Array.length pts -1 do 
    if pts.(i).x <= p0.x +.delta && pts.(i).x >= p0.x -.delta then
      res.(i)<- pts.(i)
  done;
  res
let points_proches_bande bde delta = 
  let tripl = {point1 = bde.(0); point2 = bde.(1); dist = (distance bde.(0) bde.(1))} in
  for i = 0 to Array.length bde -2 do
    for j = 0 to Array.length bde -1 do
      if bde.(j).y <= bde.(i).y +.delta && bde.(j).y >= bde.(i).y -. delta then
        if tripl.dist >= (distance bde.(j) bde.(i)) then begin
          tripl.point1 <- bde.(j);
          tripl.point2 <- bde.(i)
        end
    done
  done;
  tripl

let sous_tableau start stop arr =
    assert(start >= 0 && stop < Array.length arr);
    let res = Array.make (stop-start + 1) arr.(start) in
    for i = start+1 to stop do
      res.(i-start) <- arr.(i)
    done;
    res
  

(*let rec points_proches pts =
  let taille = Array.length pts in
  if taille > 4 then
    let tb1 = sous_tableau 0 ((taille-1)/2) pts and
    tb2 = sous_tableau (((taille-1)/2)+1) (taille -1) pts in
    let tripl1 = points_proches tb1 and
    tripl2 = points_proches tb2 in
    best tripl1 tripl2
  else*)



let _=   
  let pts0 = [|{x =  0.9 ; y = 5.7}; {x =  1.2 ; y = 2.5}; {x =  1.8 ; y = 5.0}; {x =  2.0 ; y = 8.9}; 
              {x =  3.4 ; y = 1.4}; {x =  3.7 ; y = 1.8}; {x =  4.1 ; y = 8.3}; {x =  5.6 ; y = 6.2}; 
              {x =  5.7 ; y = 1.1}; {x =  6.4 ; y = 7.8}; {x =  6.6 ; y = 4.1}; {x =  7.5 ; y = 7.1}; 
              {x =  7.8 ; y = 2.2}; {x =  8.7 ; y = 2.9}; {x =  9.1 ; y = 5.0}; {x =  9.1 ; y = 0.1}; 
              {x = 10.3 ; y = 5.4}; {x = 10.4 ; y = 7.4}; {x = 10.7 ; y = 2.4}; {x = 11.3 ; y = 6.8}|]
  in
  let trip_array = Array.make (Array.length pts0 -1) {point1 = {x=0.; y=0.}; point2 = {x=0.; y=0.}; dist = 0.} in
  for i = 0 to Array.length pts0 -2 do
    trip_array.(i) <- {point1 = pts0.(i); point2 = pts0.(i+1); dist = (distance pts0.(i) pts0.(i+1))}
  done;
  let meilleur = ref trip_array.(0) in
  for i = 1 to Array.length trip_array -1 do
    meilleur := best trip_array.(i) (!meilleur)
  done;
  Printf.printf "La distance entre (%f, %f) et (%f, %f) est de %f\n" (!meilleur).point1.x (!meilleur).point1.y (!meilleur).point2.x (!meilleur).point2.y (!meilleur).dist
