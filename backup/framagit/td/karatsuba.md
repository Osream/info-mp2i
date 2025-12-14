# TD : Algorithme de Karatsuba

On s'intéresse au problème de la multiplication de deux entiers naturels dont on possède l’écriture en base $`b`$. On travaille directement sur l’écriture, on n’effectuera aucune conversion. On considère que multiplier ou ajouter *2 chiffres* est une opération élémentaire, en revanche une opération arithmétique sur *2 nombres* de $`n`$ chiffres chacun n'en est pas une.

### Multiplication naïve

1.   Donner la complexité de l’addition de deux entiers dont les représentations en base $`b`$ comportent $n$ chiffres.
2.   Donner la complexité de la multiplication d’un entier dont la représentation en base $`b`$ comporte $n$ chiffres avec $`b^k`$.
3.   Donner la complexité de la multiplication d’un entier dont la représentation en base $`b`$ comporte $n$ chiffres avec un nombre ayant un unique chiffre en base $`b`$.
4.   On considère la multiplication effectuée comme à l'école primaire : si $`\displaystyle x = \overline{x_{n-1}\dots x_1x_0}^b`$, alors $`\displaystyle y \times x = \sum _{i=0}^{n-1} (x_i\times y)b^i`$. On suppose que $`y`$ s’écrit aussi sur $n$ chiffres. Donner la complexité de cette méthode de multiplication.

### Algorithme de Karatsuba (diviser pour régner)

On considère deux entiers $`x`$ et $`y`$ possédant tous les deux $`2n`$ chiffres. On peut décomposer ces nombres comme ceci : $`x = b^nx_g + x_p \;\text{ et } \;y = b^n y_g + y_p`$. On a alors $`x\times y = b^{2n}x_gy_g+b^n(x_gy_p+x_py_g)+x_py_p`$. Les produits $`x_gy_g,\; x_gy_p,\;x_py_g,\;x_py_p`$ peuvent être calculés récursivement de la même manière, et comme ce sont des produits de nombres de $`n`$ chiffres, on a bien une approche diviser pour régner.

5.   Appliquer cet algorithme pour effectuer le produit $`1237 \times 2587`$.
6.   Pour calculer la complexité $`C(2n)`$ de cet algorithme, il faut donc prendre en compte : les 4 multiplications récursives, les deux produits par une puissance de la base, et les trois additions. Donner une relation de récurrence pour $`C(2n)`$. Exprimer alors $`C(2^k)`$ en fonction de $`k`$. En déduire la complexité de l'algorithme dans le cas général.

L'idée de l'algorithme de Karatsuba est d'éliminer une des multiplications en la remplaçant par des additions (ou soustractions, ce qui revient au même) supplémentaires. Toujours avec $`x = b^nx_g + x_p \;\text{ et } \;y = b^n y_g + y_p`$, on a alors : $`x\times y = b^{2n}x_gy_g+b^n(x_gy_g+x_py_p-(x_g-x_p)(y_g-y_p))+x_py_p`$.

7.   Justifier que ce calcul est bien correct.
8.   Appliquer l'algorithme de Karatsuba au produit $`1237 \times 2587`$.
9.   A-t-on bien toujours une approche « diviser pour régner » ? Quels opérations sont nécessaires désormais pour calculer le produit ? Donner une relation de récurrence pour $`C(2^k)`$, la complexité de cet algorithme. Exprimer alors $`C(2^k)`$ en fonction de $`k`$. En remarquant que $`3^k = (2^k)^{\log_2 3}`$, en déduire la complexité dans le cas général.

### Implémentation

Les fonctions sont présentées en OCaml avec les nombres représentés par des tableaux d'entiers en petit-boutiste, mais vous pouvez les écrire en C si vous le souhaitez, ou bien aussi avec des listes.

10.   Implémenter l’algorithme de multiplication naïve, sans faire aucune conversion. Il est conseillé de décomposer le travail en fonctions auxiliaires :
      *   Une fonction `simplifie : int array -> int array` qui élimine les 0 inutiles dans l'écriture de l’entier donné. Par exemple, `simplifie [|1;0;2;3;0;0|] = [|1;0;2;3|]`.
      *   Une fonction `ajoute : ajoute : int array -> int array -> int -> int array` telle que `ajoute x y b` renvoie la représentation simplifiée de `x+y` en base `b`.
      *   Une fonction `mult_b_puissance_k : int array -> int -> int array` telle que `mult_b_puiss_k x k` renvoie la représentation simplifiée de $`\texttt x \times b^\texttt k`$.
      *   Une fonction `mult_chiffre : int -> int -> int array -> int array` telle que `mult_chiffre b a x` renvoie la représentation simplifiée de $`\texttt a \times \texttt x`$ où `a` est un chiffre et `x` un nombre en base `b`.
      *   Finalement, la fonction `mult_naive : int array -> int array -> int -> int array`.
11.   (Facultatif) Implémenter l’algorithme de Karatsuba.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
