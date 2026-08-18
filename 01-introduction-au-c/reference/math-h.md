# `<math.h>` — mathématiques

⚠️ **Compile toujours avec `-lm`** : `gcc prog.c -o prog -lm`

Toutes ces fonctions prennent et renvoient des `double` (des variantes suffixées `f` existent
pour `float` : `sqrtf`, `powf`…).

## Puissances et racines

| Fonction | Rôle |
|---|---|
| `sqrt(x)` | racine carrée |
| `cbrt(x)` | racine cubique |
| `pow(x, y)` | x^y |
| `hypot(x, y)` | `sqrt(x²+y²)` sans débordement |
| `exp(x)` | e^x |
| `log(x)` | logarithme naturel |
| `log10(x)` | logarithme base 10 |
| `log2(x)` | logarithme base 2 |

## Arrondis

| Fonction | `1.5` | `-1.5` |
|---|---|---|
| `ceil(x)` | `2` | `-1` |
| `floor(x)` | `1` | `-2` |
| `round(x)` | `2` | `-2` |
| `trunc(x)` | `1` | `-1` |

## Valeur absolue et reste

| Fonction | Rôle |
|---|---|
| `fabs(x)` | valeur absolue décimale |
| `fmod(x, y)` | reste de la division décimale |
| `fmin(x, y)` / `fmax(x, y)` | minimum / maximum |

## Trigonométrie (en **radians**)

`sin` `cos` `tan` · `asin` `acos` `atan` · `atan2(y, x)` · `sinh` `cosh` `tanh`

Conversion : `radians = degres * M_PI / 180.0`

## Constantes (extension GNU)

| Constante | Valeur |
|---|---|
| `M_PI` | 3.14159265358979323846 |
| `M_E` | 2.71828182845904523536 |
| `M_SQRT2` | √2 |

## Tests de valeurs spéciales

| Fonction | Rôle |
|---|---|
| `isnan(x)` | « not a number » (ex. `sqrt(-1)`) |
| `isinf(x)` | infini (ex. `1.0/0.0`) |
| `isfinite(x)` | ni NaN ni infini |

## Comparer des décimaux

```c
#define EPSILON 1e-9
if (fabs(a - b) < EPSILON) { /* egaux */ }
```

Ne compare **jamais** deux `double` avec `==`.
