# Introduction au langage C

Parcours calqué **chapitre par chapitre sur le tutoriel C de W3Schools**
(<https://www.w3schools.com/c/>), pour que tu puisses lire indifféremment ici ou là-bas.
Le contenu est réécrit en français, avec des exemples compilables au terminal (pas de « Try it Yourself »).

## Sommaire

### Les bases
| # | Chapitre | Page W3Schools correspondante |
|---|----------|-------------------------------|
| 01 | [Introduction](01-introduction.md) | C Intro |
| 02 | [Démarrer (installer et compiler)](02-demarrer.md) | C Get Started |
| 03 | [Syntaxe](03-syntaxe.md) | C Syntax |
| 04 | [Afficher du texte (output)](04-sortie-output.md) | C Output / New Lines |
| 05 | [Commentaires](05-commentaires.md) | C Comments |
| 06 | [Variables](06-variables.md) | C Variables |
| 07 | [Types de données](07-types-de-donnees.md) | C Data Types |
| 08 | [Constantes](08-constantes.md) | C Constants |
| 09 | [Opérateurs](09-operateurs.md) | C Operators |
| 10 | [Booléens](10-booleens.md) | C Booleans |

### Conditions et boucles
| # | Chapitre | Page W3Schools correspondante |
|---|----------|-------------------------------|
| 11 | [if… else](11-if-else.md) | C If...Else |
| 12 | [switch](12-switch.md) | C Switch |
| 13 | [Boucle while](13-boucle-while.md) | C While Loop |
| 14 | [Boucle for](14-boucle-for.md) | C For Loop |
| 15 | [break et continue](15-break-et-continue.md) | C Break/Continue |

### Données composées
| # | Chapitre | Page W3Schools correspondante |
|---|----------|-------------------------------|
| 16 | [Tableaux](16-tableaux.md) | C Arrays |
| 17 | [Chaînes de caractères](17-chaines-de-caracteres.md) | C Strings |
| 18 | [Saisie utilisateur](18-saisie-utilisateur.md) | C User Input |

### Mémoire
| # | Chapitre | Page W3Schools correspondante |
|---|----------|-------------------------------|
| 19 | [Adresse mémoire](19-adresse-memoire.md) | C Memory Address |
| 20 | [Pointeurs](20-pointeurs.md) | C Pointers |

### Fonctions
| # | Chapitre | Page W3Schools correspondante |
|---|----------|-------------------------------|
| 21 | [Fonctions](21-fonctions.md) | C Functions |
| 22 | [Paramètres de fonction](22-parametres-de-fonction.md) | C Function Parameters |
| 23 | [Portée (scope)](23-portee-scope.md) | C Scope |
| 24 | [Déclaration de fonction](24-declaration-de-fonction.md) | C Function Declaration |
| 25 | [Récursivité](25-recursivite.md) | C Recursion |
| 26 | [Fonctions mathématiques](26-fonctions-mathematiques.md) | C Math Functions |

### Aller plus loin
| # | Chapitre | Page W3Schools correspondante |
|---|----------|-------------------------------|
| 27 | [Fichiers](27-fichiers.md) | C Files |
| 28 | [Structures](28-structures.md) | C Structures |
| 29 | [Enums](29-enums.md) | C Enums |
| 30 | [Gestion de la mémoire](30-gestion-de-la-memoire.md) | C Memory Management |
| 31 | [Erreurs et débogage](31-erreurs-et-debogage.md) | C Errors / Debugging |
| 32 | [Date et heure](32-date-et-heure.md) | C Date |
| 33 | [Projets](33-projets.md) | C Projects |

### Annexes
- [`reference/`](reference/) — mots-clés du langage et fiches des bibliothèques standard (`stdio.h`, `stdlib.h`, `string.h`, `math.h`, `ctype.h`, `time.h`).
- [`code/`](code/) — tous les exemples, compilables (`make`).
- [`exercices/`](exercices/) — les exercices, un fichier par bloc de chapitres.

## Comment travailler chaque chapitre

1. Lis le `.md`.
2. Ouvre le fichier `code/NN_*.c` correspondant dans VS Code.
3. Compile et exécute au terminal :
   ```bash
   gcc -Wall -Wextra -std=c17 code/04_output.c -o /tmp/prog && /tmp/prog
   ```
4. **Modifie** l'exemple (casse-le exprès, regarde l'erreur du compilateur) — c'est là qu'on apprend le C.
5. Fais l'exercice du chapitre.

## Conseil venant de ton parcours

Tu viens de Python/Django et de JavaScript. En C, trois choses vont te surprendre et méritent
ton attention dès le début : **les types sont fixés à la compilation**, **rien n'est initialisé
automatiquement**, et **c'est toi qui gères la mémoire**. Les chapitres 19, 20 et 30 sont donc
les plus importants du parcours — ne les survole pas.
