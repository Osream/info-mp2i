# TD : Chemin de poids maximal

1. Il s'agit d'un problème d'optimisation.

2. Il y a $`n`$ choix possibles pour la case de départ sur la ligne du bas. Ensuite, pour les $`n-1`$ lignes supérieures, on a deux ou trois choix possibles. Le nombre de chemins possibles est donc compris entre $`n\times 2^{n-1}`$ et $`n\times 3^{n-1}`$. La complexité d'une résolution naïve serait donc exponentielle.

3. Un algorithme glouton fait un choix optimal localement, ici il choisit de se déplacer vers la case du damier de valeur maximale parmi celles disponibles.

4. ```ocaml
    let chemin_glouton d =
        let n = Array.length d in
        let chemin = Array.make n 0 in
        (* 1er choix glouton : case de poids maximal de la ligne du bas *)
        for i = 1 to n - 1 do
        	if d.(n-1).(i) > d.(n-1).(chemin.(0)) then
        		chemin.(0) <- i
        done ;
        (* choix suivants : on prend le max des (2 ou 3) cases du dessus *)
        for i = 1 to n - 1 do
        	let colonne_actuelle = chemin.(i-1) in
        	(* on suppose qu'on va se déplacer juste au dessus *)
        	let colonne_suivante = ref colonne_actuelle in
        	(* on regarde si c'est mieux au dessus à gauche *)
        	if colonne_actuelle > 0 && d.(n-1-i).(colonne_actuelle - 1) > d.(n-1-i).(!colonne_suivante) then
        		colonne_suivante := colonne_actuelle - 1 ;
        	(* on regarde si c'est mieux au dessus à droite *)
        	if colonne_actuelle < n-1 && d.(n-1-i).(colonne_actuelle + 1) > d.(n-1-i).(!colonne_suivante) then
        		colonne_suivante := colonne_actuelle + 1 ;
        	chemin.(i) <- !colonne_suivante
        done ;
        chemin
    ```

    ```c
    int* chemin_glouton(int n, int d[n][n]) {
        int* chemin = malloc(n * sizeof(int));
        // 1er choix glouton : case de poids maximal de la ligne du bas
        int colonne_bas = 0;
        for (int i = 1; i < n; i += 1) {
            if (d[n-1][i] > d[n-1][colonne_bas]) {
                colonne_bas = i;
            }
        }
        chemin[0] = colonne_bas;
        // choix suivants : on prend le max des (2 ou 3) cases du dessus
        for (int i = 1; i < n; i += 1) {
            int colonne_actuelle = chemin[i-1];
            // on suppose qu'on va se déplacer juste au dessus
            int colonne_suivante = colonne_actuelle;
            // on regarde si c'est mieux au dessus à gauche
            if (colonne_actuelle > 0 && d[n-1-i][colonne_actuelle-1] > d[n-1-i][colonne_suivante]) {
                colonne_suivante = colonne_actuelle - 1;
            }
            // on regarde si c'est mieux au dessus à droite
            if (colonne_actuelle < n-1 && d[n-1-i][colonne_actuelle+1] > d[n-1-i][colonne_suivante]) {
                colonne_suivante = colonne_actuelle + 1;
            }
            chemin[i] = colonne_suivante;
        }
        return chemin;
    }
    ```

5. L'algorithme glouton fait un choix optimal localement, et continue ainsi sans anticiper la suite ni revenir en arrière, jusqu'à trouver une solution qui n'est pas toujours optimale globalement, puisque certains chemins ne seront jamais explorés. L'algorithme glouton appliqué au damier donné dans l'énoncé par exemple ne donne pas le chemin de poids maximal : il sélectionne le chemin $`(3, 3) \rightarrow (2, 2) \rightarrow (1, 3) \rightarrow (0, 3)`$ de poids 39, alors que le chemin optimal est de poids 70.

6. $`T_{0,j} = D_{0,j}`$, puisqu'il s'agit du poids maximal pour un chemin allant de la ligne 0 à la ligne 0 (contenant donc, uniquement la case de la ligne 0).

    Pour les lignes suivantes, les sous-problèmes consistent à trouver les (2 ou 3) poids maximaux des chemins allant des (2 ou 3) cases voisines du dessus jusqu'à la ligne 0. On a donc la relation de récurrence suivante : $`T_{i, j} = D_{i, j} + \max(T_{i-1, j-1} , T_{i-1, j} , T_{i-1, j+1})`$ pour $i > 0$. Pour la première colonne et dernière colonne, il n'y a que deux valeurs dans le 'max'.

7. On est confrontés à un problème d'optimisation avec chevauchement des sous-problèmes, la programmation dynamique est donc pertinente. Pour repérer les chevauchements, il faut dessiner l'arbre d'appels (une profondeur 2 suffit).

8. On obtient la matrice :

    ```
    47   7   2   4
    49  48  15  17
    54  57  55  21
    58  60  59  70
    ```

    Les cas de base, remplis en premier, sont sur la ligne du haut.

    Les cas récursifs sont les autres lignes, remplies de haut en bas.

    Le poids du chemin optimal est finalement le maximum des valeurs de la ligne tout en bas (ici 70).

9. ```ocaml
    let poids_max_bottom_up d =
    	let n = Array.length d in
    	(* création de la structure *)
    	let t = Array.make_matrix n n (-1) in
    	(* initialisation des cas de base *)
    	for j = 0 to n - 1 do
    		t.(0).(j) <- d.(0).(j)
    	done ;
    	(* boucle pour remplir le reste de la structure *)
    	for i = 1 to n - 1 do
    		(* je traite la première et dernière colonne à part car il n'y a que 2 voisins *)
    		t.(i).(0) <- d.(i).(0) + max t.(i-1).(0) t.(i-1).(1) ;
    		t.(i).(n-1) <- d.(i).(n-1) + max t.(i-1).(n-2) t.(i-1).(n-1) ;
    		for j = 1 to n - 2 do
    			t.(i).(j) <- d.(i).(j) + max (max t.(i-1).(j-1) t.(i-1).(j)) t.(i-1).(j+1)
    		done
    	done ;
    	(* extraction du résultat (ici on cherche le max de la ligne n-1) *)
    	let maxi = ref (-1) in
    	for j = 0 to n - 1 do
    		if !maxi < t.(n-1).(j) then
    			maxi := t.(n-1).(j)
    	done ;
    	!maxi
    ```

    ```c
    int max(int a, int b) {
        if (a < b) {
            return b;
        }
        return a;
    }
    int poids_max_bottom_up(int n, int d[n][n]) {
        // création de la structure
        int** t = malloc(n * sizeof(int*));
        for (int i = 0; i < n; i += 1) {
            t[i] = malloc(n * sizeof(int));
            for (int j = 0; j < n; j += 1) {
                t[i][j] = -1;
            }
        }
        // initialisation des cas de base
        for (int j = 0; j < n; j += 1) {
            t[0][j] = d[0][j];
        }
        // boucle pour remplir le reste de la structure
        for (int i = 1; i < n; i += 1) {
            t[i][0] = d[i][0] + max(t[i-1][0] , t[i-1][1]);
            t[i][n-1] = d[i][n-1] + max(t[i-1][n-2] , t[i-1][n-1]);
            for (int j = 1; j < n-1; j += 1) {
                t[i][j] = d[i][j] + max (max (t[i-1][j-1] , t[i-1][j]), t[i-1][j+1]);
            }
        }
        // extraction du résultat (ici on cherche le max de la ligne n-1)
        int maxi = -1;
        for (int j = 0; j < n; j += 1) {
            if (maxi < t[n-1][j]) {
                maxi = t[n-1][j];
            }
        }
        // attention aux fuites de mémoire
        for (int i = 0; i < n; i += 1) {
            free(t[i]);
        }
        free(t);
        return maxi;
    }
    ```

10. ```ocaml
    (* fonction auxiliaire récursive avec mémoïsation qui remplit t.(i).(j) *)
    let rec remplir d t i j =
        if t.(i).(j) = -1 then (* on vérifie que c'était pas déjà rempli *)
            if i = 0 then (* cas de base *)
                t.(i).(j) <- d.(i).(j)
            else begin (* cas récursif *)
                (* on remplit t pour la case au dessus *)
                let maxi = ref (remplir d t (i-1) j) in
                (* pour la case au dessus à gauche si elle existe *)
                if j > 0 then
                    maxi := max !maxi (remplir d t (i-1) (j-1)) ;
                (* pour la case au dessus à droite si elle existe *)
                if j < Array.length d - 1 then
                    maxi := max !maxi (remplir d t (i-1) (j+1)) ;
                (* mémoïsation du résultat *)
                t.(i).(j) <- !maxi + d.(i).(j)
                end ;
        t.(i).(j)
        
    (* fonction principale *)
    let poids_max_top_down d =
        let n = Array.length d in
        (* création de la structure *)
        let t = Array.make_matrix n n (-1) in
        (* on lance la fonction remplir avec les valeurs qui nous intéressent, c'est-à-dire les cases de la dernière ligne *)
        let poids_max = ref 0 in
        for j = 0 to n - 1 do
            poids_max := max !poids_max (remplir d t (n-1) j)
        done ;
        !poids_max
    ```

    ```c
    // remarque : je réutilise la fonction 'max' définie dans la question précédente
    // fonction auxiliaire récursive avec mémoïsation qui remplit t[i][j]
    int remplir (int n, int d[n][n], int** t, int i, int j) {
        if (t[i][j] == -1) { // on vérifie que c'était pas déjà rempli
            if (i == 0) { // cas de base
                t[i][j] = d[i][j];
            }
            else { // cas récursif
                // on remplit t pour la case au dessus
            	int maxi = remplir(n, d, t, i-1, j);
                if (j > 0) {
                    // pour la case au dessus à gauche si elle existe
                    maxi = max(maxi, remplir(n, d, t, i-1, j-1));
                }
                if (j < n-1) {
                    // pour la case au dessus à droite si elle existe
                    maxi = max(maxi, remplir(n, d, t, i-1, j+1));
                }
            	t[i][j] = maxi + d[i][j]; // mémoïsation du résultat
            }
        }
        return t[i][j];
    }
    int poids_max_top_down(int n, int d[n][n]) {
        // création de la structure
        int** t = malloc(n * sizeof(int*));
        for (int i = 0; i < n; i += 1) {
            t[i] = malloc(n * sizeof(int));
            for (int j = 0; j < n; j += 1) {
                t[i][j] = -1;
            }
        }
        // on lance la fonction remplir avec les valeurs qui nous intéressent, c'est-à-dire les cases de la dernière ligne
        int poids_max = 0;
        for (int j = 0; j < n; j += 1) {
            poids_max = max(poids_max, remplir(n, d, t, n-1, j));
        }
        // attention aux fuites de mémoire
        for (int i = 0; i < n; i += 1) {
            free(t[i]);
        }
        free(t);
        return poids_max;
    }
    ```

11. On est passés d'une complexité exponentielle (à cause des chevauchements) à une complexité quadratique (la valeur de chaque case de $`T`$ est calculée une seule fois = $`n^2`$ opérations, puis on parcourt une ligne de $`T`$ pour trouver le poids maximal = $`n`$ opérations).

12. La complexité spatiale correspond à la taille de la structure de données $`T`$ (le reste a une taille négligeable à côté). La complexité spatiale est donc quadratique également. Utiliser un tableau associatif n'aurait rien changé car aucune case du tableau n'est inutilisée. Cependant, en réalité, pour calculer les poids maximaux de la ligne $`i`$, nous avons besoin uniquement de ceux de la ligne $`i-1`$ (et plus des lignes précédentes). On pourrait donc se ramener à une complexité spatiale linéaire.

13. ```ocaml
     let chemin_prog_dyn d =
     	let n = Array.length d in
     	(* création de la structure *)
     	let t = Array.make_matrix n n (-1) in
     	(* on lance la fonction remplir avec les valeurs qui nous intéressent, c'est-à-dire les cases de la dernière ligne *)
     	let poids_max = ref 0 in
     	let colonne = ref (-1) in (* en gardant en mémoire l'indice de la colonne qui donne le max *)
     	for j = 0 to n - 1 do
     		let poids = remplir d t (n-1) j in (* j'utilise la fonction remplir de la question précédente *)
     		if !poids_max < poids then begin
     			poids_max := poids ;
     			colonne := j
     		end
     	done ;
     	let chemin = Array.make n !colonne in
     	(* on remonte le chemin grâce à t *)
     	for i = n-2 downto 0 do
     		(* on trouve le voisin vers lequel il faut se déplacer *)
     		if !colonne = 0 then begin
     			(* si la colonne est 0, il faut regarder si on se déplace en colonne 1 ou alors si on reste sur la même colonne *)
     			if t.(i).(!colonne) < t.(i).(!colonne+1) then
     				incr colonne
     		end
     		else if !colonne = n-1 then begin
     			(* si la colonne est n-1, il faut regarder si on se déplace en colonne n-2 ou alors si on reste sur la même colonne *)
     			if t.(i).(!colonne) < t.(i).(!colonne-1) then
     				decr colonne
     		end
     		else begin
     			(* pour les autres colonnes, il faut regarder les 3 voisins *)
     			if t.(i).(!colonne) < t.(i).(!colonne+1) && t.(i).(!colonne-1) < t.(i).(!colonne+1) then
     				incr colonne (* la colonne à droite est mieux *)
     			else if t.(i).(!colonne) < t.(i).(!colonne-1) && t.(i).(!colonne+1) < t.(i).(!colonne-1) then
     				decr colonne (* la colonne à gauche est mieux *)
     			(* pas de else car correspond au cas où la colonne actuelle est mieux *)
     		end ;
     		chemin.(n-1-i) <- !colonne
     	done ;
     	chemin
    ```

     ```c
     int* chemin_prog_dyn(int n, int d[n][n]) {
         // création de la structure
         int** t = malloc(n * sizeof(int*));
         for (int i = 0; i < n; i += 1) {
             t[i] = malloc(n * sizeof(int));
             for (int j = 0; j < n; j += 1) {
                 t[i][j] = -1;
             }
         }
         // on lance la fonction remplir avec les valeurs qui nous intéressent, c'est-à-dire les cases de la dernière ligne
         int poids_max = 0;
         int colonne = -1; // en gardant en mémoire l'indice de la colonne qui donne le max
         for (int j = 0; j < n; j += 1) {
             int poids = remplir(n, d, t, n-1, j); // j'utilise la fonction remplir de la question précédente
             if (poids_max < poids) {
                 poids_max = poids;
                 colonne = j;
             }
         }
         int* chemin = malloc(n * sizeof(int));
         chemin[0] = colonne;
         // on remonte le chemin grâce à t
         for (int i = n-2; i >= 0; i -= 1) {
             // on trouve le voisin vers lequel il faut se déplacer
             if (colonne == 0) {
                 // si la colonne est 0, il faut regarder si on se déplace en colonne 1 ou alors si on reste sur la même colonne
                 if (t[i][colonne] < t[i][colonne+1]) {
                     colonne += 1;
                 }
             }
             else if (colonne == n-1) {
                 // si la colonne est n-1, il faut regarder si on se déplace en colonne n-2 ou alors si on reste sur la même colonne
                 if (t[i][colonne] < t[i][colonne-1]) {
                     colonne -= 1;
                 }
             }
             else {
                 // pour les autres colonnes, il faut regarder les 3 voisins
                 if (t[i][colonne] < t[i][colonne+1] && t[i][colonne-1] < t[i][colonne+1]) {
                     colonne += 1; // la colonne à droite est mieux
                 }
                 else if (t[i][colonne] < t[i][colonne-1] && t[i][colonne+1] < t[i][colonne-1]) {
                     colonne -= 1; // la colonne à gauche est mieux
                 }
                 // pas de else car correspond au cas où la colonne actuelle est mieux
             }
             chemin[n-1-i] = colonne;
         }
         // attention aux fuites de mémoire
         for (int i = 0; i < n; i += 1) {
             free(t[i]);
         }
         free(t);
         return chemin;
     }
     ```

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

