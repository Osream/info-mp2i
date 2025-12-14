# TD : Syntaxe et sémantique des formules logiques



### I. Logique propositionnelle

1. Représentez les arbres syntaxiques des formules propositionnelles suivantes, donnez leurs tailles, hauteurs, et ensembles de leurs sous-formules :
    * $`(x\lor y) \rightarrow (z \lor y)`$
    * $`((x\lor y)\lor ¬z) \land t`$
    * $`x \lor (y \land (¬z \lor t))`$
2. Les formules $`(x\land y)\rightarrow z`$ et $`x\rightarrow(y\rightarrow z)`$ sont-elles syntaxiquement équivalentes ? sémantiquement équivalentes ? Justifier en donnant leurs représentations arborescentes et en dressant leurs tables de vérité.
3. Même question pour les formules $`(((x\leftrightarrow y)\land y)\rightarrow x)`$ et $`((x\leftrightarrow y)\land y)\rightarrow x`$.
4. On considère les formules $`\varphi = x \lor y, \psi = x \rightarrow y\text{ et }\omega = \varphi \rightarrow \psi`$.
    * Dressez les tables de vérité de ces trois formules.
    * Quelles valuations donnent la même valeur de vérité aux formules $`\varphi \text{ et }\psi`$ ?
    * Quel est l'ensemble des modèles de $`\omega`$ ?
    * Une formule est dite *contingente* si elle est satisfiable sans être tautologique. Les trois formules $`\varphi, \psi \text{ et }\omega`$ sont-elles contingentes ?
    * Déterminez, parmi les conséquences sémantiques suivantes, lesquelles sont correctes : $`\varphi \vDash \psi \;;\;\; \psi \vDash \varphi \;;\;\; \varphi\vDash \omega \;;\;\; \psi \vDash \omega \;;\;\; \{\varphi, \psi\}\vDash \omega`$.
5. On considère les formules $`\varphi = x \land (¬y \rightarrow (y \rightarrow x)) \text{ et } \psi = (x\lor y)\leftrightarrow (¬x \lor ¬y)`$.
    * Si $v$ est une valuation, quand cela est possible, et sans dresser la table de vérité, déterminez $`[\![\varphi]\!]_v`$ et $`[\![\psi]\!]_v`$ dans les cas suivants :
        * $`v(x) = \texttt{F}, v(y) = \texttt{V}`$
        * $`v(x) = \texttt{F}`$
        * $`v(y) = \texttt{F}`$
    * Ces formules sont-elles satisfiables ? tautologiques ? antilogiques ?
    * Un ensemble de formules est dit consistant s'il existe au moins une valuation qui est un modèle de chacune de ses formules. L'ensemble $`\Gamma = \{\varphi, \psi\}`$ est-il consistant ?
6. Parmi les trois formules logiques $`\varphi_1 = (x \rightarrow y)\rightarrow y, \varphi_2 = x\rightarrow (y \rightarrow x), \varphi_3 = (x \land y)\leftrightarrow(x\rightarrow ¬y)`$, identifiez à l'aide des tables de vérité la tautologie et l'antilogie. Que dire de l'autre formule ?
7. Montrez que toute formule $`\varphi`$ est une tautologie si et seulement si $`¬\varphi`$ est insatisfiable.
8. * Montrez les lois de De Morgan.
     * Montrez les lois de distributivité.
     * Montrez la décomposition de l'implication, le tiers exclus, l'idempotence et la double négation.
9. Montrez, *de deux manières différentes*, que $((\varphi \rightarrow \psi) \land \varphi) \rightarrow \psi$ est une tautologie.
10. Le système de connecteurs $`\{\lnot, \lor\}`$ est-il complet ? Et le système $`\{\downarrow\}`$ ("nor" défini par $`\varphi \downarrow \psi \equiv \lnot(\varphi\lor\psi)`$) ?
11. Avec une équivalence sémantique et des substitutions, comment définir le quantificateur universel ? existentiel ?



### II. Logique du premier ordre

1. On considère la formule propositionnelle suivante : $`\forall x.\forall y. \exists z. ¬(x < y)\lor ((x < z)\land (z<y))`$.

    * Dessinez sa représentation arborescente.
    * Quel est son domaine ?
    * Quels sont ses termes ? ses atomes ?
    * Comporte-t-elle des variables libres ? liées ? Quelle est la portée des variables ?

2. Traduisez, en introduisant les prédicats nécessaires, les phrases suivantes en logique du premier ordre :

    * Dans une école, il existe des ordinateurs non connectés au réseau local.
    * Dans les écoles, tous les ordinateurs sont connectés à un réseau local.
    * Dans chaque école, au moins un ordinateur est connecté à la fois au réseau local et à internet.

3. On considère la fonction C suivante qui détermine si un tableau contient un doublon :

    ```c
    bool doublon(int t[], int n) {
        for (int i = 0; i < n; i += 1) {
            for (int j = i+1; j < n; j += 1) {
                if (t[i] == t[j]) { return true; }
            }
        } return false;
    }
    ```

    * Pour chaque formule suivante, donnez une traduction "en français" et un exemple de tableau vérifiant la formule. Laquelle exprime effectivement le plus fidèlement la présence d'un doublon ?
        * $`\forall i \in [0,n[. \forall j \in [0,n[. i \neq j \rightarrow t[i]=t[j]`$
        * $`\forall i \in [0,n[. \exists j \in [0,n[. i \neq j \land t[i]=t[j]`$
        * $`\exists i \in [0,n[. \forall j \in [0,n[. i \neq j \rightarrow t[i]=t[j]`$
        * $`\exists i \in [0,n[. \exists j \in [0,n[. i \neq j \land t[i]=t[j]`$
    * Donnez les invariants pour les deux boucles de la fonction, écrits comme des formules du premier ordre.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
