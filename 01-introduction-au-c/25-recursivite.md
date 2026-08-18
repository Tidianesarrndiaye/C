# 25 — La récursivité

> Équivalent W3Schools : **C Recursion**

Une fonction **récursive** est une fonction qui s'appelle elle-même.

## Un premier exemple

```c
#include <stdio.h>

int somme(int k) {
    if (k > 0) {
        return k + somme(k - 1);   // elle s'appelle avec une valeur plus petite
    }
    return 0;                      // cas de base
}

int main(void) {
    printf("%d\n", somme(10));     // 55
    return 0;
}
```

### Le déroulé

```
somme(3) = 3 + somme(2)
                 └─ 2 + somme(1)
                          └─ 1 + somme(0)
                                   └─ 0        ← cas de base : on remonte
         = 3 + (2 + (1 + 0)) = 6
```

## Les deux règles absolues

Toute fonction récursive doit avoir :

1. **Un cas de base** — la condition d'arrêt, qui ne rappelle pas la fonction.
2. **Une progression vers le cas de base** — chaque appel doit se rapprocher de l'arrêt.

Sans ça, la récursion est infinie et le programme plante :

```
Segmentation fault (core dumped)
```

C'est un **débordement de pile** (*stack overflow*) : chaque appel consomme de la mémoire sur la
pile, et elle finit par être pleine.

```c
int mauvais(int k) {
    return k + mauvais(k - 1);   // ❌ aucun cas de base
}
```

## Exemples classiques

### Factorielle

```c
long factorielle(int n) {
    if (n <= 1) return 1;              // cas de base
    return n * factorielle(n - 1);     // cas recursif
}
// factorielle(5) = 5 x 4 x 3 x 2 x 1 = 120
```

### Fibonacci

```c
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

⚠️ Cette version est élégante mais **très lente** : `fibonacci(40)` fait environ 300 millions
d'appels, parce que les mêmes valeurs sont recalculées des milliers de fois. La version
itérative est instantanée :

```c
int fibonacci_iteratif(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        int tmp = a + b;
        a = b;
        b = tmp;
    }
    return a;
}
```

Lance les deux avec `n = 40` et compare avec `time ./prog` — la leçon marque plus que le texte.

### Puissance

```c
double puissance(double base, int exposant) {
    if (exposant == 0) return 1.0;
    return base * puissance(base, exposant - 1);
}
```

### Inverser une chaîne

```c
void inverser(const char *s) {
    if (*s == '\0') return;
    inverser(s + 1);      // on traite d'abord la suite…
    putchar(*s);          // …puis on affiche au retour
}
```

## Récursif ou itératif ?

| | Récursif | Itératif (boucle) |
|---|---|---|
| Lisibilité | excellente sur les problèmes naturellement récursifs | meilleure sur les parcours simples |
| Mémoire | consomme la pile (un cadre par appel) | constante |
| Vitesse | plus lent (coût de l'appel) | plus rapide |
| Risque | débordement de pile | boucle infinie |

**Utilise la récursivité quand le problème est lui-même récursif** : parcours d'arbre, systèmes
de fichiers, algorithmes « diviser pour régner » (tri fusion, tri rapide), backtracking (sudoku,
labyrinthes). Pour compter de 1 à 100, fais une boucle.

## Voir la récursion en action

Affiche l'entrée et la sortie de chaque appel — c'est le meilleur moyen de comprendre :

```c
int somme(int k, int profondeur) {
    for (int i = 0; i < profondeur; i++) printf("  ");
    printf("→ somme(%d)\n", k);

    int resultat = (k > 0) ? k + somme(k - 1, profondeur + 1) : 0;

    for (int i = 0; i < profondeur; i++) printf("  ");
    printf("← somme(%d) = %d\n", k, resultat);
    return resultat;
}
```

## Exercice

1. Écris `factorielle` en récursif **et** en itératif.
2. Écris une fonction récursive qui calcule le PGCD (algorithme d'Euclide) :
   `pgcd(a, b) = b == 0 ? a : pgcd(b, a % b)`.
3. Écris une fonction récursive qui compte les chiffres d'un nombre.
4. Compare le temps de `fibonacci(35)` récursif et itératif avec la commande `time`.
5. Résous les tours de Hanoï pour 3 disques.

---
⬅️ [24 — Déclaration de fonction](24-declaration-de-fonction.md) | ➡️ [26 — Fonctions mathématiques](26-fonctions-mathematiques.md)
