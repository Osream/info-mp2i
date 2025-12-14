type regex =
 Vide
| Epsilon
| Lettre of string
| Union of regex * regex
| Produit of regex * regex
| Etoile of regex

let r0 = Produit (
Produit ( Etoile ( Union ( Lettre "a", Lettre "b") ) ,
Produit ( Lettre "a", Lettre "b") ) ,
Produit ( Lettre "a",
Etoile ( Union ( Lettre "a", Lettre "b") ) ) )

let rec ecrire (r:regex) = 
  match r with
  | Vide -> "0"
  | Epsilon -> "1"
  | Lettre s -> s
  | Union (r1,r2) -> "(" ^ (ecrire r1) ^ "|" ^ (ecrire r2) ^ ")"
  | Produit (r1,r2) -> "(" ^ (ecrire r1) ^ "." ^ (ecrire r2) ^ ")"
  | Etoile r -> "(" ^ (ecrire r) ^ "*" ^ ")"

let rec langageVide (r : regex) = 
  match r with
  | Vide -> true
  | Epsilon -> false
  | Lettre s -> false
  | Union (r1,r2) -> langageVide r1 || langageVide r2
  | Produit (r1,r2) -> langageVide r1 && langageVide r2
  | Etoile r -> false

let rec motVide (r : regex) = 
  match r with
  | Vide -> false
  | Epsilon -> true
  | Lettre s -> false
  | Union (r1,r2) -> langageVide r1 || langageVide r2
  | Produit (r1,r2) -> langageVide r1 && langageVide r2
  | Etoile r -> true

let rec prefixe1 (r : regex) =
  match r with
  | Vide -> []
  | Epsilon -> ["1"]
  | Lettre s -> [s]
  | Union (r1, r2) -> (prefixe1 r1) @ (prefixe1 r2)
  | Produit (r1, r2) when r1 <> Epsilon -> prefixe1 r1
  | Produit (r1, r2) -> "1"::(prefixe1 r2)
  | Etoile r -> prefixe1 r 
 

let rec suffixe1 (r : regex) =
  match r with
  | Vide -> []
  | Epsilon -> ["1"]
  | Lettre s -> [s]
  | Union (r1, r2) -> (suffixe1 r1) @ (suffixe1 r2)
  | Produit (r1, r2) when r2 <> Epsilon -> suffixe1 r2
  | Produit (r1, r2) -> "1"::(suffixe1 r1)
  | Etoile r -> suffixe1 r 

let rec prefixe (r:regex) :regex =
  match r with
  | Vide -> Vide
  | Epsilon -> Lettre "1"
  | Lettre s -> Lettre s
  | Union (r1, r2) -> Union (prefixe r1 , prefixe r2)
  | Produit (r1, r2) when r1 = Vide || r2 = Vide -> Vide
  | Produit (r1, r2) -> Union(prefixe r1 , Produit (r1, prefixe r2))
  | Etoile r -> Etoile (prefixe r) 

let rec motSans a r =
  match r with
  | Vide -> Vide
  | Epsilon -> Vide
  | Lettre s when s = a -> Epsilon
  | Lettre s -> Lettre s
  | Union (r1, r2) -> Union (motSans a r1, motSans a r2)
  | Produit (r1, r2) -> Produit (motSans a r1, motSans a r2)
  | Etoile r -> Etoile (motSans a r)

let rec enlever0 (r : regex) :regex =
  match r with
  | Vide -> failwith "L est vide"
  | Epsilon -> Epsilon
  | Lettre s -> Lettre s
  | 