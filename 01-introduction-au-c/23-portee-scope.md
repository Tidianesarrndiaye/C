# 23 — La portée (scope)

> Équivalent W3Schools : **C Scope**

La **portée** d'une variable, c'est la zone du code où elle existe et où on peut l'utiliser.

## Portée de bloc (variable locale)

Une variable déclarée dans un bloc `{ }` n'existe que dans ce bloc :

```c
int main(void) {
    int x = 10;
    printf("%d\n", x);      // ✅
    return 0;
}

void autre(void) {
    printf("%d\n", x);      // ❌ error: 'x' undeclared
}
```

Ça vaut pour n'importe quel bloc, pas seulement les fonctions :

```c
int main(void) {
    if (1) {
        int interne = 5;
        printf("%d\n", interne);   // ✅
    }
    printf("%d\n", interne);       // ❌ n'existe plus
    return 0;
}
```

Et pour les boucles :

```c
for (int i = 0; i < 5; i++) { … }
printf("%d\n", i);     // ❌ i est mort avec la boucle
```

> Différence importante avec Python : en Python, une variable créée dans un `if` ou un `for`
> survit après. En C, elle disparaît à l'accolade fermante. C'est comme `let` en JavaScript.

## Variables globales

Déclarées **en dehors** de toute fonction, elles sont visibles partout dans le fichier :

```c
#include <stdio.h>

int compteur = 0;         // globale

void incrementer(void) {
    compteur++;           // accessible
}

int main(void) {
    incrementer();
    incrementer();
    printf("%d\n", compteur);   // 2
    return 0;
}
```

Une globale non initialisée vaut **0** (contrairement à une locale, qui contient n'importe quoi).

### Pourquoi il faut les éviter

- N'importe quelle fonction peut la modifier → un bug peut venir de partout.
- Impossible de tester une fonction isolément.
- Impossible de savoir, en lisant une fonction, ce dont elle dépend vraiment.

**Règle : passe les valeurs en paramètres.** Réserve les globales aux constantes (`const`) et
aux rares états vraiment partagés (configuration, compteur de log…).

## L'occultation (*shadowing*)

Une variable locale du même nom **masque** la globale :

```c
int x = 100;          // globale

int main(void) {
    int x = 5;        // locale, masque la globale
    printf("%d\n", x);   // 5
    return 0;
}
```

Ça compile, mais c'est une source de confusion. `gcc -Wshadow` t'avertit.

## La durée de vie et le mot-clé `static`

Une variable locale est créée à l'entrée de la fonction et détruite à la sortie. `static` change
ça : la variable **survit** entre les appels, tout en restant privée à la fonction.

```c
void compter(void) {
    static int appels = 0;    // initialise UNE SEULE FOIS
    appels++;
    printf("Appel n°%d\n", appels);
}

int main(void) {
    compter();   // Appel n°1
    compter();   // Appel n°2
    compter();   // Appel n°3
    return 0;
}
```

Sans `static`, la fonction afficherait trois fois « Appel n°1 ».

### `static` au niveau du fichier

Sur une variable ou une fonction **globale**, `static` a un tout autre sens : il la rend
**invisible depuis les autres fichiers** du projet.

```c
static int compteur_interne = 0;    // privee a ce fichier .c
static void aide(void) { … }        // fonction privee
```

C'est l'équivalent C du « privé » : ce qui n'est pas destiné à être utilisé ailleurs devrait être
`static`.

## Les classes de stockage — récapitulatif

| Mot-clé | Effet |
|---|---|
| *(rien)* — `auto` | variable locale ordinaire, sur la pile |
| `static` (locale) | conserve sa valeur entre les appels |
| `static` (globale/fonction) | limitée au fichier courant |
| `extern` | déclare une variable définie dans **un autre fichier** |
| `register` | suggère de garder la variable dans un registre (obsolète, ignoré) |

### `extern` en pratique

`compteur.c`
```c
int total = 0;
```

`main.c`
```c
extern int total;    // "elle existe ailleurs"
```

## Où vit la mémoire ?

```
┌──────────────────┐
│      Pile        │  variables locales — auto-gerees, rapides, petites
│       ↓          │
│       ↑          │
│      Tas (heap)  │  malloc / free — a ta charge (chapitre 30)
├──────────────────┤
│  Données (BSS)   │  globales et static
├──────────────────┤
│      Code        │  les instructions du programme
└──────────────────┘
```

Un dépassement de la pile (récursion infinie, tableau local énorme) donne un **stack overflow**.

## Exercice

1. Écris une fonction avec un compteur `static` et vérifie qu'il progresse entre les appels.
2. Crée une globale, modifie-la depuis deux fonctions, puis réécris le même programme **sans**
   globale, en passant la valeur en paramètre. Compare la lisibilité.
3. Que vaut une variable locale non initialisée ? Une globale non initialisée ? Vérifie.

---
⬅️ [22 — Paramètres de fonction](22-parametres-de-fonction.md) | ➡️ [24 — Déclaration de fonction](24-declaration-de-fonction.md)
