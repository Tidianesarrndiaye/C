# 18 — La saisie utilisateur

> Équivalent W3Schools : **C User Input**

`printf` écrit vers la sortie ; `scanf` lit ce que l'utilisateur tape.

## `scanf`

```c
#include <stdio.h>

int main(void) {
    int age;

    printf("Quel est ton age ? ");
    scanf("%d", &age);              // ⚠️ le & est obligatoire

    printf("Tu as %d ans.\n", age);
    return 0;
}
```

### Pourquoi le `&` ?

`scanf` doit **écrire dans ta variable**. En C, les arguments sont passés par copie : sans `&`,
`scanf` recevrait la valeur d'`age` et ne pourrait rien modifier. `&age` signifie « l'adresse de
`age` » — on lui dit **où** écrire. C'est le premier contact avec les pointeurs (chapitres 19-20).

Oublier le `&` est l'erreur la plus fréquente avec `scanf` : le programme plante ou corrompt la
mémoire. `gcc -Wall` t'avertit.

## Les spécificateurs de `scanf`

| Type | scanf | printf |
|---|---|---|
| `int` | `%d` | `%d` |
| `float` | `%f` | `%f` |
| `double` | **`%lf`** | `%f` |
| `char` | `%c` | `%c` |
| chaîne | `%s` | `%s` |

⚠️ Attention à `double` : c'est `%lf` en lecture et `%f` en affichage.

## Lire plusieurs valeurs

```c
int a, b;
printf("Deux nombres : ");
scanf("%d %d", &a, &b);
printf("Somme : %d\n", a + b);
```

## Lire une chaîne — et le danger de `%s`

```c
char nom[30];
printf("Ton prenom : ");
scanf("%s", nom);          // pas de & : un tableau est deja une adresse
printf("Bonjour %s\n", nom);
```

Deux problèmes majeurs :

1. **`%s` s'arrête au premier espace.** « Tidiane Ndiaye » ne donne que « Tidiane ».
2. **Aucune limite de taille.** Si l'utilisateur tape 100 caractères dans un `char[30]`, la
   mémoire est écrasée : c'est le *buffer overflow*.

Correctif minimal — borner la largeur :

```c
char nom[30];
scanf("%29s", nom);        // au plus 29 caracteres + le '\0'
```

## `fgets` : la bonne façon de lire une ligne

```c
char nom[50];
printf("Ton nom complet : ");
fgets(nom, sizeof(nom), stdin);
printf("Bonjour %s", nom);
```

`fgets` lit **toute la ligne, espaces compris**, et ne dépasse jamais la taille indiquée.
Seul défaut : elle garde le `\n` final. On l'enlève ainsi :

```c
#include <string.h>

nom[strcspn(nom, "\n")] = '\0';   // idiome standard pour couper le retour a la ligne
```

**Recommandation : utilise `fgets` pour les chaînes, `scanf` uniquement pour les nombres.**

## Le piège du `\n` resté dans le tampon

```c
int age;
char nom[50];

scanf("%d", &age);          // laisse le '\n' de la touche Entree dans le tampon
fgets(nom, sizeof(nom), stdin);   // ⚠️ lit ce '\n' et repart immediatement !
```

Trois solutions :

```c
// 1. Vider le tampon apres le scanf
int c;
while ((c = getchar()) != '\n' && c != EOF) { }

// 2. Ajouter un espace dans le format pour ignorer les blancs (utile avant %c)
scanf(" %c", &lettre);

// 3. Tout lire avec fgets, puis convertir avec sscanf
char ligne[64];
fgets(ligne, sizeof(ligne), stdin);
sscanf(ligne, "%d", &age);
```

La troisième est la plus robuste, et c'est celle qu'utilisent les programmes sérieux.

## Vérifier que la saisie a réussi

`scanf` renvoie **le nombre de valeurs correctement lues**. Ne l'ignore pas :

```c
int age;
if (scanf("%d", &age) != 1) {
    printf("Saisie invalide\n");
    return 1;
}
```

Si l'utilisateur tape « abc » alors que tu attends un `%d`, sans cette vérification `age` reste
non initialisé et le texte reste bloqué dans le tampon → boucle infinie garantie.

## Exemple complet

Fichier [`code/18_input.c`](code/18_input.c) :

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char nom[50];
    int age;
    char ligne[64];

    printf("Ton nom : ");
    fgets(nom, sizeof(nom), stdin);
    nom[strcspn(nom, "\n")] = '\0';

    printf("Ton age : ");
    fgets(ligne, sizeof(ligne), stdin);
    if (sscanf(ligne, "%d", &age) != 1) {
        printf("Age invalide.\n");
        return 1;
    }

    printf("\nBonjour %s, tu auras %d ans l'an prochain.\n", nom, age + 1);
    return 0;
}
```

Test au terminal.

**Linux / WSL** (et shell MSYS2)

```bash
gcc -Wall -Wextra -std=c17 code/18_input.c -o /tmp/prog && /tmp/prog
```

**Windows — PowerShell**

```powershell
gcc -Wall -Wextra -std=c17 code\18_input.c -o prog.exe
if ($?) { .\prog.exe }
```

Tu peux aussi lui donner l'entrée directement, sans taper :

**Linux / WSL**

```bash
printf "Tidiane\n25\n" | /tmp/prog
```

**Windows — PowerShell** — `printf` n'existe pas ici ; on envoie un tableau de lignes dans le
tuyau, et PowerShell ajoute les retours à la ligne :

```powershell
"Tidiane", "25" | .\prog.exe
```

## Exercice

1. Demande deux nombres et affiche leur somme, différence, produit et quotient (attention à la
   division par zéro).
2. Demande un mot et affiche-le à l'envers.
3. Fais une petite calculatrice : deux nombres et un opérateur (`+ - * /`), traités par un
   `switch`.
4. Boucle avec `do… while` jusqu'à ce que l'utilisateur entre un nombre entre 1 et 10.

---
⬅️ [17 — Chaînes de caractères](17-chaines-de-caracteres.md) | ➡️ [19 — Adresse mémoire](19-adresse-memoire.md)
