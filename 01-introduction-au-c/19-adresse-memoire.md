# 19 — L'adresse mémoire

> Équivalent W3Schools : **C Memory Address**

À partir d'ici commence ce qui rend le C différent de tout ce que tu as fait en Python ou en
JavaScript. Prends ton temps sur les chapitres 19, 20 et 30.

## Chaque variable a une adresse

Quand tu déclares une variable, le système lui réserve un emplacement en mémoire (la RAM). Cet
emplacement a un **numéro** : son adresse.

```c
#include <stdio.h>

int main(void) {
    int age = 25;

    printf("Valeur  : %d\n", age);
    printf("Adresse : %p\n", (void *) &age);
    return 0;
}
```

Sortie (le nombre change à chaque exécution) :

```
Valeur  : 25
Adresse : 0x7ffd4a8b3c5c
```

- `&` est l'**opérateur d'adresse** : `&age` = « l'adresse de `age` ».
- `%p` est le spécificateur pour les adresses ; on les affiche en hexadécimal.
- Le cast `(void *)` est la forme correcte pour `%p` (`-Wall` le réclame).

## Une image mentale

Vois la mémoire comme une longue rue de maisons numérotées. Chaque maison fait un octet.

```
adresse : 1000   1001   1002   1003   1004   1005   1006   1007
contenu : [        age = 25          ][      taille = 1.82      ]
             (un int occupe 4 octets)
```

`&age` te donne 1000 : le numéro de la première maison occupée par `age`.

## Les adresses sont contiguës

```c
int a = 1, b = 2, c = 3;
printf("%p\n", (void *) &a);
printf("%p\n", (void *) &b);
printf("%p\n", (void *) &c);
```

Tu verras trois adresses proches, séparées de 4 octets (`sizeof(int)`) — l'ordre exact dépend du
compilateur.

Sur un tableau, c'est net :

```c
int notes[4] = {12, 15, 8, 19};
for (int i = 0; i < 4; i++) {
    printf("notes[%d] : valeur %2d — adresse %p\n", i, notes[i], (void *) &notes[i]);
}
```

Chaque case est exactement 4 octets après la précédente. **Un tableau, c'est un bloc contigu**,
et c'est pour ça que `notes[i]` est instantané : l'ordinateur calcule `adresse_de_depart + i × 4`.

## Le nom d'un tableau EST une adresse

```c
int notes[4];
printf("%p\n", (void *) notes);        // adresse du tableau
printf("%p\n", (void *) &notes[0]);    // la meme !
```

C'est pourquoi on n'écrit pas `&` devant un tableau avec `scanf("%s", nom)` : il est déjà une
adresse.

## À quoi ça sert concrètement ?

Trois usages, que tu as déjà croisés ou que tu vas croiser :

1. **`scanf("%d", &age)`** — donner à une fonction l'endroit où écrire.
2. **Modifier une variable depuis une fonction** — sans adresse, c'est impossible en C
   (chapitre 22).
3. **Manipuler de grosses données sans les copier** — passer l'adresse d'une structure de 10 Ko
   coûte 8 octets au lieu de 10 Ko (chapitre 28).

## Exercice

1. Affiche la valeur et l'adresse de trois variables de types différents.
2. Affiche l'adresse de chaque case d'un tableau de 5 `int`, puis d'un tableau de 5 `char`.
   Compare l'écart entre les adresses : que remarques-tu ?
3. Vérifie que `tableau` et `&tableau[0]` donnent la même adresse.

---
⬅️ [18 — Saisie utilisateur](18-saisie-utilisateur.md) | ➡️ [20 — Pointeurs](20-pointeurs.md)
