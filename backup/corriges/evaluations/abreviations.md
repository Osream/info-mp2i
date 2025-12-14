# Lexique des abréviations

Vous trouverez ici la liste des abréviations que vous pouvez trouver dans vos copies.

* **ASP** : À SimPlifier. Votre code est trop lourd, utilise des variables intermédiaires inutiles, fait des distinctions de cas redondantes, des boucles non nécessaires, ... Ça peut aller du simple « `if ... = true` » redondant au code complètement tiré par les cheveux.
* **CAD** : c'est-à-dire. Un terme est trop vague ou une explication est incomplète.
* **CM / CI** : Commentaire Manquant / Commentaire Inutile. Quand une ligne de code méritait d'avoir un commentaire pour l'expliquer, ou quand vous écrivez des commentaires inutiles qui ne font que paraphraser le code.
* **CPI** : Cas Particulier Inutile. Pas toujours sanctionné, mais témoigne d'une méthode de conception bancale.
* **DC** : Défaut de Conception. Votre code fonctionne, mais est largement améliorable (inefficace et/ou illisible). On ne vous demande pas de sur-optimiser vos algorithmes, mais n'abusez pas non plus. Concerne aussi un programme qui en soi n'est pas problématique mais sera source d'erreur quand utilisé dans une autre situation (typiquement, dans la suite du sujet). De manière générale, concerne tout code qui aurait pu (et dû) être mieux écrit.
* **ES** : Erreur de Syntaxe.
* **ET** : Erreur de Type. Une expression est invalide car il est impossible de lui attribuer un type (vous additionnez des choux et des carottes par exemple), ou le résultat de votre fonction n'a pas le type attendu, ou le type d'un des paramètres ne correspond pas, ...
* **FM** : Fuite de mémoire. En C, tout ou partie de la mémoire allouée n'a pas été libérée.
* **HS** : Hors Sujet. Vous répondez complètement à côté de la question, ou bien vous racontez des choses non pertinentes. Quand vous me faîtes perdre du temps à lire des choses qui sont inutiles pour la réponse à la question (considérations superflues, éléments de cours balancés à tort et à travers, ...), cela donne l'impression que vous êtes fragiles et que vous n'êtes pas au clair sur les arguments pertinents.
* **JM / JTL** : Justification Manquante / Justification Trop Longue. Soit vous n'avez pas justifié, soit vous en avez mis beaucoup trop. La qualité d'une explication n'est pas une fonction croissante de sa longueur.
* **MD** : Mal Dit. L'idée est la bonne, mais elle mal exprimée. Le vocabulaire est important. Soyez clairs et concis.
* **ML** : Mauvais Langage. Un opérateur en C dans du code OCaml, un appel à une fonction OCaml dans du code en C, ... tout élément de syntaxe appartenant à un autre de langage de programmation que celui demandé.
* **MNV** : Mauvais Nom de Variable. Une variable est nommée sans respecter les contraintes du langage et/ou le choix du nom n'est pas pertinent. Peut aussi concerner des noms de fonctions.
* **NE** : Non Evident. Vous avez considéré comme trivial quelque chose qui ne l'était pas (par exemple une preuve « par récurrence immédiate » qui n'est pas du tout immédiate).
* **NH** : Non exHaustif. Souvent, vous avez oublié un cas particulier. En OCaml, cela concerne surtout les filtrages.
* **NTP** : Ne Termine Pas. Boucle infinie, ou appels récursifs qui n'atteignent jamais le cas de base.
* **PI** : Parenthèse Inutile. On n'utilise des parenthèses que si elles sont nécessaires et/où permettent une meilleure lisibilité du code. Et souvent, si vous avez besoin de mettre des parenthèses partout, c'est que votre code n'est pas bien conçu.
* **RDD** : ReDonDance. Calcul redondant, répété : un même calcul est effectué plusieurs fois au lieu d'utiliser une variable locale. Répétition d'un bout de code : pensez à réutiliser les fonctions définies dans les questions précédentes. Créer des fonctions auxiliaires peut souvent être pertinent.
* **TB** : Très Bien. Oui, ça peut arriver !
* **TL** : Trop Loin. Une boucle fait trop d'itérations, une fonction récursive fait un ou plusieurs appels en trop.
* **VI** : Variable Inutile. On introduit des variables locales que si elles améliorent la lisibilité et/ou permettent d'éviter la redondance de calculs. Peut aussi signifier Variable Inutilisée, s'il s'agit d'une variable qui n'est jamais lue, ou si vous déclarez une variable qui n'est utilisée que comme variable de boucle `for`.
* **VND** : Variable Non Définie / Déclarée.

Une grande croix à un endroit signifie qu'il y manque quelque chose (une partie de code ou une réponse à une question en plusieurs parties).


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
