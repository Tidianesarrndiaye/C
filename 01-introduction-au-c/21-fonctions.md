# 21 — Les fonctions

> Équivalent W3Schools : **C Functions**

Une fonction est un bloc de code nommé, qu'on écrit une fois et qu'on appelle autant de fois
qu'on veut. Tu en utilises déjà : `main`, `printf`, `strlen`.

## Créer et appeler une fonction

```c
#include <stdio.h>

void saluer(void) {          // definition
    printf("Bonjour !\n");
}

int main(void) {
    saluer();                // appel
    saluer();                // on peut rappeler autant de fois
    return 0;
}
```

- `void` avant le nom : la fonction ne **renvoie** rien.
- `void` entre parenthèses : elle ne **prend** aucun paramètre.
- Les parenthèses sont obligatoires à l'appel, même sans argument : `saluer();`

## L'ordre compte

En C, une fonction doit être **connue avant d'être appelée**. Si tu la définis après `main`, tu
dois la déclarer avant (chapitre 24) :

```c
void saluer(void);       // declaration (prototype)

int main(void) {
    saluer();
    return 0;
}

void saluer(void) {      // definition
    printf("Bonjour !\n");
}
```

C'est la façon standard d'organiser un fichier C : prototypes en haut, `main`, puis les
définitions.

## Renvoyer une valeur

Remplace `void` par le type renvoyé, et utilise `return` :

```c
int additionner(int a, int b) {
    return a + b;
}

int main(void) {
    int resultat = additionner(5, 3);
    printf("%d\n", resultat);              // 8
    printf("%d\n", additionner(10, 20));   // 30
    return 0;
}
```

Règles :

- Le type de la valeur renvoyée doit correspondre au type déclaré.
- `return` **termine immédiatement** la fonction.
- Une fonction `void` peut utiliser `return;` seul pour sortir plus tôt.

```c
void verifier(int age) {
    if (age < 0) {
        printf("Age invalide\n");
        return;                  // on sort tout de suite
    }
    printf("Age : %d\n", age);
}
```

## Anatomie complète

```c
int   calculer_aire (int longueur, int largeur)  {  return longueur * largeur;  }
 │          │              │                              │
 │          │              └── parametres                 └── corps + valeur renvoyee
 │          └── nom
 └── type de retour
```

## Pourquoi écrire des fonctions ?

1. **Ne pas se répéter** — une correction se fait à un seul endroit.
2. **Découper** un problème en morceaux compréhensibles.
3. **Nommer** une intention : `est_bissextile(annee)` se lit mieux qu'un bloc de trois conditions.
4. **Tester** chaque morceau isolément.

Une bonne fonction fait **une seule chose**, et son nom le dit. Si tu as besoin de « et » pour
la décrire, coupe-la en deux.

## Exemple concret

Fichier [`code/21_fonctions.c`](code/21_fonctions.c) :

```c
#include <stdio.h>

float moyenne(float a, float b, float c);
void  afficher_mention(float note);

int main(void) {
    float m = moyenne(12.0f, 15.5f, 9.0f);
    printf("Moyenne : %.2f\n", m);
    afficher_mention(m);
    return 0;
}

float moyenne(float a, float b, float c) {
    return (a + b + c) / 3.0f;
}

void afficher_mention(float note) {
    if (note >= 16)      printf("Tres bien\n");
    else if (note >= 14) printf("Bien\n");
    else if (note >= 12) printf("Assez bien\n");
    else if (note >= 10) printf("Passable\n");
    else                 printf("Insuffisant\n");
}
```

## Convention de nommage

Comme pour les variables : `snake_case`, un **verbe** qui décrit l'action.

```c
calculer_moyenne()   afficher_menu()   est_valide()   lire_fichier()
```

## Découper en plusieurs fichiers (aperçu)

Dans un vrai projet, on sépare :

`maths.h` (les prototypes, l'interface)
```c
#ifndef MATHS_H
#define MATHS_H

int additionner(int a, int b);

#endif
```

`maths.c` (les définitions)
```c
#include "maths.h"

int additionner(int a, int b) { return a + b; }
```

`main.c`
```c
#include <stdio.h>
#include "maths.h"

int main(void) {
    printf("%d\n", additionner(2, 3));
    return 0;
}
```

Compilation :

```bash
gcc -Wall -Wextra -std=c17 main.c maths.c -o programme
```

Note `#include "maths.h"` avec des **guillemets** (fichier local) et non `<>` (bibliothèque
système). Le `#ifndef / #define / #endif` est la *garde d'inclusion* : elle empêche d'inclure le
même en-tête deux fois.

## Exercice

1. Écris `int carre(int n)` et affiche les carrés de 1 à 10 dans une boucle.
2. Écris `int max(int a, int b)` puis `int max3(int a, int b, int c)` qui réutilise `max`.
3. Écris `void afficher_ligne(int n)` qui affiche `n` tirets.
4. Découpe l'un de tes anciens programmes en trois fichiers (`.h`, `.c`, `main.c`) et compile-le.

---
⬅️ [20 — Pointeurs](20-pointeurs.md) | ➡️ [22 — Paramètres de fonction](22-parametres-de-fonction.md)
