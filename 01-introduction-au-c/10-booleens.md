# 10 — Les booléens

> Équivalent W3Schools : **C Booleans**

## Le C n'a pas de vrai type booléen (historiquement)

En C, **tout entier différent de zéro est vrai, et zéro est faux**. C'est tout.

```c
if (1)  printf("vrai\n");     // s'affiche
if (0)  printf("faux\n");     // ne s'affiche pas
if (-5) printf("aussi vrai\n"); // s'affiche : -5 != 0
```

Les comparaisons renvoient `1` ou `0` :

```c
int x = 10, y = 9;
printf("%d\n", x > y);    // 1
printf("%d\n", x == y);   // 0
```

C'est pour ça qu'on écrit souvent un booléen comme un `int` :

```c
int est_connecte = 1;   // vrai
int a_paye = 0;         // faux
```

## `<stdbool.h>` : le type `bool` (C99 et après)

Depuis C99, on peut utiliser un vrai type booléen en incluant `<stdbool.h>` :

```c
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    bool majeur = true;
    bool inscrit = false;

    printf("%d\n", majeur);    // 1
    printf("%d\n", inscrit);   // 0

    if (majeur && !inscrit) {
        printf("Majeur mais pas encore inscrit\n");
    }
    return 0;
}
```

- `true` vaut `1`, `false` vaut `0`.
- Il n'y a **pas** de spécificateur `%b` : on affiche un `bool` avec `%d`.
- Un `bool` ne peut contenir que 0 ou 1 : `bool b = 42;` stocke `1`.

Pour afficher du texte :

```c
printf("%s\n", majeur ? "vrai" : "faux");
```

> Note : en C23, `bool`, `true` et `false` sont devenus des mots-clés du langage, sans `#include`.
> Mais avec `-std=c17`, garde `#include <stdbool.h>`.

## Exemple concret

```c
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int age = 20;
    int solde = 15000;
    int prix = 20000;

    bool est_majeur = (age >= 18);
    bool peut_payer = (solde >= prix);

    printf("Majeur      : %s\n", est_majeur ? "oui" : "non");
    printf("Peut payer  : %s\n", peut_payer ? "oui" : "non");

    if (est_majeur && peut_payer) {
        printf("Achat autorise\n");
    } else {
        printf("Achat refuse\n");
    }
    return 0;
}
```

## Le piège venant de Python et JavaScript

En Python, `if ma_liste:` est faux pour une liste vide. En JavaScript, `""`, `null`, `undefined`,
`NaN` et `0` sont *falsy*. **Rien de tout ça n'existe en C.**

```c
char nom[] = "";
if (nom) { … }        // TOUJOURS VRAI : c'est l'adresse du tableau, jamais nulle
if (nom[0] == '\0') { … }   // ✅ la bonne facon de tester « chaine vide »
```

Retiens : en C, seule la **valeur numérique zéro** est fausse (et le pointeur `NULL`, qui vaut 0).

## Convention de nommage

Nomme tes booléens comme des questions à réponse oui/non :

```c
bool est_valide;
bool a_termine;
bool fichier_ouvert;
```

## Exercice

Écris un programme qui détermine si une année est bissextile, en stockant le résultat dans un
`bool`. Règle : divisible par 4, **sauf** les années divisibles par 100 qui ne le sont pas, **sauf**
celles divisibles par 400 qui le sont.

---
⬅️ [09 — Opérateurs](09-operateurs.md) | ➡️ [11 — if… else](11-if-else.md)
