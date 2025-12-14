# Informatique - MP2I

Tout d’abord, félicitations pour votre admission en MP2I à Faidherbe !

Pour entrer en MP2I on ne vous demande pas nécessairement d’avoir déjà suivi des cours d’informatique. Ainsi, il n’y a pas vraiment de révisions à faire pour la rentrée pour le cours d’informatique.

Cependant, afin de travailler dans de bonnes conditions toute l’année il vous sera indispensable d’avoir accès à des outils de programmation personnels. Il arrive parfois qu’installer de tels outils prenne un peu plus de temps que souhaité et afin d’aborder votre rentrée sereinement avec une charge de travail immédiate dans l’ensemble des disciplines, il est nécessaire d’avoir pris le temps d’installer les outils en amont.

Vous aurez besoin de posséder :

1. un compte « framagit »
2. un terminal de type Unix
3. un environnement de développement
4. un compilateur pour le langage C
5. un compilateur pour le langage OCaml

Vous trouverez ci-dessous des explications vous permettant d'installer le nécessaire sur votre ordinateur personnel.

### 1 - Compte « framagit »

Votre compte framagit vous permettra d'accéder à des extraits du cours, et aux sujets et corrigés des TD/TP d'informatique pendant l'année. Il vous servira également pour le rendu des DM, et vous permettra de récupérer facilement depuis votre ordinateur personnel les fichiers sur lesquels vous avez travaillé au lycée.

Pour vous créer un compte, rendez-vous sur le site [framagit.org](https://framagit.org) et cliquez en haut à droite sur le bouton « S'inscrire ». Une adresse mail est nécessaire. Vous devez impérativement renseigner votre prénom et nom correctement, mais vous pouvez choisir le nom d'utilisateur que vous voulez.

Une fois votre inscription réalisée, vous recevrez un mail provenant du site pour valider votre compte. Après l'avoir validé, il faut m'envoyer le nom d'utilisateur que vous avez choisi à l'adresse suivante : [benouwt.info@gmail.com](mailto:benouwt.info@gmail.com). L'objet du mail sera « Framagit MP2I 2025 ». Merci de préciser aussi vos nom et prénom dans le corps du mail.

Attention, framagit met parfois plusieurs jours avant de confirmer une inscription, n'attendez pas la rentrée pour créer votre compte !

### 2 - Terminal de type Unix

Si votre ordinateur personnel est sous Linux ou Mac, vous possédez déjà un terminal de type Unix, vous pouvez passer à l'étape 3. Si votre ordinateur personnel est sous Windows, plusieurs options s'offrent à vous :

* Première option. Installer une machine virtuelle, par exemple [VirtualBox](https://www.virtualbox.org/wiki/Downloads). La machine virtuelle permet de « simuler » un environnement Linux. Vous devez donc télécharger un environnement Linux pour cette machine virtuelle, par exemple celui des concours est disponible sur [le site de CCINP](https://www.concours-commun-inp.fr/fr/epreuves/les-epreuves-orales.html) (Onglet "Filière MPI", rubrique "Cadre de l'épreuve d'informatique"). Si vous choisissez cette option (Virtual Box + environnement CCINP), vous pouvez passer les étapes 3/4/5 ci-dessous, car tout ce qu’il faut y est déjà installé.
* Deuxième option. Installer un dual boot, qui permet d'avoir deux systèmes d'exploitation sur un même ordinateur. Au démarrage, vous devrez à chaque fois choisir entre Windows et Linux. Vous trouverez de nombreux tutoriels sur Internet pour vous guider, en voici par exemple un : [www.ionos.fr/digitalguide/serveur/configuration/dual-boot-ubuntu-windows-10/](https://www.ionos.fr/digitalguide/serveur/configuration/dual-boot-ubuntu-windows-10/).
* Troisième option. Installer le WSL, qui donne accès à un sous-système Linux tout en restant sous Windows. Vous trouverez toutes les explications pour l’installation sur [le site de Microsoft](https://learn.microsoft.com/fr-fr/windows/wsl/install).

Sur les ordinateurs du lycée, nous utilisons la première option (machine virtuelle équipée de l'environnement des concours).

### 3 - Environnement de développement

Pour pouvoir programmer, il est impératif de disposer d'un IDE (environnement de développement intégré). Celui que nous utilisons au lycée est [Visual Studio Code](https://code.visualstudio.com/download), disponible sous Windows, Linux, et Mac. Si vous posséder déjà un IDE différent et que vous préférez continuer à l'utiliser, cela ne pose aucun problème.

### 4 - Compilateur pour le langage C

Un des deux langages de programmation au programme de MP2I et MPI est le langage C. Pour programmer en C, nous avons besoin d'un compilateur, le plus connu est `gcc`.

* Si vous êtes sous Mac, il faut installer Xcode (depuis l'app store).

* Si vous êtes sous Linux, ou sous Windows avec le WSL, ouvrez le terminal, et entrez successivement les deux commandes suivantes (vous devrez saisir votre mot de passe, c'est normal s'il ne s'affiche pas pendant que vous tapez) :

    ```bash
    sudo apt update
    sudo apt install build-essential
    ```

Pour vérifier si votre installation est fonctionnelle :

* Ouvrez le terminal, entrez la commande suivante :

    ```bash
    touch test.c
    ```

* Vous venez de créer un fichier appelé "test.c" dans votre répertoire personnel. Ouvrez ce fichier avec l'environnement de développement installé à l'étape précédente.

* Copiez le code suivant dans le fichier et sauvegardez :

    ```c
    #include <stdio.h>
    
    int main() {
        printf("Tout fonctionne.\n");
        return 0;
    }
    ```

* Retournez dans le terminal, et entrez successivement les deux commandes suivantes :

    ```bash
    gcc -o test test.c
    ./test
    ```

    La première commande ne doit rien afficher, mais un nouveau fichier est créé. La seconde commande doit afficher "Tout fonctionne." dans le terminal.

### 5 - Compilateur pour le langage OCaml

L'autre langage de programmation au programme de MP2I et MPI est le langage OCaml. Allez suivre les directives directement sur [le site officiel](https://ocaml.org/docs/installing-ocaml) pour installer OCaml.

Pour vérifier si votre installation est fonctionnelle :

* Ouvrez le terminal, entrez la commande suivante :

    ```bash
    touch test.ml
    ```

* Vous venez de créer un fichier appelé "test.ml" dans votre répertoire personnel. Ouvrez ce fichier avec l'environnement de développement installé à l'étape 3.

* Copiez le code suivant dans le fichier et sauvegardez :

    ```c
    let _ = print_endline "Tout fonctionne."
    ```

* Retournez dans le terminal, et entrez successivement les deux commandes suivantes :

    ```bash
    ocamlc -o test test.ml
    ./test
    ```

    La première commande ne doit rien afficher, mais des nouveaux fichiers sont créés. La seconde commande doit afficher "Tout fonctionne." dans le terminal.


---

Par *J. BENOUWT*, Lycée *Faidherbe*, Filière *MP2I-MPI*.
