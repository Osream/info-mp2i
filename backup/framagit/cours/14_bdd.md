# Chapitre 14 : Bases de données

## I. Conception d'une base de données

### 1. Paradigme logique

Notion de base de données (BDD), de système de gestion de base de données (SGBD).

Principe du paradigme logique.

### 2. Modèle entité-association

Définition d'une entité, représentation et exemple. Une entité peut toujours être identifiée de manière unique.

Définition d'une association, représentation et exemple. On se limite aux associations binaires.

Définition d'une contrainte de cardinalité, cardinalités usuelles $`1-1 \;;\; 1-*\;;\;*-*`$​.

Séparation d'une association de cardinalité $`*-*`$ en deux associations $`1-*`$.

### 3. Modèle relationnel

Définitions : relation, attribut, domaine d'un attribut, enregistrement, schéma relationnel.

Contrainte d'unicité et clé primaire.

Contrainte d'intégrité et clé étrangère.

Conception d'une base de données : passage du modèle entité-association au modèle relationnel. 

## II. Requêtes SQL

Bonnes pratiques pour la syntaxe des requêtes SQL (Structured Query Language).

### 1. Projection

Mots-clefs : `SELECT, FROM, DISTINCT`.

Sélection de tous les attributs avec `*`.

Opérateurs (`+`, `-`, etc.).

Les enregistrements dans le résultat d'une projection sont dans un ordre arbitraire.

![](img/15_bdd/select_from.png)

![](img/15_bdd/select_tout.png)

![](img/15_bdd/distinct.png)

### 2. Formater une projection

Mots-clefs : `AS, ORDER BY (ASC / DESC), LIMIT, OFFSET`.

Le mot-clef `OFFSET` doit toujours être précédé de `LIMIT`.

![](img/15_bdd/as.png)

![](img/15_bdd/order_by.png)

![](img/15_bdd/limit.png)

![](img/15_bdd/offset.png)

### 3. Opérations ensemblistes

Mots-clef : `UNION, INTERSECT, EXCEPT`.

Le résultat des requêtes reliées par un opérateur ensembliste doivent avoir le même nombre de colonnes, et les colonnes aux mêmes positions doivent avoir le même domaine. Les colonnes du résultat porteront le même nom que ceux de la première requête. Le résultat ne comportera aucun doublon.

Produit cartésien : `FROM Relation1, Relation2, ...`.

![](img/15_bdd/union.png)

![](img/15_bdd/intersect.png)

![](img/15_bdd/except.png)

![](img/15_bdd/produit_cartesien.png)

### 4. Sélection

Mots-clefs : `WHERE, AND, OR, NOT, IS (NOT) NULL, LIKE`.

Opérateurs booléens (`=`, `<>`, etc.).

![](img/15_bdd/where.png)

### 5. Jointures

Mots-clefs : `JOIN ... ON ..., LEFT JOIN ... ON ...`.

![](img/15_bdd/join.png)

![](img/15_bdd/left_join.png)

Autojointures.

![](img/15_bdd/autojointure.png)

### 6. Fonctions d'agrégation

Mots-clefs : `MIN, MAX, SUM, AVG, COUNT`.

![](img/15_bdd/min.png)

![](img/15_bdd/max.png)

![](img/15_bdd/sum.png)

![](img/15_bdd/avg.png)

![](img/15_bdd/count.png)

### 7. Regroupement et filtrage des agrégats

Mots-clefs : `GROUP BY, HAVING`.

Le `WHERE` filtre les enregistrements (avant que les groupes soient faits), le `HAVING` filtre les groupes.

![](img/15_bdd/group_by.png)

![](img/15_bdd/having.png)

![](img/15_bdd/where_et_having.png)

### 8. Requêtes imbriquées

![](img/15_bdd/imbrique_where.png)

![](img/15_bdd/imbrique_from.png)

### Conclusion

![](img/15_bdd/memento_sql.png)


---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Source des images : *production personnelle*
