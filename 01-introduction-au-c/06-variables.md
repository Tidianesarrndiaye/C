# 06 — Les variables

> Équivalent W3Schools : **C Variables**, **Format Specifiers**, **Change Values**,
> **Multiple Variables**, **Variable Names**, **Real-Life Examples**

Une variable est un **conteneur nommé** pour une valeur stockée en mémoire.

## Déclarer une variable

En C, il faut **annoncer le type** avant le nom. C'est la grande différence avec Python et
JavaScript.

```c
type nom = valeur;
```

```c
int  age = 25;              // un entier
float taille = 1.82;        // un nombre a virgule
char initiale = 'T';        // un seul caractere (guillemets SIMPLES)
```

On peut aussi déclarer d'abord et affecter ensuite :

```c
int age;        // declaration
age = 25;       // affectation
```

> ⚠️ **Une variable déclarée sans valeur ne vaut pas 0.** Elle contient ce qui traînait en
> mémoire à cet endroit : n'importe quoi. Lire une variable non initialisée est un bug classique
> du C. Prends l'habitude d'initialiser tout de suite : `int age = 0;`

## Afficher une variable : les spécificateurs de format

`printf` a besoin de savoir **quel type** elle doit afficher :

```c
int age = 25;
printf("%d\n", age);
```

| Spécificateur | Type | Exemple |
|---|---|---|
| `%d` ou `%i` | `int` | `42` |
| `%u` | `unsigned int` | `42` |
| `%f` | `float` / `double` | `1.820000` |
| `%.2f` | idem, 2 décimales | `1.82` |
| `%e` | notation scientifique | `1.820000e+00` |
| `%c` | `char` | `T` |
| `%s` | chaîne de caractères | `Tidiane` |
| `%p` | pointeur / adresse | `0x7ffd…` |
| `%ld` | `long` | `1234567890` |
| `%lld` | `long long` | — |
| `%lf` | `double` (avec `scanf`) | — |
| `%x` | entier en hexadécimal | `2a` |
| `%%` | un caractère `%` littéral | `%` |

On peut en mettre plusieurs, dans l'ordre des arguments :

```c
int age = 25;
float taille = 1.82;
printf("Age : %d — Taille : %.2f m\n", age, taille);
```

> ⚠️ Si le spécificateur ne correspond pas au type passé, il n'y a **pas d'erreur à l'exécution**,
> juste un affichage absurde. `gcc -Wall` t'avertit — encore une raison de compiler avec.

## Changer la valeur

```c
int age = 25;
age = 26;              // on ecrase l'ancienne valeur
printf("%d\n", age);   // 26
```

Attention, on ne redéclare pas :

```c
int age = 25;
int age = 26;   // ❌ erreur : redefinition of 'age'
age = 26;       // ✅
```

Une variable peut aussi recevoir la valeur d'une autre :

```c
int a = 10;
int b = a;      // b vaut 10, c'est une COPIE
a = 99;         // b vaut toujours 10
```

## Déclarer plusieurs variables

```c
int x = 5, y = 6, z = 50;
printf("%d\n", x + y + z);   // 61
```

Même valeur pour plusieurs variables :

```c
int x, y, z;
x = y = z = 50;
```

## Les règles de nommage

Un nom de variable (un *identificateur*) doit :

- commencer par une **lettre** ou un **underscore** `_` (jamais par un chiffre) ;
- ne contenir que des lettres, des chiffres et des `_` (pas d'espace, pas d'accent, pas de `-`) ;
- ne pas être un **mot-clé réservé** du C (`int`, `if`, `return`, `while`… voir
  [`reference/mots-cles-c.md`](reference/mots-cles-c.md)) ;
- être **unique** dans sa portée.

Le C est **sensible à la casse** : `total`, `Total` et `TOTAL` sont trois variables différentes.

### Conventions courantes en C

| Style | Exemple | Usage habituel |
|---|---|---|
| `snake_case` | `nombre_etudiants` | variables et fonctions (le plus courant en C) |
| `MAJUSCULES` | `TAILLE_MAX` | constantes et macros |
| `camelCase` | `nombreEtudiants` | possible, plus rare en C pur |

Choisis des noms qui parlent : `m` ne veut rien dire, `moyenne` oui.

## Exemple concret

Fichier [`code/06_variables.c`](code/06_variables.c) :

```c
#include <stdio.h>

int main(void) {
    // Calcul du prix TTC d'un article
    float prix_ht = 15000.0f;   // en FCFA
    float taux_tva = 0.18f;     // 18 %
    float tva = prix_ht * taux_tva;
    float prix_ttc = prix_ht + tva;

    printf("Prix HT  : %.2f FCFA\n", prix_ht);
    printf("TVA 18%%  : %.2f FCFA\n", tva);
    printf("Prix TTC : %.2f FCFA\n", prix_ttc);

    // Aire d'un rectangle
    int longueur = 4;
    int largeur = 6;
    int aire = longueur * largeur;
    printf("\nAire du rectangle : %d\n", aire);

    return 0;
}
```

Remarque le `%%` : pour afficher un vrai `%`, il faut le doubler.

## Exercice

1. Déclare `nom_etudiant` (un `char` pour l'initiale), trois notes en `float`, et calcule la
   moyenne. Affiche-la avec une seule décimale.
2. Que se passe-t-il si tu affiches un `float` avec `%d` ? Essaie, lis l'avertissement de gcc.

---
⬅️ [05 — Commentaires](05-commentaires.md) | ➡️ [07 — Types de données](07-types-de-donnees.md)
