let sous_tableau start stop arr =
  assert(start >= 0 && stop < Array.length arr);
  let res = Array.make (stop-start + 1) arr.(start) in
  for i = start+1 to stop do
    res.(i-start) <- arr.(i)
  done;
  res

let fusion_tableau arr1 arr2 =
  try 











