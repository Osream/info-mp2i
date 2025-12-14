# TD: Parcours de Graphes

## Parcours à la main

### q1

$$
\begin{pmatrix}
    0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0\\
    0 & 0 & 1 & 0 & 0 & 0 & 1 & 0 & 0 & 0\\
    1 & 1 & 0 & 0 & 1 & 0 & 1 & 0 & 0 & 0\\
    0 & 0 & 0 & 0 & 1 & 0 & 0 & 1 & 0 & 0\\
    0 & 0 & 1 & 1 & 0 & 1 & 0 & 1 & 0 & 0\\
    0 & 0 & 0 & 0 & 1 & 0 & 1 & 0 & 1 & 0\\
    0 & 1 & 1 & 0 & 0 & 1 & 0 & 0 & 1 & 0\\  
    0 & 0 & 0 & 1 & 1 & 0 & 0 & 0 & 0 & 1\\
    0 & 0 & 0 & 0 & 0 & 1 & 1 & 0 & 0 & 0\\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0
\end{pmatrix}
$$

```OCaml
let adj = [|
    [2];
    [2; 6];
    [0; 1; 4; 6];
    [4; 7];
    [2; 3; 5; 7]:
    [4; 6; 8];
    [1; 2; 5; 8];
    [3; 4; 9];
    [5; 6];
    [7]
|]
```

## Accessibilité dans un graphe

### q9

Si $p \in \mathbb{N}$, alors les matrices $M^p$ représentent les chemins de tailles $p$ dans la matrice.

### q10

```algo
produit <- mat
POUR i ALLANT DE 1 À longeur(mat) FAIRE
    produit <- produit * mat
    SI mat[x][y] <> 0 ALORS
        RENVOYER Vrai
    FIN SI
FIN POUR
RENVOYER Faux
```

Complexité en $O(|S|³)$

### q11

Avec un parcours en largeur. Complexité en $O(|S| + |A|)$

### q12

Vérifier à l'aide d'un parcours en largeur que tous les sommets sont accessible à partir d'un autre. Si un sommet n'est pas accessible, le graphe n'est pas connexe.

## Résoudre une situation concrète à l'aide d'un graphe

![image](ressources/td_parcours_graphes.jpg)
