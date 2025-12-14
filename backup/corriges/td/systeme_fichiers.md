# TD : système de fichiers

## Exercice 1

1. 2. |     Texte     | Décimal |                        Signification                         |
       | :-----------: | :-----: | :----------------------------------------------------------: |
       | `r-x r-- r--` |   544   | Tout le monde a le droit de lecture, personne n'a le droit d'écriture, seul l'utilisateur a le droit d'exécution. |
       | `rwx rwx rwx` |   777   |               Tout le monde a tous les droits.               |
       | `rwx -w- --x` |   721   | L'utilisateur a tous les droits, son groupe a uniquement le droit d'écriture, les autres ont uniquement le droit d'exécution. |
       | `rw- --- -w-` |   602   | L'utilisateur a les droits de lecture et d'écriture, son groupe n'a aucun droit, les autres ont uniquement le droit d'écriture. |
       | `--x -wx rw-` |   136   | L'utilisateur a uniquement le droit d'exécution, son groupe a les droits d'écriture et d'exécution, les autres ont les droits de lecture et d'écriture. |
   
3. * `chmod 755 ~/info` et `chmod u+rwx,go+rx,go-w ~/info`
    * `chmod 644 ~/info/1.txt` et `chmod u+rw,go+r,ugo-x,go-w ~/info/1.txt`
    * `chmod 200 ~/info/2.txt` et `chmod u+w,go-w,ugo-rx ~/info/2.txt`
    * `chmod 711 ~` et `chmod u+rwx,go+x,go-rw ~`

## Exercice 2

1. `fic1.pdf, fic2.pdf, fic3.pdf` ont le même numéro d'inode : ce sont des liens physiques. `fic4.pdf` est un lien symbolique vers le fichier `fic1.txt`.

2. Il s'agit du compteur de lien physique.

3. ```bash
    $ touch fic1.pdf
    $ ln fic1.pdf fic2.pdf
    $ ln fic2.pdf fic3.pdf
    $ ln -s fic1.pdf fic4.pdf
    ```

4. `fic1.pdf, fic2.pdf, fic3.pdf` n'occupent pas 3 fois 25M en mémoire puisqu'il s'agit du même inode : les 3 comptent uniquement pour 25M.

5. `fic2.pdf` et `fic3.pdf` ne seraient pas impactés (seul leur compteur de liens physiques passerait à 2) mais `fic4.pdf` ne serait plus lié à rien (impossible de s'en servir donc).

## Exercices 3 et 4

Pour vérifier vos réponses, vous pouvez entrer ces commandes dans un terminal et observer directement le résultat.

## Exercice 5

```
1. txt, f.txt
2. image.png, image.ppg
3. x.gif, xxx.gif
4. fic0.pdf, fic7.pdf
5. fic0.pdf, fic77777.pdf
6. a0.html, abc7.html
7. proga.c, prog9.c
8. a-1.ml, B_.ml
9. a.ml, wxyz
10. aa, wxyz
```



---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
