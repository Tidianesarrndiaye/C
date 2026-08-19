# C

Dossier d'apprentissage du langage **C**.

## Organisation

```
C/
├── README.md                  ← tu es ici
├── .gitignore                 ← ignore les binaires compilés
└── 01-introduction-au-c/      ← parcours complet, calqué sur le tutoriel C de W3Schools
    ├── README.md              ← sommaire des chapitres
    ├── 01-…-33-….md           ← les chapitres, un fichier .md par chapitre
    ├── code/                  ← les exemples compilables (.c) de chaque chapitre
    │   └── 02-etapes-compilation/  ← démo Linux/Windows des 4 étapes de gcc (chap. 02)
    ├── exercices/             ← exercices à faire toi-même
    └── reference/             ← fiches de référence (mots-clés, stdio.h, string.h, math.h…)
```

## Outils

- **Éditeur** : VS Code (extension recommandée : `ms-vscode.cpptools`).
- **Terminal** : compilation et exécution à la main, pas d'éditeur en ligne.
- **Compilateur** : `gcc`, sur l'un ou l'autre de ces deux environnements — le cours donne
  systématiquement les commandes des deux :

| | **Linux / WSL** | **Windows natif** |
|---|---|---|
| Compilateur | `gcc` de la distribution | `gcc` de MinGW-w64, via [MSYS2](https://www.msys2.org) |
| Terminal | bash / zsh | PowerShell, ou le shell MSYS2 (qui est un bash) |
| Produit | `mon_programme` | `mon_programme.exe` |
| `make` | `make` | `mingw32-make` |
| Valgrind / sanitizers | ✅ | ❌ — voir le chapitre 30 |

L'installation pas à pas des deux est décrite au chapitre
[02 — Démarrer](01-introduction-au-c/02-demarrer.md), et les différences du langage lui-même
(taille de `long`, `\r\n`, `#ifdef _WIN32`…) dans la fiche
[portabilite.md](01-introduction-au-c/reference/portabilite.md).

## Le cycle de travail (à retenir par cœur)

**Linux / WSL** (et shell MSYS2)

```bash
gcc mon_fichier.c -o mon_programme   # compiler
./mon_programme                      # exécuter
```

**Windows — PowerShell**

```powershell
gcc mon_fichier.c -o mon_programme.exe   # compiler
.\mon_programme.exe                      # exécuter
```

Version recommandée pendant l'apprentissage (active tous les avertissements, ils t'apprennent beaucoup) :

```bash
gcc -Wall -Wextra -std=c17 mon_fichier.c -o mon_programme && ./mon_programme
```

```powershell
gcc -Wall -Wextra -std=c17 mon_fichier.c -o mon_programme.exe
if ($?) { .\mon_programme.exe }
```

Dans `code/` un `Makefile` est fourni ; il détecte le système tout seul et ajoute `.exe` sous
Windows. `make` compile tout, `make run FILE=02_hello` compile et lance un fichier précis
(`mingw32-make` sous Windows).

## Progression

| Étape | Dossier | État |
|-------|---------|------|
| Bases du langage C | `01-introduction-au-c/` | en cours |
| Structures de données & algorithmes en C | à venir | — |
| Projets C | à venir | — |
