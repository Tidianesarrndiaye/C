# 15 — break et continue

> Équivalent W3Schools : **C Break/Continue**

## `break`

`break` sort **immédiatement** de la boucle (ou du `switch`) en cours.

```c
for (int i = 0; i < 10; i++) {
    if (i == 4) {
        break;
    }
    printf("%d\n", i);
}
```

Sortie : `0 1 2 3` — la boucle s'arrête entièrement à 4.

### Cas d'usage typique : la recherche

```c
int notes[] = {12, 8, 15, 19, 6};
int trouve = -1;

for (int i = 0; i < 5; i++) {
    if (notes[i] >= 18) {
        trouve = i;
        break;          // inutile de continuer, on a ce qu'on cherche
    }
}

if (trouve != -1) {
    printf("Premiere note >= 18 en position %d\n", trouve);
} else {
    printf("Aucune note >= 18\n");
}
```

## `continue`

`continue` saute le **reste du tour en cours** et passe directement au tour suivant.

```c
for (int i = 0; i < 10; i++) {
    if (i == 4) {
        continue;
    }
    printf("%d\n", i);
}
```

Sortie : `0 1 2 3 5 6 7 8 9` — seul le 4 manque, la boucle continue.

### Cas d'usage typique : ignorer des valeurs

```c
int valeurs[] = {5, -3, 12, 0, -8, 7};

int somme = 0;
for (int i = 0; i < 6; i++) {
    if (valeurs[i] <= 0) {
        continue;          // on ignore les negatifs et zero
    }
    somme += valeurs[i];
}
printf("Somme des positifs : %d\n", somme);   // 24
```

## ⚠️ `continue` dans un `while` : le piège

Dans un `for`, l'incrémentation `i++` est exécutée même après un `continue`. Dans un `while`,
**non** :

```c
int i = 0;
while (i < 10) {
    if (i == 4) {
        continue;      // ❌ i reste a 4 pour toujours : BOUCLE INFINIE
    }
    printf("%d\n", i);
    i++;
}
```

Correction : incrémenter avant le `continue`.

```c
while (i < 10) {
    if (i == 4) { i++; continue; }
    printf("%d\n", i);
    i++;
}
```

## `break` et boucles imbriquées

`break` ne sort que de **la boucle la plus interne** :

```c
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (j == 1) break;      // sort du for j, pas du for i
        printf("%d-%d ", i, j);
    }
}
// affiche : 0-0 1-0 2-0
```

Pour sortir des deux, utilise un drapeau :

```c
int fini = 0;
for (int i = 0; i < 3 && !fini; i++) {
    for (int j = 0; j < 3; j++) {
        if (condition) { fini = 1; break; }
    }
}
```

… ou, plus rarement, un `goto` vers une étiquette après les boucles. C'est l'un des seuls usages
de `goto` encore accepté en C :

```c
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (condition) goto sortie;
    }
}
sortie:
printf("sorti des deux boucles\n");
```

En dehors de ce cas précis, **évite `goto`**.

## `break` dans un `switch`

Vu au chapitre 12 : là, `break` sort du `switch`, pas de la boucle qui l'entoure. Si tu veux
sortir de la boucle depuis un `switch`, il faut un drapeau ou un `goto`.

## Exercice

1. Parcours les nombres de 1 à 100 et arrête-toi au premier multiple de 7 **et** de 3.
2. Affiche tous les nombres de 1 à 50 sauf les multiples de 5, avec `continue`.
3. Trouve le bug : pourquoi ce code ne se termine-t-il jamais ?
   ```c
   int n = 0;
   while (n < 5) {
       if (n % 2 == 0) continue;
       printf("%d\n", n);
       n++;
   }
   ```

---
⬅️ [14 — Boucle for](14-boucle-for.md) | ➡️ [16 — Tableaux](16-tableaux.md)
