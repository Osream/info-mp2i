# TD : Algorithme de Karatsuba

### Multiplication naïve

1.   $`\mathcal O(n)`$ : on additionne les deux chiffres de poids faible (une opération élémentaire), puis les deux chiffres suivants avec éventuellement une retenue (une ou deux opérations élémentaires), et ainsi de suite pour les $n$ chiffres.

2.   $`\mathcal O(k)`$ : il suffit d’ajouter $`k`$ fois le chiffre $0$ à la représentation de l’entier.

3.   $`\mathcal O(n)`$ : on multiplie le chiffre avec le premier chiffre de poids faible (une opération élémentaire), puis e chiffre avec le second chiffre de poids faible avec éventuellement une retenue (une ou deux opérations élémentaires), et ainsi de suite pour les $n$ chiffres.

4.   Pour calculer $`\displaystyle y \times x = \sum _{i=0}^{n-1} (x_i\times y)b^i`$, il faut pour chaque $`i`$ :

     *   effectuer $`(x_i\times y)`$, cf question 3 pour la complexité ;
     *   effectuer la multiplication par $`b^i`$, cf question 2 pour la complexité ;
     *   ajouter le résultat à la somme déjà calculée, cf question 1 pour la complexité.

     À $`i`$ fixé, on a donc une complexité de $`\mathcal O(n)`$.

     Pour effectuer le produit complet, $`i`$ varie de $0$ à $`n-1`$, donc on a une complexité de $`\mathcal O(n^2)`$.

### Algorithme de Karatsuba (diviser pour régner)

5.   On divise le problème en multiplications plus petites : $`1237 \times 2587 = 
     (10^2\cdot 12 + 37) \times (10^2 \cdot 25 + 87) =
     10^4\cdot 12\times 25 + 10^2\cdot (12 \times 87 + 37\times 25)+ 37 \times 87`$
     
     On applique récursivement l'algorithme pour calculer les quatre produits obtenus :
     * $`12\times 25 = 10^2\cdot 1\times 2 + 10^1 \cdot (1\times 5 + 2\times 2) + 2 \times 5`$ ; les quatre produits n'ont plus qu'un chiffre donc leur calcul est immédiat : $`12\times 25 = 10^2\cdot 2+10^1\cdot(5+4)+10`$ ; il ne reste plus que des opérations élémentaires donc : $`12\times 25 = 200 + 90 + 10 = 300`$.
     * De même, $`12\times 87 = 10^2\cdot(1\times 8)+10^1(1\times 7 + 2 \times 8) + 2 \times 7 = 1044`$.
     * De même, $`37\times 25 = 10^2\cdot(3\times 2)+10^1(3\times 5 + 7 \times 2) + 7 \times 5 = 925`$.
     * De même, $`37\times 87 = 10^2\cdot(3\times 8)+10^1(3\times 7 + 7 \times 8) + 7 \times 7 = 3219`$.

     On combine les résultats obtenus : $`1237\times 2587= 10^4\cdot 300 + 10^2\cdot(1044+925)+3219 = 3000000+196900+3219=3200119`$.
     
6. $`C(2n) = 4\times C(n) + \mathcal O(2n)+\mathcal O(n)+3\times \mathcal O(4n)`$ car on fait 4 multiplications récursives de nombres à $`n`$ chiffres, une multiplication par $`b^{2n}`$, une multiplication par $`b^n`$, et trois additions de nombres ayant au plus $`4n`$ chiffres. Ainsi $`C(2n)=4\times C(n)+\mathcal O(n)`$.

    Pour trouver le terme général, commençons par le cas où on a une puissance de 2.

    $`C(2^0) = \mathcal O(1) \text{ et } C(2^k) = 4\times C(2^{k-1})+\mathcal  O(2^{k}) \text{ pour } k > 0`$

    D'après la formule vue en cours, on a donc $`C(2^k) = \displaystyle\sum _{i=0}^k 4^i\times f(2^{k-i})\text{ , avec }f \text{ la complexité d'un appel considéré seul (donc } f(2^0) = \mathcal O(1) \text{ et }f(2^k) = \mathcal O(2^{k}) \text{ selon la relation de récurrence)}`$

    Ainsi $`C(2^k) = \displaystyle\sum_{i=0}^{k}4^i\times \mathcal O(2^{k-i}) = \sum_{i=0}^{k}\mathcal O(2^{k+i}) = \mathcal O(2^{k})\times\mathcal O(2^{k+1}-1) = \mathcal O(4^k)`$

    Comme la complexité est croissante, on en déduit dans le cas général, $`C(n) \leqslant C(2^{\lceil\log_2 n\rceil}) = \mathcal O(4^{\lceil\log_2 n\rceil}) = \mathcal O(n^2)`$

    On retrouve la même complexité que la multiplication naïve, cette méthode diviser pour régner n'est pas efficace.

7. Il suffit de développer l'expression donnée.

8. On divise le problème en multiplications plus petites : $`1237 \times 2587 = 
    (10^2\cdot 12 + 37) \times (10^2 \cdot 25 + 87) =
    10^4\cdot 12\times 25 + 10^2\cdot (12\times 25 + 37 \times 87 - (12-37)\times(25-87))+ 37 \times 87`$

    On applique récursivement l'algorithme pour calculer les trois produits obtenus :

    * $`12\times 25 = 10^2\cdot 1\times 2 + 10^1 \cdot (1\times 2+2 \times 5-(1-2)(2-5)) + 2 \times 5`$ ; les trois produits n'ont plus qu'un chiffre donc leur calcul est immédiat : $`12\times 25 = 10^2\cdot 2+10^1\cdot(2+10-3)+10=200+90+10=300`$.
    * De même, $`37\times 87 = 10^2\cdot(3\times 8)+10^1(3\times 8 + 7\times 7 - (3-7)(8-7)) + 7 \times 7 = 3219`$.
    * De même, $`(12-37)\times(25-87) = 25\times 62 = 10^2\cdot(2\times 6)+10^1\cdot(2\times 6+5\times2-(2-5)(6-2))+5\times2=1550`$.

    On combine les résultats obtenus : $`1237\times 2587= 10^4\cdot 300 + 10^2\cdot(300+3219-1550)+3219 = 3000000+196900+3219=3200119`$.

9. On a 3 multiplications récursives, 2 produits par une puissance de la base, et 3 additions et 3 soustractions. Avec un raisonnement similaire à celui de la question 6, on trouve :

    $`C(2^0) = \mathcal O(1) \text{ et } C(2^k) = 3\times C(2^{k-1})+\mathcal  O(2^{k}) \text{ pour } k > 0`$

    Ainsi $`C(2^k) = \displaystyle\sum_{i=0}^{k}3^i\times \mathcal O(2^{k-i}) =\mathcal O\left(2^{k}\times\sum_{i=0}^{k}\left(\frac 3 2\right)^i\right) = \mathcal O(3^k)=\mathcal O\big((2^k)^{\log_2 3}\big)`$

    On en déduit le cas général :  $`C(n)=\mathcal O\big(n^{\log_2 3}\big)`$.

### Implémentation

10.   Multiplication naïve, décomposée en sous-fonctions comme suggéré dans le sujet :

```ocaml
let simplifie x =
    (* on cherche l'indice du dernier chiffre non nul dans le tableau *)
    let i = ref (Array.length x - 1) in
    while !i >= 0 && x.(!i) = 0 do
        decr i
    done ;
    (* on récupère le sous-tableau se terminant en cet indice *)
    Array.sub x 0 (!i+1)
    
let ajoute x y b =
    let tx = Array.length x in
    let ty = Array.length y in
    let res = Array.make (max tx ty + 1) 0 in (* le +1 est pour le cas où il y a une retenue sortante *)
    let retenue = ref 0 in (* on garde en mémoire l'éventuelle retenue à propager *)
    for i = 0 to max tx ty do
        let addition_chiffres_poids_i = !retenue  + (if i < tx then x.(i) else 0) + (if i < ty then y.(i) else 0) in
        res.(i) <- addition_chiffres_poids_i mod b ;
        retenue := addition_chiffres_poids_i / b
    done ;
    simplifie res
    
let mult_b_puiss_k x k =
    simplifie (Array.init (k + Array.length x) (fun i -> if i < k then 0 else x.(i-k)))
    
let mult_chiffre b a x =
    let tx = Array.length x in
    let res = Array.make (tx + 1) 0 in (* le +1 est pour le cas où il y a une retenue sortante *)
    let retenue = ref 0 in (* on garde en mémoire l'éventuelle retenue à propager *)
    for i = 0 to tx - 1 do
        let mult_chiffre_poids_i = a * x.(i) + !retenue in
        res.(i) <- mult_chiffre_poids_i mod b ;
        retenue := mult_chiffre_poids_i / b
    done ;
    res.(tx) <- !retenue ;
    simplifie res
    
let mult_naive x y b =
    let res = ref [||] in
    for i = 0 to Array.length x - 1 do
        res := ajoute !res (mult_b_puiss_k (mult_chiffre b x.(i) y) i) b
    done ;
    !res
```

11.   Algorithme de Karatsuba. Je fournis ici la version complète (longue, et assez difficile) de l'algorithme. Vous pouvez cependant vous limiter sans problème à la version où les paramètres sont des entiers naturels en base 10 (de type `int`), et où leur nombre de chiffres est le même, et égal à une puissance de 2.

```ocaml
(* On commence par réaliser la soustraction : *)

(* cette fonction renvoie (|x-y|, 1) si x < y et (x-y, 0) sinon *) 
let soustrait x y b =
  
    (* Fonction auxiliaire qui détermine si x >= y, auquel cas on calculera x-y, sinon on fera y-x. *)
    let operandes_gauche_et_droite_et_signe_du_resultat x y = 
        let tx = Array.length x in
        let ty = Array.length y in 
        (* si x a moins de chiffres que y, alors x < y *)
        if tx < ty then
            y, x, 1
        (* si x a plus de chiffres que y, alors x >= y *)          
        else if tx > ty then
            x, y, 0
        (* s'ils ont le même nombre de chiffres, il faut les parcourir du chiffre de poids fort au chiffre de poids faible, jusqu'à trouver un chiffre de x plus petit que celui de y ou inversement *)
        else
            let i = ref (tx - 1) in
            while !i >= 0 && x.(!i) = y.(!i) do decr i done ;
            (* et si c'est le chiffre de x qui est plus petit que celui de y, alors x < y ; sinon, x >= y *)
            if !i >= 0 && x.(!i) < y.(!i) then
                y, x, 1
            else
                x, y, 0 in
        
    (* op_gauche désigne l'opérande de gauche pour la soustraction (x si x >= y et y sinon)
       et op_droite désigne l'opérande droite pour la soustraction (y si x >= y et x sinon) *) 
    let op_gauche, op_droite, signe = operandes_gauche_et_droite_et_signe_du_resultat (simplifie x) (simplifie y) in
    let taille_op_gauche = Array.length op_gauche in
    let taille_op_droite = Array.length op_droite in

    (* on calcule op_gauche - op_droite en faisant la soustraction bit à bit *)
    let res = Array.make (max taille_op_gauche taille_op_droite) 0 in
    let retenue = ref 0 in (* et en n'oubliant pas de propager les éventuelles retenues *)
    for i = 0 to max taille_op_gauche taille_op_droite - 1 do
        let soustraction_chiffres_poids_i = (if i < taille_op_gauche then op_gauche.(i) else 0) - (if i < taille_op_droite then op_droite.(i) else 0) - !retenue in
        res.(i) <- (soustraction_chiffres_poids_i + b) mod b ;
        retenue := if soustraction_chiffres_poids_i < 0 then 1 else 0 
    done ;

    simplifie res, signe
    
    
(* On peut maintenant écrire l'algoritme de Karatsuba : *)

(* calcule x fois y, avec b la base dans laquelle x et y sont représentés *)
let rec karatsuba x y b = match Array.length x, Array.length y with
    (* Les cas de base où on ne divise plus les entiers en 2 correspondent aux cas où
    au moins un des deux entiers possède 0 ou 1 chiffre : *)
    | 0, _ | _, 0 -> [||]
    | 1, _ -> mult_chiffre b x.(0) y
    | _ , 1 -> mult_chiffre b y.(0) x
    (* Le cas récursif : *)
    | tx, ty -> (* la variable taille_max est nécessaire pour le cas où les entiers n'ont pas le même nombre de chiffres *)
                let taille_max = max tx ty in
                (* Je reprends toutes les notations du sujet de TD : *)
                let xp = Array.sub x 0 (taille_max / 2) in
                let xg = Array.sub x (taille_max / 2) (tx-taille_max / 2) in
                let yp = Array.sub y 0 (taille_max / 2) in
                let yg = Array.sub y (taille_max / 2) (ty-taille_max / 2) in
                (* les soustractions nécessaires : *)
                let xg_moins_xp, signe_xg_moins_xp = soustrait xg xp b in
                let yg_moins_yp, signe_yg_moins_yp = soustrait yg yp b in 
                (* les trois appels récursifs *) 
                let xg_fois_yg = karatsuba xg yg b in
                let xp_fois_yp = karatsuba xp yp b in 
                let troisieme_mult = karatsuba xg_moins_xp yg_moins_yp b in
                (* le calcul final *)
                let xg_fois_yg_plus_xp_fois_yp = ajoute xg_fois_yg xp_fois_yp b in
                let terme_milieu = match signe_xg_moins_xp, signe_yg_moins_yp with
                    | 0, 0 | 1, 1 -> fst (soustrait xg_fois_yg_plus_xp_fois_yp troisieme_mult b)
                    | _ -> ajoute xg_fois_yg_plus_xp_fois_yp troisieme_mult b in 
                let gauche = mult_b_puiss_k xg_fois_yg (taille_max - taille_max mod 2) in
                let milieu = mult_b_puiss_k terme_milieu (taille_max / 2) in
                ajoute (ajoute gauche milieu b) xp_fois_yp b
```



---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

