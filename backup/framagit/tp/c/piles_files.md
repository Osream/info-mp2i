# TP : Implémentation de piles et files en C

Nous allons utiliser les listes, piles et files à plusieurs reprises lors d'autres TP cette année. **Il faut donc impérativement qu'à la fin de ce TP vous ayez au moins une implémentation de chacune de ces trois structures entièrement fonctionnelle.**

## I. Implémentation d'une file avec des maillons chaînés

> 1. Créez trois fichiers :
>
>     * `file.h` contiendra l'interface d'une file ;
>     * `file.c` contiendra l'implémentation ;
>     * `file_tests.c` contiendra quelques tests pour vérifier que l'implémentation est correcte.
>
>     Ajoutez les directives nécessaires dans ces trois fichiers.
>
> 2. Ajoutez *dans le bon fichier* un alias `contenu_file` vers un entier. Quel est l'intérêt de faire cela ?
>
> 3. Ajoutez *dans le bon fichier* une structure pour représenter un maillon, puis un alias `maillon` vers cette structure.

Nous allons réaliser ici l'implémentation la plus classique d'une file : une file sera la donnée d'un pointeur sur le premier maillon et d'un pointeur sur le dernier maillon de la chaîne :

```c
struct file_s {
    maillon* premier;
    maillon* dernier;
};

typedef struct file_s* file;
```

On enfile au niveau du dernier maillon et on défile au niveau du premier. 

> 4. Copiez ces lignes *dans les bons fichiers*.
> 5. Que vaudront les champs `premier` et `dernier` pour la file vide ?
> 6. Schématisez avec cette représentation une file dans laquelle on aurait enfilé successivement 2, puis 7, puis 4.

L'interface d'une file est :

```c
/*
Entrée : aucune.
Précondition : aucune.
Sortie : une file.
Postcondition : la file renvoyée est vide.
*/
file creer_file(void);

/*
Entrée : une file.
Précondition : le pointeur n'est pas NULL.
Sortie : un booléen.
Postcondition : renvoie true si la file est vide, false sinon.
*/
bool est_vide_file(file);

/*
Entrée : une file et un contenu.
Précondition : le pointeur n'est pas NULL.
Sortie : aucune.
Postcondition : le contenu a été enfilé dans la file.
*/
void enfiler(file, contenu_file);

/*
Entrée : une file.
Précondition : le pointeur n'est pas NULL, la file n'est pas vide.
Sortie : un contenu.
Postcondition : le contenu renvoyé est celui qui avait été ajouté en premier dans la file (principe FIFO), et la file ne contient plus cet élément.
*/
contenu_file defiler(file);
```

À cette interface principale, nous ajouterons les deux fonctions suivantes :

* `void detruire_file(file)` (destructeur spécifique au C) ;
* `contenu_file tete_file(file)` (donne le prochain élément qui sera défilé, mais sans le défiler).

> 7. Copiez cette interface dans le bon fichier, en ajoutant les spécifications pour les fonctions `detruire_file` et `tete_file`.
> 8. Implémentez les fonctions `creer_file, est_vide_file, tete_file`. Pensez aux assertions nécessaires (vérification après le `malloc` et vérification des préconditions).
> 9. Implémentez la fonction `enfiler`. Il faudra distinguer le cas particulier où la file était vide. Pensez aux assertions.
> 10. Implémentez la fonction `defiler`. Il faudra distinguer le cas particulier où la file devient vide (on a défilé le dernier élément). Pensez aux assertions, et attention aux fuites de mémoire !
> 11. Implémentez pour finir la fonction `detruire_file`. Il faut détruire chaque maillon, puis détruire la structure de la file elle-même.
> 12. Compilez le fichier `file.c` pour obtenir un fichier objet `file.o`.
> 13. Ajoutez dans le fichier `file.h` les complexités des fonctions (à la fin de leurs spécifications).

Pour valider notre module avant de s'en servir dans d'autres programmes, nous avons besoin de faire des tests. Nous aurons besoin d'une fonction de tests par fonction de l'interface (sauf le destructeur).

> 14. Dans le fichier `file_tests.c`, copiez la fonction suivante :
>
>     ```c
>     void tests_creer_file() {
>         file f = creer_file();
>         assert(est_vide_file(f));
>         detruire_file(f);
>     }
>     ```
>
>     Le jeu de tests de cette fonction est très simple puisqu'il n'y aucune entrée et une seule postcondition.
>
> 14. Écrivez une fonction `void tests_est_vide_file()` qui contient des tests (via des assertions) pour la fonction `est_vide_file`. Il faudra faire un test pour lequel la fonction est censée renvoyer `true` et un pour lequel la fonction est censée renvoyer `false`.
>
> 15. Écrivez de même 3 fonctions de tests pour chacune des fonctions `tete_file, enfiler, defiler`. Pour `tete_file`, on peut par exemple vérifier qu'après avoir enfilé 1 et 2, la fonction donne bien 1...
>
> 16. Ajoutez ensuite dans votre fichier un main qui appelle chacune de ces fonctions de tests :
>
>     ```c
>     int main() {
>         tests_creer_file();
>         tests_est_vide_file();
>         tests_tete_file();
>         tests_enfiler();
>         tests_defiler();
>     }
>     ```
>
>     Compilez, et exécutez. S'il ne se passe rien, c'est que tous les tests sont passés et que votre programme semble correct. Sinon, c'est qu'il y a une erreur dans votre implémentation...

En C, comme aucune structure n'existe, il est fort probable que vous devrez les implémenter dans les sujets de concours. Il faut donc impérativement que vous sachiez implémenter une file (structures et types + 6 fonctions de l'interface) rapidement.

## II. Implémentation d'une pile avec des maillons chaînés

Une pile sera un pointeur vers le maillon au sommet :

```c
struct pile_s {
    maillon* sommet;
};
typedef struct pile_s* pile;
```

Son interface sera :

* `pile creer_pile(void)` qui crée une pile vide ;
* `bool est_vide_pile(pile)` qui réalise le test de vacuité ;
* `void empiler(pile, contenu_pile)` qui ajoute un élément au sommet de la pile ;
* `contenu_pile depiler(pile)` qui enlève et renvoie l'élément au sommet de la pile ;
* `contenu_pile sommet_pile(pile)` qui renvoie la valeur au sommet de la pile ;
* `void detruire_pile(pile)` qui libère toute la mémoire occupée par la pile.

> 1. Créez trois fichiers `pile.h, pile.c, pile_tests.c`. Placez-y les directives nécessaires, et les types nécessaires (un alias pour le contenu, une structure pour un maillon puis la structure pour la file donnée ci-dessus).
>
> 2. Dans le fichier `pile.h`, ajoutez les déclarations des fonctions, précédées de leurs spécifications (vous pouvez vous inspirer de `file.h`).
>
>     Rédigez le tout proprement, vous serez bien contents d'avoir ce fichier dans plusieurs semaines quand on réutilisera les piles et que vous aurez oublié ce que fait votre code...
>
> 3. Implémentez les 6 fonctions sur les piles dans le fichier `pile.c`. Pensez aux assertions (vérification après le `malloc` et vérification des préconditions).
>
> 4. Ajoutez les complexités dans le fichier d'interface.
>
> 5. Pour chaque fonction (sauf le destructeur), écrivez une fonction de tests correspondante dans le fichier `pile_tests.c`.
>
> 6. Vérifiez que tout est correct, en compilant *correctement* les fichiers nécessaires.

En C, comme aucune structure n'existe, il est fort probable que vous devrez les implémenter dans les sujets de concours. Il faut donc impérativement que vous sachiez implémenter une pile (structures et types + 6 fonctions de l'interface) rapidement.

## III. Autres implémentations

*Il est essentiel que vous sachiez implémenter une liste ou une pile en maximum 5mn, une file en maximum 10mn. Entraînez-vous régulièrement à re-créer les types nécessaires et à re-écrire les fonctions de l'interface. De nombreux algorithmes au programme du second semestre utilisent ces structures.*

Cette partie vise à étudier et programmer d'autres implémentations possibles des piles et des files.

> **Implémentation d'une file avec un tableau circulaire**
>
> Nous allons maintenant réaliser une autre implémentation d'une file utilisant un tableau circulaire. On supposera que la taille de la structure ne dépasse jamais un entier constant `TAILLE_MAX`. Autrement dit, on utilisera un tableau de taille statique (on ne le redimensionnera pas).
>
> Voici les types nécessaires :
>
> ```c
> struct file_s {
>     int debut;
>     int fin;
>     contenu_file* elts;
> };
> typedef struct file_s* file;
> ```
>
> Une file est donc définie par trois champs :
>
> * le tableau `elts` qui contient les éléments de la file, de taille `TAILLE_MAX`
> * l'indice de début de la file (où est rangé le prochain élément à défiler)
> * l'indice de fin de la file (où doit être rangé le prochain élément à enfiler)
>
> Attention, on utilise un tableau circulaire, il est donc tout à fait possible d’avoir `fin < debut`. Une conséquence de ce choix est que l’égalité `fin = debut` ne permet pas de distinguer entre la file vide et la file pleine ; pour palier à ce problème, on s’interdit de remplir complètement le tableau : ainsi, on décrète qu’une file qui contient `TAILLE_MAX − 1` éléments est pleine, situation caractérisée par l’égalité : `(fin + 1) % TAILLE_MAX = debut`.
>
> 1. Créez un fichier `file_tableau.c`, définissez une constante `TAILLE_MAX` avec la valeur de votre choix, puis implémentez les 6 fonctions de l'interface d'une file.
> 2. A-t-on besoin d'un nouveau fichier d'interface pour notre nouvelle implémentation ? D'un nouveau fichier de tests ?

> **Implémentation d'une pile avec un tableau**
>
> 3. De manière similaire à l'exercice précédent, implémentez une pile avec un tableau de taille maximale fixée. A-t-on besoin de 2 indices comme pour les files ?

> **Implémentation d'une file avec deux piles**
>
> Il est possible d'implémenter une file en utilisant deux piles :
>
> * une pile "entrée" dans laquelle on ajoute les nouveaux éléments à enfiler.
> * une pile "sortie" dans laquelle on extrait les éléments à défiler.
>
> Si la pile "sortie" est vide au moment de défiler un élément, on retourne la pile "entrée" dans la pile "sortie". Le principe est le même que ce que nous avons vu en cours pour l'implémentation d'une file avec deux listes chaînées.
>
> 4. Implémentez une file à l'aide de deux piles.

> **Implémentation d'une file avec des maillons doublement chaînés circulaires**
>
> 5. Commencez par faire des schémas, puis écrivez les fonctions sur les files avec cette implémentation.

## Pour aller plus loin

> 1. Implémentez une pile et une file non mutables utilisant des maillons chaînés. Cette implémentation doit s'inspirer de celles des parties I et II, mais les maillons doivent être intégralement recopiés quand on enfile ou défile un élément ; afin de créer une nouvelle structure totalement indépendante en mémoire de la première.
> 1. Implémentez une pile et une file avec un tableau dynamique. Cette implémentation doit s'inspirer de celles de la partie précédente, mais on redimensionne le tableau `elts` si nécessaire quand on ajoute / retire un élément.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
