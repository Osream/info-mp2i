# TP : Maîtrise du terminal

Les ordinateurs du lycée Faidherbe sont équipés du système d'exploitation Windows. En TP, nous utiliserons donc une machine virtuelle équipée d'un environnement GNU/Linux.

> 0. Ouvrez la machine virtuelle (icône Virtual Box sur le bureau) puis lancez l'environnement appelé CCINP.
>
>     *Remarque : il faudra faire cela à chaque TP.*

## I. Premières petites commandes

À l'origine, les ordinateurs étaient des colosses qui remplissaient facilement une pièce de bonnes dimensions. On les manipulait depuis un « terminal » qui leur était relié, ce dernier se composant juste d’un écran et d’un clavier. Le terme est resté pour désigner la fenêtre dans laquelle on entre une série de commandes pour effectuer des tâches d’administration sur l’ordinateur. On parle aussi de « console » (*shell*) ou d’interface en « ligne de commande ».

Le terminal présente deux avantages sur l’interface graphique :

- Tout d’abord, il permet de travailler plus vite, car une seule commande complétée par quelques paramètres remplace avantageusement une multitude de clics sur des icônes ou des menus déroulants.

- Ensuite, le terminal détaille le déroulement des actions, ce qui permet de retrouver plus facilement la source d’une erreur. Au contraire, le mode graphique n’affiche qu’une boîte de dialogue souvent peu claire.

Pour ouvrir un terminal, vous avez deux possibilités :  

* cliquer sur l’icône dans le menu des applications ;

* utiliser le raccourci `CTRL + ALT + T`.

Une fenêtre doit s’ouvrir dans laquelle vous pouvez lire :

```bash
<nom-utilisateur>@<nom-machine>:~$ 
```

> 1. * Quel est votre nom d'utilisateur ? Le nom de votre machine ?
>     * Entrez la commande `whoami`. À quoi sert-elle ? Entrez la commande `hostname`. À quoi sert-elle ?
>     * Vérifiez vos réponses avec la commande `man` (donne la documentation d'une commande). On quitte le manuel en appuyant sur la touche "q" (quit).
> 2. À l'aide de la commande `lscpu`, donnez la marque et le modèle de votre processeur.
> 3. À l'aide de la commande `top`, trouvez quelle est la taille de la mémoire vive (RAM) et combien de RAM est utilisée en ce moment. La commande `top` permet de visualiser l'état des processus (= programmes en cours d'exécution).
> 4. * Tapez `gedit` et entrez (gedit est un éditeur de texte). Sans fermer gedit, retournez dans le terminal. Que se passe-t-il ?
>     * Interrompre un programme peut se faire avec `CTRL + C`. Testez.
>     * Entrez maintenant `gedit &`. Que remarquez-vous ?
>     * Une autre commande permettant de visualiser les processus est `ps`. Entrez la et donnez le PID de gedit.
>     * La commande `kill` permet de tuer des processus. Entrez la commande `kill <PID>` en remplaçant `<PID>` par celui trouvé pour gedit. Que se passe-t-il ?
> 5. Le système de fichiers est en réalité composé de plusieurs sous-systèmes de fichiers assemblés. Certains sous-systèmes de fichiers peuvent se trouver sur le disque dur de la machine, d’autres sur un serveur et d’autres peuvent être amovibles (par exemple votre clé USB). Ces sous-systèmes, qui suivent eux-mêmes une structure arborescente sont rattachés à l’arborescence générale, donnant ainsi l’illusion d’une unique arborescence. La commande `mount` permet de visualiser les systèmes de fichiers qui sont montés à un instant donné. Exécutez la commande `mount`.
>

## II. Arborescence de fichiers

Le symbole `~` indique que vous vous trouvez dans votre répertoire personnel, c'est le répertoire par défaut lorsque vous ouvrez un terminal. La racine est le répertoire qui contient tout, elle s'appelle `/`.

> 1. Vérifiez cela avec la commande `pwd`. Qu'obtenez-vous ?
> 2. Listez le contenu de votre répertoire personnel avec `ls`. Combien d'éléments trouvez vous ?
> 3. `ls` peut être suivie d'un nom de répertoire. Testez `ls /home/<nom_utilisateur>` en remplaçant <nom_utilisateur> par le votre. Que retrouvez-vous ?
> 4. Même question avec `ls ~`.
> 5. Le répertoire courant est désigné par un `.`. Essayez `ls .`.
> 6. Le répertoire parent est désigné par `..`. Essayez `ls ..`. Que voyez-vous ?
> 7. L'option `-l` permet d'obtenir plus d'informations. Essayez `ls -l`.
> 8. L'option `-i`permet de récupérer le numéro d'inode. Testez `ls -i`.
> 9. Testez `ls /`. Retrouvez-vous les répertoires cités en cours ?

Un chemin est une suite de répertoires adjacents dans l'arborescence, que l'on sépare par le caractère "/". Un élément peut être décrit par :

* un chemin absolu, qui part de la racine : `/home/<nom_utilisateur>/Documents/exemple.txt>`

* un chemin relatif, qui part du répertoire courant : `./Documents/exemple.txt`ou encore `Documents/exemple.txt`.

> 10. Que pensez-vous de `../<nom_utilisateur>/Documents/../../<nom_utilisateur>`?
> 11. Proposez cinq chemins différents qui mèneraient à un fichier `exemple.txt` se trouvant dans le répertoire `Documents`.

La commande `cd`(change directory)  permet de changer de répertoire. Elle est suivie d'un chemin absolu ou relatif.

> 12. Testez `cd /`. Vérifiez où vous êtes avec `pwd`.
> 14. Testez `cd ~`. Où êtes-vous ?
> 15. Retournez dans le répertoire racine en utilisant cette fois un chemin relatif.
> 16. Déplacez vous dans le répertoire `Documents` en utilisant un chemin absolu.

*ASTUCE : La flèche du haut permet de retrouver la commande tapée précédemment. La touche tabulation permet de compléter automatiquement le nom d'un fichier. Pensez-y, vous gagnerez du temps !*

La commande `mkdir`(*make directory*) permet de créer un répertoire. La commande `touch` permet de créer un fichier.

> 16. Entrez `mkdir info`. Vérifiez avec `ls` que le répertoire a bien été créé.
> 18. Entrez `mkdir info/tp1`. Qu'a fait cette commande ?
> 19. Déplacez vous dans le répertoire `tp1`, et créez-y deux répertoires `rep1` et `rep2`.
> 20. Entrez `touch rep1/vide.txt`. Qu'a fait cette commande ?
> 21. Créez trois fichiers `test1.txt`, `test2.txt` et `testX.txt` dans le répertoire `rep1`.
> 23. Entrez `ls rep1/test?.txt`. Que fait cette commande ? Comparez avec `ls rep1/test[0-9].txt`.

La commande `rmdir`(*remove directory*) permet de supprimer un répertoire vide. La commande `rm` permet de supprimer un fichier. *Attention : La suppression via le terminal est irréversible !*

> 22. Testez `rmdir rep2`. Vérifiez avec `ls`.
> 23. Essayez de supprimer `rep1`. Que se passe-t-il ?
> 24. Essayez `rm rep1/test2.txt`. Vérifiez.
> 25. Testez `rm rep1/*`. Que fait cette commande ?
> 41. Supprimez `rep1`.

La commande `mv <chemin-depart> <chemin-arrivée>` (*move*) permet de déplacer le fichier ou répertoire indiqué par le chemin de départ à l’emplacement décrit par le chemin d’arrivée. Cette commande permet aussi de renommer un fichier ou un répertoire, il suffit de le déplacer au même endroit mais sous un nouveau nom.

> 27. Créez un répertoire `rep1`. Testez `mv rep1 rep2`. Vérifiez avec `ls`.
> 28. Créez un fichier `vide.txt` dans un nouveau répertoire `rep1`. Testez `mv rep1/vide.txt rep2`. Vérifiez avec `ls`.

La commande `cp <chemin-depart> <chemin-arrivée` (*copy*)  permet de copier le fichier indiqué par le chemin de départ à l’emplacement décrit par le chemin d’arrivée. Pour copier un répertoire (et son contenu), on utilise `cp` avec l’option `-r`.

> 29. Testez `cp rep2/vide.txt rep1/`. Vérifiez avec `ls`.
> 30. Testez `cp -r rep1 rep3`. Vérifiez avec `ls`.
> 31. Testez `cp rep1/vide.txt rep1/vide2.txt`. Vérifiez.
> 

L'option `-l` de `ls` permet d'afficher les droits des répertoires et fichiers.

Après le premier caractère qui identifie le type du fichier ("d" pour répertoire, "-" pour fichier), se trouvent trois blocs de trois caractères "rwx", certains étant remplacés par "-", avec r pour *read* (droits en lecture), w pour *write* (droits en écriture) et x pour *execute* (droits en exécution). Ce sont les droits d’utilisation du fichier. Le premier bloc concerne le propriétaire du fichier (u), le deuxième le groupe auquel il appartient (g), et le troisième concerne tous les autres utilisateurs (o).

La commande `chmod` permet de gérer les droits. Voici deux exemples d'utilisation :

* `chmod ug+r,o-wx fichier`

* `chmod 734 fichier`

> 32. Créez un répertoire `droits` contenant un fichier `f.txt`. Donnez ses droits.
> 33. Donnez deux manières d'obtenir les droits suivants : `rwxr-x--x`. Testez.

## III. Liens physiques et symboliques

Les fichiers sont identifiés de manière unique par un numéro appelé nœud d’index (*inode*).

> 1. Créez un répertoire `liens` et déplacez vous dedans.
>
> 2. Créez un fichier `test.txt`. Donnez son numéro d'inode.
>
> 3. Exécutez `ln test.txt test_ln.txt`. Donnez son numéro d'inode. Que remarquez-vous ?
>
> 4. Avec `gedit test_ln.txt`, ajoutez du contenu dans le fichier et enregistrez (`CTRL + S`).
>
> 5. La commande `cat` permet d'afficher le contenu d'un fichier. Avec `cat test_ln.txt`, vérifiez que vous retrouvez votre contenu ajouté. Vérifiez ensuite le contenu de `test.txt`. Que remarquez-vous ?
>
> 6. Le chiffre qui suit les droits lorsqu'on utilise la commande `ls -l` est le nombre de liens physiques d'un fichier. Quel est ce chiffre pour `test.txt`? Et pour `test_ln.txt` ?
>
> 7. Supprimez le fichier `test_ln.txt` (avec `rm`). Quel est le nombre de liens physiques de `test.txt` désormais ?
>
> 8. Combien y a-t-il de liens physiques vers le répertoire `liens` ? Expliquez pourquoi il y a toujours au moins deux liens vers un répertoire.

On ne peut pas, en général, créer de liens physiques pour les répertoires, ceci pourrait causer des problèmes de cycles, mais on dispose d’un autre outil : les liens symboliques. Les liens symboliques sont simplement des noms de chemins qui redirigent vers le fichier ou répertoire ainsi pointé, des « raccourcis ». On peut créer un lien symbolique avec l’option -s (*symbolic*).

> 9. Listez le contenu de la racine. Comment repérer les liens symboliques ?
> 10. Dans le répertoire `liens`, créez un répertoire `symb` contenant un répertoire `s` contenant lui-même un fichier `s.txt`. Entrez ensuite `ln -s symb/s sraccourci`. Vérifiez avec `ls -l`.
> 11. Déplacez vous dans le répertoire créé avec `cd sraccourci`. Listez son contenu avec `ls`. Que remarquez-vous ?
> 12. Supprimez le lien symbolique (avec `rm`).
> 13. Créez un lien symbolique vers le fichier `test.txt`. Affichez le contenu du lien créé avec `cat`. Que retrouvez-vous ?
> 14. Comparez les numéros d'inode du fichier et du lien.
> 15. Supprimez le fichier `test.txt`. Essayez d'afficher le contenu du lien avec `cat`. Que se passe-t-il ?
> 23. Vérifiez avec `ls -l`, puis supprimez le lien rompu.

## IV. Redirections

Il est possible de rediriger l'entrée, la sortie, et la sortie d'erreur d'un programme avec `<`, `>`, et `2>`. Il est également possible d'enchaîner des programmes via des tubes (*pipes*) avec `|`.

> 1. Créez deux fichiers `a.txt` et `b.txt`.
> 
> 2. Testez `ls -l > a.txt`. Vérifiez avec `cat` le contenu de `a.txt`.
> 
> 3. `echo` permet d'écrire un texte. Essayez `echo "bonjour tout le monde" > b.txt`. Vérifiez.
> 
> 4. `wc -w` permet de compter les mots d'un texte. Testez `wc -w < b.txt`.
> 
> 5. Testez `echo "comment allez vous ?" >> b.txt`. Vérifiez avec `cat` et compter les mots avec `wc`.
> 
> 6. Sans passer par un fichier, on peut enchaîner les programmes avec des tubes. Testez `echo "bonjour tout le monde" | wc -w`.
> 
> 7. `grep <motif>` permet de faire une recherche de motif dans un texte. Testez `grep "tout" < b.txt`.
> 
> 8. L'option `-l` de `wc` permet de compter les lignes. Testez `cat b.txt | grep "tout" | wc -l`. Expliquez.
> 
> 9. Testez `ls -l a.txt c.txt`. Expliquez.
> 
> 10. Testez `ls -l a.txt c.txt 2> b.txt`. Vérifiez le contenu de `b.txt`. Expliquez.

## V. Introduction à `git`

Cette dernière partie du TP sert à sauvegarder et rendre votre travail.

> 1. Allez faire l'[introduction à git](./git.md).

## Pour aller plus loin

> 1. Recréez intelligemment l'arborescence suivante :
>
>     ![](img/arborescence.png)
>
> 2. * Exécutez la commande `mount`, puis insérez une clé USB, et observez avec `mount` les modifications.
>     * Le montage de la clé USB se fait sur les machines actuelles automatiquement. Le démontage par contre se fait avec `umount`. Testez `umount /media/<nom_utilisateur>/<nom_cle_usb>` : cela revient à « éjecter la clé USB » via l'interface graphique.
>
> 3. Si vous avez terminé, voici un lien vers un petit jeu de rôle qui utilise des commandes simples : [Terminus](https://luffah.xyz/bidules/Terminus/).

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*

Inspirations : N. Pecheux
