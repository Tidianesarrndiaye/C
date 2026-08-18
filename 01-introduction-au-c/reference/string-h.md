# `<string.h>` — chaînes de caractères

## Longueur et copie

| Fonction | Rôle |
|---|---|
| `strlen(s)` | longueur, sans le `'\0'` |
| `strcpy(dest, src)` | copie (⚠️ aucune vérification de taille) |
| `strncpy(dest, src, n)` | copie au plus `n` caractères (⚠️ peut ne pas terminer par `'\0'`) |
| `memcpy(dest, src, n)` | copie `n` octets (zones disjointes) |
| `memmove(dest, src, n)` | idem, zones pouvant se chevaucher |

Plus sûr que `strcpy` :

```c
snprintf(dest, sizeof(dest), "%s", src);   // tronque et termine toujours par '\0'
```

## Concaténation

| Fonction | Rôle |
|---|---|
| `strcat(dest, src)` | ajoute `src` à la fin de `dest` |
| `strncat(dest, src, n)` | ajoute au plus `n` caractères |

## Comparaison

| Fonction | Rôle |
|---|---|
| `strcmp(a, b)` | 0 si égales, <0 si `a<b`, >0 si `a>b` |
| `strncmp(a, b, n)` | compare les `n` premiers caractères |
| `memcmp(a, b, n)` | compare `n` octets bruts |

```c
if (strcmp(a, b) == 0) { /* chaines identiques */ }
```

⚠️ `a == b` compare des **adresses**, jamais le contenu.

## Recherche

| Fonction | Rôle |
|---|---|
| `strchr(s, c)` | 1re occurrence de `c`, ou `NULL` |
| `strrchr(s, c)` | dernière occurrence de `c` |
| `strstr(s, sub)` | 1re occurrence de la sous-chaîne |
| `strspn(s, set)` | longueur du préfixe composé de caractères de `set` |
| `strcspn(s, set)` | longueur du préfixe **sans** caractère de `set` |
| `strtok(s, delim)` | découpe en morceaux (⚠️ modifie `s`) |

Idiome à connaître — supprimer le `\n` laissé par `fgets` :

```c
ligne[strcspn(ligne, "\n")] = '\0';
```

## Mémoire brute

| Fonction | Rôle |
|---|---|
| `memset(ptr, valeur, n)` | remplit `n` octets |
| `memchr(ptr, c, n)` | cherche un octet |

```c
memset(tab, 0, sizeof(tab));    // met tout a zero
```

## Erreurs

| Fonction | Rôle |
|---|---|
| `strerror(errno)` | message correspondant au code d'erreur |
