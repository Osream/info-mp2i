# Chapitre 11 : Graphes

Les graphes sont des structures de données relationnelles.

Les bases de la théorie des graphes remontent au XVIIIème siècle, où Euler a résolu le problème des 7 ponts de Königsberg en le ramenant à la recherche d'un chemin passant une unique fois par chaque arc d'un graphe (appelé ultérieurement chemin *eulérien*) :

![](img/12_graphes/ponts_konigsberg.png)

Aujourd'hui, les graphes ont de très nombreuses applications.

## I. Définition des graphes orientés et non orientés

### 1. Graphes non orientés

Définition d'un graphe non orienté. Sommets et arêtes.

Exemple de graphe non orienté : ![](img/12_graphes/non_oriente.png)

Boucles et multi-arêtes.

Vocabulaire : voisins, arête incidente.

Propriété : nombre maximal d'arêtes d'un graphe non orienté.

### 2. Graphes orientés

Définition d'un graphe orienté. Sommets et arcs.

Exemple de graphe orienté : ![](img/12_graphes/oriente.png)

Vocabulaire : prédécesseur, successeur.

Propriété : nombre maximal d'arcs d'un graphe orienté.

## II. Vocabulaire de la théorie des graphes

### 1. Degrés dans un graphe

Degré d'un sommet dans un graphe non orienté.

Propriété : lien entre le degré des sommets et le nombre d'arêtes.

Degrés entrant et sortant d'un sommet dans un graphe orienté.

Propriété : lien entre les degrés entrants et sortants des sommets et le nombre d'arcs.

### 2. Notion de sous-graphe

Définition d'un sous-graphe, et d'un sous-graphe induit.

Exemple (à gauche, un sous graphe (sommets noirs et arêtes pleines) ; à droite, un sous-graphe induit): ![](img/12_graphes/sous_graphe.png)

Propriété : nombre de sous-graphes induits dans un graphe.

### 3. Graphes isomorphes

Définition d'un isomorphisme entre deux graphes

Exemple : ![](img/12_graphes/isomorphes.png)

### 4. Chemins dans un graphe

Définition d'un chemin dans un graphe, longueur d'un chemin.

Définition d'un chemin simple et d'un chemin élémentaire.

Les propriétés suivantes sont équivalente :

* il existe un chemin allant du sommet $x$ au sommet $y$
* il existe un chemin simple allant du sommet $x$ au sommet $y$
* il existe un chemin élémentaire allant du sommet $x$ au sommet $y$

Définition d'un cycle (parfois appelé circuit si le graphe est orienté) dans un graphe.

### 5. Notion d'accessibilité dans un graphe

Définition d'un sommet accessible depuis un autre sommet dans un graphe.

Propriété : la relation d'accessibilité dans un graphe non orienté est une relation d'équivalence.

### 6. Connexité

Définitions : connexité d'un graphe non orienté, composantes connexes d'un graphe non orienté.

Propriété : effet de l'ajout d'une arête sur le nombre de composantes connexes.

Définitions : forte et faible connexités dans un graphe orienté, composantes fortement connexes d'un graphe orienté.

Exemples (un graphe fortement connexe et un non fortement connexe (sommet noir non accessible depuis le sommet gris)) : ![](img/12_graphes/forte_connexite.png)

La relation d'accessibilité mutuelle ($x$ accessible depuis $y$ et $y$ accessible depuis $x$) dans un graphe orienté est une relation d'équivalence.

### 7. Coloration de graphes

Définition d'une $k$-coloration d'un graphe.

Nombre chromatique d'un graphe.

Exemple d'application aux graphes d'intervalles :

![](img/12_graphes/intervalles.png)

## III. Graphes particuliers

### 1. Graphes ayant une forme particulière

Graphe entièrement déconnecté.

Graphe complet.

Graphe chemin, graphe cycle.

### 2. Graphes ayant des propriétés particulières

Graphes creux / denses.

Graphes bipartis.

Graphes planaires.

Graphes eulériens et hamiltoniens.

### 3. Arbres dans la théorie des graphes

Définition d'un arbre dans la théorie des graphes.

Propriétés : un graphe non orienté acyclique à possède au plus |S|-1 arêtes ; un graphe non orienté connexe possède au moins |S|-1 arêtes.

Les propriétés suivantes sont équivalentes :

* G est un arbre.
* G est acyclique et a |S|-1 arêtes.
* G est connexe et a |S|-1 arêtes.
* G est minimalement connexe.
* G est maximalement sans cycle.
* Pour tous sommets $x, y$ de G, il existe un unique chemin élémentaire reliant $x$ et $y$.

Définition d'une forêt, d'un arbre enraciné.

Définition d'un arbre couvrant.

### 4. Graphes pondérés

Définition d'un graphe pondéré. Fonction de pondération, poids d'une arête / d'un arc.

Définition du poids d'un chemin.

Intérêt des graphes pondérés.

## IV. Représentation des graphes

### 1. Matrice d'adjacence

Définition de la matrice d'adjacence d'un graphe.

Exemples : ![](img/12_graphes/matrice_adjacence.png)

Propriété : symétrie de la matrice d'adjacence des graphes non orientés.

Propriété : lien entre la diagonale de la matrice et la présence de boucles dans le graphe.

Propriété : puissances de la matrice d'adjacence.

Implémentation en C et en OCaml.

Avantages et inconvénients de cette représentation.

### 2. Liste d'adjacence

Définition de la liste d'adjacence d'un graphe.

Implémentation en C et en OCaml.

Avantages et inconvénients de cette représentation.

### 3. Autres représentations

Graphes implicites.

Sérialisation d'un graphe.

## V. Parcours de graphes

Parcours général d'un graphe.

### 1. Parcours en profondeur

Algorithme récursif du parcours en profondeur.

Arborescence du parcours.

### 2. Parcours en largeur

Algorithme avec une file du parcours en largeur.

Arborescence du parcours.

Définition de la distance dans un graphe non pondéré ; propriété du parcours en largeur : les sommets sont traités dans l'ordre croissant des distances depuis le sommet de départ.

### 3. Algorithme générique

Algorithme générique de parcours de graphe :

```
PARCOURS (G, depart) :
    a_traiter <- structure de données contenant uniquement le sommet depart
    visites <- structure de données marquant les sommets déjà visités (aucun ici)
    TANT QUE a_traiter est non vide :
        s <- extraire un sommet de a_traiter
        SI s n'a pas déjà été visité :
            marquer s comme étant visité
            POUR chaque voisin v de s :
                ajouter v dans a_traiter
```

Si `a_traiter` est une structure munie d'une stratégie LIFO, le parcours est en profondeur ; d'une stratégie FIFO, le parcours est en largeur ; d'une stratégie aléatoire, le parcours est quelconque.

Complexité du parcours.

### 4. Applications des parcours

Tester la connexité d'un graphe non orienté.

Rechercher les composantes connexes d'un graphe non orienté.

Calculer les distances d'un sommet à tous les autres dans un graphe non pondéré.

Déterminer si un graphe est biparti.

Détecter la présence d'un cycle.

### 5. Tri topologique

Propriété : dans tout graphe orienté acyclique, il existe une énumération des sommets $`s_0, s_1, ..., s_{|S|-1}`$ telle que si $`(s_i, s_j) \in A`$, alors $`i<j`$.

Définition d'un ordre topologique.

Propriété : un graphe orienté admet un ordre topologique si et seulement s'il est acyclique.

Tri topologique d'un graphe depuis son parcours en profondeur.

Application : tri topologique d'un graphe de dépendance.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*, J.B. Bianquis
