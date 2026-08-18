# 30 — La gestion de la mémoire

> Équivalent W3Schools : **C Memory Management**, **Allocate / Access / Reallocate / Deallocate**

C'est **le** chapitre qui sépare le C des langages que tu connais. En Python et en JavaScript, un
ramasse-miettes libère la mémoire pour toi. En C, c'est ton travail.

## Pile et tas

| | Pile (*stack*) | Tas (*heap*) |
|---|---|---|
| Contenu | variables locales, paramètres | mémoire allouée par `malloc` |
| Taille | limitée (~8 Mo) | limitée par la RAM |
| Gestion | automatique | **manuelle** |
| Durée de vie | jusqu'à la fin du bloc | jusqu'à `free` |
| Vitesse | très rapide | plus lente |

```c
int tab[10];                              // pile : detruit a la sortie de la fonction
int *tab = malloc(10 * sizeof(int));      // tas : vit jusqu'au free
```

## Pourquoi allouer dynamiquement ?

Un tableau classique doit avoir une **taille connue à la compilation** :

```c
int n;
scanf("%d", &n);
int tab[n];        // VLA : possible en C99, mais deconseille (pile limitee, non portable)
```

L'allocation dynamique permet :
- une taille décidée à l'exécution,
- de très gros blocs (la pile serait dépassée),
- des données qui survivent à la fonction qui les a créées,
- de redimensionner en cours de route.

## `malloc` — allouer

```c
#include <stdlib.h>

int *tab = malloc(5 * sizeof(int));
```

- `malloc(n)` réserve `n` **octets** et renvoie l'adresse du début, ou `NULL` si ça échoue.
- On écrit toujours `nombre * sizeof(type)`, jamais un nombre d'octets en dur.
- Idiome robuste : `sizeof(*tab)` au lieu de `sizeof(int)` — si tu changes le type de `tab`, la
  taille suit toute seule.

```c
int *tab = malloc(5 * sizeof(*tab));
```

### Toujours vérifier le retour

```c
int *tab = malloc(5 * sizeof(*tab));
if (tab == NULL) {
    fprintf(stderr, "Memoire insuffisante\n");
    return 1;
}
```

⚠️ La mémoire renvoyée par `malloc` **n'est pas initialisée** : elle contient des déchets.

## `calloc` — allouer et mettre à zéro

```c
int *tab = calloc(5, sizeof(int));    // 5 elements, tous a 0
```

`calloc(nombre, taille)` prend deux arguments et **initialise tout à zéro**. Un peu plus lent,
mais plus sûr.

## Utiliser la mémoire allouée

Exactement comme un tableau :

```c
for (int i = 0; i < 5; i++) {
    tab[i] = i * i;
}
printf("%d\n", tab[3]);      // 9
```

## `realloc` — redimensionner

```c
int *nouveau = realloc(tab, 10 * sizeof(*tab));
if (nouveau == NULL) {
    free(tab);               // l'ancien bloc est toujours valide : ne le perds pas
    return 1;
}
tab = nouveau;
```

⚠️ **N'écris jamais `tab = realloc(tab, …)` directement** : si `realloc` échoue, il renvoie `NULL`
et tu perds l'adresse de l'ancien bloc → fuite mémoire garantie.

`realloc` conserve le contenu existant ; les nouvelles cases ne sont pas initialisées.

## `free` — libérer

```c
free(tab);
tab = NULL;      // bonne habitude : evite l'usage apres liberation
```

**Chaque `malloc` doit avoir exactement un `free`.**

## Les quatre erreurs mémoire du C

### 1. La fuite (*memory leak*)

```c
void fuite(void) {
    int *p = malloc(1000);
    // ... pas de free
}   // ❌ les 1000 octets sont perdus a jamais
```

Dans une boucle ou un serveur, la mémoire se remplit jusqu'au crash.

### 2. L'usage après libération (*use after free*)

```c
free(p);
printf("%d\n", *p);    // ❌ comportement indefini
```

### 3. La double libération

```c
free(p);
free(p);               // ❌ corruption du tas
```

Mettre `p = NULL` après `free` neutralise les deux derniers cas : `free(NULL)` est sans effet.

### 4. Le dépassement de tampon

```c
int *tab = malloc(5 * sizeof(int));
tab[10] = 42;          // ❌ ecrit hors du bloc
```

## L'outil indispensable : Valgrind

> ⚠️ **C'est le seul chapitre du parcours où les deux systèmes ne sont pas à égalité.**
> Valgrind **et** les sanitizers de gcc existent sous Linux/WSL, et **aucun des deux** n'existe
> sous Windows avec MinGW-w64. Si tu as WSL, fais ce chapitre sous WSL.

### Linux / WSL

```bash
sudo apt install valgrind
gcc -g -Wall -Wextra -std=c17 prog.c -o prog     # -g : symboles de debogage
valgrind --leak-check=full ./prog
```

Sortie d'un programme sain :

```
All heap blocks were freed -- no leaks are possible
```

Sortie d'un programme qui fuit :

```
40 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at 0x…: malloc
   by 0x…: main (prog.c:7)
```

Il te donne **le numéro de ligne** du `malloc` fautif. Prends l'habitude de passer tous tes
programmes à Valgrind — c'est comme ça qu'on apprend le C proprement.

Alternative moderne, intégrée à gcc :

```bash
gcc -fsanitize=address,undefined -g prog.c -o prog && ./prog
```

### Windows

| Outil | Disponible ? |
|---|---|
| **Valgrind** | ❌ n'a jamais été porté sous Windows |
| **`-fsanitize=address,undefined`** | ❌ MinGW-w64 ne fournit pas `libasan`/`libubsan` |
| **Dr. Memory** | ✅ l'équivalent Windows de Valgrind, gratuit |
| **`/fsanitize=address` de MSVC** | ✅ mais il faut Visual Studio, un autre compilateur |
| **WSL** | ✅ **la solution recommandée** |

Si tu tentes le sanitizer sous MinGW, tu obtiens exactement ceci :

```
ld.exe: cannot find -lasan: No such file or directory
collect2.exe: error: ld returned 1 exit status
```

Ce n'est pas une erreur de ta part : la bibliothèque n'existe pas dans cette chaîne d'outils.

**Option A — passer par WSL** (recommandée) : tu retrouves exactement les commandes ci-dessus.

**Option B — Dr. Memory** : télécharge-le sur <https://drmemory.org>, puis

```powershell
gcc -g -Wall -Wextra -std=c17 prog.c -o prog.exe
drmemory -- .\prog.exe
```

Il affiche les fuites avec les numéros de ligne, comme Valgrind.

**Option C — sans outil** : compte tes `malloc` et tes `free` à la main, en instrumentant :

```c
static int allocations = 0;

void *mon_malloc(size_t n) { allocations++; return malloc(n); }
void  mon_free(void *p)    { if (p) allocations--; free(p); }

// a la fin de main :
printf("Blocs non liberes : %d\n", allocations);   // doit afficher 0
```

C'est rudimentaire, mais ça détecte la fuite la plus courante : le `free` oublié.

## Exemple complet

Fichier [`code/30_memoire.c`](code/30_memoire.c) :

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 5;

    int *tab = malloc(n * sizeof(*tab));
    if (tab == NULL) { fprintf(stderr, "Echec malloc\n"); return 1; }

    for (int i = 0; i < n; i++) tab[i] = (i + 1) * 10;

    printf("Avant : ");
    for (int i = 0; i < n; i++) printf("%d ", tab[i]);
    printf("\n");

    // Agrandissement
    int *tmp = realloc(tab, 8 * sizeof(*tab));
    if (tmp == NULL) { free(tab); return 1; }
    tab = tmp;

    for (int i = 5; i < 8; i++) tab[i] = (i + 1) * 10;

    printf("Apres : ");
    for (int i = 0; i < 8; i++) printf("%d ", tab[i]);
    printf("\n");

    free(tab);
    tab = NULL;
    return 0;
}
```

## Chaînes allouées dynamiquement

```c
char *copie_chaine(const char *src) {
    char *dest = malloc(strlen(src) + 1);    // +1 pour le '\0' !
    if (dest == NULL) return NULL;
    strcpy(dest, src);
    return dest;
}

char *c = copie_chaine("Bonjour");
printf("%s\n", c);
free(c);
```

Le `+1` oublié est l'un des bugs les plus fréquents du C.

## Tableau 2D dynamique

```c
int lignes = 3, colonnes = 4;

int **matrice = malloc(lignes * sizeof(*matrice));
for (int i = 0; i < lignes; i++) {
    matrice[i] = malloc(colonnes * sizeof(**matrice));
}

matrice[1][2] = 42;

for (int i = 0; i < lignes; i++) free(matrice[i]);   // liberer dans l'ordre inverse
free(matrice);
```

## Les règles d'or

1. Un `malloc` = un `free`.
2. Vérifie toujours le retour de `malloc`.
3. `p = NULL;` après `free(p)`.
4. N'accède jamais à un pointeur libéré.
5. Réserve toujours `+1` pour le `'\0'` des chaînes.
6. Fais tourner Valgrind (Linux/WSL) ou Dr. Memory (Windows).

## Exercice

1. Alloue dynamiquement un tableau dont l'utilisateur choisit la taille, remplis-le, affiche-le,
   libère-le. Vérifie qu'il n'y a aucune fuite (Valgrind sous Linux/WSL, Dr. Memory sous Windows).
2. Écris ta propre version de `strdup`.
3. Crée un tableau dynamique qui double de taille quand il est plein (`realloc`).
4. Introduis volontairement une fuite et retrouve-la avec ton détecteur de fuites.

---
⬅️ [29 — Enums](29-enums.md) | ➡️ [31 — Erreurs et débogage](31-erreurs-et-debogage.md)
