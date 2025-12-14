# TP : Pointeurs et gestion de la mémoire en C

Nous allons découvrir dans ce TP comment manipuler de la mémoire en C : nous introduirons pour commencer la notion de **pointeur** avant de découvrir l'**allocation dynamique** de mémoire.

À nouveau, il n'y aura pas de chapitre de cours dédié aux pointeurs : je vous conseille vivement de faire une fiche avec les notions essentielles de ce TP. Nous nous servirons des pointeurs et de l'allocation dynamique tout le reste de l'année, c'est un incontournable du C.

À partir de ce TP, vous *devez* compiler vos programmes avec la commande suivante :

```bash
$ gcc -Wall -Wextra -Werror -fsanitize=address -o executable codes_sources.c
```

L'option `-fsanitize=address` est essentielle quand on manipule de la mémoire.

Si vous n'aviez pas déjà noté cette commande quelque part lors des TP précédents, faîtes le maintenant : je ne la rappellerai plus dans les TP suivants.

> **Initialisation de l'espace de travail**
>
> 1. Créez un répertoire `gestion_memoire` contenant un fichier `pointeurs.c` ainsi que le fichier `librairies.h` créé lors du premier TP en C.
>
> 2. Ouvrez le fichier `pointeurs.c`, incluez-y le fichier `librairies.h` et placez-y la fonction principale `main` (vide pour l'instant).
>
>     *Remarque : le fichier `pointeurs.c` contient le main, il n'est donc pas nécessaire de créer un fichier d'entête correspondant.*

## I. Notion d'adresse et fonction `scanf`

Toute variable manipulée dans un programme est stockée quelque part en mémoire. Cette mémoire est constituée d'octets qui sont identifiés de manière univoque par un numéro qu'on appelle **adresse**. Pour retrouver une variable, il suffit donc de connaître l’adresse de l’octet où elle est stockée (ou, s’il s’agit d’une variable qui recouvre plusieurs octets contigus, l’adresse du premier de ces octets).

Pour des raisons évidentes de lisibilité, on désigne souvent les variables par des **identificateurs**, et non par leur adresse. C’est le compilateur qui fait alors le lien entre l’identificateur d’une variable et son adresse en mémoire. Toutefois, il est parfois très pratique de manipuler directement une variable par son adresse.

**L'adresse** d'un objet étant le numéro d’un octet de la mémoire, il s’agit d’un **entier** (quelque soit le type d’objet à cette adresse). Le format interne de cet entier (16 bits, 32 bits, ou 64 bits) dépend de l’architecture de la machine utilisée (64 bits sur les ordinateurs récents).

En C, l'opérateur `&` permet d'accéder à l'adresse d'une variable. On l'appelle **opérateur de référencement**.

*Remarque : `&` est également un opérateur sur les entiers. Pour ne pas confondre, veillez à ne pas mettre d'espace entre l'opérateur de référencement et la variable.*

> 1. Placez les lignes suivantes dans le `main`, compilez avec `gcc -Wall -Wextra -Werror -fsanitize=address -o executable pointeurs.c` et exécutez :
>
>     ```c
>     int i;
>     i = 3;
>     printf("variable i : adresse = %p ; valeur = %d\n", &i, i);
>     ```
>     
>     Quelle est l'adresse de la variable `i` ? Sous quel "format" est-elle affichée ?
>     
> 2. À l'aide du code suivant, déterminez si deux variables ayant la même valeur ont aussi la même adresse :
>
>     ```c
>    int i, j;
>    i = 3;
>    j = 3;
>    printf("variable i : adresse = %p ; valeur = %d\n", &i, i);
>    printf("variable j : adresse = %p ; valeur = %d\n", &j, j);
>    ```
> 
> 3. À l'aide du code suivant, déterminez si l'affectation `=` agit sur les valeurs ou sur les adresses :
>
>     ```c
>    int i, j;
>    i = 3;
>    j = i;
>    printf("variable i : adresse = %p ; valeur = %d\n", &i, i);
>    printf("variable j : adresse = %p ; valeur = %d\n", &j, j);
>    ```
>
> 6. À l'aide du code suivant, expliquez la notion de "portée des variables" :
>
>     ```c
>    for (int i = 0; i < 6; i += 1) {
>        int x = 1;
>        printf("variable x du for : adresse = %p ; valeur = %d\n", &x, x);
>        if (i % 2 == 0) {
>            int x = 2;
>            printf("variable x du if : adresse = %p ; valeur = %d\n", &x, x);
>        }
>        else {
>            int x = 3;
>            printf("variable x du else : adresse = %p ; valeur = %d\n", &x, x);
>        }
>    }
>    int x = 4;
>    printf("variable x finale : adresse = %p ; valeur = %d\n", &x, x);
>    ```
> 
> 7. Si les adresses sont différentes, les variables sont différentes. Est-ce une bonne pratique d'avoir plusieurs variables différentes ayant le même identificateur comme dans le code de la question précédente ?

Tout comme `printf` permet d'écrire sur la sortie standard (*stdout*), la fonction `scanf` permet de lire des données sur l'entrée standard (*stdin*).

Tout comme `printf`, la fonction `scanf` prend en paramètre une chaîne de format, contenant un certain nombre de champs (`%d`, `%f`, ...) qui précisent les types attendus.

La fonction prend également une série d'adresses, une par champ. C'est à ces adresses que vont être écrites les données lues.

> 6. Placez les lignes suivantes dans le `main`, compilez, exécutez, puis entrez un entier.
>
>     ```c
>     int i;
>     scanf("%d", &i); // lit un entier sur l'entrée standard et le stocke à l'adresse de i
>     printf("L'entier entré est %d.\n", i);
>     ```
>
> 7. Il est possible de lire autant de données que souhaité, pour peu qu'on passe en paramètres plusieurs adresses. Testez le code suivant en entrant successivement un entier, un réel et un caractère (en tapant sur entrée entre chaque) :
>
>    ```c
>    int i;
>    double d;
>    char c;
>    scanf("%d %lf %c", &i, &d, &c);
>    printf("L'entier entré est %d.\n", i);
>    printf("Le réel entré est %f.\n", d);
>    printf("Le caractère entré est %c.\n", c);
>    ```
>
> 8. Testez à nouveau ce code en entrant uniquement `12.3a` puis Entrée. Testez aussi en entrant `1 2.3 a`. Que se passe-t-il ? Les espaces et/ou retour à ligne sont-ils importants ?
>
> 9. Testez le code suivant en entrant `4 a 2` :
>
>     ```c
>     int x, y;
>     int nb_champs_lus = scanf("%d %d", &x, &y);
>     printf("Nombre de champs lus correctement : %d\n", nb_champs_lus);

La fonction `scanf` renvoie un entier qui indique le nombre de données lues :

* si tout va bien, ce nombre est égal au nombre de champs souhaités ;
* si la lecture des données pour un champ s'est mal déroulée, ce nombre est égal au nombre de champs lus correctement avant l'erreur (et les valeurs aux adresses correspondantes aux champs suivants reste inchangées) ;
* si toutes les données ont été lues alors qu'il restait des champs à remplir, ce nombre est négatif.

> 10. Écrire une fonction `void produits_successifs_de_30_entiers(void)` qui lit un entier sur l'entrée standard, puis lit un second entier et affiche le produit des 2, puis un troisième entier et affiche le produit des 3, puis, etc. jusque 30 entiers.
>11. Écrire une fonction `void produits_successifs_jusque_saisie_de_0(void)` similaire, qui s'arrête cette fois non plus à 30 entiers lus mais quand l'utilisateur entre 0.

Ce n'est pas très pratique d'avoir l'entrée et la sortie mélangés.

On peut rediriger la sortie avec `./executable >> fichier`.

> 12. Testez votre fonction précédente en redirigeant la sortie vers un fichier "s.txt". Affichez ensuite le contenu avec la commande `cat s.txt`. Retrouvez-vous bien ce qu'il fallait ?

Il est également possible de rediriger l'entrée avec `./executable < fichier`.

> 13. Créez un fichier `e.txt` contenant ceci :
>
>     ```
>     4
>     2
>     5 1       3
>     0
>     ```
>
>     Testez alors votre fonction précédente en redirigeant l'entrée standard vers le fichier "e.txt".
>
> 11. Essayez de rediriger à la fois l'entrée et la sortie. Qu'est-il affiché dans le terminal maintenant ?

Rediriger la sortie peut être particulièrement pertinent lorsqu'on a beaucoup de données à afficher, ou lorsqu'on souhaite les conserver pour les réutiliser ultérieurement. Rediriger l'entrée peut être particulièrement pertinent quand on veut tester du code plusieurs fois sur le même exemple. Cela évite de devoir recopier les données à chaque fois.

Un programme C peut également se servir en entrée de la sortie d'un autre.

> 15. Créez deux fichiers `c1.c` et `c2.c` contenant respectivement les codes suivants :
>
>     ```c
>     #include "librairies.h"
>     
>     int main () {
>         printf("%d", 3);
>     }
>     ```
>
>     ```c
>     #include "librairies.h"
>     
>     int main () {
>         int i;
>         scanf("%d", &i) ;
>         printf("J'ai récupéré la sortie de c1 qui vaut %d.\n", i);
>     }
>     ```
>
> 17. Compilez les 2 codes séparément pour obtenir deux exécutables "c1" et "c2". Exécutez ensuite la commande `./c1 | ./c2`. Expliquez ce qu'il se passe.

## II. Pointeur vers un objet alloué

Un **pointeur** est un objet dont la valeur est égale à l'adresse d'un autre objet.

On déclare un pointeur via l'instruction suivante :

```c
type* nom_du_pointeur;
```

Cela déclare une variable, d'identificateur `nom_du_pointeur`, et de valeur l'adresse d'un autre objet de type `type`.

Le type d'un pointeur dépend du type de l'objet vers lequel il pointe. Si l'objet pointé est de type `t`, le pointeur est de type `t*`.

Par exemple :

* Un pointeur de type `char*` pointe vers un objet de type `char`. Sa valeur est l'adresse de l'unique octet où ce caractère est stocké.
* Un pointeur de type `double*` pointe vers un objet de type `double`. Sa valeur est l’adresse du premier des 8 octets où le flottant est stocké.

> 1. Toujours en compilant avec `gcc -Wall -Wextra -Werror -fsanitize=address -o executable pointeurs.c`, copiez le code suivant dans le `main` et testez :
>
>     ```c
>     int i = 3;
>     int* p = &i;
>     printf("Adresse de la variable i : %p\n", &i);
>     printf("Valeur de la variable p : %p\n", p);
>     ```
>     
>     Trouvez-vous bien que la valeur de `p` est l'adresse de `i` ?

On peut accéder à la valeur de l'objet pointé grâce à l'**opérateur de déréférencement** : `*`.

Si `p` est un pointeur vers un objet `i`, `*p` désigne la valeur de `i`.

*Remarque : tout comme pour l'opérateur de référencement `&`, on veille à ne pas mettre d'espace entre l'astérisque et le nom du pointeur pour ne pas confondre avec l'opérateur de multiplication `*`*.

> 2. Ajoutez à la suite du code précédent la ligne suivante dans le `main` :
>
>     ```c
>     printf("*p = %d\n", *p);
>     ```
>     
>     Retrouvez-vous bien 3 comme valeur de `*p` ?
>     
> 3. Dans le programme ci-dessus, les objets `i` et `*p` sont identiques : ils ont mêmes adresses et valeurs. Cela signifie notamment que toute modification de l'un modifie également l'autre. Ajoutez à la suite du code précédent les lignes suivantes dans le `main`, et testez :
> 
>     ```c
>     *p = 7;
>     printf("i = %d\n", i);
>     printf("*p = %d\n", *p);
>    i = 4;
>    printf("i = %d\n", i);
>    printf("*p = %d\n", *p);
>    ```

Le site [C Tutor](https://pythontutor.com/visualize.html#mode=edit) permet de visualiser pas à pas l'évolution de la pile d'exécution d'un programme. Les animations visuelles de C Tutor sont particulièrement adaptées pour comprendre en quoi consiste un pointeur.

> 4. Visualisez pas à pas l'exécution du programme suivant sur C Tutor :
>
>     ```c
>     int main () {
>         int x = 12, y = 100;
>         int* p = &x;
>         *p = 15;
>         x = 7;
>         p = &y;
>         y = 4;
>         x = 3 * *p;
>     }
>     ```

Dans un programme, on peut manipuler aussi bien les objets `p` et `*p`. Seulement, ces deux manipulations sont très différentes.

> 5. Devinez la différence entre les deux programmes suivants, puis vérifiez votre réponse sur le site C Tutor :
>
>     ```c
>     // PROGRAMME 1
>     int main() {
>         int i = 3, j = 6;
>         int* pi = &i;
>         int* pj = &j;
>         *pi = *pj;
>     }
>     ```
> 
>     ```c                 
>     // PROGRAMME 2
>     int main() {
>         int i = 3, j = 6;
>         int* pi = &i;
>         int* pj = &j;
>         pi = pj;
>     }
>     ```

*Remarque : Attention, l'instruction `int* p, q;` ne déclare pas deux pointeurs vers des entiers. Ici `p` est bien un pointeur mais `q` est un entier. Si on veut que `q` soit un pointeur, il aurait fallu écrire `int* p, * q` De manière générale, pour éviter les confusions, on déclarera chaque pointeur sur une ligne indépendante.*

Un pointeur étant une valeur comme une autre, il est possible de le passer en paramètre d'une fonction.

> 6. Essayons d'écrire une fonction pour échanger deux variables :
>
>     ```c
>     void echange(int a, int b) {
>         int tmp = a;
>         a = b;
>         b = tmp;
>     }
>     
>     int main () {
>         int x = 2;
>         int y = 3;
>         echange(x, y);
>     }
>     ```
>
>     En utilisant C Tutor, expliquez pourquoi cela ne fonctionne pas.
>
> 10. Visualisez pas à pas l'exécution du programme suivant :
>
>     ```c
>     void echange(int* a, int* b) {
>         int tmp = *a;
>         *a = *b;
>         *b = tmp;
>     }
>                                                                                                                                                                                         
>     int main () {
>         int x = 2;
>         int y = 3;
>         echange(&x, &y);
>     }
>     ```
>
>     Expliquez pourquoi cela fonctionne désormais.

Lorsqu'on appelle une fonction, ce ne sont pas les paramètres directement qui sont utilisées mais des *copies* de ces paramètres, qui n'existent que dans la pile d'appel de la fonction. Une fois sortis de l'appel, ces copies n'existent plus donc rien ne ce qui a été modifié n'est conservé. C'est ce qu'on appelle un **passage des paramètres par valeur**.

Si on veut qu'une fonction ait un effet de bord (c'est-à-dire qu'elle modifie la mémoire), il faut passer les adresses des cases mémoire à modifier en paramètre. Il s'agit toujours d'un passage par valeur (les adresses sont des valeurs, et elles sont copiées lors de l'appel de la fonction) mais ces adresses permettent de manipuler de la mémoire extérieure à la fonction (et qui existe donc toujours après l'appel).

> 8. Expliquez pourquoi le code suivant affiche 2 (vous pouvez vous aider de C Tutor), puis modifiez la fonction `f` pour qu'il affiche 4.
>
>     ```c
>    int x = 4;
>     
>    void f(int* p) {
>        p = &x;
>    }
>     
>    int main() {
>        int i = 2;
>        int* p = &i;
>        f(p);
>        printf("%d\n", *p);
>    }
>    ```
> 
> 9. Écrivez une fonction `void incr(int* p)` qui augmente de 1 un entier en paramètre. Vérifiez avec C Tutor.

**`NULL`** est une valeur spéciale pour un pointeur qui signifie "aucune adresse". On peut s'en servir pour initialiser un pointeur et le modifier ensuite.

Tenter de déréférencer le pointeur nul provoque une **erreur de segmentation** ("segfault") car il ne pointe pas vers un emplacement mémoire valide. Une erreur de segmentation survient lorsqu'un programme tente d'accéder à un emplacement mémoire qui ne lui est pas *allouée*.

> 10. Copiez les lignes suivantes dans le `main`, compilez avec `gcc -Wall -Wextra -Werror -fsanitize=address -o executable pointeurs.c`, et exécutez :
>
>     ```c
>     int* p = NULL;
>     printf("%d", *p);
>     ```
>     
>     *Remarque : le message d'erreur est en rouge.*
>     
> 11. Essayez de compiler sans l'option `-fsanitize=address`, puis exécutez. Expliquez pourquoi cette option est essentielle quand on manipule de la mémoire.

Si on tente d'accéder à un objet alors qu'il n'est plus "vivant", le comportement du programme est indéfini, "**Undefined Behavior**". C'est le cas des fonctions qui renvoient des pointeurs vers un objet local.

> 12. Expliquez le problème du code suivant :
>
>     ```c
>     int* f() {
>         int x = 2;
>         return &x;
>     }
>                         
>     int main() {
>         int* p = f();
>         printf("*p = %d\n", *p);
>     }
>     ```
> 

## III. Allocation dynamique

Nous avons vu que `type* p = &v` permettait de créer un pointeur vers un objet alloué, c'est-à-dire dont l'adresse est déjà réservé à une variable dans le programme (ici `v`).

Il n’est pas obligatoire que l’adresse pointée par `p` soit l’adresse d’une variable existante. Dans ce cas, on peut directement travailler avec la valeur de `*p`, mais il faut d’abord réserver à `p` un espace mémoire de taille adéquate. On appelle cela l'**allocation dynamique**.

Elle se fait en C via la fonction `malloc` dont la signature est :

```c
void* malloc(size_t nombre_octets)
```

Le type `size_t` est un type entier utilisé pour désigner une taille en mémoire (en nombre d’octets).
Puisque la fonction `malloc` renvoie des adresses de types différents selon la situation (`int*, double*, char*`, ...), son type de retour est `void*` : ce type joue un rôle spécial et le type de la valeur de retour s’adaptera au type de pointeur utilisé.

> 1. Copiez les lignes suivantes dans le `main`, compilez avec `gcc -Wall -Wextra -Werror -fsanitize=address -o executable pointeurs.c`, et exécutez. Que se passe-t-il ?
>
>     ```c
>     char* p = malloc(1);
>     *p = 'a';
>     printf("%c\n", *p);
>     ```
>     

Lorsqu'on a plus besoin de l'espace mémoire alloué dynamiquement (c'est-à-dire quand on utilise plus le pointeur), il faut **libérer** l'espace mémoire.

Si on ne libère pas la mémoire allouée, on obtient une **fuite de mémoire** ("memory leak"). Cela peut être extrêmement problématique si on a alloué un gros bloc de mémoire, qui n'est jamais libéré : on ne peut plus s'en servir pour autre chose et surtout, on encombre la RAM ce qui ralentit nos programmes... En plus de réduire les risques d'erreurs de segmentation comme vu dans la partie précédente, l'option `-fsanitize=address` permet de détecter les fuites de mémoire.

On libère une zone allouée avec la fonction `free` de prototype suivant :

```c
void free(void* pointeur)
```

> 2. Pourquoi le pointeur pris en paramètre par la fonction `free` doit-il être de type `void*`?
>
> 6. Ajoutez donc la ligne suivante à votre programme précédent, et testez :
>
>     ```c
>    free(p);
>    ```

Toute instruction `malloc` doit donc être associée à une instruction `free`.

> 4. Que se passe-t-il si on essaie d'accéder à une adresse mémoire invalide (par exemple en oubliant d'allouer une zone pour un pointeur avec `malloc`) ? Vous pouvez par exemple tester :
>
>     ```c
>     char* p;
>     *p = 'a';
>     printf("%c\n", *p);
>     ```

Un `char` est sur 1 octet, c'est pour cela qu'on passe 1 en paramètre de `malloc`. On peut obtenir la taille d’un type à l’aide de `sizeof(type)`. Cela permet de connaître la taille de la zone à allouer :

```c
type* p = malloc(sizeof(type));
```

La fonction `malloc` renvoie un pointeur de type `void*`. La conversion est donc implicite lorsqu'on écrit l'instruction précédente. L'instruction suivante est équivalente, mais avec une conversion explicite cette fois :

```c
type* p = (type*) malloc(sizeof(type))
```

Le programme de MP2I vous oblige normalement à toujours utiliser des conversions explicites. Le cas de `malloc` est la seule exception tolérée.

> 5. Copiez les lignes suivantes dans le `main`, compilez avec `gcc -Wall -Wextra -Werror -fsanitize=address -o executable pointeurs.c`, et exécutez.
>
>     ```c
>     int* p = malloc(sizeof(int));
>     *p = 2;
>     printf("%d\n",*p);
>     free(p);
>     ```
> 
> 5. Déroulez pas à pas le code précédent dans [C Tutor](https://pythontutor.com/c.html). Quelle est la différence notable de l'allocation dynamique par rapport aux divers codes de la partie précédente ?

Lorsqu'on réalise une allocation dynamique, la zone mémoire obtenue est située sur le **tas**, et non sur la pile. Cela signifie qu'elle continue d'exister tant qu'on ne l'a pas libérée.

Ainsi tout ce qui est alloué avec `malloc` est conservé tant qu'on ne le libère pas avec `free`.

Cela vaut également si le `malloc` est réalisé à l'intérieur d'une fonction. La zone mémoire alloué continue d'exister même après la fin de l'appel.

> 7. Lequel des deux programme suivants est correct ? Vérifiez avec C Tutor.
>
>     ```c
>     // PROGRAMME 1
>     double* f(double x) {
>         double* p = &x;
>         return p;
>     }
>     int main() {
>         double* p = f(3.14);
>         printf("%f", *p);
>     }
>     ```
>
>     ```c
>     // PROGRAMME 2
>     double* f(double x) {
>         double* p = malloc(sizeof(double));
>         *p = x;
>         return p;
>     }
>     int main() {
>         double* p = f(3.14);
>         printf("%f", *p);
>         free(p);
>     }
>     ```
>
> 7. Pourquoi est-il essentiel de renvoyer un pointeur vers la zone allouée si une fonction réalise un `malloc` mais pas de `free` ?

Toute zone mémoire allouée doit forcément être libérée. Ainsi, si une fonction alloue une zone mémoire mais ne la libère pas elle-même, il faudra nécessairement renvoyer un pointeur vers la zone mémoire concernée pour qu'une autre partie du programme puisse la libérer.

La fonction `malloc` permet également d'allouer de l'espace pour plusieurs objets contigus en mémoire.

> 9. Testez le code suivant sur C Tutor :
>
>     ```c
>     #include <stdlib.h>
>     #include <stdio.h>
>     int main() {
>         int i = 3, j = 6;
>         int* p = malloc(2 * sizeof(int));
>         *p = i;
>         *(p + 1) = j;
>         printf("p = %p \t *p = %d \np+1 = %p \t *(p+1) = %d \n", p, *p, p+1, *(p+1));
>         free(p);
>     } 
>     ```
>
> 9. Si `p` est un pointeur vers 2 zones mémoires contiguës, comment accéder à la deuxième zone ?
>
> 10. Écrivez une fonction qui prend en paramètre une taille `t` et renvoie une zone mémoire qui contient `t` entiers contigus, valant tous 1.

Un des grands intérêts des pointeurs concernent les valeurs de retour des fonctions. En C, il n'est pas possible facilement de renvoyer plusieurs valeurs (il n'existe pas de "tuples" comme en OCaml). Deux possibilités :

* Passer en paramètre de la fonction des pointeurs vers des zones mémoire où l'on peut aller écrire directement les valeurs que l'on souhaitait renvoyer.
* Allouer dynamiquement dans la fonction une zone mémoire dans laquelle on stocke les valeurs que l'on souhaitait renvoyer, et renvoyer un pointeur vers cette zone.

> 12. Écrire une fonction `int division_v1(int a, int b, int* r)` qui renvoie le quotient de la division euclidienne de `a` par `b` et place le reste dans l'emplacement réservé par `r`.
>
> 12. Pour tester votre fonction, vous pouvez faire ainsi dans le `main` :
>
>     ```c
>     int q, r;
>     q = division_v1(17, 5, &r);
>     printf("Le quotient est %d et le reste est %d.\n", q, r);
>     ```
>
>     Affichez ensuite les valeurs du quotient et du reste obtenus.
>
> 13. Écrire une fonction `int* division_v2(int a, int b)` qui renvoie un pointeur vers une zone mémoire allouée dynamiquement dans laquelle sont rangés le quotient et le reste de la division euclidienne de `a` par `b`.
>
> 14. Pour tester votre fonction, vous pouvez faire ainsi dans le `main` :
>
>     ```c
>     int* q_et_r = division_v2(17, 5);
>     int q = *q_et_r;
>     int r = *(q_et_r + 1);
>     printf("Le quotient est %d et le reste est %d.\n", q, r);
>     free(q_et_r);
>     ```

## IV. Exercices

Pour cette partie, vous travaillerez dans les fichiers de votre choix.

> **Exercice 1**
>
> On considère les trois fonctions suivantes :
>
> ```c
> int* pointer(int n) {
> 	int* p = &n;
> 	return p;
> }
> void move(int* p, int* q) {
> 	*p = *q;
> }
> int get(int* p) {
> 	return *p;
> }
> ```
>
> Pour chacun des programmes suivants, déterminez si le programme est valide, en indiquant le problème s'il ne l’est pas. Dans le cas où le programme est valide, déterminez ce qui est affiché à l’écran. Vérifiez vos réponses avec C Tutor.
>
> ```c
> // PROGRAMME 1
> int n = 0;
> int* p = &n;
> n = 2;
> *p += 1;
> printf("p1 : %d %d\n", n, *p);
> ```
>
> ```c
> // PROGRAMME 2
> int n = 0;
> int* p = pointer(n);
> n = 2;
> *p += 1;
> printf("p2 : %d %d\n", n, *p);
> ```
>
> ```c
> // PROGRAMME 3
> int n = 0;
> int* p = &n;
> int* q = NULL;
> move(p, q);
> printf("p3 : %d %d %d\n", n, *p, *q);
> ```
>
> ```c
> // PROGRAMME 4
> int n = 0;
> int* p = &n;
> int m = get(p);
> n = 2;
> m += 1;
> printf("p4 : %d %d %d\n", n, *p, m);
> ```
>
> ```c
> // PROGRAMME 5
> int n = 0;
> int m = 2;
> int* p = &n;
> int** pp = &p;
> int* q = &m;
> move(*pp, q);
> *q = *q + get(p) + **pp;
> printf("p6 : %d %d %d\n", n, m, *q);
> ```
>
> Expliquez à quoi correspond un objet de type `type**`. Si `p` est de type `t**`, quel est le type de `*p` ? de `**p` ?

> **Exercice 2**
>
> Exécutez le programme suivant :
>
> ```c
> void print_bool(bool b) {
>     if (b) {
>         printf("true\n");
>     }
>     else {
>         printf("false\n");
>     }
> }
> 
> int main(){
>     double x = 3.1, y = 4.5;
>     double* p = &x;
>     *p = y;
>     print_bool(x==y);
>     x = 0.3;
>     print_bool(x==y);
>     y = 0.1 + 0.2;
>     print_bool(x==y);
> }
> ```
>
> Quel résultat étrange obtenez-vous ? Expliquez.

> **Exercice 3**
>
> Pour chacun des programmes suivants, écrivez *sur papier* l'évolution de la pile d'exécution comme vous l'obtiendriez sur C Tutor. Vérifiez *ensuite* vos réponses avec C Tutor.
>
> ```c
> // PROGRAMME 1
> int x = 5, y = 22;
> int* p;
> 
> int f(int x, int* p){
>        printf("x = %d\n", x);
>        printf("y = %d\n", y);
>        printf("*p = %d\n", *p);
>        int y = 1;
>        p = &y;
>        printf("y = %d\n", y);
>        x = x + *p + y;
>        printf("*p = %d\n", *p);
>        return x;
> }
>
> int main() {
>        int z;
>        p = &x;
>        z = f(x + 5, p);
>        printf("z = %d\n", z);
>        printf("*p = %d\n", *p);
>        x = f(x + 2, p);
>        printf("*p = %d\n", *p);
> }
> ```
> 
> ```c
> // PROGRAMME 2
> int* p;
> 
> int f(int x) {
>        x += 1;
>        return x;
> }
> 
> int main() {
>        int x = 2;
>        int y = f(x);
>        p = &x;
>        x = f(y);
>        printf("*p = %d\n", *p);
> }
> ```
> 
> ```c
> // PROGRAMME 3
> int main () {
>        int n = 1, m = 7;
>        int* p = &n;
>        int* q = &m;
>        n += 1;
>        *q = *p + 3;
>        *p += 2;
>     p = q;
>     *p += 1;
>     if (p == q) {
>            *q += 1;
>        }
>    }
>    ```

> **Exercice 4**
>
> Le programme suivant comporte un très grand nombre de problèmes (erreurs de syntaxe ou de type, lecture d’une variable non initialisée, déréférencement d’un pointeur invalide, etc.). Au brouillon, identifiez les points problématiques, corrigez ce qui peut l’être et déterminez l’évolution du programme. Vérifiez ensuite sur C Tutor.
>
> ```c
> #inclure <librairies.h>
> 
> voil f(int* p) {
> 	*p += 1
> }
> 
> int* f(int* p; int* q)
> 	int* r = *p + *p;
> return r;
> }
> 
> bool main(void) {
> let n = 0 in
> int m;
> int p = NULL	;
> 	printf("n = d\n", f(n);
> printf("n = d\n", f(p);
> printf("n = d\n", f(&n);
> int p = f(&n, &m);
> print("n + m = d\n" p);
> }
> ```

> **Exercice 5**
>
> On considère la fonction suivante :
>
> ```c
> void mystere(int* x, int* y) {
>     *x = *x - *y;
>     *y = *x + *y;
>     *x = *y - *x;
> }
> ```
>
> 1. Quel affichage obtiendrait-on avec le code suivant ?
>
>     ```c
>     int x1 = 3;
>     int y1 = 4;
>     mystere(&x1, &y1);
>     printf("x1 = %d, y1 = %d\n", x1, y1);
>     ```
>
>     Vérifiez avec C Tutor.
>
> 2. De manière générale, que fait la fonction `mystere` ? On justifiera précisément.
>
> 3. Quel affichage obtiendrait-on avec le code suivant ?
>
>     ```c
>     int x2 = 3;
>     int y2 = 3;
>     mystere(&x2, &y2);
>     printf("x2 = %d, y2 = %d\n", x2, y2);
>     ```
>
>     Vérifiez avec C Tutor.
>
> 4. Quel affichage obtiendrait-on avec le code suivant ?
>
>     ```c
>     int x3 = 3;
>     mystere(&x3, &x3);
>     printf("x3 = %d\n", x3);
>     ```
>
>     Vérifiez avec C Tutor.
>
> 5. Quel est le problème avec la démonstration faîte en question 2 ?

> **Exercice 6**
>
> Dans tous les exemples suivants, on souhaite qu’un appel à `f(px, py)` incrémente celle des valeurs pointées par `px` et `py` qui est la plus petite (ou celle pointée par `px` en cas d’égalité).
>
> Par exemple :
>
> ```c
> #include "librairies.h"
> 
> int main(void){
>        int x = 8;
>        int y = 9;
>        printf("x = %d, y = %d\n", x, y);
>        f(&x, &y);
>        printf("x = %d, y = %d\n", x, y);
>        f(&x, &y);
>        printf("x = %d, y = %d\n", x, y);
>        f(&x, &y);
>        printf("x = %d, y = %d\n", x, y);
> }
> ```
>
> doit afficher :
>
> ```bash
> x = 8, y = 9
> x = 9, y = 9
> x = 10, y = 9
> x = 10, y = 10
> ```
>
> La fonction `incr` est celle que vous avez défini plus haut dans le TP. Pour chacun des programmes suivants, expliquez s'il y a un problème, si oui lequel et sinon dire s'il a le comportement souhaité :
>
> ```c
> // PROGRAMME 1
> int plus_petit(int x, int y){
>        if (x <= y) {
>            return x;
>        }
>        return y;
> }
> 
> void f(int* px, int* py){
> 	incr(plus_petit(*px, *py));
> }
> ```
> 
> ```c
> // PROGRAMME 2
> int* plus_petit(int x, int y){
> 	if (x <= y)  {
>   		return &x;
> 	}
> 	return &y;
> }
> 
> void f(int* px, int* py){
> 	incr(plus_petit(*px, *py));
> }
> ```
> 
> ```c
> // PROGRAMME 3
> int* plus_petit(int* x, int* y){
> 	if (*x <= *y) {
>   		return x;
> 	}
> 	return y;
> }
> 
> void f(int* px, int* py){
> 	incr(plus_petit(px, py));
> }
> ```
> 
> ```c
> // PROGRAMME 4
> int* plus_petit(int* x, int* y){
> 	int a = *x;
> 	int b = *y;
> 	if (a <= b) {
>   		return &a;
> 	}
> 	return &b;
> }
> 
> void f(int* px, int* py){
> 	incr(plus_petit(px, py));
> }
> ```
>
> Vérifiez vos réponses avec C Tutor.

> **Exercice 7 : lectures, affichages et redirections**
>
> Écrire une fonction qui lit en entrée :
>
> * deux entiers n et p sur la première ligne ;
> * puis n lignes contenant chacun p flottants.
>
> Cette fonction devra afficher en sortie n lignes, contenant chacune la somme des p nombres
> flottants présents sur la ligne correspondante de l’entrée.
>
> Par exemple :
>
> ```
> Entrée                          Sortie
> 2 3                             3.9
> 1.2 1.3 1.4                     6.2
> 2.3 2.4 1.5
> ```
>
> Pour plus de lisibilité, on redirigera l'entrée et la sortie lorsqu'on testera cette fonction.
>
> Pour préciser le nombre de chiffres après la virgule à l'affichage, vous pouvez utiliser `%.1f`.
>
> La fonction devra s'arrêter dès qu'une lecture de données avec `scanf` échoue, pour éviter les accès à des zones de mémoire non initialisées correctement.

> **Exercice 8 : tubes**
>
> Écrire trois programmes :
>
> * le premier dans un fichier "somme.c" qui lit deux entiers sur l'entrée standard et affiche leur somme
> * le second dans un fichier "division.c" qui lit deux entiers sur l'entrée standard et affiche leur quotient et reste de la division euclidienne
> * le troisième dans un fichier "copie.c" qui lit un entier sur l'entrée standard et l'affiche deux fois
>
> En utilisant ces trois programmes, donnez des commandes utilisant des tubes permettant :
>
> * pour deux entiers `x` et `y` lus sur l'entrée standard, d'afficher la somme du quotient et du reste de la division de `x` par `y`
> * pour un unique entier `x` lu sur l'entrée standard, d'afficher son double
> * pour deux entiers `x` et `y` lus sur l'entrée standard, d'afficher le double de la somme du quotient et du reste de la division de `x` par `y`



## Pour aller plus loin

> **Anecdote**
>
> Les fuites de mémoire sont des bugs extrêmement courants dans les programmes écrits en C. Traditionnellement, ils étaient très difficiles à détecter et à isoler : on remarque juste que la consommation mémoire du programme semble être une fonction strictement croissante du temps, et que, par exemple, notre traitement de texte consomme 200Mo quand on ouvre un document mais 1Go au bout d’une heure de travail sur ce document. L’option `-fsanitize=address` a changé la vie de beaucoup de programmeurs.
>
> **Arithmétique des pointeurs**
>
> La valeur d’un pointeur étant un entier, on peut lui appliquer un certain nombre d’opérateurs arithmétiques classiques. Les seules opérations arithmétiques valides sur les pointeurs sont :
>
> * l’addition d’un entier à un pointeur : le résultat est un pointeur du même type que le pointeur de départ ;
> * la soustraction d’un entier à un pointeur : le résultat est un pointeur du même type que le pointeur de départ ;
> * la différence entre deux pointeurs de même type : le résultat est un entier.
>
> 1. Testez le code suivant :
>
>     ```c
>     #include "librairies.h"
>
>     int main() {
>         double i = 3;
>         double* p1;
>         double* p2;
>         p1 = &i;
>         p2 = p1 + 1;
>         printf("p1 = %p\n", p1);
>         printf("p2 = %p\n", p2);
>     }
>     ```
>
>     Expliquez le lien entre les deux adresses.
>
> 2. Même questions :
>
>     ```c
>     #include "librairies.h"
>             
>     int main() {
>         char i = 3;
>         char* p1;
>         char* p2;
>         p1 = &i;
>         p2 = p1 - 1;
>         printf("p1 = %p\n", p1);
>         printf("p2 = %p\n", p2);
>     }
>     ```
>
> Si `i` est un entier, et `p` est un pointeur de type `type*`, alors l’expression `p + i` désigne un pointeur de type `type*` dont la valeur est égale à la valeur de `p` incrémentée de `i * (taille du type)` (avec la taille du type un nombre d'octets).
>
> Il en va de même pour la soustraction d’un entier à un pointeur.
>
> 3. Testez le code suivant :
>
>     ```c
>     #include "librairies.h"
>             
>     int main() {
>         int32_t i = 3;
>         int32_t* p1;
>         int32_t* p2;
>         p1 = &i;
>         p2 = p1 + 2;
>         printf("p1 = %p\n", p1);
>         printf("p2 = %p\n", p2);
>         int n = p2 - p1;
>         printf("p1 - p2 = %d\n", n);
>     }
>     ```
>
>     Expliquez le lien entre les deux adresses et ce que représente `p1 - p2`.
>
> Si `p` et `q` sont deux pointeurs de type `type*`, l’expression `p - q` désigne un entier dont la valeur est égale à `(p−q)/(taille du type)`.
>
> Cette valeur correspond au nombre d’objets de type `type` que l’on peut stocker de manière contiguë entre les adresses `p` et `q`.
>
> **S'entraîner à coder en C**
>
> Si vous avez terminé, vous pouvez aller vous entraîner sur [France-IOI](http://www.france-ioi.org/algo/chapters.php). Ce site propose de nombreux cours, exercices et problèmes dans plusieurs langages de programmation. Il n'est pas bien adapté à OCaml, mais est vraiment très bien fait pour le C.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Inspirations : V. Monfleur, A. Lick, N. Pecheux

