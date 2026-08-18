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
    ├── exercices/             ← exercices à faire toi-même
    └── reference/             ← fiches de référence (mots-clés, stdio.h, string.h, math.h…)
```

## Outils

- **Éditeur** : VS Code (extension recommandée : `ms-vscode.cpptools`).
- **Compilateur** : `gcc` (déjà installé, version 13.3).
- **Terminal** : compilation et exécution à la main, pas d'éditeur en ligne.

## Le cycle de travail (à retenir par cœur)

```bash
gcc mon_fichier.c -o mon_programme   # compiler
./mon_programme                      # exécuter
```

Version recommandée pendant l'apprentissage (active tous les avertissements, ils t'apprennent beaucoup) :

```bash
gcc -Wall -Wextra -std=c17 mon_fichier.c -o mon_programme && ./mon_programme
```

Dans `code/` un `Makefile` est fourni : `make` compile tout, `make run FILE=01_hello` compile et lance un fichier précis.

## Progression

| Étape | Dossier | État |
|-------|---------|------|
| Bases du langage C | `01-introduction-au-c/` | en cours |
| Structures de données & algorithmes en C | à venir | — |
| Projets C | à venir | — |
