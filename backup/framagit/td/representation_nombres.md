# TD : Représentation des nombres

1. Quel est l'entier naturel représenté par $`\overline{11001011111}^2`$ ? $`\overline{240}^5`$ ? $`\overline{2A3F}^{16}`$ ?
2. Quelle est l'écriture en base 2, 8 et 16 des entiers naturels 27, 149 et 520 ?
3. Comment s'écrit $`\overline{1010001011110}^2`$ en octal ? en hexadécimal ?
4. Combien d'entiers naturels peut-on représenter sur 1 octet ? Quel est le plus grand entier représentable ?
5. Calculez, en les posant, $`\overline{1011 1101}^2 + \overline{1001 0111}^2`$ puis $`\overline{1011 1101}^2 \times \overline{1101}^2`$. Vérifiez en convertissant en décimal.
6. Quel est l’effet sur l’écriture binaire d’une multiplication par 2 ? Par une puissance de 2 ?
7. En complément à 2 sur 1 octet, quelle sont les écritures de 0, -1, 26, -52 et -79 ?
8. Quel est l'entier dont la représentation en complément à 2 est $`\overline{101101}^2`$ ? $`\overline{10001110}^2`$ ?
9. Quels sont les plus petit et plus grand entiers signés représentables sur 1 octet ? Donnez leurs écritures.
10. Quelles sont les écritures à virgule flottante de $`105.375, 1.7 \text{ et } 98.15625`$ ?
11. On considère une représentation des nombres flottants sur 16 bits : 1 bit pour le signe, 5 bits pour l'exposant, 10 bits pour la mantisse.
    * Que vaut le décalage de l'exposant ?
    * Quel nombre est représenté par $`\overline{0\,10000\,1001001000}^2`$ ?
    * Quelles sont les représentation de 1.0, -1.0, 2.0, 7.5 et -259.25 ?
    * Quelles sont les représentations machine et les valeurs des plus petit et plus grand nombres strictement positifs (normalisés) représentables ?
    * Quel est (valeur et représentation) le plus petit nombre strictement supérieur à 1 représentable ? Quel est donc le $`\varepsilon`$-machine ?
12. L'addition flottante est-elle associative ? Et la multiplication flottante ? L'égalité flottante est-elle réflexive ? La multiplication flottante est-elle distributive sur l’addition flottante ?
13. En OCaml, un bit de la représentation est réservé au fonctionnement interne du ramasse-miettes. Quel est donc le plus grand entier représentable sur une machine d'architecture 64 bits ? 32 bits ?
14. Quel est l'intérêt en C de préciser `unsigned` si on sait qu'on ne travaillera qu'avec des entiers non signés ?
15. Parmi les affirmations suivantes, lesquelles sont vraies ?
    * un entier signé représenté en binaire par complément à 2 qui se termine par 1 est pair
    * $`\overline{110}^2 = \overline{10}^b`$ dans une certaine base $`b\leqslant 10`$
    * tous les entiers naturels admettent une écriture binaire finie
    * tous les réels admettent une écriture binaire finie
    * si un réel admet une écriture décimale finie, alors il possède une écriture binaire finie
    * si un réel admet une écriture binaire finie, alors il possède une écriture décimale finie
    * l'utilisation de flottants peut provoquer des erreurs d'arrondis, mais celles-ci sont négligeables car l'erreur est minime
    * pour ne pas avoir d'erreurs d'arrondis, il suffit de coder les flottants sur 64 bits plutôt que 32

**Pour aller plus loin**

16. Comment s'écrit $`\overline{102}^3`$ en base 12? en base 5 ?
17. Les adresse IPv4 sont codées sur 4 octets. Par exemple : 192.168.1.28 (réseau local) est une adresse IPv4. Donnez l’écriture en binaire et en hexadécimal de cette adresse. Même question avec 173.194.78.99 (Google).
18. Posez les additions binaires suivantes : $`\overline{1011}^2+\overline{0111}^2, \overline{1001}^2+\overline{0011}^2,\overline{1001}^2+\overline{1011}^2,\overline{0101}^2+\overline{0011}^2`$. Interprétez ces additions comme des opérations sur des entiers non signés de 4 bits (on ne garde donc que les quatre bits les moins significatifs du résultat). Mathématiquement, cela revient à faire quoi ? Et en faisant une interprétation signée cette fois ?
19. Calculez $`\overline0^2 − \overline0^2 , \overline1^2 − \overline0^2 , \overline1^2 − \overline1^2 , \overline{10}^2 − \overline1^2 , \overline{100}^2 − \overline1^2 , \overline{1000}^2 − \overline1^2`$. Calculez ensuite $`\overline{1011 1101}^2 − \overline{1001 0111}^2`$.
20. Donnez les tables de multiplication en base 3. Effectuez alors la multiplication $`\overline{1022}^3\times \overline{221}^3`$.
21. On considère un entier non signé $`N`$ sur $`n`$ bits. En utilisant les opérateurs bit à bit, comment déterminer si $`N`$ est pair ? Comment déterminer si $`N`$ est une puissance de 2 ? Avec $`k \leq n`$, comment extraire le bit de poids $`2^k`$ ? Comment déterminer si $`N`$ est divisible par $`2^k`$ ? Comment récupérer le quotient et le reste de la division de $`N`$ par $`2^k`$ ?

---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BYNCSA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
