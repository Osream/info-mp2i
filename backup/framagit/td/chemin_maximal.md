# TD : Chemin de poids maximal

On s'intéresse au problème du chemin dans un damier.

On suppose posséder un damier $`D`$ de taille $`n \times n`$, avec $`n \geq 2`$. Chaque case contient une valeur entière positive.

On part du bord inférieur n'importe où et on se déplace jusqu'au bord supérieur n'importe où. Chaque déplacement ne peut se faire que sur la ligne supérieure à celle actuelle, dans l'une des (deux ou trois) cases voisines.

Voici un exemple de damier de taille $`4 \times 4`$, et les déplacements possibles à partir de la case encadrée :

![](/home/sunshine/Documents/pro/mp2i_prof/td/img/chemin_damier.png){width=18%}

On définit le poids d'un chemin comme la somme des valeurs des cases de ce chemin. Par exemple, le poids du chemin $`(3,2) \rightarrow (2,2) \rightarrow (1,3) \rightarrow (0,2)`$ est de $`2+7+13+2=24`$.

On cherche à déterminer le chemin de poids maximal dans un damier $`D`$, représenté par un tableau à 2 dimensions.

1. De quel type de problème s'agit-il ?
1. Une résolution "naïve" (lister tous les chemins possibles et les comparer) est-elle envisageable ? Justifiez.
1. Proposez une stratégie gloutonne pour résoudre ce problème.
1. Implémentez la en C et/ou en OCaml. On renverra un tableau contenant les indices des colonnes sélectionnées. Par exemple, si le chemin $`(3,2) \rightarrow (2,2) \rightarrow (1,3) \rightarrow (0,2)`$ est trouvé par le glouton, alors on renverra un tableau contenant les valeurs `2, 2, 3, 2`, dans cet ordre.
1. Votre algorithme renvoie-t-il toujours le chemin optimal ?

On note $`T_{i,j}`$ le poids maximal obtenu pour un chemin allant de $`(i, j)`$ à la ligne 0 (en haut) dans le damier.

6. Que dire de $`T_{i,j}`$ quand $i=0$ ? Identifiez les sous-problèmes à résoudre et déduisez-en une relation de récurrence pour  $`T_{i,j}`$ quand $i>0$.
7. Montrez que la programmation dynamique est pertinente pour résoudre ce problème.

La structure de données que nous utiliserons pour le stockage est une matrice de même dimension que le damier. La ligne $0 \leqslant i < n$, colonne $0 \leqslant j < n$ de cette matrice contiendra $T_{i, j}$.

8. Dessinez et remplissez la matrice correspondant au damier donné en exemple. Vous indiquerez quelles cases correspondent au cas de base et au cas récursif, ainsi que l'ordre dans lequel vous avez rempli les cases. Déduisez-en le poids du chemin optimal : quelle(s) case(s) de la matrice faut-il regarder ?
9. Écrivez une fonction, en C et/ou en OCaml, qui prend en paramètre un damier $`D`$ et renvoie le poids du chemin maximal dans ce damier, en utilisant une approche itérative de bas en haut (bottom-up).
10. Même question en utilisant cette fois une approche récursive avec mémoïsation (top-down).
11. Justifiez que la programmation dynamique a bien permis d'améliorer la complexité temporelle de la fonction.
12. Discutez de l'impact sur la complexité spatiale. Peut-on faire mieux ?
13. Modifiez vos fonctions pour trouver le chemin dont le poids est maximal, c'est-à-dire pour reconstruire la solution à partir des poids calculés.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*