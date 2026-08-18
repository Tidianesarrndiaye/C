# 17 — Les chaînes de caractères

> Équivalent W3Schools : **C Strings**, **Special Characters**, **String Functions**

## Il n'y a pas de type `string` en C

Une chaîne est un **tableau de `char` terminé par le caractère nul `'\0'`**. C'est le point le
plus déroutant quand on vient de Python ou de JavaScript, et il faut le comprendre à fond.

```c
char salutation[] = "Hello";
```

En mémoire :

```
indice :   0     1     2     3     4     5
valeur : 'H'   'e'   'l'   'l'   'o'  '\0'
```

Le tableau fait **6 octets**, pas 5. Le `'\0'` (octet de valeur zéro) marque la fin : c'est lui
qui permet à `printf`, `strlen` et compagnie de savoir où s'arrêter.

Écriture équivalente, explicite :

```c
char salutation[] = {'H', 'e', 'l', 'l', 'o', '\0'};
```

Si tu oublies le `'\0'`, les fonctions continuent de lire la mémoire après la fin du tableau
jusqu'à tomber sur un zéro par hasard → affichage de déchets, ou plantage.

## Afficher une chaîne

```c
char salutation[] = "Hello";
printf("%s\n", salutation);     // Hello
puts(salutation);               // Hello (avec retour a la ligne)
```

Accéder à un caractère :

```c
printf("%c\n", salutation[0]);  // H
salutation[0] = 'J';
printf("%s\n", salutation);     // Jello
```

## Parcourir une chaîne

```c
char mot[] = "Tidiane";
for (int i = 0; mot[i] != '\0'; i++) {
    printf("%c ", mot[i]);
}
```

## Les deux façons de déclarer, et leur différence capitale

```c
char a[] = "Hello";      // TABLEAU : copie modifiable, sur la pile
char *b  = "Hello";      // POINTEUR vers une chaine litterale, EN LECTURE SEULE
```

```c
a[0] = 'J';   // ✅ ok
b[0] = 'J';   // ❌ comportement indefini : plantage (segmentation fault)
```

Écris plutôt `const char *b = "Hello";` pour que le compilateur t'avertisse.

## `<string.h>` : les fonctions de chaînes

```c
#include <string.h>
```

| Fonction | Rôle |
|---|---|
| `strlen(s)` | longueur, **sans** le `'\0'` |
| `strcpy(dest, src)` | copie `src` dans `dest` |
| `strncpy(dest, src, n)` | copie au plus `n` caractères |
| `strcat(dest, src)` | concatène `src` à la fin de `dest` |
| `strncat(dest, src, n)` | concatène au plus `n` caractères |
| `strcmp(a, b)` | compare : `0` si identiques, `<0` si `a<b`, `>0` si `a>b` |
| `strncmp(a, b, n)` | compare les `n` premiers caractères |
| `strchr(s, c)` | cherche le caractère `c`, renvoie un pointeur ou `NULL` |
| `strstr(s, sub)` | cherche la sous-chaîne `sub` |
| `strtok(s, delim)` | découpe une chaîne en morceaux |

### `strlen`

```c
char mot[] = "Hello";
printf("%zu\n", strlen(mot));      // 5   ← les caracteres
printf("%zu\n", sizeof(mot));      // 6   ← les octets, '\0' compris
```

Ne confonds jamais les deux.

### `strcpy` — l'affectation n'existe pas

```c
char a[20] = "Hello";
char b[20];

b = a;              // ❌ erreur de compilation : on n'affecte pas un tableau
strcpy(b, a);       // ✅
```

⚠️ `strcpy` ne vérifie pas la taille de `dest`. Si `src` est plus longue, tu écrases la mémoire
voisine. Assure-toi que la destination est assez grande, ou utilise `snprintf` :

```c
char dest[10];
snprintf(dest, sizeof(dest), "%s", source);   // tronque proprement, termine par '\0'
```

### `strcat`

```c
char nom_complet[50] = "Tidiane";
strcat(nom_complet, " ");
strcat(nom_complet, "Ndiaye");
printf("%s\n", nom_complet);      // Tidiane Ndiaye
```

Le tableau de destination doit être assez grand pour **les deux** chaînes plus le `'\0'`.

### `strcmp` — comparer des chaînes

```c
char a[] = "Hello";
char b[] = "Hello";

if (a == b)             { … }   // ❌ compare des ADRESSES, jamais vrai ici
if (strcmp(a, b) == 0)  { … }   // ✅ compare le CONTENU
```

C'est **le** piège quand on vient d'un langage de haut niveau. En C, `==` sur des chaînes compare
les pointeurs.

```c
printf("%d\n", strcmp("abc", "abc"));   //  0
printf("%d\n", strcmp("abc", "abd"));   // negatif
printf("%d\n", strcmp("abd", "abc"));   // positif
```

## Les caractères spéciaux

Vus au chapitre 04 : `\n`, `\t`, `\\`, `\"`, `\'`, `\0`, `\a`, `\r`.

Pour insérer un guillemet dans une chaîne :

```c
char txt[] = "Il a dit \"bonjour\".";
```

## `<ctype.h>` : tester et transformer des caractères

```c
#include <ctype.h>

isalpha(c)   // lettre ?
isdigit(c)   // chiffre ?
isspace(c)   // espace, tabulation, retour a la ligne ?
isupper(c)   // majuscule ?
islower(c)   // minuscule ?
toupper(c)   // renvoie la majuscule
tolower(c)   // renvoie la minuscule
```

```c
char mot[] = "Bonjour";
for (int i = 0; mot[i]; i++) {
    mot[i] = toupper(mot[i]);
}
printf("%s\n", mot);    // BONJOUR
```

## Exemple complet

Fichier [`code/17_strings.c`](code/17_strings.c).

## Exercice

1. Compte le nombre de voyelles dans une chaîne.
2. Écris une fonction qui inverse une chaîne sur place.
3. Vérifie si un mot est un palindrome (`radar`, `kayak`).
4. Concatène prénom et nom dans une seule chaîne, en vérifiant que la destination est assez grande.

---
⬅️ [16 — Tableaux](16-tableaux.md) | ➡️ [18 — Saisie utilisateur](18-saisie-utilisateur.md)
