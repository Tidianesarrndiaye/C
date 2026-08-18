# Les mots-clés du C

Ces mots sont réservés : tu ne peux pas les utiliser comme noms de variables ou de fonctions.

## Les 32 mots-clés d'origine (C89)

| | | | |
|---|---|---|---|
| `auto` | `break` | `case` | `char` |
| `const` | `continue` | `default` | `do` |
| `double` | `else` | `enum` | `extern` |
| `float` | `for` | `goto` | `if` |
| `int` | `long` | `register` | `return` |
| `short` | `signed` | `sizeof` | `static` |
| `struct` | `switch` | `typedef` | `union` |
| `unsigned` | `void` | `volatile` | `while` |

## Ajouts C99

`inline`, `restrict`, `_Bool`, `_Complex`, `_Imaginary`

## Ajouts C11

`_Alignas`, `_Alignof`, `_Atomic`, `_Generic`, `_Noreturn`, `_Static_assert`, `_Thread_local`

## Ce qu'ils veulent dire

| Mot-clé | Rôle |
|---|---|
| `auto` | classe de stockage par défaut d'une variable locale (jamais écrit en pratique) |
| `break` | sort d'une boucle ou d'un `switch` |
| `case` | une branche d'un `switch` |
| `char` | type caractère (1 octet) |
| `const` | valeur non modifiable |
| `continue` | passe au tour de boucle suivant |
| `default` | branche par défaut d'un `switch` |
| `do` | boucle `do… while` |
| `double` | décimal double précision |
| `else` | alternative d'un `if` |
| `enum` | énumération |
| `extern` | déclare un symbole défini dans un autre fichier |
| `float` | décimal simple précision |
| `for` | boucle comptée |
| `goto` | saut vers une étiquette (à éviter) |
| `if` | condition |
| `inline` | suggère l'inlining d'une fonction |
| `int` | type entier |
| `long` | modificateur : entier plus large |
| `register` | suggestion obsolète de stockage en registre |
| `restrict` | promet qu'un pointeur est le seul accès à sa cible |
| `return` | renvoie une valeur et termine la fonction |
| `short` | modificateur : entier plus petit |
| `signed` | avec signe (par défaut) |
| `sizeof` | taille en octets |
| `static` | conserve la valeur entre appels / limite la visibilité au fichier |
| `struct` | structure |
| `switch` | aiguillage multiple |
| `typedef` | crée un alias de type |
| `union` | zone mémoire partagée entre plusieurs types |
| `unsigned` | sans signe |
| `void` | absence de type / de valeur |
| `volatile` | la valeur peut changer hors du programme (matériel, interruption) |
| `while` | boucle conditionnelle |
