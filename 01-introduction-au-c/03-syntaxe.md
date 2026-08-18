# 03 — La syntaxe du C

> Équivalent W3Schools : **C Syntax**

Reprenons le programme minimal, ligne par ligne :

```c
#include <stdio.h>

int main(void) {
    printf("Hello World!");
    return 0;
}
```

## Ligne 1 — `#include <stdio.h>`

C'est une **directive du préprocesseur**. Avant même la compilation, le préprocesseur remplace
cette ligne par le contenu du fichier d'en-tête `stdio.h` (*standard input output header*), qui
contient les déclarations de `printf`, `scanf`, `fopen`…

Sans cette ligne, le compilateur ne connaîtrait pas `printf`.

> Analogie : c'est l'équivalent de `import` en Python ou de `import`/`require` en JavaScript,
> sauf que c'est une **copie de texte** faite avant la compilation, pas un chargement de module.

Note : pas de `;` à la fin d'une directive `#`.

## Ligne 3 — `int main(void)`

`main` est le **point d'entrée** : c'est la fonction que le système appelle au lancement du
programme. Tout programme C en a exactement une.

- `int` : le type de la valeur renvoyée.
- `void` entre parenthèses : la fonction ne prend aucun paramètre. (On verra plus tard la forme
  `int main(int argc, char *argv[])` pour lire les arguments de la ligne de commande.)

## Les accolades `{ }`

Elles délimitent un **bloc** de code — exactement comme en JavaScript.

## Ligne 4 — `printf("Hello World!");`

`printf` (*print formatted*) affiche du texte dans le terminal. Toute **instruction** se termine
par un **point-virgule `;`**. En JavaScript il est facultatif ; en C il est **obligatoire**.

## Ligne 5 — `return 0;`

`main` renvoie un code de sortie au système : `0` = tout s'est bien passé, autre valeur = erreur.

Vérifie-le au terminal après avoir lancé ton programme :

```bash
./hello
echo $?      # affiche 0
```

C'est ce code que les scripts shell et les outils de CI utilisent pour savoir si ton programme a
réussi.

## Règles générales de syntaxe

- Le C est **sensible à la casse** : `maVariable`, `mavariable` et `MaVariable` sont trois choses
  différentes. `Int` n'est pas `int`.
- Les **espaces et retours à la ligne** n'ont aucune importance pour le compilateur. Ceci compile :
  ```c
  int main(void){printf("Hello");return 0;}
  ```
  … mais ne l'écris jamais. L'indentation est pour les humains.
- Chaque instruction se termine par `;`.
- Les blocs (`if`, `for`, fonctions…) se délimitent avec `{ }`.

## Convention d'écriture recommandée

```c
#include <stdio.h>

int main(void) {
    int age = 25;

    if (age >= 18) {
        printf("Majeur\n");
    } else {
        printf("Mineur\n");
    }

    return 0;
}
```

- 4 espaces d'indentation (ou une tabulation, mais sois cohérent).
- Accolade ouvrante sur la même ligne, fermante seule sur sa ligne.
- Un espace après `if`, `for`, `while` ; pas d'espace avant `(` d'un appel de fonction.

---
⬅️ [02 — Démarrer](02-demarrer.md) | ➡️ [04 — Afficher du texte](04-sortie-output.md)
