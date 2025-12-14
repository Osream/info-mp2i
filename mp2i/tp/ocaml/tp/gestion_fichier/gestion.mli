(* Fonction qui a un nom de ficher copie ses 10 premières lignes dans le second.
Entrees : 2 noms de fichier
Sorties : Aucune
Pre-condition : les fichiers existent
Post-condition : le 2eme fichier est modifié
*)
val copie10 : string -> string -> unit

(*Fonction qui a copie du premier fichier en paramètre toutes les lignes dans le 2nd
Entrees : 2 noms de fichier
Sorties : Aucune
Pre-condition : le premier fichier existe
Post-conditoon : Copie le premier fichier dans le 2eme (ou crée un fichier)
*)
val copie : string -> string -> unit

(*Fonction qui serialise une pile dans un fichier
Entrees : une pile et le fichier
Sortie : aucune
Pre-condition: le fichier est accessible
Post-condition: le fichier est modifié
*)
val serialise_pile : int Stack.t -> string -> unit


(*Fonction qui deserialise une pile
Entrees : le fichier
Sortie : une pile
Pre-condition: le fichier est accessible
Post-condition: la pile n'est constitué que d'entiers
*)
val deserialise_pile : string -> int Stack.t