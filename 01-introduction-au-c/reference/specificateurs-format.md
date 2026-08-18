# Spécificateurs de format (`printf` / `scanf`)

## Les types

| Code | Type | printf | scanf |
|---|---|---|---|
| `%d` / `%i` | `int` | ✅ | ✅ |
| `%u` | `unsigned int` | ✅ | ✅ |
| `%hd` | `short` | ✅ | ✅ |
| `%ld` | `long` | ✅ | ✅ |
| `%lld` | `long long` | ✅ | ✅ |
| `%lu` | `unsigned long` | ✅ | ✅ |
| `%f` | `float` / `double` | ✅ | `%f` pour float |
| `%lf` | `double` | ✅ (identique à `%f`) | ✅ **obligatoire** |
| `%Lf` | `long double` | ✅ | ✅ |
| `%e` / `%E` | notation scientifique | ✅ | ✅ |
| `%g` | `%f` ou `%e`, le plus court | ✅ | ✅ |
| `%c` | `char` | ✅ | ✅ |
| `%s` | chaîne | ✅ | ✅ |
| `%p` | pointeur | ✅ | — |
| `%x` / `%X` | hexadécimal | ✅ | ✅ |
| `%o` | octal | ✅ | ✅ |
| `%zu` | `size_t` (retour de `sizeof`) | ✅ | ✅ |
| `%%` | un `%` littéral | ✅ | — |

## Les options de mise en forme (printf)

`%[drapeaux][largeur][.précision][modificateur]type`

| Exemple | Résultat |
|---|---|
| `%5d` | `   42` — largeur minimale 5, aligné à droite |
| `%-5d` | `42   ` — aligné à gauche |
| `%05d` | `00042` — complété par des zéros |
| `%+d` | `+42` — signe toujours affiché |
| `%.2f` | `3.14` — 2 décimales |
| `%8.2f` | `    3.14` — largeur 8, 2 décimales |
| `%-10s` | `Tidiane   ` — chaîne alignée à gauche sur 10 |
| `%.3s` | `Tid` — au plus 3 caractères |
| `%*d` | largeur donnée en argument : `printf("%*d", 5, n)` |

## Pièges

- `double` : `%lf` en lecture (`scanf`), `%f` en écriture (`printf`).
- `%s` dans `scanf` s'arrête au premier espace — préfère `fgets`.
- Toujours borner : `scanf("%29s", tampon)` pour un `char[30]`.
- Un mauvais spécificateur ne provoque pas d'erreur à l'exécution, juste un affichage faux :
  compile avec `-Wall` pour être averti.
