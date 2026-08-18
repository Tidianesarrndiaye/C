# 04 — Afficher du texte (output)

> Équivalent W3Schools : **C Output (Print Text)** et **C New Lines**

## `printf`

Pour afficher quelque chose, on utilise la fonction `printf`, fournie par `<stdio.h>`.
Le texte à afficher se met entre **guillemets doubles** `"` :

```c
#include <stdio.h>

int main(void) {
    printf("Hello World!");
    return 0;
}
```

Tu peux appeler `printf` autant de fois que tu veux :

```c
printf("Hello World!");
printf("J'apprends le C.");
printf("Et ça marche.");
```

Sortie :

```
Hello World!J'apprends le C.Et ça marche.
```

Tout est collé ! Contrairement à `print()` en Python ou `console.log()` en JavaScript,
**`printf` ne va pas à la ligne tout seul**.

## Le retour à la ligne : `\n`

Pour aller à la ligne, on insère le caractère d'échappement `\n` (*new line*) :

```c
printf("Hello World!\n");
printf("J'apprends le C.\n");
printf("Et ça marche.\n");
```

Sortie :

```
Hello World!
J'apprends le C.
Et ça marche.
```

On peut en mettre plusieurs, et n'importe où dans la chaîne :

```c
printf("Hello World!\n\n");        // une ligne vide après
printf("Hello\nWorld!\n");         // deux lignes en un seul printf
```

## Les principaux caractères d'échappement

| Séquence | Effet |
|---|---|
| `\n` | retour à la ligne |
| `\t` | tabulation horizontale |
| `\\` | une barre oblique inverse `\` |
| `\"` | un guillemet double `"` |
| `\'` | une apostrophe `'` |
| `\0` | caractère nul (marque la fin d'une chaîne — chapitre 17) |
| `\a` | bip sonore |
| `\r` | retour chariot (début de ligne, sans descendre) |

```c
printf("Nom\tAge\n");
printf("Tidiane\t25\n");
printf("Il a dit : \"Bonjour\"\n");
printf("Chemin : C:\\Users\\tidia\n");
```

Sortie :

```
Nom	Age
Tidiane	25
Il a dit : "Bonjour"
Chemin : C:\Users\tidia
```

## `puts` : l'alternative simple

Quand tu veux juste afficher une chaîne suivie d'un retour à la ligne :

```c
puts("Hello World!");    // équivaut à printf("Hello World!\n");
```

`puts` ajoute le `\n` automatiquement. Elle est plus simple et plus sûre que `printf` quand il n'y
a aucune valeur à insérer.

> ⚠️ Ne fais **jamais** `printf(texte_variable)` avec une chaîne qui vient de l'utilisateur : si
> elle contient un `%`, `printf` va essayer de lire un argument inexistant. Écris
> `printf("%s", texte_variable)` ou `puts(texte_variable)`.

## Afficher des valeurs : les spécificateurs de format

`printf` s'appelle « print **formatted** » parce qu'elle sait insérer des valeurs dans le texte,
grâce à des marqueurs commençant par `%` :

```c
int age = 25;
printf("J'ai %d ans.\n", age);
```

Sortie : `J'ai 25 ans.`

C'est l'équivalent des f-strings de Python (`f"J'ai {age} ans"`) ou des template literals de
JavaScript, en plus rigide : **il faut dire le type**. On détaille tous les spécificateurs au
chapitre 06.

Aperçu rapide :

| Spécificateur | Type |
|---|---|
| `%d` | `int` (entier) |
| `%f` | `float` / `double` |
| `%c` | `char` (un caractère) |
| `%s` | chaîne de caractères |

```c
int age = 25;
float taille = 1.82;
char initiale = 'T';
printf("%c a %d ans et mesure %.2f m\n", initiale, age, taille);
```

Sortie : `T a 25 ans et mesure 1.82 m`

## Exemple complet

Fichier [`code/04_output.c`](code/04_output.c) :

```c
#include <stdio.h>

int main(void) {
    printf("=== Sortie en C ===\n\n");

    printf("Sans retour a la ligne : ");
    printf("suite immediate\n\n");

    printf("Tabulation :\tvaleur alignee\n");
    printf("Guillemets : \"comme ceci\"\n");
    printf("Barre oblique : \\ \n\n");

    puts("puts ajoute le retour a la ligne tout seul");

    return 0;
}
```

**Linux / WSL** (et shell MSYS2)

```bash
gcc -Wall -Wextra -std=c17 code/04_output.c -o /tmp/prog && /tmp/prog
```

**Windows — PowerShell**

```powershell
gcc -Wall -Wextra -std=c17 code\04_output.c -o prog.exe
if ($?) { .\prog.exe }
```

## Exercice

Écris un programme qui affiche exactement ceci (une seule instruction `printf`) :

```
Nom     : Tidiane
Langage : C
Statut  : "en cours d'apprentissage"
```

---
⬅️ [03 — Syntaxe](03-syntaxe.md) | ➡️ [05 — Commentaires](05-commentaires.md)
