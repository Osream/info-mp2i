-- II. Jointures

-- 1. 
SELECT Peintres.nom, Peintres.prenom, Pays.nom
FROM Peintres INNER JOIN Pays
ON Peintres.id_pays == Pays.id;

-- 2.
SELECT Oeuvres.nom
FROM Oeuvres INNER JOIN Musees
	ON Musees.id == Oeuvres.id_musee
WHERE Musees.id == 1;

-- 3.
SELECT Oeuvres.nom, Villes.nom
FROM Oeuvres INNER JOIN Musees
	ON Musees.id == Oeuvres.id_musee
INNER JOIN Villes
	ON Villes.id == Musees.id_ville;
	
-- 4.
SELECT Pays.nom, COUNT(Villes.id)
FROM Villes RIGHT JOIN Pays
	ON Villes.id_pays == Pays.id
GROUP BY Pays.id

-- 7.
SELECT Oeuvres.
