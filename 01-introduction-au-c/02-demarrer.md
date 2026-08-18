# 02 — Démarrer : installer, compiler, exécuter

> Équivalent W3Schools : **C Get Started**

W3Schools te propose son éditeur en ligne. Ici on fait ce que font les vrais développeurs C :
**VS Code + terminal**.

## 1. Vérifier le compilateur

Un fichier `.c` n'est pas exécutable tel quel : il doit être traduit en langage machine par un
**compilateur**. Sur Linux/WSL, c'est `gcc`.

```bash
gcc --version
```

Si la commande répond une version, tout est prêt. Sinon :

```bash
sudo apt update && sudo apt install build-essential
```

`build-essential` installe `gcc`, `make` et les en-têtes standard d'un coup.

## 2. Configurer VS Code

- Installe l'extension **C/C++** de Microsoft (`ms-vscode.cpptools`) : coloration, autocomplétion,
  aller-à-la-définition, détection d'erreurs en direct.
- Optionnel mais très utile : **Code Runner** (`formulahendry.code-runner`) pour lancer un fichier
  avec `Ctrl+Alt+N`.
- Sous WSL, ouvre le dossier avec `code .` depuis le terminal WSL pour que VS Code utilise le
  `gcc` de Linux et non celui de Windows.

## 3. Ton premier programme

Crée un fichier `hello.c` :

```c
#include <stdio.h>

int main(void) {
    printf("Hello World!");
    return 0;
}
```

## 4. Compiler et exécuter

```bash
gcc hello.c -o hello   # compile hello.c et produit un exécutable nommé "hello"
./hello                # lance l'exécutable
```

Résultat :

```
Hello World!
```

### Décomposition de la commande

| Morceau | Rôle |
|---|---|
| `gcc` | le compilateur |
| `hello.c` | le fichier source |
| `-o hello` | nom du fichier de sortie (**o** comme *output*). Sans lui, gcc crée `a.out` |
| `./hello` | exécute le binaire situé dans le dossier courant (`.`) |

### La commande à utiliser pendant tout l'apprentissage

```bash
gcc -Wall -Wextra -std=c17 hello.c -o hello && ./hello
```

- `-Wall -Wextra` : affiche **tous les avertissements**. En C, un avertissement est presque
  toujours un vrai bug qui t'attend. Prends l'habitude de les lire.
- `-std=c17` : fixe la version du langage (C17, la norme stable actuelle).
- `&&` : n'exécute que si la compilation a réussi.

### Enchaîner rapidement

Un petit alias à mettre dans ton `~/.zshrc` :

```bash
crun() { gcc -Wall -Wextra -std=c17 "$1" -o /tmp/crun_out && /tmp/crun_out; }
```

Ensuite : `crun hello.c`.

## 5. Que se passe-t-il à la compilation ?

```
hello.c  →  [préprocesseur]  →  [compilateur]  →  [assembleur]  →  [éditeur de liens]  →  hello
            (traite #include)   (produit l'asm)   (produit .o)     (lie la libc)          (binaire)
```

Tu peux voir chaque étape :

```bash
gcc -E hello.c > hello.i   # 1. préprocesseur seul
gcc -S hello.c             # 2. produit hello.s (assembleur)
gcc -c hello.c             # 3. produit hello.o (code objet)
gcc hello.o -o hello       # 4. édition de liens
```

Ce n'est pas à retenir maintenant, mais garde en tête que « compiler » = 4 étapes.

## Erreurs de débutant fréquentes

| Message | Cause |
|---|---|
| `gcc: command not found` | compilateur non installé |
| `hello.c:5: error: expected ';' before …` | point-virgule oublié à la ligne **précédente** |
| `undefined reference to 'main'` | pas de fonction `main` |
| `Permission denied` en lançant `./hello` | fichier non exécutable → `chmod +x hello` |
| `bash: hello: command not found` | tu as oublié le `./` devant |

## Exercice

Écris, compile et exécute un programme qui affiche ton prénom. Puis enlève volontairement le
`;` après `printf`, recompile, et **lis attentivement** le message d'erreur : apprendre à lire
gcc fait partie du métier.

---
⬅️ [01 — Introduction](01-introduction.md) | ➡️ [03 — Syntaxe](03-syntaxe.md)
