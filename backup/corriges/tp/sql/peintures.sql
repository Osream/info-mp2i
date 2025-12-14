
----------------------------------------------------------
-- CORRIGÉ PARTIEL DU TP : BASES DE DONNÉES (PEINTURES) --
-- Par J. BENOUWT                                       --
-- Licence CC BY-NC-SA                                  --
----------------------------------------------------------



----------------------------------------------------------------------------------------------------------------------------------------------------------------


----------------------
-- Étude de la base --
----------------------

-- Une clé primaire est un attribut (ou groupe d'attributs) pour lequel tous
-- les enregistrements doivent avoir une valeur différente, la clé primaire
-- permet d'identifier chaque enregistrement de manière unique.
-- Une clé étrangère est un attribut (ou groupe d'attributs) d'une relation
-- qui fait référence à la clé primaire d'une autre relation, la clé étrangère
-- permet de faire le lien entre deux relations.

-- On déduit de ces deux définitions les réponses aux questions posées :

-- Pourquoi a-t-on nécessairement dû ajouter un attribut `id` à la relation Peintres ?
-- Aucun attribut (ou groupe d'attributs) ne pouvait naturellement servir de clé primaire
-- de la relation Peintres (ils ont tous des potentiels doublons), `id` est ajouté pour
-- servir de clé primaire.

-- D’après le schéma relationnel de la base, plusieurs œuvres peuvent-elles avoir le même nom ?
-- Oui, le nom n'est pas la clé primaire.

-- D’après le schéma relationnel de la base, deux musées de noms différents peuvent-ils avoir le même identifiant ?
-- Non, l'identifiant est la clé primaire.

-- D’après le schéma relationnel de la base, un peintre peut-il avoir réalisé plusieurs œuvres ?
-- Oui, la clé étrangère reliant Oeuvres et Peintres se situe dans la relation Oeuvres
-- donc une œuvre a un unique peintre,
-- mais rien n'empêche un peintre d'avoir plusieurs œuvres qui le référence.

-- D’après le schéma relationnel de la base, une œuvre peut-elle exposée dans plusieurs musées différents ?
-- Non, la clé étrangère reliant Oeuvres et Musees se situe dans la relation Oeuvres.

-- D’après le schéma relationnel de la base, une ville peut-elle ne contenir aucun musée ?
-- Oui, la clé étrangère reliant Villes et Musees se situe dans la relation Musees,
-- donc une ville peut être référencée par aucun musée.

-- D’après le schéma relationnel de la base, un musée peut-il exposer une œuvre réalisée par un peintre non référencé dans la relation Peintres ?
-- Non, d'après les clés étrangères à nouveau,
-- une œuvre référence nécessairement un peintre existant.

-- D’après le schéma relationnel de la base, deux musées différents de même nom peuvent-ils exposer la même œuvre ?
-- Non, d'après les clés étrangères à nouveau, une œuvre est exposée dans un unique musée.

-- D’après le schéma relationnel de la base, un peintre peut-il être originaire d’un pays ne contenant aucun musée ?
-- Oui, d'après une question précédente, une ville peut ne contenir aucun musée,
-- le même raisonnement est valable pour un pays,
-- et la clé étrangère Pays-Peintres est indépendante de ce raisonnement.

-- D’après le schéma relationnel de la base, un musée peut-il se situer dans le pays d’origine du peintre d’une des œuvres qu’il expose ?
-- Oui les clés étrangères Pays-Peintres (pays d'origine) et
-- Pays-Villes-Musees-Oeuvres-Peintres (pays exposant) sont indépendantes.

-- D’après le schéma relationnel de la base, une œuvre peut-elle être exposée dans aucun musée ?
-- Oui, le schéma ne fait pas figurer les domaines donc a priori,
-- rien n'empêche l'attribut id_musee de la relation Oeuvres d'être NULL.



----------------------------------------------------------------------------------------------------------------------------------------------------------------


-------------------------------
-- Requêtes SQL élémentaires --
-------------------------------


-- Sélection avec ou sans formatage
-----------------------------------

-- Quels sont, sans doublons, les noms des musées ?
SELECT DISTINCT nom
FROM Musees

-- Qui est le peintre d’identifiant 180 ?
SELECT *
FROM Peintres
WHERE id = 180

-- Quels sont, dans l’ordre alphabétique, les noms des villes ?
SELECT nom
FROM Villes
ORDER BY nom ASC

-- Quelles sont les œuvres dont le nom commence par le mot « Le » ?
SELECT *
FROM Oeuvres
WHERE nom LIKE 'Le %'

-- Quel est le pays au nom le plus long ?
SELECT *
FROM Pays
ORDER BY LENGTH(nom) DESC
LIMIT 1

-- Quelles sont les œuvres du peintre d’identifiant 40
-- exposées dans le musée d’identifiant 5 ?
SELECT *
FROM Oeuvres
WHERE id_peintre = 40 AND id_musee = 5

-- Qui sont les deuxième et troisième peintres
-- originaires du pays d’identifiant 1 morts en dernier ?
SELECT *
FROM Peintres
WHERE id_pays = 1 AND annee_mort IS NOT NULL
ORDER BY annee_mort DESC
LIMIT 2
OFFSET 1


-- Fonctions d’agrégation et groupes
------------------------------------

-- Combien y a-t-il de pays ?
SELECT COUNT(id) AS 'nb_pays'
FROM Pays

-- Quels sont les identifiants et nombre d’œuvres de chaque peintre ?
-- Les peintres n’ayant rien réalisé n’ont pas besoin d’apparaître dans le résultat.
SELECT id_peintre, COUNT(id) AS 'nb_oeuvres'
FROM Oeuvres
GROUP BY id_peintre

-- À quel âge est mort le peintre ayant vécu le moins longtemps ?
SELECT MIN(annee_mort - annee_naissance) AS 'age_mort_minimal'
FROM Peintres
WHERE annee_mort IS NOT NULL

-- Quels sont les identifiants des villes possédant 2 musées ?
SELECT id_ville
FROM Musees
GROUP BY id_ville
HAVING COUNT(id) = 2

-- Combien de villes possèdent un musée ?
SELECT COUNT(DISTINCT id_ville) AS 'nb_villes_avec_musee'
FROM Musees

-- Quels sont les identifiants des pays dont au moins quatre peintres sont originaires ?
SELECT id_pays
FROM Peintres
GROUP BY id_pays
HAVING COUNT(id) >= 4

-- Quels sont les identifiants des peintres
-- dont une seule œuvre est exposée au musée d’identifiant 1 ?
SELECT id_peintre
FROM Oeuvres
WHERE id_musee = 1
GROUP BY id_peintre
HAVING COUNT(id) = 1


-- Jointures
------------

-- Quels sont les prénom et nom des peintres, et noms de leurs pays d’origine ?
SELECT Peintres.prenom, Peintres.nom, Pays.nom
FROM Peintres
JOIN Pays ON Peintres.id_pays = Pays.id

-- Quels sont les noms des œuvres exposées au Musée du Louvre ?
SELECT Oeuvres.nom
FROM Oeuvres
JOIN Musees ON Oeuvres.id_musee = Musees.id
WHERE Musees.nom = 'Musée du Louvre'

-- Quels sont les noms des œuvres exposées
-- et noms des villes dans lesquelles on peut les trouver ?
SELECT Oeuvres.nom, Villes.nom
FROM Oeuvres
JOIN Musees ON Oeuvres.id_musee = Musees.id
JOIN Villes ON Musees.id_ville = Villes.id

-- Quels sont les noms des œuvres exposées en France ?
SELECT Oeuvres.nom
FROM Oeuvres
JOIN Musees ON Oeuvres.id_musee = Musees.id
JOIN Villes ON Musees.id_ville = Villes.id
JOIN Pays ON Villes.id_pays = Pays.id
WHERE Pays.nom = 'France'

-- Quel est le nom et nombre de villes de chaque pays ?
-- Le résultat doit aussi contenir les pays n’ayant aucune ville.
SELECT Pays.nom, COUNT(Villes.id) AS 'nb_villes'
FROM Pays
LEFT JOIN Villes ON Pays.id = Villes.id_pays
GROUP BY Pays.id

-- Quels sont les identifiants et nombre d’œuvres de chaque peintre ?
-- Le résultat doit contenir tous les peintres.
SELECT P.id, COUNT(O.id) AS 'nb_oeuvres'
FROM Peintres AS P
LEFT JOIN Oeuvres AS O ON P.id = O.id_peintre
GROUP BY P.id

-- Pour chaque œuvre exposée, quel est son nom,
-- nom du pays dans lequel on peut la trouver,
-- et nom du pays d’origine du peintre l’ayant réalisée ?
SELECT O.nom, Pays1.nom AS 'pays_peintre', Pays2.nom AS 'pays_musee'
FROM Oeuvres AS O
JOIN Peintres AS P ON O.id_peintre = P.id
JOIN Pays AS Pays1 ON P.id_pays = Pays1.id -- pays d'origine du peintre
JOIN Musees AS M ON O.id_musee = M.id
JOIN Villes AS V ON M.id_ville = V.id
JOIN Pays AS Pays2 ON V.id_pays = Pays2.id -- pays d'exposition de l'œuvre


-- Sous-requêtes
----------------

-- Quelles sont les années ayant vu naître et mourir un peintre ?
SELECT annee_mort AS 'années ayant vu naître et mourir un peintre'
FROM Peintres
    INTERSECT
SELECT annee_naissance
FROM Peintres

-- Qui sont les peintres morts ayant vécu plus longtemps que la moyenne ?
SELECT *
FROM Peintres
WHERE annee_mort IS NOT NULL AND
      annee_mort - annee_naissance > ( SELECT AVG(annee_mort - annee_naissance) -- moyenne des durées de vies
                                       FROM Peintres )
                                       
-- Quels sont les identifiants des pays dont aucun peintre n’est originaire ?
SELECT id -- tous les pays
FROM Pays
    EXCEPT -- sauf
SELECT id_pays -- ceux dont un peintre est originaire
FROM Peintres

-- Qui est(sont) le(s) peintre(s) le(s) plus ancien(s) ?
SELECT *
FROM Peintres
WHERE annee_naissance = ( SELECT MIN(annee_naissance) -- année la plus ancienne
                          FROM Peintres )

-- Quel(s) est(sont) le(s) nom(s) du(des) musée(s) dont le nom est de taille maximale ?
SELECT nom
FROM Musees
WHERE LENGTH(nom) = ( SELECT MAX(LENGTH(nom)) -- taille maximale
                      FROM Musees )

-- Quels sont les noms communs des peintres qui en ont un
-- et noms complets (prénoms et noms concaténés) des peintres qui n’en ont pas ?
-- Le résultat doit avoir une unique colonne intitulée « nom d’usage ».

SELECT nom_commun AS 'nom d''usage' -- double apostrophe pour indiquer qu'on veut en mettre une et non fermer l'alias
FROM Peintres
WHERE nom_commun IS NOT NULL
    UNION
SELECT prenom || ' ' || nom -- espace pour plus de lisibilité
FROM Peintres
WHERE nom_commun IS NULL

-- Quels sont les identifiants des pays ayant strictement plus de villes
-- que le pays d’identifiant 2 ?
SELECT id_pays
FROM Villes
GROUP BY id_pays
HAVING COUNT(id) > ( SELECT COUNT(id) -- nombre de villes du pays d'id 2
                     FROM Villes
                     WHERE id_pays = 2 )



----------------------------------------------------------------------------------------------------------------------------------------------------------------


---------------------------
-- Requêtes SQL avancées --
---------------------------


-- Niveau ★
------------

-- Quels sont, sans doublon, les deux derniers chiffres
-- des années de naissance des peintres ?
SELECT DISTINCT annee_naissance % 100 AS 'deux derniers chiffres des années de naissance'
FROM Peintres

-- Quelles sont les œuvres qui ne sont pas exposées ?
SELECT *
FROM Oeuvres
WHERE id_musee IS NULL

-- Qui sont les peintres qui sont morts avant leur quarantième anniversaire ?
SELECT *
FROM Peintres
WHERE annee_mort - annee_naissance < 40

-- Quels sont les âges des peintres encore en vie ?
SELECT 2025 - annee_naissance AS 'age'
FROM Peintres
WHERE annee_mort IS NULL

-- Quel est le nom complet (nom et prénom concaténés)
-- et nom commun des peintres qui en ont un ?
SELECT prenom || ' ' || nom AS 'nom_complet', nom_commun
FROM Peintres
WHERE nom_commun IS NOT NULL

-- Qui sont les peintres nés une année paire et mort une année impaire du même siècle ?
SELECT *
FROM Peintres
WHERE annee_naissance % 2 = 0 AND annee_mort % 2 = 1
      AND annee_naissance / 100 = annee_mort / 100

-- Qui sont les peintres ayant un prénom composé ?
SELECT *
FROM Peintres
WHERE prenom LIKE '%-%' OR prenom LIKE '% %' -- prénom composé = contient un tiret ou espace

-- Quels sont les noms des œuvres actuellement exposées
-- dont le nom comporte deux 'e' encadrant exactement 2 caractères ?
SELECT nom
FROM Oeuvres
WHERE id_musee IS NOT NULL AND LOWER(nom) LIKE '%e__e%'

-- Quel est le nom complet (prénom et nom concaténés) des peintres
-- dont le prénom contient un 'a', le nom ne commence pas par 'Ve'
-- et dont l’avant dernière lettre est un 'i' ?
SELECT prenom || ' ' || nom AS 'nom_complet'
FROM Peintres
WHERE prenom LIKE '%a%' AND nom NOT LIKE 'Ve%' AND nom LIKE '%i_'

-- Combien y a-t-il d’œuvres exposées ?
SELECT COUNT(id_musee) AS 'nb_oeuvres_exposees' -- les NULL ne sont pas comptés
FROM Oeuvres

-- Combien de caractères contient le plus long nom d’œuvre ?
SELECT MAX(LENGTH(nom)) AS 'plus_long_nom'
FROM Oeuvres

-- Quelle est la moyenne d’âge des peintres à leur mort ?
SELECT AVG(annee_mort - annee_naissance) AS 'duree_de_vie_moyenne'
FROM Peintres
WHERE annee_mort IS NOT NULL

-- Combien de villes ont un nom qui finit par un e ou par un s ?
SELECT COUNT(id) AS 'nb_villes'
FROM Villes
WHERE nom LIKE '%e' OR nom LIKE '%s'

-- Qui sont les cinq derniers peintres morts ?
SELECT *
FROM Peintres
WHERE annee_mort IS NOT NULL
ORDER BY annee_mort DESC
LIMIT 5

-- Quels sont, suivant l’ordre lexicographique croissant de leur nom,
-- les troisième, quatrième et cinquième pays ?
SELECT *
FROM Pays
ORDER BY nom ASC
LIMIT 3
OFFSET 2

-- Combien de villes y a-t-il dans chaque pays ?
SELECT id_pays, COUNT(id) AS 'nb_villes'
FROM Villes
GROUP BY id_pays

-- Quels sont les identifiants des pays ayant au moins 2 villes ?
SELECT id_pays
FROM Villes
GROUP BY id_pays
HAVING COUNT(id) >= 2

-- Quels sont les noms des œuvres peintes par Édouard Manet ?
SELECT O.nom
FROM Oeuvres AS O
JOIN Peintres AS P ON O.id_peintre = P.id
WHERE P.prenom = 'Édouard' AND P.nom = 'Manet'

-- Quels sont les prénoms et noms des peintres qui n’ont vécu qu’au XVIIe siècle,
-- ou qui sont français et ont vécu au moins 70 ans ?
SELECT P.prenom, P.nom
FROM Peintres AS P
JOIN Pays ON P.id_pays = Pays.id
WHERE (P.annee_naissance > 1600 AND P.annee_mort <= 1700) OR
      (Pays.nom = 'France' AND annee_mort - annee_naissance >= 70)

-- Pour toutes les œuvres, quel est leur nom et,
-- le cas échéant, le nom du musée l’exposant ?
SELECT O.nom, M.nom
FROM Oeuvres AS O
LEFT JOIN Musees AS M ON O.id_musee = M.id

-- Quelles sont les années de morts de peintres qui ne sont pas aussi
-- des années de naissance d'autres peintres ?
SELECT annee_mort
FROM Peintres
WHERE annee_mort IS NOT NULL
    EXCEPT
SELECT annee_naissance
FROM Peintres


-- Niveau ★★
--------------

-- Quels sont les nom et prénom du peintre naît en dernier ?
-- 1ère possibilité :
SELECT prenom, nom
FROM Peintres
ORDER BY annee_naissance DESC
LIMIT 1
-- 2ème possibilité :
SELECT prenom, nom
FROM Peintres
WHERE annee_naissance = ( SELECT MAX(annee_naissance)
                          FROM Peintres )
                          
-- Quels sont (sans doublon) les noms qui sont ceux d’au moins deux œuvres différentes ? 
-- 1ère possibilité :
SELECT DISTINCT O1.nom
FROM Oeuvres AS O1, Oeuvres AS O2
WHERE O1.id <> O2.id AND O1.nom = O2.nom
-- 2ème possibilité :
SELECT DISTINCT nom
FROM Oeuvres
GROUP BY nom
HAVING COUNT(id) >= 2

-- Existe-t-il des musées n’exposant aucune œuvre ?
-- 1ère possibilité :
SELECT id
FROM Musees
    EXCEPT
SELECT id_musee
FROM Oeuvres
-- 2ème possibilité :
SELECT DISTINCT Musees.id
FROM Musees
LEFT JOIN Oeuvres ON Musees.id = Oeuvres.id_musee
WHERE id_musee IS NULL

-- Qui est le peintre mort, ayant un nom commun,
-- ayant un prénom ou un nom de plus de 10 lettres,
-- et né une année bissextile, qui a vécu le plus longtemps ?
SELECT *
FROM Peintres
WHERE annee_mort IS NOT NULL AND nom_commun IS NOT NULL AND
      (LENGTH(prenom) >= 10 OR LENGTH(nom) >= 10) AND
      (annee_naissance % 400 = 0 OR (annee_naissance % 4 = 0 AND annee_naissance % 100 <> 0))
ORDER BY annee_mort - annee_naissance DESC
LIMIT 1

-- Quels sont les noms des œuvres peintes par Le Titien exposées à Paris ?
SELECT O.nom
FROM Oeuvres AS O
JOIN Peintres ON O.id_peintre = Peintres.id
JOIN Musees ON O.id_musee = Musees.id
JOIN Villes ON Musees.id_ville = Villes.id
WHERE Peintres.nom_commun = 'Le Titien' AND Villes.nom = 'Paris'

-- Combien d’œuvres sont exposées au musée Unterlinden ?
SELECT COUNT(Oeuvres.id) AS 'nb_oeuvres'
FROM Oeuvres
JOIN Musees ON Oeuvres.id_musee = Musees.id
WHERE Musees.nom = 'Musée Unterlinden'

-- Quelle est la longueur totale des noms des œuvres de Vincent van Gogh ?
SELECT SUM(LENGTH(O.nom)) AS 'longueur_totale'
FROM Oeuvres AS O
JOIN Peintres AS P ON O.id_peintre = P.id
WHERE P.prenom = 'Vincent' AND P.nom = 'van Gogh'

-- Pour toutes les œuvres, quel est leur nom et,
-- le cas échéant, le nom du pays dans lequel on peut la trouver ?
-- On triera le résultat par ordre lexicographique des noms de pays puis,
-- en cas d’égalité, par ordre lexicographique décroissant des noms d’œuvres.
SELECT Oeuvres.nom, Pays.nom
FROM Oeuvres
LEFT JOIN Musees ON Oeuvres.id_musee = Musees.id
LEFT JOIN Villes ON Musees.id_ville = Villes.id
LEFT JOIN Pays ON Villes.id_pays = Pays.id
ORDER BY Pays.nom ASC, Oeuvres.nom DESC

-- Quelles sont les villes se trouvant dans un même pays ?
-- Le résultat doit comporter trois colonnes, contenant respectivement
-- deux noms de villes se trouvant dans un même pays, et le nom de ce pays.
SELECT V1.nom AS 'ville 1', V2.nom AS 'ville 2', V1.id_pays AS 'pays'
FROM Villes AS V1, Villes AS V2
WHERE V1.id <> V2.id AND V1.id_pays = V2.id_pays

-- Qui est le cinquième peintre français le plus ancien ?
SELECT Peintres.*
FROM Peintres
JOIN Pays ON Peintres.id_pays = Pays.id
WHERE Pays.nom = 'France'
ORDER BY annee_naissance ASC
LIMIT 1
OFFSET 4

-- Quels sont les noms des peintres qui ont une œuvre de nom plus long que la moyenne ?
SELECT P.nom
FROM Peintres AS P
JOIN Oeuvres AS O ON P.id = O.id_peintre
WHERE LENGTH(O.nom) > ( SELECT AVG(LENGTH(nom)) -- moyenne des tailles des noms d'œuvres
                        FROM Oeuvres )
                        
-- Combien de peintres sont nés après l’année moyenne de naissance d’un peintre ?
SELECT COUNT(id) AS 'nb_peintres'
FROM Peintres
WHERE annee_naissance > ( SELECT AVG(annee_naissance)
                          FROM Peintres )

-- Pour tous les pays, quel est son nom et nombre de peintres qui en sont originaires ?
SELECT Pays.nom, COUNT(Peintres.id) AS 'nb_peintres'
FROM Pays
LEFT JOIN Peintres ON Pays.id = Peintres.id_pays
GROUP BY Pays.id

-- Quel est l’identifiant du musée exposant le plus d’œuvres ?
SELECT id_musee
FROM Oeuvres
GROUP BY id_musee
ORDER BY COUNT(id) DESC
LIMIT 1

-- Pour chaque pays ayant vu naître au moins deux peintres,
-- quel est son nom et année de naissance du plus récent peintre né dans ce pays ?
SELECT Pays.nom, MAX(Peintres.annee_naissance) AS 'annee_naissance_plus_recente'
FROM Pays
JOIN Peintres ON Pays.id = Peintres.id_pays
GROUP BY Pays.id
HAVING COUNT(Peintres.id) >= 2

-- Quels sont les identifiants des musées qui exposent au moins deux œuvres dont le titre commence par L ?
SELECT id_musee
FROM Oeuvres
WHERE nom LIKE 'L%'
GROUP BY id_musee
HAVING COUNT(id) >= 2

-- Quels sont les prénom et nom des peintres
-- dont une seule œuvre est exposée au musée du Louvre ?
SELECT Peintres.prenom, Peintres.nom
FROM Peintres
JOIN Oeuvres ON Peintres.id = Oeuvres.id_peintre
JOIN Musees ON Oeuvres.id_musee = Musees.id
WHERE Musees.nom = 'Musée du Louvre'
GROUP BY Peintres.id
HAVING COUNT(Oeuvres.id) = 1

-- Quels sont, sans doublon, les noms des musées qui exposent
-- au moins deux œuvres du peintre de nom commun Le Titien ?
SELECT DISTINCT Musees.nom
FROM Peintres
JOIN Oeuvres ON Peintres.id = Oeuvres.id_peintre
JOIN Musees ON Oeuvres.id_musee = Musees.id
WHERE Peintres.nom_commun = 'Le Titien'
GROUP BY Musees.id
HAVING COUNT(Oeuvres.id) >= 2

-- Quels sont les prénoms et noms de peintres, ainsi que les noms des pays
-- dans lesquels un peintre a pu voyager, sachant que l’on ne prend pas en compte
-- un pays dont le peintre est originaire ?
SELECT P.prenom, P.nom, Pays.nom
FROM Peintres AS P, Pays
WHERE P.id_pays <> Pays.id


-- Niveau ★★★
----------------

-- Quel est le nom du peintre dont le plus d’œuvres sont exposées dans un même musée ?
SELECT Peintres.nom
FROM Oeuvres
JOIN Peintres ON Oeuvres.id_peintre = Peintres.id
GROUP BY Peintres.id, Oeuvres.id_musee
ORDER BY COUNT(Oeuvres.id) DESC
LIMIT 1

-- Combien y a-t-il de peintres ayant vécu à partir du XVème siècle dont le nom
-- contient la particule di ou van et dont une œuvre est exposée à Paris ?
SELECT COUNT(DISTINCT P.id) AS 'nb_peintres'
FROM Peintres AS P
JOIN Oeuvres ON P.id = Oeuvres.id_peintre
JOIN Musees ON Oeuvres.id_musee = Musees.id
JOIN Villes ON Musees.id_ville = Villes.id
WHERE P.annee_naissance > 1400 AND (P.nom LIKE '%di %' OR P.nom LIKE '%van %')
      AND Villes.nom = 'Paris'

-- Quel est le nombre moyen d’œuvres par peintre ?
SELECT AVG(nb_oeuvres_par_peintre) AS 'nb_moyen_oeuvres'
FROM ( SELECT COUNT(id) AS 'nb_oeuvres_par_peintre'
       FROM Oeuvres
       GROUP BY id_peintre )

-- Quels sont les noms des œuvres exposées
-- dans le pays d’origine du peintre l’ayant réalisée ?
SELECT O.nom
FROM Oeuvres AS O
JOIN Peintres ON O.id_peintre = Peintres.id
JOIN Musees ON O.id_musee = Musees.id
JOIN Villes ON Musees.id_ville = Villes.id
WHERE Villes.id_pays = Peintres.id_pays

-- Quel est l’identifiant du troisième pays
-- dont le plus de peintres nés au XIXème siècle sont originaires ?
SELECT id_pays
FROM Peintres
WHERE annee_naissance > 1800 AND annee_naissance <= 1900
GROUP BY id_pays
ORDER BY COUNT(id) DESC
LIMIT 1
OFFSET 2

-- Quels sont les identifiants, prénoms et noms des peintres originaires
-- du même pays que le peintre connu sous le nom commun Sandro Botticelli ?
SELECT id, prenom, nom
FROM Peintres
WHERE (nom_commun <> 'Sandro Botticelli' OR nom_commun IS NULL)
	  AND id_pays = ( SELECT id_pays
					  FROM Peintres
					  WHERE nom_commun = 'Sandro Botticelli' )
					  
-- Combien y a-t-il de villes portant le nom d'un pays ?
SELECT COUNT(*) AS 'nombre de villes portant le nom d''un pays'
FROM ( SELECT nom
       FROM Villes
           INTERSECT
       SELECT nom
       FROM Pays )
       
-- Quels sont les noms des pays pour lesquels aucun peintre originaire de ce pays
-- dont une œuvre est exposée à Paris n’est né après 1800 ?
SELECT Pays.nom
FROM Pays
JOIN Peintres ON Peintres.id_pays = Pays.id
JOIN Oeuvres ON Peintres.id = Oeuvres.id_peintre
JOIN Musees ON Oeuvres.id_musee = Musees.id
JOIN Villes ON Musees.id_ville = Villes.id
WHERE Villes.nom = 'Paris'
GROUP BY Pays.id
HAVING MAX(Peintres.annee_naissance) < 1800

-- Quels sont (sans doublon) les noms des peintres qui sont exposés dans un musée
-- dans lequel il y a au moins un autre peintre de même nationalité qui est exposé ?
SELECT DISTINCT P.nom
FROM Peintres AS P
JOIN Oeuvres AS O ON P.id = O.id_peintre
JOIN Musees AS M ON M.id = O.id_musee
JOIN Oeuvres AS O2 ON M.id = O2.id_musee
JOIN Peintres AS P2 ON P2.id = O2.id_peintre
WHERE P.id <> P2.id AND P.id_pays = P2.id_pays

-- Combien y a-t-il de pays qui contiennent un musée
-- mais dont aucun peintre n’est originaire ?
SELECT COUNT(*) AS 'nb_pays'
FROM ( SELECT id_pays -- pays contenant un musée
       FROM Villes
       JOIN Musees ON Villes.id = Musees.id_ville
           EXCEPT
       SELECT id_pays -- pays dont un peintre est originaire
       FROM Peintres )

-- Quelles sont les années qui ont vu soit la naissance soit la mort d’un peintre ?
SELECT * FROM ( SELECT annee_naissance -- années de naissance ou de mort
                FROM Peintres
                    UNION
                SELECT annee_mort
                FROM Peintres
                WHERE annee_mort IS NOT NULL )
    EXCEPT
SELECT * FROM ( SELECT annee_naissance -- années de naissance et de mort
                FROM Peintres
                    INTERSECT
                SELECT annee_mort
                FROM Peintres
                WHERE annee_mort IS NOT NULL )


-- Quel est le nom des peintres qui ont peint au moins une œuvre
-- exposée dans un pays dans lequel est exposé dans une autre ville de ce pays
-- au moins une œuvre d’un peintre qui est mort strictement plus tôt ?
SELECT DISTINCT P.nom
FROM Peintres AS P
JOIN Oeuvres AS O ON P.id = O.id_peintre
JOIN Musees AS M ON M.id = O.id_musee
JOIN Villes AS V ON V.id = M.id_ville
JOIN Pays ON Pays.id = V.id_pays
JOIN Villes AS V2 ON Pays.id = V2.id_pays
JOIN Musees AS M2 ON V2.id = M2.id_ville
JOIN Oeuvres AS O2 ON M2.id = O2.id_musee
JOIN Peintres AS P2 ON P2.id = O2.id_peintre
WHERE V.id <> V2.id AND P2.annee_mort < P.annee_mort

-- Qui sont les peintres (prénom et nom) exposés au musée d’Orsay et au musée du Louvre ?
SELECT P.prenom, P.nom -- peintres exposés au musée du Louvre
FROM Peintres AS P
JOIN Oeuvres ON P.id = Oeuvres.id_peintre
JOIN Musees ON Oeuvres.id_musee = Musees.id
WHERE Musees.nom = 'Musée du Louvre'
    INTERSECT
SELECT P.prenom, P.nom -- peintres exposés au musée d'Orsay
FROM Peintres AS P
JOIN Oeuvres ON P.id = Oeuvres.id_peintre
JOIN Musees ON Oeuvres.id_musee = Musees.id
WHERE Musees.nom = 'Musée d''Orsay'

-- Qui sont les peintres italiens dont au moins deux œuvres sont exposées en Italie ?
SELECT P.*
FROM Peintres AS P
JOIN Pays AS PaysOrigine ON P.id_pays = PaysOrigine.id
JOIN Oeuvres ON P.id = Oeuvres.id_peintre
JOIN Musees ON Oeuvres.id_musee = Musees.id
JOIN Villes ON Musees.id_ville = Villes.id
JOIN Pays AS PaysExposition ON Villes.id_pays = PaysExposition.id
WHERE PaysOrigine.nom = 'Italie' AND PaysExposition.nom = 'Italie'
GROUP BY P.id
HAVING COUNT(Oeuvres.id) >= 2

-- Qui sont les peintres dont toutes les œuvres ont un nom plus long que la moyenne ?
SELECT Peintres.*
FROM Peintres
JOIN Oeuvres ON Peintres.id = Oeuvres.id_peintre
GROUP BY Peintres.id
HAVING MIN(LENGTH(Oeuvres.nom)) > ( SELECT AVG(LENGTH(nom))
                                    FROM Oeuvres )

-- Combien de musées exposent strictement plus d’œuvres que le Rijksmuseum ?
SELECT COUNT(*)
FROM ( SELECT id_musee
       FROM Oeuvres
       GROUP BY id_musee
       HAVING COUNT(id) > ( SELECT COUNT(O.id) -- nombre d'œuvres du Rijksmuseum
                            FROM Oeuvres AS O
                            JOIN Musees ON O.id_musee = Musees.id
                            WHERE Musees.nom = 'Rijksmuseum' )
     )

-- Quel est le nombre moyen d’œuvres dans les musées français
-- qui exposent au moins deux œuvres ?
SELECT AVG(nb_oeuvres) AS 'nb_moyen_oeuvres'
FROM ( SELECT COUNT(Oeuvres.id) AS 'nb_oeuvres' -- nombre d'œuvres
       FROM Oeuvres
       JOIN Musees ON Oeuvres.id_musee = Musees.id
       JOIN Villes ON Musees.id_ville = Villes.id
       JOIN Pays ON Villes.id_pays = Pays.id
       WHERE Pays.nom = 'France' -- des musées français
       GROUP BY Musees.id
       HAVING COUNT(Oeuvres.id) >= 2 ) -- qui exposent au moins deux œuvres
       
-- Qui sont les peintres ayant réalisé plus d’œuvres que la moyenne ?
SELECT Peintres.*
FROM Peintres
JOIN Oeuvres ON Peintres.id = Oeuvres.id_peintre
GROUP BY Peintres.id
HAVING COUNT(Oeuvres.id) > ( SELECT AVG(nb_oeuvres) -- nombre moyen d'œuvres par peintre
                             FROM ( SELECT COUNT(id) AS 'nb_oeuvres'
                                    FROM Oeuvres
                                    GROUP BY id_peintre )
                           )
                           
-- Quelle(s) est(sont) la(s) ville(s) possédant le plus de musées ?
SELECT Villes.*
FROM Villes
JOIN Musees ON Villes.id = Musees.id_ville
GROUP BY Villes.id
HAVING COUNT(Musees.id) = ( SELECT MAX(nb_musees) -- nombre maximal de musées par ville
                            FROM ( SELECT COUNT(id) AS 'nb_musees'
                                   FROM Musees
                                   GROUP BY id_ville )
                          )

-- Quels sont les noms des peintres exposés dans tous les musées parisiens ?
SELECT P.nom
FROM Peintres AS P
JOIN Oeuvres AS O ON P.id = O.id_peintre
JOIN Musees AS M ON M.id = O.id_musee
JOIN Villes AS V ON V.id = M.id_ville
WHERE V.nom = 'Paris'
GROUP BY P.id
HAVING COUNT(DISTINCT M.id) = (	SELECT COUNT(M.id) -- nombre de musées parisiens
								FROM Musees AS M
								JOIN Villes AS V ON V.id = M.id_ville
								WHERE V.nom = 'Paris' )


