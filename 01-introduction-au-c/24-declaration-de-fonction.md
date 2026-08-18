# 24 — Déclaration de fonction (prototypes)

> Équivalent W3Schools : **C Function Declaration**

## Le problème

Le compilateur C lit le fichier **de haut en bas**, une seule fois. Si tu appelles une fonction
avant de l'avoir définie, il ne la connaît pas :

```c
#include <stdio.h>

int main(void) {
    saluer();          // ❌ warning: implicit declaration of function 'saluer'
    return 0;
}

void saluer(void) {
    printf("Bonjour\n");
}
```

## La solution : séparer déclaration et définition

La **déclaration** (ou *prototype*) annonce la signature ; la **définition** contient le code.

```c
#include <stdio.h>

void saluer(void);              // ← declaration : le ; est obligatoire

int main(void) {
    saluer();                   // ✅ le compilateur sait a quoi s'attendre
    return 0;
}

void saluer(void) {             // ← definition
    printf("Bonjour\n");
}
```

## Anatomie d'un prototype

```c
int calculer_aire(int longueur, int largeur);
```

- type de retour, nom, types des paramètres, `;`.
- Les **noms** des paramètres sont facultatifs dans le prototype :
  ```c
  int calculer_aire(int, int);      // valide, mais moins lisible
  ```
  Garde-les : ils documentent l'ordre des arguments.

## Pourquoi c'est la bonne pratique

1. **Lisibilité** : en haut du fichier, on voit tout ce que le programme sait faire.
2. **Liberté d'organisation** : `main` peut être en premier, comme un sommaire.
3. **Fonctions mutuellement récursives** : `a()` appelle `b()` qui appelle `a()` — impossible
   sans prototypes.
4. **Vérification** : sans prototype, le compilateur ne peut pas contrôler les types des
   arguments. En C99 et après, l'appel implicite est d'ailleurs une erreur.

## Structure recommandée d'un fichier C

```c
/* 1. En-tete de fichier (commentaire) */

/* 2. Inclusions */
#include <stdio.h>
#include <stdlib.h>
#include "mon_module.h"

/* 3. Constantes et macros */
#define TAILLE_MAX 100

/* 4. Types (structs, enums) */
typedef struct { … } Etudiant;

/* 5. Prototypes */
float moyenne(const float notes[], int n);
void  afficher(const Etudiant *e);

/* 6. main */
int main(void) { … }

/* 7. Definitions des fonctions */
float moyenne(const float notes[], int n) { … }
void  afficher(const Etudiant *e) { … }
```

## Les fichiers d'en-tête (`.h`)

Quand le projet grandit, on met les prototypes dans un fichier `.h` partagé.

`geometrie.h`
```c
#ifndef GEOMETRIE_H          // garde d'inclusion
#define GEOMETRIE_H

float aire_rectangle(float longueur, float largeur);
float aire_cercle(float rayon);

#endif
```

`geometrie.c`
```c
#include "geometrie.h"

float aire_rectangle(float longueur, float largeur) { return longueur * largeur; }
float aire_cercle(float rayon)                      { return 3.14159f * rayon * rayon; }
```

`main.c`
```c
#include <stdio.h>
#include "geometrie.h"

int main(void) {
    printf("%.2f\n", aire_cercle(3.0f));
    return 0;
}
```

Compilation :

```bash
gcc -Wall -Wextra -std=c17 main.c geometrie.c -o programme
```

### La garde d'inclusion

`#ifndef GEOMETRIE_H / #define GEOMETRIE_H / #endif` évite qu'un en-tête inclus deux fois
(directement et via un autre en-tête) provoque des redéfinitions. **Mets-en une dans chaque
`.h`, sans exception.**

### Ce qui va où

| Dans le `.h` | Dans le `.c` |
|---|---|
| prototypes des fonctions publiques | définitions des fonctions |
| `typedef`, `struct`, `enum` partagés | fonctions `static` (privées) |
| `#define` partagés | variables globales |
| `extern` pour les globales partagées | tout le reste |

## Compilation séparée et `make`

Avec plusieurs fichiers, on compile chaque `.c` en `.o` puis on lie le tout — seuls les fichiers
modifiés sont recompilés :

```bash
gcc -c geometrie.c      # -> geometrie.o
gcc -c main.c           # -> main.o
gcc main.o geometrie.o -o programme
```

Un `Makefile` automatise ça :

```makefile
CC     = gcc
CFLAGS = -Wall -Wextra -std=c17

programme: main.o geometrie.o
	$(CC) main.o geometrie.o -o programme

main.o: main.c geometrie.h
	$(CC) $(CFLAGS) -c main.c

geometrie.o: geometrie.c geometrie.h
	$(CC) $(CFLAGS) -c geometrie.c

clean:
	rm -f *.o programme
```

⚠️ Dans un `Makefile`, l'indentation des commandes doit être une **tabulation**, pas des espaces.

Puis : `make` pour construire, `make clean` pour nettoyer.

## Exercice

1. Reprends un programme d'un chapitre précédent, mets tous les prototypes en haut et les
   définitions après `main`.
2. Découpe-le en `module.h`, `module.c`, `main.c` avec garde d'inclusion, et compile à la main.
3. Écris le `Makefile` correspondant et vérifie que `make` puis `make clean` fonctionnent.

---
⬅️ [23 — Portée (scope)](23-portee-scope.md) | ➡️ [25 — Récursivité](25-recursivite.md)
