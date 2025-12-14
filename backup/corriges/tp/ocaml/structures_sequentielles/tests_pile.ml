(*
open est hors programme, mais permet d'éviter de répéter le nom du module devant chaque nom de fonction.
Il faut cependant éviter de l'utiliser pour plusieurs raisons :
   - on a rarement besoin de TOUTES les fonctions d'un module
   - certains noms sont communs à plusieurs modules (ex : length, mem, map...)
   - le code est moins lisible puisqu'il n'indique plus d'où viennent les fonctions
L'usage d'open ne sera toléré que dans le cas d'un fichier de tests d'un module comme celui-ci.
*)
open Pile


let tests_creer () =
    let p = creer () in
    assert (est_vide p)
    

let tests_est_vide () =
    let p = creer () in
    assert (est_vide p) ;
    empiler 4 p ;
    assert(not (est_vide p))


let tests_empiler () =
    let p = creer () in
    empiler 4 p ;
    assert(not (est_vide p)) ;
    empiler 2 p ;
    assert(depiler p = 2)


let tests_depiler () =
    let p = creer () in
    (try
        let _ = depiler p in failwith "pas d'assertions dans la fonction depiler"
    with
        | Assert_failure _ -> assert(true)
        | _ -> assert(false)
    ) ;
    empiler 1 p ;
    empiler 2 p ;
    assert(depiler p = 2) ;
    assert(depiler p = 1) ;
    assert(est_vide p)


let _ = tests_creer () ;
        tests_est_vide () ;
        tests_empiler () ;
        tests_depiler ()