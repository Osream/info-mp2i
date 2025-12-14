# TP : Bases du C

**Le contenu de ce TP introduit les bases de syntaxe du langage C et doit ainsi être considéré comme du cours. Charge à vous de prendre en note les notions importantes.**

Pour rappel, la commande à utiliser pour compiler vos programmes est :

````bash
gcc -Wall -Wextra -Werror -o executable codes_sources.c
````

> **Initialisation de l'espace de travail**
>
> 1. Depuis la machine virtuelle, ouvrez Visual Studio Code, puis ouvrez le terminal intégré.
> 2. Créez-y un répertoire `tp_bases_c`.
> 3. Récupérez sur votre git le fichier `librairies.h` créé lors du TP précédent et placez le dans ce répertoire.
> 4. Créez aussi dans ce répertoire un fichier `bases.c`, placez-y la fonction `main` (vide pour l'instant) et incluez-y le fichier d'entête `librairies.h`.
>
> *Vous devrez effectuer ces manipulations toute l'année pour chaque nouveau TP en C. Notez les bien, je ne les rappellerai pas à chaque fois !*

## I. Types de base et variables

*Toutes les instructions de cette partie sont à écrire directement dans la fonction `main` du fichier `bases.c`.*

### 1. Commentaires

Première chose à savoir pour tout langage de programmation : les commentaires. En C, il y a deux manières d'écrire un commentaire :

* sur une ligne :

    ```c
    // un petit commentaire
    ```

* sur plusieurs lignes :

     ```c
     /*
         un commentaire
         sur plusieurs
         lignes
     */
     ```

Généralement, on utilise le `//` pour des petites indications dans le code, et `/* */` pour la *documentation* (nous y reviendrons).

### 2. Déclaration et affectation

Comme vous avez pu le remarquer avec les fonctions, le C est un langage typé. Lorsqu'on déclare une variable, on doit préciser son type (contrairement à OCaml qui réalise une inférence de types pour nous).

> 1. Copiez les **déclarations** suivantes dans le main :
>
>     ```c
>     int i;
>     bool b;
>     double d;
>     char c;
>     ```
>
> 2. Copiez à la suite les **affectations** suivantes :
>
>     ```c
>     i = 1;
>     b = true;
>     d = 4.2;
>     c = 'a';
>     ```
>
> 3. Il est aussi possible de déclarer une variable et de lui affecter une valeur en une même instruction. Copiez :
>
>     ```c
>     int i2 = 4;
>     bool fAlSe = false;
>     double d0uble_2 = 2.0;
>     char Carac___tere = 'b';
>     ```
>
> 4. Copiez à la suite et complétez les `??` des instructions suivantes permettant d'afficher les valeurs de ces 8 variables :
>
>     ```c
>     printf("Valeur de i : %d\n", i);
>     printf("Valeur de i2 : %d\n", i2);
>     printf("Valeur de b : %d\n", b);
>     printf("Valeur de fAlSe : %d\n", fAlSe);
>     printf("Valeur de d : ?? \n", d);
>     printf("Valeur de c : ?? \n", c);
>     printf("Valeur de d0uble_2 : ?? \n", d0uble_2);
>     printf("Valeur de Carac___tere : ?? \n", Carac___tere);
>     ```
>
> 5. Compilez puis exécutez.
>
>     On remarque que les booléens ne peuvent être affichés qu'en tant qu'entiers. A quel entier correspond le booléen `true` ? et `false` ?

Quelques points importants :

* Même si 0 et 1 peuvent représenter des booléens, le programme de MP2I précise clairement qu'*on ne doit surtout pas* les utiliser pour cela. On utilisera bien toujours `true` et `false` de la bibliothèque `stdbool`.
* La déclaration de chaque variable est *obligatoire* en C. Vous ne pouvez pas affecter une valeur à une variable si elle n'a pas été déclarée avant.
* Le typage est *statique* en C, ce qui signifie qu'une variable ne peut pas changer de type une fois qu'elle est déclarée.

*Remarque* : Par convention, on déclare toutes les variables *globales* au début du fichier (après les directives et avant les définitions de fonctions). On déclare les variables *locales* à une fonction au tout début de la fonction (même si on ne s'en sert que beaucoup plus tard dans le code). Par contre, on n'affecte une valeur à une variable qu'au moment où en a besoin.

> 6. Devinez ce que font les instructions suivantes, puis vérifier vos réponses à l'aide d'affichages :
>
>     ```c
>     int a, b;
>     int c = 1, d = 2, e = 3, f;
>     int g, h = 9;
>     int gg;
>     char q, qq;
>     double x = 1.;
>     char caractere_nul = '\0';
>     a = 4.2;
>     b = c;
>     f = d - e;
>     g = 'a';
>     gg = g + 1;
>     q = 'a';
>     qq = q + 1;
>     ```
>
> 6. Mettez tout le contenu du main en commentaire avant de passer à la suite (cela permet de conserver votre code sans qu'il ne soit ré-exécuté à chaque fois).

Les variables sont mutables en C. Pour obtenir une **constante** (variable non modifiable), on la déclare avec le mot-clef `const`.

> 8. Testez :
>
>     ```c
>     const int ANNEE = 2024;
>     ANNEE = 2025;
>     printf("%d\n", ANNEE);
>     ```
>
> 9. Testez :
>
>     ```c
>     const int ANNEE;
>     ANNEE = 2024;
>     printf("%d\n", ANNEE);
>     ```
>
> 15. Définissez une constante `PI` de valeur `3.14`.

C'est une bonne pratique d'utiliser des noms en majuscule pour les constantes, mais ce n'est pas obligatoire.

*Remarque : pour ceux qui ont déjà programmé en C, vous avez peut-être déjà utilisé la macro #define. Le programme précise clairement de ne pas l'utiliser pour déclarer des constantes.*

### 3. Opérateurs

Les **opérateurs arithmétiques** en C sont les suivants : `+    -    *    /    %`.

> 11. Testez ces opérateurs sur diverses valeurs entières (`int`) et flottantes (`double`).

Les **opérateurs de comparaison** sont les suivants : `<    <=    >    >=    ==    !=`.

> 12. * Peut-on comparer deux valeurs de types différents ? Testez pour vérifiez votre réponse.
>     * Peut-on comparer correctement deux flottants ?

Les **opérateurs logiques** booléens sont `&&    ||    !`.

> 13. L'évaluation est-elle séquentielle et paresseuse comme en OCaml ? Testez pour vérifiez votre réponse.

Il est possible de réaliser des **affectations composées**, en plaçant un opérateur arithmétique devant le `=`.

> 14. Testez :
>
>     ```c
>     int a = 1, b = 3;
>     a += 5;
>     b /= 2;
>     printf("a vaut %d et b vaut %d\n", a, b);
>     ```

*Remarque : ceux qui ont déjà programmé en C connaissent probablement les opérateurs d'incrémentation. Il sont hors programme, il ne faudra pas les utiliser.*

### 4. Conversions

Les conversions sont implicites en C (elles se font "toutes seules") quand on réalise une affectation. Il existe aussi une façon de convertir explicitement une valeur dans un autre type : `(type)valeur`.

> 15. Testez :
>
>     ```c
>     int i = 3, j = 2;
>     double k = 4.2;
>     printf("%d\n", (int)k);
>     printf("%f\n", (float)i / j);
>     printf("%f\n", (float)(i / j));

Le programme de MP2I conseille d'éviter les conversions implicites.

> 16. Pensez à placer tout ce qu'il y a dans le main en commentaire avant de passer à la suite.

## II. Structures de contrôle

Les structures de contrôle, typiques du paradigme de programmation impératif, sont les instructions conditionnelles, les boucles bornées et les boucles non bornées.

### 1. Bloc et portée des variables

Pour qu'un ensemble d'instructions appartiennent à un même bloc (même fonction, ou même conditionnelle, ou même boucle), nous devons encadrer ces instructions par des accolades. Pour les fonctions par exemple, le corps de la fonction était intégralement à l'intérieur des accolades. Dès lors qu'on sort de l'accolade, on sort de la fonction.

Les accolades délimitant un bloc délimitent aussi la **portée des variables**. Cela signifie que si l'on déclare une variable dans un bloc délimité par des accolades, une fois sorti du bloc la variable n'est plus définie. Pour les fonctions, on parle de variables *locales*. Pour les conditionnelles et les boucles, on n'en parle pas : *c'est une mauvaise pratique*.

> 1. Copiez la fonction `f` suivante au dessus du main (toujours dans le fichier `bases.c`).
>
>     ```c
>     int f() {
>         int a = 1234;
>         return a;
>     }
>     ```
>
>     Dans le main, copiez les lignes suivantes :
>
>     ```c
>     int a = 2;
>     f();
>     printf("%d\n", a);
>     ```
>
>     Compilez, testez.
>
> 2. Même question en ajoutant `a = ` devant l'appel à `f()`.

### 2. Syntaxe

> 3. * Créez, toujours dans le répertoire `tp_bases_c`, un nouveau fichier `conditions_boucles.c`.
>     * Créez le fichier d'entête `conditions_boucles.h` correspondant.
>     * Ajoutez au fichier d'entête les directives `#define, #ifndef, #endif` et incluez-y le fichier `librairies.h`.
>     * Incluez ce fichier d'entête à vos deux fichiers de code source `bases.c` et `conditions_boucles.c`.

La syntaxe d'une **instruction conditionnelle** est la suivante :

```c
if (condition1) {
    instructions1;
    ...
}
else if (condition2) {
    instructions2;
    ...
}
...
else if (conditionN) {
    instructionsN;
    ...
}
else {
    instructions_else;
    ...
}
```

Les `else if` peuvent être aussi nombreux que nécessaires (y compris aucun). Le dernier `else` est facultatif.

> 4. * Dans le fichier `conditions_boucles.c`, définissez une fonction `void affiche_bool(bool)` qui affiche « vrai » si le booléen passé en paramètre vaut `true`, et affiche « faux » sinon.
>     * Déclarez cette fonction dans le fichier `conditions_boucles.h`.
>     * Dans le main du fichier `bases.c`, appelez la fonction pour la tester.
>     * Compilez et exécutez.
>
> 5. Écrivez une fonction `void est_pair(int)` qui prend en paramètre un entier et affiche une phrase indiquant si cet entier est pair ou impair. On affichera une phrase supplémentaire si l'entier est nul.
>
>     N'oubliez pas de déclarer la fonction et de tester !
>
> 6. Retour sur la portée des variables. Testez dans le main :
>
>     ```c
>     if (true) {
>         int x = 4;
>         printf("%d\n", x);
>     }
>     printf("%d\n", x);
>     ```
>
>     Comprenez-vous pourquoi on dit que c'est une mauvaise pratique de déclarer une variable dans un bloc ?

La syntaxe pour les **boucles non bornées** :

```c
while (condition) {
    instructions;
    ...
}
```

Si la condition est vraie, les instructions sont exécutées puis la condition est à nouveau testée. Si elle est fausse, le programme passe à la suite.

> 7. Toujours dans le fichier `conditions_boucles.c`, définissez une fonction `int depasse_seuil(int)` qui renvoie l'entier $n$ à partir duquel $`\displaystyle\prod_{i=1}^n i`$ dépasse le seuil passé en paramètre.
>
>     N'oubliez pas de la déclarer dans le `.h` et de tester dans le main !

Et la syntaxe pour les **boucles bornées** :

```c
for (initialisation; condition; modification) {
    instructions;
    ...
}
```

Exemple :

```c
int i;
for (i = 0; i < 4; i += 1) {
    printf("%d\n", i);
}

// ou encore :
for (int j = 0; j < 4; j += 1) {
    printf("%d\n", j);
}
```

On remarque qu'il est possible de déclarer une variable directement dans l'initialisation.

> 8. Testez ces deux codes (directement dans le main).
> 9. Que valent les variables `i` et `j` une fois sorti des boucles ? Testez.

On s'autorisera à déclarer une variable dans l'initialisation si on est sûr de ne pas en avoir l'utilité après.

> 10. Toujours dans le fichier `conditions_boucles.c`, définissez une fonction `int somme(int)` qui calcule $`\displaystyle\sum_{i=0}^n i\text{ avec }n\in\mathbb{N}`$.
>
>     N'oubliez pas de la déclarer dans le `.h` et de tester dans le main !

Il existe deux mots-clefs particuliers sur les boucles (for et while) :

* `continue` : permet de passer directement au tour de boucle suivant sans terminer celui actuel ;
* `break` : permet d'interrompre la boucle.

> 11. Testez (dans le main) :
>
>     ```c
>     for (int i = 0; i < 4; i += 1) {
>         if (i == 2) {
>             break;
>         }
>         printf("%d\n", i);
>     }
>     ```
>
> 12. Testez :
>
>     ```c
>     for (int i = 0; i < 4; i += 1) {
>         if (i == 2) {
>             continue;
>         }
>         printf("%d\n", i);
>     }
>     ```

### 3. Retour sur les boucles `for`

Nous avons pour l'instant vu qu'une boucle bornée s'écrivait ainsi :

```c
for (initialisation; condition; modification) {
    instructions;
}
```

En réalité, `initialisation` est optionnelle, on peut écrire :

```c
for (; condition; modification) {
    instructions;
}
```

> 13. Testez (dans le main) :
>
>     ```c
>     int i = 1;
>     for (; i <= 3 ; i += 1) {
>         printf("%d\n", i);
>     }
>     ```
>
> 14. Écrivez (dans `conditions_boucles.c`) une fonction qui prend en paramètre deux entiers `m`  et `n`  affiche les entiers de `m` à `n` inclus de la même manière. N'oubliez pas de tester !

En réalité, `modification` est optionnelle aussi, on peut écrire :

```c
for (initialisation; condition; ) {
    instructions;
}
```

> 15. Testez :
>
>     ```c
>     for (int i = 1; i <= 3; ) {
>         printf("%d\n", i);
>         i += 1;
>     }
>     ```
>
> 16. Modifiez votre fonction de la question 14 pour n'avoir ni initialisation ni modification.

Et pour finir, `condition` aussi est optionnelle, on peut écrire :

```c
for (initialisation; ; modification) {
    instructions;
}
```

> 17. Testez :
>
>     ```c
>     for (int i = 1; ; i += 1) {
>         if (i > n) {
>             break;
>         }
>         printf("%d\n", i);   
>     }
>     ```
>
> 13. Modifiez votre fonction de la question 16 pour n'avoir ni initialisation ni modification ni condition.
>
> 14. Que se passe-t-il si on a une boucle sans condition et sans aucun `break` ?

Une boucle for peut donc avoir cette forme :

```c
for (;;) {
    instructions;
}
```

> 20. À votre avis, est-ce une bonne pratique ?
> 21. Peut-on écrire n'importe quelle boucle while avec une boucle for ? Et inversement ?
> 22. Essayez de déterminer les cas où on utilisera une boucle for, et les cas où on utilisera une boucle while. Appelez le professeur pour faire le point.

## III. Exercices

Pour ces exercices, je vous laisse créer les fichiers nécessaires (`.c` et `.h`) par vous-même.

> **Quelques conditionnelles**
>
> 1. Écrivez une fonction qui prend en paramètres deux entiers, un numéro de jour et un numéro de mois, et affiche la saison correspondante.
> 2. Une année est bissextile si l’année est divisible par 4 et non divisible par 100, ou bien si l’année est divisible par 400. Écrivez une fonction qui prend une année en paramètre et renvoie un booléen indiquant si elle est bissextile.
> 3. Écrivez une fonction qui prend en paramètres trois entiers : un jour, un mois et une année et vérifie si la date existe. Vous pourrez appeler la fonction précédente.
> 4. Écrire une fonction qui prend en entrée une date sous la forme de trois entiers et affiche la date du lendemain.

> **Quelques boucles**
>
> 1. Écrivez une fonction qui calcule `n!`.
> 2. Écrivez une fonction qui calcule $`n^p`$ en utilisant uniquement des multiplications.
> 3. Les cheveux de Elsa mesurent actuellement 21 centimètres. Elle souhaite les couper quand ils atteindront 50 centimètres. Chaque jour la longueur de ses cheveux augmente de 1%. Écrivez un programme qui calcule dans combien de jours Elsa devra couper ses cheveux.
> 4. Écrivez une fonction qui vérifie si un entier `p` est premier.
> 5. Écrivez une fonction qui prend en entrée un entier `n` et renvoie le plus petit $`k \geq 0`$ tel que $`2^k \geq n`$.


> **Sommes**
>
> Écrivez des fonctions calculant les sommes suivantes :
>
> 1. $`\displaystyle S_1(n) = \sum_{k=1}^n (2k + 1)`$
>
> 2. $`\displaystyle S_2(n) = \sum_{k=1}^n \frac 1 {k^2}`$
>
> 3. $`\displaystyle S_3(n) = \sum_{i=1}^n \sum_{j=1}^n (i+j)`$
>
> 4. $`\displaystyle S_4(n) = \sum_{i=1}^n \sum_{j=i}^n (i+j)`$
>
> 5. $`\displaystyle S_5(n) = \sum_{i=1}^n \sum_{j=1}^{i-1} (i+j)`$
>
> 6. Modifiez le main pour obtenir l'affichage suivant :
>
>     ```
>     S1(0) = 0
>     S2(0) = 0.000000
>     S3(0) = 0
>     S4(0) = 0
>     S5(0) = 0
>     S1(1) = 3
>     S2(1) = 1.000000
>     S3(1) = 2
>     S4(1) = 2
>     S5(1) = 0
>     S1(2) = 8
>     S2(2) = 1.250000
>     S3(2) = 12
>     S4(2) = 9
>     S5(2) = 3
>     S1(3) = 15
>     S2(3) = 1.361111
>     S3(3) = 36
>     S4(3) = 24
>     S5(3) = 12
>     ```


> **For vs While**
>
> Ré-écrivez les boucles suivantes en utilisant une boucle while.
>
> 1. ```c
>     int n = 12;
>     for (int i = 0; i < n; i += 1) {
>         if (i % 2 == 0) {
>             printf("%d\n", i);
>         }
>     }
>     ```
>     
> 20. ```c
>     int i = 3, n = 12;
>     for (; i < n; ) {
>         printf("%d\n", i);
>         if (i % 2 == 1) {
>             i = i + 1;
>         }
>         else {
>             i = i + 2;
>         }
>     }
>     ```
>     
> 21. ```c
>     for (int i = 100; ;) {
>         if (i == 1) {
>             break;
>         }
>         else {
>             i /= 2;
>         }
>         printf("%d\n", i);
>     }   
>     ```
>
> 22. ```c
>     int i, n = 12;
>     for (i = 0; n != 0; n /= 2) {
>         i = i + 1;
>     }
>     printf("%d\n", i);
>     ```

> **Petits affichages**
>
> 1. Écrire une fonction qui affiche tous les entiers multiples de 3 entre 1 et 100 et renvoie le nombre de tels entiers.
>
> 3. Écrire une fonction qui affiche tous les entiers entre 100 et 0 (compte à rebours) dans l’ordre décroissant.
>
> 4. Écrire une fonction qui affiche la table de multiplications de taille 10*10.
>
> 5. Écrire une fonction qui prend en entrée un entier `n` et un caractère `c` et affiche une ligne de `n` caractères `c`.
>
>     ```c
>    // ex avec n = 5, c = 'X'
>    XXXXX
>    ```
> 
> 6. Écrire une fonction qui prend en entrée deux entiers `n` et `m` et un caractère `c` et affiche un rectangle de `m` lignes et `n` colonnes composé du caractère `c`.
>
>     ```c
>    // ex avec m = 3, n = 4, c = 's'
>    ssss
>    ssss
>    ssss
>    ```
> 
> 7. Même question mais cette fois avec un rectangle creux :
>
>     ```c
>    ssss
>    s  s
>    ssss
>    ```
> 
> 8. Écrire une fonction qui prend en entrée un entier `n` et un caractère `c` et affiche un triangle creux de `n` caractères `c`.
>
>     ```c
>    // n = 6, c = 'x'
>     x
>     xx
>     x x
>     x  x
>     x   x
>     xxxxxx
>    ```
> 
> 9. Même question en "redressant" le triangle :
>
>     ```c
>    // n = 4, c = 'x'
>        x
>       x x
>      x   x
>     xxxxxxx
>    ```

## Pour aller plus loin

> 1. Si vous avez terminé, vous pouvez aller vous entraîner sur [France-IOI](http://www.france-ioi.org/algo/chapters.php). Ce site propose de nombreux cours, exercices et problèmes dans plusieurs langages de programmation. Il n'est pas bien adapté à OCaml, mais est vraiment très bien fait pour le C.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Inspirations : J.B. Bianquis (exercices sommes)
