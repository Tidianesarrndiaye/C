# 26 — Les fonctions mathématiques

> Équivalent W3Schools : **C Math Functions**

La bibliothèque standard fournit les fonctions mathématiques dans `<math.h>`.

```c
#include <math.h>
```

## ⚠️ L'édition de liens

Sur Linux, il faut **ajouter `-lm`** à la compilation, sinon tu obtiens
`undefined reference to 'sqrt'` :

```bash
gcc -Wall -Wextra -std=c17 prog.c -o prog -lm
```

Le `-lm` (*link math*) doit être placé **après** les fichiers source. C'est une erreur de
débutant très fréquente, et le message ne dit pas quoi faire.

## Les fonctions les plus utiles

| Fonction | Rôle | Exemple |
|---|---|---|
| `sqrt(x)` | racine carrée | `sqrt(16)` → `4.0` |
| `pow(x, y)` | x puissance y | `pow(2, 3)` → `8.0` |
| `fabs(x)` | valeur absolue (décimal) | `fabs(-4.7)` → `4.7` |
| `abs(x)` | valeur absolue (entier, `<stdlib.h>`) | `abs(-5)` → `5` |
| `ceil(x)` | arrondi au **supérieur** | `ceil(1.2)` → `2.0` |
| `floor(x)` | arrondi à l'**inférieur** | `floor(1.8)` → `1.0` |
| `round(x)` | arrondi au plus proche | `round(1.5)` → `2.0` |
| `trunc(x)` | tronque la partie décimale | `trunc(1.9)` → `1.0` |
| `fmod(x, y)` | modulo décimal | `fmod(7.5, 2)` → `1.5` |
| `exp(x)` | e^x | `exp(1)` → `2.718…` |
| `log(x)` | logarithme naturel | `log(M_E)` → `1.0` |
| `log10(x)` | logarithme base 10 | `log10(100)` → `2.0` |
| `sin` `cos` `tan` | trigonométrie (**en radians**) | `sin(M_PI/2)` → `1.0` |
| `asin` `acos` `atan` | trigonométrie inverse | |
| `atan2(y, x)` | angle d'un point | |
| `hypot(x, y)` | `sqrt(x²+y²)` sans débordement | |

Toutes ces fonctions prennent et renvoient des `double`.

```c
#include <stdio.h>
#include <math.h>

int main(void) {
    printf("%.2f\n", sqrt(64));        // 8.00
    printf("%.2f\n", pow(4, 3));       // 64.00
    printf("%.2f\n", ceil(1.4));       // 2.00
    printf("%.2f\n", floor(1.4));      // 1.00
    printf("%.2f\n", fabs(-7.25));     // 7.25
    return 0;
}
```

## Les constantes

`<math.h>` définit `M_PI`, `M_E`, `M_SQRT2`… Elles ne sont pas dans la norme stricte, mais gcc
les fournit :

```c
printf("%.5f\n", M_PI);    // 3.14159
```

⚠️ Avec `-std=c17` (norme stricte), gcc les **retire** : tu obtiens `error: 'M_PI' undeclared`.
Deux solutions — compiler en `-std=gnu17`, ou définir la tienne avec un repli :

```c
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
```

C'est ce que fait [`code/26_math.c`](code/26_math.c).

## Les nombres aléatoires

Ils sont dans `<stdlib.h>`, pas dans `<math.h>` :

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));            // initialise le generateur UNE SEULE FOIS

    int n = rand() % 100 + 1;     // entier entre 1 et 100
    printf("%d\n", n);
    return 0;
}
```

- `rand()` renvoie un entier entre 0 et `RAND_MAX`.
- `rand() % n` donne 0…n-1 ; `+ 1` décale vers 1…n.
- **Sans `srand(time(NULL))`, la suite est identique à chaque exécution** (utile pour déboguer,
  gênant pour un jeu).
- `srand` ne s'appelle **qu'une fois**, au début de `main`.

Pour un décimal entre 0 et 1 : `(double) rand() / RAND_MAX`.

## Les pièges de la virgule flottante

```c
printf("%d\n", 0.1 + 0.2 == 0.3);   // 0 — FAUX !
```

Les `float` et `double` sont des approximations binaires. **Ne compare jamais deux décimaux avec
`==`** ; compare l'écart à une tolérance :

```c
#define EPSILON 1e-9
if (fabs(a - b) < EPSILON) { … }
```

Autres valeurs spéciales :

```c
printf("%f\n", sqrt(-1.0));    // nan  (not a number)
printf("%f\n", 1.0 / 0.0);     // inf
if (isnan(x)) { … }
if (isinf(x)) { … }
```

## Exemple concret

Fichier [`code/26_math.c`](code/26_math.c) :

```c
#include <stdio.h>
#include <math.h>

int main(void) {
    // Distance entre deux points
    double x1 = 0, y1 = 0, x2 = 3, y2 = 4;
    double d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    printf("Distance : %.2f\n", d);            // 5.00

    // Hypotenuse (plus sur que la formule ci-dessus)
    printf("Hypotenuse : %.2f\n", hypot(3, 4));

    // Aire et perimetre d'un cercle
    double r = 5.0;
    printf("Aire   : %.4f\n", M_PI * r * r);
    printf("Perim. : %.4f\n", 2 * M_PI * r);

    // Interets composes : 100000 FCFA a 5 %% pendant 10 ans
    double capital = 100000, taux = 0.05;
    printf("Capital final : %.2f FCFA\n", capital * pow(1 + taux, 10));

    return 0;
}
```

```bash
gcc -Wall -Wextra -std=c17 code/26_math.c -o /tmp/prog -lm && /tmp/prog
```

## Exercice

1. Calcule les racines d'une équation du second degré `ax² + bx + c = 0` (attention au
   discriminant négatif).
2. Convertis des coordonnées polaires en cartésiennes (`x = r·cos θ`, `y = r·sin θ`).
3. Écris un jeu : le programme tire un nombre entre 1 et 100, l'utilisateur devine, le programme
   répond « plus grand » ou « plus petit ».
4. Vérifie que `0.1 + 0.2 != 0.3` et affiche `0.1 + 0.2` avec `%.20f`.

---
⬅️ [25 — Récursivité](25-recursivite.md) | ➡️ [27 — Fichiers](27-fichiers.md)
