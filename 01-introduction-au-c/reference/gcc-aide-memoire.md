# Aide-mémoire gcc et terminal

## Compiler

```bash
gcc prog.c                       # produit a.out
gcc prog.c -o prog               # produit prog
./prog                           # executer
```

### La commande d'apprentissage

```bash
gcc -Wall -Wextra -std=c17 prog.c -o prog && ./prog
```

## Les options utiles

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
| `-lm` | lie la bibliothèque math (**après** les sources) |
| `-c` | compile sans lier (produit un `.o`) |
| `-I dossier` | ajoute un dossier d'en-têtes |
| `-fsanitize=address,undefined` | détecte les erreurs mémoire à l'exécution |
| `-E` / `-S` | s'arrête après le préprocesseur / la génération d'assembleur |

## Plusieurs fichiers

```bash
gcc -Wall -Wextra -std=c17 main.c module.c -o prog
```

## Débogage

```bash
gcc -g prog.c -o prog
gdb ./prog                       # run, break N, next, print x, backtrace, quit
valgrind --leak-check=full ./prog
gcc -fsanitize=address,undefined -g prog.c -o prog && ./prog
```

## Makefile minimal

```makefile
CC     = gcc
CFLAGS = -Wall -Wextra -std=c17 -g

prog: main.o module.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o prog
```

⚠️ Les commandes d'une règle sont indentées par une **tabulation**, jamais par des espaces.

## Terminal

| Commande | Effet |
|---|---|
| `./prog` | exécuter |
| `echo $?` | code de retour du dernier programme |
| `time ./prog` | mesurer la durée |
| `./prog > sortie.txt` | rediriger la sortie |
| `./prog 2> erreurs.txt` | rediriger les erreurs |
| `printf "5\n7\n" \| ./prog` | fournir l'entrée sans taper |
| `Ctrl + C` | interrompre un programme bloqué |
| `chmod +x prog` | rendre exécutable |
