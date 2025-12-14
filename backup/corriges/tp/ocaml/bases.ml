(* CORRIGÉ PARTIEL DU TP : BASES FONCTIONNELLES D'OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* premières définitions de fonctions *)
let somme x y = x + y
let produit n p = n * p
let somme_de_q_avec_produit_de_n_et_p n p q = somme q (produit n p)


(* ou exclusif avec une conditionnelle *)
let xor a b = 
    if a = b then
      false
  	else
    	true


(* implication logique avec trois filtrages différents *)
let implique_v1 a b = match a, b with
	| false, false -> true
	| false, true -> true
	| true, false -> false
	| true, true -> true
let implique_v2 a b = match a, b with
  	| true, false -> false
  	| _ -> true

let implique_v3 a b = match a with
  	| false -> true
  	| _ -> b


(* quelques fonctions récursives *)
let rec u n = match n with
	| 0 -> 5
	| _ -> 3 * u (n - 1) + 2
	
let rec v n = match n with
	| 1 -> 5.
	| _ -> (v (n - 1)) ** 0.5 +. 4.

let rec somme_cubes n = match n with
	| 1 -> 1
	| _ -> n * n * n + somme_cubes (n - 1)

let rec pgcd_euclide u v = match v with
	| 0 -> u
	| _ -> pgcd_euclide v (u mod v)

let binom n k =
	let rec factorielle n = match n with
		| 0 -> 1
		| _ -> n * factorielle (n-1)
	in factorielle n / (factorielle k * factorielle (n - k))

let rec binom_rec n k = match n, k with
	| _, 0 -> 1
	| _ when n = k -> 1
	| _ -> binom_rec (n-1) (k-1) + binom_rec (n-1) k

let rec expo_rapide x n = match n with
	| 0 -> 1.
	| _ -> expo_rapide (x *. x) (n / 2) *. (if n mod 2 = 0 then 1. else x)
	
let ( *** ) = expo_rapide


(* exercices *)

let norme a b = sqrt (a *. a +. b *. b)

let moyenne a b = (a +. b) /. 2.

let th x =
  	let ex = exp x in
  	(ex -. 1. /. ex) /. (ex +. 1. /. ex)

let min a b = if a < b then a else b

let valeur_absolue x = if x < 0 then -x else x

let f_ronf_f f = fun x -> f (f x)

let duplicate a = (a, a)
let swap (a, b) = (b, a)
let concat (a, b) (c, d) = (a, b, c, d)

let decurryfier f = fun (x, y) -> f x y
let curryfier f = fun x y -> f (x, y)

let bissextile_v1 annee =
  	if annee mod 400 = 0 then
    	true
  	else if annee mod 100 = 0 then
    	false
  	else
    	annee mod 4 = 0

let bissextile_v2 annee = annee mod 400 = 0 || (annee mod 4 = 0 && annee mod 100 <> 0)

let ( &&& ) a b = match a, b with
  	| true, true -> true
  	| _ -> false

let ( ^^^ ) = xor (* fonction définie plus haut *)

let rec syracuse d =
	if d = 1 then
		0
	else if d mod 2 = 0 then
		1 + syracuse (d / 2)
	else
		1 + syracuse (3*d + 1)

let rec renverse_chaine s =
	let n = String.length s in
	match n with
		| 0 | 1 -> s
		| _ -> renverse_chaine (String.sub s 1 (n-1)) ^ String.make 1 s.[0] (* mettre le premier caractère à la fin, puis placer devant le reste de la chaîne renversé *)

let rec renverse_chaine_v2 s =
  	let n = String.length s in
  	match n with
      	| 0 | 1 -> s
      	| _ -> String.make 1 s.[n-1] ^ renverse_chaine_v2 (String.sub s 0 (n-1)) (* même principe mais dans l'autre sens : on met le dernier caractère devant, auquel on concatène le début de la chaîne renversé *)

let premier n =
  	let rec divise k = match k with
		| 1 -> true (* tous les diviseurs potentiels ont été testés, n est premier *)
		| _ when n mod k = 0 -> false (* n possède un diviseur, n n'est pas premier *)
		| _ -> divise (k - 1) (* k ne divise pas n, on continue la vérification *)
	in
	if n <= 1 then
		false (* 0 et 1 ne sont pas premiers *)
	else
  		divise (n - 1) (* on vérifie si n possède un diviseur *)

let rec dean n = match n with
	| 0 -> 0
	| _ -> 1 + sam (n - 1) (* 1 étape + c'est au tour de sam *)
and sam n = match n with
	| 0 -> 0
	| _ -> 1 + ( if n mod 2 = 0 then dean (n-2) else dean (n-1) ) (* 1 étape + c'est au tour de dean *)
