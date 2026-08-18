# 29 — Les énumérations (enum)

> Équivalent W3Schools : **C Enums**

Une **énumération** est un type dont les valeurs sont une liste de constantes nommées. Elle sert à
représenter un choix parmi un ensemble fixe : les jours, les états d'une machine, les niveaux
d'un log.

## Déclarer un enum

```c
enum Niveau {
    BAS,
    MOYEN,
    HAUT
};
```

Par défaut, les valeurs commencent à **0** et s'incrémentent : `BAS = 0`, `MOYEN = 1`, `HAUT = 2`.

## L'utiliser

```c
#include <stdio.h>

enum Niveau { BAS, MOYEN, HAUT };

int main(void) {
    enum Niveau mon_niveau = MOYEN;

    printf("%d\n", mon_niveau);       // 1

    switch (mon_niveau) {
        case BAS:   printf("Niveau bas\n");   break;
        case MOYEN: printf("Niveau moyen\n"); break;
        case HAUT:  printf("Niveau haut\n");  break;
    }
    return 0;
}
```

C'est le mariage naturel de `enum` et de `switch` : le compilateur peut même t'avertir si tu
oublies un cas (`-Wswitch`, actif avec `-Wall`).

## Valeurs personnalisées

```c
enum Niveau { BAS = 1, MOYEN = 5, HAUT = 10 };
```

Si tu n'en fixes qu'une, les suivantes continuent à partir de là :

```c
enum Mois { JANVIER = 1, FEVRIER, MARS };   // 1, 2, 3
```

## `typedef` pour alléger

```c
typedef enum {
    LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI, DIMANCHE
} Jour;

Jour aujourd_hui = JEUDI;      // plus besoin d'ecrire "enum"
```

## Afficher le nom, pas le numéro

Un `enum` n'est qu'un entier : `printf("%d", JEUDI)` affiche `3`. Pour le nom, on associe un
tableau de chaînes :

```c
typedef enum { LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI, DIMANCHE, NB_JOURS } Jour;

const char *noms_jours[] = {
    "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"
};

Jour j = JEUDI;
printf("%s\n", noms_jours[j]);      // Jeudi
```

Remarque l'astuce `NB_JOURS` en dernier : il vaut automatiquement le nombre d'éléments (7), ce
qui donne la taille du tableau sans la recompter à la main.

## Pourquoi utiliser un enum ?

Compare :

```c
// ❌ Nombres magiques : illisible et fragile
if (statut == 2) { … }

// ❌ Constantes eparpillees
#define EN_ATTENTE 0
#define EN_COURS   1
#define TERMINE    2

// ✅ Enum : groupé, nommé, typé, et le debogueur l'affiche
typedef enum { EN_ATTENTE, EN_COURS, TERMINE, ANNULE } Statut;
if (statut == TERMINE) { … }
```

Avantages : lisibilité, valeurs uniques garanties, un seul endroit à modifier, et le compilateur
peut détecter les `switch` incomplets.

## Enum et drapeaux binaires

En donnant des puissances de 2, on peut combiner plusieurs valeurs dans un seul entier :

```c
typedef enum {
    LECTURE  = 1,    // 0001
    ECRITURE = 2,    // 0010
    EXEC     = 4     // 0100
} Permission;

int droits = LECTURE | ECRITURE;         // 0011
if (droits & ECRITURE) { … }             // teste un drapeau
droits &= ~ECRITURE;                     // retire un drapeau
```

C'est exactement le mécanisme des permissions de fichiers Unix.

## Limites

- Un `enum` est un `int` : rien n'empêche `Jour j = 42;`. Le C ne vérifie pas.
- Les noms sont **globaux** : deux enums ne peuvent pas partager un même nom de constante.
  D'où l'usage d'un préfixe : `COULEUR_ROUGE`, `STATUT_ROUGE`.

## Exemple complet

```c
#include <stdio.h>

typedef enum { ROUGE, ORANGE, VERT } Feu;

const char *nom_feu(Feu f) {
    switch (f) {
        case ROUGE:  return "Rouge — arret";
        case ORANGE: return "Orange — ralentir";
        case VERT:   return "Vert — passage";
        default:     return "Inconnu";
    }
}

int main(void) {
    for (Feu f = ROUGE; f <= VERT; f++) {
        printf("%d : %s\n", f, nom_feu(f));
    }
    return 0;
}
```

## Exercice

1. Crée un enum `Saison` et affiche la saison correspondant à un mois donné.
2. Crée un enum `Statut { EN_ATTENTE, VALIDE, REFUSE }` et une fonction qui affiche un message
   pour chacun via un `switch`.
3. Combine un enum et une structure : une `Tache` avec un `titre` et un `Statut`.
4. Implémente un système de permissions par drapeaux binaires.

---
⬅️ [28 — Structures](28-structures.md) | ➡️ [30 — Gestion de la mémoire](30-gestion-de-la-memoire.md)
