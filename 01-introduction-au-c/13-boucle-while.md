# 13 — La boucle while

> Équivalent W3Schools : **C While Loop**, **Do/While Loop**

Une boucle répète un bloc de code tant qu'une condition reste vraie. Ça évite d'écrire cent fois
la même ligne.

## `while`

```c
while (condition) {
    // code repete
}
```

```c
#include <stdio.h>

int main(void) {
    int i = 0;

    while (i < 5) {
        printf("i = %d\n", i);
        i++;                    // ⚠️ indispensable
    }
    return 0;
}
```

Sortie :

```
i = 0
i = 1
i = 2
i = 3
i = 4
```

### Les trois éléments d'une boucle correcte

1. **L'initialisation** : `int i = 0;` avant la boucle.
2. **La condition** : `i < 5`, testée **avant** chaque tour.
3. **La progression** : `i++`, qui rapproche de la fin.

Si tu oublies le troisième, la condition reste vraie pour toujours : c'est la **boucle infinie**.

```c
int i = 0;
while (i < 5) {
    printf("%d\n", i);   // ❌ i ne change jamais -> boucle infinie
}
```

Pour interrompre un programme parti en boucle infinie dans le terminal : **`Ctrl + C`**.

## `do… while`

Variante qui exécute le bloc **une fois avant** de tester la condition :

```c
do {
    // code
} while (condition);     // ⚠️ point-virgule obligatoire ici
```

```c
int i = 0;
do {
    printf("i = %d\n", i);
    i++;
} while (i < 5);
```

Différence visible quand la condition est fausse dès le départ :

```c
int i = 10;

while (i < 5) { printf("while\n"); }        // n'affiche RIEN

do { printf("do-while\n"); } while (i < 5); // affiche UNE fois
```

### Quand utiliser `do… while` ?

Quand l'action doit avoir lieu au moins une fois : un menu, une demande de saisie qu'on
revalide…

```c
int choix;
do {
    printf("Menu : 1) Jouer  2) Quitter\n> ");
    scanf("%d", &choix);
} while (choix != 1 && choix != 2);
```

## Boucle infinie volontaire

```c
while (1) {
    // ... traitement
    if (fini) break;      // on sort explicitement
}
```

C'est courant dans les programmes qui tournent en continu (serveurs, systèmes embarqués). Voir
`break` au chapitre 15.

## Exemples concrets

### Compte à rebours

```c
int n = 5;
while (n > 0) {
    printf("%d…\n", n);
    n--;
}
printf("Decollage !\n");
```

### Somme des chiffres d'un nombre

```c
int nombre = 1234;
int somme = 0;

while (nombre > 0) {
    somme += nombre % 10;   // dernier chiffre
    nombre /= 10;           // on le retire
}
printf("Somme des chiffres : %d\n", somme);   // 10
```

Ces deux lignes (`% 10` puis `/= 10`) forment un idiome à connaître : elles parcourent un nombre
chiffre par chiffre, de droite à gauche.

### Table de multiplication

```c
int table = 7;
int i = 1;
while (i <= 10) {
    printf("%d x %2d = %3d\n", table, i, table * i);
    i++;
}
```

Remarque `%2d` et `%3d` : ils réservent une largeur minimale, ce qui aligne les colonnes.

## Exercice

1. Affiche les nombres pairs de 0 à 20 avec un `while`.
2. Calcule la factorielle de 6 (`1 × 2 × … × 6`) avec un `while`.
3. Écris un `do… while` qui redemande un nombre tant qu'il n'est pas entre 1 et 10
   (tu auras besoin de `scanf`, chapitre 18 — ou fixe la valeur en dur pour l'instant).

---
⬅️ [12 — switch](12-switch.md) | ➡️ [14 — Boucle for](14-boucle-for.md)
