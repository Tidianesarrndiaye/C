# Étapes de compilation (chapitre 02)

`hello.c` sert de base à la démo des 4 étapes de compilation du chapitre
[02 — Démarrer](../../02-demarrer.md#6-que-se-passe-t-il-à-la-compilation) : préprocesseur,
compilation, assemblage, édition de liens.

Les fichiers générés (`hello.i`, `hello.s`, `hello.o`, `hello`/`hello.exe`) ne sont pas
versionnés : ils diffèrent selon le système (glibc vs UCRT) et se régénèrent en une commande.

```bash
gcc -E hello.c > hello.i   # 1. préprocesseur seul
gcc -S hello.c             # 2. produit hello.s (assembleur)
gcc -c hello.c             # 3. produit hello.o (code objet)
gcc hello.o -o hello       # 4. édition de liens
```

Pour comparer Linux/WSL et Windows, lance ces commandes séparément dans les deux environnements
et regarde les différences dans `hello.i` (en-têtes système) et `hello.s` (ABI).
