# TD : Complexité

## Exercice 1

1. $$`1 = 1\times(1+0) \leq C_+(n)\leq \displaystyle\sum_{i=0}^{n-1}{\left(1 + \sum_{j=0}^{n-1} 1\right)} = \sum_{i=0}^{n-1}{\left(1 + n\right)} = n(n+1)`$$

2. La boucle interne effectue 1 comparaison avec `e` par itération. Pour la boucle externe, le nombre de comparaisons avec `e` effectuée correspond au nombre de comparaisons avec `e` effectuées par la boucle interne (il n'y en a aucune autre). Les nombres d'itérations dans le meilleur et dans le pire des cas de chaque boucle sont les mêmes que pour la question précédente. On obtient donc :

    $$`1 = 1\times1 \leqslant C_{\text{comp}}(n)\leqslant \displaystyle\sum_{i=0}^{n-1}{\sum_{j=0}^{n-1} 1} = \sum_{i=0}^{n-1}n = n^2`$$

3. Même raisonnement, mais on compte absolument toutes les opérations élémentaires. Par exemple dans le meilleur des cas, la boucle interne ne fait aucune itération donc on a 4 opérations élémentaires pour cette boucle (celles de la condition), la boucle externe fait 1 seule itération qui possède 8 opérations élémentaires (3 dans la condition, 1 avant la boucle interne, 2 dans la conditionnelle, 2 après la conditionnelle) en plus de celles de la boucle interne, et en dehors on a 8 opérations élémentaires (4 avant la boucle, 3 pour la condition, 1 après la boucle). On compte de même pour le pire des cas, on trouve alors :

    $$`20 = 8 + 1\times(8+4) \leqslant C_{\text{tout}}(n)\leqslant 7 + \displaystyle\sum_{i=0}^{n-1}{\left(7 + \sum_{j=0}^{n-1} 6\right)} =7+ \sum_{i=0}^{n-1}{\left(7 + 6n\right)} = 7+7n+6n^2`$$

4. Dans les trois cas, nous obtenons dans le meilleur cas $`\Omega(1)`$ et dans le pire des cas $`\mathcal O(n^2)`$. Compliquer le calcul en comptant les opérations une par une n'est pas utile, c'est pour cela qu'on regroupe toutes les opérations élémentaires en un seul $`\mathcal O(1)`$.

5. Avec les boucles bornées, le nombre d'itérations est toujours le même (puisqu'on ne peut pas sortir "avant" de la boucle). En notant $C(n)$ la complexité de l'algorithme pour une matrice de taille $n\times n$, on obtient $`C(n) = \displaystyle\sum_{i=0}^{n-1}{\sum_{j=0}^{n-1} \mathcal O(1)} = \sum_{i=0}^{n-1}{\mathcal O\left(\sum_{j=0}^{n-1} 1 \right)} = \sum_{i=0}^{n-1}\mathcal O(n) = \mathcal O\left(\sum_{i=0}^{n-1} n\right) = \mathcal O(n^2)`$.

    La complexité est donc linéaire en le nombre de cases de la matrice.

6. On a 7 opérations dans le cas récursif (2 appels à queue, 1 à tête, 1 à est_vide, 2 additions, 1 multiplication). On en déduit : $C_n = 7 + C_{n-1}$.

7. On reconnaît une suite arithmétique. On trouve ainsi $C_n = C_1 + (n-1)\times 7 = 7n-3$.

8. $7n-3 = \mathcal O(n)$, la complexité de la fonction est donc linéaire en la taille de la liste. Tout comme les algorithmes impératifs, compliquer le calcul en comptant les opérations une par une n'est pas utile, c'est pour cela qu'on regroupe toutes les opérations élémentaires en un seul $`\mathcal O(1)`$. On aurait alors eu la relation de récurrence suivante : $`\begin{cases} C_1 = \mathcal O(1) \\ C_n = \mathcal O(1) + C_{n-1} & \text{pour } n >1\end{cases}`$

## Exercice 2

1. L' « ordre asymptotique » consiste à classer les fonctions en fonction de la manière dont elles croissent quand $`n`$ devient très grand, il s'agit de comparer les $`\mathcal O`$. On obtient : $`f_5 < f_6 < f_1, f_2, f_3 < f_4 < f_8 < f_7`$.

2. * Si $`C_1(n) = \mathcal O(C_2(n))`$ et $`C_2(n) = \mathcal O(C_1(n))`$. Les deux fonctions ont une complexité asymptotiquement équivalentes (elles croissent au même rythme quand $`n`$ devient grand). Attention, elles sont équivalentes et non égales (il y a toujours des constantes cachées dans les $`\mathcal O`$). Pour le montrer, on peut se ramener aux définitions mathématiques des notations de Landau.
   * Si $`C_1(n) = \mathcal O(C_2(n))`$ et $`C_1(n) = \Omega(C_2(n))`$. Même chose que le cas précédent (on peut se ramener à la définition mathématique des notations de Landau, on voit qu'on retrouve la même chose).
   * Si $`C_1(n) = \mathcal O(n^k)`$ et $`C_2(n) = \mathcal O(n^k)`$, avec $`k\in\mathbb N`$. On ne peut absolument rien dire sur les deux fonctions. Le « = » sur les notations de Landau n'a pas le sens habituel. On sait que les deux fonctions ont une complexité qui est au plus polynomiale... mais l'une pourrait très bien être constante et l'autre linéaire par exemple. Elles ne sont en aucun cas égales ni même équivalentes.

3. Le nombre de chiffres nécessaires pour écrire $`n`$ est $`\lfloor \log_{10} n\rfloor + 1`$. L'entier $`n`$ a 1 chiffre de plus que $`\left\lfloor \frac n {10} \right\rfloor`$. Ainsi dans le code donné, l'entier `i` "perd" un chiffre à chaque itération, et ce tant qu'il est supérieur à 0. On a donc $`\lfloor \log_{10} n\rfloor + 1`$ itérations (soit une complexité logarithmique).

4. Cette fois-ci, on effectue des divisions par 2 à chaque itération. Avec un raisonnement similaire à celui de la question précédente, cela signifie que l'entier `i` perd un chiffre dans son écriture binaire (base 2) à chaque itération. Il y a donc $`\lfloor \log_{2} n\rfloor + 1`$ itérations. Comme chaque itération est en $`\mathcal O(1)`$ (trois dé-référencements, une comparaison d'entiers, un affichage, deux opérations arithmétiques, une affectation), la boucle est donc en $`\mathcal O(\log n)`$. L'instruction avant la boucle est de complexité constante, la fonction `affichages` est donc logarithmique.

Dans toute la suite de l'exercice, je note $n$ la taille de la structure de données (c'est-à-dire la taille du tableau `t` en C, et de la liste `l` en OCaml). Je note alors $C(n)$ la complexité de la fonction.

5. Pour chaque élément de la structure, il faut le comparer à tous les autres éléments, chaque comparaison étant en $\mathcal O(1)$ (car la structure contient des entiers).
2. Si la structure est triée, deux éléments égaux (doublon) sont forcément consécutifs. Pour chaque élément de la structure, il ne faut donc plus que le comparer au suivant (chaque comparaison étant toujours en $\mathcal O(1)$).
3. Si on ne trie pas : $`\mathcal O(n^2)`$. Si on trie : $`n \log n + n = \mathcal O(n \log n)`$. Trier est plus efficace !

4. ```c
    bool doublons_trie(int t[], int n) { // n est la taille de t
        for (int i = 0; i < n - 1; i += 1) {
            if (t[i] == t[i+1]) {
                return true;
            }
        }
        return false;
    }
    ```

    Une itération de la boucle est en $\mathcal O(1)$ car toutes les opérations sont élémentaires (opérations arithmétiques, comparaisons d'entiers, accès à un élément d'un tableau d'indice donné, affectation, renvoi). Dans le meilleur des cas, on effectue 1 seule itération (sortie due au `return`) et dans le pire des cas, on effectue autant d'itérations que nécessaire pour que la condition `i < n - 1` soit fausse.

    Les instructions en dehors de la boucle sont en $\mathcal O(1)$.
    
    On trouve donc :
    
    $`1\times \mathcal O(1) \leqslant C(n) \leqslant \mathcal O(1)+\displaystyle\sum_{i=0}^{n-2} \mathcal O(1)`$
    
    On en déduit le meilleur des cas : $`C_n = \Omega(1)`$.
    
    Et le pire des cas : $`\displaystyle C_n =\mathcal O(1) + \mathcal O\left(\sum_{i=0}^{n-2} 1\right) = \mathcal O(1) + \mathcal O(n-1) = \mathcal O(n)`$
    
3. ```c
    bool doublons_non_trie(int t[], int n) { // n est la taille de t
        for (int i = 0; i < n - 1; i += 1) {
            for (int j = i + 1; j < n; j += 1) {
                if (t[i] == t[j]) {
                	return true;
            	}
            }
        }
        return false;
    }
    ```

    Une itération de la boucle interne est en $\mathcal O(1)$ car toutes les opérations sont élémentaires (opérations arithmétiques, comparaisons d'entiers, accès à un élément d'un tableau d'indice donné, affectation, renvoi). Dans le meilleur des cas, on effectue 1 seule itération de la boucle interne (sortie due au `return`) et dans le pire des cas, on effectue autant d'itérations que nécessaire pour que la condition `j < n` soit fausse.

    Une itération de la boucle externe a une complexité en $`\mathcal O(1)`$ + la complexité de la boucle interne. Dans le meilleur des cas, on effectue 1 seule itération de la boucle externe (sortie due au `return`) et dans le pire des cas, on effectue autant d'itérations que nécessaire pour que la condition `i < n-1` soit fausse.
    
    Les instructions en dehors des boucles sont en $\mathcal O(1)$.
    
    On trouve donc :
    
    $`1\times 1 \times\mathcal O(1) \leqslant C(n) \leqslant \mathcal O(1)+\displaystyle\sum_{i=0}^{n-2} \left(\mathcal O(1)+ \sum_{j=i+1}^{n-1} \mathcal O(1)\right)`$
    
    On en déduit le meilleur des cas : $`C_n = \Omega(1)`$.
    
    Et le pire des cas : $`\displaystyle C_n =\mathcal O(1)+\sum_{i=0}^{n-2} \big(\mathcal O(1)+ \mathcal O(n-1-i) \big) =\mathcal O(1)+\sum_{i=0}^{n-2} \mathcal O(n-i) = \mathcal O(1)+\mathcal O\left(\sum_{i=0}^{n-2}n-\sum_{i=0}^{n-2} i\right) = \mathcal O(1) + \mathcal O(n(n-1)-\frac {(n-2)(n-1)} 2) = \mathcal O(1 +(n-1)(n-\frac {n-2} 2)) = \mathcal O(n^2)`$
    
4. ```ocaml
    let rec doublons_trie l = match l with
    	| [] | [_] -> false
    	| t1::t2::q -> t1 = t2 || doublons_trie (t2::q)
    ```

    $`\begin{cases}C_0 = C_1 = \mathcal O(1) \\\mathcal O(1) \leqslant C_n \leqslant \mathcal O(1) + C_{n-1} \;\forall n>1 \end{cases}& \text{  donc } C_n = \mathcal O(n) \text{ et } C_n = \Omega(1)`$.

5. ```ocaml
    let rec doublons_non_trie l = match l with
    	| [] -> false
    	| t::q -> List.mem t q || doublons_non_trie q
    ```

    Pour rappel, `List.mem` est constant dans le meilleur des cas et linéaire dans le pire des cas.

    $`\begin{cases}C_0 = \mathcal O(1) \\ \mathcal O(1) + \mathcal O(1) \leqslant C_n \leqslant \mathcal O(n) + \mathcal O(1) + C_{n-1} \;\forall n>0 \end{cases}& \text{  donc } C_n = \mathcal O(n^2) \text{ et } C_n = \Omega(1)`$.

6. L'implémentation de la structure n'impacte pas ici l'efficacité de la recherche (on obtient les mêmes complexités pour les fonctions correspondantes en C sur les tableaux / en OCaml sur les listes).

## Exercice 3

Dans tous les codes, les opérations en dehors des boucles sont élémentaires, et les opérations dans le corps des boucles sont élémentaires aussi.

De plus il s'agit de boucles bornées qui réalisent toujours le même nombre d'itérations. Pour les boucles bornées « classiques » ou les variables de boucle vont de 1 en 1, il s'agit d'un simple calcul de somme. Pour les boucles où le nombre d'itérations est logarithmique, on peut le justifier avec un raisonnement analogue à ce que nous avons fait en cours pour la recherche dichotomique.

Je rappelle aussi que la base du logarithme n'est pas importante (puisqu'il s'agit d'une constante) : vous pouvez la préciser ou non, cela reste correct.

Je ne détaille pas les calculs (similaires aux exercices précédents) mais n'hésitez pas à me poser la question si vous en avez besoin.

1. $`\mathcal O(n^2)`$
2. $`\mathcal O(n^2)`$
3. $`\mathcal O(\log n)`$
4. $`\mathcal O(\log n)`$
5. $`\mathcal O(n \log n)`$
6. $`\mathcal O(1)`$
7. $`\mathcal O(n^5)`$ (il s'agit du nombre de façons de payer la somme d'argent `n`, cette complexité est améliorable).

## Exercice 4

Dans tous les codes sauf le dernier, toutes les opérations hors appels récursifs ont une complexité constante. On commence par donner une relation de récurrence pour la complexité, et il faut ensuite trouver le terme général pour exprimer la complexité en fonction de `n`. Dans le cas où il faut encadrer la complexité (plusieurs cas récursifs différents), je donne les deux côtés de l'encadrement et donc la complexité dans le meilleur des cas : en réalité elle n'était pas demandée, sans précision supplémentaire de l'énoncé seul le pire des cas est à calculer. Je ne détaille pas les calculs mais n'hésitez pas à me poser la question si vous en avez besoin.

1. $`\begin{cases}C_0 = \mathcal O(1) \\ C_n =\mathcal O(1) + C_{\left\lfloor \frac n 2 \right\rfloor} \;\forall n>0 \end{cases}& \text{  donc } C_n = \mathcal O(\log n)`$

2. $`\begin{cases}C_0 =C_1=C_2= \mathcal O(1) \\ C_n =\mathcal O(1) + C_{n-2} \;\forall n>2 \end{cases}& \text{  donc } C_n = \mathcal O(n)`$

3. $`\begin{cases}C_0 =C_1= \mathcal O(1) \\ C_n =\mathcal O(1) + C_{n-1} + C_{n-2} \;\forall n>1 \end{cases}& \text{  donc } C_n = \mathcal O(2^n)`$

4. $`\begin{cases}C_n = \mathcal O(1)\;\forall n<10 \\ \mathcal O(1) + C_{\left\lfloor \frac n 5 \right\rfloor} \leqslant C_n \leqslant + \mathcal O(1) + C_{n-2} \;\forall n\geqslant10 \end{cases}& \text{  donc } C_n = \mathcal O(n) \text{ et } C_n = \Omega(\log n)`$

5. $`\begin{cases}C_0 = \mathcal O(1) \\ C_n =\mathcal O(1) + C_{\left\lfloor \frac n 2 \right\rfloor} \;\forall n>0 \end{cases}& \text{  donc } C_n = \mathcal O(\log n)`$

    On remarque au passage qu'il s'agit de l'algorithme d'exponentiation rapide.

6. $`\begin{cases}C_{0,0} = \mathcal O(1) \\ C_{0,m} = \mathcal O(1) + C_{0,m-1} = \mathcal O(m)\\ C_{n,0} = \mathcal O(1) + C_{n-1,0} = \mathcal O(n) \\ C_{n,m} =\mathcal O(1) + C_{n-1,m-1} \;\forall n>0,m>0 \end{cases}`$

    Pour trouver le terme général, on peut distinguer deux cas :

    * Si $`n<m, C_{n,m} = \mathcal O(1) \times n + C_{0,m-n} = \mathcal O(n) + \mathcal O(m-n) = \mathcal O(m)`$
    * Sinon, $C_{n,m} = \mathcal O(1) \times m + C_{n-m,0} = \mathcal O(m) + \mathcal O(n-m) = \mathcal O(n)`$

    D'où $`C_{n,m} = \mathcal O(\max(n,m))`$

7. Pour simplifier le calcul, on peut poser $`x = n+m`$ et donner une relation de récurrence pour $`C_x`$. On obtient pour le terme général $`C_x = \mathcal O(x)`$, et on en déduit alors simplement que $`C_{n,m} = \mathcal O(n+m)`$.

8. $`\begin{cases}C_{n,m} = \mathcal O(1) \text{ si } n=m\\ C_{n,m} = \mathcal O(1) + C_{n+1,m} = \mathcal O(m-n) \text{ si } n <m \\ C_{n,m} = \mathcal O(1) + C_{n-1,m} = \mathcal O(n-m) \text{ si } n >m \end{cases}`$

    Donc $`C_{n,m} = \mathcal O(|n-m|)`$

9. On pose ici $n$ la taille de la liste.

    $`\begin{cases}C_{0} = \mathcal O(n) \\ C_{n} = \mathcal O(n) + C_{n-1} \;\forall n>0 \end{cases} & \text{  donc } C_n = \mathcal O(n^2)`$

    Les $`\mathcal O(n)`$ viennent de l'appel (épouvantable) à `List.length`. Merci de ne pas reproduire une telle horreur dans vos copies !

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
