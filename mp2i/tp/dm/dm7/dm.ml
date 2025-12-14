let switch arr i k = 
  let tmp = arr.(i) in
  arr.(i) <- arr.(k);
  arr.(k) <- tmp

let partition arr start stop =
  assert (start < stop && stop < Array.length arr && 0 <= start);
  let k = ref start in
  for i = start to stop -1 do 
    if arr.(i) <= arr.(stop) then begin
      switch arr i (!k);
      incr k;
    end
  done;
  switch arr (!k) stop;
  !k

let tri_rapide arr =
  let rec tri_rapide_aux arr start stop =
    try
      let mid = partition arr start stop in 
      tri_rapide_aux arr start (mid-1);
      tri_rapide_aux arr (mid + 1) stop
    with Assert_failure _ -> ()
  in 
  tri_rapide_aux arr 0 (Array.length arr -1)
