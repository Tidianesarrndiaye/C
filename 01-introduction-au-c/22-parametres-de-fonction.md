# 22 — Les paramètres de fonction

> Équivalent W3Schools : **C Function Parameters**

## Paramètres et arguments

```c
void saluer(char nom[]) {       // "nom" est un PARAMETRE
    printf("Bonjour %s !\n", nom);
}

int main(void) {
    saluer("Tidiane");          // "Tidiane" est un ARGUMENT
    return 0;
}
```

Plusieurs paramètres — chacun avec **son type**, séparés par des virgules :

```c
void afficher_fiche(char nom[], int age, float taille) {
    printf("%s, %d ans, %.2f m\n", nom, age, taille);
}
```

Le nombre et le type des arguments doivent correspondre exactement. Il n'y a **pas de valeur par
défaut** en C (contrairement à Python), et **pas de surcharge** de fonction (contrairement au C++).

## Le passage par valeur

**En C, les arguments sont toujours copiés.** La fonction travaille sur une copie ; l'original
n'est pas touché.

```c
void doubler(int x) {
    x = x * 2;
    printf("dans la fonction : %d\n", x);   // 20
}

int main(void) {
    int n = 10;
    doubler(n);
    printf("dans main : %d\n", n);          // 10 — inchange !
    return 0;
}
```

C'est le même comportement qu'en Python avec un `int`, ou en JavaScript avec un nombre.

## Le passage par adresse

Pour qu'une fonction modifie vraiment la variable, on lui passe son **adresse** :

```c
void doubler(int *x) {
    *x = *x * 2;
}

int main(void) {
    int n = 10;
    doubler(&n);            // on passe l'ADRESSE
    printf("%d\n", n);      // 20 ✅
    return 0;
}
```

Trois choses à remarquer :

1. Le paramètre est déclaré `int *x`.
2. Dans la fonction, on écrit `*x` pour atteindre la valeur.
3. À l'appel, on écrit `&n`.

### L'exemple canonique : échanger deux valeurs

```c
void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int x = 5, y = 10;
    echanger(&x, &y);
    printf("x=%d y=%d\n", x, y);   // x=10 y=5
    return 0;
}
```

Sans pointeurs, cette fonction est **impossible** à écrire en C. C'est le meilleur exercice pour
vérifier que tu as compris.

### Renvoyer plusieurs valeurs

Une fonction C ne renvoie qu'une valeur. Les pointeurs contournent la limite :

```c
void min_max(int tab[], int n, int *min, int *max) {
    *min = *max = tab[0];
    for (int i = 1; i < n; i++) {
        if (tab[i] < *min) *min = tab[i];
        if (tab[i] > *max) *max = tab[i];
    }
}

int mn, mx;
min_max(notes, 5, &mn, &mx);
```

C'est un idiome que tu retrouveras partout dans les API C (`scanf`, `fscanf`, `strtol`…).

## Les tableaux sont toujours passés par adresse

```c
void modifier(int tab[], int taille) {
    tab[0] = 999;              // modifie le TABLEAU D'ORIGINE
}

int main(void) {
    int notes[3] = {1, 2, 3};
    modifier(notes, 3);
    printf("%d\n", notes[0]);  // 999
    return 0;
}
```

Un tableau ne peut pas être copié en argument : le C passe l'adresse de sa première case. Ces
trois écritures sont **strictement équivalentes** :

```c
void f(int tab[]);     void f(int tab[10]);     void f(int *tab);
```

Conséquence importante : **`sizeof` ne marche plus dans la fonction** — il faut toujours passer la
taille :

```c
void afficher(int tab[], int taille) {
    for (int i = 0; i < taille; i++) printf("%d ", tab[i]);
}
```

### Protéger un tableau qu'on ne veut pas modifier

```c
void afficher(const int tab[], int taille) { … }   // le compilateur refusera toute ecriture
```

Prends l'habitude de mettre `const` sur les paramètres en lecture seule : c'est de la
documentation vérifiée par le compilateur.

## Les chaînes en paramètre

```c
void afficher_majuscules(const char *texte) {
    for (int i = 0; texte[i] != '\0'; i++) {
        putchar(toupper((unsigned char) texte[i]));
    }
    putchar('\n');
}
```

## Les arguments de la ligne de commande

`main` peut recevoir ce que tu tapes après le nom du programme :

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Nombre d'arguments : %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return 0;
}
```

**Linux / WSL** (et shell MSYS2)

```bash
./prog bonjour 42
# argc = 3
# argv[0] = ./prog
# argv[1] = bonjour
# argv[2] = 42
```

**Windows — PowerShell**

```powershell
.\prog.exe bonjour 42
# argc = 3
# argv[0] = C:\...\prog.exe      <- chemin complet, pas ".\prog.exe"
# argv[1] = bonjour
# argv[2] = 42
```

`argv[0]` est toujours le nom du programme — mais **sa forme exacte dépend du système** : le
texte tapé sous Linux, le chemin complet sous Windows. Ne t'en sers jamais pour autre chose que
l'affichage d'un message d'aide. Les arguments arrivent comme des **chaînes** :
pour un nombre, il faut convertir avec `atoi()` ou mieux `strtol()` (`<stdlib.h>`).

## Récapitulatif

| Je veux… | J'écris |
|---|---|
| Lire une valeur sans la modifier | `void f(int x)` |
| Modifier la variable de l'appelant | `void f(int *x)` puis `f(&n)` |
| Passer un tableau | `void f(int tab[], int n)` |
| Passer un tableau en lecture seule | `void f(const int tab[], int n)` |
| Renvoyer plusieurs résultats | des paramètres pointeurs de sortie |

## Exercice

1. Écris `void incrementer(int *n)` qui ajoute 1 à la variable passée.
2. Écris `void trier(int tab[], int n)` qui trie un tableau par ordre croissant (tri à bulles).
3. Écris `void statistiques(const int tab[], int n, float *moyenne, int *max)`.
4. Écris un programme qui additionne tous les nombres passés en arguments de la ligne de commande.

---
⬅️ [21 — Fonctions](21-fonctions.md) | ➡️ [23 — Portée (scope)](23-portee-scope.md)
