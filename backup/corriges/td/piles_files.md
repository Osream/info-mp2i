# TD : Manipulations de piles et files

## Exercice 1

Je fournis les algorithmes implémentés en OCaml (avec les modules `Stack` et `Queue` existants) :

```ocaml
(* Les fonctions sur les piles et les files utilisent beaucoup de transvasements (pile vers pile, pile vers file et inversement),
il est donc pertinent d'écrire des fonctions auxiliaires.
Toutes les fonctions de transvasement sont linéaires en la taille du premier paramètre,
on en déduiera donc aisément les complexités des autres algorithmes. *)

let transvase_pile_vers_pile p1 p2 =
    while not (Stack.is_empty p1) do
        Stack.push (Stack.pop p1) p2
    done

let transvase_file_vers_file f1 f2 =
    while not (Queue.is_empty f1) do
        Queue.push (Queue.pop f1) f2
    done

let transvase_pile_vers_file p f =
    while not (Stack.is_empty p) do
        Queue.push (Stack.pop p) f
    done

let transvase_file_vers_pile f p =
    while not (Queue.is_empty f) do
        Stack.push (Queue.pop f) p
    done


(* Affichage *)

let affiche_file f =
    let sauv = Queue.create () in
    print_string "<- "
    (* on affiche chaque élément
       tout en sauvegardant les valeurs dans une file intermédiaire *)
    while not (Queue.is_empty f) do
        let tete = Queue.pop f in
        print_int tete ;
        print_string " " ;
        Queue.push tete sauv
    done ;
    print_string "<-"
    print_newline () ;
    transvase_file_vers_file sauv f (* on remet tout dans la file d'origine *)

let affiche_pile p =
	(* même principe, on sauvegarde les éléments dans une pile intermédiaire
	pour pouvoir les remettre à leur place après *)
    let sauv = Stack.create () in
    while not (Stack.is_empty p) do
        let tete = Stack.pop p in
        print_string "| " ;
        print_int tete ;
        print_string " |" ;
        print_newline () ;
        Stack.push tete sauv
    done ;
    print_string "-----" ;
    print_newline () ;
    transvase_pile_vers_pile sauv p


(* Taille *)

let taille_file f =
    let sauv = Queue.create () in
    let taille = ref 0 in
    while not (Queue.is_empty f) do
        incr taille ;
        Queue.push (Queue.pop f) sauv
    done ;
    transvase_file_vers_file sauv f ;
    !taille

let taille_pile p =
    let sauv = Stack.create () in
    let taille = ref 0 in
    while not (Stack.is_empty p) do
        incr taille ;
        Stack.push (Stack.pop p) sauv
    done ;
    transvase_pile_vers_pile sauv p ;
    !taille


(* Copie *)

let copie_file f =
    let sauv = Queue.create () in
    let copie = Queue.create () in
    transvase_file_vers_file f sauv ;
    (* arrivé ici sauv est une copie de f mais f est vide donc 
       on remet les valeurs de sauv dans f ET dans la copie *)
    while not (Queue.is_empty sauv) do
        let tete = Queue.pop sauv in
        Queue.push tete f ;
        Queue.push tete copie
    done ;
    copie

let copie_pile p = (* version avec une seule pile intermédiaire *)
    let sauv = Stack.create () in
    let copie = Stack.create () in
    transvase_pile_vers_pile p sauv ;
    (* à ce stade p est vide
       et sauv contient les éléments dans l'autre sens *)
    while not (Stack.is_empty sauv) do
        let sommet = Stack.pop sauv in
        Stack.push sommet p ;
        Stack.push sommet copie
    done ;
    copie

let copie_pile_v2 p = (* version avec une seule file intermédiaire *)
    let sauv = Queue.create () in
    let copie = Stack.create () in
    transvase_pile_vers_file p sauv ;
    (* à ce stade p est vide et
       sauv contient les éléments avec en tête l'ancien sommet de p *)
    transvase_file_vers_pile sauv p ;
    (* à ce stade sauv est vide et
       p contient les éléments dans l'autre sens qu'au départ *)
    transvase_pile_vers_file p sauv ;
    (* à ce stade p est vide et
       sauv contient les éléments avec en tête la valeur à l'origine en bas de p *)
    while not (Queue.is_empty sauv) do
        let tete = Queue.pop sauv in
        Stack.push tete p ;
        Stack.push tete copie
    done ;
    copie

(*
On note n le nombre d'éléments.
En utilisant une pile pour la copie, on a deux transvasements à réaliser.
On est en O(n) + O(n) = O(n).
En utilisant une file, on a quatre transvasements à réaliser.
On est en O(n) + O(n) + O(n) + O(n) = O(n).
Les deux sont linéaires, mais avec une pile
on fait tout de même deux fois moins d'opérations
(et le code est plus simple et plus lisible).
Le choix de la structure de donnée la plus appropriée est essentiel
dans la conception d'un algorithme.
*)


(* Renverser une pile / une file *)

let renverse_pile p =
	let p_renversee = Stack.create () in
	transvase_pile_vers_pile p p_renversee ;
	p_renversee

let renverse_file f =
    (* on utilise une pile intermédiaire *)
    let sauv = Stack.create () in
    transvase_file_vers_pile f sauv ;
    let f_renversee = Queue.create () in
    transvase_pile_vers_file sauv f_renversee ;
    f_renversee

let renverse_pile_v1 p =
    (* par effet de bord, avec une file intermédiaire *)
    let sauv = Queue.create () in
    transvase_pile_vers_file p sauv ;
    transvase_file_vers_pile sauv p

let renverse_pile_v2 p =
    (* par effet de bord, avec 2 piles intermédiaire *)
    let envers = Stack.create () in
    let endroit = Stack.create () in
    transvase_pile_vers_pile p envers ;
    transvase_pile_vers_pile envers endroit ;
    transvase_pile_vers_pile endroit p
    
(*
La v2 est à nouveau moins efficace :
- 2 structures intermédiaires (contre 1 pour la v1)
- 3 transvasements (contre 2 pour la v1)
Le choix de la structure de donnée la plus appropriée est essentiel
dans la conception d'un algorithme.
*)
```

Je fournis également l'implémentation en C, en supposant disposer d'une implémentation d'une pile et d'une file (on le fera en TP) :

```c
#include "pile.h"
#include "file.h"

/* Taille */

int taille_pile(pile p) {
    int res = 0;
    pile sauv = creer_pile();
    while (!est_vide_pile(p)) {
        res += 1;
        empiler(sauv, depiler(p));
    }
    while (!est_vide_pile(sauv)) {
        empiler(p, depiler(sauv));
    }
    detruire_pile(sauv);
    return res;
}

int taille_file(file f) {
    int res = 0;
    file sauv = creer_file();
    while (!est_vide_file(f)) {
        res += 1;
        enfiler(sauv, defiler(f));
    }
    while (!est_vide_file(sauv)) {
        enfiler(f, defiler(sauv));
    }
    detruire_file(sauv);
    return res;
}


/* Affichage */

void affiche_pile(pile p) {
    pile sauv = creer_pile();
    while (!est_vide_pile(p)) {
        contenu s = depiler(p);
        printf("| %d |\n", s);
        empiler(sauv, s);
    }
    printf("-----\n");
    while (!est_vide_pile(sauv)) {
        empiler(p, depiler(sauv));
    }
    detruire_pile(sauv);
}

void affiche_file(file f) {
    file sauv = creer_file();
    printf("<- ");
    while (!est_vide_file(f)) {
        contenu t = defiler(f);
        printf("%d ", t);
        enfiler(sauv, t);
    }
    printf("<- \n");
    while (!est_vide_file(sauv)) {
        enfiler(f, defiler(sauv));
    }
    detruire_file(sauv);
}


/* Copie */

pile copie_pile(pile p) {
    // version efficace avec une seule pile intermédiaire
    pile envers = creer_pile();
    pile copie = creer_pile();
    while (!est_vide_pile(p)) {
        empiler(envers, depiler(p));
    }
    while (!est_vide_pile(envers)) {
        contenu s = depiler(envers);
        empiler(p, s);
        empiler(copie, s);
    }
    detruire_pile(envers);
    return copie;
}

file copie_file(file f) {
    file sauv = creer_file();
    file copie = creer_file();
    while (!est_vide_file(f)) {
        enfiler(sauv, defiler(f));
    }
    while (!est_vide_file(sauv)) {
        contenu t = defiler(sauv);
        enfiler(f, t);
        enfiler(copie, t);
    }
    detruire_file(sauv);
    return copie;
}

/* Renverser */

void renverse_pile(pile p) {
    // renverse par effet de bord,
    // version efficace avec une seule file intermédiaire
    file f = creer_file();
    while (!est_vide_pile(p)) {
        enfiler(f, depiler(p));
    }
    while (!est_vide_file(f)) {
        empiler(p, defiler(f));
    }
    detruire_file(f);
}

void renverse_file(file f) {
    // renverse par effet de bord
    pile p = creer_pile();
    while (!est_vide_file(f)) {
        empiler(p, defiler(f));
    }
    while (!est_vide_pile(p)) {
        enfiler(f, depiler(p));
    }
    detruire_pile(p);
}
```




## Exercice 2

1. ```ocaml
    let mystere_derecursive n_initial = (* somme des chiffres d'un entier *)
    	let res = ref 0 in
    	let n = ref n_initial in
    	while not (!n = 0) do
    		res := !res + !n mod 10 ;
    		n := !n / 10
    	done ;
    	!res
    ```

2. ```ocaml
    let expo_terminale x n_initial =
    	let rec expo_aux x n res = match n with
    		| 0 -> res
    		| _ -> expo_aux x (n - 1) (res * x)
    	in expo_aux x n_initial 1
    	
    let expo_derecursive x n_initial =
    	let res = ref 1 in
    	let n = ref n_initial in
    	while not (!n = 0) do
    		res := !res * x ;
    		n := !n - 1
    	done ;
    	!res
    ```

3. ![](img/paradigmes_piles_fact.jpg)

4. ```ocaml
    let rec expo x n = match n with
        | 0 -> 1
        | _ -> let appel = expo x (n - 1) in
               appel * x
               
    let expo_pile x n =
    	let res = ref 0 in
    	let p = Stack.create () in
    	Stack.push ("appel", n) p ;
    	while not (Stack.is_empty p) do
    		let instr, n = Stack.pop p in
    		if instr = "appel" then
    			if n = 0 then
    				res := 1
    			else begin
    				Stack.push ("mult", x) p ;
    				Stack.push ("appel", n-1) p
    			end
    		else
    			res := !res * x
    	done ;
    	!res
    ```

5. ```ocaml
    let rec somme_liste l = match l with
    	| [] -> 0
    	| x::xs -> x + somme_liste xs
    	
    let somme_liste_pile l =
    	let res = ref 0 in
    	let p = Stack.create () in
        Stack.push ("appel", l) p ;
        while not (Stack.is_empty p) do
        	let instr, l = Stack.pop p in
        	if instr = "appel" then
        		if l = [] then
        			res := 0
        		else begin
        			Stack.push ("somme", l) p ;
        			Stack.push ("appel", List.tl l) p
        		end
        	else
        		res := !res + List.hd l
        done ;
        !res
    ```



---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
