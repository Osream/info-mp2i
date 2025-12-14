type 'a arbre_aq = {etiquette : 'a ; fils : 'a arbre_aq list}

type 'e ab =
	| Vide
	| N of 'e * 'e ab * 'e ab

let rec taille arb =
  let rec somme fils_list =
    match fils_list with
    | [] -> 0
    | t::q -> taille t + somme q
  in
  match arb.fils with
    | [] -> 1
    | _ -> 1 + somme (arb.fils)

let rec hauteur arb =
  let rec max_parcourt fils_list =
    match fils_list with
    | [] -> 0
    | t::q -> let suite = max_parcourt q and actuel = hauteur t in if actuel > suite then actuel else suite
  in
  match arb.fils with
    | [] -> 0
    | _ -> 1 + max_parcourt (arb.fils)


let rec arite arb =
  let rec list_taille l = 
    match l with
    | [] -> 0
    | t::q -> 1 + list_taille q
  in
  let rec max_parcourt fils_list =
    match fils_list with
    | [] -> 0
    | t::q -> let suite = max_parcourt q and actuel = arite t in if actuel > suite then actuel else suite
  in
  match arb.fils with
  | [] -> 0
  | _ -> max (list_taille (arb.fils)) (max_parcourt (arb.fils))


let rec egaux arb1 arb2 =
  let rec egaux_parcours_fils fils_l1 fils_l2= 
    match fils_l1, fils_l2 with
      | [], [] -> true
      | f1::q1, f2::q2 -> egaux f1 f2 && egaux_parcours_fils q1 q2
      | _ -> false
  in
  if arb1.etiquette = arb2.etiquette then
    egaux_parcours_fils (arb1.fils) (arb2.fils)
  else
    false

let binarise arb =
  let rec parcours liste_fils =
  match liste_fils with 
  | [] -> Vide
  | t::q -> N (t.etiquette, parcours (t.fils), parcours q)
  in
  N (arb.etiquette, parcours (arb.fils), Vide)

let debinarise arb =
  let parcours arb_ns =

  in
  match arb with f f

let _ = 
  let arb1 =
    {etiquette = 0; fils = [
        {etiquette = 1; fils = [
            {etiquette = 5; fils = []}
        ]};
        {etiquette = 2; fils = [
            {etiquette = 6; fils = [
                {etiquette = 11; fils = []}
            ]};
            {etiquette = 7; fils = []};
            {etiquette = 8; fils = []}
        ]};
        {etiquette = 3; fils = [
            {etiquette = 9; fils = []};
            {etiquette = 10; fils = [
            	{etiquette = 12; fils = []};
            	{etiquette = 13; fils = []};
            	{etiquette = 14; fils = []};
            	{etiquette = 15; fils = []};
            	{etiquette = 16; fils = []}
            ]}
        ]};
        {etiquette = 4; fils = []}
    ]}
  in
  let arb2 =
    {etiquette = 0; fils = [
        {etiquette = 1; fils = [
            {etiquette = 5; fils = []}
        ]};
        {etiquette = 2; fils = [
            {etiquette = 6; fils = [
               {etiquette = 11; fils = []}
            ]};
            {etiquette = 7; fils = []};
            {etiquette = 8; fils = []}
        ]};
        {etiquette = 3; fils = [
            {etiquette = 9; fils = []};
            {etiquette = 10; fils = [
            	{etiquette = 12; fils = []};
            	{etiquette = 13; fils = []};
            	{etiquette = 14; fils = []};
            	{etiquette = 15; fils = []};
            	{etiquette = 15; fils = []}
            ]}
        ]};
        {etiquette = 4; fils = []}
    ]}
  in
  print_int (taille arb1);
  print_newline ();
  print_int (hauteur arb1);
  print_newline ();
  print_int (arite arb1);
  print_newline ();
  if egaux arb1 arb2 then begin
    print_int 1;
    print_newline ()
  end
