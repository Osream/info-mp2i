# Introduction à `git`

Git est un logiciel développé par Linus Torvalds (le fondateur de Linux) en 2005. Il est facilement installable sur n'importe quel système d'exploitation.

Git permet de créer des **dépôts** contenant des fichiers de tous types. Ils sont hébergés en ligne, et peuvent être téléchargés en local sur n'importe quel ordinateur : on dit **cloner** un dépôt.

Utiliser `git` vous permettra de créer un dépôt contenant vos TP et de les récupérer facilement depuis votre ordinateur personnel ou ceux du lycée.

Même si vous travaillez toujours sur votre propre PC, c'est une très bonne idée d'apprendre à se servir de `git`. C'est un outil utilisé par quasiment tous les informaticiens, et il vous servira très certainement tout au long de vos études et de votre future carrière.

## I. Créer un dépôt

> 1. Ouvrez un navigateur et connectez-vous sur votre compte Framagit.
> 3. En haut à gauche, vous trouverez votre "Tableau de bord" (en cliquant sur l'icône de framagit). C'est ici que vous pouvez consulter la liste de vos dépôts.
> 4. Cliquez sur "Nouveau projet" pour créer un nouveau dépôt, puis "Créer un projet vide". Nous allons créer ce dépôt pour stocker vos TP, donc donnez lui un nom approprié (par exemple "TP info MP2I"). Vous pouvez choisir la visibilité de votre dépôt. Si vous mettez "privé", vous seul y aurez accès (ce qui est sans doute mieux ici). Si vous mettez "public", le dépôt sera accessible par tout le monde (mon dépôt `mp2i` sur lequel vous lisez cet énoncé est public par exemple). Laissez bien "Initialiser avec un README" coché en dessous. Cliquez finalement sur "Créer le projet".
> 6. Vous arrivez sur la page principale de votre nouveau projet. Sur la gauche vous trouverez énormément de paramètres. Voici ceux qui pourraient vous servir :
>     * Informations du projet > Membres : il est possible de donner accès à votre dépôt à d'autres utilisateurs. Cela peut être pratique si vous souhaitez travailler avec un de vos camarades par exemple.
>     * Dépôt > Commits : un "commit" est une modification du dépôt. Vous pouvez donc voir ici l'historique des modifications (pour l'instant, vous ne devez avoir qu'un seul commit).
>     * Paramètres > Général : vous permet de modifier votre dépôt (nom, avatar, description, visibilité...).
> 7. Si vous retournez sur votre tableau de bord, vous devez maintenant voir votre projet apparaître. Cliquez dessus. Allez dans l'onglet Code > Dépôt.

## 2. Cloner un dépôt

> 1. Cliquez sur le bouton "Code" (en bleu en haut à droite) puis copiez le lien HTTPS.
> 2. Ouvrez un terminal, et déplacez-vous à l'endroit où vous souhaitez cloner votre dépôt. Entrez la commande `git clone <depot>` en remplaçant `<depot>` par l'adresse copiée à la question précédente. On vous demandera de saisir ensuite votre nom d'utilisateur et mot de passe Framagit (c'est normal s'il ne s'affiche pas quand vous tapez).
> 5. Votre dépôt est cloné ! Vous pouvez vérifier avec `ls`. Déplacez vous dans votre dépôt. Vous devez y trouver le fichier "README" créé par défaut.

Une fois qu'un dépôt est cloné, vous n'aurez plus besoin de la commande `git clone`. Il est possible de cloner un dépôt autant de fois que souhaité sur n'importe quel ordinateur. Vous récupérez alors une sorte de "copie" des fichiers stockés sur votre compte en ligne.

## 3. Modifier un dépôt

Il y a 2 façons de modifier un dépôt :

* soit directement en ligne
* soit en synchronisant votre dépôt en ligne avec le clone sur votre ordinateur

> 1. Depuis l'interface en ligne, cliquez sur le fichier "README", puis cliquez sur "Modifier" (bouton bleu).
> 2. Supprimez tout le contenu du fichier sauf la première ligne (celle qui indique le nom de votre dépôt). Ajoutez un petit texte explicatif de ce que contient le dépôt (ex : "Ce dépôt contient les TP d'informatique de Prénom NOM de l'année .... en MP2I - lycée Faidherbe.").
> 3. Le champ "Message de commit" en dessous permet de mettre un petit message expliquant la modification effectuée. Il est très utile pour s'y retrouver dans l'historique des modifications. Mettez ce que vous voulez, et validez.
> 4. Allez voir l'historique des modifications (dans Code > Validations sur la gauche). Retrouvez-vous bien ce que vous venez de changer ?
> 5. Retournez dans le terminal. Le fichier README a été modifié en ligne mais pas dans votre clone local : il faut synchroniser les 2. Entrez la commande `git pull`. Entrez votre nom utilisateur et mot de passe. Vous devez avoir un message comme quoi les modifications du fichier README ont bien été téléchargées.

Dès que vous commencerez à travailler sur un dépôt (à chaque début de TP ou chez vous), `git pull` sera la première commande à exécuter. Elle vous permet de récupérer toutes les modifications effectuées en ligne.

> 6. La commande `git status` permet de voir les modifications en cours. Entrez la (normalement vous devez avoir un message indiquant que tout est à jour).
> 7. Ajoutez dans votre dépôt les fichiers créés lors du TP d'aujourd'hui.
> 8. Recommencez `git status`. La liste des fichiers que vous venez d'ajouter doit apparaître en rouge.

Il y a trois étapes permettant de synchroniser les modifications en cours avec le dépôt en ligne.

> 9. Tout d'abord, il faut ajouter les fichiers à synchroniser avec `git add`. Testez `git add <fichier>` en remplaçant `<fichier>` par le nom d'un de vos fichiers à ajouter.
> 2. Vérifiez avec `git status` que ce fichier apparaît maintenant en vert. Les autres doivent toujours être en rouge.
> 3. Il faut ensuite préciser le message de modification (qui apparaît dans l'historique des commits). Entrez la commande `git commit -m "......"` en plaçant votre message de commit entre les guillemets.
> 4. Vérifiez avec `git status` que vous avez bien 1 commit en attente.
> 5. Ce n'est pas très pratique de tout ajouter un par un, donc voici une astuce : `git add -A`. Testez, et vérifiez avec `git status` que tous vos fichiers sont en vert. L'option `-A` permet d'ajouter tous les fichiers modifiés d'un seul coup.
> 6. Faîtes un commit avec le message approprié.
> 7. Vérifiez avec `git status`. Vous ne devez plus avoir aucun fichier ni en rouge ni en vert, mais avoir 2 commits en attente.
> 8. Pour finir, il faut envoyer les modifications vers le dépôt en ligne : `git push`. Testez, entrez votre nom utilisateur et mot de passe.
> 9. `git status` doit maintenant indiquer que tout est à jour. Vous pouvez aussi aller vérifier en ligne sur Framagit que tous vos fichiers sont bien apparus.

Il vous faudra donc, à chaque fin de TP (ou quand vous travaillez chez vous) : `git add -A` pour ajouter les fichiers modifiés, `git commit -m "..."` pour préciser le message de modification, et `git push` pour les mettre en ligne.

Si vous avez travaillé sur plusieurs choses (par exemple sur 2 TP différents), il peut être pertinent d'ajouter les fichiers séparément (avec des commits séparés) mais ce n'est pas obligatoire, cela sert juste à rendre l'historique des modifications plus clair. Le `git push` est essentiel (sinon vous ne retrouverez pas vos modifications en ligne).

## 4. Résumé

Il est possible de manipuler vos dépôts directement depuis l'interface en ligne : on peut facilement déposer, supprimer ou modifier un fichier directement depuis le site Framagit. Si vous n'êtes pas à l'aise avec les commandes, vous pouvez faire ça au début. C'est par contre beaucoup plus long que d'utiliser les commandes, surtout si vous manipulez de nombreux fichiers (comme c'est le cas en C). Je vous conseille donc à terme de vous entraîner à n'utiliser que les commandes `git`. Voici un résumé de ce dont vous aurez besoin (*pas besoin de les apprendre*, mais vous verrez qu'à force d'utilisation vous les retiendrez) :

* `git clone` : cloner un dépôt en ligne sur son ordinateur (seulement si c'est un nouveau dépôt)
* `git pull` : synchroniser les modifications en ligne vers son ordinateur (au début du TP)
* `git add ...` : ajouter les fichiers à modifier (`-A` pour tous les fichiers)
* `git commit -m "..."` : valider un changement (entre guillemets le message de modification qui apparaîtra dans l'historique)
* `git push` : synchroniser les modifications du clone vers le dépôt en ligne (à la fin du TP)
* `git status` : voir les modifications en cours

> **Utilisations supplémentaires**
>
> * Au final, `git` n'est qu'un outil (très sophistiqué) de sauvegarde de données. Vous pouvez vous en servir pour stocker vos TP, vos cours, votre TIPE au deuxième semestre... même vos fichiers personnels. Vous êtes ainsi sûrs de ne rien perdre, et avez accès à tous vos fichiers depuis n'importe quel appareil connecté (même votre smartphone). Il est indispensable à tout informaticien, et est de plus en plus utilisé dans d'autres domaines scientifiques et en entreprise. Vous finirez par ne plus pouvoir vous en passer !
>
> * `git` est un outil collaboratif. Plusieurs personnes peuvent modifier le même dépôt en même temps (et même le même fichier dans un dépôt, `git` s'occupe des synchronisations pour vous). N'hésitez pas à vous en servir si vous avez un projet à faire avec d'autres camarades. Vous pouvez également donner un accès "Invité" à d'autres personnes afin qu'elles puissent lire vos fichiers mais pas y toucher : cela peut vous permettre de vous entraider lorsque vous devez terminer les TP à la maison. Si vous êtes bloqué dans un TP, vous pouvez également me donner un accès temporaire à votre dépôt (utilisateur `@JB_info`) et m'envoyer un message pour que j'aille regarder.
>
> * Si vous êtes sur votre ordinateur personnel, devoir entrer son nom d'utilisateur et mot de passe à chaque fois peut être un peu casse-pied. Pour ne pas devoir le faire, il faut cloner ses dépôts avec SSH et non HTTPS. Vous trouverez de nombreux tutoriels en ligne si ça vous intéresse. Sur framagit, il faut aller dans les réglages de votre compte pour utiliser une clef SSH.
>
> * Il y a un certain nombre de fichiers que vous ne voulez pas inclure dans vos dépôt. Par exemple en C, on n'a besoin que des fichiers de code source .c. Les fichiers objets ou exécutables peuvent être recompilés et il est inutile de les sauvegarder, ils prendraient de la place inutilement dans votre dépôt. Pour indiquer à `git` que vous voulez ignorer un fichier, il faut créer un fichier `.gitignore` (exactement ce nom). Vous pouvez alors mettre la liste des fichiers à ignorer (un par ligne). Par exemple pour votre dépôt de TP, un `.gitignore` contenant les lignes suivantes peut être pertinent :
>
>     ```
>     *.o
>     *.cmi
>     *.cmo
>     *.cma
>     *.cmx
>     *.cmxs
>     *.cmxa
>     *.exe
>     a.out
>     ```
>
> * `git` permet de faire énormément de choses, mais inutile de chercher à tout savoir maintenant : vous découvrirez de nouvelles fonctionnalités au fur et à mesure de vos besoins.
>

![](https://imgs.xkcd.com/comics/git.png)




---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : [xkcd](https://xkcd.com/)
