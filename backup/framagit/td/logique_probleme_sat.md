# TD : Problème SAT

### I. Formes normales

Pour chacune des formules propositionnelles suivantes :

* $`(x \leftrightarrow y)`$
* $`(x \rightarrow ¬y) \land (y\lor(\lnot x \land z))`$
* $`(x\lor y) \lor (¬z \land x)`$
* $`(x\lor ¬y) \land ¬(z \land ¬(u \land w))`$​

1. Indiquez s'il s'agit d'une forme normale négative, conjonctive, disjonctive.
2. Utilisez les équivalences fondamentales afin de déterminer une formule équivalente en FNC / en FND.
3. Dressez sa table de vérité, et en déduire ses FNC / FND canoniques.
4. Appliquez l'algorithme de Quine à la formule. En déduire si elle satisfiable, tautologique, antilogique. Vérifiez à l'aide de la table de vérité dressée à la question précédente.

### II. Problème `k`-SAT

Pour chacune des formules propositionnelles suivantes :

* $`((x\land y)\land (\lnot z \land w)) \land (u \land (\lnot t \land \lnot y))`$​
* $`(x \lor y) \land (w \lor \lnot z) \land (\lnot z \lor x) \land (\lnot w \lor y) \land (\lnot x \lor \lnot y) \land (z\lor \lnot x) \land (\lnot w \lor \lnot y)`$​
* $`(x\lor y) \land \lnot x \land (\lnot z \lor x) \land (\lnot y \lor z)`$
* $`(\lnot x\lor z \lor w) \land (\lnot x \lor y) \land \lnot w \land (z \lor y \lor w\lor x)`$

1. Justifiez qu'il s'agit d'une instance de `k`-SAT, en précisant `k`.
2. En utilisant la méthode de résolution la plus optimale, déterminez si la formule est satisfiable.

### III. Modéliser une situation par une formule propositionnelle

Pour chacune des situations suivantes :

* Voici le curieux règlement d’un club britannique : tout membre non écossais porte des chaussures rouges ; tout membre porte un kilt ou ne porte pas de chaussures rouges ; les membres mariés ne sortent pas le dimanche ; un membre sort le dimanche si et seulement s’il est écossais ; tout membre qui porte un kilt est écossais et marié ; tout membre écossais porte un kilt. Ce règlement permet-il d’accueillir des membres ?
* Vous êtes perdus dans le désert et vous avez le choix entre 2 chemins, gardés par 2 sphinx. Le premier vous dit : « au moins un des chemins conduit à une oasis ». Le second ajoute : « le chemin de droite se perd dans le désert ». Sachant que les deux sphinx disent tous deux la vérité, ou bien mentent tous deux, que faites vous ?
* Vous êtes face à 3 portes de couleurs rouge, verte et bleue. Un sphinx affirme : « la porte rouge n’est pas sûre ou la verte est sûre », « si les portes rouge et verte sont sûres alors la bleue n’est pas sûre », « la porte verte n’est pas sûre mais la bleue est sûre ». On sait que la première et la dernière affirmation sont de même nature (soit vérité, soit mensonge), et que la seconde affirmation est de nature opposée aux deux autres. Par quelle porte passer ?

1. Introduisez les variables propositionnelles nécessaires en explicitant leurs significations.
2. Donnez une formule propositionnelle permettant de modéliser la situation.
3. Appliquez l'algorithme de Quine à la formule et déduisez-en la solution au problème.
4. Simplifiez au maximum la formule à l'aide des équivalences fondamentales, dressez la table de vérité de la formule ainsi simplifiée et vérifiez que vous retrouvez la même solution.

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
