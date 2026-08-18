# 11 — Les conditions : if… else

> Équivalent W3Schools : **C If...Else**, **Short Hand If Else**

## `if`

```c
if (condition) {
    // execute si la condition est vraie (differente de 0)
}
```

```c
if (20 > 18) {
    printf("20 est plus grand que 18\n");
}
```

Avec des variables :

```c
int x = 20, y = 18;
if (x > y) {
    printf("x est plus grand que y\n");
}
```

## `else`

```c
int heure = 20;

if (heure < 18) {
    printf("Bonne journee\n");
} else {
    printf("Bonne soiree\n");
}
```

## `else if`

```c
int heure = 22;

if (heure < 10) {
    printf("Bonjour\n");
} else if (heure < 20) {
    printf("Bonne journee\n");
} else {
    printf("Bonne soiree\n");
}
```

Les conditions sont testées **dans l'ordre** ; dès que l'une est vraie, les suivantes sont
ignorées. C'est pour ça que `heure < 20` n'a pas besoin de `&& heure >= 10`.

## La forme abrégée : l'opérateur ternaire

```c
variable = (condition) ? valeur_si_vrai : valeur_si_faux;
```

```c
int heure = 20;
printf("%s\n", (heure < 18) ? "Bonne journee" : "Bonne soiree");
```

Utile pour les cas courts. Dès que ça s'imbrique, repasse à un `if`.

## Les accolades sont facultatives… mais mets-les

```c
if (x > y)
    printf("plus grand\n");     // valide : une seule instruction
```

Piège classique :

```c
if (x > y)
    printf("ligne 1\n");
    printf("ligne 2\n");        // ⚠️ TOUJOURS executee, elle n'est pas dans le if !
```

L'indentation ment, le compilateur ne lit que la structure. **Mets toujours les accolades.**

Autre piège, le point-virgule fantôme :

```c
if (x > y);                     // ⚠️ le if se termine ici, corps vide
{
    printf("toujours affiche\n");
}
```

## Imbrication

```c
int age = 25;
int a_permis = 1;

if (age >= 18) {
    if (a_permis) {
        printf("Peut conduire\n");
    } else {
        printf("Majeur mais sans permis\n");
    }
} else {
    printf("Trop jeune\n");
}
```

Souvent, une condition combinée est plus lisible :

```c
if (age >= 18 && a_permis) { … }
```

## Le retour anticipé (*early return*)

Idiome très courant en C pour éviter les imbrications profondes :

```c
if (!fichier_ouvert) {
    printf("Erreur : impossible d'ouvrir le fichier\n");
    return 1;
}
// ici on sait que tout va bien, sans imbrication
```

## Exemple concret — un barème de notes

Fichier [`code/11_if_else.c`](code/11_if_else.c) :

```c
#include <stdio.h>

int main(void) {
    float note = 14.5f;

    if (note < 0 || note > 20) {
        printf("Note invalide\n");
    } else if (note >= 16) {
        printf("Tres bien\n");
    } else if (note >= 14) {
        printf("Bien\n");
    } else if (note >= 12) {
        printf("Assez bien\n");
    } else if (note >= 10) {
        printf("Passable\n");
    } else {
        printf("Insuffisant\n");
    }

    return 0;
}
```

Remarque l'ordre : du plus exigeant au moins exigeant. Si tu inversais, `note >= 10` capturerait
tout le monde.

## Exercice

1. Écris un programme qui compare deux nombres et affiche le plus grand, ou « égaux ».
2. Écris un programme qui donne l'état de l'eau selon la température : glace (≤ 0), liquide,
   vapeur (≥ 100).
3. Trouve le bug :
   ```c
   int code = 0;
   if (code = 1) { printf("acces autorise\n"); }
   ```

---
⬅️ [10 — Booléens](10-booleens.md) | ➡️ [12 — switch](12-switch.md)
