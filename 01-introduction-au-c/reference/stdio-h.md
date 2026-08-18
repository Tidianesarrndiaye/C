# `<stdio.h>` — entrées/sorties

## Sortie

| Fonction | Rôle |
|---|---|
| `printf(format, …)` | affiche du texte formaté sur `stdout` |
| `fprintf(f, format, …)` | idem, vers un fichier ou `stderr` |
| `sprintf(buf, format, …)` | écrit dans une chaîne (⚠️ pas de limite de taille) |
| `snprintf(buf, n, format, …)` | ✅ version sûre de `sprintf` |
| `puts(s)` | affiche une chaîne + `\n` |
| `fputs(s, f)` | écrit une chaîne dans un fichier (sans `\n`) |
| `putchar(c)` | affiche un caractère |
| `fputc(c, f)` | écrit un caractère dans un fichier |

## Entrée

| Fonction | Rôle |
|---|---|
| `scanf(format, …)` | lit une entrée formatée (⚠️ `&` obligatoire) |
| `fscanf(f, format, …)` | lit depuis un fichier |
| `sscanf(s, format, …)` | lit depuis une chaîne |
| `fgets(buf, n, f)` | ✅ lit une ligne, taille bornée |
| `fgetc(f)` / `getchar()` | lit un caractère (renvoie un `int`, `EOF` à la fin) |

> `gets()` a été **supprimée de la norme** : jamais de limite de taille, faille garantie.
> Utilise `fgets`.

## Fichiers

| Fonction | Rôle |
|---|---|
| `fopen(nom, mode)` | ouvre, renvoie `FILE *` ou `NULL` |
| `fclose(f)` | ferme et vide le tampon |
| `feof(f)` | fin de fichier atteinte |
| `ferror(f)` | erreur survenue |
| `fflush(f)` | force l'écriture du tampon |
| `fseek(f, off, orig)` | déplace le curseur |
| `ftell(f)` | position courante |
| `rewind(f)` | retour au début |
| `fread(ptr, taille, n, f)` | lecture binaire |
| `fwrite(ptr, taille, n, f)` | écriture binaire |
| `remove(nom)` | supprime un fichier |
| `rename(a, b)` | renomme |
| `perror(msg)` | affiche `msg: description de l'erreur` |

### Modes de `fopen`

`"r"` lecture · `"w"` écriture (écrase) · `"a"` ajout · `"r+"` `"w+"` `"a+"` lecture+écriture ·
suffixe `b` pour le binaire.

## Flux standards

`stdin` (clavier) · `stdout` (écran) · `stderr` (erreurs, non tamponné)
