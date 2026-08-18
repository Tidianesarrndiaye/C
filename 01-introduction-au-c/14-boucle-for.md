# 14 — La boucle for

> Équivalent W3Schools : **C For Loop**, **Nested Loops**

Quand on sait **combien de fois** répéter, `for` est plus compact que `while` : les trois
éléments de la boucle tiennent sur une ligne.

## Syntaxe

```c
for (initialisation; condition; incrementation) {
    // code repete
}
```

```c
for (int i = 0; i < 5; i++) {
    printf("i = %d\n", i);
}
```

C'est **exactement** la même syntaxe qu'en JavaScript — tu es en terrain connu.

### Ordre d'exécution

1. `int i = 0` — une seule fois, au début.
2. `i < 5` — testée avant chaque tour ; si fausse, la boucle s'arrête.
3. le bloc s'exécute.
4. `i++` — après chaque tour, puis retour à l'étape 2.

## Variantes

```c
for (int i = 10; i > 0; i--)       { … }   // decroissant
for (int i = 0; i <= 100; i += 10) { … }   // pas de 10
for (int i = 1; i <= 512; i *= 2)  { … }   // progression geometrique
for (;;)                           { … }   // boucle infinie
```

On peut déclarer et faire évoluer plusieurs variables avec la virgule :

```c
for (int i = 0, j = 10; i < j; i++, j--) {
    printf("i=%d j=%d\n", i, j);
}
```

> Note : `for (int i = 0; …)` — déclarer la variable dans le `for` — n'est valide qu'à partir de
> C99. Avec `-std=c17` c'est parfait. Sur du très vieux code, tu verras la déclaration au-dessus.

## Portée de la variable

```c
for (int i = 0; i < 5; i++) { … }
printf("%d\n", i);    // ❌ erreur : i n'existe plus ici
```

Si tu as besoin de `i` après la boucle, déclare-la avant :

```c
int i;
for (i = 0; i < 5; i++) { if (…) break; }
printf("arret a i = %d\n", i);
```

## Boucles imbriquées

Une boucle dans une boucle : la boucle interne fait **tous ses tours** à chaque tour de la boucle
externe.

```c
for (int i = 1; i <= 3; i++) {          // externe
    for (int j = 1; j <= 3; j++) {      // interne
        printf("%d-%d  ", i, j);
    }
    printf("\n");
}
```

Sortie :

```
1-1  1-2  1-3  
2-1  2-2  2-3  
3-1  3-2  3-3  
```

Convention : `i` pour la première boucle, `j` pour la deuxième, `k` pour la troisième.

### Table de multiplication complète

```c
for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
        printf("%3d", i * j);
    }
    printf("\n");
}
```

### Un triangle

```c
for (int i = 1; i <= 5; i++) {
    for (int j = 0; j < i; j++) {
        printf("*");
    }
    printf("\n");
}
```

```
*
**
***
****
*****
```

## `for` ou `while` ?

| Situation | Choix |
|---|---|
| Nombre de tours connu à l'avance | `for` |
| Parcourir un tableau | `for` |
| Répéter tant qu'une condition externe tient (saisie, lecture de fichier) | `while` |
| Exécuter au moins une fois | `do… while` |

Les deux sont interchangeables :

```c
for (int i = 0; i < 5; i++) { … }

int i = 0;
while (i < 5) { …; i++; }
```

## Pièges

```c
for (int i = 0; i <= 5; i++)     // 6 tours (0,1,2,3,4,5) — attention au <= 
for (int i = 0; i < 5; i++);     // ⚠️ point-virgule : corps vide !
```

Le premier n'est pas un bug en soi, mais quand tu parcours un tableau de 5 cases, `i <= 5`
sort du tableau. Retiens : `< taille`, jamais `<= taille`.

## Exercice

1. Affiche la table de 9 avec un `for`.
2. Affiche la somme des nombres de 1 à 100.
3. Affiche un carré de `*` de 5 × 5, puis un triangle inversé.
4. Affiche tous les nombres premiers inférieurs à 50 (boucle imbriquée).

---
⬅️ [13 — Boucle while](13-boucle-while.md) | ➡️ [15 — break et continue](15-break-et-continue.md)
