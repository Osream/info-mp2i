# Chapitre 17 : Algorithmique du texte

> __Vocabulaire__
>
> Un __Alphabet__ $\Sigma$ est un ensemble fini non vide de caractères.
>
> Un __mot__ sur un alphabet est une suite de caractères. Le mot vide est noté $\varepsilon$
>
> L'ensemble des mots de longeur $n$ sur l'alphabet $\Sigma$ est noté $\Sigma ^n$ . L'ensemble des mots est noté $\Sigma ^*$ .
>
> La __concaténation__ de deux mots $m$ et $n$ sur le même alphabet $\Sigma$ , noté $m \cdot n$ est la suite composée des caractères de m puis de n.
>
> Un __préfixe__ d'un mot $m \in \Sigma ^*$ est un mot $p$ tel qu'il existe $n \in \Sigma ^*$ tel que $m = p \cdot n$ .
>
> Un __suffixe__ d'un mot $m \in \Sigma ^*$ est un mot $s$ tel qu'il existe $n \in \Sigma ^*$ tel que $m = n \cdot s$ .
>
> Un __facteur__ d'un mot $m \in \Sigma ^*$ est un mot $f$ tel qu'il existe $n \in \Sigma ^*$ et $n' \in \Sigma ^*$ tel que $m = n \cdot f \cdot n'$ .

- Proposition : Un mot de longeur $n$
  - $n+1$ préfixes
  - $n+1$ suffixes
  - au plus $1 + \frac{n(n+1)}{2}$ facteurs

> Algorithmique du texte regroupe tous les algos pour lesquelles la taille de l'alphabet est négligeable devant la taille des mots.

## I. Recherche

- Enoncé du pb :
  - Entrées :
    - deux mots $m$ et $t$ sur un alphabet $\Sigma ^*$ avec la taille de $m$ inférieure (souvent de beaucoup) à la taille de $t$ .
    - Sortie booléen indiquant si $m$ est un facteur de $f$ .

### 1. Rabin-Karp

- $\underline{\small{\text{Idée}}}$
  - À chaque indice de $t$ , on ne fait pas toutes les comparaisons, donc on ne parcourt pas tout $m$ . Pour cela, on utilise une fct de hachage et on compare leurs résultats : $O(1)$ car ce sont des entiers.

- $\underline{\small{\text{Principe de Rabin-Karp}}}$
  - On calcule l'emprunte (= résultat de la fonction de hachage) du motif $m$ et celle du préfixe de $t$ de la taille de $m$.
  - On compare les 2 empruntes
    - Si elles sont différentes, on calcule l'emprunte du texte facteur dans $t$ à l'indice suivant, et on continue
    - Sinon elles sont égales, on compare caractère par caractère $m$ avaec le facteur de $t$ . Soit c'est une colision, alors on passe au facteur suivant, soit on a trouvé $m$ .

$\underline{\small{\text{Exemple :}}}$

- $\Sigma = \{\small{\text{26 lettres minuscules}}\}$
- Fonction de hachage: $h(l{\scriptsize 1}, l{\scriptsize 2}, \dots, l{\scriptsize n}) = \sum_{i = 1}^{n} \small{\text{position de }} l{\scriptsize i} \small{\text{ dans }} \Sigma$

On recherche

- Motif : $m =$ `abc`
- Text : $t =$ `abacbbabca`

Application de Rabin-Karp

- Emprunte de $m$ : $h(m) = 1+2+3 = 6$
- Emprunte du 1er facteur $h(aba) = 4$ . Pas besoin de comparer.
- Emprunte du 2eme facteur $h(bac) = 6$ . On compare $m$ et `bac` => colision.
- Emprunte du 3eme facteur $h(acb) = 6$ . On compare $m$ et `bac` => colision.
- Emprunte du 4eme facteur $h(cbb) = 7$ . Pas besoin de comparer.
- Emprunte du 5eme facteur $h(bba) = 5$ . Pas besoin de comparer.
- Emprunte du 6eme facteur $h(bab) = 5$ . Pas besoin de comparer.
- Emprunte du 7eme facteur $h(abc) = 6$ . On compare $m$ et `abc` => on a trouvé.

Pour être efficace, il faur pouvoir calculer l'emprunte du facteur suivant en $O(1)$ à partir de l'emprunte du facteur actuel.

Avec une telle fonction de hachage, la complexité de Rabin-Karp est

- $2 \times O(n)$ pour le calcule des empruntes.
- La fonction de hachage utilisée par Rabin-Karp est $h(l{\scriptsize 1}, l{\scriptsize 2}, \dots, l{\scriptsize n}) = \sum_{i=1}^{n} l{\scriptsize i} \times b^{n-i} \space mod \space p$ avec $b$ >> taille de l'alphabet et $p$ entier permier choixi grand mais inférieur à la capacité des entiers.
  - Avec cette fonction la complexité de Rabin-Karp est garentie en $O(\small{\text{taille de m + taille de t}})$ .

### 2. Boyer-Moore

- $\underline{\small{\text{Idée}}}$
  - Ne pas tester tous les facteur du texte.

- $\underline{\small{\text{Principe de Boyer-Moore}}}$
  - Pour comparer le motif et un facteur du texte, on procède du dernier carctère vers le premier.
  - Au moment où une comparaison échoue, on étudie plusieurs règles de décalage, et le prochain facteur à regarder est donné par la meilleur règle.
    - La règles principale est __la règles du mauvais caractère__ . Si on utilise que celle-ci on parle de "version de Horspool".

- $\underline{\small{\text{Principe de Boyer-Moore-Horspool}}}$
  - On commence par construire la table de décalage du motif $m$ .
    - Tableaux à (taille de $m$ + 1) liges et à (nb de caractères de l'alphabter) colonnes.
    - Le coefficient ligne $l$ , colonne $c$ contient __l'indice de la dernière occurence__ de $c$ dans le préfixe de $m$ de taille $l$ ou __-1__s s'il n'y apparaît pas.

$\underline{\small{\text{Exemple}}}$

- $\Sigma = \{$a, b, c$\}$
- motif $m =$ `abaaa`

|a|b|c||
|:-:|:-:|:-:|:-:|
|-1|-1|-1|$\varepsilon$|
|0|-1|-1|`a`|
|0|1|-1|`ab`|
|2|1|-1|`aba`|
|3|1|-1|`abaa`|
|4|1|-1|`abaaa`|

- On parcourt les facteurs de $t$ , quand une comparaison échoue, on décale de $i -$ Table (ligne $i$ , colonne $c$) avec $i$ l'indice où la comparaison échoue et $c$ le caractère du texte pour lequel ça a échoué.

$\underline{\text{\small{Exemple}}} :$

- $m =$ `abaaa`
- $t =$ `abcaababbaabaaaa`

```algo
|a b c |a a| b |a |b| b a |a| b| a a a| a
|      |   |   |  | |     | |  |      |
|    x |   |   |  | |     | |  |      |
|a b a |a a|   |  | |     | |  |      |
       |       |  | |     | |  |      |
       |     x |  | |     | |  |      |
       |a b  a |a |a|     | |  |      |
               |  |       | |  |      |
               |  |   x   | |  |      |
               |a |b  a a |a|  |      |
                  |       |    |      |
                  |       |   x|      |
                  |a  b a |a  a|      |
                          |           |
                          |           |
                          |a  b  a a a| -> trouvé
```

- $\underline{\text{\small Complexité}}$ :
  - Construction de la table :
    - Le nombre de colonnes est négligeable donc on est en $O(\text{Taille de} \space n)$
  - Recherche :
    - $\newline$ Dans le pire des cas on décale de 1 à chaque fois, on est en : $\newline O(\text{\small Taille de} \space t \times \text{\small Taille de} \space m)$
    - Par contre, dans la version complète de Boyer-Moore est en : $\newline O(\text{\small Taille de} \space m + \text{\small Taille de} \space t)$
  
## II. Compression

> On se limite à la compression __sans perte__. On passe d'un mot $t \in \Sigma^*$. On veut construire deux algorithmes comp & decomp tels que : $decomp(comp(t)) = t$ .
>
> On souhaite également que pour les mots qui nous intéresse : $\text{Taille comp}(t) < \text{Taille de} t$

On va construire pour cela des __codes__ = suite de bits correspondant à la compression d'un mot de l'alphabet.

Les codes permettent de faire de la compression sans perte.

- Codes à __longueur fixe__ : même nombre de bits
- Codes __préfixe__ : aucun code n'est le préfixe d'un autre code.

### 1. Huffman

Donne un code préfixe (de compression sans perte)

- $\underline{\small{\text{Compression}}}$ :
  1. On compte pour chaque caractère de $t$ son nombre d'occurences.

  2. Construction de l'arbre de Huffman
     - Chaque caractère devient une feuille de poids son nombre d'occurence.
     - Tant qu'il reste plus d'un arbre, on sélectionne $2$ arbres de poids minimaux $a{\scriptsize 1}$ et $a{\scriptsize 2}$ de poids respectifs $p{\scriptsize 1}$ et $p{\scriptsize 2}$

  3. Construction du code : $\newline$
      À chaque caractère, on associe une suite bits construite en prenant le chemin de la racine au caractère et en $0$ pour un sous arbre gauche et $1$ pour un sous arbre droit.

  4. Construire la compression de $t$ en concaténant les codes de ses caractères

$\underline{\small{\text{Exemple}}}$

- $t =$ `scienceinformatique`

![image](ressources/chap_17/construction_arbre_huffman.png)

On en déduit les codes : `n = 000, a = 0010, f = 0011, m = 0100, o = 0101, q = 0110, r = 0111, s = 1000, t = 1001, e = 101, i = 110, u = 1110, c = 1111` .

Et donc le texte compréssé est `10001111110101000111110111000000110101011101000010100111001101110101` .

- $\underline{\small{\text{Décompression de Huffman}}}$
  - On travail en connaissant __l'arbre__ en plus du code compressé.
  - Principe:
    - On lit le texte bit pat bit en déscendant dans l'abre à gauche en 0 et à droite en 1. Arrivé à une feuille, on ajoure la lettre au texte et on repart de la racine

$\underline{\small{\text{Exemple}}}$

Avec l'arbre de Huffman ce-dessus, décompresser `0011011100100001111101` .

$$
\underbrace{0011}_\text{f} \space
\underbrace{0111}_\text{r} \space
\underbrace{0010}_\text{a} \space
\underbrace{000}_\text{n} \space
\underbrace{1111}_\text{c} \space
\underbrace{101}_\text{e}
$$

### 2. Lempel-Ziv-Welch

Très utilisé pour l'envoie de données.

Compression sans perte car code à longueur fixe.

- $\underline{\small{\text{Principe}}}$
  - On stocke les codes dans un tableau $T$.
    - Au départ, $T {\scriptsize i} = i$ pour $i \in \Sigma$
    - On lit le texte caractère par caractèren en conservant un "buffer" de caractères.
    - Si buffer $\cdot$ caractère lu $\in T$ on confinue la lecture.
    - Sinon, on l'ajoute à $T$ avec un nouveau code, on ajoute le code du buffer à la compression. on laisse juste le caractère lu dans le buffer.

$\underline{\small{\text{Exemple}}}$

![image](ressources/chap_17/lzw_compression/Image1_lzw.png)

![image](ressources/chap_17/lzw_compression/Image2_lzw.png)

![image](ressources/chap_17/lzw_compression/Image3_lzw.png)

![image](ressources/chap_17/lzw_compression/Image4_lzw.png)

![image](ressources/chap_17/lzw_compression/Image5_lzw.png)

![image](ressources/chap_17/lzw_compression/Image6_lzw.png)

![image](ressources/chap_17/lzw_compression/Image7_lzw.png)

![image](ressources/chap_17/lzw_compression/Image8_lzw.png)

![image](ressources/chap_17/lzw_compression/Image9_lzw.png)

![image](ressources/chap_17/lzw_compression/Image10_lzw.png)

![image](ressources/chap_17/lzw_compression/Image11_lzw.png)

- $\underline{\small{\text{Décompression}}}$
  - Le tableau $T$ des codes n'est pas stocké, on le reconstruit pendant la décompression.
  - On connait les codes de chaque caractère de l'alphabet
  - Quand on décompresse un mot, on ajoute au tableau $T$ une nouvelle entrée pour décompression précédente $\cdot$ 1er caractère de $m$

$\underline{\small{\text{Exemple}}}$

![image](ressources/chap_17/lzw_decompression/Imaged1_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged2_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged3_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged4_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged5_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged6_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged7_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged8_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged9_lzw.png)

![image](ressources/chap_17/lzw_decompression/Imaged10_lzw.png)

Quand on a un code que l'on ne connait pas, on prend la précédente lecture $\cdot$ premier caractère de la précédente lecture.
