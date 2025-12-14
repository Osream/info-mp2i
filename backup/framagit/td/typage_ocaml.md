# TD : Typage OCaml

## Exercice 1 : variables

1. Pour chacun des codes suivants, dites si les variables `x`, `y` et `z` sont définies à la fin de l'exécution du programme. Si elles sont définies, donnez leur valeur.

```ocaml
(* code 1 *)					(* code 2 *)							(* code 3 *)
let x = 10 						let x = 2 								let x = 2
let y = x + 2 					let z = let y = 3 in y + x   			let z = 5 in let y = 10 in y - z * x
let z = 3 in x + y + z													let y = let z = 1 in x - z

(* code 4 *)					(* code 5 *)								(* code 6 *)
let x = 4   					let x = 10   								let x = 1
let y =   						let x =										let y =	
	let z = x - 1 in      			let y = 10 + x in							let z = x + 9 in
	let z = z * 2 in				let z = (let x = y * x in y + x) in			let x = 2 in
	z + x							z + x 										z + x
								let y = x + 100									   
```

2. Pour chacun des codes suivants, dites s'il est bien typé ou mal typé. S'il est bien typé, donnez le type de toutes les variables et fonctions globales. Sinon, indiquez la ligne et la nature de l'erreur de typage.

```ocaml
(* code 1 *)						(* code 2 *)					(* code 3 *)
let x = 3   						let x = 1   					let f x y = (x + 1) * (y - 1)
let y = 4   						let y = 7.2   					let u = f (f 1 2) (f 3 4)
let z = string_of_int x + y   		let f a b = a * b   
									let u = f x y   

(* code 4 *)						(* code 5 *)					(* code 6 *)
let g b = b + 1   					let x = 42						let x = 42   
let f a b = (a b) + (a b)   		let y =							let y =
let u = f g 4   						if x mod 2 = 0 then				if x mod 2 = 0 then
											true							0
										else							else
(* code 7 *)								"impair"						1
let x = 7															let z = x + y   
let pair =
   	if x mod 2 then					(* code 8 *)							
		true						let x = 3.5   	
	else							let y = 4. in y *. y   	
		false						let z = x +. y   	   						
```

## Exercice 2 : filtrages

1. Les codes suivants sont diverses tentatives d'implémenter l'opérateur `xor` (ou exclusif) avec un filtrage. Corrigez chaque code pour qu'il fonctionne, soit exhaustif, et ne contienne pas de clause inutilisée.

```ocaml
(* code 1 *)						(* code 2 *)						(* code 3 *)
let xor a b = match a, b with		let xor a b = match a, b with		let xor a b = match a, b with
	| true, true -> false				| true, true -> false				| false, _ -> true
 	| false, false -> false				| true, _ -> true					| false,false | true,true -> false
 	| _, _ -> true						| _, false -> false					| true, _ -> true 
 	| false, true -> true   			| _, true -> false   
 	
(* code 4 *)						(* code 5 *)						(* code 6 *)
let xor a b = match a, b with		let xor a b = match a, b with		let xor a b = match a, b with
	| false, false -> false				| x, y when x = y -> false			| x, x -> false
	| _, false -> true					| true, false -> true				| _ -> true
	| false, _ -> true   				| false, true -> true   
```

2. Pour chacun des filtrages suivants : (a) Indiquez s'il est exhaustif et s'il ne l'est pas, ajoutez les clauses nécessaires. (b) Si certaines clauses sont inutilisées, enlevez les. (c) Précisez le type de `x`.

```ocaml
(* code 1 *)						(* code 4 *)							(* code 6 *)
match x with						match x with							match x with
	| 0 -> true							| y, z when y mod z = 0 -> true			| true, true, true -> true
	| x when x > 0 -> false	  			| y, z when z mod y = 0 -> true			| true, false, true -> true
										| y, z -> false							| false, true, _ -> false
										| _ -> false							| false, false, true -> true
(* code 2 *)																	| false, _, false -> false
match x with									(* code 5 *)					| true, false, _ -> true
	| s when String.length s < 5 -> s ^ s		match x with					| false, false, _ -> false
	| s when String.length s = 0 -> "vide"			| 0, _, _ -> true			| true, false, false -> true 
	| s -> s										| 0, _, 0 -> true	
    		   										| 0, 0, _ -> true
	   												| _, y, 0 -> true
(* code 3 *)										| _, 0, z -> true
match x, y with										| _, 0, 0 -> true
	| 0, _ -> 1	   									| 0, 0, 0 -> true
	| _, 0 -> 2	   									| w, y, z -> false 
```

## Exercice 3 : fonctions

1. Pour chaque fonction suivante : (a) Identifiez ce qu'elle réalise. (b) Donnez son type. (c) Écrivez en une version curryfiée.

```ocaml
(* code 1 *)							(* code 2 *)						(* code 3 *)
let f x =								let f x =							let f (a, b) = match a with
	let a, b = x in							let a, b, c = x in					| 0 -> b
	(a + b) * (a - b)   					a b + a c   						| _ -> -b
	
(* code 4 *)							(* code 5 *)						(* code 6 *)
let f (a, b) = match a, b with			let f x =							let f x =
	| _, 0. -> 0.							let a, b, c = x in					let a, _ = x in
	| x, y -> x /. y   						let q = a / b in					a
											let r = a mod b in
											a = q * b + r && c = r
```

2. Pour chaque question suivante, vous écrirez une version curryfiée puis une version décurryfiée de vos fonctions.
    * `f` de paramètres une fonction `a` et deux entiers qui applique `a` sur la somme des deux entiers
    * `g` de paramètres deux fonctions `a` et `b` et un entier qui applique `a` et `b` à l'entier et renvoie la somme des résultats
    * `h` de paramètres deux fonctions `a` et `b` qui renvoie la fonction $`a \circ b`$
3. Donnez le type de vos fonctions de la question 2.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
