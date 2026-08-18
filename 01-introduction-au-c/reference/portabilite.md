# Portabilité : où Linux et Windows diffèrent vraiment

Le langage C est le même partout. Ce qui change, c'est **ce qu'il y a autour** : la taille de
certains types, la fin de ligne des fichiers, les outils. Cette fiche liste tout ce qui peut te
surprendre en passant d'un système à l'autre.

Pour les **commandes** (gcc, gdb, terminal), voir [gcc-aide-memoire.md](gcc-aide-memoire.md).

## 1. La macro `_WIN32` : le test standard

```c
#ifdef _WIN32
    // code Windows
#else
    // code Linux / macOS / Unix
#endif
```

`_WIN32` est défini par **tout** compilateur Windows — y compris MinGW en 64 bits, où le nom est
trompeur. C'est le test de plateforme universel en C. Autres macros utiles :

| Macro | Définie sur |
|---|---|
| `_WIN32` | Windows, 32 **et** 64 bits |
| `_WIN64` | Windows 64 bits seulement |
| `__linux__` | Linux (donc aussi WSL) |
| `__unix__` | Linux, macOS, BSD |
| `__APPLE__` | macOS |
| `__MINGW32__` | compilé avec MinGW (32 et 64 bits) |

**Règle de méthode** : n'écris jamais deux versions complètes de ton programme. Isole la
poignée de lignes qui diffèrent derrière une petite fonction ou une macro, et écris le reste
une seule fois.

```c
#ifdef _WIN32
  #define EFFACER_ECRAN "cls"
#else
  #define EFFACER_ECRAN "clear"
#endif

system(EFFACER_ECRAN);      // le reste du programme ignore le systeme
```

## 2. La taille des types : LP64 contre LLP64

C'est le piège numéro un, et il est **silencieux** — pas d'avertissement, juste un mauvais
résultat.

| Type | Linux / WSL 64 bits (**LP64**) | Windows 64 bits (**LLP64**) |
|---|---|---|
| `char` | 1 | 1 |
| `short` | 2 | 2 |
| `int` | 4 | 4 |
| **`long`** | **8** | **4** |
| `long long` | 8 | 8 |
| `size_t` | 8 | 8 |
| pointeur | 8 | 8 |
| `long double` | 16 | 16 (MinGW) / 8 (MSVC) |

```c
long grand = 3000000000L;   // correct sous Linux, deborde sous Windows
```

Les réflexes :

1. « Au moins 64 bits » → écris **`long long`**, jamais `long`.
2. Mieux : `<stdint.h>` (`int32_t`, `int64_t`, `uint64_t`…) — tailles garanties partout.
3. Ne suppose jamais : demande à `sizeof`.
4. Pour afficher un type de `<stdint.h>`, utilise les macros de `<inttypes.h>` :

```c
#include <stdint.h>
#include <inttypes.h>

int64_t n = 3000000000;
printf("%" PRId64 "\n", n);       // le bon specificateur, sur les deux systemes
```

## 3. Les fins de ligne : `\n` contre `\r\n`

| | Fin de ligne d'un fichier texte |
|---|---|
| Linux / WSL / macOS | `\n` (1 octet) |
| Windows | `\r\n` (2 octets) |

En **mode texte** (`fopen(…, "r")` / `"w"`), la bibliothèque C de Windows traduit
automatiquement dans les deux sens. En **mode binaire** (`"rb"` / `"wb"`), aucune traduction.

Trois conséquences :

1. Le même programme produit un fichier plus gros sous Windows (un octet par ligne).
2. Pour des données non textuelles (`fwrite` d'une `struct`, une image), **toujours `"rb"` /
   `"wb"`** : sinon un octet `0x0A` au milieu de tes données serait transformé en `0x0D 0x0A`.
3. En lisant sous Linux un fichier écrit sous Windows, tu récupères un `\r` parasite. Nettoie
   avec l'idiome portable :

```c
ligne[strcspn(ligne, "\r\n")] = '\0';    // enleve \n ET \r\n
```

Côté Git, sous Windows : `git config --global core.autocrlf input`.

## 4. Les chemins de fichiers

| | Séparateur | Racine |
|---|---|---|
| Linux / WSL | `/` | `/home/tidia/…` |
| Windows | `\` (mais `/` est **accepté** par toutes les fonctions C) | `C:\Users\tidia\…` |

En C, **écris toujours `/`** : `fopen("donnees/notes.txt", "r")` fonctionne sur les deux
systèmes. Le `\` t'obligerait en plus à le doubler (`"donnees\\notes.txt"`), puisque `\` est le
caractère d'échappement des chaînes.

Depuis WSL, les disques Windows sont montés dans `/mnt/c/…`.

## 5. L'encodage de la console

| | Par défaut |
|---|---|
| Linux / WSL | UTF-8 |
| Windows | page de codes 850 ou 1252 → les accents s'affichent `Ã©` |

Sous Windows, `chcp 65001` dans PowerShell (voir le chapitre 02 pour le rendre permanent).
Tant que tu apprends, le plus simple reste d'écrire ton code **sans accents**, comme les fichiers
`code/*.c` de ce parcours.

## 6. Ce qui n'existe pas des deux côtés

| | Linux / WSL | Windows (MinGW-w64) |
|---|---|---|
| `<unistd.h>`, `fork`, `exec`, `pipe` | ✅ | ❌ (API Win32 à la place) |
| `<pthread.h>` | ✅ | ✅ via winpthreads |
| `clock_gettime(CLOCK_MONOTONIC, …)` | ✅ | ✅ fourni par MinGW-w64 |
| `<sys/socket.h>` | ✅ | ❌ (`<winsock2.h>` à la place) |
| `strdup` | ✅ | ✅ |
| `Valgrind` | ✅ | ❌ (Dr. Memory à la place) |
| `-fsanitize=address,undefined` | ✅ | ❌ (`cannot find -lasan`) |
| `gdb` | ✅ | ✅ |
| `make` | ✅ | ✅ sous le nom `mingw32-make` |

## 7. Le conseil général

Si tu es sous Windows et que tu apprends le C **pour apprendre le C** : travaille dans **WSL**.
Tu retrouves l'environnement de tous les livres, de tous les cours et de la quasi-totalité du
code C existant, sans aucune de ces divergences.

Garde MinGW pour ce qu'il fait de mieux : produire un `.exe` que tu peux donner à quelqu'un
sous Windows.
