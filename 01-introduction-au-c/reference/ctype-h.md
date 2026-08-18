# `<ctype.h>` — classification de caractères

Toutes ces fonctions prennent un `int` (le code du caractère) et renvoient une valeur non nulle
si le test est vrai.

## Tests

| Fonction | Vrai si… |
|---|---|
| `isalpha(c)` | lettre |
| `isdigit(c)` | chiffre `0`–`9` |
| `isalnum(c)` | lettre ou chiffre |
| `isspace(c)` | espace, `\t`, `\n`, `\r`, `\f`, `\v` |
| `isupper(c)` | majuscule |
| `islower(c)` | minuscule |
| `ispunct(c)` | ponctuation |
| `isprint(c)` | affichable (espace compris) |
| `isgraph(c)` | affichable, hors espace |
| `iscntrl(c)` | caractère de contrôle |
| `isxdigit(c)` | chiffre hexadécimal |

## Conversions

| Fonction | Rôle |
|---|---|
| `toupper(c)` | majuscule (inchangé si ce n'est pas une lettre) |
| `tolower(c)` | minuscule |

## Exemple

```c
#include <ctype.h>

void en_majuscules(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = (char) toupper((unsigned char) s[i]);
    }
}
```

> ⚠️ Le cast `(unsigned char)` est la forme correcte : passer un `char` signé négatif à ces
> fonctions est un comportement indéterminé. C'est un détail, mais c'est la bonne habitude.

## Attention aux accents

Ces fonctions ne gèrent que l'ASCII. `isalpha('é')` est faux en UTF-8, où `é` occupe deux octets.
Pour de vrai texte accentué, il faut `<wctype.h>` et les caractères larges.
