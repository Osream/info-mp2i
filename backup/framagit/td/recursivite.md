# TD : Récursivité



## Exercice 1 : suite de Fibonacci

La suite de Fibonacci est définie ainsi :  $`F_n = \begin{cases} F_0 = 0 \\ F_1 = 1 \\ F_n =  F_{n-1} + F_{n-2} \; \; \forall n \geq 2 \end{cases}`$.

1. Définissez en OCaml une fonction récursive `fibo n` qui implémente $`F_n`$ avec un filtrage.

2. Définissez une autre version de `fibo n` utilisant une instruction conditionnelle.

3. Définissez en C une fonction récursive `int fibo(int n)`.

4. Dessinez les évolutions de la pile d'appels lors de l'évaluation de `fibo 4`. Quelle est la hauteur maximale de la pile ?

5. Dessinez l'arbre d'appels lors de l'évaluation de `fibo 4`. Y a-t-il des chevauchements ? Si oui, combien ?

6. On appelle $`A_n`$ le nombre d'appels récursifs effectués par l'évaluation de `fibo n`. Démontrez que $`A_n`$ est exponentiel (c'est-à-dire que $`A_n \geq x^{yn}`$ avec `x > 1` et `y > 0` indépendants de `n`).

7. Il est possible d'éviter ces chevauchements en utilisant un accumulateur. Un accumulateur est un argument d'une fonction récursive que l'on va utiliser pour construire le résultat final. L'accumulateur est modifié à chaque appel récursif. Expliquez ce que représentent `a` et `b`  dans le code OCaml suivant :

    ```ocaml
    let rec fibo_acc n a b = match n with
    	| 0 -> b
    	| _ -> fibo_acc (n - 1) (a + b) a
    ```

8. Avec quelles valeurs initiales de `a` et `b` faudrait-il appeler la fonction pour calculer  $`F_n`$ ? Donnez une fonction `fibo n` non récursive qui appelle la fonction `fibo_acc` avec ces valeurs de `a` et `b`.

9. Une fonction récursive est dite *terminale* lorsque l'appel récursif est la dernière instruction effectuée par la fonction (il n'y a aucun calcul à faire une fois l'appel terminé). La fonction `fibo_acc` est-elle récursive terminale ?

10. Donnez le nombre d'appels récursifs $`B_n`$ effectués avec cette méthode lors de l'évaluation de `fibo n`.  Justifiez alors que la récursivité terminale avait ici un réel intérêt.



## Exercice 2 : un peu de construction

On cherche à calculer le nombre de façons différentes qu'il existe pour construire une clôture de longueur `n` en utilisant des barrières de longueur 2 ou 3 uniquement. On appelle ce nombre $`C_n`$.

1. Expliquez pourquoi il faut distinguer deux cas de base : le premier pour $`C_0`$ et $`C_1`$  et le second pour $`C_2`$ et $`C_3`$.
2. De quel(s) terme(s) va dépendre le calcul de  $`C_n`$ pour $`n > 3`$ ? Donnez alors la définition récursive de $`C_n`$.
3. Définissez en OCaml une fonction `cloture n` qui implémente cette définition avec un filtrage.
4. Définissez de même en C une fonction `int cloture(int n)`.
5. Dessinez l'arbre d'appels de l'évaluation de `cloture 10`. Y a-t-il des chevauchements ?
6. Quelle est la hauteur maximale de la pile d'appels ?



## Exercice 3 : appels récursifs imbriqués

Certaines fonctions peuvent réaliser des appels récursifs imbriqués.

1. La fonction d'Ackermann est définie par : $`\begin{cases} ack (0, n) = n + 1 \text{ si } n > 0 \\ ack(m, 0) = ack(m-1, 1)\text{ si } m > 0 \\ ack (m,n) = ack(m-1, ack(m, n-1)) \text{ sinon} \end{cases}`$.

    * Implémentez cette fonction en OCaml avec un filtrage.
    * Calculez à la main $`ack (1, 4)`$. Pourquoi cette fonction peut-elle vite engendrer un *stack overflow* ?
1. Voici une fonction que l'on doit à John McCarthy (le créateur du langage Lisp) : $`f (n) = \begin{cases} n - 10 \text{ si } n > 100 \\ f (f (n+11)) \text{ sinon}\end{cases}`$.

    * Implémentez cette fonction en C.
    * Dessinez les évolutions de la pile d'appels lors de l'évaluation de $`f(99)`$.
    * Calculez à la main $`f(101), f(100), f(99)`$. Peut-on être certain que la fonction va toujours se terminer ?



---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
