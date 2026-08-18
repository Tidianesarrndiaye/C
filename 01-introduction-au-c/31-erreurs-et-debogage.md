# 31 — Erreurs, débogage et gestion d'erreurs

> Équivalent W3Schools : **C Errors**, **C Debugging**, **C NULL**, **C Error Handling**

## Les trois familles d'erreurs

| Type | Quand | Exemple |
|---|---|---|
| **Compilation** (syntaxe) | à la compilation | `;` manquant, variable non déclarée |
| **Exécution** (*runtime*) | pendant l'exécution | division par zéro, `Segmentation fault` |
| **Logique** | jamais signalée | le programme tourne mais donne un mauvais résultat |

Les deux premières sont faciles : le compilateur ou le système te préviennent. La troisième est
celle qui coûte du temps.

## Lire les erreurs de gcc

```
prog.c:5:12: error: expected ';' before 'return'
    5 |     int x = 5
      |            ^
      |            ;
```

- `prog.c` : le fichier ; `5` : la ligne ; `12` : la colonne.
- **Corrige toujours la première erreur d'abord** : une seule faute en génère souvent dix.
- Une erreur signalée ligne 5 vient très souvent de la ligne 4 (point-virgule oublié).

### Les messages les plus fréquents

| Message | Cause probable |
|---|---|
| `expected ';' before …` | `;` manquant à la ligne précédente |
| `'x' undeclared` | variable non déclarée, ou faute de frappe |
| `implicit declaration of function 'f'` | prototype manquant ou `#include` oublié |
| `undefined reference to 'sqrt'` | il manque `-lm` à l'édition de liens |
| `undefined reference to 'ma_fonction'` | fonction déclarée mais jamais définie, ou `.c` non compilé |
| `format '%d' expects argument of type 'int'` | mauvais spécificateur dans `printf` |
| `assignment to 'int' from 'int *'` | confusion `=` / `*` avec un pointeur |
| `control reaches end of non-void function` | `return` oublié |

## Les avertissements sont des bugs futurs

```bash
gcc -Wall -Wextra -Wpedantic -std=c17 prog.c -o prog
```

Un programme qui compile sans **aucun** avertissement, ce n'est pas de la coquetterie : la
plupart des avertissements de gcc signalent du vrai code cassé qui « marche par hasard ».

Options utiles en plus : `-Wshadow` (variable masquée), `-Wconversion` (conversions
silencieuses), `-Werror` (transforme tout avertissement en erreur).

## Les erreurs d'exécution les plus courantes

### `Segmentation fault (core dumped)`

Le programme a accédé à une mémoire qui ne lui appartient pas. Causes classiques :

- déréférencer un pointeur `NULL` ou non initialisé ;
- dépasser les limites d'un tableau ;
- utiliser de la mémoire déjà libérée ;
- récursion infinie (débordement de pile) ;
- écrire dans une chaîne littérale (`char *s = "abc"; s[0] = 'A';`).

### Division par zéro

```c
int a = 10, b = 0;
printf("%d\n", a / b);        // ❌ plantage (entiers)
printf("%f\n", 10.0 / 0.0);   // inf   (decimaux : pas de plantage)
```

Vérifie toujours avant de diviser.

## Le pointeur `NULL`

`NULL` signifie « ne pointe sur rien ». C'est la valeur de retour d'échec de `malloc`, `fopen`,
`strchr`…

```c
FILE *f = fopen("absent.txt", "r");
if (f == NULL) { … }        // ✅ toujours tester
```

Trois règles :
1. Initialise tout pointeur (à `NULL` par défaut).
2. Teste avant de déréférencer.
3. `p = NULL;` après `free(p)`.

## `errno` et `perror`

Beaucoup de fonctions système renseignent la variable globale `errno` en cas d'échec :

```c
#include <errno.h>
#include <string.h>

FILE *f = fopen("absent.txt", "r");
if (f == NULL) {
    perror("fopen");                                  // fopen: No such file or directory
    fprintf(stderr, "Detail : %s\n", strerror(errno)); // meme message, personnalisable
    return 1;
}
```

## Les conventions de gestion d'erreurs en C

Il n'y a **pas d'exceptions** en C (pas de `try/except` comme en Python). Trois conventions :

### 1. Un code de retour

```c
int diviser(int a, int b, int *resultat) {
    if (b == 0) return -1;      // code d'erreur
    *resultat = a / b;
    return 0;                   // succes
}

int r;
if (diviser(10, 0, &r) != 0) {
    fprintf(stderr, "Division par zero\n");
}
```

C'est la convention dominante : **0 = succès, non-zéro = erreur**, et le résultat sort par un
pointeur.

### 2. Un pointeur `NULL` en cas d'échec

C'est ce que font `malloc` et `fopen`.

### 3. Le code de sortie de `main`

```c
return 0;                 // succes
return 1;                 // erreur
exit(EXIT_FAILURE);       // equivalent, depuis n'importe ou (<stdlib.h>)
```

## Le débogage sans outil : `printf`

La méthode la plus utilisée au monde, et elle marche :

```c
printf("[DEBUG] i=%d, tab[i]=%d\n", i, tab[i]);
```

Avec un interrupteur pour tout désactiver d'un coup :

```c
#define DEBUG 1
#if DEBUG
  #define LOG(...) fprintf(stderr, __VA_ARGS__)
#else
  #define LOG(...)
#endif

LOG("valeur de i : %d\n", i);
```

`__FILE__` et `__LINE__` donnent automatiquement le fichier et la ligne :

```c
fprintf(stderr, "[%s:%d] i = %d\n", __FILE__, __LINE__, i);
```

## Le débogueur : `gdb`

`gdb` fonctionne à l'identique sur les deux systèmes — seuls le nom du binaire et le préfixe
changent.

**Linux / WSL** (et shell MSYS2)

```bash
gcc -g -Wall -Wextra -std=c17 prog.c -o prog     # -g : indispensable
gdb ./prog
```

**Windows — PowerShell**

```powershell
gcc -g -Wall -Wextra -std=c17 prog.c -o prog.exe
gdb .\prog.exe
```

Sous Windows, `gdb` fait partie du groupe `mingw-w64-x86_64-toolchain` ; s'il manque :
`pacman -S mingw-w64-x86_64-gdb` depuis le shell MSYS2.

Une fois dans `gdb`, **toutes les commandes du tableau ci-dessous sont identiques**.

| Commande | Effet |
|---|---|
| `run` (`r`) | lancer |
| `break 15` (`b`) | point d'arrêt ligne 15 |
| `break ma_fonction` | point d'arrêt sur une fonction |
| `next` (`n`) | ligne suivante (sans entrer dans les fonctions) |
| `step` (`s`) | ligne suivante (en entrant dans les fonctions) |
| `continue` (`c`) | reprendre jusqu'au prochain arrêt |
| `print x` (`p`) | afficher une variable |
| `print *ptr` | afficher la valeur pointée |
| `backtrace` (`bt`) | pile des appels — **le réflexe après un crash** |
| `list` (`l`) | voir le code autour |
| `quit` (`q`) | sortir |

Après un `Segmentation fault`, `run` puis `bt` te donne la ligne exacte du crash.

### Dans VS Code

L'extension C/C++ intègre gdb : mets un point d'arrêt en cliquant à gauche du numéro de ligne,
puis `F5`. Tu vois les variables, la pile et la mémoire sans taper de commande.

## Les sanitizers

Le moyen le plus rapide de trouver les bugs mémoire :

```bash
gcc -fsanitize=address,undefined -g prog.c -o prog && ./prog
```

Le programme s'arrête **au moment exact** de l'erreur, avec la ligne et une explication —
dépassement de tableau, usage après libération, débordement d'entier…

> ⚠️ **Linux / WSL uniquement.** MinGW-w64 ne fournit pas `libasan` / `libubsan` : sous Windows
> la commande échoue à l'édition de liens avec `ld.exe: cannot find -lasan`. Ce n'est pas une
> erreur de ta part. Sous Windows, utilise **Dr. Memory** ou repasse par **WSL** — voir le
> chapitre [30](30-gestion-de-la-memoire.md).

En revanche, ces protections-là marchent sur les deux systèmes :

```bash
gcc -Wall -Wextra -Wpedantic -Wshadow -Wconversion -g -O1 -fstack-protector-all \
    -D_FORTIFY_SOURCE=2 prog.c -o prog
```

## `assert` : vérifier les hypothèses

```c
#include <assert.h>

void traiter(int *tab, int n) {
    assert(tab != NULL);
    assert(n > 0);
    …
}
```

Si la condition est fausse, le programme s'arrête avec le fichier et la ligne. Compiler avec
`-DNDEBUG` désactive tous les `assert` (pour la version finale).

## Méthode de débogage

1. **Reproduire** l'erreur de façon fiable.
2. **Isoler** : réduire le programme au plus petit cas qui plante encore.
3. **Observer** : `printf`, gdb, ou sanitizer.
4. **Formuler une hypothèse**, la tester, une seule à la fois.
5. **Corriger**, puis vérifier que le reste marche toujours.

## Exercice

1. Écris un programme avec 5 erreurs de syntaxe, compile, corrige-les une par une en lisant gcc.
2. Provoque un `Segmentation fault` (déréférence de `NULL`), puis retrouve la ligne avec `gdb` et
   `backtrace`.
3. Écris une fonction de division sûre qui renvoie un code d'erreur.
4. Fais tourner un de tes programmes avec `-fsanitize=address` et `valgrind` (Linux/WSL), ou avec
   Dr. Memory (Windows).

---
⬅️ [30 — Gestion de la mémoire](30-gestion-de-la-memoire.md) | ➡️ [32 — Date et heure](32-date-et-heure.md)
