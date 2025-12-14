# TP bases de données

## I. modèle relationnel

### 4. Schema relationnel

Q.23) Flemme de faire un dessin donc voici les schemas écrit.

- Clients : {🔑 __numero_premis__ = INTEGER, nom = TEXT, prenom = TEXT, annee_naissance = INTEGER, adresse = TEXT, email = TEXT, telephone = TEXT}
- Locations : {🔑 __id__ = INTEGER, 🔑 #permis_client (Clients.id) = INTEGER, 🔑 # immat_voiture (Voitures.id) = INTEGER, nb_jours = INTEGER, date_debut = TEXT}
- Voitures : {🔑 __immatriculation__ = INTEGER, marque = TEXT, model = TEXT, annee = INTEGER, prix_par_jour = REAL}

## II. Projections et Sélections

### 3 Quelques sélections

Q.6

```SQL
SELECT nom, prenom, annee_naissance
FROM Clients
WHERE prenom = 'Dimitri' AND annee_naissance % 2 = 0 AND LENGTH(nom) <= 6
```

Q.7

```SQL
SELECT nom
FROM Clients
WHERE telephone IS NULL OR email IS NULL OR adresse IS NULL;
```

Q.8

```SQL
SELECT *
FROM Locations
WHERE date_debut LIKE '%-01-%';
```

Q.9

```SQL
SELECT prenom
FROM Clients
WHERE LOWER(prenom) LIKE '%e___e%';
-- N'est pas totalement correcte plutôt utiliser LENGTH mais
```

### 4. Formatages

Q.11

```SQL
SELECT immatriculation, prix_par_jour, modele
FROM Voitures
ORDER BY prix_par_jour ASC 
LIMIT 2
OFFSET 3;
```

### 5. Opérations ensemblistes

Q.12.

```SQL
SELECT nom 
FROM Clients
INTERSECT 
SELECT prenom
FROM Clients;
```

Q.13

```SQL
SELECT immatriculation
FROM Voitures
EXCEPT
SELECT immat_voiture
FROM Locations;
```

Q.16

```SQL
SELECT DISTINCT Voit1.marque
FROM Voitures AS Voit1, Voitures AS Voit2
WHERE Voit1.modele <> Voit2.modele AND Voit1.marque = Voit2.marque;
```

### 6. Fonctions d'agrégation

Q.17

```SQL
SELECT MAX(nb_jours)
FROM Locations;
```

Q.18

```SQL
SELECT AVG(2025-annee_naissance)
FROM Clients;
```

Q.19

```SQL
SELECT SUM(prix_par_jour)
FROM Voitures;
```

Q.20

```SQL
SELECT COUNT(DISTINCT marque)
FROM Voitures;
```

Q.21

```SQL
SELECT SUM(nb_jours)
FROM Locations
WHERE immat_voiture = 'GH-963-TU';
```

Q.22

```SQL
SELECT COUNT(email)
FROM Clients;
```

Q.22

```SQL
SELECT COUNT(*)
FROM Clients
WHERE LOWER(adresse) LIKE 'lille%';
```

### 7. Groupes

Q.24

```SQL
SELECT immat_voiture, MAX(nb_jours)
FROM Locations
GROUP BY immat_voiture;
```

Q.25

```SQL
SELECT marque, COUNT(modele)
FROM Voitures
GROUP BY modele;
```

Q.26

```SQL
SELECT prix_par_jour
FROM Voitures
GROUP BY prix_par_jour 
HAVING COUNT(modele) >= 2;
```

Q.27

```SQL
SELECT immat_voiture
FROM Locations
WHERE nb_jours >= 6
GROUP BY immat_voiture 
HAVING COUNT() >= 2;
```

Q.28

```SQL
SELECT permis_client
FROM Locations
WHERE date_debut LIKE '2024%'
GROUP BY permis_client
HAVING AVG(nb_jours) >= 4;
```

// La suite du tp sera fait si j'ai pas la flemme
