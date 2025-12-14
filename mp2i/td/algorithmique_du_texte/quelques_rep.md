# TD algorithmique du texte

## II. Boyer-Moore

Q 17.

`cherchera` :

||c|h|e|r|a|
|:-:|:-:|:-:|:-:|:-:|:-:|
|0|-1|-1|-1|-1|-1|
|1|0|-1|-1|-1|-1|
|2|0|1|-1|-1|-1|
|3|0|1|2|-1|-1|
|4|0|1|2|3|-1|
|5|4|1|2|3|-1|
|6|4|5|2|3|-1|
|7|4|5|6|3|-1|
|8|4|5|6|7|-1|
|9|4|5|6|7|8|

Q 18.

```ALGO
J'ai recherché, tu recherchais et il recherchera encore.
chercher
```

```ALGO
J'ai recherché, tu recherchais et il recherchera encore.
   chercher
```

```ALGO
J'ai recherché, tu recherchais et il recherchera encore.
    chercher
```

.
.
.

```ALGO
J'ai recherché, tu recherchais et il recherchera encore.
                                       chercher
```

Q. 19.

```ALGO
aabbbababacaabbabacbaaacabaabababb
aababab

- On aplique ici la règle du mauvais caractère:
aabbbababacaabbabacbaaacabaabababb
 aababab

- On aplique ici la règle du mauvais caractère:
aabbbababacaabbabacbaaacabaabababb
  aababab

- Aucune règle ne s'applique, on avance de 1 :
aabbbababacaabbabacbaaacabaabababb
   aababab

- Règle du mauvais caractère :
aabbbababacaabbabacbaaacabaabababb
    aababab

- Règle du mauvais caractère :
aabbbababacaabbabacbaaacabaabababb
           aababab

- Règle du mauvais caractère :
aabbbababacaabbabacbaaacabaabababb
            aababab

- Règle du mauvais caractère :
aabbbababacaabbabacbaaacabaabababb
                   aababab

- Règle du bon suffixe :
aabbbababacaabbabacbaaacabaabababb
                       aababab

- Règle du mauvais caractère :
aabbbababacaabbabacbaaacabaabababb
                        aababab

- Règle du bon suffixe :
aabbbababacaabbabacbaaacabaabababb
                          aababab

-> OK
```
