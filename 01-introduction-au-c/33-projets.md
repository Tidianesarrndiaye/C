# 33 — Projets

> Équivalent W3Schools : **C Projects**, **C Exercises**, **C Examples**

Les chapitres t'ont donné les briques. Ces projets te font construire quelque chose. Fais-les
dans l'ordre : chacun réutilise les notions du précédent.

## Comment aborder un projet

1. Écris d'abord **ce que le programme doit faire**, en français, dans un commentaire.
2. Découpe en fonctions **avant** de coder.
3. Fais marcher une version minuscule (une seule fonctionnalité), puis ajoute.
4. Compile souvent : `gcc -Wall -Wextra -std=c17`.
5. Teste les cas limites : entrée vide, valeur négative, tableau plein, fichier absent.
6. Si ton code doit tourner sur les deux systèmes, isole ce qui diffère derrière un `#ifdef _WIN32`
   et n'en parle plus.

---

## Niveau 1 — après le chapitre 15

### 1.1 Jeu du nombre mystère
Le programme tire un nombre entre 1 et 100 (`rand`), l'utilisateur devine, le programme répond
« plus grand » / « plus petit ». Compte les essais.

*Notions : boucles, conditions, `rand`, `scanf`.*

### 1.2 Calculatrice
Deux nombres, un opérateur, un `switch`, une boucle pour recommencer. Gère la division par zéro.

### 1.3 Table de multiplication
L'utilisateur choisit un nombre, le programme affiche sa table alignée. Puis toutes les tables de
1 à 9 dans une grille.

### 1.4 FizzBuzz
De 1 à 100 : « Fizz » si multiple de 3, « Buzz » si multiple de 5, « FizzBuzz » si les deux.

### 1.5 Convertisseur d'unités
Menu : °C↔°F, km↔miles, kg↔livres, FCFA↔EUR.

---

## Niveau 2 — après le chapitre 18

### 2.1 Gestionnaire de notes
Saisir N notes dans un tableau, puis afficher moyenne, min, max, nombre d'admis (≥ 10) et
l'histogramme des mentions.

*Notions : tableaux, boucles, fonctions.*

### 2.2 Analyseur de texte
L'utilisateur saisit une phrase (`fgets`). Le programme compte les caractères, les mots, les
voyelles, et affiche la phrase en majuscules puis à l'envers.

### 2.3 Vérificateur de palindrome
En ignorant les espaces, la casse et la ponctuation. « Engage le jeu que je le gagne » doit
passer.

### 2.4 Morpion (tic-tac-toe)
Grille 3 × 3 en tableau 2D, deux joueurs à tour de rôle, détection de victoire et de match nul.

*Notions : tableaux 2D, fonctions, boucles imbriquées.*

---

## Niveau 3 — après le chapitre 26

### 3.1 Bibliothèque de fonctions maths
Ton propre `mathperso.h` / `mathperso.c` : `est_premier`, `pgcd`, `ppcm`, `factorielle`,
`fibonacci`, `est_parfait`, `inverser_nombre`. Plus un `main.c` qui les teste toutes.

*Notions : compilation séparée, prototypes, `Makefile`.*

### 3.2 Tri et recherche
Implémente tri à bulles, tri par sélection, tri par insertion, recherche linéaire et recherche
dichotomique. Compare leur nombre de comparaisons sur un tableau de 1000 éléments.

### 3.3 Convertisseur de bases
Décimal ↔ binaire ↔ hexadécimal ↔ octal, dans les deux sens.

### 3.4 Matrices
Addition, multiplication, transposition, déterminant 3 × 3.

---

## Niveau 4 — après le chapitre 30

### 4.1 Carnet de contacts
Structure `Contact` (nom, téléphone, e-mail). Menu : ajouter, lister, rechercher, supprimer,
sauvegarder dans un fichier, charger au démarrage. Tableau alloué dynamiquement qui s'agrandit
avec `realloc`.

*Notions : structures, fichiers, `malloc`/`realloc`/`free`. C'est LE projet de synthèse.*

### 4.2 Gestion de stock
Structure `Produit` (référence, nom, quantité, prix). Alertes de rupture, valeur totale du stock,
export CSV.

### 4.3 Liste chaînée
```c
typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
} Noeud;
```
Implémente : insertion en tête, en queue, suppression, recherche, affichage, inversion, libération
complète. **Passe le tout à un détecteur de fuites** (Valgrind sous Linux/WSL, Dr. Memory sous
Windows) : zéro fuite.

*C'est la structure de données fondamentale du C. Ne saute pas ce projet.*

### 4.4 Pile et file
Implémente une pile (LIFO) et une file (FIFO), d'abord avec un tableau, puis avec une liste
chaînée. Utilise la pile pour vérifier l'équilibrage des parenthèses d'une expression.

### 4.5 Mini `wc`
Reproduis la commande Unix : `./wc fichier.txt` (Linux/WSL) ou `.\wc.exe fichier.txt` (Windows)
affiche lignes, mots, octets. Lis le nom du fichier dans `argv`.

⚠️ Sous Windows, un fichier texte se termine par `\r\n` : ouvre-le en mode binaire (`"rb"`) si tu
veux un compte d'octets identique à celui de la vraie commande `wc`.

---

## Niveau 5 — pour aller plus loin

### 5.1 Éditeur de texte en ligne de commande
Ouvrir, afficher avec numéros de ligne, modifier une ligne, insérer, supprimer, sauvegarder.

### 5.2 Jeu de la vie de Conway
Grille 2D, règles de voisinage, animation dans le terminal. Effacer l'écran dépend du système —
c'est l'occasion d'écrire ta première fonction portable :

```c
#ifdef _WIN32
  #define EFFACER "cls"
#else
  #define EFFACER "clear"
#endif

system(EFFACER);
```

`_WIN32` est défini automatiquement par tout compilateur Windows (y compris MinGW en 64 bits) et
par aucun compilateur Linux. C'est **le** test de plateforme standard en C.

### 5.3 Table de hachage
Fonction de hachage, gestion des collisions par chaînage, `inserer` / `chercher` / `supprimer`.

### 5.4 Interpréteur d'expressions
Évalue `3 + 4 * (2 - 1)` : tokenisation, puis algorithme *shunting-yard* ou analyse récursive
descendante.

---

## Idées de suite après ce parcours

- **Structures de données et algorithmes en C** : arbres binaires, graphes, complexité.
- **Programmation système** : sous Linux, `fork`, `exec`, `pipe`, signaux, sockets, `pthread` ;
  sous Windows, l'API Win32 (`CreateProcess`, `CreateThread`, *named pipes*). Les deux mondes
  divergent complètement ici — d'où l'intérêt de WSL pour suivre les cours et livres classiques.
- **Le livre de référence** : *The C Programming Language*, Kernighan & Ritchie (« le K&R »).
- **Passer au C++ ou au Rust** : la marche est bien plus courte une fois le C acquis.

---

⬅️ [32 — Date et heure](32-date-et-heure.md) | 🏠 [Sommaire](README.md)
