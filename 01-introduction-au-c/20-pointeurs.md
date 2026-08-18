# 20 — Les pointeurs

> Équivalent W3Schools : **C Pointers**, **Pointers & Arrays**

Un **pointeur** est une variable qui contient l'**adresse** d'une autre variable. C'est le concept
central du C : tout le reste (chaînes, tableaux, structures dynamiques, `malloc`) en découle.

## Déclarer un pointeur

```c
int age = 25;
int *ptr = &age;      // ptr contient l'adresse de age
```

- `int *ptr` : « `ptr` est un pointeur vers un `int` ».
- Le type compte : un `int *` et un `char *` ne se manipulent pas pareil.

Les trois écritures suivantes sont identiques pour le compilateur ; la deuxième est la plus
courante en C :

```c
int* ptr;    int *ptr;    int * ptr;
```

Attention avec les déclarations multiples :

```c
int* a, b;    // ⚠️ a est un pointeur, b est un simple int !
int *a, *b;   // ✅ les deux sont des pointeurs
```

## Les deux opérateurs

| Opérateur | Nom | Signification |
|---|---|---|
| `&` | opérateur d'adresse | donne l'adresse d'une variable |
| `*` | opérateur de déréférencement | donne la **valeur** à l'adresse contenue |

```c
#include <stdio.h>

int main(void) {
    int age = 25;
    int *ptr = &age;

    printf("age        : %d\n", age);           // 25
    printf("&age       : %p\n", (void *) &age); // 0x7ffd…
    printf("ptr        : %p\n", (void *) ptr);  // la meme adresse
    printf("*ptr       : %d\n", *ptr);          // 25  ← la valeur pointee

    return 0;
}
```

> ⚠️ Le `*` a **deux sens différents** :
> - à la **déclaration** (`int *ptr;`) il fait partie du type ;
> - à l'**utilisation** (`*ptr`) il déréférence, c'est-à-dire « va chercher la valeur là-bas ».

## Modifier par le pointeur

```c
int age = 25;
int *ptr = &age;

*ptr = 30;              // on ecrit A L'ADRESSE pointee
printf("%d\n", age);    // 30  ← age a change !
```

C'est ça, la puissance des pointeurs : agir sur une variable **sans y avoir accès directement**.
C'est exactement ce que fait `scanf("%d", &age)`.

## Le pointeur `NULL`

Un pointeur qui ne pointe sur rien vaut `NULL` :

```c
int *ptr = NULL;

if (ptr != NULL) {
    printf("%d\n", *ptr);
}
```

**Déréférencer un pointeur `NULL` fait planter le programme** (`Segmentation fault`). Deux règles :

1. Initialise toujours un pointeur — à `NULL` si tu n'as rien d'autre.
2. Teste avant de déréférencer.

Un pointeur non initialisé est pire que `NULL` : il contient une adresse aléatoire, et écrire
dedans corrompt silencieusement la mémoire.

```c
int *p;        // ❌ pointeur sauvage
int *p = NULL; // ✅
```

## Pointeurs et tableaux

Le nom d'un tableau est l'adresse de son premier élément. Ces deux lignes sont équivalentes :

```c
int notes[] = {12, 15, 8, 19};
int *p = notes;          // ou &notes[0]
```

On peut alors accéder aux éléments de deux façons :

```c
printf("%d\n", notes[2]);   // 8
printf("%d\n", *(p + 2));   // 8   ← arithmetique de pointeurs
printf("%d\n", p[2]);       // 8   ← un pointeur s'indexe aussi
```

### L'arithmétique de pointeurs

`p + 1` n'ajoute pas 1 octet, mais **la taille du type pointé**.

```c
int *p = notes;
printf("%p\n", (void *) p);       // 1000
printf("%p\n", (void *) (p + 1)); // 1004  (+ sizeof(int))
```

Parcours d'un tableau à la façon C :

```c
int notes[] = {12, 15, 8, 19};
for (int *p = notes; p < notes + 4; p++) {
    printf("%d ", *p);
}
```

C'est équivalent à la boucle avec indices, et souvent plus rapide historiquement. Les deux
styles se rencontrent dans du vrai code.

### Pointeurs et chaînes

```c
const char *msg = "Bonjour";
while (*msg != '\0') {
    printf("%c", *msg);
    msg++;
}
```

Voilà pourquoi une chaîne C est un `char *` : c'est simplement l'adresse du premier caractère, et
le `'\0'` dit où s'arrêter.

## Pointeurs et fonctions (aperçu)

Sans pointeur, une fonction ne peut pas modifier ses arguments :

```c
void doubler(int x)   { x = x * 2; }        // ne change rien a l'exterieur
void doubler2(int *x) { *x = *x * 2; }      // ✅ modifie la variable d'origine

int n = 5;
doubler(n);   printf("%d\n", n);   // 5
doubler2(&n); printf("%d\n", n);   // 10
```

C'est développé au chapitre 22.

## Récapitulatif visuel

```
    age                       ptr
 ┌────────┐               ┌────────────┐
 │   25   │  adresse 1000 │    1000    │  adresse 2000
 └────────┘               └────────────┘
      ▲                          │
      └──────────────────────────┘
          *ptr donne 25       ptr donne 1000       &ptr donne 2000
```

## Les erreurs classiques

| Erreur | Conséquence |
|---|---|
| Déréférencer `NULL` ou un pointeur non initialisé | `Segmentation fault` |
| Oublier le `*` en écrivant (`ptr = 30;` au lieu de `*ptr = 30;`) | le pointeur pointe vers l'adresse 30 → crash |
| Renvoyer l'adresse d'une variable locale | pointeur vers de la mémoire libérée |
| Confondre `int *a, b;` et `int *a, *b;` | `b` n'est pas un pointeur |

## Exemple complet

Fichier [`code/20_pointeurs.c`](code/20_pointeurs.c) — adresses, déréférencement, échange par
adresse, arithmétique de pointeurs et double résultat renvoyé par pointeurs.

## Exercice

1. Déclare une variable, un pointeur vers elle, et affiche : la valeur, l'adresse, le pointeur,
   la valeur déréférencée.
2. Écris une fonction `echanger(int *a, int *b)` qui échange deux valeurs. Teste-la.
3. Parcours un tableau uniquement avec un pointeur, sans utiliser `[]`.
4. Écris ta propre version de `strlen` en n'utilisant qu'un `char *`.

---
⬅️ [19 — Adresse mémoire](19-adresse-memoire.md) | ➡️ [21 — Fonctions](21-fonctions.md)
