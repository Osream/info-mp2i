# TP : Chaînes de caractères en C

Dans ce TP, nous allons manipuler les chaînes de caractères en C.

Pour rappel, vous devez compiler vos programmes avec la commande suivante :

```bash
$ gcc -Wall -Wextra -Werror -fsanitize=address -o executable codes_sources.c
```

> **Initialisation de l'espace de travail**
>
> 0. Créez un fichier `chaines.c` contenant directement la fonction principale `main` et incluant le fichier `librairies.h`.
>
> *C'est le dernier TP en C où je vous indique quoi créer, à partir du suivant, ce sera à vous de gérer votre organisation.*

*Remarque : si vous souhaitez désactiver l'erreur "unused variable" qui apparaît lorsque vous n'utilisez pas une variable, et qui peut être assez contraignante, vous pouvez ajouter l'option `-Wno-unused-variable` lorsque vous compilez.*

## I. Syntaxe pour les chaînes de caractères

### 1. Création de chaînes

Une chaîne de caractères en C est en réalité un **tableau statique** de caractères.

Ce tableau de caractère **termine toujours par le caractère nul** `'\0'`. Ce caractère nul est appelé **sentinelle**.

> 1. Directement dans le `main`, copiez les lignes suivantes :
>
>     ```c
>     char bjr[8] = {'b', 'o', 'n', 'j', 'o', 'u', 'r', '\0'};
>     ```
>     
>    Ajoutez à la suite une boucle for permettant d'afficher les 8 caractères un par un, séparés par un tiret.
>     
>5. La fonction `printf` permet en réalité d'afficher une chaîne sans avoir besoin d'une boucle. Testez :
> 
>    ```c
>    printf("%s\n", bjr);
>    ```
> 
>6. Remplaçons le caractère `'n'` par le caractère nul, testez :
> 
>     ```c
>    char bjr[8] = {'b', 'o', '\0', 'j', 'o', 'u', 'r', '\0'};
>    printf("%s\n", bjr);
>    ```

La sentinelle marque la fin de la chaîne, peu importe où elle se trouve dans le tableau.

Comme c'est long de devoir définir les caractères un par un à mettre dans le tableau, le C propose une syntaxe allégée qui utilise les guillemets.

> 4. Testez :
>
>     ```c
>     char hlo[6] = "hello";
>     ```
>
>     Pourquoi le tableau doit-il être de taille au moins 6 ?
>
> 5. Testez :
>
>     ```c
>     char cc[] = "coucou";
>     ```
>
>     Pourquoi peut-on ne rien mettre dans les crochets ?

La syntaxe avec les guillemets pour les chaînes, tout comme celle avec les accolades pour les tableaux, permet *d'initialiser* les valeurs lors de la *création* du tableau.

Tout comme `{1, 2, 3}` n'est *pas* un tableau, **`"abc"` n'est *pas* une chaîne de caractères**. Simplement un raccourci syntaxique pour **initialiser** un bloc mémoire de 4 caractères ('a', 'b', 'c' et la sentinelle '\0').

On ne peut donc pas écrire écrire ceci :

```c
char c[4];
c = "abc"; // NON ! "abc" N'EST PAS UNE CHAÎNE !
```

### 2. Fonctions de `<string.h>`

Il existe une bibliothèque qui fournit quelques fonctions utiles sur les chaînes de caractères : `<string.h>`.

* La fonction `size_t strlen(chaine)` renvoie le nombre de caractères de la chaîne *avant la sentinelle*.
* La fonction `void strcpy(chaine_destination, chaine_source)` copie la chaîne "source" dans la chaîne "destination".
* La fonction `void strcat(chaine_destination, chaine_source)`  concatène la chaîne source dans la chaîne "destination" à la suite de ce qui y était.
* La fonction `int strcmp(chaine1, chaine2)` compare deux chaînes selon l'ordre lexicographique (l'ordre du dictionnaire) et renvoie 0 si elles sont égales, un entier négatif si la première chaîne est inférieure à la seconde, un entier positif sinon.

> 6. Incluez la bibliothèque dans le fichier `chaines.c`, puis testez dans le `main` :
>
>     ```c
>     // Fonction strlen
>     char hello[] = "hello";
>     printf("Taille de hello : %d\n", (int)strlen(hello));
>     hello[2] = '\0';
>     printf("Nouvelle taille de hello : %d\n", (int)strlen(hello));
>     
>     // Fonction strcpy
>     char bjr1[8] = "bonjour";
>     char bjr2[8];
>     strcpy(bjr2, bjr1);
>     printf("bjr1 est de taille %d et vaut : %s\n", (int)strlen(bjr1), bjr1);
>     printf("bjr2 est de taille %d et vaut : %s\n", (int)strlen(bjr2), bjr2);
>     bjr1[2] = '\0';
>     printf("bjr1 est de taille %d et vaut : %s\n", (int)strlen(bjr1), bjr1);
>     printf("bjr2 est de taille %d et vaut : %s\n", (int)strlen(bjr2), bjr2);
>     
>     // Fonction strcat
>     char bonjour[8] = "bonjour";
>     char monde[10] = " le monde";
>     char bjr_mnd[20];
>     strcpy(bjr_mnd, bonjour);
>     strcat(bjr_mnd, monde);
>     printf("bonjour est de taille %d et vaut : %s\n", (int)strlen(bonjour), bonjour);
>     printf("monde est de taille %d et vaut : %s\n", (int)strlen(monde), monde);
>     printf("bjr_mnd est de taille %d et vaut : %s\n", (int)strlen(bjr_mnd), bjr_mnd);
>     
>     // Fonction strcmp
>     char banjour[8] = "banjour";
>     char bon[4] = "bon";
>     char bon2[4] = "bon";
>     printf("Comparaison de banjour et bonjour : %d\n", strcmp(banjour, bonjour));
>     printf("Comparaison de bonjour et bon : %d\n", strcmp(bonjour, bon));
>     printf("Comparaison de bon et bon2 : %d\n", strcmp(bon, bon2));
>     ```
>
> 7. Attention, les fonctions `strcpy` et `strcat` ne vérifient pas du tout que le tableau de destination est suffisamment grand pour y copier / concaténer tout le tableau source.  C'est à vous d'y prendre garde !
>
>     À votre avis, que peut-il se passer si on tente de copier / concaténer un tableau dans un autre qui est trop petit ?

*Remarque pour les concours : vous devez connaître et savoir utiliser les fonctions `strlen`, `strcpy`, `strcat` et `strcmp`. Par contre, la bibliothèque `<string.h>` ne fait pas partie de celles autorisées par défaut : vous n'avez donc le droit de vous servir de ces fonctions que si le sujet l'autorise.*

Comme les fonctions  `strlen`, `strcpy`, `strcat` et `strcmp` peuvent ne pas être autorisées dans un sujet de concours, il faut absolument savoir les ré-écrire rapidement.

> 8. Écrivez (dans le fichier `chaines.c`) une fonction `int taille_chaine(char chaine[])` qui renvoie la taille d'une chaîne de caractère sans utiliser `strlen`. Il faut donc parcourir la chaîne jusqu'à croiser un caractère nul.

Lorsqu'on parcourt une chaîne de caractères, il faut éviter d'utiliser `strlen` dans la condition d'arrêt car pour calculer la taille de la chaîne elle est intégralement parcourue. On utilise donc plutôt la comparaison avec le caractère nul `\0`.

> Dans le fichier `chaines.c`, écrivez les fonctions suivantes :
>
> 9. `void copie_chaine(char dest[], char src[])` sans utiliser `strcpy`. On supposera que le tableau `dest` est suffisamment grand, sans le vérifier.
> 10. `void concatene_chaine(char dest[], char src[])` sans utiliser `strcat`. On suppose à nouveau que le tableau est suffisamment grand.
> 11. `int compare_chaine(char s1[], char s2[])` sans utiliser `strcmp`. On renverra un entier négatif quelconque si la première chaîne est inférieure à la seconde, 0 si elles sont égales, et un entier positif quelconque sinon.
> 12. Testez vos 4 fonctions avec le même `main` que celui de la question 6.

Attention, tout comme vos propres fonctions, les fonctions de la bibliothèque `<string.h>` ne marchent que si le tableau de caractères donné en paramètre contient une sentinelle. **Si un `char c[]` ne contient pas de sentinelle, c'est un tableau de caractères, et non une *chaîne* de caractères.**

Les chaînes fonctionnent essentiellement comme les tableaux. Ainsi, si on veut copier une chaîne `c1` :

* Écrire `char c2[] = c1` ne fonctionne pas !
* Écrire `char* c2 = c1` ne copie pas le tableau, mais son adresse (donc modifier l'un modifie l'autre).

> 13. Testez le code suivant dans [C Tutor](https://pythontutor.com/visualize.html#mode=edit) :
>
>     ```c
>     int main() {
>         char c1[] = "abc";
>         char* c2 = c1;
>         c1[0] = 'X';
>         c2[0] = 'Y';
>     }
>     ```

Pour copier une chaîne on utilise donc `strcpy` ou on fait la copie à la main avec une boucle.

### 3. Mutabilité des chaînes

Nous avons dit lors du TP précédent qu'un tableau n'était qu'un pointeur sur son premier élément. Une chaîne serait donc un pointeur vers le premier caractère ?

C'est majoritairement vrai, mais il y a quand même une différence importante, à laquelle nous devrons faire attention lorsque nous manipulerons des chaînes de caractères :

* un `char* c` est un *pointeur* vers une zone contenant un ou plusieurs caractères : **on ne peut donc pas modifier les caractères** de cette zone ; par contre on peut modifier le pointeur.
* un `char c[]` est un *tableau* contenant un ou plusieurs caractères dont l'adresse de la première case est le pointeur `c` : **on peut donc modifier les caractères** du tableau, mais *pas* son adresse.

> 14. Testez le code suivant dans [C Tutor](https://pythontutor.com/visualize.html#mode=edit) :
>
>     ```c
>     int main() {
>         char c1[] = "abc"; // caractères mutables
>         c1[1] = 'X';
>         char* c2 = "abc"; // caractères non mutables
>         c2[1] = 'X';
>     }
>     ```
>
> 14. Testez dans [C Tutor](https://pythontutor.com/visualize.html#mode=edit) :
>
>     ```c
>     int main() {
>         char c1[] = "abc"; // pointeur non mutable
>         char* c2 = "abc"; // pointeur mutable
>         c2 += 1;
>         // essayez ensuite d'ajouter cela : c1 += 1;
>     }
>     ```

Supposons qu'on ait une chaîne « bonjour tout le monde » et que l'on souhaite ne conserver que « tout le monde » :

* si on travaille avec un `char* c`, il suffit de "décaler" le pointeur de 8 cases vers la droite (rapide).
* si on travaille avec un `char c[]`, il faut alors recopier un par un tous les caractères de « tout le monde » à partir de l'indice 0 (long).

Supposons qu'on ait une chaîne « bonjour tout le monde » et que l'on souhaite avoir « bonsoir tout le monde » :

* si on travaille avec un `char c[]`, il suffit de modifier les 2 caractères souhaités (rapide).
* si on travaille avec un `char* c`, il faut recréer la chaîne entièrement (long).

**En fonction de l'utilisation souhaitée pour une chaîne, une déclaration sera souvent préférable à une autre.** Par défaut, le programme suggère d'utiliser les chaînes de caractères comme des tableaux : on écrira donc plutôt `char c[]`.

Il nous reste une dernière façon d'obtenir une chaîne à étudier : celle avec l'allocation dynamique, par exemple quand une fonction doit renvoyer une chaîne.

> 16. Testez le code suivant dans [C Tutor](https://pythontutor.com/visualize.html#mode=edit) :
>
>     ```c
>     #include <stdio.h>
>     char* f(int i) {
>       if (i < 0) {
>           return "neg";
>       }
>       else {
>           return "pos";
>       }
>     }
>     
>     int main() {
>         char* c = f(4);
>         printf("%s\n", c);
>     }
>     ```
>
> 16. Si on peut renvoyer une chaîne ainsi, difficile de voir l'intérêt de l'allocation dynamique pour l'instant...
>
>     Toujours dans C Tutor, ajoutez les lignes suivantes dans le `main` précédent :
>
>     ```c
>     char* c1 = f(7);
>     printf("%s\n", c1);
>     char* c2 = f(-1);
>     printf("%s\n", c2);
>     c2[0] = 'X';
>     ```
>

Lorsqu'une fonction renvoie une chaîne de caractères, l'allocation dynamique permettra alors :

* de bien obtenir une chaîne différente à chaque appel de fonction
* de pouvoir modifier la chaîne renvoyée.

> 18. Testez dans [C Tutor](https://pythontutor.com/visualize.html#mode=edit) le code suivant, modifié pour allouer les chaînes dynamiquement :
>
>     ```c
>     #include <stdio.h>
>     #include <stdlib.h>
>     char* f(int i) {
>         char* res = malloc(4 * sizeof(char));
>         if (i < 0) {
>             res[0] = 'n' ; res[1] = 'e' ; res[2] = 'g' ; res[3] = '\0';
>             return res;
>         }
>         else {
>             res[0] = 'p' ; res[1] = 'o' ; res[2] = 's' ; res[3] = '\0';
>             return res;
>             }
>     }
>                     
>     int main() {
>         char* c = f(4);
>         printf("%s\n", c);
>         char* c1 = f(7);
>         printf("%s\n", c1);
>         char* c2 = f(-1);
>         printf("%s\n", c2);
>     	c2[0] = 'X';
>         free(c); free(c1); free(c2);
>       }
>     ```
>     
>     Quel est cependant l'inconvénient évident de l'allocation dynamique ici ?

De manière générale, nous n'allouerons une chaîne dynamiquement *que* si on souhaite la modifier par la suite. Si ce n'est pas le cas, on utilisera une allocation statique classique (le code est ainsi plus léger).

Si on alloue une chaîne dynamiquement, il ne faudra pas oublier la sentinelle lorsqu'on l'initialise (sinon, ce n'est pas une chaîne...).

## II. Tableaux de chaînes

Les chaînes de caractères étant des tableaux, si on souhaite avoir un tableau de chaînes on se retrouve alors avec un tableau bidimensionnel, de type `char**`.

> 1. Comparez les deux affectations suivantes à l'aide de [C Tutor](https://pythontutor.com/visualize.html#mode=edit) :
>
>     ```c
>     char t[3][8] = {"bonjour", "le", "monde"};
>     ```
>
>     ```c
>     char* t[3] = {"bonjour", "le", "monde"};
>     ```
>
>     Notez notamment les différences en terme de mémoire.

Sauf besoin spécifique, nous utiliserons la deuxième façon pour déclarer nos tableaux de chaînes de caractères.

```c
char* /*nom du tableau*/[/*taille*/] = {/*chaînes séparées par des virgules*/};
```

Comme tout tableau statique en C, il ne faudra pas oublier de conserver la taille du tableau dans une constante.

> 2. Écrivez (dans le fichier `chaines.c`) une fonction `void affiche_tab_de_chaines(char* t[], int taille_t)` qui affiche les chaînes de caractères du tableau `t` séparées par des espaces.
> 3. Écrivez une fonction `int taille_totale(char* t[], int taille_t)` qui calcule la somme des tailles des chaînes du tableau `t`.

Comme tout tableau multidimensionnel, lorsqu'on alloue dynamiquement un tableau de `x` chaînes de caractères, il y a 2 façons de le faire :

* soit en allouant `x` cases contenant chacune un pointeur de type `char*` vers une chaîne
* soit en linéarisant le tableau (toutes les chaînes sont alors stockées "à la suite")

> 4. À votre avis, laquelle de ces deux solutions privilégiera-t-on pour les tableaux de chaînes ?
> 5. Écrivez une fonction `char** tab_langages(int taille)` qui crée et renvoie un tableau dont la taille est passée en paramètre et qui contient une fois sur 2 la chaîne "OCaml" et une fois sur 2 la chaîne "C".
> 6. Dans le `main`, testez votre fonction puis :
>     * essayez de remplacer une des chaînes "C" en "Python", est-ce que cela fonctionne ?
>     * essayez de modifier un des « a » d'une chaîne "OCaml" en « b », est-ce que cela fonctionne ?

## III. Exercices

Les exercices de cette partie sont à faire dans un fichier `chaines_manip.c`, avec fichier d'entête correspondant.

> **Exercice 1 : parcours de chaînes**
>
> On rappelle que lorsqu'on parcourt une chaîne de caractères, il faut éviter d'utiliser `strlen` dans la condition d'arrêt car pour calculer la taille de la chaîne elle est intégralement parcourue. On utilise donc plutôt la comparaison avec le caractère nul `\0`.
>
> 1. Écrivez une fonction qui affiche une chaîne de caractères en allant à la ligne entre chaque caractère.
> 2. Écrivez une fonction qui prend en paramètre une chaîne `sortie` et une chaîne `entree` et renverse `entree` dans `sortie`.
> 3. Écrivez une fonction qui détermine si une chaîne est un palindrome.
> 4. Écrivez une fonction qui prend en paramètre une chaîne et échange les caractères deux à deux. Par exemple `abcdefg` devient `badcfeg`.
> 5. Écrivez une fonction qui prend en paramètre trois chaînes et remplit la troisième avec le plus petit caractère entre les deux premières chaînes pour chaque indice. On s'arrêtera dès que l'on croise la première sentinelle (peu importe dans quelle chaîne).

> **Exercice 2 : renvoi de chaînes**
>
> Écrivez les fonctions suivantes :
>
> 1. `char* couleur(int r, int g, int b)` qui calcule la couleur moyenne du pixel passé en paramètre, et renvoie « noir » si elle est inférieure à 128, « blanc » sinon.
> 2. `char* renverse(char chaine[])` qui renvoie une chaîne renversée par rapport à celle passée en paramètre.
> 3. `char* lit_chaine()` qui lit sur l'entrée standard un entier puis une chaîne de taille strictement inférieure à cet entier, puis renvoie la chaîne.
> 4. `char* mot_bienvenue()` qui lit sur l'entrée standard un prénom (qu'on supposera de 20 lettres maximum) et renvoie une chaîne contenant le mot de bienvenue suivant : « [prénom], bienvenue au TP sur les chaînes de caractères ! J'espère que tu apprendras beaucoup de choses. »

> **Exercice 3 : code César**
>
> 1. Écrivez une fonction `char* encode(char* message, int i)` qui prend en entrée une chaîne de caractères contenant uniquement des lettres majuscules et un entier `i` et qui renvoie une chaîne de caractères qui correspond au message encodé à l’aide du code César, c’est-à-dire où on a appliqué un décalage de `i` lettres à chacune des lettres du message.
>
>     Par exemple, `encode("YOU", 3)` renvoie `"BRX"`.
>
> 2. Améliorez votre fonction pour prendre en paramètre une chaîne contenant n'importe quel type de caractère. S'il s'agit d'une lettre (minuscule ou majuscule) elle sera transformée, sinon le caractère sera conservé tel quel.
>
> 3. Testez votre fonction avec le `main` suivant, en compilant avec toutes les options :
>
>     ```c
>     int main () {
>         char msg[] = "bonjour YOU z !";
>         char* cesar = encode(msg, 3);
>         printf("le message «%s» devient avec un décalage de 3 : «%s»\n", msg, cesar);
>         free(cesar);
>     }
>     ```

> **Exercice 4 : recherche de motifs**
>
> 1. Écrivez une fonction `est_fact_gauche` qui prend en entrée deux chaînes de caractères `s1` et `s2` et détermine si `s1` est un facteur gauche de `s2`. Par exemple "mp" est un facteur gauche de "mp2i". On renverra un booléen.
> 2. Écrivez une fonction `est_fact` qui prend en entrée deux chaînes de caractères `s1` et `s2` et détermine si `s1` est un facteur de `s2`. Par exemple "bell" est un facteur de "libellule".

> **Exercice 5 : un langage**
>
> On appelle « mot » une chaîne de caractères (type `char*`) et « langage » un ensemble de mots (type `char**`).
>
> 1. Écrivez une fonction `appartient` qui prend en paramètres un mot ainsi qu'un langage et sa taille et détermine si le mot appartient au langage. On renverra un booléen.
> 2. Écrivez une fonction `ajoute` qui prend en paramètres un mot ainsi qu'un langage et sa taille et renvoie un nouveau langage construit à partir de celui passé en paramètre où on a ajouté le nouveau mot *s'il n'y était pas déjà présent*.
> 3. Écrivez une fonction `verifie` qui prend en paramètre un tableau de chaînes et détermine s'il s'agit bien d'un langage, c'est-à-dire s'il n'y a pas de mot en double.

## Pour aller plus loin

> Si vous avez terminé, vous pouvez également aller vous entraîner sur [France-IOI](http://www.france-ioi.org/algo/chapters.php). Ce site propose de nombreux cours, exercices et problèmes dans plusieurs langages de programmation. Il n'est pas bien adapté à OCaml, mais est vraiment très bien fait pour le C.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*

Inspirations : *V. Monfleur* (IV. Exercices)
