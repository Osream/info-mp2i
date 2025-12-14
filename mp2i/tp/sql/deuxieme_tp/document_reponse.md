# TP SQL 14/05

## I. Étude d'une base

Q1.

- Les relations sont `Villes`, `Musees`, `Oeuvres`, `Peintres` et `Pays`.

Q2/3/4/5.

🔑 primary key
◀️ foreign key

- `Villes`
  - 🔑 `id` : non null positive integer
  - `nom` : text
  - ◀️ `id_pays` : positive integer

- `Musees`
  - 🔑 `id` : non null positive integer
  - `nom` : text
  - ◀️ `id_ville` : positive integer

- `Oeuvres`
  - 🔑 id : non null positive integer
  - `nom` : text
  - ◀️ `id_peintre` : positive integer
  - ◀️ `id_musee` : positive integer

- `Peintres`
  - 🔑 `id` : non null positive integer
  - `nom` : text
  - `prenom` : text
  - `nom_commun` : text
  - ◀️ `id_pays` : positive integer
  - `annee_mort` : positive integer
  - `annee_naissance` : positive integer

- `Pays`
  - 🔑 `id` : non null positive integer
  - `nom` : text

Q6.

- Plusieurs peintres peuvent avoir le même prénom / nom. Il faut donc un attribut vérifiant la contrainte d'unicité.

Q7.

- Oui

Q8.

- Non

Q9.

- Oui

Q10.

- Non

Q11.

- Oui

Q12.

- Non

Q13

- Non

Q14.

- Oui

Q15.

- Oui

Q16.

- Oui
