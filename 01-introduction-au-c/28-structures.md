# 28 — Les structures

> Équivalent W3Schools : **C Structures**, **Structures & Pointers**

Une structure (`struct`) regroupe **plusieurs variables de types différents** sous un seul nom.
C'est l'ancêtre de l'objet : des données groupées, sans les méthodes.

## Déclarer une structure

```c
struct Etudiant {
    char  nom[50];
    int   age;
    float moyenne;
};        // ⚠️ le point-virgule est obligatoire
```

## Créer et utiliser une variable

```c
struct Etudiant e1;

strcpy(e1.nom, "Tidiane");     // pas e1.nom = "…" : c'est un tableau !
e1.age = 25;
e1.moyenne = 15.5f;

printf("%s, %d ans, %.2f\n", e1.nom, e1.age, e1.moyenne);
```

L'opérateur `.` accède à un membre.

### Initialisation directe

```c
struct Etudiant e2 = {"Awa", 22, 17.0f};                    // dans l'ordre des champs
struct Etudiant e3 = {.nom = "Moussa", .moyenne = 12.5f};   // par nom (C99), le reste a 0
```

La deuxième forme (*designated initializers*) est plus lisible et résiste aux changements
d'ordre des champs. Préfère-la.

## `typedef` : éviter de répéter `struct`

```c
typedef struct {
    char  nom[50];
    int   age;
    float moyenne;
} Etudiant;

Etudiant e1;                   // plus besoin d'ecrire "struct"
```

C'est la forme la plus courante en C moderne. Variante nommée, utile quand la structure doit se
référencer elle-même (listes chaînées) :

```c
typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;     // ici le nom "struct Noeud" est indispensable
} Noeud;
```

## Copier une structure

Contrairement aux tableaux, une structure **se copie** avec `=` :

```c
Etudiant a = {"Tidiane", 25, 15.5f};
Etudiant b = a;                 // copie complete (membre par membre)
b.age = 30;
printf("%d\n", a.age);          // 25 — a est intact
```

⚠️ C'est une copie **superficielle** : si la structure contient un pointeur, seule l'adresse est
copiée, pas ce qu'elle désigne.

Pour comparer, il n'y a pas de `==` : il faut comparer champ par champ (ou `memcmp`, avec
prudence à cause du remplissage entre les champs).

## Tableau de structures

```c
Etudiant classe[3] = {
    {"Tidiane", 25, 15.5f},
    {"Awa",     22, 17.0f},
    {"Moussa",  24, 12.5f}
};

for (int i = 0; i < 3; i++) {
    printf("%-10s %3d ans  %.2f\n", classe[i].nom, classe[i].age, classe[i].moyenne);
}
```

`%-10s` aligne à gauche sur 10 caractères — pratique pour les tableaux à l'écran.

## Structures et fonctions

### Passage par valeur (copie)

```c
void afficher(Etudiant e) {
    printf("%s\n", e.nom);
}
```

Toute la structure est copiée. Pour une grosse structure, c'est coûteux.

### Passage par pointeur — et l'opérateur `->`

```c
void anniversaire(Etudiant *e) {
    (*e).age++;      // fonctionne, mais lourd
    e->age++;        // ✅ notation flechee, strictement equivalente
}

anniversaire(&e1);
```

**`e->age` est un raccourci pour `(*e).age`.** C'est la notation standard en C dès qu'on manipule
un pointeur vers une structure.

Pour un accès en lecture seule sans copie :

```c
void afficher(const Etudiant *e) {
    printf("%s a %d ans\n", e->nom, e->age);
}
```

C'est la signature idiomatique : `const` + pointeur = rapide **et** sûr.

### Renvoyer une structure

```c
Etudiant creer_etudiant(const char *nom, int age) {
    Etudiant e;
    strncpy(e.nom, nom, sizeof(e.nom) - 1);
    e.nom[sizeof(e.nom) - 1] = '\0';
    e.age = age;
    e.moyenne = 0.0f;
    return e;                   // ✅ la structure est copiee, c'est valide
}
```

(Renvoyer un **pointeur** vers une variable locale serait un bug ; renvoyer la structure
elle-même est correct.)

## Structures imbriquées

```c
typedef struct {
    int jour, mois, annee;
} Date;

typedef struct {
    char nom[50];
    Date naissance;
} Personne;

Personne p = {"Tidiane", {18, 8, 2000}};
printf("%02d/%02d/%d\n", p.naissance.jour, p.naissance.mois, p.naissance.annee);
```

## Taille et alignement

```c
printf("%zu\n", sizeof(Etudiant));
```

La taille peut être **supérieure** à la somme des champs : le compilateur insère du remplissage
(*padding*) pour aligner les champs sur des frontières mémoire. Ranger les champs du plus grand
au plus petit réduit ce gaspillage.

## `union` et `enum` : les cousins

```c
union Valeur {          // tous les membres partagent la MEME zone memoire
    int    i;
    float  f;
    char   c[4];
};
```

Une `union` occupe la taille de son plus grand membre, et un seul champ est valide à la fois.
Usage : économiser la mémoire, ou interpréter les mêmes octets de deux façons. Les `enum` sont
au chapitre suivant.

## Exemple complet

Fichier [`code/28_structures.c`](code/28_structures.c) — un mini carnet d'étudiants avec
recherche et calcul de moyenne.

## Exercice

1. Crée une structure `Livre` (titre, auteur, année, prix) et affiche une bibliothèque de 3 livres.
2. Écris `void augmenter_prix(Livre *l, float pourcentage)`.
3. Crée `Point {x, y}` et écris `double distance(const Point *a, const Point *b)`.
4. Trie un tableau de structures `Etudiant` par moyenne décroissante.

---
⬅️ [27 — Fichiers](27-fichiers.md) | ➡️ [29 — Enums](29-enums.md)
