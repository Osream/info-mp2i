# TD : Représentation des nombres

Seuls les résultats sont donnés dans ce corrigé, n'hésitez pas à venir me voir si vous avez une question concernant la méthodologie.

1. $`\overline{11001011111}^2 = 1631, \overline{240}^5 = 70, \overline{2A3F}^{16} = 10815`$

2. $`27 = \overline{11011}^2 = \overline{33}^8 = \overline{1B}^{16}, 149 = \overline{10010101}^2 = \overline{225}^8 = \overline{95}^{16}, 520 = \overline{1000001000}^2 = \overline{1010}^8 = \overline{208}^{16}`$

3. $`\overline{1 0100 0101 1110}^2 = \overline{12136}^8 = \overline{145E}^{16}`$

4. Sur $n$ bits, on peut représenter $`2^n`$ entiers naturels, le plus grand entier étant $`2^n-1`$. Sur un octet, on peut donc représenter les entiers naturels allant de 0 à 255.

5. $`\overline{1011 1101}^2 + \overline{1001 0111}^2 = \overline{101010100}^2, \overline{1011 1101}^2 \times \overline{1101}^2 = \overline{1001 1001 1001}^{2}`$

6. Une multiplication par 2 "décale" tous les bits d'un cran à gauche (avec un nouveau bit de poids faible 0). Plus généralement, une multiplication par $`2^k`$ ajoute $k$ bits de poids faibles valant 0.

7. $`0=\overline{00000000}^2, -1 = \overline{11111111}^2, 26 = \overline{00011010}^2, -52=\overline{11001100}^2, -79= \overline{10110001}^2`$

8. $`\overline{101101}^2 = -19, \overline{10001110}^2 = -18`$

9. Les entiers signés représentables sur $n$ bits vont de $`-2^{n-1}`$ (un 1 puis que des 0) à $`2^{n-1}-1`$ (un 0 puis que des 1). Sur un octet, on peut donc représenter les entiers relatifs allant de -128 à 127.

10. $`105.375 = \overline{1101001.011}^2 = \overline{1.101001011}^2\times2^6, 1.7 = \overline{1.1011001100\,1100...}^2, 98.15625 = \overline{1100010.00101}^2 = \overline{1.10001000101}^2\times 2^6`$

11. * Le décalage est de $`2^{5-1}-1=15`$.
    * Le nombre représenté par $`\overline{0\,10000\,1001001000}^2`$ est $`(+1)\times (1+2^{-1}+2^{-4}+2^{-7}) \times 2^{16-15} = 3.140625`$. On peut vérifier que c'est la meilleure approximation de $`\pi`$ pour cette représentation.
    * $`1.0 = \overline{0\,01111\,0000000000}^2, -1.0 = \overline{1\,01111\,0000000000}^2, 2.0=\overline{0\,10000\,0000000000}^2, 7.5=\overline{0\,10001\,1110000000}^2, -259.25 = \overline{1\,10111\,0000001101}^2`$
    * Le plus petit nombre strictement positif normalisé est représenté par $\overline{0\,00001\,0000000000}^2$, c'est donc $`2^{-14}`$. Le plus grand est représenté par $\overline{0\,11110\,1111111111}^2$, c'est donc $65504$.
    * Le plus petit nombre strictement supérieur à 1 est représenté par $\overline{0\,01111\,0000000001}^2$, c'est donc $1+2^{-10}$. Le $`\varepsilon-`$machine est donc $`2^{-10}`$.

12. Non, non, non, et non. Les réels non dyadiques sont représentés par le nombre dyadique le plus proche, donc aucun calcul sur les flottants n'est garanti de donner un résultat correct. Voir le cours [(https://framagit.org/JB_info/mp2i/-/blob/main/docs/cours/8_representation_nombres.md)](https://framagit.org/JB_info/mp2i/-/blob/main/docs/cours/8_representation_nombres.md) pour des exemples de codes avec divergences entre le résultat théorique et le flottant calculé par des programmes en C.

13. Voir question 9, avec $n = 63$ (architecture 64 bits) ou $n = 31$ (architecture 32 bits).

14. En précisant `unsigned`, on possède deux fois plus d'entiers positifs (voir questions 4 et 9).

15. Seules ces trois affirmations sont vraies :

    * $`\overline{110}^2 = \overline{10}^b`$ dans la base $b = 6$.
    * Tous les entiers naturels admettent une écriture binaire finie.
    * Si un réel admet une écriture binaire finie, alors il possède une écriture décimale finie.

    À titre informatif, cette question vient de sujets de concours.

**Pour aller plus loin**

16. $`\overline{102}^3 = 11 = \overline{11}^{12} = \overline{21}^{5}`$
17. $`192.168.1.28 = \overline{11000000.10101000.00000001.00011100}^{2} = \overline{C0.A8.01.1C}^{16}, 173.194.78.99 = \overline{10101101.11000010.01001110.01100011}^{2} = \overline{AD.C2.4E.63}^{16}`$
18. Si on ne tient pas compte de l'éventuel bit sortant, le résultat est correct si les entiers sont signés, et modulo $`2^4`$ s'ils sont non signés.
19. $`\overline0^2 − \overline0^2 = \overline0^2 , \overline1^2 − \overline0^2 = \overline1^2, \overline1^2 − \overline1^2 = \overline0^2 , \overline{10}^2 − \overline1^2 = \overline1^2 , \overline{100}^2 − \overline1^2 = \overline{11}^2, \overline{1000}^2 − \overline1^2 = \overline{111}^2, \overline{1011 1101}^2 − \overline{1001 0111}^2 = \overline{00100110}^2`$
20. $`\begin{array}{c|ccc} \times&0&1&2 \\\hline 0&0&0&0\\ 1&0&1&2 \\2&0&2&11\end{array}`$ donc $`\overline{1022}^3\times \overline{221}^3 = \overline{1012102}^3`$
21. J'utilise la syntaxe C pour les opérateurs bit à bit ici. Pour déterminer si $N$ est pair, il suffit de vérifier si $N \& 1$ vaut 0. Pour déterminer si $N$ est une puissance de 2, il faut vérifier si $N \& (N-1)$ vaut 0. Pour extraire le bit de poids $`2^k`$, il faut faire $`(N\texttt{>>}k) \& 1`$. Pour déterminer si $N$ est divisible par $`2^k`$, il suffit de vérifier si $`N\&((1<<k)-1)`$ vaut 0. Le quotient de la division euclidienne de $N$ par $`2^k`$ est $`N>>k`$ et le reste est $`N\&((1<<k)-1)`$.



---

Par *Justine BENOUWT*

Sous licence [*CC BY-NC-SA*](https://creativecommons.org/licenses/by-nc-sa/4.0/)

![CC BY-NC-SA](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)
