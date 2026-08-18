# `<time.h>` — date et heure

## Types

| Type | Rôle |
|---|---|
| `time_t` | secondes depuis le 1er janvier 1970 (epoch Unix) |
| `struct tm` | date décomposée |
| `clock_t` | temps processeur |

## Fonctions

| Fonction | Rôle |
|---|---|
| `time(NULL)` | instant présent en `time_t` |
| `localtime(&t)` | `time_t` → `struct tm` (heure locale) |
| `gmtime(&t)` | `time_t` → `struct tm` (UTC) |
| `mktime(&tm)` | `struct tm` → `time_t` |
| `ctime(&t)` | `time_t` → chaîne (`Mon Aug 18 09:15:42 2026\n`) |
| `asctime(&tm)` | `struct tm` → chaîne |
| `strftime(buf, n, fmt, &tm)` | formatage personnalisé |
| `difftime(t2, t1)` | différence en secondes (`double`) |
| `clock()` | temps processeur écoulé |

## Champs de `struct tm`

| Champ | Plage | Piège |
|---|---|---|
| `tm_sec` | 0–60 | |
| `tm_min` | 0–59 | |
| `tm_hour` | 0–23 | |
| `tm_mday` | 1–31 | |
| `tm_mon` | **0–11** | janvier = 0 → `+1` pour l'affichage |
| `tm_year` | depuis 1900 | 2026 → 126 → `+1900` pour l'affichage |
| `tm_wday` | 0–6 | 0 = dimanche |
| `tm_yday` | 0–365 | |
| `tm_isdst` | | >0 si heure d'été |

## Formats de `strftime`

| Code | Sens | Code | Sens |
|---|---|---|---|
| `%d` | jour 01–31 | `%H` | heure 00–23 |
| `%m` | mois 01–12 | `%M` | minute |
| `%Y` | année 4 chiffres | `%S` | seconde |
| `%A` | jour, nom long | `%B` | mois, nom long |
| `%a` | jour, nom court | `%b` | mois, nom court |
| `%F` | `%Y-%m-%d` | `%T` | `%H:%M:%S` |
| `%j` | jour de l'année | `%p` | AM/PM |

## Recettes

```c
// Date formatee
char buf[64];
time_t t = time(NULL);
strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", localtime(&t));

// Mesurer une duree
clock_t d = clock();
/* … */
printf("%.4f s\n", (double)(clock() - d) / CLOCKS_PER_SEC);

// Initialiser le generateur aleatoire
srand((unsigned) time(NULL));
```
