# 12 — L'instruction switch

> Équivalent W3Schools : **C Switch**

Quand on compare une **même variable** à plusieurs valeurs précises, `switch` est plus lisible
qu'une chaîne de `else if`.

## Syntaxe

```c
switch (expression) {
    case valeur1:
        // code
        break;
    case valeur2:
        // code
        break;
    default:
        // code si aucun case ne correspond
}
```

## Exemple

```c
#include <stdio.h>

int main(void) {
    int jour = 4;

    switch (jour) {
        case 1:  printf("Lundi\n");    break;
        case 2:  printf("Mardi\n");    break;
        case 3:  printf("Mercredi\n"); break;
        case 4:  printf("Jeudi\n");    break;
        case 5:  printf("Vendredi\n"); break;
        case 6:  printf("Samedi\n");   break;
        case 7:  printf("Dimanche\n"); break;
        default: printf("Jour invalide\n");
    }
    return 0;
}
```

## Le rôle de `break`

`break` sort du `switch`. **Sans lui, l'exécution continue dans les cas suivants** — c'est le
*fall-through*, et c'est la source de bug numéro un avec `switch` :

```c
int jour = 4;
switch (jour) {
    case 4: printf("Jeudi\n");
    case 5: printf("Vendredi\n");     // s'affiche aussi !
    case 6: printf("Samedi\n");       // et celui-la aussi !
}
```

Sortie : `Jeudi` `Vendredi` `Samedi`.

### Le fall-through volontaire

Parfois on le veut, pour regrouper des cas :

```c
switch (jour) {
    case 6:
    case 7:
        printf("Week-end\n");
        break;
    default:
        printf("Jour de semaine\n");
}
```

Quand tu l'utilises exprès, mets un commentaire `/* fall through */` — les relecteurs (et
`-Wimplicit-fallthrough`) te remercieront.

## `default`

Le bloc `default` s'exécute si aucun `case` ne correspond. Il est facultatif, mais **mets-le
toujours** : il attrape les cas que tu n'avais pas prévus. Il peut être placé n'importe où, mais
par convention on le met à la fin (et là, son `break` est facultatif).

## Contraintes de `switch`

1. L'expression doit être de type **entier** (`int`, `char`, `enum`…). **Pas de `float`, pas de
   chaîne de caractères.**
   ```c
   switch (nom) { case "Tidiane": … }   // ❌ impossible en C
   ```
   Pour comparer des chaînes, il faut `strcmp` dans des `if` (chapitre 17).
2. Les `case` doivent être des **constantes** connues à la compilation (littéral, `#define`,
   `enum`), pas des variables.
3. Deux `case` ne peuvent pas avoir la même valeur.

## Avec des `char`

```c
char grade = 'B';

switch (grade) {
    case 'A': printf("Excellent\n"); break;
    case 'B': printf("Bien\n");      break;
    case 'C': printf("Moyen\n");     break;
    default:  printf("Note inconnue\n");
}
```

## Exemple concret — une calculatrice

Fichier [`code/12_switch.c`](code/12_switch.c) :

```c
#include <stdio.h>

int main(void) {
    double a = 12, b = 4;
    char op = '/';
    
    switch (op) {
        case '+': printf("%.2f\n", a + b); break;
        case '-': printf("%.2f\n", a - b); break;
        case '*': printf("%.2f\n", a * b); break;
        case '/':
            if (b == 0) {
                printf("Division par zero impossible\n");
            } else {
                printf("%.2f\n", a / b);
            }
            break;
        default:
            printf("Operateur inconnu : %c\n", op);
    }
    return 0;
}
```

## `switch` ou `if… else` ?

| Situation | Choix |
|---|---|
| Une variable entière comparée à des valeurs fixes | `switch` |
| Des intervalles (`note >= 14`) | `if… else` |
| Des conditions composées (`a > b && c`) | `if… else` |
| Des chaînes de caractères | `if… else` + `strcmp` |

## Exercice

Écris un menu : la variable `choix` vaut 1, 2, 3 ou 4, et le programme affiche « Ajouter »,
« Supprimer », « Lister », « Quitter », ou « Choix invalide ». Puis enlève un `break` et observe
le fall-through.

---
⬅️ [11 — if… else](11-if-else.md) | ➡️ [13 — Boucle while](13-boucle-while.md)
