# TP : Ligne de commande et déclaration de types en C

On rappelle la commande pour compiler vos fichiers :

```bash
$ gcc -Wall -Wextra -Werror -fsanitize=address -o executable codes_source.c
```

*Remarque : si vous souhaitez désactiver l'erreur "unused variable" qui apparaît lorsque vous n'utilisez pas une variable, et qui peut être assez contraignante, vous pouvez ajouter l'option `-Wno-unused-variable` lorsque vous compilez.*

## I. Ligne de commande

Pour l'instant, votre fonction `main` avait systématiquement le prototype suivant :

```c
int main (void)
```

> 1. Rappelez pourquoi le type de retour est toujours `int` pour la fonction `main`. Quelle valeur a l'entier renvoyé ?

Un autre prototype est possible pour cette fonction :

```c
int main(int argc, char* argv[])
```

* `argc` (*argument count*) est le nombre d'arguments passés au programme, sachant que le premier argument est toujours la commande utilisée pour le lancer.
* `argv` (*argument vector*) est un tableau de chaînes de caractères de taille `argc`. Le premier élément (indice 0) est le nom de la commande, les autres éléments correspondent chacun à un argument, dans l'ordre où ils ont été fournis.

Les arguments sont donnés séparés par des espaces sur la ligne de commande qui lance l'exécution du programme.

Ainsi, si on exécute le programme avec :

```bash
$ ./executable argument1 argument2 ... argumentN
```

alors `argc` vaut `N+1` et `argv` est un tableau contenant les chaînes "./executable", "argument1", ..., "argumentN".

> 2. Expliquez d'où vient le type de `argv`.
> 2. Combien vaut `argc` au minimum ?
> 3. Écrivez un main avec un tel prototype, qui affiche la valeur de `argc` puis successivement toutes les valeurs contenues dans `argv`.
> 4. Testez en exécutant sans argument comme d'habitude, puis avec un argument, puis plusieurs.

Lorsqu'un programme attend des arguments, il faut vérifier que l'utilisateur respecte bien ce qui est attendu. Si le nombre d'arguments donnés ne correspond pas à ce qu'on demandait :

* on affiche un message rappelant ce qui est attendu (par exemple « Mauvais arguments, on attend : ./[nom_de_l'executable] [type et signification de l'argument 1] [ ... ] ») ;
* on renvoie 1 (au lieu de l'habituel 0 qui signifie que tout s'est bien passé).

Chaque argument est donné sous forme d'une chaîne de caractères. Il faut donc parfois les convertir dans le bon type pour s'en servir. La bibliothèque `stdlib.h` fournit des fonctions pour les conversions de chaînes :

* `int atoi(char*)` = chaîne vers entier (*Ascii TO Int*)
* `double atof(char*)` = chaîne vers réel (*Ascii TO Float*)

> 6. Écrivez un programme qui prend en argument un entier et un réel et affiche leur somme. Si le nombre d'arguments fournis est incorrect, le programme affichera un message d'erreur précisant les consignes à respecter pour l'exécution, et se terminera sur une erreur.
> 7. Rappelez comment récupérer l'entier renvoyé par le main depuis le terminal. Testez votre programme précédent avec le bon nombre d'arguments puis avec le mauvais et vérifiez l'entier renvoyé dans les deux cas.

Lorsqu'un programme attend une entrée de l'utilisateur, il y a donc deux façons de faire :

* **en ligne de commande** : ce sont les arguments du main comme on vient de le voir ;
* **en lisant sur le flux standard** : avec `scanf` comme on le faisait avant.

> 8. À votre avis, dans quel cas préfère-t-on la ligne de commande ? le flux standard ?

## II. Déclaration de types simples

Il est possible en C de définir ses propres types.

### 1. Alias

Pour créer un alias (renommer un type existant), on utilise le mot-clef **typedef**.

Par exemple, on peut définir un alias pour le type `int64_t` (entiers stockés sur 64 bits) :

```c
typedef int64_t grand_entier;
```

On peut alors se servir de `grand_entier` comme de n'importe quel type :

```c
int main() {
    grand_entier i = 4;
    grand_entier j = 7;
    grand_entier k;
    k = i + j;
    grand_entier tableau_statique[3] = {i, j, k};
    grand_entier* tableau_dynamique = malloc(3 * sizeof(grand_entier));
    free(tableau_dynamique);
    // ...
}
```

Si le type n'est utilisé que dans le module même, alors on place cette définition de type dans le code source directement. Par contre, si le type est destiné à être utilisé dans d'autres fichiers, alors cette déclaration est à placer dans le fichier d'entête.

> 1. Dans un fichier `structures.h`, déclarez un alias "reel" vers le type `double`.
> 2. Dans un fichier `structures.c`, écrivez une fonction qui prend en paramètre deux réels (du type déclaré) et renvoie leur produit.
> 3. Appelez votre fonction depuis un autre fichier contenant un main et testez.

On peut définir des alias vers tout ce que l'on souhaite, y compris des tableaux.

Voici un exemple si on souhaite manipuler des tableaux bidimensionnels de taille 2 par 2 :

```c
typedef int carre[2][2];
// puis par exemple :
// carre id = {{1,0}, {0,1}};
// au lieu de :
// int id[2][2] = {{1,0}, {0,1}};
```

### 2. Types énumérés

On peut également définir en C des types énumérés avec le mot-clef **enum**. On peut par exemple redéfinir le type `bool` ainsi :

```c
enum booleen_e {faux, vrai}; // le _e à la fin du nom est optionnel mais vivement conseillé
```

On déclare alors un booléen ainsi :

```c
enum booleen_e v = vrai;
```

On peut utiliser le type `enum booleen_e` comme n'importe quel autre type (en paramètre d'une fonction, en valeur de retour, ...).

> 4. Placez la déclaration du type énuméré dans un fichier `.c`, et placez dans ce même fichier un `main` déclarant une variable `f` valant faux.
> 5. Toujours dans ce fichier, définissez une fonction `void affiche_booleen(enum booleen_e)` qui prend en paramètre un booléen et l'affiche.
> 6. Définissez une fonction `enum booleen_e est_pair(int)` qui prend en paramètre un entier et renvoie vrai s'il est pair, faux sinon.

La syntaxe est assez lourde pour les types énumérés, comme on doit répéter le mot-clef `enum` à chaque fois... Une astuce est alors d'utiliser un alias avec `typedef` :

```c
enum booleen_e {faux, vrai};
typedef enum booleen_e booleen;
// puis : booleen b =  vrai;
```

> 7. Ajoutez le `typedef` dans votre fichier, et modifiez les fonctions précédentes utilisant `enum booleen_e` afin d'utiliser l'alias `booleen`.

Si on avait souhaité utiliser le type `booleen` dans un autre fichier, on aurait du placer l'alias dans un fichier d'entête (comme dans la partie précédente).

### 3. Types structurés

On peut également définir en C des types structurés avec le mot-clef **struct**. Voici la structure pour une couleur comme définie dans la première partie :

```c
struct couleur_s { // le _s à la fin du nom est optionnel mais très fortement recommandé
    double rouge;
    double bleu;
    double jaune;
};
```

Il y a ensuite plusieurs syntaxes possibles pour définir un objet de ce type :

```c
// méthode 1 : initialisateur nommé (champs dans n'importe quel ordre)
struct couleur_s c1 = {.rouge = 29.5, .jaune = 50.5, .bleu = 20.};
// méthode 2 : initialisateur non nommé (champs dans l'ordre de définition du type)
struct couleur_s c2 = {29.5, 20., 50.5};
// méthode 3 : par mutations
struct couleur_s c3;
c3.jaune = 50.5;
c3.rouge = 29.5;
c3.bleu = 20.;
```

Attention, comme avec les tableaux, les syntaxes utilisant les accolades ne servent qu'à l'initialisation (ce ne sont pas des structures). On devine de par la troisième méthode que les champs d'une structure sont mutables.

> 8. Placez la déclaration du type structuré dans un fichier `.c`, et placez dans ce même fichier un `main` déclarant :
>     * une variable `orange` créée avec la première syntaxe
>     * une variable `bleu` créée avec la deuxième syntaxe
>     * une variable `vert` créée avec la troisième syntaxe
> 2. Modifiez le `main` pour prendre en arguments 3 flottants et créer la couleur correspondante. On vérifiera que l'utilisateur donne bien 3 arguments et qu'avec le total des flottants on arrive bien à 100.

On peut bien sûr passer des structures en paramètre d'une fonction, et en renvoyer. :

```c
struct couleur_s melange(struct couleur_s c1, struct couleur_s c2) {
    struct couleur_s mel = {.rouge = (c1.rouge + c2.rouge) / 2,
                            .bleu = (c1.bleu + c2.bleu) / 2,
                            .jaune = (c1.jaune + c2.jaune) / 2};
    return mel;
}
```

> 10. Copiez cette fonction dans votre fichier et testez là.

Pour alléger la syntaxe, on utilise généralement `typedef` également :

```c
typedef struct couleur_s couleur;
```

> 11. Placez l'alias dans votre fichier et modifiez la fonction `melange` pour l'utiliser.

Le passage en paramètre d'une structure se fait *par valeur*, ce qui signifie que la structure est copiée lorsqu'on appelle la fonction (donc les modifications faites sur cette structure dans la fonction n'ont pas d'impact sur la structure une fois l'appel terminé).

Pour rappel, l'autre manière de passer un paramètre dans une fonction est *par référence*, autrement dit on fournit un pointeur à la fonction (et dans ce cas, l'adresse est recopiée mais pas l'élément, donc on peut le modifier et cela est permanent).

> 12. À l'aide de [C Tutor](https://pythontutor.com/c.html), déroulez le code suivant :
>
>     ```c
>     struct couleur_s { double rouge; double bleu; double jaune; };
>     typedef struct couleur_s couleur;
>
>     couleur devient_marron(couleur c) {
>         c.rouge = 33.3;
>         c.jaune = 33.3;
>         c.bleu = 33.3;
>         return c;
>     }
>
>     int main() {
>         couleur origine = {29.5, 20., 50.5};
>         couleur marron = devient_marron(origine);
>     }
>     ```
>
> 6. À l'aide de [C Tutor](https://pythontutor.com/c.html), déroulez le code suivant :
>
>     ```c
>     struct couleur_s { double rouge; double bleu; double jaune; };
>     typedef struct couleur_s couleur;
>     
>     void devient_marron(couleur* c) {
>         (*c).rouge = 33.3;
>         (*c).jaune = 33.3;
>         (*c).bleu = 33.3;
>     }
>     
>     int main() {
>         couleur origine = {29.5, 20., 50.5};
>         devient_marron(&origine);
>     }
>     ```
>     
> 17. Résumez la différence entre passage par valeur et passage par référence des paramètres. Donnez les avantages et inconvénients des deux.
>

Il arrive très souvent de manipuler des pointeurs vers des structures :

* parce qu'il est inefficace de passer une structure par valeur à une fonction (ce qui implique une copie)
* parce qu'il est inefficace qu'une fonction renvoie une structure (ce qui implique aussi une copie)
* quand on souhaite qu'une fonction puisse modifier la structure passée en paramètre
* pour faire des structures récursives (on en fera dans le prochain TP)

Les parenthèses autour de `*c` sont obligatoires dans la fonction précédente. Comme ces parenthèses deviennent rapidement pénibles, on dispose d'une syntaxe spéciale :

```c
// on suppose que ps est un pointeur vers une structure, alors
ps->champ
// est équivalent à
(*ps).champ
```

> 15. Ré-écrire la fonction `void devient_marron(couleur* c)` avec cette syntaxe.

Attention à ne pas confondre les deux syntaxes : `s.champ` si `s` est une structure, `s->champ` si `s` est un pointeur vers une structure.

> 16. Complétez par la bonne syntaxe :
>
>     ```c
>     couleur violet = {.rouge = 50., .jaune = 0., .bleu = 50.};
>     couleur* vert = malloc(sizeof(couleur));
>     vert->rouge = 0.;
>     vert->jaune = 50;
>     vert->bleu = 50;
>                     
>     printf("Le vert est composé à %f%% de bleu, %f%% de jaune, %f%% de rouge.\n", /*COMPLETER ICI*/);
>     printf("Le violet est composé à %f%% de bleu, %f%% de jaune, %f%% de rouge.\n", /*COMPLETER ICI*/);
>                     
>     free(vert);
>     ```
>     
>     *Remarque : le `%%` sert à afficher un symbole `%`, ce n'est pas un formatage.*

On remarque au passage que tout comme n'importe quel autre type, on peut utiliser `sizeof` pour connaître la taille nécessaire à réserver en mémoire pour allouer dynamiquement une structure.

> 17. Ré-écrivez la fonction `melange` définie plus haut pour renvoyer et prendre en paramètres des pointeurs vers des couleurs (et non directement des couleurs).

Si on avait souhaité utiliser le type `couleur` depuis un autre fichier, on aurait du placer l'alias (le `typedef...`) dans un fichier d'entête (.h). Cependant, la déclaration de la structure (le `struct ...`) doit rester dans le fichier de code source (.c) pour que l'utilisateur ne puisse pas modifier les champs des structures.

## III. Exercices

Ce TP comportait les tous derniers éléments de syntaxe C au programme : on ne verra plus rien d'autre ! Je vous rappelle que le contenu des TP sert aussi de cours, je vous conseille donc de vous faire une fiche résumant tous les éléments que nous avons vus (tout ce qui est listé dans les fichiers "fondamentaux"...).

> **Ligne de commande**
>
> 1. Écrivez une fonction `int operation (char op, int a, int b)` qui prend en paramètres deux entiers `a` et `b` et un caractère `op` correspondant à un des opérateurs `+ - x / %` et renvoie le résultat de `a op b`.
> 2. Écrivez un programme qui prend en arguments successivement un entier, un opérateur et un autre entier et affiche le résultat de l'opération. Par exemple `./executable 7 + 2` doit afficher 9.
> 3. Reprenez les deux questions précédentes mais cette fois le programme prend en arguments deux entiers et une chaîne décrivant l'opération. Par exemple `./executable 7 2 somme` doit afficher 9. Vous pouvez utiliser la bibliothèque `string.h`.
>
> Avez-vous bien pensé à gérer les cas où les arguments fournis ne sont pas ceux attendus ?

> **Couleurs**
>
> 1. Déclarez un alias `coul` représentant une couleur comme un tableau de 3 réels correspondant au pourcentage de chaque couleur primaire (rouge, bleu, jaune).
> 2. Écrivez une fonction `void melange_couleurs(coul c1, coul c2, coul melange)` qui prend en paramètre deux couleurs et remplit la couleur `melange` en mélangeant les deux couleurs en quantité égale, c’est-à-dire en déterminant le pourcentage de chaque couleur primaire dans le mélange des deux couleurs passées en argument.
> 3. Dans le `main`, définissez deux variables `bleu` et `orange` et mélangez les avec la fonction précédente.

> **Signes**
>
> 1. Définissez un type énuméré pour représenter le signe d'un entier (positif, négatif ou nul). 
> 2. Définissez un alias `signe` vers ce type énuméré.
> 3. Écrivez une fonction `signe signe_int(int)` qui prend en paramètre un entier et renvoie son signe.
> 4. Écrivez une fonction `signe signe_produit(signe, signe)` qui renvoie le signe qu'aurait le produit de deux entiers dont le signe est donné en paramètre.

> **Pixels**
>
> 1. Définissez un type structuré pour représenter un pixel, et l'alias `pixel` correspondant.
> 2. Écrivez une fonction `bool valide_pixel(pixel)` qui vérifie que les valeurs des niveaux d'un pixel sont valides (chaque niveau doit être compris entre 0 et 255).
> 3. Écrivez une fonction `pixel pixel_noir_blanc(pixel)` qui renvoie un pixel noir (tout à 0) ou blanc (tout à 255). Un pixel devient noir si la moyenne de ses trois niveaux est strictement inférieure à 128, blanc sinon.
> 4. Écrivez une fonction similaire `void devient_pixel_noir_blanc(pixel*)` qui modifie le pixel passé en paramètre pour qu'il devienne noir ou blanc.
> 5. Laquelle de vos fonctions a un effet de bord ? Laquelle de ces deux fonctions effectue un passage du paramètre par valeur ? par référence ?

> **Dates**
>
> 1. Définissez un type énuméré pour représenter les mois.
> 2. Écrivez une fonction qui prend en paramètre un mois et renvoie le mois suivant.
> 3. Définissez un type structuré représentant une date (jour, mois, année).
> 4. Écrivez une fonction qui vérifie si une date est valide (par exemple le 29/02/2000 doit être valide, mais pas le 29/02/2001).
> 5. Définissez un type énuméré pour représenter les saisons.
> 6. Écrivez une fonction qui prend en paramètre une date et renvoie la saison.
> 7. Écrivez une fonction qui prend en paramètre une date et renvoie la date du lendemain.
> 8. Écrivez un programme qui prend en arguments une date, vérifie si elle valide et affiche la date du lendemain. Par exemple `./executable 28 fevrier 1900` doit afficher « 1 mars 1900 ». Si les arguments sont invalides ou que la date est invalide, le programme doit se terminer sur une erreur (renvoyer 1).

> **Complexes**
>
> Soit $`z \in \mathbb C`$. On rappelle que $`z`$ peut s’écrire de manière unique $`z = x + iy`$ avec $`(x, y) \in \mathbb R^2`$. x (resp. y) s’appelle la partie réelle (resp. imaginaire) de z.
>
> 1. Créez un type complexe ayant deux champs de type double.
> 2. Écrivez une fonction `void affiche_complexe(complexe z)` qui prend un complexe z = x + iy et affiche « x + y*i » à l’écran.
> 3. Écrivez une fonction `complexe addition(complexe z1, complexe z2)` qui renvoie le complexe correspondant à z1 + z2.
> 4. Écrivez une fonction `complexe mult_const(complexe z, double a)` qui renvoie le complexe correspondant à $`a \times z`$.
> 5. Déduisez-en une fonction `complexe soustraction(complexe z1, complexe z2)` qui renvoie le complexe correspondant à z1 − z2.
> 6. Écrivez une fonction `complexe produit(complexe z1, complexe z2)` qui renvoie le complexe correspondant à  $`z1 \times z2`$..
> 7. Écrivez une fonction `double module(complexe z)` qui renvoie |z|. Pour la racine carrée, vous pouvez utiliser la fonction `sqrt` de la bibliothèque `math.h` (hors programme normalement) en compilant avec `-lm`.
> 8. Écrivez une fonction `complexe conjugue(complexe z)` qui renvoie $`\bar z`$.
> 9. Écrivez une fonction similaire `conjugue_en_place` qui modifie z directement.
> 10. Déduisez-en une fonction `complexe division(complexe z1, complexe z2)` qui renvoie le complexe correspondant à $`\frac {z1} {z2}`$.

## Pour aller plus loin

> * Vous pouvez reprendre les exercices du TP OCaml sur les déclarations de type (sauf les types récursifs), et essayer de les adapter en C.
> * Si vous avez terminé, vous pouvez aller vous entraîner sur [France-IOI](http://www.france-ioi.org/algo/chapters.php). Ce site propose de nombreux cours, exercices et problèmes dans plusieurs langages de programmation. Il n'est pas bien adapté à OCaml, mais est vraiment très bien fait pour le C.


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*
