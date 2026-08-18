# 16 — Les tableaux

> Équivalent W3Schools : **C Arrays**, **Array Size**, **Multidimensional Arrays**

Un tableau stocke **plusieurs valeurs du même type** dans une seule variable, dans des cases
contiguës en mémoire.

## Déclarer un tableau

```c
type nom[taille];
```

```c
int notes[4];                          // 4 entiers, non initialises
int notes[4] = {12, 15, 8, 19};        // declaration + initialisation
int notes[]  = {12, 15, 8, 19};        // la taille est deduite : 4
```

Mettre à zéro toutes les cases :

```c
int notes[100] = {0};    // toutes les cases valent 0
```

> ⚠️ `int notes[4];` sans initialisation contient **des valeurs aléatoires**, pas des zéros.

## Accéder aux éléments

Les indices commencent à **0** (comme en Python et JavaScript) :

```c
int notes[] = {12, 15, 8, 19};

printf("%d\n", notes[0]);   // 12  (premier)
printf("%d\n", notes[3]);   // 19  (dernier)
```

Modifier une case :

```c
notes[0] = 20;
printf("%d\n", notes[0]);   // 20
```

## Parcourir un tableau

```c
int notes[] = {12, 15, 8, 19};

for (int i = 0; i < 4; i++) {
    printf("notes[%d] = %d\n", i, notes[i]);
}
```

## ⚠️ Le C ne vérifie pas les limites

```c
int notes[4] = {12, 15, 8, 19};
printf("%d\n", notes[10]);    // ❌ pas d'erreur : affiche n'importe quoi
notes[10] = 5;                // ❌ pire : ecrase une autre zone memoire
```

En Python tu aurais une `IndexError`, en JavaScript `undefined`. En C, tu as un **comportement
indéterminé** : le programme peut afficher n'importe quoi, planter, ou pire — sembler marcher
et corrompre autre chose. C'est la faille de sécurité la plus classique de l'histoire
(*buffer overflow*).

**Règle absolue : c'est à toi de rester dans les bornes.**

## Connaître la taille d'un tableau

Le C ne stocke pas la taille. On la calcule avec `sizeof` :

```c
int notes[] = {12, 15, 8, 19};

printf("%zu\n", sizeof(notes));            // 16 octets (4 int x 4 octets)
printf("%zu\n", sizeof(notes[0]));         // 4 octets
printf("%zu\n", sizeof(notes) / sizeof(notes[0]));   // 4 elements
```

L'idiome à retenir :

```c
size_t n = sizeof(tableau) / sizeof(tableau[0]);
for (size_t i = 0; i < n; i++) { … }
```

> ⚠️ Cette astuce **ne marche que là où le tableau est déclaré**. Passé à une fonction, un
> tableau « se dégrade » en pointeur et `sizeof` renvoie la taille du pointeur (8 octets), pas
> celle du tableau. C'est pourquoi on passe **toujours la taille en paramètre** :
> ```c
> void afficher(int tab[], int taille) { … }
> ```

## Exemples concrets

### Moyenne

```c
int notes[] = {12, 15, 8, 19, 14};
int n = 5;
int somme = 0;

for (int i = 0; i < n; i++) {
    somme += notes[i];
}
printf("Moyenne : %.2f\n", (float) somme / n);
```

### Le plus grand élément

```c
int notes[] = {12, 15, 8, 19, 14};
int max = notes[0];                     // on part du premier, pas de 0 !

for (int i = 1; i < 5; i++) {
    if (notes[i] > max) {
        max = notes[i];
    }
}
printf("Max : %d\n", max);
```

## Tableaux multidimensionnels

Un tableau de tableaux, pour représenter une grille, une matrice, un plateau de jeu :

```c
int matrice[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};

printf("%d\n", matrice[0][2]);   // 3
matrice[1][0] = 40;
```

Parcours avec deux boucles imbriquées :

```c
for (int i = 0; i < 2; i++) {          // lignes
    for (int j = 0; j < 3; j++) {      // colonnes
        printf("%3d", matrice[i][j]);
    }
    printf("\n");
}
```

On peut aller à trois dimensions et plus (`int cube[2][3][4];`), mais au-delà de deux ça devient
vite illisible.

## En mémoire

Un tableau, c'est une suite d'octets contigus. `notes[2]` signifie littéralement « l'adresse de
départ + 2 × la taille d'un `int` ». C'est pour ça que l'accès est instantané, et c'est le lien
direct avec les pointeurs (chapitre 20) :

```
notes:  [ 12 ][ 15 ][  8 ][ 19 ]
adresse: 1000  1004  1008  1012
```

## Exemple complet

Fichier [`code/16_tableaux.c`](code/16_tableaux.c) — parcours, somme, min, max, moyenne et
matrice 2D.

## Exercice

1. Crée un tableau de 10 entiers, remplis-le avec les carrés de 1 à 10, puis affiche-le.
2. Calcule le minimum, le maximum et la moyenne d'un tableau de notes.
3. Inverse un tableau sur place (le premier devient le dernier, etc.).
4. Crée une matrice 3 × 3 et affiche la somme de sa diagonale.

---
⬅️ [15 — break et continue](15-break-et-continue.md) | ➡️ [17 — Chaînes de caractères](17-chaines-de-caracteres.md)
