# 09 — Les opérateurs

> Équivalent W3Schools : **C Operators**, **Arithmetic**, **Assignment**, **Comparison**, **Logical**

## Opérateurs arithmétiques

| Opérateur | Nom | Exemple | Résultat |
|---|---|---|---|
| `+` | addition | `5 + 3` | `8` |
| `-` | soustraction | `5 - 3` | `2` |
| `*` | multiplication | `5 * 3` | `15` |
| `/` | division | `5 / 3` | `1` (entière !) |
| `%` | modulo (reste) | `5 % 3` | `2` |
| `++` | incrémentation | `x++` | `x` augmente de 1 |
| `--` | décrémentation | `x--` | `x` diminue de 1 |

### Le modulo `%`

Il donne le **reste** de la division entière. Très utile :

```c
if (n % 2 == 0) printf("pair\n");    // divisible par 2
printf("%d\n", 17 % 5);              // 2
```

⚠️ `%` ne fonctionne **qu'avec des entiers**. Pour les décimaux, utilise `fmod()` de `<math.h>`.

### Pré- et post-incrémentation

```c
int x = 5;
printf("%d\n", x++);   // affiche 5, PUIS x devient 6   (post)
printf("%d\n", x);     // 6

int y = 5;
printf("%d\n", ++y);   // y devient 6, PUIS affiche 6   (pre)
```

Conseil : dans une instruction seule (`x++;`) les deux sont identiques. Évite de mélanger `++` et
d'autres opérations dans la même expression — c'est illisible et parfois indéfini.

## Opérateurs d'affectation

| Opérateur | Équivaut à |
|---|---|
| `x = 5` | — |
| `x += 3` | `x = x + 3` |
| `x -= 3` | `x = x - 3` |
| `x *= 3` | `x = x * 3` |
| `x /= 3` | `x = x / 3` |
| `x %= 3` | `x = x % 3` |
| `x &= 3` | `x = x & 3` |
| `x \|= 3` | `x = x \| 3` |
| `x ^= 3` | `x = x ^ 3` |
| `x >>= 3` | `x = x >> 3` |
| `x <<= 3` | `x = x << 3` |

## Opérateurs de comparaison

Ils renvoient `1` (vrai) ou `0` (faux).

| Opérateur | Signification | Exemple |
|---|---|---|
| `==` | égal à | `x == y` |
| `!=` | différent de | `x != y` |
| `>` | supérieur | `x > y` |
| `<` | inférieur | `x < y` |
| `>=` | supérieur ou égal | `x >= y` |
| `<=` | inférieur ou égal | `x <= y` |

```c
int x = 5, y = 3;
printf("%d\n", x > y);    // 1
printf("%d\n", x == y);   // 0
```

> ⚠️ **Le piège absolu du C** : `=` (affectation) et `==` (comparaison).
> ```c
> if (x = 10) { … }   // affecte 10 a x, la condition vaut 10 -> TOUJOURS VRAIE
> if (x == 10) { … }  // ✅ compare
> ```
> gcc t'avertit avec `-Wall` (`suggest parentheses around assignment`). Lis les avertissements.
>
> Il n'y a **pas** de `===` en C : `==` compare bien les valeurs, sans conversion surprise comme
> en JavaScript.

## Opérateurs logiques

| Opérateur | Nom | Description |
|---|---|---|
| `&&` | ET | vrai si les deux sont vrais |
| `\|\|` | OU | vrai si au moins un est vrai |
| `!` | NON | inverse la valeur |

```c
int age = 20;
int a_permis = 1;

if (age >= 18 && a_permis) {
    printf("Peut conduire\n");
}
if (age < 18 || !a_permis) {
    printf("Ne peut pas conduire\n");
}
```

### Évaluation paresseuse (*short-circuit*)

Comme en JavaScript, `&&` et `||` s'arrêtent dès que le résultat est connu :

```c
if (p != NULL && p->valeur > 0)   // si p est NULL, la 2e partie n'est PAS evaluee
```

C'est un idiome de sécurité très fréquent en C. L'ordre compte.

## Opérateurs sur les bits

Le C manipule directement les bits — chose rare dans les langages de haut niveau.

| Opérateur | Nom | Exemple (`a=5` `0101`, `b=3` `0011`) |
|---|---|---|
| `&` | ET bit à bit | `a & b` → `0001` = 1 |
| `\|` | OU bit à bit | `a \| b` → `0111` = 7 |
| `^` | OU exclusif (XOR) | `a ^ b` → `0110` = 6 |
| `~` | NON bit à bit | `~a` → `-6` |
| `<<` | décalage à gauche | `a << 1` → `1010` = 10 (× 2) |
| `>>` | décalage à droite | `a >> 1` → `0010` = 2 (÷ 2) |

Usage courant : les **drapeaux** (flags).

```c
#define LECTURE  1   // 0001
#define ECRITURE 2   // 0010
#define EXEC     4   // 0100

int droits = LECTURE | ECRITURE;        // 0011
if (droits & ECRITURE) printf("Ecriture autorisee\n");
```

## L'opérateur ternaire

```c
int age = 20;
char *statut = (age >= 18) ? "majeur" : "mineur";
printf("%s\n", statut);
```

Identique à JavaScript. Pratique pour les cas courts, à éviter quand ça s'imbrique.

## `sizeof`

C'est aussi un opérateur (pas une fonction) :

```c
printf("%zu\n", sizeof(int));   // 4
```

## Priorité des opérateurs

De la plus forte à la plus faible (extrait utile) :

1. `()` `[]` `->` `.`
2. `!` `~` `++` `--` `+`/`-` unaires, `*` (déréférencement), `&` (adresse), `sizeof`, cast
3. `*` `/` `%`
4. `+` `-`
5. `<<` `>>`
6. `<` `<=` `>` `>=`
7. `==` `!=`
8. `&` puis `^` puis `|`
9. `&&` puis `||`
10. `?:`
11. `=` `+=` `-=` …
12. `,`

**Conseil pratique** : n'apprends pas ce tableau par cœur, mets des parenthèses. `(a & b) == 0`
et `a & (b == 0)` ne sont pas la même chose, et c'est le second que le C choisit par défaut —
source de bugs redoutés.

## Exercice

Écris un programme qui, pour un entier `n` donné, affiche : s'il est pair ou impair, son carré,
sa moitié en division entière, sa moitié en décimal, et le résultat de `n & 1`. Compare
`n % 2` et `n & 1`.

---
⬅️ [08 — Constantes](08-constantes.md) | ➡️ [10 — Booléens](10-booleens.md)
