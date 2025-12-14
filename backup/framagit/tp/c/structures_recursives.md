# TP : Structures récursives en C

On rappelle qu'on définit un type structuré en C avec :

```c
// à placer dans le .c :
struct nom_s {
    type1 champ1;
    type2 champ2;
    ...
    typeN champN;
};
// à placer dans le .h :
typedef struct nom_s nom;
```

Placer le `typedef` dans le fichier d'entête permet à un utilisateur de se servir du type depuis un autre fichier. Par contre, placer le `struct` dans le code source permet de s'assurer qu'il ne pourra manipuler la structure que par les fonctions qu'on lui donne.

## I. Une première structure récursive

Regardons un peu comment fonctionnent les structures récursives en C.

Reprenons par exemple les poupées russes, qui sont des poupées contenant une poupée plus petite, contenant elle même une poupée encore plus petite, contenant ... jusqu'à la plus petite poupée qui est vide.

> 1. Dans un fichier `poupees.c`, copiez :
>
>     ```c
>     #include "poupees.h"
>     
>     struct poupee_s {
>         int taille; // taille de la poupée
>         struct poupee_s* contenu; // pointeur vers la poupée à l'intérieur
>     };
>     ```
>
> 2. Dans un fichier `poupees.h`, copiez :
>
>     ```c
>     #ifndef _POUPEES_H_
>     #define _POUPEES_H_
>     
>     #include "librairies.h"
>     
>     typedef struct poupee_s poupee;
>     
>     #endif
>     ```
>
> 3. Expliquez, en termes de mémoire, pourquoi il n'est pas possible que le contenu soit directement une poupée et pourquoi il faut donc que ce soit un *pointeur* vers une poupée.
>
> 4. Quel sera le contenu de la plus petite poupée ?

Le fichier d'entête (.h) contient **l'interface** de la structure `poupee`, c'est-à-dire tout ce que l'utilisateur a besoin de connaître pour utiliser des poupées russes (nom du type + spécification des fonctions).

Le fichier de code source (.c) contient **l'implémentation** de la structure `poupee`, c'est-à-dire l'organisation en mémoire et les algorithmes choisis pour manipuler les poupées.

Nous allons commencer par ajouter à nos fichiers une fonction permettant de créer une poupée de taille donnée.

> 5. Ajoutez ceci à l'interface des poupées (c'est-à-dire dans `poupees.h`) :
>
>     ```c
>     /*
>     Entrée : un entier correspondant à la taille de la poupée à créer.
>     Précondition : la taille donnée doit être strictement positive.
>     Sortie : un pointeur vers la poupée créée.
>     Postcondition : la poupée renvoyée est de taille t donnée en paramètre, et contient une poupée de taille t-1, contenant ... contenant une poupée de taille 1 vide.
>     */
>     poupee* poupee_creer(int);
>     ```
>
> 6. Dans le fichier d'implémentation (c'est-à-dire dans `poupees.c`), copiez et complétez la définition de la fonction :
>
>     ```c
>     poupee* poupee_creer(int t) {
>         // allocation pour la première poupée
>         poupee* p = ..........;
>         // la taille de la poupée est t
>         p->taille = ..........;
>         // cas de base : la poupée créée est vide
>         if (t == 1) {
>             p->contenu = ..........;
>         }
>         // cas récursif : on crée récursivement les poupées à l'intérieur
>         else {
>             p->contenu = ..........;
>         }
>         return p;
>     }
>     ```
>
>     *Remarque : ne cherchez pas à tester votre code pour l'instant, ça viendra dans la suite du TP.*

Pour valider nos programmes, il faut idéalement :

* vérifier que les préconditions sont respectées ;
* vérifier que tout se passe bien en mémoire quand on réalise un `malloc` (s'il n'y a plus de place, l'allocation échoue en renvoyant `NULL`).

Pour cela, nous allons utiliser des **assertions** :

```c
assert (propriete_booleenne); // le programme s'arrête si propriete_booleenne est false
```

Par exemple, `assert (x <= 3)` arrête le programme si la variable `x` est strictement supérieure à 3.

> 7. Dans l'implémentation de la fonction `poupee_creer`, ajoutez deux assertions :
>     * une au tout début de la fonction qui vérifie la précondition ;
>     * une juste après le `malloc` qui vérifie que le pointeur renvoyé n'est pas `NULL`.

Nous allons fournir deux fonctions supplémentaires aux utilisateurs de nos poupées :

```c
/*
Entrée : un pointeur vers une poupée.
Précondition : le pointeur n'est pas NULL.
Sortie : aucune.
Postcondition : tout le stockage induit par la poupée donnée en paramètre est libéré.
*/
void poupee_detruire(poupee*);

/*
Entrée : un pointeur vers une poupée.
Précondition : aucune.
Sortie : aucune.
Postcondition : la taille de la poupée est affichée, puis sur la ligne suivante la taille de son contenu est affichée, puis ... jusqu'à la dernière poupée.
*/
void poupee_afficher(poupee*);
```

> 8. Placez les spécifications et déclarations de ces deux fonctions dans l'interface des poupées.
>
> 9. Copiez et complétez les définitions de ces deux fonctions dans l'implémentation des poupées :
>
>     ```c
>     void poupee_detruire(poupee* p) {
>         // vérification du respect des préconditions
>         assert(..........);
>         // si nécessaire, on libère récursivement tout le contenu
>         if (..........) {
>             poupee_detruire(..........); 
>         }
>         // puis on libère la poupée elle-même
>         free(p);
>     }
>             
>     void poupee_afficher(poupee* p) {
>         // si la poupée n'est pas vide
>         if (..........) {
>             // on affiche sa taille
>             printf(..........);
>             // puis on affiche récursivement son contenu
>             poupee_afficher(..........);
>         }
>     }
>     ```

On veut maintenant pouvoir utiliser nos poupées russes dans d'autres programmes. Pour cela, il ne faut surtout pas donner le code source à l'utilisateur ! Il pourrait aller modifier notre code... On va lui donner **le fichier objet et le fichier d'entête**.

> 10. Compilez ainsi afin de récupérer le fichier objet :
>
>     ```bash
>     gcc -Wall -Wextra -Werror -fsanitize=address -c poupees.c
>     ```
>
> 11. Créez un fichier `utilisation.c` contenant le code suivant :
>
>     ```c
>     #include "poupees.h"
>     
>     int main() {
>         poupee* p5 = poupee_creer(5);
>         poupee_afficher(p5);
>         poupee_detruire(p5);
>     }
>     ```
>
> 12. Compilez ce fichier avec la commande :
>
>      ```bash
>     gcc -Wall -Wextra -Werror -fsanitize=address -o test utilisation.c poupees.o
>      ```
>
> 13. Exécutez !
>
> 14. Essayez d'ajouter la ligne suivante dans le `main` précédent (juste après la création de `p5`) : `printf("%d\n", p5->taille);`. Pourquoi cela ne fonctionne-t-il pas ? Est-ce une bonne chose ?
>
> 15. Expliquez en quoi nous avons bien séparé *interface* et *implémentation*, et quel est l'intérêt.

Dès que nous créerons une structure de données (ce qui arrivera souvent comme rien n'existe en C), nous devrons donc procéder de la même manière :

* le `struct` et définitions des fonctions dans un `.c` dont on ne fournira que le fichier objet pour que l'utilisateur ne puisse pas avoir connaissance de l'implémentation ;
* le `typedef` et déclarations et spécifications des fonctions dans un `.h` qu'on fournira pour que l'utilisateur puisse avoir connaissance de l'interface.

## II. Listes chaînées

Nous avons maintenant tous les outils pour pouvoir implémenter des listes chaînées, semblables au type `list` d'OCaml.

Pour que notre implémentation puisse être adaptable rapidement à des listes de n'importe quel type de valeur, nous utiliserons :

```c
typedef int contenu;
```

Ainsi aujourd'hui nos listes contiendront des entiers, mais si dans la suite de l'année nous voulons ré-utiliser notre implémentation avec un autre type, on aura une seule ligne à modifier.

Pour définir nos listes chaînées en C, nous avons besoin de créer une structure de maillon :

```c
struct maillon_s {
    contenu valeur;
    struct maillon_s* suivant;
};
typedef struct maillon_s maillon;
```

Une liste non vide est alors un pointeur vers son premier maillon :

```c
typedef maillon* liste;
```

> 1. Par quoi sera représentée la liste vide ?
> 2. Si on veut rendre cette implémentation ensuite utilisable dans d'autres programmes, sans qu'ils puissent toucher à la structure, que faut-il mettre dans le fichier d'entête ?

Nous allons définir les fonctions principales pour les listes. Quelques consignes :

* Il faut bien **séparer l'*interface* et l'*implémentation***.
* On utilisera des **assertions** pour vérifier que les préconditions sont respectées et que les allocations se passent bien.
* Toutes les déclarations des fonctions (dans le fichier d'interface) seront précédées **de leur spécification et de leur complexité**.
* Toutes les définitions des fonctions (dans le fichier d'implémentation) seront **récursives**.

> 3. Créez un fichier `listes.h` pour l'interface et un fichier `listes.c `pour l'implémentation des listes chaînées. Placez-y toutes les directives nécessaires et la définition des types *au bon endroit*.
>
> 4. Ajoutez une fonction `liste creer_liste(void)` qui renvoie une liste vide.
>
> 5. Ajoutez une fonction `bool est_vide_liste(liste)` qui réalise le test de vacuité.
>
> 6. Ajoutez une fonction `void ajouter_tete_liste(contenu, liste*)` qui ajoute en tête de la liste passée en paramètre un maillon dont le contenu est passé en paramètre.
>
> 7. Ajoutez une fonction `contenu tete_liste(liste)` qui renvoie la valeur de la tête de la liste.
>
> 8. Ajoutez une fonction `liste queue_liste(liste)` qui renvoie la queue de la liste.
>
> 9. Ajoutez une fonction `void detruire_liste(liste)` qui libère toute la mémoire occupée par la liste.
>
> 10. N'oubliez pas les assertions dans vos implémentations. N'oubliez pas les complexités et spécifications dans l'interface.
>
> 11. Compilez afin d'obtenir le fichier objet `listes.o`.
>
> 12. Dans un autre fichier, écrivez un `main` pour faire quelques tests, en utilisant uniquement les fonctions d'interface des listes. Par exemple :
>
>     ```c
>     // crée une liste l équivalente à la liste OCaml [1;2;3]
>     liste l = creer_liste();
>     ajouter_tete_liste(3, &l);
>     ajouter_tete_liste(2, &l);
>     ajouter_tete_liste(1, &l);
>     // affichage de l
>     printf("[%d; ", tete_liste(l));
>     printf("%d; ", tete_liste(queue_liste(l)));
>     printf("%d]\n", tete_liste(queue_liste(queue_liste(l))));
>     // la liste ne contient que 3 éléments
>     if(est_vide_liste(queue_liste(queue_liste(queue_liste(l))))) {
>         printf("La liste contient 3 éléments.\n");
>     }
>     // attention aux fuite de mémoire
>     detruire_liste(l);
>     ```

*Conservez bien vos fichiers sur les listes, et assurez-vous que tout fonctionne : on en aura besoin plusieurs fois cette année.*

**Il faut impérativement être capable d'implémenter très rapidement une liste chaînée en C. Entraînez-vous régulièrement à redéfinir les types maillon et liste, et à ré-écrire les fonctions ci-dessus.**

## III. Fonctions sur les listes chaînées

Maintenant que nous avons créé des listes chaînées en C, on peut s'en servir comme de n'importe quel type existant !

Il suffit pour cela d'inclure le fichier `listes.h` dans notre fichier utilisant les listes, puis au moment de compiler d'ajouter le fichier `listes.o` à la commande.

> 1. Créez un fichier `manip_listes.c` incluant l'interface des listes.

Toutes les fonctions de ce fichier `manip_listes.c` ne peuvent utiliser **que les six fonctions de l'interface des listes**.

> 2. Écrivez dans ce fichier une fonction récursive `int list_length(liste l)` qui renvoie la longueur de la liste passée en paramètre. Son fonctionnement sera similaire à la fonction `List.length` d'OCaml.
> 3. Ajoutez un `main` (directement dans ce fichier) pour tester la fonction précédente.
> 4. Écrivez une fonction récursive `bool list_mem(liste l, contenu elt)` qui détermine si l'élément appartient à la liste.
> 5. Écrire une fonction récursive `bool egales(liste l1, liste l2)` qui prend deux listes en paramètres et indique si elles ont les mêmes valeurs, dans le même ordre.
> 6. Écrivez une fonction récursive `void afficher(liste l)` qui affiche une liste. L’affichage de la liste contenant les éléments 0 en tête, puis 1, puis 2 puis 3 devra produire précisément l’affichage sous la forme suivante : `[0; 1; 2; 3]`.
>     *Remarque : cette fonction suppose que contenu soit un alias de `int`, on ne pourra donc pas toujours l'utiliser.*
> 7. *Pensez à tester vos fonctions ! Vérifier que ça compile ne suffit pas...*
> 8. Calculez les complexités des quatre fonctions précédentes.

## III. Exercices

> **Retour sur les poupées russes**
>
> On souhaite ajouter les fonctions suivantes pour nos poupées russes :
>
> ```c
> /*
> Entrée : un pointeur vers une poupée.
> Précondition : le pointeur n'est pas NULL.
> Sortie : un entier.
> Postcondition : renvoie la taille de la poupée.
> */
> int poupee_taille(poupee*);
> 
> /*
> Entrée : un pointeur vers une poupée.
> Précondition : le pointeur n'est pas NULL.
> Sortie : un booléen.
> Postcondition : on ne renvoie true que si les poupées sont bien de tailles strictement décroissantes.
> */
> bool poupee_check(poupee*);
> 
> /*
> Entrée : un pointeur vers une poupée et un entier.
> Précondition : le pointeur n'est pas NULL, et l'entier est strictement positif et inférieur ou égal au nombre de poupées disponibles à l'intérieur de la poupée donnée.
> Sortie : un pointeur vers une poupée.
> Postcondition : en notant n l'entier, récupère la n-ième poupée à l'intérieur de celle donnée en paramètre.
> */
> poupee* poupee_ouvre(poupee*, int);
> ```
>
> 1. Ajoutez ces déclarations et spécifications au fichier d'interface des poupées russes.
> 2. Définissez ces fonctions dans le fichier d'implémentation des poupées russes. On veillera à faire les vérifications nécessaires (assertions) pour le respect des préconditions.
> 3. Compilez afin d'obtenir le fichier objet.
> 4. Dans un autre fichier, écrivez un `main` pour faire quelques tests, en utilisant uniquement les fonctions d'interface.

> **Fonctions complémentaires sur les listes chaînées**
>
> Pour simplifier l'utilisation des listes, nous allons écrire quelques fonctions bien utiles. Vous pouvez les ajouter au fichier `manip_listes.c` de la partie III.
>
> On rappelle que toutes vos fonctions ne peuvent utiliser que les six fonctions de l'interface des listes.
>
> *Toutes vos fonctions doivent être récursives.*
>
> 1. Écrivez une fonction `contenu acces_indice(liste l, int indice)` qui renvoie la valeur du maillon de la liste dont l'indice est passé en paramètre.
> 2. Écrivez une fonction récursive `bool est_triee(liste l)` qui détermine si une liste est triée dans l'ordre croissant.
> 3. Écrivez une fonction `liste copie(liste l)` qui renvoie une copie totalement indépendante en mémoire de celle passée en paramètre.
> 4. Écrivez une fonction `liste concatene(liste l1, liste l2)` qui prend en paramètre deux listes et les met bout à bout. Le résultat sera totalement indépendant en mémoire des deux listes concaténées.
> 5. Écrivez une fonction `liste renverse(liste l)` qui prend en argument une liste et qui renvoie une copie de cette liste, à l’envers. La liste et sa copie renversée seront totalement indépendantes en mémoire.
> 6. Écrivez une fonction `void insere(liste l, contenu val, int indice)` qui prend en paramètre une liste, une valeur, et un indice et insère un maillon contenant la valeur donnée à l'indice donné. Le résultat sera totalement indépendant en mémoire de la liste `l`.

## Pour aller plus loin

> Vous pouvez reprendre les variantes des listes chaînées vues en cours (ex : liste doublement chaînée, liste circulaire...) et les implémenter en C.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
