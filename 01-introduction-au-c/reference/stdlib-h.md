# `<stdlib.h>` — utilitaires généraux

## Mémoire dynamique

| Fonction | Rôle |
|---|---|
| `malloc(taille)` | alloue `taille` octets non initialisés |
| `calloc(n, taille)` | alloue `n × taille` octets, mis à zéro |
| `realloc(ptr, taille)` | redimensionne un bloc |
| `free(ptr)` | libère |

```c
int *t = malloc(n * sizeof(*t));
if (t == NULL) { /* echec */ }
free(t);
t = NULL;
```

## Conversion de chaînes

| Fonction | Rôle |
|---|---|
| `atoi(s)` | chaîne → `int` (aucune détection d'erreur) |
| `atof(s)` | chaîne → `double` |
| `atol(s)` | chaîne → `long` |
| `strtol(s, &fin, base)` | ✅ chaîne → `long`, avec détection d'erreur |
| `strtod(s, &fin)` | ✅ chaîne → `double`, avec détection d'erreur |

```c
char *fin;
long n = strtol("42abc", &fin, 10);   // n = 42, fin pointe sur "abc"
if (fin == s) { /* rien n'a ete converti */ }
```

## Nombres aléatoires

| Fonction | Rôle |
|---|---|
| `rand()` | entier entre 0 et `RAND_MAX` |
| `srand(graine)` | initialise le générateur (une seule fois) |

```c
srand(time(NULL));
int n = rand() % 100 + 1;    // 1 a 100
```

## Contrôle du programme

| Fonction | Rôle |
|---|---|
| `exit(code)` | termine le programme (`EXIT_SUCCESS` / `EXIT_FAILURE`) |
| `abort()` | termine brutalement |
| `atexit(f)` | enregistre une fonction à exécuter à la sortie |
| `system(cmd)` | exécute une commande shell — ⚠️ la commande dépend du système : `"clear"` sous Linux, `"cls"` sous Windows |
| `getenv(nom)` | lit une variable d'environnement |

## Divers

| Fonction | Rôle |
|---|---|
| `abs(n)` / `labs(n)` | valeur absolue (entiers) |
| `div(a, b)` | quotient et reste en une fois |
| `qsort(base, n, taille, cmp)` | tri générique |
| `bsearch(cle, base, n, taille, cmp)` | recherche dichotomique |

```c
int comparer(const void *a, const void *b) {
    return (*(const int *)a) - (*(const int *)b);
}
qsort(tab, n, sizeof(int), comparer);
```
