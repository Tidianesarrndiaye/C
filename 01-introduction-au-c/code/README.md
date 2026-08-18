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

```bash
gcc -Wall -Wextra -std=c17 07_types.c -o /tmp/prog && /tmp/prog
gcc -Wall -Wextra -std=c17 26_math.c  -o /tmp/prog -lm && /tmp/prog   # math -> -lm
```

## Avec le Makefile

```bash
make                      # compile tout dans bin/
make run FILE=07_types    # compile et lance un exemple
make clean                # nettoie
```

`18_input.c` attend une saisie ; pour le tester sans taper :

```bash
printf "Tidiane\n25\n" | ./bin/18_input
```
