# TD : Bases d'algorithmique

L'objectif du TD est de se familiariser avec le vocabulaire et les structures principales dont nous aurons besoin lorsque nous programmerons. Nous utiliserons ici du pseudo-code, c'est à dire une description de l'algorithme en langage naturel, sans utiliser de langage de programmation.

## Exercice 1 : variables et types de base

Les types de base en algorithmique sont : **entier, flottant, caractère, chaîne de caractères, booléen**. Une **variable** est un emplacement mémoire dans lequel on stocke une donnée, elle est identifiée par son nom. En pseudo-code, on **affecte** une valeur à une variable ainsi : `nom_variable` $`\leftarrow`$ `valeur`.

1. Rappelez les 5 opérations de base typiquement réalisables avec des entiers.

2. Qu'est-ce qu'un flottant ? Quel est le danger lorsqu'on effectue des opérations avec des flottants ?

3. Qu'est-ce qu'un booléen ? Quels sont les 3 opérations de base réalisables avec des booléens ?

4. Rappelez en quoi consiste la concaténation et la duplication sur les chaînes de caractères.

5. Quels sont les 6 opérations de comparaison existantes en programmation ?

6. Expliquez sous quelle condition l'instruction suivante ne déclenche pas d'**exception** : `x < 0 ET 2 / 0 = 1`.

7. Donnez l'état des variables à la fin de l'exécution de chacun des 3 programmes suivants :

    $`\begin{array}{ll} a \leftarrow 1 \\b \leftarrow a \\ a \leftarrow 2 \\ b \leftarrow b + 3\end{array} \;\;\;\;\;\;\;\;\;\;\;\;\;\;\; \begin{array}{ll}x \leftarrow 1 \\y \leftarrow 2 \\ z \leftarrow y \\ y \leftarrow x \\ x \leftarrow z\end{array} \;\;\;\;\;\;\;\;\;\;\;\;\;\;\; \begin{array}{ll}a \leftarrow 1 \\b \leftarrow 2 \\ c \leftarrow a + b \\ b \leftarrow c - b \\ c \leftarrow c + b\end{array}`$

8. Donnez une séquence d'instructions permettant d'échanger les valeurs de deux variables `a` et `b`.

9. Pour chacune des 2 séquences suivantes, remettez les instructions dans l’ordre pour que suite à l'exécution de la séquence, la valeur associée à la variable `chaine2` soit "oh oh oh !" :

    $`\begin{array}{ll}\text{chaine1} \leftarrow \text{"oh "} \\\text{chaine2} \leftarrow \text{chaine2 + "!"} \\ \text{chaine2} \leftarrow \text{coeff} * \text{chaine1} \\ \text{coeff} \leftarrow 3\end{array} \;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\; \begin{array}{ll}\text{chaine1} \leftarrow \text{"oh "} \\ \text{chaine1} \leftarrow \text{"oh !"}\\ \text{chaine2} \leftarrow \text{chaine2 + "!"} \\ \text{coeff2} \leftarrow \text{coeff - 1} \\ \text{chaine2} \leftarrow \text{coeff} * \text{chaine1} \\ \text{coeff} \leftarrow 3\end{array}`$

## Exercice 2 : structures de base

Les structures élémentaires permettant d'écrire un algorithme sont :

* les **instructions conditionnelles** : `SI condition ALORS instructions_si_vrai SINON instructions_si_faux FIN SI`
* les **boucles bornées** : `POUR variable_de_boucle ALLANT DE valeur_depart A valeur_arrivee FAIRE instructions_a_répéter FIN POUR`
* les **boucles non bornées** : `TANT QUE condition FAIRE instructions_a_répéter FIN TANT QUE`
* les **fonctions** : `FONCTION nom_fonction (liste_des_paramètres) : code_de_la_fonction FIN FONCTION`

1. Écrivez une fonction qui prend en paramètres 2 entiers : un numéro de jour et un numéro de mois, et affecte à une variable `saison` une des chaînes de caractères "printemps", "été", "automne", "hiver" en fonction de la saison.
2. Une année est bissextile si l’année est divisible par 4 et non divisible par 100, ou bien si l’année est divisible par 400. Écrivez une fonction qui prend une année en paramètre et renvoie un booléen indiquant si elle est bissextile.
3. Écrivez une fonction qui calcule $`\displaystyle\sum_{i=0}^n i\;\text{ avec }n\in\mathbb{N}`$.
4. Écrivez une fonction qui calcule $`n^p`$ en utilisant uniquement des multiplications.
5. Écrivez une fonction qui compte le nombre de voyelles d'une chaîne.
6. Écrivez une fonction qui détermine si une chaîne est un palindrome.
7. Écrivez un programme qui permet de déterminer à partir de quel entier `n`, $`\displaystyle\prod_{i=1}^n i`$ dépasse 5000.
8. Les cheveux d'Elsa mesurent actuellement 21 centimètres. Elle souhaite les couper quand ils atteindront 50 centimètres. Chaque jour la longueur de ses cheveux augmente de 1%. Écrivez un programme qui calcule dans combien de jours Elsa devra couper ses cheveux.
9. Écrivez une fonction qui vérifie si un entier `p` est premier.

## Exercice 3 : tableaux

Un **tableau** est une collection d'éléments ordonnés. Chaque élément est repéré par son **indice**, allant de 0 (premier élément) à la taille du tableau moins un (dernier élément). Pour parcourir un tableau, on fait une boucle sur les indices des éléments.

1. Écrivez une fonction qui prend en paramètre un tableau d'entiers et renvoie la somme de ses éléments.
2. Écrivez une fonction qui prend en paramètre un tableau et une valeur et qui renvoie le nombre d'occurrences de la valeur dans le tableau.
3. Écrivez une fonction qui prend en paramètre un tableau et une valeur et qui renvoie l'indice de la première occurrence de la valeur dans le tableau.
4. Même question pour la dernière occurrence.
5. Écrivez une fonction qui prend en paramètre un tableau d'entiers et renvoie le maximum.
6. Écrivez une fonction qui prend en paramètre un tableau d'entiers et renvoie l'indice du minimum.

## Pour aller plus loin : récursivité

Voici un exemple de fonction **récursive** permettant de calculer $`n!\text{ avec }n\in\mathbb{N}`$ :

```
FONCTION factorielle (n) :
	SI n = 0 ALORS
		RENVOYER 1
	SINON
		RENVOYER n * factorielle (n-1)
	FIN SI
FIN FONCTION
```

1. Écrivez une fonction récursive permettant de calculer $`\displaystyle\sum_{i=0}^n i\;\text{ avec } n\in\mathbb{N}`$.

2. Écrivez une fonction récursive permettant de calculer $`x^n\;\text{ avec }n\in\mathbb{N}`$.

3. Écrivez une fonction récursive permettant de calculer $`n\times p`$ en ne faisant que des additions.

4. Écrivez une fonction récursive permettant de calculer les termes de la suite de Fibonacci définie pour tout entier naturel par : $`U_n = \begin{cases}     0 & \text{si } n = 0    \\ 1 &\text{si } n=1 \\ U_{n-1} + U_{n-2}& \text{sinon} \end{cases}`$

5. Écrivez une fonction récursive permettant de calculer le PGCD de deux entiers positifs :

    $`\begin{cases} pgcd(u, 0) = u \\ pgcd(u, v) = pgcd(v, r) \; \; \text{avec }r \text{ le reste de la division euclidienne de }u \text{ par } v\end{cases}`$


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
