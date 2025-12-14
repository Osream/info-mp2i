# TD : Système de fichiers

## Exercice 1 : droits et permissions

1. Complétez le tableau suivant :

    |     Texte     | Décimal |
    | :-----------: | :-----: |
    | `r-x r-- r--` |   544   |
    |               |   777   |
    | `rwx -w- --x` |         |
    |               |   602   |
    | `--x -wx rw-` |         |

2. Pour chaque situation du tableau précédent, expliquez ce que peuvent faire l'utilisateur, son groupe et les autres.

3. On suppose qu'il existe dans le répertoire personnel un répertoire `info`, et deux fichiers `info/1.txt` et `info/2.txt`.  Donnez, pour chaque situation, 2 commandes visant à mettre les permissions demandées :

    * Le répertoire `info` possède tous les droits pour l'utilisateur et les droits d'exécution et de lecture pour le groupe et les autres.
    * Le fichier `info/1.txt` possède les droits de lecture et écriture pour l'utilisateur et uniquement les droits de lecture pour le groupe et les autres.
    * Le fichier `info/2.txt` possède les droits d'écriture pour l'utilisateur et aucun droit pour le groupe et les autres.
    * Le répertoire personnel possède tous les droits pour l'utilisateur et uniquement le droit d'exécution pour le groupe et les autres.

## Exercice 2 : liens

L'utilisateur `dean` exécute la commande `ls -l -i -h`. Il obtient ceci :

```bash
total 100M
1573301 -rw-r--r-- 3 dean mp2i 25M sept. 11 18:46 fic1.pdf
1573301 -rw-r--r-- 3 dean mp2i 25M sept. 11 18:46 fic2.pdf
1573301 -rw-r--r-- 3 dean mp2i 25M sept. 11 18:46 fic3.pdf
1573422 -rw-r--r-- 1 dean mp2i 25M sept. 11 18:46 fic4.pdf -> fic1.pdf
```

1. Repérez les liens physiques et les liens symboliques.
2. Que signifie le `3` sur la troisième colonne des trois premières lignes ? Et pour le `1` de la quatrième ligne ?
3. Donnez une suite de commande permettant de créer ce contenu.
4. L'option `-h` indique à  `ls` d'afficher les tailles de fichiers de façon lisible (donc avec la plus grande unité possible, ici `M` pour méga-octet). La commande affiche `total 100M`. Est-il vrai que les quatre fichiers occupent 100 méga-octets sur le disque ?
5. Que se passerait-il pour les trois autres fichiers si on supprimait `fic1.pdf` ?

## Exercice 3 : commandes de base et arborescence

1. On considère la suite de commandes suivantes, rentrées les unes après les autres dans le terminal. Décrire l'effet de chaque commande.

    ```bash
    $ cd ~
    $ mkdir info
    $ mkdir info/td2
    $ cd info/td2
    $ cd ..
    $ ls
    $ chmod 700 td2
    $ ln -s ../info ../mp2i
    $ touch td2/exo3.txt
    $ mkdir ../info/reponses
    $ cp td2/exo3.txt reponses/exo3_rep.txt
    $ mv td2/exo3.txt td2/exo3_enonce.txt
    ```

2. On suppose que l'on se trouve dans un répertoire `test` vide. On considère la suite de commandes suivantes, rentrées les unes après les autres dans le terminal. Dessinez l'arborescence finale des fichiers et répertoires (en utilisant `test` comme racine). Pour information, la commande `echo` permet d'écrire quelque chose.

    ```bash
    $ mkdir a b c d
    $ echo "hello" > a/t.txt
    $ cp a/t.txt d/foo.txt
    $ cd c
    $ mkdir ../b/f e g
    $ cd ..
    $ cp */*.txt c/[a-f]
    $ rm d/foo.txt
    $ rmdir d
    ```

## Exercice 4 : redirections

On considère la suite de commandes suivantes, rentrées les unes après les autres dans le terminal. Décrire l'effet de chaque commande. La commande `grep` permet de rechercher une chaîne de caractères et la commande `wc -l` permet d'afficher le nombre de lignes.

```bash
$ mkdir test
$ cd test
$ touch vide.txt
$ echo 'bonjour' > vide.txt
$ echo 'à tous' > vide.txt
$ echo 'ici présents' >> vide.txt
$ ls -l vide.txt existe_pas.txt
$ ls -l vide.txt existe_pas.txt 2> erreur.txt
$ ls -l vide.txt existe_pas.txt > contenu.log 2> erreur.txt
$ ls -l existe_pas_non_plus.txt 2>> erreur.txt
$ cat erreur.txt | wc -l
$ ls -l | grep .txt | wc -l
$ ls -l | grep .txt | wc -l > nb_txt.txt
```

## Exercice 5 : motifs

Pour chacun des motifs ci-dessous, donnez deux suites de caractères de longueur au moins 1 reconnues par le motif.

1. `*txt`
2. `image.[pj][np]g`
3. `+(x).gif`
4. `fic[0-9].pdf`
5. `fic+([0-9]).pdf`
6. `+([a-z])+([0-9]).html`
7. `prog?.c`
8. `[a-zA-Z][-_]*.ml`
9. `????`
10. `?*?`

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
