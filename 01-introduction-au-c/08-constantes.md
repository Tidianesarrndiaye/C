# 08 — Les constantes

> Équivalent W3Schools : **C Constants**

Quand une valeur ne doit **jamais changer**, on la déclare constante. Le compilateur refusera
toute tentative de modification, ce qui transforme un bug potentiel en erreur de compilation.

## Le mot-clé `const`

```c
const int NOMBRE_JOURS = 7;
const float PI = 3.14159f;
const char SEPARATEUR = '-';
```

Tentative de modification :

```c
const int NOMBRE_JOURS = 7;
NOMBRE_JOURS = 8;   // ❌ error: assignment of read-only variable 'NOMBRE_JOURS'
```

### Toujours initialiser une `const`

```c
const int x;    // ❌ inutilisable : on ne pourra jamais lui donner de valeur
const int x = 15;   // ✅
```

### Convention

Les constantes s'écrivent traditionnellement en **MAJUSCULES**, pour les distinguer d'un coup
d'œil des variables :

```c
const int TAILLE_MAX = 100;
const float TAUX_TVA = 0.18f;
```

## Les macros `#define`

L'autre façon de définir une constante, historiquement la plus fréquente en C :

```c
#define PI 3.14159
#define TAILLE_MAX 100
#define NOM_APP "Mon programme"
```

C'est une directive du préprocesseur : avant compilation, **chaque occurrence du nom est
remplacée par le texte**. Remarque : pas de `=`, pas de `;`, pas de type.

```c
#include <stdio.h>
#define PI 3.14159

int main(void) {
    float rayon = 3.0f;
    float aire = PI * rayon * rayon;   // devient : 3.14159 * rayon * rayon
    printf("Aire : %.2f\n", aire);
    return 0;
}
```

### `const` ou `#define` ?

| | `const` | `#define` |
|---|---|---|
| Connu du compilateur | oui (a un type) | non (simple remplacement de texte) |
| Vérification de type | oui | non |
| Visible au débogueur | oui | non |
| Portée | respecte les blocs | tout le fichier à partir de la ligne |
| Peut définir une macro avec paramètres | non | oui |

**Recommandation moderne : préfère `const`.** Réserve `#define` aux tailles de tableaux (car en
C99/C17 un tableau de taille `const int` n'est pas un tableau de taille constante au sens strict)
et aux macros à paramètres.

```c
#define TAILLE 5
int notes[TAILLE];      // ✅ toujours valide
```

### Macro avec paramètres

```c
#define CARRE(x) ((x) * (x))
printf("%d\n", CARRE(4));    // devient ((4) * (4)) -> 16
```

⚠️ Les parenthèses sont indispensables. Sans elles :

```c
#define CARRE_MAUVAIS(x) x * x
CARRE_MAUVAIS(2 + 3)   // devient 2 + 3 * 2 + 3  =  11, et non 25 !
```

## `const` et pointeurs (aperçu)

Tu croiseras ces formes plus tard (chapitre 20) :

```c
const char *p;        // le CONTENU pointe est constant, p peut changer de cible
char * const p;       // p est constant, le contenu peut changer
const char * const p; // les deux sont constants
```

Le prototype `int printf(const char *format, ...)` utilise le premier : `printf` promet de ne
pas modifier la chaîne que tu lui donnes.

## Pourquoi c'est utile

```c
// ❌ Sans constante : que veut dire 0.18 ? Et si le taux change ?
float ttc = ht + ht * 0.18f;

// ✅ Avec constante : le nom explique, et une seule ligne a modifier
const float TAUX_TVA = 0.18f;
float ttc = ht + ht * TAUX_TVA;
```

On appelle « nombre magique » une valeur numérique brute perdue dans le code. Les constantes
les éliminent.

## Exercice

Écris un programme qui calcule le périmètre et l'aire d'un cercle, avec `PI` défini une seule
fois via `const`. Puis refais-le avec `#define` et compare.

---
⬅️ [07 — Types de données](07-types-de-donnees.md) | ➡️ [09 — Opérateurs](09-operateurs.md)
