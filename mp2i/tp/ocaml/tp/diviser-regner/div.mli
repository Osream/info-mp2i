type point = {x : float; y : float}

type triplet = {mutable point1 : point; mutable point2 : point; mutable dist : float}

val distance : point -> point -> float 

val best : triplet -> triplet -> triplet

val bande : point array -> point -> float -> point array 

val points_proches_bande : point array -> float -> triplet

val sous_tableau : int -> int -> 'a array -> 'a array

(*val points_proches : point array -> triplet*)
