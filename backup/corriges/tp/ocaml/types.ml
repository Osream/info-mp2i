(* CORRIGÉ DU TP : DÉCLARATION DE TYPES EN OCAML *)
(* Par J. BENOUWT *)
(* Licence CC BY-NC-SA *)


(* --------------------------------------------------------- *)

(* Alias *)


type date = int * int * int

let nb_jours (d : date) =
    let _, m, a = d in
    match m with
        | 1 | 3 | 5 | 7 | 8 | 10 | 12 -> 31
        | 4 | 6 | 9 | 11 -> 30
        | 2 -> if a mod 400 = 0 || (a mod 4 = 0 && a mod 100 <> 0) then 29 else 28
        | _ -> failwith "Mois invalide"

let demain (d : date) : date =
    let j, m, a = d in
    if j < nb_jours d then
        j + 1, m, a (* jour suivant dans le même mois *)
    else if m < 12 then
        1, m + 1, a (* 1er du mois suivant *)
    else
        1, 1, a + 1 (* 1er janvier de l'année suivante *)


(* --------------------------------------------------------- *)

(* Type produit *)


(* couleurs *)

type couleur = {rouge : float ; bleu : float ; jaune : float}

let orange = {jaune = 50. ; rouge = 50. ; bleu = 0.}
let vert = {jaune = 50. ; rouge = 0. ; bleu = 50.}

let taux_de_bleu c =
    c.bleu

let melange c1 c2 =
    { jaune = (c1.jaune +. c2.jaune) /. 2. ;
      rouge = (c1.rouge +. c2.rouge) /. 2. ;
      bleu = (c1.bleu +. c2.bleu) /. 2. }


(* personnes *)

type personne = {prenom : string ; nom : string ; mutable age : int}

let anniversaire pers =
    pers.age <- pers.age + 1


(* variables mutables *)

type 'a var_mutable = {mutable valeur : 'a}

let incremente v = v.valeur <- v.valeur + 1

let decremente v = v.valeur <- v.valeur - 1

let echange_valeurs v1 v2 =
    let tmp = v1.valeur in
    v1.valeur <- v2.valeur ;
    v2.valeur <- tmp


(* --------------------------------------------------------- *)

(* Type somme *)


(* cartes *)

type valeur = As | Roi | Dame | Valet | Petite of int
type symbole = Pique | Trefle | Carreau | Coeur
type carte = valeur * symbole

let int_of_valeur v = match v with
        | As -> 14
        | Roi -> 13
        | Dame -> 12
        | Valet -> 11
        | Petite i when 1 < i && i < 11 -> i
        | _ -> failwith "carte non existante"

let est_valide v = match v with
    | Petite i when i < 2 || i > 10 -> false
    | _ -> true

let gagne v1 v2 =
    int_of_valeur v1 > int_of_valeur v2

let est_rouge symb = match symb with
    | Pique | Trefle -> false
    | _ -> true


(* type 'a option *)

let rec indice elt l = match l with
    | [] -> None
    | t::q when t = elt -> Some 0
    | t::q -> (* on ne peut pas faire (1 + indice elt q) car (indice elt q) est un int option, pas un int *)
                match indice elt q with
                    | None -> None
                    | Some i -> Some (i+1)

let indice_rec_terminale elt l = (* ou bien en version récursive terminale : *)
    let rec aux liste acc = match liste with
    (* acc désigne l'indice de la tête actuelle de liste dans l *)
        | [] -> None
        | t::q when t = elt -> Some acc
        | t::q -> aux q (acc + 1) in
    aux l 0

let premier_indice x l1 l2 = match indice x l1, indice x l2 with
    | Some i1, Some i2 -> Some (min i1 i2)
    | None, Some i2 -> Some i2
    | Some i1, None -> Some i1
    | _ -> None


(* --------------------------------------------------------- *)

(* Types récursifs *)


(* itinéraires *)

type itineraire = Arrive | Prendre of string * itineraire | Avancer of int * itineraire
let route = Prendre("rue des Acacias", Avancer(200, Prendre("boulevard Alan Turing", Avancer(70, Arrive))))

let rec distance it = match it with
    | Avancer (m, suite) -> m + distance suite
    | Prendre (_, suite) -> distance suite
    | Arrive -> 0

let rec itineraire_complet i = match i with
    | Arrive -> "vous êtes arrivés."
    | Prendre (rue, suite) -> "prendre " ^ rue ^ ", puis " ^ itineraire_complet suite
    | Avancer (dist, suite) -> "avancer de " ^ string_of_int dist ^ "m, puis " ^ itineraire_complet suite


(* poupées russes *)

type poupee = {taille : int ; contenu : poupee option}
let poupee_taille_2 = {taille = 2 ; contenu = Some {taille = 1 ; contenu = None}}

let rec poupees_decr p = match p.contenu with
    | None -> true
    | Some pp -> p.taille > pp.taille && poupees_decr pp

let rec creer_poupees n = match n with
    | 1 -> {taille = 1 ; contenu = None}
    | _ -> {taille = n ; contenu = Some (creer_poupees (n - 1))}


(* magasins *)

type magasin =
    | Boutique of string * string (* nom de la boutique, nom de la ville *)
    | Supermarche of string * string (* nom du supermarché, nom de la ville *)
    | Centre_commercial of centre
and centre = {nom : string ; ville : string ; magasins : magasin list}

let v2 = Centre_commercial {nom = "V2" ;
                            ville = "Villeneuve d'Ascq" ;
                            magasins = [Centre_commercial { nom = "Heron Parc";
                                                            ville = "Villeneuve d'Ascq" ;
                                                            magasins = [Boutique ("Cultura", "Villeneuve d'Ascq")]} ;
                                        Boutique ("Micromania", "Villeneuve d'Ascq") ;
                                        Supermarche ("Auchan", "Villeneuve d'Ascq")]}

let rec verifie_villes c =
    let verifie_magasin m = match m with (* fonction qui vérifie la ville d'un unique magasin *)
        | Boutique (_, v) | Supermarche (_, v) -> v = c.ville
        | Centre_commercial cc -> cc.ville = c.ville && verifie_villes cc in
    List.for_all verifie_magasin c.magasins


(* --------------------------------------------------------- *)

(* Exercices *)


(* triplets *)

type triplet = int * int * int
type permutation = triplet list

let rotation ((a,b,c) : triplet) : triplet = (c, a, b)

let rotations ((a,b,c) : triplet) : permutation = [(a,b,c) ; (c,a,b) ; (b,c,a)]

let trouve_permutations ((a,b,c) : triplet) : permutation = rotations (a,b,c) @ rotations (a,c,b)

let est_permutation (l : permutation) t = List.for_all (fun x -> List.mem x (trouve_permutations t)) l


(* pixels *)

type pixel = {rouge : int ; vert : int ; bleu : int}

let valide_pixel p =
    0 <= p.rouge && 0 <= p.vert && 0 <= p.bleu &&
    p.rouge <= 255 && p.vert <= 255 && p.bleu <= 255

let pixel_noir_blanc p =
    if (p.rouge + p.vert + p.bleu) / 3 < 128 then
        {rouge = 0 ; vert = 0 ; bleu = 0}
    else
        {rouge = 255 ; vert = 255 ; bleu = 255}

type image = pixel list list

let image_noir_blanc (im : image) : image = List.map (List.map pixel_noir_blanc) im


(* pierre feuille ciseaux *)


type coup = Pierre | Feuille | Ciseaux
type resultat = Victoire | Defaite | Egalite
type manche = coup * coup
type score = int * int

let tour () : manche =
    let associe x = match x with (* associe un entier entre 0 et 2 à un coup *)
        | 0 -> Pierre
        | 1 -> Feuille
        | _ -> Ciseaux in
    associe (Random.int 3), associe (Random.int 3)

let resultat_tour (m : manche) = match m with
    | joueur, adv when joueur = adv -> Egalite
    | Pierre, Ciseaux | Ciseaux, Feuille | Feuille, Pierre -> Victoire
    | _ -> Defaite

let maj_score (sc : score) (res : resultat) : score = match res with
    | Victoire -> fst sc + 1, snd sc
    | Defaite -> fst sc, snd sc + 1
    | _ -> sc

let resultat_jeu ((joueur, adversaire) : score) =
    if joueur > adversaire then
        Victoire
    else if joueur = adversaire then
        Egalite
    else
        Defaite

let jeu nb_manches =
    let rec partie sc n = match n with (* effectue n manches en modifiant le score à chaque tour *)
        | 0 -> sc
        | _ -> partie (maj_score sc (resultat_tour (tour ()))) (n - 1) in
    resultat_jeu (partie (0, 0) nb_manches)


(* dates *)


type mois = Janvier | Fevrier | Mars | Avril | Mai | Juin | Juillet | Aout | Septembre | Octobre | Novembre | Decembre
type date = {j : int ; m : mois ; a : int}

let est_valide d =
    let bissextile annee =
        annee mod 400 = 0 || (annee mod 4 = 0 && annee mod 100 <> 0) in
    0 < d.j && match d.m with
                | Fevrier -> d.j <= (28 + if bissextile d.a then 1 else 0)
                | Avril | Juin | Septembre | Novembre -> d.j <= 30
                | _ -> d.j <= 31

let lendemain d =
    if est_valide {a = d.a ; m = d.m ; j = d.j + 1} then
        {a = d.a ; m = d.m ; j = d.j + 1}
    else
        let rec donne_mois_suivant liste_mois = match liste_mois with
            | t1::t2::q when t1 = d.m -> t2
            | t::q -> donne_mois_suivant q
            | [] -> failwith "n'arrivera jamais ici" in
        {j = 1 ;
         a = d.a + if d.m = Decembre then 1 else 0;
         m = donne_mois_suivant [Janvier ; Fevrier ; Mars ; Avril ; Mai ; Juin ; Juillet ; Aout ; Septembre ; Octobre ; Novembre ; Decembre ; Janvier]}
