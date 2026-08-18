# 07 — Les types de données

> Équivalent W3Schools : **C Data Types**, **Basic Data Types**, **Type Conversion**

En C, chaque variable a un type fixé à la déclaration, qui détermine **la place qu'elle occupe en
mémoire** et **les valeurs qu'elle peut contenir**.

## Les types de base

| Type | Taille typique | Contenu | Spécificateur |
|---|---|---|---|
| `char` | 1 octet | un caractère / un très petit entier (−128 à 127) | `%c` |
| `int` | 4 octets | entier (−2 147 483 648 à 2 147 483 647) | `%d` |
| `float` | 4 octets | décimal, ~6-7 chiffres significatifs | `%f` |
| `double` | 8 octets | décimal, ~15 chiffres significatifs | `%lf` |

```c
int   annee = 2026;
float note = 15.5f;
double pi = 3.141592653589793;
char  grade = 'A';
```

## Les modificateurs

On combine les types de base avec `short`, `long`, `signed`, `unsigned` :

| Type | Taille min. | Plage | Spécificateur |
|---|---|---|---|
| `short int` | 2 octets | −32 768 … 32 767 | `%hd` |
| `unsigned short` | 2 octets | 0 … 65 535 | `%hu` |
| `unsigned int` | 4 octets | 0 … 4 294 967 295 | `%u` |
| `long int` | **dépend du système** (voir ci-dessous) | — | `%ld` |
| `long long int` | 8 octets | ±9,2 × 10¹⁸ | `%lld` |
| `unsigned long long` | 8 octets | 0 … 1,8 × 10¹⁹ | `%llu` |
| `long double` | dépend du système | très grande précision | `%Lf` |

`unsigned` = « sans signe » : pas de valeurs négatives, mais deux fois plus de valeurs positives.

## ⚠️ `long` ne fait pas la même taille sous Linux et sous Windows

C'est le piège de portabilité numéro un du C, et il concerne directement ce parcours :

| Type | Linux / WSL 64 bits (**LP64**) | Windows 64 bits (**LLP64**) |
|---|---|---|
| `int` | 4 octets | 4 octets |
| `long` | **8 octets** | **4 octets** |
| `long long` | 8 octets | 8 octets |
| pointeur (`int *`) | 8 octets | 8 octets |
| `long double` | 16 octets | 16 octets sous MinGW, 8 sous MSVC |

Conséquence concrète : un programme qui stocke une grande valeur dans un `long` marche sous Linux
et **déborde silencieusement** sous Windows.

```c
long grand = 3000000000L;    // OK sous Linux (8 octets), deborde sous Windows (4 octets)
```

Les trois réflexes :

1. Si tu veux « au moins 64 bits », écris **`long long`**, jamais `long`.
2. Mieux : utilise les types de largeur fixe de `<stdint.h>`, identiques partout —
   `int32_t`, `int64_t`, `uint64_t`… Ce sont eux qu'on utilise dans le vrai code portable.
3. Ne suppose **jamais** une taille : demande-la à `sizeof`.

```c
#include <stdint.h>
#include <inttypes.h>

int64_t grand = 3000000000;
printf("%" PRId64 "\n", grand);    // PRId64 : le bon specificateur, sur les deux systemes
```

## Connaître la taille réelle : `sizeof`

Les tailles dépendent de la machine. `sizeof` te donne la vérité, en octets :

```c
printf("char   : %zu octets\n", sizeof(char));
printf("int    : %zu octets\n", sizeof(int));
printf("float  : %zu octets\n", sizeof(float));
printf("double : %zu octets\n", sizeof(double));
```

`%zu` est le spécificateur du type `size_t`, celui que renvoie `sizeof`.

Les valeurs limites exactes sont dans `<limits.h>` (entiers) et `<float.h>` (décimaux) :

```c
#include <limits.h>
printf("int max : %d\n", INT_MAX);   // 2147483647
printf("int min : %d\n", INT_MIN);
```

## `float` ou `double` ?

- `double` est le type décimal **par défaut** en C : `3.14` est un `double`, `3.14f` est un `float`.
- Utilise `double` sauf si tu as une raison précise (mémoire très limitée, gros tableaux).
- Les deux sont **imprécis** : `0.1 + 0.2 != 0.3` en C comme en JavaScript. Ne compare jamais
  deux décimaux avec `==` ; compare la valeur absolue de leur différence à un petit seuil.

## Le type `char` est un entier

Un `char` stocke en réalité un **code numérique** (ASCII) :

```c
char lettre = 'A';
printf("%c\n", lettre);   // A
printf("%d\n", lettre);   // 65   ← le code ASCII de 'A'

char suivante = 'A' + 1;
printf("%c\n", suivante); // B
```

C'est pour ça que `'a' - 'A' == 32` permet de passer d'une majuscule à une minuscule.

> ⚠️ `'A'` (apostrophes) est un caractère. `"A"` (guillemets) est une **chaîne** de 2 octets :
> `'A'` et le marqueur de fin `'\0'`. Ce n'est pas la même chose.

## La conversion de types

### Conversion implicite (automatique)

Le compilateur convertit tout seul vers le type « le plus large » :

```c
int   a = 9;
float b = a;          // int -> float, sans perte : 9.0
printf("%f\n", b);    // 9.000000
```

Mais dans l'autre sens, il y a **perte** :

```c
float x = 9.99f;
int   y = x;          // float -> int : la partie decimale est TRONQUEE (pas arrondie)
printf("%d\n", y);    // 9
```

### Le piège de la division entière

C'est **l'erreur numéro un** des débutants en C :

```c
int a = 5, b = 2;
printf("%d\n", a / b);        // 2   ← et pas 2.5 !
```

Deux entiers divisés donnent un entier. Même ceci ne suffit pas :

```c
float r = 5 / 2;              // le calcul se fait en entier AVANT l'affectation
printf("%f\n", r);            // 2.000000
```

### Conversion explicite (le *cast*)

On force le type avec `(type)` devant la valeur :

```c
int a = 5, b = 2;
float r = (float) a / b;      // a devient 5.0, la division est decimale
printf("%.2f\n", r);          // 2.50
```

Autre exemple typique — un pourcentage :

```c
int reussis = 7, total = 9;
float pct = (float) reussis / total * 100;
printf("%.1f %%\n", pct);     // 77.8 %
```

## Le dépassement de capacité (*overflow*)

```c
int grand = 2147483647;   // INT_MAX
grand = grand + 1;
printf("%d\n", grand);    // -2147483648  ← il « boucle »
```

En Python, un entier grandit indéfiniment. En C, il déborde silencieusement. À toi de choisir un
type assez large (`long long`) ou de vérifier tes bornes.

## Exemple complet

Fichier [`code/07_types.c`](code/07_types.c).

## Exercice

1. Affiche la taille de chaque type de base sur ta machine avec `sizeof`.
2. Écris un programme qui convertit une température en Celsius (`float`) vers Fahrenheit
   (`F = C * 9/5 + 32`). Attention au `9/5` : trouve pourquoi ça donne un mauvais résultat, et
   corrige avec un cast.

---
⬅️ [06 — Variables](06-variables.md) | ➡️ [08 — Constantes](08-constantes.md)
