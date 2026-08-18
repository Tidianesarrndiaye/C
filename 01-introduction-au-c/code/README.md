# Exemples de code

Un fichier par chapitre, tous compilables.

| Fichier | Chapitre |
|---|---|
| `02_hello.c` | 02 — Démarrer |
| `04_output.c` | 04 — Afficher du texte |
| `06_variables.c` | 06 — Variables |
| `07_types.c` | 07 — Types de données |
| `11_if_else.c` | 11 — if… else |
| `12_switch.c` | 12 — switch |
| `16_tableaux.c` | 16 — Tableaux |
| `17_strings.c` | 17 — Chaînes de caractères |
| `18_input.c` | 18 — Saisie utilisateur |
| `20_pointeurs.c` | 20 — Pointeurs |
| `21_fonctions.c` | 21 — Fonctions |
| `26_math.c` | 26 — Fonctions mathématiques (nécessite `-lm`) |
| `27_fichiers.c` | 27 — Fichiers |
| `28_structures.c` | 28 — Structures |
| `30_memoire.c` | 30 — Gestion de la mémoire |

## Compiler un seul fichier

**Linux / WSL** (et shell MSYS2)

```bash
gcc -Wall -Wextra -std=c17 07_types.c -o /tmp/prog && /tmp/prog
gcc -Wall -Wextra -std=c17 26_math.c  -o /tmp/prog -lm && /tmp/prog   # math -> -lm
```

**Windows — PowerShell**

```powershell
gcc -Wall -Wextra -std=c17 07_types.c -o prog.exe ; if ($?) { .\prog.exe }
gcc -Wall -Wextra -std=c17 26_math.c  -o prog.exe -lm ; if ($?) { .\prog.exe }
```

Sous Windows, `-lm` est inutile (les fonctions math sont dans la runtime C) mais accepté :
garde-le, ton code restera compilable sous Linux.

## Avec le Makefile

Le `Makefile` détecte le système tout seul et ajoute `.exe` sous Windows.

**Linux / WSL** (et shell MSYS2)

```bash
make                      # compile tout dans bin/
make run FILE=07_types    # compile et lance un exemple
make clean                # nettoie
```

**Windows — PowerShell** — la commande s'appelle `mingw32-make` :

```powershell
mingw32-make
mingw32-make run FILE=07_types
mingw32-make clean
```

Pour taper `make` comme sous Linux, ajoute `Set-Alias make mingw32-make` à ton `$PROFILE`.

## Donner l'entrée sans taper

`18_input.c` attend une saisie.

**Linux / WSL**

```bash
printf "Tidiane\n25\n" | ./bin/18_input
```

**Windows — PowerShell** (`printf` n'existe pas ; PowerShell ajoute les retours à la ligne) :

```powershell
"Tidiane", "25" | .\bin\18_input.exe
```
