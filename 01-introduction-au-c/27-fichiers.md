# 27 — Les fichiers

> Équivalent W3Schools : **C Files**, **Create/Write To Files**, **Read Files**

Tout se fait avec `<stdio.h>` et le type `FILE *`.

## Le cycle en trois temps

```
ouvrir (fopen)  →  lire / écrire  →  fermer (fclose)
```

## Ouvrir un fichier : `fopen`

```c
FILE *f = fopen("donnees.txt", "w");
```

### Les modes

| Mode | Effet | Si le fichier n'existe pas |
|---|---|---|
| `"r"` | lecture seule | échoue (`NULL`) |
| `"w"` | écriture — **vide le fichier existant** | le crée |
| `"a"` | ajout à la fin | le crée |
| `"r+"` | lecture + écriture | échoue |
| `"w+"` | lecture + écriture, vide le fichier | le crée |
| `"a+"` | lecture + ajout | le crée |

Ajoute `b` pour le mode binaire (`"rb"`, `"wb"`).

### Mode texte et mode binaire : la différence Linux / Windows

C'est **le** point du chapitre où les deux systèmes divergent vraiment.

| | Mode texte (`"r"`, `"w"`) | Mode binaire (`"rb"`, `"wb"`) |
|---|---|---|
| **Linux / WSL** | rien de spécial : `\n` est écrit tel quel | identique au mode texte |
| **Windows** | `\n` écrit devient `\r\n` sur le disque ; à la lecture `\r\n` redevient `\n` | **aucune traduction** : tu lis et écris exactement les octets |

Trois conséquences pratiques :

1. Un fichier écrit par ton programme sous Windows en mode texte pèse **une ligne = un octet de
   plus** que le même fichier sous Linux. `ftell`/`fseek` sur un fichier texte n'y donnent donc
   pas la même valeur.
2. Dès que tu manipules autre chose que du texte (images, `fwrite` d'une `struct`), **utilise
   toujours `"rb"`/`"wb"`** : en mode texte, un octet `0x0A` au milieu de tes données serait
   corrompu en `0x0D 0x0A`.
3. Si tu lis sous Linux un fichier produit sous Windows, tes lignes se terminent par un `\r`
   parasite que `fgets` te rendra. Pour le nettoyer :

   ```c
   ligne[strcspn(ligne, "\r\n")] = '\0';   // enleve \n ET \r\n
   ```

   Cet idiome remplace avantageusement le `ligne[strcspn(ligne, "\n")] = '\0'` habituel : il est
   correct sur les deux systèmes.

> 💡 Si tu versionnes tes fichiers avec Git sous Windows, configure une bonne fois
> `git config --global core.autocrlf input` pour ne pas committer des `\r\n`.

> ⚠️ `"w"` **efface tout le contenu existant** sans prévenir. Si tu veux ajouter, c'est `"a"`.

## Toujours vérifier l'ouverture

```c
FILE *f = fopen("donnees.txt", "r");
if (f == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier\n");
    return 1;
}
```

Sans cette vérification, la première opération sur un `FILE *` à `NULL` fait planter le programme.
Pour un message précis :

```c
#include <errno.h>
#include <string.h>

if (f == NULL) {
    fprintf(stderr, "Erreur : %s\n", strerror(errno));   // "No such file or directory"
    return 1;
}
```

## Écrire dans un fichier

```c
#include <stdio.h>

int main(void) {
    FILE *f = fopen("notes.txt", "w");
    if (f == NULL) { perror("fopen"); return 1; }

    fprintf(f, "Tidiane;15.5\n");        // comme printf, mais vers le fichier
    fprintf(f, "Awa;17.0\n");
    fputs("Moussa;12.5\n", f);           // comme puts, sans ajouter de \n

    fclose(f);                           // ⚠️ indispensable
    return 0;
}
```

`fclose` vide le tampon sur le disque et libère la ressource. **Sans lui, tes données peuvent
être perdues** — l'écriture est mise en tampon, pas immédiate.

Mode ajout :

```c
FILE *f = fopen("notes.txt", "a");
fprintf(f, "Fatou;19.0\n");     // ajoute a la fin, sans effacer
fclose(f);
```

## Lire un fichier

### Ligne par ligne — la méthode recommandée

```c
FILE *f = fopen("notes.txt", "r");
if (f == NULL) { perror("fopen"); return 1; }

char ligne[256];
while (fgets(ligne, sizeof(ligne), f) != NULL) {
    printf("%s", ligne);        // la ligne contient deja son \n
}
fclose(f);
```

`fgets` renvoie `NULL` à la fin du fichier : c'est la condition d'arrêt.

### Caractère par caractère

```c
int c;                          // int, pas char : EOF ne tient pas dans un char !
while ((c = fgetc(f)) != EOF) {
    putchar(c);
}
```

### Données formatées

```c
char nom[50];
float note;
while (fscanf(f, "%49[^;];%f\n", nom, &note) == 2) {
    printf("%s a eu %.1f\n", nom, note);
}
```

`%49[^;]` lit jusqu'au `;` (au plus 49 caractères). `fscanf` renvoie le nombre de champs lus :
tester `== 2` garantit que la ligne était bien formée.

> Conseil : pour un vrai parseur, préfère `fgets` + `sscanf` ou `strtok`. `fscanf` se désynchronise
> vite dès qu'une ligne est mal formée.

## Découper une ligne avec `strtok`

```c
char ligne[] = "Tidiane;15.5;Dakar";
char *champ = strtok(ligne, ";");
while (champ != NULL) {
    printf("[%s]\n", champ);
    champ = strtok(NULL, ";");     // NULL = "continue la meme chaine"
}
```

⚠️ `strtok` **modifie** la chaîne d'origine (elle y insère des `'\0'`). Ne l'utilise pas sur une
chaîne littérale.

## Les autres fonctions utiles

| Fonction | Rôle |
|---|---|
| `feof(f)` | vrai si la fin du fichier a été atteinte |
| `ferror(f)` | vrai si une erreur est survenue |
| `rewind(f)` | revient au début |
| `fseek(f, offset, origine)` | se déplace (`SEEK_SET`, `SEEK_CUR`, `SEEK_END`) |
| `ftell(f)` | position courante en octets |
| `remove("f.txt")` | supprime un fichier |
| `rename("a", "b")` | renomme |
| `fflush(f)` | force l'écriture du tampon |

> ⚠️ N'écris **jamais** `while (!feof(f))` pour lire : `feof` ne devient vrai qu'**après** une
> lecture ratée, ce qui te fait traiter une dernière ligne fantôme. Teste toujours la valeur de
> retour de `fgets` / `fscanf`.

### Taille d'un fichier

```c
fseek(f, 0, SEEK_END);
long taille = ftell(f);
rewind(f);
printf("%ld octets\n", taille);
```

## Les trois flux toujours ouverts

| Flux | Rôle |
|---|---|
| `stdin` | entrée standard (clavier) |
| `stdout` | sortie standard (écran) |
| `stderr` | sortie d'erreur (écran, non tamponnée) |

```c
printf("bonjour\n");                     // = fprintf(stdout, …)
fprintf(stderr, "Erreur critique\n");    // messages d'erreur
```

Écrire les erreurs sur `stderr` permet de les séparer au terminal.

**Linux / WSL** (et shell MSYS2)

```bash
./prog > sortie.txt 2> erreurs.txt
```

**Windows — PowerShell**

```powershell
.\prog.exe > sortie.txt 2> erreurs.txt
```

## Programme complet

Fichier [`code/27_fichiers.c`](code/27_fichiers.c) — écrit un fichier, le relit, puis y ajoute
une ligne.

## Exercice

1. Écris un programme qui crée `journal.txt` et y écrit 5 lignes.
2. Relis le fichier et affiche-le en numérotant les lignes.
3. Compte le nombre de lignes, de mots et de caractères d'un fichier (une mini-commande `wc`).
4. Lis un fichier CSV `nom;note` et affiche la moyenne de la classe.
5. Copie un fichier vers un autre, caractère par caractère.

---
⬅️ [26 — Fonctions mathématiques](26-fonctions-mathematiques.md) | ➡️ [28 — Structures](28-structures.md)
