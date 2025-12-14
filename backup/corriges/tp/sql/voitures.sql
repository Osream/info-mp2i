
-----------------------------------------------------------------------------------
-- CORRIGÉ PARTIEL DU TP : BASES DE DONNÉES (LOCATIONS DE VOITURES, SUITE DU DM) --
-- Par J. BENOUWT                                                                --
-- Licence CC BY-NC-SA                                                           --
-----------------------------------------------------------------------------------



----------------------------------------------------------------------------------------------------------------------------------------------------------------


--------------------------------------
-- Découverte du modèle relationnel --
--------------------------------------


-- L'objectif de cette partie était de découvrir l'organisation d'une base de données
-- selon le modèle relationnel, avec vocabulaire associé. Voici un résumé pour notre base :


-- Les trois « relations » sont Locations, Voitures, Clients.


-- Les sept « attributs » (et leurs « domaines ») de la relation Clients sont :
-- * numero_permis : INTEGER, positif à 12 chiffres, non NULL
-- * nom : TEXT, non NULL
-- * prenom : TEXT, non NULL
-- * annee_naissance : INTEGER, compris entre 1900 et 2025, non NULL
-- * adresse : TEXT, au format [Ville], [numéro] [type de voie] [nom de la voie], peut être NULL
-- * email : TEXT, au format [texte]@[texte].[texte], peut être NULL
-- * telephone : TEXT, contient 10 caractères étant des chiffres, peut être NULL

-- Les cinq « attributs » (et leurs « domaines ») de la relation Voitures sont :
-- * immatriculation : TEXT, au format [2 lettres]-[3 chiffres]-[2 lettres], non NULL
-- * marque : TEXT, non NULL
-- * modele : TEXT, non NULL
-- * annee : INTEGER, compris entre 1900 et 2025, non NULL
-- * prix_par_jour : REAL, positif, non NULL

-- Les cinq « attributs » (et leurs « domaines ») de la relation Locations sont :
-- * id : INTEGER, non NULL
-- * permis_client : INTEGER, positif à 12 chiffres, non NULL
-- * immat_voiture : TEXT, au format [2 lettres]-[3 chiffres]-[2 lettres], non NULL
-- * nb_jours : INTEGER, positif, non NULL
-- * date_debut : TEXT, date au format [année]-[mois]-[jour], non NULL


-- Les « clés primaires » sont :
-- * pour Clients, l'attribut numero_permis ;
-- * pour Voitures, l'attribut immatriculation ;
-- * pour Locations, l'attribut id.

-- Les « clés étrangères sont » :
-- * l'attribut permis_client de la relation Locations qui fait référence à l'attribut numero_permis de la relation Clients ;
-- * l'attribut immat_voiture de la relation Locations qui fait référence à l'attribut immatriculation de la relation Voitures.


-- Le « schéma relationnel » résume tous les éléments ci-dessus.


-- Concernant les « enregistrements » :
-- * la relation Clients en comporte 60 ;
-- * la relation Voitures en comporte 32 ;
-- * la relation Locations en comporte 71.



----------------------------------------------------------------------------------------------------------------------------------------------------------------


---------------------
-- Compléments SQL --
---------------------


-- Sélection simple

-- q1, requête 1
SELECT numero_permis
FROM Clients
-- q1, requête 2
SELECT Clients.numero_permis
FROM Clients
-- q1, requête 3
SELECT C.numero_permis
FROM Clients AS C
-- q1, requête 4
SELECT DISTINCT numero_permis
FROM Clients

-- q2
SELECT DISTINCT immat_voiture
FROM Locations

-- q3
SELECT *
FROM Voitures

-- q4, requête 1
SELECT 10 / 3
-- q4, requête 2
SELECT LOWER ('AZErtY')
-- q4, requête 3
SELECT ABS (-4.2)

-- q5
SELECT prenom || ' ' || nom AS 'noms complets des clients'
FROM Clients


-- Filtrer les enregistrements

-- q6
SELECT *
FROM Clients
WHERE prenom = 'Dimitri' AND LENGTH(nom) <= 6 AND annee_naissance % 2 = 0

-- q7
SELECT *
FROM Clients
WHERE adresse IS NULL OR email IS NULL OR telephone IS NULL

-- q8
SELECT *
FROM Locations
WHERE date_debut LIKE '____-01-__'

-- q9
SELECT *
FROM Clients
WHERE LOWER(prenom) LIKE '%e___e%'


-- Formatage

-- q10, 3 clients les plus vieux
SELECT prenom || ' ' || nom AS 'client', 2025 - annee_naissance AS 'age'
FROM Clients
ORDER BY age DESC, client ASC
LIMIT 3

-- q11
SELECT *
FROM Voitures
ORDER BY prix_par_jour ASC
LIMIT 2
OFFSET 3


-- Opérations ensemblistes

-- q12
SELECT prenom AS 'nom qui sont aussi des prénoms'
FROM Clients
    INTERSECT
SELECT nom
FROM Clients

-- q13
SELECT immatriculation AS 'voitures jamais louées'
FROM Voitures
    EXCEPT
SELECT immat_voiture
FROM Locations

-- q14
SELECT immatriculation, nom -- 32 * 60 = 1920 lignes
FROM Voitures, Clients

-- q15
SELECT DISTINCT Loc1.permis_client AS 'clients ayant loué au moins 2 fois'
FROM Locations AS Loc1, Locations AS Loc2
WHERE Loc1.id <> Loc2.id AND Loc1.permis_client = Loc2.permis_client

-- q16
SELECT DISTINCT V1.marque AS 'voitures ayant au moins deux modèles différents'
FROM Voitures AS V1, Voitures AS V2
WHERE V1.marque = V2.marque AND V1.modele <> V2.modele


-- Fonctions d'agrégation

-- q17
SELECT MAX(nb_jours) AS 'durée de la plus longue location'
FROM Locations

-- q18
SELECT AVG(2025 - annee_naissance) AS 'age moyen des clients'
FROM Clients

-- q19
SELECT SUM(prix_par_jour) AS 'coût total par jour des voitures'
FROM Voitures

-- q20
SELECT COUNT(DISTINCT marque) AS 'nombre de marques différentes'
FROM Voitures

-- q21
SELECT SUM(nb_jours) AS 'nombre de jours où la voiture GH-963-TU a été louée'
FROM Locations
WHERE immat_voiture = 'GH-963-TU'

-- q22
SELECT COUNT(email) AS 'nombre de clients ayant renseigné leur email'
FROM Clients

-- q23
SELECT COUNT(numero_permis) AS 'nombre de clients lillois' -- ou COUNT(*)
FROM Clients
WHERE adresse LIKE 'Lille%'


-- Groupes

-- q24
SELECT immat_voiture, MAX(nb_jours) AS 'plus longue location'
FROM Locations
GROUP BY immat_voiture

-- q25
SELECT marque, modele, COUNT(immatriculation) AS 'nombre de voitures'
FROM Voitures
GROUP BY marque, modele

-- q26
SELECT prix_par_jour
FROM Voitures
GROUP BY prix_par_jour
HAVING COUNT(immatriculation) >= 2

-- q27
SELECT immat_voiture
FROM Locations
WHERE nb_jours >= 6
GROUP BY immat_voiture
HAVING COUNT(id) = 2

-- q28
SELECT permis_client
FROM Locations
WHERE date_debut LIKE '2024-%'
GROUP BY permis_client
HAVING AVG(nb_jours) >= 4

-- q29
SELECT marque
FROM Voitures
WHERE annee <= 2000
GROUP BY marque
HAVING COUNT(DISTINCT modele) >= 2


-- Jointures

-- q30
SELECT prenom, nom, marque, modele
FROM Clients
JOIN Locations ON Clients.numero_permis = Locations.permis_client
JOIN Voitures ON Voitures.immatriculation = Locations.immat_voiture

-- q31
SELECT *
FROM Voitures -- les voitures non louées sont associées à NULL dans le résultat
LEFT JOIN Locations ON Voitures.immatriculation = Locations.immat_voiture

-- q32
SELECT immatriculation, COUNT(id) AS 'nombre de locations' -- COUNT(id) = 0 si tous les id du groupe sont NULL
FROM Voitures
LEFT JOIN Locations ON Voitures.immatriculation = Locations.immat_voiture
GROUP BY immatriculation


-- Sous-requêtes

-- q33
SELECT COUNT(*) AS 'nombre de type de voitures différents'
FROM (	SELECT DISTINCT marque, modele
		FROM Voitures )
		
-- q34
SELECT immatriculation AS 'voitures plus jeunes que la moyenne'
FROM Voitures
WHERE annee > (	SELECT AVG(annee)
                FROM Voitures )

-- q35
SELECT marque AS 'marque ayant le plus de modèle différents', MAX(nb_modeles) AS 'nombre de modèles de cette marque'
FROM ( SELECT marque, COUNT(DISTINCT modele) AS 'nb_modeles'
       FROM Voitures
       GROUP BY marque )

-- q36
SELECT *
FROM Voitures
WHERE prix_par_jour < ( SELECT AVG(prix_par_jour) -- sous-requête obligatoire pour calculer la moyenne
                        FROM Voitures )

-- q37
SELECT SUM(min_prix_par_marque) AS 'argent gagné si les voitures les moins chères de chaque marque sont louées'
FROM ( SELECT MIN(prix_par_jour) AS 'min_prix_par_marque'
       FROM Voitures
       GROUP BY marque )

-- q38
-- il faut partir de la dernière requête imbriquée et "remonter" pour comprendre
SELECT immatriculation -- voitures coûtant le deuxième plus petit prix
FROM Voitures
WHERE prix_par_jour = ( SELECT MIN(prix) -- deuxième plus petit prix
                        FROM ( SELECT prix_par_jour AS prix -- voitures ne coûtant pas le plus petit prix
                               FROM Voitures
                               WHERE prix <> ( SELECT MIN(prix_par_jour) -- plus petit prix
                                               FROM Voitures )
                             )
                      )

-- q39
SELECT immatriculation
FROM Voitures
WHERE prix_par_jour = ( SELECT DISTINCT prix_par_jour -- deuxième plus petit prix
						FROM Voitures
						ORDER BY prix_par_jour ASC
						LIMIT 1
						OFFSET 1 )

-- q40
SELECT prenom, nom -- prénom et nom du client pour lequel
FROM Clients
JOIN Locations ON Clients.numero_permis = Locations.permis_client
GROUP BY permis_client
HAVING COUNT(id) = -- le nombre de locations de ce client est égal
	( SELECT MAX(nombre_locations) -- au nombre maximal de locations effectuées
	  FROM ( SELECT COUNT(id) AS 'nombre_locations'
		     FROM Locations
		     GROUP BY permis_client )
    )

