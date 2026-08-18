# Aide-mémoire gcc et terminal

Toutes les commandes sont données pour les **deux systèmes**.
Le shell **MSYS2** (menu Démarrer) étant un bash, la colonne « Linux / WSL » y fonctionne telle
quelle ; la colonne « Windows » s'adresse à **PowerShell**.

## Compiler

| | **Linux / WSL** | **Windows (PowerShell)** |
|---|---|---|
| Compiler, nom par défaut | `gcc prog.c` → `a.out` | `gcc prog.c` → `a.exe` |
| Compiler, nom choisi | `gcc prog.c -o prog` | `gcc prog.c -o prog.exe` |
| Exécuter | `./prog` | `.\prog.exe` |
| Compiler **et** exécuter | `gcc prog.c -o prog && ./prog` | `gcc prog.c -o prog.exe`<br>`if ($?) { .\prog.exe }` |

> `&&` fonctionne aussi dans PowerShell **7** ; Windows PowerShell 5.1 (celui livré par défaut)
> ne le connaît pas — d'où le `if ($?)`.

### La commande d'apprentissage

**Linux / WSL**

```bash
gcc -Wall -Wextra -std=c17 prog.c -o prog && ./prog
```

**Windows — PowerShell**

```powershell
gcc -Wall -Wextra -std=c17 prog.c -o prog.exe
if ($?) { .\prog.exe }
```

## Les options utiles

Identiques sur les deux systèmes, sauf mention contraire.

| Option | Effet |
|---|---|
| `-o nom` | nom du fichier de sortie |
| `-Wall` | avertissements courants |
| `-Wextra` | avertissements supplémentaires |
| `-Wpedantic` | conformité stricte à la norme |
| `-Werror` | transforme les avertissements en erreurs |
| `-std=c17` | version du langage (`c99`, `c11`, `c17`) |
| `-g` | infos de débogage (nécessaire pour gdb/valgrind) |
| `-O0` … `-O3` | niveau d'optimisation (`-O0` pour déboguer) |
| `-lm` | lie la bibliothèque math (**après** les sources). Obligatoire sous Linux, sans effet sous Windows |
| `-c` | compile sans lier (produit un `.o`) |
| `-I dossier` | ajoute un dossier d'en-têtes |
| `-fsanitize=address,undefined` | détecte les erreurs mémoire à l'exécution. **Linux / WSL uniquement** — MinGW-w64 n'a pas `libasan` |
| `-fstack-protector-all` | détecte les débordements de pile. Les deux systèmes |
| `-E` / `-S` | s'arrête après le préprocesseur / la génération d'assembleur |
| `-municode` | **Windows** : `wmain` au lieu de `main`, pour recevoir un `argv` en UTF-16 |

## Plusieurs fichiers

**Linux / WSL**

```bash
gcc -Wall -Wextra -std=c17 main.c module.c -o prog
```

**Windows — PowerShell**

```powershell
gcc -Wall -Wextra -std=c17 main.c module.c -o prog.exe
```

## Débogage

| | **Linux / WSL** | **Windows** |
|---|---|---|
| Compiler avec symboles | `gcc -g prog.c -o prog` | `gcc -g prog.c -o prog.exe` |
| Débogueur | `gdb ./prog` | `gdb .\prog.exe` |
| Détecteur de fuites | `valgrind --leak-check=full ./prog` | `drmemory -- .\prog.exe` |
| Sanitizers | `gcc -fsanitize=address,undefined -g prog.c -o prog && ./prog` | ❌ indisponible (`cannot find -lasan`) |

Les commandes **à l'intérieur** de `gdb` sont identiques :
`run`, `break N`, `next`, `step`, `print x`, `backtrace`, `quit`.

## Makefile minimal

```makefile
CC     = gcc
CFLAGS = -Wall -Wextra -std=c17 -g

ifeq ($(OS),Windows_NT)
  EXE := .exe
else
  EXE :=
endif

prog$(EXE): main.o module.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o prog$(EXE)
```

⚠️ Les commandes d'une règle sont indentées par une **tabulation**, jamais par des espaces.

⚠️ Sous Windows, la commande s'appelle **`mingw32-make`**. Pour taper `make` comme sous Linux :
`Set-Alias make mingw32-make` dans ton `$PROFILE`. Et si tu lances make depuis PowerShell, le
shell des règles est `cmd.exe` : `rm -f` n'existe pas, il faut `del /q`. Le `Makefile` de
[`code/`](../code/Makefile) montre comment gérer les deux cas.

## Terminal

| Effet | **Linux / WSL** | **Windows (PowerShell)** |
|---|---|---|
| Exécuter | `./prog` | `.\prog.exe` |
| Code de retour du dernier programme | `echo $?` | `$LASTEXITCODE` |
| Le dernier a-t-il réussi ? | `[ $? -eq 0 ]` | `$?` (booléen) |
| Mesurer la durée | `time ./prog` | `Measure-Command { .\prog.exe }` |
| Rediriger la sortie | `./prog > sortie.txt` | `.\prog.exe > sortie.txt` |
| Rediriger les erreurs | `./prog 2> erreurs.txt` | `.\prog.exe 2> erreurs.txt` |
| Fournir l'entrée sans taper | `printf "5\n7\n" \| ./prog` | `"5", "7" \| .\prog.exe` |
| Interrompre un programme bloqué | `Ctrl + C` | `Ctrl + C` |
| Rendre exécutable | `chmod +x prog` | *sans objet* |
| Console en UTF-8 | déjà le cas | `chcp 65001` |
| Lister les fichiers | `ls` | `ls` (alias de `Get-ChildItem`) |
| Effacer l'écran | `clear` | `cls` |

## Où le C lui-même diffère

Voir la fiche [portabilite.md](portabilite.md) : taille de `long`, `\r\n`, `#ifdef _WIN32`…
