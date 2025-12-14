-- II. Fct d'agrégations et de groupes

-- 1.
SELECT COUNT(nom) FROM Pays;

-- 2.
SELECT Peintres.id, COUNT(Oeuvres.nom) AS nombre
FROM Oeuvres INNER JOIN Peintres
ON Oeuvres.id_peintre = Peintres.id
GROUP BY Oeuvres.id_peintre;

-- 3.
SELECT MIN(annee_mort - annee_naissance) AS age
FROM Peintres;

-- 4.
SELECT id_ville
FROM Musees
GROUP BY id_ville
HAVING COUNT(id) == 2;

-- 5.
SELECT COUNT(DISTINCT id_ville) AS nbre_ville
FROM Musees;

-- 6.
SELECT id_pays
FROM Peintres
GROUP BY id_pays
HAVING COUNT(id) >= 4;

-- 7.
SELECT id_peintre
FROM Oeuvres
WHERE id_musee ==1
GROUP BY id_peintre
HAVING COUNT(id) == 1;
