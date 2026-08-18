# 02 — Démarrer : installer, compiler, exécuter

> Équivalent W3Schools : **C Get Started**

W3Schools te propose son éditeur en ligne. Ici on fait ce que font les vrais développeurs C :
**VS Code + terminal**.

Ce parcours est utilisable sur **deux environnements**, et chaque commande du cours est donnée
dans les deux versions.

## 1. Choisir son environnement

| | **Linux / WSL** | **Windows natif (MSYS2 / MinGW-w64)** |
|---|---|---|
| Compilateur | `gcc` fourni par la distribution | `gcc` de MinGW-w64, installé via MSYS2 |
| Ce que produit `gcc` | un binaire ELF (`hello`) | un exécutable Windows (`hello.exe`) |
| Terminal du cours | bash / zsh | PowerShell, **ou** le shell MSYS2 |
| Valgrind | ✅ | ❌ (voir chapitre 30) |
| Sanitizers (`-fsanitize`) | ✅ | ❌ dans MinGW-w64 |
| Taille de `long` | 8 octets | **4 octets** (voir chapitre 07) |

**Recommandation** : si tu es sous Windows, installe **WSL** — tu obtiens un vrai Linux, tous les
outils du cours fonctionnent, et c'est ce qu'utilise l'immense majorité du monde C. Garde
MSYS2 pour les cas où tu dois produire un `.exe` Windows.

> 💡 Le shell **MSYS2 MINGW64** (menu Démarrer) est un bash. Toutes les commandes de la colonne
> « Linux / WSL » y fonctionnent telles quelles (`./prog`, `/tmp`, `printf … |`). La colonne
> « Windows » du cours s'adresse à **PowerShell**.

## 2. Installer le compilateur

Un fichier `.c` n'est pas exécutable tel quel : il doit être traduit en langage machine par un
**compilateur**.

### Linux / WSL

```bash
gcc --version
```

Si la commande répond une version, tout est prêt. Sinon :

```bash
sudo apt update && sudo apt install build-essential gdb valgrind
```

`build-essential` installe `gcc`, `make` et les en-têtes standard d'un coup.

### Windows — MSYS2 / MinGW-w64

**Vérifie d'abord si tu l'as déjà.** Dans PowerShell :

```powershell
Get-Command gcc -All | Select-Object Source
gcc --version
gcc -dumpmachine        # doit repondre x86_64-w64-mingw32
```

Si `gcc` répond, tu es prêt — passe à la section suivante. Un IDE comme Code::Blocks, Dev-C++ ou
CLion a pu installer MSYS2 pour toi sans le dire.

#### Installation depuis zéro

1. Télécharge et installe MSYS2 depuis <https://www.msys2.org> (par défaut dans `C:\msys64`).
2. Lance **MSYS2 MINGW64** depuis le menu Démarrer — pas « MSYS2 MSYS » :

   | Raccourci | À quoi il sert |
   |---|---|
   | **MSYS2 MINGW64** | ✅ compiler des programmes **Windows natifs** 64 bits. C'est celui du cours |
   | MSYS2 UCRT64 | même chose, mais lié à l'UCRT (la runtime C plus récente de Windows 10/11). Aussi valable — voir l'encadré ci-dessous |
   | MSYS2 MSYS | administrer MSYS2 lui-même ; produit des binaires dépendants de `msys-2.0.dll`, **pas** de vrais programmes Windows |
   | MSYS2 CLANG64 | même chose avec clang au lieu de gcc |

3. Mets à jour, puis installe la chaîne d'outils :

   ```bash
   pacman -Syu                                        # peut demander de rouvrir le terminal
   pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-make
   ```

   Le groupe `toolchain` contient `gcc`, `gdb`, `binutils` — tout ce dont le cours a besoin.

4. Pour que `gcc` soit visible depuis **PowerShell** et VS Code, ajoute au `Path` Windows :

   ```
   C:\msys64\mingw64\bin
   ```

   *Paramètres → Système → Informations système → Paramètres système avancés → Variables
   d'environnement → `Path` → Nouveau.* Rouvre PowerShell et retape `gcc --version`.

#### `make` sous Windows

Le paquet MinGW installe la commande sous le nom **`mingw32-make`**, pas `make`. Trois façons de
s'en sortir :

```powershell
mingw32-make                                   # 1. taper le vrai nom
Set-Alias make mingw32-make                    # 2. alias (a mettre dans $PROFILE)
```

```bash
pacman -S make                                 # 3. installer aussi le make de MSYS2
```

#### MINGW64 ou UCRT64 : lequel ?

| | **MINGW64** | **UCRT64** |
|---|---|---|
| Runtime C liée | `msvcrt.dll` (présente sur tout Windows) | UCRT (Windows 10/11, ou redistribuable) |
| `printf("%zu")`, `%lld` | ✅ corrects — MinGW-w64 fournit son propre `printf` | ✅ corrects |
| Compatibilité vieux Windows | meilleure | Windows 10+ |
| Pour apprendre le C | **aucune différence pratique** | aucune différence pratique |

**N'installe pas les deux.** Tu te retrouverais avec deux `gcc` dans `C:\msys64`, et c'est
l'ordre du `Path` qui déciderait lequel s'exécute — source de bugs incompréhensibles. Reste sur
celui que tu as déjà.

### Windows — l'accentuation dans la console

La console Windows n'est pas en UTF-8 par défaut : `é` s'affichera `Ã©`. Une fois par session :

```powershell
chcp 65001
```

Ou, définitivement, dans ton profil PowerShell (`notepad $PROFILE`) :

```powershell
$OutputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::new()
chcp 65001 > $null
```

C'est aussi pour cette raison que les fichiers `code/*.c` de ce parcours sont écrits **sans
accents** (voir chapitre 05).

## 3. Configurer VS Code

Communs aux deux systèmes :

- Installe l'extension **C/C++** de Microsoft (`ms-vscode.cpptools`) : coloration, autocomplétion,
  aller-à-la-définition, détection d'erreurs en direct.
- Optionnel mais très utile : **Code Runner** (`formulahendry.code-runner`) pour lancer un fichier
  avec `Ctrl+Alt+N`.

### Linux / WSL

- Installe l'extension **WSL** (`ms-vscode-remote.remote-wsl`).
- Ouvre le dossier avec `code .` **depuis le terminal WSL**, pour que VS Code utilise le `gcc` de
  Linux et non celui de Windows. En bas à gauche tu dois lire `WSL: Ubuntu`.

### Windows natif

- Indique à l'extension C/C++ où est le compilateur. Palette (`Ctrl+Shift+P`) →
  *C/C++: Edit Configurations (UI)* → **Compiler path** :

  ```
  C:\msys64\mingw64\bin\gcc.exe
  ```

  et **IntelliSense mode** : `windows-gcc-x64`.
- Pour que le terminal intégré soit celui de MSYS2, ajoute dans `settings.json` :

  ```json
  "terminal.integrated.profiles.windows": {
    "MINGW64": {
      "path": "C:\\msys64\\usr\\bin\\bash.exe",
      "args": ["--login", "-i"],
      "env": { "MSYSTEM": "MINGW64", "CHERE_INVOKING": "1" }
    }
  }
  ```

## 4. Ton premier programme

Crée un fichier `hello.c` — identique sur les deux systèmes :

```c
#include <stdio.h>

int main(void) {
    printf("Hello World!");
    return 0;
}
```

## 5. Compiler et exécuter

**Linux / WSL** (et shell MSYS2)

```bash
gcc hello.c -o hello   # compile hello.c et produit un executable nomme "hello"
./hello                # lance l'executable
```

**Windows — PowerShell**

```powershell
gcc hello.c -o hello.exe   # compile hello.c et produit hello.exe
.\hello.exe                # lance l'executable
```

Résultat, dans les deux cas :

```
Hello World!
```

### Décomposition de la commande

| Morceau | Rôle |
|---|---|
| `gcc` | le compilateur |
| `hello.c` | le fichier source |
| `-o hello` / `-o hello.exe` | nom du fichier de sortie (**o** comme *output*). Sans lui, gcc crée `a.out` (Linux) ou `a.exe` (Windows) |
| `./hello` / `.\hello.exe` | exécute le binaire situé dans le dossier courant (`.`) |

> Sous MinGW, `gcc hello.c -o hello` (sans extension) produit quand même `hello.exe` : gcc ajoute
> `.exe` tout seul. Écris quand même `-o hello.exe`, c'est plus clair.

### La commande à utiliser pendant tout l'apprentissage

**Linux / WSL**

```bash
gcc -Wall -Wextra -std=c17 hello.c -o hello && ./hello
```

**Windows — PowerShell**

```powershell
gcc -Wall -Wextra -std=c17 hello.c -o hello.exe
if ($?) { .\hello.exe }
```

- `-Wall -Wextra` : affiche **tous les avertissements**. En C, un avertissement est presque
  toujours un vrai bug qui t'attend. Prends l'habitude de les lire.
- `-std=c17` : fixe la version du langage (C17, la norme stable actuelle).
- `&&` / `if ($?)` : n'exécute que si la compilation a réussi. Windows PowerShell 5.1 ne connaît
  pas `&&` ; PowerShell 7 le connaît, et tu peux alors écrire la même ligne que sous Linux.

### Enchaîner rapidement

**Linux / WSL** — dans ton `~/.zshrc` (ou `~/.bashrc`) :

```bash
crun() { gcc -Wall -Wextra -std=c17 "$1" -o /tmp/crun_out && /tmp/crun_out; }
```

**Windows — PowerShell** — dans ton profil (`notepad $PROFILE`) :

```powershell
function crun {
    param([string]$f)
    gcc -Wall -Wextra -std=c17 $f -o "$env:TEMP\crun.exe"
    if ($?) { & "$env:TEMP\crun.exe" }
}
```

Ensuite, des deux côtés : `crun hello.c`.

## 6. Que se passe-t-il à la compilation ?

```
hello.c  →  [préprocesseur]  →  [compilateur]  →  [assembleur]  →  [éditeur de liens]  →  hello
            (traite #include)   (produit l'asm)   (produit .o)     (lie la libc)          (binaire)
```

Tu peux voir chaque étape (mêmes commandes sur les deux systèmes) :

```bash
gcc -E hello.c > hello.i   # 1. preprocesseur seul
gcc -S hello.c             # 2. produit hello.s (assembleur)
gcc -c hello.c             # 3. produit hello.o (code objet)
gcc hello.o -o hello       # 4. edition de liens
```

Ce n'est pas à retenir maintenant, mais garde en tête que « compiler » = 4 étapes.

Seule la dernière étape diffère vraiment : sous Linux elle lie la **glibc** et produit un ELF ;
sous Windows elle lie l'**UCRT** et produit un PE (`.exe`).

## Erreurs de débutant fréquentes

| Message | Cause | Système |
|---|---|---|
| `gcc: command not found` / `gcc n'est pas reconnu…` | compilateur non installé, ou `C:\msys64\mingw64\bin` absent du `Path` | les deux |
| `hello.c:5: error: expected ';' before …` | point-virgule oublié à la ligne **précédente** | les deux |
| `undefined reference to 'main'` | pas de fonction `main` | les deux |
| `Permission denied` en lançant `./hello` | fichier non exécutable → `chmod +x hello` | Linux / WSL |
| `bash: hello: command not found` | tu as oublié le `./` devant | Linux / WSL |
| `hello : le terme « hello » n'est pas reconnu…` | tu as oublié le `.\` devant | Windows |
| Sortie pleine de `Ã©`, `Ã¨` | console pas en UTF-8 → `chcp 65001` | Windows |
| `impossible de charger le fichier … profile.ps1` | politique d'exécution → `Set-ExecutionPolicy -Scope CurrentUser RemoteSigned` | Windows |

## Exercice

Écris, compile et exécute un programme qui affiche ton prénom. Puis enlève volontairement le
`;` après `printf`, recompile, et **lis attentivement** le message d'erreur : apprendre à lire
gcc fait partie du métier.

---
⬅️ [01 — Introduction](01-introduction.md) | ➡️ [03 — Syntaxe](03-syntaxe.md)
