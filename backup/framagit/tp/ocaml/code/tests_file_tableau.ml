(*
open est hors programme, mais permet d'éviter de répéter le nom du module devant chaque nom de fonction.
Il faut cependant éviter de l'utiliser pour plusieurs raisons :
   - on a rarement besoin de TOUTES les fonctions d'un module
   - certains noms sont communs à plusieurs modules (ex : length, mem, map...)
   - le code est moins lisible puisqu'il n'indique plus d'où viennent les fonctions
L'usage d'open ne sera toléré que dans le cas d'un fichier de tests d'un module comme celui-ci.
*)
open File_tableau


let tests_creer () =
    let f = creer () in
    assert (est_vide f)


let tests_est_vide () =
    let f = creer () in
    assert (est_vide f) ;
    enfiler 4 f ;
    assert(not (est_vide f))


let tests_enfiler () =
    let f = creer () in
    enfiler 4 f ;
    assert(not (est_vide f)) ;
    enfiler 2 f ;
    assert(defiler f = 4)


let tests_defiler () =
    let f = creer () in
    (try
        let _ = defiler f in failwith "pas d'assertions dans la fonction defiler"
    with
        | Assert_failure _ -> assert(true)
        | _ -> assert(false)
    ) ;
    enfiler 1 f ;
    enfiler 2 f ;
    assert(defiler f = 1) ;
    assert(defiler f = 2) ;
    assert(est_vide f)


let _ = tests_creer () ;
        tests_est_vide () ;
        tests_enfiler () ;
        tests_defiler ()

