(*
CORRIGÉ PARTIEL DU TP : PREMIERS ALGORITHMES DE TRIS (PARTIE EN OCAML)
Par J. BENOUWT
Licence CC BY-NC-SA
*)


(* --------------------------------------------------------- *)


(* fonction d'affichage utile pour les tests *)
let rec affiche_liste l = match l with
    | [] -> ()
    | [x] -> print_int x ; print_newline ()
    | x::xs ->  print_int x ;
                print_string " - " ;
                affiche_liste xs


(*

    QUESTIONS D'ANALYSE :
    ---------------------

Pour chaque fonction des algos de tris, je donnerai systématiquement dans ce corrigé
la propriété qu'il faut montrer par récurrence pour justifier la terminaison et correction,
qui sera placée juste au dessus de la fonction concernée.
Cependant, seules certaines preuves sont intégralement rédigées.
De même, seuls certains calculs de complexité sont rédigés.
Si vous avez un problème pour la rédaction des preuves / calculs non fournis, n'hésitez pas à me poser vos questions.


    NOTATIONS
    ---------

La notation x_i sert à désigner l'élément d'indice i de la liste x,
x_{i -> j} sert à désigner la tranche de la liste x entre les indices i et j inclus,
et |x| sert à désigner le nombre d'éléments de la liste x.

*)


(* --------------------------------------------------------- *)

(* Algorithmes de tris *)


(* Les listes sont immuables, les tris ne peuvent pas se faire par effet de bord. *)


(* Tri par sélection *)

let rec extrait_minimum l = match l with
    | [] -> failwith "pas de min"
    | [t] -> t, []
    | t::q ->   let mini, reste = extrait_minimum q in
                if t < mini then
                    t, q
                else
                    mini, t::reste

let rec tri_selection l = match l with
    | [] -> []
    | _ ->  let mini, reste = extrait_minimum l in
            mini :: tri_selection reste

(*

        -------------------------------------------
        | ANALYSE DE LA FONCTION extrait_minimum. |
        -------------------------------------------


    TERMINAISON ET CORRECTION
    -------------------------

On souhaite montrer la propriété suivante pour tout entier naturel n non nul :
H(n) :  extrait_minimum l, avec l de taille n, termine et renvoie un couple
        formé du minimum de l et de l privée de son minimum.

Initialisation.
Si l est de taille 1, la fonction extrait_minimum termine trivialement (cas de base),
et renvoie le couple (t, []) avec t la tête de la liste,
ce qui est correct puisque t étant le seul élément de l, t est le minimum,
et la liste privée de t est vide.
Donc H(1) est vraie.

Hérédité.
Supposons H(n-1) vraie pour un certain n > 1.
Montrons alors H(n).
L'appel à extrait_minimum l, avec l de taille de taille n > 1,
appelle récursivement extrait_minimum avec la queue de l (q dans le code) qui est de taille n-1.
Par hypothèse de récurrence, cet appel termine, et renvoie correctement le couple (mini, reste)
avec mini = minimum de la queue de l et reste = queue de l privée de mini
Le minimum de l est donc le plus petit élément entre la tete de l (t dans le code) et mini,
or la fonction extrait_minimum compare les deux pour renvoyer le plus petit
comme premier élément du couple ce qui est correct.
Le second élément du couple renvoyé est bien l privée soit de t soit de mini selon le résultat
de la comparaison ce qui est correct aussi.
Comme les autres instructions terminent et sont correctes trivialement, on a bien H(n) vraie.

Conclusion.
extrait_minimum l termine et renvoie un couple formé du minimum de l
et de l privée de son minimum pour toute liste l :
la fonction est totalement correcte.


    COMPLEXITÉ
    ----------

On suppose que la liste passée en paramètre de extrait_minimum est composée
d'éléments ayant un type de base, pour lesquels les comparaisons sont en O(1).

Calculons la complexité (temporelle dans le pire des cas) de extrait_minimum, notée C_em(|l|).

On trouve la relation de récurrence suivante :
*   C_em(1) = O(1)   
    car le cas de base n'effectue que des opérations élémentaires
*   C_em(|l|) = C_em(|l| - 1) + O(1)  pour |l| > 1
    car il y a un unique appel récursif sur la queue de l (de taille |l| - 1 donc)
    et toutes les autres opérations sont élémentaires.

On en déduit (avec le cours de maths sur les suites),
C_em(|l|) = O(|l|).



        -----------------------------------------
        | ANALYSE DE LA FONCTION tri_selection. |
        -----------------------------------------


    TERMINAISON ET CORRECTION
    -------------------------

On souhaite montrer la propriété suivante pour tout entier naturel n :
H(n) :  tri_selection l, avec l de taille n, termine et
        renvoie une liste composée des mêmes éléments que l mais triée.

Initialisation.
Si l est de taille 0, la fonction tri_selection termine trivialement (cas de base), et
renvoie la liste vide ce qui est correcte car une liste vide triée est une liste vide.
Donc H(0) est vraie.

Hérédité.
Supposons H(n-1) vraie pour un certain n > 0.
Montrons alors H(n).
L'appel à tri_selection l, avec l de taille de taille n > 0,
appelle récursivement tri_selection avec la liste l privée de son minimum
(car extrait_minimum est correcte), qui est de taille n-1.
Par hypothèse de récurrence, cet appel termine, et renvoie correctement
une liste triée contenant tous les éléments de l sauf le minimum.
Le minimum de l étant plus petit que tous les autres, il suffit de le placer
en tête du résultat de cet appel récursif, et c'est bien ce qui est renvoyé.
Comme les autres instructions terminent et sont correctes trivialement, on a bien H(n) vraie.

Conclusion.
tri_selection l termine et renvoie une liste composée des mêmes éléments que l
mais triée pour toute liste l : la fonction est totalement correcte.


    COMPLEXITÉ
    ----------

On suppose que la liste passée en paramètre de tri_selection est composée
d'éléments ayant un type de base, pour lesquels les comparaisons sont en O(1).

Calculons la complexité (temporelle dans le pire des cas) de tri_selection, notée C(|l|).

On trouve la relation de récurrence suivante :
*   C(0) = O(1)   
    car le cas de base n'effectue que des opérations élémentaires
*   C(|l|) = C(|l| - 1) + C_em(|l|) + O(1)  pour |l| > 0
    car il y a un unique appel récursif sur une liste ayant 1 élément de moins que l,
    un appel à la fonction extrait_minimum sur la liste l,
    et toutes les autres opérations sont élémentaires.
    Ce qui revient à C(|l|) = C(|l| - 1) + O(|l|) pour |l| > 0.

On en déduit (avec le cours de maths sur les suites),
C(|l|) =  O(|l|²).

*)



(* Tri à bulles *)

(*
Terminaison et correction : il faut montrer pour tout entier naturel n la propriété
H(n) : un_tour l, avec l de taille n, termine et renvoie une liste contenant les mêmes éléments
que l mais dont le plus grand élément qui n'était pas encore à la bonne place a été "remonté"
(comme une bulle d'eau, d'où le nom du tri) à la bonne place.
Complexité : O(|l|)
*)
let rec un_tour l = match l with
  | t1::t2::q when t1 <= t2 -> t1 :: un_tour (t2::q) (* pas d'échange nécessaire car bon ordre pour les 2 premiers éléments *)
  | t1::t2::q -> t2 :: un_tour (t1::q) (* on échange les deux premiers éléments car mauvais ordre pour les 2 premiers éléments *)
  | _ -> l (* 0 ou 1 élément, c'est fini *)

(*
Terminaison et correction : il faut montrer pour tout entier naturel n la propriété
H(n) :  aux l n termine et renvoie une liste composée des mêmes éléments que l mais
dont les n derniers éléments sont les n plus grands éléments triés.
Complexité : O(|l|²)
*)
let tri_bulles l =
    let rec aux l nb_tours_restants = match nb_tours_restants with
        | 0 -> l
        | _ -> aux (un_tour l) (nb_tours_restants - 1)
    in aux l (List.length l)

(* autre possibilité : *)
let tri_bulles_v2 l =
    (* on fait un tour en échangeant 2 à 2 si mauvais ordre *)
    let l_apres_un_tour = un_tour l in
    (* s'il n'y a eu aucun échange c'est que l est triée, on s'arrête *)
    if l_apres_un_tour = l then
        l
    else
    (* sinon on refait des tours *)
        tri_bulles l_apres_un_tour



(* Tri par insertion *)

(*
Terminaison et correction : il faut montrer pour tout entier naturel n la propriété
H(n) :  insere elt l, avec l triée de taille n, termine et renvoie une liste triée
        composée de elt et de tous les éléments de l
Complexité : O(|l|) ; Ω(1)
*)
let rec insere elt l = match l with
    | [] -> [elt]
    | x::_ when elt < x -> elt :: l
    | t::q -> t :: insere elt q

(*
Terminaison et correction : il faut montrer pour tout entier naturel n la propriété
H(n) :  tri_insertion l, avec l de taille n, termine et
        renvoie une liste composée des mêmes éléments que l mais triée.
Complexité : O(|l|²) ; Ω(|l|) *)
let rec tri_insertion l = match l with
    | [] -> []
    | t::q -> insere t (tri_insertion q)



(* --------------------------------------------------------- *)

(* Inclusion d'ensembles *)


(* Réponse au problème sans trier *)

let rec inclusion_simple e f =
    (* fonction auxiliaire implémentant List.mem *)
    let rec appartient elt l = match l with
        | [] -> false
        | t::q -> elt = t || appartient elt q in
    (* tout élément de e doit appartenir à f *)
    match e with
        | [] -> true
        | t::q -> appartient t f && inclusion_simple q f

(*
        --------------------------------------------
        | ANALYSE DE LA FONCTION inclusion_simple. |
        --------------------------------------------

TERMINAISON ET CORRECTION DE LA FONCTION appartient.
----------------------------------------------------

On souhaite montrer la propriété suivante :
H(n) : appartient elt l, avec l une liste de taille n, termine et détermine si elt ∈ l.

Initialisation.
Si l est de taille 0, la fonction appartient termine trivialement,
et renvoie false ce qui est correct puisqu'un élément ne peut pas appartenir à une liste vide.
Donc H(0) est vraie.

Hérédité.
Supposons H(n-1) vraie pour un certain n > 0.
Montrons alors H(n).
L'appel à appartient elt l, avec l de taille de taille n > 0,
appelle récursivement appartient avec la queue de l (q dans le code) qui est de taille n-1.
Par hypothèse de récurrence, cet appel termine, et
détermine correctement si elt ∈ q c'est-à-dire si elt ∈ l_{1 -> |l|-1}.
De plus, on détermine aussi si elt = tete(l) (t dans le code), c'est-à-dire si elt = l_0.
Ainsi on a bien déterminé si elt ∈ l_{0 -> |l|-1} c'est-à-dire si elt ∈ l.
Comme les autres instructions terminent et sont correctes trivialement, on a bien H(n) vrai.

Conclusion.
appartient elt l termine et détermine si elt ∈ l pour toute liste l et tout élément elt :
la fonction est totalement correcte.


TERMINAISON ET CORRECTION DE LA FONCTION inclusion_simple.
----------------------------------------------------------

On souhaite montrer la propriété suivante :
H(n) : inclusion_simple e f, avec e une liste de taille n, termine et détermine si e ⊂ f.

Initialisation.
Si e est de taille 0, la fonction inclusion_simple termine trivialement, et
renvoie true ce qui est correct puisque tous les éléments de e (puisqu'il y en a aucun) sont bien inclus dans f.
Donc H(0) est vraie.

Hérédité.
Supposons H(n-1) vraie pour un certain n > 0.
Montrons alors H(n).
L'appel à inclusion_simple e f, avec e de taille de taille n,
appelle récursivement inclusion_simple avec la queue de e (q dans le code) qui est de taille n-1.
Par hypothèse de récurrence, cet appel termine, et
détermine correctement si q ⊂ f c'est-à-dire si e_{1 -> |e|-1} ⊂ f.
De plus, on détermine aussi si tete(e) (t dans le code) ∈ f, c'est-à-dire si e_0 ∈ f
(termine et est correct puisqu'on a montré la correction totale de appartient).
Ainsi on a bien déterminé si e_{0 -> |e|-1} ⊂ f, c'est-à-dire si e ⊂ f.
Comme les autres instructions terminent trivialement, on a bien H(n) vrai.

Conclusion.
inclusion_simple e f termine et détermine si e ⊂ f pour toute liste e et toute liste f :
la fonction est totalement correcte.


COMPLEXITÉ TEMPORELLE.
----------------------

Commençons par calculer la complexité (dans le pire des cas) de appartient, notée C_a(|l|).
On trouve la relation de récurrence suivante :
*   C_a(0) = O(1)
    car le cas de base n'effectue que des opérations élémentaires
*   C_a(|l|) = C_a(|l| - 1) + O(1) pour |l| > 0
    car il y a un unique appel récursif sur la queue de l (de taille |l| - 1 donc)
    et toutes les autres opérations sont élémentaires.
On en déduit C_a(|l|) = O(|l|).

Calculons maintenant la complexité de la fonction inclusion_simple, notée C(|e|, |f|).
On trouve la relation de récurrence suivante :
*   C(0, |f|) = O(1)
    car le cas de base n'effectue que des opérations élémentaires
*   C(|e|, |f|) = C(|e|-1, |f|) + C_a(|f|) + O(1) = C(|e|-1, |f|) + O(|f|)
    car il y a un unique appel récursif sur la queue de e (de taille |e| - 1 donc),
    un appel à la fonction appartient sur f,
    et toutes les autres opérations sont élémentaires.
On en déduit C(|e|, |f|) = O(|e| * |f|)

Comme les opérateurs booléens && et || sont paresseux,
le parcours de F dans appartient va s'arrêter dès qu'on trouve l'élément recherché, et
le parcours de E dans inclusion_simple va s'arrêter dès qu'un élément n'appartient pas à F.
Ainsi, la complexité de cette fonction s'apparente à celle de inclusion_v3 sur les tableaux en C.

Le choix de la structure de données n'a ici pas d'impact sur la complexité temporelle de l'algorithme.
*)


(* Réponse au problème en triant *)

let inclusion_un_tri e f =
    (* Fonction d'appartenance mais dans une liste triée *)
    let rec appartient elt f_trie = match f_trie with
        | [] -> false
        | t::_ when elt = t -> true
        | t::q when elt > t -> appartient elt q
        | _ -> false (* comme f est trié, inutile de chercher elt dans la suite si elt < tete(f) *)
    in
    let rec inclus e f_trie = match e with
        | [] -> true
        | t::q -> appartient t f_trie && inclus q f_trie
    in inclus e (tri_insertion f)

let inclusion_deux_tris e f =
    (* vérifie si e est inclus dans f avec e et f triés *)
    let rec inclusion_tries e f = match e, f with
        | [], _-> true
        | te::qe, tf::qf when te = tf -> inclusion_tries qe qf
        | te::qe, tf::qf when te > tf -> inclusion_tries e qf
        | _ -> false
    in inclusion_tries (tri_insertion e) (tri_insertion f)
