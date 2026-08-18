# 32 — Date et heure

> Équivalent W3Schools : **C Date**

Tout est dans `<time.h>`.

## L'heure actuelle

```c
#include <stdio.h>
#include <time.h>

int main(void) {
    time_t maintenant = time(NULL);
    printf("%s", ctime(&maintenant));     // Mon Aug 18 09:15:42 2026
    return 0;
}
```

- `time_t` est un entier : le nombre de **secondes écoulées depuis le 1er janvier 1970** (l'« epoch »
  Unix).
- `time(NULL)` renvoie l'instant présent.
- `ctime()` le convertit en chaîne lisible — et ajoute déjà un `\n`.

```c
printf("%ld secondes depuis 1970\n", (long) maintenant);
```

## Décomposer une date : `struct tm`

```c
time_t t = time(NULL);
struct tm *d = localtime(&t);       // heure locale
// struct tm *d = gmtime(&t);       // heure UTC
```

Les champs de `struct tm` :

| Champ | Contenu | ⚠️ |
|---|---|---|
| `tm_sec` | secondes | 0–60 |
| `tm_min` | minutes | 0–59 |
| `tm_hour` | heures | 0–23 |
| `tm_mday` | jour du mois | 1–31 |
| `tm_mon` | mois | **0–11** (janvier = 0 !) |
| `tm_year` | année | **depuis 1900** (2026 → 126) |
| `tm_wday` | jour de la semaine | 0 = dimanche |
| `tm_yday` | jour de l'année | 0–365 |
| `tm_isdst` | heure d'été | >0 si active |

Les deux pièges (`tm_mon` et `tm_year`) sont sources de bugs à chaque fois :

```c
printf("%02d/%02d/%d\n", d->tm_mday, d->tm_mon + 1, d->tm_year + 1900);
```

## Formater : `strftime`

La méthode propre pour afficher une date :

```c
char tampon[100];
time_t t = time(NULL);
struct tm *d = localtime(&t);

strftime(tampon, sizeof(tampon), "%d/%m/%Y %H:%M:%S", d);
printf("%s\n", tampon);          // 18/08/2026 09:15:42
```

### Les formats les plus utiles

| Code | Signification | Exemple |
|---|---|---|
| `%d` | jour (01–31) | `18` |
| `%m` | mois (01–12) | `08` |
| `%Y` | année sur 4 chiffres | `2026` |
| `%y` | année sur 2 chiffres | `26` |
| `%H` `%M` `%S` | heure, minute, seconde | `09` `15` `42` |
| `%A` / `%a` | jour de la semaine, long / court | `Tuesday` / `Tue` |
| `%B` / `%b` | mois, long / court | `August` / `Aug` |
| `%j` | jour de l'année | `230` |
| `%p` | AM/PM | `AM` |
| `%x` `%X` | date / heure au format local | |
| `%F` | équivaut à `%Y-%m-%d` | `2026-08-18` |
| `%T` | équivaut à `%H:%M:%S` | `09:15:42` |

Pour avoir les noms en français, il faut passer par la locale :

```c
#include <locale.h>
setlocale(LC_TIME, "fr_FR.UTF-8");
```

(Encore faut-il que cette locale soit installée sur le système.)

## Construire une date précise : `mktime`

```c
struct tm date = {0};          // ⚠️ toujours initialiser a zero
date.tm_year = 2000 - 1900;
date.tm_mon  = 8 - 1;          // aout
date.tm_mday = 18;

time_t t = mktime(&date);      // remplit aussi tm_wday et tm_yday
printf("%s", ctime(&t));
```

## Différences entre deux dates : `difftime`

```c
double secondes = difftime(t2, t1);        // t2 - t1, en secondes
printf("%.0f jours\n", secondes / 86400);
```

### Calculer un âge

```c
struct tm naissance = {0};
naissance.tm_year = 2000 - 1900;
naissance.tm_mon  = 8 - 1;
naissance.tm_mday = 18;

time_t t_naiss = mktime(&naissance);
time_t t_now   = time(NULL);

double ans = difftime(t_now, t_naiss) / (365.2425 * 24 * 3600);
printf("Age : %.0f ans\n", ans);
```

## Mesurer une durée d'exécution

```c
#include <time.h>

clock_t debut = clock();
// … traitement long …
clock_t fin = clock();

double duree = (double)(fin - debut) / CLOCKS_PER_SEC;
printf("Duree : %.4f s\n", duree);
```

`clock()` mesure le **temps processeur**, pas le temps réel écoulé. Pour ce dernier, utilise
`time()` (précision : la seconde) ou `clock_gettime(CLOCK_MONOTONIC, …)` (précision : la
nanoseconde).

Depuis le terminal, le plus simple reste :

```bash
time ./prog
```

## Résumé des types

| Type | Rôle |
|---|---|
| `time_t` | secondes depuis 1970 (un entier) |
| `struct tm` | date décomposée (année, mois, jour…) |
| `clock_t` | temps processeur |

| Fonction | Rôle |
|---|---|
| `time(NULL)` | instant présent |
| `localtime(&t)` | `time_t` → `struct tm` (local) |
| `gmtime(&t)` | `time_t` → `struct tm` (UTC) |
| `mktime(&tm)` | `struct tm` → `time_t` |
| `ctime(&t)` / `asctime(&tm)` | → chaîne prête à l'emploi |
| `strftime(…)` | → chaîne formatée à ta guise |
| `difftime(t2, t1)` | différence en secondes |
| `clock()` | temps processeur écoulé |

## Exercice

1. Affiche la date et l'heure actuelles au format `Mardi 18 août 2026, 09h15`.
2. Calcule combien de jours te séparent d'une date future.
3. Calcule ton âge exact en jours.
4. Mesure le temps d'exécution d'une boucle qui compte jusqu'à un milliard.

---
⬅️ [31 — Erreurs et débogage](31-erreurs-et-debogage.md) | ➡️ [33 — Projets](33-projets.md)
