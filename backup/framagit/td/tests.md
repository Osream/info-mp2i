# TD : Tests

```c
void triangle(int j, int k, int l) {
    assert(j >= 0 && k >= 0 && l >= 0);
    int eg = 0;
    if (j+k <= l || k+l <= j || l+j <= k) {
    	printf("impossible");
    }
    else {
        if (j == k) { eg += 1; }
        if (l == k) { eg += 1; }
        if (l == j) { eg += 1; }
        if (eg == 0) { printf("scalene"); }
        else if (eg == 1) { printf("isocele"); }
        else { printf("equilateral"); }
    }
}
```

1. Dessinez le graphe de flot de contrôle de cette fonction.
2. Donnez le chemin du graphe correspondant à l'exécution de la fonction sur l'entrée `j=3, k=5, l=3`.
3. Donnez un ensemble de chemin respectant le critère de couverture des sommets. Pour chacun de ces chemins, réalisez une exécution symbolique afin de trouver un test correspondant.
4. Même question avec un critère de couverture des arcs.
5. Modifiez le graphe et ajoutez des tests pour que les conditions soient testées de manière exhaustive.
6. Trouvez un chemin infaisable.
7. Écrire une fonction en OCaml et/ou en C pouvant correspondre au graphe suivant (`T` est un tableau d'entiers) :

    ![](/home/sunshine/Documents/pro/mp2i_prof/td/img/flot_controle.png){width=35%}

8. Écrire un jeu de test complet respectant le critère de couverture des arcs. Il faut donc : trouver un ensemble de chemin faisables qui couvrent ce critère, réaliser une exécution symbolique pour chacun de ces chemins pour trouver une valeur de test, puis trouver à la main la sortie attendue pour chaque valeur.

9. Complétez votre jeu de tests par des tests « boîte noire » (limites, partitionnement des entrées...).

On considère la fonction suivante :

```c
int recherche_simple(int t[], int taille, int val) {
    bool trouve = false;
    for (int i = 0; i < taille; i += 1) {
        if (t[i] == val) { trouve = true; }
    }
    return trouve;
}
```

10. Dessinez le graphe de flot de contrôle associé à cette fonction.
11. Donnez un jeu de tests permettant d'assurer le critère de couverture des sommets. Proposez une version fausse de la fonction pour laquelle ce jeu de tests ne détecterait pas d'erreur.
12. Même question pour la couverture des arcs.
13. Si vous avez terminé, écrivez une fonction en C et/ou en OCaml réalisant cette fois une recherche dichotomique ; puis recommencez les trois dernières questions sur votre fonction.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Inspiration : V. Monfleur (fonction `triangle`)

Source des images : *production personnelle*
